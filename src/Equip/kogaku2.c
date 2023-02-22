#include "libgv/libgv.h"
#include "kogaku2.h"
#include "unknown.h"
#include "libgcl/hash.h"

extern int GV_Clock_800AB920;
extern int GM_GameStatus_800AB3CC;

extern const char aKogaku2C[]; // = "kogaku2.c"

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
            visible  = EQ_VisibleUnit_80060F20(&packs->x0, &packs->u0);
            visible |= EQ_VisibleUnit_80060F20(&packs->x1, &packs->u1);
            visible |= EQ_VisibleUnit_80060F20(&packs->x2, &packs->u2);
            visible |= EQ_VisibleUnit_80060F20(&packs->x3, &packs->u3);

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
                visible  = EQ_VisibleUnit_80060F20(&packs->x0, &packs->u0);
                visible |= EQ_VisibleUnit_80060F20(&packs->x1, &packs->u1);
                visible |= EQ_VisibleUnit_80060F20(&packs->x2, &packs->u2);
                visible |= EQ_VisibleUnit_80060F20(&packs->x3, &packs->u3);

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

void kogaku2_update_prims1_80061204(Actor_kogaku2 *pActor)
{
    DG_OBJS  *objs;     // $v0
    int       n_models; // $s2
    DG_OBJ   *i;        // $s1
    POLY_GT4 *pPack;    // $v0
    DG_OBJ   *j;        // $s0

    objs = pActor->field_20_pObj->objs;
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

void kogaku2_update_prims2_800612BC(Actor_kogaku2 *pActor)
{
    DG_OBJS  *objs;     // $v0
    int       n_models; // $s2
    DG_OBJ   *i;        // $s1
    POLY_GT4 *pPack;    // $v0
    DG_OBJ   *j;        // $s0

    objs = pActor->field_20_pObj->objs;
    n_models = objs->n_models;
    for (i = objs->objs; n_models > 0; ++i)
    {
        pPack = i->packs[1 - GV_Clock_800AB920];
        if (pPack)
        {
            for (j = i; j; j = j->extend)
            {
                pPack = kogaku2_tpage_uv_rgb_update_800610A4(pPack, j->n_packs, pActor->field_2C_ypos2);
            }
        }
        --n_models;
    }
}

void kogaku2_kill_helper_80061384(Actor_kogaku2 *pActor)
{
    DG_OBJS *objs;     // $a2
    DG_OBJ  *pIter;    // $s0
    int      n_models; // $s1

    objs = pActor->field_20_pObj->objs;
    pIter = objs->objs;
    n_models = objs->n_models;
    objs->flag = (objs->flag & DG_FLAG_INVISIBLE) | (pActor->field_28_obj_old_flag & ~DG_FLAG_INVISIBLE);
    while (n_models > 0)
    {
        DG_WriteObjPacketUV_8001A774(pIter, 0);
        DG_WriteObjPacketUV_8001A774(pIter, 1);
        ++pIter;
        --n_models;
    }
}

void kogaku2_act_800613FC(Actor_kogaku2 *pActor)
{
    int field_2C_ypos2 = pActor->field_2C_ypos2;
    if (pActor->field_30_ypos1 < field_2C_ypos2)
    {
        pActor->field_2C_ypos2 = field_2C_ypos2 - pActor->field_38_ninja_var;
        kogaku2_update_prims2_800612BC(pActor);

        field_2C_ypos2 = pActor->field_2C_ypos2;
        if (pActor->field_30_ypos1 >= field_2C_ypos2)
        {
            EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 0);
        }
    }
    else
    {
        EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 1);
        kogaku2_update_prims1_80061204(pActor);
    }
    if ((GM_GameStatus_800AB3CC & 8) != 0)
    {
        pActor->field_20_pObj->objs->flag = pActor->field_28_obj_old_flag;
        DG_FreeObjsPacket_8001ABA8(pActor->field_20_pObj->objs, 0);
        DG_FreeObjsPacket_8001ABA8(pActor->field_20_pObj->objs, 1);
        pActor->field_0_actor.mFnUpdate = (TActorFunction)kogaku2_act_helper_80061528;
        pActor->field_0_actor.mFnShutdown = (TActorFunction)kogaku2_act_nullsub_800615F4;
    }
}

void kogaku2_kill_80061508(Actor_kogaku2 *pActor)
{
    kogaku2_kill_helper_80061384(pActor);
}

void kogaku2_act_helper_80061528(Actor_kogaku2 *pActor)
{
    if (!(GM_GameStatus_800AB3CC & 8))
    {
        pActor->field_20_pObj->objs->flag &= ~DG_FLAG_SHADE;
        pActor->field_20_pObj->objs->flag &= ~DG_FLAG_BOUND;
        pActor->field_20_pObj->objs->flag |= DG_FLAG_GBOUND;
        EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 0);
        pActor->field_0_actor.mFnUpdate = (TActorFunction)kogaku2_act_800613FC;
        pActor->field_0_actor.mFnShutdown = (TActorFunction)kogaku2_kill_80061508;
    }
    else
    {
        pActor->field_2C_ypos2 = pActor->field_30_ypos1;
    }
}

void kogaku2_act_nullsub_800615F4(Actor_kogaku2 *pActor)
{
}

Actor_kogaku2 *NewKogaku2_800615FC(GM_Control *pCtrl, OBJECT *pObj, int unit)
{
  Actor_kogaku2 *pActor;
  DG_OBJS *objs;
  pActor = (Actor_kogaku2 *) GV_NewActor_800150E4(1, sizeof(Actor_kogaku2));
  if (pActor)
  {
    GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction) kogaku2_act_800613FC, (TActorFunction) kogaku2_kill_80061508, aKogaku2C);

    pActor->field_20_pObj = pObj;
    pActor->field_24_unit = unit;
    pActor->field_2C_ypos2 = 0;
    pActor->field_30_ypos1 = 1;
    objs = pActor->field_20_pObj->objs;

    pActor->field_28_obj_old_flag = objs->flag;
    DG_UnShadeObjs(objs);
    DG_UnBoundObjs(objs);
    DG_GBoundObjs(objs);

    if (pCtrl->field_30_scriptData == CHARA_SNAKE)
    {
      pActor->field_3C_msg_is_8650 = 1;
      pActor->field_40_rgb = 0x3C60A080;
      EQ_InvisibleUnit_80060E68(objs, pActor->field_40_rgb , 0);
    }
    else
    {
      pActor->field_40_rgb = 0x3C808080;
      EQ_InvisibleUnit_80060E68(objs, pActor->field_40_rgb , 0);
    }
  }
  return pActor;
}

Actor_kogaku2 * NewKogaku3_80061708(GM_Control *pCtrl, OBJECT *pObject, int unit)
{
    SVECTOR vecs[9];
    long coords[9];
    long unused;

    Actor_kogaku2 *pActor;
    DG_OBJS *pObjs;
    DG_DEF *pDef;
    int maxx, maxy, maxz;
    int minx, miny, minz;
    int i;
    SVECTOR *vec_iter;
    int max, min;
    long *coord_iter;
    int y;

    pActor = (Actor_kogaku2 *)GV_NewActor_800150E4(1, sizeof(Actor_kogaku2));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                  (TActorFunction)&kogaku2_act_800613FC,
                                  (TActorFunction)&kogaku2_kill_80061508,
                                  aKogaku2C);

        pActor->field_20_pObj = pObject;
        pActor->field_24_unit = unit;

        pObjs = pActor->field_20_pObj->objs;
        pDef = pActor->field_20_pObj->objs->def;

        DG_UnShadeObjs(pObjs);
        DG_SetPos_8001BC44(&pObjs->objs[0].screen);

        maxx = pDef->max.field_0_x;
        maxy = pDef->max.field_4_y;
        maxz = pDef->max.field_8_z;

        minx = pDef->min.field_0_x;
        miny = pDef->min.field_4_y;
        minz = pDef->min.field_8_z;

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

        RotTransPers3_800934A8(&vecs[0], &vecs[1], &vecs[2], &coords[0], &coords[1], &coords[2], &unused, &unused);
        RotTransPers3_800934A8(&vecs[3], &vecs[4], &vecs[5], &coords[3], &coords[4], &coords[5], &unused, &unused);
        RotTransPers3_800934A8(&vecs[6], &vecs[7], &vecs[8], &coords[6], &coords[7], &coords[8], &unused, &unused);

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

        pActor->field_2C_ypos2 = max;
        pActor->field_34_ypos3_ninja = max;
        pActor->field_30_ypos1 = min;
        pActor->field_38_ninja_var = (max - min) / 10;

        if (pActor->field_38_ninja_var == 0)
        {
            pActor->field_38_ninja_var = 1;
        }

        if (pCtrl->field_30_scriptData == CHARA_SNAKE)
        {
            pActor->field_3C_msg_is_8650 = 1;
            pActor->field_40_rgb = 0x3C60A080;
        }
        else
        {
            pActor->field_40_rgb = 0x3C808080;
        }
    }

    return pActor;
}
