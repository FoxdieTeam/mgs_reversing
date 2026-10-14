#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           /* 0x20 */
    char     pad_24[0x4];
    DG_PRIM *prim;          /* 0x28 */
    int      length;        /* 0x2C: distance between start and end */
    SVECTOR  points[17];    /* 0x30 */
    SVECTOR  vertices[68];  /* 0xB8 */
    SVECTOR  start;         /* 0x2D8 */
    SVECTOR  end;           /* 0x2E0 */
    SVECTOR  rot;           /* 0x2E8: direction from start to end */
    int      angle[17];     /* 0x2F0: per point, around the line */
    int      pos[17];       /* 0x334: per point, along the line (0..4096) */
    int      radius[17];    /* 0x378: per point, distance from the line */
    int      time;          /* 0x3BC */
    int      max_time;      /* 0x3C0 */
} Work;

int s08b_plasma_l_800D98F4(SVECTOR *a, SVECTOR *b, SVECTOR *out)
{
    int dx = (a->vx - b->vx) / 16;
    int dy = (a->vy - b->vy) / 16;
    int dz = (a->vz - b->vz) / 16;
    int dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
    int d  = dist << 4;
    int ex = b->vx - a->vx;
    int ez = b->vz - a->vz;
    int ey = b->vy - a->vy;

    out->vy = ratan2(ex, ez) & 0xFFF;
    out->vx = ratan2(d, ey) & 0xFFF;
    out->vz = 0;
    return d;
}

void s08b_plasma_l_800D9A00(Work *work, POLY_FT4 *packs, int count, DG_TEX *tex)
{
    (void)work;
    while (--count >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 0xFF, 0xFF, 0xFF);
        DG_SetPacketTexture4(packs, tex);
        packs->tpage |= 0x20;
        packs++;
    }
}

void s08b_plasma_l_800D9A90(Work *work, SVECTOR *a, SVECTOR *b)
{
    int d;
    int q;
    int r;

    work->start = *a;
    work->end = *b;
    d = s08b_plasma_l_800D98F4(&work->start, &work->end, &work->rot);
    work->length = d;
    q = d / 4;

    work->angle[0]  = GV_RandU(0x1000);
    work->angle[4]  = GV_RandU(0x200);
    work->pos[4]  = GV_RandU(0x400);
    work->radius[4]  = q * GV_RandU(0x1000) / 4096;
    work->angle[8]  = work->angle[4] + GV_RandS(0x200);
    work->pos[8]  = GV_RandU(0x400) + 0x400;
    r = GV_RandU(0x1000) * 2;
    work->radius[8]  = q * r / 4096;
    work->angle[12] = work->angle[8] + GV_RandS(0x200);
    work->pos[12] = GV_RandU(0x400) + 0x800;
    work->radius[12] = q * GV_RandU(0x1000) / 4096;
    work->angle[16] = work->angle[12] + GV_RandS(0x200);

    if (work->pos[8] < work->pos[4])
        work->pos[4] = work->pos[8];
    if (work->pos[12] < work->pos[4])
        work->pos[4] = work->pos[12];
    if (work->pos[12] < work->pos[8])
        work->pos[8] = work->pos[12];

    work->points[0]  = work->start;
    work->points[16] = work->end;
    work->pos[0]  = 0;
    work->pos[16] = 0x1000;
    work->radius[0]  = 0;
    work->radius[16] = 0;
}

void s08b_plasma_l_800D9C98(Work *work)
{
    int q;

    q = work->length / 4;

    work->angle[0] += GV_RandS(0x80);
    work->angle[4] += GV_RandS(0x40);
    work->pos[4] += GV_RandS(0x20);

    work->radius[4] += GV_RandS(0x20);
    if (work->radius[4] < 0)
        work->radius[4] = 0;
    if (q < work->radius[4])
        work->radius[4] = q;

    work->angle[8] += GV_RandS(0x40);
    if (work->angle[4] + 0x200 < work->angle[8])
        work->angle[8] = work->angle[4] + GV_RandS(0x200);
    if (work->angle[8] < work->angle[4] - 0x200)
        work->angle[8] = work->angle[4] + GV_RandS(0x200);

    work->pos[8] += GV_RandS(0x20);

    {
        int r = GV_RandS(0x40);
        int t = work->radius[8] + 0x10;
        work->radius[8] = t + r;
    }
    if (work->radius[8] < 0)
        work->radius[8] = 0;
    if (q < work->radius[8])
        work->radius[8] = q;

    work->angle[12] += GV_RandS(0x40);
    if (work->angle[8] + 0x200 < work->angle[12])
        work->angle[12] = work->angle[8] + GV_RandS(0x200);
    if (work->angle[12] < work->angle[8] - 0x200)
        work->angle[12] = work->angle[8] + GV_RandS(0x200);

    work->pos[12] += GV_RandS(0x20);

    work->radius[12] += GV_RandS(0x20);
    if (work->radius[12] < 0)
        work->radius[12] = 0;
    if (q * 2 < work->radius[12])
        work->radius[12] = q * 2;

    if (work->pos[8] < work->pos[4])
    {
        int t = work->pos[4];
        work->pos[4] = work->pos[8];
        work->pos[8] = t;
    }
    if (work->pos[12] < work->pos[4])
    {
        int t = work->pos[4];
        work->pos[4] = work->pos[12];
        work->pos[12] = t;
    }
    if (work->pos[12] < work->pos[8])
    {
        int t = work->pos[8];
        work->pos[8] = work->pos[12];
        work->pos[12] = t;
    }
}
void s08b_plasma_l_800D9F1C(Work *work, int index, int step)
{
    int v1, v2;

    v1 = index - step;
    v2 = index + step;

    work->pos[index] = work->pos[v1] + ((work->pos[v2] - work->pos[v1]) * 3) / 4;
    work->radius[index] = work->radius[v1] + (work->radius[v2] - work->radius[v1]) / 2;
    work->angle[index] = work->angle[v1] + (work->angle[v2] - work->angle[v1]) / 2;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800D9FB4.s")
void s08b_plasma_l_800D9FB4(Work *);

void s08b_plasma_l_800DA28C(Work *work)
{
    GM_FreePrim(work->prim);
}

int s08b_plasma_l_800DA2C8(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (tex == NULL)
    {
        return -1;
    }

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 17, work->vertices, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = 200;

    s08b_plasma_l_800D9A00(work, prim->packs[0], 17, tex);
    s08b_plasma_l_800D9A00(work, prim->packs[1], 17, tex);
    return 0;
}

int s08b_plasma_l_800DA394(Work *work, SVECTOR *start, SVECTOR *end, int time)
{
    work->max_time = time;
    work->map = GM_CurrentMap;
    if (s08b_plasma_l_800DA2C8(work) < 0)
    {
        return -1;
    }
    s08b_plasma_l_800D9A90(work, start, end);
    work->time = 0;
    return 0;
}

void *NewPlasmaL(SVECTOR *start, SVECTOR *end, int time)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s08b_plasma_l_800D9FB4, s08b_plasma_l_800DA28C, "plasma_l.c");

        if (s08b_plasma_l_800DA394(work, start, end, time) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
