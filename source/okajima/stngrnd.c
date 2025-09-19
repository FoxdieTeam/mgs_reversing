#include "stngrnd.h"
#include "stgfd_io.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "sd/g_sound.h"
#include "strcode.h"

extern SVECTOR stru_800BDF90;

/*---------------------------------------------------------------------------*/

typedef struct StunGrenadeWork
{
    GV_ACT      actor;
    RECT        field_20[8];
    DG_PRIM    *field_60_pPrims[8];
    int         field_80_array[8];
    SVECTOR     field_A0_vecs[8];
    SVECTOR     field_E0;
    int         alive_counter;
    int         field_EC;
    int         map;
    int         field_F4;
} StunGrenadeWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

/*---------------------------------------------------------------------------*/

STATIC void stngrnd_loader2_80074644(POLY_FT4 *pPoly, DG_TEX *pTexture, int r, int g, int b)
{
    int x, w, y, h;

    setPolyFT4(pPoly);
    setSemiTrans(pPoly, 1);
    setRGB0(pPoly, r, g, b);

    x = pTexture->off_x;
    w = pTexture->w;
    y = pTexture->off_y;
    h = pTexture->h;

    setUVWH(pPoly, x, y, w, h);

    pPoly->tpage = pTexture->tpage;
    pPoly->clut = pTexture->clut;
}

STATIC void stngrnd_800746B4(StunGrenadeWork *work, int idx, DVECTOR vec)
{
    work->field_A0_vecs[idx].vx = vec.vx - (vec.vx * work->field_80_array[idx]) / 16;
    work->field_A0_vecs[idx].vy = vec.vy - (vec.vy * work->field_80_array[idx]) / 16;
    work->field_A0_vecs[idx].vz = 320;
}

STATIC void stngrnd_Act(StunGrenadeWork *work)
{
    DVECTOR screenCoords;
    long interp;
    long flag;
    int i;
    MATRIX* mtx;

    GM_SetCurrentMap(work->map);

    if ( work->alive_counter == 15 )
    {
        sub_800790E8();
        GM_GameStatus |= STATE_STUN;
    }

    if ( work->alive_counter == 14 )
    {
        sub_8007913C();
        GM_GameStatus &= ~STATE_STUN;
    }

    --work->alive_counter;

    mtx = &DG_Chanl(0)->eye_inv;
    SetRotMatrix(mtx);
    SetTransMatrix(mtx);
    RotTransPers(&work->field_E0, (u_long *)&screenCoords, &interp, &flag);

    for (i = 0; i < 8; i++)
    {
        stngrnd_800746B4(work, i, screenCoords);
    }

    if ( work->alive_counter <= 0 )
    {
        GV_DestroyActor(&work->actor);
    }
}

STATIC void stngrnd_FreePrims(StunGrenadeWork *work, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        GM_FreePrim(work->field_60_pPrims[i]);
    }
}

STATIC void stngrnd_Die(StunGrenadeWork *work)
{
    stngrnd_FreePrims(work, 8);
}

STATIC int stngrnd_GetResources(StunGrenadeWork *work, MATRIX *world)
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

    work->map = GM_CurrentMap;
    GM_SetCurrentMap(work->map);

    work->field_E0.vx = world->t[0];
    work->field_E0.vy = world->t[1];
    work->field_E0.vz = world->t[2];

    AN_Stn_G_Sonic(&work->field_E0);
    AN_Stn_G_Center(&work->field_E0);

    NewStnFade();

    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&work->field_E0, (long *)&xy, &p, &flag);

    for (i = 0; i < 8; i++)
    {
        val = sp20[i][0];
        work->field_20[i].y = work->field_20[i].x = val / 2;
        work->field_20[i].h = work->field_20[i].w = val;
        work->field_80_array[i] = sp20[i][1];

        stngrnd_800746B4(work, i, xy);

        pPrim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_WORLD | DG_PRIM_POLY_FT4, 1, 0, &work->field_A0_vecs[i], &work->field_20[i]);
        work->field_60_pPrims[i] = pPrim;

        if (!pPrim)
        {
            if (i != 0)
            {
                stngrnd_FreePrims(work, i - 1);
            }

            return -1;
        }

        pPrim->root = NULL;
        pPrim->field_2E_k500 = 320;

        pTex = DG_GetTexture(GV_StrCode("refrection6"));

        if (!pTex)
        {
            if (i != 0)
            {
                stngrnd_FreePrims(work, i - 1);
            }

            return -1;
        }

        stngrnd_loader2_80074644(&pPrim->packs[0]->poly_ft4, pTex, 30, 30, 30);
        stngrnd_loader2_80074644(&pPrim->packs[1]->poly_ft4, pTex, 25, 25, 25);
    }

    work->alive_counter = 15;
    work->field_F4 = 1;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewStanBlast(MATRIX *world)
{
    StunGrenadeWork *work;

    if (GM_GameStatus & STATE_STUN)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(StunGrenadeWork));
    if ( work )
    {
        GV_SetNamedActor(&work->actor, stngrnd_Act, stngrnd_Die, "stngrnd.c");

        GM_ClaymoreMap = GM_CurrentMap;

        if ( stngrnd_GetResources(work, world) < 0 )
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        stru_800BDF90 = work->field_E0;
        GM_SeSet(&work->field_E0, SE_EXPLOSION);

        GM_SetNoise(255, 32, &work->field_E0);
    }
    return (void *)work;
}

/*---------------------------------------------------------------------------*/

STATIC const int stun_g_sonic_anim_data[] = {
    0x00011F00, 0x0C000105, 0x010A0400,
    0x02F401F4, 0x0C0D0100, 0x010A0700,
    0x08F401F4, 0x02F0F0F0, 0x0F0D0100
};

STATIC ANIMATION stun_g_sonic_anim = {
    PCX_SONIC,                      // texture_hash
    1,                              //
    1,                              //
    1,                              // n_anims
    1,                              // n_vertices
    500,                            //
    3,                              //
    800,                            // xw
    800,                            // yh
    128,                            // rgb
    NULL,                           // pre_script
    (void *)stun_g_sonic_anim_data  // ptr
};

void AN_Stn_G_Sonic(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stun_g_sonic_anim;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

STATIC const int stun_g_center_anim_data[] = {
    0x00011F00, 0x0C000105, 0x020A0500,
    0x02580258, 0x0C0D0100, 0x000A0900,
    0x081E001E, 0x02EEEEEE, 0x0F0D0100
};

STATIC ANIMATION stun_g_center_anim = {
    PCX_LENSE_FLARE1,               // texture_hash
    1,                              //
    1,                              //
    1,                              // n_anims
    1,                              // n_vertices
    500,                            //
    3,                              //
    600,                            // xw
    600,                            // yh
    180,                            // rgb
    NULL,                           // pre_script
    (void *)stun_g_center_anim_data // ptr
};

void AN_Stn_G_Center(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stun_g_center_anim;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}
