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
    int i;
    uint8_t elbow_curr = 170;
    uint8_t wrist_curr = 120;
    for (i=0; i < 42; i++)
    {
        elbow_curr-=2;
        wrist_curr-=1;
        move (ELBOW, elbow_curr);
        move (WRIST, wrist_curr);
    }
}
void withdraw()
{
    int i;
    uint8_t elbow_curr = 86;
    uint8_t wrist_curr = 78;
    for (i=0; i < 42; i++)
    {
        elbow_curr+=2;
        wrist_curr+=1;
        move (ELBOW, elbow_curr);
        move (WRIST, wrist_curr);
    }
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
