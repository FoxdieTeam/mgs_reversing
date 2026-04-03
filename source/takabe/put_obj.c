#include "put_obj.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      name;
    int      map;
    int      model_name;
    int      n_objs;
    DG_OBJS *objs[0];
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

static void Act(Work *work)
{
    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    DG_OBJS **objs;
    int       i;

    objs = work->objs;
    for (i = work->n_objs; i > 0; objs++, i--)
    {
        DG_DequeueObjs(*objs);
        if (i == work->n_objs)
        {
            DG_FreePreshade(*objs);
        }
        else
        {
            (*objs)->objs[0].rgbs = NULL;
        }
        DG_FreeObjs(*objs);
    }
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR   svec1, svec2;
    DG_DEF   *def;
    DG_OBJS  *createdObjs;
    DG_OBJS **workObjs;
    int       n_models;
    LIT      *lit;
    int       i;
    DG_OBJ   *objsIter2;
    DG_OBJ   *objsIter1;

    GM_CurrentMap = where;
    work->model_name = THING_Gcl_GetInt('m');

    def = GV_GetCache(GV_CacheID(work->model_name, 'k'));
    workObjs = work->objs;
    lit = GM_GetMap(where)->lit;
    GCL_GetOption('s');

    for (i = work->n_objs; i > 0; i--)
    {
        GCL_StrToSV(GCL_GetParamResult(), &svec1);
        GCL_StrToSV(GCL_GetParamResult(), &svec2);
        DG_SetPos2(&svec1, &svec2);

        createdObjs = DG_MakeObjs(def, 0x57, 0);
        *workObjs = createdObjs;

        DG_PutObjs(createdObjs);

        if (i == work->n_objs)
        {
            DG_MakePreshade(createdObjs, lit->lights, lit->n_lights);
        }
        else
        {
            objsIter1 = createdObjs->objs;
            objsIter2 = (*work->objs)->objs;
            n_models = createdObjs->n_models;

            while (n_models > 0)
            {
                n_models--;
                objsIter1->rgbs = objsIter2->rgbs;
                objsIter1++, objsIter2++;
            }
        }
        DG_QueueObjs(createdObjs);
        createdObjs->group_id = where;

        workObjs++;
    }
    return 0;
}

void *NewPutObject(int name, int where, int argc, char **argv)
{
    SVECTOR svec;
    Work   *work;
    int     n_objs;
    u_char *param, *param2;

    n_objs = 0;
    GCL_GetOption('s');
    while ((param = GCL_GetParamResult()))
    {
        GCL_StrToSV(param, &svec);
        param2 = GCL_GetParamResult();
        if (param2 == NULL)
        {
            break;
        }
        GCL_StrToSV(param2, &svec);
        n_objs++;
    }
    printf("(put_obj.c) total ojbect : %d \n", n_objs);

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work) + n_objs * sizeof(DG_OBJS *));
    if (work != NULL)
    {
        work->name = name;
        work->map = where;
        work->n_objs = n_objs;
        GV_SetNamedActor(&work->actor, Act, Die, "put_obj.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
