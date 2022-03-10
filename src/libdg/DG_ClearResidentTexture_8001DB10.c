#include "linker.h"

int SECTION(".sbss") gTextureCacheSize_800AB988;
int SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;

void DG_ClearResidentTexture_8001DB10()
{
    gTextureCacheSize_800AB988 = 0;
    gResidentTextureCacheCopy_800AB98C = 0;
}
