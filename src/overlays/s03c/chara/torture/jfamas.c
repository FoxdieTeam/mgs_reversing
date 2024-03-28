#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Okajima/bullet.h"
#include "Anime/animeconv/anime.h"

typedef struct JFamasWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *field_44;
    OBJECT        *parent;
    int            num_parent;
    int           *field_50;
    int            field_54;
} JFamasWork;

#define EXEC_LEVEL 5

SVECTOR s03c_dword_800C33AC = {5, 65036, 80};

extern int DG_CurrentGroupID_800AB968;

void JFamasAct_800CAE30(JFamasWork *work)
{
    MATRIX rot;
    int    field_50;

    GM_SetCurrentMap(work->field_44->field_2C_map->field_0_map_index_bit);
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID_800AB968);

    field_50 = *work->field_50;

    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
    }

    if (field_50 & 2)
    {
        DG_SetPos_8001BC44(&work->object.objs->world);
        DG_MovePos_8001BD20(&s03c_dword_800C33AC);
        ReadRotMatrix(&rot);
        bullet_init_80076584(&rot, work->field_54, 0, 1);
        GM_SeSet_80032858(&work->field_44->field_0_mov, 48);
        anime_create_8005D604(&rot);
    }
}

void JFamasDie_800CAF20(JFamasWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->object);
}

int JFamasGetResources_800CAF40(JFamasWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object;

    object = &work->object;

    GM_InitObjectNoRots_800349B0(object, GV_StrCode_80016CCC("famas"), 0x6D, 0);
    GM_ConfigObjectRoot_80034C5C((OBJECT *)object, parent, num_parent);

    return 0;
}

GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *arg4)
{
    JFamasWork *work;

    work = (JFamasWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(JFamasWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)JFamasAct_800CAE30, (TActorFunction)JFamasDie_800CAF20,
                                  "jfamas.c");
        if (JFamasGetResources_800CAF40(work, parent, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_44 = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->field_50 = arg4;
        work->field_54 = 2;
    }

    return &work->actor;
}
