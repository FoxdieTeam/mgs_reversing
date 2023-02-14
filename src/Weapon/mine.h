#ifndef _MINE_H_
#define _MINE_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/GM_Control.h"

// claymore (in hands)

typedef struct Actor_Mine
{
    GV_ACT       field_0_actor;
    GM_Control *field_20_pCtrl;
    OBJECT     *field_24_pObj;
    OBJECT      field_28_obj;
    int         field_4C_unit;
    int        *field_50_pFlags;
    int         field_54_counter;
} Actor_Mine;

STATIC_ASSERT_SIZE(Actor_Mine, 0x58);

void mine_act_80067558(Actor_Mine *pActor);

#endif // _MINE_H
