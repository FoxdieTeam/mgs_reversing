#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct ShadowWork
{
    GV_ACT         field_0_actor;
    CONTROL       *control;
    OBJECT        *field_24_pObj;
    OBJECT_NO_ROTS field_28_obj;
    MATRIX         field_4C_mtx[2];
    int            field_8C;
    int            field_90_bEnable;
    SVECTOR        indices;
} ShadowWork;

void shadow_act_helper_8005FD28(ShadowWork *pShadow); // dummy signature

ShadowWork * shadow_init_800602CC(CONTROL *pCtrl, OBJECT *pObj, SVECTOR indices);
ShadowWork * shadow_init2_80060384(CONTROL *pCtrl, OBJECT *pObj, SVECTOR indices, int **field_90_bEnable);

#endif // _SHADOW_H_
