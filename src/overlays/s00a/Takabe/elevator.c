#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/object.h"
#include "Game/vibrate.h"
#include "Takabe/thing.h"

typedef struct _ElevatorWork
{
    GV_ACT      actor;
    int         map;
    int         name;
    CONTROL     control;
    OBJECT      object1; // OBJECT[2] ???
    OBJECT      object2;
    MATRIX      light[2];
    HZD_HEADER *hzm;     // HZD_HEADER[5] ???
    HZD_HEADER *hzm1;
    HZD_HEADER *hzm2;
    HZD_HEADER *hzm3;
    HZD_HEADER *hzm4;
    HZD_AREA   *areas;   // HZD_AREA[5] ???
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

extern int           bakudan_count_8009F42C;
extern int           counter_8009F448;
extern SVECTOR       DG_ZeroVector_800AB39C;
extern int           GM_CurrentMap_800AB9B0;
extern int           gControlCount_800AB9B4;
extern int           GM_AlertMode_800ABA00;
extern CONTROL      *GM_WhereList_800B56D0[96];
extern CONTROL      *tenage_ctrls_800BDD30[16];
extern int           tenage_ctrls_count_800BDD70;
extern HITTABLE      c4_actors[16];
extern HITTABLE stru_800BDE78[8];

unsigned short elevator_hash_800C3634[4] = {0xACDC, 0x085B, 0x804B, 0xDBC9};

char elevator_vib_800C363C[] = {0x00, 0x02, 0x7F, 0x02, 0x00, 0x00, 0x00, 0x00};
char elevator_vib_800C3644[] = {0x87, 0x04, 0x55, 0x01, 0x69, 0x01, 0x7D, 0x08, 0x5F, 0x08, 0x46, 0x0A, 0x37, 0x0C, 0x2D, 0x0E, 0x00, 0x00, 0x00, 0x00};
char elevator_vib_800C3658[] = {0x7F, 0x04, 0x00, 0x00};
char elevator_vib_800C365C[] = {0xA5, 0x06, 0x4B, 0x08, 0x2D, 0x0C, 0x00, 0x00};

void Elevator_800D9FC4(ElevatorWork *, SVECTOR *);
void Elevator_800DA140(ElevatorWork *);
void Elevator_800DA268(ElevatorWork *);
void Elevator_800DA358(ElevatorWork *, HZD_AREA *);
void Elevator_800DA3F8(ElevatorWork *, HZD_AREA *);
int  Elevator_800DA464(ElevatorWork *, void *);
void Elevator_800DA57C(int proc, long arg);

void      Takabe_ReshadeModel_800DC854(DG_OBJS *objs, LitHeader *lit);
DG_OBJS * s00a_unknown3_800DC7DC(int model, LitHeader *lit);
void      Takabe_FreeObjs_800DC820(DG_OBJS *objs);

#define EXEC_LEVEL 5

void ElevatorAct_800D8EA8(ElevatorWork *work)
{
    SVECTOR        sp10;
    SVECTOR        sp18;
    HZD_VEC        sp20;
    GV_MSG        *msg;
    int            var_s6;
    int            var_s5;
    int            found;
    int            message;
    int            scale;
    CONTROL      **where;
    int            n_controls;
    CONTROL       *control;
    HITTABLE *bomb;
    int            i, j;
    HITTABLE *mine;
    CONTROL      **tenage;
    HZD_FLR       *floor;
    int            n_floors;
    SVECTOR       *mov;
    SVECTOR       *var_s0_4;
    int            n_messages;

    var_s6 = 0;
    var_s5 = 0;

    GM_CurrentMap_800AB9B0 = work->map;

    found = THING_Msg_CheckMessage(work->name, 4, elevator_hash_800C3634);
    message = THING_Msg_GetResult();

    if (GM_AlertMode_800ABA00 != 0)
    {
        found = -1;
    }

    switch (work->f5C0)
    {
    case 0:
        if (found == 0 || found == 2)
        {
            work->f5C0 = 1;
            Elevator_800DA57C(work->f5D0, 0x361E);
            Elevator_800DA3F8(work, work->areas4);
            Elevator_800DA358(work, work->areas3);
            Elevator_800DA140(work);

            if (found == 2)
            {
                work->f594 = message;
                work->f58C |= 0x4;
            }

            work->f5A8 = 0;
            work->f598 = work->f5A0;
            work->f59C = work->f5A4;
        }
        break;

    case 1:
        if (work->f59C > 0)
        {
            if (--work->f59C == 0)
            {
                var_s5 = 0x4;
            }
        }
        else if (work->f584 < work->f580)
        {
            work->f584++;
            if (++work->f5C4 >= work->f5B4)
            {
                work->f5C4 = 0;
            }

            if (work->f5C4 == 0)
            {
                var_s5 = 0x8;
            }

            if (work->f584 == work->f580)
            {
                var_s5 |= 0x10;
            }
        }
        else if (--work->f598 <= 0)
        {
            work->f5C0 = 2;
            work->f58C &= ~0x4;

            Elevator_800DA57C(work->f5D0, 0xADBF);
            Elevator_800DA3F8(work, work->areas1);
            Elevator_800DA358(work, work->areas2);
            Elevator_800DA268(work);

            work->f5A8 = 1;
        }
        break;

    case 2:
        if (found == 1 || found == 3)
        {
            work->f5C0 = 3;

            Elevator_800DA57C(work->f5D0, 0xF624);
            Elevator_800DA3F8(work, work->areas2);
            Elevator_800DA358(work, work->areas1);
            Elevator_800DA140(work);

            if (found == 3)
            {
                work->f594 = message;
                work->f58C |= 0x4;
            }

            work->f5A8 = 0;
            work->f598 = work->f5A0;
            work->f59C = work->f5A4;
        }
        break;

    case 3:
        if (work->f59C > 0)
        {
            if (--work->f59C == 0)
            {
                var_s5 = 0x20;
            }
        }
        else if (work->f584 > 0)
        {
            work->f584--;

            if (++work->f5C4 >= work->f5B4)
            {
                work->f5C4 = 0;
            }

            if (work->f5C4 == 0)
            {
                var_s5 = 0x1;
            }

            if (work->f584 == 0)
            {
                var_s5 |= 0x2;
            }
        }
        else if (--work->f598 <= 0)
        {
            work->f5C0 = 0;
            work->f58C &= ~0x4;

            Elevator_800DA57C(work->f5D0, 0xEDB8);
            Elevator_800DA3F8(work, work->areas3);
            Elevator_800DA358(work, work->areas4);
            Elevator_800DA268(work);

            work->f5A8 = 1;
        }
        break;
    }

    if (work->f5A8 != 0)
    {
        work->f5AC = GV_NearExp4_800263B0(work->f5AC, -1500);
    }
    else
    {
        work->f5AC = GV_NearExp4_800263B0(work->f5AC, 0);
    }

    if (work->f584 == work->f588 && work->f598 <= 0)
    {
        var_s6 = 1;
    }

    work->f588 = work->f584;

    if (var_s6 == 0)
    {
        scale = work->f584;
        sp18.vx = (work->f568.vx * scale) / work->f580;
        sp18.vy = (work->f568.vy * scale) / work->f580;
        sp18.vz = (work->f568.vz * scale) / work->f580;

        GV_AddVec3_80016D00(&work->f560, &sp18, &work->f570);
        GV_SubVec3_80016D40(&sp18, &work->f578, &sp10);

        work->f578 = sp18;

        if (work->f58C & 0x4)
        {
            where = GM_WhereList_800B56D0;
            for (n_controls = gControlCount_800AB9B4; n_controls > 0; n_controls--)
            {
                control = *where;
                if (control->name == work->f594)
                {
                    GV_AddVec3_80016D00(&control->mov, &sp10, &control->mov);
                    break;
                }

                where++;
            }
        }
        // translate the position of the c4 actors if they are on the elevator
        if (bakudan_count_8009F42C != 0)
        {
            bomb = c4_actors;
            for (j = 16; j > 0; j--)
            {
                // check if the c4 is on the walls or floors of the elevator
                if (bomb->actor && Elevator_800DA464(work, bomb->data))
                {
                    GV_AddVec3_80016D00(&bomb->control->mov, &sp10, &bomb->control->mov);
                }

                bomb++;
            }
        }

        if (counter_8009F448 != 0)
        {
            mine = stru_800BDE78;
            for (j = 8; j > 0; j--)
            {
                if (mine->actor && Elevator_800DA464(work, mine->data))
                {
                    GV_AddVec3_80016D00(&mine->control->mov, &sp10, &mine->control->mov);
                }

                mine++;
            }
        }

        if (tenage_ctrls_count_800BDD70 != 0)
        {
            tenage = tenage_ctrls_800BDD30;
            for (i = 16; i > 0; i--)
            {
                if (*tenage)
                {
                    floor = work->floors;
                    for (n_floors = work->n_floors; n_floors > 0; n_floors--)
                    {
                        if (sub_8002992C(floor, &(*tenage)->mov) & 0x1)
                        {
                            sub_800298DC(&sp20);
                            mov = &(*tenage)->mov;

                            if ((mov->vy - sp20.long_access[0]) < 200)
                            {
                                GV_AddVec3_80016D00(mov, &sp10, mov);
                            }

                            break;
                        }

                        floor++;
                    }
                }

                tenage++;
            }
        }
    }

    if (work->f58C & 0x20)
    {
        var_s0_4 = &work->f570;
    }
    else
    {
        var_s0_4 = &work->f578;
    }

    if (work->f58C & 0x1)
    {
        if (work->f590 == 0)
        {
            Takabe_ReshadeModel_800DC854(work->object1.objs, Map_FromId_800314C0(GM_CurrentMap_800AB9B0)->lit);
            work->f590 = 1;
        }
    }
    else if (var_s6 == 0)
    {
        DG_GetLightMatrix_8001A3C4(&work->f570, work->light);
    }

    if (var_s6 == 0)
    {
        Elevator_800D9FC4(work, var_s0_4);
        DG_SetPos2_8001BC8C(var_s0_4, &DG_ZeroVector_800AB39C);
        GM_ActObject2_80034B88(&work->object1);
    }

    var_s5 &= work->f5B0;

    if (var_s5 & 0x9)
    {
        sub_80032BC4(var_s0_4, work->f5B6, work->f5BC);
    }

    if (var_s5 & 0x12)
    {
        sub_80032BC4(var_s0_4, work->f5B8, work->f5BC);
    }

    if (var_s5 & 0x24)
    {
        sub_80032BC4(var_s0_4, work->f5BA, work->f5BC);
    }

    if (((work->f58C & 0xC) == 0xC) && (work->f594 == CHARA_SNAKE))
    {
        if (var_s5 & 0x24)
        {
            NewPadVibration_8005D58C(elevator_vib_800C363C, 1);
            NewPadVibration_8005D58C(elevator_vib_800C3644, 2);
        }

        if (var_s5 & 0x12)
        {
            NewPadVibration_8005D58C(elevator_vib_800C3658, 1);
            NewPadVibration_8005D58C(elevator_vib_800C365C, 2);
        }
    }

    if (work->f58C & 0x8)
    {
        if (work->f5AC < -1000)
        {
            DG_InvisibleObjs(work->object2.objs);
        }
        else
        {
            DG_VisibleObjs(work->object2.objs);
        }

        sp20.x = var_s0_4->vx;
        sp20.y = var_s0_4->vz;
        sp20.z = var_s0_4->vy + work->f5AC;

        DG_SetPos2_8001BC8C((SVECTOR *)&sp20, &DG_ZeroVector_800AB39C);
        GM_ActObject2_80034B88(&work->object2);
    }

    work->control.mov = work->f570;

    n_messages = GV_ReceiveMessage_80016620(work->name, &msg);
    for (; n_messages > 0; n_messages--)
    {
        if (msg->message[0] == 0x335E)
        {
            work->object1.objs->objs[msg->message[1]].raise = msg->message[2];
        }

        msg++;
    }
}

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
        Takabe_FreeObjs_800DC820(work->object1.objs);

        if (work->f58C & 0x8)
        {
            Takabe_FreeObjs_800DC820(work->object2.objs);
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
    work->hzd = Map_FromId_800314C0(work->map)->hzd;

    control = &work->control;
    if (GM_InitControl_8002599C(control, name, where) < 0)
    {
error:
        return -1;
    }

    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);

    object1 = &work->object1;
    object2 = &work->object2;

    model2 = THING_Gcl_GetShort('f');
    model1 = THING_Gcl_GetShort('m');

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
        model1 = THING_Gcl_GetShort('n');
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
    work->f5C8 = THING_Gcl_GetShort('o');
    work->f5CC = THING_Gcl_GetShort('u');
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

    filename = THING_Gcl_GetShort('h');
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
    control->mov = work->f570;

    return 0;
}

GV_ACT * NewElevator_800D9F30(int name, int where, int argc, char **argv)
{
    ElevatorWork *work;

    work = (ElevatorWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ElevatorWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ElevatorAct_800D8EA8, (TActorFunction)ElevatorDie_800D97D8, "elevator.c");

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
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, wall);
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
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, wall);
        wall++;
    }
}

/**
 * @brief Check if the given pointer is in the list of walls or floors.
 *  Used to check if c4 or claymores are on the elevator.
 *
 * @param work ElevatorWork actor
 * @param ptr Pointer to check
 * @return int 1 if the target is a wall or floor, 0 otherwise
 */
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
    GV_ZeroMemory_8001619C(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap_800AB9B0;
    object->objs = s00a_unknown3_800DC7DC(model, Map_FromId_800314C0(GM_CurrentMap_800AB9B0)->lit);
}

void Elevator_800DA534(HZD_VEC *in, SVECTOR *addend, HZD_VEC *out)
{
    out->x = in->x + addend->vx;
    out->y = in->y + addend->vy;
    out->z = in->z + addend->vz;
    out->h = in->h;
}

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
