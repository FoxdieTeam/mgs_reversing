#include "linker.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "loader.h"

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest_800AB3D0;
extern int GM_PadVibration2_800ABA54;

//Act
void Loader_Act_8002E390(struct Loader *pLoader)
{
    pLoader->field_2C_counter++;

    if (pLoader->field_24_proc_cancel_flags != 2)
    {
        if (pLoader->field_24_proc_cancel_flags == 3)
        {
            DG_OffsetDispEnv(pLoader->field_2C_counter & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (pLoader->field_28_bRunning)
    {
        if (!FS_LoadStageSync(pLoader->field_20_pStageFile))
        {
            pLoader->field_28_bRunning = 0;
        }
    }
    else
    {
        GV_DestroyActor(&pLoader->base);
    }
}


//Die
void Loader_Kill_8002E41C(struct Loader *pLoader)
{
    printf("LoadEnd\n");
    FS_LoadStageComplete(pLoader->field_20_pStageFile);
    GM_LoadComplete_800ABA38 = -1;
}

//NewLoader
struct Loader *Loader_Init_8002E460(const char *pStageName)
{
    struct Loader *pLoader;

#ifdef DEV_EXE
    // force load some overlay in dev variant
    if (strcmp(pStageName, "title") == 0)
    {
        pStageName = "select1";
    }
#endif

    pLoader = (struct Loader *)GV_NewActor(2, sizeof(struct Loader));
    printf("LoadReq\n");
    pLoader->field_20_pStageFile = FS_LoadStageRequest(pStageName);

    if (!pLoader->field_20_pStageFile)
    {
        printf("NOT FOUND STAGE %s\n", pStageName);
    }

    GV_SetNamedActor(&pLoader->base, (TActorFunction)Loader_Act_8002E390, (TActorFunction)Loader_Kill_8002E41C, "loader.c");

    pLoader->field_28_bRunning = 1;
    pLoader->field_24_proc_cancel_flags = (GM_LoadRequest_800AB3D0 & 0xf);
    GM_LoadComplete_800ABA38 = 0;
    return pLoader;
}
