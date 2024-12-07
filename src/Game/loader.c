#include "loader.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest;
extern int GM_PadVibration2_800ABA54;

typedef struct LoaderWork
{
    GV_ACT      actor;
    STAGE_FILE *stage_file;         // void *info;
    int         proc_cancel_flags;  // int type;
    int         reading;            // int reading;
    int         time;               // int time;
} LoaderWork;

#define EXEC_LEVEL 2

STATIC void LoaderAct(LoaderWork *work)
{
    work->time++;

    if (work->proc_cancel_flags != 2)
    {
        if (work->proc_cancel_flags == 3)
        {
            DG_OffsetDispEnv(work->time & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (work->reading)
    {
        if (!FS_LoadStageSync(work->stage_file))
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
    FS_LoadStageComplete(work->stage_file);
    GM_LoadComplete_800ABA38 = -1;
}

void *NewLoader(const char *stage_name)
{
    LoaderWork *work;

#ifdef DEV_EXE
    // force load some overlay in dev variant
    if (strcmp(stage_name, "title") == 0)
    {
        stage_name = "select1";
    }
#endif

    work = (LoaderWork *)GV_NewActor(EXEC_LEVEL, sizeof(LoaderWork));
    printf("LoadReq\n");
    work->stage_file = FS_LoadStageRequest(stage_name);

    if (!work->stage_file)
    {
        printf("NOT FOUND STAGE %s\n", stage_name);
    }

    GV_SetNamedActor(&work->actor, (GV_ACTFUNC)LoaderAct,
                     (GV_ACTFUNC)LoaderDie, "loader.c");

    work->reading = TRUE;
    work->proc_cancel_flags = (GM_LoadRequest & 0xf);
    GM_LoadComplete_800ABA38 = 0;
    return (void *)work;
}
