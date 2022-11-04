#ifndef _AAM_H_
#define _AAM_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "stnsight.h"

// stinger

typedef struct _Actor_Aam
{
    Actor               field_0_actor;
    OBJECT              field_20_obj;
    Actor_stnsight_unk *field_44_unk;
    OBJECT             *field_48_parent_obj;
    int                 field_4C_num_parent;
    int                *field_50;
    int                 field_54;
    int                 field_58;
    Actor_stnsight     *field_5C_stnsight;
} Actor_Aam;

STATIC_ASSERT_SIZE(Actor_Aam, 0x60);

void aam_act_800670CC(Actor_Aam *actor);

#endif // _AAM
