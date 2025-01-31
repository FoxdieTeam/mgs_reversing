#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Okajima/bullet.h"
#include "Anime/animeconv/anime.h"
#include "SD/g_sound.h"

typedef struct JFamasWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    int           *trigger;
    int            side;
} JFamasWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

SVECTOR s03c_dword_800C33AC = {5, 65036, 80};

extern int DG_CurrentGroupID;

void JFamasAct_800CAE30(JFamasWork *work)
{
    MATRIX rot;
    int    trigger;

    GM_SetCurrentMap(work->control->map->index);
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

    trigger = *work->trigger;

    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
    }

    if (trigger & 2)
    {
        DG_SetPos(&work->object.objs->world);
        DG_MovePos(&s03c_dword_800C33AC);
        ReadRotMatrix(&rot);
        NewBullet(&rot, work->side, 0, 1);
        GM_SeSet(&work->control->mov, SE_FAMAS_SHOT);
        NewAnime_8005D604(&rot);
    }
}

void JFamasDie_800CAF20(JFamasWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

int JFamasGetResources_800CAF40(JFamasWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object;

    object = &work->object;

    GM_InitObjectNoRots(object, GV_StrCode("famas"), 0x6D, 0);
    GM_ConfigObjectRoot((OBJECT *)object, parent, num_parent);

    return 0;
}

GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *trigger)
{
    JFamasWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(JFamasWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, JFamasAct_800CAE30, JFamasDie_800CAF20, "jfamas.c");
        if (JFamasGetResources_800CAF40(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->trigger = trigger;
        work->side = 2;
    }

    return &work->actor;
}
