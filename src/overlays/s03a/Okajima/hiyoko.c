#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Takabe/prim.h"

typedef struct _HiyokoWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    DG_PRIM *prim;
    SVECTOR  f2C[3];
    SVECTOR  prim_vecs[4];
    DG_TEX  *tex;
    SVECTOR  pos;
    MATRIX  *world;
    int      f74;
} HiyokoWork;

extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

int HiyokoGetSvec_800CFD04(char *opt, SVECTOR *out)
{
    char *res;

    res = GCL_Get_Param_Result_80020AA4();
    if (res == NULL)
    {
        return 0;
    }

    GCL_StrToSV_80020A14(res, out);
    return 1;
}

void HiyokoAct_800CFD44(HiyokoWork *work)
{
    SVECTOR  rot;
    SVECTOR *vec;
    int      pad;
    int      i;

    if ((work->f74 > 0) && (--work->f74 == 0))
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    if (work->world != NULL)
    {
        work->pos.vx = work->world->t[0];
        work->pos.vy = work->world->t[1] + 500;
        work->pos.vz = work->world->t[2];
    }

    GM_CurrentMap_800AB9B0 = work->map;

    rot = DG_ZeroVector_800AB39C;
    rot.vy = GV_Time_800AB330 * 256;

    DG_SetPos2_8001BC8C(&work->pos, &rot);
    DG_PutVector_8001BE48(work->f2C, work->prim_vecs, 3);

    vec = work->prim_vecs;
    pad = 50;
    for (i = 2; i >= 0; i--)
    {
        vec->pad = pad;
        vec++;
    }
}

void HiyokoShadePacks_800CFE3C(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 128, 128, 128);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->field_4_tPage;
        packs->clut = tex->field_6_clut;

        packs->tpage |= 0x20;

        packs++;
    }
}

int HiyokoGetResources_800CFECC(HiyokoWork *work, int map)
{
    SVECTOR  off;
    SVECTOR  rot;
    int      opt;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      i;
    SVECTOR *vec;

    work->map = map;

    work->f74 = -1;
    work->world = NULL;

    opt = GCL_GetOption_80020968('p');
    if (opt != NULL)
    {
        HiyokoGetSvec_800CFD04((char *)opt, &work->pos);
    }

    prim = Takabe_MakeIndividualRect3DPrim_800793E8(3, work->prim_vecs);
    work->prim = prim;
    prim->field_4C = 0;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("hosi"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    HiyokoShadePacks_800CFE3C(&prim->field_40_pBuffers[0]->poly_ft4, 3, tex);
    HiyokoShadePacks_800CFE3C(&prim->field_40_pBuffers[1]->poly_ft4, 3, tex);

    off.vx = 100;
    off.vy = 0;
    off.vz = 0;

    rot = DG_ZeroVector_800AB39C;

    vec = work->f2C;
    for (i = 0; i < 3; i++, vec++)
    {
        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rot);
        DG_PutVector_8001BE48(&off, vec, 1);
        rot.vy += 4096 / 3;
    }

    return 0;
}

int HiyokoGetResources_800D0018(HiyokoWork *work, MATRIX *world, int arg2)
{
    SVECTOR  off;
    SVECTOR  rot;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      i;
    SVECTOR *vec;

    work->map = GM_CurrentMap_800AB9B0;

    work->world = world;
    work->f74 = arg2;

    work->prim = prim = Takabe_MakeIndividualRect3DPrim_800793E8(3, work->prim_vecs);
    prim->field_4C = 0;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("hosi"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    HiyokoShadePacks_800CFE3C(&prim->field_40_pBuffers[0]->poly_ft4, 3, tex);
    HiyokoShadePacks_800CFE3C(&prim->field_40_pBuffers[1]->poly_ft4, 3, tex);

    off.vx = 100;
    off.vy = 0;
    off.vz = 0;

    rot = DG_ZeroVector_800AB39C;

    vec = work->f2C;
    for (i = 0; i < 3; i++, vec++)
    {
        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rot);
        DG_PutVector_8001BE48(&off, vec, 1);
        rot.vy += 4096 / 3;
    }

    return 0;
}

void HiyokoDie_800D0150(HiyokoWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

GV_ACT * NewHiyoko_800D018C(int name, int map)
{
    HiyokoWork *work;

    work = (HiyokoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(HiyokoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)HiyokoAct_800CFD44, (TActorFunction)HiyokoDie_800D0150, "hiyoko.c");

        if (HiyokoGetResources_800CFECC(work, map) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT * NewHiyoko_800D0210(MATRIX *world, int arg1)
{
    HiyokoWork *work;

    work = (HiyokoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(HiyokoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)HiyokoAct_800CFD44, (TActorFunction)HiyokoDie_800D0150, "hiyoko.c");

        if (HiyokoGetResources_800D0018(work, world, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
