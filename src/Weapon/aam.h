#ifndef _AAM_H_
#define _AAM_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "stnsight.h"

// stinger

typedef struct _Actor_Aam
{
    GV_ACT           field_0_actor;
    OBJECT          field_20_obj;
    GM_Control     *field_44_ctrl;
    OBJECT         *field_48_parent_obj;
    int             field_4C_num_parent;
    int            *field_50;
    int             field_54;
    int             field_58;
    Actor_Stnsight *field_5C_stnsight;
} Actor_Aam;

STATIC_ASSERT_SIZE(Actor_Aam, 0x60);

void aam_act_800670CC(Actor_Aam *actor);

Actor_Aam * NewAAM_80067480(GM_Control *ctrl, OBJECT *parentObj, int unit, void *a4, int a5);

#endif // _AAM
