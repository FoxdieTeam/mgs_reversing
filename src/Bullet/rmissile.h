#ifndef _RMISSILE_H_
#define _RMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "Game/camera.h"
#include "Game/game.h"
#include "Game/target.h"
#include "libdg/libdg.h"
#include "libgcl/gcl.h"
#include "libgv/libgv.h"

// nikita missile

typedef struct Actor_rmissile
{
    Actor           field_0_actor;
    GM_Control      field_20_ctrl;
    OBJECT          field_9C_kmd;
    MATRIX          field_C0_matrix;
    char            field_E0[32];
    SVECTOR         field_100_svector;
    SVECTOR         field_108_svector;
    char            field_110;
    char            field_111;
    char            field_112;
    char            field_113;
    char            field_114;
    char            field_115;
    char            field_116;
    char            field_117;
    short           field_118;
    short           field_11A;
    int             field_11C;
    GM_Target       field_120_target;
    short           field_168;
    char            field_16A[10];
    POLY_F4        *field_174_polys_2Array[2];
    GM_Camera       field_17C_camera;
    UnkCameraStruct field_1F8;
    CAMERA          field_228_camera[8];
    int             field_2C8;
    SVECTOR         field_2CC_svector;
    int             field_2D4;
    DG_PRIM        *field_2D8_prim;
    DG_TEX         *field_2DC_tex;
    char            field_2E0[4];
    SVECTOR         field_2E4_svector;
    char            field_2EC[54];
    int             field_324;
} Actor_rmissile;

STATIC_ASSERT_SIZE(Actor_rmissile, 0x328);

void rmissile_8006B924(Actor_rmissile *pActor);
void rmissile_act_8006C5C4(Actor_rmissile *pActor);
void rmissile_kill_8006CB40(Actor_rmissile *pActor);

int  rmissile_loader_helper2_8006CC50(Actor_rmissile *pActor);
int  rmissile_loader_helper3_8006CBD8(Actor_rmissile *pActor, int whichSide);
void rmissile_loader_helper4_8006B800(Actor_rmissile *pActor);
void rmissile_loader_helper_8006CE54(Actor_rmissile *pActor);
int  rmissile_loader_8006CF44(Actor_rmissile *pActor, MATRIX *pMtx, int whichSide);
void rmissile_loader_helper_helper_8006CD1C(POLY_FT4 *pPoly, DG_TEX *pTex, int primCount);
void rmissile_act_helper_helper_8006BB10(Actor_rmissile *pActor);

Actor_rmissile *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

#endif // _RMISSILE_H_
