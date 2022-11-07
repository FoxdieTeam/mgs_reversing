#include "anime.h"
#include "Game/GM_Control.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "Game/game.h"

extern SVECTOR DG_ZeroVector_800AB39C;

extern int GV_Time_800AB330;

extern Anim_Data stru_8009F10C;
extern Anim_Data stru_8009F144;
extern Anim_Data stru_8009F160;
extern Anim_Data stru_8009F17C;
extern Anim_Data stru_8009F1EC;
extern Anim_Data stru_8009F208;

extern int        GV_Clock_800AB920;
extern const char aScriptActErr[];
extern const char aAnimeC[];

extern TAnimeVMFn anime_fn_table_8009F228[];

Actor *anime_create_8005D604(MATRIX *pMtx, GM_Control *not_used1)
{
    signed int      rnd; // $v1
    anime_data_0x14 data;

    data.field_0_vec.vx = pMtx->t[0];
    data.field_0_vec.vy = pMtx->t[1];
    data.field_0_vec.vz = pMtx->t[2];
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_10_anim_idx = 0;
    data.field_12 = 0;

    rnd = GV_RandU_80017090(16);
    if (rnd >= 5)
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

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D6BC.s") // 716 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D988.s") // 1112 bytes

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

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DE70.s") // 224 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DF50.s") // 320 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E090.s")          // 272 bytes
#pragma INCLUDE_ASM("asm/sub_8005E1A0.s")                          // 184 bytes
#pragma INCLUDE_ASM("asm/sub_8005E258.s")                          // 220 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E334.s") // 468 bytes

void anime_create_8005E508(SVECTOR *pVec)
{
    anime_data_0x14 data = {{ 0 }}; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    stru_8009F1EC.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F1EC);
}

void sub_8005E574(MATRIX *pMtx)
{
    SVECTOR         vec;  // [sp+10h] [-20h] BYREF
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
    SVECTOR         vec1; // [sp+10h] [-28h] BYREF
    SVECTOR         vec2; // [sp+18h] [-20h] BYREF
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
    Anim_Data      *p = &stru_8009F144;

    data.field_0_vec = *pVec;
    data.field_8_vec.vx = 0;
    data.field_8_vec.vy = 0;
    data.field_8_vec.vz = 0;
    data.field_10_anim_idx = 0;
    data.field_12 = GV_RandU_80017090(4);

    p->field_14 = &data;
    anime_init_8005FBC8(0, 0, p);
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_change_prim_8005E7EC.s") // 500 bytes

void anime_change_polygon_8005E9E0(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[0];
    if ((pActor->field_38_active_buff & (GV_Clock_800AB920 + 1)) != 0)
    {
        anime_change_prim_8005E7EC(&pActor->field_24_pPrim->field_40_pBuffers[GV_Clock_800AB920][idx].poly_ft4,
                                   pActor->field_20_pTexture, pItem->field_4, pActor);
        pActor->field_38_active_buff &= ~(GV_Clock_800AB920 + 1);
    }
}

short anime_read_maybe_randomised_short_8005EA6C(unsigned char *pData, int opCode)
{
    const short temp = (pData[1]) | (pData[0] << 8);
    if (opCode & 0x80)
    {
        if (temp < 0)
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

int anime_fn_0_8005EC1C(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem;   // $s0
    int         next_op; // $v1

    pItem = &pActor->field_4C_items[idx];
    next_op = pItem->field_18_op_code[1];
    if (next_op == 255)
    {
        pItem->field_4++;
        if (pItem->field_4 >= pActor->field_3E_maybe_data_count)
        {
            pItem->field_4 = 0;
        }
    }
    else
    {
        if (next_op == 254)
        {
            next_op = rand_8008E6B8() % pActor->field_3E_maybe_data_count;
        }
        pItem->field_4 = next_op;
    }
    pActor->field_38_active_buff = 3;
    pItem->field_18_op_code += 2;
    return 0;
}

int anime_fn_1_8005ED0C(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    pItem->field_0_counter =
        anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 3;
    return 1;
}

int anime_fn_2_8005ED74(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    anime_read_vec_8005EB30(&pActor->field_48_pPrimVec[idx], pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_3_8005EDDC(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    anime_adjust_vec_8005EB98(&pActor->field_48_pPrimVec[idx], pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_4_8005EE44(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    anime_read_vec_8005EB30(&pItem->field_8_vec, pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_5_8005EEA4(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    anime_adjust_vec_8005EB98(&pItem->field_8_vec, pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_6_8005EF04.s") // 244 bytes

int anime_fn_7_8005EFF8(Actor_anime *pActor, int idx)
{
    anime_0x34    *pItem;   // $a2
    int            i;       // $a0
    unsigned char *pOpData; // $a1
    unsigned char  rgb_incr[3];

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

void anime_act_helper_8005F094(Actor_anime *pActor)
{
    int               i;          // $a1
    union Prim_Union *pPrimStart; // $v1
    anime_0x34       *pOffIter;   // $a0
    POLY_FT4         *pPrim;      // $v1

    pPrimStart = pActor->field_24_pPrim->field_40_pBuffers[GV_Clock_800AB920];
    pPrim = &pPrimStart->poly_ft4;
    pOffIter = &pActor->field_4C_items[0];

    for (i = pActor->field_42_count; i > 0; i--)
    {
        setRGB0(pPrim, pOffIter->field_10_r, pOffIter->field_11_g, pOffIter->field_12_b);
        pPrim++;
        pOffIter++;
    }
}

int anime_fn_8_8005F0F0(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[idx];
    short       value = anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, 0);
    DG_SetTmpLight_8001A114(&pActor->field_48_pPrimVec[idx], 512, value);
    pItem->field_18_op_code += 3;
    return 0;
}

int anime_fn_9_8005F180(Actor_anime *pActor, int idx)
{
    int            i;                 // $s2
    anime_0x34    *pItem;             // $s3
    unsigned char *opCode_pos;        // $s0
    short          rect_wh_offset[2]; // [sp+10h] [-8h] BYREF
    RECT          *pRect;

    pItem = &pActor->field_4C_items[idx];
    opCode_pos = pItem->field_18_op_code + 1;
    for (i = 0; i < 2; i++)
    {
        rect_wh_offset[i] = anime_read_maybe_randomised_short_8005EA6C(opCode_pos, 0);
        opCode_pos += 2;
    }

    pRect = &pActor->field_28_prim_rect;
    pRect->w += rect_wh_offset[0];
    pRect->h += rect_wh_offset[1];
    pRect->x = pRect->w / 2;
    pRect->y = pRect->h / 2;
    pItem->field_18_op_code += 5;
    return 0;
}

int anime_fn_10_8005F288(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem; // $s0

    pItem = &pActor->field_4C_items[idx];
    GM_SeSet_80032858(&pActor->field_48_pPrimVec[idx], pItem->field_18_op_code[1]);
    pItem->field_18_op_code += 2;
    return 0;
}

int anime_fn_11_8005F2F4(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem;                           // $s0
    int         maybe_randomised_short_8005EA6C; // $v0
    int         new_idx;                         // $a0

    pItem = &pActor->field_4C_items[idx];
    maybe_randomised_short_8005EA6C = anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, 0);
    pItem->field_13++;
    new_idx = pItem->field_13;
    pItem->field_18_op_code += 3;
    pItem->field_1C[new_idx] = maybe_randomised_short_8005EA6C;
    pItem->field_24_saved_op_code[new_idx] = pItem->field_18_op_code;
    return 0;
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_fn_12_8005F37C.s") // 140 bytes

int anime_fn_13_8005F408(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem; // $a2
    pItem = &pActor->field_4C_items[idx];
    pItem->field_18_op_code = pItem->field_14;
    return 1;
}

int anime_fn_14_8005F438(Actor_anime *pActor, int idx)
{
    DG_InvisiblePrim(pActor->field_24_pPrim);
    GV_DestroyActor_800151C8(&pActor->field_0_actor);
    return 1;
}

void anime_act_helper_8005F46C(SVECTOR *pVec, anime_0x34 *pItem)
{
    pVec->vx += pItem->field_8_vec.vx;
    pVec->vy += pItem->field_8_vec.vy;
    pVec->vz += pItem->field_8_vec.vz;
}

void anime_act_8005F4AC(Actor_anime *pActor)
{
    anime_0x34  *pItemsIter;        // $s0
    SVECTOR     *field_48_pPrimVec; // $s3
    int          i;                 // $s1
    unsigned int script_op_code;    // $v1
    int          opCodeRet;         // $v0

    pItemsIter = pActor->field_4C_items;
    pActor->field_24_pPrim->type &= ~0x100u;
    field_48_pPrimVec = pActor->field_48_pPrimVec;
    for (i = 0; i < pActor->field_42_count; ++i)
    {
        if (pItemsIter->field_0_counter <= 0)
        {
            while (1)
            {
                script_op_code = *pItemsIter->field_18_op_code & 0x7F;
                if (script_op_code > 15)
                {
                    mts_nullsub_8_8008BB98(1, aScriptActErr); //  SCRIPT ACT ERR!! \n
                    GV_DestroyActor_800151C8(&pActor->field_0_actor);
                    break;
                }
                opCodeRet = anime_fn_table_8009F228[script_op_code - 1](pActor, i);
                if (opCodeRet)
                {
                    break;
                }
            }
        }
        anime_act_helper_8005F46C(field_48_pPrimVec, pItemsIter);
        anime_change_polygon_8005E9E0(pActor, i);
        ++field_48_pPrimVec;
        --pItemsIter->field_0_counter;
        ++pItemsIter;
    }
    anime_act_helper_8005F094(pActor);
    GM_CurrentMap_800AB9B0 = pActor->field_34_map;
    if (pActor->field_30_mtx)
    {
        DG_SetPos_8001BC44(pActor->field_30_mtx);
        DG_PutPrim_8001BE00(&pActor->field_24_pPrim->world);
    }
}

void anime_kill_8005F608(Actor_anime *anime)
{
    DG_OBJS *objs = (DG_OBJS *)anime->field_24_pPrim;
    if (objs)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F644.s") // 168 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F6EC.s") // 680 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_8005F994.s")        // 564 bytes

Actor *anime_init_8005FBC8(MATRIX *pMtx, int map, Anim_Data *pAnimData)
{
    int          count;  // $s1
    Actor_anime *pActor; // $v0

    count = pAnimData->field_8_count;
    pActor =
        (Actor_anime *)GV_NewActor_800150E4(6, ((sizeof(anime_0x34) + sizeof(SVECTOR)) * count) + sizeof(Actor_anime));
    if (pActor)
    {
        pActor->field_48_pPrimVec = (SVECTOR *)&pActor->field_4C_items[count]; // count vectors after the items
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)anime_act_8005F4AC,
                                  (TActorFunction)anime_kill_8005F608, aAnimeC);
        if (anime_loader_8005F994(pActor, map, pAnimData) < 0)
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

#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005FCA4.s") // 132 bytes
