#include "game/game.h"

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
    SVECTOR  pos;
    SVECTOR *root_pos;
    int      depth;
    int      field_34;
    DG_PRIM *prim;
} Work;

#define EXEC_LEVEL 5

extern RECT s19b_dword_800C3988;

static void InitPacks(DG_PRIM *prim, DG_TEX *tex)
{
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;

    pack0 = &prim->packs[0]->poly_ft4;
    pack1 = &prim->packs[1]->poly_ft4;

    setPolyFT4(pack0);
    setSemiTrans(pack0, 1);
    setRGB0(pack0, 128, 128, 128);
    DG_SetPacketTexture4(pack0, tex);
    pack0->tpage = (pack0->tpage & ~0x60) | (1 << 5);
    *pack1 = *pack0;

    prim->raise = 1500;
}

static void ShadePacks(DG_PRIM *prim, int shade, int index)
{
    POLY_FT4 *pack;

    pack = &prim->packs[index]->poly_ft4;
    setRGB0(pack, shade, shade, shade);
}

static void Act(Work *work)
{
    GM_CurrentMap = work->map;
    
    work->pos.vx += s19b_dword_800DE658.pos.vx;
    work->pos.vy += s19b_dword_800DE658.pos.vy;
    work->depth += s19b_dword_800DE658.pos.vz;

    work->pos.vz = work->depth;

    if (work->field_34 & 0x1)
    {
        work->pos = *work->root_pos;
    }
    else if (work->depth > 32000)
    {
        GV_DestroyActor(work);
    }

    ShadePacks(work->prim, 128, GV_Clock);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, SVECTOR *root_pos, int tex_id, int unused)
{
    DG_PRIM *prim;

    work->root_pos = root_pos;

    work->map = GM_CurrentMap;
    work->pos = *root_pos;

    work->depth = work->pos.vz;
    if (work->depth > 16000)
    {
        work->depth -= 65536;
    }

    work->prim = prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, &work->pos, &s19b_dword_800C3988);
    if (!prim)
    {
        return -1;
    }

    InitPacks(prim, DG_GetTexture(tex_id));

    ShadePacks(prim, 128, 0);
    ShadePacks(prim, 128, 1);

    DG_SetPos(&DG_ZeroMatrix);
    DG_PutPrim(&work->prim->world);
    return 0;
}

void *NewJeepLamp(SVECTOR *root_pos, int tex_id, int unused)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "jlamp.c");

        if (GetResources(work, root_pos, tex_id, unused) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
