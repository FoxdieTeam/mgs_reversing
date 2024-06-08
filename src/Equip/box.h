#ifndef _BOX_H_
#define _BOX_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct BoxWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20;
    CONTROL       *control;
    OBJECT        *field_48_pParent;
    int            field_4C_bFound;
    const char   **field_50_ppName;
    int            field_54;
} BoxWork;

int    BoxCheckMessage_8006195C(BoxWork *work);
void   BoxAct_80061A14(BoxWork *work);
void   BoxDie_80061B30(BoxWork *work);
int    BoxGetResources_80061BA0(BoxWork *work, OBJECT *pParent);

GV_ACT *NewBox_80061C7C(CONTROL *pCtrl, OBJECT *pParent, int unused);

#endif // _BOX_H_
