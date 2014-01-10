#include "arm.h"
#include "obj_classification.h"

void classifier (obj_t type)
{
    switch (type)
    {
        case OBJ_A:
            move (WAVER, OBJ_A_CONTAINER);
            break;
        case OBJ_B:
            move (WAVER, OBJ_B_CONTAINER);
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

