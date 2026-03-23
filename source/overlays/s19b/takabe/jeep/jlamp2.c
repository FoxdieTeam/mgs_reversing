#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    MATRIX  *root;
    DG_PRIM *prim;
} Work;

#define EXEC_LEVEL 7

SVECTOR lamp_falloff = {0, 0, 4096};
RECT lamp_rect = {200, 200, 400, 400};
SVECTOR lamp_position[] = {{330, 890, 1436}, {-330, 890, 1436}};

/* TODO: static */
static void InitPacks(DG_PRIM *prim, DG_TEX *tex)
{
    POLY_FT4 *packs0;
    POLY_FT4 *packs1;
    int       i;

    packs0 = &prim->packs[0]->poly_ft4;
    packs1 = &prim->packs[1]->poly_ft4;

    for (i = 2; i > 0; i--)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);
        setRGB0(packs0, 128, 128, 128);
        DG_SetPacketTexture4(packs0, tex);
        packs0->tpage = (packs0->tpage & ~0x60) | (1 << 5);
        *packs1 = *packs0;
        packs0++;
        packs1++;
    }

    prim->raise = 750;
}

static void ShadePacks(DG_PRIM *prim, int shade, int index)
{
    POLY_FT4 *packs;
    int       i;

    packs = &prim->packs[index]->poly_ft4;
    for (i = 2; i > 0; i--)
    {
        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}

static void Act(Work *work)
{
    SVECTOR   vertices[2];
    SVECTOR   scale;
    SVECTOR   diff;
    MATRIX   *eye;
    POLY_FT4 *packs;
    int       i;
    SVECTOR  *vertex;
    int       shade;

    GM_CurrentMap = work->map;

    eye = &DG_Chanl(0)->eye;

    DG_SetPos(work->root);
    DG_PutVector(work->prim->pos, vertices, 2);
    DG_RotVector(&lamp_falloff, &scale, 1);

    packs = &work->prim->packs[GV_Clock]->poly_ft4;
    for (i = 0; i < 2; i++)
    {
        vertex = &vertices[i];
        diff.vx = (vertex->vx - eye->t[0]) / 4;
        diff.vy = (vertex->vy - eye->t[1]) / 4;
        diff.vz = (vertex->vz - eye->t[2]) / 4;

        GV_LenVec3(&diff, &diff, GV_VecLen3(&diff), 4096);
        shade = (diff.vx * scale.vx + diff.vy * scale.vy + diff.vz * scale.vz) >> 12;
        if (shade < 0)
        {
            shade = -shade * 2;
            shade = (shade * shade) / 4096;
            shade = (shade * shade) / 4096;
            shade = (shade * shade) / 4096;
            shade /= 32;
            setRGB0(packs, shade, shade, shade);
        }
        else
        {
            setRGB0(packs, 0, 0, 0);
        }

        packs++;
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *root)
{
    DG_PRIM *prim;

    work->map = GM_CurrentMap;
    work->root = root;

    work->prim = prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 2, lamp_position, &lamp_rect);
    if (prim == NULL)
    {
        return -1;
    }

    InitPacks(prim, DG_GetTexture(PCX_HEAD_LIGHT));

    ShadePacks(prim, 128, 0);
    ShadePacks(prim, 128, 1);

    DG_SetPos(&DG_ZeroMatrix);
    DG_PutPrim(&work->prim->world);
    prim->root = root;
    return 0;
}

void *NewJeepLamp2(MATRIX *root)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "jlamp2.c");

        if (GetResources(work, root) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
