#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    char     pad1[0x4];
    DG_PRIM *prim;
    int      field_2C;
    SVECTOR  field_30[17];
    SVECTOR  vertices[68];
    SVECTOR  field_2D8;
    SVECTOR  field_2E0;
    SVECTOR  field_2E8;
    int      field_2F0[17];
    int      field_334[17];
    int      field_378[17];
    int      field_3BC;
    int      field_3C0;
} Work;

#define EXEC_LEVEL GV_ACTOR_PREV

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

    work->field_2D8 = *a;
    work->field_2E0 = *b;
    d = s08b_plasma_l_800D98F4(&work->field_2D8, &work->field_2E0, &work->field_2E8);
    work->field_2C = d;
    q = d / 4;

    work->field_2F0[0]  = GV_RandU(0x1000);
    work->field_2F0[4]  = GV_RandU(0x200);
    work->field_334[4]  = GV_RandU(0x400);
    work->field_378[4]  = q * GV_RandU(0x1000) / 4096;
    work->field_2F0[8]  = work->field_2F0[4] + GV_RandS(0x200);
    work->field_334[8]  = GV_RandU(0x400) + 0x400;
    r = GV_RandU(0x1000) * 2;
    work->field_378[8]  = q * r / 4096;
    work->field_2F0[12] = work->field_2F0[8] + GV_RandS(0x200);
    work->field_334[12] = GV_RandU(0x400) + 0x800;
    work->field_378[12] = q * GV_RandU(0x1000) / 4096;
    work->field_2F0[16] = work->field_2F0[12] + GV_RandS(0x200);

    if (work->field_334[8] < work->field_334[4])
        work->field_334[4] = work->field_334[8];
    if (work->field_334[12] < work->field_334[4])
        work->field_334[4] = work->field_334[12];
    if (work->field_334[12] < work->field_334[8])
        work->field_334[8] = work->field_334[12];

    work->field_30[0]  = work->field_2D8;
    work->field_30[16] = work->field_2E0;
    work->field_334[0]  = 0;
    work->field_334[16] = 0x1000;
    work->field_378[0]  = 0;
    work->field_378[16] = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800D9C98.s")
void s08b_plasma_l_800D9F1C(Work *work, int arg1, int arg2)
{
    int v1, v2;

    v1 = arg1 - arg2;
    v2 = arg1 + arg2;

    work->field_334[arg1] = work->field_334[v1] + ((work->field_334[v2] - work->field_334[v1]) * 3) / 4;
    work->field_378[arg1] = work->field_378[v1] + (work->field_378[v2] - work->field_378[v1]) / 2;
    work->field_2F0[arg1] = work->field_2F0[v1] + (work->field_2F0[v2] - work->field_2F0[v1]) / 2;
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

int s08b_plasma_l_800DA394(Work *work, int arg1, int arg2, int arg3)
{
    work->field_3C0 = arg3;
    work->map = GM_CurrentMap;
    if (s08b_plasma_l_800DA2C8(work) < 0)
    {
        return -1;
    }
    s08b_plasma_l_800D9A90(work, (SVECTOR *)arg1, (SVECTOR *)arg2);
    work->field_3BC = 0;
    return 0;
}

void *NewPlasmaL(int arg0, int arg1, int arg2)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s08b_plasma_l_800D9FB4, s08b_plasma_l_800DA28C, "plasma_l.c");

        if (s08b_plasma_l_800DA394(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
