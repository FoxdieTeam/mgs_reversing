#include "scn_mask.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "equip/equip.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL2

#define SCANLINE_NUM    (FRAME_HEIGHT/2)

typedef struct _PRIM_WORK
{
    /* filter overlay */
    DR_TPAGE    filter_tpage[2];
    TILE        filter_tile[2];
    /* scanline prims */
    DR_TPAGE    scanline_tpage[2];
    TILE        scanline_tile[2][SCANLINE_NUM];
} PRIM_WORK;

typedef struct _Work
{
    GV_ACT      actor;
    PRIM_WORK  *prims;
    int         unused0;
    int         unused1;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int     i;
    TILE   *tile;
    u_long *ot;

    ot = (u_long *)DG_ChanlOTag(0);

    tile = &work->prims->scanline_tile[GV_Clock][0];
    for (i = SCANLINE_NUM; i > 0; i--)
    {
        addPrim(ot, tile);
        tile++;
    }

    addPrim(ot, &work->prims->scanline_tpage[GV_Clock]);
    addPrim(ot, &work->prims->filter_tile[GV_Clock]);
    addPrim(ot, &work->prims->filter_tpage[GV_Clock]);
}

static void Die(Work *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

static int GetResources(Work *work, int mode)
{
    PRIM_WORK  *prims;
    TILE       *tile0, *tile1;
    int         counter;

    prims = (PRIM_WORK *)GV_Malloc(sizeof(PRIM_WORK));
    work->prims = prims;
    if (!prims)
    {
        return -1;
    }

    setDrawTPage(&prims->filter_tpage[0], 0, 1, 0x20);
    setDrawTPage(&prims->filter_tpage[1], 0, 1, 0x20);

    setTile(&prims->filter_tile[0]);
    setSemiTrans(&prims->filter_tile[0], 1);

    prims->filter_tile[0].x0 = -(FRAME_WIDTH/2);    // -160
    prims->filter_tile[0].y0 = -(FRAME_HEIGHT/2);   // -112
    prims->filter_tile[0].w = FRAME_WIDTH;
    prims->filter_tile[0].h = FRAME_HEIGHT;

    prims->filter_tile[1] = prims->filter_tile[0];

    if (mode == SCREEN_MASK_NV_MODE)
    {
        // dark green tint
        setRGB0(&prims->filter_tile[0], 56, 120, 40);
        setRGB0(&prims->filter_tile[1], 56, 120, 40);
    }
    else
    {
        // dark red tint
        setRGB0(&prims->filter_tile[0], 80, 0, 0);
        setRGB0(&prims->filter_tile[1], 80, 0, 0);
    }

    setDrawTPage(&prims->scanline_tpage[0], 0, 1, 0x40);
    setDrawTPage(&prims->scanline_tpage[1], 0, 1, 0x40);

    tile0 = &prims->scanline_tile[0][0];
    tile1 = &prims->scanline_tile[1][0];
    counter = 0;

    // setup the scanline tiles
    do {
        setTile(tile0);
        setSemiTrans(tile0, 1);
        setRGB0(tile0, 64, 64, 64);
        setXY0(tile0, -160, -112 + (counter * 2));
        setWH(tile0, FRAME_WIDTH, 1);

        *tile1++ = *tile0++;
        counter++;
    } while (counter < SCANLINE_NUM);

    return 0;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Constructor for the screen effect of the thermal goggles
 *          or night vision goggles.
 *
 * @param   mode    SCREEN_MASK_NV_MODE for night vision green tint.
 *                  SCREEN_MASK_IR_MODE for thermal goggle red tint.
 *
 * @returns The actor's work area.
 */
void *NewNightVisionScreen(int mode)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "scn_mask.c");

        if (GetResources(work, mode) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
