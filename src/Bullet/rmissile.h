#ifndef _RMISSILE_H_
#define _RMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "Game/camera.h"
#include "Game/game.h"
#include "Game/target.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

// nikita missile

typedef struct RMissileWork
{
    GV_ACT          field_0_actor;
    CONTROL         field_20_ctrl;
    OBJECT_NO_ROTS  field_9C_kmd;
    MATRIX          field_C0_light_matrices[2];
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
    TARGET          field_120_target;
    short           field_168;
    short           field_16A;
    SVECTOR         field_16C_svector;
    POLY_F4        *field_174_polys_2Array[2];
    GM_Camera       field_17C_camera;
    UnkCameraStruct field_1F8;
    CAMERA          field_228_camera[8];
    int             field_2C8;
    SVECTOR         field_2CC_svector;
    int             field_2D4;
    DG_PRIM        *field_2D8_prim;
    DG_TEX         *field_2DC_tex;
    char            field_2E0_pad[4];
    SVECTOR         field_2E4_svector_8Array[8];
    int             field_324;
} RMissileWork;

GV_ACT *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

#endif // _RMISSILE_H_
