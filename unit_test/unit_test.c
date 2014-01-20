#include "unit_test.h"
#include "serial_io.h"

// Application
#include "arm.h"
#include "servo.h"
// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

static void test_servo_turn()
{
        servo_set_pos(0,60);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(0,120);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(0,60);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(0,180);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);
}

void test_task(void *pvParameters)
{
    while (1) {
        /* Test Servo motor */
        my_printf("Servo motor test starts!\n\r");
        test_servo_turn();
        my_printf("Servo motor test end.\n\r");
        vTaskDelay(1000);

    }
    vTaskDelete(NULL);
}
