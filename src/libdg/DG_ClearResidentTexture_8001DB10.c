#include "linker.h"
#include "libdg.h"
#include "dgd.h"

int SECTION(".sbss") gTextureCacheSize_800AB988;
DG_TEX* SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;

void DG_ClearResidentTexture_8001DB10()
{
    gTextureCacheSize_800AB988 = 0;
    gResidentTextureCacheCopy_800AB98C = 0;
}
