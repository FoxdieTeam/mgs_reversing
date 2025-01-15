#include "dummy_wl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/object.h"
#include "Takabe/thing.h"
#include "Bullet/bakudan.h"

typedef struct DummyWallWork
{
    GV_ACT   actor;
    int      field_20;
    OBJECT   field_24;
    MATRIX   field_108;
    int      field_128;
    int      field_12C;
    int      field_130;
    int      field_134;
    int      field_138;
    int      field_13C;
    int      field_140;
    int      field_144;
    TARGET  *field_148;
    SVECTOR  field_14C;
    SVECTOR  field_154;
    SVECTOR  field_15C;
    int      field_164;
    int      field_168;
    short    field_16C;
    short    field_16E;
    short    field_170;
    short    field_172;
    short    field_174;
    short    field_176;
    short    field_178;
    short    field_17A;
    int      field_17C;
    int      field_180;
    short    field_184;
    short    field_186;
    int      field_188;
    int      field_18C;
    int      field_190;
    short    field_194;
    short    field_196;
    HZD_HDL *field_198;
    HZD_SEG  field_19C;
} DummyWallWork;

SVECTOR s04a_dword_800C3620 = {100, 100, 100};

void     Takabe_FreeObjs_800DC820(DG_OBJS *objs);
void     s16b_800C49AC(HZD_SEG *seg);
DG_OBJS *s00a_unknown3_800DC7BC(int model, LIT *lit);

extern HITTABLE      c4_actors_800BDD78[C4_COUNT];

void DummyWall_800D7418(OBJECT *obj, int model, int where, int flag);
void DummyWall_800D7488(DummyWallWork *work, DG_MDL *mdl);

void DummyWallAct_800D6E64(DummyWallWork *work)
{
    SVECTOR        svec1;
    SVECTOR       *svec2;
    HITTABLE *jirai;
    TARGET        *target;
    int            i;
    OBJECT        *obj;

    target = work->field_148;
    GM_CurrentMap_800AB9B0 = work->field_20;

    if ((target->damaged & TARGET_POWER || work->field_168 != 0) && work->field_164 == 0)
    {
        target->damaged &= ~TARGET_POWER;
        if (work->field_168 != 0 ||
            (target->a_mode == 2 && (target->field_44 == 6 || target->field_44 == 4) && target->field_26_hp < -128))
        {
            work->field_164 = 1;
            if (work->field_168 == 0)
            {
                work->field_190 = 10;
                svec1 = work->field_14C;
                NewAnime_8005E090(&svec1);
            }

            HZD_DequeueDynamicSegment(work->field_198, &work->field_19C);
            work->field_194 = 0;

            jirai = c4_actors_800BDD78;
            for (i = C4_COUNT; i > 0; i--, jirai++)
            {
                if (jirai->actor && jirai->data == &work->field_19C)
                {
                    GV_DestroyActor(jirai->actor);
                }
            }
            Takabe_FreeObjs_800DC820(work->field_24.objs);

            obj = &work->field_24;
            DG_SetPos2(&work->field_14C, &work->field_154);
            DummyWall_800D7418(obj, work->field_180, work->field_20, 0x57);

            work->field_24.objs->objs[0].raise = work->field_17C;
            if (work->field_188 && work->field_168 == 0)
            {
                GCL_ExecProc(work->field_188, NULL);
            }
        }
        target->field_26_hp = 0;
    }

    svec2 = &work->field_15C;
    GM_MoveTarget(target, svec2);

    target->field_26_hp = 0;
    target->damaged &= ~TARGET_PUSH;

    DG_SetPos2(&work->field_14C, &work->field_154);
    GM_ActObject2(&work->field_24);

    if (work->field_190 == 1)
    {
        if (work->field_18C != 0)
        {
            GM_SeSetMode(svec2, work->field_18C, GM_SEMODE_BOMB);
        }
    }

    if (work->field_190 != 0)
    {
        work->field_190--;
    }
}

void DummyWallDie_800D70A4(DummyWallWork *work)
{
    if (work->field_194 != 0)
    {
        HZD_DequeueDynamicSegment(work->field_198, &work->field_19C);
    }
    GM_FreeTarget(work->field_148);
    work->field_24.objs->flag = 0x57;
    Takabe_FreeObjs_800DC820(work->field_24.objs);
}

void DummyWall_800D7104(DummyWallWork *work)
{
    TARGET *target;
    target = GM_AllocTarget();

    work->field_148 = target;
    GM_SetTarget(target, 0x204, 2, &s04a_dword_800C3620);
    GM_Target_8002DCCC(target, 1, -1, 0, 0, &DG_ZeroVector);
    target->damaged = TARGET_STALE;
}

int DummyWallGetResources_800D7178(DummyWallWork *work, int name, int where)
{
    MATRIX   mat;
    SVECTOR  svec1, svec2;
    SVECTOR *svec3, *svec4, *svec5;
    OBJECT  *obj;
    int      param1, param2;

    GM_CurrentMap_800AB9B0 = where;
    work->field_20 = where;

    svec3 = &work->field_14C;
    THING_Gcl_GetSVector('p', svec3);

    svec4 = &work->field_154;
    THING_Gcl_GetSVector('d', svec4);

    work->field_17C = THING_Gcl_GetInt('r');
    param1 = THING_Gcl_GetIntDefault('s', 0);
    work->field_188 = THING_Gcl_GetInt('e');
    work->field_168 = THING_Gcl_GetIntDefault('f', 0);
    work->field_18C = THING_Gcl_GetIntDefault('c', 185);

    obj = &work->field_24;

    GCL_GetOption('m');
    param2 = GCL_StrToInt(GCL_GetParamResult());
    work->field_180 = GCL_StrToInt(GCL_GetParamResult());

    DG_SetPos2(svec3, svec4);

    DummyWall_800D7418(obj, param2, work->field_20, 0x57);

    GM_ConfigObjectLight(obj, &work->field_108);

    DummyWall_800D7104(work);
    DummyWall_800D7488(work, &work->field_24.objs->def->model[0]);

    svec1.vx = work->field_16C;
    svec1.vy = work->field_16E;
    svec1.vz = 0;

    svec5 = &work->field_15C;

    svec2.vx = work->field_174;
    svec2.vy = work->field_176;
    svec2.vz = 0;

    svec5->vx = (work->field_174 + work->field_16C) / 2;
    svec5->vy = 1000;
    svec5->vz = 0;

    DG_PutVector(svec5, svec5, 1);
    ReadRotMatrix(&mat);

    s16b_800C45C4(&work->field_19C, &mat, &svec1, &svec2);
    s16b_800C49AC(&work->field_19C);

    work->field_198 = GM_GetMap(where)->hzd;
    HZD_QueueDynamicSegment2(work->field_198, &work->field_19C, param1);

    work->field_194 = 1;
    work->field_164 = 0;
    work->field_184 = 0;
    work->field_24.objs->objs[0].raise = work->field_17C;

    return 0;
}

GV_ACT *NewDummyWall_800D7384(int name, int where, int argc, char **argv)
{
    DummyWallWork *work;

    work = (DummyWallWork *)GV_NewActor(5, sizeof(DummyWallWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)DummyWallAct_800D6E64,
                         (GV_ACTFUNC)DummyWallDie_800D70A4, "dummy_wl.c");
        if (DummyWallGetResources_800D7178(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void DummyWall_800D7418(OBJECT *obj, int model, int where, int flag)
{
    GV_ZeroMemory(obj, sizeof(OBJECT));
    obj->flag = flag;
    obj->map_name = where;
    obj->objs = s00a_unknown3_800DC7BC(model, GM_GetMap(where)->lit);
    obj->objs->flag = flag;
}

void DummyWall_800D7488(DummyWallWork *work, DG_MDL *mdl)
{
    SVECTOR *vertexIndexOffsetIter;
    int      min_vx, min_vy, min_vz;
    int      max_vx, max_vy, max_vz;
    int      numVertex;

    max_vx = max_vy = max_vz = -32000;
    min_vx = min_vy = min_vz = 32000;

    numVertex = mdl->n_verts;
    vertexIndexOffsetIter = mdl->vertices;

    for (; numVertex > 0; vertexIndexOffsetIter++, numVertex--)
    {
        if (vertexIndexOffsetIter->vx > max_vx)
        {
            max_vx = vertexIndexOffsetIter->vx;
        }
        if (vertexIndexOffsetIter->vx < min_vx)
        {
            min_vx = vertexIndexOffsetIter->vx;
        }

        if (vertexIndexOffsetIter->vy > max_vy)
        {
            max_vy = vertexIndexOffsetIter->vy;
        }
        if (vertexIndexOffsetIter->vy < min_vy)
        {
            min_vy = vertexIndexOffsetIter->vy;
        }

        if (vertexIndexOffsetIter->vz > max_vz)
        {
            max_vz = vertexIndexOffsetIter->vz;
        }
        if (vertexIndexOffsetIter->vz < min_vz)
        {
            min_vz = vertexIndexOffsetIter->vz;
        }
    }

    work->field_16C = min_vx;
    work->field_16E = min_vy;
    work->field_170 = min_vz;

    work->field_174 = max_vx;
    work->field_176 = max_vy;
    work->field_178 = max_vz;
}
