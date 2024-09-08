#include "linker.h"
#include "common.h"
#include "mts/mts_new.h"
#include "mts/taskid.h"
#include "libfs.h"
#include "psyq.h"
#include <libcd.h>

int cdbios_next_state_8009D4DC = CDBIOS_STATE_INVALID;
int cdbios_start_8009D4E0 = 0;
int cdbios_stop_8009D4E4 = 0;

extern CDBIOS_TASK  cd_bios_task_800B4E58;

#define CDBIOS_STACK_SIZE 1024
extern char cd_bios_stack_800B4E88[CDBIOS_STACK_SIZE];

extern const char *MGS_DiskName_8009D2FC[3];

static inline u_long loc_to_int( CdlLOC *loc )
{
    return (btoi(loc->minute) * (60 * 75)
          + btoi(loc->second) * 75
          + btoi(loc->sector));
}

static inline void int_to_loc( int pos, CdlLOC *loc )
{
    int seconds;

    seconds = pos / 75;
    loc->sector = itob(pos % 75);
    loc->second = itob(seconds % 60);
    loc->minute = itob(seconds / 60);
}

void MakeFullPath(int name, char *buffer)
{
    /* do nothing */
}

int CDBIOS_Reset(void)
{
    int           retries;
    unsigned char params[8];

    CDBIOS_TaskStart();

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

    mts_wait_vbl(3);
    return 1;
}

void CDBIOS_Stop(void)
{
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
    CdControl(CdlPause, 0, 0);
    cdbios_next_state_8009D4DC = CDBIOS_STATE_IDLE;
}

void CDBIOS_Error(void)
{
    if (cd_bios_task_800B4E58.field_10_ticks == 0)
    {
        cd_bios_task_800B4E58.field_10_ticks = mts_get_tick_count();
    }

    cdbios_next_state_8009D4DC = CDBIOS_STATE_ERROR;
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
}

void CDBIOS_SyncCallback(u_char status, u_char *result)
{
    /* do nothing */
}

void CDBIOS_ReadyCallback(u_char status, u_char *result)
{
    int sector;
    int callback_status;
    unsigned int size;
    CDBIOS_TASK *task;
    CdlLOC loc[3];

    if (cdbios_stop_8009D4E4 != 0)
    {
        CDBIOS_Stop();
        return;
    }

    if (status == 1)
    {
        task = &cd_bios_task_800B4E58;

        CdGetSector(loc, 3);

        sector = loc_to_int(&loc[0]);

        if (sector < task->field_4_sector)
        {
            return;
        }

        if (sector > task->field_4_sector)
        {
            printf("CDFS: skip error %d %d %d\n", task->field_10_ticks, sector, task->field_4_sector);
        }
        else
        {
            size = 0x200;

            if (task->field_1C_remaining <= 512u)
            {
                size = task->field_1C_remaining;
            }

            if (task->field_8_buffer)
            {
                CdGetSector(task->field_8_buffer, size);
            }

            task->field_1C_remaining -= size;
            task->field_C = size;

            if (task->field_20_callback)
            {
                callback_status = task->field_20_callback(&cd_bios_task_800B4E58);

                if (callback_status == 0)
                {
                    CDBIOS_Stop();
                }
                else if (callback_status == 2)
                {
                    size = 0;
                }
            }

            if (task->field_8_buffer)
            {
                task->field_8_buffer = (int *)task->field_8_buffer + size;
            }

            task->field_4_sector++;
            task->field_14_sectors_delivered++;
            task->field_10_ticks = 0;

            if (task->field_1C_remaining <= 0)
            {
                CDBIOS_Stop();
            }

            return;
        }
    }

    CDBIOS_Error();
}

void CDBIOS_Main(void)
{
    CdlLOC loc;
    u_char result[8];
    u_char param[3];

    CDBIOS_TASK *pTask;

    int last_ticks;
    int last_sector;
    int failed_reads;
    int ticks;

    mts_set_vsync_task();

    pTask = &cd_bios_task_800B4E58;

    last_ticks = 0;
    last_sector = 0;
    failed_reads = 0;

    while (1)
    {
        ticks = mts_get_tick_count();

        if (cdbios_stop_8009D4E4 != 0)
        {
            cdbios_stop_8009D4E4 = 0;
            CDBIOS_Stop();
        }

        if (cdbios_next_state_8009D4DC >= 0)
        {
            pTask->field_0_state = cdbios_next_state_8009D4DC;
            cdbios_next_state_8009D4DC = CDBIOS_STATE_INVALID;
        }

        if (cdbios_start_8009D4E0 != 0)
        {
            pTask->field_0_state = CDBIOS_STATE_START;
            cdbios_start_8009D4E0 = 0;
            cdbios_stop_8009D4E4 = 0;
            cdbios_next_state_8009D4DC = CDBIOS_STATE_INVALID;
        }

        switch (pTask->field_0_state)
        {
        case CDBIOS_STATE_IDLE:
            break;

        case CDBIOS_STATE_START:
            last_sector = pTask->field_4_sector;
            failed_reads = 0;

            int_to_loc(pTask->field_4_sector, &loc);

            CdFlush();
            CdSyncCallback(&CDBIOS_SyncCallback);
            CdReadyCallback(&CDBIOS_ReadyCallback);

            pTask->field_10_ticks = 0;
            pTask->field_0_state = CDBIOS_STATE_READ;

            if (!CdControl(CdlReadN, (u_char *)&loc, result))
            {
                CDBIOS_Error();
            }

            last_ticks = ticks;
            break;

        case CDBIOS_STATE_READ:
            if (last_sector != pTask->field_4_sector)
            {
                last_ticks = ticks;
                last_sector = pTask->field_4_sector;
            }
            else if ((ticks - last_ticks) > 500)
            {
                CDBIOS_Error();
                printf("[T]");
            }
            break;

        case CDBIOS_STATE_ERROR:
            printf(".");

            CdFlush();
            CdReadyCallback(NULL);
            CdSyncCallback(NULL);

            if ((ticks - pTask->field_10_ticks) > 800)
            {
                if (CdReset(0))
                {
                    param[0] = CdlModeSpeed | CdlModeSize1;

                    if (CdControl(CdlSetmode, param, NULL))
                    {
                        mts_wait_vbl(1);
                        mts_wait_vbl(3);
                        pTask->field_10_ticks = mts_get_tick_count();
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            CdFlush();

            if ((failed_reads % 4) < 3)
            {
                int_to_loc(pTask->field_4_sector, &loc);
            }
            else
            {
                int_to_loc(pTask->field_4_sector - 4, &loc);
            }

            CdFlush();
            CdSyncCallback(&CDBIOS_SyncCallback);
            CdReadyCallback(&CDBIOS_ReadyCallback);

            if (cdbios_stop_8009D4E4 == 0)
            {
                pTask->field_0_state = CDBIOS_STATE_READ;

                if (!CdControl(CdlReadN, (u_char *)&loc, NULL))
                {
                    failed_reads++;
                    pTask->field_0_state = CDBIOS_STATE_ERROR;
                }
                else
                {
                    last_sector = pTask->field_4_sector;
                    last_ticks = mts_get_tick_count();
                }
            }
            break;

        default:
            printf("[%d]", pTask->field_0_state);
            break;
        }

        mts_wait_vbl(1);
    }
}

void CDBIOS_TaskStart(void)
{
    cd_bios_task_800B4E58.field_0_state = CDBIOS_STATE_IDLE;

    cdbios_next_state_8009D4DC = CDBIOS_STATE_INVALID;
    cdbios_stop_8009D4E4 = 0;

    mts_start_task(MTSID_CDBIOS, CDBIOS_Main, STACK_BOTTOM(cd_bios_stack_800B4E88), CDBIOS_STACK_SIZE);
}

void CDBIOS_ReadRequest(void *pHeap, unsigned int startSector, unsigned int sectorSize, void *fnCallBack)
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
    cd_bios_task_800B4E58.field_14_sectors_delivered = 0;

    cdbios_stop_8009D4E4 = 0;
    cdbios_start_8009D4E0 = 1;
}

int CDBIOS_ReadSync(void)
{
    return cd_bios_task_800B4E58.field_1C_remaining * 4;
}

void CDBIOS_ForceStop(void)
{
    if (cd_bios_task_800B4E58.field_0_state != CDBIOS_STATE_IDLE)
    {
        cdbios_stop_8009D4E4 = 1;
    }
}

int CDBIOS_TaskState(void)
{
    return cd_bios_task_800B4E58.field_0_state;
}

STATIC void CDFS_ParseFileName(char *pOutput, char *pInput, int input_len)
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

STATIC int FS_CdMakePositionTable_helper2(void *pBuffer, int startSector, int sectorSize)
{
    CDBIOS_ReadRequest(pBuffer, startSector + 150, sectorSize, 0);

    while (1)
    {
        if (CDBIOS_ReadSync() <= 0)
        {
            break;
        }
        mts_wait_vbl(1);
    }

    return 1;
}

STATIC FS_FILE_INFO *FS_FindDirEntry(char *filename, FS_FILE_INFO *file_info)
{
    FS_FILE_INFO *ip;

    for (ip = file_info; ip->name; ip++)
    {
        if (!strcmp(filename, ip->name))
        {
            return ip;
        }
    }

    return 0;
}

// See: https://psx-spx.consoledev.net/cdromdrive/#cdrom-iso-file-and-directory-descriptors
static inline char getXAUserID(int directoryRecord, int fileIdentifierLength, int basicRecordLength)
{
    int xaRecord;
    int padding;

    xaRecord = fileIdentifierLength;
    xaRecord += directoryRecord;
    xaRecord = xaRecord + basicRecordLength;

    padding = fileIdentifierLength & 1;
    xaRecord = xaRecord - padding;
    return *((char *)xaRecord + 3);
}

#define byteswap_ulong(p) p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24)

STATIC int FS_CdMakePositionTable_helper(char *inDirectoryRecord, FS_FILE_INFO *file_info)
{
    FS_FILE_INFO    *foundRecord;
    const char     **diskNameIterator;
    const char      *currentStringPtr;
    int              fileIdentifierLength;
    char             parsedFileName[32];
    char            *sectorBaseValues;
    char            *topValues;
    char            *sizeValues;
    int              sectorBase;
    int              top;
    int              size;
    int              returnValue;
    int              stringCount;
    int              basicRecordLength;
    char            *fileIdentifier;
    char            *directoryRecord;
    FS_FILE_INFO    *directoryRecords;

    directoryRecords = file_info;
    directoryRecord = inDirectoryRecord;
    returnValue = -1;

    while (*directoryRecord != 0)
    {
        fileIdentifierLength = directoryRecord[32];

        if (fileIdentifierLength != 1)
        {
            fileIdentifier = directoryRecord + 33;
            CDFS_ParseFileName(parsedFileName, fileIdentifier, fileIdentifierLength);

            if ((directoryRecord[25] & 2) == 0)
            {
                foundRecord = FS_FindDirEntry(parsedFileName, directoryRecords);

                if (foundRecord)
                {
                    basicRecordLength = 35;

                    if (parsedFileName[0] == 'Z' && getXAUserID((int)directoryRecord, fileIdentifierLength, basicRecordLength) == 0xd)
                    {
                        foundRecord->sector = 0;
                    }
                    else
                    {
                        sectorBaseValues = (directoryRecord + 2);
                        sectorBase = byteswap_ulong(sectorBaseValues);
                        foundRecord->sector = sectorBase + 150;
                    }
                }
                else
                {
                    diskNameIterator = MGS_DiskName_8009D2FC;
                    currentStringPtr = *diskNameIterator;
                    stringCount = 0;

                    while (currentStringPtr)
                    {
                        if (strcmp(parsedFileName, diskNameIterator[0]) == 0)
                        {
                            returnValue = stringCount;
                        }

                        diskNameIterator++;
                        currentStringPtr = *diskNameIterator;
                        stringCount++;
                    }
                }

                topValues = (directoryRecord + 2);
                top = byteswap_ulong(topValues);

                sizeValues = (directoryRecord + 10);
                size = byteswap_ulong(sizeValues);

                printf("FILE %s : top %d size %d set %d\n", parsedFileName, top, size, foundRecord->sector);
            }
        }

        directoryRecord += *directoryRecord;
    }

    return returnValue;
}

int FS_CdMakePositionTable(char *pHeap, FS_FILE_INFO *file_info)
{
    char *buffer2;
    char *dir_block_ptr;
    int directory_block;
    int path_table_size;
    int ret;
    int uVar7;
    int directory_length;
    char *directory_block_data;
    char directory_name[16];

    FS_CdMakePositionTable_helper2(pHeap, 16, 2048);

    if (strncmp(pHeap + 8, "PLAYSTATION", 11))
    {
        return -1;
    }

    path_table_size = *(int *)(pHeap + 0x84);

    FS_CdMakePositionTable_helper2(pHeap, *(int *)(pHeap + 0x8c), path_table_size);
    directory_block_data = pHeap + ((((unsigned int)path_table_size + 3) >> 2) << 2);

    ret = -1;
    buffer2 = pHeap;

    while (path_table_size > 0)
    {
        directory_length = *buffer2;
        uVar7 = directory_length + 8;

        CDFS_ParseFileName(directory_name, buffer2 + 8, directory_length);

        dir_block_ptr = buffer2 + 2;
        directory_block = *dir_block_ptr | (*(dir_block_ptr + 1) << 8) | (*(dir_block_ptr + 2) << 16) | (*(dir_block_ptr + 3) << 24);

        if (!strcmp(directory_name, "MGS"))
        {
            printf("MGS read_sector %d\n", directory_block);
            FS_CdMakePositionTable_helper2(directory_block_data, directory_block, 2048);
            ret = FS_CdMakePositionTable_helper(directory_block_data, file_info);
        }

        if (uVar7 & 1)
        {
            uVar7 = directory_length + 9;
        }

        path_table_size -= uVar7;
        buffer2 += uVar7;
    }

    return ret;
}
