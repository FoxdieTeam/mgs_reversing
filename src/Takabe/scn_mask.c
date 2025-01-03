#include "scn_mask.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Equip/equip.h"

extern int GV_Clock_800AB920;

/*---------------------------------------------------------------------------*/

typedef struct SCN_MASK_PRIMS
{
    DR_TPAGE field_0_unknown1[2];
    TILE     field_10_tile_big[2];
    DR_TPAGE field_30_unknown2[2];
    TILE     field_40_tile_lines[2][112];
} SCN_MASK_PRIMS;

typedef struct ScnMaskWork
{
    GV_ACT           actor;
    SCN_MASK_PRIMS  *field_20_pPrims;
    int              field_24;
    int              field_28;
} ScnMaskWork;

#define EXEC_LEVEL 2

/*---------------------------------------------------------------------------*/

STATIC void scn_mask_Act(struct ScnMaskWork *work)
{
    int            i;
    TILE          *pTiles;
    unsigned char *pOt;

    pOt = DG_ChanlOTag(0);

    pTiles = &work->field_20_pPrims->field_40_tile_lines[GV_Clock_800AB920][0];
    for (i = 112; i > 0; i--)
    {

        addPrim(pOt, pTiles);
        pTiles++;
    }

    addPrim(pOt, &work->field_20_pPrims->field_30_unknown2[GV_Clock_800AB920]);
    addPrim(pOt, &work->field_20_pPrims->field_10_tile_big[GV_Clock_800AB920]);
    addPrim(pOt, &work->field_20_pPrims->field_0_unknown1[GV_Clock_800AB920]);
}

STATIC void scn_mask_Die(struct ScnMaskWork *work)
{
    if (work->field_20_pPrims)
    {
        GV_DelayedFree(work->field_20_pPrims);
    }
}

STATIC int scn_mask_GetResources(struct ScnMaskWork *work, int a2)
{
    SCN_MASK_PRIMS  *pPrims;
    TILE            *p2nd;
    int              k112_counter;
    TILE            *p1st;

    pPrims = (SCN_MASK_PRIMS *)GV_Malloc(sizeof(SCN_MASK_PRIMS));
    work->field_20_pPrims = pPrims;
    if (!pPrims)
    {
        return -1;
    }

    setDrawTPage(&pPrims->field_0_unknown1[0], 0, 1, 0x20);
    setDrawTPage(&pPrims->field_0_unknown1[1], 0, 1, 0x20);

    setTile(&pPrims->field_10_tile_big[0]);
    setSemiTrans(&pPrims->field_10_tile_big[0], 1);

    pPrims->field_10_tile_big[0].x0 = -160;
    pPrims->field_10_tile_big[0].y0 = -112;
    pPrims->field_10_tile_big[0].w = 320;
    pPrims->field_10_tile_big[0].h = 224;

    pPrims->field_10_tile_big[1] = pPrims->field_10_tile_big[0];

    if (!a2)
    {
        // night vision goggles green color
        setRGB0(&pPrims->field_10_tile_big[0], 56, 120, 40);
        setRGB0(&pPrims->field_10_tile_big[1], 56, 120, 40);
    }
    else
    {
        // thermal goggles red color
        setRGB0(&pPrims->field_10_tile_big[0], 80, 0, 0);
        setRGB0(&pPrims->field_10_tile_big[1], 80, 0, 0);
    }

    setDrawTPage(&pPrims->field_30_unknown2[0], 0, 1, 0x40);
    setDrawTPage(&pPrims->field_30_unknown2[1], 0, 1, 0x40);

    p1st = &pPrims->field_40_tile_lines[0][0];
    p2nd = &pPrims->field_40_tile_lines[1][0];

    k112_counter = 0;

    // create the interlaced lines effect for the thermal goggles
    do
    {
        setTile(p1st);
        setSemiTrans(p1st, 1);

        setRGB0(p1st, 64, 64, 64);

        p1st->x0 = -160;
        p1st->y0 = -112 + (k112_counter * 2);

        p1st->w = 320;
        p1st->h = 1;

        *p2nd = *p1st;

        p1st++;
        p2nd++;

        k112_counter++;
    } while (k112_counter < 112);

    return 0;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Constructor for the screen effect of the thermal goggles
 *          or night vision goggles.
 *
 * @param   type    1 for thermal goggles, 0 for night vision goggles.
 *
 * @return  GV_ACT* the actor for the screen effect.
 */
GV_ACT *NewNightVisionScreen(int type)
{
    ScnMaskWork *work = (ScnMaskWork *)GV_NewActor(EXEC_LEVEL, sizeof(ScnMaskWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)scn_mask_Act,
                         (GV_ACTFUNC)scn_mask_Die, "scn_mask.c");

        if (scn_mask_GetResources(work, type) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
