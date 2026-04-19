#include "game/game.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x18];
    SVECTOR  field_38;
    char     pad4[0x20];
    OBJECT  *body;
    char     pad5[0x18];
    int      field_7C;
    MATRIX   world;
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL  5

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )
#define BODY_MODEL  GV_StrCode("19b_o1")

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    TARGET *target;
    MATRIX  world;
    int     side;
    int     dist;
} Work;

extern VECTOR  s19b_dword_800C3730;
extern SVECTOR s19b_dword_800C3740;
extern SVECTOR s19b_dword_800C3748;

void *NewGlassSplash3(MATRIX *world);

void s19b_jeep_gls_800CF0B0(Work *work)
{
    MATRIX   world;
    CONTROL *control;
    TARGET  *trg;
    int      dead;

    dead = 0;

    control = &work->control;
    trg = work->target;
    if (trg->damaged & TARGET_POWER)
    {
        trg->damaged &= ~TARGET_POWER;

        if (trg->life < 0)
        {
            trg->life = 255;
            DG_InvisibleObjs(work->body.objs);
            work->target->class = TARGET_AVAIL;
            dead = 1;
            GM_SeSet(&control->mov, 179);
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
    ScaleMatrix(&work->body.objs->world, &s19b_dword_800C3730);

    if (dead == 1)
    {
        world = work->body.objs->world;
        NewGlassSplash3(&world);

        world = work->body.objs->world;
        RotMatrixY(1024, &world);
        NewGlassSplash3(&world);

        world = work->body.objs->world;
        RotMatrixY(3072, &world);
        NewGlassSplash3(&world);
    }

    GM_MoveTarget(trg, &work->control.mov);
}

void s19b_jeep_gls_800CF2F4(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

void s19b_jeep_gls_800CF330(Work *work)
{
    SVECTOR size;
    SVECTOR scale;
    DG_MDL *model;
    TARGET* trg;

    model = work->body.objs->def->model;

    size.vx = (model->max.vx - model->min.vx) / 4;
    size.vy = (model->max.vy - model->min.vy) / 4 + 100;
    size.vz = (model->max.vz - model->min.vz) / 4;

    scale = DG_ZeroVector;

    trg = work->target = GM_AllocTarget();
    GM_SetTarget(trg, ( TARGET_POWER | TARGET_SEEK ), ENEMY_SIDE, &size);
    GM_Target_8002DCCC(trg, 1, -1, 3, 0, &scale);
    GM_MoveTarget(trg, &work->control.mov);
}

int s19b_jeep_gls_800CF454(Work *work, int name, SVECTOR *pos)
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

    if (work->side == 1)
    {
        control->rot.vy = 2048;
        control->turn.vy = 2048;
    }

    control->step = DG_ZeroVector;

    work->dist = pos->vz;
    if (work->dist > 0)
    {
        work->dist -= 65536;
    }

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectStep(body, &control->step);

    s19b_jeep_gls_800CF330(work);
    return 0;
}

void *NewJeepGlass(int name, SVECTOR *pos, int side)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_gls_800CF0B0, s19b_jeep_gls_800CF2F4, "jeep_gls.c");

        work->side = side;

        if (side == 0)
        {
            GV_AddVec3(pos, &s19b_dword_800C3740, &vec);
        }
        else
        {
            GV_AddVec3(pos, &s19b_dword_800C3748, &vec);
        }

        if (s19b_jeep_gls_800CF454(work, name, &vec) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
