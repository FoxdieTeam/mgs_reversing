#ifndef __KOJO_M1E1_H__
#define __KOJO_M1E1_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct M1E1Work
{
    GV_ACT  actor;
    CONTROL control;
    MATRIX  field_9C_light_matrices[2];
    OBJECT  field_DC;
    OBJECT  field_1C0[3];
    OBJECT  field_46C[3];
    TARGET *field_718_targets[10];
    int     field_740;
    char    field_744[0x61C];
    int     field_D60;
    int     field_D64;
    int     field_D68;
    int     field_D6C;
    char    field_D70[0x1C];
    int     field_D8C;
    char    field_D90[0xD0];
    int     field_E60;
    int     field_E64;
    int     field_E68;
    int     field_E6C;
    int     field_E70;
    int     field_E74;
    int     field_E78;
    int     field_E7C;
    int     field_E80;
    int     field_E84;
    int     field_E88;
    SVECTOR field_E8C;
    SVECTOR field_E94;
    char    field_E9C[0xC4];
    int     field_F60;
    int     field_F64;
    int     field_F68;
    int     field_F6C;
    int     field_F70;
    int     field_F74;
} M1E1Work;

/* m1e1catr.c */
void M1E1Caterpiller(M1E1Work *work);
void M1E1GetCaterpillerVertex(OBJECT *obj1, OBJECT *obj2, SVECTOR *pos, int a4);

#endif // __KOJO_M1E1_H__
