#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  field_28[16];
    SVECTOR  prim_verts[64];
    int      field_2A8;
    MATRIX   field_2AC;
    int      field_2CC;
} Work;

extern SVECTOR s19b_dword_800DE658[];

// anims

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C7FB8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8070.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8128.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8448.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C850C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8610.s")

// jblood.c

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C86AC.s")

void s19b_jblood_800C8A48(SVECTOR *arg0, SVECTOR *arg1, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = arg0->vx;
        y = arg0->vy;
        z = arg0->vz;
    
        arg1[0].vx += x;
        arg1[0].vy += y;
        arg1[0].vz += z;

        arg1[3].vx += x;
        arg1[3].vy += y;
        arg1[3].vz += z;

        arg1[1].vx += x;
        arg1[1].vy += y;
        arg1[1].vz += z;

        arg1[2].vx += x;
        arg1[2].vy += y;
        arg1[2].vz += z;

        arg0->vx = x;
        arg0->vy = y - 11;
        arg0->vz = z;

        arg1 += 4;
        arg0++;
    }
}

void s19b_jblood_800C8B2C(POLY_FT4 *pack, int n_packs, DG_TEX *tex, int abr)
{
    int i;

    for (i = n_packs - 1; i >= 0; i--, pack++)
    {
        setPolyFT4(pack);
        setSemiTrans(pack, 1);
        DG_SetPacketTexture4(pack, tex);

        if (abr == 2)
        {
            pack->tpage |= 0x60;
        }
        else
        {
            pack->tpage |= 0x60;
        }
    }
}

void s19b_jblood_800C8BC0(POLY_FT4 *pack, int n_packs, int shade)
{
    int i;

    for (i = n_packs - 1; i >= 0; i--)
    {
        setRGB0(pack, shade, shade, shade);
        pack++;
    }
}

void s19b_jblood_800C8BEC(Work *work)
{
    int      time;
    DG_PRIM *prim;

    GM_CurrentMap = work->map;

    time = --work->field_2A8;
    if (time <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    s19b_jblood_800C8A48(work->field_28, work->prim_verts, 16);

    prim = work->prim;
    s19b_jblood_800C8BC0(&prim->packs[0]->poly_ft4, 16, time * 16);
    s19b_jblood_800C8BC0(&prim->packs[1]->poly_ft4, 16, time * 16);

    work->field_2AC.t[0] += s19b_dword_800DE658[3].vx;
    work->field_2AC.t[1] += s19b_dword_800DE658[3].vy;
    work->field_2AC.t[2] += s19b_dword_800DE658[3].vz;

    DG_SetPos(&work->field_2AC);
    DG_PutPrim(&work->prim->world);
}

void s19b_jblood_800C8CD4(Work *work)
{
    GM_FreePrim(work->prim);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8D10.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jblood_800C8E4C.s")
