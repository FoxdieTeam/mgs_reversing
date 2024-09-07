#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _AsiatoWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  f28;
    SVECTOR  f30;
    SVECTOR  f38;
    SVECTOR  f40;
    int      f48;
    int      f4C;
    int      f50;
    int      f54;
} AsiatoWork;

typedef struct _AsiatoUnk
{
    SVECTOR vec[128];
    short   index;
    short   total;
} AsiatoUnk;

AsiatoUnk SECTION("overlay.bss") asiato2_800E4FC0;

#define EXEC_LEVEL 4

void s01a_asiato2_800DCE0C(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->packs[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->packs[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

void s01a_asiato2_800DCE38(SVECTOR *vec, int x, int y, int z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void Asiato2Act_800DCE48(AsiatoWork *work)
{
    int t;
    int shade;

    if (++work->f48 > (work->f54 - 300))
    {
        GV_DestroyActor(&work->actor);
    }

    t = work->f54 - work->f48;
    if (t < 690)
    {
        shade = 48 - ((690 - t) * 48) / 690;
        s01a_asiato2_800DCE0C(work->prim, work->tex, shade, shade, shade);
    }
    else
    {
        s01a_asiato2_800DCE0C(work->prim, work->tex, 48, 48, 48);
    }
}

void s01a_asiato2_800DCF00(POLY_FT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    int x, y, w, h;
    int x2, y2, w2, h2;

    setPolyFT4(poly);
    setRGB0(poly, r, g, b);

    if (abr < 4)
    {
        setSemiTrans(poly, 1);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;

        poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
    }
    else
    {
        x2 = tex->off_x;
        w2 = tex->w;
        y2 = tex->off_y;
        h2 = tex->h;

        setUVWH(poly, x2, y2, w2, h2);

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
}

int Asiato2GetResources_800DCFF4(AsiatoWork *work, MATRIX *world, int arg2, int height, int arg4)
{
    SVECTOR  rot;
    SVECTOR  pos;
    DG_PRIM *prim;
    DG_TEX  *tex;

    s01a_asiato2_800DCE38(&rot, 0, arg4, 0);

    if (arg2 == 1)
    {
        s01a_asiato2_800DCE38(&work->f30, -70, 0, -140);
        s01a_asiato2_800DCE38(&work->f28, 70, 0, -140);
        s01a_asiato2_800DCE38(&work->f40, -70, 0, 140);
        s01a_asiato2_800DCE38(&work->f38, 70, 0, 140);
    }
    else
    {
        s01a_asiato2_800DCE38(&work->f28, -70, 0, -140);
        s01a_asiato2_800DCE38(&work->f30, 70, 0, -140);
        s01a_asiato2_800DCE38(&work->f38, -70, 0, 140);
        s01a_asiato2_800DCE38(&work->f40, 70, 0, 140);
    }

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 1, 0, &work->f28, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];

    pos.vy = height;

    tex = DG_GetTexture(PCX_ASIATO);
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    s01a_asiato2_800DCF00(&prim->packs[0]->poly_ft4, tex, 2, 48, 48, 48);
    s01a_asiato2_800DCF00(&prim->packs[1]->poly_ft4, tex, 2, 48, 48, 48);

    DG_SetPos2(&pos, &rot);
    DG_PutPrim(&work->prim->world);

    return 0;
}

void Asiato2Die_800DD1C8(AsiatoWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    asiato2_800E4FC0.vec[work->f4C].pad = 0;
    asiato2_800E4FC0.total--;
}

GV_ACT * NewAsiato2_800DD238(MATRIX *world, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor(EXEC_LEVEL, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)Asiato2Act_800DCE48, (TActorFunction)Asiato2Die_800DD1C8, "asiato2.c");

        work->f4C = arg3;
        work->f54 = arg6;

        if (Asiato2GetResources_800DCFF4(work, world, arg1, arg2, arg5) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f48 = arg4;
    }

    return &work->actor;
}

typedef struct _Asiato2Work2
{
    GV_ACT   actor;
    CONTROL *control;
    OBJECT  *object;
    int      f28;
    int      f2C;
    int      f30;
    int     *f34;
} Asiato2Work2;

int s01a_blink_tx_800DD308(Asiato2Work2 *work, int name)
{
    HZD_EVT *events;
    int      i;

    events = &work->control->field_10_events;
    for (i = 0; i < events->field_6_count; i++)
    {
        if (events->field_8_array[i] == name)
        {
            return 1;
        }
    }

    return 0;
}

int s01a_blink_tx_800DD358(Asiato2Work2 *work)
{
    work->f28 = 0;

    if (s01a_blink_tx_800DD308(work, 0xCA85))
    {
        work->f2C = 360;
        return 0;
    }

    if (work->f2C > 0)
    {
        work->f28 = 360 - work->f2C;
        work->f2C--;
        return 1;
    }

    return s01a_blink_tx_800DD308(work, 0xDC55);
}

int s01a_blink_tx_800DD3D4(Asiato2Work2 *work)
{
    int temp_s0;

    temp_s0 = *work->f34 & 0x3;
    if (temp_s0 == 0)
    {
        return 0;
    }

    if (!s01a_blink_tx_800DD358(work))
    {
        return 0;
    }

    return temp_s0;
}

void s01a_blink_tx_800DD42C(Asiato2Work2 *work)
{
    asiato2_800E4FC0.vec[asiato2_800E4FC0.index] = work->control->mov;
    asiato2_800E4FC0.vec[asiato2_800E4FC0.index].pad = 1;

    asiato2_800E4FC0.total++;

    if (++asiato2_800E4FC0.index >= 128)
    {
        asiato2_800E4FC0.index = 0;
    }
}

void s01a_blink_tx_800DD4AC(Asiato2Work2 *work)
{
    int     which;
    MATRIX *world;

    which = s01a_blink_tx_800DD3D4(work);
    if (which == 0 || asiato2_800E4FC0.total >= 128)
    {
        return;
    }

    if (which == 1)
    {
        world = &work->object->objs->objs[12].world;
    }
    else
    {
        world = &work->object->objs->objs[15].world;
    }

    s01a_blink_tx_800DD42C(work);

    GM_CurrentMap_800AB9B0 = work->control->map->index;

    NewAsiato2_800DD238(world, which, work->control->levels[0], asiato2_800E4FC0.index - 1, work->f28, work->control->rot.vy, work->f30);
}

void s01a_blink_tx_800DD58C(Asiato2Work2 *work)
{
}

void s01a_blink_tx_800DD594(Asiato2Work2 *work)
{
    int i;

    for (i = 0; i < 128; i++)
    {
        s01a_asiato2_800DCE38(&asiato2_800E4FC0.vec[i], 0, 0, 0);
        asiato2_800E4FC0.vec[i].pad = 0;
    }

    asiato2_800E4FC0.index = 0;
    asiato2_800E4FC0.total = 0;

    work->f2C = 0;
}

GV_ACT * s01a_blink_tx_800DD60C(CONTROL *control, OBJECT *object, int arg2, int *arg3)
{
    Asiato2Work2 *work;

    work = (Asiato2Work2 *)GV_NewActor(4, sizeof(Asiato2Work2));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor,
                         (TActorFunction)s01a_blink_tx_800DD4AC,
                         (TActorFunction)s01a_blink_tx_800DD58C,
                         "asiato2.c");

        work->control = control;
        work->object = object;
        work->f30 = arg2;
        work->f34 = arg3;

        s01a_blink_tx_800DD594(work);
    }

    return &work->actor;
}
