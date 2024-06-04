#include "stgfd_io.h"
#include "stngrnd.h"
#include "unknown.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"

typedef struct StunGrenadeWork
{
  GV_ACT field_0;
  RECT field_20[8];
  DG_PRIM *field_60_pPrims[8];
  int field_80_array[8];
  SVECTOR field_A0_vecs[8];
  SVECTOR field_E0;
  int field_E8_alive_counter;
  int field_EC;
  int field_F0_map;
  int field_F4;
} StunGrenadeWork;

#define EXEC_LEVEL 5

extern SVECTOR stru_800BDF90;
extern int GM_ClaymoreMap_800AB9DC;
extern SVECTOR DG_ZeroVector_800AB39C;

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

void stngrnd_800746B4(StunGrenadeWork *work, int idx, DVECTOR vec)
{
    work->field_A0_vecs[idx].vx = vec.vx - (vec.vx * work->field_80_array[idx]) / 16;
    work->field_A0_vecs[idx].vy = vec.vy - (vec.vy * work->field_80_array[idx]) / 16;
    work->field_A0_vecs[idx].vz = 320;
}

void StunGrenadeAct_80074730(StunGrenadeWork *work)
{
    DVECTOR screenCoords;
    long interp; // [sp+18h] [-8h] BYREF
    long flag; // [sp+1Ch] [-4h] BYREF
    int i; // $s1
    MATRIX* mtx;

    GM_SetCurrentMap(work->field_F0_map);

    if ( work->field_E8_alive_counter == 15 )
    {
        sub_800790E8();
        GM_GameStatus_800AB3CC |= 2u;
    }

    if ( work->field_E8_alive_counter == 14 )
    {
        sub_8007913C();
        GM_GameStatus_800AB3CC &= ~2u;
    }

    --work->field_E8_alive_counter;

    mtx = &DG_Chanl(0)->field_10_eye_inv;
    SetRotMatrix(mtx);
    SetTransMatrix(mtx);
    RotTransPers(&work->field_E0, (u_long *)&screenCoords, &interp, &flag);

    for (i = 0; i < 8; i++)
    {
        stngrnd_800746B4(work, i, screenCoords);
    }

    if ( work->field_E8_alive_counter <= 0 )
    {
        GV_DestroyActor_800151C8(&work->field_0);
    }
}

void StunGrenadeFree_80074844(StunGrenadeWork *work, int count)
{
    int i;
    DG_PRIM *pPrim;

    for (i = 0; i < count; i++)
    {
        pPrim = work->field_60_pPrims[i];
        if (pPrim)
        {
            DG_DequeuePrim_800182E0(pPrim);
            DG_FreePrim_8001BC04(pPrim);
        }
    }
}

void StunGrenadeDie_800748B8(StunGrenadeWork *work)
{
    StunGrenadeFree_80074844(work, 8);
}

int StunGrenadeGetResources_800748D8(StunGrenadeWork *work, MATRIX *pMtx)
{
    DVECTOR xy;
    int sp20[8][2];
    long p;
    long flag;
    int i;
    int val;
    DG_PRIM* pPrim;
    DG_TEX* pTex;

    work->field_F4 = 0;

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

    work->field_F0_map = GM_CurrentMap_800AB9B0;
    GM_SetCurrentMap(work->field_F0_map);

    work->field_E0.vx = pMtx->t[0];
    work->field_E0.vy = pMtx->t[1];
    work->field_E0.vz = pMtx->t[2];

    AN_Stn_G_Sonic_80074CA4(&work->field_E0);
    AN_Stn_G_Center_80074D28(&work->field_E0);

    NewStnFade_800752A0();

    SetRotMatrix(&DG_Chanl(0)->field_10_eye_inv);
    SetTransMatrix(&DG_Chanl(0)->field_10_eye_inv);
    RotTransPers(&work->field_E0, (long *)&xy, &p, &flag);

    for (i = 0; i < 8; i++)
    {
        val = sp20[i][0];
        work->field_20[i].y = work->field_20[i].x = val / 2;
        work->field_20[i].h = work->field_20[i].w = val;
        work->field_80_array[i] = sp20[i][1];

        stngrnd_800746B4(work, i, xy);

        pPrim = DG_GetPrim(0x612, 1, 0, &work->field_A0_vecs[i], &work->field_20[i]);
        work->field_60_pPrims[i] = pPrim;

        if (!pPrim)
        {
            if (i != 0)
            {
                StunGrenadeFree_80074844(work, i - 1);
            }

            return -1;
        }

        pPrim->root = NULL;
        pPrim->field_2E_k500 = 320;

        pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("refrection6"));

        if (!pTex)
        {
            if (i != 0)
            {
                StunGrenadeFree_80074844(work, i - 1);
            }

            return -1;
        }

        stngrnd_loader2_80074644(&pPrim->packs[0]->poly_ft4, pTex, 30, 30, 30);
        stngrnd_loader2_80074644(&pPrim->packs[1]->poly_ft4, pTex, 25, 25, 25);
    }

    work->field_E8_alive_counter = 15;
    work->field_F4 = 1;
    return 0;
}

GV_ACT *NewStunGrenade_80074B5C(MATRIX *pMtx)
{
    StunGrenadeWork *work; // $s0

    if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_02)
    {
        return 0;
    }

    work = (StunGrenadeWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(StunGrenadeWork));
    if ( work )
    {
        GV_SetNamedActor_8001514C(&work->field_0, (TActorFunction)StunGrenadeAct_80074730, (TActorFunction)StunGrenadeDie_800748B8, "stngrnd.c");

        GM_ClaymoreMap_800AB9DC = GM_CurrentMap_800AB9B0;

        if ( StunGrenadeGetResources_800748D8(work, pMtx) < 0 )
        {
            GV_DestroyActor_800151C8(&work->field_0);
            return 0;
        }

        stru_800BDF90 = work->field_E0;
        GM_SeSet_80032858(&work->field_E0, 41);

        GM_SetNoise(255, 32, &work->field_E0);
    }
    return &work->field_0;
}

const int animation_data_80012F2C[] = {
    0x00011F00, 0x0C000105, 0x010A0400,
    0x02F401F4, 0x0C0D0100, 0x010A0700,
    0x08F401F4, 0x02F0F0F0, 0x0F0D0100
};

ANIMATION stru_8009F670 = {PCX_SONIC, 1, 1, 1, 1, 500, 3, 800, 800, 128, 0, (void *)animation_data_80012F2C};

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

const int animation_data_80012F50[] = {
    0x00011F00, 0x0C000105, 0x020A0500,
    0x02580258, 0x0C0D0100, 0x000A0900,
    0x081E001E, 0x02EEEEEE, 0x0F0D0100
};

ANIMATION stru_8009F68C = {PCX_LENSE_FLARE1, 1, 1, 1, 1, 500, 3, 600, 600, 180, 0, (void *)animation_data_80012F50};

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
