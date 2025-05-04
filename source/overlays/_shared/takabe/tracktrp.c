#include "tracktrp.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "linkvar.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _TracktrpWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    int     time;
    int     enter;
    int     count;
    SVECTOR pos;
    int     item;
    int     proc[4];
} TracktrpWork;

extern GV_PAD  GV_PadData_800B05C0[4];

unsigned short tracktrp_hashes[] = {HASH_ENTER, HASH_LEAVE};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void TracktrpAct_800E1A94(TracktrpWork *work)
{
    int found;
    int proc;

    found = THING_Msg_CheckMessage(work->name, 2, tracktrp_hashes);
    switch (found)
    {
    case 0:
        work->enter = 1;
        work->item = IT_None;
        work->count = 0;
        work->pos = GM_PlayerPosition;
        break;

    case 1:
        work->enter = 0;
        break;
    }

    if (work->enter == 0)
    {
        return;
    }

    if (GM_CurrentItemId == work->item && GM_CurrentItemId != IT_None)
    {
        if (GV_PadData_800B05C0[0].status & 0xF013)
        {
            work->count = 0;
            work->pos = GM_PlayerPosition;
        }

        if ((GM_PlayerPosition.vx != work->pos.vx) ||
            (GM_PlayerPosition.vy != work->pos.vy) ||
            (GM_PlayerPosition.vz != work->pos.vz))
        {
            work->count = 0;
            work->pos = GM_PlayerPosition;
        }

        if (GM_AlertMode != 0)
        {
            work->count = 0;
        }

        if (GM_GameStatus & STATE_PADRELEASE)
        {
            work->count = 0;
        }

        if (work->count > work->time)
        {
            proc = 0;

            switch (work->item)
            {
            case 2:
                proc = work->proc[0];
                break;

            case 3:
                proc = work->proc[1];
                break;

            case 4:
                proc = work->proc[2];
                break;
            }

            if (proc != 0)
            {
                GCL_ExecProc(proc, NULL);
            }
            else
            {
                work->count = 0;
            }
        }

        work->count++;
    }
    else
    {
        if (GM_CurrentItemId == IT_Box1 ||
            GM_CurrentItemId == IT_Box2 ||
            GM_CurrentItemId == IT_Box3)
        {
            work->item = GM_CurrentItemId;
        }
        else
        {
            work->item = -1;
        }

        work->count = 0;
        work->pos = GM_PlayerPosition;
    }
}

void TracktrpDie_800E1D30(TracktrpWork *work)
{
}

int TracktrpGetResources_800E1D38(TracktrpWork *work, int name, int map)
{
    work->time = THING_Gcl_GetIntDefault('t', 90);

    if (GCL_GetOption('e'))
    {
        work->proc[0] = GCL_StrToInt(GCL_GetParamResult());
        work->proc[1] = GCL_StrToInt(GCL_GetParamResult());
        work->proc[2] = GCL_StrToInt(GCL_GetParamResult());
    }

    return 0;
}

void *NewTracktrp_800E1DB0(int name, int where, int argc, char **argv)
{
    TracktrpWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(TracktrpWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, TracktrpAct_800E1A94, TracktrpDie_800E1D30, "tracktrp.c");

        if (TracktrpGetResources_800E1D38(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return (void *)work;
}
