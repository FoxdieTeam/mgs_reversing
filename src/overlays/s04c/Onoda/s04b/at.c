#include "common.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Okajima/blood.h"

typedef struct _AtWork
{
    GV_ACT         actor;
    OBJECT         body;
    CONTROL        control;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT oar1[16];
    MOTION_SEGMENT oar2[16];
    SVECTOR        rots[15];
    MATRIX         light[2];
    TARGET        *target;
    int            f70C;
    int            f710;
    MENU_BAR_CONF  lifebar;
    int            f720;
    int            f724;
    int            f728;
    int            f72C;
    int            f730;
    int            map;
    int            f738;
    int            f73C;
    int            f740;
} AtWork;

char    at_lifebar_name[] = "BAKER";
SVECTOR at_bloodpos = {0, 0, 100, 0};
SVECTOR at_bloodrot = {-1024, 0, 0, 0};
SVECTOR at_target_size = {400, 900, 400, 0};

extern SVECTOR DG_ZeroVector;
extern int     GM_GameOverTimer;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

void s04c_at_800D7134(AtWork *work, int index, int count)
{
    MATRIX rot;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&at_bloodpos);
    DG_RotatePos(&at_bloodrot);
    ReadRotMatrix(&rot);
    NewBlood_80072728(&rot, count);
}

void s04c_at_800D71A4(AtWork *work)
{
    TARGET *target;
    int     hp;

    target = work->target;

    if (target->damaged & 0x4)
    {
        target->damaged &= ~0x4;

        if (work->f728 > -1 && work->f728 < 2)
        {
            s04c_at_800D7134(work, 2, 0);

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

            work->f724 = (hp * 1024) / work->f73C;

            if (hp <= 0)
            {
                work->f728 = 3;
                work->f72C = 0;
                GM_ConfigObjectAction(&work->body, 3, 0, 0);
                GM_SeSet2(0, 47, 129);
            }
            else
            {
                work->f728 = 2;
                work->f72C = 0;
                GM_ConfigObjectAction(&work->body, 2, 0, 0);
                GM_SeSet2(0, 47, 128);
                GM_SeSet2(0, 63, 139);
            }
        }
    }
}

void AtAct_800D7324(AtWork *work)
{
    DG_GetLightMatrix2(&work->control.mov, work->light);
    GM_CurrentMap_800AB9B0 = work->map;
    DG_SetPos(&work->body.objs->world);

    GM_ActObject2(&work->body);

    s04c_at_800D71A4(work);
    work->target->field_28 = 0;

    switch (work->f728)
    {
    case 0:
        if (++work->f72C >= 60)
        {
            work->f72C = 0;

            if (work->f740 != 0)
            {
                GM_SeSet(&work->control.mov, 141);
                work->f728 = 1;
                GM_ConfigObjectAction(&work->body, 1, 0, 0);
            }
        }
        break;

    case 1:
        if (work->body.is_end != 0)
        {
            work->f728 = 0;
            GM_ConfigObjectAction(&work->body, 0, 0, 0);
        }
        break;

    case 2:
        if (++work->f72C >= 20)
        {
            work->f72C = 0;
            work->f728 = 0;
            GM_ConfigObjectAction(&work->body, 0, 0, 0);
        }
        break;

    case 3:
        if (work->body.is_end != 0)
        {
            work->f728 = 4;
            GM_ConfigObjectAction(&work->body, 4, 0, 0);

            if (GM_SnakeCurrentHealth > 0)
            {
                printf("GameOver!\n");
                GCL_ExecProc(work->f70C, 0);
                GM_GameOverTimer = 0;
                GM_GameOver();
            }
        }
        break;

    case 4:
        break;
    }

    if (work->f710 != 0)
    {
        MENU_DrawBar2_80038DE0(40, work->f720, work->f724, work->f738, &work->lifebar);
        work->f720 = GV_NearSpeed(work->f720, work->f724, 4);
    }

    printf("GameOverTimer = %d\n", GM_GameOverTimer);
}

void AtDie_800D7510(AtWork *work)
{
    GM_FreeObject(&work->body);
}

int s04c_at_800D7530(AtWork *work)
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

int AtGetResources_800D75BC(AtWork *work, int name, int map)
{
    CONTROL       *control;
    OBJECT        *body;
    MENU_BAR_CONF *lifebar;

    GM_CurrentMap_800AB9B0 = map;

    work->f728 = 0;

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
    GM_ConfigMotionControl_80034F08(body, &work->m_ctrl, GV_StrCode("shacho"), work->oar1, work->oar2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    DG_SetPos2(&control->mov, &control->rot);
    ReadRotMatrix(&work->body.objs->world);

    if (s04c_at_800D7530(work) < 0)
    {
        return -1;
    }

    if (GCL_GetOption('h'))
    {
        work->f73C = GCL_StrToInt(GCL_GetParamResult());
        work->f738 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f738 = 192;
        work->f73C = 1024;
    }

    lifebar = &work->lifebar;
    lifebar->field_0_text = at_lifebar_name;
    // Set the left and right RGB values for the health bar gradient
    lifebar->field_4_rgb_left[0] = 31;
    lifebar->field_4_rgb_left[1] = 191;
    lifebar->field_4_rgb_left[2] = 95;
    lifebar->field_7_rgb_right[0] = 31;
    lifebar->field_7_rgb_right[1] = 191;
    lifebar->field_7_rgb_right[2] = 95;
    lifebar->field_A_bar_height = 1;

    work->f724 = (work->f738 * 1024) / work->f73C;
    work->f720 = (work->f738 * 1024) / work->f73C;

    if (GCL_GetOption('l'))
    {
        work->f710 = GCL_StrToInt(GCL_GetParamResult());
    }

    work->f730 = 0;
    work->f72C = 0;

    work->target->field_26_hp = work->f738;

    if (GCL_GetOption('u'))
    {
        work->f740 = GCL_StrToInt(GCL_GetParamResult());
    } else
    {
        work->f740 = 1;
    }

    if (GCL_GetOption('e'))
    {
        work->f70C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f70C = -1;
    }

    return 0;
}

GV_ACT *NewAt_800D78A4(int name, int where)
{
    AtWork *work;

    work = (AtWork *)GV_NewActor(EXEC_LEVEL, sizeof(AtWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)AtAct_800D7324, (GV_ACTFUNC)AtDie_800D7510, "at.c");

        if (AtGetResources_800D75BC(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
