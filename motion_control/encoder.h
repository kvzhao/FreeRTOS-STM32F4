#ifndef __ENCODER__
#define __ENCODER__

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

// Three Omni-wheel named as R(ight), L(eft) and H(orizontal).
//
// Right wheel channel
//  Phase A
#define ENCA_R_Pin      GPIO_Pin_6
#define ENCA_R_Port     GPIOB
#define ENCA_R_GPIO_CLK RCC_AHB1Periph_GPIOB
#define ENCA_R_Source   GPIO_PinSource6
#define ENCA_R_AF       PGIO_AF_TIM4
// Phase B
#define ENCB_R_Pin      GPIO_Pin_7
#define ENCB_R_Port     GPIOB
#define ENCB_R_GPIO_CLK RCC_AHB1Periph_GPIOB
#define ENCB_R_Source   GPIO_PinSource7
#define ENCB_R_AF       PGIO_AF_TIM4
// Determine the timer
#define ENC_R_TIM      TIM4
#define ENC_R_TIMCLK   RCC_APB1Periph_TIM4
// Count
#define RIGHT_COUNT()   ENC_R_TIM->CNT

void encoder_Configuration();

#endif
