/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 
 */

/******************************************************************************
 * included
 */

#include <stdio.h>
#include <libsn.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

#include "demo.h"
#include "demo_.h"

extern int demodebug_finish_proc;

/******************************************************************************
 * functions
 */

static void ActStream(LPMGSDEMOACT lpAct);
static void DieStream(LPMGSDEMOACT lpAct);
static void ActFile(LPMGSDEMOACT lpAct);
static void DieFile(LPMGSDEMOACT lpAct);

/******************************************************************************
 * publics
 */

int DM_ThreadStream(
    DWORD dwStyle,
    int   unused)
{
    LPMGSDEMOACT lpAct;

    lpAct = GV_NewActor(GV_ACTOR_MANAGER, sizeof(MGSDEMOACT));
    if (!lpAct)
    {
        return 0;
    }

    lpAct->dwStyle = dwStyle;
    lpAct->nTime = -1;

    GV_SetNamedActor(&lpAct->actor, &ActStream, &DieStream, "demothrd.c");

    lpAct->nMap = GM_CurrentMap;
    FS_StreamOpen();
    return 1;
}

int DM_ThreadFile(
    DWORD dwStyle,
    char* lpstrFileName)
{
    LPMGSDEMOACT lpAct;
    int         fd;
    char       *buffer;
    int         fsize, length;

    if ((lpAct = GV_NewActor(GV_ACTOR_MANAGER, sizeof(MGSDEMOACT))) == NULL)
        return 0;

    lpAct->dwStyle = dwStyle;
    lpAct->nTime = -1;

    GV_SetNamedActor(&lpAct->actor, &ActFile, &DieFile, "demothrd.c");
    lpAct->nMap = GM_CurrentMap;

    FS_EnableMemfile(0, 0);
    lpAct->lpExtMemory = (void *)0x80200000;

    MakeFullPath(lpstrFileName, (char *)&lpAct->chain.bCheck);
    printf("Demo file = \"%s\"\n", (char *)&lpAct->chain.bCheck);

    fd = PCopen((char *)&lpAct->chain.bCheck, 0, 0);
    if ( fd < 0 )
    {
        printf("\"%s\" not found\n", (char *)&lpAct->chain.bCheck);
        GV_DestroyActor(&lpAct->actor);
        return 0;
    }

    fsize = PClseek(fd, 0, 2);
    PClseek(fd, 0, 0);

    buffer = (char *)lpAct->lpExtMemory;

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

/******************************************************************************
 * statics
 */

static void ActStream(
    LPMGSDEMOACT lpAct)
{
    int      ticks;
    char    *data;
    int      status;
    int      temp;
    LPMGSDEMO lpDemo;

    ticks = FS_StreamGetTick();

    if (lpAct->nTime == -1)
    {
        data = FS_StreamGetData(5);

        if (data)
        {
            lpDemo = (MGSDEMO *)(data - 4);
            status = CreateDemo(lpAct, lpDemo);

            FS_StreamClear(data);

            if (status == 0)
            {
                GV_DestroyActor(&lpAct->actor);
            }

            lpAct->nTime = 0;
        }

        return;
    }

    if (lpAct->nVSync == 0)
    {
        lpAct->nVSync = ticks - 2;
    }

    lpAct->nTime = (ticks - lpAct->nVSync) / 2;
    status = 0;
    temp = 0;

    if (lpAct->nTime <= lpAct->lpDemo->nFrameCount)
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

            lpDemo = (LPMGSDEMO)(data - 4);
            if (lpDemo->nTime >= lpAct->nTime)
            {
                break;
            }

            FS_StreamClear(data);
        }

        status = FrameRunDemo(lpAct, (LPMGSDEMOFRAME)lpDemo);

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

static void DieStream(
    LPMGSDEMOACT lpAct)
{
    DestroyDemo(lpAct);
    FS_StreamClose();
    DG_UnDrawFrameCount = 0x7fff0000;
}

static void ActFile(
    LPMGSDEMOACT lpAct)
{
    int nVSync;
    int nTime;
    BOOL bNext;

    nVSync = VSync(-1);

    if (lpAct->nTime == -1)
    {
        if (!CreateDemo(lpAct, (MGSDEMO *)lpAct->lpExtMemory))
        {
            printf("Error:Initialize demo\n");
            GV_DestroyActor(&lpAct->actor);
        }

        lpAct->nTime = 0;
        return;
    }

    if (lpAct->nVSync == 0)
    {
        lpAct->nVSync = nVSync - 2;
        printf("PlayDemoSound\n");
    }

    if (lpAct->dwStyle & DMT_WRITEFILEAVI)
        nTime = lpAct->nTime + 1;
    else
        nTime = (nVSync - lpAct->nVSync) / 2;

    lpAct->nTime = nTime;

    if (lpAct->lpDemo->nFrameCount < lpAct->nTime)
        bNext = FALSE;
    else
    {
        while (lpAct->nTime != lpAct->lpExtMemory->nTime)
        {
            lpAct->lpExtMemory = (MGSDEMO *)((char *)lpAct->lpExtMemory + lpAct->lpExtMemory->nSize);
        }

        bNext = FrameRunDemo(lpAct, (MGSDEMOFRAME *)lpAct->lpExtMemory);
    }

    if (GV_PadData[1].status & PAD_CROSS)
        bNext = FALSE;

    if (bNext == FALSE)
        GV_DestroyActor(&lpAct->actor);
}

static void DieFile(
    LPMGSDEMOACT lpAct)
{
    DestroyDemo(lpAct);
    FS_EnableMemfile(1, 1);

    if (demodebug_finish_proc != -1)
    {
        GCL_ExecProc(demodebug_finish_proc, NULL);
    }
}
