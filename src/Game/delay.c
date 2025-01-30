#include "delay.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/jimctrl.h"

typedef union GCL_EXEC_UNION {
    int            proc_id;
    unsigned char *block_top;
} GCL_EXEC_UNION;

typedef struct DelayWork
{
    GV_ACT         actor;
    GCL_EXEC_UNION gcl_exec;
    GCL_ARGS       args;
    int            delay_counter;
    int            active;
    long           argv_buf[8];
} DelayWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

//not sure if this one belongs here
void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec)
{
    int found;

    found = jimctrl_helper_80037F68(id) & 0xFF;
    if (found == 1)
    {
        vec->vx += 32;

        if (vec->vx >= 128)
        {
            vec->vx = 128;

            if (vec->vz == 0)
            {
                vec->vz = GV_RandS(32);
            }
        }
    }
    else if (found == 2)
    {
        if (vec->vx < 64)
        {
            vec->vx += 16;

            if (vec->vx >= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS(16);
                }
            }
        }
        else
        {
            vec->vx -= 16;

            if (vec->vx <= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS(16);
                }
            }
        }
    }
    else if (vec->vx > 0)
    {
        vec->vx -= 8;
    }

    if (vec->vz != 0)
    {
        if (vec->vz > 0)
        {
            vec->vz -= 8;

            if (vec->vz < 0)
            {
                vec->vz = 0;
            }
        }
        else
        {
            vec->vz += 8;

            if (vec->vz > 0)
            {
                vec->vz = 0;
            }
        }
    }
}

STATIC void delay_Act(DelayWork *work)
{
    if (work->active == FALSE && GM_GameOverTimer != 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    work->delay_counter--;
    if (work->delay_counter > 0)
    {
        return;
    }

    if (work->gcl_exec.proc_id < 0)
    {
        GCL_ExecBlock(work->gcl_exec.block_top, &work->args);
    }
    else
    {
        GCL_ExecProc(work->gcl_exec.proc_id, &work->args);
    }

    GV_DestroyActor(&work->actor);
}

GV_ACT *GM_DelayedExecCommand(int proc, GCL_ARGS *args, int time)
{
    unsigned short argc;
    DelayWork     *work;
    int            i;
    long          *dst_args;
    long          *src_args;

    work = (DelayWork *)GV_NewActor(EXEC_LEVEL, sizeof(DelayWork));
    if (work)
    {
        if (!args)
        {
            work->args.argc = 0;
        }
        else
        {
            src_args = args->argv;

            work->args.argv = work->argv_buf;
            dst_args = work->args.argv;

            argc = args->argc;
            work->args.argc = argc;
            for (i = argc; i > 0; i--)
            {
                *dst_args = *src_args;
                src_args++;
                dst_args++;
            }
        }

        if (time < 0)
        {
            work->active = TRUE;
            time = -time;
        }
        else
        {
            work->active = FALSE;
        }

        work->delay_counter = time;
        work->gcl_exec.proc_id = proc;

        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)delay_Act, NULL, "delay.c");
    }
    return &work->actor;
}
