#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/target.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Takabe/thing.h"
#include "Anime/animeconv/anime.h"

typedef struct BreakObjWork
{
    GV_ACT  actor;
    int     where;
    int     name;
    OBJECT  object;
    MATRIX  light[2];
    TARGET *target;
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    int     flag;
    int     raise;
    int     flag2;
    int     model;
    short   unused1;
    short   unused2;
} BreakObjWork;

#define EXEC_LEVEL 5

unsigned short breakobj_msgs_800C36E8[2] = {0xC39B, 0x881D};
SVECTOR        s08a_dword_800C36EC = {100, 100, 100};

extern int     GV_Clock_800AB920;
extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;

void     Takabe_FreeObjs_800DC820(DG_OBJS *objs);
DG_OBJS *s00a_unknown3_800DC7BC(int model, LitHeader *lit);

void BreakObj_800D5AC0(OBJECT *object, int model, int where, int flag);

void BreakObjAct_800D5670(BreakObjWork *work)
{
    SVECTOR svec;
    TARGET *target;
    int     flag;
    OBJECT *object;

    GM_CurrentMap_800AB9B0 = work->where;

    flag = THING_Msg_CheckMessage(work->name, 2, breakobj_msgs_800C36E8) == 0;

    if (work->flag2)
    {
        target = work->target;
        if ((target->damaged & TARGET_POWER) && !work->flag)
        {
            target->damaged &= ~TARGET_POWER;
            if (target->a_mode == 2)
            {
                work->flag = 1;
                svec = work->svec1;
                NewAnime_8005E090(&svec);
                flag |= 1;
            }
        }
        GM_MoveTarget(target, &work->svec3);
        target->damaged &= ~TARGET_PUSH;
    }

    if (flag)
    {
        object = &work->object;
        Takabe_FreeObjs_800DC820(work->object.objs);
        DG_SetPos2(&work->svec1, &work->svec2);
        BreakObj_800D5AC0(object, work->model, work->where, 0x57);
        if (work->raise != 32767)
        {
            work->object.objs->objs[0].raise = work->raise;
        }
    }

    DG_SetPos2(&work->svec1, &work->svec2);
    GM_ActObject2(&work->object);
}

void BreakObjDie_800D57C4(BreakObjWork *work)
{
    if (work->flag2)
    {
        GM_FreeTarget(work->target);
    }
    Takabe_FreeObjs_800DC820(work->object.objs);
}

void BreakObj_800D580C(BreakObjWork *work)
{
    TARGET *target;

    if (work->flag2)
    {
        work->target = target = GM_AllocTarget();
        GM_SetTarget(target, 4, 2, &s08a_dword_800C36EC);
        GM_Target_8002DCCC(target, 1, -1, 0, 0, &DG_ZeroVector_800AB39C);
        target->damaged = 0;
    }
}

int BreakObjGetResources_800D5894(BreakObjWork *work, int name, int where)
{
    DG_DEF  *def;
    OBJECT  *object;
    SVECTOR *svec1;
    SVECTOR *svec2;
    SVECTOR *svec3;
    int      model;

    svec1 = &work->svec1;

    work->name = name;
    GM_CurrentMap_800AB9B0 = where;
    work->where = where;

    THING_Gcl_GetSVector('p', svec1);

    svec2 = &work->svec2;
    THING_Gcl_GetSVector('d', svec2);

    work->flag2 = THING_Gcl_GetInt('a');

    object = &work->object;

    GCL_GetOption('m');
    model = GCL_StrToInt(GCL_GetParamResult());
    work->model = GCL_StrToInt(GCL_GetParamResult());

    DG_SetPos2(svec1, svec2);
    BreakObj_800D5AC0(object, model, work->where, 0x57);

    GM_ConfigObjectLight(object, work->light);
    BreakObj_800D580C(work);

    def = work->object.objs->def;
    svec3 = &work->svec3;

    svec3->vx = (def->min.vx - def->max.vx) / 2;
    svec3->vy = (def->min.vy - def->max.vy) / 2;
    svec3->vz = (def->min.vz - def->max.vz) / 2;

    GV_AddVec3(&work->svec3, svec1, svec3);

    work->flag = 0;
    work->unused1 = 0;

    if (GCL_GetOption('r'))
    {
        work->raise = GCL_StrToInt(GCL_GetParamResult());
        work->object.objs->objs[0].raise = work->raise;
    }
    else
    {
        work->raise = 32767;
    }

    return 0;
}

GV_ACT *NewBreakObj_800D5A2C(int name, int where)
{
    BreakObjWork *work;

    work = (BreakObjWork *)GV_NewActor(EXEC_LEVEL, sizeof(BreakObjWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BreakObjAct_800D5670,
                         (TActorFunction)BreakObjDie_800D57C4, "breakobj.c");
        if (BreakObjGetResources_800D5894(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void BreakObj_800D5AC0(OBJECT *object, int model, int where, int flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = where;
    object->objs = s00a_unknown3_800DC7BC(model, Map_FromId_800314C0(where)->lit);
    object->objs->flag = flag;
}
