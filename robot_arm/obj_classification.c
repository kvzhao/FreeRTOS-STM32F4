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
}
void approach()
{
}
void withdraw()
{
}

void arm_operate_task(void *pv)
{
    my_printf("Enter operation function\r\n");
    while(1)
   {
        xQueueReceive(arm_op_queue, &op_flag, (portTickType)(1));

        if(op_flag == TRUE)
        {
            my_printf("operation enabled\r\n");
            op_flag = FALSE;
        }
    }
}
