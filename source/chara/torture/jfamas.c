#include "jfamas.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "okajima/bullet.h"
#include "anime/animconv/anime.h"
#include "sound/g_sound.h"

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS body;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    int           *trigger;
    int            side;
} Work;

#define EXEC_LEVEL  GV_ACTOR_LEVEL5
#define BODY_MODEL  GV_StrCode("famas")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

SVECTOR famas_pos = {5, 65036, 80};

static void Act(Work *work)
{
    MATRIX world;
    int    trigger;

    GM_SetCurrentMap(work->root_ctrl->map->index);
    DG_GroupObjsEx(work->body.objs);

    trigger = *work->trigger;

    if (work->root_obj->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }

    if (trigger & 2)
    {
        DG_SetPos(&work->body.objs->world);
        DG_MovePos(&famas_pos);
        ReadRotMatrix(&world);
        NewBullet(&world, work->side, 0, 1);
        GM_SeSet(&work->root_ctrl->mov, SE_FAMAS_SHOT);
        NewAnime_8005D604(&world);
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
}

static int GetResources(Work *work, OBJECT *root_obj, int unit)
{
    OBJECT_NO_ROTS *body;

    body = &work->body;
    GM_InitObjectNoRots(body, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectRoot((OBJECT *)body, root_obj, unit);
    return 0;
}

void *NewJohnnyFamas(CONTROL *root_ctrl, OBJECT *root_obj, int unit, int *trigger)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "jfamas.c");
        if (GetResources(work, root_obj, unit) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->trigger = trigger;
        work->side = ENEMY_SIDE;
    }

    return (void *)work;
}
