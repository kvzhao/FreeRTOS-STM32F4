#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

#include "usart_com.h"
#include "serial_io.h"
#include "sys_manager.h"
#include "servo.h"
#include "arm.h"

extern volatile char received_cmd[]; // this will hold the recieved string

int angle, ret;
int base_cur_angle;

uint8_t base_init = 90;
uint8_t wrist_init = 90;
uint8_t waver_init = 90;

char op_flag = FALSE;

// goal : move (node, dir, deg)
int move (arm_node_t node, uint8_t angle)
{
    /* Chose the node*/
    switch (node)
    {
    case BASE:
            servo_set_pos(node, angle);
    break;
   case ELBOW:
            servo_set_pos(node, angle);
    break;
    case WRIST:
            servo_set_pos(node, angle);
    break;
    case WAVER:
            servo_set_pos(node, angle);
    break;
    default :
        return -1;
    } // End of switch
    return 1;
}

void execute_command(char cmd[CMD_LEN+1])
{
    // Check the command format
    if (cmd[0] == '#' && cmd[2] == 'D') {
        arm_node_t node_num = atoi(&cmd[1]);
        angle = atoi(cmd+3);

        ret = move (node_num, angle);

        if (ret) {
            com_echo("moving\r\n");
        } else {
            com_echo("bad command\r\n");
        }

        /* for debug, show the received cmd */
        my_printf("[arm_task] Move node %d, to angle %d.\r\n", node_num, angle);

    } // End of format check

}

void arm_task(void *pvParameters)
{
    // Command counter
    uint8_t cnt = 0;
    char t;

    arm_op_queue = xQueueCreate(1, sizeof(op_flag));

    while (1) {
        if ( cnt < CMD_LEN ) {
            t = com.getch();
            if ( t >= 0x21 && t <= 0x7E )
                received_cmd[cnt++]= t;
        } else {
            cnt = 0;
            execute_command(received_cmd);
        }

        xQueueSend(arm_op_queue, &op_flag, (portTickType)10);
    }
}

void robot_arm_initialization()
{
  Servo_Configuration();
  USART1_COM_Configuration(57600);
}


