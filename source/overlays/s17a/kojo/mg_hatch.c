#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "anime/animconv/anime.h"
#include "takabe/spark2.h"

/* Metal Gear REX missile hatch flying off */

typedef struct _Work
{
    GV_ACT         actor;
    int            map;         // 0x20
    OBJECT_NO_ROTS body;        // 0x24
    MATRIX         light[2];    // 0x48
    MATRIX         unused;      // 0x88
    SVECTOR        rot_speed;   // 0xA8
    SVECTOR        pos;         // 0xB0
    SVECTOR        rot;         // 0xB8
    SVECTOR        speed;       // 0xC0
    int            time;        // 0xC8
} Work;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

SVECTOR mg_hatch_speed = {0, 0, 300};

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    if (work->time < 6)
    {
        AN_RecoilSmoke(&work->pos);
    }

    GV_AddVec3(&work->pos, &work->speed, &work->pos);
    GV_AddVec3(&work->rot, &work->rot_speed, &work->rot);

    work->speed.vx -= work->speed.vx / 8;
    work->speed.vz -= work->speed.vz / 8;
    work->speed.vy -= 40;

    work->rot_speed.vx -= work->rot_speed.vx / 16;
    work->rot_speed.vy -= work->rot_speed.vy / 16;
    work->rot_speed.vz -= work->rot_speed.vz / 16;

    if (work->pos.vy < 0)
    {
        work->pos.vy = -work->pos.vy - 100;

        work->speed.vy = -work->speed.vy / 4;
        work->speed.vx -= work->speed.vx / 4;
        work->speed.vz -= work->speed.vz / 4;

        work->rot = DG_ZeroVector;

        work->rot_speed.vx -= work->rot_speed.vx / 2;
        work->rot_speed.vy -= work->rot_speed.vy / 2;
        work->rot_speed.vz -= work->rot_speed.vz / 2;

        if (work->pos.vy < 0)
        {
            GV_DestroyActor(work);
        }
    }

    DG_SetPos2(&work->pos, &work->rot);
    GM_ActObject2((OBJECT *)&work->body);

    if (work->time > 60)
    {
        if (work->time & 1)
        {
            DG_VisibleObjs(work->body.objs);
        }
        else
        {
            DG_InvisibleObjs(work->body.objs);
        }
    }

    if (work->time > 80)
    {
        GV_DestroyActor(work);
    }

    work->time++;
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
}

static int GetResources(Work *work, MATRIX *world)
{
    OBJECT_NO_ROTS *body;

    body = &work->body;
    GM_InitObjectNoRots(body, GV_StrCode("rex_mhat"), BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)body, work->light);

    ApplyMatrixSV(world, &mg_hatch_speed, &work->speed);

    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];

    work->rot_speed.vx = GV_RandU(256);
    work->rot_speed.vy = GV_RandS(256);
    work->rot_speed.vz = GV_RandS(256);

    work->time = 0;
    work->map = GM_CurrentMap;

    NewSpark2_800CA714(world);
    return 0;
}

void *NewMgHatch(MATRIX *world)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "mg_hatch.c");

        if (GetResources(work, world) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}
