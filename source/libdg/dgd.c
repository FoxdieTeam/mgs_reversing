#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "mts/mts.h"
#include "game/game.h"

extern GV_PAD *GM_CurrentPadData;
extern int DG_CurrentGroupID;

/*---------------------------------------------------------------------------*/

typedef struct {
    GV_ACT actor;
} Work;

extern Work DG_WorkFirst;
extern Work DG_WorkLast;
extern int dword_800B3790;

int DG_FrameRate = 2;
int DG_HikituriFlag = 0;        // 引きつり = twitching
int DG_HikituriFlagOld = 0;     //   〃          〃

STATIC int DG_TickCount = -1;

/*---------------------------------------------------------------------------*/

int DG_VSyncCallbackFunc(void)
{
    if (DrawSync(1) > 0)
    {
        dword_800B3790++;
        if (dword_800B3790 < 30)
        {
            return 0;
        }
        printf("@");
        ResetGraph(1);
        dword_800B3790 = 0;
    }
    return 1;
}

void DG_ActFirst(Work *work)
{
    int ticks;

    dword_800B3790 = 0;

    DG_HikituriFlagOld = DG_HikituriFlag;

    if (GM_GameStatus & STATE_NOSLOW)
    {
        if (DG_TickCount == -1)
        {
            DG_TickCount = mts_get_tick_count();
            DG_HikituriFlag = 0;
        }

        if (!DG_HikituriFlag)
        {
            mts_wait_vbl(DG_FrameRate);
        }

        ticks = mts_get_tick_count();
        if (DG_TickCount + 2 < ticks)
        {
            DG_HikituriFlag = 1;
        }
        else
        {
            DG_HikituriFlag = 0;
        }

        DG_TickCount += 2;
    }
    else
    {
        mts_wait_vbl(DG_FrameRate);
        DG_TickCount = -1;
        DG_HikituriFlag = 0;
    }

    DG_SwapFrame();

    GV_UpdatePadSystem();
    GM_CurrentPadData = GV_PadData;

    if ((GM_PlayerStatus & PLAYER_SECOND_AVAILABLE) != 0)
    {
        if (GV_PadData[1].status | GV_PadData[1].release)
        {
            GM_CurrentPadData = &GV_PadData[1];
        }
    }
}

void DG_ActLast(Work *work)
{
    DG_RenderFrame();
}

void DG_ResetPipeline(void)
{
    DG_InitLightSystem();
    DG_RenderPipeline_Init();

    DG_CurrentGroupID = 0;

    DG_ReloadPalette();
    DG_ResetPaletteEffect();
    DG_SetRGB(0, 0, 0);

    printf("Object Queue %d\n", DG_Chanl(0)->mTotalObjectCount);
    printf("Primitive Queue %d\n", DG_Chanl(0)->mTotalQueueSize - DG_Chanl(0)->mFreePrimCount);

    DG_Chanl(0)->mTotalObjectCount = 0;
    DG_Chanl(0)->mFreePrimCount = DG_Chanl(0)->mTotalQueueSize;
}

void DG_ResetTextureCache(void)
{
    DG_InitTextureSystem();
    DG_LoadResidentTextureCache();
}

void DG_StartDaemon(void)
{
    mts_set_vsync_task();
    mts_set_vsync_callback_func(DG_VSyncCallbackFunc);

    DG_InitDispEnv(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 320);
    DG_InitChanlSystem(SCREEN_WIDTH);
    DG_ClearResidentTexture();
    DG_ResetPipeline();

    GV_SetLoader('p', DG_LoadInitPcx);      // *.pcx format
    GV_SetLoader('k', DG_LoadInitKmd);      // *.kmd format
    GV_SetLoader('l', DG_LoadInitLit);      // *.lit format
    GV_SetLoader('n', DG_LoadInitNar);      // *.nar format
    GV_SetLoader('o', DG_LoadInitOar);      // *.oar format
    GV_SetLoader('z', DG_LoadInitKmdar);    // *.zmd format
    GV_SetLoader('i', DG_LoadInitImg);      // *.img format
    GV_SetLoader('s', DG_LoadInitSgt);      // *.sgt format

    // Wait for vsync, swap frame, fetch input
    GV_InitActor(GV_ACTOR_DAEMON, &DG_WorkFirst, NULL);
    GV_SetNamedActor(&DG_WorkFirst, DG_ActFirst, NULL, "dgd.c");

    // Render new frame
    GV_InitActor(GV_ACTOR_DAEMON2, &DG_WorkLast, NULL);
    GV_SetNamedActor(&DG_WorkLast, DG_ActLast, NULL, "dgd.c");
}
