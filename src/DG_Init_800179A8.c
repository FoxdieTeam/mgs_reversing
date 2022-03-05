#include "linker.h"
#include "dgd.h"


void SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);

DG_CHNL SECTION(".DG_Chanls_800B1800") DG_Chanls_800B1800[3];

// re-declare to force GP usage
extern int dword_800AB978;
int SECTION(".sbss") dword_800AB978;

extern DR_ENV stru_800B1380[2];

void DG_Init_800179A8(DG_CHNL *pStruct, unsigned char *pOtBuffer, unsigned int otLen, void **pQueue, short queueSize, short param_6, short param_7)
{
    unsigned char* pEnd = pOtBuffer + ((((1 << (otLen))) + 1) * 4); // TODO: Aligning the end ptr? Also not sure if type is correct
    pStruct->mOrderingTables[0] = pOtBuffer;
    pStruct->mOrderingTables[1] = pEnd;
    pStruct->mTotalObjectCount = 0;
    pStruct->mQueue = pQueue;
    pStruct->word_6BC374_8 = otLen;
    pStruct->word_6BC37A_0_1EC_size = 0;
    pStruct->mFreePrimCount = queueSize;
    pStruct->mTotalQueueSize = queueSize;
    pStruct->word_6BC376_16 = param_6;
    pStruct->word_6BC378_1 = param_7;
}


void DG_Init_800179F4(DG_CHNL *pOt, DRAWENV *pDrawEnv, int a3)
{
    int x_off;
    DRAWENV drawEnv;

    drawEnv = *pDrawEnv;
    x_off = 0;
    
    if ( pOt->word_6BC378_1 )
    {
        x_off = dword_800AB978;
    }
    pOt->field_64_rect.x = drawEnv.clip.x - drawEnv.ofs[0];
    pOt->field_64_rect.y = drawEnv.clip.y - drawEnv.ofs[1];
    pOt->field_64_rect.w = drawEnv.clip.w;
    pOt->field_64_rect.h = drawEnv.clip.h;
    SetDrawEnv_800906B0(pOt->field_16C_dr_env, &drawEnv);
    drawEnv.clip.x += x_off;
    drawEnv.ofs[0] += x_off;
    SetDrawEnv_800906B0(&pOt->field_16C_dr_env[1], &drawEnv);
    if ( a3 )
    {
        drawEnv.isbg = 0;
        SetDrawEnv_800906B0(&stru_800B1380[1], &drawEnv);
        drawEnv.clip.x -= x_off;
        drawEnv.ofs[0] -= x_off;
        SetDrawEnv_800906B0(&stru_800B1380[0], &drawEnv);
    }
}
