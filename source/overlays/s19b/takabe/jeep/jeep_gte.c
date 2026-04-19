#include "game/game.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
    char     pad4[0x1C];
    MATRIX   world;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL  5

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )
#define BODY_MODEL  GV_StrCode("19b_o2")
#define BODY_MODEL2 GV_StrCode("19b_o3a")
#define BODY_MODEL3 GV_StrCode("19b_o3b")
#define BODY_MODEL4 GV_StrCode("19b_o3c")

typedef struct _GATE
{
    OBJECT  object;
    SVECTOR pos;
    SVECTOR step;
    SVECTOR rot;
    SVECTOR turn;
    char    pad1[0x4];
} GATE;

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    GATE    gates[2];
    TARGET *target;
    MATRIX  world;
    int     side;
    int     dist;
    int     hit_flag;
} Work;

extern SVECTOR s19b_dword_800C3750;
extern SVECTOR s19b_dword_800C3758;

void s19b_jeep_gls_800CEC24(int, SVECTOR *);

static void Act(Work *work)
{
    VECTOR   scale = {2048, 2048, 2048};
    SVECTOR  vec;
    CONTROL *control;
    TARGET  *trg;
    GATE    *gate1;
    GATE    *gate2;
    GATE    *gate;
    int      i;

    control = &work->control;

    if (Takabe_JeepSystem.pos.vz != 0)
    {
        DG_GetLightMatrix(&control->mov, work->light);
    }

    trg = work->target;
    if (trg->damaged & TARGET_POWER)
    {
        if (work->hit_flag == 0)
        {
            trg->damaged &= ~TARGET_POWER;

            if (trg->a_mode == 2)
            {
                trg->life = 255;
                DG_InvisibleObjs(work->body.objs);

                gate1 = &work->gates[0];
                GM_InitObject(&gate1->object, BODY_MODEL3, BODY_FLAG, 0);
                GM_ConfigObjectLight(&gate1->object, work->light);

                gate2 = &work->gates[1];
                GM_InitObject(&gate2->object, BODY_MODEL4, BODY_FLAG, 0);
                GM_ConfigObjectLight(&gate2->object, work->light);

                gate1[0].pos.vy = gate1[1].pos.vy = control->mov.vy;
                gate1[0].pos.vz = gate1[1].pos.vz = control->mov.vz;

                gate1[0].pos.vx = control->mov.vx + trg->size.vx / 2;
                gate1[1].pos.vx = control->mov.vx - trg->size.vx / 2;

                gate1[0].step = gate1[1].step = trg->scale;

                gate1[0].turn.vx = 300;
                gate1[0].turn.vy = -160;
                gate1[0].rot.vz = 500;

                gate1[1].turn.vx = 200;
                gate1[1].turn.vy = 20;
                gate1[1].rot.vz = -200;

                gate1[0].step.vx = 50;
                gate1[0].step.vy = -10;
                gate1[0].step.vz = -170;

                gate1[1].step.vx = 80;
                gate1[1].step.vy = 50;
                gate1[1].step.vz = -50;

                work->hit_flag = 1;
                work->target->class = TARGET_AVAIL;

                GM_SeSet(&control->mov, 186);
            }
        }
    }

    GV_AddVec3(&control->mov, &Takabe_JeepSystem.pos, &control->mov);

    work->dist += Takabe_JeepSystem.pos.vz;
    if (work->dist > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    work->world.t[0] = control->mov.vx;
    work->world.t[1] = control->mov.vy;
    work->world.t[2] = control->mov.vz;

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    ScaleMatrix(&work->body.objs->world, &scale);

    if (work->hit_flag != 0)
    {
        gate = work->gates;
        for (i = 2; i > 0; i--)
        {
            gate->step.vy -= 27;

            GV_AddVec3(&gate->pos, &Takabe_JeepSystem.pos, &gate->pos);
            GV_AddVec3(&gate->pos, &gate->step, &gate->pos);
            GV_AddVec3(&gate->rot, &gate->turn, &gate->rot);

            s19b_jeep_gls_800CEC24(gate->pos.vz, &vec);

            if (gate->pos.vy < vec.vy)
            {
                gate->pos.vy = vec.vy;

                gate->step.vx /= 2;
                gate->step.vy = -(gate->step.vy / 2);
                gate->step.vz /= 2;

                gate->turn.vx /= 2;
                gate->turn.vy = -(gate->turn.vy / 2);
                gate->rot.vz = -(gate->rot.vz / 2);

                gate->pos.vy = vec.vy;
            }

            DG_SetPos2(&gate->pos, &gate->rot);
            GM_ActObject2(&gate->object);
            ScaleMatrix(&gate->object.objs->world, &scale);
            gate++;
        }
    }

    GM_MoveTarget(trg, &work->control.mov);
    GM_PushTarget(trg);
}

static void Die(Work *work)
{
    if (work->gates[0].object.objs != NULL)
    {
        GM_FreeObject(&work->gates[0].object);
        GM_FreeObject(&work->gates[1].object);
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    SVECTOR size;
    SVECTOR scale;
    DG_MDL *model;
    TARGET *trg;

    model = work->body.objs->def->model;
    size.vx = (model->max.vx - model->min.vx) / 4;
    size.vy = (model->max.vy - model->min.vy) / 4;
    size.vz = (model->max.vz - model->min.vz) / 4;

    scale = DG_ZeroVector;
    size.vy = 1000;

    trg = work->target = GM_AllocTarget();
    GM_SetTarget(trg, TARGET_POWER, NO_SIDE, &size);
    GM_Target_8002DCCC(trg, 1, -1, 3, 0, &scale);
    GM_MoveTarget(trg, &work->control.mov);
}

static int GetResources(Work *work, int name, SVECTOR *pos)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, GM_CurrentMap) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    work->world = DG_ZeroMatrix;

    control->mov = *pos;
    control->turn = control->rot = DG_ZeroVector;
    control->step = DG_ZeroVector;

    work->dist = pos->vz;
    if (work->dist > 0)
    {
        work->dist -= 65536;
    }

    body = &work->body;
    if (work->side == 0)
    {
        GM_InitObject(body, BODY_MODEL, BODY_FLAG, 0);
        GM_ConfigObjectLight(body, work->light);
    }
    else
    {
        GM_InitObject(body, BODY_MODEL2, BODY_FLAG, 0);
        GM_ConfigObjectLight(body, work->light);
    }

    InitTarget(work);
    work->hit_flag = 0;
    return 0;
}

void *NewJeepGate(int name, SVECTOR *pos, int side)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jeep_gte.c");

        work->side = side;

        if (side == 0)
        {
            GV_AddVec3(pos, &s19b_dword_800C3750, &vec);
        }
        else
        {
            GV_AddVec3(pos, &s19b_dword_800C3758, &vec);
        }

        if (GetResources(work, name, &vec) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
