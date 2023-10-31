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

typedef struct Actor_bakudan
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
} Actor_bakudan;

GV_ACT *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, TARGET *pTarget);
void   bakudan_act_8006A218(Actor_bakudan *pActor);
void   bakudan_kill_8006A4A4(Actor_bakudan *pActor);
int    bakudan_8006A54C(Actor_bakudan *pActor, MATRIX *pMtx, SVECTOR *pVec, int a4, TARGET *pTarget);
int    bakudan_next_free_item_8006A510(void);

#endif // _BAKUDAN_H_
