#ifndef _RCM_H_
#define _RCM_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/GM_Control.h"
#include "libdg/libdg.h"

// nikita

typedef struct Actor_Rcm
{
    Actor         field_0_actor;
    OBJECT        f20_obj;
    GM_Control   *field_44_pCtrl;
    OBJECT       *field_48_pParent;
    int           field_4C_obj_idx;
    unsigned int *field_50_pUnknown;
    int           field_54_whichSide;
    int           field_58_counter;
    DG_PRIM      *field_5C_pPrim;
    int           field_60_rgb;
} Actor_Rcm;

STATIC_ASSERT_SIZE(Actor_Rcm, 0x64);

#endif // _RCM_H_
