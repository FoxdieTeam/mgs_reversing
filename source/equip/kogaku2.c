#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_MANAGER

#define SNAKE_COLOR     MAKE_RGBA(128,160, 96,0x3C)  // 0x3C = POLY_GT4
#define NINJA_COLOR     MAKE_RGBA(128,128,128,0x3C)  // 0x3C = POLY_GT4

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT *parent;
    int     num_parent;
    int     saved_objs_flag;
    int     ypos2;              // TODO: rename?
    int     ypos1;              // TODO: rename?
    int     ypos3_ninja;        // TODO: rename?
    int     ninja_var;          // TODO: rename?
    int     player_flag;        // Set but not used.
    int     color;              // RGB + primitive code
} Work;

/*---------------------------------------------------------------------------*/

// TODO: Originally mistaken for EQ_InvisibleUnit, give it a better name
static void EQ_InvisibleUnit2(DG_OBJS *objs, unsigned int color, int arg2)
{
    int       i;
    int       n_models;
    DG_OBJ   *obj;
    POLY_GT4 *poly;
    DG_OBJ   *iter;
    int       n_packs;

    for (i = 0; i < 2; i++)
    {
        obj = objs->objs;

        for (n_models = objs->n_models; n_models > 0; n_models--)
        {
            poly = obj->packs[i];

            if (!poly)
            {
                obj++;
                continue;
            }

            if ((arg2 != 0) && (LLOAD(&poly->r0) == color))
            {
                continue;
            }

            for (iter = obj; iter; iter = iter->extend)
            {
                for (n_packs = iter->n_packs; n_packs > 0; n_packs--)
                {
                    LSTORE(color, &poly->r0);
                    LSTORE(color, &poly->r1);
                    LSTORE(color, &poly->r2);
                    LSTORE(color, &poly->r3);
                    poly++;
                }
            }

            obj++;
        }
    }
}

// TODO: Originally mistaken for EQ_VisibleUnit, give it a better name
static int EQ_VisibleUnit2(short *arg0, char *arg1)
{
    int adjust;
    int x, y;

    adjust = ((arg0[0] / 4) - 160);
    x = arg0[0] - adjust;

    if (x < 0)
    {
        x = 0;
    }

    if (x > 319)
    {
        x = 319;
    }

    arg1[0] = x;

    y = arg0[1] + 112;

    if (y < 0)
    {
        y = 0;
    }

    if (y > 223)
    {
        y = 223;
    }

    arg1[1] = y;

    return x > 255;
}

/*---------------------------------------------------------------------------*/

static POLY_GT4 *TPageUVUpdate(POLY_GT4 *packs, int n_packs)
{
    int tpage;
    int visible;

    if (GV_Clock != 0)
    {
        tpage = getTPage(2, 0, 0, 0);
    }
    else
    {
        tpage = getTPage(2, 0, 320, 0);
    }

    while (--n_packs >= 0)
    {
        if ((packs->tag & 0xff000000) != 0)
        {
            visible  = EQ_VisibleUnit2(&packs->x0, &packs->u0);
            visible |= EQ_VisibleUnit2(&packs->x1, &packs->u1);
            visible |= EQ_VisibleUnit2(&packs->x2, &packs->u2);
            visible |= EQ_VisibleUnit2(&packs->x3, &packs->u3);

            if (visible != 0)
            {
                packs->tpage = tpage + 1;
                packs->u0 -= 64;
                packs->u1 -= 64;
                packs->u2 -= 64;
                packs->u3 -= 64;
            }
            else
            {
                packs->tpage = tpage;
            }
        }

        packs++;
    }

    return packs;
}

static POLY_GT4 *TPageUVRGBUpdate(POLY_GT4 *packs, int n_packs, int ypos)
{
    int tpage;
    int visible;

    if (GV_Clock != 0)
    {
        tpage = getTPage(2, 0, 0, 0);
    }
    else
    {
        tpage = getTPage(2, 0, 320, 0);
    }

    while (--n_packs >= 0)
    {
        if (packs->y0 > ypos)
        {
            if ((packs->tpage & 0x180) != getTPage(2, 0, 0, 0))
            {
                LSTORE(NINJA_COLOR, &packs->r0);
                LSTORE(NINJA_COLOR, &packs->r1);
                LSTORE(NINJA_COLOR, &packs->r2);
                LSTORE(NINJA_COLOR, &packs->r3);
            }

            if ((packs->tag & 0xff000000) != 0)
            {
                visible  = EQ_VisibleUnit2(&packs->x0, &packs->u0);
                visible |= EQ_VisibleUnit2(&packs->x1, &packs->u1);
                visible |= EQ_VisibleUnit2(&packs->x2, &packs->u2);
                visible |= EQ_VisibleUnit2(&packs->x3, &packs->u3);

                if (visible != 0)
                {
                    packs->tpage = tpage + 1;
                    packs->u0 -= 64;
                    packs->u1 -= 64;
                    packs->u2 -= 64;
                    packs->u3 -= 64;
                }
                else
                {
                    packs->tpage = tpage;
                }
            }
        }

        packs++;
    }

    return packs;
}

static void UpdatePrims1(Work *work)
{
    DG_OBJS  *objs;     // $v0
    int       n_models; // $s2
    DG_OBJ   *i;        // $s1
    POLY_GT4 *pPack;    // $v0
    DG_OBJ   *j;        // $s0

    objs = work->parent->objs;
    n_models = objs->n_models;
    for (i = objs->objs; n_models > 0; ++i)
    {
        pPack = i->packs[1 - GV_Clock];
        if (pPack)
        {
            for (j = i; j; j = j->extend)
            {
                pPack = TPageUVUpdate(pPack, j->n_packs);
            }
        }
        --n_models;
    }
}

static void UpdatePrims2(Work *work)
{
    DG_OBJS  *objs;     // $v0
    int       n_models; // $s2
    DG_OBJ   *i;        // $s1
    POLY_GT4 *pPack;    // $v0
    DG_OBJ   *j;        // $s0

    objs = work->parent->objs;
    n_models = objs->n_models;
    for (i = objs->objs; n_models > 0; ++i)
    {
        pPack = i->packs[1 - GV_Clock];
        if (pPack)
        {
            for (j = i; j; j = j->extend)
            {
                pPack = TPageUVRGBUpdate(pPack, j->n_packs, work->ypos2);
            }
        }
        --n_models;
    }
}

static void RestoreModelFlags(Work *work)
{
    DG_OBJS *objs;
    DG_OBJ  *obj;
    int      n_models;

    objs = work->parent->objs;
    obj = objs->objs;
    n_models = objs->n_models;
    objs->flag = (objs->flag & DG_FLAG_INVISIBLE) | (work->saved_objs_flag & ~DG_FLAG_INVISIBLE);
    while (n_models > 0)
    {
        DG_WriteObjPacketUV(obj, 0);
        DG_WriteObjPacketUV(obj, 1);
        ++obj;
        --n_models;
    }
}

static void Act2(Work *work);
static void Die2(Work *work);

static void Act(Work *work)
{
    int ypos2 = work->ypos2;
    if (work->ypos1 < ypos2)
    {
        work->ypos2 = ypos2 - work->ninja_var;
        UpdatePrims2(work);

        ypos2 = work->ypos2;
        if (work->ypos1 >= ypos2)
        {
            EQ_InvisibleUnit2(work->parent->objs, work->color, 0);
        }
    }
    else
    {
        EQ_InvisibleUnit2(work->parent->objs, work->color, 1);
        UpdatePrims1(work);
    }
    if (GM_GameStatus & STATE_THERMG)
    {
        work->parent->objs->flag = work->saved_objs_flag;
        DG_FreeObjsPacket(work->parent->objs, 0);
        DG_FreeObjsPacket(work->parent->objs, 1);
        work->actor.act = (GV_ACTFUNC)Act2;
        work->actor.die = (GV_ACTFUNC)Die2;
    }
}

static void Die(Work *work)
{
    RestoreModelFlags(work);
}

static void Act2(Work *work)
{
    if (!(GM_GameStatus & STATE_THERMG))
    {
        work->parent->objs->flag &= ~DG_FLAG_SHADE;
        work->parent->objs->flag &= ~DG_FLAG_BOUND;
        work->parent->objs->flag |= DG_FLAG_GBOUND;
        EQ_InvisibleUnit2(work->parent->objs, work->color, 0);
        work->actor.act = (GV_ACTFUNC)Act;
        work->actor.die = (GV_ACTFUNC)Die;
    }
    else
    {
        work->ypos2 = work->ypos1;
    }
}

static void Die2(Work *work)
{
    /* do nothing */
}

/*---------------------------------------------------------------------------*/

void *NewKogaku2(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work;
    DG_OBJS *objs;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "kogaku2.c");

        work->parent = parent;
        work->num_parent = num_parent;
        work->ypos2 = 0;
        work->ypos1 = 1;
        objs = work->parent->objs;

        work->saved_objs_flag = objs->flag;
        DG_UnShadeObjs(objs);
        DG_UnBoundObjs(objs);
        DG_GBoundObjs(objs);

        if (control->name == CHARAID_SNAKE)
        {
            work->player_flag = 1;
            work->color = SNAKE_COLOR;
            EQ_InvisibleUnit2(objs, work->color , 0);
        }
        else
        {
            work->color = NINJA_COLOR;
            EQ_InvisibleUnit2(objs, work->color , 0);
        }
    }

    return (void *)work;
}

/*---------------------------------------------------------------------------*/

void *NewKogaku3(CONTROL *control, OBJECT *parent, int num_parent)
{
    SVECTOR vecs[9];
    long coords[9];
    long unused;

    Work *work;
    DG_OBJS *objs;
    DG_DEF *def;
    int minx, miny, minz;
    int maxx, maxy, maxz;
    int i;
    SVECTOR *vec_iter;
    int max, min;
    long *coord_iter;
    int y;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "kogaku2.c");

        work->parent = parent;
        work->num_parent = num_parent;

        objs = work->parent->objs;
        def = work->parent->objs->def;

        DG_UnShadeObjs(objs);
        DG_SetPos(&objs->objs[0].screen);

        minx = def->min.vx;
        miny = def->min.vy;
        minz = def->min.vz;

        maxx = def->max.vx;
        maxy = def->max.vy;
        maxz = def->max.vz;

        vec_iter = vecs;

        for (i = 9; i > 0; i--)
        {
            if (i & 1)
            {
                vec_iter->vx = minx;
            }
            else
            {
                vec_iter->vx = maxx;
            }

            if (i & 2)
            {
                vec_iter->vy = miny;
            }
            else
            {
                vec_iter->vy = maxy;
            }

            if (i & 4)
            {
                vec_iter->vz = minz;
            }
            else
            {
                vec_iter->vz = maxz;
            }

            vec_iter++;
        }

        RotTransPers3(&vecs[0], &vecs[1], &vecs[2], &coords[0], &coords[1], &coords[2], &unused, &unused);
        RotTransPers3(&vecs[3], &vecs[4], &vecs[5], &coords[3], &coords[4], &coords[5], &unused, &unused);
        RotTransPers3(&vecs[6], &vecs[7], &vecs[8], &coords[6], &coords[7], &coords[8], &unused, &unused);

        max = -20000;
        min = 20000;

        coord_iter = coords;

        for (i = 8; i > 0; i--)
        {
            y = *coord_iter >> 16;

            if (y > max)
            {
                max = y;
            }

            if (y < min)
            {
                min = y;
            }

            coord_iter++;
        }

        work->ypos2 = max;
        work->ypos3_ninja = max;
        work->ypos1 = min;
        work->ninja_var = (max - min) / 10;

        if (work->ninja_var == 0)
        {
            work->ninja_var = 1;
        }

        if (control->name == CHARAID_SNAKE)
        {
            work->player_flag = 1;
            work->color = SNAKE_COLOR;
        }
        else
        {
            work->color = NINJA_COLOR;
        }
    }

    return (void *)work;
}
