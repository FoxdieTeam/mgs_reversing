#include "put_obj.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct PutObjWork
{
    GV_ACT   actor;
    int      field_20;
    int      field_24;
    int      field_28;
    int      field_2C_count;
    DG_OBJS *field_30_objs[0];
} PutObjWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void PutObjectAct_800E237C(PutObjWork *work)
{
    if (GM_CheckMessage(&work->actor, work->field_20, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
    }
}

void PutObjectDie_800E23B8(PutObjWork *work)
{
    DG_OBJS **objs;
    int       i;

    objs = work->field_30_objs;
    for (i = work->field_2C_count; i > 0; objs++, i--)
    {
        DG_DequeueObjs(*objs);
        if (i == work->field_2C_count)
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

int PutObjectGetResources_800E244C(PutObjWork *work, int name, int where)
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
    work->field_28 = THING_Gcl_GetInt('m');

    def = GV_GetCache(GV_CacheID(work->field_28, 'k'));
    workObjs = work->field_30_objs;
    lit = GM_GetMap(where)->lit;
    GCL_GetOption('s');

    for (i = work->field_2C_count; i > 0; i--)
    {
        GCL_StrToSV(GCL_GetParamResult(), &svec1);
        GCL_StrToSV(GCL_GetParamResult(), &svec2);
        DG_SetPos2(&svec1, &svec2);

        createdObjs = DG_MakeObjs(def, 0x57, 0);
        *workObjs = createdObjs;

        DG_PutObjs(createdObjs);

        if (i == work->field_2C_count)
        {
            DG_MakePreshade(createdObjs, lit->lights, lit->n_lights);
        }
        else
        {
            objsIter1 = createdObjs->objs;
            objsIter2 = (*work->field_30_objs)->objs;
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

GV_ACT *NewPutObject_800E25C0(int name, int where, int argc, char **argv)
{
    SVECTOR svec;

    PutObjWork    *work;
    int            total_ojbects;
    unsigned char *param, *param2;

    total_ojbects = 0;
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
        total_ojbects++;
    }
    printf("(put_obj.c) total ojbect : %d \n", total_ojbects);

    work = (PutObjWork *)GV_NewActor(EXEC_LEVEL, sizeof(PutObjWork) + total_ojbects * sizeof(DG_OBJS *));
    if (work != NULL)
    {
        work->field_20 = name;
        work->field_24 = where;
        work->field_2C_count = total_ojbects;
        GV_SetNamedActor(&work->actor, PutObjectAct_800E237C, PutObjectDie_800E23B8, "put_obj.c");
        if (PutObjectGetResources_800E244C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
