#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _PlasmaHWork
{
    GV_ACT   actor;
    int      map;
    char     pad1[0x4];
    DG_PRIM *prim;
    int      len;
    SVECTOR  f30[17];
    SVECTOR  verts[68];
    SVECTOR  pos1;
    SVECTOR  pos2;
    SVECTOR  rot;
    int      f2F0[17];
    int      f334[17];
    int      f378[17];
    int      count;
    int      time;
} PlasmaHWork;

extern SVECTOR DG_ZeroVector;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 4

int s08a_plasma_h_800D100C(SVECTOR *a, SVECTOR *b, SVECTOR *out)
{
    int dx, dy, dz;
    int len;
    int height;

    dx = (a->vx - b->vx) / 16;
    dy = (a->vy - b->vy) / 16;
    dz = (a->vz - b->vz) / 16;

    len = SquareRoot0(dx * dx + dy * dy + dz * dz) * 16;
    height = b->vy - a->vy;

    out->vy = ratan2(b->vx - a->vx, b->vz - a->vz) & 0xFFF;
    out->vx = ratan2(len, height) & 0xFFF;
    out->vz = 0;

    return len;
}

void s08a_plasma_h_800D1118(PlasmaHWork *work, POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        setRGB0(packs, 100, 100, 250);

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

void s08a_plasma_h_800D11AC(PlasmaHWork *work, SVECTOR *pos1, SVECTOR *pos2)
{
    int len;

    work->pos1 = *pos1;
    work->pos2 = *pos2;

    work->len = s08a_plasma_h_800D100C(&work->pos1, &work->pos2, &work->rot);
    len = work->len / 4;

    work->f2F0[0] = GV_RandU(4096);
    work->f2F0[4] = GV_RandU(512);
    work->f334[4] = GV_RandU(1024);
    work->f378[4] = (len * GV_RandU(4096)) / 4096;
    work->f2F0[8] = work->f2F0[4] + GV_RandS(512);
    work->f334[8] = GV_RandU(1024) + 1024;
    work->f378[8] = (len * 2 * GV_RandU(4096)) / 4096;
    work->f2F0[12] = work->f2F0[8] + GV_RandS(512);
    work->f334[12] = GV_RandU(1024) + 2048;
    work->f378[12] = (len * GV_RandU(4096)) / 4096;
    work->f2F0[16] = work->f2F0[12] + GV_RandS(512);

    if (work->f334[8] < work->f334[4])
    {
        work->f334[4] = work->f334[8];
    }

    if (work->f334[12] < work->f334[4])
    {
        work->f334[4] = work->f334[12];
    }

    if (work->f334[12] < work->f334[8])
    {
        work->f334[8] = work->f334[12];
    }

    work->f30[0] = work->pos1;
    work->f30[16] = work->pos2;

    work->f334[0] = 0;
    work->f334[16] = 4096;
    work->f378[0] = 0;
    work->f378[16] = 0;
}

void s08a_plasma_h_800D13B4(PlasmaHWork *work)
{
    int len;
    int tmp;

    len = work->len / 4;

    work->f2F0[0] = work->f2F0[0] + GV_RandS(128);
    work->f2F0[4] = work->f2F0[4] + GV_RandS(64);
    work->f334[4] = work->f334[4] + GV_RandS(32);

    work->f378[4] += GV_RandS(32);

    if (work->f378[4] < 0)
    {
        work->f378[4] = 0;
    }

    if (work->f378[4] > len)
    {
        work->f378[4] = len;
    }

    work->f2F0[8] += GV_RandS(64);

    if (work->f2F0[8] > (work->f2F0[4] + 512))
    {
        work->f2F0[8] = work->f2F0[4] + GV_RandS(512);
    }

    if (work->f2F0[8] < (work->f2F0[4] - 512))
    {
        work->f2F0[8] = work->f2F0[4] + GV_RandS(512);
    }

    work->f334[8] += GV_RandS(32);
    work->f378[8] += GV_RandS(64) + 16;

    if (work->f378[8] < 0)
    {
        work->f378[8] = 0;
    }

    if (work->f378[8] > len)
    {
        work->f378[8] = len;
    }

    work->f2F0[12] += GV_RandS(64);

    if (work->f2F0[12] > (work->f2F0[8] + 512))
    {
        work->f2F0[12] = work->f2F0[8] + GV_RandS(512);
    }

    if (work->f2F0[12] < (work->f2F0[8] - 512))
    {
        work->f2F0[12] = work->f2F0[8] + GV_RandS(512);
    }

    work->f334[12] += GV_RandS(32);
    work->f378[12] += GV_RandS(32);

    if (work->f378[12] < 0)
    {
        work->f378[12] = 0;
    }

    if (work->f378[12] > (len * 2))
    {
        work->f378[12] = len * 2;
    }

    if (work->f334[8] < work->f334[4])
    {
        tmp = work->f334[4];
        work->f334[4] = work->f334[8];
        work->f334[8] = tmp;
    }

    if (work->f334[12] < work->f334[4])
    {
        tmp = work->f334[4];
        work->f334[4] = work->f334[12];
        work->f334[12] = tmp;
    }

    if (work->f334[12] < work->f334[8])
    {
        tmp = work->f334[8];
        work->f334[8] = work->f334[12];
        work->f334[12] = tmp;
    }
}

void s08a_plasma_h_800D1638(PlasmaHWork *work, int a, int b)
{
    int m, p;

    m = a - b;
    p = a + b;

    work->f334[a] = work->f334[m] + ((work->f334[p] - work->f334[m]) * 3) / 4;
    work->f378[a] = work->f378[m] + (work->f378[p] - work->f378[m]) / 2;
    work->f2F0[a] = work->f2F0[m] + (work->f2F0[p] - work->f2F0[m]) / 2;
}

void PlasmaAct_800D16D0(PlasmaHWork *work)
{
    SVECTOR  sp10;
    SVECTOR  rot;
    SVECTOR  sp20;
    SVECTOR  sp28;
    int      i;
    SVECTOR *verts;
    int     *var_s5;
    int     *var_s4;
    int     *var_s2;
    int      len;
    SVECTOR *iter;

    GM_CurrentMap_800AB9B0 = work->map;

    if (work->count > work->time)
    {
        GV_DestroyActor(&work->actor);
    }

    work->count++;

    s08a_plasma_h_800D13B4(work);

    s08a_plasma_h_800D1638(work, 2, 2);
    s08a_plasma_h_800D1638(work, 6, 2);
    s08a_plasma_h_800D1638(work, 10, 2);
    s08a_plasma_h_800D1638(work, 14, 2);

    for (i = 0; i < 8; i++)
    {
        s08a_plasma_h_800D1638(work, i * 2 + 1, 1);
    }

    rot.vx = 0;
    rot.vz = 0;

    sp10.vx = 0;

    verts = work->f30;
    var_s5 = work->f334;
    var_s4 = work->f378;
    var_s2 = work->f2F0;
    for (i = 0; i < 17;)
    {
        sp10.vy = (*var_s5 * work->len) / 4096;
        sp10.vz = *var_s4;

        rot.vy = *var_s2;

        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&sp10, verts, 1);

        i++;
        verts++;
        var_s5++;
        var_s4++;
        var_s2++;
    }

    DG_SetPos2(&work->pos1, &work->rot);
    DG_PutVector(work->f30, work->f30, 17);

    len = work->len / 128;
    sp10.vx = len + GV_RandS(16);
    sp10.vy = len + GV_RandS(16);
    sp10.vz = len;

    iter = work->f30 + 1;
    verts = work->verts;

    sp20 = work->f30[0];
    GV_AddVec3(work->f30, &sp10, &sp28);

    for (i = 0; i < 16; i++)
    {
        *verts++ = sp20;
        *verts = *iter;
        sp20 = *verts++;
        *verts++ = sp28;
        GV_AddVec3(iter, &sp10, verts);
        sp28 = *verts++;
        iter++;
    }
}

void PlasmaDie_800D19B4(PlasmaHWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int s08a_plasma_h_800D19F0(PlasmaHWork *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 17, 0, work->verts, NULL);
    work->prim = prim;

    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 200;

    s08a_plasma_h_800D1118(work, &prim->packs[0]->poly_ft4, 17, tex);
    s08a_plasma_h_800D1118(work, &prim->packs[1]->poly_ft4, 17, tex);

    return 0;
}

int PlasmaHGetResources_800D1ABC(PlasmaHWork *work, SVECTOR *pos1, SVECTOR *pos2, int time)
{
    work->map = GM_CurrentMap_800AB9B0;
    work->time = time;

    if (s08a_plasma_h_800D19F0(work) < 0)
    {
        return -1;
    }

    s08a_plasma_h_800D11AC(work, pos1, pos2);

    work->count = 0;
    return 0;
}

GV_ACT *NewPlasmaH_800D1B2C(SVECTOR *pos1, SVECTOR *pos2, int time)
{
    PlasmaHWork *work;

    work = (PlasmaHWork *)GV_NewActor(EXEC_LEVEL, sizeof(PlasmaHWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)PlasmaAct_800D16D0, (TActorFunction)PlasmaDie_800D19B4, "plasma_h.c");

        if (PlasmaHGetResources_800D1ABC(work, pos1, pos2, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
