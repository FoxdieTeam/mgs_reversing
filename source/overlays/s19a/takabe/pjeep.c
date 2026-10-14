#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "takabe/thing.h"

extern void *NewPadVibration(unsigned char *table, int dir);

/* parked jeep (CHARA_PK_JEEP): the jeep Snake and Meryl escape in at the end of s19a */

typedef struct _Work
{
    GV_ACT   actor;
    GV_ACT  *snake;         // 0x20
    GV_ACT  *meryl;         // 0x24
    int      map;           // 0x28
    int      name;          // 0x2C
    CONTROL  control;       // 0x30
    OBJECT   body;          // 0xAC
    OBJECT   object2;       // 0x190
    OBJECT_NO_ROTS object3; // 0x274
    MATRIX   light[2];      // 0x298
    TARGET   target;        // 0x2D8
    OBJECT_NO_ROTS object4; // 0x320
    OBJECT_NO_ROTS object5; // 0x344
    MATRIX   light2[2];     // 0x368
    char     pad_3A8[0x1C8];
    int      field_570;     // 0x570
    int      field_574;     // 0x574
    int      field_578;     // 0x578
    char     pad_57C[0x4];
    int      field_580;     // 0x580
    int      field_584;     // 0x584
    char     pad_588[0x4];
    int      proc_c;        // 0x58C
    char     pad_590[0x4];
    int      proc_e;        // 0x594
    char     pad_598[0x4];
    HZD_HDL *hzd;           // 0x59C
    HZD_SEG  segs[8];       // 0x5A0
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

/* used by pkjp_sne.c and pkjp_mrl.c */
DG_OBJS *SECTION(".bss") PkJeep_800E0E10;
int      SECTION(".bss") PkJeep_800E0E14;
int      SECTION(".bss") PkJeep_800E0E18;
int      SECTION(".bss") PkJeep_800E0E1C;
int      SECTION(".bss") PkJeep_Flags;
int      SECTION(".bss") PkJeep_800E0E24;

unsigned short pjeep_messages[4] = {0xEA14, 0xDE32, 0xB4AC, 0x89CE};
u_char  pjeep_vib[8] = {0xDE, 0x02, 0x49, 0x05, 0x25, 0x07, 0x00, 0x00};
short   pjeep_382C[8] = {511, 1719, 2960, 2396, 1093, 1058, 0, 0};
SVECTOR pjeep_383C = {0, 1435, -925};
SVECTOR pjeep_3844[2] = {{330, 890, 1436}, {-330, 890, 1436}};
SVECTOR pjeep_target_size = {730, 880, 730};
SVECTOR pjeep_walls[4] = {{750, 0, 1500}, {-750, 0, 1500}, {-750, 0, -1500}, {750, 0, -1500}};
SVECTOR pjeep_push_pos[2] = {{0, 900, 600}, {0, 900, -600}};
SVECTOR pjeep_push_force = {0, 0, 0};

void PkJeepExecProc(int proc, int value)
{
    GCL_ARGS args;
    long     data = value;

    if (proc == 0) return;

    args.argc = 1;
    args.argv = &data;
    GCL_ExecProc(proc, &args);
}

/* jump table of the Act switch (Act is still asm) */
const int pjeep_act_jtbl[5] = {0x800D8F7C, 0x800D8FB8, 0x800D9068, 0x800D910C, 0x800D92D8};

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D8E8C.s")
void s19a_800D8E8C(Work *work); /* Act */

void PkJeepDie(Work *work)
{
    int i;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->object2);
    GM_FreeObject((OBJECT *)&work->object3);
    GM_FreeObject((OBJECT *)&work->object4);
    GM_FreeObject((OBJECT *)&work->object5);

    if (work->snake)
    {
        GV_DestroyActor(work->snake);
    }

    if (work->meryl)
    {
        GV_DestroyActor(work->meryl);
    }

    GM_PlayerStatus &= ~PLAYER_INVINCIBLE;

    for (i = 0; i < 8; i++)
    {
        HZD_DequeueDynamicSegment(work->hzd, &work->segs[i]);
    }
}

static void InitTarget(Work *work)
{
    TARGET *target;

    target = &work->target;
    GM_SetTarget(target, TARGET_POWER, PLAYER_SIDE, &pjeep_target_size);
    GM_SetPowerTarget(target, TARGET_POWER, 2, 256, 0, &DG_ZeroVector);
}

static void InitSegs(Work *work);

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    HZD_SEG *seg;
    OBJECT  *body;
    OBJECT  *object2;
    OBJECT_NO_ROTS *obj;
    int      i;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    work->proc_e = THING_Gcl_GetInt('e');

    body = &work->body;
    object2 = &work->object2;
    GM_InitObject(body, 0x26C7, 0x6D, 0);
    GM_InitObject(object2, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(object2);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectLight(object2, work->light);

    GM_InitObjectNoRots(&work->object3, 0x3FA9, 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)&work->object3, work->light);
    PkJeep_800E0E10 = work->object3.objs;

    obj = &work->object4;
    GM_InitObjectNoRots(obj, 0x7607, 0x16D, 0);
    obj->objs->root = &work->body.objs->world;
    GM_ConfigObjectLight((OBJECT *)obj, work->light2);

    obj = &work->object5;
    GM_InitObjectNoRots(obj, 0xDA10, 0x16D, 0);
    obj->objs->root = &work->body.objs->world;
    GM_ConfigObjectLight((OBJECT *)obj, work->light2);
    obj->objs->flag |= DG_FLAG_INVISIBLE;

    work->light2[0].t[0] = 0;
    work->light2[0].t[1] = 0;
    work->light2[0].t[2] = 0;

    InitTarget(work);

    work->hzd = GM_GetMap(where)->hzd;
    work->body.objs->world = DG_ZeroMatrix;

    InitSegs(work);

    seg = work->segs;
    for (i = 4; i > 0; i--)
    {
        HZD_QueueDynamicSegment2(work->hzd, seg++, 0x100);
    }

    for (i = 4; i > 0; i--)
    {
        HZD_QueueDynamicSegment2(work->hzd, seg++, 0x45);
    }

    work->proc_c = THING_Gcl_GetInt('c');
    work->map = where;
    work->name = name;
    work->field_570 = 0;
    work->field_574 = 0;
    work->field_578 = 0;
    work->field_580 = control->rot.vy;
    PkJeep_800E0E1C = 0;
    work->field_584 = 0;
    PkJeep_800E0E18 = 0;
    return 0;
}

void *NewPkJeep(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s19a_800D8E8C, PkJeepDie, "pjeep.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

/* moves pos by len in the direction *dir, then turns *dir by angle */
void s19a_800D9BBC(SVECTOR *pos, short *dir, int angle, short len)
{
    SVECTOR move2;
    SVECTOR move;
    SVECTOR front = {0, 0, 2250};
    SVECTOR ofs;
    MATRIX  world;
    long    flag;

    ofs = DG_ZeroVector;
    ofs.vz = len;

    world = DG_ZeroMatrix;
    RotMatrixY(*dir, &world);
    SetRotMatrix(&world);
    SetTransMatrix(&world);
    RotTransSV(&front, &front, &flag);
    RotTransSV(&ofs, &move, &flag);
    GV_AddVec3(pos, &move, pos);

    world = DG_ZeroMatrix;
    RotMatrixY(angle, &world);
    SetRotMatrix(&world);
    RotTransSV(&ofs, &move2, &flag);
    GV_AddVec3(&front, &move2, &move2);
    GV_SubVec3(&move2, &move, &front);

    *dir = ratan2(front.vx, front.vz);
}

static void InitSegs(Work *work)
{
    HZD_SEG *seg;
    MATRIX  *world;
    int      i;

    seg = work->segs;
    world = &work->body.objs->world;

    for (i = 0; i < 4; i++)
    {
        pjeep_walls[i].vy = 0;
        pjeep_walls[(i + 1) & 3].vy = 1000;
        THING_Hzd_800C45C4(seg++, world, &pjeep_walls[i], &pjeep_walls[(i + 1) & 3]);
    }

    for (i = 0; i < 4; i++)
    {
        pjeep_walls[i].vy = 1000;
        pjeep_walls[(i + 1) & 3].vy = 2000;
        THING_Hzd_800C45C4(seg++, world, &pjeep_walls[i], &pjeep_walls[(i + 1) & 3]);
    }
}

/* pushes whatever is in front of (or behind) the jeep */
void s19a_800D9E98(Work *work, int speed)
{
    CONTROL *control;
    TARGET  *target;
    int      back;
    int      hit;

    back = 0;
    control = &work->control;
    if (speed <= 0)
    {
        back = 1;
        speed = -speed;
    }

    target = &work->target;
    GM_SetPowerTarget(target, POWER_DECREASE, 2, 256, 0, &DG_ZeroVector);

    DG_SetPos2(&control->mov, &control->rot);
    DG_PutVector(&pjeep_push_pos[back], &target->center, 1);

    pjeep_push_force.vz = speed / 2;
    DG_RotVector(&pjeep_push_force, &target->force, 1);

    hit = GM_PowerTarget(target);
    work->target.vital = 256;
    work->target.damaged &= ~TARGET_POWER;

    if (hit)
    {
        GM_SeSetMode(&target->center, 0x25, GM_SEMODE_BOMB);
        NewPadVibration(pjeep_vib, 2);
    }
}

int s19a_800D9FA8(void)
{
    CONTROL **where;
    int       found;
    int       n;

    found = 0;
    where = GM_WhereList;

    for (n = GM_N_WhereList; n > 0; n--, where++)
    {
        if ((*where)->name == 0x95F2)
        {
            found = 1;
        }

        if ((*where)->name == 0x3D2C)
        {
            found = 1;
        }
    }

    return found;
}
