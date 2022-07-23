#include "bandana.h"

extern const char aBandanaC[];

extern void bandana_80061D14(OBJECT *param_1);
#pragma INCLUDE_ASM("asm/Equip/bandana_80061D14.s")

void bandana_act_80061DA0(Actor_bandana *pActor);
#pragma INCLUDE_ASM("asm/Equip/bandana_act_80061DA0.s")

void bandana_kill_80061E1C(Actor_bandana *pActor)
{
    bandana_80061D14(pActor->field_20_pParent);
}

Actor* NewBandana_80061E40(GM_Control* pCtrl, OBJECT *pParent)
{
    Actor_bandana *pActor = (Actor_bandana *)GV_NewActor_800150E4(7, sizeof(Actor_bandana));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(
            &pActor->field_0_actor,
            (TActorFunction)bandana_act_80061DA0,
            (TActorFunction)bandana_kill_80061E1C,
            aBandanaC);
        pActor->field_20_pParent = pParent;
        bandana_80061D14(pParent);
    }
    return &pActor->field_0_actor;
}
