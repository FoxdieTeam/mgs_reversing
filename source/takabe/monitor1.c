#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "sound/g_sound.h"

#include "takabe/spark2.h"      // for NewSpark2_800CA714

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    TARGET *target;
    int     flag;
    int     broken;
    int     flag2;
    int     height;
    int     proc_id;
} Work;

#define EXEC_LEVEL  GV_ACTOR_LEVEL5

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND )

void AN_PanelSmoke(SVECTOR *pos);

static void Act(Work *work)
{
    MATRIX   world;
    SVECTOR  vec;
    SVECTOR  pos;
    CONTROL *control;
    MATRIX  *light;
    OBJECT  *body;
    TARGET  *target;
    int      flag;

    flag = 0;

    control = &work->control;
    light = work->light;
    world = DG_ZeroMatrix;
    target = work->target;

    work->flag2 = 0;
    DG_GetLightMatrix(&control->mov, light);

    if ((target->damaged & TARGET_POWER) && target->life != 255 && work->broken == 0)
    {
        work->flag = 1;
        work->broken = 1;

        target->life = 255;
        target->damaged &= ~TARGET_POWER;

        GM_SeSet(&control->mov, SE_ELECTRIC_PANEL);

        body = &work->body;
        GM_FreeObject(body);
        GM_InitObject(body, GV_StrCode("nanao_d"), BODY_FLAG, 0);
        GM_ConfigObjectJoint(body);
        GM_ConfigObjectLight(body, light);
        GM_ConfigObjectStep(body, &work->control.step);

        control->rot.vz = -GV_RandU(128) - 128;
        control->step.vy = 32;

        vec.vy = control->rot.vy - 1024;
        vec.vz = 0;
        vec.vx = control->rot.vz;

        world.t[0] = control->mov.vx;
        world.t[1] = control->mov.vy;
        world.t[2] = control->mov.vz;

        RotMatrixYXZ(&vec, &world);

        flag = 1;

        if (work->proc_id)
        {
            GCL_ExecProc(work->proc_id, NULL);
        }
    }

    if (work->flag)
    {
        if (control->mov.vy < work->height)
        {
            control->step.vy = -control->step.vy / 4;
            control->mov.vy = work->height;
            if (control->step.vy < 16)
            {
                work->flag = 0;
                control->step.vy = 0;
                control->mov.vy = work->height;
                control->rot.vx = 0;
            }
        }
        else
        {
            control->step.vy -= 16;
            work->flag2 |= 1;
        }
    }

    if (work->flag2 == 0)
    {
        GM_ConfigControlHazard(control, -1, 0, -1);
    }
    else
    {
        GM_ConfigControlHazard(control, -1, -2, -1);
    }

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    if (flag)
    {
        NewSpark2_800CA714(&world);
        vec.vx = 0;
        vec.vy = 0;
        vec.vz = 350;
        DG_SetPos(&world);
        DG_PutVector(&vec, &pos, 1);
        AN_PanelSmoke(&pos);
    }

    GM_MoveTarget(target, &work->control.mov);
    GM_PushTarget(target);
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    SVECTOR size;
    SVECTOR scale;
    TARGET *target;

    size.vx = 300;
    size.vy = 400;
    size.vz = 300;

    scale = DG_ZeroVector;

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, NO_SIDE, &size);
    GM_Target_8002DCCC(target, 1, -1, 255, 0, &scale);
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    work->control.step = DG_ZeroVector;
    work->proc_id = THING_Gcl_GetInt('e');
    work->broken = THING_Gcl_GetInt('b');

    control->rot.vy += 1024;
    control->turn.vy += 1024;

    body = &work->body;
    if (work->broken == 0)
    {
        GM_InitObject(body, GV_StrCode("nanao"), BODY_FLAG, 0);
    }
    else
    {
        GM_InitObject(body, GV_StrCode("nanao_d"), BODY_FLAG, 0);
    }

    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectStep(body, &work->control.step);

    InitTarget(work);

    return 0;
}

void *NewMonitor1(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "monitor1.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->flag = 0;
        work->flag2 = 0;
        work->height = work->control.mov.vy;
    }
    return (void *)work;
}
