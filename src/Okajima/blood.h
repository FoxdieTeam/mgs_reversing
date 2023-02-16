#ifndef _BLOOD_H
#define _BLOOD_H

#include "Game/game.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Actor_Blood
{
    GV_ACT   field_0_actor;
    int      f20;
    DG_OBJS *f24_prim;
    int      f28_unk;
    char     f2c_placeholder[12];
    int      current_map;
} Actor_Blood;
STATIC_ASSERT_SIZE(Actor_Blood, 0x3c);

void             NewBlood_80072728(MATRIX *, int); // dummy signature
Actor_Blood      *NewKetchap_80072B60(void);

#endif // _BLOOD_H
