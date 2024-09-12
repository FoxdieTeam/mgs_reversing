#include "dummy_fl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/vibrate.h"
#include "Takabe/thing.h"

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

typedef struct DummyFloorScratch
{
    MATRIX  mat;
    SVECTOR vec;
} Scratch;

char dummy_floor_800C3610[] = {0x7F, 0x01, 0x00, 0x00};
char dummy_floor_800C3614[] = {0x50, 0x04, 0x00, 0x00};

SVECTOR dummy_floor_800C3618 = {0, 4096, 0, 0};

extern SVECTOR  DG_ZeroVector;
extern int      GM_GameStatus;
extern int      GM_GameOverTimer;
extern int      GM_CurrentMap_800AB9B0;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern int      dword_800ABA1C;
extern CONTROL *tenage_ctrls_800BDD30[16];
extern int      tenage_ctrls_count_800BDD70;

void Takabe_FreeObjs_800DC820(DG_OBJS *objs);
void Takabe_ReshadeModel_800DC854(DG_OBJS *, LitHeader *);
void Takabe_RefreshObjectPacks_800DC854(DG_OBJS *);

DG_OBJS *s00a_unknown3_800DC7BC(int model, LitHeader *lit);

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
void s16b_800C4874(int arg0, HZD_SEG *arg1, int arg2, HZD_FLR *arg3);

void DummyFloor_800D6C94(DummyFloorWork *work, DummyFlap *flap, int model, int map);
void DummyFloor_800D6D38(SVECTOR *in, HZD_FLR *floor);

#define EXEC_LEVEL 5

void DummyFloorAct_800D61A4(DummyFloorWork *work)
{
    VECTOR     sp10;
    Scratch   *scratch;
    CONTROL  **iter;
    int        count;
    int        i;
    DummyFlap *flap;

    GM_CurrentMap_800AB9B0 = work->map;

    s01a_800E2364(&work->f164, &GM_PlayerControl_800AB9F4->mov, &sp10);

    sp10.vx = ABS(sp10.vx);
    sp10.vy = ABS(sp10.vy);
    sp10.vz = ABS(sp10.vz);

    if ((sp10.vx < (work->flaps[0].f34.vx - 100)) &&
        (sp10.vz < (work->flaps[0].f34.vz / 2)))
    {
        if (work->f1BC != 0)
        {
            work->f188 = 0;
            work->f1A8 = 0;
            work->f1BC = 0;
            work->f194 = 1;
            work->f184 = work->f190;

            GM_SeSet(&work->f15C, 187);

            NewPadVibration_8005D58C(dummy_floor_800C3610, 1);
            NewPadVibration_8005D58C(dummy_floor_800C3614, 2);
        }

        work->f198 = 1;
    }
    else
    {
        if (work->f1B0 != 0)
        {
            work->f1B0--;
        }
        else if ((work->f1BC == 0) && (work->f194 == 0))
        {
            work->f188 = 1;
            work->f184 = 0;
            work->f1A4 = 2;
            work->f1BC = 1;
        }

        work->f198 = 0;
    }

    if (work->f194 != 0)
    {
        work->f184--;
    }

    switch (work->f188)
    {
    case 0:
        if ((work->f184 < 0) && (GM_GameOverTimer == 0))
        {
            GM_SeSet(&work->f15C, 186);

            if (GM_GameOverTimer == 0)
            {
                if (work->f198 == 1)
                {
                    GM_UnkFlagA0++;
                    dword_800ABA1C = 1;

                    if (work->proc != 0)
                    {
                        GCL_ExecProc(work->proc, NULL);
                    }

                    GM_GameOver();
                }

                work->f188 = 2;
                work->f1A4 = 1;
                work->f1B0 = 40;
            }

            s16b_800C4874(0, NULL, 2, work->floors);

            scratch = (Scratch *)0x1F800000;

            scratch->mat = work->f164;
            DG_TransposeMatrix(&scratch->mat, &scratch->mat);
            DG_SetPos(&scratch->mat);

            if (tenage_ctrls_count_800BDD70 != 0)
            {
                iter = tenage_ctrls_800BDD30;
                for (count = 16; count > 0; count--)
                {
                    *iter = NULL;

                    scratch->vec = *(SVECTOR *)0x00000000;
                    scratch->vec.vx -= scratch->mat.t[0];
                    scratch->vec.vy -= scratch->mat.t[1];
                    scratch->vec.vz -= scratch->mat.t[2];

                    DG_RotVector(&scratch->vec, &scratch->vec, 1);

                    scratch->vec.vx = ABS(scratch->vec.vx);
                    scratch->vec.vy = ABS(scratch->vec.vy);
                    scratch->vec.vz = ABS(scratch->vec.vz);

                    if ((scratch->vec.vx < work->flaps[0].f34.vx) &&
                        (scratch->vec.vz < work->flaps[0].f34.vz / 2) &&
                        (scratch->vec.vy < 150))
                    {
                        (*iter)->mov.pad = 1;
                    }

                    iter++;
                }
            }

            work->f194 = 0;
        }

        work->f1A0 = work->f19C - 100;
        break;

    case 1:
        work->f1A0 = GV_NearSpeed(work->f1A0, work->f19C, 32);
        break;

    case 2:
        if ((GM_GameOverTimer == 0) && (work->f198 == 1))
        {
            work->f1A4 = 1;
            GM_UnkFlagA0++;
            dword_800ABA1C = 1;

            if (work->proc != 0)
            {
                GCL_ExecProc(work->proc, NULL);
            }

            if (work->name == 0x5862)
            {
                work->proc = 0;
            }
            else
            {
                GM_GameOver();
            }
        }
        break;
    }

    switch (work->f1A4)
    {
    case 0:
        break;

    case 1:
        work->f1A8 += (rcos(work->f1AC) * 40) / 4096;
        work->f1AC += work->f1A8;

        if (work->f1AC > 1024)
        {
            work->f1AC = 2048 - work->f1AC;
            work->f1A8 = -work->f1A8 / 4;
        }

        work->flaps[0].rot.vz = -work->f1AC;
        work->flaps[1].rot.vz = work->f1AC;
        break;

    case 2:
        work->f1AC = GV_NearExp8(work->f1AC, 0);
        if (work->f1AC < 8)
        {
            work->f1AC = 0;
            work->f1A4 = 0;
            GM_SeSet(&work->f15C, 188);
        }

        work->flaps[0].rot.vz = -work->f1AC;
        work->flaps[1].rot.vz = work->f1AC;
        break;
    }

    work->world.t[1] = work->f1A0;

    for (i = 0; i < 2; i++)
    {
        flap = &work->flaps[i];
        DG_SetPos2(&flap->pos, &flap->rot);
        ReadRotMatrix(&flap->model);
        CompMatrix(&work->world, &flap->model, &flap->objs->world);
    }

    if (GM_GameStatus & STATE_THERMG)
    {
        if (work->f1B8 == 0)
        {
            work->flaps[0].objs->flag = 0x35D;
            work->flaps[1].objs->flag = 0x35D;
            work->flaps[0].objs->light = work->light;
            work->flaps[1].objs->light = work->light;
            DG_GetLightMatrix2(&DG_ZeroVector, work->light);
            work->f1B8 = 1;
        }
    }
    else if (work->f1B8 != 0)
    {
        work->flaps[0].objs->flag = 0x257;
        work->flaps[1].objs->flag = 0x257;
        Takabe_RefreshObjectPacks_800DC854(work->flaps[0].objs);
        Takabe_RefreshObjectPacks_800DC854(work->flaps[1].objs);
        work->f1B8 = 0;
    }
}

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

    DG_SetPos2(&pos, &dir);
    ReadRotMatrix(&work->world);

    flaps = &work->flaps[0];

    work->f1A0 = work->f19C = pos.vy;

    GCL_GetOption('m');

    model = GCL_StrToInt(GCL_GetParamResult());
    DummyFloor_800D6C94(work, &work->flaps[0], model, work->map);
    flaps[0].objs->light = work->light;

    model = GCL_StrToInt(GCL_GetParamResult());
    DummyFloor_800D6C94(work, &work->flaps[1], model, work->map);
    flaps[1].objs->light = work->light;

    ReadRotMatrix(&flaps[0].model);
    ReadRotMatrix(&flaps[0].objs->world);

    Takabe_ReshadeModel_800DC854(flaps[0].objs, Map_FromId_800314C0(map)->lit);

    flaps[1].pos.vx = flaps[0].f34.vx + flaps[1].f34.vx;

    DG_MovePos(&flaps[1].pos);

    ReadRotMatrix(&flaps[1].model);
    ReadRotMatrix(&flaps[1].objs->world);

    Takabe_ReshadeModel_800DC854(flaps[1].objs, Map_FromId_800314C0(map)->lit);

    work->f15C.vx = flaps[0].f34.vx;
    work->f15C.vz = flaps[0].f34.vz / 2;
    work->f15C.vy = 0;

    DG_SetPos(&flaps[0].model);
    DG_PutVector(&work->f15C, &work->f15C, 1);
    DG_SetPos2(&work->f15C, &dir);
    ReadRotMatrix(&work->f164);

    for (i = 0; i < 2; i++)
    {
        flap = &work->flaps[i];
        mdl = flap->objs->def->model;
        bound = flap->bounds;

        xmax = mdl->min.vx;
        xmin = mdl->max.vx;

        zmax = mdl->min.vz;
        zmin = mdl->max.vz;

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

        DG_SetPos(&flap->model);
        DG_PutVector(flap->bounds, bounds, 4);
        DG_RotVector(&dummy_floor_800C3618, &bounds[4], 1);

        work->hzd = Map_FromId_800314C0(map)->hzd;
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

GV_ACT *NewDummyFloor_800D6BF8(int name, int where, int argc, char **argv)
{
    DummyFloorWork *work;

    work = (DummyFloorWork *)GV_NewActor(EXEC_LEVEL, sizeof(DummyFloorWork));
    if (work != NULL)
    {
        work->name = name;
        work->map = where;

        GV_SetNamedActor(&work->actor, (TActorFunction)DummyFloorAct_800D61A4,
                         (TActorFunction)DummyFloorDie_800D61A4, "dummy_fl.c");

        if (DummyFloorGetResources_800D68E4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
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
    flap->f34.vx = mdl->max.vx - mdl->min.vx;
    flap->f34.vy = mdl->max.vy - mdl->min.vy;
    flap->f34.vz = mdl->max.vz - mdl->min.vz;

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
