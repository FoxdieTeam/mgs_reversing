
#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "actor.h"
#include "mts_new.h"

extern DG_CHNL DG_Chanls_800B1800[3];

extern void DG_RenderPipeline_800172A8(void);

void DG_InitLightSystem_80019F40(void);
void DG_RenderPipeline_Init_8001715C(void);
void DG_ReloadPalette_8001FC58(void);
void DG_ResetPaletteEffect_80078FF8(void);
void DG_Set_RGB_800184F4(int, int, int);
void GV_UpdatePadSystem_8001682C(void);
void DG_80017194(void);
extern void mts_printf_8008BBA0(const char *, ...);

extern int dword_800B3790;
extern int DG_HikituriFlag_8009D460;
extern int DG_HikituriFlagOld_8009D464;
extern int GM_GameStatus_800AB3CC;
extern int dword_8009D468;
extern int GM_PlayerStatus_800ABA50;
extern int DG_FrameRate_8009D45C;
extern short* GM_CurrentPadData_800AB91C;

extern GV_PAD GV_PadData_800B05C0[4];


extern const char asc_80010208[];

extern int ResetGraph(int mode);

int DG_DrawSyncResetGraph_8001F014()
{
    if ( DrawSync(1) > 0 )
    {
        dword_800B3790++;
        if ( dword_800B3790 < 30 )
        {
            return 0;
        }
        mts_printf_8008BBA0(asc_80010208);
        ResetGraph(1);
        dword_800B3790 = 0;
    }
    return 1;
}

void DG_Update2_8001F078(Actor *pActor)
{
    int t;

    dword_800B3790 = 0;

    DG_HikituriFlagOld_8009D464 = DG_HikituriFlag_8009D460;

    if ((GM_GameStatus_800AB3CC & 0x20000000) != 0)
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

    DG_80017194();
    GV_UpdatePadSystem_8001682C();
    GM_CurrentPadData_800AB91C = GV_PadData_800B05C0;

    if ((GM_PlayerStatus_800ABA50 & 0x10000000) != 0)
    {
        if (GV_PadData_800B05C0[1].status | GV_PadData_800B05C0[1].release)
        {
            GM_CurrentPadData_800AB91C = &GV_PadData_800B05C0[1];
        }
    }
}

void DG_Update1_8001F1BC(void)
{
    DG_RenderPipeline_800172A8();
}

extern const char aObjectQueueD[];
extern const char aPrimitiveQueue[];

extern int DG_CurrentGroupID_800AB968;

void DG_8001F1DC()
{
    DG_CHNL *pChanl;
    DG_InitLightSystem_80019F40();
    DG_RenderPipeline_Init_8001715C();
    DG_CurrentGroupID_800AB968 = 0;
    DG_ReloadPalette_8001FC58();
    DG_ResetPaletteEffect_80078FF8();
    DG_Set_RGB_800184F4(0, 0, 0);
    pChanl = &DG_Chanls_800B1800[1];
    mts_printf_8008BBA0(aObjectQueueD, pChanl->mTotalObjectCount);
    mts_printf_8008BBA0(aPrimitiveQueue, pChanl->mTotalQueueSize - pChanl->mFreePrimCount);
    pChanl->mTotalObjectCount = 0;
    pChanl->mFreePrimCount = pChanl->mTotalQueueSize;
}
