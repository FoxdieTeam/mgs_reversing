#include "famas.h"
#include "Anime/animeconv/anime.h"
#include "Game/object.h"
#include "map/map.h"
#include "unknown.h"

extern char aFamas[];  // = "famas"
extern char aMpfive[]; // = "mpfive"
extern char aFamasC[]; // = "famas.c"

extern short     d_800AB9EC_mag_size;
extern short     d_800ABA2C_ammo;
extern int       DG_CurrentGroupID_800AB968;
extern int       GV_Clock_800AB920;
extern SVECTOR   stru_800AB850;

extern short gGameState_800B4D98[0x60];
extern short gGcl_gameStateVars_800B44C8[0x60];

void famas_act_80065E90(Actor_Famas *pActor)
{
    int field_5C_mp5;
    int flags;
    GM_Control *pCtrl;

    int newSize;
    int v9;
    int v10;
    GM_Control *field_44_pCtrl;

    int v13;
    int v14;
    int f54;
    MATRIX mtx;
    MATRIX *pMtx;

    GM_CurrentMap_800AB9B0 = pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;
    DG_GroupObjs(pActor->f20_obj.objs, DG_CurrentGroupID_800AB968);

    field_5C_mp5 = pActor->field_5C_mp5;

    if (pActor->parent_object->objs->flag & 0x80)
    {
        pActor->f20_obj.objs->flag |= 0x80u;
    }
    else
    {
        pActor->f20_obj.objs->flag &= ~0x80u;
    }

    flags = *pActor->field_50_pFlags;

    newSize = d_800AB9EC_mag_size;

    if (!newSize && (flags & 2))
    {
        if (GV_Clock_800AB920)
        {
            GM_SeSet_80032858(&pActor->field_44_pCtrl->field_0_position, 4);
            pCtrl = pActor->field_44_pCtrl;
            GM_SetNoise(5, 2, &pCtrl->field_0_position);
        }
    }
    else
    {
        if (newSize > 0 && (flags & 2))
        {
            if ( (pActor->field_58_counter & 1) == 0 )
            {
                newSize--;

                DG_SetPos_8001BC44(&pActor->f20_obj.objs->world);
                DG_MovePos_8001BD20(&stru_800AB850);
                ReadRotMatrix_80092DD8(&mtx);

                d_800AB9EC_mag_size = newSize;
                d_800ABA2C_ammo = 25;

                if ( !field_5C_mp5 )
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = pActor->field_54;
                        v9 = 2;
                        v10 = 0;
                    }
                    else
                    {
                        f54 = pActor->field_54;
                        v9 = 0;
                        v10 = 1;
                    }

                    bullet_init_80076584(pMtx, f54, v9, v10);
                    *GM_WeaponFamas -= 1;

                    GM_SeSet_80032858(&pActor->field_44_pCtrl->field_0_position, 48);
                    field_44_pCtrl = pActor->field_44_pCtrl;

                    GM_SetNoise(200, 2, &field_44_pCtrl->field_0_position);
                    anime_create_8005D604(&mtx, field_44_pCtrl);
                }
                else
                {
                    pMtx = &mtx;

                    if ( newSize < 3 )
                    {
                        f54 = pActor->field_54;
                        v13 = 2;
                        v14 = 0;
                    }
                    else
                    {
                        f54 = pActor->field_54;
                        v13 = 0;
                        v14 = 1;
                    }

                    bullet_init_80076584(pMtx, f54, v13, v14);
                    GM_SeSet_80032858(&pActor->field_44_pCtrl->field_0_position, 101);
                }

                anime_create_8005D6BC(&pActor->f20_obj.objs->world, pActor->field_58_counter == 0);
            }

            ++pActor->field_58_counter;
        }
        else
        {
            pActor->field_58_counter = 0;
        }
    }
}

void famas_die_80066188(Actor_Famas *famas)
{
    GM_FreeObject_80034BF8(&famas->f20_obj);
}

int famas_loader_800661A8(Actor_Famas *actor_famas, OBJECT *parent_obj, int num_parent, int flag)
{
    OBJECT *obj = &actor_famas->f20_obj;
    int     id;

    if (flag == 0)
        id = GV_StrCode_80016CCC(aFamas);
    else
        id = GV_StrCode_80016CCC(aMpfive);

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Famas *NewFAMAS_8006623C(GM_Control* a1, OBJECT *parent_obj, int num_parent, int* a4, int flag)
{
    int v11;

    Actor_Famas *famas_actor = (Actor_Famas *)GV_NewActor_800150E4(6, sizeof(Actor_Famas));
    if (famas_actor)
    {
        GV_SetNamedActor_8001514C(&famas_actor->field_0_actor, (TActorFunction)famas_act_80065E90,
                                  (TActorFunction)famas_die_80066188, aFamasC);
        if (famas_loader_800661A8(famas_actor, parent_obj, num_parent, flag) < 0)
        {
            GV_DestroyActor_800151C8(&famas_actor->field_0_actor);
            return 0;
        }

        famas_actor->field_44_pCtrl = a1;
        famas_actor->parent_object = parent_obj;
        famas_actor->num_parent = num_parent;
        famas_actor->field_50_pFlags = a4;
        famas_actor->field_54 = 1;
        famas_actor->field_58_counter = 0;
        famas_actor->field_5C_mp5 = flag;
    }

    v11 = 25;
    if (d_800AB9EC_mag_size)
        v11 = 26;

    if (flag == 0)
    {
        int temp = *GM_WeaponFamas;

        if ((v11 > 0) && (v11 < temp))
        {
            temp = (short)v11;
        }

        d_800ABA2C_ammo = v11;
        d_800AB9EC_mag_size = temp;
    }
    else
    {
        // @note(Voxel): Comments are possibly what is happening here. Suggested by WantedThing.
        d_800AB9EC_mag_size = v11; // Set famas max magazine ammo.
        d_800ABA2C_ammo = v11;      // Set current ammo.
    }

    return famas_actor;
}

Actor_Famas *famas_create_80066374(GM_Control* a1, OBJECT *a2, int num_parent, int* a4)
{
    return NewFAMAS_8006623C(a1, a2, num_parent, a4, (unsigned int)gGameState_800B4D98[GM_Difficulty] >> 31);
}
