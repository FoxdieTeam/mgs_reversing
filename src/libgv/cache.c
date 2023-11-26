#include "libgv.h"
#include "mts/mts_new.h"

#define MAX_TAGS 128
#define RESIDENT_REGION_FLAG 0x1000000

/**bss***********************************************************************************************/
extern CacheSystems    GV_CacheSystem_800ACEF0;
extern TFileExtHandler gFileExtHandlers_800ACE80[MAX_FILE_HANDLERS];
/***************************************************************************************************/

/***$gp***************************************************************/
extern LibGV_FileRecord *GV_CurrentTag_800AB930;
LibGV_FileRecord        *SECTION(".sbss") GV_CurrentTag_800AB930;

extern LibGV_FileRecord *GV_ResidentFileRecords_800AB934;
LibGV_FileRecord        *SECTION(".sbss") GV_ResidentFileRecords_800AB934;

extern int N_ResidentFileRecords_800AB938;
int        SECTION(".sbss") N_ResidentFileRecords_800AB938;
/********************************************************************/

// searches for a cached file from the cache system with a given ID
LibGV_FileRecord *GV_FileCacheFind_80015240(int id)
{

    int               i;
    int               pos;
    int               cacheID;
    int               remainder;
    LibGV_FileRecord *tag;
    LibGV_FileRecord *selectedTag;

    selectedTag = 0;
    pos = id % 0x80;
    tag = &GV_CacheSystem_800ACEF0.tags[pos];

    remainder = 0x80 - pos;
    i = 0x80;

    while (i > 0)
    {
        cacheID = tag->mId & 0xFFFFFF;

        if (!cacheID)
        {
            if (selectedTag == 0)
            {
                selectedTag = tag;
            }
            break;
        }
        else
        {
            remainder--;

            if (cacheID == id)
            {
                return tag;
            }
            else
            {
                tag++;
                if (!remainder)
                {
                    tag = GV_CacheSystem_800ACEF0.tags;
                }
                i--;
            }
        }
    }

    GV_CurrentTag_800AB930 = selectedTag;
    return 0;
}

// returns a file's cache id using the file id and ext id.
int GV_CacheID_800152DC(int hashedFileName, int extID)
{
    extID -= 'a';

    if (extID > 0x19)
    {
        extID += 0x20;
    }

    return hashedFileName + (extID << 16);
}

// takes the file name to create strcode which is used
// to call cacheID along with the ext id.
int GV_CacheID2_800152FC(const char *fileName, int extID)
{
    int hashedFileName = GV_StrCode_80016CCC(fileName);
    return GV_CacheID_800152DC(hashedFileName, extID);
}

// iterates the string to grab the filename up to the period.
// uses the first chracter after the period as the file ext id.
// calls CacheID2 with this information.
int GV_CacheID3_8001532C(char *string)
{
    char  filename[32];
    char *pFilename = filename;
    char  pIterator = *string++;

    if (pIterator == '.')
    {
        *filename = 0;
    }
    else
    {
    LOOP:
        *pFilename++ = pIterator;
        if (pIterator)
        {
            pIterator = *string++;
            if (pIterator != '.')
            {
                goto LOOP;
            }
            *pFilename = 0;
        }
    }
    return GV_CacheID2_800152FC(filename, (int)*string);
}

// returns cached file for a given id
void *GV_GetCache_8001538C(int fileNameHashed)
{
    LibGV_FileRecord *pRecord = GV_FileCacheFind_80015240(fileNameHashed);
    if (pRecord)
    {
        return pRecord->mFileBuffer;
    }

    return 0;
}

// sets currently active cached file if it can be found
int GV_SetCache_800153C0(int id, void *buf)
{
    if (!GV_FileCacheFind_80015240(id))
    {
        if (GV_CurrentTag_800AB930)
        {
            GV_CurrentTag_800AB930->mId = id;
            GV_CurrentTag_800AB930->mFileBuffer = buf;
            return 0;
        }
    }

    return -1;
}

// sets the loadfunc in the loader table. It is mapped to a char id
void GV_SetLoader_80015418(int fileExtChar, TFileExtHandler pFn)
{
    const int idx = fileExtChar - 'a';
    gFileExtHandlers_800ACE80[idx] = pFn;
}

// initialises the loader table by setting all values to 0
void GV_InitLoader_80015434()
{
    TFileExtHandler *pExtIter;
    int              i;

    pExtIter = &gFileExtHandlers_800ACE80[0];
    for (i = MAX_FILE_HANDLERS; i > 0; i--)
    {
        *pExtIter = 0;
        pExtIter++;
    }
}

// initialises cache system by setting all entries to 0
// also sets the resident caches info to 0 as well
void GV_InitCacheSystem_80015458()
{
    int               i;
    LibGV_FileRecord *tag = GV_CacheSystem_800ACEF0.tags;

    for (i = MAX_TAGS; i > 0; i--)
    {
        tag->mId = 0;
        tag++;
    }

    GV_ResidentFileRecords_800AB934 = 0;
    N_ResidentFileRecords_800AB938 = 0;
}

// GV_InitResidentCacheSystem?
// Iterates all the records in the cache system and checks the
// region flag to see if it should be placed in the resident area
void GV_ResidentFileCache_80015484()
{
    int               i;
    int               n_resident_tags;
    LibGV_FileRecord *tag;
    LibGV_FileRecord *temp_tag;
    tag = (LibGV_FileRecord *)&GV_CacheSystem_800ACEF0.tags;
    n_resident_tags = 0;

    for (i = MAX_TAGS; i > 0; i--)
    {

        if (tag->mId & RESIDENT_REGION_FLAG)
        {
            n_resident_tags++;
        }
        tag++;
    }

    temp_tag = (LibGV_FileRecord *)&GV_CacheSystem_800ACEF0.tags;

    if (n_resident_tags)
    {
        LibGV_FileRecord *resident_tag = GV_AllocResidentMemory_800163D8(n_resident_tags * sizeof(LibGV_FileRecord));
        tag = temp_tag;

        GV_ResidentFileRecords_800AB934 = resident_tag;
        N_ResidentFileRecords_800AB938 = n_resident_tags;

        for (i = MAX_TAGS; i > 0; i--)
        {
            if (tag->mId & RESIDENT_REGION_FLAG)
            {
                *resident_tag = *tag;
                resident_tag++;
            }
            tag++;
        }
    }
}

// iterates through all entries in the cache system and
// sets all ID's to 0. Then iterates through all resident
// file records and
void GV_FreeCacheSystem_80015540()
{
    int               i;
    LibGV_FileRecord *tag;
    tag = GV_CacheSystem_800ACEF0.tags;

    for (i = MAX_TAGS; i > 0; i--)
    {
        tag->mId = 0;
        tag++;
    }

    tag = GV_ResidentFileRecords_800AB934;

    if (!tag)
        return;

    for (i = N_ResidentFileRecords_800AB938; i > 0; i--)
    {
        GV_SetCache_800153C0(tag->mId, tag->mFileBuffer);
        tag++;
    }
}

// inline function to set tag for a specific region, was required to
// match below function, should be moved to libgv.h
static inline void GV_SetCurrentTag(int id, int region)
{
    if (region != GV_NORMAL_CACHE)
    {
        id |= RESIDENT_REGION_FLAG;
    }

    GV_CurrentTag_800AB930->mId = id;
}

// inline function to return the file handler function for a given ID
static inline TFileExtHandler GV_GetLoadFunc(int id)
{
    TFileExtHandler *lt = gFileExtHandlers_800ACE80;
    if (id < 0)
        id += 0xFFFF;
    return lt[id >> 16];
}

// loads given init function
int GV_LoadInit_800155BC(void *buf, int id, int region)
{
    int               ret;
    TFileExtHandler   func;
    LibGV_FileRecord *current_tag;

    if (region == GV_NO_CACHE)
    {
        func = GV_GetLoadFunc(id);
        if (func)
        {
            ret = func(buf, id);
            if (ret <= 0)
                return ret;
        }
    }
    else
    {
        if (GV_FileCacheFind_80015240(id) || !GV_CurrentTag_800AB930)
        {
            printf("id conflict\n");
            return -1;
        }

        current_tag = GV_CurrentTag_800AB930;

        GV_SetCurrentTag(id, region);
        current_tag->mFileBuffer = buf;

        func = GV_GetLoadFunc(id);
        if (func)
        {
            ret = func(buf, id);
            if (ret > 0)
                return 1;
            current_tag->mId = 0;
            return ret;
        }
    }

    return 1;
}
