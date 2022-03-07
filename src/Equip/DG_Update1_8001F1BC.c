
#include "linker.h"
#include "libdg.h"
#include "dgd.h"

extern DG_CHNL          DG_Chanls_800B1800[3];

extern void DG_RenderPipeline_800172A8(void);

void DG_InitLightSystem_80019F40(void);
void DG_RenderPipeline_Init_8001715C(void);
void DG_ReloadPalette_8001FC58(void);
void DG_ResetPaletteEffect_80078FF8(void);
void DG_Set_RGB_800184F4(int, int, int);
extern void mts_printf_8008BBA0(const char*, ...);


void DG_Update1_8001F1BC(void)
{
    DG_RenderPipeline_800172A8();
}

extern const char aObjectQueueD[];
extern const char aPrimitiveQueue[];

extern int DG_CurrentGroupID_800AB968;

void DG_8001F1DC()
{
    DG_CHNL* pChanl;
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
