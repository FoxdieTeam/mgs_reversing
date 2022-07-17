#include "famas.h"
#include "Script_tbl_map_8002BB44.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

extern char aFamas[];   // = "famas"
extern char aMpfive[];  // = "mpfive"
extern char aFamasC[]; // = "famas.c"

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

extern short dword_800AB9EC;
extern short dword_800ABA2C;
extern GameState_800B4D98 gGameState_800B4D98;

extern void GV_DestroyActor_800151C8(struct Actor *pActor);
extern void GV_SetNamedActor_8001514C(Actor *pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown, const char *pActorName);
extern int famas_kill_80065E90(int a1);

#pragma INCLUDE_ASM("asm/Weapon/famas_kill_80065E90.s")

void famas_act_80066188(Actor_Famas *famas)
{
    GM_FreeObject_80034BF8(&famas->f20_obj);
}

int famas_loader_800661A8(Actor_Famas *actor_famas, OBJECT *parent_obj, int num_parent, int flag)
{
    OBJECT *obj = &actor_famas->f20_obj;
    int id;

    if (flag == 0)
        id = GV_Strcode_80016CCC(aFamas);
    else
        id = GV_Strcode_80016CCC(aMpfive);

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Famas *NewFAMAS_8006623C(int a1, OBJECT *parent_obj, int num_parent, int a4, int flag)
{
    int v11;

    Actor_Famas *famas_actor = (Actor_Famas*)GV_NewActor_800150E4(6, sizeof(Actor_Famas));
    if (famas_actor)
    {
        GV_SetNamedActor_8001514C(&famas_actor->field_0_actor, (TActorFunction)&famas_kill_80065E90, (TActorFunction)&famas_act_80066188, aFamasC);
        if (famas_loader_800661A8(famas_actor, parent_obj, num_parent, flag) < 0)
        {
            GV_DestroyActor_800151C8(&famas_actor->field_0_actor);
            return 0;
        }
        
        famas_actor->f44 = a1;
        famas_actor->parent_object = parent_obj;
        famas_actor->num_parent = num_parent;
        famas_actor->f50 = a4;
        famas_actor->f54 = 1;
        famas_actor->f58 = 0;
        famas_actor->f5c = flag;
    }
    
    v11 = 25;
    if (dword_800AB9EC)
        v11 = 26;
    
    if (flag == 0)
    {
        int temp = gGameState_800B4D98.field_22_weapon_states[1];
        if ((v11 > 0) && (v11 < temp))
        {
            temp = (short)v11;
        }
        
        dword_800ABA2C = v11;
        dword_800AB9EC = temp;
    }
    else
    {
        // @note(Voxel): Comments are possibly what is happening here. Suggested by WantedThing.
        dword_800AB9EC = v11;    // Set famas max magazine ammo.
        dword_800ABA2C = v11;    // Set current ammo.
    }
    
    return famas_actor;
}

Actor_Famas *famas_create_80066374(int a1, OBJECT *a2, int num_parent, int a4)
{
    return NewFAMAS_8006623C(a1, a2, num_parent, a4, (unsigned int)gGameState_800B4D98.field_02_diffcultyLevel >> 31);
}
