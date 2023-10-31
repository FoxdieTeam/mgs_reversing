#ifndef _BOX_H_
#define _BOX_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct Actor_Box
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20;
    CONTROL       *field_44_pCtrl;
    OBJECT        *field_48_pParent;
    int            field_4C_bFound;
    const char   **field_50_ppName;
    int            field_54;
} Actor_Box;

int    BoxCheckMessage_8006195C(Actor_Box *pActor);
void   BoxAct_80061A14(Actor_Box *pActor);
void   BoxDie_80061B30(Actor_Box *pActor);
int    BoxGetResources_80061BA0(Actor_Box *pActor, OBJECT *pParent);

GV_ACT *NewBox_80061C7C(CONTROL *pCtrl, OBJECT *pParent, int unused);

#endif // _BOX_H_
