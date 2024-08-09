#ifndef _SOCOM_H
#define _SOCOM_H

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/control.h"

typedef struct _SocomWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20;
    CONTROL       *control;
    OBJECT        *field_48_parent_object;
    int            field_4C_obj_idx;
    int           *field_50_ptr;
    short          field_54_bullet_type;
    short          field_56;
    DG_PRIM       *field_58_prim;
    DG_TEX        *field_5C_pTexture;
    SVECTOR        field_60_array[20];
    int            field_100;
    int            field_104_rnd;
    int            field_108;
    DG_PRIM       *field_10C_pPrim;
    SVECTOR        field_110;
    SVECTOR        field_118;
} SocomWork;

GV_ACT *NewSOCOM_80065D74(CONTROL *a1, OBJECT *parentObj, int unit,  unsigned int *a4, int a5 );

#endif // _SOCOM_H
