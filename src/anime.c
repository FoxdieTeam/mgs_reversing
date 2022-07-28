#include "anime.h"
#include "GM_Control.h"

Actor_anime * anime_init_8005FBC8(TActorFreeFunction param_1, char *param_2, struct Anim_Data *param_3);

extern SVECTOR DG_ZeroVector_800AB39C;

extern int GV_Time_800AB330;

extern Anim_Data stru_8009F160;
extern Anim_Data stru_8009F17C;

extern Anim_Data stru_8009F208;
extern Anim_Data stru_8009F144;

unsigned int GV_RandU_80017090(unsigned int input);

Actor_anime* anime_create_8005D604(MATRIX *pMtx, GM_Control *not_used1, int not_used2)
{
	signed int rnd; // $v1
    anime_data_0x14 data;

    data.field_0_vec.vx = pMtx->t[0];
    data.field_0_vec.vy = pMtx->t[1];
    data.field_0_vec.vz = pMtx->t[2];
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_10_anim_idx = 0;
    data.field_12 = 0;

    rnd = GV_RandU_80017090(16);
    if ( rnd >= 5 )
    {
        data.field_12 = 2;
    }
    else if (rnd > 0)
    {
        data.field_12 = 1;
    }
    else
    {
        data.field_12 = 0;
    }

    stru_8009F160.field_14 = &data;
    return anime_init_8005FBC8(0, 0, &stru_8009F160);
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D6BC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D988.s")

void anime_create_8005DDE0(MATRIX *pMtx)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec.vx = pMtx->t[0];
    data.field_0_vec.vy = pMtx->t[1];
    data.field_0_vec.vz = pMtx->t[2];
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_10_anim_idx = GV_RandU_80017090(2);
    data.field_12 = 0;
    stru_8009F17C.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F17C);
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DE70.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DF50.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E090.s")
#pragma INCLUDE_ASM("asm/sub_8005E1A0.s")
#pragma INCLUDE_ASM("asm/sub_8005E258.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E334.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E508.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E574.s")

void anime_create_8005E6A4(SVECTOR *pVec)
{
    SVECTOR vec1; // [sp+10h] [-28h] BYREF
    SVECTOR vec2; // [sp+18h] [-20h] BYREF
    anime_data_0x14 data; // [sp+20h] [-18h] BYREF
    
    vec1 = DG_ZeroVector_800AB39C;
    vec1.vy = GV_Time_800AB330 * 128;
    data.field_0_vec = *pVec;

    vec2.vx = 0;
    vec2.vy = GV_RandU_80017090(2) + 10;
    vec2.vz = 2;

    DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &vec1);
    DG_PutVector_8001BE48(&vec2, &data.field_8_vec, 1);
    data.field_10_anim_idx = 0;
    stru_8009F208.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F208);
}

void sub_8005E774(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF
    Anim_Data* p = &stru_8009F144;
    
    data.field_0_vec = *pVec;
    data.field_8_vec.vx = 0;
    data.field_8_vec.vy = 0;
    data.field_8_vec.vz = 0;
    data.field_10_anim_idx = 0;
    data.field_12 = GV_RandU_80017090(4);
    
    p->field_14 = &data;
    anime_init_8005FBC8(0, 0, p);
}

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

extern int anime_loader_8005F994(Actor *pActor, char *param_2, struct Anim_Data *param_3);
extern void anime_act_8005F4AC(Actor *param_1,int param_2,int param_3);
extern const char aAnimeC[];

Actor_anime * anime_init_8005FBC8(TActorFreeFunction param_1, char *param_2, struct Anim_Data *param_3)
{
	Actor *pActor;
	int loaded;
	short count;
	
	count = param_3->field_8_count;
	if ((pActor = GV_NewActor_800150E4(6,count * 0x3c + 0x4c)))
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
	return (Actor_anime*)pActor;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005FCA4.s")
