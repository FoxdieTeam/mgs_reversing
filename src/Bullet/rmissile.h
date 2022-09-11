#ifndef _RMISSILE_H_
#define _RMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "libgv/libgv.h"

// nikita missile

typedef struct Actor_rmissile
{
    Actor field_0_actor;
    char  field_4[241];
    char  field_111;
    char  field_112;
    char  field_113;
    char  field_114;
    char  field_115;
    char  field_116;
    char  field_117;
    short field_118;
    short field_11A;
    int   field_11C;
    char  field_11E[72];
    short field_168;
    char  field_16A[444];
} Actor_rmissile;

STATIC_ASSERT_SIZE(Actor_rmissile, 0x328);

void rmissile_act_8006C5C4(Actor_rmissile *pActor);
void rmissile_kill_8006CB40(Actor_rmissile *pActor);
int  rmissile_loader_8006CF44(Actor_rmissile *pActor, MATRIX *pMtx, int whichSide);

Actor_rmissile *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

#endif // _RMISSILE_H_
