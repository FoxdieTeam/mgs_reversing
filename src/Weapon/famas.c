#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "Anime/animeconv/anime.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/linkvarbuf.h"
#include "Okajima/bullet.h"
#include "SD/g_sound.h"

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;
extern int   DG_CurrentGroupID_800AB968;
extern int   GV_Clock_800AB920;

/*---------------------------------------------------------------------------*/

typedef struct _FamasWork
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
} FamasWork;

#define EXEC_LEVEL      6
#define MAGAZINE_SIZE   25

STATIC SVECTOR stru_800AB850 = { 5, -500, 80, 0 };

/*---------------------------------------------------------------------------*/

STATIC void FamasAct(FamasWork *work)
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

    GM_CurrentMap_800AB9B0 = work->control->map->index;
    DG_GroupObjs(work->obj.objs, DG_CurrentGroupID_800AB968);

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

    newSize = GM_Magazine_800AB9EC;

    if (!newSize && (flags & 2))
    {
        if (GV_Clock_800AB920)
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

                GM_Magazine_800AB9EC = newSize;
                GM_MagazineMax_800ABA2C = MAGAZINE_SIZE;

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
                    --GM_Weapons[WEAPON_FAMAS];

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

STATIC void FamasDie(FamasWork *work)
{
    GM_FreeObject((OBJECT *)&work->obj);
}

STATIC int FamasGetResources(FamasWork *work, OBJECT *parent, int num_parent, int mp5flag)
{
    OBJECT_NO_ROTS *obj = &work->obj;
    int id;

    if (mp5flag == 0)
        id = GV_StrCode("famas");
    else
        id = GV_StrCode("mpfive");

    GM_InitObjectNoRots(obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    return 0;
}

/*---------------------------------------------------------------------------*/

STATIC GV_ACT *InitFAMAS(CONTROL *control, OBJECT *parent, int num_parent, int *flags, int mp5flag)
{
    int mag_size;

    FamasWork *work = (FamasWork *)GV_NewActor(EXEC_LEVEL, sizeof(FamasWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)FamasAct,
                         (GV_ACTFUNC)FamasDie, "famas.c");
        if (FamasGetResources(work, parent, num_parent, mp5flag) < 0)
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
    if (GM_Magazine_800AB9EC)
        mag_size = MAGAZINE_SIZE + 1;   /* +1 in the chamber */

    if (mp5flag == 0)
    {
        int temp = GM_Weapons[WEAPON_FAMAS];

        if ((mag_size > 0) && (mag_size < temp))
        {
            temp = (short)mag_size;
        }

        GM_MagazineMax_800ABA2C = mag_size;
        GM_Magazine_800AB9EC = temp;
    }
    else
    {
        GM_Magazine_800AB9EC = mag_size;
        GM_MagazineMax_800ABA2C = mag_size;
    }

    return &work->actor;
}

GV_ACT *NewFAMAS(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    return InitFAMAS(control, parent, num_parent, flags, (unsigned int)GM_DifficultyFlag >> 31);
}
