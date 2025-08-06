#include "libdg.h"
#include "common.h"

/*** bss ***/
extern DG_TEX TexSets[DG_MAX_TEXTURES];

/*** data ***/
STATIC DG_TEX DG_NullTexture = {};

/*** $gp ***/
int     SECTION(".sbss") DG_ResidentTextureCacheSize;
DG_TEX *SECTION(".sbss") DG_ResidentTextureCache;

/*** sdata ***/
STATIC int DG_LastMissingTexture = -1;

/**
 * @brief Searches the cache for an entry matching a given ID.
 * Also returns an empty texture if one is found first.
 *
 * @param id The ID to search for in the cache.
 * @param found The pointer to write the found texture pointer to.
 */
STATIC int FindTexture( int id, DG_TEX **found )
{
    int     start;
    DG_TEX *record;
    int     index;
    int     record_id;

    start = id % DG_MAX_TEXTURES;
    record = &TexSets[start];

    index = start;
    do
    {
        record_id = record->id;

        if (record_id == 0)
        {
            *found = record;
            return 0;
        }

        if (record_id == id)
        {
            *found = record;
            return 1;
        }

        index++;
        record++;

        if (index == DG_MAX_TEXTURES)
        {
            record = TexSets;
            index = 0;
        }
    } while(index != start);

    *found = NULL;
    return 0;
}

/**
 * @brief Initialises the texture cache by marking all entries as unused.
 */
void DG_InitTextureSystem( void )
{
    DG_TEX *tex;
    int     i;

    tex = TexSets;
    for (i = DG_MAX_TEXTURES; i > 0; i--)
    {
        tex->id = 0;
        tex->used = 0;
        tex++;
    }
}

/**
 * @brief Searches the cache for an entry matching a given ID and returns a
 * matching entry if found.
 * Returns an empty texture if no texture with a matching ID was found.
 * Also sets DG_LastMissingTexture to the given ID if it was not found.
 *
 * @param id The ID to search for in the cache.
 */
DG_TEX *DG_GetTexture( int id )
{
    DG_TEX *found;

    if (!FindTexture(id, &found))
    {
        if (id != DG_LastMissingTexture)
        {
            DG_LastMissingTexture = id;
        }

        found = &DG_NullTexture;
    }

    return found;
}

/**
 * @brief Sets a texture given its ID and parameters.
 *
 * @param id The ID of the texture to set.
 * @param tp The bitdepth of the texture (0: 4bpp, 1: 8bpp).
 * @param abr The blend rate of the texture (see libgpu.h).
 * @param tex The RECT describing the texture data.
 * @param pal The RECT describing the palette data.
 * @param col The number of palette entries.
 */
void DG_SetTexture( int id, int tp, int abr, RECT *img, RECT *pal, int col )
{
    DG_TEX *tex;
    int     x, y, w, h;
    int     cx, cy;
    int     tpage;
    int     temp;

    if (FindTexture(id, &tex) && tex->used)
    {
        tex->id = 0;
    }

    tex->id = id;
    tex->col = col;
    tex->used = 0;

    x = img->x;
    y = img->y;

    cx = pal->x;
    cy = pal->y;

    // They didn't use the LIBGPU macros :(
    temp = x;
    tpage = ((x / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->tpage = tpage;
    tex->clut = cy << 6 | cx >> 4;

    x %= 64;

    w = img->w;
    h = img->h;

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

/**
 * @brief Gets the RECT describing the given texture's extents.
 *
 * @param tex The texture to get the RECT for.
 * @param rect The RECT to write the texture's extents to.
 */
void DG_GetTextureRect( DG_TEX *tex, RECT *rect )
{
    int tpage;
    int x, y, w;

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
        w /= 2;
    case 0x80:
        w /= 2;
        break;
    }

    rect->w = w;
}

/**
 * @brief Gets the RECT describing the given texture's palette extents.
 *
 * @param tex The texture to get the RECT for.
 * @param rect The RECT to write the texture's palette extents to.
 */
void DG_GetClutRect( DG_TEX *tex, RECT *rect )
{
    int clut;
    int x, y, y2, w;

    clut = tex->clut;

    y = ( clut & 0x7FC0 );
    x = ( clut & 0x003F ) << 4;
    y2 = y / 64;

    w = 0;

    switch ( tex->tpage & 0x180 )
    {
    case 0:
        w = 16;
        break;
    case 1:
        w = 256;
        break;
    }

    rect->x = x;
    rect->y = y2;
    rect->w = w;
    rect->h = 1;
}

/**
 * @brief Initialises the resident texture cache as empty.
 */
void DG_ClearResidentTexture( void )
{
    DG_ResidentTextureCacheSize = 0;
    DG_ResidentTextureCache = NULL;
}

/**
 * @brief Saves all texture cache entries to the resident texture cache.
 */
void DG_SaveResidentTextureCache( void )
{
    DG_TEX *tex;
    int     size;
    int     i;
    DG_TEX *resident;

    tex = TexSets;
    size = 0;
    for (i = DG_MAX_TEXTURES; i > 0; tex++, i--)
    {
        if (tex->id != 0)
        {
            size++;
        }
    }

    if (size)
    {
        DG_ResidentTextureCacheSize = size;
        DG_ResidentTextureCache = resident = GV_AllocResidentMemory(size * sizeof(DG_TEX));

        tex = TexSets;
        for (i = DG_MAX_TEXTURES; i > 0; i--)
        {
            if (tex->id != 0)
            {
                *resident++ = *tex;
            }

            tex++;
        }
    }
}

/**
 * @brief Loads all resident texture cache entries into the main texture cache.
 */
void DG_LoadResidentTextureCache( void )
{
    DG_TEX *tex;
    int     i;
    DG_TEX *found;

    if (DG_ResidentTextureCache)
    {
        tex = DG_ResidentTextureCache;
        for (i = DG_ResidentTextureCacheSize; i > 0; i--)
        {
            FindTexture(tex->id, &found);
            *found = *tex++;
            found->used = 1;
        }
    }
}
