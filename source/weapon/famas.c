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
#include "sound/g_sound.h"

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
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    u_long        *flags;
    int            side;
    int            time;
    int            is_mp5;    // Use H&K MP5 (for VERY EASY)
} Work;

STATIC SVECTOR stru_800AB850 = { 5, -500, 80, 0 };

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int is_mp5;
    u_long flags;
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

    GM_CurrentMap = work->root_ctrl->map->index;
    DG_GroupObjsEx(work->obj.objs);

    is_mp5 = work->is_mp5;

    if (work->root_obj->objs->flag & DG_FLAG_INVISIBLE)
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
            GM_SeSet(&work->root_ctrl->mov, SE_KARASHT);
            ctrl1 = work->root_ctrl;
            GM_SetNoise(5, 2, &ctrl1->mov);
        }
    }
    else
    {
        if (newSize > 0 && (flags & 2))
        {
            if ( (work->time & 1) == 0 )
            {
                newSize--;

                DG_SetPos(&work->obj.objs->world);
                DG_MovePos(&stru_800AB850);
                ReadRotMatrix(&mtx);

                GM_Magazine = newSize;
                GM_MagazineMax = MAGAZINE_SIZE;

                if ( !is_mp5 )
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = work->side;
                        v9 = 2;
                        v10 = 0;
                    }
                    else
                    {
                        f54 = work->side;
                        v9 = 0;
                        v10 = 1;
                    }

                    NewBullet(pMtx, f54, v9, v10);
                    --GM_Weapons[WP_Famas];

                    GM_SeSet(&work->root_ctrl->mov, SE_FAMAS_SHOT);
                    ctrl2 = work->root_ctrl;

                    GM_SetNoise(200, 2, &ctrl2->mov);
                    NewAnime_8005D604(&mtx);
                }
                else
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = work->side;
                        v13 = 2;
                        v14 = 0;
                    }
                    else
                    {
                        f54 = work->side;
                        v13 = 0;
                        v14 = 1;
                    }

                    NewBullet(pMtx, f54, v13, v14);
                    GM_SeSet(&work->root_ctrl->mov, SE_MP5_SHOT);
                }

                NewAnime_8005D6BC(&work->obj.objs->world, work->time == 0);
            }

            ++work->time;
        }
        else
        {
            work->time = 0;
        }
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->obj);
}

static int GetResources(Work *work, OBJECT *root_obj, int unit, int is_mp5)
{
    OBJECT_NO_ROTS *obj = &work->obj;
    int id;

    if (is_mp5 == 0)
        id = FAMAS_MODEL;
    else
        id = MP5SD_MODEL;

    GM_InitObjectNoRots(obj, id, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, root_obj, unit);
    return 0;
}

/*---------------------------------------------------------------------------*/

static void *InitFAMAS(CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int is_mp5)
{
    int mag_size;

    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "famas.c");
        if (GetResources(work, root_obj, unit, is_mp5) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->flags = flags;
        work->side = PLAYER_SIDE;
        work->time = 0;
        work->is_mp5 = is_mp5;
    }

    mag_size = MAGAZINE_SIZE;
    if (GM_Magazine)
        mag_size = MAGAZINE_SIZE + 1;   /* +1 in the chamber */

    if (is_mp5 == 0)
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

void *NewFAMAS(CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side)
{
    return InitFAMAS(root_ctrl, root_obj, unit, flags, GM_DifficultyFlag < 0);
}
