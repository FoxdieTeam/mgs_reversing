#include "tracktrp.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "takabe/thing.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

#define DEFAULT_TIME 90

typedef struct _Work
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
} Work;

static unsigned short mes_list[] = {
    HASH_ENTER,     // GV_StrCode("入る")
    HASH_LEAVE      // GV_StrCode("出る")
};

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int found;
    int proc;

    found = THING_Msg_CheckMessage(work->name, 2, mes_list);
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
        if (GV_PadData[0].status & 0xF013)
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
            case IT_Box1:
                proc = work->proc[0];
                break;

            case IT_Box2:
                proc = work->proc[1];
                break;

            case IT_Box3:
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
            work->item = IT_None;
        }

        work->count = 0;
        work->pos = GM_PlayerPosition;
    }
}

static void Die(Work *work)
{
}

static int GetResources(Work *work, int name, int map)
{
    work->time = THING_Gcl_GetIntDefault('t', DEFAULT_TIME);

    if (GCL_GetOption('e'))
    {
        work->proc[0] = GCL_StrToInt(GCL_GetParamResult());
        work->proc[1] = GCL_StrToInt(GCL_GetParamResult());
        work->proc[2] = GCL_StrToInt(GCL_GetParamResult());
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewTruckTrap(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "tracktrp.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return (void *)work;
}
