#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "common.h"
#include "takabe/thing.h"

#include "takabe/spark2.h"      // for NewSpark2_800CA714

typedef struct _Work
{
    GV_ACT         actor;
    int            where;
    int            name;
    OBJECT_NO_ROTS body;
    SVECTOR        pos;
    SVECTOR        dir;
    SVECTOR        center;
    SVECTOR        size;
    TARGET        *target;
    MATRIX         world;
    int            model1;
    int            model2;
    DG_DEF        *def;
    DG_DEF        *kmd;
    int            broken;
    int            hittable;
    int            raise;
    int            proc_id;
} Work;

#define EXEC_LEVEL  GV_ACTOR_LEVEL5

#define OBJECT_FLAG ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

static SVECTOR panel_pos = {0, 0, 65236};

void     Takabe_FreeObjs(DG_OBJS *objs);
DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

void AN_PanelSmoke(SVECTOR *pos);

static void InitObject(OBJECT_NO_ROTS *object, int model, int where, int flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT_NO_ROTS));

    object->flag = flag;
    object->map_name = where;
    object->objs = Takabe_MakePreshade(model, GM_GetMap(where)->lit);
    object->objs->flag = flag;
}

static void Act(Work *work)
{
    SVECTOR *center;
    TARGET  *target;

    if (work->hittable == 0)
    {
        return;
    }

    GM_SetCurrentMap(work->where);

    target = work->target;
    if (target != NULL)
    {
        if ((target->damaged & TARGET_POWER) && work->broken == 0)
        {
            target->damaged &= ~TARGET_POWER;

            DG_FreeObjsPacket(work->body.objs, 0);
            DG_FreeObjsPacket(work->body.objs, 1);

            center = &work->center;
            work->body.objs->def = work->kmd;
            work->body.objs->objs[0].model = work->kmd->model;

            AN_PanelSmoke(center);
            NewSpark2_800CA714(&work->world);
            GM_SeSet(center, 184);

            if (work->proc_id != 0)
            {
                GCL_ExecProc(work->proc_id, NULL);
            }
            work->broken = 1;
        }
        GM_MoveTarget(target, &work->center);
    }
}

static void Die(Work *work)
{
    if (work->target)
    {
        GM_FreeTarget(work->target);
    }

    Takabe_FreeObjs(work->body.objs);
}

static void InitTarget(Work *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, TARGET_SEEK | TARGET_POWER, NO_SIDE, &work->size);
    GM_Target_8002DCCC(target, 1, -1, 2, 0, &DG_ZeroVector);
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR         vertices[4];
    SVECTOR        *dir;
    SVECTOR        *pos;
    int             i;
    int             sum_vx, sum_vy, sum_vz;
    int             model;
    OBJECT_NO_ROTS *body;

    pos = &work->pos;

    work->name = name;
    GM_SetCurrentMap(where);
    work->where = where;

    THING_Gcl_GetSVector('p', pos);

    dir = &work->dir;
    THING_Gcl_GetSVector('d', dir);

    work->hittable = THING_Gcl_GetIntDefault('h', 1);
    work->broken = THING_Gcl_GetInt('b');
    work->proc_id = THING_Gcl_GetInt('e');

    body = &work->body;

    GCL_GetOption('m');
    work->model1 = GCL_StrToInt(GCL_GetParamResult());

    model = GCL_StrToInt(GCL_GetParamResult());
    work->model2 = model;
    if (work->broken == 0)
    {
        model = work->model1;
    }

    DG_SetPos2(pos, dir);

    InitObject(body, model, work->where, OBJECT_FLAG);

    ReadRotMatrix(&work->body.objs->world);

    work->def = work->body.objs->def;
    work->kmd = (DG_DEF *)GV_GetCache(GV_CacheID(work->model2, 'k'));

    DG_PutVector(work->body.objs->def->model[0].vertices, vertices, 4);

    sum_vx = sum_vy = sum_vz = 0;
    for (i = 0; i < 4; i++)
    {
        sum_vx += vertices[i].vx;
        sum_vy += vertices[i].vy;
        sum_vz += vertices[i].vz;
    }

    work->center.vx = sum_vx / 4;
    work->center.vy = sum_vy / 4;
    work->center.vz = sum_vz / 4;

    work->size.vx = ABS(work->center.vx - vertices[0].vx) + 1;
    work->size.vy = ABS(work->center.vy - vertices[0].vy) + 1;
    work->size.vz = ABS(work->center.vz - vertices[0].vz) + 1;

    DG_SetPos2(&work->center, &work->dir);
    DG_MovePos(&panel_pos);
    ReadRotMatrix(&work->world);

    if (work->hittable == 1 && work->broken == 0)
    {
        InitTarget(work);
    }
    else
    {
        work->target = NULL;
    }

    if (GCL_GetOption('r'))
    {
        work->raise = GCL_StrToInt(GCL_GetParamResult());
        work->body.objs->objs[0].raise = work->raise;
    }
    return 0;
}

void *NewPanel2(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "panel2.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
