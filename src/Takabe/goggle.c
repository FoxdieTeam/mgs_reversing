#include "actor.h"
#include "game.h"

extern char aGoggleC[]; // = "goggle.c"

typedef struct _Actor_Goggle
{
    Actor field_0_actor;
    OBJECT f20_obj;
    int f44;
    OBJECT *parent_object;
    int num_parent;
    int f50;
    short f54;
    short f56;
    int f58;
    int f5c;
} Actor_Goggle;


extern int goggle_act_800775B4(int a1);
extern int goggle_kill_800776AC(int a1);
extern void GV_DestroyActor_800151C8(struct Actor *pActor);
extern int  goggle_loader_8007773C(Actor_Goggle *a1, OBJECT *a2);

STATIC_ASSERT_SIZE(Actor_Goggle, 0x60);

#pragma INCLUDE_ASM("asm/Takabe/goggle_8007743C.s")
#pragma INCLUDE_ASM("asm/Takabe/goggle_act_helper_800774C0.s")
#pragma INCLUDE_ASM("asm/Takabe/goggle_act_800775B4.s")
#pragma INCLUDE_ASM("asm/Takabe/goggle_kill_800776AC.s")
#pragma INCLUDE_ASM("asm/Takabe/goggle_loader_8007773C.s")

Actor_Goggle *NewGoggle_8007781C(int a1, OBJECT *parent_obj)
{
    Actor_Goggle *goggle_actor = (Actor_Goggle*)GV_NewActor_800150E4(6, sizeof(Actor_Goggle));

    if (goggle_actor)
    {
        GV_SetNamedActor_8001514C(
            &goggle_actor->field_0_actor,
            (TActorFunction)&goggle_act_800775B4,
            (TActorFunction)&goggle_kill_800776AC,
            aGoggleC);

        if (goggle_loader_8007773C(goggle_actor, parent_obj) < 0)
        {
            GV_DestroyActor_800151C8(&goggle_actor->field_0_actor);
            return 0;
        }
    }
    
    goggle_actor->f44 = a1;
    goggle_actor->f50 = 0;
    
    return goggle_actor;
}
