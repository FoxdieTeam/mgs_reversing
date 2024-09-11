#ifndef _CLAYMORE_H_
#define _CLAYMORE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/target.h"

typedef struct ClaymoreWork
{
    GV_ACT     field_0;
    int       field_20_map;
    SVECTOR   field_24;
    SVECTOR   field_2C;
    SVECTOR   field_34;
    TARGET field_3C_target;
    DG_PRIM  *field_84_pPrim;
    SVECTOR   field_88;
    int       field_90;
    int       field_94;
    int       field_98;
    int       field_9C;
    int       field_A0;
    int       field_A4;
    int       field_A8;
    int       field_AC;
    int       field_B0;
    int       field_B4;
    int       field_B8;
    int       field_BC;
    int       field_C0;
    int       field_C4;
    SVECTOR   field_C8; // Maybe a SVECTOR array from here? ([8], [4][2] or [2][4])
    SVECTOR   field_D0;
    SVECTOR   field_D8;
    SVECTOR   field_E0;
    SVECTOR   field_E8;
    SVECTOR   field_F0;
    SVECTOR   field_F8;
    SVECTOR   field_100;
    int       field_108;
    int       field_10C;
    SVECTOR   field_110;
    SVECTOR   field_118;
    int       field_120;
    int       field_124; // Counter increasing from 0 to 3?
    int       field_128;
} ClaymoreWork;

GV_ACT *NewClaymore_80073B8C(SVECTOR *noise_position, SVECTOR *new_field_2C, int pCnt, int param_4);

#endif // _CLAYMORE_H_
