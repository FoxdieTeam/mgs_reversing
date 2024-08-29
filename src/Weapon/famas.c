#include "famas.h"
#include "Anime/animeconv/anime.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/linkvarbuf.h"
#include "Okajima/bullet.h"

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;
extern int   DG_CurrentGroupID_800AB968;
extern int   GV_Clock_800AB920;

SVECTOR stru_800AB850 = { 5, -500, 80, 0 };

void famas_act_80065E90(FamasWork *work)
{
    int field_5C_mp5;
    int flags;
    CONTROL *pCtrl;

    int newSize;
    int v9;
    int v10;
    CONTROL *control;

    int v13;
    int v14;
    int f54;
    MATRIX mtx;
    MATRIX *pMtx;

    GM_CurrentMap_800AB9B0 = work->control->map->index;
    DG_GroupObjs(work->obj.objs, DG_CurrentGroupID_800AB968);

    field_5C_mp5 = work->field_5C_mp5;

    if (work->parent_object->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->obj.objs);
    }
    else
    {
        DG_VisibleObjs(work->obj.objs);
    }

    flags = *work->field_50_pFlags;

    newSize = GM_Magazine_800AB9EC;

    if (!newSize && (flags & 2))
    {
        if (GV_Clock_800AB920)
        {
            GM_SeSet_80032858(&work->control->mov, 4);
            pCtrl = work->control;
            GM_SetNoise(5, 2, &pCtrl->mov);
        }
    }
    else
    {
        if (newSize > 0 && (flags & 2))
        {
            if ( (work->field_58_counter & 1) == 0 )
            {
                newSize--;

                DG_SetPos_8001BC44(&work->obj.objs->world);
                DG_MovePos_8001BD20(&stru_800AB850);
                ReadRotMatrix(&mtx);

                GM_Magazine_800AB9EC = newSize;
                GM_MagazineMax_800ABA2C = 25;

                if ( !field_5C_mp5 )
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

                    bullet_init_80076584(pMtx, f54, v9, v10);
                    --GM_Weapons[WEAPON_FAMAS];

                    GM_SeSet_80032858(&work->control->mov, 48);
                    control = work->control;

                    GM_SetNoise(200, 2, &control->mov);
                    anime_create_8005D604(&mtx);
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

                    bullet_init_80076584(pMtx, f54, v13, v14);
                    GM_SeSet_80032858(&work->control->mov, 101);
                }

                anime_create_8005D6BC(&work->obj.objs->world, work->field_58_counter == 0);
            }

            ++work->field_58_counter;
        }
        else
        {
            work->field_58_counter = 0;
        }
    }
}

void famas_die_80066188(FamasWork *famas)
{
    GM_FreeObject_80034BF8((OBJECT *)&famas->obj);
}

int famas_loader_800661A8(FamasWork *actor_famas, OBJECT *parent_obj, int num_parent, int flag)
{
    OBJECT_NO_ROTS *obj = &actor_famas->obj;
    int     id;

    if (flag == 0)
        id = GV_StrCode_80016CCC("famas");
    else
        id = GV_StrCode_80016CCC("mpfive");

    GM_InitObjectNoRots_800349B0(obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, parent_obj, num_parent);
    return 0;
}

GV_ACT *NewFAMAS_body_8006623C(CONTROL *control, OBJECT *parent_obj, int num_parent, int* arg3, int flag)
{
    int v11;

    FamasWork *famas_actor = (FamasWork *)GV_NewActor_800150E4(6, sizeof(FamasWork));
    if (famas_actor)
    {
        GV_SetNamedActor_8001514C(&famas_actor->actor, (TActorFunction)famas_act_80065E90,
                                  (TActorFunction)famas_die_80066188, "famas.c");
        if (famas_loader_800661A8(famas_actor, parent_obj, num_parent, flag) < 0)
        {
            GV_DestroyActor_800151C8(&famas_actor->actor);
            return 0;
        }

        famas_actor->control = control;
        famas_actor->parent_object = parent_obj;
        famas_actor->num_parent = num_parent;
        famas_actor->field_50_pFlags = arg3;
        famas_actor->field_54 = 1;
        famas_actor->field_58_counter = 0;
        famas_actor->field_5C_mp5 = flag;
    }

    v11 = 25;
    if (GM_Magazine_800AB9EC)
        v11 = 26;

    if (flag == 0)
    {
        int temp = GM_Weapons[WEAPON_FAMAS];

        if ((v11 > 0) && (v11 < temp))
        {
            temp = (short)v11;
        }

        GM_MagazineMax_800ABA2C = v11;
        GM_Magazine_800AB9EC = temp;
    }
    else
    {
        // @note(Voxel): Comments are possibly what is happening here. Suggested by WantedThing.
        GM_Magazine_800AB9EC = v11; // Set famas max magazine ammo.
        GM_MagazineMax_800ABA2C = v11;      // Set current ammo.
    }

    return &famas_actor->actor;
}

GV_ACT *NewFAMAS_80066374(CONTROL *control, OBJECT *obj, int num_parent, unsigned int* arg3, int side)
{
    return NewFAMAS_body_8006623C(control, obj, num_parent, arg3, (unsigned int)GM_DifficultyFlag >> 31);
}
