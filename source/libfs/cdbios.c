#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "libfs.h"

extern CDBIOS_TASK cd_bios_task_800B4E58;

#define CDBIOS_STACK_SIZE 1024
extern char cd_bios_stack_800B4E88[CDBIOS_STACK_SIZE];

STATIC int cdbios_next_state = CDBIOS_STATE_INVALID;
STATIC int cdbios_start_flag = 0;
STATIC int cdbios_stop_flag = 0;

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
    cdbios_next_state = CDBIOS_STATE_IDLE;
}

STATIC void CDBIOS_Error(void)
{
    if (cd_bios_task_800B4E58.ticks == 0)
    {
        cd_bios_task_800B4E58.ticks = mts_get_tick_count();
    }

    cdbios_next_state = CDBIOS_STATE_ERROR;
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

    if (cdbios_stop_flag != 0)
    {
        CDBIOS_Stop();
        return;
    }

    if (status == 1)
    {
        task = &cd_bios_task_800B4E58;

        CdGetSector(loc, 3);

        sector = loc_to_int(&loc[0]);

        if (sector < task->sector)
        {
            return;
        }

        if (sector > task->sector)
        {
            printf("CDFS: skip error %d %d %d\n", task->ticks, sector, task->sector);
        }
        else
        {
            size = 0x200;

            if (task->remaining <= 512u)
            {
                size = task->remaining;
            }

            if (task->buffer)
            {
                CdGetSector(task->buffer, size);
            }

            task->remaining -= size;
            task->buffer_size = size;

            if (task->callback)
            {
                callback_status = task->callback(&cd_bios_task_800B4E58);

                if (callback_status == 0)
                {
                    CDBIOS_Stop();
                }
                else if (callback_status == 2)
                {
                    size = 0;
                }
            }

            if (task->buffer)
            {
                task->buffer = (int *)task->buffer + size;
            }

            task->sector++;
            task->sectors_delivered++;
            task->ticks = 0;

            if (task->remaining <= 0)
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

    CDBIOS_TASK *task;

    int last_ticks;
    int last_sector;
    int failed_reads;
    int ticks;

    mts_set_vsync_task();

    task = &cd_bios_task_800B4E58;

    last_ticks = 0;
    last_sector = 0;
    failed_reads = 0;

    while (1)
    {
        ticks = mts_get_tick_count();

        if (cdbios_stop_flag != 0)
        {
            cdbios_stop_flag = 0;
            CDBIOS_Stop();
        }

        if (cdbios_next_state >= 0)
        {
            task->state = cdbios_next_state;
            cdbios_next_state = CDBIOS_STATE_INVALID;
        }

        if (cdbios_start_flag != 0)
        {
            task->state = CDBIOS_STATE_START;
            cdbios_start_flag = 0;
            cdbios_stop_flag = 0;
            cdbios_next_state = CDBIOS_STATE_INVALID;
        }

        switch (task->state)
        {
        case CDBIOS_STATE_IDLE:
            break;

        case CDBIOS_STATE_START:
            last_sector = task->sector;
            failed_reads = 0;

            int_to_loc(task->sector, &loc);

            CdFlush();
            CdSyncCallback(&CDBIOS_SyncCallback);
            CdReadyCallback(&CDBIOS_ReadyCallback);

            task->ticks = 0;
            task->state = CDBIOS_STATE_READ;

            if (!CdControl(CdlReadN, (u_char *)&loc, result))
            {
                CDBIOS_Error();
            }

            last_ticks = ticks;
            break;

        case CDBIOS_STATE_READ:
            if (last_sector != task->sector)
            {
                last_ticks = ticks;
                last_sector = task->sector;
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

            if ((ticks - task->ticks) > 800)
            {
                if (CdReset(0))
                {
                    param[0] = CdlModeSpeed | CdlModeSize1;

                    if (CdControl(CdlSetmode, param, NULL))
                    {
                        mts_wait_vbl(1);
                        mts_wait_vbl(3);
                        task->ticks = mts_get_tick_count();
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
                int_to_loc(task->sector, &loc);
            }
            else
            {
                int_to_loc(task->sector - 4, &loc);
            }

            CdFlush();
            CdSyncCallback(&CDBIOS_SyncCallback);
            CdReadyCallback(&CDBIOS_ReadyCallback);

            if (cdbios_stop_flag == 0)
            {
                task->state = CDBIOS_STATE_READ;

                if (!CdControl(CdlReadN, (u_char *)&loc, NULL))
                {
                    failed_reads++;
                    task->state = CDBIOS_STATE_ERROR;
                }
                else
                {
                    last_sector = task->sector;
                    last_ticks = mts_get_tick_count();
                }
            }
            break;

        default:
            printf("[%d]", task->state);
            break;
        }

        mts_wait_vbl(1);
    }
}

void CDBIOS_TaskStart(void)
{
    cd_bios_task_800B4E58.state = CDBIOS_STATE_IDLE;

    cdbios_next_state = CDBIOS_STATE_INVALID;
    cdbios_stop_flag = 0;

    mts_start_task(MTSID_CDBIOS, CDBIOS_Main, STACK_BOTTOM(cd_bios_stack_800B4E88), CDBIOS_STACK_SIZE);
}

void CDBIOS_ReadRequest(void *buffer, unsigned int sector, unsigned int size, void *callback)
{
    cd_bios_task_800B4E58.buffer = buffer;

    if (size == 0)
    {
        size = 0x7fff0000;
    }

    cd_bios_task_800B4E58.remaining = (size + 3) >> 2;
    cd_bios_task_800B4E58.size = (size + 3) >> 2;
    cd_bios_task_800B4E58.sector = sector;
    cd_bios_task_800B4E58.callback = callback;
    cd_bios_task_800B4E58.sectors_delivered = 0;

    cdbios_stop_flag = 0;
    cdbios_start_flag = 1;
}

int CDBIOS_ReadSync(void)
{
    return cd_bios_task_800B4E58.remaining * 4;
}

void CDBIOS_ForceStop(void)
{
    if (cd_bios_task_800B4E58.state != CDBIOS_STATE_IDLE)
    {
        cdbios_stop_flag = 1;
    }
}

int CDBIOS_TaskState(void)
{
    return cd_bios_task_800B4E58.state;
}
