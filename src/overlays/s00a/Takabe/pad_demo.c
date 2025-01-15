#include "pad_demo.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

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

extern int   GV_PauseLevel_800AB928;
extern short GV_DemoPadStatus_800AB958[2];
extern int   GM_CurrentMap_800AB9B0;

// Something to do with setting current/last item to ITEM_NONE
void sub_8003CC88(void);

// Something to do with setting current/last weapon to WEAPON_NONE
void MENU_ResetWeaponPos(void);

#define EXEC_LEVEL 1

void PadDemo_800DCBB0(PadDemoWork *work)
{
    if (GM_StreamStatus() == -1)
    {
        GV_DestroyActor(&work->actor);
    }
}

void PadDemo_800DCBE8(PadDemoWork *work)
{
    unsigned short status;

    if (GV_PauseLevel_800AB928 & 8)
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

    if (work->f44 != 0 && mts_read_pad(1) & PAD_CROSS)
    {
        work->f44 = 1;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
            GM_GameStatus &= ~(STATE_PADDEMO | STATE_NOSLOW);
            GV_DemoPadStatus_800AB958[0] = 0;
            work->actor.act = (GV_ACTFUNC)PadDemo_800DCBB0;
        }
        else
        {
            GV_DestroyActor(&work->actor);
        }
    }

    status = work->f3C & ~0x200;
    GV_DemoPadStatus_800AB958[0] = status & ~0xA00;

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
        work->f44 = 0;
        GM_GameStatus &= ~(STATE_PADDEMO | STATE_NOSLOW | STATE_PADRELEASE | GAME_FLAG_BIT_13);
        GV_DestroyActor(&work->actor);
    }
}

void PadDemoAct_800DCD94(PadDemoWork *work)
{
    if (GM_StreamStatus() == 0)
    {
        GV_PauseLevel_800AB928 |= 4;
        GM_GameStatus |= STATE_PADRELEASE;
        DG_UnDrawFrameCount = 3;
    }
    else
    {
        printf("Pad rec start\n");
        work->actor.act = (GV_ACTFUNC)PadDemo_800DCBE8;
        GM_GameStatus |= (STATE_PADRELEASE | GAME_FLAG_BIT_13);
        DG_UnDrawFrameCount = 4;
        GV_PauseLevel_800AB928 &= ~4;
        PadDemo_800DCBE8(work);
    }
}

void PadDemoDie_800DCE48(PadDemoWork *work)
{
    GCL_ARGS args;
    long     val;

    if (work->proc > 0)
    {
        args.argc = 1;
        args.argv = &val;

        val = work->f44;

        GCL_ExecProc(work->proc, &args);
    }
}

int PadDemoGetResources_800DCE94(PadDemoWork *work, int name, int map)
{
    int filename;

    GM_CurrentMap_800AB9B0 = map;

    work->map = map;
    work->name = name;

    work->f3C = 0;

    GV_DemoPadStatus_800AB958[0] = 0;
    GV_DemoPadStatus_800AB958[1] = 0;

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

    sub_8003CC88();
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

GV_ACT *NewPadDemo_800DCFD4(int name, int where, int argc, char **argv)
{
    PadDemoWork *work;

    work = (PadDemoWork *)GV_NewActor(EXEC_LEVEL, sizeof(PadDemoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)PadDemoAct_800DCD94, (GV_ACTFUNC)PadDemoDie_800DCE48, "pad_demo.c");

        if (PadDemoGetResources_800DCE94(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
