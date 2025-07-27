#include "libgv.h"
#include <stdio.h>
#include <stddef.h>

extern GV_CACHE_PAGE GV_CacheSystem;
extern GV_LOADFUNC  GV_LoaderFunctions[GV_MAX_LOADERS];

/*---------------------------------------------------------------------------*/

#define RESIDENT_FLAG   0x01000000

STATIC GV_CACHE_TAG *SECTION(".sbss") GV_CurrentTag;
STATIC GV_CACHE_TAG *SECTION(".sbss") GV_ResidentCache;
STATIC int           SECTION(".sbss") GV_ResidentCacheSize;

/**
 * Searches for a cached file from the cache system with a given ID.
 */
static GV_CACHE_TAG *GetCacheTag(int id)
{
    GV_CACHE_TAG *current;
    int           start;
    GV_CACHE_TAG *tag;
    int           left;
    int           i;
    int           current_id;

    current = NULL;
    start = id % MAX_CACHE_TAGS;
    tag = &GV_CacheSystem.tags[start];
    left = MAX_CACHE_TAGS - start;

    for (i = MAX_CACHE_TAGS; i > 0; i--)
    {
        current_id = tag->id & 0xFFFFFF;

        if (current_id == 0)
        {
            if (!current)
            {
                current = tag;
            }

            break;
        }

        left--;

        if (current_id == id)
        {
            return tag;
        }

        tag++;

        if (left == 0)
        {
            tag = GV_CacheSystem.tags;
        }
    }

    GV_CurrentTag = current;
    return NULL;
}

/**
 * Gets a file's cache ID from a given StrCode and extension ID.
 *
 * @param   name    StrCode of the filename (without extension)
 * @param   ext     ASCII character ('a' through 'z')
 *
 * @returns Cache ID of the requested file.
 */
int GV_CacheID(int name, int ext)
{
    ext -= 'a';

    if (ext > 25)
    {
        ext += 32;
    }

    return name + (ext << 16);
}

/**
 * Gets the file's cache ID using the filename and extension ID.
 *
 * @param   filename    ASCII filename (without extension)
 * @param   extid       ASCII character ('a' through 'z')
 *
 * @returns Cache ID of the requested file.
 */
int GV_CacheID2(const char *name, int ext)
{
    int hash;

    hash = GV_StrCode(name);
    return GV_CacheID(hash, ext);
}

/**
 * Gets the file's cache ID using the complete filename.
 *
 * The first character found after the '.' is considered the extension
 * and gets passed to GV_CacheID2.
 *
 * @param   filename    ASCII filename (with extension)
 *
 * @returns Cache ID of the requested file.
 */
int GV_CacheID3(char *filename)
{
    char  buf[32];
    char *iter;
    char  c;

    iter = buf;
    c = *filename++;

    // won't match with a real loop
    if (c == '.')
    {
        *iter = '\0';
        goto exit;
    }

loop:
    *iter++ = c;
    if (c == '\0')
    {
        goto exit;
    }

    c = *filename++;
    if (c == '.')
    {
        *iter = '\0';
        goto exit;
    }

    goto loop;

exit:
    return GV_CacheID2(buf, *filename);
}

/**
 * Gets a cached file's in-memory address from its ID.
 *
 * @param   id      Cache ID of the file to search for.
 *
 * @retval  non-NULL    pointer to the file data in memory
 * @retval  NULL        file was not found
 */
void *GV_GetCache(int id)
{
    GV_CACHE_TAG *tag;

    tag = GetCacheTag(id);
    if (tag)
    {
        return tag->ptr;
    }

    return NULL;
}

// sets currently active cached file if it can be found
int GV_SetCache(int id, void *ptr)
{
    if (!GetCacheTag(id) && GV_CurrentTag)
    {
        GV_CurrentTag->id = id;
        GV_CurrentTag->ptr = ptr;
        return 0;
    }
    return -1;
}

// sets the loadfunc in the loader table. It is mapped to a char id
void GV_SetLoader(int ext, GV_LOADFUNC func)
{
    ext -= 'a';
    GV_LoaderFunctions[ext] = func;
}

// initialises the loader table by setting all values to 0
void GV_InitLoader(void)
{
    GV_LOADFUNC *loader;
    int          i;

    loader = GV_LoaderFunctions;
    for (i = GV_MAX_LOADERS; i > 0; i--)
    {
        *loader++ = NULL;
    }
}

// initialises cache system by setting all entries to 0
// also sets the resident caches info to 0 as well
void GV_InitCacheSystem(void)
{
    GV_CACHE_TAG *tag;
    int           i;

    tag = GV_CacheSystem.tags;
    for (i = MAX_CACHE_TAGS; i > 0; i--)
    {
        tag->id = 0;
        tag++;
    }

    GV_ResidentCache = NULL;
    GV_ResidentCacheSize = 0;
}

// Iterates all the records in the cache system and checks the
// region flag to see if it should be placed in the resident area
void GV_SaveResidentFileCache(void)
{
    GV_CACHE_TAG *tag;
    int           size;
    int           i;
    GV_CACHE_TAG *resident;

    tag = GV_CacheSystem.tags;
    size = 0;
    for (i = MAX_CACHE_TAGS; i > 0; i--)
    {
        if (tag->id & RESIDENT_FLAG)
        {
            size++;
        }

        tag++;
    }

    if (size)
    {
        resident = GV_AllocResidentMemory(size * sizeof(GV_CACHE_TAG));

        GV_ResidentCache = resident;
        GV_ResidentCacheSize = size;

        tag = GV_CacheSystem.tags;
        for (i = MAX_CACHE_TAGS; i > 0; i--)
        {
            if (tag->id & RESIDENT_FLAG)
            {
                *resident++ = *tag;
            }

            tag++;
        }
    }
}

// iterates through all entries in the cache system and
// sets all ID's to 0. Then iterates through all resident
// file records and
void GV_FreeCacheSystem(void)
{
    GV_CACHE_TAG *tag;
    int           i;

    tag = GV_CacheSystem.tags;
    for (i = MAX_CACHE_TAGS; i > 0; i--)
    {
        tag->id = 0;
        tag++;
    }

    tag = GV_ResidentCache;
    if (tag)
    {
        for (i = GV_ResidentCacheSize; i > 0; i--)
        {
            GV_SetCache(tag->id, tag->ptr);
            tag++;
        }
    }
}

// inline function to set tag for a specific region, was required to
// match below function, should be moved to libgv.h
static inline void SetCurrentTag(void *ptr, int id, int region)
{
    if (region != GV_REGION_CACHE)
    {
        id |= RESIDENT_FLAG;
    }

    GV_CurrentTag->id = id;
    GV_CurrentTag->ptr = ptr;
}

// inline function to return the file handler function for a given ID
static inline GV_LOADFUNC GetLoadFunc(int id)
{
    GV_LOADFUNC *loader;

    loader = GV_LoaderFunctions;

    if (id < 0)
    {
        id += 0xFFFF;
    }

    return loader[id >> 16];
}

// loads given init function
int GV_LoadInit(void *ptr, int id, int region)
{
    GV_LOADFUNC   func;
    int           ret;
    GV_CACHE_TAG *tag;

    if (region == GV_REGION_NOCACHE)
    {
        func = GetLoadFunc(id);
        if (func)
        {
            ret = func(ptr, id);
            if (ret <= 0)
            {
                return ret;
            }
        }
    }
    else
    {
        if (GetCacheTag(id) || !GV_CurrentTag)
        {
            printf("id conflict\n");
            return -1;
        }

        tag = GV_CurrentTag;
        SetCurrentTag(ptr, id, region);

        func = GetLoadFunc(id);
        if (func)
        {
            ret = func(ptr, id);
            if (ret <= 0)
            {
                tag->id = 0;
                return ret;
            }
        }
    }
    return 1;
}
