#include "linker.h"
#include "mts/mts_new.h"
#include "data/data/data.h"
#include "libfs.h"
#include "mts/mts_new.h"
#include "psyq.h"
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
    unsigned char params[8];
  
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
    params[0] = CdlModeSpeed | CdlModeSize1;
    while (!CdControl(CdlSetmode, params, 0));
      
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

void sub_80022024(void)
{   
    if (cd_bios_task_800B4E58.field_10_ticks == 0)
    {
        cd_bios_task_800B4E58.field_10_ticks = mts_get_tick_count_8008BBB0();   
    }

    dword_8009D4DC = 3;
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
}

void nullsub_9_80022088(void)
{

}

#pragma INCLUDE_ASM("asm/CDBIOS_TaskStart_helper_helper_80022090.s") // 468 bytes
#pragma INCLUDE_ASM("asm/CDBIOS_TaskStart_helper_80022264.s") // 1348 bytes

extern struct Loader_Record *gLoaderRec_800B5288;

void CDBIOS_TaskStart_800227A8(void)
{
    cd_bios_task_800B4E58.field_0_state = 0;

    dword_8009D4DC = -1;
    dword_8009D4E4 = 0;
    
    mts_set_stack_check_8008B648(10, (unsigned int *)&gLoaderRec_800B5288, 1024);
    mts_sta_tsk_8008B47C(10, &CDBIOS_TaskStart_helper_80022264, &gLoaderRec_800B5288);
}

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

FS_FILE_INFO_8009D49C * FS_CdMakePositionTable_helper_helper_80022918(char *pFileName, FS_FILE_INFO_8009D49C *pFile)
{
    FS_FILE_INFO_8009D49C *file;

    for (file = pFile; file->pDatName; file++)
    {
        if (!strcmp_8008E6F8(pFileName, file->pDatName))
        {
            return file;
        }
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/libfs/FS_CdMakePositionTable_helper_8002297C.s") // 480 bytes
#pragma INCLUDE_ASM("asm/libfs/FS_CdMakePositionTable_80022B5C.s") // 352 bytes
#pragma INCLUDE_ASM("asm/libfs/FS_CdStageFileInit_helper_80022CBC.s") // 68 bytes

extern FS_FILE_TABLE fs_file_table_8009D4E8;
extern const char aXXD[]; // = "%X %X %d\n"

void FS_CdStageFileInit_80022D00(void *pHeap, int startSector)
{
    int size;
  
    fs_file_table_8009D4E8.field_0_start = startSector;
    CDBIOS_ReadRequest_8002280C(pHeap, startSector, 2048, &FS_CdStageFileInit_helper_80022CBC);

    while (CDBIOS_ReadSync_80022854() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    size = fs_file_table_8009D4E8.field_4_size;
    
    if (!fs_file_table_8009D4E8.field_C_files)
    {
        fs_file_table_8009D4E8.field_C_files = GV_AllocResidentMemory_800163D8(size);
    }

    mts_printf_8008BBA0(aXXD, (char *)pHeap + 4, fs_file_table_8009D4E8.field_C_files, size);
    GV_CopyMemory_800160D8((char *)pHeap + 4, fs_file_table_8009D4E8.field_C_files, size);

    fs_file_table_8009D4E8.field_8_count = size / sizeof(FS_FILE);
}

int FS_CdGetStageFileTop_80022DCC(char *pFileName)
{
    FS_FILE *file;
    int count;
  
    file = fs_file_table_8009D4E8.field_C_files;

    for (count = fs_file_table_8009D4E8.field_8_count; count > 0; count--)
    {
        if (!strncmp_8008E7F8(file->field_0_name, pFileName, 8))
        {
            return file->field_4_offset + fs_file_table_8009D4E8.field_0_start;
        }
      
        file++;
    }

    return -1;
}
