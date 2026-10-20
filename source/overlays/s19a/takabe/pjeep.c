#include "mgstype.h"
#include "strcode.h"
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
    GV_ACT  *meryl;         // 0x20
    GV_ACT  *snake;         // 0x24
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
    int      time;          // 0x570
    int      state;         // 0x574
    int      speed;         // 0x578
    int      accel;         // 0x57C
    int      dir;           // 0x580
    int      field_584;     // 0x584
    int      ready;         // 0x588: Snake is in the jeep
    int      proc_c;        // 0x58C
    int      voice_timer;   // 0x590
    int      proc_e;        // 0x594
    int      voice_index;   // 0x598
    HZD_HDL *hzd;           // 0x59C
    HZD_SEG  segs[8];       // 0x5A0
} Work;

/* used by pkjp_sne.c and pkjp_mrl.c */
DG_OBJS *SECTION(".bss") PkJeep_800E0E10;
int      SECTION(".bss") PkJeep_800E0E14;
int      SECTION(".bss") PkJeep_800E0E18;
int      SECTION(".bss") PkJeep_800E0E1C;
int      SECTION(".bss") PkJeep_Flags;
int      SECTION(".bss") PkJeep_800E0E24;

unsigned short pjeep_messages[4] = {0xEA14, 0xDE32, 0xB4AC, 0x89CE};
u_char  pjeep_vib[8] = {0xDE, 0x02, 0x49, 0x05, 0x25, 0x07, 0x00, 0x00};
u_char  pjeep_382C[16] = {0xFF, 0x01, 0xB7, 0x06, 0x90, 0x0B, 0x5C, 0x09, 0x45, 0x04, 0x22, 0x04, 0x00, 0x00, 0x00, 0x00};
SVECTOR pjeep_383C = {0, 1435, -925};
SVECTOR pjeep_3844[2] = {{330, 890, 1436}, {-330, 890, 1436}};
SVECTOR pjeep_target_size = {730, 880, 730};
SVECTOR pjeep_walls[4] = {{750, 0, 1500}, {-750, 0, 1500}, {-750, 0, -1500}, {750, 0, -1500}};
SVECTOR pjeep_push_pos[2] = {{0, 900, 600}, {0, 900, -600}};
SVECTOR pjeep_push_force = {0, 0, 0};

static void ExecProc(int proc, int value)
{
    GCL_ARGS args;
    long     data = value;

    if (proc == 0) return;

    args.argc = 1;
    args.argv = &data;
    GCL_ExecProc(proc, &args);
}

extern int  GM_GameOverTimer;
extern void Voicesys_800CE2D0(void);
extern void Voicesys_800CE5F8(int index, int field_18);
extern void Voicesys_800CE6AC(int arg0);
extern void Voicesys_800CE734(void);
extern void *NewPkJeepMeryl(CONTROL *root_ctrl, MATRIX *root_mat, int which);
extern void *NewPkJeepSnake(CONTROL *root_ctrl, MATRIX *root_mat);

void s19a_800D9BBC(SVECTOR *pos, short *dir, int angle, int len);
void s19a_800D9E98(Work *work, int speed);
int  s19a_800D9FA8(void);
static void InitSegs(Work *work);

static void Act(Work *work)
{
    SVECTOR  pos;
    SVECTOR  rot;
    SVECTOR  light_pos[2];
    CONTROL *control;
    OBJECT  *object;
    int      msg;
    int      d;

    GM_CurrentMap = work->map;

    pos = work->control.mov;
    pos.vy += 500;
    control = &work->control;
    DG_GetLightMatrix(&pos, work->light);

    if (work->state < 3 && GM_GameOverTimer != 0 && GM_Vitality <= 0)
    {
        Voicesys_800CE734();
    }

    msg = THING_Msg_CheckMessage(work->name, 4, pjeep_messages);
    work->time++;

    switch (work->state)
    {
    case 0:
        if (!s19a_800D9FA8())
        {
            work->state = 1;
            work->time = 0;
            PkJeep_Flags = 0x1000;
            work->meryl = NewPkJeepMeryl(control, &work->body.objs->world, work->proc_c);
        }
        break;

    case 1:
        if (msg == 1)
        {
            PkJeep_Flags |= 0x10000;
        }

        if (PkJeep_800E0E18 == 1)
        {
            work->state = 2;
            work->time = 0;
            Voicesys_800CE2D0();
            PkJeep_800E0E1C = 255;
            DG_VisibleObjs(work->object5.objs);
            work->light2[0].t[0] = 128;
            work->light2[0].t[1] = 128;
            work->light2[0].t[2] = 128;
            ExecProc(work->proc_e, 0x1C8E);
        }
        else
        {
            PkJeep_800E0E1C = work->light2[0].t[2] = work->light2[0].t[1] = work->light2[0].t[0] = PkJeep_800E0E1C / 2;
        }
        break;

    case 2:
        PkJeep_Flags |= 0x2000;

        if (msg == 2)
        {
            work->state = 3;
            work->time = 0;
            break;
        }

        if (++work->voice_timer > 450)
        {
            work->voice_timer = 0;

            switch (work->voice_index++)
            {
            case 0:
                Voicesys_800CE5F8(7, 1);
                break;

            case 1:
                Voicesys_800CE5F8(8, 1);
                break;

            case 2:
                Voicesys_800CE5F8(9, 1);
                work->voice_index = 0;
                break;
            }
        }
        break;

    case 3:
        if (GM_PlayerStatus & PLAYER_ACT_ONLY)
        {
            work->time = 0;
            break;
        }

        if (msg == 3)
        {
            work->ready = 1;
        }

        if (work->time == 1)
        {
            work->speed = 0;
            THING_Msg_SendMessage(SNAKE_NAME, HASH_KILL);
            work->snake = NewPkJeepSnake(control, &work->body.objs->world);
        }
        else if (work->time < 15)
        {
            work->speed = GV_NearSpeed(work->speed, 400, 30);
            work->dir = GV_NearSpeed(work->dir, 0x600, 60);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);
            PkJeep_Flags |= 0x20;
            s19a_800D9E98(work, work->speed);

            if (work->time == 2)
            {
                GM_SeSet(&work->control.mov, 188);
                NewPadVibration(pjeep_382C, 2);
            }
        }
        else if (work->time < 20)
        {
            work->dir = GV_NearExp4(work->dir, 0x600);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);
            s19a_800D9E98(work, work->speed);
        }
        else if (work->time < 90)
        {
            work->speed = GV_NearExp4(work->speed, 0);
            work->dir = GV_NearExp4(work->dir, 0x600);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);
            s19a_800D9E98(work, work->speed);

            if (work->time == 89)
            {
                Voicesys_800CE5F8(11, 1);
            }
        }
        else if (work->ready)
        {
            work->state = 4;
            work->time = 0;
        }

        GM_PlayerStatus &= ~PLAYER_INVINCIBLE;
        break;

    case 4:
        if (work->time == 4)
        {
            Voicesys_800CE6AC(1);
            Voicesys_800CE2D0();
        }

        if (work->time < 30)
        {
            work->accel = 0;
            if (work->time == 20)
            {
                PkJeep_Flags = 0x20200;
            }
        }
        else if (work->time < 40)
        {
            work->dir = GV_NearExp4(work->dir, control->rot.vy);
            work->speed = GV_NearSpeed(work->speed, -300, work->accel);
            work->accel = GV_NearSpeed(work->accel, 30, 4);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);
            s19a_800D9E98(work, work->speed);

            if (work->time == 30)
            {
                GM_SeSet(&work->control.mov, 183);
                NewPadVibration(pjeep_382C, 2);
            }
        }
        else if (work->time < 50)
        {
            work->dir = GV_NearExp4(work->dir, control->rot.vy - 200);
            work->speed = GV_NearSpeed(work->speed, -300, work->accel);
            work->accel = GV_NearSpeed(work->accel, 30, 4);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);

            if (work->time == 49)
            {
                work->accel = 0;
            }

            s19a_800D9E98(work, work->speed);
            PkJeep_Flags &= ~0x20200;
        }
        else if (work->time < 60)
        {
            work->dir = GV_NearExp4(work->dir, control->rot.vy);
            work->speed = GV_NearExp8(work->speed, 0);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);

            if (work->speed == 0)
            {
                work->time = 60;
            }

            s19a_800D9E98(work, work->speed);
        }
        else if (work->time < 80)
        {
            work->accel = 0;
            work->speed = 2;

            if (GM_GameOverTimer != 0)
            {
                work->time = 70;
            }

            GM_PlayerStatus |= PLAYER_INVINCIBLE;

            if (work->time == 70)
            {
                PkJeep_Flags = 0x20;
            }
        }
        else if (work->time < 210)
        {
            work->dir = GV_NearSpeed(work->dir, 0x800, 40);
            work->speed = GV_NearSpeed(work->speed, 700, work->accel);
            work->accel = GV_NearSpeed(work->accel, 30, 4);
            s19a_800D9BBC(&control->mov, &control->rot.vy, work->dir, work->speed);
            s19a_800D9E98(work, work->speed);

            if (work->time == 80)
            {
                GM_SeSet(&work->control.mov, 180);
                NewPadVibration(pjeep_382C, 2);
            }

            if (work->time == 120)
            {
                PkJeep_Flags &= ~0x20200;
            }
        }
        else
        {
            work->state = 5;
            work->time = 0;
        }
        break;
    }

    if (control->mov.vz < -25000)
    {
        work->speed = 0;
        control->mov.vz = -25000;
    }

    control->turn = control->rot;
    GM_ActControl(control);
    GM_ActObject2(&work->body);

    rot.vx = control->rot.vx;
    rot.vy = control->rot.vy;
    rot.vz = 0;

    d = (work->speed * 4096) / 2199;
    object = &work->object2;
    object->rots[1].vx += d;
    object->rots[2].vx += d;
    object->rots[3].vx += d;
    object->rots[4].vx += d;
    object->rots[3].vy = work->dir - control->rot.vy;
    object->rots[4].vy = work->dir - control->rot.vy;

    DG_SetPos2(&control->mov, &rot);
    GM_ActObject2(object);
    DG_MovePos(&pjeep_383C);
    GM_ActObject2((OBJECT *)&work->object3);

    InitSegs(work);

    if (PkJeep_800E0E1C > 64)
    {
        DG_SetPos(&work->body.objs->world);
        DG_PutVector(pjeep_3844, light_pos, 2);
        DG_SetTmpLight(&light_pos[0], PkJeep_800E0E1C * 4, PkJeep_800E0E1C * 5);
        DG_SetTmpLight(&light_pos[1], PkJeep_800E0E1C * 4, PkJeep_800E0E1C * 5);
    }
}

static void Die(Work *work)
{
    int i;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->object2);
    GM_FreeObject((OBJECT *)&work->object3);
    GM_FreeObject((OBJECT *)&work->object4);
    GM_FreeObject((OBJECT *)&work->object5);

    if (work->meryl)
    {
        GV_DestroyActor(work->meryl);
    }

    if (work->snake)
    {
        GV_DestroyActor(work->snake);
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
    DG_InvisibleObjs(obj->objs);

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
    work->time = 0;
    work->state = 0;
    work->speed = 0;
    work->dir = control->rot.vy;
    PkJeep_800E0E1C = 0;
    work->field_584 = 0;
    PkJeep_800E0E18 = 0;
    return 0;
}

void *NewPkJeep(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "pjeep.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}

/* moves pos by len in the direction *dir, then turns *dir by angle */
void s19a_800D9BBC(SVECTOR *pos, short *dir, int angle, int len)
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
        GM_SeSetMode(&target->center, SE_HIT, GM_SEMODE_BOMB);
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
