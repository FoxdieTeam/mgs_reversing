#include "common.h"
#include "strcode.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

const char animation_data_800124A8[] = {
    0x00, 0x8b, 0x03, 0x00, 0x09, 0x00, 0x34, 0x00, 0x64, 0x01, 0xfe, 0x02, 0x00, 0x01, 0x0c, 0x00,
    0x08, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x04, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x0a, 0xff, 0xf6, 0xff, 0xf6, 0x02,
    0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0xff, 0xf6, 0xff, 0xf6, 0x02, 0x00, 0x01, 0x0c, 0x00,
    0x10, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x04, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x0a, 0xff, 0xf6, 0xff, 0xf6, 0x02,
    0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0x00, 0x1e, 0x00, 0x1e, 0x02, 0x00, 0x01, 0x0c, 0x00,
    0x10, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x04, 0x01, 0xff, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00, 0x00, 0x0a, 0xff, 0xf6, 0xff, 0xf6, 0x02,
    0x00, 0x01, 0x0d, 0x0f
};

ANIMATION stru_8009F0D4 = {PCX_WT_SUD11, 2, 2, 4, 1, 0, 5, 50, 50, 250, 0, (char *)animation_data_800124A8};

const char animation_data_8001253C[] = {
    0x00, 0x83, 0x04, 0x00, 0x0b, 0x00, 0x33, 0x00, 0x5a, 0x00, 0x74, 0x01, 0xfe, 0x01, 0xff, 0x08,
    0x01, 0x01, 0x01, 0x0c, 0x00, 0x05, 0x08, 0x02, 0x02, 0x02, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x14, 0x01, 0xff, 0x0a, 0x00, 0x1e, 0x00, 0x1e, 0x08, 0xfe, 0xfe, 0xfe, 0x02, 0x00,
    0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0xfe, 0xd4, 0xfe, 0xd4, 0x0c, 0x00, 0x05, 0x08, 0x02, 0x02,
    0x02, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x14, 0x01, 0xff, 0x0a, 0x00, 0x1e, 0x00,
    0x1e, 0x08, 0xfe, 0xfe, 0xfe, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0xff, 0x9c, 0xff,
    0x9c, 0x0c, 0x00, 0x0e, 0x0a, 0xff, 0xfe, 0xff, 0xfe, 0x08, 0xfe, 0xfe, 0xfe, 0x01, 0xff, 0x02,
    0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0x01, 0xf4, 0x01, 0xf4, 0x0c, 0x00, 0x1d, 0x0a, 0x00,
    0x14, 0x00, 0x14, 0x08, 0xff, 0xff, 0xff, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F0F0 = {PCX_SMOKE, 8, 4, 30, 1, 300, 1, 400, 400, 32, 0, (char *)animation_data_8001253C};

const char animation_data_800125CC[] = {
    0x00, 0x1d, 0x03, 0x00, 0x09, 0x00, 0x10, 0x00, 0x1b, 0x09, 0x03, 0xe8, 0x02, 0x00, 0x01, 0x0f,
    0x07, 0x03, 0x0a, 0xff, 0x38, 0xff, 0x38, 0x02, 0x00, 0x01, 0x0f, 0x07, 0x03, 0x0a, 0xfe, 0xfc,
    0xfe, 0xfc, 0x02, 0x00, 0x01, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F10C = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (char *)animation_data_800125CC};

const char animation_data_800125F4[] = {
    0x00, 0x1d, 0x03, 0x00, 0x09, 0x00, 0x10, 0x00, 0x1b, 0x09, 0x03, 0xe8, 0x02, 0x00, 0x01, 0x0f,
    0x07, 0x03, 0x0a, 0xfd, 0xa8, 0xfd, 0xa8, 0x02, 0x00, 0x01, 0x0f, 0x07, 0x03, 0x0a, 0xfc, 0x7c,
    0xfc, 0x7c, 0x02, 0x00, 0x01, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F128 = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 1400, 1400, 128, 0, (char *)animation_data_800125F4};

const char animation_data_8001261C[] = {
    0x00, 0x04, 0x01, 0x00, 0x05, 0x02, 0x00, 0x01, 0x0f, 0x00, 0x00, 0x00
};

ANIMATION stru_8009F144 = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (char *)animation_data_8001261C};

const char animation_data_80012628[] = {
    0x00, 0x07, 0x01, 0x00, 0x05, 0x09, 0x03, 0xe8, 0x02, 0x00, 0x01, 0x0f,
};

ANIMATION stru_8009F160 = {PCX_FA_FL10, 2, 2, 3, 1, 300, 1, 600, 600, 100, 0, (char *)animation_data_80012628};

const char animation_data_80012634[] = {
    0x00, 0xcb, 0x02, 0x00, 0x07, 0x00, 0x79, 0x0c, 0x00, 0x0b, 0x06, 0x00, 0x00, 0xff, 0xec, 0x00,
    0x00, 0x02, 0x00, 0x01, 0x0d, 0x0b, 0x2b, 0x05, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x86, 0xff,
    0xf6, 0x00, 0x01, 0xff, 0xf6, 0x86, 0x00, 0x0a, 0x00, 0x01, 0x00, 0x0a, 0x0c, 0x00, 0x04, 0x01,
    0xff, 0x02, 0x00, 0x01, 0x0d, 0x06, 0x00, 0x00, 0xff, 0xd8, 0x00, 0x00, 0x0c, 0x00, 0x04, 0x01,
    0xff, 0x02, 0x00, 0x01, 0x0d, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x02, 0x01,
    0xff, 0x0b, 0x2b, 0x02, 0x00, 0x02, 0x0d, 0x0c, 0x00, 0x02, 0x01, 0xff, 0x02, 0x00, 0x02, 0x0d,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x08, 0xd8, 0xd8, 0xd8, 0x0c, 0x00, 0x04,
    0x08, 0xf0, 0xf0, 0xf0, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x0c, 0x00, 0x0b, 0x06, 0x00, 0x00, 0xff,
    0xec, 0x00, 0x00, 0x02, 0x00, 0x01, 0x0d, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0xff,
    0xec, 0x00, 0x01, 0xff, 0xec, 0x86, 0x00, 0x14, 0x00, 0x01, 0x00, 0x14, 0x0c, 0x00, 0x02, 0x01,
    0xff, 0x0b, 0x2b, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x04, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x04, 0x01, 0xff, 0x02, 0x00, 0x02, 0x0d, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x01, 0x08, 0xd8, 0xd8, 0xd8, 0x0c, 0x00, 0x04, 0x08, 0xf0, 0xf0, 0xf0, 0x02, 0x00, 0x01,
    0x0d, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F17C = {PCX_MAGAZIN, 2, 2, 4, 1, 200, 5, 100, 100, 128, 0, (char *)animation_data_80012634};

const char animation_data_80012708[] = {
    0x00, 0x19, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x14, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x0a, 0x01, 0xff, 0x08, 0xf9, 0xf9, 0xf9, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x00, 0x00,
};

ANIMATION stru_8009F198 = {PCX_SMOKE, 8, 4, 30, 8, 0, 3, 2200, 2200, 77, 0, (char *)animation_data_80012708};

const char animation_data_80012728[] = {
    0x00, 0x23, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x0a, 0x01, 0xff, 0x0a, 0x00, 0x50, 0x00,
    0x50, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x05, 0x0a, 0x00, 0x50, 0x00, 0x50, 0x01, 0xff, 0x08,
    0xf2, 0xf2, 0xf2, 0x02, 0x00, 0x01, 0x0d, 0x0f,
};

ANIMATION stru_8009F1B4 = {PCX_SMOKE, 8, 4, 30, 1, 0, 1, 1000, 1000, 77, 0, (char *)animation_data_80012728};

const char animation_data_80012750[] = {
    0x00, 0x4a, 0x02, 0x00, 0x07, 0x00, 0x20, 0x01, 0xfe, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x02, 0x00,
    0x01, 0x0d, 0x0c, 0x00, 0x0a, 0x01, 0xff, 0x08, 0xf4, 0xf4, 0xf4, 0x02, 0x00, 0x01, 0x0d, 0x0f,
    0x01, 0xfe, 0x0c, 0x00, 0x04, 0x0a, 0x01, 0x2c, 0x01, 0x2c, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x0a, 0x0a, 0x00, 0x46, 0x00, 0x46, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x0a, 0x01, 0xff, 0x0a, 0x00, 0x50, 0x00, 0x50, 0x08, 0xe7, 0xe7, 0xe7, 0x02, 0x00, 0x01, 0x0d,
    0x0f, 0x00, 0x00, 0x00,
};

ANIMATION stru_8009F1D0 = {PCX_SMOKE, 8, 4, 30, 4, 0, 1, 2200, 2200, 128, 0, (char *)animation_data_80012750};

const char animation_data_800127A4[] = {
    0x00, 0x27, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x0a, 0x00, 0x64, 0x00,
    0x64, 0x08, 0xf6, 0xf6, 0xf6, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x0a, 0x00,
    0xc8, 0x00, 0xc8, 0x08, 0xf3, 0xf3, 0xf3, 0x02, 0x00, 0x01, 0x0d, 0x0f,
};

ANIMATION stru_8009F1EC = {PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 400, 400, 128, 0, (char *)animation_data_800127A4};

const char animation_data_800127D0[] = {
    0x00, 0x39, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x14, 0x01, 0xff, 0x0a, 0x00, 0x01, 0x00,
    0x01, 0x08, 0x05, 0x05, 0x05, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x0c, 0x01, 0xff, 0x0a, 0x00,
    0x05, 0x00, 0x05, 0x08, 0xfb, 0xfb, 0xfb, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x0a, 0x01, 0xff,
    0x0a, 0x00, 0x0a, 0x00, 0x0a, 0x08, 0xfb, 0xfb, 0xfb, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F208 = {PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 30, 30, 10, 0, (char *)animation_data_800127D0};

int dword_8009F224 = 0;

/*---------------------------------------------------------------------------*/

void *NewAnime_8005D604(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    int rnd;

    pre.pos.vx = pMtx->t[ 0 ]; pre.pos.vy = pMtx->t[ 1 ]; pre.pos.vz = pMtx->t[ 2 ];
    pre.speed = DG_ZeroVector;

    pre.scr_num = 0;
    pre.s_anim = 0;

    rnd = GV_RandU(16);
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
    anm->pre_script = &pre;

    return NewAnime( NULL, 0, anm );
}

void NewAnime_8005D6BC(MATRIX *arg0, int arg1)
{
    PRESCRIPT pre;
    MATRIX sp28;
    SVECTOR sp48;
    int mod, mod2;
    ANIMATION *anm;
    PRESCRIPT *pPre;
    SVECTOR *pSpeed;
    int rand;

    pPre = &pre;
    pSpeed = &pre.speed;

    pPre->pos.vx = arg0->t[ 0 ];
    pPre->pos.vy = arg0->t[ 1 ];
    pPre->pos.vz = arg0->t[ 2 ];

    mod = 3;
    mod2 = 5;

    if (((dword_8009F224 % mod) == 0) || (arg1 != 0))
    {
        sp48.vx = GV_RandU(32) - 100;
        sp48.vy = GV_RandU(16) - 10;
        sp48.vz = GV_RandU(16) + 40;

        DG_SetPos(arg0);
        DG_MovePos(&sp48);
        ReadRotMatrix(&sp28);

        pSpeed->vx = sp28.t[ 0 ] - arg0->t[ 0 ];
        pSpeed->vy = sp28.t[ 1 ] - arg0->t[ 1 ];
        pSpeed->vz = sp28.t[ 2 ] - arg0->t[ 2 ];

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = pPre;

        NewAnime( NULL, 0, anm );
    }

    rand = GV_RandU(8);

    if (((rand > 3) && (GM_PlayerStatus == (PLAYER_MOVE | PLAYER_ATTACK))) ||
        ((((dword_8009F224 % mod2) == 0) || (arg1 != 0)) && (GM_PlayerStatus != (PLAYER_MOVE | PLAYER_ATTACK))))
    {
        pPre = &pre;

        sp48.vx = 0;
        sp48.vy = 0;
        sp48.vz = 0;

        DG_SetPos(arg0);
        DG_MovePos(&sp48);
        ReadRotMatrix(&sp28);

        pPre->pos.vx = sp28.t[ 0 ];
        pPre->pos.vy = sp28.t[ 1 ];
        pPre->pos.vz = sp28.t[ 2 ];

        sp48.vx = 0;
        sp48.vy = -10;
        sp48.vz = GV_RandU(8);

        pSpeed = &pre.speed;

        DG_MovePos(&sp48);
        ReadRotMatrix(&sp28);

        pSpeed->vx = sp28.t[ 0 ] - pPre->pos.vx;
        pSpeed->vy = sp28.t[ 1 ] - pPre->pos.vy;
        pSpeed->vz = sp28.t[ 2 ] - pPre->pos.vz;

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime( NULL, 0, anm );
    }

#ifndef VR_EXE
    if (dword_8009F224++ >= ((mod2 * mod) - 1))
    {
        dword_8009F224 = 0;
    }
#endif
}

void NewAnime_8005D988(MATRIX *pMatrix1, MATRIX *pMatrix2, int mode)
{
    PRESCRIPT  prescript;
    MATRIX     m;
    SVECTOR    move;
    int        randu;
    ANIMATION *anm;
    SVECTOR   *pos;
    SVECTOR   *speed;

    pos = &prescript.pos;

    move.vx = 0;
    move.vy = -130;
    move.vz = 0;

    DG_SetPos(pMatrix1);
    DG_MovePos(&move);
    ReadRotMatrix(&m);

    pos->vx = m.t[ 0 ];
    pos->vy = m.t[ 1 ];
    pos->vz = m.t[ 2 ];

    move.vx = GV_RandU(32) - 100;
    move.vy = GV_RandU(32) + 15;
    move.vz = GV_RandU(64) + 100;

    DG_MovePos(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[ 0 ] - pos->vx;
    speed->vy = m.t[ 1 ] - pos->vy;
    speed->vz = m.t[ 2 ] - pos->vz;
    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm = &stru_8009F0D4;
    stru_8009F0D4.pre_script = &prescript;

    NewAnime(NULL, 0, anm);

    if (mode != 1)
    {
        prescript.speed = DG_ZeroVector;

        randu = GV_RandU(16);
        if (randu >= 7)
        {
            prescript.s_anim = 3;
        }
        else if (randu >= 5)
        {
            prescript.s_anim = 2;
        }
        else if (randu >= 3)
        {
            prescript.s_anim = 1;
        }
        else
        {
            prescript.s_anim = 0;
        }

        anm = &stru_8009F10C;
        anm->pre_script = &prescript;

        move.vx = 0;
        move.vy = -270;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[ 0 ];
        pos->vy = m.t[ 1 ];
        pos->vz = m.t[ 2 ];

        prescript.scr_num = 0;
        NewAnime(NULL, 0, anm);

        move.vx = 0;
        move.vy = -370;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[ 0 ];
        pos->vy = m.t[ 1 ];
        pos->vz = m.t[ 2 ];

        prescript.scr_num = 1;
        NewAnime(NULL, 0, anm);

        move.vx = 0;
        move.vy = -420;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[ 0 ];
        pos->vy = m.t[ 1 ];
        pos->vz = m.t[ 2 ];

        prescript.scr_num = 2;
        NewAnime(NULL, 0, anm);
    }
    else
    {
        DG_SetPos(pMatrix2);

        move.vx = 0;
        move.vy = 0;
        move.vz = 0;

        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[ 0 ];
        pos->vy = m.t[ 1 ];
        pos->vz = m.t[ 2 ];

        move.vx = 0;
        move.vy = -10;
        move.vz = GV_RandU(8);

        DG_MovePos(&move);
        ReadRotMatrix(&m);

        speed->vx = m.t[ 0 ] - pos->vx;
        speed->vy = m.t[ 1 ] - pos->vy;
        speed->vz = m.t[ 2 ] - pos->vz;

        prescript.scr_num = 2;

        anm = &stru_8009F0F0;
        anm->pre_script = &prescript;

        NewAnime(NULL, 0, anm);
    }

    DG_SetPos(pMatrix1);

    pos = &prescript.pos;

    move.vx = 0;
    move.vy = 0;
    move.vz = 0;

    DG_MovePos(&move);
    ReadRotMatrix(&m);

    pos->vx = m.t[ 0 ];
    pos->vy = m.t[ 1 ];
    pos->vz = m.t[ 2 ];

    move.vx = 0;
    move.vy = 0;
    move.vz = GV_RandU(8);

    DG_MovePos(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[ 0 ] - pos->vx;
    speed->vy = m.t[ 1 ] - pos->vy;
    speed->vz = m.t[ 2 ] - pos->vz;
    prescript.scr_num = 0;

    anm = &stru_8009F0F0;
    anm->pre_script = &prescript;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005DDE0(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos.vx = pMtx->t[ 0 ];
    pre.pos.vy = pMtx->t[ 1 ];
    pre.pos.vz = pMtx->t[ 2 ];
    pre.speed = DG_ZeroVector;

    pre.scr_num = GV_RandU(2);
    pre.s_anim = 0;

    anm = &stru_8009F17C;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005DE70(MATRIX *rotation)
{
    SVECTOR    sp10;
    SVECTOR    sp18;
    MATRIX     rot;
    PRESCRIPT  pre;
    ANIMATION *anm;

    rot = *rotation;

    sp10.vx = 0;
    sp10.vy = -1500;
    sp10.vz = 0;

    ApplyMatrixSV(&rot, &sp10, &sp18);

    pre.pos.vx = rotation->t[ 0 ] + sp18.vx;
    pre.pos.vy = rotation->t[ 1 ] + sp18.vy;
    pre.pos.vz = rotation->t[ 2 ] + sp18.vz;
    pre.speed.vx = 0;
    pre.speed.vy = 0;
    pre.speed.vz = 0;
    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &stru_8009F1B4;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005DF50(SVECTOR *arg0, SVECTOR *arg1)
{
    SVECTOR   sp10;
    SVECTOR   sp18;
    PRESCRIPT pres[4];
    int       i;

    sp18.vx = arg1->vx;
    sp18.vy = arg1->vy - 448;
    sp18.vz = arg1->vz;

    sp10.vx = 0;
    sp10.vy = 30;

    for (i = 0; i < 3; i++)
    {
        sp10.vz = GV_RandU(64) + 150;
        pres[ i ].pos = *arg0;
        sp18.vy += 128;

        DG_SetPos2(arg0, &sp18);
        DG_RotVector(&sp10, &pres[ i ].speed, 1);

        pres[ i ].scr_num = 0;
        pres[ i ].s_anim = 0;
    }

    pres[3].pos = *arg0;
    pres[3].speed = DG_ZeroVector;
    pres[3].scr_num = 1;
    pres[3].s_anim = 0;

    stru_8009F1D0.pre_script = pres;
    NewAnime( NULL, 0, &stru_8009F1D0 );
}

void NewAnime_8005E090(SVECTOR *pPos)
{
    SVECTOR axis;
    SVECTOR speed_in;
    SVECTOR speed_out;
    MATRIX rot;
    PRESCRIPT pres[8];
    int i;
    ANIMATION *anm;

    axis.vx = 0;
    axis.vz = 0;
    speed_in.vx = 0;
    speed_in.vy = 0;

    for (i = 0; i < 8; i++)
    {
        axis.vy = i * 512;
        speed_in.vz = GV_RandS(16) + 40;

        pres[ i ].s_anim = 0;
        pres[ i ].pos = *pPos;
        pres[ i ].scr_num = 0;

        RotMatrixYXZ(&axis, &rot);
        ApplyMatrixSV(&rot, &speed_in, &speed_out);

        pres[ i ].speed.vx = speed_out.vx;
        pres[ i ].speed.vy = speed_out.vy;
        pres[ i ].speed.vz = speed_out.vz;
    }

    anm = &stru_8009F198;
    anm->pre_script = pres;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005E1A0(MATRIX *arg0)
{
    PRESCRIPT  pre;
    int        rnd;
    ANIMATION *anm;

    pre.pos.vx = arg0->t[ 0 ];
    pre.pos.vy = arg0->t[ 1 ];
    pre.pos.vz = arg0->t[ 2 ];
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = 0;

    rnd = GV_RandU(16);

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

    anm = &stru_8009F10C;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005E258(MATRIX *pMatrix)
{
    SVECTOR   vec1, vec2;
    MATRIX    m;
    PRESCRIPT prescript;

    m = *pMatrix;
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0;
    ApplyMatrixSV(&m, &vec1, &vec2);
    prescript.pos.vx = pMatrix->t[ 0 ] + vec2.vx;
    prescript.pos.vy = pMatrix->t[ 1 ] + vec2.vy;
    prescript.pos.vz = pMatrix->t[ 2 ] + vec2.vz;
    prescript.speed.vx = 0;
    prescript.speed.vy = 0;
    prescript.speed.vz = 0;
    prescript.scr_num = 0;
    prescript.s_anim = 0;
    stru_8009F1B4.pre_script = &prescript;
    NewAnime(NULL, 0, &stru_8009F1B4);
}

void NewAnime_8005E334(MATRIX *rotation)
{
    PRESCRIPT  pre;
    SVECTOR    translation;
    MATRIX     rot;
    int        rnd;
    PRESCRIPT *pPre;
    ANIMATION *anm;

    pPre = &pre;
    pPre->speed = DG_ZeroVector;

    rnd = GV_RandU(16);

    if (rnd >= 7)
    {
        pre.s_anim = 3;
    }
    else if (rnd >= 5)
    {
        pre.s_anim = 2;
    }
    else if (rnd >= 3)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &stru_8009F128;
    anm->pre_script = &pre;

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 300;

    DG_SetPos(rotation);
    DG_MovePos(&translation);
    ReadRotMatrix(&rot);

    pPre->pos.vx = rot.t[ 0 ];
    pPre->pos.vy = rot.t[ 1 ];
    pPre->pos.vz = rot.t[ 2 ];

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 750;

    DG_SetPos(rotation);
    DG_MovePos(&translation);
    ReadRotMatrix(&rot);

    pPre->pos.vx = rot.t[ 0 ];
    pPre->pos.vy = rot.t[ 1 ];
    pPre->pos.vz = rot.t[ 2 ];

    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 990;

    DG_SetPos(rotation);
    DG_MovePos(&translation);
    ReadRotMatrix(&rot);

    pPre->pos.vx = rot.t[ 0 ];
    pPre->pos.vy = rot.t[ 1 ];
    pPre->pos.vz = rot.t[ 2 ];

    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );
}

void NewAnime_8005E508(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &stru_8009F1EC;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005E574(MATRIX *pMtx)
{
    ANIMATION *anm;
    SVECTOR    vec;
    PRESCRIPT  pre;

    anm = &stru_8009F10C;
    anm->pre_script = &pre;

    pre.speed = DG_ZeroVector;
    pre.s_anim = GV_RandU(4);

    vec.vx = 0; vec.vy = -270; vec.vz = 0;
    DG_SetPos(pMtx);
    DG_PutVector(&vec, &pre.pos, 1);
    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    vec.vx = 0; vec.vy = -370; vec.vz = 0;
    DG_SetPos(pMtx);
    DG_PutVector(&vec, &pre.pos, 1);
    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    vec.vx = 0; vec.vy = -420; vec.vz = 0;
    DG_SetPos(pMtx);
    DG_PutVector(&vec, &pre.pos, 1);
    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );
}

void NewAnime_8005E6A4(SVECTOR *pos)
{
    ANIMATION *anm;
    SVECTOR    rot;
    SVECTOR    speed;
    PRESCRIPT  pre;

    rot = DG_ZeroVector;
    rot.vy = GV_Time * 128;

    pre.pos = *pos;

    speed.vx = 0;
    speed.vy = GV_RandU(2) + 10;
    speed.vz = 2;

    DG_SetPos2(&DG_ZeroVector, &rot);
    DG_PutVector(&speed, &pre.speed, 1);

    pre.scr_num = 0;

    anm = &stru_8009F208;
    anm->pre_script = &pre;

    NewAnime( 0, 0, anm );
}

void NewAnime_8005E774(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    anm = &stru_8009F144;

    pre.pos = *pos;
    pre.speed.vx = 0;
    pre.speed.vy = 0;
    pre.speed.vz = 0;

    pre.scr_num = 0;
    pre.s_anim = GV_RandU(4);

    anm->pre_script = &pre;

    NewAnime( 0, 0, anm );
}
