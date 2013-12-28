#include "servo.h"

void TIM4_PWM_Configuration()
{
    /* RCC Initialization */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Timer 4 Initialization */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef       TIM_OCInitStruct;

    // Set PWM frequency equal 100 Hz.which is standard frequency of servo
    // Let period equal 1000. Therefore, timer runs from zero to 1000. Gives 0.1Hz resolution.
    // Solving for prescaler gives 240.

    TIM_TimeBaseStructInit( &TIM_TimeBaseInitStruct );
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_TimeBaseInitStruct.TIM_Period = 3360 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 500 - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStruct );

    TIM_OCStructInit( &TIM_OCInitStruct );
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;

    // Initial duty cycle equals 0%. Value can range from zero to 65535.
    // TIM_Pulse = TIM4_CCR1 register (16 bits)
    TIM_OCInitStruct.TIM_Pulse = 0;

    TIM_OC1Init( TIM4, &TIM_OCInitStruct ); // Channel 1  LED
    TIM_OC2Init( TIM4, &TIM_OCInitStruct ); // Channel 2  LED
    TIM_OC3Init( TIM4, &TIM_OCInitStruct ); // Channel 3  LED
    TIM_OC4Init( TIM4, &TIM_OCInitStruct ); // Channel 4  LED

    TIM_Cmd( TIM4, ENABLE );

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure); // Reset init structure

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

    // Setup Blue & Green LED on STM32-Discovery Board to use PWM.
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            // Alt Function - Push Pull
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init( GPIOD, &GPIO_InitStructure );
}

void Servo_Configuration()
{
    /* Set the period of PWM is 20 ms (f=50 Hz) */
    TIM4_PWM_Configuration();
}

void Servo_set_pos (uint8_t angle, uint8_t ch)
{
    uint32_t cval = TIM4->ARR / (10 + 10*angle/180);
    switch (ch) {
        case 0:
            TIM4->CCR1 = cval;
            break;
        case 1:
            TIM4->CCR2 = cval;
            break;
        case 2:
            TIM4->CCR3 = cval;
            break;
        case 3:
            TIM4->CCR4 = cval;
            break;
    }
    vTaskDelay(50);
}

