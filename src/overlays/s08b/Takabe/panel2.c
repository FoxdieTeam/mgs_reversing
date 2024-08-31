#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/target.h"
#include "Game/game.h"
#include "common.h"
#include "Takabe/thing.h"

typedef struct Panel2Work
{
    GV_ACT         actor;
    int            where;
    int            name;
    OBJECT_NO_ROTS object;
    SVECTOR        unk4C;
    SVECTOR        unk54;
    SVECTOR        unk5C;
    SVECTOR        unk64;
    TARGET        *target;
    MATRIX         world;
    int            gcl_model_param;
    int            model;
    DG_DEF        *def;
    DG_DEF        *kmd;
    int            unkA0;
    int            unkA4;
    int            raise;
    int            unkAC;
} Panel2Work;

#define EXEC_LEVEL 5

SVECTOR s08b_dword_800C3650 = {0, 0, 65236};

extern SVECTOR DG_ZeroVector_800AB39C;

void     Takabe_FreeObjs_800DC820(DG_OBJS *objs);
DG_OBJS *s00a_unknown3_800DC7BC(int model, LitHeader *lit);

// Modified BreakObj_800D5AC0 (OBJECT_NO_ROTS instead of OBJECT)
void Panel2_800E1244(OBJECT_NO_ROTS *object, int model, int where, int flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT_NO_ROTS));

    object->flag = flag;
    object->map_name = where;
    object->objs = s00a_unknown3_800DC7BC(model, Map_FromId_800314C0(where)->lit);
    object->objs->flag = flag;
}

int     AN_Unknown_800DCE84(SVECTOR *);
GV_ACT *NewSpark2_800CA714(MATRIX *world);

void Panel2Act_800E12B4(Panel2Work *work)
{
    SVECTOR *unk5C;
    TARGET  *target;

    if (work->unkA4 == 0)
    {
        return;
    }

    GM_CurrentMap_800AB9B0 = work->where;

    target = work->target;
    if (target != NULL)
    {
        if ((target->damaged & TARGET_POWER) && work->unkA0 == 0)
        {
            target->damaged &= ~TARGET_POWER;

            DG_FreeObjsPacket_8001ABA8(work->object.objs, 0);
            DG_FreeObjsPacket_8001ABA8(work->object.objs, 1);

            unk5C = &work->unk5C;
            work->object.objs->def = work->kmd;
            work->object.objs->objs[0].model = work->kmd->model;

            AN_Unknown_800DCE84(unk5C);
            NewSpark2_800CA714(&work->world);
            GM_SeSet_80032858(unk5C, 0xB8);

            if (work->unkAC != 0)
            {
                GCL_ExecProc_8001FF2C(work->unkAC, NULL);
            }
            work->unkA0 = 1;
        }
        GM_MoveTarget_8002D500(target, &work->unk5C);
    }
}

void Panel2Die_800E13B0(Panel2Work *work)
{
    if (work->target)
    {
        GM_FreeTarget_8002D4B0(work->target);
    }

    Takabe_FreeObjs_800DC820(work->object.objs);
}

void Panel2InitTarget_800E13F4(Panel2Work *work)
{
    TARGET *target;

    target = GM_AllocTarget_8002D400();
    work->target = target;
    GM_SetTarget_8002DC74(target, TARGET_SEEK | TARGET_POWER, NO_SIDE, &work->unk64);
    GM_Target_8002DCCC(target, 1, -1, 2, 0, &DG_ZeroVector_800AB39C);
}

int Panel2GetResources_800E1460(Panel2Work *work, int name, int where)
{
    SVECTOR         vertices[4];
    SVECTOR        *unk54;
    SVECTOR        *unk4C;
    int             i;
    int             sum_vx, sum_vy, sum_vz;
    int             model;
    OBJECT_NO_ROTS *object;

    unk4C = &work->unk4C;

    work->name = name;
    GM_CurrentMap_800AB9B0 = where;
    work->where = where;

    THING_Gcl_GetSVector('p', unk4C);

    unk54 = &work->unk54;
    THING_Gcl_GetSVector('d', unk54);

    work->unkA4 = THING_Gcl_GetIntDefault('h', 1);
    work->unkA0 = THING_Gcl_GetInt('b');
    work->unkAC = THING_Gcl_GetInt('e');

    object = &work->object;

    GCL_GetOption_80020968('m');
    work->gcl_model_param = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

    model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    work->model = model;
    if (work->unkA0 == 0)
    {
        model = work->gcl_model_param;
    }

    DG_SetPos2_8001BC8C(unk4C, unk54);

    Panel2_800E1244(object, model, work->where, 0x57);

    ReadRotMatrix(&work->object.objs->world);

    work->def = work->object.objs->def;
    work->kmd = (DG_DEF *)GV_GetCache(GV_CacheID(work->model, 'k'));

    DG_PutVector_8001BE48(work->object.objs->def->model[0].vertices, vertices, 4);

    sum_vx = sum_vy = sum_vz = 0;
    for (i = 0; i < 4; i++)
    {
        sum_vx += vertices[i].vx;
        sum_vy += vertices[i].vy;
        sum_vz += vertices[i].vz;
    }

    work->unk5C.vx = sum_vx / 4;
    work->unk5C.vy = sum_vy / 4;
    work->unk5C.vz = sum_vz / 4;

    work->unk64.vx = ABS(work->unk5C.vx - vertices[0].vx) + 1;
    work->unk64.vy = ABS(work->unk5C.vy - vertices[0].vy) + 1;
    work->unk64.vz = ABS(work->unk5C.vz - vertices[0].vz) + 1;

    DG_SetPos2_8001BC8C(&work->unk5C, &work->unk54);
    DG_MovePos_8001BD20(&s08b_dword_800C3650);
    ReadRotMatrix(&work->world);

    if (work->unkA4 == 1 && work->unkA0 == 0)
    {
        Panel2InitTarget_800E13F4(work);
    }
    else
    {
        work->target = NULL;
    }

    if (GCL_GetOption_80020968('r'))
    {
        work->raise = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->object.objs->objs[0].raise = work->raise;
    }
    return 0;
}

GV_ACT *NewPanel2_800E1728(int name, int where, int argc, char **argv)
{
    Panel2Work *work;

    work = (Panel2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Panel2Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)Panel2Act_800E12B4,
                         (TActorFunction)Panel2Die_800E13B0, "panel2.c");
        if (Panel2GetResources_800E1460(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
