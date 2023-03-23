#include "libfs.h"
#include "linker.h"
#include "psyq.h"
#include "unknown.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "SD/sd.h"

extern int              DG_FrameRate_8009D45C;
extern STAGE_FILE      *gStageFile_800B5288;
extern int              gLoaderStartTime_800B528C;
extern int              gOverlayBinSize_800B5290;
extern int              gSaveCache_800B5294;
extern unsigned short   word_8009D504;
extern unsigned short   dword_8009D500[];
extern unsigned short   word_8009D506;
extern unsigned short   word_8009D508;
extern char            *gOverlayBase_800AB9C8;
extern TFsCallback      gFsCallback_8009D4F8;
extern TFsSoundCallback gFsSoundCallback_8009D4FC;

extern const char aLoadCompleteTi[]; // "load complete time %d\n";
extern const char aLoadS[];          // = "load %s\n";
extern const char aNotFoundS[];      // = "NOT FOUND %s\n";
extern const char aNo2[];            // = "no_mem\n";
extern const char aNtagXSizeD[];     // = "ntag %X size %d\n"
extern const char aLimitX[];         // = "limit = %X\n"
extern const char aDataXCNowX[];     // = "data %X %c, now %X\n"
extern const char aInitXCNowX[];     // = "init %X %c, now %X\n"
extern const char aWrongD[];         // = "!!! WRONG %d !!!\n"
extern const char aDCCD[];           // = "%d %c %c %d\n"
extern const char aHere[];           // = "HERE !!\n"
extern const char aWrongMode02xC;    // = "WRONG mode %02X (%c)\n"

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
            break;

        case 'w':
            if ( dword_8009D500[ word_8009D504 ] != config->field_0_hash )
            {
                task->field_8_buffer = LoadInit_80083F08( config->field_0_hash );
                gFsSoundCallback_8009D4FC = SD_Unload_800843BC;
                gFsCallback_8009D4F8 = &SD_WavLoadBuf_800841D4;
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
                task->field_8_buffer = SD_SngDataLoadInit_80083E8C(config->field_0_hash);
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
                    mts_printf_8008BBA0( aDCCD,
                                         loopConfig->field_0_hash,
                                         loopConfig->field_2_mode,
                                         loopConfig->field_3_extension,
                                         loopConfig->field_4_size );
                    if ( loopConfig == (conf - 1) )
                    {
                        mts_printf_8008BBA0( aHere );
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
        mts_printf_8008BBA0( &aWrongMode02xC, config->field_2_mode, config->field_2_mode);
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
                mts_printf_8008BBA0(aWrongD, pTask->field_1C_remaining);
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

#pragma INCLUDE_ASM( "asm/libfs/Loader_helper_8002336C.s" )

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
            mts_printf_8008BBA0( aNtagXSizeD, pConfig, pConfig->field_4_size );
            mts_printf_8008BBA0( aLimitX, pLimit );
            mts_printf_8008BBA0( aDataXCNowX,
                                 pStageFile->field_14_pConfigStart1,
                                 pStageFile->field_14_pConfigStart1->field_2_mode,
                                 pStageFile->field_20_pConfigEnd2 );
            mts_printf_8008BBA0( aInitXCNowX,
                                 pStageFile->field_2C_config,
                                 pStageFile->field_2C_config->field_2_mode,
                                 pStageFile->field_30_current_ptr );
        }

        size = pConfig->field_4_size + 8;

        if ( ( (char *)pConfig + size ) > (char *)pLimit )
        {
            break;
        }

        if ( region != GV_NO_CACHE )
        {
            pData = GV_AllocResidentMemory_800163D8( pConfig->field_4_size );
            GV_CopyMemory_800160D8( pConfig + 1, pData, pConfig->field_4_size );
        }
        else
        {
            pData = pConfig + 1;
        }

        GV_LoadInit_800155BC(
            pData, ( ( pConfigCopy->field_2_mode_and_ext[0] - 'a' ) << 16 ) | pConfigCopy->field_0_hash, region );
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
    mts_printf_8008BBA0( aLoadS, pFileName );
    gLoaderStartTime_800B528C = VSync_80098108( -1 );
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop_80022DCC( (char *)pFileName );
    if ( sector < 0 )
    {
        mts_printf_8008BBA0( aNotFoundS, pFileName );
    }

    pStageFile = GV_Malloc_8001620C( sizeof( STAGE_FILE ) ); // 0x38
    if ( !pStageFile )
    {
        mts_printf_8008BBA0( aNo2 );
    }

    pBuffer = GV_GetMaxFreeMemory_8001627C( 2 );

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

    vBlanks = VSync_80098108( -1 );
    mts_printf_8008BBA0( aLoadCompleteTi, vBlanks - gLoaderStartTime_800B528C );
    GV_Free_80016230( pStageFile );
    FS_CdStageProgBinFix_80014AAC();
    DG_FrameRate_8009D45C = 2;
}
