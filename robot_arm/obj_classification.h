#ifndef __OBJ_CLASSIFICATION_H__
#define __OBJ_CLASSIFICATION_H__


typedef enum {
    OBJ_A, // Coin
    OBJ_B  // Gear
} obj_t;

void classifier (obj_t type);
void grab_obj (obj_t type);
void withdraw();

#endif
