#include "demothrd.h"

#include <stdio.h>
#include <libsn.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

extern int demodebug_finish_proc;

/* from demo.c */
extern int CreateDemo(DemoWork *work, DMO_DEF *def);
extern int DestroyDemo(DemoWork *work);
extern int FrameRunDemo(DemoWork *work, DMO_DAT *data);

/*---------------------------------------------------------------------------*/

static void StreamAct(DemoWork *work);
static void StreamDie(DemoWork *work);
static void FileAct(DemoWork *work);
static void FileDie(DemoWork *work);

int DM_ThreadStream(int flag, int unused)
{
    DemoWork *work;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(DemoWork));
    if (!work)
    {
        return 0;
    }

    work->flag = flag;
    work->frame = -1;

    GV_SetNamedActor(&work->actor, &StreamAct, &StreamDie, "demothrd.c");

    work->map = GM_CurrentMap;
    FS_StreamOpen();
    return 1;
}

int DM_ThreadFile(int flag, char *filename)
{
    DemoWork   *work;
    int         fd;
    char       *buffer;
    int         fsize, length;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(DemoWork));

    if ( !work )
    {
        return 0;
    }

    work->flag = flag;
    work->frame = -1;

    GV_SetNamedActor(&work->actor, &FileAct, &FileDie, "demothrd.c");

    work->map = GM_CurrentMap;
    FS_EnableMemfile(0, 0);
    work->stream = (void *)0x80200000;

    MakeFullPath(filename, (char *)&work->chain.used);
    printf("Demo file = \"%s\"\n", (char *)&work->chain.used);

    fd = PCopen((char *)&work->chain.used, 0, 0);
    if ( fd < 0 )
    {
        printf("\"%s\" not found\n", (char *)&work->chain.used);
        GV_DestroyActor(&work->actor);
        return 0;
    }

    fsize = PClseek(fd, 0, 2);
    PClseek(fd, 0, 0);

    buffer = (char *)work->stream;

    while ( fsize > 0 )
    {
        length = (fsize <= 0x8000) ? fsize : 0x8000;
        length = PCread(fd, buffer, length);

        fsize -= length;

        if ( length < 0 )
        {
            PCclose(fd);
            GV_DestroyActor(&work->actor);
            return 0;
        }

        buffer += length;
    }

    PCclose(fd);
    return 1;
}

/*---------------------------------------------------------------------------*/

static void StreamAct(DemoWork *work)
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

static void StreamDie(DemoWork *work)
{
    DestroyDemo(work);
    FS_StreamClose();
    DG_UnDrawFrameCount = 0x7fff0000;
}

static void FileAct(DemoWork *work)
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

static void FileDie(DemoWork *work)
{
    DestroyDemo(work);
    FS_EnableMemfile(1, 1);

    if (demodebug_finish_proc != -1)
    {
        GCL_ExecProc(demodebug_finish_proc, NULL);
    }
}
