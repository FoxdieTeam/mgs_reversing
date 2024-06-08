#ifndef _MINE_H_
#define _MINE_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/control.h"

// claymore (in hands)

typedef struct MineWork
{
    GV_ACT         field_0_actor;
    CONTROL       *control;
    OBJECT        *field_24_pObj;
    OBJECT_NO_ROTS field_28_obj;
    int            field_4C_unit;
    int           *field_50_pFlags;
    int            field_54_counter;
} MineWork;

GV_ACT *mine_init_800677BC(CONTROL *a1, OBJECT *parent_object, int num_parent, int *a4);

#endif // _MINE_H
