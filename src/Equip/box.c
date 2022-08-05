#include "box.h"

extern const char aBoxC[];

#pragma INCLUDE_ASM("asm/Equip/BoxCheckMessage_8006195C.s") // 184 bytes
int BoxCheckMessage_8006195C(Actor_Box *pActor);

#pragma INCLUDE_ASM("asm/Equip/BoxAct_80061A14.s") // 284 bytes
void BoxAct_80061A14(Actor_Box *pActor);

#pragma INCLUDE_ASM("asm/Equip/BoxDie_80061B30.s") // 112 bytes
void BoxDie_80061B30(Actor_Box *pActor);

#pragma INCLUDE_ASM("asm/Equip/BoxGetResources_80061BA0.s") // 220 bytes
int BoxGetResources_80061BA0(Actor_Box *pActor, OBJECT *pParent);

Actor *NewBox_80061C7C(GM_Control *pCtrl, OBJECT *pObj)
{
    Actor_Box *pActor = (Actor_Box *)GV_NewActor_800150E4(6, sizeof(Actor_Box));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)BoxAct_80061A14,
                                  (TActorFunction)BoxDie_80061B30, aBoxC);
        if (BoxGetResources_80061BA0(pActor, pObj) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pParent = pObj;
    }
    return &pActor->field_0_actor;
}
