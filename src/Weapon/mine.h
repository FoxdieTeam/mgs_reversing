#ifndef _MINE_H_
#define _MINE_H_

#include "game.h"
#include "actor.h"

typedef struct _Actor_Mine
{
    Actor field_0_actor;
    int f20;
    int f24;
    OBJECT f28_obj;
    int f4c;
    int f40;
    int f54;
} Actor_Mine;

STATIC_ASSERT_SIZE(Actor_Mine, 0x58);

#endif // _MINE_H