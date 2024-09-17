#include "kogaku2.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Equip/effect.h"
#include "strcode.h"

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

extern int GV_Clock_800AB920;
extern int GM_GameStatus;

void kogaku2_act_helper_80061528(Kogaku2Work *work);
void kogaku2_act_nullsub_800615F4(Kogaku2Work *work);

POLY_GT4 *kogaku2_tpage_uv_update_80060F98(POLY_GT4 *packs, int n_packs)
{
    int tpage;
    int visible;

    if (GV_Clock_800AB920 != 0)
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

POLY_GT4 *kogaku2_tpage_uv_rgb_update_800610A4(POLY_GT4 *packs, int n_packs, int ypos)
{
    int tpage;
    int visible;

    if (GV_Clock_800AB920 != 0)
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

void kogaku2_update_prims1_80061204(Kogaku2Work *work)
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
        pPack = i->packs[1 - GV_Clock_800AB920];
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

void kogaku2_update_prims2_800612BC(Kogaku2Work *work)
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
        pPack = i->packs[1 - GV_Clock_800AB920];
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

void kogaku2_kill_helper_80061384(Kogaku2Work *work)
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

void Kogaku2Act_800613FC(Kogaku2Work *work)
{
    int field_2C_ypos2 = work->field_2C_ypos2;
    if (work->field_30_ypos1 < field_2C_ypos2)
    {
        work->field_2C_ypos2 = field_2C_ypos2 - work->field_38_ninja_var;
        kogaku2_update_prims2_800612BC(work);

        field_2C_ypos2 = work->field_2C_ypos2;
        if (work->field_30_ypos1 >= field_2C_ypos2)
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
        work->actor.act = (GV_ACTFUNC)kogaku2_act_helper_80061528;
        work->actor.die = (GV_ACTFUNC)kogaku2_act_nullsub_800615F4;
    }
}

void Kogaku2Die_80061508(Kogaku2Work *work)
{
    kogaku2_kill_helper_80061384(work);
}

void kogaku2_act_helper_80061528(Kogaku2Work *work)
{
    if (!(GM_GameStatus & STATE_THERMG))
    {
        work->parent->objs->flag &= ~DG_FLAG_SHADE;
        work->parent->objs->flag &= ~DG_FLAG_BOUND;
        work->parent->objs->flag |= DG_FLAG_GBOUND;
        EQ_InvisibleUnit2(work->parent->objs, work->field_40_rgb, 0);
        work->actor.act = (GV_ACTFUNC)Kogaku2Act_800613FC;
        work->actor.die = (GV_ACTFUNC)Kogaku2Die_80061508;
    }
    else
    {
        work->field_2C_ypos2 = work->field_30_ypos1;
    }
}

void kogaku2_act_nullsub_800615F4(Kogaku2Work *work)
{
}

GV_ACT *NewKogaku2_800615FC(CONTROL *control, OBJECT *pObj, int num_parent)
{
  Kogaku2Work *work;
  DG_OBJS *objs;
  work = (Kogaku2Work *) GV_NewActor(1, sizeof(Kogaku2Work));
  if (work)
  {
    GV_SetNamedActor(&work->actor,
                     (GV_ACTFUNC)Kogaku2Act_800613FC,
                     (GV_ACTFUNC)Kogaku2Die_80061508,
                     "kogaku2.c");

    work->parent = pObj;
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

GV_ACT *NewKogaku3_80061708(CONTROL *control, OBJECT *parent, int num_parent)
{
    SVECTOR vecs[9];
    long coords[9];
    long unused;

    Kogaku2Work *work;
    DG_OBJS *pObjs;
    DG_DEF *pDef;
    int maxx, maxy, maxz;
    int minx, miny, minz;
    int i;
    SVECTOR *vec_iter;
    int max, min;
    long *coord_iter;
    int y;

    work = (Kogaku2Work *)GV_NewActor(1, sizeof(Kogaku2Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)Kogaku2Act_800613FC,
                         (GV_ACTFUNC)Kogaku2Die_80061508,
                         "kogaku2.c");

        work->parent = parent;
        work->num_parent = num_parent;

        pObjs = work->parent->objs;
        pDef = work->parent->objs->def;

        DG_UnShadeObjs(pObjs);
        DG_SetPos(&pObjs->objs[0].screen);

        maxx = pDef->max.vx;
        maxy = pDef->max.vy;
        maxz = pDef->max.vz;

        minx = pDef->min.vx;
        miny = pDef->min.vy;
        minz = pDef->min.vz;

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
