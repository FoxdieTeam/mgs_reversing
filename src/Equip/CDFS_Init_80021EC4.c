#include "linker.h"
#include "mts_new.h"

void CDBIOS_Reset_80021F70(void);
void FS_StreamCD_80023F8C(void);
void FS_StreamTaskInit_80023E1C(void);
int FS_ResetCdFilePosition_80021E2C(void*);

extern unsigned char heap_80117000[];

int SECTION(".gDiskNum_800ACBF0") gDiskNum_800ACBF0;

void CDFS_Init_80021EC4()
{
    CDBIOS_Reset_80021F70();
    gDiskNum_800ACBF0 = FS_ResetCdFilePosition_80021E2C((void*)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD_80023F8C();
    FS_StreamTaskInit_80023E1C();
    mts_wait_vbl_800895F4(2);
}
