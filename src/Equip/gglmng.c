#include "gglmng.h"

extern const char aGglmngC[];

#pragma INCLUDE_ASM("asm/Equip/gglmng_act_800778B4.s") // 212 bytes
void gglmng_act_800778B4(Actor_gglmng* pActor);

void gglmng_kill_80077988(Actor_gglmng *pActor)
{
    if ( pActor->field_28_pGglsight )
    {
        GV_DestroyOtherActor_800151D8(pActor->field_28_pGglsight);
    }
}

Actor_gglmng* gglmng_init_800779B8(int type)
{
    Actor_gglmng *pActor; // $s0

    pActor = (Actor_gglmng *)GV_NewActor_800150E4(7, sizeof(Actor_gglmng));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)gglmng_act_800778B4, (TActorFunction)gglmng_kill_80077988, aGglmngC);
        pActor->field_20_type = type;
        pActor->field_24 = 0;
        pActor->field_28_pGglsight = 0;
    }
    return pActor;
}

