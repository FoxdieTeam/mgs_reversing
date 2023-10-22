#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct _ElevatorWork
{
    GV_ACT      actor;
    int         map;
    int         name;
    CONTROL     control;
    OBJECT      object1;
    SVECTOR     rots1[24];
    OBJECT      object2;
    SVECTOR     rots2[24];
    MATRIX      light[2];
    HZD_HEADER *hzm;
    HZD_HEADER *hzm1;
    HZD_HEADER *hzm2;
    HZD_HEADER *hzm3;
    HZD_HEADER *hzm4;
    HZD_AREA   *areas;
    HZD_AREA   *areas1;
    HZD_AREA   *areas2;
    HZD_AREA   *areas3;
    HZD_AREA   *areas4;
    HZD_HDL    *hzd;
    int         n_floors;
    int         n_walls;
    HZD_FLR     floors[8];
    HZD_SEG     walls[16];
    SVECTOR     f560;
    SVECTOR     f568;
    SVECTOR     f570;
    SVECTOR     f578;
    int         f580;
    int         f584;
    int         f588;
    int         f58C;
    int         f590;
    int         f594;
    int         f598;
    int         f59C;
    int         f5A0;
    int         f5A4;
    int         f5A8;
    int         f5AC;
    int         f5B0;
    short       f5B4;
    short       f5B6;
    short       f5B8;
    short       f5BA;
    int         f5BC;
    int         f5C0;
    int         f5C4;
    int         f5C8;
    int         f5CC;
    int         f5D0;
} ElevatorWork;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

extern const char aElevatorC[]; // = "elevator.c"

int THING_Gcl_GetInt(int);
int THING_Gcl_GetIntDefault(int, int);
int THING_Gcl_GetSVector(int, SVECTOR *);
int s16b_800C440C(int);

DG_OBJS * s00a_mosaic_800DC7DC(int, LitHeader *);
void      s00a_mosaic_800DC820(DG_OBJS *);

#define EXEC_LEVEL 5

#pragma INCLUDE_ASM("asm/overlays/s00a/ElevatorAct_800D8EA8.s")
void ElevatorAct_800D8EA8(ElevatorWork *work);

void Elevator_800D9FC4(ElevatorWork *, SVECTOR *);
void Elevator_800DA534(HZD_VEC *, SVECTOR *, HZD_VEC *);
void Elevator_800DA140(ElevatorWork *);
void Elevator_800DA1F0(ElevatorWork *);
void Elevator_800DA358(ElevatorWork *, HZD_AREA *);
void Elevator_800DA4CC(OBJECT *, int, int);
void Elevator_800DA268(ElevatorWork *);
void Elevator_800DA2E0(ElevatorWork *);
void Elevator_800DA3F8(ElevatorWork *, HZD_AREA *);

void ElevatorDie_800D97D8(ElevatorWork *work)
{
    Elevator_800DA2E0(work);
    Elevator_800DA268(work);

    GM_FreeControl_800260CC(&work->control);

    if (work->f58C & 0x1)
    {
        s00a_mosaic_800DC820(work->object1.objs);

        if (work->f58C & 0x8)
        {
            s00a_mosaic_800DC820(work->object2.objs);
        }
    }
    else
    {
        GM_FreeObject_80034BF8(&work->object1);

        if (work->f58C & 0x8)
        {
            GM_FreeObject_80034BF8(&work->object2);
        }
    }

    Elevator_800DA3F8(work, work->areas1);
    Elevator_800DA3F8(work, work->areas2);
    Elevator_800DA3F8(work, work->areas3);
    Elevator_800DA3F8(work, work->areas4);
}

int ElevatorGetResources_800D98A8(ElevatorWork *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *object1;
    OBJECT  *object2;
    int      model1, model2;
    MATRIX  *light;
    int      filename;
    int      f584;

    GM_SetCurrentMap(where);

    work->map = where;
    work->name = name;

    work->f58C = 0;
    work->hzd = Map_FromId_800314C0(work->map)->field_8_hzd;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, name, where) < 0)
    {
error:
        return -1;
    }

    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);

    object1 = &work->object1;
    object2 = &work->object2;

    model2 = s16b_800C440C('f') & 0xFFFF;
    model1 = s16b_800C440C('m') & 0xFFFF;

    if (model1 != 0)
    {
        GM_InitObject_80034A18(object1, model1, 0x5D, 0);

        light = work->light;
        GM_ConfigObjectLight_80034C44(object1, light);

        if (model2 != 0)
        {
            GM_InitObject_80034A18(object2, model2, 0x5D, 0);
            GM_ConfigObjectLight_80034C44(object2, light);
            work->f58C |= 0x8;
        }
    }
    else
    {
        model1 = s16b_800C440C('n') & 0xFFFF;
        if (model1 == 0)
        {
            goto error;
        }

        Elevator_800DA4CC(object1, model1, 0x57);

        if (model2 != 0)
        {
            Elevator_800DA4CC(object2, model2, 0x57);
            work->f58C |= 0x8;
        }

        work->f58C |= 0x1;
    }

    THING_Gcl_GetSVector('s', &work->f560);
    THING_Gcl_GetSVector('e', &work->f568);
    GV_SubVec3_80016D40(&work->f568, &work->f560, &work->f568);

    work->f580 = THING_Gcl_GetIntDefault('c', 300);
    work->f5C8 = s16b_800C440C('o') & 0xFFFF;
    work->f5CC = s16b_800C440C('u') & 0xFFFF;
    work->f5D0 = THING_Gcl_GetInt('p');
    work->f5B0 = THING_Gcl_GetInt('x');

    work->f5B6 = 184;
    work->f5B8 = 185;
    work->f5BA = 186;
    work->f5B4 = 8;
    work->f5BC = 2000;

    if (GCL_GetOption_80020968('X'))
    {
        work->f5B6 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f5B8 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f5BA = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f5B4 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f5BC = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    filename = s16b_800C440C('h') & 0xFFFF;
    if (filename != 0)
    {
        work->hzm = GV_GetCache_8001538C(GV_CacheID_800152DC(filename, 'h'));
        work->areas = work->hzm->areas;

        work->n_floors = work->areas->n_altimetry;
        if (work->n_floors > 8)
        {
            work->n_floors = 8;
        }

        work->n_walls = work->areas->n_walls;
        if (work->n_walls > 16)
        {
            work->n_walls = 16;
        }

        work->f58C |= 0x2;
    }

    if (GCL_GetOption_80020968('z'))
    {
        work->f58C |= 0x10;

        filename = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->hzm3 = GV_GetCache_8001538C(GV_CacheID_800152DC(filename, 'h'));

        filename = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->hzm4 = GV_GetCache_8001538C(GV_CacheID_800152DC(filename, 'h'));

        filename = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->hzm1 = GV_GetCache_8001538C(GV_CacheID_800152DC(filename, 'h'));

        filename = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->hzm2 = GV_GetCache_8001538C(GV_CacheID_800152DC(filename, 'h'));

        work->areas3 = work->hzm3->areas;
        work->areas4 = work->hzm4->areas;
        work->areas1 = work->hzm1->areas;
        work->areas2 = work->hzm2->areas;

        Elevator_800DA358(work, work->areas3);
        Elevator_800DA358(work, work->areas1);
    }

    Elevator_800D9FC4(work, &DG_ZeroVector_800AB39C);
    Elevator_800DA1F0(work);
    Elevator_800DA140(work);

    work->f584 = 0;
    work->f5C0 = 3;
    work->f590 = 0;

    work->f58C |= 0x20;

    if (GCL_GetOption_80020968('i'))
    {
        f584 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        if (f584 >= 0)
        {
            work->f5C0 = 1;
        }
        else
        {
            f584 = -f584;
        }

        work->f584 = f584;
    }

    if (GCL_GetOption_80020968('w'))
    {
        work->f594 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f58C |= 0x4;
    }

    if (GCL_GetOption_80020968('a') && GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()) == 0)
    {
        work->f58C &= ~0x20;
    }

    work->f578.vx = (work->f568.vx * work->f584) / work->f580;
    work->f578.vy = (work->f568.vy * work->f584) / work->f580;
    work->f578.vz = (work->f568.vz * work->f584) / work->f580;

    if (work->f58C & 0x8)
    {
        work->f5A0 = 24;
        work->f5A4 = 40;
    }
    else
    {
        work->f5A0 = 1;
        work->f5A4 = 1;
    }

    work->f59C = 0;
    work->f598 = work->f5A0;

    if (work->f5C0 == 3)
    {
        if (work->f584 == 0)
        {
            work->f5AC = -1500;
            work->f598 = 0;
            work->f5A8 = 1;
        }
        else
        {
            work->f5AC = 0;
            work->f5A8 = 0;
        }
    }

    if (work->f5C0 == 1)
    {
        if (work->f584 == work->f580)
        {
            work->f598 = 0;
            work->f5AC = -1500;
            work->f5A8 = 1;
        }
        else
        {
            work->f5AC = 0;
            work->f5A8 = 0;
        }
    }

    work->f588 = 0x8000;
    control->field_0_mov = work->f570;

    return 0;
}

GV_ACT * NewElevator_800D9F30(int name, int where)
{
    ElevatorWork *work;

    work = (ElevatorWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ElevatorWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ElevatorAct_800D8EA8, (TActorFunction)ElevatorDie_800D97D8, aElevatorC);

        if (ElevatorGetResources_800D98A8(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void Elevator_800D9FC4(ElevatorWork *work, SVECTOR *offset)
{
    HZD_AREA *areas;
    HZD_FLR  *floor;
    HZD_FLR  *flooro;
    int       i;
    HZD_SEG  *wall;
    HZD_SEG  *wallo;

    if (!(work->f58C & 0x2))
    {
        return;
    }

    areas = work->areas;

    floor = areas->altimetry;
    flooro = work->floors;

    for (i = 0; i < work->n_floors; i++)
    {
        Elevator_800DA534(&floor->b1, offset, &flooro->b1);
        Elevator_800DA534(&floor->b2, offset, &flooro->b2);
        Elevator_800DA534(&floor->p1, offset, &flooro->p1);
        Elevator_800DA534(&floor->p2, offset, &flooro->p2);
        Elevator_800DA534(&floor->p3, offset, &flooro->p3);
        Elevator_800DA534(&floor->p4, offset, &flooro->p4);

        flooro->b1.h = floor->b1.h;
        flooro->p1.h = floor->p1.h;
        flooro->p2.h = floor->p2.h;
        flooro->p3.h = floor->p3.h;

        flooro++;
        floor++;
    }

    wall = areas->walls;
    wallo = work->walls;

    for (i = 0; i < work->n_walls; i++)
    {
        Elevator_800DA534(&wall->p1, offset, &wallo->p1);
        Elevator_800DA534(&wall->p2, offset, &wallo->p2);

        wallo++;
        wall++;
    }
}

void Elevator_800DA140(ElevatorWork *work)
{
    HZD_SEG *wall;
    char    *flags_lo;
    char    *flags_hi;
    int      i;

    if (!(work->f58C & 0x2))
    {
        return;
    }

    wall = work->walls;
    flags_lo = work->areas->wallsFlags;
    flags_hi = flags_lo + work->areas->n_walls;

    for (i = 0; i < work->n_walls; i++)
    {
        HZD_QueueDynamicSegment2_8006FDDC(work->hzd, wall, *flags_lo | (*flags_hi << 8));
        wall++;
        flags_lo++;
        flags_hi++;
    }
}

void Elevator_800DA1F0(ElevatorWork *work)
{
    HZD_FLR *floor;
    int      i;

    if (!(work->f58C & 0x2))
    {
        return;
    }

    floor = work->floors;
    for (i = 0; i < work->n_floors; i++)
    {
        HZD_QueueDynamicFloor_8006FF9C(work->hzd, floor);
        floor++;
    }
}

void Elevator_800DA268(ElevatorWork *work)
{
    HZD_SEG *wall;
    int      i;

    if (!(work->f58C & 0x2))
    {
        return;
    }

    wall = work->walls;
    for (i = 0; i < work->n_walls; i++)
    {
        HZD_DequeueDynamicSegment2_8006FE44(work->hzd, wall);
        wall++;
    }
}

void Elevator_800DA2E0(ElevatorWork *work)
{
    HZD_FLR *floor;
    int      i;

    if (!(work->f58C & 0x2))
    {
        return;
    }

    floor = work->floors;
    for (i = 0; i < work->n_floors; i++)
    {
        HZD_DequeueDynamicFloor_8006FFE8(work->hzd, floor);
        floor++;
    }
}

void Elevator_800DA358(ElevatorWork *work, HZD_AREA *area)
{
    HZD_SEG *wall;
    char    *flags_lo;
    char    *flags_hi;
    int      i;

    if (!(work->f58C & 0x10))
    {
        return;
    }

    wall = area->walls;
    flags_lo = area->wallsFlags;
    flags_hi = flags_lo + area->n_walls;

    for (i = area->n_walls; i > 0; i--)
    {
        HZD_QueueDynamicSegment2_8006FDDC(work->hzd, wall, *flags_lo | (*flags_hi << 8));
        wall++;
        flags_lo++;
        flags_hi++;
    }
}

void Elevator_800DA3F8(ElevatorWork *work, HZD_AREA *area)
{
    HZD_SEG *wall;
    int      i;

    if (!(work->f58C & 0x10))
    {
        return;
    }

    wall = area->walls;
    for (i = area->n_walls; i > 0; i--)
    {
        HZD_DequeueDynamicSegment2_8006FE44(work->hzd, wall);
        wall++;
    }
}

int Elevator_800DA464(ElevatorWork *work, void *ptr)
{
    HZD_SEG *wall;
    int      i;
    HZD_FLR *floor;

    if ((int)ptr & 0x80000000)
    {
        wall = work->walls;
        for (i = work->n_walls; i > 0; i--)
        {
            if (wall == ptr)
            {
                return 1;
            }

            wall++;
        }
    }
    else
    {
        ptr = (HZD_FLR *)((int)ptr | 0x80000000);

        floor = work->floors;
        for (i = work->n_floors; i > 0; i--)
        {
            if (floor == ptr)
            {
                return 1;
            }

            floor++;
        }
    }

    return 0;
}

void Elevator_800DA4CC(OBJECT *object, int model, int flag)
{
    GV_ZeroMemory_8001619C(object, sizeof(*object) + sizeof(SVECTOR) * 24);

    object->flag = flag;
    object->map_name = GM_CurrentMap_800AB9B0;
    object->objs = s00a_mosaic_800DC7DC(model, Map_FromId_800314C0(GM_CurrentMap_800AB9B0)->field_C_lit);
}

void Elevator_800DA534(HZD_VEC *in, SVECTOR *addend, HZD_VEC *out)
{
    out->x = in->x + addend->vx;
    out->y = in->y + addend->vy;
    out->z = in->z + addend->vz;
    out->h = in->h;
}

// This isn't called by any reversed code yet.
// It might be part of wt_area.c if it's not used in ElevatorAct.
void Elevator_800DA57C(int proc, long arg)
{
    GCL_ARGS args;
    long     val;

    val = arg;
    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &val;
        GCL_ExecProc_8001FF2C(proc, &args);
    }
}
