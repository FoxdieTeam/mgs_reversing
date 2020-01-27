#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void DG_ClearChanlSystem_80017E9C(int bufferIdx);
void DG_RenderPipeline_80018028(int bufferIdx);

int SECTION(".sbss") gClipHeights_800AB960[2];

int SECTION(".sbss") DG_CurrentGroupID_800AB968;

short SECTION(".sbss") DG_ClipMin_800AB96C;
short SECTION(".sbss") word_800AB96E;
short SECTION(".sbss") DG_ClipMax_800AB970[4];

int SECTION(".sbss") dword_800AB978;

char SECTION(".sbss") byte_800AB97C;
char SECTION(".sbss") byte_800AB97D;
short SECTION(".sbss") byte_800AB97E;

short SECTION(".sbss") word_800AB980;
short SECTION(".sbss") word_800AB982;

short SECTION(".sbss") word_800AB984[2];

int SECTION(".sbss") dword_800AB988;
int SECTION(".sbss") dword_800AB98C;

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
