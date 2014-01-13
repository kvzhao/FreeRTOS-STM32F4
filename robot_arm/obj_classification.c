#include "arm.h"
#include "obj_classification.h"
#include "sys_manager.h"

uint8_t obj_container_A = 10;
uint8_t obj_container_B = 170;


void classifier (obj_t type)
{
    switch (type)
    {
        case OBJ_A:
            move (WAVER, obj_container_A) ;
            break;
        case OBJ_B:
            move (WAVER, obj_container_B);
            break;
    }
}

void grab_obj (obj_t type)
{
    vTaskDelay(1000);
    switch (type)
    {
        case OBJ_A:
            my_printf("Grab A\r\n");
            move (BASE, obj_container_A) ;
            break;
        case OBJ_B:
            my_printf("Grab B\r\n");
            move (BASE, obj_container_B) ;
            break;
    }
    my_printf("Arm moves forward\r\n");
    approach();
    vTaskDelay(1000);
    my_printf("Arm moves backward\r\n");
    withdraw();
    vTaskDelay(1000);
}

void arm_operate_task(void *pv)
{
    while(1)
   {
            while(!xQueueReceive(arm_op_queue, &op_flag, (portTickType)(10)));
        if(FALSE)
        {
            vTaskDelay(10000);
            my_printf("operation enabled\r\n");
            grab_obj(op_flag);
//            op_flag = FALSE;
            my_printf("operation complete\r\n");
        }
    }
}
