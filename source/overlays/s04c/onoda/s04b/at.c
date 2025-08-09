#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/blood.h"

typedef struct _AtWork
{
    GV_ACT         actor;
    OBJECT         body;
    CONTROL        control;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[16];
    MOTION_SEGMENT m_segs2[16];
    SVECTOR        rots[15];
    MATRIX         light[2];
    TARGET        *target;
    int            end_proc;
    int            draw_lifebar;
    MENU_BAR_CONF  lifebar;
    int            last_hp;
    int            hp;
    int            state;
    int            anim_timer;
    int            f730; /* unused */
    int            map;
    int            max_hp;
    int            frac_hp;
    int            update;
} AtWork;

char    at_lifebar_name[] = "BAKER";
SVECTOR at_bloodpos = {0, 0, 100, 0};
SVECTOR at_bloodrot = {-1024, 0, 0, 0};
SVECTOR at_target_size = {400, 900, 400, 0};

#define EXEC_LEVEL      GV_ACTOR_LEVEL5
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

STATIC void SetBlood(AtWork *work, int index, int count)
{
    MATRIX rot;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&at_bloodpos);
    DG_RotatePos(&at_bloodrot);
    ReadRotMatrix(&rot);
    NewBlood(&rot, count);
}

STATIC void UpdateTarget(AtWork *work)
{
    TARGET *target;
    int     hp;

    target = work->target;

    if (target->damaged & 0x4)
    {
        target->damaged &= ~0x4;

        if (work->state > -1 && work->state < 2)
        {
            SetBlood(work, 2, 0);

            switch (target->a_mode)
            {
            case 1:
                break;

            case 2:
                target->field_26_hp = 0;
                break;

            case 3:
                target->field_26_hp -= 10;
                break;

            case 4:
                target->field_26_hp -= 20;
                break;
            }

            hp = target->field_26_hp;
            if (hp < 0)
            {
                hp = 0;
            }

            work->hp = (hp * 1024) / work->frac_hp;

            if (hp <= 0)
            {
                work->state = 3;
                work->anim_timer = 0;
                GM_ConfigObjectAction(&work->body, 3, 0, 0);
                GM_SeSet2(0, 47, 129);
            }
            else
            {
                work->state = 2;
                work->anim_timer = 0;
                GM_ConfigObjectAction(&work->body, 2, 0, 0);
                GM_SeSet2(0, 47, 128);
                GM_SeSet2(0, 63, 139);
            }
        }
    }
}

STATIC void Act(AtWork *work)
{
    DG_GetLightMatrix2(&work->control.mov, work->light);
    GM_CurrentMap = work->map;
    DG_SetPos(&work->body.objs->world);

    GM_ActObject2(&work->body);

    UpdateTarget(work);
    work->target->field_28 = 0;

    switch (work->state)
    {
    case 0:
        if (++work->anim_timer >= 60)
        {
            work->anim_timer = 0;

            if (work->update != 0)
            {
                GM_SeSet(&work->control.mov, 141);
                work->state = 1;
                GM_ConfigObjectAction(&work->body, 1, 0, 0);
            }
        }
        break;

    case 1:
        if (work->body.is_end != 0)
        {
            work->state = 0;
            GM_ConfigObjectAction(&work->body, 0, 0, 0);
        }
        break;

    case 2:
        if (++work->anim_timer >= 20)
        {
            work->anim_timer = 0;
            work->state = 0;
            GM_ConfigObjectAction(&work->body, 0, 0, 0);
        }
        break;

    case 3:
        if (work->body.is_end != 0)
        {
            work->state = 4;
            GM_ConfigObjectAction(&work->body, 4, 0, 0);

            if (GM_SnakeCurrentHealth > 0)
            {
                printf("GameOver!\n");
                GCL_ExecProc(work->end_proc, 0);
                GM_GameOverTimer = 0;
                GM_GameOver();
            }
        }
        break;

    case 4:
        break;
    }

    if (work->draw_lifebar != 0)
    {
        MENU_DrawBar2(40, work->last_hp, work->hp, work->max_hp, &work->lifebar);
        work->last_hp = GV_NearSpeed(work->last_hp, work->hp, 4);
    }

    printf("GameOverTimer = %d\n", GM_GameOverTimer);
}

STATIC void Die(AtWork *work)
{
    GM_FreeObject(&work->body);
}

STATIC int CreateTarget(AtWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_SEEK | TARGET_POWER, ENEMY_SIDE, &at_target_size);
    GM_Target_8002DCCC(target, 1, -1, 128, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &work->control.mov);
    return 0;
}

STATIC int GetResources(AtWork *work, int name, int map)
{
    CONTROL       *control;
    OBJECT        *body;
    MENU_BAR_CONF *lifebar;

    GM_CurrentMap = map;

    work->state = 0;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    work->map = map;

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, control->mov.vy, -2, -2);

    body = &work->body;
    GM_InitObject(body, GV_StrCode("ats_noc"), BODY_FLAG, GV_StrCode("shacho"));
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("shacho"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    DG_SetPos2(&control->mov, &control->rot);
    ReadRotMatrix(&work->body.objs->world);

    if (CreateTarget(work) < 0)
    {
        return -1;
    }

    if (GCL_GetOption('h'))
    {
        work->frac_hp = GCL_StrToInt(GCL_GetParamResult());
        work->max_hp = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->max_hp = 192;
        work->frac_hp = 1024;
    }

    lifebar = &work->lifebar;
    lifebar->name = at_lifebar_name;
    // Set the left and right RGB values for the health bar gradient
    lifebar->left[0] = 31;
    lifebar->left[1] = 191;
    lifebar->left[2] = 95;
    lifebar->right[0] = 31;
    lifebar->right[1] = 191;
    lifebar->right[2] = 95;
    lifebar->height = 1;

    work->hp = (work->max_hp * 1024) / work->frac_hp;
    work->last_hp = (work->max_hp * 1024) / work->frac_hp;

    if (GCL_GetOption('l'))
    {
        work->draw_lifebar = GCL_StrToInt(GCL_GetParamResult());
    }

    work->f730 = 0;
    work->anim_timer = 0;

    work->target->field_26_hp = work->max_hp;

    if (GCL_GetOption('u'))
    {
        work->update = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->update = 1;
    }

    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->end_proc = -1;
    }

    return 0;
}

void *NewArmsTechPresident(int name, int where)
{
    AtWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(AtWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "at.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
