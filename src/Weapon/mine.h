#ifndef _MINE_H_
#define _MINE_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/control.h"

// claymore (in hands)

typedef struct MineWork
{
    GV_ACT         field_0_actor;
    CONTROL       *field_20_pCtrl;
    OBJECT        *field_24_pObj;
    OBJECT_NO_ROTS field_28_obj;
    int            field_4C_unit;
    int           *field_50_pFlags;
    int            field_54_counter;
} MineWork;

STATIC_ASSERT_SIZE(MineWork, 0x58);

void mine_act_80067558(MineWork *work);

#endif // _MINE_H
