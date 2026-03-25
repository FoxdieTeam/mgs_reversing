#include "fadeio.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL3

#define MODE_FADEOUT    (0 << 0)    // 0x0000
#define MODE_FADEIN     (1 << 0)    // 0x0001
#define MODE_BLACK      (0 << 1)    // 0x0000
#define MODE_WHITE      (1 << 1)    // 0x0002

typedef struct _FADE_PRIMS
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} FADE_PRIMS;

typedef struct _Work
{
    GV_ACT       actor;
    int          name;
    FADE_PRIMS  *prims;
    int          shade;
    int          field_2c;
    int          field_30;
    int          mode;
    int          field_38;
} Work;

/*---------------------------------------------------------------------------*/

unsigned short fadeio_mes_list[] = { HASH_KILL, 0x71F1 };

static void Act(Work *work)
{
    int   status;
    char *ot;
    int   shade;

    if (GV_PauseLevel == 0)
    {
        status = THING_Msg_CheckMessage(work->name, 2, fadeio_mes_list);
        if (status == 0)
        {
            GV_DestroyActor(&work->actor);
            return;
        }

        if (status == 1)
        {
            work->field_2c = 0;
            work->mode |= MODE_FADEIN;
        }
    }

    ot = DG_ChanlOTag(1);
    addPrim(ot, &work->prims->tile[GV_Clock]);
    addPrim(ot, &work->prims->tpage[GV_Clock]);

    if (work->field_2c > work->shade)
    {
        work->field_2c = work->shade;
    }

    shade = (work->field_2c * 255) / work->shade;
    if (work->mode & MODE_FADEIN)
    {
        shade = 255 - shade;
    }

    if (GV_PauseLevel == 0)
    {
        if (!(GM_GameStatus & STATE_DEMO))
        {
            work->field_2c++;
        }
        else
        {
            work->field_38 += GV_PassageTime;
            work->field_2c += work->field_38 >> 1;
            work->field_38 &= 0x1;
        }
    }

    work->field_30 = shade;
    setRGB0(&work->prims->tile[GV_Clock], shade, shade, shade);

    if ((work->mode & MODE_FADEIN) && (work->field_2c >= work->shade))
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

static int GetResources(Work *work, int mode, int shade)
{
    FADE_PRIMS *prims;

    prims = GV_Malloc(sizeof(FADE_PRIMS));
    work->prims = prims;
    if (prims == NULL)
    {
        return -1;
    }
    if (mode & MODE_WHITE)
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 1, 0, 0));
    }
    else
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 2, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 2, 0, 0));
    }
    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);

    prims->tile[0].w = FRAME_WIDTH;
    prims->tile[0].h = FRAME_HEIGHT;
    prims->tile[0].x0 = 0;
    prims->tile[0].y0 = 0;
    prims->tile[1] = prims->tile[0];
    if (!(mode & MODE_FADEIN))
    {
        prims->tile[0].r0 = 0;
        prims->tile[0].g0 = 0;
        prims->tile[0].b0 = 0;
        prims->tile[1].r0 = 0;
        prims->tile[1].g0 = 0;
        prims->tile[1].b0 = 0;
        work->field_30 = 0;
    }
    else
    {
        prims->tile[0].r0 = 0xFF;
        prims->tile[0].g0 = 0xFF;
        prims->tile[0].b0 = 0xFF;
        prims->tile[1].r0 = 0xFF;
        prims->tile[1].g0 = 0xFF;
        prims->tile[1].b0 = 0xFF;
        work->field_30 = 0xFF;
    }
    work->mode = mode;
    work->shade = shade;
    work->field_2c = 1;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewFadeInOut(int mode, int shade)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "fadeio.c");
        if (GetResources(work, mode, shade) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = 0x62FE;
    }
    return (void *)work;
}

void *NewFadeInOutSet(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "fadeio.c");

        if (GetResources(work, THING_Gcl_GetInt('m'), THING_Gcl_GetInt('s')) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }
    return (void *)work;
}
