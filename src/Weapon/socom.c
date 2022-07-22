#include "socom.h"
#include "game.h"
#include "libdg.h"
#include "actor.h"

extern int dword_800AB824;
int SECTION(".sdata") dword_800AB824;

extern char                 aSocomC[]; // = "socom.c"

extern short                dword_800AB9EC;
extern short                dword_800ABA2C;
extern GameState_800B4D98   gGameState_800B4D98;

extern int                  socom_act_80065518(int a1);
extern int                  socom_loader_80065B04(Actor_Socom *a1, OBJECT *a2, int a3);

extern void                 DG_FreePrim_8001BC04(int param_1);
extern void                 GM_FreeObject_80034BF8(OBJECT *param_1);

#pragma INCLUDE_ASM("asm/Weapon/socom_loader_helper_800651B0.s")
#pragma INCLUDE_ASM("asm/Weapon/socom_act_helper_80065200.s")

void socom_init_vectors_80065254(Actor_Socom *pActor)
{
    int i;
    SVECTOR *pIter;
    pIter = pActor->field_60_array;
    for ( i = 20; i > 0; i-- )
    {
        pIter->vx = 0;
        pIter->vy = -215;
        pIter->vz = 32;
        ++pIter;
    }
}

#pragma INCLUDE_ASM("asm/Weapon/socom_act_helper_8006528C.s")

void socom_init_tiles_80065338(TILE* a1)
{
    TILE* pIter = a1;
    int i;
    for ( i = 2; i > 0; i-- )
    {
        setTile(pIter);
        setRGB0(pIter, 255, 63, 63);
        setWH(pIter, 2, 2);
        pIter++;
    }
}

#pragma INCLUDE_ASM("asm/Weapon/socom_act_helper_80065384.s")

void socom_act_helper_800653B8(Actor_Socom *socom)
{
	int local_var = socom->field_100;
	
	if (local_var == 0) 
    {
		socom->field_10C_pPrim->n_prims = 1;
		(socom->field_110).vy = (short)dword_800AB824;
	}
	else
	{
		socom->field_10C_pPrim->n_prims = 2;
		(socom->field_118).vy = -0xd7 - (short)local_var;
		(socom->field_110).vy = (short)dword_800AB824;
	}
}

#pragma INCLUDE_ASM("asm/Weapon/socom_act_helper_80065408.s")
#pragma INCLUDE_ASM("asm/Weapon/socom_act_80065518.s")

void socom_kill_80065A94(Actor_Socom* a1)
{
    DG_PRIM *field_58_prim;
    DG_PRIM *field_10C_pPrim;

    GM_FreeObject_80034BF8(&a1->field_20);
    field_58_prim = a1->field_58_prim;
    if ( field_58_prim )
    {
        DG_DequeuePrim_800182E0((DG_OBJS *)field_58_prim);
        DG_FreePrim_8001BC04((DG_OBJS *)field_58_prim);
    }

    field_10C_pPrim = a1->field_10C_pPrim;
    if ( field_10C_pPrim )
    {
        DG_DequeuePrim_800182E0((DG_OBJS *)field_10C_pPrim);
        DG_FreePrim_8001BC04((DG_OBJS *)field_10C_pPrim);
    }
}

#pragma INCLUDE_ASM("asm/Weapon/socom_loader_80065B04.s")

Actor_Socom *NewSOCOM_80065D74(void *a1, OBJECT *parentObj, int unit, int a4, int a5)
{
    Actor_Socom *pActor;
    int         mag;
    int         ammo;

    pActor = (Actor_Socom *)GV_NewActor_800150E4(6, sizeof(Actor_Socom));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                (TActorFunction)socom_act_80065518,
                                (TActorFunction)socom_kill_80065A94, aSocomC);
        if (socom_loader_80065B04(pActor, parentObj, unit) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = a1;
        pActor->field_48_parent_object = parentObj;
        pActor->field_4C_obj_idx = unit;
        pActor->field_50_ptr = a4;
        pActor->field_54_bullet_type = a5;
        pActor->field_108 = 0;
        pActor->field_104_rnd = 1;
        pActor->field_100 = 1000;

    }
    mag = 12;
    if (dword_800AB9EC)
    {
        mag++;
    }
    ammo = gGameState_800B4D98.field_22_weapon_states[eSOCOM];
    if (mag > 0 && mag < ammo)
    {
        ammo = mag;
    }
    dword_800ABA2C = mag;
    dword_800AB9EC = ammo;
    return pActor;
}
