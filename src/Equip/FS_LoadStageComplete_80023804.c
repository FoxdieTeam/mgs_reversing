#include "linker.h"
#include "unknown.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"

struct Loader_Rec_2
{
    char field_0;
    char field_1;
};

struct Loader_Record // TODO: Share in a header
{
    int field_0;
    int field_4; // cnf count?
    struct Loader_Rec_2 *field_8_p2Alloc;
    int field_C; // str ptr?
    int field_10;
    int field_14; // last size?
    int field_18; // state ?
    int field_1C; // cnf ptr?
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
};

extern const char aLoadCompleteTi[]; // "load complete time %d\n";

void FS_CdStageProgBinFix_80014AAC(void);

extern int DG_FrameRate_8009D45C;

struct Loader_Record *SECTION(".gLoaderRec_800B5288") gLoaderRec_800B5288;
int SECTION(".gLoaderRec_800B5288") gLoaderStartTime_800B528C;
int SECTION(".gLoaderRec_800B5288") gOverlayBinSize_800B5290;
int SECTION(".gLoaderRec_800B5288") gSaveCache_800B5294;

int Loader_80023624(struct Loader_Record *pRec);
int CDBIOS_ReadSync_80022854(void);

extern const char aLoadS[];     // = "load %s\n";
extern const char aNotFoundS[]; // = "NOT FOUND %s\n";
extern const char aNo2[];       // = "no_mem\n";

extern short word_8009D504;

int FS_CdGetStageFileTop_80022DCC(char *pFileName);
void *GV_GetMaxFreeMemory_8001627C(int which);

void CDBIOS_ReadRequest_8002280C(void *pHeap, int startSector, int sectorSize, void *fnCallBack);
int Loader_CD_Read_CallBack_80023274(int *a1);



struct Loader_Record *FS_LoadStageRequest_800236E0(const char *pFileName)
{
    int sector;                // $s1
    struct Loader_Record *pLoaderRec; // $s0
    struct Loader_Rec_2 *p2Alloc;     // $v0

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
    do { } while (0); // TODO: Figure out what this was, a compiled out macro, checking mem alloc didn't fail ?

    pLoaderRec->field_8_p2Alloc = p2Alloc;

    pLoaderRec->field_28 = 2;
    gLoaderRec_800B5288 = pLoaderRec;
    pLoaderRec->field_0 = 0;
    pLoaderRec->field_2C = 0;
    word_8009D504 = 0;
    CDBIOS_ReadRequest_8002280C(p2Alloc, sector, 2048, Loader_CD_Read_CallBack_80023274);
    return pLoaderRec;
}


static inline struct Loader_Rec_2* DoIt( struct Loader_Record *pLoaderRec)
{
    struct Loader_Rec_2* rec;
    rec = pLoaderRec->field_8_p2Alloc;
    return rec;
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
