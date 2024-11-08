#include "libfs.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "SD/sound.h"

extern int              DG_FrameRate;
extern FS_STAGE_INFO   *gStageInfo_800B5288;
extern int              gLoaderStartTime_800B528C;
extern int              gOverlayBinSize_800B5290;
extern int              gSaveCache_800B5294;
extern char            *gOverlayBase_800AB9C8;

TFsCallback      gFsCallback_8009D4F8 = NULL;
TFsSoundCallback gFsSoundCallback_8009D4FC = NULL;
unsigned short   dword_8009D500[] = {0, 0};
unsigned short   word_8009D504 = 0;
unsigned short   word_8009D506 = 0;
unsigned short   word_8009D508 = 0;

STATIC int FS_80022E50( STAGE_CONFIG *config, CDBIOS_TASK *task )
{
    unsigned char   type;
    FS_STAGE_INFO  *info;
    void           *tmp;
    STAGE_CONFIG   *conf;
    STAGE_CONFIG   *loopConfig;

    info = gStageInfo_800B5288;
    if ( gFsSoundCallback_8009D4FC )
    {
        gFsSoundCallback_8009D4FC();
        gFsSoundCallback_8009D4FC = NULL;
    }
    gFsCallback_8009D4F8 = 0;
    type = config->field_2_mode;

    switch ( type )
    {
    case 's': // .sound
        switch ( config->field_3_extension )
        {
        case 'b': // *.bin
            task->field_8_buffer = gOverlayBase_800AB9C8;
        #ifdef DEV_EXE
            task->field_8_buffer = NULL; // the overlay is embedded in the executable in dev variant
        #endif
            break;

        case 'w': // *.wvx
            if ( dword_8009D500[ word_8009D504 ] != config->field_0_hash )
            {
                task->field_8_buffer = LoadInit( config->field_0_hash );
                gFsSoundCallback_8009D4FC = SD_Unload;
                gFsCallback_8009D4F8 = &SD_WavLoadBuf;
                dword_8009D500[ word_8009D504 ] = config->field_0_hash;
            }
            else
            {
                task->field_8_buffer = 0;
            }
            word_8009D504 += 1;
            break;

        case 'm': // *.mdx
            if ( word_8009D506 != config->field_0_hash )
            {
                task->field_8_buffer = SD_SngDataLoadInit(config->field_0_hash);
                gFsSoundCallback_8009D4FC = SD_80083ED4;
                word_8009D506 = config->field_0_hash;
            }
            else
            {
                task->field_8_buffer = 0;
            }
            break;

        case 'e': // *.efx
            if ( word_8009D508 != config->field_0_hash )
            {
                task->field_8_buffer = SD_80083EE8( config->field_0_hash );
                gFsSoundCallback_8009D4FC = SD_80083ED4;
                word_8009D508 = config->field_0_hash;
            }
            else
            {
                task->field_8_buffer = 0;
            }
            break;
        }
        info->field_24 = config->field_4_size;
        info->field_0 = config->field_2_mode;
        return 1;

    case 'r': // .resident
        gSaveCache_800B5294 = 1;

    case 'n': // .nocache
        if ( config->field_4_size <= 0x13FFF )
        {
            info->field_1C = (STAGE_CONFIG *)((int)info->field_18_pConfigEnd1 + 0x19000);
        }
        else
        {
            info->field_1C = info->field_18_pConfigEnd1;
        }
        tmp = info->field_1C;
        task->field_8_buffer = tmp;
        info->field_20_pConfigEnd2 = tmp;
        info->field_24 = config->field_4_size;
        break;

    case 'c': // .cache
        if ( info->field_0 != type )
        {
            conf = info->field_14_pConfigStart1;
            if ( conf->field_2_mode == type )
            {
                while ( conf->field_2_mode == 'c' )
                {
                    conf++;
                }
            }
            if (  (conf - 1)->field_3_extension != 0xFF )
            {
                loopConfig = (STAGE_CONFIG *)info->field_10_pContents;
                while ( 1 )
                {
                    printf( "%d %c %c %d\n",
                            loopConfig->field_0_hash,
                            loopConfig->field_2_mode,
                            loopConfig->field_3_extension,
                            loopConfig->field_4_size );
                    if ( loopConfig == (conf - 1) )
                    {
                        printf( "HERE !!\n" );
                    }
                    loopConfig++;
                }
            }
            tmp = info->field_18_pConfigEnd1;
            task->field_8_buffer = tmp;
            info->field_20_pConfigEnd2 = tmp;
            info->field_24 = (conf - 1)->field_4_size;
            info->field_14_pConfigStart1 = conf - 1;
        }
        break;

    case 0:
        return 0;

    default:
        printf( "WRONG mode %02X (%c)\n", config->field_2_mode, config->field_2_mode);
        break;
    }

    return 1;
}

STATIC int CDReadCallBack_helper(CDBIOS_TASK *pTask)
{
    FS_STAGE_INFO *info;
    int result;

    info = gStageInfo_800B5288;
    info->field_24 -= 2048;

    if (info->field_24 <= 0)
    {
        if (!FS_80022E50(info->field_14_pConfigStart1, pTask))
        {
            if (pTask->field_1C_remaining > 0)
            {
                printf("!!! WRONG %d !!!\n", pTask->field_1C_remaining);
            }

            result = 0;
        }
        else
        {
            result = 2;
        }

        info->field_14_pConfigStart1++;
        return result;
    }

    if (gFsCallback_8009D4F8)
    {
        pTask->field_8_buffer = gFsCallback_8009D4F8(pTask->field_8_buffer + pTask->field_C * 4);
        return 2;
    }

    info->field_20_pConfigEnd2 = pTask->field_8_buffer + pTask->field_C * 4;
    return 1;
}

STATIC int CDReadCallBack( CDBIOS_TASK *task )
{
    FS_STAGE_INFO *info;
    STAGE_HEADER *pHeader;
    STAGE_CONFIG *pConfig;

    info = gStageInfo_800B5288;

    if ( task->field_14_sectors_delivered == 0 )
    {
        info->field_4_pTask = task;

        pHeader = (STAGE_HEADER *)info->field_8_pBuffer;
        info->field_C_pHeader = pHeader;

        info->field_10_pContents = info->field_8_pBuffer + 4;
        task->field_18_size = pHeader->field_2_size * 512;
        task->field_1C_remaining = task->field_18_size - 512;
    }

    if ( --info->field_C_pHeader->field_0 != 0 )
    {
        return 1;
    }

    pConfig = info->field_10_pContents;
    while ( ( pConfig->field_2_mode ) != 0 )
    {
        pConfig++;
    }

    pConfig++;

    info->field_20_pConfigEnd2 = info->field_18_pConfigEnd1 = pConfig;
    task->field_20_callback = &CDReadCallBack_helper;
    info->field_2C_config = info->field_14_pConfigStart1 = info->field_10_pContents;

    FS_80022E50( info->field_14_pConfigStart1, task );
    info->field_14_pConfigStart1++;

    return 2;
}

static inline int get_cache_id( STAGE_CONFIG *tag )
{
    return ( tag->field_3_extension - 'a' ) << 16 | tag->field_0_hash;
}

STATIC int FS_8002336C( FS_STAGE_INFO *info, int unused )
{
    STAGE_CONFIG *pNext;
    STAGE_CONFIG *pTag;
    int size;

    if ( info->field_28 != 1 )
    {
        info->field_28 = 1;
        info->field_30_current_ptr = info->field_18_pConfigEnd1;
    }

    pTag = info->field_2C_config;

    while(1)
    {
        pNext = info->field_30_current_ptr + pTag[1].field_4_size;

        if ( info->field_14_pConfigStart1[-1].field_2_mode != 'c' ||
             info->field_20_pConfigEnd2 >= pNext )
        {
            GV_LoadInit(info->field_30_current_ptr + pTag->field_4_size, get_cache_id(pTag), GV_REGION_CACHE);
        }
        else
        {
            return 0;
        }

        pTag++;
        info->field_2C_config = pTag;

        if (pTag->field_3_extension == 0xFF)
        {
            size = (int)(info->field_30_current_ptr + pTag->field_4_size) - (int)info->field_8_pBuffer;
            GV_SplitMemory(2, info->field_8_pBuffer, size);
            break;
        }
    }

    info->field_2C_config++;
    return 1;
}

STATIC int FS_80023460( FS_STAGE_INFO *info )
{
    STAGE_CONFIG *pConfig;
    STAGE_CONFIG *pLimit;
    int           region;
    STAGE_CONFIG *pConfigCopy;
    int           size;
    void         *pData;

    if ( info->field_28 != 0 )
    {
        info->field_28 = 0;
        info->field_30_current_ptr = info->field_1C;
        info->field_34_remaining = info->field_2C_config->field_4_size;
    }

    pConfig = info->field_30_current_ptr;

    if ( info->field_2C_config >= ( info->field_14_pConfigStart1 - 1 ) )
    {
        pLimit = info->field_20_pConfigEnd2;
    }
    else
    {
        pLimit = (STAGE_CONFIG *)-1;
    }

    region = ( ( info->field_2C_config->field_2_mode ) == 'r' ) ? GV_REGION_RESIDENT : 0;

    while ( pLimit >= ( pConfig + 1 ) )
    {
        pConfigCopy = pConfig;

        if ( pConfig->field_4_size <= 0 )
        {
            printf( "ntag %X size %d\n", (unsigned int)pConfig, pConfig->field_4_size );
            printf( "limit = %X\n", (unsigned int)pLimit );
            printf( "data %X %c, now %X\n",
                    (unsigned int)info->field_14_pConfigStart1,
                    info->field_14_pConfigStart1->field_2_mode,
                    (unsigned int)info->field_20_pConfigEnd2 );
            printf( "init %X %c, now %X\n",
                    (unsigned int)info->field_2C_config,
                    info->field_2C_config->field_2_mode,
                    (unsigned int)info->field_30_current_ptr );
        }

        size = pConfig->field_4_size + 8;

        if ( ( (char *)pConfig + size ) > (char *)pLimit )
        {
            break;
        }

        if ( region != GV_REGION_NOCACHE )
        {
            pData = GV_AllocResidentMemory( pConfig->field_4_size );
            GV_CopyMemory( pConfig + 1, pData, pConfig->field_4_size );
        }
        else
        {
            pData = pConfig + 1;
        }

        GV_LoadInit( pData, ( ( pConfigCopy->field_2_mode_and_ext[0] - 'a' ) << 16 ) | pConfigCopy->field_0_hash, region );
        info->field_34_remaining -= size;

        if ( info->field_34_remaining <= 0 )
        {
            info->field_28 = 2;
            info->field_2C_config++;
            return -1;
        }

        pConfig = (STAGE_CONFIG *)( (char *)pConfigCopy + size );
        info->field_30_current_ptr = pConfig;
    }

    return 0;
}

STATIC int FS_80023624( FS_STAGE_INFO *info )
{
    int status;

    if ( !info->field_2C_config )
    {
        return 1;
    }

    status = -1;

    while ( ( status < 0 ) &&
            ( info->field_2C_config <= ( info->field_14_pConfigStart1 - 1 ) ) )
    {
        switch ( info->field_2C_config->field_2_mode & 0xff )
        {
        case 'c':
            if ( FS_8002336C( info, status ) )
            {
                return 0;
            }
            goto exit;

        case 's':
            info->field_2C_config++;
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

void *FS_LoadStageRequest( const char *filename )
{
    int              sector;
    FS_STAGE_INFO   *info;
    void            *pBuffer;

    DG_FrameRate = 1;
    printf( "load %s\n", filename );
    gLoaderStartTime_800B528C = VSync( -1 );
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop( (char *)filename );
    if ( sector < 0 )
    {
        printf( "NOT FOUND %s\n", filename );
    }

    info = GV_Malloc( sizeof( FS_STAGE_INFO ) ); // 0x38
    if ( !info )
    {
        printf( "no_mem\n" );
    }

    pBuffer = GV_GetMaxFreeMemory( 2 );

    do {} while ( 0 ); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    info->field_8_pBuffer = pBuffer;

    info->field_28 = 2;
    gStageInfo_800B5288 = info;
    info->field_0 = 0;
    info->field_2C_config = 0;
    word_8009D504 = 0;
    CDBIOS_ReadRequest( pBuffer, sector, 2048, CDReadCallBack );
    return (void *)info;
}

int FS_LoadStageSync( void *info )
{
    int ret = 0;
    if ( FS_80023624( (void *)info ) != 0 || CDBIOS_ReadSync() > 0 )
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
