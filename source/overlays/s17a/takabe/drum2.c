#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "bullet/blast.h"
#include "takabe/thing.h"

typedef struct _Work
{
    GV_ACT  actor;
    int     map;            // 0x20
    CONTROL control;        // 0x24
    OBJECT  body;           // 0xA0
    MATRIX  light[2];       // 0x184
    SVECTOR size;           // 0x1C4
    TARGET *target;         // 0x1CC
    char    pad_1D0[0x24];
    int     field_1F4;
    int     field_1F8;
    int     field_1FC;
    int     height;         // 0x200
    int     field_204;
    SVECTOR min;            // 0x208
    SVECTOR max;            // 0x210
    int     proc;           // 0x218
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

extern BLAST_DATA blast_data_8009F4B8[8];

void *NewDrumSmoke(MATRIX *world, int arg1, int arg2);
void *NewDrumFire(MATRIX *world, int arg1, int arg2);

SVECTOR drum2_offsets[2] = {{-875, 1000, 0}, {875, 1000, 0}};

static void GetModelBounds(DG_DEF *def, SVECTOR *min, SVECTOR *max)
{
    int     lx, ly, lz;
    int     ux, uy, uz;
    int     n_models;
    DG_MDL *mdl;

    lz = 0x7FFF;
    ly = lz;
    lx = lz;
    uz = -0x8000;
    uy = uz;
    n_models = def->n_models;
    ux = uz;

    for (mdl = def->models; n_models > 0; n_models--, mdl++)
    {
        if (mdl->lx < lx)
        {
            lx = mdl->lx;
        }
        if (mdl->ly < ly)
        {
            ly = mdl->ly;
        }
        if (mdl->lz < lz)
        {
            lz = mdl->lz;
        }
        if (ux < mdl->ux)
        {
            ux = mdl->ux;
        }
        if (uy < mdl->uy)
        {
            uy = mdl->uy;
        }
        if (uz < mdl->uz)
        {
            uz = mdl->uz;
        }
    }

    min->vx = lx;
    min->vy = ly;
    min->vz = lz;
    max->vx = ux;
    max->vy = uy;
    max->vz = uz;
}

static void Act(Work *work)
{
    TARGET  *target;
    CONTROL *control;
    GV_MSG  *msg;
    MATRIX   world;

    target = work->target;
    GM_CurrentMap = work->map;
    control = &work->control;

    if (target->damaged & (TARGET_POWER | TARGET_PUSH))
    {
        if (target->vital < 0 || target->a_mode == 2 || (target->damaged & TARGET_PUSH))
        {
            if (work->proc != 0)
            {
                GCL_ExecProc(work->proc, NULL);
            }

            DG_SetPos(&work->body.objs->world);
            DG_MovePos(&drum2_offsets[0]);
            ReadRotMatrix(&world);
            NewBlast(&world, blast_data_8009F4B8);
            world.t[1] = 0;
            NewDrumSmoke(&world, 0, 150);
            NewDrumFire(&world, 0, 100);

            DG_SetPos(&work->body.objs->world);
            DG_MovePos(&drum2_offsets[1]);
            ReadRotMatrix(&world);
            NewBlast(&world, blast_data_8009F4B8);
            world.t[1] = 0;
            NewDrumSmoke(&world, 0, 150);
            NewDrumFire(&world, 0, 100);

            GV_DestroyActor(&work->actor);
        }

        target->damaged &= ~(TARGET_POWER | TARGET_PUSH);
    }

    GM_ActControl(control);
    GM_ActObject2(&work->body);
    GM_MoveTarget(target, &work->control.mov);
    GM_PushTarget(target);

    msg = control->msg;
    if (msg->message_len != 0 && msg->message[0] == 0xC39B)
    {
        target->vital = -1;
        target->a_mode = 2;
        target->damaged |= TARGET_POWER;
    }
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    DG_FreePreshade(work->body.objs);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    int     height;
    TARGET *target;

    work->target = target = GM_AllocTarget();

    work->size.vx = (work->max.vx - work->min.vx) / 4;
    work->size.vy = (work->max.vy - work->min.vy) / 4;
    work->size.vz = (work->max.vz - work->min.vz) / 4;

    GM_SetTarget(target, TARGET_POWER | TARGET_PUSH | TARGET_SEEK, NO_SIDE, &work->size);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, 20, 0, &DG_ZeroVector);

    height = work->control.mov.vy;
    work->height = height;
    work->control.mov.vy -= work->min.vy;
    GM_MoveTarget(target, &work->control.mov);
}

static int GetResources(Work *work, int name, int map)
{
    CONTROL *control;
    char    *pos, *dir;
    DG_LITS *lit;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);

    work->proc = THING_Gcl_GetInt('e');
    work->field_204 = THING_Gcl_GetIntDefault('r', 500);

    body = &work->body;
    GM_InitObject(body, THING_Gcl_GetInt('m'), BODY_FLAG, 0);

    DG_SetPos2(&control->mov, &control->rot);
    DG_PutObjs(work->body.objs);

    lit = control->map->lit;
    DG_MakePreshade(work->body.objs, lit->lights, lit->n_lights);

    GetModelBounds(work->body.objs->def, &work->min, &work->max);
    InitTarget(work);

    work->map = map;
    work->field_1F8 = 0;
    work->field_1F4 = 0;
    work->field_1FC = 0;
    return 0;
}

void *NewDrumCan2(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "drum2.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
