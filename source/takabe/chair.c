#include "game/game.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    TARGET *target;
    int     hit;
    int     unused;
    int     midair;
    int     broken;
    int     flag;
    SVECTOR bounds[8];
    int     proc_id;
} Work;

#define EXEC_LEVEL  5

#define BODY_MODEL  GV_StrCode("isu")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

static void ExecProc(int proc_id, SVECTOR *rot)
{
    GCL_ARGS args;
    long     data[4];

    if (proc_id != 0)
    {
        args.argc = 3;
        args.argv = data;
        data[0] = rot->vy;
        data[1] = rot->vz;
        GCL_ExecProc(proc_id, &args);
    }
}

static int GetHeight(Work *work)
{
    SVECTOR *bounds;
    int      height;
    int      i;

    bounds = (SVECTOR *)SCRPAD_ADDR;
    DG_RotVector(work->bounds, bounds, 8);

    height = 0;
    for (i = 8; i > 0; i--)
    {
        height = MIN(bounds->vy, height);
        bounds++;
    }

    return -height;
}

static void Act(Work *work)
{
    SVECTOR  rot;
    CONTROL *control;
    TARGET  *target;

    control = &work->control;
    target = work->target;

    work->midair = FALSE;

    if ((target->damaged & TARGET_POWER) && !work->hit)
    {
        work->hit = TRUE;

        if (control->turn.vz == 0)
        {
            control->turn.vy += GV_RandS(256);

            rot.vx = 0;
            rot.vy = control->turn.vy;

            if (GV_RandU(2) != 0)
            {
                control->turn.vz = GV_RandS(128) + 724;
                rot.vz = 1024;
            }
            else
            {
                control->turn.vz = GV_RandS(128) + 3372;
                rot.vz = 3072;
            }
        }
        else
        {
            control->turn.vy += GV_RandS(128);

            rot.vx = 0;
            rot.vy = control->turn.vy;

            if (control->turn.vz < 2048)
            {
                control->turn.vz = GV_RandS(256) + 1024;
                rot.vz = 1024;
            }
            else
            {
                control->turn.vz = GV_RandS(256) + 3072;
                rot.vz = 3072;
            }
        }

        if (work->proc_id != 0)
        {
            ExecProc(work->proc_id, &rot);
        }

        control->step.vy = 128;
    }

    if (work->hit)
    {
        if (control->level_flag != 0)
        {
            control->level_flag = 0;
            control->step.vy = -control->step.vy / 2;

            GM_SeSet(&control->mov, SE_UNK061);

            if (control->step.vy < 32)
            {
                work->hit = FALSE;
                control->step.vy = 0;

                if (control->turn.vz < 2048)
                {
                    control->turn.vz = 1024;
                }
                else
                {
                    control->turn.vz = 3072;
                }
            }
            else
            {
                if (control->turn.vz < 2048)
                {
                    control->turn.vz = (1024 - control->turn.vz) / 2 + 1024;
                }
                else
                {
                    control->turn.vz = (3072 - control->turn.vz) / 2 + 3072;
                }
            }
        }
        else
        {
            control->step.vy -= 16;
            work->midair |= TRUE;
        }

        control->step.vx -= control->step.vx / 4;
        control->step.vz -= control->step.vz / 4;
    }

    if (!work->midair)
    {
        GM_ConfigControlHazard(control, -1, 0, -1);
    }
    else
    {
        GM_ConfigControlHazard(control, 100, 500, 500);

        DG_SetPos(&work->body.objs->world);
        control->height = GetHeight(work);
    }

    GM_ActControl(control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix(&work->control.mov, work->light);

    target->damaged &= ~( TARGET_POWER | TARGET_PUSH );
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

    size.vx = 500;
    size.vy = 500;
    size.vz = 500;
    scale = DG_ZeroVector;

    work->target = target = GM_AllocTarget();

    if (work->flag & 0x1)
    {
        GM_SetTarget(target, ( TARGET_POWER | TARGET_PUSH ), NO_SIDE, &size);
    }
    else
    {
        GM_SetTarget(target, TARGET_POWER, NO_SIDE, &size);
    }

    GM_Target_8002DCCC(target, 1, -1, 0, 60, &scale);
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    DG_DEF  *def;
    int      i;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, 100, 500, 500);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    work->control.step = DG_ZeroVector;

    work->broken = THING_Gcl_GetInt('b');
    work->proc_id = THING_Gcl_GetInt('e');
    work->flag = THING_Gcl_GetInt('f');

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectStep(body, &work->control.step);

    def = work->body.objs->def;
    for (i = 0; i < 8; i++)
    {
        if (i & 1)
        {
            work->bounds[i].vx = def->max.vx;
        }
        else
        {
            work->bounds[i].vx = def->min.vx;
        }

        if (i & 2)
        {
            work->bounds[i].vy = def->max.vy;
        }
        else
        {
            work->bounds[i].vy = def->min.vy;
        }

        if (i & 4)
        {
            work->bounds[i].vz = def->max.vz;
        }
        else
        {
            work->bounds[i].vz = def->min.vz;
        }
    }

    DG_SetPos2(&control->mov, &control->rot);
    control->height = GetHeight(work);
    control->step.vy = -1000;

    GM_ActControl(control);

    InitTarget(work);
    return 0;
}

void *NewChair(int arg0, int arg1)
{
    Work* work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "chair.c");

        if (GetResources(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->unused = -1;
        work->hit = FALSE;
        work->midair = FALSE;
    }

    return work;
}
