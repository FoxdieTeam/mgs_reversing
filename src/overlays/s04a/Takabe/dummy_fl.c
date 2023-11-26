#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"

typedef struct _DummyFlap
{
    SVECTOR  pos;
    SVECTOR  rot;
    MATRIX   model;
    DG_OBJS *objs;
    SVECTOR  f34;
    char     pad[0x4];
    SVECTOR  bounds[5];
} DummyFlap;

typedef struct _DummyFloorWork
{
    GV_ACT    actor;
    int       name;
    int       map;
    char      pad[0x4];
    DummyFlap flaps[2];
    MATRIX    world;
    MATRIX    light[2];
    SVECTOR   f15C;
    MATRIX    f164;
    int       f184;
    int       f188;
    int       raise;
    int       f190;
    int       f194;
    int       f198;
    int       f19C;
    int       f1A0;
    int       f1A4;
    int       f1A8;
    int       f1AC;
    int       f1B0;
    int       proc;
    int       f1B8;
    int       f1BC;
    HZD_HDL  *hzd;
    HZD_FLR   floors[2];
} DummyFloorWork;

char dummy_floor_800C3610[] = {0x7F, 0x01, 0x00, 0x00};
char dummy_floor_800C3614[] = {0x50, 0x04, 0x00, 0x00};

SVECTOR dummy_floor_800C3618 = {0, 4096, 0, 0};

extern int GM_CurrentMap_800AB9B0;

int THING_Gcl_GetInt(int);
int THING_Gcl_GetIntDefault(int, int);
int THING_Gcl_GetSVector(int, SVECTOR *);

void Takabe_FreeObjs_800DC820(DG_OBJS *objs);
void Takabe_ReshadeModel_800DC854(DG_OBJS *, LitHeader *);

DG_OBJS *s00a_unknown3_800DC7BC(int model, LitHeader *lit);

void DummyFloor_800D6C94(DummyFloorWork *work, DummyFlap *flap, int model, int map);
void DummyFloor_800D6D38(SVECTOR *in, HZD_FLR *floor);

#define EXEC_LEVEL 5

#pragma INCLUDE_ASM("asm/overlays/s04a/DummyFloorAct_800D61A4.s")
void DummyFloorAct_800D61A4(DummyFloorWork *work);

void DummyFloorDie_800D61A4(DummyFloorWork *work)
{
    if (work->f1BC != 0)
    {
        HZD_DequeueDynamicFloor_8006FFE8(work->hzd, &work->floors[0]);
        HZD_DequeueDynamicFloor_8006FFE8(work->hzd, &work->floors[1]);
    }

    work->flaps[0].objs->flag = 0x257;
    Takabe_FreeObjs_800DC820(work->flaps[0].objs);

    work->flaps[1].objs->flag = 0x257;
    Takabe_FreeObjs_800DC820(work->flaps[1].objs);
}

int DummyFloorGetResources_800D68E4(DummyFloorWork *work, int name, int map)
{
    SVECTOR    pos;
    SVECTOR    dir;
    SVECTOR    bounds[5];
    DummyFlap *flaps;
    int        model;
    DummyFlap *flap;
    int        i, j;
    DG_MDL    *mdl;
    SVECTOR   *bound;
    int        xmax, xmin;
    int        zmax, zmin;

    GM_CurrentMap_800AB9B0 = map;

    THING_Gcl_GetSVector('p', &pos);
    THING_Gcl_GetSVector('d', &dir);

    work->raise = THING_Gcl_GetInt('r');
    work->f190 = THING_Gcl_GetIntDefault('t', 30);
    work->proc = THING_Gcl_GetInt('e');

    DG_SetPos2_8001BC8C(&pos, &dir);
    ReadRotMatrix(&work->world);

    flaps = &work->flaps[0];

    work->f1A0 = work->f19C = pos.vy;

    GCL_GetOption_80020968('m');

    model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    DummyFloor_800D6C94(work, &work->flaps[0], model, work->map);
    flaps[0].objs->light = work->light;

    model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    DummyFloor_800D6C94(work, &work->flaps[1], model, work->map);
    flaps[1].objs->light = work->light;

    ReadRotMatrix(&flaps[0].model);
    ReadRotMatrix(&flaps[0].objs->world);

    Takabe_ReshadeModel_800DC854(flaps[0].objs, Map_FromId_800314C0(map)->field_C_lit);

    flaps[1].pos.vx = flaps[0].f34.vx + flaps[1].f34.vx;

    DG_MovePos_8001BD20(&flaps[1].pos);

    ReadRotMatrix(&flaps[1].model);
    ReadRotMatrix(&flaps[1].objs->world);

    Takabe_ReshadeModel_800DC854(flaps[1].objs, Map_FromId_800314C0(map)->field_C_lit);

    work->f15C.vx = flaps[0].f34.vx;
    work->f15C.vz = flaps[0].f34.vz / 2;
    work->f15C.vy = 0;

    DG_SetPos_8001BC44(&flaps[0].model);
    DG_PutVector_8001BE48(&work->f15C, &work->f15C, 1);
    DG_SetPos2_8001BC8C(&work->f15C, &dir);
    ReadRotMatrix(&work->f164);

    for (i = 0; i < 2; i++)
    {
        flap = &work->flaps[i];
        mdl = flap->objs->def->model;
        bound = flap->bounds;

        xmax = mdl->max_8.vx;
        xmin = mdl->min_14.vx;

        zmax = mdl->max_8.vz;
        zmin = mdl->min_14.vz;

        for (j = 4; j > 0; j--)
        {
            if (j & 2)
            {
                bound->vx = xmax;
            }
            else
            {
                bound->vx = xmin;
            }

            bound->vy = 0;

            if ((j + 1) & 2)
            {
                bound->vz = zmax;
            }
            else
            {
                bound->vz = zmin;
            }

            bound++;
        }

        bound->vx = 0;
        bound->vy = 4096;
        bound->vz = 0;

        DG_SetPos_8001BC44(&flap->model);
        DG_PutVector_8001BE48(flap->bounds, bounds, 4);
        DG_RotVector_8001BE98(&dummy_floor_800C3618, &bounds[4], 1);

        work->hzd = Map_FromId_800314C0(map)->field_8_hzd;
        DummyFloor_800D6D38(bounds, &work->floors[i]);
        HZD_QueueDynamicFloor_8006FF9C(work->hzd, &work->floors[i]);

        flap++;
    }

    work->f1BC = 1;
    work->f184 = 0;
    work->f188 = -1;
    work->f1B8 = 0;
    work->f1A8 = 0;
    return 0;
}

GV_ACT * NewDummyFloor_800D6BF8(int name, int where)
{
    DummyFloorWork *work;

    work = (DummyFloorWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(DummyFloorWork));
    if (work != NULL)
    {
        work->name = name;
        work->map = where;

        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)DummyFloorAct_800D61A4, (TActorFunction)DummyFloorDie_800D61A4, "dummy_fl.c");

        if (DummyFloorGetResources_800D68E4(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void DummyFloor_800D6C94(DummyFloorWork *work, DummyFlap *flap, int model, int map)
{
    DG_MDL *mdl;

    flap->objs = s00a_unknown3_800DC7BC(model, 0);
    flap->objs->flag = 0x257;

    mdl = flap->objs->def->model;
    flap->f34.vx = mdl->min_14.vx - mdl->max_8.vx;
    flap->f34.vy = mdl->min_14.vy - mdl->max_8.vy;
    flap->f34.vz = mdl->min_14.vz - mdl->max_8.vz;

    flap->objs->objs[0].raise = work->raise;
}

void DummyFloor_800D6D38(SVECTOR *in, HZD_FLR *floor)
{
    int      xmax, ymax, zmax;
    int      xmin, ymin, zmin;
    int      x, y, z;
    SVECTOR *vec;
    HZD_VEC *bounds;
    int      i;

    zmax = -32000;
    ymax = -32000;
    xmax = -32000;

    zmin = 32000;
    ymin = 32000;
    xmin = 32000;

    vec = in;
    bounds = &floor->p1;

    for (i = 4; i > 0; i--)
    {
        x = vec->vx;

        if (x > xmax)
        {
            xmax = x;
        }

        if (x < xmin)
        {
            xmin = x;
        }

        bounds->x = x;

        y = vec->vy;

        if (y > ymax)
        {
            ymax = y;
        }

        if (y < ymin)
        {
            ymin = y;
        }

        bounds->y = y;

        z = vec->vz;

        if (z > zmax)
        {
            zmax = z;
        }

        if (z < zmin)
        {
            zmin = z;
        }

        bounds->z = z;

        vec++;
        bounds++;
    }

    floor->p1.h = in[4].vx >> 4;
    floor->p2.h = in[4].vz >> 4;
    floor->p3.h = in[4].vy >> 4;

    if (in[4].vy == 0)
    {
        floor->p3.h++;
    }

    floor->b1.z = zmin;
    floor->b2.z = zmax;
    floor->b1.x = xmin;
    floor->b2.x = xmax;
    floor->b1.y = ymin;
    floor->b2.y = ymax;
    floor->b1.h = 0;
}
