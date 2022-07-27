#include "jirai.h"
#include "gcl.h"

extern const char   aJiraiC[];

extern int          jirai_act_8006AB5C(Actor_Jirai *pActor);
extern int          jirai_loader_8006B564(Actor_Jirai *pActor, int a2, int a3);

void sub_8007913C();
void GM_ClearBulName_8004FBE4(int idx);

extern int counter_8009F448;
extern int dword_8009F444;
extern int dword_8009F440;

#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006A798.s")
#pragma INCLUDE_ASM("asm/jirai_act_helper_8006A8F4.s")
#pragma INCLUDE_ASM("asm/jirai_act_helper_8006A950.s")
#pragma INCLUDE_ASM("asm/jirai_act_8006AB5C.s")

void jirai_kill_8006B05C(Actor_Jirai *pActor);

Jirai_unknown SECTION(".stru_800BDE78") stru_800BDE78[8];

#pragma INCLUDE_ASM("asm/jirai_kill_8006B05C.s")
/*
void jirai_kill_8006B05C(Actor_Jirai *pActor)
{
    int new_count; // $v1
    GCL_ARGS v3; // [sp+10h] [-10h] BYREF
    long* args[1]; // [sp+18h] [-8h] BYREF


    sub_8007913C();
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    GM_FreeTarget_8002D4B0(pActor->field_100_pTarget);


    if ( pActor->field_13C_idx >= 0 )
    {
        GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
        new_count = counter_8009F448 - 1;
        stru_800BDE78[pActor->field_13C_idx].field_4_pActor = 0;
        counter_8009F448 = new_count;
    }
    
    if ( pActor->field_138_gcl >= 0 )
    {
        v3.argc = 1;
        //v3.argv = &field_134_gcl_arg;
        args[0] = &pActor->field_134_gcl_arg;
        v3.argv = &args[0];
        GCL_ExecProc_8001FF2C(pActor->field_138_gcl, &v3);
    }

    dword_8009F444 = 0;
    dword_8009F440 = 0;
}
*/

#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006B124.s")

int jirai_get_free_item_8006B268()
{
    int i; // $v1
    for (i=0; i<8; i++)
    {
        if (!stru_800BDE78[i].field_4_pActor)
        {
            return i;
        }
    }
    return -1;
}

#pragma INCLUDE_ASM("asm/jirai_loader_8006B2A4.s")
#pragma INCLUDE_ASM("asm/NewJirai_8006B48C.s")
#pragma INCLUDE_ASM("asm/jirai_loader_8006B564.s")

Actor* NewScenarioJirai_8006B76C(int a1, int where)
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