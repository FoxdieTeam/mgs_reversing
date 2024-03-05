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
    CONTROL        field_20_ctrl;
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

typedef struct Jirai_unknown
{
    int         field_0_ypos; // might be a short
    GV_ACT      *field_4_pActor; // sometimes it stores JiraiWork*, sometimes BakudanWork*, but based on several matches there was only one Jirai_unknown type (no Bakudan_unknown type) and they must have casted the types
    CONTROL *field_8_pCtrl;
    TARGET *field_C_pTarget;
} Jirai_unknown;

GV_ACT *NewJirai_8006B48C(DG_OBJ *pObj, TARGET *pTarget);

#endif // _JIRAI_H_
