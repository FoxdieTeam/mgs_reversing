#include "game/game.h"
#include "strcode.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
} JEEP_SYSTEM;

extern JEEP_SYSTEM s19b_dword_800DE658; // Takabe_JeepSystem

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  speeds[24];
    SVECTOR  vertices[96];
    int      count;
} Work;

#define EXEC_LEVEL 5

void MovePacks(SVECTOR *speeds, SVECTOR *vertices, int count)
{
    int rx, ry, rz;
    int x, y;

    while (--count >= 0)
    {
        rx = GV_RandS(256);
        ry = GV_RandS(256);
        rz = GV_RandU(80);

        vertices[0].vz = vertices[1].vz = vertices[2].vz = vertices[3].vz = rz;

        x = GV_RandU(64);
        y = GV_RandU(64);
        vertices[0].vx = rx + x;
        vertices[0].vy = ry + y;

        x = GV_RandU(64);
        y = GV_RandU(64);
        vertices[3].vx = rx - x;
        vertices[3].vy = ry - y;

        x = GV_RandU(64);
        y = GV_RandU(64);
        vertices[1].vx = rx + x;
        vertices[1].vy = ry - y;

        x = GV_RandU(64);
        y = GV_RandU(64);
        vertices[2].vx = rx - x;
        vertices[2].vy = ry + y;

        speeds->vx = rx / 4;
        speeds->vz = GV_RandU(256) + 150;
        speeds->vy = ry / 4;

        vertices += 4;
        speeds++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_gsplash3_800D00F4.s")
void s19b_gsplash3_800D00F4(SVECTOR *, SVECTOR *, int);

void InitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        DG_SetPacketTexture4(packs0, tex);
        DG_SetPacketTexture4(packs1, tex);

        packs0++;
        packs1++;
    }
}

void ShadePacks(POLY_FT4 *packs, int n_packs, short shade)
{
    int color;
    int i;

    shade *= 4;

    color = MAKE_RGB(shade, shade, shade);
    for (i = n_packs - 1; i >= 0; i--)
    {
        LSTORE((LLOAD(&packs->r0) & RGBA_A_MASK) | color, &packs->r0);
        packs++;
    }
}

static void Act(Work *work)
{
    short    count;
    short    shade;
    DG_PRIM *prim;

    GM_CurrentMap = work->map;

    count = --work->count;
    if (count <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    s19b_gsplash3_800D00F4(work->speeds, work->vertices, 24);

    prim = work->prim;
    shade = 100 + count * 5;
    if (shade > 255)
    {
        ShadePacks(prim->packs[GV_Clock], 24, 255);
    }
    else
    {
        ShadePacks(prim->packs[GV_Clock], 24, shade);
    }

    prim->world.t[0] += s19b_dword_800DE658.pos.vx;
    prim->world.t[1] += s19b_dword_800DE658.pos.vy;
    prim->world.t[2] += s19b_dword_800DE658.pos.vz;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap;

    MovePacks(work->speeds, work->vertices, 24);

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 24, work->vertices, NULL);
    if (!prim)
    {
        return -1;
    }

    DG_SetPos(world);
    DG_PutPrim(&prim->world);

    prim->raise = 500;

    tex = DG_GetTexture(PCX_M19_C2_GLASS1HLF);
    if (!tex)
    {
        return -1;
    }

    InitPacks(prim->packs[0], prim->packs[1], 24, tex);
    ShadePacks(prim->packs[GV_Clock], 24, 255);

    work->count = 24;
    return 0;
}

void *NewGlassSplash3(MATRIX *world)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "gsplash3.c");

        if (GetResources(work, world) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

// new file

extern int s19b_dword_800DE5D0;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0648.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D06E0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D072C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D07EC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D087C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D08C8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D08F0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0928.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D094C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0970.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0990.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D09B8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D09DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0A20.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0ABC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0C44.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0CE0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0D40.s")

void s19b_jlamp_800D0FE4(int arg0)
{
    s19b_dword_800DE5D0 = arg0;
}

// blur.c

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0FF0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D1190.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D173C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D18B0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D18E0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D19F8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D1AA0.s")
