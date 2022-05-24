#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "game.h"
#include "actor.h"

typedef struct _Actor_Grenade
{
    Actor field_0_actor;
    int f20;
    int f24;
    OBJECT f28_obj;
    int f4c;
    int f40;
    int f54;
    int f58;
    int f5c;
    int f60;
    int f64;
} Actor_Grenade;

STATIC_ASSERT_SIZE(Actor_Grenade, 0x68);

#endif // _GRENADE_H_