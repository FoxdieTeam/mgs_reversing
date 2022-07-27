#include "libdg.h"
#include "actor.h"
#include "data.h"

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D604.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D6BC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D988.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DDE0.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DE70.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DF50.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E090.s")
#pragma INCLUDE_ASM("asm/sub_8005E1A0.s")
#pragma INCLUDE_ASM("asm/sub_8005E258.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E334.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E508.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E574.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E6A4.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E774.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E7EC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E9E0.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005EA6C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005EB30.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005EB98.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_0_8005EC1C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_1_8005ED0C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_2_8005ED74.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_3_8005EDDC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_4_8005EE44.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_5_8005EEA4.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_6_8005EF04.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_7_8005EFF8.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_act_helper_8005F094.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_8_8005F0F0.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_9_8005F180.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_10_8005F288.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_11_8005F2F4.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_12_8005F37C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_13_8005F408.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_14_8005F438.s")


void anime_act_helper_8005F46C(SVECTOR *vec, SVECTOR *vec_arr)
{
    vec->vx += vec_arr[1].vx;
    vec->vy += vec_arr[1].vy;
    vec->vz += vec_arr[1].vz;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_act_8005F4AC.s")

void anime_kill_8005F608(int param_1)
{
    DG_OBJS *iVar1;

    iVar1 = *(DG_OBJS **)(param_1 + 0x24);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F644.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F6EC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_8005F994.s")

extern void anime_act_8005F4AC(Actor *param_1,int param_2,int param_3);
extern const char aAnimeC[];

Actor * anime_init_8005FBC8(TActorFreeFunction param_1, char *param_2, struct Anim_Data *param_3)
{
	Actor *pActor;
	int loaded;
	short count;
	
	count = param_3->field_8_count;
	if (pActor = GV_NewActor_800150E4(6,count * 0x3c + 0x4c))
	{
		pActor[2].mFnUpdate = (TActorFunction)((int)pActor + 0x4c + count * 0x34);
		GV_SetNamedActor_8001514C(pActor, (TActorFunction)anime_act_8005F4AC, (TActorFunction)anime_kill_8005F608, aAnimeC);
		loaded = anime_loader_8005F994(pActor,param_2,param_3);
		if (loaded < 0)
		{
			GV_DestroyActor_800151C8(pActor);
			return 0;
		}
		else
		{
			pActor[1].mFreeFunc = param_1;
		}
	}
	return pActor;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005FCA4.s")
