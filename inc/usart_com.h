#ifndef _USART_COM_H_
#define _USART_COM_H_

#include "stm32f4xx.h"
#include "misc.h"            // I recommend you have a look at these in the ST firmware folder
#include "stm32f4xx_usart.h" // under Libraries/STM32F4xx_StdPeriph_Driver/inc and src

#define MAX_CMD_LEN 6 // this is the maximum string length of our string in characters
extern volatile char received_cmd[MAX_CMD_LEN+1]; // this will hold the recieved string

void USART1_COM_Configuration(uint32_t baudrate);
void command_send (USART_TypeDef* USARTx, volatile char *s);

#endif
