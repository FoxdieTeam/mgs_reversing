#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Takabe/prim.h"

typedef struct BlastoffWork
{
    GV_ACT   actor;
    int      where;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  field_2C;
    SVECTOR  field_34;
    SVECTOR *field_3C;
    int      field_40;
    int      field_44;
    int      field_48;
    int      field_4C;
    SVECTOR  prim_vecs[16];
} BlastoffWork;

#define EXEC_LEVEL 5

extern int    GM_CurrentMap_800AB9B0;
extern MATRIX DG_ZeroMatrix_8009D430;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_blastoff_800DB880.s")
void s11g_blastoff_800DB880(BlastoffWork *work);

void BlastoffAct_800DBB60(BlastoffWork *work)
{
    GM_CurrentMap_800AB9B0 = work->where;
    work->field_2C = work->field_34;
    work->field_34 = *work->field_3C;

    if (work->field_40 > 0)
    {
        s11g_blastoff_800DB880(work);
    }
    else
    {
        s11g_blastoff_800DB880(work);
        if (work->field_44 == 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return;
        }
        work->field_44--;
    }
    work->field_40--;
}

void BlastoffDie_800DBC28(BlastoffWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void Blastoff_800DBC64(POLY_FT4 *polys, DG_TEX *tex, int count)
{
    int width;
    int u1, u2;
    int v0, v2;

    for (count--; count != -1; count--)
    {
        setPolyFT4(polys);
        setSemiTrans(polys, 1);

        width = tex->field_A_width + 1;
        u2 = tex->field_8_offx;

        polys->u0 = polys->u2 = u2;

        u1 = u2 + (width / 4) - 1;
        polys->u1 = polys->u3 = u1;

        v0 = tex->field_9_offy;
        v2 = (tex->field_B_height + 1) / 7 + v0 - 1;

        polys->v0 = polys->v1 = v0;
        polys->v2 = polys->v3 = v2;

        polys->tpage = tex->field_4_tPage;
        polys->clut = tex->field_6_clut;
        polys->tpage |= 0x60;

        setRGB0(polys, 0, 0, 0);

        polys++;
    }
}

void Blastoff_800DBD34(BlastoffWork *work)
{
    DG_PRIM *prim;
    SVECTOR *iter;
    DG_TEX  *tex;
    int      i;

    work->tex = tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("bomb1_fl"));
    work->prim = prim = Takabe_MakeIndividualRect3DPrim_800793E8(16, work->prim_vecs);

    Blastoff_800DBC64(&prim->field_40_pBuffers[0]->poly_ft4, tex, 16);
    Blastoff_800DBC64(&prim->field_40_pBuffers[1]->poly_ft4, tex, 16);

    prim->world = DG_ZeroMatrix_8009D430;
    prim->field_2E_k500 = 1000;

    iter = work->prim_vecs;
    for (i = 16; i > 0; i--, iter++)
    {
        *iter = work->field_34;
        iter->pad = 0;
    }
}

int BlastoffGetResources_800DBE44(BlastoffWork *work, SVECTOR *arg1, int arg2, int arg3, int arg4)
{
    work->field_3C = arg1;
    work->where = GM_CurrentMap_800AB9B0;
    work->field_34 = *arg1;
    work->field_2C = *arg1;
    work->field_40 = arg2;
    work->field_48 = arg3;
    work->field_4C = arg4;
    Blastoff_800DBD34(work);
    work->field_44 = 80;
    return 0;
}

GV_ACT *NewBlastoff_800DBED4(SVECTOR *arg0, int arg1, int arg2, int arg3)
{
    BlastoffWork *work;

    work = (BlastoffWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(BlastoffWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BlastoffAct_800DBB60,
                                  (TActorFunction)BlastoffDie_800DBC28, "blastoff.c");
        if (BlastoffGetResources_800DBE44(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
