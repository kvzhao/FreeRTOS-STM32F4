#include "unit_test.h"
#include "serial_io.h"

#include "arm.h"
#include "usart_com.h"
#include "servo.h"

#include "FreeRTOS.h"
#include "task.h"

void test_servo_turn()
{
    int angle;
    for (angle=0; angle < 180; angle++) {
        servo_set_pos(0,angle);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(10);
    }
    for (; angle >0 ; angle--) {
        servo_set_pos(0,angle);
        my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(10);
    }
}

void test_arm_receive_cmd()
{
    execute_command("#0D120");
    vTaskDelay(50);

    execute_command("#0D090");
    vTaskDelay(50);

    execute_command("#0D000");
    vTaskDelay(50);

}

void test_task(void *pvParameters)
{
    while (1) {
        /* Test Servo motor */
        my_printf("Servo motor test starts!\n\r");
        test_servo_turn();
        my_printf("Servo motor test end.\n\r");
        vTaskDelay(1000);

        /* Test robot command parser */
        /*
        my_printf("Robot Arm command test starts!\n\r");
        test_arm_receive_cmd();
        my_printf("Robot Arm command test end!\n\r");
        vTaskDelay(1000);
        */
    }
    vTaskDelete(NULL);
}
