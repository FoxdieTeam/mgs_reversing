#include "asiato2.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Asiato2CharWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  pos[4];
    int      f48;
    int      f4C;
    int      f50;
    int      f54;
} Asiato2CharWork;

/*---------------------------------------------------------------------------*/

typedef struct _Asiato2Global
{
    SVECTOR vec[128];
    short   index;
    short   total;
} Asiato2Global;

Asiato2Global SECTION(".bss") asiato2_800E4FC0;

/*---------------------------------------------------------------------------*/

static void Asiato2Char_ShadePacks(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = prim->packs[0];
    setRGB0(poly, r, g, b);

    poly = prim->packs[1];
    setRGB0(poly, r, g, b);
}

static void Asiato2Char_SetPos(SVECTOR *vec, int x, int y, int z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

static void Asiato2Char_Act(Asiato2CharWork *work)
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
        Asiato2Char_ShadePacks(work->prim, work->tex, shade, shade, shade);
    }
    else
    {
        Asiato2Char_ShadePacks(work->prim, work->tex, 48, 48, 48);
    }
}

static void Asiato2Char_InitPacks(POLY_FT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    setPolyFT4(poly);
    setRGB0(poly, r, g, b);

    if (abr < 4)
    {
        setSemiTrans(poly, 1);
        DG_SetPacketTexture4(poly, tex);
        poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
    }
    else
    {
        DG_SetPacketTexture4(poly, tex);
    }
}

static int Asiato2Char_GetResources(Asiato2CharWork *work, MATRIX *world, int arg2, int height, int arg4)
{
    SVECTOR  rot;
    SVECTOR  pos;
    DG_PRIM *prim;
    DG_TEX  *tex;

    Asiato2Char_SetPos(&rot, 0, arg4, 0);

    if (arg2 == 1)
    {
        Asiato2Char_SetPos(&work->pos[1], -70, 0, -140);
        Asiato2Char_SetPos(&work->pos[0], 70, 0, -140);
        Asiato2Char_SetPos(&work->pos[3], -70, 0, 140);
        Asiato2Char_SetPos(&work->pos[2], 70, 0, 140);
    }
    else
    {
        Asiato2Char_SetPos(&work->pos[0], -70, 0, -140);
        Asiato2Char_SetPos(&work->pos[1], 70, 0, -140);
        Asiato2Char_SetPos(&work->pos[2], -70, 0, 140);
        Asiato2Char_SetPos(&work->pos[3], 70, 0, 140);
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, &work->pos[0], NULL);
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

    Asiato2Char_InitPacks(prim->packs[0], tex, 2, 48, 48, 48);
    Asiato2Char_InitPacks(prim->packs[1], tex, 2, 48, 48, 48);

    DG_SetPos2(&pos, &rot);
    DG_PutPrim(&work->prim->world);

    return 0;
}

static void Asiato2Char_Die(Asiato2CharWork *work)
{
    GM_FreePrim(work->prim);

    asiato2_800E4FC0.vec[work->f4C].pad = 0;
    asiato2_800E4FC0.total--;
}

/*---------------------------------------------------------------------------*/

void *NewAsiato2Char(MATRIX *world, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    Asiato2CharWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Asiato2CharWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Asiato2Char_Act, Asiato2Char_Die, "asiato2.c");

        work->f4C = arg3;
        work->f54 = arg6;

        if (Asiato2Char_GetResources(work, world, arg1, arg2, arg5) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f48 = arg4;
    }

    return (void *)work;
}

/*---------------------------------------------------------------------------*/

typedef struct _Asiato2Work
{
    GV_ACT   actor;
    CONTROL *control;
    OBJECT  *object;
    int      f28;
    int      f2C;
    int      f30;
    int     *f34;
} Asiato2Work;

static int asiato2_800DD308(Asiato2Work *work, int name)
{
    HZD_EVT *events;
    int      i;

    events = &work->control->event;
    for (i = 0; i < events->n_triggers; i++)
    {
        if (events->triggers[i] == name)
        {
            return 1;
        }
    }

    return 0;
}

static int asiato2_800DD358(Asiato2Work *work)
{
    work->f28 = 0;

    if (asiato2_800DD308(work, 0xCA85))
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

    return asiato2_800DD308(work, 0xDC55);
}

static int asiato2_800DD3D4(Asiato2Work *work)
{
    int temp_s0;

    temp_s0 = *work->f34 & 0x3;
    if (temp_s0 == 0)
    {
        return 0;
    }

    if (!asiato2_800DD358(work))
    {
        return 0;
    }

    return temp_s0;
}

static void asiato2_800DD42C(Asiato2Work *work)
{
    asiato2_800E4FC0.vec[asiato2_800E4FC0.index] = work->control->mov;
    asiato2_800E4FC0.vec[asiato2_800E4FC0.index].pad = 1;

    asiato2_800E4FC0.total++;

    if (++asiato2_800E4FC0.index >= 128)
    {
        asiato2_800E4FC0.index = 0;
    }
}

static void Act(Asiato2Work *work)
{
    int     which;
    MATRIX *world;

    which = asiato2_800DD3D4(work);
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

    asiato2_800DD42C(work);

    GM_CurrentMap = work->control->map->index;

    NewAsiato2Char(world, which, work->control->levels[0], asiato2_800E4FC0.index - 1, work->f28, work->control->rot.vy, work->f30);
}

static void Die(Asiato2Work *work)
{
}

static void GetResources(Asiato2Work *work)
{
    int i;

    for (i = 0; i < 128; i++)
    {
        Asiato2Char_SetPos(&asiato2_800E4FC0.vec[i], 0, 0, 0);
        asiato2_800E4FC0.vec[i].pad = 0;
    }

    asiato2_800E4FC0.index = 0;
    asiato2_800E4FC0.total = 0;

    work->f2C = 0;
}

/*---------------------------------------------------------------------------*/

void *NewAsiato2(CONTROL *control, OBJECT *object, int arg2, int *arg3)
{
    Asiato2Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Asiato2Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "asiato2.c");

        work->control = control;
        work->object = object;
        work->f30 = arg2;
        work->f34 = arg3;

        GetResources(work);
    }

    return (void *)work;
}
