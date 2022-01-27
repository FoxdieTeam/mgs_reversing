#include "linker.h"
#include "libdg.h"
#include "dgd.h"

void SetDrawSyncCallBack_8008F76C(void*);

void DG_DrawSyncCallback_80017984(void);

int SECTION(".sbss") dword_800AB978;
extern int dword_800AB978;

extern DG_CHNL DG_Chanls_800B1800[3];

void DG_Init_800179A8(DG_CHNL *pStruct, unsigned char *pOtBuffer, unsigned int otLen, DG_OBJS **pQueue, short queueSize, short param_6, short param_7);
void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void DG_Init_800179F4(DG_CHNL *pDg, DRAWENV *pDrawEnv, int bUnknown);
void DG_InitOT_80017B30(DG_CHNL *a1, int a2);

int SECTION(".dword_800B0630") dword_800B0630[68];
int SECTION(".dword_800B0630") dword_800B0740[516];
int SECTION(".dword_800B0630") dword_800B0F50[4];

DG_OBJS* SECTION(".dword_800B0630") dword_800B0F60[8];
DG_OBJS* SECTION(".dword_800B0630") dword_800B0F80[256];

DR_ENV SECTION(".dword_800B0630") stru_800B1380[2];

void DG_3OTsInit_80017B98(int width)
{
    DRAWENV drawEnv;
    DG_CHNL* ptr;

    SetDrawSyncCallBack_8008F76C(DG_DrawSyncCallback_80017984);
    dword_800AB978 = width;
    ptr = DG_Chanls_800B1800;
    DG_Init_800179A8(ptr, (unsigned char*)dword_800B0630, 5, dword_800B0F60, 8, -1, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    DG_Init_800179F4(ptr, &drawEnv, 1);
    DG_InitOT_80017B30(ptr, 0);
    DG_InitOT_80017B30(ptr, 1);

    ptr++;
    DG_Init_800179A8(ptr, (unsigned char*)dword_800B0740, 8, dword_800B0F80, 256, 16, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.ofs[0] = 160;
    drawEnv.ofs[1] = 112;
    DG_Init_800179F4(ptr, &drawEnv, 0);
    DG_InitOT_80017B30(ptr, 0);
    DG_InitOT_80017B30(ptr, 1);

    ptr->dword_6BC458 = stru_800B1380[0];
    ptr->dword_6BC498 = stru_800B1380[1];

    ptr++;
    DG_Init_800179A8(ptr, (unsigned char*)dword_800B0F50, 0, 0, 0, 8, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    DG_Init_800179F4(ptr, &drawEnv, 0);
    DG_InitOT_80017B30(ptr, 0);
    DG_InitOT_80017B30(ptr, 1);

    ptr->dword_6BC458 = stru_800B1380[0];
    ptr->dword_6BC498 = stru_800B1380[1];
}
