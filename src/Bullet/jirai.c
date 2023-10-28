#include "jirai.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Okajima/claymore.h"
#include "libdg/libdg.h"
#include "chara/snake/sna_init.h"
#include "unknown.h"
#include "psyq.h"
#include "Game/map.h"

// claymore (on ground)

extern int           dword_8009F440;
extern int           dword_8009F444;
extern int           counter_8009F448;
extern CONTROL   *GM_PlayerControl_800AB9F4;
extern int           GM_PlayerStatus_800ABA50;
extern int           GM_GameStatus_800AB3CC;
extern int           GM_CurrentMap_800AB9B0;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern Jirai_unknown stru_800BDE78[8];
extern SVECTOR       svec_8009F44C;
extern SVECTOR       svec_8009F454;
extern SVECTOR       svec_8009F45C;
extern SVECTOR       svec_8009F464;
extern int           GM_PlayerMap_800ABA0C;
extern int           GM_PlayerMap_800ABA0C;
extern SVECTOR       DG_ZeroVector_800AB39C;

int dword_8009F440 = 0;
int dword_8009F444 = 0;
int counter_8009F448 = 0;
SVECTOR svec_8009F44C = {-625, -250, 750, 0};
SVECTOR svec_8009F454 = {-500, -250, 750, 0};
SVECTOR svec_8009F45C = {500, 200, 500, 0};
SVECTOR svec_8009F464 = {300, 200, 300, 0};

// TARGET here seems to be wrong
MATRIX * jirai_loader_helper_8006A798(MATRIX *arg0, MATRIX *arg1, TARGET *pTarget)
{
    MATRIX mtx1;
    MATRIX mtx2;

    TARGET *temp_v0;

    int var_a2;
    int var_a0;
    int var_v1;

    if (!pTarget)
    {
        *arg0 = *arg1;
    }
    else
    {
        temp_v0 = (TARGET *)((int)pTarget | 0x80000000);

        var_a2 = temp_v0->field_10_size.pad << 4;
        var_v1 = ((int)temp_v0->field_1C >> 16) << 4;
        var_a0 = temp_v0->field_26_hp << 4;

        if (var_a0 < 0)
        {
            var_a2 = -var_a2;
            var_a0 = -var_a0;
            var_v1 = -var_v1;
        }

        mtx1.m[2][0] = 0;
        mtx1.m[0][1] = var_a2;
        mtx1.m[1][0] = -var_a2;
        mtx1.m[0][0] = var_a0;
        mtx1.m[1][1] = var_a0;
        mtx1.m[2][1] = var_v1;
        mtx1.m[0][2] = 0;
        mtx1.m[2][2] = var_a0;
        mtx1.m[1][2] = -var_v1;

        mtx2 = *arg1;
        MulMatrix2(&mtx1, &mtx2);
        *arg0 = mtx2;
    }

    return arg0;
}

int jirai_act_helper_8006A8F4(Actor_Jirai *pActor)
{
    int         local_10E;       // $v1
    CONTROL *p_field_20_ctrl; // $a0
    SVECTOR     v;

    if ((GM_PlayerStatus_800ABA50 & 0x40) == 0)
    {
        return 0;
    }

    local_10E = pActor->field_10E;
    p_field_20_ctrl = &pActor->field_20_ctrl;
    if (local_10E == 1)
    {
        return 0;
    }
    GV_SubVec3_80016D40(&p_field_20_ctrl->field_0_mov, &GM_PlayerPosition_800ABA10, &v);
    return GV_LengthVec3_80016D80(&v) < 800;
}

void jirai_act_helper_8006A950(Actor_Jirai *pActor, int arg1)
{
    SVECTOR vec;
    MATRIX *pMatrix;
    int temp_a2;
    int var_a1;
    int r, g, b;
    const char *pText;

    pMatrix = &DG_Chanl(0)->field_10_eye_inv;

    gte_SetRotMatrix(pMatrix);
    gte_SetTransMatrix(pMatrix);
    gte_ldv0(&pActor->field_20_ctrl.field_0_mov);
    gte_rtps();
    gte_stsxy(&vec);

    if ((pActor->field_130 < 16) && (arg1 == 0))
    {
        vec.vy -= pActor->field_130;
    }
    else
    {
        vec.vy -= 16;
    }

    if (arg1 == 0)
    {
        temp_a2 = pActor->field_130;

        if (temp_a2 == 1)
        {
            if (GM_Weapons[WEAPON_CLAYMORE] >= GM_WeaponsMax[WEAPON_CLAYMORE])
            {
                var_a1 = 11;
                pActor->field_150 = temp_a2;
            }
            else
            {
                pActor->field_20_ctrl.field_3A = 0;
                var_a1 = 22;

                if (GM_Weapons[WEAPON_CLAYMORE] < 0)
                {
                    GM_Weapons[WEAPON_CLAYMORE] = 0;
                }

                GM_Weapons[WEAPON_CLAYMORE]++;

                pActor->field_140 = temp_a2;
                pActor->field_150 = 0;
            }

            GM_Sound_800329C4(&pActor->field_20_ctrl.field_0_mov, var_a1, 1);
        }

        if (pActor->field_150 != 0)
        {
            r = 255;
            g = 48;
            b = 48;
        }
        else
        {
            r = 200;
            g = 200;
            b = 200;
        }

        menu_Color_80038B4C(r, g, b);
        pText = "CLAYMORE";
    }
    else
    {
        pText = "FULL";
        menu_Color_80038B4C(255, 48, 48);
    }

    if (pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C)
    {
        menu_Text_XY_Flags_80038B34(vec.vx + 160, vec.vy + 104, 0x12);
        menu_Text_80038C38(pText);

        menu_Color_80038B4C(1, 1, 1);
        menu_Text_XY_Flags_80038B34(vec.vx + 161, vec.vy + 105, 0x12);
        menu_Text_80038C38(pText);

        menu_Text_Init_80038B98();
    }
}

void jirai_act_8006AB5C(Actor_Jirai *pActor)
{
    TARGET target;
    CONTROL *pCtrl;
    TARGET *pTarget;
    int f130;
    Actor_Claymore *pClaymore;

    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    pCtrl = &pActor->field_20_ctrl;
    DG_GetLightMatrix2_8001A5D8(&pCtrl->field_0_mov, pActor->field_C0_light_matrices);

    if (pActor->field_134_gcl_arg == 2)
    {
        if (++pActor->field_130 < 45)
        {
            jirai_act_helper_8006A950(pActor, 0);

            if ((pActor->field_140 != 0) && (pActor->field_130 == 16))
            {
                DG_InvisibleObjs(pActor->field_9C_obj.objs);
            }
        }
        else if (pActor->field_140 != 0)
        {
            sub_8002A258(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl.field_10_pStruct_hzd_unknown);
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
        }
        else
        {
            pActor->field_130 = 0;
            pActor->field_134_gcl_arg = 3;
        }
    }
    else if (pActor->field_134_gcl_arg == 3)
    {
        if ((++pActor->field_130 < 45) || jirai_act_helper_8006A8F4(pActor))
        {
            jirai_act_helper_8006A950(pActor, 1);
        }
        else
        {
            pActor->field_134_gcl_arg = 0;
            pActor->field_130 = 0;
        }
    }

    if (pActor->field_134_gcl_arg >= 2)
    {
        pActor->field_100_pTarget->field_6_flags &= ~TARGET_PUSH;
        return;
    }

    pTarget = pActor->field_100_pTarget;

    GM_ActControl_80025A7C(pCtrl);
    GM_SetCurrentMap(pActor->field_14C_map);
    GM_ActObject2_80034B88(&pActor->field_9C_obj);

    f130 = pActor->field_130;

    if (f130 < 16)
    {
        pActor->field_130++;
    }

    if ((f130 > 15) && (f130 < 64))
    {
        if (f130 & 1)
        {
            DG_InvisibleObjs(pActor->field_9C_obj.objs);
        }
        else
        {
            DG_VisibleObjs(pActor->field_9C_obj.objs);
        }

        if (++pActor->field_130 == 64)
        {
            DG_InvisibleObjs(pActor->field_9C_obj.objs);
        }
    }

    if (GM_GameStatus_800AB3CC & 8)
    {
        DG_VisibleObjs(pActor->field_9C_obj.objs);
    }
    else if (pActor->field_130 == 64)
    {
        DG_InvisibleObjs(pActor->field_9C_obj.objs);
    }

    if (GM_CurrentItemId == ITEM_MINE_D)
    {
        GM_ConfigControlAttribute_8002623C(pCtrl, 0x202D);
    }
    else
    {
        GM_ConfigControlAttribute_8002623C(pCtrl, 0);
    }

    if (
#ifdef VR_EXE
        (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_32))
#else
        (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_FLAG_BIT_32))
#endif
        || (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
    {
        pTarget->class &= ~TARGET_PUSH;
        pTarget->field_6_flags &= ~TARGET_PUSH;
    }
    else
    {
        pTarget->class |= TARGET_PUSH;
    }

    if (((pTarget->field_6_flags & TARGET_PUSH) || (dword_8009F444 != 0)) && (pActor->field_10E == 0))
    {
        if (dword_8009F440 == 1)
        {
            pActor->field_134_gcl_arg = dword_8009F440;
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return;
        }

        if ((pTarget->field_40 & 1) && (GM_PlayerStatus_800ABA50 & (PLAYER_INVULNERABLE | PLAYER_PRONE)))
        {
            pTarget->field_6_flags &= ~TARGET_PUSH;
            dword_8009F444 = 0;
            return;
        }

        if (dword_8009F444 != 0)
        {
            pActor->field_144_vec.vy += 2048;
        }

        dword_8009F440 = 1;
        pActor->field_10E = 1;

        DG_VisibleObjs(pActor->field_9C_obj.objs);

        sub_800790E8();

#ifdef VR_EXE
        pActor->field_154 = 1;
#endif

        GM_SetTarget_8002DC74(&target, 4, NO_SIDE, &pTarget->field_10_size);
        GM_Target_8002DCCC(&target, 1, 2, 128, 0, &DG_ZeroVector_800AB39C);
        GM_Target_SetVector_8002D500(&target, &pTarget->field_8_vec);

        sub_8002D7DC(&target);
        sub_8002A258(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl.field_10_pStruct_hzd_unknown);
    }

    if (pActor->field_10E == 1)
    {
        if (pActor->field_10C == 7)
        {
            sub_8007913C();
        }

        pClaymore = NewClaymore_80073B8C(&pActor->field_20_ctrl.field_0_mov, &pActor->field_144_vec, 2, pActor->field_10C);

        if (!pClaymore)
        {
            pActor->field_10C = 0;
            pActor->field_10E = 0;
        }
        else
        {
            pActor->field_10C--;
        }

        if ((pActor->field_10C <= 0) || !pClaymore)
        {
            pActor->field_134_gcl_arg = 1;
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return;
        }
    }

    if (jirai_act_helper_8006A8F4(pActor))
    {
        pActor->field_134_gcl_arg = 2;
        DG_VisibleObjs(pActor->field_9C_obj.objs);
        pActor->field_130 = 0;
    }
}

// A different version of ExecProc is used here, which checks for a proccess ID less than zero.
#define ExecProc(proc_id, mode)            \
{                                          \
    GCL_ARGS args;                         \
    long data;                             \
                                           \
    if (proc_id < 0) goto skip;            \
                                           \
    args.argc = 1;                         \
    args.argv = &data;                     \
    data = mode;                           \
    do {} while (0);                       \
    GCL_ExecProc_8001FF2C(proc_id, &args); \
skip:                                      \
}

void jirai_kill_8006B05C(Actor_Jirai *pActor)
{
#ifdef VR_EXE
    if (pActor->field_154)
#endif
    {
        sub_8007913C();
    }
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    GM_FreeTarget_8002D4B0(pActor->field_100_pTarget);

    if (pActor->field_13C_idx >= 0)
    {
        GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
        stru_800BDE78[pActor->field_13C_idx].field_4_pActor = NULL;
        counter_8009F448 = counter_8009F448 - 1;
    }

    ExecProc(pActor->field_138_gcl, pActor->field_134_gcl_arg);

    dword_8009F444 = 0;
    dword_8009F440 = 0;
}

int jirai_loader_helper_8006B124(Actor_Jirai *pActor, MATRIX *pMtx, int a3)
{
    TARGET *pNewTarget;
    SVECTOR    v12;
    SVECTOR   *v8;

    pNewTarget = GM_AllocTarget_8002D400();
    pActor->field_100_pTarget = pNewTarget;
    if (!pNewTarget)
    {
        return -1;
    }

    if (a3)
    {
        v12 = svec_8009F45C;
    }
    else
    {
        v12 = svec_8009F464;
    }

    if (a3)
    {
        v8 = &svec_8009F454;
    }
    else
    {
        v8 = &svec_8009F44C;
    }

    if (GCL_GetOption_80020968('t'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &v12);
    }
    GM_SetTarget_8002DC74(pNewTarget, 9, NO_SIDE, &v12);
    pNewTarget->field_3C |= 2;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(v8, &v12, 1);
    GM_Target_SetVector_8002D500(pNewTarget, &v12);
    pActor->field_10C = 8;
    pActor->field_10E = 0;
    return 0;
}

int jirai_get_free_item_8006B268()
{
    int i; // $v1
    for (i = 0; i < 8; i++)
    {
        if (!stru_800BDE78[i].field_4_pActor)
        {
            return i;
        }
    }
    return -1;
}

int jirai_loader_8006B2A4(Actor_Jirai *pActor, MATRIX *pMtx, TARGET *pTarget)
{
    int            map;      // $v1
    CONTROL       *pCtrl;    // $s2
    Jirai_unknown *pUnknown; // $a0
    MATRIX         matrix;   // [sp+10h] [-20h] BYREF
    SVECTOR       *vec;
    OBJECT        *obj;

    map = GM_PlayerMap_800ABA0C;
    pCtrl = &pActor->field_20_ctrl;
    pActor->field_138_gcl = -1;
    pActor->field_13C_idx = -1;
    GM_CurrentMap_800AB9B0 = map;
    pActor->field_14C_map = map;
    if (GM_InitLoader_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    jirai_loader_helper_8006A798(&matrix, pMtx, pTarget);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    pActor->field_144_vec.vy = ratan2(-matrix.m[0][0], -matrix.m[2][0]) & 4095;
    pActor->field_144_vec.vx = ratan2(matrix.m[1][0], 4096) & 4095;
    pActor->field_144_vec.vz = 0;
    GM_ConfigControlAttribute_8002623C(pCtrl, 0);
    obj = &pActor->field_9C_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC("claymore"), 877, 0);
    if (!obj->objs)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->field_0_mov, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutObjs_8001BDB8(obj->objs);
    GM_ConfigObjectLight_80034C44(obj, pActor->field_C0_light_matrices);

    pActor->field_130 = 0;
    pActor->field_138_gcl = -1;
    pActor->field_134_gcl_arg = 0;
    pActor->field_140 = 0;

    if (jirai_loader_helper_8006B124(pActor, pMtx, 0) < 0)
    {
        return -1;
    }

    pActor->field_13C_idx = jirai_get_free_item_8006B268();
    if (pActor->field_13C_idx < 0)
    {
        return -1;
    }

    pUnknown = &stru_800BDE78[pActor->field_13C_idx];
    pUnknown->field_4_pActor = &pActor->field_0_actor;
    pUnknown->field_8_pCtrl = pCtrl;
    pUnknown->field_C_pTarget = pTarget;

    vec = &pActor->field_20_ctrl.field_3C;
    vec->vy = 2000;
    vec->vz = 1024;
    ++counter_8009F448;
    vec->vx = GM_PlayerControl_800AB9F4->field_8_rotator.vy;
    return 0;
}

Actor_Jirai * NewJirai_8006B48C(DG_OBJ *pObj, TARGET *pTarget)
{
    Actor_Jirai *pActor; // $s0

    if (counter_8009F448 == 8)
    {
        return 0;
    }

    pActor = (Actor_Jirai *)GV_NewActor_800150E4(5, sizeof(Actor_Jirai));
    if (pActor)
    {
        pActor->field_104_vec = GM_PlayerControl_800AB9F4->field_8_rotator;
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, "jirai.c");

        if (jirai_loader_8006B2A4(pActor, &pObj->world, pTarget) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return pActor;
}

int jirai_loader_8006B564(Actor_Jirai *pActor, int _matrix, int map)
{
    MATRIX      matrix;
    CONTROL *ctrl;
    SVECTOR    *vec;
    OBJECT     *obj;

    pActor->field_14C_map = map;

    ctrl =  &pActor->field_20_ctrl;
    if (GM_InitLoader_8002599C(ctrl, GV_StrCode_80016CCC("claymore"), map) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(ctrl, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(ctrl, 0, -2, -2);
    GM_ConfigControlAttribute_8002623C(ctrl, 0);

    pActor->field_144_vec = ctrl->field_8_rotator;
    obj = &pActor->field_9C_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC("claymore"), 877, 0);
    GM_ConfigObjectLight_80034C44(obj, pActor->field_C0_light_matrices);

    pActor->field_104_vec = ctrl->field_8_rotator;

    ctrl->field_8_rotator.vx = ctrl->field_4C_turn_vec.vx = -1024;
    ctrl->field_8_rotator.vy = ctrl->field_4C_turn_vec.vy += 1024;
    ctrl->field_0_mov.vy += 500;

    DG_SetPos2_8001BC8C(&ctrl->field_0_mov, &ctrl->field_8_rotator);

    ReadRotMatrix(&matrix);

    if (jirai_loader_helper_8006B124(pActor, &matrix, 1) < 0)
    {
        return -1;
    }

    ctrl->field_0_mov.vy -= 500;
    DG_InvisibleObjs(obj->objs);
    pActor->field_130 = 64;

    if (GCL_GetOption_80020968('e'))
    {
        pActor->field_138_gcl = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        pActor->field_138_gcl = -1;
    }

    pActor->field_134_gcl_arg = 0;
    pActor->field_13C_idx = -1;
    pActor->field_140 = 0;

    vec = &ctrl->field_3C;
    vec->vy = 2000;
    vec->vz = 1024;
    vec->vx = ctrl->field_8_rotator.vy - 1024;

    return 0;
}

Actor_Jirai * NewScenarioJirai_8006B76C(int a1, int map)
{
    Actor_Jirai *pActor = (Actor_Jirai *)GV_NewActor_800150E4(6, sizeof(Actor_Jirai));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, "jirai.c");
        if (jirai_loader_8006B564(pActor, a1, map) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }
    }
    return pActor;
}
