#ifndef _CHAFGRND_H_
#define _CHAFGRND_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Actor_Chafgrnd
{
    GV_ACT    field_0_actor;
    int      field_20_map;
    int      field_24;
    int      field_28;
    SVECTOR  field_2c;
    SVECTOR  field_34[2][64];
    SVECTOR  field_434[2][64];
    SVECTOR  field_834[64];
    DG_PRIM *field_a34;
    int      field_a38;
    int      field_a3c;
    char     field_a40[64];
    MATRIX   field_a80;
} Actor_Chafgrnd;

STATIC_ASSERT_SIZE(Actor_Chafgrnd, 0xaa0);

void chafgrnd_act_80076B28(Actor_Chafgrnd *pActor);
void chafgrnd_kill_8007721C(Actor_Chafgrnd *pActor);

int chafgrnd_loader_80077014(Actor_Chafgrnd *pActor, MATRIX *pWorld);

Actor_Chafgrnd * NewChafgrnd_80077264(MATRIX *pWorld);

#endif // _CHAFGRND_H_
