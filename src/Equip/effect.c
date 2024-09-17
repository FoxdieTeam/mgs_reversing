#include "common.h"
#include "Game/game.h"
#include "libdg/libdg.h"

STATIC void EQ_MoveTexture(u_short *in, u_short *out)
{
    u_short i;

    for (i = 0; i < 5; i++)
    {
        *out++ = *in++;
    }
}

void EQ_ChangeTexture(const char *itemName1, const char *itemName2)
{
    u_short temp[5];
    DG_TEX *tex1;
    DG_TEX *tex2;

    tex1 = DG_GetTexture(GV_StrCode(itemName1));
    tex2 = DG_GetTexture(GV_StrCode(itemName2));

    EQ_MoveTexture((u_short *)&tex1->used, temp);
    EQ_MoveTexture((u_short *)&tex2->used, (u_short *)&tex1->used);
    EQ_MoveTexture(temp, (u_short *)&tex2->used);
}

// Remove head model
void EQ_InvisibleHead(OBJECT *object, short *n_packs, short *raise)
{
    if (object->objs->n_models >= 7)
    {
        *n_packs = object->objs->objs[6].n_packs;
        *raise = object->objs->objs[6].raise;
        DG_FreeObjPacket(&object->objs->objs[6], 0);
        DG_FreeObjPacket(&object->objs->objs[6], 1);
        object->objs->objs[6].n_packs = 1;
        object->objs->objs[6].raise = -30000;
    }
}

// Put head model back
void EQ_VisibleHead(OBJECT *object, short *n_packs, short *raise)
{
    if (object->objs->n_models >= 7)
    {
        object->objs->objs[6].n_packs = *n_packs;
        object->objs->objs[6].raise = *raise;
        DG_FreeObjPacket(&object->objs->objs[6], 0);
        DG_FreeObjPacket(&object->objs->objs[6], 1);
    }
}

#ifdef VR_EXE
// Copies of EQ_InvisibleHead/EQ_VisibleHead
// but with additional parameter "idx"

void EQ_InvisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise)
{
    if (idx < object->objs->n_models)
    {
        *n_packs = object->objs->objs[idx].n_packs;
        *raise = object->objs->objs[idx].raise;
        DG_FreeObjPacket(&object->objs->objs[idx], 0);
        DG_FreeObjPacket(&object->objs->objs[idx], 1);
        object->objs->objs[idx].n_packs = 1;
        object->objs->objs[idx].raise = -30000;
    }
}

void EQ_VisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise)
{
    if (idx < object->objs->n_models)
    {
        object->objs->objs[idx].n_packs = *n_packs;
        object->objs->objs[idx].raise = *raise;
        DG_FreeObjPacket(&object->objs->objs[idx], 0);
        DG_FreeObjPacket(&object->objs->objs[idx], 1);
    }
}
#endif

/*STATIC*/
void EQ_InvisibleUnit2(DG_OBJS *objs, unsigned int color, int arg2)
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

/*STATIC*/
int EQ_VisibleUnit2(short *arg0, char *arg1)
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
