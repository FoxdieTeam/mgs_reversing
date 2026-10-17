#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "takabe/thing.h"

/* parking lot gate (CHARA_PK_GATE): opens when it is shot */

typedef struct _Work
{
    GV_ACT   actor;
    int      map;       // 0x20
    OBJECT   object;    // 0x24
    TARGET  *target;    // 0x108
    HZD_HDL *hzd;       // 0x10C
    HZD_SEG  seg;       // 0x110
    int      opened;    // 0x120
    int      shaded;    // 0x124
} Work;

#define OBJECT_FLAG ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

void      Takabe_FreeObjs(DG_OBJS *objs);
void      Takabe_ReshadeModel(DG_OBJS *objs, DG_LITS *lit);
DG_OBJS * Takabe_MakeElevatorPreshade(int model, DG_LITS *lit);

SVECTOR pk_gate_target_size = {2500, 2000, 500};
SVECTOR pk_gate_target_pos = {-500, 2000, -5000};

SVECTOR pk_gate_wall_p1 = {-3500, 0, -5000};
SVECTOR pk_gate_wall_p2 = {1500, 4000, -5000};

static void InitObject(OBJECT *object, int model, int flag);

static void Act(Work *work)
{
    TARGET *target;
    OBJECT *object;

    GM_CurrentMap = work->map;

    if (!work->shaded)
    {
        Takabe_ReshadeModel(work->object.objs, GM_GetMap(GM_CurrentMap)->lit);
        work->shaded = 1;
    }

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        if (target->a_mode == 2 && !work->opened)
        {
            work->opened = 1;

            object = &work->object;
            Takabe_FreeObjs(object->objs);
            InitObject(object, GV_StrCode("19a_o1b"), OBJECT_FLAG);
            Takabe_ReshadeModel(object->objs, GM_GetMap(GM_CurrentMap)->lit);

            work->target->side = BOTH_SIDE;
            work->seg.p1.x = 500;
        }
    }

    DG_SetPos(&DG_ZeroMatrix);
    GM_ActObject2(&work->object);
}

static void Die(Work *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
    Takabe_FreeObjs(work->object.objs);
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, ENEMY_SIDE, &pk_gate_target_size);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, 3, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &pk_gate_target_pos);
}

static int GetResources(Work *work, int name, int where)
{
    OBJECT  *object;
    HZD_SEG *seg;

    object = &work->object;
    GM_CurrentMap = where;
    work->map = where;

    InitObject(object, GV_StrCode("19a_o1a"), OBJECT_FLAG);

    seg = &work->seg;
    THING_Hzd_800C45C4(seg, NULL, &pk_gate_wall_p1, &pk_gate_wall_p2);
    work->hzd = GM_GetMap(where)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, seg, 0x200);

    InitTarget(work);

    work->shaded = 0;
    work->opened = 0;
    return 0;
}

void *NewParkingGate(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "pk_gate.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}

static void InitObject(OBJECT *object, int model, int flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap;
    object->objs = Takabe_MakeElevatorPreshade(model, GM_GetMap(GM_CurrentMap)->lit);
}
