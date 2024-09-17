#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "Game/game.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _Door2Work
{
    GV_ACT   actor;
    int      name;
    int      map;
    char     pad1[0x8];
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    SVECTOR  verts[88];
    SVECTOR  pos;
    int      f300;
    int      f304;
    int      f308;
    HZD_HDL *hzd;
    HZD_SEG  seg;
    int      f320;
} Door2Work;

extern int GM_CurrentMap_800AB9B0;

unsigned short door2_800C37B4[2] = {0x418B, 0x3A02};
SVECTOR        door2_800C37B8[2] = {{500, 2500, 0, 0}, {-500, 0, 0, 0}};

const char door2_800E3334[11] = {0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3};

void s16b_800C49AC(HZD_SEG *seg);

#define EXEC_LEVEL 5

void s13a_door2_800DD0FC(SVECTOR *verts, Door2Work *work)
{
    int i;

    GV_ZeroMemory(verts, sizeof(SVECTOR) * 22);

    for (i = 0; i < 11; i++)
    {
        verts[0].vy = verts[1].vy = 2500;
        verts[2].vy = verts[3].vy = verts[4].vy = verts[5].vy = 1250;
        verts += 8;
    }

    verts -= 8;
    verts[0].vx = verts[2].vx = verts[4].vx = verts[6].vx = 650;
    verts[1].vx = verts[3].vx = verts[5].vx = verts[7].vx = 750;
}

void s13a_door2_800DD18C(SVECTOR *verts, int arg1)
{
    int mult = 400;
    int var_t0;
    int var_t1;
    int i;
    int x;
    int temp_a1;
    int new_var;

    var_t0 = 0;
    var_t1 = (arg1 * mult) / 256;

    for (i = 0; i < 5; i++)
    {
        x = var_t1 + var_t0;
        temp_a1 = var_t0 + 50;
        verts[0].vx = verts[2].vx = verts[4].vx = verts[6].vx = x;
        verts[1].vx = verts[3].vx = verts[5].vx = verts[7].vx = x + 50;
        verts[8].vx = verts[10].vx = verts[12].vx = verts[14].vx = var_t1 + temp_a1;
        var_t0 = (i + 1) * 130;
        new_var = 650 - var_t0;
        mult = new_var - 50 * (4 - i);
        var_t1 = (mult * arg1) / 256;
        verts[9].vx = verts[11].vx = verts[13].vx = verts[15].vx = var_t1 + var_t0;
        verts += 16;
    }
}

void s13a_door2_800DD274(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        LSTORE((LLOAD(&packs0->r0) & 0xff000000) | 0x808080, &packs0->r0);

        setPolyFT4(packs1);
        LSTORE((LLOAD(&packs1->r0) & 0xff000000) | 0x808080, &packs1->r0);
        setSemiTrans(packs1, 0);

        packs0++;
        packs1++;
    }
}

void s13a_door2_800DD2EC(POLY_FT4 *packs0, POLY_FT4 *packs1, DG_TEX *tex)
{
    char  scale[11];
    char *scalep;
    int   i;
    int   s;
    int   x, w, h;
    int   new_var;
    short y, new_var2;

    scalep = scale;
    memcpy(scalep, door2_800E3334, 11);

    for (i = 0; i < 11; i++)
    {
        s = scale[i];

        x = tex->off_x;
        w = tex->w + 1;
        packs0->u0 = packs0->u2 = x + w * s / 4;
        packs0->u1 = packs0->u3 = x + w * (s + 1) / 4 - 1;

        h = tex->h + 1;
        new_var = tex->off_y;
        packs0->v0 = packs0->v1 = new_var;
        packs0->v2 = packs0->v3 = new_var + h / 2 - 1;

        packs0->tpage = tex->tpage;
        packs0->clut = tex->clut;

        x = tex->off_x;
        w = tex->w + 1;
        packs1->u0 = packs1->u2 = x + w * s / 4;
        packs1->u1 = packs1->u3 = x + w * (s + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h + 1;
        new_var2 = packs1->v1 = y;
        packs1->v0 = new_var2;
        packs1->v2 = packs1->v3 = y + h / 2 - 1;

        packs1->tpage = tex->tpage;
        packs1->clut = tex->clut;

        packs0++;
        packs1++;

        x = tex->off_x;
        w = tex->w + 1;
        packs0->u0 = packs0->u2 = x + w * s / 4;
        packs0->u1 = packs0->u3 = x + w * (s + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h;
        h = h + 1;
        packs0->v0 = packs0->v1 = y + h / 2;
        packs0->v2 = packs0->v3 = y + h - 1;

        packs0->tpage = tex->tpage;
        packs0->clut = tex->clut;

        x = tex->off_x;
        w = tex->w + 1;
        packs1->u0 = packs1->u2 = x + w * s / 4;
        packs1->u1 = packs1->u3 = x + w * (s + 1) / 4 - 1;

        new_var2 = tex->h + 1;
        y = tex->off_y;
        h = new_var2;
        packs1->v0 = packs1->v1 = y + h / 2;
        packs1->v2 = packs1->v3 = y + h - 1;

        packs1->tpage = tex->tpage;
        packs1->clut = tex->clut;

        packs0++;
        packs1++;
    }
}

void Door2Act_800DD5C0(Door2Work *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    switch (THING_Msg_CheckMessage(work->name, 2, door2_800C37B4))
    {
    case 0:
        work->f304 = 0;
        work->f308 = 32;
        GM_SeSet(&work->pos, 183);
        break;

    case 1:
        work->f304 = 1;
        work->f308 = 32;
        GM_SeSet(&work->pos, 183);
        break;
    }

    switch (work->f304)
    {
    case 0:
        work->f300 += work->f308 + 10;
        if (work->f300 > 256)
        {
            work->f300 = 256;
            work->f304 = -1;

            GM_SeSet(&work->pos, 184);

            if (work->f320 != 0)
            {
                HZD_DequeueDynamicSegment_8006FE44(work->hzd, &work->seg);
                work->f320 = 0;
            }
        }
        break;

    case 1:
        work->f300 -= work->f308 + 10;
        if (work->f300 < 0)
        {
            work->f300 = 0;
            work->f304 = -1;

            GM_SeSet(&work->pos, 182);

            if (work->f320 != 1)
            {
                HZD_QueueDynamicSegment2_8006FDDC(work->hzd, &work->seg, 0x210);
                work->f320 = 1;
            }
        }
        break;
    }

    work->f308 -= work->f308 / 4;
    s13a_door2_800DD18C(work->verts, work->f300);
}

void Door2Die_800DD744(Door2Work *work)
{
    DG_PRIM *prim;

    if (work->f320 != 0)
    {
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, &work->seg);
    }

    prim = work->prim1;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim2;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int Door2GetResources_800DD7C8(Door2Work *work, int name, int map)
{
    SVECTOR  dir;
    MATRIX   sp20;
    MATRIX   sp40;
    SVECTOR *verts;
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    DG_TEX  *tex;

    GM_CurrentMap_800AB9B0 = map;

    THING_Gcl_GetSVector('p', &work->pos);

    sp20.t[0] = sp40.t[0] = work->pos.vx;
    sp20.t[1] = sp40.t[1] = work->pos.vy;
    sp20.t[2] = sp40.t[2] = work->pos.vz;

    THING_Gcl_GetSVector('d', &dir);
    RotMatrix(&dir, &sp20);
    dir.vy += 2048;
    RotMatrix(&dir, &sp40);

    verts = work->verts;
    s13a_door2_800DD0FC(verts, work);
    s13a_door2_800DD18C(verts, 0);

    prim1 = DG_GetPrim(DG_PRIM_POLY_FT4, 22, 0, verts, NULL);
    work->prim1 = prim1;
    if (prim1 == NULL)
    {
        return -1;
    }

    prim2 = DG_GetPrim(DG_PRIM_POLY_FT4, 22, 0, verts, NULL);
    work->prim2 = prim2;
    if (prim2 == NULL)
    {
        return -1;
    }

    DG_SetPos(&sp20);
    DG_PutPrim(&prim1->world);

    DG_SetPos(&sp40);
    DG_PutPrim(&prim2->world);

    tex = DG_GetTexture(PCX_DOOR2);
    if (tex == NULL)
    {
        return -1;
    }

    s13a_door2_800DD274(&prim1->packs[0]->poly_ft4, &prim1->packs[1]->poly_ft4, 22, tex);
    s13a_door2_800DD2EC(&prim1->packs[0]->poly_ft4, &prim1->packs[1]->poly_ft4, tex);

    s13a_door2_800DD274(&prim2->packs[0]->poly_ft4, &prim2->packs[1]->poly_ft4, 22, tex);
    s13a_door2_800DD2EC(&prim2->packs[0]->poly_ft4, &prim2->packs[1]->poly_ft4, tex);

    work->hzd = Map_FromId_800314C0(map)->hzd;

    s16b_800C45C4(&work->seg, &sp20, &door2_800C37B8[0], &door2_800C37B8[1]);
    s16b_800C49AC(&work->seg);
    return 0;
}

GV_ACT *NewDoor2_800DD9E4(int name, int where)
{
    Door2Work *work;

    work = (Door2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Door2Work));
    if (work != NULL)
    {
        work->name = name;
        work->map = where;

        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)Door2Act_800DD5C0, (GV_ACTFUNC)Door2Die_800DD744, "door2.c");

        if (Door2GetResources_800DD7C8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f300 = 0;
        work->f308 = 0;
        work->f304 = 1;
        work->f320 = 0;
    }

    return &work->actor;
}
