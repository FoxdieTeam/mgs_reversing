#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "libfs.h"

extern CDBIOS_TASK  cd_bios_task_800B4E58;

#define CDBIOS_STACK_SIZE 1024
extern char cd_bios_stack_800B4E88[CDBIOS_STACK_SIZE];

int cdbios_next_state_8009D4DC = CDBIOS_STATE_INVALID;
int cdbios_start_8009D4E0 = 0;
int cdbios_stop_8009D4E4 = 0;

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

STATIC void CDBIOS_Stop(void)
{
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
    CdControl(CdlPause, 0, 0);
    cdbios_next_state_8009D4DC = CDBIOS_STATE_IDLE;
}

STATIC void CDBIOS_Error(void)
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

STATIC void CDBIOS_SyncCallback(u_char status, u_char *result)
{
    /* do nothing */
}

STATIC void CDBIOS_ReadyCallback(u_char status, u_char *result)
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

STATIC void CDBIOS_Main(void)
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
