#include "loader.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;
    void   *info;
    int     type;
    int     reading;
    int     time;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL2

static void Act(Work *work)
{
    work->time++;

    if (work->type != 2)
    {
        if (work->type == 3)
        {
            DG_OffsetDispEnv(work->time & 2);
            GM_PadVibration2 = 100;
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

static void Die(Work *work)
{
    printf("LoadEnd\n");
    FS_LoadStageComplete(work->info);
    GM_LoadComplete = -1;
}

void *NewLoader(const char *dir)
{
    Work *work;

#ifdef DEV_EXE
    // force load some overlay in dev variant
    if (strcmp(dir, "title") == 0)
    {
        dir = "select1";
    }
#endif

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    printf("LoadReq\n");
    work->info = FS_LoadStageRequest(dir);

    if (!work->info)
    {
        printf("NOT FOUND STAGE %s\n", dir);
    }

    GV_SetNamedActor(&work->actor, Act, Die, "loader.c");

    work->reading = TRUE;
    work->type = (GM_LoadRequest & 0x0f);
    GM_LoadComplete = 0;

    return (void *)work;
}
