#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "strcode.h"

extern int GV_Clock;

/*---------------------------------------------------------------------------*/

typedef struct Kogaku2Work
{
    GV_ACT  actor;
    OBJECT *parent;
    int     num_parent;
    int     field_28_obj_old_flag;
    int     field_2C_ypos2;
    int     field_30_ypos1;
    int     field_34_ypos3_ninja;
    int     field_38_ninja_var;
    int     field_3C_msg_is_8650;
    int     field_40_rgb;
} Kogaku2Work;

#define EXEC_LEVEL 1

/*---------------------------------------------------------------------------*/

// TODO: Originally mistaken for EQ_InvisibleUnit, give it a better name
STATIC void EQ_InvisibleUnit2(DG_OBJS *objs, unsigned int color, int arg2)
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
STATIC int EQ_VisibleUnit2(short *arg0, char *arg1)
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

STATIC void Kogaku2Act2(Kogaku2Work *work);
STATIC void Kogaku2Die2(Kogaku2Work *work);

STATIC POLY_GT4 *kogaku2_tpage_uv_update_80060F98(POLY_GT4 *packs, int n_packs)
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

STATIC POLY_GT4 *kogaku2_tpage_uv_rgb_update_800610A4(POLY_GT4 *packs, int n_packs, int ypos)
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
                LSTORE(0x3C808080, &packs->r0);
                LSTORE(0x3C808080, &packs->r1);
                LSTORE(0x3C808080, &packs->r2);
                LSTORE(0x3C808080, &packs->r3);
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

STATIC void kogaku2_update_prims1_80061204(Kogaku2Work *work)
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
                pPack = kogaku2_tpage_uv_update_80060F98(pPack, j->n_packs);
            }
        }
        --n_models;
    }
}

STATIC void kogaku2_update_prims2_800612BC(Kogaku2Work *work)
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
                pPack = kogaku2_tpage_uv_rgb_update_800610A4(pPack, j->n_packs, work->field_2C_ypos2);
            }
        }
        --n_models;
    }
}

STATIC void kogaku2_kill_helper_80061384(Kogaku2Work *work)
{
    DG_OBJS *objs;     // $a2
    DG_OBJ  *pIter;    // $s0
    int      n_models; // $s1

    objs = work->parent->objs;
    pIter = objs->objs;
    n_models = objs->n_models;
    objs->flag = (objs->flag & DG_FLAG_INVISIBLE) | (work->field_28_obj_old_flag & ~DG_FLAG_INVISIBLE);
    while (n_models > 0)
    {
        DG_WriteObjPacketUV(pIter, 0);
        DG_WriteObjPacketUV(pIter, 1);
        ++pIter;
        --n_models;
    }
}

STATIC void Kogaku2Act(Kogaku2Work *work)
{
    int ypos2 = work->field_2C_ypos2;
    if (work->field_30_ypos1 < ypos2)
    {
        work->field_2C_ypos2 = ypos2 - work->field_38_ninja_var;
        kogaku2_update_prims2_800612BC(work);

        ypos2 = work->field_2C_ypos2;
        if (work->field_30_ypos1 >= ypos2)
        {
            EQ_InvisibleUnit2(work->parent->objs, work->field_40_rgb, 0);
        }
    }
    else
    {
        EQ_InvisibleUnit2(work->parent->objs, work->field_40_rgb, 1);
        kogaku2_update_prims1_80061204(work);
    }
    if (GM_GameStatus & STATE_THERMG)
    {
        work->parent->objs->flag = work->field_28_obj_old_flag;
        DG_FreeObjsPacket(work->parent->objs, 0);
        DG_FreeObjsPacket(work->parent->objs, 1);
        work->actor.act = (GV_ACTFUNC)Kogaku2Act2;
        work->actor.die = (GV_ACTFUNC)Kogaku2Die2;
    }
}

STATIC void Kogaku2Die(Kogaku2Work *work)
{
    kogaku2_kill_helper_80061384(work);
}

STATIC void Kogaku2Act2(Kogaku2Work *work)
{
    if (!(GM_GameStatus & STATE_THERMG))
    {
        work->parent->objs->flag &= ~DG_FLAG_SHADE;
        work->parent->objs->flag &= ~DG_FLAG_BOUND;
        work->parent->objs->flag |= DG_FLAG_GBOUND;
        EQ_InvisibleUnit2(work->parent->objs, work->field_40_rgb, 0);
        work->actor.act = (GV_ACTFUNC)Kogaku2Act;
        work->actor.die = (GV_ACTFUNC)Kogaku2Die;
    }
    else
    {
        work->field_2C_ypos2 = work->field_30_ypos1;
    }
}

STATIC void Kogaku2Die2(Kogaku2Work *work)
{
    /* do nothing */
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewKogaku2(CONTROL *control, OBJECT *parent, int num_parent)
{
    Kogaku2Work *work;
    DG_OBJS *objs;

    work = (Kogaku2Work *) GV_NewActor(EXEC_LEVEL, sizeof(Kogaku2Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                        (GV_ACTFUNC)Kogaku2Act,
                        (GV_ACTFUNC)Kogaku2Die,
                        "kogaku2.c");

        work->parent = parent;
        work->num_parent = num_parent;
        work->field_2C_ypos2 = 0;
        work->field_30_ypos1 = 1;
        objs = work->parent->objs;

        work->field_28_obj_old_flag = objs->flag;
        DG_UnShadeObjs(objs);
        DG_UnBoundObjs(objs);
        DG_GBoundObjs(objs);

        if (control->name == CHARA_SNAKE)
        {
            work->field_3C_msg_is_8650 = 1;
            work->field_40_rgb = 0x3C60A080;
            EQ_InvisibleUnit2(objs, work->field_40_rgb , 0);
        }
        else
        {
            work->field_40_rgb = 0x3C808080;
            EQ_InvisibleUnit2(objs, work->field_40_rgb , 0);
        }
    }

    return &work->actor;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewKogaku3(CONTROL *control, OBJECT *parent, int num_parent)
{
    SVECTOR vecs[9];
    long coords[9];
    long unused;

    Kogaku2Work *work;
    DG_OBJS *objs;
    DG_DEF *def;
    int maxx, maxy, maxz;
    int minx, miny, minz;
    int i;
    SVECTOR *vec_iter;
    int max, min;
    long *coord_iter;
    int y;

    work = (Kogaku2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Kogaku2Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)Kogaku2Act,
                         (GV_ACTFUNC)Kogaku2Die,
                         "kogaku2.c");

        work->parent = parent;
        work->num_parent = num_parent;

        objs = work->parent->objs;
        def = work->parent->objs->def;

        DG_UnShadeObjs(objs);
        DG_SetPos(&objs->objs[0].screen);

        maxx = def->max.vx;
        maxy = def->max.vy;
        maxz = def->max.vz;

        minx = def->min.vx;
        miny = def->min.vy;
        minz = def->min.vz;

        vec_iter = vecs;

        for (i = 9; i > 0; i--)
        {
            if (i & 1)
            {
                vec_iter->vx = maxx;
            }
            else
            {
                vec_iter->vx = minx;
            }

            if (i & 2)
            {
                vec_iter->vy = maxy;
            }
            else
            {
                vec_iter->vy = miny;
            }

            if (i & 4)
            {
                vec_iter->vz = maxz;
            }
            else
            {
                vec_iter->vz = minz;
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

        work->field_2C_ypos2 = max;
        work->field_34_ypos3_ninja = max;
        work->field_30_ypos1 = min;
        work->field_38_ninja_var = (max - min) / 10;

        if (work->field_38_ninja_var == 0)
        {
            work->field_38_ninja_var = 1;
        }

        if (control->name == CHARA_SNAKE)
        {
            work->field_3C_msg_is_8650 = 1;
            work->field_40_rgb = 0x3C60A080;
        }
        else
        {
            work->field_40_rgb = 0x3C808080;
        }
    }

    return (GV_ACT *)work;
}
