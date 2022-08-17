#include "tenage.h"
#include "chara/snake/sna_init.h"

extern char aTenageC[]; // = "tenage.c"

// the projectile for all types of grenades

#pragma INCLUDE_ASM("asm/tenage_act_800699A4.s") // 1048 bytes

extern GM_Control *tenage_ctrls_800BDD30[16];
extern int         tenage_ctrls_count_800BDD70;

void tenage_kill_80069DBC(Actor_tenage *pActor)
{
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);

    if (pActor->field_120_ctrl_idx >= 0)
    {
        tenage_ctrls_800BDD30[pActor->field_120_ctrl_idx] = 0;
        tenage_ctrls_count_800BDD70--;
    }
}

int tenage_get_free_ctrl_80069E28(void)
{
    int i;

    for (i = 0; i < (int)(sizeof(tenage_ctrls_800BDD30) / sizeof(GM_Control *)); i++)
    {
        if (tenage_ctrls_800BDD30[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

#pragma INCLUDE_ASM("asm/tenage_loader_80069E64.s")      // 428 bytes

Actor_tenage *NewTenage_8006A010(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5)
{
    Actor_tenage *pActor;

    if (tenage_ctrls_count_800BDD70 == 16)
    {
        return NULL;
    }

    pActor = (Actor_tenage *)GV_NewActor_800150E4(5, sizeof(Actor_tenage));

    if (pActor)
    {
        GV_SetNamedActor_8001514C((Actor *)pActor, (TActorFunction)tenage_act_800699A4,
                                  (TActorFunction)tenage_kill_80069DBC, aTenageC);

        if (tenage_loader_80069E64(pActor, vec, vec2, param_4, param_5, 1, 1) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)pActor);
            return NULL;
        }

        pActor->field_100_homing_arg2 = param_3;
        pActor->field_104_count = 0;
        pActor->field_110 = param_4;
        pActor->field_118_do_sound = 1;
        pActor->field_11C = 1;
    }

    return pActor;
}

void sub_8006A100(SVECTOR *vec, SVECTOR *vec2, int param_3)
{
    NewTenage_8006A010(vec, vec2, param_3, 0, 0x3b88);
}

// enemy's grenades, probably
Actor_tenage *NewTenage3_8006A128(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5, int param_6,
                                  int param_7)
{
    Actor_tenage *pActor;

    pActor = (Actor_tenage *)GV_NewActor_800150E4(6, sizeof(Actor_tenage));
    if (pActor)
    {
        GV_SetNamedActor_8001514C((Actor *)pActor, (TActorFunction)tenage_act_800699A4,
                                  (TActorFunction)tenage_kill_80069DBC, aTenageC);

        if (tenage_loader_80069E64(pActor, vec, vec2, param_4, param_5, 0, 2) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)pActor);
            return NULL;
        }

        pActor->field_100_homing_arg2 = param_3;
        pActor->field_104_count = 0;
        pActor->field_110 = param_4;
        pActor->field_118_do_sound = param_6 & 1;
        pActor->field_11C = param_7 & 1;
    }

    return pActor;
}
