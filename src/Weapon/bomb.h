#ifndef _BOMB_H_
#define _BOMB_H_

#include "game.h"
#include "actor.h"

typedef struct _Actor_Bomb
{
    Actor field_0_actor;
    int f20;
    OBJECT *parent_obj;
    OBJECT f28_obj;
    int num_parent;
    int f50;
    int f54;
    int f58;
} Actor_Bomb;

STATIC_ASSERT_SIZE(Actor_Bomb, 0x5c);

#endif // _BOMB_H_