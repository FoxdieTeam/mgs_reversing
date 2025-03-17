#include "intr_cam.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "strcode.h"

extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT  actor;
    int     name;
    int     state;
    int     interp;
    SVECTOR pos;
    SVECTOR eye;
} Work;

#define EXEC_LEVEL GV_ACTOR_AFTER2

/*---------------------------------------------------------------------------*/

static void CheckMessage(Work *work)
{
    GV_MSG *msgs;
    int     count;

    count = GV_ReceiveMessage(work->name, &msgs);
    if (count <= 0)
    {
        return;
    }

    while (--count >= 0)
    {
        switch (msgs->message[0])
        {
        case HASH_KILL:
            work->state = 3;
            break;

        case HASH_ON:
            work->state = 1;
            work->eye = gUnkCameraStruct_800B77B8.eye;
            break;

        case HASH_OFF:
            work->state = 2;
            break;
        }
        msgs++;
    }
}

static void Act(Work *work)
{
    int interp;

    CheckMessage(work);
    if (!(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        work->interp = 8;
        return;
    }

    if (work->state >= 2)
    {
        if (work->state == 3)
        {
            GV_DestroyActor(&work->actor);
        }
        work->interp = 8;
        return;
    }

    interp = work->interp;
    if (work->interp > 0)
    {
        work->interp--;
    }
    GV_NearTimeV(&work->eye.vx, &work->pos.vx, interp, 3);
    gUnkCameraStruct_800B77B8.eye = work->eye;
}

static void Die(Work *work)
{
}

static int GetResources(Work *work)
{
    GCL_GetOption('p');
    GCL_StrToSV(GCL_GetParamResult(), &work->pos);
    work->state = 2;
    work->interp = 8;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewIntrudeCamera(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "intr_cam.c");
        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->name = name;
    }
    return (void *)work;
}
