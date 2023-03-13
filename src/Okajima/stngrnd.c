#include "stngrnd.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "libdg/libdg.h"

extern ANIMATION stru_8009F670;
extern ANIMATION stru_8009F68C;

extern SVECTOR DG_ZeroVector_800AB39C;

int stngrnd_loader_800748D8(Actor_StunGrenade *pActor, MATRIX *pMtx);

void stngrnd_loader2_80074644(POLY_FT4 *pPoly, DG_TEX *pTexture, int r, int g, int b)
{
    int x, w, y, h;

    setPolyFT4(pPoly);
    setSemiTrans(pPoly, 1);
    setRGB0(pPoly, r, g, b);

    x = pTexture->field_8_offx;
    w = pTexture->field_A_width;
    y = pTexture->field_9_offy;
    h = pTexture->field_B_height;

    setUVWH(pPoly, x, y, w, h);

    pPoly->tpage = pTexture->field_4_tPage;
    pPoly->clut = pTexture->field_6_clut;
}

void stngrnd_800746B4(Actor_StunGrenade *pActor, int idx, DVECTOR vec)
{
    pActor->field_A0_vecs[idx].vx = vec.vx - (vec.vx * pActor->field_80_array[idx]) / 16;
    pActor->field_A0_vecs[idx].vy = vec.vy - (vec.vy * pActor->field_80_array[idx]) / 16;
    pActor->field_A0_vecs[idx].vz = 320;
}

void sub_800790E8();
void sub_8007913C();
void stngrnd_800746B4(Actor_StunGrenade *a1, int a2, DVECTOR a3);

void stngrnd_act_80074730(Actor_StunGrenade *pActor)
{
    DVECTOR screenCoords;
    long interp; // [sp+18h] [-8h] BYREF
    long flag; // [sp+1Ch] [-4h] BYREF
    int i; // $s1
    MATRIX* mtx;

    GM_SetCurrentMap(pActor->field_F0_map);
    
    if ( pActor->field_E8_alive_counter == 15 )
    {
        sub_800790E8();
        GM_GameStatus_800AB3CC |= 2u;
    }
    
    if ( pActor->field_E8_alive_counter == 14 )
    {
        sub_8007913C();
        GM_GameStatus_800AB3CC &= ~2u;
    }

    --pActor->field_E8_alive_counter;

    mtx = &DG_Chanl(0)->field_10_eye_inv;
    SetRotMatrix_80093218(mtx);
    SetTransMatrix_80093248(mtx);
    RotTransPers_80093478(&pActor->field_E0, (u_long *)&screenCoords, &interp, &flag);


    for (i = 0; i < 8; i++)
    {
        stngrnd_800746B4(pActor, i, screenCoords);
    }

    if ( pActor->field_E8_alive_counter <= 0 )
    {
        GV_DestroyActor_800151C8(&pActor->field_0);
    } 
}

void stngrnd_free_80074844(int pActor, int num)
{
    int i;

    for (i = 0; i < num; i++)
    {
        int *a = (int *)pActor;
        DG_PRIM *prim = (DG_PRIM *)a[0x18 + i];
        if (prim)
        {
            DG_DequeuePrim_800182E0(prim);
            DG_FreePrim_8001BC04(prim);
        }
    }
}

void stngrnd_kill_800748B8(Actor_StunGrenade* param_1)
{
    stngrnd_free_80074844((int)param_1, 8);
}

#pragma INCLUDE_ASM("asm/Okajima/stngrnd_loader_800748D8.s") // 644 bytes

extern SVECTOR stru_800BDF90;
extern int GM_NoisePower_800ABA24;
extern int        claymore_map_800AB9DC;

extern const char aStngrndC[];

Actor_StunGrenade* NewStanBlast_80074B5C(MATRIX *pMtx)
{
    Actor_StunGrenade *pActor; // $s0

    if ( (GM_GameStatus_800AB3CC & 2) != 0 )
    {
        return 0;
    }

    pActor = (Actor_StunGrenade *)GV_NewActor_800150E4(5, sizeof(Actor_StunGrenade));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)stngrnd_act_80074730, (TActorFunction)stngrnd_kill_800748B8, aStngrndC);

        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;

        if ( stngrnd_loader_800748D8(pActor, pMtx) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return 0;
        }

        stru_800BDF90 = pActor->field_E0;
        GM_SeSet_80032858(&pActor->field_E0, 41);

        GM_SetNoise(255, 32, &pActor->field_E0);
    }
    return pActor;
}

void AN_Stn_G_Sonic_80074CA4(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F670;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Stn_G_Center_80074D28(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F68C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}
