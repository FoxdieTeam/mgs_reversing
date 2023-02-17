#ifndef _BLOOD_H
#define _BLOOD_H

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _Actor_Blood
{
    GV_ACT   field_0_actor;
    int      field_20_map;
    DG_PRIM *field_24_prims;
    SVECTOR  field_28[16];
    SVECTOR  field_A8[64];
    int      field_2A8;
    int      field_2AC_prim_count;
} Actor_Blood;

STATIC_ASSERT_SIZE(Actor_Blood, 0x2B0);

void blood_act_80072538(Actor_Blood *pActor);
void blood_kill_800725CC(Actor_Blood *pActor);

int blood_loader2_80072608(Actor_Blood *pActor, MATRIX *, int index);

Actor_Blood * NewBlood_80072728(MATRIX *, int count);

void AN_Blood_Mist_80072934(SVECTOR *pos, SVECTOR *speed);

#endif // _BLOOD_H
