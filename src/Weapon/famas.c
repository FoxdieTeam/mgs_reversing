#include "famas.h"
#include "Game/object.h"
#include "map/map.h"

extern char aFamas[];  // = "famas"
extern char aMpfive[]; // = "mpfive"
extern char aFamasC[]; // = "famas.c"

extern short              d_800AB9EC_mag_size;
extern short              d_800ABA2C_ammo;
extern GameState_800B4D98 gGameState_800B4D98;
extern int DG_CurrentGroupID_800AB968;
extern int GV_Clock_800AB920;
extern SVECTOR stru_800AB850;


Actor *anime_create_8005D604(MATRIX *pMtx, GM_Control *not_used1, int not_used2);
void anime_create_8005D6BC(MATRIX *pMtx, int a2);
Actor* bullet_init_80076584(MATRIX *pMtx, int a2, int a3, int noiseLen);

// https://decomp.me/scratch/PEF5G
#pragma INCLUDE_ASM("asm/Weapon/famas_act_80065E90.s") // 760 bytes
void famas_act_80065E90(Actor_Famas *pActor);

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
        int temp = gGameState_800B4D98.field_22_weapon_states[1];
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
    return NewFAMAS_8006623C(a1, a2, num_parent, a4, (unsigned int)gGameState_800B4D98.field_02_diffcultyLevel >> 31);
}
