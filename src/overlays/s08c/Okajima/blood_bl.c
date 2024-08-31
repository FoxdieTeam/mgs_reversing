#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _BloodBlWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  pos;
    SVECTOR  verts[4];
    SVECTOR  dir;
    int      scale;
    int      target;
    int      time;
    int      map;
} BloodBlWork;

extern int GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 4

int BloodBlGetSvecs_800CD3C0(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(res, out);
        out++;
        count++;
    }

    return count;
}

void BloodBlDie_800CD414(BloodBlWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void BloodBlAct_800CD450(BloodBlWork *work)
{
    SVECTOR verts[4];
    int     size;

    if (work->time < work->target)
    {
        work->time++;

        size = (work->scale * work->time) / work->target;

        verts[0].vx = size;
        verts[0].vy = 0;
        verts[0].vz = size;

        verts[1].vx = -size;
        verts[1].vy = 0;
        verts[1].vz = size;

        verts[2].vx = size;
        verts[2].vy = 0;
        verts[2].vz = -size;

        verts[3].vx = -size;
        verts[3].vy = 0;
        verts[3].vz = -size;

        DG_SetPos2_8001BC8C(&work->pos, &work->dir);
        DG_PutVector_8001BE48(verts, work->verts, 4);
    }
}

static inline void BloodBlTexPack(POLY_FT4 *pack, DG_TEX *tex)
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

int BloodBlGetResources_800CD520(BloodBlWork *work, int map)
{
    SVECTOR   color;
    char     *opt;
    int       raise;
    int       abr;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;

    work->time = 0;

    raise = 0;

    opt = GCL_GetOption_80020968('r');
    if (opt != NULL)
    {
        raise = GCL_StrToInt_800209E8(opt);
    }

    opt = GCL_GetOption_80020968('p');
    if (opt != NULL)
    {
        BloodBlGetSvecs_800CD3C0(opt, &work->pos);
    }

    opt = GCL_GetOption_80020968('d');
    if (opt != NULL)
    {
        BloodBlGetSvecs_800CD3C0(opt, &work->dir);
    }

    opt = GCL_GetOption_80020968('s');
    if (opt != NULL)
    {
        work->scale = GCL_StrToInt_800209E8(opt);
    }

    opt = GCL_GetOption_80020968('t');
    if (opt != NULL)
    {
        work->target = GCL_StrToInt_800209E8(opt);
    }
    else
    {
        work->target = 1;
    }

    opt = GCL_GetOption_80020968('u');
    if (opt != NULL)
    {
        abr = GCL_StrToInt_800209E8(opt);
        abr &= 0x3;
    }
    else
    {
        abr = 0;
    }

    opt = GCL_GetOption_80020968('c');
    if (opt != NULL)
    {
        BloodBlGetSvecs_800CD3C0(opt, &color);
    }

    work->map = map;
    GM_CurrentMap_800AB9B0 = map;

    prim = DG_GetPrim(0x12, 1, 0, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = raise;

    tex = DG_GetTexture_8001D830(GV_StrCode("ketchap_grey"));
    if (tex == NULL)
    {
        return -1;
    }

    pack0 = &prim->packs[0]->poly_ft4;
    pack1 = &prim->packs[1]->poly_ft4;

    setPolyFT4(pack0);
    setSemiTrans(pack0, 1);

    setPolyFT4(pack1);
    setSemiTrans(pack1, 1);

    BloodBlTexPack(pack0, tex);
    BloodBlTexPack(pack1, tex);

    setRGB0(pack0, color.vx, color.vy, color.vz);
    setRGB0(pack1, color.vx, color.vy, color.vz);

    pack0->tpage |= abr << 5;
    pack1->tpage |= abr << 5;

    return 0;
}

GV_ACT * NewBloodBl_800CD7CC(int name, int where)
{
    BloodBlWork *work;

    work = (BloodBlWork *)GV_NewActor(EXEC_LEVEL, sizeof(BloodBlWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BloodBlAct_800CD450,
                         (TActorFunction)BloodBlDie_800CD414, "blood_bl.c");

        if (BloodBlGetResources_800CD520(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
