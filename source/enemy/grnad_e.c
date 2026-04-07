#include "grnad_e.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "strcode.h"

#include "bullet/tenage.h"      // for NewTenage3
#include "weapon/weapon.h"      // for GRD_*

extern void *NewBlast(MATRIX *world /*, BLAST_DATA *blast_data */);

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL5

#define GRENADE_MODEL   0x3b88  // GV_StrCode("grenade")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    CONTROL *control;
    OBJECT  *parent;
    OBJECT   object;
    int      num_parent;
    int     *flags;
    SVECTOR  pos;
    int      timer;
    int      type;
} Work;

/*---------------------------------------------------------------------------*/

SVECTOR svec_800C360C[2] = {{0, 80, 80, 0}, {0, 20, 500, 0}};

static void Act(Work *work)
{
    SVECTOR  pos;
    SVECTOR  step;
    int      flags;
    MATRIX  *world;
    CONTROL *control;
    SVECTOR *var_s2;
    int      dist;

    GM_CurrentMap = work->control->map->index;

    GM_ActObject2(&work->object);

    flags = *work->flags;
    world = &work->parent->objs->objs[work->num_parent].world;

    if (flags & 0x1)
    {
        if (--work->timer <= 0)
        {
            // Missing second argument `pBlastData`.
            NewBlast(world);
            work->timer = 120;
        }

        if (flags & 0x6)
        {
            control = work->control;
            DG_SetPos2(&control->mov, &control->rot);

            var_s2 = (flags & 0x4) ? &svec_800C360C[1] : &svec_800C360C[0];

            work->pos.vy = control->mov.vy;

            dist = GV_DiffVec3(&control->mov, &work->pos);

            if (flags & 0x2)
            {
                dist /= 2;
            }

            var_s2->vz = dist / 8;

            DG_RotVector(var_s2, &step, 1);

            pos.vx = world->t[0];
            pos.vy = world->t[1];
            pos.vz = world->t[2];

            NewTenage3(&pos, &step, work->timer, work->type, GRENADE_MODEL, 0, 0);
            work->timer = 120;
        }

        DG_VisibleObjs(work->object.objs);
    }
    else
    {
        DG_InvisibleObjs(work->object.objs);
        work->timer = 120;
    }
}

static void Die(Work *work)
{
    GM_FreeObject(&work->object);
}

static int GetResources(Work *work, OBJECT *parent, int num_parent, int unused)
{
    OBJECT *object;

    object = &work->object;

    printf("grenade model=%d \n", GRENADE_MODEL);

    GM_InitObject(object, GRENADE_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectRoot(object, parent, num_parent);

    return 0;
}

/*---------------------------------------------------------------------------*/

static void *InitGrenadeEnemy(CONTROL *control, OBJECT *parent, int num_parent, u_long *flags, int side, SVECTOR *pos, int type)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "grnad_e.c");

        if (GetResources(work, parent, num_parent, type) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->timer = 120;
        work->type = type;
        work->pos = *pos;
    }

    return (void *)work;
}

void *NewGrenadeEnemy(CONTROL *control, OBJECT *parent, int num_parent, u_long *flags, SVECTOR *pos, int side)
{
    return InitGrenadeEnemy(control, parent, num_parent, flags, side, pos, GRD_GRENADE);
}

void *NewGrenadeEnemy2(CONTROL *control, OBJECT *parent, int num_parent, u_long *flags, SVECTOR *pos, int side)
{
    return InitGrenadeEnemy(control, parent, num_parent, flags, side, pos, GRD_STUN);
}
