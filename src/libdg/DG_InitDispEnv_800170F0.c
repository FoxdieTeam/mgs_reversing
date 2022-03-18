#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void DG_ClearChanlSystem_80017E9C(int bufferIdx);
void DG_RenderPipeline_80018028(int bufferIdx);

int SECTION(".sbss") gClipHeights_800AB960[2];

int SECTION(".sbss") DG_CurrentGroupID_800AB968;

short SECTION(".sbss") DG_ClipMin_800AB96C[2];
short SECTION(".sbss") DG_ClipMax_800AB970[2];

int SECTION(".sbss") dword_800AB974;
int SECTION(".sbss") dword_800AB978;

unsigned char SECTION(".sbss") DG_r_800AB97C;
unsigned char SECTION(".sbss") DG_b_800AB97D;
unsigned char SECTION(".sbss") DG_g_800AB97E;

extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;

extern int DG_UnDrawFrameCount_800AB380; // gp
int SECTION(".sdata") DG_UnDrawFrameCount_800AB380;

extern int dword_800AB384;               // gp
int SECTION(".sdata") dword_800AB384;

extern int DG_HikituriFlagOld_8009D464; // short ?

DISPENV SECTION(".gDispEnv_800B0600") gDispEnv_800B0600;

void DG_InitDispEnv_800170F0(int x, short y, short w, short h, int clipH)
{
    DISPENV *pDispEnv = &gDispEnv_800B0600;
    RECT *pDispRect;
    RECT *pScreenRect;

    pDispRect = &pDispEnv->disp;
    pScreenRect = &pDispEnv->screen;

    setRECT(pDispRect, x, y, w, h);
    setRECT(pScreenRect, 0, 0, 256, 240);

    pDispEnv->isinter = 0;
    pDispEnv->isrgb24 = 0;

    // For some reason lets overwrite what we already setup
    pDispEnv->screen.y = 8;
    pDispEnv->screen.h = 224;

    gClipHeights_800AB960[0] = x;
    gClipHeights_800AB960[1] = x + clipH;
}

void DG_ChangeReso_80017154(void)
{
}

void DG_RenderPipeline_Init_8001715C(void)
{
    DG_ClearChanlSystem_80017E9C(0);
    DG_ClearChanlSystem_80017E9C(1);
    DG_RenderPipeline_80018028(0);
    DG_RenderPipeline_80018028(1);
}

DISPENV *PutDispEnv_80090094(DISPENV *env);
void DG_DrawOTag_80017E4C(int activeBuffer);
void MENU_ResetSystem_80038A88();
void DG_ClearTmpLight_8001A0E4();
void GV_ClearMemorySystem_80015B4C( int which );

void DG_80017194()
{
    int activeBuffer = GV_Clock_800AB920;
    if ((GV_PauseLevel_800AB928 & 8) != 0 || DG_UnDrawFrameCount_800AB380 > 0)
    {
        if (dword_800AB384 < 0)
        {
            dword_800AB384 = activeBuffer;
        }
        if ((GV_PauseLevel_800AB928 & 8) == 0)
        {
            --DG_UnDrawFrameCount_800AB380;
        }
    }
    else if (dword_800AB384 < 0 || activeBuffer != dword_800AB384)
    {

        DISPENV *p = &gDispEnv_800B0600;
        p->disp.x = gClipHeights_800AB960[activeBuffer ];

        PutDispEnv_80090094(&gDispEnv_800B0600);
        if (!DG_HikituriFlagOld_8009D464)
        {
            DG_DrawOTag_80017E4C(1 - activeBuffer);
        }
        dword_800AB384 = -1;
    }
    GV_ClearMemorySystem_80015B4C(activeBuffer);
    if (!DG_HikituriFlagOld_8009D464)
    {
        GV_ClearMemorySystem_80015B4C(2);
    }
    MENU_ResetSystem_80038A88();
    DG_ClearChanlSystem_80017E9C(activeBuffer);
    DG_ClearTmpLight_8001A0E4();
}
