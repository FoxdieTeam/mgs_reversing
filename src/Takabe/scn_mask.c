#include "scn_mask.h"

extern int GV_Clock_800AB920;

void scn_mask_act_80078620(struct ScnMaskWork *work)
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

void scn_mask_kill_80078774(struct ScnMaskWork *work)
{
    if (work->field_20_pPrims)
    {
        GV_DelayedFree(work->field_20_pPrims);
    }
}

int scn_mask_loader_800787A4(struct ScnMaskWork *work, int a2)
{
    struct scn_mask_prims *pPrims;
    TILE                  *p2nd;
    int                    k112_counter;
    TILE                  *p1st;
    pPrims = (struct scn_mask_prims *)GV_Malloc(sizeof(struct scn_mask_prims));
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

/**
 * @brief Constructor for the screen effect of the thermal goggles or night vision goggles.
 *
 * @param a1 1 for thermal goggles, 0 for night vision goggles.
 * @return GV_ACT* the actor for the screen effect.
 */
GV_ACT *new_scn_mask_8007895C(int a1)
{
    ScnMaskWork *work = (ScnMaskWork *)GV_NewActor(2, sizeof(ScnMaskWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)scn_mask_act_80078620,
                         (TActorFunction)scn_mask_kill_80078774, "scn_mask.c");

        if (scn_mask_loader_800787A4(work, a1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
    }
    return &work->actor;
}
