#include "jirai.h"


extern const char   aJiraiC[];

extern int          jirai_act_8006AB5C(Actor_Jirai *pActor);
extern int          jirai_kill_8006B05C(Actor_Jirai *pActor);
extern int          jirai_loader_8006B564(Actor_Jirai *pActor, int a2, int a3);

#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006A798.s")
#pragma INCLUDE_ASM("asm/jirai_act_helper_8006A8F4.s")
#pragma INCLUDE_ASM("asm/jirai_act_helper_8006A950.s")
#pragma INCLUDE_ASM("asm/jirai_act_8006AB5C.s")
#pragma INCLUDE_ASM("asm/jirai_kill_8006B05C.s")
#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006B124.s")
#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006B268.s")
#pragma INCLUDE_ASM("asm/jirai_loader_8006B2A4.s")
#pragma INCLUDE_ASM("asm/NewJirai_8006B48C.s")
#pragma INCLUDE_ASM("asm/jirai_loader_8006B564.s")

Actor_Jirai* NewScenarioJirai_8006B76C(int a1, int where)
{
    Actor_Jirai *pActor = (Actor_Jirai *)GV_NewActor_800150E4(6, sizeof(Actor_Jirai));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jirai_act_8006AB5C, (TActorFunction)jirai_kill_8006B05C, aJiraiC);
        if (jirai_loader_8006B564(pActor, a1, where) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }
    return &pActor->field_0_actor;
}