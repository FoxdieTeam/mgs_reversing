#include "libfs.h"
#include "datacnf.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"    // for DG_FrameRate
#include "SD/sd_cli.h"

extern FS_STAGE_INFO   *gStageInfo_800B5288;
extern int              gLoaderStartTime_800B528C;
extern int              gOverlayBinSize_800B5290;
extern int              gSaveCache_800B5294;
extern char            *gOverlayBase_800AB9C8;

/*---------------------------------------------------------------------------*/

STATIC TFsCallback      gFsCallback_8009D4F8 = NULL;
STATIC TFsSoundCallback gFsSoundCallback_8009D4FC = NULL;

STATIC unsigned short   dword_8009D500[] = {0, 0};      // *.wvx id
STATIC unsigned short   word_8009D504 = 0;              // *.wvx index
STATIC unsigned short   word_8009D506 = 0;              // *.mdx id
STATIC unsigned short   word_8009D508 = 0;              // *.efx id

STATIC int FS_80022E50( DATACNF_TAG *tag, CDBIOS_TASK *task )
{
    unsigned char   region;
    FS_STAGE_INFO  *info;
    void           *tmp;
    DATACNF_TAG    *tagptr;
    DATACNF_TAG    *looptag;

    info = gStageInfo_800B5288;
    if ( gFsSoundCallback_8009D4FC )
    {
        gFsSoundCallback_8009D4FC();
        gFsSoundCallback_8009D4FC = NULL;
    }
    gFsCallback_8009D4F8 = 0;
    region = tag->mode;

    switch ( region )
    {
    case 's': // .sound
        switch ( tag->ext )
        {
        case 'b': // *.bin
            task->buffer = gOverlayBase_800AB9C8;
        #ifdef DEV_EXE
            task->buffer = NULL; // no overlay in the dev variant
        #endif
            break;

        case 'w': // *.wvx
            if ( dword_8009D500[ word_8009D504 ] != tag->id )
            {
                task->buffer = SD_WavDataLoadInit( tag->id );
                gFsSoundCallback_8009D4FC = SD_WavUnload;
                gFsCallback_8009D4F8 = &SD_WavLoadBuf;
                dword_8009D500[ word_8009D504 ] = tag->id;
            }
            else
            {
                task->buffer = 0;
            }
            word_8009D504 += 1;
            break;

        case 'm': // *.mdx
            if ( word_8009D506 != tag->id )
            {
                task->buffer = SD_SngDataLoadInit(tag->id);
                gFsSoundCallback_8009D4FC = SD_80083ED4;
                word_8009D506 = tag->id;
            }
            else
            {
                task->buffer = 0;
            }
            break;

        case 'e': // *.efx
            if ( word_8009D508 != tag->id )
            {
                task->buffer = SD_SeDataLoadInit( tag->id );
                gFsSoundCallback_8009D4FC = SD_80083ED4;
                word_8009D508 = tag->id;
            }
            else
            {
                task->buffer = 0;
            }
            break;
        }
        info->size = tag->size;
        info->mode = tag->mode;
        return 1;

    case 'r': // .resident
        gSaveCache_800B5294 = 1;

    case 'n': // .nocache
        if ( tag->size <= 0x13FFF )
        {
            info->tag_start2 = (DATACNF_TAG *)((int)info->tag_end1 + 0x19000);
        }
        else
        {
            info->tag_start2 = info->tag_end1;
        }
        tmp = info->tag_start2;
        task->buffer = tmp;
        info->tag_end2 = tmp;
        info->size = tag->size;
        break;

    case 'c': // .cache
        if ( info->mode != region )
        {
            tagptr = info->tag_start1;
            if ( tagptr->mode == region )
            {
                while ( tagptr->mode == 'c' )
                {
                    tagptr++;
                }
            }
            if ( (tagptr - 1)->ext != 0xFF )
            {
                looptag = (DATACNF_TAG *)info->tags;
                while ( 1 )
                {
                    printf( "%d %c %c %d\n",
                            looptag->id,
                            looptag->mode,
                            looptag->ext,
                            looptag->size );
                    if ( looptag == (tagptr - 1) )
                    {
                        printf( "HERE !!\n" );
                    }
                    looptag++;
                }
            }
            tmp = info->tag_end1;
            task->buffer = tmp;
            info->tag_end2 = tmp;
            info->size = (tagptr - 1)->size;
            info->tag_start1 = tagptr - 1;
        }
        break;

    case 0:
        return 0;

    default:
        printf( "WRONG mode %02X (%c)\n", tag->mode, tag->mode);
        break;
    }

    return 1;
}

STATIC int StageLoadCallback_helper(CDBIOS_TASK *task)
{
    FS_STAGE_INFO *info;
    int result;

    info = gStageInfo_800B5288;
    info->size -= FS_SECTOR_SIZE;

    if (info->size <= 0)
    {
        if (!FS_80022E50(info->tag_start1, task))
        {
            if (task->remaining > 0)
            {
                printf("!!! WRONG %d !!!\n", task->remaining);
            }

            result = 0;
        }
        else
        {
            result = 2;
        }

        info->tag_start1++;
        return result;
    }

    if (gFsCallback_8009D4F8)
    {
        task->buffer = gFsCallback_8009D4F8(task->buffer + task->field_C * 4);
        return 2;
    }

    info->tag_end2 = task->buffer + task->field_C * 4;
    return 1;
}

STATIC int StageLoadCallback( CDBIOS_TASK *task )
{
    FS_STAGE_INFO   *info;
    DATACNF         *datacnf;
    DATACNF_TAG     *tag;

    info = gStageInfo_800B5288;

    if ( task->sectors_delivered == 0 )
    {
        info->task = task;

        datacnf = (DATACNF *)info->buffer;
        info->datacnf = datacnf;

        info->tags = (info->buffer + offsetof(DATACNF, tags));
        task->size = datacnf->size * 512;
        task->remaining = task->size - 512;
    }

    if ( --info->datacnf->version != 0 )
    {
        return 1;
    }

    tag = info->tags;
    while ( ( tag->mode ) != 0 )
    {
        tag++;
    }
    tag++;

    info->tag_end2 = info->tag_end1 = tag;
    task->callback = &StageLoadCallback_helper;
    info->tag = info->tag_start1 = info->tags;

    FS_80022E50( info->tag_start1, task );
    info->tag_start1++;

    return 2;
}

static inline int get_cache_id( DATACNF_TAG *tag )
{
    return ( tag->ext - 'a' ) << 16 | tag->id;
}

STATIC int FS_8002336C( FS_STAGE_INFO *info, int unused )
{
    DATACNF_TAG *next_tag;
    DATACNF_TAG *tag;
    int size;

    if ( info->field_28 != 1 )
    {
        info->field_28 = 1;
        info->current_ptr = info->tag_end1;
    }

    tag = info->tag;

    while(1)
    {
        next_tag = info->current_ptr + tag[1].size;

        if ( info->tag_start1[-1].mode != 'c' || info->tag_end2 >= next_tag )
        {
            GV_LoadInit(info->current_ptr + tag->size, get_cache_id(tag), GV_REGION_CACHE);
        }
        else
        {
            return 0;
        }

        tag++;
        info->tag = tag;

        if (tag->ext == 0xFF) /* fake tag */
        {
            size = (int)(info->current_ptr + tag->size) - (int)info->buffer;
            GV_SplitMemory(GV_NORMAL_MEMORY, info->buffer, size);
            break;
        }
    }

    info->tag++;
    return 1;
}

STATIC int FS_80023460( FS_STAGE_INFO *info )
{
    DARFILE_TAG  *ntag;     // "now tag"?
    DARFILE_TAG  *limit;
    int           region;
    DARFILE_TAG  *ntag2;    // todo: rename
    int           size;
    void         *ptr;

    if ( info->field_28 != 0 )
    {
        info->field_28 = 0;
        info->current_ptr = info->tag_start2;
        info->remaining = info->tag->size;
    }

    ntag = info->current_ptr;

    if ( info->tag >= ( info->tag_start1 - 1 ) )
    {
        limit = (DARFILE_TAG *)info->tag_end2;
    }
    else
    {
        limit = (DARFILE_TAG *)-1;
    }

    region = ( ( info->tag->mode ) == 'r' ) ? GV_REGION_RESIDENT : GV_REGION_NOCACHE;

    while ( limit >= ( ntag + 1 ) )
    {
        ntag2 = ntag;

        if ( ntag->size <= 0 )
        {
            printf( "ntag %X size %d\n", (unsigned int)ntag, ntag->size );
            printf( "limit = %X\n", (unsigned int)limit );
            printf( "data %X %c, now %X\n",
                    (unsigned int)info->tag_start1, info->tag_start1->mode,
                    (unsigned int)info->tag_end2 );
            printf( "init %X %c, now %X\n",
                    (unsigned int)info->tag, info->tag->mode,
                    (unsigned int)info->current_ptr );
        }

        size = ntag->size + 8;

        if ( ( (char *)ntag + size ) > (char *)limit )
        {
            break;
        }

        if ( region != GV_REGION_NOCACHE )
        {
            ptr = GV_AllocResidentMemory( ntag->size );
            GV_CopyMemory( ntag + 1, ptr, ntag->size );
        }
        else
        {
            ptr = ntag + 1;
        }

        GV_LoadInit( ptr, ( ( ntag2->ext - 'a' ) << 16 ) | ntag2->id, region );
        info->remaining -= size;

        if ( info->remaining <= 0 )
        {
            info->field_28 = 2;
            info->tag++;
            return -1;
        }

        ntag = (DARFILE_TAG *)( (char *)ntag2 + size );
        info->current_ptr = ntag;
    }

    return 0;
}

STATIC int FS_80023624( FS_STAGE_INFO *info )
{
    int status;

    if ( !info->tag )
    {
        return 1;
    }

    status = -1;

    while ( ( status < 0 ) && ( info->tag <= ( info->tag_start1 - 1 ) ) )
    {
        switch ( info->tag->mode & 0xff )
        {
        case 'c': // cache
            if ( FS_8002336C( info, status ) )
            {
                return 0;
            }
            goto exit;

        case 's': // sound
            info->tag++;
            break;

        case '\0':
            return 0;

        default:
            status = FS_80023460( info );
            break;
        }
    }

exit:
    return 1;
}

/*---------------------------------------------------------------------------*/

void *FS_LoadStageRequest( const char *dirname )
{
    int             sector;
    FS_STAGE_INFO  *info;
    void           *buffer;

    DG_FrameRate = 1;
    printf( "load %s\n", dirname );
    gLoaderStartTime_800B528C = VSync( -1 );
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop( (char *)dirname );
    if ( sector < 0 )
    {
        printf( "NOT FOUND %s\n", dirname );
    }

    info = GV_Malloc( sizeof( FS_STAGE_INFO ) );
    if ( !info )
    {
        printf( "no_mem\n" );
    }

    buffer = GV_GetMaxFreeMemory( GV_NORMAL_MEMORY );

    do {} while ( 0 ); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    info->buffer = buffer;

    info->field_28 = 2;
    gStageInfo_800B5288 = info;
    info->mode = 0;
    info->tag = NULL;
    word_8009D504 = 0;
    CDBIOS_ReadRequest( buffer, sector, FS_SECTOR_SIZE, StageLoadCallback );

    return (void *)info;
}

int FS_LoadStageSync( void *info )
{
    int ret = 0;
    if ( FS_80023624( (FS_STAGE_INFO *)info ) != 0 || CDBIOS_ReadSync() > 0 )
    {
        ret = 1;
    }
    return ret;
}

void FS_LoadStageComplete( void *info )
{
    int vblanks;

    vblanks = VSync( -1 );
    printf( "load complete time %d\n", vblanks - gLoaderStartTime_800B528C );
    GV_Free( info );
    FS_CdStageProgBinFix();
    DG_FrameRate = 2;
}
