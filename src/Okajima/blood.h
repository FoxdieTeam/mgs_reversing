#ifndef _BLOOD_H
#define _BLOOD_H

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _Actor_Blood
{
    GV_ACT   field_0_actor;
    char     field_20_pad[0x4];
    DG_OBJS *field_24_prim;
    char     field_28_pad[0x288];
} Actor_Blood;

STATIC_ASSERT_SIZE(Actor_Blood, 0x2B0);

void blood_act_80072538(Actor_Blood *pActor);
void blood_kill_800725CC(Actor_Blood *pActor);

int blood_loader2_80072608(Actor_Blood *pActor, MATRIX *, int index);

Actor_Blood * NewBlood_80072728(MATRIX *, int count);

void AN_Blood_Mist_80072934(SVECTOR *pos, SVECTOR *speed);

#endif // _BLOOD_H
