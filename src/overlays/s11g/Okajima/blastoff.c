#include "common.h"
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
    int     *field_4C;
    SVECTOR  prim_vecs[16];
} BlastoffWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern int    GV_Clock;
extern int    GM_CurrentMap;

void Blastoff_800DB880(BlastoffWork *work)
{
    SVECTOR  *vec;
    int       t1, t2;
    int       scale;
    SVECTOR  *prev;
    int       i;
    POLY_FT4 *pack;
    int       m, n;
    int       x, y, w, h;

    vec = work->prim_vecs;

    t1 = work->field_48;
    t2 = 4 - work->field_48;
    scale = *work->field_4C;

    vec->vx = ((work->field_2C.vx * t1) + (work->field_34.vx * t2)) / 4 + GV_RandS(64);
    vec->vy = ((work->field_2C.vy * t1) + (work->field_34.vy * t2)) / 4 + GV_RandS(64);
    vec->vz = ((work->field_2C.vz * t1) + (work->field_34.vz * t2)) / 4 + GV_RandS(64);
    vec->pad = (GV_RandU(256) * scale + 600) / 4096;

    vec = &work->prim_vecs[15];
    prev = &work->prim_vecs[14];
    for (i = 16; i >= 2; i--, vec--, prev--)
    {
        *vec = *prev;
        vec->pad += ((GV_RandU(16) + 40) * scale) / 4096;
    }

    pack = &work->prim->packs[GV_Clock]->poly_ft4;
    for (i = 16; i > 0; i--)
    {
        m = i & 3;
        n = i / 4;

        x = work->tex->off_x;
        w = work->tex->w + 1;
        pack->u0 = pack->u2 = x + (w * m) / 4;
        pack->u1 = pack->u3 = x + (w * (m + 1)) / 4 - 1;

        y = work->tex->off_y;
        h = work->tex->h + 1;
        pack->v0 = pack->v1 = y + (h * n) / 4;
        pack->v2 = pack->v3 = y + (h * (n + 1)) / 4 - 1;

        setRGB0(pack, i * 8, i * 8, i * 8);

        pack++;
    }
}

void BlastoffAct_800DBB60(BlastoffWork *work)
{
    GM_CurrentMap = work->where;
    work->field_2C = work->field_34;
    work->field_34 = *work->field_3C;

    if (work->field_40 > 0)
    {
        Blastoff_800DB880(work);
    }
    else
    {
        Blastoff_800DB880(work);
        if (work->field_44 == 0)
        {
            GV_DestroyActor(&work->actor);
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
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
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

        width = tex->w + 1;
        u2 = tex->off_x;

        polys->u0 = polys->u2 = u2;

        u1 = u2 + (width / 4) - 1;
        polys->u1 = polys->u3 = u1;

        v0 = tex->off_y;
        v2 = (tex->h + 1) / 7 + v0 - 1;

        polys->v0 = polys->v1 = v0;
        polys->v2 = polys->v3 = v2;

        polys->tpage = tex->tpage;
        polys->clut = tex->clut;
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

    work->tex = tex = DG_GetTexture(GV_StrCode("bomb1_fl"));
    work->prim = prim = Takabe_MakeIndividualRect3DPrim(16, work->prim_vecs);

    Blastoff_800DBC64(&prim->packs[0]->poly_ft4, tex, 16);
    Blastoff_800DBC64(&prim->packs[1]->poly_ft4, tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->field_2E_k500 = 1000;

    iter = work->prim_vecs;
    for (i = 16; i > 0; i--, iter++)
    {
        *iter = work->field_34;
        iter->pad = 0;
    }
}

int BlastoffGetResources_800DBE44(BlastoffWork *work, SVECTOR *arg1, int arg2, int arg3, int *arg4)
{
    work->field_3C = arg1;
    work->where = GM_CurrentMap;
    work->field_34 = *arg1;
    work->field_2C = *arg1;
    work->field_40 = arg2;
    work->field_48 = arg3;
    work->field_4C = arg4;
    Blastoff_800DBD34(work);
    work->field_44 = 80;
    return 0;
}

void *NewBlastoff_800DBED4(SVECTOR *arg0, int arg1, int arg2, int *arg3)
{
    BlastoffWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(BlastoffWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BlastoffAct_800DBB60, BlastoffDie_800DBC28, "blastoff.c");
        if (BlastoffGetResources_800DBE44(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
