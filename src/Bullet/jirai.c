#include "jirai.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Okajima/claymore.h"
#include "chara/snake/sna_init.h"
#include "SD/g_sound.h"

extern int           dword_8009F440;
extern int           dword_8009F444;
extern int           counter_8009F448;
extern CONTROL   *GM_PlayerControl_800AB9F4;
extern int           GM_PlayerStatus_800ABA50;
extern int           GM_CurrentMap_800AB9B0;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern HITTABLE stru_800BDE78[8];
extern SVECTOR       svec_8009F44C;
extern SVECTOR       svec_8009F454;
extern SVECTOR       svec_8009F45C;
extern SVECTOR       svec_8009F464;
extern int           GM_PlayerMap_800ABA0C;
extern int           GM_PlayerMap_800ABA0C;

/*---------------------------------------------------------------------------*/
// Claymore (armed)

int dword_8009F440 = 0;
int dword_8009F444 = 0;
int counter_8009F448 = 0;
SVECTOR svec_8009F44C = {-625, -250, 750, 0};
SVECTOR svec_8009F454 = {-500, -250, 750, 0};
SVECTOR svec_8009F45C = {500, 200, 500, 0};
SVECTOR svec_8009F464 = {300, 200, 300, 0};

STATIC MATRIX *jirai_loader_helper_8006A798(MATRIX *arg0, MATRIX *arg1, HZD_FLR *floor)
{
    MATRIX mtx1;
    MATRIX mtx2;

    HZD_FLR *flr;

    int var_a2;
    int var_a0;
    int var_v1;

    if (!floor)
    {
        *arg0 = *arg1;
    }
    else
    {
        flr = (HZD_FLR *)((int)floor | 0x80000000); // cached

        var_a2 = flr->p1.h * 16;
        var_v1 = flr->p2.h * 16;
        var_a0 = flr->p3.h * 16;

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

STATIC int jirai_act_helper_8006A8F4(JiraiWork *work)
{
    int      local_10E;
    CONTROL *p_control;
    SVECTOR  v;

    if ((GM_PlayerStatus_800ABA50 & 0x40) == 0)
    {
        return 0;
    }

    local_10E = work->field_10E;
    p_control = &work->control;

    if (local_10E == TRUE)
    {
        return 0;
    }
    GV_SubVec3(&p_control->mov, &GM_PlayerPosition_800ABA10, &v);
    return GV_VecLen3(&v) < 800;
}

STATIC void JiraiDisplayText(JiraiWork *work, int arg1)
{
    SVECTOR vec;
    MATRIX *matrix;
    int temp_a2;
    int var_a1;
    int r, g, b;
    const char *text;

    matrix = &DG_Chanl(0)->field_10_eye_inv;

    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);
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
                var_a1 = SE_ITEM_FULL;
                work->field_150 = temp_a2;
            }
            else
            {
                work->control.radar_atr = RADAR_OFF;
                var_a1 = SE_ITEM_GET;

                if (GM_Weapons[WEAPON_CLAYMORE] < 0)
                {
                    GM_Weapons[WEAPON_CLAYMORE] = 0;
                }

                GM_Weapons[WEAPON_CLAYMORE]++;

                work->field_140 = temp_a2;
                work->field_150 = 0;
            }

            GM_SeSetMode(&work->control.mov, var_a1, GM_SEMODE_BOMB);
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

        MENU_Color(r, g, b);
        text = "CLAYMORE";
    }
    else
    {
        text = "FULL";
        MENU_Color(255, 48, 48);
    }

    if (work->control.map->index & GM_PlayerMap_800ABA0C)
    {
        MENU_Locate(vec.vx + 160, vec.vy + 104, 0x12);
        MENU_Printf(text);

        MENU_Color(1, 1, 1);
        MENU_Locate(vec.vx + 161, vec.vy + 105, 0x12);
        MENU_Printf(text);

        menu_Text_Init_80038B98();
    }
}

STATIC void JiraiAct(JiraiWork *work)
{
    TARGET   target;
    CONTROL *control;
    TARGET  *target2;
    int      f130;
    GV_ACT  *claymore;

    if (GM_GameStatus < 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    control = &work->control;
    DG_GetLightMatrix2(&control->mov, work->light);

    if (work->field_134_gcl_arg == 2)
    {
        if (++work->field_130 < 45)
        {
            JiraiDisplayText(work, 0);

            if ((work->field_140 != 0) && (work->field_130 == 16))
            {
                DG_InvisibleObjs(work->body.objs);
            }
        }
        else if (work->field_140 != 0)
        {
            HZD_8002A258(work->control.map->hzd, &work->control.event);
            GV_DestroyActor(&work->actor);
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
            JiraiDisplayText(work, 1);
        }
        else
        {
            work->field_134_gcl_arg = 0;
            work->field_130 = 0;
        }
    }

    if (work->field_134_gcl_arg >= 2)
    {
        work->target->damaged &= ~TARGET_PUSH;
        return;
    }

    target2 = work->target;

    GM_ActControl(control);
    GM_SetCurrentMap(work->map);
    GM_ActObject2((OBJECT *)&work->body);

    f130 = work->field_130;

    if (f130 < 16)
    {
        work->field_130++;
    }

    if ((f130 > 15) && (f130 < 64))
    {
        if (f130 & 1)
        {
            DG_InvisibleObjs(work->body.objs);
        }
        else
        {
            DG_VisibleObjs(work->body.objs);
        }

        if (++work->field_130 == 64)
        {
            DG_InvisibleObjs(work->body.objs);
        }
    }

    if (GM_GameStatus & STATE_THERMG)
    {
        DG_VisibleObjs(work->body.objs);
    }
    else if (work->field_130 == 64)
    {
        DG_InvisibleObjs(work->body.objs);
    }

    if (GM_CurrentItemId == ITEM_MINE_D)
    {
        GM_ConfigControlAttribute(control, 0x202D);
    }
    else
    {
        GM_ConfigControlAttribute(control, 0);
    }

    if (
#ifdef VR_EXE
        (GM_GameStatus & (STATE_PADRELEASE | STATE_DEMO))
#else
        (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO))
#endif
        || (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
    {
        target2->class &= ~TARGET_PUSH;
        target2->damaged &= ~TARGET_PUSH;
    }
    else
    {
        target2->class |= TARGET_PUSH;
    }

    if (((target2->damaged & TARGET_PUSH) || (dword_8009F444 != 0)) && (work->field_10E == FALSE))
    {
        if (dword_8009F440 == 1)
        {
            work->field_134_gcl_arg = dword_8009F440;
            GV_DestroyActor(&work->actor);
            return;
        }

        if ((target2->field_40 & 1) && (GM_PlayerStatus_800ABA50 & (PLAYER_INVULNERABLE | PLAYER_GROUND)))
        {
            target2->damaged &= ~TARGET_PUSH;
            dword_8009F444 = 0;
            return;
        }

        if (dword_8009F444 != 0)
        {
            work->field_144_vec.vy += 2048;
        }

        dword_8009F440 = 1;
        work->field_10E = TRUE;

        DG_VisibleObjs(work->body.objs);

        sub_800790E8();

#ifdef VR_EXE
        work->field_154 = 1;
#endif

        GM_SetTarget(&target, 4, NO_SIDE, &target2->size);
        GM_Target_8002DCCC(&target, 1, 2, 128, 0, &DG_ZeroVector);
        GM_MoveTarget(&target, &target2->center);

        GM_PowerTarget(&target);
        HZD_8002A258(work->control.map->hzd, &work->control.event);
    }

    if (work->field_10E == TRUE)
    {
        if (work->field_10C == 7)
        {
            sub_8007913C();
        }

        claymore = NewClaymore(&work->control.mov, &work->field_144_vec, 2, work->field_10C);

        if (!claymore)
        {
            work->field_10C = 0;
            work->field_10E = FALSE;
        }
        else
        {
            work->field_10C--;
        }

        if ((work->field_10C <= 0) || !claymore)
        {
            work->field_134_gcl_arg = 1;
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    if (jirai_act_helper_8006A8F4(work))
    {
        work->field_134_gcl_arg = 2;
        DG_VisibleObjs(work->body.objs);
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
    GCL_ExecProc(proc_id, &args);          \
skip:                                      \
}

STATIC void JiraiDie(JiraiWork *work)
{
#ifdef VR_EXE
    if (work->field_154)
#endif
    {
        sub_8007913C();
    }
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->body);
    GM_FreeTarget(work->target);

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

STATIC int jirai_loader_helper_8006B124(JiraiWork *work, MATRIX *pMtx, int a3)
{
    TARGET  *target;
    SVECTOR  v12;
    SVECTOR *v8;

    target = GM_AllocTarget();
    work->target = target;
    if (!target)
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

    if (GCL_GetOption('t'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &v12);
    }
    GM_SetTarget(target, 9, NO_SIDE, &v12);
    target->field_3C |= 2;
    DG_SetPos(pMtx);
    DG_PutVector(v8, &v12, 1);
    GM_MoveTarget(target, &v12);
    work->field_10C = 8;
    work->field_10E = FALSE;
    return 0;
}

STATIC int jirai_get_free_item_8006B268(void)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (!stru_800BDE78[i].actor)
        {
            return i;
        }
    }
    return -1;
}

/*---------------------------------------------------------------------------*/

STATIC int JiraiGetResources(JiraiWork *work, MATRIX *world, HZD_FLR *floor)
{
    int             map;
    CONTROL        *control;
    HITTABLE       *hittable;
    MATRIX          matrix;
    RADAR_CONE     *cone;
    OBJECT_NO_ROTS *obj;

    map = GM_PlayerMap_800ABA0C;
    control = &work->control;
    work->field_138_gcl = -1;
    work->field_13C_idx = -1;
    GM_CurrentMap_800AB9B0 = map;
    work->map = map;
    if (GM_InitControl(control, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, 0, 0, 0);
    jirai_loader_helper_8006A798(&matrix, world, floor);
    GM_ConfigControlMatrix(control, world);
    work->field_144_vec.vy = ratan2(-matrix.m[0][0], -matrix.m[2][0]) & 4095;
    work->field_144_vec.vx = ratan2(matrix.m[1][0], 4096) & 4095;
    work->field_144_vec.vz = 0;
    GM_ConfigControlAttribute(control, 0);
    obj = &work->body;
    GM_InitObjectNoRots(obj, GV_StrCode("claymore"), BODY_FLAG | DG_FLAG_ONEPIECE, 0);
    if (!obj->objs)
    {
        return -1;
    }

    DG_SetPos2(&control->mov, &work->control.rot);
    DG_PutObjs(obj->objs);
    GM_ConfigObjectLight((OBJECT *)obj, work->light);

    work->field_130 = 0;
    work->field_138_gcl = -1;
    work->field_134_gcl_arg = 0;
    work->field_140 = 0;

    if (jirai_loader_helper_8006B124(work, world, 0) < 0)
    {
        return -1;
    }

    work->field_13C_idx = jirai_get_free_item_8006B268();
    if (work->field_13C_idx < 0)
    {
        return -1;
    }

    hittable = &stru_800BDE78[work->field_13C_idx];
    hittable->actor = &work->actor;
    hittable->control = control;
    hittable->data = floor;

    cone = &work->control.radar_cone;
    cone->len = 2000;
    cone->ang = 1024;
    ++counter_8009F448;
    cone->dir = GM_PlayerControl_800AB9F4->rot.vy;
    return 0;
}

GV_ACT *NewJirai(MATRIX *world, HZD_FLR *floor)
{
    JiraiWork *work;

    if (counter_8009F448 == 8)
    {
        return 0;
    }

    work = (JiraiWork *)GV_NewActor(5, sizeof(JiraiWork));
    if (work)
    {
        work->field_104_vec = GM_PlayerControl_800AB9F4->rot;
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)JiraiAct,
                         (GV_ACTFUNC)JiraiDie, "jirai.c");

        if (JiraiGetResources(work, world, floor) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
    }

    return &work->actor;
}

/*---------------------------------------------------------------------------*/

STATIC int JiraiGetResources2(JiraiWork *work, MATRIX *world, int map)
{
    MATRIX          matrix;
    CONTROL        *ctrl;
    RADAR_CONE     *cone;
    OBJECT_NO_ROTS *obj;

    work->map = map;

    ctrl =  &work->control;
    if (GM_InitControl(ctrl, GV_StrCode("claymore"), map) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(ctrl, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(ctrl, 0, -2, -2);
    GM_ConfigControlAttribute(ctrl, 0);

    work->field_144_vec = ctrl->rot;
    obj = &work->body;
    GM_InitObjectNoRots(obj, GV_StrCode("claymore"), 877, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->light);

    work->field_104_vec = ctrl->rot;

    ctrl->rot.vx = ctrl->turn.vx = -1024;
    ctrl->rot.vy = ctrl->turn.vy += 1024;
    ctrl->mov.vy += 500;

    DG_SetPos2(&ctrl->mov, &ctrl->rot);

    ReadRotMatrix(&matrix);

    if (jirai_loader_helper_8006B124(work, &matrix, 1) < 0)
    {
        return -1;
    }

    ctrl->mov.vy -= 500;
    DG_InvisibleObjs(obj->objs);
    work->field_130 = 64;

    if (GCL_GetOption('e'))
    {
        work->field_138_gcl = GCL_StrToInt(GCL_GetParamResult());
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

GV_ACT *NewScenarioJirai(MATRIX *world, int map)
{
    JiraiWork *work = (JiraiWork *)GV_NewActor(6, sizeof(JiraiWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)JiraiAct,
                         (GV_ACTFUNC)JiraiDie, "jirai.c");
        if (JiraiGetResources2(work, world, map) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (GV_ACT *)work;
}
