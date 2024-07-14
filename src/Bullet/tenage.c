#include "tenage.h"
#include "Bullet/blast.h"
#include "Okajima/stngrnd.h"
#include "Game/control.h"
#include "Okajima/chafgrnd.h"
#include "chara/snake/sna_init.h"
#include "unknown.h"

// the projectile for all types of grenades

extern short          GM_uBombHoming_800AB3E4;
extern TBombFunction  GM_lpfnBombHoming_800AB3E8;
extern TBombFunction2 GM_lpfnBombBound_800AB3EC;
extern int            GM_GameStatus_800AB3CC;
extern int            GM_PlayerStatus_800ABA50;
extern int            dword_800BDD28;
extern Blast_Data     blast_data_8009F4B8[8];
extern SVECTOR        GM_PlayerPosition_800ABA10;
extern SVECTOR        DG_ZeroVector_800AB39C;
extern CONTROL    *tenage_ctrls_800BDD30[16];
extern int            tenage_ctrls_count_800BDD70;

//------------------------------------------------------------------------------

void TenageAct_800699A4(TenageWork *work)
{
    MATRIX rotation;
    SVECTOR vec;
    CONTROL *pCtrl;
#ifdef VR_EXE
    int vy, level;
#endif

    work->control.step = work->field_108;

    pCtrl = &work->control;

    if (GM_lpfnBombHoming_800AB3E8)
    {
        GM_lpfnBombHoming_800AB3E8(pCtrl, work->field_100_homing_arg2, &work->field_114_homing_arg3);
    }

    if ((work->control.mov.pad != 0) || (GM_GameStatus_800AB3CC < 0))
    {
        GV_DestroyActor_800151C8(&work->field_0_actor);
        return;
    }

    work->field_108 = work->control.step;

#ifdef VR_EXE
    vy = pCtrl->step.vy;
    pCtrl->step.vy = 0;
#endif

    GM_ActControl_80025A7C(pCtrl);

#ifdef VR_EXE
    vy = vy + pCtrl->mov.vy;
    level = pCtrl->levels[0] + 100;
    if (level >= vy)
    {
        pCtrl->field_57 |= 1;
        vy = level;
    }
    else
    {
        level = pCtrl->levels[1] - 100;
        if (level <= vy)
        {
            pCtrl->field_57 |= 2;
            vy = level;
        }
    }
    pCtrl->mov.vy = vy;
    DG_SetPos2_8001BC8C(&pCtrl->mov, &pCtrl->rot);
#endif

    GM_ActObject2_80034B88((OBJECT *)&work->field_9C_obj);
    DG_GetLightMatrix_8001A3C4(&pCtrl->mov, work->field_C0_light_matrices);

    if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_FLAG_BIT_32)) && !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
    {
        work->field_100_homing_arg2--;
    }

#ifdef VR_EXE
    else if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31)) == GAME_FLAG_BIT_31 && !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
    {
        work->field_100_homing_arg2--;
    }
#endif

    if (work->field_100_homing_arg2 <= 0 || dword_800BDD28 == 1)
    {
        ReadRotMatrix(&rotation);

        GM_uBombHoming_800AB3E4 = work->field_114_homing_arg3;

        switch (work->field_110)
        {
        case 1:
            NewStunGrenade_80074B5C(&rotation);
            break;

        case 2:
            NewChafgrnd_80077264(&rotation);
            break;

        case 3:
            NewBlast2_8006E0F0(&rotation, &blast_data_8009F4B8[6], work->field_118_do_sound, work->field_11C);
            break;

        default:
            NewBlast2_8006E0F0(&rotation, &blast_data_8009F4B8[0], work->field_118_do_sound, work->field_11C);
            break;
        }

        sub_8002A258(work->control.map->hzd, &work->control.field_10_events);
        GV_DestroyActor_800151C8(&work->field_0_actor);

        GM_uBombHoming_800AB3E4 = 0;
        return;
    }

    if (pCtrl->field_57 && work->field_108.vy <= 0)
    {
        work->field_108.vy = -work->field_108.vy / 8;
        work->field_108.vz /= 4;
        work->field_108.vx /= 4;

        if (work->field_108.vy < 5)
        {
            work->field_108 = DG_ZeroVector_800AB39C;
        }

        if (++work->field_104_count < 3)
        {
            if (!GM_lpfnBombBound_800AB3EC || !GM_lpfnBombBound_800AB3EC(0, pCtrl, &work->field_114_homing_arg3))
            {
                GM_SeSet_80032858(&pCtrl->mov, 43);
            }

            if (work->field_118_do_sound != 0)
            {
                GM_SetNoise(128, 12, &pCtrl->mov);
            }
        }
    }
    else
    {
        work->field_108.vy -= 16;
    }

    if (pCtrl->field_58 > 0 && GM_CheckControlTouches_8002624C(pCtrl, 300))
    {
        sub_800272E0(pCtrl->field_70[0], &vec);
        DG_ReflectVector_8001ECB4(&vec, &work->field_108, &work->field_108);

        work->field_108.vx /= 4;
        work->field_108.vz /= 4;

        if (++work->field_104_count < 3)
        {
            if (!GM_lpfnBombBound_800AB3EC || !GM_lpfnBombBound_800AB3EC(1, pCtrl, &work->field_114_homing_arg3))
            {
                GM_SeSet_80032858(&pCtrl->mov, 43);
            }
        }
    }
}

void TenageDie_80069DBC(TenageWork *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_ClearBulName_8004FBE4(work->control.name);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C_obj);

    if (work->field_120_ctrl_idx >= 0)
    {
        tenage_ctrls_800BDD30[work->field_120_ctrl_idx] = 0;
        tenage_ctrls_count_800BDD70--;
    }
}

int tenage_get_free_ctrl_80069E28(void)
{
    int i;

    for (i = 0; i < (int)(sizeof(tenage_ctrls_800BDD30) / sizeof(CONTROL *)); i++)
    {
        if (tenage_ctrls_800BDD30[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

int TenageGetResources_80069E64(TenageWork *work, SVECTOR *vec, SVECTOR *vec2,
                           int int_3,int int_4,int int_5, int int_6)
{
    CONTROL *pControl;

    pControl = &work->control;
    if (GM_InitLoader_8002599C(pControl, GM_Next_BulName_8004FBA0(), 0) >= 0)
    {
        if (int_5 != 0)
        {
            GM_ConfigControlHazard_8002622C(pControl, 100, 50, 50);
        }
        else
        {
            GM_ConfigControlHazard_8002622C(pControl, 100, -1, -1);
        }
        pControl->field_59 = 4;
        if (int_6 == 1)
        {
            pControl->mov = GM_PlayerPosition_800ABA10;
            GM_ConfigControlTrapCheck_80026308(pControl);
            GM_ActControl_80025A7C(pControl);
        }
        GM_ConfigControlVector_800260FC(pControl, vec, (SVECTOR *)&DG_ZeroVector_800AB39C);
        work->field_108 = *vec2;
        GM_InitObjectNoRots_800349B0(&work->field_9C_obj, int_4, WEAPON_FLAG, 0);
        if (work->field_9C_obj.objs)
        {
            DG_SetPos2_8001BC8C(&pControl->mov, &pControl->rot);
            DG_PutObjs_8001BDB8((work->field_9C_obj).objs);
            GM_ConfigObjectLight_80034C44((OBJECT *)&work->field_9C_obj, work->field_C0_light_matrices);

            work->field_120_ctrl_idx = tenage_get_free_ctrl_80069E28();
            if (work->field_120_ctrl_idx >= 0)
            {
                tenage_ctrls_800BDD30[work->field_120_ctrl_idx] = pControl;
                pControl->mov.pad = 0;
                tenage_ctrls_count_800BDD70 = tenage_ctrls_count_800BDD70 + 1;
                return 0;
            }
        }
    }
    return -1;
}

GV_ACT *NewTenage_8006A010(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5)
{
    TenageWork *work;

    if (tenage_ctrls_count_800BDD70 == 16)
    {
        return NULL;
    }

    work = (TenageWork *)GV_NewActor_800150E4(5, sizeof(TenageWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)TenageAct_800699A4,
                                  (TActorFunction)TenageDie_80069DBC, "tenage.c");

        if (TenageGetResources_80069E64(work, vec, vec2, param_4, param_5, 1, 1) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return NULL;
        }

        work->field_100_homing_arg2 = param_3;
        work->field_104_count = 0;
        work->field_110 = param_4;
        work->field_118_do_sound = 1;
        work->field_11C = 1;
    }

    return &work->field_0_actor;
}

void sub_8006A100(SVECTOR *vec, SVECTOR *vec2, int param_3)
{
    NewTenage_8006A010(vec, vec2, param_3, 0, 0x3b88);
}

// enemy's grenades, probably
TenageWork *NewTenage3_8006A128(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5, int param_6,
                                  int param_7)
{
    TenageWork *work;

    work = (TenageWork *)GV_NewActor_800150E4(6, sizeof(TenageWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)TenageAct_800699A4,
                                  (TActorFunction)TenageDie_80069DBC, "tenage.c");

        if (TenageGetResources_80069E64(work, vec, vec2, param_4, param_5, 0, 2) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return NULL;
        }

        work->field_100_homing_arg2 = param_3;
        work->field_104_count = 0;
        work->field_110 = param_4;
        work->field_118_do_sound = param_6 & 1;
        work->field_11C = param_7 & 1;
    }

    return work;
}
