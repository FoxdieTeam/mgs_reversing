#include "libdg.h"

/**bss************************************/
extern DG_TEX gTextureRecs_800B1F50[512];
/*****************************************/

/**data***********************/
DG_TEX dword_8009D450 = {};
/*****************************/

/**gp************************************************************/
int     SECTION(".sbss") gTextureCacheSize_800AB988;
DG_TEX *SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;
/****************************************************************/

/**sdata*******************************************************************/
int last_searched_texture_name_800AB3A4 = -1;
/**************************************************************************/

int DG_SearchTexture_8001D778(int hash, DG_TEX **ppFound)
{
    int start;
    DG_TEX *record;
    int index;
    int record_hash;

    start = hash % 512;
    record = &gTextureRecs_800B1F50[start];
    index = start;

    do
    {
        record_hash = record->field_0_hash;

        if (record_hash == 0)
        {
            *ppFound = record;
            return 0;
        }

        if (record_hash == hash)
        {
            *ppFound = record;
            return 1;
        }

        index++;
        record++;

        if (index == 512)
        {
            record = gTextureRecs_800B1F50;
            index = 0;
        }
    } while(index != start);

    *ppFound = 0;
    return 0;
}


void DG_InitTextureSystem_8001D808()
{
    DG_TEX *pIter;
    int     i;

    pIter = gTextureRecs_800B1F50;
    for (i = 512; i > 0; pIter++, i--)
    {
        pIter->field_0_hash = 0;
        pIter->field_2_bUsed.c[0] = 0;
    }
}

DG_TEX *DG_GetTexture_8001D830(int name)
{
    DG_TEX *pFound;
    if (!DG_SearchTexture_8001D778(name, &pFound))
    {
        if (name != last_searched_texture_name_800AB3A4)
        {
            last_searched_texture_name_800AB3A4 = name;
        }
        pFound = &dword_8009D450;
    }
    return pFound;
}

void DG_SetTexture_8001D880(int hash, int tp, int abr, DG_Image *a, DG_Image *b, int param_6)
{
    DG_TEX *tex;

    int x, y, w, h;
    int cx, cy;
    int tpage;
    int temp;

    if (DG_SearchTexture_8001D778(hash, &tex) && tex->field_2_bUsed.c[0])
    {
        tex->field_0_hash = 0;
    }

    tex->field_0_hash = hash;
    tex->field_2_bUsed.c[1] = param_6;
    tex->field_2_bUsed.c[0] = 0;

    x = a->dim.x;
    y = a->dim.y;

    cx = b->dim.x;
    cy = b->dim.y;

    // They didn't use the LIBGPU macros :(
    temp = x;
    tpage = ((x / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->field_4_tPage = tpage;
    tex->field_6_clut = cy << 6 | cx >> 4;

    x %= 64;

    w = a->dim.w;
    h = a->dim.h;

    if (tp == 0)
    {
        x *= 4;
        w *= 4;
    }
    else
    {
        x *= 2;
        w *= 2;
    }

    tex->field_8_offx = x;
    tex->field_9_offy = y % 256;

    tex->field_A_width = w - 1;
    temp = h;
    tex->field_B_height = temp - 1;
}

void DG_GetTextureRect_8001D9EC( DG_TEX* tex, RECT* rect )
{
    short tpage;
    int x;
    int y;
    int w;

    tpage = tex->field_4_tPage;
    x = ( tpage & 0x0F ) << 6;
    y = ( tpage & 0x10 ) << 4;

    switch ( tpage & 0x180 )
    {
    case 0:
        rect->x = x + ( tex->field_8_offx >> 2 );
        break;
    case 0x80:
        rect->x = x + ( tex->field_8_offx >> 1 );
        break;
    }

    rect->y = tex->field_9_offy + y;
    rect->h = tex->field_B_height + 1;
    w = tex->field_A_width + 1;


    switch ( tpage & 0x180 )
    {
    case 0:
        w = w / 2;
    case 0x80:
        w = w / 2;
        break;
    }

    rect->w = w;
}

void DG_GetClutRect_8001DAA8( DG_TEX* tex, RECT* rect )
{
    short clut;
    int v1;
    int x, y, w;

    clut = tex->field_6_clut;
    v1 = ( clut & 0x7FC0 );
    x =  ( clut & 0x003F ) << 4;
    y = v1 / 64;
    w = 0;

    switch ( tex->field_4_tPage & 0x180 )
    {
    case 0:
        w = 0x10;
        break;
    case 1:
        w = 0x100;
        break;
    }

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = 1;
}

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
    for (i = 512; i > 0; pSrcIter++, i--)
    {
        if (pSrcIter->field_0_hash)
        {
            recordCount++;
        }
    }

    if (recordCount)
    {
        gTextureCacheSize_800AB988 = recordCount;

        pResidentTextureCacheCopy = GV_AllocResidentMemory_800163D8(recordCount * sizeof(DG_TEX));
        gResidentTextureCacheCopy_800AB98C = pResidentTextureCacheCopy;

        pSrcIter = gTextureRecs_800B1F50;
        for (i = 512; i > 0; pSrcIter++, i--)
        {
            if (pSrcIter->field_0_hash)
            {
                *pResidentTextureCacheCopy++ = *pSrcIter;
            }
        }
    }
}

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
            DG_SearchTexture_8001D778(pSrc->field_0_hash, &pFoundRec);
            *pFoundRec = *pSrc++;
            pFoundRec->field_2_bUsed.c[0] = 1;
        }
    }
}
