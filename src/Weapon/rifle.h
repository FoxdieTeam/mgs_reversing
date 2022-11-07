#ifndef _RIFLE_H_
#define _RIFLE_H_

#include "Game/game.h"
#include "libgv/libgv.h"

// PSG1

typedef struct _Actor_Rifle
{
    Actor       field_0_actor;
    OBJECT      field_20_obj;
    GM_Control *field_44_pCtrl;
    OBJECT     *field_48_pParentObj;
    int         field_4c_numParent;
    int         field_50;
    int         field_54;
    int         field_58;
    int         field_5c;
} Actor_Rifle;

STATIC_ASSERT_SIZE(Actor_Rifle, 0x60);

void rifle_act_80067D60(Actor_Rifle *pActor);
void rifle_kill_80068118(Actor_Rifle *pActor);

int rifle_loader_80068184(Actor_Rifle *pActor, OBJECT *pParentObj, int numParent);

Actor_Rifle * NewRifle_80068214(GM_Control *pCtrl, OBJECT *pParentObj, int numParent, int a4, int a5);

#endif // _RIFLE_H_
