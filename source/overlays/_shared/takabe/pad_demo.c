#include "pad_demo.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

extern void MENU_ResetItemPos(void);
extern void MENU_ResetWeaponPos(void);

/*---------------------------------------------------------------------------*/

typedef struct _PadDemoWork
{
    GV_ACT          actor;
    int             map;
    int             name;
    int             f28;
    int             f2C;
    char            f30[0x4];
    int             f34;
    unsigned short *f38;
    unsigned short  f3C;
    char            f3E[0x2];
    int             proc;
    int             f44;
} PadDemoWork;

#define EXEC_LEVEL GV_ACTOR_MANAGER

/*---------------------------------------------------------------------------*/

static void PadDemo_800DCBB0(PadDemoWork *work)
{
    if (GM_StreamStatus() == -1)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void PadDemo_800DCBE8(PadDemoWork *work)
{
    unsigned short status;

    if (GV_PauseLevel & 8)
    {
        return;
    }

    if (DG_UnDrawFrameCount == 1 && GM_GetMap(work->map)->used == 1)
    {
        work->f28 |= 0x1;

        GM_GameStatus |= STATE_PADDEMO;
        if (work->f34 != 0)
        {
            GM_GameStatus |= STATE_NOSLOW;
        }
    }

    if (work->f28 == 0)
    {
        return;
    }

    if (work->f44 != FALSE && mts_read_pad(1) & PAD_CROSS)
    {
        work->f44 = TRUE;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
            GM_GameStatus &= ~(STATE_PADDEMO | STATE_NOSLOW);
            GV_DemoPadStatus[0] = 0;
            work->actor.act = (GV_ACTFUNC)PadDemo_800DCBB0;
        }
        else
        {
            GV_DestroyActor(&work->actor);
        }
    }

    status = work->f3C & ~0x200;
    GV_DemoPadStatus[0] = status & ~0xA00;

    if (--work->f2C == 0)
    {
        work->f3C = *work->f38++;
        if (work->f3C & 0x200)
        {
            work->f2C = *work->f38++;
        }
        else
        {
            work->f2C = 1;
        }
    }

    if (status & 0x800)
    {
        work->f44 = FALSE;
        GM_GameStatus &= ~(STATE_PADDEMO | STATE_NOSLOW | STATE_PADRELEASE | GAME_FLAG_BIT_13);
        GV_DestroyActor(&work->actor);
    }
}

/*---------------------------------------------------------------------------*/

static void Act(PadDemoWork *work)
{
    if (GM_StreamStatus() == 0)
    {
        GV_PauseLevel |= 4;
        GM_GameStatus |= STATE_PADRELEASE;
        DG_UnDrawFrameCount = 3;
    }
    else
    {
        printf("Pad rec start\n");
        work->actor.act = (GV_ACTFUNC)PadDemo_800DCBE8;
        GM_GameStatus |= (STATE_PADRELEASE | GAME_FLAG_BIT_13);
        DG_UnDrawFrameCount = 4;
        GV_PauseLevel &= ~4;
        PadDemo_800DCBE8(work);
    }
}

static void Die(PadDemoWork *work)
{
    GCL_ARGS args;
    long     data;

    if (work->proc > 0)
    {
        args.argc = 1;
        args.argv = &data;

        data = work->f44;

        GCL_ExecProc(work->proc, &args);
    }
}

static int GetResources(PadDemoWork *work, int name, int map)
{
    int filename;

    GM_CurrentMap = map;

    work->map = map;
    work->name = name;

    work->f3C = 0;

    GV_DemoPadStatus[0] = 0;
    GV_DemoPadStatus[1] = 0;

    GM_GameStatus |= STATE_PADRELEASE;

    if (GCL_GetOption('d'))
    {
        // s0102a1.con
        filename = GCL_StrToInt(GCL_GetParamResult());
        work->f38 = GV_GetCache(GV_CacheID(filename, 'c')) + 4;
    }

    work->f3C = *work->f38++;
    if (work->f3C & 0x200)
    {
        work->f2C = *work->f38++;
    }
    else
    {
        work->f2C = 1;
    }

    if (GCL_GetOption('h'))
    {
        work->f34 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f34 = 1;
    }

    MENU_ResetItemPos();
    MENU_ResetWeaponPos();

    if (GCL_GetOption('f'))
    {
        work->proc = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->proc = -1;
    }

    work->f44 = GCL_GetOption('c') != 0;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewPadDemo(int name, int where, int argc, char **argv)
{
    PadDemoWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(PadDemoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "pad_demo.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
