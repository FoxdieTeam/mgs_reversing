#include "linker.h"
#include "unknown.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"
#include "libfs.h"

extern int                   DG_FrameRate_8009D45C;
extern struct Loader_Record *gLoaderRec_800B5288;
extern int                   gLoaderStartTime_800B528C;
extern int                   gOverlayBinSize_800B5290;
extern int                   gSaveCache_800B5294;
extern short                 word_8009D504;

extern const char aLoadCompleteTi[]; // "load complete time %d\n";
extern const char aLoadS[];          // = "load %s\n";
extern const char aNotFoundS[];      // = "NOT FOUND %s\n";
extern const char aNo2[];            // = "no_mem\n";

#pragma INCLUDE_ASM("asm/libfs/sub_80022E50.s")
#pragma INCLUDE_ASM("asm/libfs/Loader_CD_Read_CallBack_helper_800231A8.s")
#pragma INCLUDE_ASM("asm/libfs/Loader_CD_Read_CallBack_80023274.s")
#pragma INCLUDE_ASM("asm/libfs/Loader_helper_8002336C.s")
#pragma INCLUDE_ASM("asm/libfs/Loader_helper2_80023460.s")

int Loader_80023624(struct Loader_Record *pRec)
{
    int status;

    if (pRec->field_2C == 0)
    {
        return 1;
    }

    status = -1;

    while ((status < 0) && (pRec->field_2C <= (pRec->field_14 - 8)))
    {
        switch(pRec->field_2C[2])
        {
        case 'c':
            if (Loader_helper_8002336C(pRec, status))
            {
                return 0;
            }

            goto exit;

        case 's':
            pRec->field_2C += 8;
            break;

        case '\0':
            return 0;

        default:
            status = Loader_helper2_80023460(pRec, status);
            break;
        }
    }

exit:
    return 1;
}

struct Loader_Record *FS_LoadStageRequest_800236E0(const char *pFileName)
{
    int                   sector;     // $s1
    struct Loader_Record *pLoaderRec; // $s0
    struct Loader_Rec_2  *p2Alloc;    // $v0

    DG_FrameRate_8009D45C = 1;
    mts_printf_8008BBA0(aLoadS, pFileName);
    gLoaderStartTime_800B528C = VSync_80098108(-1);
    gSaveCache_800B5294 = 0;
    sector = FS_CdGetStageFileTop_80022DCC((char *)pFileName);
    if (sector < 0)
    {
        mts_printf_8008BBA0(aNotFoundS, pFileName);
    }
    pLoaderRec = (struct Loader_Record *)GV_Malloc_8001620C(sizeof(struct Loader_Record)); // 0x38
    if (!pLoaderRec)
    {
        mts_printf_8008BBA0(aNo2);
    }
    p2Alloc = (struct Loader_Rec_2 *)GV_GetMaxFreeMemory_8001627C(2);
    do
    {
    } while (0); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    pLoaderRec->field_8_p2Alloc = p2Alloc;

    pLoaderRec->field_28 = 2;
    gLoaderRec_800B5288 = pLoaderRec;
    pLoaderRec->field_0 = 0;
    pLoaderRec->field_2C = 0;
    word_8009D504 = 0;
    CDBIOS_ReadRequest_8002280C(p2Alloc, sector, 2048, Loader_CD_Read_CallBack_80023274);
    return pLoaderRec;
}

int FS_LoadStageSync_800237C0(struct Loader_Record *pRec)
{
    int ret = 0;
    if (Loader_80023624(pRec) != 0 || CDBIOS_ReadSync_80022854() > 0)
    {
        ret = 1;
    }
    return ret;
}

void FS_LoadStageComplete_80023804(struct Loader_Record *pFileName)
{
    int vBlanks; // $v0

    vBlanks = VSync_80098108(-1);
    mts_printf_8008BBA0(aLoadCompleteTi, vBlanks - gLoaderStartTime_800B528C);
    GV_Free_80016230(pFileName);
    FS_CdStageProgBinFix_80014AAC();
    DG_FrameRate_8009D45C = 2;
}
