#include "bullet/blast.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;
    MATRIX  light[2];
    TARGET *target;
    char    pad1[0x14];
    int     x;
    int     y;
    int     z;
    HOMING *hom;
    int     depth;
    int     field_1EC;
    int     field_1F0;
    int     field_1F4;
    int     height;
    int     field_1FC;
} Work;

#define EXEC_LEVEL  5
#define BODY_MODEL  GV_StrCode("19b_o4a")
#define BODY_MODEL2 GV_StrCode("19b_o4b")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )
#define TARGET_FLAG ( TARGET_POWER | TARGET_SEEK )

extern BLAST_DATA blast_data_8009F4B8[8];

SVECTOR s19b_dword_800C3494 = {435, 375, 185};

extern SVECTOR s19b_dword_800DE670;
extern SVECTOR s19b_dword_800DE690;

void *NewJeepBlast(MATRIX *world, BLAST_DATA *blast);
void *NewJeepDrumSmoke(MATRIX *world, int, int);
void *NewJeepDrumFire(MATRIX *world, int, int);

void s19b_jdrum_800C90BC(Work *work)
{
    VECTOR   scale = {2048, 2048, 2048};
    MATRIX   world;
    CONTROL *control;
    int      changed;
    TARGET  *target;
    OBJECT  *body;

    work->field_1F4 = FALSE;

    control = &work->control;
    DG_GetLightMatrix(&control->mov, work->light);

    changed = FALSE;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        if (target->life < 0 && work->field_1F0 == 0)
        {
            work->field_1EC = 1;
            work->field_1F0 = 1;
            target->life = 255;
            work->hom->flag = FALSE;
            work->target->side = BOTH_SIDE;
            work->target->class = TARGET_AVAIL;
        }
    }

    if (work->field_1F0 != 0)
    {
        if (work->field_1F0 < 10)
        {
            work->field_1F0++;
        }

        body = &work->body;
        if (work->field_1F0 == 7)
        {
            GM_FreeObject(body);
            GM_InitObject(body, BODY_MODEL2, BODY_FLAG, 0);
            GM_ConfigObjectJoint(body);
            GM_ConfigObjectLight(body, work->light);
            GM_ConfigObjectStep(body, &work->control.step);
            changed = TRUE;
        }
    }

    if (!work->field_1F4)
    {
        GM_ConfigControlHazard(control, -1, 0, -1);
    }
    else
    {
        GM_ConfigControlHazard(control, -1, -2, -1);
    }

    GV_AddVec3(&control->mov, &s19b_dword_800DE670, &control->mov);
    work->depth += s19b_dword_800DE670.vz;
    if (work->depth > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    work->x = control->mov.vx;
    work->y = control->mov.vy;
    work->z = control->mov.vz;

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    ScaleMatrix(&work->body.objs->world, &scale);

    if (changed)
    {
        world = work->body.objs->world;
        NewJeepBlast(&work->body.objs->world, blast_data_8009F4B8);
        NewJeepDrumSmoke(&work->body.objs->world, 0, 150);

        world.t[1] -= work->height;
        NewJeepDrumFire(&world, 0, 30);
    }

    GM_MoveTarget(target, &work->control.mov);
}

void s19b_jdrum_800C9374(Work *work)
{
    GM_FreeHomingTarget(work->hom);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

void s19b_jdrum_800C93BC(Work *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    GM_SetTarget(target, TARGET_FLAG, ENEMY_SIDE, &s19b_dword_800C3494);
    GM_Target_8002DCCC(target, 1, -1, 150, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &work->control.mov);
}

int s19b_jdrum_800C9438(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;

    work->field_1FC = TRUE;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    if (work->field_1FC)
    {
        control->mov.vx /= 2;
        control->mov.vy = 0;
        control->mov.vz /= 2;

        GV_AddVec3(&control->mov, &s19b_dword_800DE690, &control->mov);

        work->depth = control->mov.vz;
        if (work->depth > 0)
        {
            work->depth -= 65536;
        }
    }

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectLight(body, work->light);

    s19b_jdrum_800C93BC(work);

    work->hom = GM_AllocHomingTarget(&body->objs->world, &work->control);
    if (work->hom)
    {
        work->hom->flag = 1;
    }

    work->field_1F0 = 0;
    work->field_1EC = 0;
    work->field_1F4 = FALSE;
    work->height = -body->objs->def->model[0].min.vy / 2;
    control->mov.vy += work->height;
    return 0;
}

void *NewJeepDrum(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jdrum_800C90BC, s19b_jdrum_800C9374, "jdrum.c");

        if (s19b_jdrum_800C9438(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
