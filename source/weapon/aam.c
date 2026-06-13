#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "game/vibrate.h"
#include "linkvar.h"
#include "bullet/amissile.h"
#include "sound/g_sound.h"

extern int amissile_alive_8009F490;
extern GM_SnakeCameraWork GM_SnakeCamera;
extern TARGET *target_800BDF00;
extern int dword_800AB8A4;

/*---------------------------------------------------------------------------*/
// Anti-Air Missile (Stinger)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define STINGER_MODEL   GV_StrCode("stinger")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    u_long        *flags;
    int            side;
    int            time;
    void          *sight;
} Work;

TARGET *StnTarget = NULL;
SVECTOR svector_800AB8A4 = {-300, 200, 0, 0};

char byte_8009F40C[] = {0, 2, 127, 4, 0};
char byte_8009F414[] = {145, 4, 75, 10, 0};

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    MATRIX      world;
    MATRIX      pos;
    SVECTOR     rot;
    u_long      flags;
    int         ammo;

    if (!work->sight)
    {
        work->sight = NewStnSight(work->root_ctrl);
    }

    GM_SetCurrentMap(work->root_ctrl->map->index);
    DG_GroupObjsEx(work->object.objs);

    if (work->root_obj->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
    }

    flags = *work->flags;

    if (work->time > 0)
    {
        if (work->time >= 27)
        {
            GM_SnakeCamera.rotate2.vx += (30 - work->time) * -36;
        }
        else if (work->time > 14)
        {
            GM_SnakeCamera.rotate2.vx += (work->time - 12) * -12;
        }

        work->time--;
    }

    if ((work->time == 0) && (flags & WEAPON_TRIG) && !amissile_alive_8009F490)
    {
        work->time = 30;

        ammo = GM_Weapons[WP_Stinger];

        if (ammo > 0)
        {
            if (target_800BDF00 != 0)
            {
                StnTarget = target_800BDF00;
            }
            else
            {
                StnTarget = NULL;
            }

            rot.vx = work->root_ctrl->rot.vx - 1024;
            rot.vy = work->root_ctrl->rot.vy;
            rot.vz = 0;

            RotMatrixYXZ(&rot, &world);
            rot.vx = 0;
            DG_SetPos2(&GM_SnakeCamera.position, &rot);
            DG_MovePos(&svector_800AB8A4);
            ReadRotMatrix(&pos);

            world.t[0] = pos.t[0];
            world.t[1] = pos.t[1];
            world.t[2] = pos.t[2];

            if (NewAMissile(&world, work->side))
            {
                GM_Weapons[WP_Stinger] = --ammo;

                GM_SeSet(&work->root_ctrl->mov, SE_MISSILE_FIRED);
                GM_SetNoise(200, 2, &work->root_ctrl->mov);

                NewPadVibration(byte_8009F40C, 1);
                NewPadVibration(byte_8009F414, 2);
            }
        }
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

static int GetResources(Work *work, OBJECT *root_obj, int unit)
{
    OBJECT_NO_ROTS *object;

    object = &work->object;
    work->sight = NULL;

    GM_InitObjectNoRots(object, STINGER_MODEL, BODY_FLAG, 0);

    if (!object->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)object, root_obj, unit);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewAAM(CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "aam.c");

        if (GetResources(work, root_obj, unit) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->flags = flags;
        work->side = side;
        work->time = 0;
    }

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}
