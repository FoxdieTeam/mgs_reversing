#include "linker.h"
#include "mts/mts_new.h"
#include "data/data/data.h"
#include "libfs.h"
#include "mts/mts_new.h"
#include <LIBCD.H>

extern unsigned char heap_80117000[];
extern FS_FILE_INFO_8009D49C gDirFiles_8009D49C[];
extern int gDiskNum_800ACBF0;

extern const char aDiskD[];
extern const char aIllegalDisk[];
extern const char aPositionEnd[];

extern int dword_8009D4DC;
extern int dword_8009D4E0;
extern int dword_8009D4E4;

extern CDBIOS_TASK cd_bios_task_800B4E58;

int FS_ResetCdFilePosition_80021E2C(void *pHeap)
{
    int disk_num = FS_CdMakePositionTable_80022B5C(pHeap, gDirFiles_8009D49C);
    mts_printf_8008BBA0(aPositionEnd);
    if (disk_num >= 0)
    {
        mts_printf_8008BBA0(aDiskD, disk_num);
        FS_CdStageFileInit_80022D00(pHeap, gDirFiles_8009D49C[0].field_4_sector);
        FS_MovieFileInit_80023860(pHeap, gDirFiles_8009D49C[3].field_4_sector);
    }
    else
    {
        mts_printf_8008BBA0(aIllegalDisk);
    }
    return disk_num;
}

void CDFS_Init_80021EC4()
{
    CDBIOS_Reset_80021F70();
    // TODO: hardcoded pointer
    gDiskNum_800ACBF0 = FS_ResetCdFilePosition_80021E2C((void *)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD_80023F8C();
    FS_StreamTaskInit_80023E1C();
    mts_wait_vbl_800895F4(2);
}

void FS_LoadFileRequest_80021F0C(int dirFile, int startSector, int endSector, void *pBuffer)
{
    CDBIOS_ReadRequest_8002280C(pBuffer, gDirFiles_8009D49C[dirFile].field_4_sector + startSector, endSector, 0);
}

int FS_LoadFileSync_80021F48(void)
{
    return CDBIOS_ReadSync_80022854();
}

void MakeFullPath_80021F68(void)
{

}

int CDBIOS_Reset_80021F70(void)
{
    int retries;
    char param;
  
    CDBIOS_TaskStart_800227A8();
    
    for (retries = 4; retries >= 0; retries--)
    {
        if (CdInit())
        {
            goto success;
        }
    }

    return 0;
    
success:
    param = 0xa0;
    while (!CdControl(CdlSetmode, &param, 0));
      
    mts_wait_vbl_800895F4(3);
    return 1;
}

void sub_80021FE0(void)
{
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
    CdControl(CdlPause, 0, 0);
    dword_8009D4DC = 0;
}

#pragma INCLUDE_ASM("asm/sub_80022024.s")

void nullsub_9_80022088(void)
{

}

#pragma INCLUDE_ASM("asm/CDBIOS_TaskStart_helper_helper_80022090.s")
#pragma INCLUDE_ASM("asm/CDBIOS_TaskStart_helper_80022264.s")
#pragma INCLUDE_ASM("asm/CDBIOS_TaskStart_800227A8.s")

void CDBIOS_ReadRequest_8002280C(void *pHeap, unsigned int startSector, unsigned int sectorSize, void *fnCallBack)
{   
    cd_bios_task_800B4E58.field_8_buffer = pHeap;

    if (sectorSize == 0)
    {
        sectorSize = 0x7fff0000;
    }

    cd_bios_task_800B4E58.field_1C_remaining = (sectorSize + 3) >> 2;
    cd_bios_task_800B4E58.field_18_size = (sectorSize + 3) >> 2;
    cd_bios_task_800B4E58.field_4_sector = startSector;
    cd_bios_task_800B4E58.field_20_callback = fnCallBack;
    cd_bios_task_800B4E58.field_14 = 0;

    dword_8009D4E4 = 0;
    dword_8009D4E0 = 1;
}

int CDBIOS_ReadSync_80022854(void)
{
    return cd_bios_task_800B4E58.field_1C_remaining * 4;
}

void CDBIOS_ForceStop_80022864(void)
{
    if (cd_bios_task_800B4E58.field_0_state != 0)
    {
        dword_8009D4E4 = 1;
    }
}

int CDBIOS_TaskState_80022888(void)
{
    return cd_bios_task_800B4E58.field_0_state;
}

void CDFS_ParseFileName_80022898(char *pOutput, char *pInput, int input_len)
{
    while (input_len > 0)
    {
        *pOutput++ = *pInput++;
        if (!*pInput)
        {
            break;
        }

        --input_len;
        if (*pInput == ';')
        {
            break;
        }
    }
    *pOutput = 0;
}

int FS_CdMakePositionTable_helper2_800228D4(void *pBuffer, int startSector, int sectorSize)
{
    CDBIOS_ReadRequest_8002280C(pBuffer, startSector + 150, sectorSize, 0);

    while (1)
    {
        if (CDBIOS_ReadSync_80022854() <= 0)
        {
            break;
        }
        mts_wait_vbl_800895F4(1);
    }

    return 1;
}

#pragma INCLUDE_ASM("asm/libfs/FS_CdMakePositionTable_helper_helper_80022918.s")
#pragma INCLUDE_ASM("asm/libfs/FS_CdMakePositionTable_helper_8002297C.s")
#pragma INCLUDE_ASM("asm/libfs/FS_CdMakePositionTable_80022B5C.s")
#pragma INCLUDE_ASM("asm/libfs/FS_CdStageFileInit_helper_80022CBC.s")
#pragma INCLUDE_ASM("asm/libfs/FS_CdStageFileInit_80022D00.s")
#pragma INCLUDE_ASM("asm/libfs/FS_CdGetStageFileTop_80022DCC.s")
