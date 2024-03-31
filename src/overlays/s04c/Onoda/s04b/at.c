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
    OAR_RECORD     oar1[16];
    OAR_RECORD     oar2[16];
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

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_GameOverTimer_800AB3D4;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

void s04c_at_800D7134(AtWork *work, int index, int count)
{
    MATRIX rot;

    DG_SetPos_8001BC44(&work->body.objs->objs[index].world);
    DG_MovePos_8001BD20(&at_bloodpos);
    DG_RotatePos_8001BD64(&at_bloodrot);
    ReadRotMatrix(&rot);
    NewBlood_80072728(&rot, count);
}

void s04c_at_800D71A4(AtWork *work)
{
    TARGET *target;
    int     hp;

    target = work->target;

    if (target->field_6_flags & 0x4)
    {
        target->field_6_flags &= ~0x4;

        if (work->f728 > -1 && work->f728 < 2)
        {
            s04c_at_800D7134(work, 2, 0);

            switch (target->field_3E)
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
                GM_ConfigObjectAction_80034CD4(&work->body, 3, 0, 0);
                GM_SeSet2_80032968(0, 47, 129);
            }
            else
            {
                work->f728 = 2;
                work->f72C = 0;
                GM_ConfigObjectAction_80034CD4(&work->body, 2, 0, 0);
                GM_SeSet2_80032968(0, 47, 128);
                GM_SeSet2_80032968(0, 63, 139);
            }
        }
    }
}

void AtAct_800D7324(AtWork *work)
{
    DG_GetLightMatrix2_8001A5D8(&work->control.field_0_mov, work->light);
    GM_CurrentMap_800AB9B0 = work->map;
    DG_SetPos_8001BC44(&work->body.objs->world);

    GM_ActObject2_80034B88(&work->body);

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
                GM_SeSet_80032858(&work->control.field_0_mov, 141);
                work->f728 = 1;
                GM_ConfigObjectAction_80034CD4(&work->body, 1, 0, 0);
            }
        }
        break;

    case 1:
        if (work->body.is_end != 0)
        {
            work->f728 = 0;
            GM_ConfigObjectAction_80034CD4(&work->body, 0, 0, 0);
        }
        break;

    case 2:
        if (++work->f72C >= 20)
        {
            work->f72C = 0;
            work->f728 = 0;
            GM_ConfigObjectAction_80034CD4(&work->body, 0, 0, 0);
        }
        break;

    case 3:
        if (work->body.is_end != 0)
        {
            work->f728 = 4;
            GM_ConfigObjectAction_80034CD4(&work->body, 4, 0, 0);

            if (GM_SnakeCurrentHealth > 0)
            {
                printf("GameOver!\n");
                GCL_ExecProc_8001FF2C(work->f70C, 0);
                GM_GameOverTimer_800AB3D4 = 0;
                GM_GameOver_8002B6C8();
            }
        }
        break;

    case 4:
        break;
    }

    if (work->f710 != 0)
    {
        menu_DrawBar2_80038DE0(40, work->f720, work->f724, work->f738, &work->lifebar);
        work->f720 = sub_8002646C(work->f720, work->f724, 4);
    }

    printf("GameOverTimer = %d\n", GM_GameOverTimer_800AB3D4);
}

void AtDie_800D7510(AtWork *work)
{
    GM_FreeObject_80034BF8(&work->body);
}

int s04c_at_800D7530(AtWork *work)
{
    TARGET *target;

    target = GM_AllocTarget_8002D400();
    work->target = target;

    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget_8002DC74(target, TARGET_SEEK | TARGET_POWER, ENEMY_SIDE, &at_target_size);
    GM_Target_8002DCCC(target, 1, -1, 128, 0, &DG_ZeroVector_800AB39C);
    GM_Target_SetVector_8002D500(target, &work->control.field_0_mov);
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
    if (GM_InitLoader_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    work->map = map;

    GM_ConfigControlString_800261C0(control, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(control, control->field_0_mov.vy, -2, -2);

    body = &work->body;
    GM_InitObject_80034A18(body, GV_StrCode_80016CCC("ats_noc"), BODY_FLAG, GV_StrCode_80016CCC("shacho"));
    GM_ConfigObjectJoint_80034CB4(body);
    GM_ConfigMotionControl_80034F08(body, &work->m_ctrl, GV_StrCode_80016CCC("shacho"), work->oar1, work->oar2, control, work->rots);
    GM_ConfigObjectLight_80034C44(body, work->light);
    GM_ConfigObjectAction_80034CD4(body, 0, 0, 0);

    DG_SetPos2_8001BC8C(&control->field_0_mov, &control->field_8_rot);
    ReadRotMatrix(&work->body.objs->world);

    if (s04c_at_800D7530(work) < 0)
    {
        return -1;
    }

    if (GCL_GetOption_80020968('h'))
    {
        work->f73C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f738 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f738 = 192;
        work->f73C = 1024;
    }

    lifebar = &work->lifebar;
    lifebar->field_0_text = at_lifebar_name;
    lifebar->field_4_rgb_left[0] = 31;
    lifebar->field_4_rgb_left[1] = 191;
    lifebar->field_4_rgb_left[2] = 95;
    lifebar->field_7_rgb_right[0] = 31;
    lifebar->field_7_rgb_right[1] = 191;
    lifebar->field_7_rgb_right[2] = 95;
    lifebar->field_A_bar_height = 1;

    work->f724 = (work->f738 * 1024) / work->f73C;
    work->f720 = (work->f738 * 1024) / work->f73C;

    if (GCL_GetOption_80020968('l'))
    {
        work->f710 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f730 = 0;
    work->f72C = 0;

    work->target->field_26_hp = work->f738;

    if (GCL_GetOption_80020968('u'))
    {
        work->f740 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    } else
    {
        work->f740 = 1;
    }

    if (GCL_GetOption_80020968('e'))
    {
        work->f70C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f70C = -1;
    }

    return 0;
}

GV_ACT * NewAt_800D78A4(int name, int where)
{
    AtWork *work;

    work = (AtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(AtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)AtAct_800D7324, (TActorFunction)AtDie_800D7510, "at.c");

        if (AtGetResources_800D75BC(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
