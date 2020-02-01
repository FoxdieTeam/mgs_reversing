#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct
{
    unsigned char *mOrderingTables[2]; // 257 pointers? // One for each active buffer
    short word_6BC374_8;
    short word_6BC376_16;
    short word_6BC378_1;
    short word_6BC37A_0_1EC_size;
    MATRIX field_10_matrix;
    MATRIX dword_6BC39C;
    short word_6BC3BC; // Camera number?
    short mTotalQueueSize;
    short mFreePrimCount;
    short mTotalObjectCount;
    void **mQueue;
    RECT dword_6BC3C8_pStructure_rect;
    RECT dword_6BC3D0_rect;
    int dword_6BC3D8_dst[16]; // One for each active buffer
    int dword_6BC418_dst[16];
    int dword_6BC458[16];
    int dword_6BC498[16];
    DR_ENV dword_6BC4D8_src_dr_env1;
    DR_ENV dword_6BC518_src_offsetted_dr_evn;
} struct_gv;
struct_gv SECTION(".gOts_800B1800") gOts_800B1800[3];

void DG_Init_800179A8(struct_gv *pStruct, unsigned char *pOtBuffer, unsigned int otLen, void **pQueue, short queueSize, short param_6, short param_7)
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
