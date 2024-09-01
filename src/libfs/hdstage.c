#include "libfs.h"
#include "linker.h"
#include "psyq.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "SD/sound.h"

extern int              DG_FrameRate_8009D45C;
extern STAGE_FILE      *gStageFile_800B5288;
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

FS_MOVIE_FILE_TABLE *fs_movie_file_table_8009D50C = NULL;

int sub_80022E50( STAGE_CONFIG *config, CDBIOS_TASK *task )
{
    unsigned char   type;
    STAGE_FILE     *file;
    void           *tmp;
    STAGE_CONFIG   *conf;
    STAGE_CONFIG   *loopConfig;

    file = gStageFile_800B5288;
    if ( gFsSoundCallback_8009D4FC )
    {
        gFsSoundCallback_8009D4FC();
        gFsSoundCallback_8009D4FC = NULL;
    }
    gFsCallback_8009D4F8 = 0;
    type = config->field_2_mode;
    switch ( type )
    {

    case 's':
        switch ( config->field_3_extension )
        {

        case 'b':
            task->field_8_buffer = gOverlayBase_800AB9C8;

            #ifdef DEV_EXE
                task->field_8_buffer = NULL; // the overlay is embedded in the executable in dev variant
            #endif

            break;

        case 'w':
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

        case 'm':
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

        case 'e':
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
        file->field_24 = config->field_4_size;
        file->field_0 = config->field_2_mode;
        return 1;

    case 'r':
        gSaveCache_800B5294 = 1;

    case 'n':
        if ( config->field_4_size <= 0x13FFF )
        {
            file->field_1C = (STAGE_CONFIG *)((int)file->field_18_pConfigEnd1 + 0x19000);
        }
        else
        {
            file->field_1C = file->field_18_pConfigEnd1;
        }
        tmp = file->field_1C;
        task->field_8_buffer = tmp;
        file->field_20_pConfigEnd2 = tmp;
        file->field_24 = config->field_4_size;
        break;

    case 'c':
        if ( file->field_0 != type )
        {
            conf = file->field_14_pConfigStart1;
            if ( conf->field_2_mode == type )
            {
                while ( conf->field_2_mode == 'c' )
                {
                    conf++;
                }
            }
            if (  (conf - 1)->field_3_extension != 0xFF )
            {
                loopConfig = (STAGE_CONFIG *)file->field_10_pContents;
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
            tmp = file->field_18_pConfigEnd1;
            task->field_8_buffer = tmp;
            file->field_20_pConfigEnd2 = tmp;
            file->field_24 = (conf - 1)->field_4_size;
            file->field_14_pConfigStart1 = conf - 1;
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

int Loader_CD_Read_CallBack_helper_800231A8(CDBIOS_TASK *pTask)
{
    STAGE_FILE *pStageFile;
    int result;

    pStageFile = gStageFile_800B5288;
    pStageFile->field_24 -= 2048;

    if (pStageFile->field_24 <= 0)
    {
        if (!sub_80022E50(pStageFile->field_14_pConfigStart1, pTask))
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

        pStageFile->field_14_pConfigStart1++;
        return result;
    }

    if (gFsCallback_8009D4F8)
    {
        pTask->field_8_buffer = gFsCallback_8009D4F8(pTask->field_8_buffer + pTask->field_C * 4);
        return 2;
    }

    pStageFile->field_20_pConfigEnd2 = pTask->field_8_buffer + pTask->field_C * 4;
    return 1;
}

int Loader_CD_Read_CallBack_80023274(CDBIOS_TASK *pTask)
{
    STAGE_FILE   *pStageFile;
    STAGE_HEADER *pHeader;
    STAGE_CONFIG *pConfig;

    pStageFile = gStageFile_800B5288;

    if ( pTask->field_14_sectors_delivered == 0 )
    {
        pStageFile->field_4_pTask = pTask;

        pHeader = (STAGE_HEADER *)pStageFile->field_8_pBuffer;
        pStageFile->field_C_pHeader = pHeader;

        pStageFile->field_10_pContents = pStageFile->field_8_pBuffer + 4;
        pTask->field_18_size = pHeader->field_2_size * 512;
        pTask->field_1C_remaining = pTask->field_18_size - 512;
    }

    if ( --pStageFile->field_C_pHeader->field_0 != 0 )
    {
        return 1;
    }

    pConfig = pStageFile->field_10_pContents;
    while ( ( pConfig->field_2_mode ) != 0 )
    {
        pConfig++;
    }

    pConfig++;

    pStageFile->field_20_pConfigEnd2 = pStageFile->field_18_pConfigEnd1 = pConfig;
    pTask->field_20_callback = &Loader_CD_Read_CallBack_helper_800231A8;
    pStageFile->field_2C_config = pStageFile->field_14_pConfigStart1 = pStageFile->field_10_pContents;

    sub_80022E50( pStageFile->field_14_pConfigStart1, pTask );
    pStageFile->field_14_pConfigStart1++;

    return 2;
}

static inline int get_cache_id( STAGE_CONFIG* pTag )
{
    return ( pTag->field_3_extension - 'a' ) << 16 | pTag->field_0_hash;
}

int Loader_helper_8002336C(STAGE_FILE *pRec, int unused)
{
    STAGE_CONFIG *pNext;
    STAGE_CONFIG *pTag;
    int size;

    if ( pRec->field_28 != 1 )
    {
        pRec->field_28 = 1;
        pRec->field_30_current_ptr = pRec->field_18_pConfigEnd1;
    }

    pTag = pRec->field_2C_config;

    while(1)
    {
        pNext = pRec->field_30_current_ptr + pTag[1].field_4_size;

        if ( pRec->field_14_pConfigStart1[-1].field_2_mode != 'c' || pRec->field_20_pConfigEnd2 >= pNext )
        {
            GV_LoadInit(pRec->field_30_current_ptr + pTag->field_4_size, get_cache_id(pTag), GV_NORMAL_CACHE);
        }
        else
        {
            return 0;
        }

        pTag++;
        pRec->field_2C_config = pTag;

        if (pTag->field_3_extension == 0xFF)
        {
            size =  (int)(pRec->field_30_current_ptr + pTag->field_4_size) - (int)pRec->field_8_pBuffer;
            GV_ResizeMemory(2, pRec->field_8_pBuffer, size);
            break;
        }
    }

    pRec->field_2C_config++;
    return 1;
}

int Loader_helper2_80023460( STAGE_FILE *pStageFile )
{
    STAGE_CONFIG *pConfig;
    STAGE_CONFIG *pLimit;
    int           region;
    STAGE_CONFIG *pConfigCopy;
    int           size;
    void         *pData;

    if ( pStageFile->field_28 != 0 )
    {
        pStageFile->field_28 = 0;
        pStageFile->field_30_current_ptr = pStageFile->field_1C;
        pStageFile->field_34_remaining = pStageFile->field_2C_config->field_4_size;
    }

    pConfig = pStageFile->field_30_current_ptr;

    if ( pStageFile->field_2C_config >= ( pStageFile->field_14_pConfigStart1 - 1 ) )
    {
        pLimit = pStageFile->field_20_pConfigEnd2;
    }
    else
    {
        pLimit = (STAGE_CONFIG *)-1;
    }

    region = ( ( pStageFile->field_2C_config->field_2_mode ) == 'r' ) ? GV_RESIDENT_CACHE : 0;

    while ( pLimit >= ( pConfig + 1 ) )
    {
        pConfigCopy = pConfig;

        if ( pConfig->field_4_size <= 0 )
        {
            printf( "ntag %X size %d\n", (unsigned int)pConfig, pConfig->field_4_size );
            printf( "limit = %X\n", (unsigned int)pLimit );
            printf( "data %X %c, now %X\n",
                                 (unsigned int)pStageFile->field_14_pConfigStart1,
                                 pStageFile->field_14_pConfigStart1->field_2_mode,
                                 (unsigned int)pStageFile->field_20_pConfigEnd2 );
            printf( "init %X %c, now %X\n",
                                 (unsigned int)pStageFile->field_2C_config,
                                 pStageFile->field_2C_config->field_2_mode,
                                 (unsigned int)pStageFile->field_30_current_ptr );
        }

        size = pConfig->field_4_size + 8;

        if ( ( (char *)pConfig + size ) > (char *)pLimit )
        {
            break;
        }

        if ( region != GV_NO_CACHE )
        {
            pData = GV_AllocResidentMemory( pConfig->field_4_size );
            GV_CopyMemory( pConfig + 1, pData, pConfig->field_4_size );
        }
        else
        {
            pData = pConfig + 1;
        }

        GV_LoadInit( pData, ( ( pConfigCopy->field_2_mode_and_ext[0] - 'a' ) << 16 ) | pConfigCopy->field_0_hash, region );
        pStageFile->field_34_remaining -= size;

        if ( pStageFile->field_34_remaining <= 0 )
        {
            pStageFile->field_28 = 2;
            pStageFile->field_2C_config++;
            return -1;
        }

        pConfig = (STAGE_CONFIG *)( (char *)pConfigCopy + size );
        pStageFile->field_30_current_ptr = pConfig;
    }

    return 0;
}

int Loader_80023624( STAGE_FILE *pStageFile )
{
    int status;

    if ( !pStageFile->field_2C_config )
    {
        return 1;
    }

    status = -1;

    while ( ( status < 0 ) &&
            ( pStageFile->field_2C_config <= ( pStageFile->field_14_pConfigStart1 - 1 ) ) )
    {
        switch ( pStageFile->field_2C_config->field_2_mode & 0xff )
        {
        case 'c':
            if ( Loader_helper_8002336C( pStageFile, status ) )
            {
                return 0;
            }

            goto exit;

        case 's':
            pStageFile->field_2C_config++;
            break;

        case '\0':
            return 0;

        default:
            status = Loader_helper2_80023460( pStageFile );
            break;
        }
    }

exit:
    return 1;
}

STAGE_FILE *FS_LoadStageRequest_800236E0( const char *pFileName )
{
    int         sector;     // $s1
    STAGE_FILE *pStageFile; // $s0
    void       *pBuffer;    // $v0

    DG_FrameRate_8009D45C = 1;
    printf( "load %s\n", pFileName );
    gLoaderStartTime_800B528C = VSync( -1 );
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop_80022DCC( (char *)pFileName );
    if ( sector < 0 )
    {
        printf( "NOT FOUND %s\n", pFileName );
    }

    pStageFile = GV_Malloc( sizeof( STAGE_FILE ) ); // 0x38
    if ( !pStageFile )
    {
        printf( "no_mem\n" );
    }

    pBuffer = GV_GetMaxFreeMemory( 2 );

    do
    {
    } while (
        0 ); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    pStageFile->field_8_pBuffer = pBuffer;

    pStageFile->field_28 = 2;
    gStageFile_800B5288 = pStageFile;
    pStageFile->field_0 = 0;
    pStageFile->field_2C_config = 0;
    word_8009D504 = 0;
    CDBIOS_ReadRequest_8002280C( pBuffer, sector, 2048, Loader_CD_Read_CallBack_80023274 );
    return pStageFile;
}

int FS_LoadStageSync_800237C0( STAGE_FILE *pStageFile )
{
    int ret = 0;
    if ( Loader_80023624( pStageFile ) != 0 || CDBIOS_ReadSync_80022854() > 0 )
    {
        ret = 1;
    }
    return ret;
}

void FS_LoadStageComplete_80023804( STAGE_FILE *pStageFile )
{
    int vBlanks; // $v0

    vBlanks = VSync( -1 );
    printf( "load complete time %d\n", vBlanks - gLoaderStartTime_800B528C );
    GV_Free( pStageFile );
    FS_CdStageProgBinFix_80014AAC();
    DG_FrameRate_8009D45C = 2;
}
