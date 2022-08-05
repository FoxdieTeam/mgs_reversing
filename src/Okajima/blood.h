#ifndef _BLOOD_H
#define _BLOOD_H

#include "Game/game.h"
#include "libgv/actor.h"
#include "libdg/libdg.h"

typedef struct _Actor_Blood
{
    Actor    field_0_actor;
    int      f20;
    DG_OBJS *f24_prim;
    char     f28_placeholder[16];
    int      current_map;
} Actor_Blood;
STATIC_ASSERT_SIZE(Actor_Blood, 0x3c);

void NewBlood_80072728(MATRIX *, int); // dummy signature

#endif // _BLOOD_H
