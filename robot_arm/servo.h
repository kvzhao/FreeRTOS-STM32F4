#ifndef _SERVO_H_
#define _SERVO_H_

#include "FreeRTOS.h"
#include "stm32f4xx.h"

// Specs of MG-995 servo
// PWM Frequency : 50Hz
// Duty : 5% ~ 10%
#define SERVO_0    100/* counter */
#define SERVO_180  420/* counter */

void Servo_Configuration();
void servo_set_pos(uint8_t ch, uint16_t angle /* degree */);

#endif
