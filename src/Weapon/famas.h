#ifndef _FAMAS_H_
#define _FAMAS_H_

#include "Game/game.h"
#include "libgv/actor.h"

typedef struct _Actor_Famas
{
    Actor   field_0_actor;
    OBJECT  f20_obj;
    int     f44;
    OBJECT *parent_object;
    int     num_parent;
    int     f50;
    int     f54;
    int     f58;
    int     f5c;
} Actor_Famas;

STATIC_ASSERT_SIZE(Actor_Famas, 0x60);

int famas_act_80065E90(int a1);

#endif // _FAMAS_H_
