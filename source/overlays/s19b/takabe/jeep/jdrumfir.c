#include "strcode.h"
#include "game/game.h"
#include "takabe/prim.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x18];
    SVECTOR  field_38;
    int      field_40;
    char     pad4[0x1C];
    OBJECT  *body;
    char     pad5[0x18];
    int      field_7C;
    MATRIX   world;
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL 5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX   world;
    MATRIX  *root;
    int      field_50;
    int      field_54;
    int      field_58;
    int      field_5C;
    int      field_60;
    SVECTOR  vertices[16];
    SVECTOR  speeds[16];
} Work;

void s19b_jdrumfir_800CA4A0(Work *work);
void s19b_jdrumfir_800CA564(Work *work, int);

void s19b_jdrumfir_800CA13C(Work *work)
{
    GM_CurrentMap = work->map;

    work->prim->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->prim->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->prim->world.t[2] += Takabe_JeepSystem.pos.vz;

    if (work->prim->world.t[2] > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->field_50 & 1)
    {
        work->world = *work->root;
    }

    if (work->field_54 > 0)
    {
        s19b_jdrumfir_800CA564(work, 1);
    }
    else
    {
        s19b_jdrumfir_800CA564(work, 1);

        if (work->field_58 == 0)
        {
            GV_DestroyActor(work);
            return;
        }

        work->field_58--;
    }

    work->field_54--;
}

void s19b_jdrumfir_800CA280(Work *work)
{
    GM_FreePrim(work->prim);
}

int s19b_jdrumfir_800CA2BC(Work *work, MATRIX *world, int arg2, int arg3)
{
    work->root = world;
    work->map = GM_CurrentMap;
    work->world = *world;

    work->field_50 = arg2;
    work->field_54 = arg3;

    s19b_jdrumfir_800CA4A0(work);
    work->field_58 = 40;
    return 0;
}

void *NewJeepDrumFire(MATRIX *world, int arg1, int arg2)
{
    Work* work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jdrumfir_800CA13C, s19b_jdrumfir_800CA280, "jdrumfir.c");

        if (s19b_jdrumfir_800CA2BC(work, world, arg1, arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

void s19b_jdrumfir_800CA3E8(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int x, y, w, h;

    while (--n_packs != -1)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;
        packs->u0 = packs->u2 = x;
        packs->u1 = packs->u3 = x + (w + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h;
        packs->v0 = packs->v1 = y;
        packs->v2 = packs->v3 = y + (h + 1) / 4 - 1;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= (3 << 5);

        setRGB0(packs, 0, 0, 0);
        packs++;
    }
}

void s19b_jdrumfir_800CA4A0(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = work->tex = DG_GetTexture(PCX_FIRE2);
    prim = work->prim = Takabe_MakeIndividualRect3DPrim(16, work->vertices);

    s19b_jdrumfir_800CA3E8(prim->packs[0], tex, 16);
    s19b_jdrumfir_800CA3E8(prim->packs[1], tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->raise = 500;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA564.s")
