#include "arm.h"
#include "obj_classification.h"

uint8_t obj_container_A = 60;
uint8_t obj_container_B = 120;

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

void withdraw()
{
    move (WAVER, WAVER_INIT);
}

