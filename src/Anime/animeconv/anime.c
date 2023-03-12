#include "anime.h"
#include "Game/GM_Control.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "map/map.h"

extern SVECTOR DG_ZeroVector_800AB39C;

extern int GV_Time_800AB330;

extern ANIMATION stru_8009F10C;
extern ANIMATION stru_8009F144;
extern ANIMATION stru_8009F160;
extern ANIMATION stru_8009F17C;
extern ANIMATION stru_8009F1EC;
extern ANIMATION stru_8009F208;

extern int        GV_Clock_800AB920;
extern const char aScriptActErr[];
extern const char aAnimeC[];

extern TAnimeVMFn anime_fn_table_8009F228[];

Actor_anime * anime_create_8005D604(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    int rnd;

    pre.pos.vx = pMtx->t[0]; pre.pos.vy = pMtx->t[1]; pre.pos.vz = pMtx->t[2];
    pre.speed = DG_ZeroVector_800AB39C;

    pre.scr_num = 0;
    pre.s_anim = 0;

    rnd = GV_RandU_80017090(16);
    if (rnd >= 5)
    {
        pre.s_anim = 2;
    }
    else if (rnd > 0)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &stru_8009F160;
    anm->field_14_pre_script = &pre;

    return NewAnime_8005FBC8( NULL, 0, anm );
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D6BC.s") // 716 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005D988.s") // 1112 bytes

void anime_create_8005DDE0(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos.vx = pMtx->t[0];
    pre.pos.vy = pMtx->t[1];
    pre.pos.vz = pMtx->t[2];
    pre.speed = DG_ZeroVector_800AB39C;

    pre.scr_num = GV_RandU_80017090(2);
    pre.s_anim = 0;

    anm = &stru_8009F17C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DE70.s") // 224 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005DF50.s") // 320 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/sub_8005E090.s")          // 272 bytes
#pragma INCLUDE_ASM("asm/sub_8005E1A0.s")                          // 184 bytes
#pragma INCLUDE_ASM("asm/sub_8005E258.s")                          // 220 bytes
#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_create_8005E334.s") // 468 bytes

void anime_create_8005E508(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &stru_8009F1EC;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8005E574(MATRIX *pMtx)
{
    ANIMATION *anm;
    SVECTOR    vec;
    PRESCRIPT  pre;

    anm = &stru_8009F10C;
    anm->field_14_pre_script = &pre;

    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = GV_RandU_80017090(4);

    vec.vx = 0; vec.vy = -270; vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &pre.pos, 1);
    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    vec.vx = 0; vec.vy = -370; vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &pre.pos, 1);
    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    vec.vx = 0; vec.vy = -420; vec.vz = 0;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&vec, &pre.pos, 1);
    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005E6A4(SVECTOR *pos)
{
    ANIMATION *anm;
    SVECTOR    rotation;
    SVECTOR    speed;
    PRESCRIPT  pre;

    rotation = DG_ZeroVector_800AB39C;
    rotation.vy = GV_Time_800AB330 * 128;

    pre.pos = *pos;

    speed.vx = 0;
    speed.vy = GV_RandU_80017090(2) + 10;
    speed.vz = 2;

    DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rotation);
    DG_PutVector_8001BE48(&speed, &pre.speed, 1);

    pre.scr_num = 0;

    anm = &stru_8009F208;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( 0, 0, anm );
}

void sub_8005E774(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    anm = &stru_8009F144;

    pre.pos = *pos;
    pre.speed.vx = 0;
    pre.speed.vy = 0;
    pre.speed.vz = 0;

    pre.scr_num = 0;
    pre.s_anim = GV_RandU_80017090(4);

    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( 0, 0, anm );
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_change_prim_8005E7EC.s") // 500 bytes

void anime_change_polygon_8005E9E0(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem = &pActor->field_4C_items[0];
    if ((pActor->field_38_active_buff & (GV_Clock_800AB920 + 1)) != 0)
    {
        anime_change_prim_8005E7EC(
            &((POLY_FT4 *)pActor->field_24_pPrim->field_40_pBuffers[GV_Clock_800AB920])[idx],
            pActor->field_20_pTexture, pItem->field_4, pActor
        );
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

int anime_fn_6_8005EF04(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem;
    int i;
    POLY_FT4 *pPoly;

    pItem = &pActor->field_4C_items[idx];
    pActor->field_40_data_C = pItem->field_18_op_code[1];

    if ((pActor->field_40_data_C & ~0x3) == 0)
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &pActor->field_24_pPrim->field_40_pBuffers[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 1);

            pPoly->tpage &= ~0x60;
            pPoly->tpage |= pActor->field_40_data_C << 5;
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &pActor->field_24_pPrim->field_40_pBuffers[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 0);
        }
    }

    pItem->field_18_op_code += 2;
    return 0;
}

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

int anime_fn_12_8005F37C(Actor_anime *pActor, int idx)
{
    anime_0x34 *pItem;
    int temp_a1;
    short *temp_v1;

    pItem = &pActor->field_4C_items[idx];
    temp_a1 = pItem->field_13;
    temp_v1 = (short *)pItem + temp_a1; // TODO: figure out what's happening here

    if (--temp_v1[14] <= 0)
    {
        if (temp_v1[14] == 0)
        {
            pItem->field_13--;
            pItem->field_18_op_code++;
        }
        else
        {
            pItem->field_18_op_code = pItem->field_24_saved_op_code[temp_a1];
        }
    }
    else
    {
        pItem->field_18_op_code = pItem->field_24_saved_op_code[temp_a1];
    }

    return 0;
}

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
    DG_VisiblePrim(pActor->field_24_pPrim);

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
    DG_PRIM *prim = anime->field_24_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F644.s") // 168 bytes
int anime_loader_helper_8005F644(Actor_anime *pActor, ANIMATION *pAnimation);

#pragma INCLUDE_ASM("asm/Anime/animeconv/anime_loader_helper_8005F6EC.s") // 680 bytes
void anime_loader_helper_8005F6EC(Actor_anime *pActor, char rgb);

int anime_loader_8005F994(Actor_anime *pActor, int map, ANIMATION *pAnimation)
{
    int count;
    PRESCRIPT *pPrescript;
    int i;
    RECT *pRect;
    anime_0x34 *pItem;

    pActor->field_38_active_buff = 3;
    pActor->field_34_map = map;
    pActor->field_3A_data_2 = pAnimation->field_2;
    pActor->field_3C_data_4 = pAnimation->field_4;
    pActor->field_3E_maybe_data_count = pAnimation->field_6;
    pActor->field_40_data_C = pAnimation->field_C;

    count = pAnimation->field_8_count;
    pActor->field_42_count = count;
    pActor->field_44_data_A = pAnimation->field_A;

    pPrescript = pAnimation->field_14_pre_script;

    for (i = 0; i < count; i++)
    {
        pActor->field_48_pPrimVec[i] = pPrescript->pos;
        pPrescript++;
    }

    pRect = &pActor->field_28_prim_rect;
    pRect->x = pAnimation->field_E_xw / 2;
    pRect->y = pAnimation->field_10_yh / 2;
    pRect->w = pAnimation->field_E_xw;
    pRect->h = pAnimation->field_10_yh;

    pActor->field_24_pPrim = DG_GetPrim(0x412, count, 0, pActor->field_48_pPrimVec, pRect);
    if (!pActor->field_24_pPrim)
    {
        return -1;
    }

    pActor->field_20_pTexture = DG_GetTexture_8001D830(pAnimation->field_0_texture_hash);

    pItem = pActor->field_4C_items;
    pPrescript = pAnimation->field_14_pre_script;

    for (i = 0; i < count; i++)
    {
        pItem->field_0_counter = 0;
        pItem->field_4 = pPrescript->s_anim;
        pItem->field_8_vec = pPrescript->speed;
        pItem->field_10_r = pItem->field_11_g = pItem->field_12_b = pAnimation->field_12_rgb;
        pItem->field_13 = 0xFF;

        pItem++;
        pPrescript++;
    }

    anime_loader_helper_8005F6EC(pActor, pAnimation->field_12_rgb);
    DG_InvisiblePrim(pActor->field_24_pPrim);

    if (anime_loader_helper_8005F644(pActor, pAnimation) < 0)
    {
        return -1;
    }

    return 0;
}

Actor_anime *NewAnime_8005FBC8(MATRIX *pMtx, int map, ANIMATION *pAnimData)
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
            return NULL;
        }
        else
        {
            pActor->field_30_mtx = pMtx;
        }
    }
    return pActor;
}

Actor_anime *sub_8005FCA4(DG_PRIM *pPrim, int map, ANIMATION *pAnimData)
{
    Actor_anime *pActor = NewAnime_8005FBC8(NULL, map, pAnimData);

    if (pActor && pPrim)
    {
        pActor->field_24_pPrim->world = pPrim->world;
    }

    return pActor;
}
