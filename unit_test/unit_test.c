#include "unit_test.h"
#include "serial_io.h"
#include "FreeRTOS.h"
#include "task.h"

void test_servo_task()
{
        servo_set_pos(60,0);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(120,0);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(60,0);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        servo_set_pos(180,0);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);
}

void test_task(void *pvParameters)
{
    while (1) {
        /* Test Servo motor */
        my_printf("Servo motor test starts!\n\r");
        test_servo_task();
        my_printf("Servo motor test end.\n\r");
        vTaskDelay(1000);
    }
    vTaskDelete(NULL);
}
