#include "blurpure.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "strcode.h"

typedef struct BlurPurePrims
{
    TILE     tile[2];
    char     pad[0x20];
    DR_STP   stp1[2];
    DR_STP   stp2[2];
    SPRT     sprt1[2];
    SPRT     sprt2[2];
    DR_TPAGE tpage1[2];
    DR_TPAGE tpage2[2];
} BlurPurePrims;

typedef struct BlurPureWork
{
    GV_ACT         actor;
    BlurPurePrims *field_20;
    int            field_24;
    int            field_28;
} BlurPureWork;

#define EXEC_LEVEL GV_ACTOR_AFTER2

extern int GV_Clock;

void d03a_blurpure_800C4F68(BlurPureWork *work)
{
    TILE          *tile;
    DR_STP        *stp;
    unsigned char *pOt;

    pOt = DG_Chanl(0)->mOrderingTables[GV_Clock]; // DG_ChanlOTag doesn't work here
    tile = &work->field_20->tile[GV_Clock];

    setTile(tile);
    tile->x0 = -160;
    tile->y0 = -112;
    tile->w = 320;
    tile->h = 224;
    tile->r0 = 0;
    tile->g0 = 0;
    tile->b0 = 0;
    addPrim(pOt + 4 * 0xFF, tile); // TODO: what's this offset 0x3CF = 4 * 0xFF?

    stp = &work->field_20->stp1[GV_Clock];
    SetDrawStp(stp, 1);
    addPrim(pOt + 4 * 0xFF, stp); // TODO: what's this offset 0x3CF = 4 * 0xFF?

    pOt = DG_Chanl(1)->mOrderingTables[GV_Clock];
    stp = &work->field_20->stp2[GV_Clock];
    SetDrawStp(stp, 1);
    addPrim(pOt, stp);
}

void d03a_blurpure_800C5108(BlurPureWork *work)
{
    SPRT *sprt;

    sprt = &work->field_20->sprt1[0];
    sprt->x0 = 0;
    sprt->y0 = -88;
    sprt->w = 160;
    sprt->h = 160;
    sprt->u0 = 32;
    sprt->v0 = 24;

    sprt = &work->field_20->sprt2[0];
    sprt->x0 = -160;
    sprt->y0 = -88;
    sprt->w = 160;
    sprt->h = 160;
    sprt->u0 = 0;
    sprt->v0 = 24;

    sprt = &work->field_20->sprt1[1];
    sprt->x0 = 0;
    sprt->y0 = -88;
    sprt->w = 160;
    sprt->h = 160;
    sprt->u0 = 32;
    sprt->v0 = 24;

    sprt = &work->field_20->sprt2[1];
    sprt->x0 = -160;
    sprt->y0 = -88;
    sprt->w = 160;
    sprt->h = 160;
    sprt->u0 = 0;
    sprt->v0 = 24;
}

void d03a_blurpure_800C51A8(BlurPureWork *work)
{
    DR_TPAGE      *tpage;
    SPRT          *sprt;
    unsigned char *pOt;

    sprt = &work->field_20->sprt1[GV_Clock];
    pOt = DG_Chanl(0)->mOrderingTables[GV_Clock];
    SetSprt(sprt);
    sprt->r0 = 0x78;
    sprt->g0 = 0x78;
    sprt->b0 = 0x78;
    setSemiTrans(sprt, 1);
    addPrim(pOt, sprt);

    tpage = &work->field_20->tpage1[GV_Clock];
    SetDrawTPage(tpage, 0, 1, GetTPage(2, 0, ((1 - GV_Clock) * 320) + 128, 0));
    addPrim(pOt, tpage);

    sprt = &work->field_20->sprt2[GV_Clock];
    SetSprt(sprt);
    sprt->r0 = 0x78;
    sprt->g0 = 0x78;
    sprt->b0 = 0x78;
    setSemiTrans(sprt, 1);
    addPrim(pOt, sprt);

    tpage = &work->field_20->tpage2[GV_Clock];
    SetDrawTPage(tpage, 0, 1, GetTPage(2, 0, (1 - GV_Clock) * 320, 0));
    addPrim(pOt, tpage);
}

void BlurPureAct_800C53E4(BlurPureWork *work)
{
    if (work->field_28 != -1 && GM_CheckMessage(&work->actor, work->field_28, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    if (work->field_24 != 0)
    {
        d03a_blurpure_800C51A8(work);
    }
    work->field_24 = 1;
    d03a_blurpure_800C4F68(work);
}

void BlurPureDie_800C545C(BlurPureWork *work)
{
    BlurPurePrims *prims;

    prims = work->field_20;
    if (prims != NULL)
    {
        GV_DelayedFree(prims);
    }
}

int BlurPureGetResources_800C548C(BlurPureWork *work)
{
    work->field_20 = GV_Malloc(sizeof(BlurPurePrims));
    if (work->field_20 == NULL)
    {
        return -1;
    }

    d03a_blurpure_800C5108(work);
    work->field_24 = 0;
    return 0;
}

GV_ACT *NewBlurPure_800C54D4(int name, int where, int argc, char **argv)
{
    BlurPureWork *work;

    work = (BlurPureWork *)GV_NewActor(EXEC_LEVEL, sizeof(BlurPureWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)BlurPureAct_800C53E4,
                         (GV_ACTFUNC)BlurPureDie_800C545C, "blurpure.c");
        if (BlurPureGetResources_800C548C(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_28 = -1;
    }
    return &work->actor;
}

GV_ACT *NewBlurPure2_800C554C(int name, int where, int argc, char **argv)
{
    BlurPureWork *work;

    work = (BlurPureWork *)GV_NewActor(EXEC_LEVEL, sizeof(BlurPureWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)BlurPureAct_800C53E4,
                         (GV_ACTFUNC)BlurPureDie_800C545C, "blurpure.c");
        if (BlurPureGetResources_800C548C(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_28 = name;
    }
    return &work->actor;
}
