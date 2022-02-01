#include "linker.h"

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

int VSync_80098108(int);
extern void mts_printf_8008BBA0(const char *, ...);
extern void GV_Free_80016230(void *ptr);
void FS_Null_80014AAC(void);

extern int DG_FrameRate_8009D45C;

struct Loader_Record *SECTION(".gLoaderRec_800B5288") gLoaderRec_800B5288;
int SECTION(".gLoaderRec_800B5288") gLoaderStartTime_800B528C;

int Loader_80023624(struct Loader_Record *pRec);
int CDFS_SectorsLeft_80022854(void);

int Loader_Act_helper_800237C0(struct Loader_Record *pRec)
{
    int ret = 0;
    if (Loader_80023624(pRec) != 0 || CDFS_SectorsLeft_80022854() > 0)
    {
        ret = 1;
    }
    return ret;
}

void Loader_End_80023804(struct Loader_Record *pFileName)
{
    int vBlanks; // $v0

    vBlanks = VSync_80098108(-1);
    mts_printf_8008BBA0(aLoadCompleteTi, vBlanks - gLoaderStartTime_800B528C);
    GV_Free_80016230(pFileName);
    FS_Null_80014AAC();
    DG_FrameRate_8009D45C = 2;
}
