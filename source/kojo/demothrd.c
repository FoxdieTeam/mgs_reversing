#include "demo.h"

#include <stdio.h>
#include <libsn.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

extern int demodebug_finish_proc;

/*---------------------------------------------------------------------------*/

static void ActStream(LPMGSDEMOACT lpAct);
static void DieStream(LPMGSDEMOACT lpAct);
static void ActFile(LPMGSDEMOACT lpAct);
static void DieFile(LPMGSDEMOACT lpAct);

int DM_ThreadStream(int flag, int unused)
{
    LPMGSDEMOACT lpAct;

    lpAct = GV_NewActor(GV_ACTOR_MANAGER, sizeof(MGSDEMOACT));
    if (!lpAct)
    {
        return 0;
    }

    lpAct->flag = flag;
    lpAct->frame = -1;

    GV_SetNamedActor(&lpAct->actor, &ActStream, &DieStream, "demothrd.c");

    lpAct->map = GM_CurrentMap;
    FS_StreamOpen();
    return 1;
}

int DM_ThreadFile(int flag, char *filename)
{
    LPMGSDEMOACT lpAct;
    int         fd;
    char       *buffer;
    int         fsize, length;

    lpAct = GV_NewActor(GV_ACTOR_MANAGER, sizeof(MGSDEMOACT));

    if ( !lpAct )
    {
        return 0;
    }

    lpAct->flag = flag;
    lpAct->frame = -1;

    GV_SetNamedActor(&lpAct->actor, &ActFile, &DieFile, "demothrd.c");

    lpAct->map = GM_CurrentMap;
    FS_EnableMemfile(0, 0);
    lpAct->stream = (void *)0x80200000;

    MakeFullPath(filename, (char *)&lpAct->chain.used);
    printf("Demo file = \"%s\"\n", (char *)&lpAct->chain.used);

    fd = PCopen((char *)&lpAct->chain.used, 0, 0);
    if ( fd < 0 )
    {
        printf("\"%s\" not found\n", (char *)&lpAct->chain.used);
        GV_DestroyActor(&lpAct->actor);
        return 0;
    }

    fsize = PClseek(fd, 0, 2);
    PClseek(fd, 0, 0);

    buffer = (char *)lpAct->stream;

    while ( fsize > 0 )
    {
        length = (fsize <= 0x8000) ? fsize : 0x8000;
        length = PCread(fd, buffer, length);

        fsize -= length;

        if ( length < 0 )
        {
            PCclose(fd);
            GV_DestroyActor(&lpAct->actor);
            return 0;
        }

        buffer += length;
    }

    PCclose(fd);
    return 1;
}

/*---------------------------------------------------------------------------*/

static void ActStream(LPMGSDEMOACT lpAct)
{
    int      ticks;
    char    *data;
    int      status;
    int      temp;
    DMO_DEF *def;

    ticks = FS_StreamGetTick();

    if (lpAct->frame == -1)
    {
        data = FS_StreamGetData(5);

        if (data)
        {
            def = (DMO_DEF *)(data - 4);
            status = CreateDemo(lpAct, def);

            FS_StreamClear(data);

            if (status == 0)
            {
                GV_DestroyActor(&lpAct->actor);
            }

            lpAct->frame = 0;
        }

        return;
    }

    if (lpAct->start_time == 0)
    {
        lpAct->start_time = ticks - 2;
    }

    lpAct->frame = (ticks - lpAct->start_time) / 2;
    status = 0;
    temp = 0;

    if (lpAct->frame <= lpAct->header->n_frames)
    {
        while (1)
        {
            data = FS_StreamGetData(5);

            if (!data)
            {
                if (FS_StreamGetEndFlag() == 1)
                {
                    GV_DestroyActor(&lpAct->actor);
                }

                return;
            }

            def = (DMO_DEF *)(data - 4);
            if (def->frame >= lpAct->frame)
            {
                break;
            }

            FS_StreamClear(data);
        }

        status = FrameRunDemo(lpAct, (DMO_DAT *)def);

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
        GV_DestroyActor(&lpAct->actor);
    }
}

static void DieStream(LPMGSDEMOACT lpAct)
{
    DestroyDemo(lpAct);
    FS_StreamClose();
    DG_UnDrawFrameCount = 0x7fff0000;
}

static void ActFile(LPMGSDEMOACT lpAct)
{
    int time;
    int new_time;
    int success;

    time = VSync(-1);

    if (lpAct->frame == -1)
    {
        if (!CreateDemo(lpAct, (DMO_DEF *)lpAct->stream))
        {
            printf("Error:Initialize demo\n");
            GV_DestroyActor(&lpAct->actor);
        }

        lpAct->frame = 0;
        return;
    }

    if (lpAct->start_time == 0)
    {
        lpAct->start_time = time - 2;
        printf("PlayDemoSound\n");
    }

    if (lpAct->flag & 4)
    {
        new_time = lpAct->frame + 1;
    }
    else
    {
        new_time = (time - lpAct->start_time) / 2;
    }

    lpAct->frame = new_time;

    if (lpAct->header->n_frames < lpAct->frame)
    {
        success = 0;
    }
    else
    {
        while (lpAct->frame != lpAct->stream->frame)
        {
            lpAct->stream = (DMO_DEF *)((char *)lpAct->stream + lpAct->stream->tag);
        }

        success = FrameRunDemo(lpAct, (DMO_DAT *)lpAct->stream);
    }

    if (GV_PadData[1].status & PAD_CROSS)
    {
        success = 0;
    }

    if (success == 0)
    {
        GV_DestroyActor(&lpAct->actor);
    }
}

static void DieFile(LPMGSDEMOACT lpAct)
{
    DestroyDemo(lpAct);
    FS_EnableMemfile(1, 1);

    if (demodebug_finish_proc != -1)
    {
        GCL_ExecProc(demodebug_finish_proc, NULL);
    }
}
