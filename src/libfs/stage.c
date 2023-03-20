#include "linker.h"
#include "unknown.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"
#include "libfs.h"

extern int         DG_FrameRate_8009D45C;
extern STAGE_FILE *gStageFile_800B5288;
extern int         gLoaderStartTime_800B528C;
extern int         gOverlayBinSize_800B5290;
extern int         gSaveCache_800B5294;
extern short       word_8009D504;

extern const char aLoadCompleteTi[]; // "load complete time %d\n";
extern const char aLoadS[];          // = "load %s\n";
extern const char aNotFoundS[];      // = "NOT FOUND %s\n";
extern const char aNo2[];            // = "no_mem\n";

#pragma INCLUDE_ASM("asm/libfs/sub_80022E50.s")
void sub_80022E50(STAGE_CONFIG *pConfig, CDBIOS_TASK *pTask);

#pragma INCLUDE_ASM("asm/libfs/Loader_CD_Read_CallBack_helper_800231A8.s")
int Loader_CD_Read_CallBack_helper_800231A8(CDBIOS_TASK *pTask);

int Loader_CD_Read_CallBack_80023274(CDBIOS_TASK *pTask)
{
    STAGE_FILE *pStageFile;
    STAGE_HEADER *pHeader;
    STAGE_CONFIG *pConfig;

    pStageFile = gStageFile_800B5288;

    if (pTask->field_14_sectors_delivered == 0)
    {
        pStageFile->field_4_pTask = pTask;

        pHeader = (STAGE_HEADER *)pStageFile->field_8_pBuffer;
        pStageFile->field_C_pHeader = pHeader;

        pStageFile->field_10_pContents = pStageFile->field_8_pBuffer + 4;
        pTask->field_18_size = pHeader->field_2_size * 512;
        pTask->field_1C_remaining = pTask->field_18_size - 512;
    }

    if (--pStageFile->field_C_pHeader->field_0 != 0)
    {
        return 1;
    }

    pConfig = pStageFile->field_10_pContents;
    while (pConfig->field_2_mode != 0)
    {
        pConfig++;
    }

    pConfig++;

    pStageFile->field_20_pConfigEnd2 = pStageFile->field_18_pConfigEnd1 = pConfig;
    pTask->field_20_callback = &Loader_CD_Read_CallBack_helper_800231A8;
    pStageFile->field_2C_config = pStageFile->field_14_pConfigStart1 = pStageFile->field_10_pContents;

    sub_80022E50(pStageFile->field_14_pConfigStart1, pTask);
    pStageFile->field_14_pConfigStart1++;

    return 2;
}

#pragma INCLUDE_ASM("asm/libfs/Loader_helper_8002336C.s")
#pragma INCLUDE_ASM("asm/libfs/Loader_helper2_80023460.s")

int Loader_80023624(STAGE_FILE *pStageFile)
{
    int status;

    if (pStageFile->field_2C_config == 0)
    {
        return 1;
    }

    status = -1;

    while ((status < 0) && (pStageFile->field_2C_config <= (pStageFile->field_14_pConfigStart1 - 1)))
    {
        switch(pStageFile->field_2C_config->field_2_mode)
        {
        case 'c':
            if (Loader_helper_8002336C(pStageFile, status))
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
            status = Loader_helper2_80023460(pStageFile, status);
            break;
        }
    }

exit:
    return 1;
}

STAGE_FILE * FS_LoadStageRequest_800236E0(const char *pFileName)
{
    int         sector;     // $s1
    STAGE_FILE *pStageFile; // $s0
    void       *pBuffer;    // $v0

    DG_FrameRate_8009D45C = 1;
    mts_printf_8008BBA0(aLoadS, pFileName);
    gLoaderStartTime_800B528C = VSync_80098108(-1);
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop_80022DCC((char *)pFileName);
    if (sector < 0)
    {
        mts_printf_8008BBA0(aNotFoundS, pFileName);
    }

    pStageFile = GV_Malloc_8001620C(sizeof(STAGE_FILE)); // 0x38
    if (!pStageFile)
    {
        mts_printf_8008BBA0(aNo2);
    }

    pBuffer = GV_GetMaxFreeMemory_8001627C(2);

    do
    {
    } while (0); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    pStageFile->field_8_pBuffer = pBuffer;

    pStageFile->field_28 = 2;
    gStageFile_800B5288 = pStageFile;
    pStageFile->field_0 = 0;
    pStageFile->field_2C_config = 0;
    word_8009D504 = 0;
    CDBIOS_ReadRequest_8002280C(pBuffer, sector, 2048, Loader_CD_Read_CallBack_80023274);
    return pStageFile;
}

int FS_LoadStageSync_800237C0(STAGE_FILE *pStageFile)
{
    int ret = 0;
    if (Loader_80023624(pStageFile) != 0 || CDBIOS_ReadSync_80022854() > 0)
    {
        ret = 1;
    }
    return ret;
}

void FS_LoadStageComplete_80023804(STAGE_FILE *pStageFile)
{
    int vBlanks; // $v0

    vBlanks = VSync_80098108(-1);
    mts_printf_8008BBA0(aLoadCompleteTi, vBlanks - gLoaderStartTime_800B528C);
    GV_Free_80016230(pStageFile);
    FS_CdStageProgBinFix_80014AAC();
    DG_FrameRate_8009D45C = 2;
}
