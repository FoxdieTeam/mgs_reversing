#ifndef _TABAKO_H_
#define _TABAKO_H_

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/control.h"
#include "Game/game.h"

// cigarettes

typedef struct _TabakoWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20_obj;
    CONTROL       *control;
    OBJECT        *field_48_pParent;
    int            field_4C_numParent;
    DG_PRIM       *field_50_pPrims;
    SVECTOR        field_54_vec;
    RECT           field_5C_rect;
} TabakoWork;

void tabako_act_80061EAC(TabakoWork *work);
void tabako_kill_8006206C(TabakoWork *work);
int  tabako_loader_800620B4(TabakoWork *work, OBJECT *pParent, int numParent);

GV_ACT * NewTabako_80062274(CONTROL *pCtrl, OBJECT *pParent, int numParent);

#endif // _TABAKO_H_
