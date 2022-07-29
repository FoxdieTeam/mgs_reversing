#include "anime.h"
#include "GM_Control.h"

Actor* anime_init_8005FBC8(MATRIX *pMtx, int map, Anim_Data *pAnimData);

extern SVECTOR DG_ZeroVector_800AB39C;

extern int GV_Time_800AB330;

extern Anim_Data stru_8009F160;
extern Anim_Data stru_8009F17C;

extern Anim_Data stru_8009F10C;
extern Anim_Data stru_8009F1EC;
extern Anim_Data stru_8009F208;
extern Anim_Data stru_8009F144;

unsigned int GV_RandU_80017090(unsigned int input);
int rand_8008E6B8(void);
void *memset_8008E688(void *pSrc, int value, int len);

extern int GV_Clock_800AB920;

Actor* anime_create_8005D604(MATRIX *pMtx, GM_Control *not_used1, int not_used2)
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

void anime_create_8005E508(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF
    memset_8008E688(&data, 0, sizeof(anime_data_0x14));
    data.field_0_vec = *pVec;
    stru_8009F1EC.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F1EC);
}

//#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E574.s")
void sub_8005E574(MATRIX *pMtx)
{
    SVECTOR vec; // [sp+10h] [-20h] BYREF
    anime_data_0x14 data; // [sp+18h] [-18h] BYREF

    stru_8009F10C.field_14 = &data;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = GV_RandU_80017090(4);
    vec.vx = 0;
    vec.vy = -270;
    vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &data.field_0_vec, 1);
    data.field_10_anim_idx = 0;
    anime_init_8005FBC8(0, 0, &stru_8009F10C);
    vec.vx = 0;
    vec.vy = -370;
    vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &data.field_0_vec, 1);
    data.field_10_anim_idx = 1;
    anime_init_8005FBC8(0, 0, &stru_8009F10C);
    vec.vx = 0;
    vec.vy = -420;
    vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &data.field_0_vec, 1);
    data.field_10_anim_idx = 2;
    anime_init_8005FBC8(0, 0, &stru_8009F10C);
}

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

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_change_prim_8005E7EC.s")
void anime_change_prim_8005E7EC(POLY_FT4 *pPrims, DG_TEX *pTexture, int item_f4, Actor_anime *pActor);


void anime_change_polygon_8005E9E0(Actor_anime *pActor, int idx)
{
    anime_0x34* pItem = &pActor->field_4C_items[0];
    if ( (pActor->field_38_active_buff & (GV_Clock_800AB920 + 1)) != 0 )
    {
        anime_change_prim_8005E7EC(
            &pActor->field_24_pPrim->field_40_pBuffers[GV_Clock_800AB920][idx].poly_ft4,
            pActor->field_20_pTexture,
            pItem->field_4,
            pActor);
        pActor->field_38_active_buff &= ~(GV_Clock_800AB920 + 1);
    }
}
short anime_read_maybe_randomised_short_8005EA6C(unsigned char *pData, int opCode)
{
    const short temp = (pData[1]) | (pData[0] << 8);
    if ( opCode & 0x80 )
    {
        if ( temp < 0 )
        {
            return -(rand_8008E6B8() % -temp);
        }
        else
        {
            return (rand_8008E6B8() % temp);
        }
    }
    return temp;
}

void anime_read_vec_8005EB30(SVECTOR *pVec, unsigned char *pData, int opCode)
{
    pVec->vx = anime_read_maybe_randomised_short_8005EA6C(pData, opCode); 
    pVec->vy = anime_read_maybe_randomised_short_8005EA6C(pData + 2, opCode);
    pVec->vz = anime_read_maybe_randomised_short_8005EA6C(pData + 4, opCode);
}

void anime_adjust_vec_8005EB98(SVECTOR *pVec, unsigned char *pData, int opCode)
{
    pVec->vx += anime_read_maybe_randomised_short_8005EA6C(pData, opCode);
    pVec->vy += anime_read_maybe_randomised_short_8005EA6C(pData + 2, opCode);
    pVec->vz += anime_read_maybe_randomised_short_8005EA6C(pData + 4, opCode);
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_0_8005EC1C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_1_8005ED0C.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_2_8005ED74.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_3_8005EDDC.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_4_8005EE44.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_5_8005EEA4.s")
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_6_8005EF04.s")

int anime_fn_7_8005EFF8(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem; // $a2
    int i; // $a0
    unsigned char *pOpData; // $a1
    unsigned char rgb_incr[3];
    
    pItem = &pActor->field_4C_items[idx];
    pOpData = pItem->field_18_op_code;
 
    for (i = 0; i < 3; i++)
    {
        pOpData++;
        rgb_incr[i] = *pOpData;
    }
    
    pItem->field_10_r += rgb_incr[0];
    pItem->field_11_g += rgb_incr[1];
    pItem->field_12_b += rgb_incr[2];

    pItem->field_18_op_code += 4;

    return 0;
}

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

extern int anime_loader_8005F994(Actor_anime *pActor, int param_2, struct Anim_Data *param_3);
extern void anime_act_8005F4AC(Actor_anime *param_1,int param_2,int param_3);
extern const char aAnimeC[];

Actor* anime_init_8005FBC8(MATRIX *pMtx, int map, Anim_Data *pAnimData)
{
    int count; // $s1
    Actor_anime *pActor; // $v0

    count = pAnimData->field_8_count;
    pActor = (Actor_anime *)GV_NewActor_800150E4(6, ((sizeof(anime_0x34) + sizeof(SVECTOR)) * count) + sizeof(Actor_anime));
    if ( pActor )
    {
        pActor->field_48_pPrimVec = (SVECTOR *)&pActor->field_4C_items[count]; // count vectors after the items
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)anime_act_8005F4AC, (TActorFunction)anime_kill_8005F608, aAnimeC);
        if ( anime_loader_8005F994(pActor, map, pAnimData) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
		else
		{
	        pActor->field_30_mtx = pMtx;
		}
    }
    return &pActor->field_0_actor;
}


#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005FCA4.s")
