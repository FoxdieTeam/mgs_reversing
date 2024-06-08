#ifndef _JIRAI_H_
#define _JIRAI_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/object.h"
#include "Game/control.h"
#include "Game/target.h"

// claymore (on ground)

typedef struct JiraiWork
{
    GV_ACT         field_0_actor;
    CONTROL        control;
    OBJECT_NO_ROTS field_9C_obj;
    MATRIX         field_C0_light_matrices[2];
    TARGET        *field_100_pTarget;
    SVECTOR        field_104_vec;
    short          field_10C;
    short          field_10E;
    int            field_110;
    int            field_114;
    int            field_118;
    int            field_11C;
    int            field_120;
    int            field_124;
    int            field_128;
    int            field_12C;
    int            field_130;
    long           field_134_gcl_arg;
    int            field_138_gcl;
    int            field_13C_idx;
    int            field_140;
    SVECTOR        field_144_vec;
    int            field_14C_map;
    int            field_150;
#ifdef VR_EXE
    int            field_154;
#endif
} JiraiWork;

GV_ACT *NewJirai_8006B48C(DG_OBJ *pObj, HZD_FLR *flr);

#endif // _JIRAI_H_
