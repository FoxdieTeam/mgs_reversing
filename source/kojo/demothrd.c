#include "demothrd.h"

#include <stdio.h>
#include <libsn.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

extern int demodebug_finish_proc;

void demothrd_cd_act_80079664(DemothrdWork *work);
void demothrd_cd_stream_die_800797CC(DemothrdWork *work);

void demothrd_file_stream_act_800797FC(DemothrdWork *work);
void demothrd_file_stream_kill_80079960(DemothrdWork *work);

int CreateDemo(DemothrdWork *work, DMO_DEF *def);
int DestroyDemo(DemothrdWork *work);
int FrameRunDemo(DemothrdWork *work, DMO_DAT *data);

int DM_ThreadStream_80079460(int flag, int unused)
{
    DemothrdWork *pDemoThrd = GV_NewActor(GV_ACTOR_MANAGER, sizeof(DemothrdWork));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->flag = flag;
    pDemoThrd->frame = -1;

    GV_SetNamedActor(&pDemoThrd->actor,
                     &demothrd_cd_act_80079664,
                     &demothrd_cd_stream_die_800797CC,
                     "demothrd.c");

    pDemoThrd->map = GM_CurrentMap;
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

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(DemothrdWork));

    if ( !work )
    {
        return 0;
    }

    work->flag = flag;
    work->frame = -1;

    GV_SetNamedActor(&work->actor,
                     &demothrd_file_stream_act_800797FC,
                     &demothrd_file_stream_kill_80079960,
                     "demothrd.c");

    work->map = GM_CurrentMap;
    FS_EnableMemfile(0, 0);
    work->stream = (void *)0x80200000;

    MakeFullPath(demoNameHashed, (char *)&work->chain.used);
    printf("Demo file = \"%s\"\n", (char *)&work->chain.used);

    hFile = PCopen((char *)&work->chain.used, 0, 0);
    if ( hFile < 0 )
    {
        printf("\"%s\" not found\n", (char *)&work->chain.used);
        GV_DestroyActor(&work->actor);
        return 0;
    }

    seekRet = PClseek(hFile, 0, 2);
    PClseek(hFile, 0, 0);

    pHdr = (char *)work->stream;

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

void demothrd_cd_act_80079664(DemothrdWork *work)
{
    int      ticks;
    char    *data;
    int      status;
    int      temp;
    DMO_DEF *def;

    ticks = FS_StreamGetTick();

    if (work->frame == -1)
    {
        data = FS_StreamGetData(5);

        if (data)
        {
            def = (DMO_DEF *)(data - 4);
            status = CreateDemo(work, def);

            FS_StreamClear(data);

            if (status == 0)
            {
                GV_DestroyActor(&work->actor);
            }

            work->frame = 0;
        }

        return;
    }

    if (work->start_time == 0)
    {
        work->start_time = ticks - 2;
    }

    work->frame = (ticks - work->start_time) / 2;
    status = 0;
    temp = 0;

    if (work->frame <= work->header->n_frames)
    {
        while (1)
        {
            data = FS_StreamGetData(5);

            if (!data)
            {
                if (FS_StreamGetEndFlag() == 1)
                {
                    GV_DestroyActor(&work->actor);
                }

                return;
            }

            def = (DMO_DEF *)(data - 4);
            if (def->frame >= work->frame)
            {
                break;
            }

            FS_StreamClear(data);
        }

        status = FrameRunDemo(work, (DMO_DAT *)def);

        if (status == 0)
        {
            FS_StreamStop();
        }
        else
        {
            FS_StreamClear(data);
        }
    }

    if (status == temp)
    {
        GV_DestroyActor(&work->actor);
    }
}

void demothrd_cd_stream_die_800797CC(DemothrdWork *work)
{
    DestroyDemo(work);
    FS_StreamClose();
    DG_UnDrawFrameCount = 0x7fff0000;
}

void demothrd_file_stream_act_800797FC(DemothrdWork *work)
{
    int time;
    int new_time;
    int success;

    time = VSync(-1);

    if (work->frame == -1)
    {
        if (!CreateDemo(work, (DMO_DEF *)work->stream))
        {
            printf("Error:Initialize demo\n");
            GV_DestroyActor(&work->actor);
        }

        work->frame = 0;
        return;
    }

    if (work->start_time == 0)
    {
        work->start_time = time - 2;
        printf("PlayDemoSound\n");
    }

    if (work->flag & 4)
    {
        new_time = work->frame + 1;
    }
    else
    {
        new_time = (time - work->start_time) / 2;
    }

    work->frame = new_time;

    if (work->header->n_frames < work->frame)
    {
        success = 0;
    }
    else
    {
        while (work->frame != work->stream->frame)
        {
            work->stream = (DMO_DEF *)((char *)work->stream + work->stream->tag);
        }

        success = FrameRunDemo(work, (DMO_DAT *)work->stream);
    }

    if (GV_PadData[1].status & PAD_CROSS)
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
    DestroyDemo(work);
    FS_EnableMemfile(1, 1);

    if (demodebug_finish_proc != -1)
    {
        GCL_ExecProc(demodebug_finish_proc, NULL);
    }
}
