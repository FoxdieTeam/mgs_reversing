#ifndef _BLOOD_H
#define _BLOOD_H

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _BloodWork
{
    GV_ACT   actor;
    int      field_20_map;
    DG_PRIM *field_24_prims;
    SVECTOR  field_28[16];
    SVECTOR  field_A8[64];
    int      field_2A8;
    int      field_2AC_prim_count;
} BloodWork;

STATIC_ASSERT(sizeof(BloodWork) == 0x2B0, "sizeof(BloodWork) is wrong!");

void blood_act_80072538(BloodWork *work);
void blood_kill_800725CC(BloodWork *work);

int blood_loader2_80072608(BloodWork *work, MATRIX *, int index);

GV_ACT *NewBlood_80072728(MATRIX *, int count);

void AN_Blood_Mist_80072934(SVECTOR *pos, SVECTOR *speed);

#endif // _BLOOD_H
