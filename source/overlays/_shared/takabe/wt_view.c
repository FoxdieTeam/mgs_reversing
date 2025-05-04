#include "wt_view.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

// XXX SetPriority & DR_PRIO are undocumented APIs.
// XXX They were previously public until their removal from libgpu.h
// XXX in Runtime Library Release 3.7 (built December 27, 1996).

// clang-format off
typedef struct {
        u_long  tag;
        u_long  code[2];
} DR_PRIO;                              /* Priority */

extern void SetPriority(DR_PRIO *p, int pbc, int pbw);
// clang-format on

extern DG_CHANL DG_Chanls_800B1800[3];

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL3

typedef struct _WaterViewPrims
{
    DR_TPAGE tpage[4];
    DR_PRIO  priority[2];
    SPRT     sprt[2][122];
    SPRT     sprt2[2][122];
    TILE     tile[4];
    TILE     tile2[2];
} WaterViewPrims;

typedef struct _Work
{
    GV_ACT          actor;
    int             map;
    int             name;
    SVECTOR         bound[2];
    WaterViewPrims *prims;
    CVECTOR         color;
    int             has_alloc;
    char            pad2[0x4];
    int             n_prims;
} Work;

static int  WaterViewCreatePrims(Work *work);
static void WaterViewInitSinTable(void);
static void WaterViewDraw(Work *work);

static short wt_view_sin_table[32];

/*---------------------------------------------------------------------------*/

static void SetupSprites1(SPRT *sa, SPRT *sb, CVECTOR *color)
{
    SPRT sprt;
    int  i;

    SetSprt(&sprt);

    sprt.x0 = -160;
    sprt.y0 = -112;
    sprt.w = 160;
    sprt.h = 2;
    sprt.u0 = 0;
    sprt.v0 = 0;

    sprt.r0 = color->r;
    sprt.g0 = color->g;
    sprt.b0 = color->b;

    for (i = 122; i >= 0; i--)
    {
        *sa = sprt;
        *sb = *sa;

        sa++;
        sb++;
    }
}

static void SetupSprites2(SPRT *sa, SPRT *sb, CVECTOR *color)
{
    SPRT sprt;
    int  i;

    SetSprt(&sprt);

    sprt.x0 = 0;
    sprt.y0 = -112;
    sprt.w = 160;
    sprt.h = 2;
    sprt.u0 = 32;
    sprt.v0 = 0;

    sprt.r0 = color->r;
    sprt.g0 = color->g;
    sprt.b0 = color->b;

    for (i = 122; i >= 0; i--)
    {
        *sa = sprt;
        *sb = *sa;

        sa++;
        sb++;
    }
}

/*---------------------------------------------------------------------------*/

static inline int CheckInBounds(Work *work, short x, short y, short z)
{
    if (x > work->bound[0].vx && x < work->bound[1].vx &&
        y > work->bound[0].vy && y < work->bound[1].vy &&
        z > work->bound[0].vz && z < work->bound[1].vz)
    {
        return 1;
    }
    return 0;
}

static void Act(Work *work)
{
    SVECTOR  sp10;
    u_long  *ot;
    SVECTOR *vec;
    MATRIX  *eye;
    short    x, y, z;
    TILE    *tile;
    void    *priority;

    ot = (u_long *)DG_ChanlOTag(0);

    vec = &sp10;
    eye = &DG_Chanls_800B1800[1].field_30_eye;

    vec->vx = x = eye->t[0];
    vec->vy = y = eye->t[1];
    vec->vz = z = eye->t[2];

    if (CheckInBounds(work, x, y, z) != work->has_alloc)
    {
        if (work->has_alloc != 0)
        {
            GV_DelayedFree(work->prims);
            work->has_alloc = 0;
        }
        else if (!WaterViewCreatePrims(work))
        {
            work->has_alloc = 1;
        }
    }

    if (work->has_alloc != 0)
    {
        WaterViewDraw(work);

        tile = &work->prims->tile2[GV_Clock];
        addPrim(&ot[0xFF], tile);

        priority = &work->prims->priority[GV_Clock];
        SetPriority(priority, 0, 1);
        addPrim(&ot[0xFF], priority);

        if (GV_PauseLevel == 0)
        {
            work->n_prims++;
        }
    }
}

static void Die(Work *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

/*---------------------------------------------------------------------------*/

static int GetResources(Work *work, int name, int map)
{
    work->color.r = 100;
    work->color.g = 128;
    work->color.b = 120;

    if (GCL_GetOption('b'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &work->bound[0]);
        GCL_StrToSV(GCL_GetParamResult(), &work->bound[1]);
    }

    if (GCL_GetOption('c'))
    {
        work->color.r = GCL_StrToInt(GCL_GetParamResult());
        work->color.g = GCL_StrToInt(GCL_GetParamResult());
        work->color.b = GCL_StrToInt(GCL_GetParamResult());
    }

    WaterViewInitSinTable();

    work->has_alloc = 0;
    return 0;
}

static int GetResources2(Work *work, SVECTOR *bounds, CVECTOR *color)
{
    work->bound[0] = bounds[0];
    work->bound[1] = bounds[1];

    work->color = *color;

    WaterViewInitSinTable();

    work->has_alloc = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewWaterView(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "wt_view.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return (void *)work;
}

void *NewWaterView2(int name, int where, SVECTOR *bounds, CVECTOR *color)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "wt_view.c");

        if (GetResources2(work, bounds, color) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return (void *)work;
}

/*---------------------------------------------------------------------------*/

static int WaterViewCreatePrims(Work *work)
{
    WaterViewPrims *prims;
    TILE           *tile;
    TILE           *tile2;

    prims = GV_Malloc(sizeof(WaterViewPrims));
    work->prims = prims;
    if (!prims)
    {
        return -1;
    }

    SetupSprites1(prims->sprt[0], prims->sprt[1], &work->color);
    SetupSprites2(prims->sprt2[0], prims->sprt2[1], &work->color);

    SetDrawTPage(&prims->tpage[0], 0, 1, GetTPage(2, 0, 0, 0));
    SetDrawTPage(&prims->tpage[1], 0, 1, GetTPage(2, 0, 320, 0));
    SetDrawTPage(&prims->tpage[2], 0, 1, GetTPage(2, 0, 128, 0));
    SetDrawTPage(&prims->tpage[3], 0, 1, GetTPage(2, 0, 448, 0));

    tile = &work->prims->tile[0];
    SetTile(tile);

    tile->x0 = -160;
    tile->w = 320;
    tile->h = 6;

    tile->r0 = 0;
    tile->g0 = 0;
    tile->b0 = 0;

    tile[1] = tile[0];

    tile[0].y0 = -112;
    tile[1].y0 = 106;

    tile[2] = tile[0];
    tile[3] = tile[1];

    tile2 = &work->prims->tile2[0];
    setTile(tile2);

    tile2->x0 = -160;
    tile2->y0 = -112;
    tile2->w = 320;
    tile2->h = 224;

    tile2->r0 = 0;
    tile2->g0 = 0;
    tile2->b0 = 0;

    tile2[1] = tile2[0];

    return 0;
}

static void WaterViewInitSinTable(void)
{
    int i;

    for (i = 0; i < 32; i++)
    {
        wt_view_sin_table[i] = rsin(i * 128) / 1024;
    }
}

static void WaterViewDraw(Work *work)
{
    short *scratch1;
    short *scratch2;
    short *scratch3;
    short *scratch4;
    short *scratch5;
    char  *ot;
    int    i;
    SPRT  *sprt;
    int    nprims;
    int    count1, count2;

    ot = DG_ChanlOTag(0);

    addPrim(ot, &work->prims->tile[GV_Clock * 2 + 0]);
    addPrim(ot, &work->prims->tile[GV_Clock * 2 + 1]);

    scratch1 = (short *)0x1F800200;
    scratch2 = (short *)0x1F800400;

    nprims = work->n_prims;

    scratch3 = (short *)0x1F80000C;

    for (i = 6; i < 218; i += 2)
    {
        if (wt_view_sin_table[nprims & 0x1F] <= 0)
        {
            *scratch3 = wt_view_sin_table[nprims & 0x1F] + i;
            *scratch1++ = i;
        }
        else
        {
            *scratch3 = wt_view_sin_table[nprims & 0x1F] + i;
            *--scratch2 = i;
        }

        nprims++;
        scratch3 += 2;
    }

    scratch3 = (short *)SCRPAD_ADDR;

    nprims = 0;

    scratch4 = scratch1 - 256;
    count2 = scratch4 - scratch3;

    scratch1 = (short *)0x1F800200;

    scratch5 = scratch2 - 512;
    count1 = scratch3 - scratch5;

    sprt = work->prims->sprt2[GV_Clock];

    for (i = count2; i > 0; i--)
    {
        if ((*scratch1 - scratch3[*scratch1]) != 1)
        {
            sprt->y0 = *scratch1 - 112;
            sprt->v0 = scratch3[*scratch1];
            sprt->h = 2;
            scratch1++;

            addPrim(ot, sprt);

            sprt++;
        }
        else
        {
            nprims++;

            sprt->y0 = *scratch1 - 112;
            sprt->v0 = scratch3[*scratch1];
            sprt->h = 1;

            addPrim(ot, sprt);

            sprt++;

            sprt->y0 = *scratch1 - 111;
            sprt->v0 = scratch3[*scratch1] + 1;
            sprt->h = 1;
            scratch1++;
            addPrim(ot, sprt);

            sprt++;
        }
    }

    scratch2 = scratch3 - (count1 - 512);

    for (i = count1; i > 0; i--)
    {
        sprt->y0 = *scratch2 - 112;
        sprt->v0 = scratch3[*scratch2];
        sprt->h = 2;
        scratch2++;

        addPrim(ot, sprt);

        sprt++;
    }

    addPrim(ot, &work->prims->tpage[GV_Clock + 2]);

    scratch1 = scratch3 + 256;
    sprt = work->prims->sprt[GV_Clock];

    for (i = count2; i > 0; i--)
    {
        if ((*scratch1 - scratch3[*scratch1]) != 1)
        {
            sprt->y0 = *scratch1 - 112;
            sprt->v0 = scratch3[*scratch1];
            sprt->h = 2;
            scratch1++;

            addPrim(ot, sprt);

            sprt++;
        }
        else
        {
            nprims++;

            sprt->y0 = *scratch1 - 112;
            sprt->v0 = scratch3[*scratch1];
            sprt->h = 1;

            addPrim(ot, sprt);

            sprt++;

            sprt->y0 = *scratch1 - 111;
            sprt->v0 = scratch3[*scratch1] + 1;
            sprt->h = 1;

            scratch1++;

            addPrim(ot, sprt);

            sprt++;
        }
    }

    scratch2 = scratch3 - (count1 - 512);

    for (i = count1; i > 0; i--)
    {
        sprt->y0 = *scratch2 - 112;
        sprt->v0 = scratch3[*scratch2];
        sprt->h = 2;

        addPrim(ot, sprt);
        scratch2++;
        sprt++;
    }

    addPrim(ot, &work->prims->tpage[GV_Clock]);

    if (nprims > 16)
    {
        printf("(wt_view.c) Over prims !!!\n");
    }
}
