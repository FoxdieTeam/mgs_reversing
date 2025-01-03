#include "loader.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "Game/game.h"

extern int GM_LoadComplete_800ABA38;
extern int GM_PadVibration2_800ABA54;

typedef struct LoaderWork
{
    GV_ACT  actor;
    void   *info;
    int     type;
    int     reading;
    int     time;
} LoaderWork;

#define EXEC_LEVEL 2

STATIC void LoaderAct(LoaderWork *work)
{
    work->time++;

    if (work->type != 2)
    {
        if (work->type == 3)
        {
            DG_OffsetDispEnv(work->time & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (work->reading)
    {
        if (!FS_LoadStageSync(work->info))
        {
            work->reading = FALSE;
        }
    }
    else
    {
        GV_DestroyActor(&work->actor);
    }
}

STATIC void LoaderDie(LoaderWork *work)
{
    printf("LoadEnd\n");
    FS_LoadStageComplete(work->info);
    GM_LoadComplete_800ABA38 = -1;
}

void *NewLoader(const char *dir)
{
    LoaderWork *work;

#ifdef DEV_EXE
    // force load some overlay in dev variant
    if (strcmp(dir, "title") == 0)
    {
        dir = "select1";
    }
#endif

    work = (LoaderWork *)GV_NewActor(EXEC_LEVEL, sizeof(LoaderWork));
    printf("LoadReq\n");
    work->info = FS_LoadStageRequest(dir);

    if (!work->info)
    {
        printf("NOT FOUND STAGE %s\n", dir);
    }

    GV_SetNamedActor(&work->actor, (GV_ACTFUNC)LoaderAct,
                     (GV_ACTFUNC)LoaderDie, "loader.c");

    work->reading = TRUE;
    work->type = (GM_LoadRequest & 0x0f);
    GM_LoadComplete_800ABA38 = 0;
    return (void *)work;
}
