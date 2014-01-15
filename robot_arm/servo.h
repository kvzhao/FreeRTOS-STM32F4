#ifndef _SERVO_H_
#define _SERVO_H_

#include "FreeRTOS.h"
#include "stm32f4xx.h"

// Specs of MG-995 servo
#define PERIOD     20 /* micro-sec */
#define SERVO_0    1  /* micro-sec */
#define SERVO_180  2  /* micro-sec */

void Servo_Configuration();
void servo_set_pos(uint8_t ch, uint8_t angle /* degree */);

#endif
