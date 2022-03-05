#include "dgd.h"

extern DG_CHNL DG_Chanls_800B1800[];

void DG_Init_800179F4(DG_CHNL *pDg, DRAWENV *pDrawEnv, int bUnknown);

void DG_80018128(int chanl, DRAWENV *pDrawEnv)
{
    DG_CHNL *pOt = &DG_Chanls_800B1800[chanl + 1];
    DG_Init_800179F4(pOt, pDrawEnv, 0);
    pOt->word_6BC37A_0_1EC_size = 2;
}
