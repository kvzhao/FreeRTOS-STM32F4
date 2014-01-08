#ifndef _SERVO_H_
#define _SERVO_H_

#include "FreeRTOS.h"
#include "stm32f4xx.h"

#define PERIOD     20 /* micro-sec */
#define SERVO_0    1
#define SERVO_180  2

void Servo_Configuration();
void servo_set_pos(uint8_t angle /* degree */, uint8_t ch);

#endif
