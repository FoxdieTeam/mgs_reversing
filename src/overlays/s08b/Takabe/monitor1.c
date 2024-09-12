#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Takabe/thing.h"
#include "SD/g_sound.h"

typedef struct Monitor1Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  object;
    MATRIX  light[2];
    TARGET *target;
    int     flag;
    int     bound;
    int     flag2;
    int     vy;
    int     proc;
} Monitor1Work;

#define EXEC_LEVEL 5

extern SVECTOR DG_ZeroVector;
extern MATRIX  DG_ZeroMatrix;

GV_ACT *NewSpark2_800CA714(MATRIX *world);
void    AN_Unknown_800DCE84(SVECTOR *pos);

void Monitor1Act_800DC8BC(Monitor1Work *work)
{
    MATRIX   world;
    SVECTOR  svec1;
    SVECTOR  pos;
    CONTROL *control;
    MATRIX  *light;
    OBJECT  *object;
    TARGET  *target;
    int      flag;

    flag = 0;

    control = &work->control;
    light = work->light;
    world = DG_ZeroMatrix;
    target = work->target;

    work->flag2 = 0;
    DG_GetLightMatrix(&control->mov, light);

    if ((target->damaged & TARGET_POWER) && target->field_26_hp != 255 && work->bound == 0)
    {
        work->flag = 1;
        work->bound = 1;

        target->field_26_hp = 255;
        target->damaged &= ~TARGET_POWER;

        GM_SeSet(&control->mov, SE_ELECTRIC_PANEL);

        object = &work->object;
        GM_FreeObject(object);
        GM_InitObject(object, GV_StrCode("nanao_d"), 0x1D, 0);
        GM_ConfigObjectJoint(object);
        GM_ConfigObjectLight(object, light);
        GM_ConfigObjectStep(object, &work->control.step);

        control->rot.vz = -GV_RandU(128) - 128;
        control->step.vy = 32;

        svec1.vy = control->rot.vy - 1024;
        svec1.vz = 0;
        svec1.vx = control->rot.vz;

        world.t[0] = control->mov.vx;
        world.t[1] = control->mov.vy;
        world.t[2] = control->mov.vz;

        RotMatrixYXZ(&svec1, &world);

        flag = 1;

        if (work->proc)
        {
            GCL_ExecProc(work->proc, NULL);
        }
    }

    if (work->flag)
    {
        if (control->mov.vy < work->vy)
        {
            control->step.vy = -control->step.vy / 4;
            control->mov.vy = work->vy;
            if (control->step.vy < 16)
            {
                work->flag = 0;
                control->step.vy = 0;
                control->mov.vy = work->vy;
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
    GM_ActObject2(&work->object);

    if (flag)
    {
        NewSpark2_800CA714(&world);
        svec1.vx = 0;
        svec1.vy = 0;
        svec1.vz = 0x15E;
        DG_SetPos(&world);
        DG_PutVector(&svec1, &pos, 1);
        AN_Unknown_800DCE84(&pos);
    }

    GM_MoveTarget(target, &work->control.mov);
    GM_PushTarget(target);
}

void Monitor1Die_800DCBB0(Monitor1Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
    GM_FreeTarget(work->target);
}

void Monitor1InitTarget_800DCBEC(Monitor1Work *work)
{
    SVECTOR svec1;
    SVECTOR svec2;
    TARGET *target;

    svec1.vx = 300;
    svec1.vy = 400;
    svec1.vz = 300;

    svec2 = DG_ZeroVector;

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, NO_SIDE, &svec1);
    GM_Target_8002DCCC(target, 1, -1, 0xFF, 0, &svec2);
}

int Monitor1GetResources_800DCC90(Monitor1Work *work, int arg1, int arg2)
{
    OBJECT  *object;
    CONTROL *control;

    control = &work->control;
    if (GM_InitControl(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    work->control.step = DG_ZeroVector;
    work->proc = THING_Gcl_GetInt('e');
    work->bound = THING_Gcl_GetInt('b');

    control->rot.vy += 1024;
    control->turn.vy += 1024;

    object = &work->object;
    if (work->bound == 0)
    {
        GM_InitObject(object, GV_StrCode("nanao"), 0x1D, 0);
    }
    else
    {
        GM_InitObject(object, GV_StrCode("nanao_d"), 0x1D, 0);
    }

    GM_ConfigObjectJoint(object);
    GM_ConfigObjectLight(object, work->light);
    GM_ConfigObjectStep(object, &work->control.step);

    Monitor1InitTarget_800DCBEC(work);

    return 0;
}

GV_ACT *NewMonitor1_800DCDE0(int arg0, int arg1)
{
    Monitor1Work *work;

    work = (Monitor1Work *)GV_NewActor(EXEC_LEVEL, sizeof(Monitor1Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)Monitor1Act_800DC8BC,
                         (TActorFunction)Monitor1Die_800DCBB0, "monitor1.c");
        if (Monitor1GetResources_800DCC90(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->flag = 0;
        work->flag2 = 0;
        work->vy = work->control.mov.vy;
    }
    return &work->actor;
}
