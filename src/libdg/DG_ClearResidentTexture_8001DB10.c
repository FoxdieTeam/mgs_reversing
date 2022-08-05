#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "libgv/libgv.h"

int     SECTION(".sbss") gTextureCacheSize_800AB988;
DG_TEX *SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;

extern DG_TEX gTextureRecs_800B1F50[];

void DG_ClearResidentTexture_8001DB10()
{
    gTextureCacheSize_800AB988 = 0;
    gResidentTextureCacheCopy_800AB98C = 0;
}

void DG_SaveTexureCacheToResidentMem_8001DB20()
{
    DG_TEX *pSrcIter;
    int     recordCount;
    int     i;
    DG_TEX *pResidentTextureCacheCopy;

    pSrcIter = gTextureRecs_800B1F50;
    recordCount = 0;
    for (i = 512; i > 0; i--)
    {
        if (pSrcIter->field_0_hash)
        {
            recordCount++;
        }
        pSrcIter++;
    }

    if (recordCount)
    {
        gTextureCacheSize_800AB988 = recordCount;

        pResidentTextureCacheCopy = GV_AllocResidentMemory_800163D8(recordCount * sizeof(DG_TEX));
        gResidentTextureCacheCopy_800AB98C = pResidentTextureCacheCopy;

        pSrcIter = gTextureRecs_800B1F50;
        for (i = 512; i > 0; i--)
        {
            if (pSrcIter->field_0_hash)
            {
                *pResidentTextureCacheCopy++ = *pSrcIter;
            }
            pSrcIter++;
        }
    }
}
