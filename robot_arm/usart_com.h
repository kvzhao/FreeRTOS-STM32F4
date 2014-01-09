#ifndef _USART_COM_H_
#define _USART_COM_H_

#include "stm32f4xx.h"
#include "misc.h"            // I recommend you have a look at these in the ST firmware folder
#include "stm32f4xx_usart.h" // under Libraries/STM32F4xx_StdPeriph_Driver/inc and src

#define CMD_LEN 6 // this is the maximum string length of our string in characters
extern volatile char received_cmd[]; // this will hold the recieved string

typedef struct {
    char ch;
} com_msg;

typedef struct {
    char (*getch)();
    void (*putch)(char c);
} com_ops;

extern com_ops com;

void USART1_COM_Configuration(uint32_t baudrate);

int com_echo(const char*);

#endif
