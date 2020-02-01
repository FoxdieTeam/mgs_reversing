#include "linker.h"
#include "dgd.h"

struct_dg SECTION(".gOts_800B1800") gOts_800B1800[3];

void DG_Init_800179A8(struct_dg *pStruct, unsigned char *pOtBuffer, unsigned int otLen, void **pQueue, short queueSize, short param_6, short param_7)
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
