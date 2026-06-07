#include "game/game.h"

#define BODY_DATA GV_StrCode("njatrans")
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _Work
{
    GV_ACT   actor;
    OBJECT   body;
    OBJECT  *root_obj;
    SVECTOR *field_108;
    SVECTOR  rots[32][16];
    MATRIX   world[32];
    int      field_150C;
    int      field_1510;
    int     *field_1514;
    char     field_1518[32];
    int      field_1538;
    int      field_153C;
    MATRIX   light[2];
} Work;

static void s08b_bunsin2_800D54CC(DG_OBJS *objs)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        objs->objs[i].model->flags |= DG_FLAG_PAINT;
    }
}

static void s08b_bunsin2_800D54FC(DG_OBJS *objs)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        objs->objs[i].model->flags &= ~DG_FLAG_PAINT;
    }
}

static void s08b_bunsin2_800D5530(Work *work)
{
    int      index, i;
    SVECTOR *src, *dst;

    if (++work->field_150C >= 32)
    {
        work->field_150C = 0;
    }

    index = work->field_150C;
    work->world[index] = work->root_obj->objs->world;

    src = work->root_obj->objs->rots;
    dst = work->rots[work->field_150C];
    for (i = 0; i < 16; i++)
    {
        *dst = *src;
        dst++;
        src++;
    }
}

void s08b_bunsin2_800D5600(Work *work)
{
    SVECTOR dir;
    int     state;

    state = *work->field_1514;
    if (state == 2)
    {
        s08b_bunsin2_800D54CC(work->root_obj->objs);
        work->field_153C = 2;
    }

    if (work->field_153C > 0)
    {
        GV_DirVec2(GV_RandU(4096), 500, &dir);
        work->world[work->field_150C].t[0] += dir.vx;
        work->world[work->field_150C].t[2] += dir.vz;

        work->field_1518[work->field_150C] = 2;

        if (--work->field_153C == 0)
        {
            s08b_bunsin2_800D54FC(work->root_obj->objs);
        }
    }
    else if (state == 0)
    {
        work->field_1518[work->field_150C] = 0;
    }
    else
    {
        work->field_1518[work->field_150C] = 1;
    }
}

static void s08b_bunsin2_800D5734(Work *work)
{
    int      index;
    DG_OBJS *objs;

    index = work->field_150C - work->field_1510;
    if (index < 0) index += 32;

    objs = work->body.objs;
    objs->world = work->world[index];
    objs->rots = work->rots[index];

    if (work->field_1518[index] != 0)
    {
        DG_VisibleObjs(objs);
    }
    else
    {
        DG_InvisibleObjs(objs);
    }

    work->field_1538++;
}

static void Act(Work *work)
{
    s08b_bunsin2_800D5530(work);
    s08b_bunsin2_800D5600(work);
    s08b_bunsin2_800D5734(work);

    DG_GetLightMatrix2(work->field_108, work->light);
}

static void Die(Work *work)
{
    GM_FreeObject(&work->body);
}

static int GetResources(Work *work, OBJECT *root_obj, int arg2, int *arg3)
{
    OBJECT *body;
    int     i, bright;

    body = &work->body;
    GM_InitObject(body, BODY_DATA, BODY_FLAG, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);

    for (i = 0; i < 16; i++)
    {
        body->objs->objs[i].model->flags |= DG_MODEL_TRANS;
    }

    work->root_obj = root_obj;
    work->field_1510 = arg2;
    work->field_150C = 0;
    work->field_1538 = 0;
    work->field_153C = 0;
    work->field_1514 = arg3;

    bright = (8 - arg2) * 10 + 40;
    work->light[0].t[0] = bright;
    work->light[0].t[1] = bright;
    work->light[0].t[2] = bright;
    return 0;
}

void *NewBunsin2(OBJECT *root_obj, int arg1, int *arg2)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "bunsin2.c");
        if (GetResources(work, root_obj, arg1, arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
