
#include "linker.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "Game/game.h"
#include "psyq.h"

/**data*********************************************************/

int DG_FrameRate_8009D45C = 2;
int DG_HikituriFlag_8009D460 = 0;
int DG_HikituriFlagOld_8009D464 = 0;
int dword_8009D468 = -1;

/***************************************************************/

extern int              dword_800B3790;
extern int              GM_GameStatus_800AB3CC;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              DG_FrameRate_8009D45C;
extern GV_PAD          *GM_CurrentPadData_800AB91C;

extern GV_PAD GV_PadData_800B05C0[4];

int DG_DrawSyncResetGraph_8001F014()
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

void DG_StartFrame_8001F078(GV_ACT *pActor)
{
    int t;

    dword_800B3790 = 0;

    DG_HikituriFlagOld_8009D464 = DG_HikituriFlag_8009D460;

    if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_30) != 0)
    {
        if (dword_8009D468 == -1)
        {
            dword_8009D468 = mts_get_tick_count_8008BBB0();
            DG_HikituriFlag_8009D460 = 0;
        }

        if (!DG_HikituriFlag_8009D460)
        {
            mts_wait_vbl_800895F4(DG_FrameRate_8009D45C);
        }

        t = mts_get_tick_count_8008BBB0();
        if (dword_8009D468 + 2 < t)
        {
            DG_HikituriFlag_8009D460 = 1;
        }
        else
        {
            DG_HikituriFlag_8009D460 = 0;
        }

        dword_8009D468 += 2;
    }
    else
    {
        mts_wait_vbl_800895F4(DG_FrameRate_8009D45C);
        dword_8009D468 = -1;
        DG_HikituriFlag_8009D460 = 0;
    }

    DG_SwapFrame_80017194();

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

void DG_EndFrame_8001F1BC(void)
{
    DG_RenderPipeline_800172A8();
}

extern int DG_CurrentGroupID_800AB968;

void DG_ResetPipeline_8001F1DC()
{
    DG_InitLightSystem_80019F40();
    DG_RenderPipeline_Init_8001715C();

    DG_CurrentGroupID_800AB968 = 0;

    DG_ReloadPalette_8001FC58();
    DG_ResetPaletteEffect_80078FF8();
    DG_Set_RGB_800184F4(0, 0, 0);

    printf("Object Queue %d\n", DG_Chanl(0)->mTotalObjectCount);
    printf("Primitive Queue %d\n", DG_Chanl(0)->mTotalQueueSize - DG_Chanl(0)->mFreePrimCount);

    DG_Chanl(0)->mTotalObjectCount = 0;
    DG_Chanl(0)->mFreePrimCount = DG_Chanl(0)->mTotalQueueSize;
}

void DG_TextureCacheInit_8001F25C(void)
{
    DG_InitTextureSystem_8001D808();
    DG_ResetResidentTexture_8001DBEC();
}

extern GV_ACT DG_StartFrameActor_800B3750;
extern GV_ACT DG_EndFrameActor_800B3770; // same section as its directly after
extern int   dword_800B3790;

void DG_StartDaemon_8001F284(void)
{
    mts_set_vsync_task_800892B8();
    mts_set_callback_800893B4(DG_DrawSyncResetGraph_8001F014);
    DG_InitDispEnv_800170F0(0, 0, 320, 240, 320);
    DG_InitChanlSystem_80017B98(320);
    DG_ClearResidentTexture_8001DB10();
    DG_ResetPipeline_8001F1DC();
    GV_SetLoader('p', DG_LoadInitPcx_8001F920);
    GV_SetLoader('k', DG_LoadInitKmd_8001F4EC);
    GV_SetLoader('l', DG_LoadInitLit_8001F6B4);
    GV_SetLoader('n', DG_LoadInitNar_8001F5F8);
    GV_SetLoader('o', DG_LoadInitOar_8001F610);
    GV_SetLoader('z', DG_LoadInitKmdar_8001FAD0);
    GV_SetLoader('i', DG_LoadInitImg_8001F644);
    GV_SetLoader('s', DG_LoadInitSgt_8001F670);

    // Wait for vsync, swap frame, fetch input
    GV_InitActor(0, &DG_StartFrameActor_800B3750, NULL);
    GV_SetNamedActor(&DG_StartFrameActor_800B3750, (TActorFunction)DG_StartFrame_8001F078, NULL, "dgd.c");

    // Render new frame
    GV_InitActor(8, &DG_EndFrameActor_800B3770, NULL);
    GV_SetNamedActor(&DG_EndFrameActor_800B3770, (TActorFunction)DG_EndFrame_8001F1BC, NULL, "dgd.c");
}
