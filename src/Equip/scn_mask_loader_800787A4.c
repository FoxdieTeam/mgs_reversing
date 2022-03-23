#include "linker.h"
#include "actor.h"
#include "libdg.h"
#include "dgd.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern void *GV_Malloc_8001620C(int size);
void GV_DelayedFree_80016254(void *addr);
extern int GV_Clock_800AB920;
extern DG_CHNL DG_Chanls_800B1800[3];

struct scn_mask_prims
{
    DR_TPAGE field_0_unknown1[2];
    TILE field_10_tile_big[2];
    DR_TPAGE field_30_unknown2[2];
    TILE field_40_tile_lines[2][112];
};

struct Actor_scn_mask
{
    Actor field_0_actor;
    struct scn_mask_prims *field_20_pPrims;
    int field_24;
    int field_28;
};

void scn_mask_act_80078620(struct Actor_scn_mask *pActor)
{
    int i;
    TILE *pTiles;
    unsigned char *pOt;
    DG_CHNL *chanl = DG_Chanls_800B1800 + 1;

    pOt = chanl->mOrderingTables[GV_Clock_800AB920];

    pTiles = &pActor->field_20_pPrims->field_40_tile_lines[GV_Clock_800AB920][0];
    for (i = 112; i > 0; i--)
    {

        addPrim(pOt, pTiles);
        pTiles++;
    }

    addPrim(pOt, &pActor->field_20_pPrims->field_30_unknown2[GV_Clock_800AB920]);
    addPrim(pOt, &pActor->field_20_pPrims->field_10_tile_big[GV_Clock_800AB920]);
    addPrim(pOt, &pActor->field_20_pPrims->field_0_unknown1[GV_Clock_800AB920]);
}

void scn_mask_kill_80078774(struct Actor_scn_mask *pActor)
{
    if (pActor->field_20_pPrims)
    {
        GV_DelayedFree_80016254(pActor->field_20_pPrims);
    }
}

int scn_mask_loader_800787A4(struct Actor_scn_mask *pActor, int a2)
{
    struct scn_mask_prims *pPrims;
    TILE *p2nd;
    int k112_counter;
    TILE *p1st;
    pPrims = (struct scn_mask_prims *)GV_Malloc_8001620C(sizeof(struct scn_mask_prims));
    pActor->field_20_pPrims = pPrims;
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
        setRGB0(&pPrims->field_10_tile_big[0], 56, 120, 40);
        setRGB0(&pPrims->field_10_tile_big[1], 56, 120, 40);
    }
    else
    {
        setRGB0(&pPrims->field_10_tile_big[0], 80, 0, 0);
        setRGB0(&pPrims->field_10_tile_big[1], 80, 0, 0);
    }

    setDrawTPage(&pPrims->field_30_unknown2[0], 0, 1, 0x40);
    setDrawTPage(&pPrims->field_30_unknown2[1], 0, 1, 0x40);

    p1st = &pPrims->field_40_tile_lines[0][0];
    p2nd = &pPrims->field_40_tile_lines[1][0];

    k112_counter = 0;

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

extern const char aScnMaskC[];

struct Actor_scn_mask* new_scn_mask_8007895C(int a1)
{
    struct Actor_scn_mask *pActor = (struct Actor_scn_mask *)GV_NewActor_800150E4(2, sizeof(struct Actor_scn_mask));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)scn_mask_act_80078620, (TActorFunction)scn_mask_kill_80078774, aScnMaskC);

        if (scn_mask_loader_800787A4(pActor, a1) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }
    return pActor;
}
