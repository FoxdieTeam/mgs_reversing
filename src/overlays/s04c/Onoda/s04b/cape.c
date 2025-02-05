#include "common.h"
#include "Game/game.h"

typedef struct _CapeWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    GV_PAD  *pad;
    SVECTOR  verts[4][6][4]; // TODO: is this one big array here?
    SVECTOR  f328[4];
    SVECTOR  f348[4][7];
    SVECTOR  f428[4][7];
    SVECTOR  f508[4][7];
    SVECTOR  f5E8[5][7];
    int      f700[4][7];
    int      f770[4][7];
    SVECTOR *f7E0;
    SVECTOR *f7E4;
    int      f7E8[4];
    int      f7F8[4];
    CVECTOR  f808[5][7];
    CVECTOR  f894[4][7];
    CVECTOR  f904[4][7];
    char     pad2[0xFC];
    int      fA70;
    MATRIX  *light;
    MATRIX  *color;
    SVECTOR  fA7C;
} CapeWork;

extern GV_PAD GV_PadData_800B05C0[4];

#define EXEC_LEVEL GV_ACTOR_LEVEL5


void s04c_cape_800D7938(CapeWork *work)
{
    int i;
    int count;

    for (i = 0; i < 4; i++)
    {
        work->f328[i].vx = -300;
        work->f328[i].vy = -300;
    }

    count = 2;

    for (i = 0; i < count; i++)
    {
        work->f328[i].vz = ((count - i) * 2 - 1) * 20;
    }

    for (i = 0; i < count; i++)
    {
        work->f328[i + count].vz = -20 - i * 40;
    }
}

void s04c_cape_800D79C8(CapeWork *work)
{
    SVECTOR sp10;
    MATRIX  sp18;
    SVECTOR sp38;
    int     i;

    sp10.vx = work->f7E4->vx;
    sp10.vy = work->f7E4->vy - 1024;
    sp10.vz = work->f7E4->vz;

    sp38.vx = -300;
    sp38.vy = -300;
    sp38.vz = 0;

    RotMatrix(&sp10, &sp18);

    for (i = 0; i < 4; i++)
    {
        ApplyMatrixSV(&sp18, &work->f328[i], &work->f348[i][0]);
        ApplyMatrixSV(&sp18, &sp38, &work->fA7C);

        work->f348[i][0].vx += work->f7E0->vx;
        work->f348[i][0].vy += work->f7E0->vy;
        work->f348[i][0].vz += work->f7E0->vz;

        work->fA7C.vx += work->f7E0->vx;
        work->fA7C.vy += work->f7E0->vy;
        work->fA7C.vz += work->f7E0->vz;
    }
}

void s04c_cape_800D7B2C(CapeWork *work)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 1; j < 7; j++)
        {
            work->f348[i][j].vx = work->f348[i][j - 1].vx;
            work->f348[i][j].vy = work->f348[i][j - 1].vy - 30;
            work->f348[i][j].vz = work->f348[i][j - 1].vz;
            work->f700[i][j] = 0;
            work->f770[i][j] = 0;
        }
    }
}

void s04c_cape_800D7BB4(CapeWork *work)
{
    int a, b, c, d, e, f, g;
    int i, j;

    a = (rcos(work->f7E4->vy - 1024) * 20) >> 12;
    b = (rsin(work->f7E4->vy - 1024) * 20) >> 12;

    for (i = 0; i < 4; i++)
    {
        work->f428[i][0].vx = work->f348[i][0].vx + b;
        work->f508[i][0].vx = work->f348[i][0].vx - b;

        work->f428[i][0].vy = work->f348[i][0].vy;
        work->f508[i][0].vy = work->f348[i][0].vy;

        work->f428[i][0].vz = work->f348[i][0].vz + a;
        work->f508[i][0].vz = work->f348[i][0].vz - a;

        for (j = 1; j < 7; j++)
        {
            c = (j * 64 * rsin(work->f7E8[i] + j * 64)) >> 12;
            d = rcos(c);

            e = (rsin(c) * 20) >> 12;
            work->f428[i][j].vy = work->f348[i][j].vy + e;
            work->f508[i][j].vy = work->f348[i][j].vy - e;

            f = (b * d) >> 12;
            work->f428[i][j].vx = work->f348[i][j].vx + f;
            work->f508[i][j].vx = work->f348[i][j].vx - f;

            g = (a * d) >> 12;
            work->f428[i][j].vz = work->f348[i][j].vz + g;
            work->f508[i][j].vz = work->f348[i][j].vz - g;
        }

        if (work->f7E8[i] == 4096)
        {
            work->f7E8[i] = 0;
        }
    }
}

void s04c_cape_800D7D90(CapeWork *work)
{
    int i, j;

    for (i = 0; i < 7; i++)
    {
        work->f5E8[0][i].vx = work->f428[0][i].vx;
        work->f5E8[0][i].vy = work->f428[0][i].vy;
        work->f5E8[0][i].vz = work->f428[0][i].vz;

        work->f5E8[4][i].vx = work->f508[3][i].vx;
        work->f5E8[4][i].vy = work->f508[3][i].vy;
        work->f5E8[4][i].vz = work->f508[3][i].vz;

        for (j = 1; j < 4; j++)
        {
            work->f5E8[j][i].vx = (work->f508[j - 1][i].vx + work->f428[j][i].vx) / 2;
            work->f5E8[j][i].vy = (work->f508[j - 1][i].vy + work->f428[j][i].vy) / 2;
            work->f5E8[j][i].vz = (work->f508[j - 1][i].vz + work->f428[j][i].vz) / 2;
        }
    }
}

void s04c_cape_800D7E6C(CapeWork *work)
{
    VECTOR  in0;
    VECTOR  in1;
    VECTOR  cross;
    SVECTOR normal;
    CVECTOR color;
    int     i, j;
    int     r, g, b;

    SetLightMatrix(work->light);
    SetColorMatrix(work->color);

    for (i = 0; i < 4; i++)
    {
        for (j = 1; j < 7; j++)
        {
            in0.vx = work->f5E8[i][j - 1].vx / 2 - work->f5E8[i + 1][j - 1].vx / 2;
            in0.vy = work->f5E8[i][j - 1].vy / 2 - work->f5E8[i + 1][j - 1].vy / 2;
            in0.vz = work->f5E8[i][j - 1].vz / 2 - work->f5E8[i + 1][j - 1].vz / 2;

            in1.vx = work->f5E8[i + 1][j].vx / 2 - work->f5E8[i + 1][j - 1].vx / 2;
            in1.vy = work->f5E8[i + 1][j].vy / 2 - work->f5E8[i + 1][j - 1].vy / 2;
            in1.vz = work->f5E8[i + 1][j].vz / 2 - work->f5E8[i + 1][j - 1].vz / 2;

            OuterProduct0(&in0, &in1, &cross);
            VectorNormalS(&cross, &normal);

            color.r = 128;
            color.g = 128;
            color.b = 128;

            NormalColorCol(&normal, &color, &work->f808[i + 1][j]);
        }
    }

    work->f894[0][0].r = work->f808[1][1].r;
    work->f894[0][0].g = work->f808[1][1].g;
    work->f894[0][0].b = work->f808[1][1].b;

    for (j = 1; j < 6; j++)
    {
        work->f894[0][j].r = (work->f808[1][j].r + work->f808[1][j + 1].r) / 2;
        work->f894[0][j].g = (work->f808[1][j].g + work->f808[1][j + 1].g) / 2;
        work->f894[0][j].b = (work->f808[1][j].b + work->f808[1][j + 1].b) / 2;
    }

    work->f894[0][6].r = work->f808[1][6].r;
    work->f894[0][6].g = work->f808[1][6].g;
    work->f894[0][6].b = work->f808[1][6].b;

    for (i = 1; i < 4; i++)
    {
        work->f894[i][0].r = (work->f808[i][1].r + work->f808[i + 1][1].r) / 2;
        work->f894[i][0].g = (work->f808[i][1].g + work->f808[i + 1][1].g) / 2;
        work->f894[i][0].b = (work->f808[i][1].b + work->f808[i + 1][1].b) / 2;

        for (j = 1; j < 6; j++)
        {
            r = work->f808[i][j].r + work->f808[i][j + 1].r + work->f808[i + 1][j].r + work->f808[i + 1][j + 1].r;
            work->f894[i][j].r = r / 4;

            g = work->f808[i][j].g + work->f808[i][j + 1].g + work->f808[i + 1][j].g + work->f808[i + 1][j + 1].g;
            work->f894[i][j].g = g / 4;

            b = work->f808[i][j].b + work->f808[i][j + 1].b + work->f808[i + 1][j].b + work->f808[i + 1][j + 1].b;
            work->f894[i][j].b = b / 4;
        }

        work->f894[i][6].r = (work->f808[i][6].r + work->f808[i + 1][6].r) / 2;
        work->f894[i][6].g = (work->f808[i][6].g + work->f808[i + 1][6].g) / 2;
        work->f894[i][6].b = (work->f808[i][6].b + work->f808[i + 1][6].b) / 2;
    }

    work->f904[0][0].r = work->f808[4][1].r;
    work->f904[0][0].g = work->f808[4][1].g;
    work->f904[0][0].b = work->f808[4][1].b;

    for (j = 1; j < 6; j++)
    {
        work->f904[0][j].r = (work->f808[4][j].r + work->f808[4][j + 1].r) / 2;
        work->f904[0][j].g = (work->f808[4][j].g + work->f808[4][j + 1].g) / 2;
        work->f904[0][j].b = (work->f808[4][j].b + work->f808[4][j + 1].b) / 2;
    }

    work->f904[0][6].r = work->f808[4][6].r;
    work->f904[0][6].g = work->f808[4][6].g;
    work->f904[0][6].b = work->f808[4][6].b;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_cape_800D83D4.s")
void s04c_cape_800D83D4(CapeWork *work);

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_cape_800D8724.s")
void s04c_cape_800D8724(CapeWork *work);

void CapeAct_800D8FF8(CapeWork *work)
{
    work->fA70 = 0;
    s04c_cape_800D79C8(work);
    s04c_cape_800D8724(work);
    s04c_cape_800D7D90(work);
    s04c_cape_800D7E6C(work);
    s04c_cape_800D83D4(work);
}

void CapeDie_800D9040(CapeWork* work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

static inline void CapeInitPack(POLY_GT4 *poly, DG_TEX *tex)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

int CapeGetResources_800D907C(CapeWork *work, SVECTOR *arg1, SVECTOR *arg2, MATRIX *light, MATRIX *color)
{
    DG_PRIM  *prim;
    POLY_GT4 *packs0;
    POLY_GT4 *packs1;
    DG_TEX   *tex;
    int       i;

    work->f7E0 = arg1;
    work->f7E4 = arg2;
    work->light = light;
    work->color = color;

    work->pad = &GV_PadData_800B05C0[0];

    prim = DG_GetPrim(DG_PRIM_POLY_GT4, 24, 0, (SVECTOR *)work->verts, NULL);
    work->prim = prim;

    packs0 = &prim->packs[0]->poly_gt4;
    packs1 = &prim->packs[1]->poly_gt4;

    tex = DG_GetTexture(GV_StrCode("oce_skirt1"));

    for (i = 0; i < 24; i++)
    {
        SetPolyGT4(packs0);
        SetPolyGT4(packs1);

        CapeInitPack(packs0, tex);
        CapeInitPack(packs1, tex);

        setRGB0(packs0, 128, 128, 128);
        setRGB1(packs0, 128, 128, 128);
        setRGB2(packs0, 128, 128, 128);
        setRGB3(packs0, 128, 128, 128);

        setRGB0(packs1, 128, 128, 128);
        setRGB1(packs1, 128, 128, 128);
        setRGB2(packs1, 128, 128, 128);
        setRGB3(packs1, 128, 128, 128);

        packs0++;
        packs1++;
    }

    work->fA70 = 0;

    for (i = 0; i < 4; i++)
    {
        work->f7E8[i] = 0;
        work->f7F8[i] = 5;
    }

    s04c_cape_800D7938(work);
    s04c_cape_800D79C8(work);
    s04c_cape_800D7B2C(work);
    s04c_cape_800D7BB4(work);
    s04c_cape_800D7D90(work);
    s04c_cape_800D7E6C(work);
    s04c_cape_800D83D4(work);
    return 0;
}

void *NewCape_800D92F8(SVECTOR *arg0, SVECTOR *arg1, MATRIX *light, MATRIX *color)
{
    CapeWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(CapeWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, CapeAct_800D8FF8, CapeDie_800D9040, "cape.c");

        if (CapeGetResources_800D907C(work, arg0, arg1, light, color) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
