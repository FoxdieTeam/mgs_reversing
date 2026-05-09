#include "libgv.h"
#include <stdio.h>
#include <stddef.h>

#define CACHEID_RESIDENT 0x01000000

#define SET_SPEC( _id, _spec )  ( (_id) + ( (_spec) << 16 ) )
#define GET_SPEC( _id )         ( (_id & ~CACHEID_RESIDENT) >> 16 )

#define NEVER_USED  (0)

extern GV_LOADFUNC Loaders[ MAX_LOADERS ];

extern CACHE Caches[ MAX_CACHES ];
static CACHE *SECTION(".sbss") EmptyCache;

STATIC CACHE *SECTION(".sbss") GV_ResidentCache;
STATIC int    SECTION(".sbss") GV_ResidentCacheSize;

/*---------------------------------------------------------------------------*/

/**
 * @brief Searches the cache for an entry matching a given ID and returns the
 * tag of a matching entry if found.
 * EmptyCache is also set to the first free cache entry if one is found.
 *
 * @param id The ID to search for in the cache.
 */
static CACHE *FindCache( int id )
{
    CACHE *cp, *empty;
    int    mod, this;
    int    i, j;

    empty = NULL;
    mod = id % MAX_CACHES;
    cp = Caches + mod;
    j = MAX_CACHES - mod;

    for ( i = MAX_CACHES; i > 0; i-- )
    {
        this = 0xFFFFFF & cp->id;
        if ( this == NEVER_USED )
        {
            if ( empty == NULL ) empty = cp;
            break;
        }
        if ( this == id )
        {
            return cp;
        }
        cp++;
        if ( --j == 0 ) cp = Caches;
    }

    EmptyCache = empty;
    return NULL;
}

/* --------------------------------------------------------- */

/**
 * @brief Returns the cache ID of a file using its hashed name and extension.
 *
 * @param   root_id    strcode hash of the filename (without extension).
 * @param   spec     The first character of the file extension.
 */
int GV_CacheID( int root_id, int spec )
{
    spec -= 'a';
    if ( spec > 25 ) spec += 32;
    return SET_SPEC( root_id, spec );
}

/**
 * @brief Returns the cache ID of a file using its name and extension.
 *
 * @param   root_name    The name of the file (without extension).
 * @param   spec     The first character of the file extension.
 */
int GV_CacheID2( const char *root_name, int spec )
{
    return GV_CacheID( GV_StrCode( root_name ), spec );
}

/**
 * @brief Returns the cache ID of a file using its full file name as a string.
 * The character found after the first '.' is considered the extension.
 *
 * @param   name    The full name of the file with extension.
 */
int GV_CacheID3( char *name )
{
    char root[ 32 ];
    char c, *cp, *cp2;

    cp = name;
    cp2 = root;
    do
    {
        if ( ( c = *cp++ ) == '.' )
        {
            *cp2 = '\0';
            break;
        }
        *cp2++ = c;
    } while ( c != '\0' );

    return GV_CacheID2( root, cp[0] );
}

/**
 * @brief Returns the data pointer of a cache entry given its ID.
 *
 * @param   id      The ID to search for in the cache.
 *
 * @returns NULL if the file couldn't be found.
 */
void *GV_GetCache( int id )
{
    CACHE *cp;

    if ( ( cp = FindCache( id ) ) != NULL ) return cp->buf;
    return NULL;
}

/**
 * @brief Sets the data pointer of a cache entry given its ID.
 *
 * @param id The ID to search for in the cache.
 * @param buf The data pointer to be written into the cache entry.
 */
int GV_SetCache( int id, void *buf )
{
    if ( FindCache(id) == NULL && EmptyCache != NULL )
    {
        EmptyCache->id = id;
        EmptyCache->buf = buf;
        return 0;
    }
    return -1;
}

/**
 * @brief Sets the loader callback for a given file extension.
 *
 * @param spec The file extension to set a loader callback for.
 * @param init The function pointer to the loader callback.
 */
void GV_SetLoader( int spec, GV_LOADFUNC init )
{
    int type;

    type = spec - 'a';
    Loaders[ type ] = init;
}

/**
 * @brief Initialises the loader callbacks by setting them all to NULL.
 */
void GV_ResetLoader( void )
{
    GV_LOADFUNC *func;
    int          i;

    func = Loaders;
    for ( i = MAX_LOADERS; i > 0; i-- )
    {
        *func = NULL;
        func++;
    }
}

/**
 * @brief Initialises the cache system by marking all entries as unused.
 * Also initialises the resident cache as empty.
 */
void GV_InitCacheSystem( void )
{
    CACHE *cp;
    int    i;

    cp = Caches;
    for ( i = MAX_CACHES; i > 0; i-- )
    {
        cp->id = NEVER_USED;
        cp++;
    }

    GV_ResidentCache = NULL;
    GV_ResidentCacheSize = 0;
}

/**
 * @brief Saves all cache entries marked as resident to GV_ResidentCache.
 */
void GV_SaveResidentFileCache( void )
{
    CACHE *cp;
    int    i, size;

    cp = Caches;
    size = 0;
    for ( i = MAX_CACHES; i > 0; i-- )
    {
        if ( cp->id & CACHEID_RESIDENT ) size++;
        cp++;
    }

    if ( size != 0 )
    {
        CACHE *res;

        res = GV_AllocResidentMemory( size * sizeof(CACHE) );
        GV_ResidentCache = res;
        GV_ResidentCacheSize = size;
        cp = Caches;
        for ( i = MAX_CACHES; i > 0; i-- )
        {
            if ( cp->id & CACHEID_RESIDENT ) *res++ = *cp;
            cp++;
        }
    }
}

/**
 * @brief Frees the cache system by marking all entries as unused.
 * Then loads all resident entries from GV_ResidentCache.
 */
void GV_FreeCacheSystem( void )
{
    CACHE *cp;
    int    i;

    cp = Caches;
    for ( i = MAX_CACHES; i > 0; i-- )
    {
        cp->id = NEVER_USED;
        cp++;
    }

    cp = GV_ResidentCache;
    if ( cp != NULL )
    {
        for ( i = GV_ResidentCacheSize; i > 0; i-- )
        {
            GV_SetCache( cp->id, cp->buf );
            cp++;
        }
    }
}

/**
 * @brief Sets the current free cache tag.
 *
 * @param data The data pointer of the file to write.
 * @param name The ID of the file to write.
 * @param cache_mode The region of the file to write.
 */
static inline void SetCurrentTag( void *data, int name, int cache_mode )
{
    if ( cache_mode != GV_INIT_CACHE )
    {
        name |= CACHEID_RESIDENT;
    }
    EmptyCache->id = name;
    EmptyCache->buf = data;
}

/**
 * @brief Loads a given file by calling its loader function.
 * Also inserts the file into the file cache depending on the region.
 *
 * @param data The data pointer of the file being loaded.
 * @param name The ID of the file being loaded.
 * @param cache_mode The region of the file being loaded.
 */
int GV_LoadInit( void *data, int name, int cache_mode )
{
    GV_LOADFUNC func;
    int         ret;

    if ( cache_mode == GV_INIT_NOCACHE )
    {
        func = Loaders[ name / 65536 ];
        if ( func != NULL )
        {
            ret = func( data, name );
            if ( ret <= 0 )
            {
                return ret;
            }
        }
    }
    else
    {
        CACHE *cp;

        if ( FindCache( name ) != NULL || EmptyCache == NULL )
        {
            printf( "id conflict\n" );
            return -1;
        }
        cp = EmptyCache;
        SetCurrentTag( data, name, cache_mode );
        func = Loaders[ name / 65536 ];
        if ( func != NULL )
        {
            ret = func( data, name );
            if ( ret <= 0 )
            {
                cp->id = NEVER_USED;
                return ret;
            }
        }
    }
    return 1;
}
