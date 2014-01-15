#include <stdlib.h>
// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
//
#include "serial_io.h"
#include "sys_manager.h"
#include "servo.h"
#include "arm.h"

volatile char received_cmd[CMD_LEN]; // this will hold the recieved string

int angle, ret;
int base_cur_angle;

// goal : move (node, dir, deg)
int move (arm_node_t node, int8_t angle)
{
    servo_set_pos(node, angle);
    /* Chose the node*/
    switch (node)
    {
    case BASE:
        if ( angle <= BASE_MAX && angle >= BASE_MIN ) {
            servo_set_pos(node, angle);
        }
    break;
    case ELBOW:
    break;
    case WRIST:
    break;
    case GRIPPER:
    break;
    default :
        return -1;
    } // End of switch
    return 1;
}

// Command format : #<number of servo>D<Degree of angle>
// Example #0D120
void execute_command(char cmd[CMD_LEN+1])
{
    // Check the command format
    if (cmd[0] == '#' && cmd[2] == 'D') {
        arm_node_t node_num = atoi(&cmd[1]);
        angle = atoi(cmd+3);

        ret = move (node_num, angle);

        if (ret) {
        } else {
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

    while (1) {
        if ( cnt < CMD_LEN ) {
            //t = com.getch(); //TODO: method of receiving command
            if ( t >= 0x21 && t <= 0x7E )
                received_cmd[cnt++]= t;
        } else {
            cnt = 0;
            execute_command(received_cmd);
        }

    }
}
