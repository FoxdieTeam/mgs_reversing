#include "bubble_p.h"

#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _BubblePWork
{
    GV_ACT   actor;
    int      map;
    char     pad[0x4];
    DG_PRIM *prim;
    RECT     rect;
    char     pad2[0x10];
    SVECTOR  f44[3];
    SVECTOR  f5C[3];
    int      f74;
    int      f78;
    int      f7C;
    int      f80;
} BubblePWork;

extern int GV_Clock_800AB920;
extern int GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 4

void BubblePShadePack_800D96AC(POLY_FT4 *packs, int shade, int index)
{
    POLY_FT4 *pack;

    pack = &packs[index];
    setRGB0(pack, shade, shade, shade);
}

void BubblePInitPack_800D96CC(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    setPolyFT4(pack);
    setSemiTrans(pack, 1);
    setRGB0(pack, 64, 64, 128);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(pack, x, y, w, h);

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;

    pack->tpage |= 0x60;
}

void BubblePUpdatePacks_800D9748(BubblePWork *work)
{
    int       size;
    SVECTOR  *vec1;
    SVECTOR  *vec2;
    int       i;
    POLY_FT4 *packs;
    int       shade;

    size = ((((work->f7C * work->f7C) / 2) + 400) * work->f78) >> 8;

    vec1 = work->f44;
    vec2 = work->f5C;

    for (i = 0; i < 3; i++)
    {
        vec2->vx = (vec2->vx * 15) / 16;
        vec2->vy = (vec2->vy * 15) / 16;
        vec2->vz = (vec2->vz * 15) / 16;

        vec1->vx = vec1->vx + vec2->vx + GV_RandS(2);
        vec1->vy = vec1->vy + vec2->vy + (3 - i) * 16 + GV_RandU(2);
        vec1->vz = vec1->vz + vec2->vz + GV_RandS(2);
        vec1++;
    }

    work->rect.x = size >> 1;
    work->rect.y = size >> 1;
    work->rect.w = size;
    work->rect.h = size;

    packs = &work->prim->packs[GV_Clock_800AB920]->poly_ft4;

    if (work->f74 < 30)
    {
        shade = (work->f80 + work->f74) - 20;
        if (shade >= 0)
        {
            shade >>= 1;
        }
        else
        {
            shade = 0;
        }

        BubblePShadePack_800D96AC(packs, shade, 0);
    }

    if (work->f74 < 20)
    {
        shade = (work->f80 + work->f74) - 10;
        if (shade >= 0)
        {
            shade >>= 1;
        }
        else
        {
            shade = 0;
        }

        BubblePShadePack_800D96AC(packs, shade, 1);
    }

    if (work->f74 < 10)
    {
        work->f80 = (work->f80 + work->f74) >> 1;
        BubblePShadePack_800D96AC(packs, work->f80, 2);
    }
}

void BubblePAct_800D9974(BubblePWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    work->f7C++;

    if (--work->f74 < 0)
    {
        GV_DestroyActor(&work->actor);
    }

    BubblePUpdatePacks_800D9748(work);
}

void BubblePDie_800D99CC(BubblePWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int BubblePCreatePacks_800D9A08(BubblePWork *work)
{
    DG_PRIM  *prim;
    POLY_FT4 *packs0;
    POLY_FT4 *packs1;
    DG_TEX   *tex;

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 3, 0, work->f44, &work->rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 3000;

    packs0 = &prim->packs[0]->poly_ft4;
    packs1 = &prim->packs[1]->poly_ft4;

    tex = DG_GetTexture(GV_StrCode("awa_1"));
    if (tex == NULL)
    {
        return -1;
    }

    BubblePInitPack_800D96CC(packs0, tex);
    BubblePInitPack_800D96CC(packs1, tex);

    packs0++;
    packs1++;

    tex = DG_GetTexture(GV_StrCode("awa_2"));
    if (tex == NULL)
    {
        return -1;
    }

    BubblePInitPack_800D96CC(packs0, tex);
    BubblePInitPack_800D96CC(packs1, tex);

    packs0++;
    packs1++;

    tex = DG_GetTexture(GV_StrCode("awa_3"));
    if (tex == NULL)
    {
        return -1;
    }

    BubblePInitPack_800D96CC(packs0, tex);
    BubblePInitPack_800D96CC(packs1, tex);

    work->f80 = 128;
    return 0;
}

int BubblePGetResources_800D9B58(BubblePWork *work, SVECTOR *arg1, SVECTOR *arg2, int arg3)
{
    SVECTOR vec;
    int     i;

    work->map = GM_CurrentMap_800AB9B0;

    vec = *arg2;
    vec.vx /= 6;
    vec.vy /= 6;
    vec.vz /= 6;

    work->f78 = arg3;

    for (i = 0; i < 3; i++)
    {
        work->f44[i] = *arg1;
        work->f44[i].vx += (GV_RandS(256) * work->f78) >> 8;
        work->f44[i].vy += (GV_RandS(256) * work->f78) >> 8;
        work->f44[i].vz += (GV_RandS(256) * work->f78) >> 8;

        work->f5C[i].vx = ((arg2->vx + (arg2->vx * GV_RandU(4))) * work->f78) >> 8;
        work->f5C[i].vy = ((arg2->vy + (arg2->vy * GV_RandU(4))) * work->f78) >> 8;
        work->f5C[i].vz = ((arg2->vz + (arg2->vz * GV_RandU(4))) * work->f78) >> 8;
    }

    work->f7C = 0;

    if (BubblePCreatePacks_800D9A08(work) < 0)
    {
        return -1;
    }

    return 0;
}

GV_ACT *NewBubbleP_800D9D94(SVECTOR *arg0, SVECTOR *arg1, int arg2)
{
    BubblePWork *work;

    work = (BubblePWork *)GV_NewActor(sizeof(EXEC_LEVEL), sizeof(BubblePWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BubblePAct_800D9974, (TActorFunction)BubblePDie_800D99CC, "bubble_p.c");

        work->f74 = 40;

        if (BubblePGetResources_800D9B58(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewBubbleP_800D9E40(SVECTOR *arg0, SVECTOR *arg1, int arg2)
{
    BubblePWork *work;

    work = (BubblePWork *)GV_NewActor(sizeof(EXEC_LEVEL), sizeof(BubblePWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BubblePAct_800D9974, (TActorFunction)BubblePDie_800D99CC, "bubble_p.c");

        work->f74 = 8;

        if (BubblePGetResources_800D9B58(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
