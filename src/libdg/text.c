#include "libdg.h"
#include "common.h"

/*** bss ***/
extern DG_TEX TexSets_800B1F50[512];

/*** data ***/
DG_TEX dword_8009D450 = {};

/*** $gp ***/
int     SECTION(".sbss") gTextureCacheSize_800AB988;
DG_TEX *SECTION(".sbss") gResidentTextureCacheCopy_800AB98C;

/*** sdata ***/
STATIC int last_searched_texture_name = -1;

int DG_SearchTexture( int hash, DG_TEX **ppFound )
{
    int start;
    DG_TEX *record;
    int index;
    int record_hash;

    start = hash % 512;
    record = &TexSets_800B1F50[start];
    index = start;

    do
    {
        record_hash = record->id;

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
            record = TexSets_800B1F50;
            index = 0;
        }
    } while(index != start);

    *ppFound = 0;
    return 0;
}


void DG_InitTextureSystem( void )
{
    DG_TEX *tex;
    int     i;

    tex = TexSets_800B1F50;
    for (i = 512; i > 0; tex++, i--)
    {
        tex->id = 0;
        tex->used = 0;
    }
}

DG_TEX *DG_GetTexture( int name )
{
    DG_TEX *pFound;
    if (!DG_SearchTexture(name, &pFound))
    {
        if (name != last_searched_texture_name)
        {
            last_searched_texture_name = name;
        }
        pFound = &dword_8009D450;
    }
    return pFound;
}

void DG_SetTexture( int hash, int tp, int abr, DG_Image *a, DG_Image *b, int col )
{
    DG_TEX *tex;

    int x, y, w, h;
    int cx, cy;
    int tpage;
    int temp;

    if (DG_SearchTexture(hash, &tex) && tex->used)
    {
        tex->id = 0;
    }

    tex->id = hash;
    tex->col = col;
    tex->used = 0;

    x = a->dim.x;
    y = a->dim.y;

    cx = b->dim.x;
    cy = b->dim.y;

    // They didn't use the LIBGPU macros :(
    temp = x;
    tpage = ((x / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->tpage = tpage;
    tex->clut = cy << 6 | cx >> 4;

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

    tex->off_x = x;
    tex->off_y = y % 256;

    tex->w = w - 1;
    temp = h;
    tex->h = temp - 1;
}

void DG_GetTextureRect( DG_TEX* tex, RECT* rect )
{
    short tpage;
    int x;
    int y;
    int w;

    tpage = tex->tpage;
    x = ( tpage & 0x0F ) << 6;
    y = ( tpage & 0x10 ) << 4;

    switch ( tpage & 0x180 )
    {
    case 0:
        rect->x = x + ( tex->off_x >> 2 );
        break;
    case 0x80:
        rect->x = x + ( tex->off_x >> 1 );
        break;
    }

    rect->y = tex->off_y + y;
    rect->h = tex->h + 1;
    w = tex->w + 1;


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

void DG_GetClutRect( DG_TEX* tex, RECT* rect )
{
    short clut;
    int v1;
    int x, y, w;

    clut = tex->clut;
    v1 = ( clut & 0x7FC0 );
    x =  ( clut & 0x003F ) << 4;
    y = v1 / 64;
    w = 0;

    switch ( tex->tpage & 0x180 )
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

void DG_ClearResidentTexture( void )
{
    gTextureCacheSize_800AB988 = 0;
    gResidentTextureCacheCopy_800AB98C = 0;
}

void DG_SaveTexureCacheToResidentMem( void )
{
    DG_TEX *tex;
    int     recordCount;
    int     i;
    DG_TEX *resident_copy;

    tex = TexSets_800B1F50;
    recordCount = 0;
    for (i = 512; i > 0; tex++, i--)
    {
        if (tex->id)
        {
            recordCount++;
        }
    }

    if (recordCount)
    {
        gTextureCacheSize_800AB988 = recordCount;

        resident_copy = GV_AllocResidentMemory(recordCount * sizeof(DG_TEX));
        gResidentTextureCacheCopy_800AB98C = resident_copy;

        tex = TexSets_800B1F50;
        for (i = 512; i > 0; tex++, i--)
        {
            if (tex->id)
            {
                *resident_copy++ = *tex;
            }
        }
    }
}

void DG_ResetResidentTexture( void )
{
    int     i;
    DG_TEX *tex;

    if (gResidentTextureCacheCopy_800AB98C)
    {
        tex = gResidentTextureCacheCopy_800AB98C;
        for (i = gTextureCacheSize_800AB988; i > 0; i--)
        {
            DG_TEX *found;
            DG_SearchTexture(tex->id, &found);
            *found = *tex++;
            found->used = 1;
        }
    }
}
