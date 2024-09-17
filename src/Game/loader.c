#include "loader.h"

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest;
extern int GM_PadVibration2_800ABA54;

typedef struct LoaderWork
{
    GV_ACT      actor;
    STAGE_FILE *field_20_pStageFile;
    int         field_24_proc_cancel_flags;
    int         field_28_bRunning;
    int         field_2C_counter;
} LoaderWork;

#define EXEC_LEVEL 2

STATIC void LoaderAct(LoaderWork *work)
{
    work->field_2C_counter++;

    if (work->field_24_proc_cancel_flags != 2)
    {
        if (work->field_24_proc_cancel_flags == 3)
        {
            DG_OffsetDispEnv(work->field_2C_counter & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (work->field_28_bRunning)
    {
        if (!FS_LoadStageSync(work->field_20_pStageFile))
        {
            work->field_28_bRunning = 0;
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
    FS_LoadStageComplete(work->field_20_pStageFile);
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
    work->field_20_pStageFile = FS_LoadStageRequest(stage_name);

    if (!work->field_20_pStageFile)
    {
        printf("NOT FOUND STAGE %s\n", stage_name);
    }

    GV_SetNamedActor(&work->actor, (GV_ACTFUNC)LoaderAct,
                     (GV_ACTFUNC)LoaderDie, "loader.c");

    work->field_28_bRunning = 1;
    work->field_24_proc_cancel_flags = (GM_LoadRequest & 0xf);
    GM_LoadComplete_800ABA38 = 0;
    return (void *)work;
}
