#ifndef _RIFLE_H_
#define _RIFLE_H_

#include "Game/game.h"
#include "libgv/actor.h"

// PSG1

typedef struct _Actor_Rifle
{
    Actor field_0_actor;
    OBJECT f20_obj;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
} Actor_Rifle;

STATIC_ASSERT_SIZE(Actor_Rifle, 0x60);

#endif // _RIFLE_H_
