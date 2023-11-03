#include "demothrd.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include <LIBSN.H>

extern int    DG_UnDrawFrameCount_800AB380;
extern int    demodebug_finish_proc_800AB414;
extern GV_PAD GV_PadData_800B05C0[4];

void demothrd_file_stream_act_800797FC(Actor_demothrd *pActor);
void demothrd_file_stream_kill_80079960(Actor_demothrd *pActor);

int DM_ThreadStream_80079460(int flag, int unused)
{
    Actor_demothrd *pDemoThrd = (Actor_demothrd *)GV_NewActor_800150E4(1, sizeof(Actor_demothrd));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->field_20_flag = flag;
    pDemoThrd->field_2C_timer_ticks = -1;

    GV_SetNamedActor_8001514C(&pDemoThrd->field_0_actor,
                              (TActorFunction)demothrd_cd_act_80079664,
                              (TActorFunction)demothrd_cd_stream_die_800797CC,
                              "demothrd.c");

    pDemoThrd->field_28_map = GM_CurrentMap_800AB9B0;
    FS_StreamOpen_80024060();
    return 1;
}

int DM_ThreadFile_800794E4(int flag, int demoNameHashed)
{
    Actor_demothrd *pActor;
    int             hFile;
    int             seekRet;
    char           *pHdr;
    int             readRet;

    pActor = (Actor_demothrd *)GV_NewActor_800150E4(1, sizeof(Actor_demothrd));

    if ( !pActor )
    {
        return 0;
    }

    pActor->field_20_flag = flag;
    pActor->field_2C_timer_ticks = -1;

    GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                              (TActorFunction)&demothrd_file_stream_act_800797FC,
                              (TActorFunction)&demothrd_file_stream_kill_80079960,
                              "demothrd.c");

    pActor->field_28_map = GM_CurrentMap_800AB9B0;
    FS_EnableMemfile_800799A8(0, 0);
    pActor->field_C0_pHeader = (demothrd_0x1C *)0x80200000;

    MakeFullPath_80021F68(demoNameHashed, pActor->field_38.field_8_fileNameBuffer);
    printf("Demo file = \"%s\"\n", pActor->field_38.field_8_fileNameBuffer);

    hFile = PCopen_80014B1C(pActor->field_38.field_8_fileNameBuffer, 0, 0);
    if ( hFile < 0 )
    {
        printf("\"%s\" not found\n", pActor->field_38.field_8_fileNameBuffer);
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return 0;
    }

    seekRet = PClseek(hFile, 0, 2);
    PClseek(hFile, 0, 0);

    pHdr = (char *)pActor->field_C0_pHeader;

    while ( seekRet > 0 )
    {
        readRet = (seekRet <= 0x8000) ? seekRet : 0x8000;
        readRet = PCread_80014B24(hFile, pHdr, readRet);

        seekRet -= readRet;

        if ( readRet < 0 )
        {
            PCclose_80014B2C(hFile);
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        pHdr += readRet;
    }

    PCclose_80014B2C(hFile);
    return 1;
}

int CreateDemo_80079B50(Actor_demothrd *, demothrd_0x1C *);
int demothrd_1_FrameRunDemo_8007A948(Actor_demothrd *pThis, dmo_data_0x28 *pDmoData);

void demothrd_cd_act_80079664(Actor_demothrd *pActor)
{
    int            ticks;
    char          *pData;
    int            status;
    int            temp;
    demothrd_0x1C *pDmoHeader;

    ticks = FS_StreamGetTick_80024420();

    if (pActor->field_2C_timer_ticks == -1)
    {
        pData = FS_StreamGetData_800240E0(5);

        if (pData)
        {
            pDmoHeader = (demothrd_0x1C *)(pData - 4);
            status = CreateDemo_80079B50(pActor, pDmoHeader);

            sub_800241B4(pData);

            if (status == 0)
            {
                GV_DestroyActor_800151C8(&pActor->field_0_actor);
            }

            pActor->field_2C_timer_ticks = 0;
        }

        return;
    }

    if (pActor->field_24_ticks == 0)
    {
        pActor->field_24_ticks = ticks - 2;
    }

    pActor->field_2C_timer_ticks = (ticks - pActor->field_24_ticks) / 2;
    status = 0;
    temp = 0;

    if (pActor->field_2C_timer_ticks <= pActor->field_30_dmo_header->field_8_movie_frames)
    {
        while (1)
        {
            pData = FS_StreamGetData_800240E0(5);

            if (!pData)
            {
                if (FS_StreamGetEndFlag_800243B8() == 1)
                {
                    GV_DestroyActor_800151C8(&pActor->field_0_actor);
                }

                return;
            }

            pDmoHeader = (demothrd_0x1C *)(pData - 4);
            if (pDmoHeader->field_4_chunk_size >= pActor->field_2C_timer_ticks)
            {
                break;
            }

            sub_800241B4(pData);
        }

        status = demothrd_1_FrameRunDemo_8007A948(pActor, (dmo_data_0x28 *)pDmoHeader);

        if (status == 0)
        {
            FS_StreamStop_80024028();
        }
        else
        {
            sub_800241B4(pData);
        }
    }

    if (status == temp)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
}

void demothrd_cd_stream_die_800797CC(Actor_demothrd *pActor)
{
    DestroyDemo_8007A66C(pActor);
    FS_StreamClose_80024098();
    DG_UnDrawFrameCount_800AB380 = 0x7fff0000;
}

void demothrd_file_stream_act_800797FC(Actor_demothrd *pActor)
{
    int time;
    int new_time;
    int success;

    time = VSync(-1);

    if (pActor->field_2C_timer_ticks == -1)
    {
        if (!CreateDemo_80079B50(pActor, pActor->field_C0_pHeader))
        {
            printf("Error:Initialize demo\n");
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
        }

        pActor->field_2C_timer_ticks = 0;
        return;
    }

    if (pActor->field_24_ticks == 0)
    {
        pActor->field_24_ticks = time - 2;
        printf("PlayDemoSound\n");
    }

    if (pActor->field_20_flag & 4)
    {
        new_time = pActor->field_2C_timer_ticks + 1;
    }
    else
    {
        new_time = (time - pActor->field_24_ticks) / 2;
    }

    pActor->field_2C_timer_ticks = new_time;

    if (pActor->field_30_dmo_header->field_8_movie_frames < pActor->field_2C_timer_ticks)
    {
        success = 0;
    }
    else
    {
        while (pActor->field_2C_timer_ticks != pActor->field_C0_pHeader->field_4_chunk_size)
        {
            pActor->field_C0_pHeader = (void *)pActor->field_C0_pHeader + pActor->field_C0_pHeader->field_0_magic;
        }

        success = demothrd_1_FrameRunDemo_8007A948(pActor, (dmo_data_0x28 *)pActor->field_C0_pHeader);
    }

    if (GV_PadData_800B05C0[1].status & PAD_CROSS)
    {
        success = 0;
    }

    if (success == 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
}

void demothrd_file_stream_kill_80079960(Actor_demothrd *pActor)
{
    DestroyDemo_8007A66C(pActor);
    FS_EnableMemfile_800799A8(1, 1);

    if (demodebug_finish_proc_800AB414 != -1)
    {
        GCL_ExecProc_8001FF2C(demodebug_finish_proc_800AB414, NULL);
    }
}
