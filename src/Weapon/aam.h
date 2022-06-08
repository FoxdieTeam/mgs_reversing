#ifndef _AAM_H_
#define _AAM_H_

#include "game.h"
#include "actor.h"

typedef struct _Actor_Aam
{
    Actor field_0_actor;
    OBJECT f20_obj;
    int f44;
    OBJECT *parent_object;
    int num_parent;
    int f50;
    int f54;
    int f58;
    Actor* f5c;
} Actor_Aam;

STATIC_ASSERT_SIZE(Actor_Aam, 0x60);

#endif // _AAM