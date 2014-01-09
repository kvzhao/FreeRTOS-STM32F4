/* Standard function */
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
/* Customized function */
#include "serial_io.h"
#include "sys_manager.h"
/* STM32F4 */
#include "FreeRTOSConfig.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"

volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string

/*
 * Configure USART3(PB10, PB11) to redirect my_printf data to host PC.
 */
void USART3_Configuration(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

  USART_InitStruct.USART_BaudRate = 57600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART3, &USART_InitStruct);

  /* USART for receiving data */
  NVIC_InitTypeDef NVIC_InitStructure;
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;       // we want to configure the USART3 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY +2;
    // this sets the priority group of the USART3 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // the USART3 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    USART_Cmd(USART3, ENABLE);
}

void Serial_Configuration(void)
{
    USART3_Configuration();
}

char getch_base()
{
    serial_msg msg;
    while(!xQueueReceive(serial_rx_queue, &msg, portMAX_DELAY));
    return msg.ch;
}

void putch_base(char c)
{
    while(!xSemaphoreTake(serial_tx_wait_sem, portMAX_DELAY));
    USART_SendData(USART3, (uint16_t)c);
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

/* Serial read/write callback functions */
serial_ops serial = {
    .getch = getch_base,
    .putch = putch_base,
};

int putstr(const char *msg)
{
    for(;*msg;++msg)
        serial.putch(*msg);
    return 1;
}

int getstr(void)
{
    char str;
    str = serial.getch();
    my_printf("%c",str);
    return 1;
}

char *itoa(int value, char *str)
{
	int base = 10;
	int divideNum = base;
	int i = 0;

	if (value < 0) {
		str[0] = '-';
		i++;
		value *= -1;
	}

	while (value / divideNum > 0) {
		divideNum *= base;
	}



	while (divideNum / base > 0) {
		divideNum /= base;
		str[i++] = value / divideNum + 48;
		value %= divideNum;
	}

	str[i] = '\0';
	return str;

}

void ltoa(char *buf, unsigned long i, int base)
{
	char *s;
#define LEN        25
	int rem;
	char rev[LEN + 1];

	if (i == 0)
		s = "0";
	else {
		rev[LEN] = 0;
		s = &rev[LEN];

		while (i) {
			rem = i % base;

			if (rem < 10)
				*--s = rem + '0';
			else if (base == 16)
				*--s = "abcdef"[rem - 10];

			i /= base;
		}
	}

	strcpy(buf, s);
}

typedef union {
	long        L;
	float        F;
}         LF_t;

char *ftoa(float f) //, int *status)
{
	long mantissa, int_part, frac_part;
	short exp2;
	LF_t x;
	char *p;
	static char outbuf[15];

	//*status = 0;
	if (f == 0.0) {
		outbuf[0] = '0';
		outbuf[1] = '.';
		outbuf[2] = '0';
		outbuf[3] = 0;
		return outbuf;
	}

	x.F = f;

	exp2 = (unsigned char)(x.L >> 23) - 127;
	mantissa = (x.L & 0xFFFFFF) | 0x800000;
	frac_part = 0;
	int_part = 0;

	if (exp2 >= 31) {
		//*status = _FTOA_TOO_LARGE;
		return 0;

	} else if (exp2 < -23) {
		//*status = _FTOA_TOO_SMALL;
		return 0;

	} else if (exp2 >= 23)
		int_part = mantissa << (exp2 - 23);
	else if (exp2 >= 0) {
		int_part = mantissa >> (23 - exp2);
		frac_part = (mantissa << (exp2 + 1)) & 0xFFFFFF;

	} else /* if (exp2 < 0) */
		frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

	p = outbuf;

	if (x.L < 0)
		*p++ = '-';

	if (int_part == 0)
		*p++ = '0';
	else {
		ltoa(p, int_part, 10);

		while (*p)
			p++;
	}

	*p++ = '.';

	if (frac_part == 0)
		*p++ = '0';
	else {
		char m, max;

		max = sizeof(outbuf) - (p - outbuf) - 1;

		if (max > 7)
			max = 7;

		/* print BCD */
		for (m = 0; m < max; m++) {
			/* frac_part *= 10;        */
			frac_part = (frac_part << 3) + (frac_part << 1);

			*p++ = (frac_part >> 24) + '0';
			frac_part &= 0xFFFFFF;
		}

		/* delete ending zeroes */
		for (--p; p[0] == '0' && p[-1] != '.'; --p)
			;

		++p;
	}

	*p = 0;

	return outbuf;
}

double atof(const char *s)
{
	int sign = 1;
	int i = 0;
	for( i=0; isspace((unsigned char)s[i]); i++ );

	sign = (s[i] == '-')? -1:1;

	if( s[i] == '+' || s[i] == '-' )
		i++;

	double num = 0.0;
	double pow = 1.0;
	//整數
	for( ;isdigit((unsigned char)s[i]); i++ )
		num = num*10 + (s[i]-'0');

	for( i++; isdigit((unsigned char)s[i]); i++ )
	{
		num = num*10 + (s[i]-'0');
		pow *= 10;
	}

	return sign * (num/pow);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : smy_printf
**功能 :
**輸入 : ( char * str, const char * format, ... )
**輸出 : strlen(str)
**使用 :
**=====================================================================================================*/
/*=====================================================================================================*/

int smy_printf(char *str, const char *format, ...)
{
	va_list para;
	va_start(para, format);
	int curr_pos = 0;
	char ch[] = {'0', '\0'};
	char integer[11];
	str[0] = '\0';

	while (format[curr_pos] != '\0') {
		if (format[curr_pos] != '%') {
			ch[0] = format[curr_pos];
			strcat(str, ch);

		} else {
			switch (format[++curr_pos]) {
			case 's':
				strcat(str, va_arg(para, char *));
				break;

			case 'c':
				ch[0] = (char)va_arg(para, int);
				strcat(str, ch);
				break;

			case 'i':
			case 'f':
				strcat(str, ftoa(va_arg(para, double)));
				break;

			case 'd':
				strcat(str, itoa(va_arg(para, int), integer));
				break;

			case 'u':
				strcat(str, itoa(va_arg(para, unsigned), integer));
				break;

			default:
				break;
			}
		}

		curr_pos++;
	}

	va_end(para);
	return strlen(str);
}

/*=====================================================================================================*
**函數 : my_printf
**功能 :
**輸入 :
**輸出 : RS232_SendData(USART3, str, strlen(str));
**使用 :
**=====================================================================================================*/
/*=====================================================================================================*/

int my_printf(const char *format, ...)
{
	char str[128];
	va_list para;
	va_start(para, format);
	int curr_pos = 0;
	char ch[] = {'0', '\0'};
	char integer[11];
	str[0] = '\0';

	while (format[curr_pos] != '\0') {
		if (format[curr_pos] != '%') {
			ch[0] = format[curr_pos];
			strcat(str, ch);

		} else {
			switch (format[++curr_pos]) {
			case 's':
				strcat(str, va_arg(para, char *));
				break;

			case 'c':
				ch[0] = (char)va_arg(para, int);
				strcat(str, ch);
				break;

			case 'i':
			case 'f':
				strcat(str, ftoa(va_arg(para, double)));
				break;

			case 'd':
				strcat(str, itoa(va_arg(para, int), integer));
				break;

			case 'u':
				strcat(str, itoa(va_arg(para, unsigned), integer));
				break;

			default:
				break;
			}
		}

		curr_pos++;
	}

	va_end(para);
	putstr(str);
	return 1;
}
