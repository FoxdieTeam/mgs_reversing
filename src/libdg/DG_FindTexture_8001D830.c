#include "linker.h"
#include "libdg.h"

int SECTION(".sdata") last_searched_texture_name_800AB3A4 = 0xFFFFFFFF;

extern DG_TEX dword_8009D450;

extern DG_TEX gTextureRecs_800B1F50[512];

void DG_ClearTextureRecs_8001D808()
{
    DG_TEX *pIter;
    int     i;

    pIter = gTextureRecs_800B1F50;
    for (i = 512; i > 0; --i)
    {
        pIter->field_0_hash = 0;
        pIter->field_2_bUsed.c[0] = 0;
        ++pIter;
    }
}

DG_TEX *DG_FindTexture_8001D830(int name)
{
    DG_TEX *pFound;
    if (!DG_SearchForTextureRecord_8001D778(name, &pFound))
    {
        if (name != last_searched_texture_name_800AB3A4)
        {
            last_searched_texture_name_800AB3A4 = name;
        }
        pFound = &dword_8009D450;
    }
    return pFound;
}
