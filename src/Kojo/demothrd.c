#include "demothrd.h"

#include "psyq.h"
#include "common.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include <libsn.h>

extern int    DG_UnDrawFrameCount;
extern int    demodebug_finish_proc;
extern GV_PAD GV_PadData_800B05C0[4];

void demothrd_file_stream_act_800797FC(DemothrdWork *work);
void demothrd_file_stream_kill_80079960(DemothrdWork *work);

int DM_ThreadStream_80079460(int flag, int unused)
{
    DemothrdWork *pDemoThrd = (DemothrdWork *)GV_NewActor(1, sizeof(DemothrdWork));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->field_20_flag = flag;
    pDemoThrd->field_2C_timer_ticks = -1;

    GV_SetNamedActor(&pDemoThrd->actor,
                     (GV_ACTFUNC)demothrd_cd_act_80079664,
                     (GV_ACTFUNC)demothrd_cd_stream_die_800797CC,
                     "demothrd.c");

    pDemoThrd->field_28_map = GM_CurrentMap_800AB9B0;
    FS_StreamOpen();
    return 1;
}

int DM_ThreadFile_800794E4(int flag, int demoNameHashed)
{
    DemothrdWork *work;
    int             hFile;
    int             seekRet;
    char           *pHdr;
    int             readRet;

    work = (DemothrdWork *)GV_NewActor(1, sizeof(DemothrdWork));

    if ( !work )
    {
        return 0;
    }

    work->field_20_flag = flag;
    work->field_2C_timer_ticks = -1;

    GV_SetNamedActor(&work->actor,
                     (GV_ACTFUNC)&demothrd_file_stream_act_800797FC,
                     (GV_ACTFUNC)&demothrd_file_stream_kill_80079960,
                     "demothrd.c");

    work->field_28_map = GM_CurrentMap_800AB9B0;
    FS_EnableMemfile(0, 0);
    work->field_C0_pHeader = (demothrd_0x1C *)0x80200000;

    MakeFullPath(demoNameHashed, work->field_38.field_8_fileNameBuffer);
    printf("Demo file = \"%s\"\n", work->field_38.field_8_fileNameBuffer);

    hFile = PCopen(work->field_38.field_8_fileNameBuffer, 0, 0);
    if ( hFile < 0 )
    {
        printf("\"%s\" not found\n", work->field_38.field_8_fileNameBuffer);
        GV_DestroyActor(&work->actor);
        return 0;
    }

    seekRet = PClseek(hFile, 0, 2);
    PClseek(hFile, 0, 0);

    pHdr = (char *)work->field_C0_pHeader;

    while ( seekRet > 0 )
    {
        readRet = (seekRet <= 0x8000) ? seekRet : 0x8000;
        readRet = PCread(hFile, pHdr, readRet);

        seekRet -= readRet;

        if ( readRet < 0 )
        {
            PCclose(hFile);
            GV_DestroyActor(&work->actor);
            return 0;
        }

        pHdr += readRet;
    }

    PCclose(hFile);
    return 1;
}

int CreateDemo_80079B50(DemothrdWork *, demothrd_0x1C *);
int FrameRunDemo_8007A948(DemothrdWork *pThis, dmo_data_0x28 *pDmoData);

void demothrd_cd_act_80079664(DemothrdWork *work)
{
    int            ticks;
    char          *pData;
    int            status;
    int            temp;
    demothrd_0x1C *pDmoHeader;

    ticks = FS_StreamGetTick();

    if (work->field_2C_timer_ticks == -1)
    {
        pData = FS_StreamGetData(5);

        if (pData)
        {
            pDmoHeader = (demothrd_0x1C *)(pData - 4);
            status = CreateDemo_80079B50(work, pDmoHeader);

            FS_StreamClear(pData);

            if (status == 0)
            {
                GV_DestroyActor(&work->actor);
            }

            work->field_2C_timer_ticks = 0;
        }

        return;
    }

    if (work->field_24_ticks == 0)
    {
        work->field_24_ticks = ticks - 2;
    }

    work->field_2C_timer_ticks = (ticks - work->field_24_ticks) / 2;
    status = 0;
    temp = 0;

    if (work->field_2C_timer_ticks <= work->field_30_dmo_header->field_8_movie_frames)
    {
        while (1)
        {
            pData = FS_StreamGetData(5);

            if (!pData)
            {
                if (FS_StreamGetEndFlag() == 1)
                {
                    GV_DestroyActor(&work->actor);
                }

                return;
            }

            pDmoHeader = (demothrd_0x1C *)(pData - 4);
            if (pDmoHeader->field_4_chunk_size >= work->field_2C_timer_ticks)
            {
                break;
            }

            FS_StreamClear(pData);
        }

        status = FrameRunDemo_8007A948(work, (dmo_data_0x28 *)pDmoHeader);

        if (status == 0)
        {
            FS_StreamStop();
        }
        else
        {
            FS_StreamClear(pData);
        }
    }

    if (status == temp)
    {
        GV_DestroyActor(&work->actor);
    }
}

void demothrd_cd_stream_die_800797CC(DemothrdWork *work)
{
    DestroyDemo_8007A66C(work);
    FS_StreamClose();
    DG_UnDrawFrameCount = 0x7fff0000;
}

void demothrd_file_stream_act_800797FC(DemothrdWork *work)
{
    int time;
    int new_time;
    int success;

    time = VSync(-1);

    if (work->field_2C_timer_ticks == -1)
    {
        if (!CreateDemo_80079B50(work, work->field_C0_pHeader))
        {
            printf("Error:Initialize demo\n");
            GV_DestroyActor(&work->actor);
        }

        work->field_2C_timer_ticks = 0;
        return;
    }

    if (work->field_24_ticks == 0)
    {
        work->field_24_ticks = time - 2;
        printf("PlayDemoSound\n");
    }

    if (work->field_20_flag & 4)
    {
        new_time = work->field_2C_timer_ticks + 1;
    }
    else
    {
        new_time = (time - work->field_24_ticks) / 2;
    }

    work->field_2C_timer_ticks = new_time;

    if (work->field_30_dmo_header->field_8_movie_frames < work->field_2C_timer_ticks)
    {
        success = 0;
    }
    else
    {
        while (work->field_2C_timer_ticks != work->field_C0_pHeader->field_4_chunk_size)
        {
            work->field_C0_pHeader = (void *)work->field_C0_pHeader + work->field_C0_pHeader->field_0_magic;
        }

        success = FrameRunDemo_8007A948(work, (dmo_data_0x28 *)work->field_C0_pHeader);
    }

    if (GV_PadData_800B05C0[1].status & PAD_CROSS)
    {
        success = 0;
    }

    if (success == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

void demothrd_file_stream_kill_80079960(DemothrdWork *work)
{
    DestroyDemo_8007A66C(work);
    FS_EnableMemfile(1, 1);

    if (demodebug_finish_proc != -1)
    {
        GCL_ExecProc(demodebug_finish_proc, NULL);
    }
}
