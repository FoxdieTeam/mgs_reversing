#include "linker.h"
#include "libgv/actor.h"
#include "mts/mts_new.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "loader.h"

extern const char aLoadreq[];
extern const char aNotFoundStageS[];
extern const char aLoaderC[];
extern const char aLoadend[];

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest_800AB3D0;
extern int GM_PadVibration2_800ABA54;

/* int FS_LoadStageSync_800237C0(struct Loader_Record *pRec); */
/*  */
/* struct Loader_Record *FS_LoadStageRequest_800236E0(const char *pStageName); */
/* void                  FS_LoadStageComplete_80023804(struct Loader_Record *pImpl); */

void Loader_Act_8002E390(struct Loader *pLoader)
{
    pLoader->field_2C_counter++;

    if (pLoader->field_24_proc_cancel_flags != 2)
    {
        if (pLoader->field_24_proc_cancel_flags == 3)
        {
            DG_OffsetDispEnv_80017784(pLoader->field_2C_counter & 2);
            GM_PadVibration2_800ABA54 = 100;
        }
    }

    if (pLoader->field_28_bRunning)
    {
        if (!FS_LoadStageSync_800237C0(pLoader->field_20_pFileName))
        {
            pLoader->field_28_bRunning = 0;
        }
    }
    else
    {
        GV_DestroyActor_800151C8(&pLoader->base);
    }
}

void Loader_Kill_8002E41C(struct Loader *pLoader)
{
    mts_printf_8008BBA0(aLoadend);
    FS_LoadStageComplete_80023804(pLoader->field_20_pFileName);
    GM_LoadComplete_800ABA38 = -1;
}

struct Loader *Loader_Init_8002E460(const char *pStageName)
{
    struct Loader        *pLoader;
    struct Loader_Record *pLoaderRec;

    pLoader = (struct Loader *)GV_NewActor_800150E4(2, sizeof(struct Loader));
    mts_printf_8008BBA0(aLoadreq);
    pLoaderRec = FS_LoadStageRequest_800236E0(pStageName);

    pLoader->field_20_pFileName = pLoaderRec;
    if (pLoaderRec == 0)
    {
        mts_printf_8008BBA0(aNotFoundStageS, pStageName);
    }

    GV_SetNamedActor_8001514C(&pLoader->base, (TActorFunction)Loader_Act_8002E390, (TActorFunction)Loader_Kill_8002E41C,
                              aLoaderC);

    pLoader->field_28_bRunning = 1;
    pLoader->field_24_proc_cancel_flags = (GM_LoadRequest_800AB3D0 & 0xf);
    GM_LoadComplete_800ABA38 = 0;
    return pLoader;
}
