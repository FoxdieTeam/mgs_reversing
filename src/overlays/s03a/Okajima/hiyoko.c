#include "hiyoko.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
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

#define EXEC_LEVEL GV_ACTOR_LEVEL5

int HiyokoGetSvec_800CFD04(char *opt, SVECTOR *out)
{
    char *res;

    res = GCL_GetParamResult();
    if (res == NULL)
    {
        return 0;
    }

    GCL_StrToSV(res, out);
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
        GV_DestroyActor(&work->actor);
        return;
    }

    if (work->world != NULL)
    {
        work->pos.vx = work->world->t[0];
        work->pos.vy = work->world->t[1] + 500;
        work->pos.vz = work->world->t[2];
    }

    GM_CurrentMap = work->map;

    rot = DG_ZeroVector;
    rot.vy = GV_Time * 256;

    DG_SetPos2(&work->pos, &rot);
    DG_PutVector(work->f2C, work->prim_vecs, 3);

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

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= 0x20;

        packs++;
    }
}

int HiyokoGetResources_800CFECC(HiyokoWork *work, int map)
{
    SVECTOR  off;
    SVECTOR  rot;
    char    *opt;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      i;
    SVECTOR *vec;

    work->map = map;

    work->f74 = -1;
    work->world = NULL;

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        HiyokoGetSvec_800CFD04(opt, &work->pos);
    }

    prim = Takabe_MakeIndividualRect3DPrim(3, work->prim_vecs);
    work->prim = prim;
    prim->userdata = NULL;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;

    tex = DG_GetTexture(GV_StrCode("hosi"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    HiyokoShadePacks_800CFE3C(&prim->packs[0]->poly_ft4, 3, tex);
    HiyokoShadePacks_800CFE3C(&prim->packs[1]->poly_ft4, 3, tex);

    off.vx = 100;
    off.vy = 0;
    off.vz = 0;

    rot = DG_ZeroVector;

    vec = work->f2C;
    for (i = 0; i < 3; i++, vec++)
    {
        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&off, vec, 1);
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

    work->map = GM_CurrentMap;

    work->world = world;
    work->f74 = arg2;

    work->prim = prim = Takabe_MakeIndividualRect3DPrim(3, work->prim_vecs);
    prim->userdata = NULL;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;

    tex = DG_GetTexture(GV_StrCode("hosi"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    HiyokoShadePacks_800CFE3C(&prim->packs[0]->poly_ft4, 3, tex);
    HiyokoShadePacks_800CFE3C(&prim->packs[1]->poly_ft4, 3, tex);

    off.vx = 100;
    off.vy = 0;
    off.vz = 0;

    rot = DG_ZeroVector;

    vec = work->f2C;
    for (i = 0; i < 3; i++, vec++)
    {
        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&off, vec, 1);
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
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void *NewHiyoko_800D018C(int name, int where, int argc, char **argv)
{
    HiyokoWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(HiyokoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, HiyokoAct_800CFD44, HiyokoDie_800D0150, "hiyoko.c");

        if (HiyokoGetResources_800CFECC(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

void *NewHiyoko_800D0210(MATRIX *world, int arg1)
{
    HiyokoWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(HiyokoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, HiyokoAct_800CFD44, HiyokoDie_800D0150, "hiyoko.c");

        if (HiyokoGetResources_800D0018(work, world, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
