#ifndef _BAKUDAN_H_
#define _BAKUDAN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/target.h"
#include "Game/control.h"

// c4 (armed)

typedef struct BakudanWork
{
    GV_ACT         field_0_actor;
    CONTROL        field_20_ctrl;
    OBJECT_NO_ROTS field_9C_kmd;
    MATRIX         field_C0_light_mtx[2];
    MATRIX        *field_100_pMtx;
    SVECTOR       *field_104;
    int            field_108;
    int            field_10C;
    GV_PAD        *field_110_pPad;
    int            field_114;
    int            field_118;
} BakudanWork;

GV_ACT *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, void *data);

#endif // _BAKUDAN_H_
