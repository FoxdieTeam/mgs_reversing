#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _WaterViewPrims
{
    DR_TPAGE tpage[4];
    char     pad[0x18];
    SPRT     sprt[2][122];
    SPRT     sprt2[2][122];
    TILE     tile[4];
    TILE     tile2[2];
} WaterViewPrims;

typedef struct _WaterViewWork
{
    GV_ACT          actor;
    int             map;
    int             name;
    SVECTOR         f28;
    SVECTOR         f30;
    WaterViewPrims *prims;
    CVECTOR         color;
    int             f40;
    char            pad2[0x4];
    int             f48;
} WaterViewWork;

extern int     GV_Clock_800AB920;
extern int     GV_PauseLevel_800AB928;
extern DG_CHNL DG_Chanls_800B1800[3];

// TODO: can't find the signature of this function in PsyQ headers
void SetPriority(void *prim, int, int);

int  WaterView_800DBEB8(WaterViewWork *work);
void WaterView_800DC0CC(void);
void WaterView_800DC128(WaterViewWork *work);

static short wt_view_sin_table[32];

#define EXEC_LEVEL 3

void WaterView_800DB800(SPRT *sa, SPRT *sb, CVECTOR *color)
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

void WaterView_800DB8F4(SPRT *sa, SPRT *sb, CVECTOR *color)
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

static inline int WaterViewActHelper_800DB9E8(WaterViewWork *work, short x, short y, short z)
{
    if ((x > work->f28.vx) && (x < work->f30.vx) && (y > work->f28.vy) && (y < work->f30.vy) && (z > work->f28.vz) &&
        (z < work->f30.vz))
    {
        return 1;
    }

    return 0;
}

void WaterViewAct_800DB9E8(WaterViewWork *work)
{
    SVECTOR  sp10;
    u_long  *ot;
    SVECTOR *vec;
    MATRIX  *eye;
    short    x, y, z;
    TILE    *tile;
    void    *prim2;

    ot = (u_long *)DG_ChanlOTag(0);

    vec = &sp10;
    eye = &DG_Chanls_800B1800[1].field_30_eye;

    vec->vx = x = eye->t[0];
    vec->vy = y = eye->t[1];
    vec->vz = z = eye->t[2];

    if (WaterViewActHelper_800DB9E8(work, x, y, z) != work->f40)
    {
        if (work->f40 != 0)
        {
            GV_DelayedFree_80016254(work->prims);
            work->f40 = 0;
        }
        else if (!WaterView_800DBEB8(work))
        {
            work->f40 = 1;
        }
    }

    if (work->f40 != 0)
    {
        WaterView_800DC128(work);

        tile = &work->prims->tile2[GV_Clock_800AB920];
        addPrim(&ot[0xFF], tile);

        prim2 = (char *)work->prims + 0x20 + GV_Clock_800AB920 * 12;
        SetPriority(prim2, 0, 1);
        addPrim(&ot[0xFF], prim2);

        if (GV_PauseLevel_800AB928 == 0)
        {
            work->f48++;
        }
    }
}

void WaterViewDie_800DBBF0(WaterViewWork *work)
{
    if (work->prims)
    {
        GV_DelayedFree_80016254(work->prims);
    }
}

int WaterViewGetResources_800DBC20(WaterViewWork *work, int unused, int unused2)
{
    work->color.r = 100;
    work->color.g = 128;
    work->color.b = 120;

    if (GCL_GetOption_80020968('b'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f28);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f30);
    }

    if (GCL_GetOption_80020968('c'))
    {
        work->color.r = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.g = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.b = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    WaterView_800DC0CC();

    work->f40 = 0;
    return 0;
}

int WaterViewGetResources_800DBCE4(WaterViewWork *work, SVECTOR *arg1, CVECTOR *color)
{
    work->f28 = arg1[0];
    work->f30 = arg1[1];

    work->color = *color;

    WaterView_800DC0CC();

    work->f40 = 0;
    return 0;
}

GV_ACT * NewWaterView_800DBD68(int name, int where, int argc, char **argv)
{
    WaterViewWork *work;

    work = (WaterViewWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WaterViewWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WaterViewAct_800DB9E8,
                                  (TActorFunction)WaterViewDie_800DBBF0, "wt_view.c");

        if (WaterViewGetResources_800DBC20(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return &work->actor;
}

GV_ACT *NewWaterView_800DBE04(int name, int where, SVECTOR *arg2, CVECTOR *color)
{
    WaterViewWork *work;

    work = (WaterViewWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WaterViewWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WaterViewAct_800DB9E8,
                                  (TActorFunction)WaterViewDie_800DBBF0, "wt_view.c");

        if (WaterViewGetResources_800DBCE4(work, arg2, color) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return &work->actor;
}

int WaterView_800DBEB8(WaterViewWork *work)
{
    WaterViewPrims *prims;
    TILE           *tile;
    TILE           *tile2;

    prims = GV_Malloc_8001620C(sizeof(WaterViewPrims));
    work->prims = prims;
    if (!prims)
    {
        return -1;
    }

    WaterView_800DB800(prims->sprt[0], prims->sprt[1], &work->color);
    WaterView_800DB8F4(prims->sprt2[0], prims->sprt2[1], &work->color);

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

void WaterView_800DC0CC(void)
{
    int i;

    for (i = 0; i < 32; i++)
    {
        wt_view_sin_table[i] = rsin(i * 128) / 1024;
    }
}

void WaterView_800DC128(WaterViewWork *work)
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

    addPrim(ot, &work->prims->tile[GV_Clock_800AB920 * 2 + 0]);
    addPrim(ot, &work->prims->tile[GV_Clock_800AB920 * 2 + 1]);

    scratch1 = (short *)0x1F800200;
    scratch2 = (short *)0x1F800400;

    nprims = work->f48;

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

    scratch3 = (short *)0x1F800000;

    nprims = 0;

    scratch4 = scratch1 - 256;
    count2 = scratch4 - scratch3;

    scratch1 = (short *)0x1F800200;

    scratch5 = scratch2 - 512;
    count1 = scratch3 - scratch5;

    sprt = work->prims->sprt2[GV_Clock_800AB920];

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

    addPrim(ot, &work->prims->tpage[GV_Clock_800AB920 + 2]);

    scratch1 = scratch3 + 256;
    sprt = work->prims->sprt[GV_Clock_800AB920];

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

    addPrim(ot, &work->prims->tpage[GV_Clock_800AB920]);

    if (nprims > 16)
    {
        printf("(wt_view.c) Over prims !!!\n");
    }
}
