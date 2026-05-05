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
    char     pad2[0x8];
    SVECTOR  field_2E8;
    int      field_2F0[17];
    int      field_334[17];
    int      field_378[17];
    int      field_3BC;
    int      field_3C0;
} Work;

#define EXEC_LEVEL 4

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800D98F4.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800D9A00.s")
void s08b_plasma_l_800D9A00(Work *, POLY_FT4 *, int, DG_TEX *);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800D9A90.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_plasma_l_800DA394.s")
int s08b_plasma_l_800DA394(Work *, int, int, int);

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
