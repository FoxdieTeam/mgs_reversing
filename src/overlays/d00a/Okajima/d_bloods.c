#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _DBloodsWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[8];
    SVECTOR  f64[2];
    SVECTOR  f74;
    int      map;
    int      f80;
    SVECTOR  f84;
    int      f8C;
    int      f90;
    int      f94;
} DBloodsWork;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 7

void DBloodsDie_800D5078(DBloodsWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

// DBloodsAct_800D50B4 jumptable
const int d00a_dword_800E0F74 = 0x800D5100;
const int d00a_dword_800E0F78 = 0x800D5314;
const int d00a_dword_800E0F7C = 0x800D5100;
const int d00a_dword_800E0F80 = 0x800D5314;
const int d00a_dword_800E0F84 = 0x800D5464;
const int d00a_dword_800E0F88 = 0x800D568C;
const int d00a_dword_800E0F8C = 0x800D5464;
const int d00a_dword_800E0F90 = 0x800D568C;

#pragma INCLUDE_ASM("asm/overlays/d00a/DBloodsAct_800D50B4.s")
void DBloodsAct_800D50B4(DBloodsWork *work);

void DBloods_800D57F0(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex, int arg4)
{
    int x, y, w, h;
    int x2, y2, w2, h2;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(packs0, x, y, w, h);

        packs0->tpage = tex->field_4_tPage;
        packs0->clut = tex->field_6_clut;

        x2 = tex->field_8_offx;
        w2 = tex->field_A_width;
        y2 = tex->field_9_offy;
        h2 = tex->field_B_height;
        setUVWH(packs1, x2, y2, w2, h2);

        packs1->tpage = tex->field_4_tPage;
        packs1->clut = tex->field_6_clut;

        if (arg4 > 1 && arg4 < 6)
        {
            setRGB0(packs0, 0, 0, 32);
            setRGB0(packs1, 0, 0, 32);
        }
        else
        {
            setRGB0(packs0, 90, 128, 128);
            setRGB0(packs1, 90, 128, 128);
        }

        packs0++;
        packs1++;
    }
}

int DBloods_800D591C(DBloodsWork *work, SVECTOR *arg1, int arg2, int arg3, int arg4)
{
    work->f80 = 0;
    work->f84 = *arg1;
    work->f8C = arg2;
    work->f90 = arg3;
    work->f94 = arg4;
    return 0;
}

int DBloods_800D5958(DBloodsWork *work, int arg1)
{
    SVECTOR  sp18;
    SVECTOR  sp20[4];
    int      i;
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->f74 = DG_ZeroVector_800AB39C;

    for (i = 0; i < 2; i++)
    {
        sp18.vx = work->f84.vx;
        sp18.vy = work->f84.vy;
        sp18.vz = work->f84.vz;

        work->f64[i] = sp18;

        sp20[0].vx = 0;
        sp20[0].vy = 0;
        sp20[0].vz = 0;
        sp20[1].vx = 0;
        sp20[1].vy = 0;
        sp20[1].vz = 0;
        sp20[2].vx = 0;
        sp20[2].vy = 0;
        sp20[2].vz = 0;
        sp20[3].vx = 0;
        sp20[3].vy = 0;
        sp20[3].vz = 0;

        DG_SetPos2_8001BC8C(&work->f64[i], &DG_ZeroVector_800AB39C);
        DG_PutVector_8001BE48(sp20, &work->vecs[i * 4], 4);
    }

    prim = DG_GetPrim(0x12, 2, 0, work->vecs, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 500;
    prim->field_2E_k500 *= -1;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("ketchap"));
    if (tex == NULL)
    {
        return -1;
    }

    DBloods_800D57F0(&prim->field_40_pBuffers[0]->poly_ft4, &prim->field_40_pBuffers[1]->poly_ft4, 2, tex, arg1);

    return 0;
}

int DBloodsGetResources_800D5B08(DBloodsWork *work, SVECTOR *arg1, int arg2, int arg3, int arg4)
{
    work->map = GM_CurrentMap_800AB9B0;

    DBloods_800D591C(work, arg1, arg2, arg3, arg4);

    if (DBloods_800D5958(work, arg2) == -1)
    {
        GV_DestroyActor_800151C8(&work->actor);
    }

    return 0;
}

GV_ACT * NewDBloods_800D5B70(SVECTOR *arg0, int arg1, int arg2, int arg3)
{
    DBloodsWork *work;

    work = (DBloodsWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(DBloodsWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)DBloodsAct_800D50B4, (TActorFunction)DBloodsDie_800D5078, "d_bloods.c");

        if (DBloodsGetResources_800D5B08(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
