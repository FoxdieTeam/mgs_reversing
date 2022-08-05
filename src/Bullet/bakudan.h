#ifndef _BAKUDAN_H_
#define _BAKUDAN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/game.h"
#include "libgv/actor.h"
#include "target.h"
#include "Game/GM_Control.h"

typedef struct Actor_bakudan
{
    Actor           field_0;
    GM_Control      field_20_ctrl;
    OBJECT          field_9C_kmd;
    MATRIX          field_C0_light_mtx;
    int             field_E0;
    int             field_E4;
    int             field_E8;
    int             field_EC;
    int             field_F0;
    int             field_F4;
    int             field_F8;
    int             field_FC;
    MATRIX         *field_100_pMtx;
    SVECTOR        *field_104;
    int             field_108;
    int             field_10C;
    unsigned short *field_110_padObj;
    int             field_114;
    int             field_118;
} Actor_bakudan;

Actor *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, GM_Target *pTarget);

#endif // _BAKUDAN_H_
