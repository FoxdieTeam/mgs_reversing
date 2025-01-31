#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

typedef struct _BloodClWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[64];
    int      map;
} BloodClWork;

extern int GM_CurrentMap;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int BloodClGetSvecs_800C99AC(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

void BloodClGetInts_800C9A00(char *opt, int *out)
{
    char *res;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        *out = GCL_StrToInt(res);
        out++;
    }
}

void BloodClDie_800C9A44(BloodClWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void BloodClAct_800C9A80(BloodClWork *work)
{
}

static inline void BloodClTexPack(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(pack, x, y, w, h);

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

int BloodClGetResources_800C9A88(BloodClWork *work, int map)
{
    SVECTOR   pos[16];
    SVECTOR   dir[16];
    int       size[16];
    SVECTOR   local[4];
    SVECTOR   color;
    int       raise;
    int       n_prims;
    char     *opt;
    int       abr;
    int       i;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *packs0;
    POLY_FT4 *packs1;

    raise = 0;

    n_prims = 0;
    opt = GCL_GetOption('r');
    if (opt != NULL)
    {
        raise = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        n_prims = BloodClGetSvecs_800C99AC(opt, pos);

        opt = GCL_GetOption('d');
        if (opt != NULL)
        {
            BloodClGetSvecs_800C99AC(opt, dir);
        }

        opt = GCL_GetOption('s');
        if (opt != NULL)
        {
            BloodClGetInts_800C9A00(opt, size);
        }
    }

    opt = GCL_GetOption('u');
    if (opt != NULL)
    {
        abr = GCL_StrToInt(opt);
        abr &= 0x3;
    }
    else
    {
        abr = 0;
    }

    opt = GCL_GetOption('c');
    if (opt != NULL)
    {
        BloodClGetSvecs_800C99AC(opt, &color);
    }

    work->map = map;
    GM_CurrentMap = map;

    for (i = 0; i < n_prims; i++)
    {
        local[0].vx = size[i];
        local[0].vy = 0;
        local[0].vz = size[i];

        local[1].vx = -size[i];
        local[1].vy = 0;
        local[1].vz = size[i];

        local[2].vx = size[i];
        local[2].vy = 0;
        local[2].vz = -size[i];

        local[3].vx = -size[i];
        local[3].vy = 0;
        local[3].vz = -size[i];

        DG_SetPos2(&pos[i], &dir[i]);
        DG_PutVector(local, &work->vecs[i * 4], 4);
    }

    prim = DG_GetPrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, n_prims, 0, work->vecs, NULL);
    work->prim = prim;
    if (work->prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = raise;

    tex = DG_GetTexture(GV_StrCode("ketchap_grey"));
    if (tex == NULL)
    {
        return -1;
    }

    packs0 = (POLY_FT4 *)prim->packs[0];
    packs1 = (POLY_FT4 *)prim->packs[1];

    while (--n_prims >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        BloodClTexPack(packs0, tex);
        BloodClTexPack(packs1, tex);

        setRGB0(packs0, color.vx, color.vy, color.vz);
        setRGB0(packs1, color.vx, color.vy, color.vz);

        packs0->tpage |= abr << 5;
        packs1->tpage |= abr << 5;

        packs0++;
        packs1++;
    }

    return 0;
}

GV_ACT *NewBloodCl_800C9DF0(int name, int where)
{
    BloodClWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(BloodClWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BloodClAct_800C9A80, BloodClDie_800C9A44, "blood_cl.c");

        if (BloodClGetResources_800C9A88(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
