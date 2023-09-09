#include "stngrnd.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "libdg/libdg.h"
#include "unknown.h"
#include "stgfd_io.h"

extern SVECTOR stru_800BDF90;
extern int claymore_map_800AB9DC;
extern SVECTOR DG_ZeroVector_800AB39C;

extern const char animation_data_80012F2C[];
extern const char animation_data_80012F50[];

extern const char aRefrection6[]; // = "refrection6"
extern const char aStngrndC[];    // = "stngrnd.c"

ANIMATION stru_8009F670 = {19692, 1, 1, 1, 1, 500, 3, 800, 800, 128, 0, (void *)animation_data_80012F2C};
ANIMATION stru_8009F68C = {21926, 1, 1, 1, 1, 500, 3, 600, 600, 180, 0, (void *)animation_data_80012F50};

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

void stngrnd_free_80074844(Actor_StunGrenade *pActor, int count)
{
    int i;
    DG_PRIM *pPrim;

    for (i = 0; i < count; i++)
    {
        pPrim = pActor->field_60_pPrims[i];
        if (pPrim)
        {
            DG_DequeuePrim_800182E0(pPrim);
            DG_FreePrim_8001BC04(pPrim);
        }
    }
}

void stngrnd_kill_800748B8(Actor_StunGrenade *pActor)
{
    stngrnd_free_80074844(pActor, 8);
}

int stngrnd_loader_800748D8(Actor_StunGrenade *pActor, MATRIX *pMtx)
{
    DVECTOR xy;
    int sp20[8][2];
    long p;
    long flag;
    int i;
    int val;
    DG_PRIM* pPrim;
    DG_TEX* pTex;

    pActor->field_F4 = 0;

    sp20[0][0] = 8;
    sp20[0][1] = 8;
    sp20[1][0] = 34;
    sp20[1][1] = 11;
    sp20[2][0] = 6;
    sp20[2][1] = 20;
    sp20[3][0] = 25;
    sp20[3][1] = 33;
    sp20[4][0] = 12;
    sp20[4][1] = 37;
    sp20[5][0] = 70;
    sp20[5][1] = 50;
    sp20[6][0] = 11;
    sp20[6][1] = -7;
    sp20[7][0] = 50;
    sp20[7][1] = -9;

    pActor->field_F0_map = GM_CurrentMap_800AB9B0;
    GM_SetCurrentMap(pActor->field_F0_map);

    pActor->field_E0.vx = pMtx->t[0];
    pActor->field_E0.vy = pMtx->t[1];
    pActor->field_E0.vz = pMtx->t[2];

    AN_Stn_G_Sonic_80074CA4(&pActor->field_E0);
    AN_Stn_G_Center_80074D28(&pActor->field_E0);

    NewStnFade_800752A0();

    SetRotMatrix_80093218(&DG_Chanl(0)->field_10_eye_inv);
    SetTransMatrix_80093248(&DG_Chanl(0)->field_10_eye_inv);
    RotTransPers_80093478(&pActor->field_E0, (long *)&xy, &p, &flag);

    for (i = 0; i < 8; i++)
    {
        val = sp20[i][0];
        pActor->field_20[i].y = pActor->field_20[i].x = val / 2;
        pActor->field_20[i].h = pActor->field_20[i].w = val;
        pActor->field_80_array[i] = sp20[i][1];

        stngrnd_800746B4(pActor, i, xy);

        pPrim = DG_GetPrim(0x612, 1, 0, &pActor->field_A0_vecs[i], &pActor->field_20[i]);
        pActor->field_60_pPrims[i] = pPrim;

        if (!pPrim)
        {
            if (i != 0)
            {
                stngrnd_free_80074844(pActor, i - 1);
            }

            return -1;
        }

        pPrim->root = NULL;
        pPrim->field_2E_k500 = 320;

        pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aRefrection6));

        if (!pTex)
        {
            if (i != 0)
            {
                stngrnd_free_80074844(pActor, i - 1);
            }

            return -1;
        }

        stngrnd_loader2_80074644(&pPrim->field_40_pBuffers[0]->poly_ft4, pTex, 30, 30, 30);
        stngrnd_loader2_80074644(&pPrim->field_40_pBuffers[1]->poly_ft4, pTex, 25, 25, 25);
    }

    pActor->field_E8_alive_counter = 15;
    pActor->field_F4 = 1;
    return 0;
}

Actor_StunGrenade * NewStanBlast_80074B5C(MATRIX *pMtx)
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
