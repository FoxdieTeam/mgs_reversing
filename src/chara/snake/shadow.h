#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct Shadow_94
{
    // In shadow_act_helper_8005FD28 those values
    // are used as an index in pShadow->field_24_pObj->objs[0].objs[objs_offsets[i]]
    short objs_offsets[4];
} Shadow_94;

typedef struct Actor_Shadow
{
    GV_ACT         field_0_actor;
    CONTROL       *field_20_ctrl;
    OBJECT        *field_24_pObj;
    OBJECT_NO_ROTS field_28_obj;
    MATRIX         field_4C_mtx[2];
    int            field_8C;
    int            field_90_bEnable;
    Shadow_94      field_94;
} Actor_Shadow;

void shadow_act_helper_8005FD28(Actor_Shadow *pShadow); // dummy signature
Actor_Shadow * shadow_init2_80060384(CONTROL *pCtrl, OBJECT *pObj, Shadow_94 field_94, int **field_90_bEnable);

#endif // _SHADOW_H_
