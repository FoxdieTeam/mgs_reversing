#ifndef _RCM_H_
#define _RCM_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "libdg/libdg.h"

// nikita

typedef struct RcmWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS f20_obj;
    CONTROL       *control;
    OBJECT        *field_48_pParent;
    int            field_4C_obj_idx;
    unsigned int  *field_50_pFlags;
    int            field_54_whichSide;
    int            field_58_counter;
    DG_PRIM       *field_5C_pPrim;
    int            field_60_rgb; // state of the blinking light
} RcmWork;

GV_ACT *NewRCM_80066FF0(CONTROL *pCtrl, OBJECT *parent_obj, int num_parent, unsigned int *pFlags, int whichSide);

#endif // _RCM_H_
