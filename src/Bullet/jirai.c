#include "jirai.h"
#include "libgcl/libgcl.h"
#include "Game/hittable.h"
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
extern HITTABLE stru_800BDE78[8];
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

MATRIX * jirai_loader_helper_8006A798(MATRIX *arg0, MATRIX *arg1, HZD_FLR *flr)
{
    MATRIX mtx1;
    MATRIX mtx2;

    HZD_FLR *temp_v0;

    int var_a2;
    int var_a0;
    int var_v1;

    if (!flr)
    {
        *arg0 = *arg1;
    }
    else
    {
        temp_v0 = (HZD_FLR *)((int)flr | 0x80000000);

        var_a2 = temp_v0->p1.h * 16;
        var_v1 = temp_v0->p2.h * 16;
        var_a0 = temp_v0->p3.h * 16;

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

int jirai_act_helper_8006A8F4(JiraiWork *work)
{
    int         local_10E;       // $v1
    CONTROL *p_control; // $a0
    SVECTOR     v;

    if ((GM_PlayerStatus_800ABA50 & 0x40) == 0)
    {
        return 0;
    }

    local_10E = work->field_10E;
    p_control = &work->control;
    if (local_10E == 1)
    {
        return 0;
    }
    GV_SubVec3_80016D40(&p_control->mov, &GM_PlayerPosition_800ABA10, &v);
    return GV_VecLen3_80016D80(&v) < 800;
}

void jirai_act_helper_8006A950(JiraiWork *work, int arg1)
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
    gte_ldv0(&work->control.mov);
    gte_rtps();
    gte_stsxy(&vec);

    if ((work->field_130 < 16) && (arg1 == 0))
    {
        vec.vy -= work->field_130;
    }
    else
    {
        vec.vy -= 16;
    }

    if (arg1 == 0)
    {
        temp_a2 = work->field_130;

        if (temp_a2 == 1)
        {
            if (GM_Weapons[WEAPON_CLAYMORE] >= GM_WeaponsMax[WEAPON_CLAYMORE])
            {
                var_a1 = 11;
                work->field_150 = temp_a2;
            }
            else
            {
                work->control.radar_atr = RADAR_OFF;
                var_a1 = 22;

                if (GM_Weapons[WEAPON_CLAYMORE] < 0)
                {
                    GM_Weapons[WEAPON_CLAYMORE] = 0;
                }

                GM_Weapons[WEAPON_CLAYMORE]++;

                work->field_140 = temp_a2;
                work->field_150 = 0;
            }

            GM_Sound_800329C4(&work->control.mov, var_a1, 1);
        }

        if (work->field_150 != 0)
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

        MENU_Color_80038B4C(r, g, b);
        pText = "CLAYMORE";
    }
    else
    {
        pText = "FULL";
        MENU_Color_80038B4C(255, 48, 48);
    }

    if (work->control.map->index & GM_PlayerMap_800ABA0C)
    {
        MENU_Locate_80038B34(vec.vx + 160, vec.vy + 104, 0x12);
        MENU_Printf_80038C38(pText);

        MENU_Color_80038B4C(1, 1, 1);
        MENU_Locate_80038B34(vec.vx + 161, vec.vy + 105, 0x12);
        MENU_Printf_80038C38(pText);

        menu_Text_Init_80038B98();
    }
}

void jirai_act_8006AB5C(JiraiWork *work)
{
    TARGET target;
    CONTROL *pCtrl;
    TARGET *pTarget;
    int f130;
    GV_ACT *pClaymore;

    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&work->field_0_actor);
        return;
    }

    pCtrl = &work->control;
    DG_GetLightMatrix2_8001A5D8(&pCtrl->mov, work->field_C0_light_matrices);

    if (work->field_134_gcl_arg == 2)
    {
        if (++work->field_130 < 45)
        {
            jirai_act_helper_8006A950(work, 0);

            if ((work->field_140 != 0) && (work->field_130 == 16))
            {
                DG_InvisibleObjs(work->field_9C_obj.objs);
            }
        }
        else if (work->field_140 != 0)
        {
            sub_8002A258(work->control.map->hzd, &work->control.field_10_events);
            GV_DestroyActor_800151C8(&work->field_0_actor);
        }
        else
        {
            work->field_130 = 0;
            work->field_134_gcl_arg = 3;
        }
    }
    else if (work->field_134_gcl_arg == 3)
    {
        if ((++work->field_130 < 45) || jirai_act_helper_8006A8F4(work))
        {
            jirai_act_helper_8006A950(work, 1);
        }
        else
        {
            work->field_134_gcl_arg = 0;
            work->field_130 = 0;
        }
    }

    if (work->field_134_gcl_arg >= 2)
    {
        work->field_100_pTarget->damaged &= ~TARGET_PUSH;
        return;
    }

    pTarget = work->field_100_pTarget;

    GM_ActControl_80025A7C(pCtrl);
    GM_SetCurrentMap(work->field_14C_map);
    GM_ActObject2_80034B88((OBJECT *)&work->field_9C_obj);

    f130 = work->field_130;

    if (f130 < 16)
    {
        work->field_130++;
    }

    if ((f130 > 15) && (f130 < 64))
    {
        if (f130 & 1)
        {
            DG_InvisibleObjs(work->field_9C_obj.objs);
        }
        else
        {
            DG_VisibleObjs(work->field_9C_obj.objs);
        }

        if (++work->field_130 == 64)
        {
            DG_InvisibleObjs(work->field_9C_obj.objs);
        }
    }

    if (GM_GameStatus_800AB3CC & 8)
    {
        DG_VisibleObjs(work->field_9C_obj.objs);
    }
    else if (work->field_130 == 64)
    {
        DG_InvisibleObjs(work->field_9C_obj.objs);
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
        pTarget->damaged &= ~TARGET_PUSH;
    }
    else
    {
        pTarget->class |= TARGET_PUSH;
    }

    if (((pTarget->damaged & TARGET_PUSH) || (dword_8009F444 != 0)) && (work->field_10E == 0))
    {
        if (dword_8009F440 == 1)
        {
            work->field_134_gcl_arg = dword_8009F440;
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return;
        }

        if ((pTarget->field_40 & 1) && (GM_PlayerStatus_800ABA50 & (PLAYER_INVULNERABLE | PLAYER_GROUND)))
        {
            pTarget->damaged &= ~TARGET_PUSH;
            dword_8009F444 = 0;
            return;
        }

        if (dword_8009F444 != 0)
        {
            work->field_144_vec.vy += 2048;
        }

        dword_8009F440 = 1;
        work->field_10E = 1;

        DG_VisibleObjs(work->field_9C_obj.objs);

        sub_800790E8();

#ifdef VR_EXE
        work->field_154 = 1;
#endif

        GM_SetTarget_8002DC74(&target, 4, NO_SIDE, &pTarget->size);
        GM_Target_8002DCCC(&target, 1, 2, 128, 0, &DG_ZeroVector_800AB39C);
        GM_MoveTarget_8002D500(&target, &pTarget->center);

        GM_PowerTarget_8002D7DC(&target);
        sub_8002A258(work->control.map->hzd, &work->control.field_10_events);
    }

    if (work->field_10E == 1)
    {
        if (work->field_10C == 7)
        {
            sub_8007913C();
        }

        pClaymore = NewClaymore_80073B8C(&work->control.mov, &work->field_144_vec, 2, work->field_10C);

        if (!pClaymore)
        {
            work->field_10C = 0;
            work->field_10E = 0;
        }
        else
        {
            work->field_10C--;
        }

        if ((work->field_10C <= 0) || !pClaymore)
        {
            work->field_134_gcl_arg = 1;
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return;
        }
    }

    if (jirai_act_helper_8006A8F4(work))
    {
        work->field_134_gcl_arg = 2;
        DG_VisibleObjs(work->field_9C_obj.objs);
        work->field_130 = 0;
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

void jirai_kill_8006B05C(JiraiWork *work)
{
#ifdef VR_EXE
    if (work->field_154)
#endif
    {
        sub_8007913C();
    }
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C_obj);
    GM_FreeTarget_8002D4B0(work->field_100_pTarget);

    if (work->field_13C_idx >= 0)
    {
        GM_ClearBulName_8004FBE4(work->control.name);
        stru_800BDE78[work->field_13C_idx].actor = NULL;
        counter_8009F448--;
    }

    ExecProc(work->field_138_gcl, work->field_134_gcl_arg);

    dword_8009F444 = 0;
    dword_8009F440 = 0;
}

int jirai_loader_helper_8006B124(JiraiWork *work, MATRIX *pMtx, int a3)
{
    TARGET *pNewTarget;
    SVECTOR    v12;
    SVECTOR   *v8;

    pNewTarget = GM_AllocTarget_8002D400();
    work->field_100_pTarget = pNewTarget;
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
    GM_MoveTarget_8002D500(pNewTarget, &v12);
    work->field_10C = 8;
    work->field_10E = 0;
    return 0;
}

int jirai_get_free_item_8006B268()
{
    int i; // $v1
    for (i = 0; i < 8; i++)
    {
        if (!stru_800BDE78[i].actor)
        {
            return i;
        }
    }
    return -1;
}

int jirai_loader_8006B2A4(JiraiWork *work, MATRIX *pMtx, HZD_FLR *flr)
{
    int             map;      // $v1
    CONTROL        *pCtrl;    // $s2
    HITTABLE       *pUnknown; // $a0
    MATRIX          matrix;   // [sp+10h] [-20h] BYREF
    RADAR_CONE     *cone;
    OBJECT_NO_ROTS *obj;

    map = GM_PlayerMap_800ABA0C;
    pCtrl = &work->control;
    work->field_138_gcl = -1;
    work->field_13C_idx = -1;
    GM_CurrentMap_800AB9B0 = map;
    work->field_14C_map = map;
    if (GM_InitLoader_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    jirai_loader_helper_8006A798(&matrix, pMtx, flr);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    work->field_144_vec.vy = ratan2(-matrix.m[0][0], -matrix.m[2][0]) & 4095;
    work->field_144_vec.vx = ratan2(matrix.m[1][0], 4096) & 4095;
    work->field_144_vec.vz = 0;
    GM_ConfigControlAttribute_8002623C(pCtrl, 0);
    obj = &work->field_9C_obj;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode_80016CCC("claymore"), 877, 0);
    if (!obj->objs)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->mov, &work->control.rot);
    DG_PutObjs_8001BDB8(obj->objs);
    GM_ConfigObjectLight_80034C44((OBJECT *)obj, work->field_C0_light_matrices);

    work->field_130 = 0;
    work->field_138_gcl = -1;
    work->field_134_gcl_arg = 0;
    work->field_140 = 0;

    if (jirai_loader_helper_8006B124(work, pMtx, 0) < 0)
    {
        return -1;
    }

    work->field_13C_idx = jirai_get_free_item_8006B268();
    if (work->field_13C_idx < 0)
    {
        return -1;
    }

    pUnknown = &stru_800BDE78[work->field_13C_idx];
    pUnknown->actor = &work->field_0_actor;
    pUnknown->control = pCtrl;
    pUnknown->data = flr;

    cone = &work->control.radar_cone;
    cone->len = 2000;
    cone->ang = 1024;
    ++counter_8009F448;
    cone->dir = GM_PlayerControl_800AB9F4->rot.vy;
    return 0;
}

GV_ACT *NewJirai_8006B48C(DG_OBJ *pObj, HZD_FLR *flr)
{
    JiraiWork *work; // $s0

    if (counter_8009F448 == 8)
    {
        return 0;
    }

    work = (JiraiWork *)GV_NewActor_800150E4(5, sizeof(JiraiWork));
    if (work)
    {
        work->field_104_vec = GM_PlayerControl_800AB9F4->rot;
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, "jirai.c");

        if (jirai_loader_8006B2A4(work, &pObj->world, flr) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }
    }

    return &work->field_0_actor;
}

int jirai_loader_8006B564(JiraiWork *work, int _matrix, int map)
{
    MATRIX          matrix;
    CONTROL        *ctrl;
    RADAR_CONE     *cone;
    OBJECT_NO_ROTS *obj;

    work->field_14C_map = map;

    ctrl =  &work->control;
    if (GM_InitLoader_8002599C(ctrl, GV_StrCode_80016CCC("claymore"), map) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(ctrl, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(ctrl, 0, -2, -2);
    GM_ConfigControlAttribute_8002623C(ctrl, 0);

    work->field_144_vec = ctrl->rot;
    obj = &work->field_9C_obj;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode_80016CCC("claymore"), 877, 0);
    GM_ConfigObjectLight_80034C44((OBJECT *)obj, work->field_C0_light_matrices);

    work->field_104_vec = ctrl->rot;

    ctrl->rot.vx = ctrl->turn.vx = -1024;
    ctrl->rot.vy = ctrl->turn.vy += 1024;
    ctrl->mov.vy += 500;

    DG_SetPos2_8001BC8C(&ctrl->mov, &ctrl->rot);

    ReadRotMatrix(&matrix);

    if (jirai_loader_helper_8006B124(work, &matrix, 1) < 0)
    {
        return -1;
    }

    ctrl->mov.vy -= 500;
    DG_InvisibleObjs(obj->objs);
    work->field_130 = 64;

    if (GCL_GetOption_80020968('e'))
    {
        work->field_138_gcl = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_138_gcl = -1;
    }

    work->field_134_gcl_arg = 0;
    work->field_13C_idx = -1;
    work->field_140 = 0;

    cone = &ctrl->radar_cone;
    cone->len = 2000;
    cone->ang = 1024;
    cone->dir = ctrl->rot.vy - 1024;

    return 0;
}

JiraiWork * NewScenarioJirai_8006B76C(int a1, int map)
{
    JiraiWork *work = (JiraiWork *)GV_NewActor_800150E4(6, sizeof(JiraiWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, "jirai.c");
        if (jirai_loader_8006B564(work, a1, map) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return NULL;
        }
    }
    return work;
}
