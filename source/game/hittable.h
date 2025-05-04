#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "libgv/libgv.h"
#include "game/control.h"

typedef struct HITTABLE
{
    int      type;    // Not read from, set as either WP_Claymore or WP_C4
    GV_ACT  *actor;
    CONTROL *control;
    void    *data;    // The thing being collided with, can be walls, floors, targets
} HITTABLE;

#endif // _HITTABLE_H_
