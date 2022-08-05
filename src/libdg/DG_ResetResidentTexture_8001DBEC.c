#include "linker.h"
#include "libdg.h"
#include "dgd.h"

// re-declare to force GP usage
extern int gTextureCacheSize_800AB988;
int        SECTION(".sbss") gTextureCacheSize_800AB988;

extern DG_TEX *gResidentTextureCacheCopy_800AB98C;
DG_TEX        *SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;

void DG_ResetResidentTexture_8001DBEC()
{
    int     counter;
    DG_TEX *pSrc;
    if (gResidentTextureCacheCopy_800AB98C)
    {
        pSrc = gResidentTextureCacheCopy_800AB98C;
        for (counter = gTextureCacheSize_800AB988; counter > 0; counter--)
        {
            DG_TEX *pFoundRec;
            DG_SearchForTextureRecord_8001D778(pSrc->field_0_hash, &pFoundRec);
            *pFoundRec = *pSrc++;
            pFoundRec->field_2_bUsed.b1 = 1;
        }
    }
}

void sub_8001DC88()
{
}
