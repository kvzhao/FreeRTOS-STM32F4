#include "unit_test.h"
#include "serial_io.h"
#include "sys_manager.h"

#include "arm.h"
#include "usart_com.h"
#include "servo.h"
#include "obj_classification.h"

#include "FreeRTOS.h"
#include "task.h"

void servo_swing(int ch)
{
    int angle;
    for (angle=0; angle < 180; angle+=2) {
        servo_set_pos(ch,angle);
        my_printf("Deg:%u\r\n",angle);
        //my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(10);
    }
    for (; angle >0 ; angle-=2) {
        servo_set_pos(ch,angle);
        my_printf("Deg:%u\r\n",angle);
        //my_printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(10);
    }
}
void test_servo_turn(int ch)
{
    my_printf("Initial Position\r\n");
    servo_set_pos(ch,0);
    vTaskDelay(1500);

    my_printf("Extreme Position\r\n");
    servo_set_pos(ch,180);
    vTaskDelay(1500);

    servo_set_pos(ch,0);
    vTaskDelay(1000);

    my_printf("Swing Test\r\n");
    servo_swing(ch);
    vTaskDelay(500);
    my_printf("Position Test : 30 deg\r\n");
    servo_set_pos(ch,30);
    vTaskDelay(1000);

    my_printf("Position Test : 60 deg\r\n");
    servo_set_pos(ch,60);
    vTaskDelay(1000);

    my_printf("Position Test : 90 deg\r\n");
    servo_set_pos(ch,90);
    vTaskDelay(1000);

    my_printf("Position Test : 120 deg\r\n");
    servo_set_pos(ch,120);
    vTaskDelay(1000);

    my_printf("Position Test : 180 deg\r\n");
    servo_set_pos(ch,180);
    vTaskDelay(1000);

    my_printf("Moving Test\r\n");
    move (WAVER, 120);
    vTaskDelay(1000);
    my_printf("Moving Test\r\n");
    move (WAVER, 90);
    vTaskDelay(1000);
    my_printf("Moving Test\r\n");
    move (WAVER, 60);
    vTaskDelay(1000);
    my_printf("Moving Test\r\n");
    move (WAVER, 30);
    vTaskDelay(1000);
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

void task_com_test() {
    op_flag = TRUE;
    while(!xQueueSend(arm_op_queue, &op_flag, (portTickType)10));
}

void Elbow_test()
{
   int i;
   for (i=0; i <= 180; i +=20)
   {
       move (ELBOW, i);
       my_printf("%d\r\n",i);
       vTaskDelay(500);
   }
   vTaskDelay(200);
}

void test_task(void *pvParameters)
{
    while (1) {
    //    Elbow_test();

        classifier(OBJ_A);
        my_printf("Approaching\r\n");
        approach();
        my_printf("Withdrawing\r\n");
        withdraw();
        vTaskDelay(1000);

        classifier(OBJ_B);
        my_printf("Approaching\r\n");
        approach();
        my_printf("Withdrawing\r\n");
        withdraw();
        vTaskDelay(1000);
/*
        // Test Servo motor
        my_printf("Servo motor test starts!\n\r");
        test_servo_turn(3);
        my_printf("Servo motor test end.\n\r");
        vTaskDelay(1000);

        my_printf("Swing test Wrist\r\n");
        servo_swing(3);
        my_printf("Swing test end\r\n");
        vTaskDelay(1000);
*/
        /*
        my_printf("Classify test : A\r\n");
        classifier(OBJ_A);
        vTaskDelay(1000);
        my_printf("Classify test : B\r\n");
        classifier(OBJ_B);
        vTaskDelay(1000);

        task_com_test();
        vTaskDelay(1000);

        task_com_test();
        vTaskDelay(1000);
*/
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
