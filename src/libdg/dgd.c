#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "mts/mts.h"
#include "Game/game.h"

/**data*********************************************************/

int DG_FrameRate = 2;
int DG_HikituriFlag = 0;
int DG_HikituriFlagOld = 0;
int dword_8009D468 = -1;

/***************************************************************/

extern int              dword_800B3790;
extern int              GM_GameStatus;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              DG_FrameRate;
extern GV_PAD          *GM_CurrentPadData_800AB91C;
extern GV_PAD           GV_PadData_800B05C0[4];

int DG_DrawSyncResetGraph(void)
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

void DG_StartFrame(GV_ACT *actor)
{
    int t;

    dword_800B3790 = 0;

    DG_HikituriFlagOld = DG_HikituriFlag;

    if (GM_GameStatus & STATE_NOSLOW)
    {
        if (dword_8009D468 == -1)
        {
            dword_8009D468 = mts_get_tick_count();
            DG_HikituriFlag = 0;
        }

        if (!DG_HikituriFlag)
        {
            mts_wait_vbl(DG_FrameRate);
        }

        t = mts_get_tick_count();
        if (dword_8009D468 + 2 < t)
        {
            DG_HikituriFlag = 1;
        }
        else
        {
            DG_HikituriFlag = 0;
        }

        dword_8009D468 += 2;
    }
    else
    {
        mts_wait_vbl(DG_FrameRate);
        dword_8009D468 = -1;
        DG_HikituriFlag = 0;
    }

    DG_SwapFrame();

    GV_UpdatePadSystem();
    GM_CurrentPadData_800AB91C = GV_PadData_800B05C0;

    if ((GM_PlayerStatus_800ABA50 & PLAYER_CAN_USE_CONTROLLER_PORT_2) != 0)
    {
        if (GV_PadData_800B05C0[1].status | GV_PadData_800B05C0[1].release)
        {
            GM_CurrentPadData_800AB91C = &GV_PadData_800B05C0[1];
        }
    }
}

void DG_EndFrame(void)
{
    DG_RenderPipeline_800172A8();
}

extern int DG_CurrentGroupID_800AB968;

void DG_ResetPipeline(void)
{
    DG_InitLightSystem();
    DG_RenderPipeline_Init();

    DG_CurrentGroupID_800AB968 = 0;

    DG_ReloadPalette();
    DG_ResetPaletteEffect_80078FF8();
    DG_SetRGB(0, 0, 0);

    printf("Object Queue %d\n", DG_Chanl(0)->mTotalObjectCount);
    printf("Primitive Queue %d\n", DG_Chanl(0)->mTotalQueueSize - DG_Chanl(0)->mFreePrimCount);

    DG_Chanl(0)->mTotalObjectCount = 0;
    DG_Chanl(0)->mFreePrimCount = DG_Chanl(0)->mTotalQueueSize;
}

void DG_TextureCacheInit(void)
{
    DG_InitTextureSystem();
    DG_ResetResidentTexture();
}

extern GV_ACT DG_StartFrameActor_800B3750;
extern GV_ACT DG_EndFrameActor_800B3770; // same section as its directly after
extern int   dword_800B3790;

void DG_StartDaemon(void)
{
    mts_set_vsync_task();
    mts_set_vsync_callback_func(DG_DrawSyncResetGraph);

    DG_InitDispEnv(0, 0, 320, 240, 320);
    DG_InitChanlSystem(320);
    DG_ClearResidentTexture();
    DG_ResetPipeline();

    GV_SetLoader('p', DG_LoadInitPcx);
    GV_SetLoader('k', DG_LoadInitKmd);
    GV_SetLoader('l', DG_LoadInitLit);
    GV_SetLoader('n', DG_LoadInitNar);
    GV_SetLoader('o', DG_LoadInitOar);
    GV_SetLoader('z', DG_LoadInitKmdar);
    GV_SetLoader('i', DG_LoadInitImg);
    GV_SetLoader('s', DG_LoadInitSgt);

    // Wait for vsync, swap frame, fetch input
    GV_InitActor(0, &DG_StartFrameActor_800B3750, NULL);
    GV_SetNamedActor(&DG_StartFrameActor_800B3750, (GV_ACTFUNC)DG_StartFrame, NULL, "dgd.c");

    // Render new frame
    GV_InitActor(8, &DG_EndFrameActor_800B3770, NULL);
    GV_SetNamedActor(&DG_EndFrameActor_800B3770, (GV_ACTFUNC)DG_EndFrame, NULL, "dgd.c");
}
