#include "blurpure.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL  GV_ACTOR_AFTER2

/* TODO: move */
#define OT_LEN      256

/*---------------------------------------------------------------------------*/

typedef struct _BLUR_PRIMS
{
    TILE     tile[2];
    char     pad[0x20];
    DR_STP   stp1[2];
    DR_STP   stp2[2];
    SPRT     sprt1[2];
    SPRT     sprt2[2];
    DR_TPAGE tpage1[2];
    DR_TPAGE tpage2[2];
} BLUR_PRIMS;

typedef struct _Work
{
    GV_ACT      actor;
    BLUR_PRIMS *prims;
    int         draw;
    int         name;
} Work;

/*---------------------------------------------------------------------------*/

static void ClearScreen(Work *work)
{
    u_long *ot;
    TILE   *tile;
    DR_STP *stp;

    /* DG_ChanlOTag doesn't work here */
    ot = DG_Chanl(0)->ot[GV_Clock];

    tile = &work->prims->tile[GV_Clock];
    setTile(tile);
    setXY0(tile, -FRAME_WIDTH/2, -FRAME_HEIGHT/2);
    setWH(tile, FRAME_WIDTH, FRAME_HEIGHT);
    setRGB0(tile, 0, 0, 0);
    addPrim(ot + OT_LEN - 1, tile);

    stp = &work->prims->stp1[GV_Clock];
    SetDrawStp(stp, 1);
    addPrim(ot + OT_LEN - 1, stp);

    /* DG_ChanlOTag doesn't work here */
    ot = DG_Chanl(1)->ot[GV_Clock];

    stp = &work->prims->stp2[GV_Clock];
    SetDrawStp(stp, 1);
    addPrim(ot, stp);
}

static void InitPrims(Work *work)
{
    SPRT *sprt;

    sprt = &work->prims->sprt1[0];
    setXY0(sprt, 0, -88);
    setWH(sprt, 160, 160);
    setUV0(sprt, 32, 24);

    sprt = &work->prims->sprt2[0];
    setXY0(sprt, -160, -88);
    setWH(sprt, 160, 160);
    setUV0(sprt, 0, 24);

    sprt = &work->prims->sprt1[1];
    setXY0(sprt, 0, -88);
    setWH(sprt, 160, 160);
    setUV0(sprt, 32, 24);

    sprt = &work->prims->sprt2[1];
    setXY0(sprt, -160, -88);
    setWH(sprt, 160, 160);
    setUV0(sprt, 0, 24);
}

static void DrawEffect(Work *work)
{
    u_long   *ot;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    /* DG_ChanlOTag doesn't work here */
    ot = DG_Chanl(0)->ot[GV_Clock];

    sprt = &work->prims->sprt1[GV_Clock];
    SetSprt(sprt);
    setSemiTrans(sprt, 1);
    setRGB0(sprt, 120, 120, 120);
    addPrim(ot, sprt);

    tpage = &work->prims->tpage1[GV_Clock];
    SetDrawTPage(tpage, 0, 1, GetTPage(2, 0, FRAME_WIDTH * (1 - GV_Clock) + 128, 0));
    addPrim(ot, tpage);

    sprt = &work->prims->sprt2[GV_Clock];
    SetSprt(sprt);
    setSemiTrans(sprt, 1);
    setRGB0(sprt, 120, 120, 120);
    addPrim(ot, sprt);

    tpage = &work->prims->tpage2[GV_Clock];
    SetDrawTPage(tpage, 0, 1, GetTPage(2, 0, FRAME_WIDTH * (1 - GV_Clock), 0));
    addPrim(ot, tpage);
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (work->name != -1)
    {
        if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
        {
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    if (work->draw)
    {
        DrawEffect(work);
    }

    work->draw = TRUE;
    ClearScreen(work);
}

static void Die(Work *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

static int GetResources(Work *work)
{
    work->prims = GV_Malloc(sizeof(BLUR_PRIMS));
    if (work->prims == NULL)
    {
        return -1;
    }

    InitPrims(work);
    work->draw = FALSE;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBlurPure(void)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blurpure.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = -1;
    }

    return (void *)work;
}

void *NewBlurPureSet(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blurpure.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
