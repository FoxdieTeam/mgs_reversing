#include "libgv.h"
#include <stdio.h>

#define RESIDENT_REGION_FLAG 0x1000000

/**bss****************************************************************/
extern GV_CACHE_PAGE GV_CacheSystem;
extern GV_LOADFUNC   GV_LoaderFunctions[MAX_LOADERS];
/*********************************************************************/

STATIC GV_CACHE_TAG *SECTION(".sbss") GV_CurrentTag;
STATIC GV_CACHE_TAG *SECTION(".sbss") GV_ResidentCache;
STATIC int           SECTION(".sbss") GV_ResidentCacheSize;

/**
 * @brief Searches the cache for an entry matching a given ID and returns the
 * tag of a matching entry if found.
 * GV_CurrentTag is also set to the first free cache entry if one is found.
 *
 * @param id The ID to search for in the cache.
 */
STATIC GV_CACHE_TAG *GV_FileCacheFind(int id)
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
 * @brief Returns the cache ID of a file using its hashed name and extension.
 *
 * @param name The hashed name of the file.
 * @param ext The first character of the file extension.
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
 * @brief Returns the cache ID of a file using its name and extension.
 *
 * @param name The name of the file.
 * @param ext The first character of the file extension.
 */
int GV_CacheID2(const char *name, int ext)
{
    int hash;

    hash = GV_StrCode(name);
    return GV_CacheID(hash, ext);
}

/**
 * @brief Returns the cache ID of a file using its full file name as a string.
 *
 * @param filename The full name of the file with extension.
 */
int GV_CacheID3(char *filename)
{
    char  stem[32];
    char *iter;
    char  c;

    iter = stem;
    c = *filename++;

    if (c == '.')
    {
        *stem = '\0';
        goto exit;
    }

    // won't match with a real loop
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
    return GV_CacheID2(stem, *filename);
}

/**
 * @brief Returns the data pointer of a cache entry given its ID.
 *
 * @param id The ID to search for in the cache.
 */
void *GV_GetCache(int id)
{
    GV_CACHE_TAG *tag;

    tag = GV_FileCacheFind(id);
    if (tag)
    {
        return tag->ptr;
    }

    return NULL;
}

/**
 * @brief Sets the data pointer of a cache entry given its ID.
 *
 * @param id The ID to search for in the cache.
 * @param ptr The data pointer to be written into the cache entry.
 */
int GV_SetCache(int id, void *ptr)
{
    if (!GV_FileCacheFind(id) && GV_CurrentTag)
    {
        GV_CurrentTag->id = id;
        GV_CurrentTag->ptr = ptr;
        return 0;
    }

    return -1;
}

/**
 * @brief Sets the loader callback for a given file extension.
 *
 * @param ext The file extension to set a loader callback for.
 * @param func The function pointer to the loader callback.
 */
void GV_SetLoader(int ext, GV_LOADFUNC func)
{
    ext -= 'a';
    GV_LoaderFunctions[ext] = func;
}

/**
 * @brief Initialises the loader callbacks by setting them all to NULL.
 */
void GV_InitLoader(void)
{
    GV_LOADFUNC *loader;
    int          i;

    loader = GV_LoaderFunctions;
    for (i = MAX_LOADERS; i > 0; i--)
    {
        *loader++ = NULL;
    }
}

/**
 * @brief Initialises the cache system by marking all entries as unused.
 * Also initialises the resident cache as empty.
 */
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

/**
 * @brief Saves all cache entries marked as resident to GV_ResidentCache.
 */
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
        if (tag->id & RESIDENT_REGION_FLAG)
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
            if (tag->id & RESIDENT_REGION_FLAG)
            {
                *resident++ = *tag;
            }

            tag++;
        }
    }
}

/**
 * @brief Frees the cache system by marking all entries as unused.
 * Then loads all resident entries from GV_ResidentCache.
 */
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

/**
 * @brief Sets the current free cache tag.
 *
 * @param ptr The data pointer of the file to write.
 * @param id The ID of the file to write.
 * @param region The region of the file to write.
 */
static inline void GV_SetCurrentTag(void *ptr, int id, int region)
{
    if (region != GV_REGION_CACHE)
    {
        id |= RESIDENT_REGION_FLAG;
    }

    GV_CurrentTag->id = id;
    GV_CurrentTag->ptr = ptr;
}

/**
 * @brief Returns the loader function for a file given its ID.
 *
 * @param id The ID of the file to return the loader function for.
 */
static inline GV_LOADFUNC GV_GetLoadFunc(int id)
{
    GV_LOADFUNC *loader;

    loader = GV_LoaderFunctions;

    if (id < 0)
    {
        id += 0xFFFF;
    }

    return loader[id >> 16];
}

/**
 * @brief Loads a given file by calling its loader function.
 * Also inserts the file into the file cache depending on the region.
 *
 * @param ptr The data pointer of the file being loaded.
 * @param id The ID of the file being loaded.
 * @param region The region of the file being loaded.
 */
int GV_LoadInit(void *ptr, int id, int region)
{
    GV_LOADFUNC   func;
    int           ret;
    GV_CACHE_TAG *tag;

    if (region == GV_REGION_NOCACHE)
    {
        func = GV_GetLoadFunc(id);
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
        if (GV_FileCacheFind(id) || !GV_CurrentTag)
        {
            printf("id conflict\n");
            return -1;
        }

        tag = GV_CurrentTag;
        GV_SetCurrentTag(ptr, id, region);

        func = GV_GetLoadFunc(id);
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
