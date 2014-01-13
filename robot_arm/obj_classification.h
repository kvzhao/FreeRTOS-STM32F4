#ifndef __OBJ_CLASSIFICATION_H__
#define __OBJ_CLASSIFICATION_H__

typedef enum {
    OBJ_A, // Coin
    OBJ_B  // Gear
} obj_t;

extern uint8_t obj_container_A;
extern uint8_t obj_container_B;

void classifier (obj_t type);
void grab_obj (obj_t type);

void arm_operate_task(void* pv);

#endif
