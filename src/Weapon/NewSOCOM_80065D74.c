#include "socom.h"

extern char                 aSocomC[]; // = "socom.c"

extern short                dword_800AB9EC;
extern short                dword_800ABA2C;
extern GameState_800B4D98   gGameState_800B4D98;

extern int                  socom_act_80065518(int a1);
extern int                  socom_kill_80065A94(int a1);
extern void                 GV_DestroyActor_800151C8(struct Actor *pActor);
extern int                  socom_loader_80065B04(Actor_Socom *a1, OBJECT *a2, int a3);

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