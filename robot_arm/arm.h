#ifndef __ARM_H__
#define __ARM_H__

// Angle Constraints and Initial Value
#define BASE_MIN 0
#define BASE_MAX 180
#define BASE_INIT 90
#define WAVER_MIN 0
#define WAVER_MAX 180
#define WAVER_INIT 90

typedef enum {
    BASE = 0,
    ELBOW,
    WRIST,
    //GRIPPER
    WAVER
} arm_node_t;

// A flag indicate receiving move arm request
void execute_command(char cmd[]);
int move (arm_node_t node, int8_t angle);
void arm_task(void *pv);

void robot_arm_initialization();
#endif
