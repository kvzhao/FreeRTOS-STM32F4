#ifndef __ARM_H__
#define __ARM_H__

#include <stdint.h>

// Angle Constraints and Initial Value
#define BASE_MIN 0
#define BASE_MAX 180

#define ELBOW_MIN 90
#define ELBOW_MAX 175

#define WRIST_MIN 90
#define WRIST_MAX 175

#define WAVER_MIN 0
#define WAVER_MAX 180

#define TRUE 1
#define FALSE 0

extern char op_flag;


typedef enum {
    BASE = 0,
    ELBOW,
    WRIST,
    //GRIPPER
    WAVER
} arm_node_t;

// A flag indicate receiving move arm request
void execute_command(char cmd[]);
int move (arm_node_t node, uint8_t angle);
void arm_task(void *pv);

void robot_arm_initialization();
#endif
