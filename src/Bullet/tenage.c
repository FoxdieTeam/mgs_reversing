#include "tenage.h"
#include "chara/snake/sna_init.h"
#include "game/gm_control.h"

extern char aTenageC[]; // = "tenage.c"

// the projectile for all types of grenades

#pragma INCLUDE_ASM("asm/tenage_act_800699A4.s") // 1048 bytes

extern GM_Control  *tenage_ctrls_800BDD30[16];
extern int         tenage_ctrls_count_800BDD70;
extern SVECTOR     svector_800ABA10;
extern SVECTOR     DG_ZeroVector_800AB39C;
extern GM_Control  *tenage_ctrls_800BDD30[16];
extern int         tenage_ctrls_count_800BDD70;

//------------------------------------------------------------------------------

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

int tenage_loader_80069E64(Actor_tenage *pActor, SVECTOR *vec, SVECTOR *vec2,
                           int int_3,int int_4,int int_5, int int_6)
{
    GM_Control *pControl;
    int        tmp;
    
    pControl = &pActor->field_20_ctrl;
    tmp = Res_Control_init_loader_8002599C(pControl, GM_Next_BulName_8004FBA0(), 0);
    if (tmp >= 0)
    {
        if (int_5 != 0)
        {
            GM_ConfigControlHazard_8002622C(pControl, 100, 50, 50);
        }
        else
        {
            GM_ConfigControlHazard_8002622C(pControl, 100, -1, -1);
        }
        pControl->field_59 = '\x04';
        if (int_6 == 1)
        {
            pControl->field_0_position = svector_800ABA10;
            GM_ConfigControlTrapCheck_80026308(pControl);
            GM_ActControl_80025A7C(pControl);
        }
        GM_ConfigControlVector_800260FC(pControl, vec, (SVECTOR *)&DG_ZeroVector_800AB39C);
        pActor->field_108 = *vec2;
        GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)&pActor->field_9C_obj, int_4, WEAPON_FLAG, 0);
        if ((pActor->field_9C_obj).objs != NULL)
        {
            DG_SetPos2_8001BC8C(&pControl->field_0_position, &pControl->field_8_rotator);
            DG_PutObjs_8001BDB8((pActor->field_9C_obj).objs);
            GM_ConfigObjectLight_80034C44(&pActor->field_9C_obj, &pActor->field_C0_mtx);
            tmp = tenage_get_free_ctrl_80069E28();
            pActor->field_120_ctrl_idx = tmp;
            if (tmp >= 0)
            {
                tenage_ctrls_800BDD30[tmp] = pControl;
                pControl->field_0_position.pad = 0;
                tenage_ctrls_count_800BDD70 = tenage_ctrls_count_800BDD70 + 1;
                return 0;
            }
        }
    }
    return -1;
}

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
        GV_SetNamedActor_8001514C((GV_ACT *)pActor, (TActorFunction)tenage_act_800699A4,
                                  (TActorFunction)tenage_kill_80069DBC, aTenageC);

        if (tenage_loader_80069E64(pActor, vec, vec2, param_4, param_5, 1, 1) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)pActor);
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
        GV_SetNamedActor_8001514C((GV_ACT *)pActor, (TActorFunction)tenage_act_800699A4,
                                  (TActorFunction)tenage_kill_80069DBC, aTenageC);

        if (tenage_loader_80069E64(pActor, vec, vec2, param_4, param_5, 0, 2) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)pActor);
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
