#include "common.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/object.h"
#include "Takabe/thing.h"
#include "Bullet/bakudan.h"

typedef struct _LiftWork
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    HZD_FLR floor;
    TARGET *target;
    SVECTOR size;
    int     f1FC;
    int     f200;
    int     f204;
    int     f208;
    short   f20C;
    short   f20E;
    int     f210;
    int     f214;
    int     f218;
} LiftWork;

extern int      bakudan_count_8009F42C;
extern int      counter_8009F448;
extern HITTABLE c4_actors_800BDD78[C4_COUNT];
extern HITTABLE stru_800BDE78[8];

#define TAG(ptr, tag) ((void *)((unsigned int)ptr | tag))

#define EXEC_LEVEL 5

void s13a_lift_800DDA90(LiftWork *work)
{
    work->floor.p1.y = work->floor.p2.y = work->floor.p3.y = work->floor.p4.y = work->control.mov.vy + work->size.vy + 1;
}

void s13a_lift_800DDAB8(LiftWork *work)
{
    work->floor.p1.x = work->control.mov.vx - work->size.vx;
    work->floor.p1.z = work->control.mov.vz - work->size.vz;
    work->floor.p2.x = work->control.mov.vx + work->size.vx;
    work->floor.p2.z = work->control.mov.vz - work->size.vz;
    work->floor.p4.x = work->control.mov.vx - work->size.vx;
    work->floor.p4.z = work->control.mov.vz + work->size.vz;
    work->floor.p3.x = work->control.mov.vx + work->size.vx;
    work->floor.p3.z = work->control.mov.vz + work->size.vz;

    s13a_lift_800DDA90(work);

    work->floor.p1.h = 0;
    work->floor.p2.h = 0;
    work->floor.p3.h = 255;

    work->floor.b1.x = work->control.mov.vx - work->size.vx;
    work->floor.b1.z = work->control.mov.vz - work->size.vz;
    work->floor.b1.y = work->control.mov.vy - work->size.vy;
    work->floor.b2.x = work->control.mov.vx + work->size.vx;
    work->floor.b2.z = work->control.mov.vz + work->size.vz;
    work->floor.b2.y = work->control.mov.vy + work->size.vy;

    work->floor.b1.h |= 0xC000;
}

void s13a_lift_800DDBC4(int proc, int param)
{
    GCL_ARGS args;
    long     data;

    data = param;

    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &data;
        GCL_ExecProc(proc, &args);
    }
}


void LiftAct_800DDBFC(LiftWork *work)
{
    unsigned short messages[2];
    CONTROL       *control;
    TARGET        *target;
    int            i;
    HZD_FLR       *floor;
    unsigned int   tag, tag2;
    HITTABLE      *iter;


    control = &work->control;
    DG_GetLightMatrix(&control->mov, work->light);

    target = work->target;

    messages[0] = 0xACDC;
    messages[1] = 0x85B;

    switch (work->f1FC)
    {
    case 0:
        if (work->f20C > 0)
        {
            if (--work->f20C == 0)
            {
                s16b_800C4594(work->f214, 0x418B);
            }
        }
        else if (THING_Msg_CheckMessage(control->name, 2, messages) == 0)
        {
            work->f1FC = 1;
            s16b_800C4594(work->f214, 0x3A02);
            work->f20C = 15;
            work->f20E = 30;
        }
        break;

    case 1:
        if (work->f20E > 0)
        {
            if (--work->f20E == 0)
            {
                s13a_lift_800DDBC4(work->f218, 0x361E);
                control->step.vy = work->f208;
            }
        }
        else if (control->mov.vy >= work->f200)
        {
            work->f1FC = 2;
            control->mov.vy = work->f200;
            control->step.vy = 0;
            s13a_lift_800DDBC4(work->f218, 0xADBF);
        }
        break;

    case 2:
        if (work->f20C > 0)
        {
            if (--work->f20C == 0)
            {
                s16b_800C4594(work->f210, 0x418B);
            }
        }
        else if (THING_Msg_CheckMessage(control->name, 2, messages) == 1)
        {
            work->f1FC = 3;
            s16b_800C4594(work->f210, 0x3A02);
            work->f20C = 15;
            work->f20E = 30;
        }
        break;

    case 3:
        if (work->f20E > 0)
        {
            if (--work->f20E == 0)
            {
                s13a_lift_800DDBC4(work->f218, 0xF624);
                control->step.vy = -work->f208;
            }
        }
        else if (work->f204 >= control->mov.vy)
        {
            work->f1FC = 0;
            control->mov.vy = work->f204;
            control->step.vy = 0;
            s13a_lift_800DDBC4(work->f218, 0xEDB8);
        }
        break;
    }

    GV_AddVec3(&control->mov, &control->step, &control->mov);

    s13a_lift_800DDA90(work);

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    if (bakudan_count_8009F42C != 0)
    {
        i = C4_COUNT;
        floor = &work->floor;
        tag = 0x80000000;
        iter = c4_actors_800BDD78;
        for (; i > 0; iter++, i--)
        {
            if (iter->actor && floor == TAG(iter->data, tag))
            {
                GV_AddVec3(&iter->control->mov, &control->step, &iter->control->mov);
            }
        }
    }

    if (counter_8009F448 != 0)
    {
        i = 8;
        floor = &work->floor;
        tag2 = 0x80000000;
        iter = stru_800BDE78;
        for (; i > 0; iter++, i--)
        {
            if (iter->actor && floor == TAG(iter->data, tag2))
            {
                GV_AddVec3(&iter->control->mov, &control->step, &iter->control->mov);
            }
        }
    }

    target->center.vy = (control->mov.vy + work->f204) / 2 - 500;
    target->size.vy = (control->mov.vy - work->f204) / 2;
}

void LiftDie_800DDF88(LiftWork *work)
{
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->floor);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

void s13a_lift_800DDFD8(LiftWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    GM_SetTarget(target, 1, 0, &work->size);
    GM_MoveTarget(target, &work->control.mov);

    target->center.vy = (work->control.mov.vy + work->f204) / 2 - 200;
    target->size.vy = (work->control.mov.vy - work->f204) / 2;
}

int LiftGetResources_800DE070(LiftWork *work, int name, int map)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, 0, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    control->step = DG_ZeroVector;
    work->f204 = control->mov.vy;

    body = &work->body;

    GM_InitObject(body, THING_Gcl_GetShort('m'), 29, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectStep(body, &control->step);

    work->f208 = THING_Gcl_GetIntDefault('v', 30);
    work->f200 = THING_Gcl_GetIntDefault('h', 6000) + control->mov.vy;
    THING_Gcl_GetSVectorDefault('s', 875, 100, 750, &work->size);
    work->f210 = THING_Gcl_GetShort('o');
    work->f214 = THING_Gcl_GetShort('u');
    work->f218 = THING_Gcl_GetInt('e');

    if (!THING_Gcl_GetInt('i'))
    {
        work->f1FC = 3;
        work->control.step.vy = -work->f208;
    }
    else
    {
        work->f1FC = 1;
        work->control.step.vy = work->f208;
        control->mov.vy = work->f200;
    }

    s13a_lift_800DDFD8(work);
    s13a_lift_800DDAB8(work);

    HZD_QueueDynamicFloor(control->map->hzd, &work->floor);

    work->f20C = 15;
    work->f20E = 30;
    return 0;
}

GV_ACT *NewLift_800DE25C(int name, int where)
{
    LiftWork *work;

    work = (LiftWork *)GV_NewActor(EXEC_LEVEL, sizeof(LiftWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)LiftAct_800DDBFC, (GV_ACTFUNC)LiftDie_800DDF88, "lift.c");

        if (LiftGetResources_800DE070(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
