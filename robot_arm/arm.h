#ifndef __ARM_H__
#define __ARM_H__

// Angle Constraints
#define BASE_MIN 0
#define BASE_MAX 180

typedef enum {
    BASE = 0,
    ELBOW,
    WRIST,
    GRIPPER
} arm_node_t;

// A flag indicate receiving move arm request
extern char isReceive_move_req;
void execute_command(char cmd[]);
int move (arm_node_t node, int8_t angle);
void arm_task(void *pv);

void robot_arm_initialization();
#endif
