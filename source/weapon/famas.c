#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/bullet.h"
#include "sd/g_sound.h"

extern int   DG_CurrentGroupID;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define FAMAS_MODEL     GV_StrCode("famas")
#define MP5SD_MODEL     GV_StrCode("mpfive")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define MAGAZINE_SIZE   25

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS obj;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    int           *flags;
    int            field_54;
    int            counter;
    int            mp5_flag;    // Use H&K MP5 (for VERY EASY)
} Work;

STATIC SVECTOR stru_800AB850 = { 5, -500, 80, 0 };

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int mp5_flag;
    int flags;
    CONTROL *ctrl1;

    int newSize;
    int v9;
    int v10;
    CONTROL *ctrl2;

    int v13;
    int v14;
    int f54;
    MATRIX mtx;
    MATRIX *pMtx;

    GM_CurrentMap = work->control->map->index;
    DG_GroupObjs(work->obj.objs, DG_CurrentGroupID);

    mp5_flag = work->mp5_flag;

    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->obj.objs);
    }
    else
    {
        DG_VisibleObjs(work->obj.objs);
    }

    flags = *work->flags;

    newSize = GM_Magazine;

    if (!newSize && (flags & 2))
    {
        if (GV_Clock)
        {
            GM_SeSet(&work->control->mov, SE_KARASHT);
            ctrl1 = work->control;
            GM_SetNoise(5, 2, &ctrl1->mov);
        }
    }
    else
    {
        if (newSize > 0 && (flags & 2))
        {
            if ( (work->counter & 1) == 0 )
            {
                newSize--;

                DG_SetPos(&work->obj.objs->world);
                DG_MovePos(&stru_800AB850);
                ReadRotMatrix(&mtx);

                GM_Magazine = newSize;
                GM_MagazineMax = MAGAZINE_SIZE;

                if ( !mp5_flag )
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = work->field_54;
                        v9 = 2;
                        v10 = 0;
                    }
                    else
                    {
                        f54 = work->field_54;
                        v9 = 0;
                        v10 = 1;
                    }

                    NewBullet(pMtx, f54, v9, v10);
                    --GM_Weapons[WP_Famas];

                    GM_SeSet(&work->control->mov, SE_FAMAS_SHOT);
                    ctrl2 = work->control;

                    GM_SetNoise(200, 2, &ctrl2->mov);
                    NewAnime_8005D604(&mtx);
                }
                else
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = work->field_54;
                        v13 = 2;
                        v14 = 0;
                    }
                    else
                    {
                        f54 = work->field_54;
                        v13 = 0;
                        v14 = 1;
                    }

                    NewBullet(pMtx, f54, v13, v14);
                    GM_SeSet(&work->control->mov, SE_MP5_SHOT);
                }

                NewAnime_8005D6BC(&work->obj.objs->world, work->counter == 0);
            }

            ++work->counter;
        }
        else
        {
            work->counter = 0;
        }
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->obj);
}

static int GetResources(Work *work, OBJECT *parent, int num_parent, int mp5flag)
{
    OBJECT_NO_ROTS *obj = &work->obj;
    int id;

    if (mp5flag == 0)
        id = FAMAS_MODEL;
    else
        id = MP5SD_MODEL;

    GM_InitObjectNoRots(obj, id, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    return 0;
}

/*---------------------------------------------------------------------------*/

static void *InitFAMAS(CONTROL *control, OBJECT *parent, int num_parent, int *flags, int mp5flag)
{
    int mag_size;

    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "famas.c");
        if (GetResources(work, parent, num_parent, mp5flag) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->field_54 = 1;
        work->counter = 0;
        work->mp5_flag = mp5flag;
    }

    mag_size = MAGAZINE_SIZE;
    if (GM_Magazine)
        mag_size = MAGAZINE_SIZE + 1;   /* +1 in the chamber */

    if (mp5flag == 0)
    {
        int temp = GM_Weapons[WP_Famas];

        if ((mag_size > 0) && (mag_size < temp))
        {
            temp = (short)mag_size;
        }

        GM_MagazineMax = mag_size;
        GM_Magazine = temp;
    }
    else
    {
        GM_Magazine = mag_size;
        GM_MagazineMax = mag_size;
    }

    return (void *)work;
}

void *NewFAMAS(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    return InitFAMAS(control, parent, num_parent, flags, (unsigned int)GM_DifficultyFlag >> 31);
}
