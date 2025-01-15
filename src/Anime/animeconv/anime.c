#include "anime.h"

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/map.h"
#include "strcode.h"

extern int     GV_Clock;
extern int     GM_PlayerStatus;

/*---------------------------------------------------------------------------*/

typedef struct AnimeItem
{
    int         counter;
    int         s_anim;
    SVECTOR     speed;
    char        r, g, b;
    char        field_13; // index into field_1C
    const char *field_14; // loop/jump target?
    const char *op_code;
    short       field_1C[4];
    const char *saved_op_code[4];
} AnimeItem;

typedef struct AnimeWork
{
    GV_ACT    actor;
    DG_TEX   *tex;
    DG_PRIM  *prim;
    RECT      prim_rect;
    MATRIX   *world;
    int       map;
    char      field_38_active_buff;
    short     field_3A_data_2;
    short     field_3C_data_4;
    short     n_anims;
    short     abr; // semi-transparency rate
    short     n_vertices;
    short     raise;
    SVECTOR  *vertices;
    AnimeItem items[0];
} AnimeWork;

#define EXEC_LEVEL 6

/*---------------------------------------------------------------------------*/

typedef int (*TAnimeVMFn)(AnimeWork *, int);

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

GV_ACT *NewAnime_8005D604(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    int rnd;

    pre.pos.vx = pMtx->t[0]; pre.pos.vy = pMtx->t[1]; pre.pos.vz = pMtx->t[2];
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

    pPre->pos.vx = arg0->t[0];
    pPre->pos.vy = arg0->t[1];
    pPre->pos.vz = arg0->t[2];

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

        pSpeed->vx = sp28.t[0] - arg0->t[0];
        pSpeed->vy = sp28.t[1] - arg0->t[1];
        pSpeed->vz = sp28.t[2] - arg0->t[2];

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = pPre;

        NewAnime( NULL, 0, anm );
    }

    rand = GV_RandU(8);

    if (((rand > 3) && (GM_PlayerStatus == 0x810)) ||
        ((((dword_8009F224 % mod2) == 0) || (arg1 != 0)) && (GM_PlayerStatus != 0x810)))
    {
        pPre = &pre;

        sp48.vx = 0;
        sp48.vy = 0;
        sp48.vz = 0;

        DG_SetPos(arg0);
        DG_MovePos(&sp48);
        ReadRotMatrix(&sp28);

        pPre->pos.vx = sp28.t[0];
        pPre->pos.vy = sp28.t[1];
        pPre->pos.vz = sp28.t[2];

        sp48.vx = 0;
        sp48.vy = -10;
        sp48.vz = GV_RandU(8);

        pSpeed = &pre.speed;

        DG_MovePos(&sp48);
        ReadRotMatrix(&sp28);

        pSpeed->vx = sp28.t[0] - pPre->pos.vx;
        pSpeed->vy = sp28.t[1] - pPre->pos.vy;
        pSpeed->vz = sp28.t[2] - pPre->pos.vz;

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

    pos->vx = m.t[0];
    pos->vy = m.t[1];
    pos->vz = m.t[2];

    move.vx = GV_RandU(32) - 100;
    move.vy = GV_RandU(32) + 15;
    move.vz = GV_RandU(64) + 100;

    DG_MovePos(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[0] - pos->vx;
    speed->vy = m.t[1] - pos->vy;
    speed->vz = m.t[2] - pos->vz;
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

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        prescript.scr_num = 0;
        NewAnime(NULL, 0, anm);

        move.vx = 0;
        move.vy = -370;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        prescript.scr_num = 1;
        NewAnime(NULL, 0, anm);

        move.vx = 0;
        move.vy = -420;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

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

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        move.vx = 0;
        move.vy = -10;
        move.vz = GV_RandU(8);

        DG_MovePos(&move);
        ReadRotMatrix(&m);

        speed->vx = m.t[0] - pos->vx;
        speed->vy = m.t[1] - pos->vy;
        speed->vz = m.t[2] - pos->vz;

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

    pos->vx = m.t[0];
    pos->vy = m.t[1];
    pos->vz = m.t[2];

    move.vx = 0;
    move.vy = 0;
    move.vz = GV_RandU(8);

    DG_MovePos(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[0] - pos->vx;
    speed->vy = m.t[1] - pos->vy;
    speed->vz = m.t[2] - pos->vz;
    prescript.scr_num = 0;

    anm = &stru_8009F0F0;
    anm->pre_script = &prescript;

    NewAnime( NULL, 0, anm );
}

void NewAnime_8005DDE0(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos.vx = pMtx->t[0];
    pre.pos.vy = pMtx->t[1];
    pre.pos.vz = pMtx->t[2];
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

    pre.pos.vx = rotation->t[0] + sp18.vx;
    pre.pos.vy = rotation->t[1] + sp18.vy;
    pre.pos.vz = rotation->t[2] + sp18.vz;
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
        pres[i].pos = *arg0;
        sp18.vy += 128;

        DG_SetPos2(arg0, &sp18);
        DG_RotVector(&sp10, &pres[i].speed, 1);

        pres[i].scr_num = 0;
        pres[i].s_anim = 0;
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

        pres[i].s_anim = 0;
        pres[i].pos = *pPos;
        pres[i].scr_num = 0;

        RotMatrixYXZ(&axis, &rot);
        ApplyMatrixSV(&rot, &speed_in, &speed_out);

        pres[i].speed.vx = speed_out.vx;
        pres[i].speed.vy = speed_out.vy;
        pres[i].speed.vz = speed_out.vz;
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

    pre.pos.vx = arg0->t[0];
    pre.pos.vy = arg0->t[1];
    pre.pos.vz = arg0->t[2];
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
    prescript.pos.vx = pMatrix->t[0] + vec2.vx;
    prescript.pos.vy = pMatrix->t[1] + vec2.vy;
    prescript.pos.vz = pMatrix->t[2] + vec2.vz;
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

    pPre->pos.vx = rot.t[0];
    pPre->pos.vy = rot.t[1];
    pPre->pos.vz = rot.t[2];

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 750;

    DG_SetPos(rotation);
    DG_MovePos(&translation);
    ReadRotMatrix(&rot);

    pPre->pos.vx = rot.t[0];
    pPre->pos.vy = rot.t[1];
    pPre->pos.vz = rot.t[2];

    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 990;

    DG_SetPos(rotation);
    DG_MovePos(&translation);
    ReadRotMatrix(&rot);

    pPre->pos.vx = rot.t[0];
    pPre->pos.vy = rot.t[1];
    pPre->pos.vz = rot.t[2];

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

/*---------------------------------------------------------------------------*/

STATIC void anime_change_prim_8005E7EC(POLY_FT4 *pPrim, DG_TEX *tex, int anim, AnimeWork *work)
{
    int r, q;
    int x, y, w, h;
    int f40;

    r = anim % work->field_3A_data_2;
    q = anim / work->field_3A_data_2;

    x = tex->off_x;
    w = tex->w + 1;
    pPrim->u0 = pPrim->u2 = x + ((w * r) / work->field_3A_data_2);
    pPrim->u1 = pPrim->u3 = x + ((w * (r + 1)) / work->field_3A_data_2) - 1;

    y = tex->off_y;
    h = tex->h + 1;
    pPrim->v0 = pPrim->v1 = y + ((h * q) / work->field_3C_data_4);
    pPrim->v2 = pPrim->v3 = y + ((h * (q + 1)) / work->field_3C_data_4) - 1;

    pPrim->tpage = tex->tpage;
    pPrim->clut = tex->clut;

    f40 = work->abr;
    if ((f40 & 0xfffc) == 0)
    {
        pPrim->tpage &= ~0x60;
        pPrim->tpage |= work->abr << 5;
    }
}

STATIC void anime_change_polygon_8005E9E0(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[0];
    if ((work->field_38_active_buff & (GV_Clock + 1)) != 0)
    {
        anime_change_prim_8005E7EC(
            &((POLY_FT4 *)work->prim->packs[GV_Clock])[idx],
            work->tex, item->s_anim, work
        );
        work->field_38_active_buff &= ~(GV_Clock + 1);
    }
}

STATIC short anime_read_maybe_randomised_short_8005EA6C(const char *data, int opCode)
{
    const short temp = (data[1]) | (data[0] << 8);
    if (opCode & 0x80)
    {
        if (temp < 0)
        {
            return -(rand() % -temp);
        }
        else
        {
            return (rand() % temp);
        }
    }
    return temp;
}

STATIC void anime_read_vec_8005EB30(SVECTOR *pVec, const char *data, int opCode)
{
    pVec->vx = anime_read_maybe_randomised_short_8005EA6C(data, opCode);
    pVec->vy = anime_read_maybe_randomised_short_8005EA6C(data + 2, opCode);
    pVec->vz = anime_read_maybe_randomised_short_8005EA6C(data + 4, opCode);
}

STATIC void anime_adjust_vec_8005EB98(SVECTOR *pVec, const char *data, int opCode)
{
    pVec->vx += anime_read_maybe_randomised_short_8005EA6C(data, opCode);
    pVec->vy += anime_read_maybe_randomised_short_8005EA6C(data + 2, opCode);
    pVec->vz += anime_read_maybe_randomised_short_8005EA6C(data + 4, opCode);
}

STATIC int anime_fn_0_8005EC1C(AnimeWork *work, int idx)
{
    AnimeItem *item;
    int         next_op;

    item = &work->items[idx];
    next_op = item->op_code[1];
    if (next_op == 255)
    {
        item->s_anim++;
        if (item->s_anim >= work->n_anims)
        {
            item->s_anim = 0;
        }
    }
    else
    {
        if (next_op == 254)
        {
            next_op = rand() % work->n_anims;
        }
        item->s_anim = next_op;
    }
    work->field_38_active_buff = 3;
    item->op_code += 2;
    return 0;
}

STATIC int anime_fn_1_8005ED0C(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    item->counter =
        anime_read_maybe_randomised_short_8005EA6C(item->op_code + 1, *item->op_code);
    item->op_code += 3;
    return 1;
}

STATIC int anime_fn_2_8005ED74(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    anime_read_vec_8005EB30(&work->vertices[idx], item->op_code + 1, *item->op_code);
    item->op_code += 7;
    return 0;
}

STATIC int anime_fn_3_8005EDDC(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    anime_adjust_vec_8005EB98(&work->vertices[idx], item->op_code + 1, *item->op_code);
    item->op_code += 7;
    return 0;
}

STATIC int anime_fn_4_8005EE44(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    anime_read_vec_8005EB30(&item->speed, item->op_code + 1, *item->op_code);
    item->op_code += 7;
    return 0;
}

STATIC int anime_fn_5_8005EEA4(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    anime_adjust_vec_8005EB98(&item->speed, item->op_code + 1, *item->op_code);
    item->op_code += 7;
    return 0;
}

STATIC int anime_fn_6_8005EF04(AnimeWork *work, int idx)
{
    AnimeItem *item;
    int i;
    POLY_FT4 *pPoly;

    item = &work->items[idx];
    work->abr = item->op_code[1];

    if ((work->abr & 0xfffc) == 0)
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &work->prim->packs[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 1);

            pPoly->tpage &= ~0x60;
            pPoly->tpage |= work->abr << 5;
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &work->prim->packs[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 0);
        }
    }

    item->op_code += 2;
    return 0;
}

STATIC int anime_fn_7_8005EFF8(AnimeWork *work, int idx)
{
    AnimeItem   *item;
    int           i;
    const char   *pOpData;
    unsigned char rgb_incr[3];

    item = &work->items[idx];
    pOpData = item->op_code;

    for (i = 0; i < 3; i++)
    {
        pOpData++;
        rgb_incr[i] = *pOpData;
    }

    item->r += rgb_incr[0];
    item->g += rgb_incr[1];
    item->b += rgb_incr[2];

    item->op_code += 4;

    return 0;
}

STATIC void anime_act_helper_8005F094(AnimeWork *work)
{
    int               i;
    union Prim_Union *pPrimStart;
    AnimeItem       *pOffIter;
    POLY_FT4         *pPrim;

    pPrimStart = work->prim->packs[GV_Clock];
    pPrim = &pPrimStart->poly_ft4;
    pOffIter = &work->items[0];

    for (i = work->n_vertices; i > 0; i--)
    {
        setRGB0(pPrim, pOffIter->r, pOffIter->g, pOffIter->b);
        pPrim++;
        pOffIter++;
    }
}

STATIC int anime_fn_8_8005F0F0(AnimeWork *work, int idx)
{
    AnimeItem *item = &work->items[idx];
    short       value = anime_read_maybe_randomised_short_8005EA6C(item->op_code + 1, 0);
    DG_SetTmpLight(&work->vertices[idx], 512, value);
    item->op_code += 3;
    return 0;
}

STATIC int anime_fn_9_8005F180(AnimeWork *work, int idx)
{
    int         i;
    AnimeItem *item;
    const char *opCode_pos;
    short       rect_wh_offset[2];
    RECT       *rect;

    item = &work->items[idx];
    opCode_pos = item->op_code + 1;
    for (i = 0; i < 2; i++)
    {
        rect_wh_offset[i] = anime_read_maybe_randomised_short_8005EA6C(opCode_pos, 0);
        opCode_pos += 2;
    }

    rect = &work->prim_rect;
    rect->w += rect_wh_offset[0];
    rect->h += rect_wh_offset[1];
    rect->x = rect->w / 2;
    rect->y = rect->h / 2;
    item->op_code += 5;
    return 0;
}

STATIC int anime_fn_10_8005F288(AnimeWork *work, int idx)
{
    AnimeItem *item;

    item = &work->items[idx];
    GM_SeSet(&work->vertices[idx], item->op_code[1]);
    item->op_code += 2;
    return 0;
}

STATIC int anime_fn_11_8005F2F4(AnimeWork *work, int idx)
{
    AnimeItem *item;
    int         maybe_randomised_short_8005EA6C;
    int         new_idx;

    item = &work->items[idx];
    maybe_randomised_short_8005EA6C = anime_read_maybe_randomised_short_8005EA6C(item->op_code + 1, 0);
    item->field_13++;
    new_idx = item->field_13;
    item->op_code += 3;
    item->field_1C[new_idx] = maybe_randomised_short_8005EA6C;
    item->saved_op_code[new_idx] = item->op_code;
    return 0;
}

STATIC int anime_fn_12_8005F37C(AnimeWork *work, int idx)
{
    AnimeItem *item;
    int         idx2;

    item = &work->items[idx];
    idx2 = item->field_13;

    if (--item->field_1C[idx2] <= 0)
    {
        if (item->field_1C[idx2] == 0)
        {
            item->field_13--;
            item->op_code++;
        }
        else
        {
            item->op_code = item->saved_op_code[idx2];
        }
    }
    else
    {
        item->op_code = item->saved_op_code[idx2];
    }

    return 0;
}

STATIC int anime_fn_13_8005F408(AnimeWork *work, int idx)
{
    AnimeItem *item;
    item = &work->items[idx];
    item->op_code = item->field_14;
    return 1;
}

STATIC int anime_fn_14_8005F438(AnimeWork *work, int idx)
{
    DG_InvisiblePrim(work->prim);
    GV_DestroyActor(&work->actor);
    return 1;
}

STATIC void anime_act_helper_8005F46C(SVECTOR *svec, AnimeItem *item)
{
    svec->vx += item->speed.vx;
    svec->vy += item->speed.vy;
    svec->vz += item->speed.vz;
}

TAnimeVMFn anime_fn_table_8009F228[] = {
    anime_fn_0_8005EC1C,
    anime_fn_1_8005ED0C,
    anime_fn_2_8005ED74,
    anime_fn_3_8005EDDC,
    anime_fn_4_8005EE44,
    anime_fn_5_8005EEA4,
    anime_fn_6_8005EF04,
    anime_fn_7_8005EFF8,
    anime_fn_8_8005F0F0,
    anime_fn_9_8005F180,
    anime_fn_10_8005F288,
    anime_fn_11_8005F2F4,
    anime_fn_12_8005F37C,
    anime_fn_13_8005F408,
    anime_fn_14_8005F438
};

STATIC void anime_Act(AnimeWork *work)
{
    AnimeItem   *item;
    SVECTOR     *vertices;
    int          i;
    unsigned int script_op_code;
    int          opCodeRet;

    item = work->items;
    DG_VisiblePrim(work->prim);

    vertices = work->vertices;
    for (i = 0; i < work->n_vertices; ++i)
    {
        if (item->counter <= 0)
        {
            while (1)
            {
                script_op_code = *item->op_code & 0x7F;
                if (script_op_code > 15)
                {
                    fprintf(1, " SCRIPT ACT ERR!! \n");
                    GV_DestroyActor(&work->actor);
                    break;
                }
                opCodeRet = anime_fn_table_8009F228[script_op_code - 1](work, i);
                if (opCodeRet)
                {
                    break;
                }
            }
        }
        anime_act_helper_8005F46C(vertices, item);
        anime_change_polygon_8005E9E0(work, i);
        ++vertices;
        --item->counter;
        ++item;
    }
    anime_act_helper_8005F094(work);
    GM_CurrentMap_800AB9B0 = work->map;
    if (work->world)
    {
        DG_SetPos(work->world);
        DG_PutPrim(&work->prim->world);
    }
}

STATIC void anime_Die(AnimeWork *anime)
{
    DG_PRIM *prim = anime->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

STATIC int anime_loader_helper_8005F644(AnimeWork *work, ANIMATION *animation)
{
    const char *opcodes[4];
    const char *data;
    int         count;
    int         i;
    int         index;
    PRESCRIPT  *prescript;
    AnimeItem  *item;

    data = animation->field_18_ptr;
    count = data[2];

    data += 3;

    for (i = 0; i < count; data += 2, i++)
    {
        index = (data[0] << 8) + data[1];
        opcodes[i] = &animation->field_18_ptr[index];
    }

    prescript = animation->pre_script;
    item = work->items;

    for (i = 0; i < work->n_vertices; i++)
    {
        item->op_code = item->field_14 = opcodes[prescript->scr_num];

        prescript++;
        item++;
    }

    return 0;
}

STATIC void anime_loader_helper_8005F6EC(AnimeWork *work, char shade)
{
    POLY_FT4 *poly_ft4[2];
    DG_PRIM* prim;
    DG_TEX* tex;
    int f44;
    AnimeItem *item;
    int i, j;
    int r, q;
    POLY_FT4 *pPoly;
    int x, y, w, h;
    int f40;

    prim = work->prim;
    tex = work->tex;

    poly_ft4[0] = &prim->packs[0]->poly_ft4;
    poly_ft4[1] = &prim->packs[1]->poly_ft4;

    f44 = work->raise;
    prim->field_2E_k500 = f44;

    item = work->items;

    for (i = 0; i < work->n_vertices; i++)
    {
        r = item->s_anim % work->field_3A_data_2;
        q = item->s_anim / work->field_3A_data_2;

        for (j = 0; j < 2; j++)
        {
            pPoly = &poly_ft4[j][i];
            setPolyFT4(pPoly);

            x = tex->off_x;
            w = tex->w + 1;
            pPoly->u0 = pPoly->u2 = x + ((w * r) / work->field_3A_data_2);
            pPoly->u1 = pPoly->u3 = x + ((w * (r + 1)) / work->field_3A_data_2) - 1;

            y = tex->off_y;
            h = tex->h + 1;
            pPoly->v0 = pPoly->v1 = y + ((h * q) / work->field_3C_data_4);
            pPoly->v2 = pPoly->v3 = y + ((h * (q + 1)) / work->field_3C_data_4) - 1;

            pPoly->tpage = tex->tpage;
            pPoly->clut = tex->clut;

            f40 = work->abr;
            if ((f40 & 0xfffc) == 0)
            {
                setSemiTrans(pPoly, 1);
                pPoly->tpage &= ~0x60;
                pPoly->tpage |= work->abr << 5;
            }
            else
            {
                setSemiTrans(pPoly, 0);
            }

            setRGB0(pPoly, shade, shade, shade);
        }

        item++;
    }
}

STATIC int anime_GetResources(AnimeWork *work, int map, ANIMATION *animation)
{
    int count;
    PRESCRIPT *prescript;
    int i;
    RECT *rect;
    AnimeItem *item;

    work->field_38_active_buff = 3;
    work->map = map;
    work->field_3A_data_2 = animation->field_2;
    work->field_3C_data_4 = animation->field_4;
    work->n_anims = animation->n_anims;
    work->abr = animation->field_C;

    count = animation->n_vertices;
    work->n_vertices = count;
    work->raise = animation->field_A;

    prescript = animation->pre_script;

    for (i = 0; i < count; i++)
    {
        work->vertices[i] = prescript->pos;
        prescript++;
    }

    rect = &work->prim_rect;
    rect->x = animation->field_E_xw / 2;
    rect->y = animation->field_10_yh / 2;
    rect->w = animation->field_E_xw;
    rect->h = animation->field_10_yh;

    work->prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, count, 0, work->vertices, rect);
    if (!work->prim)
    {
        return -1;
    }

    work->tex = DG_GetTexture(animation->field_0_texture_hash);

    item = work->items;
    prescript = animation->pre_script;

    for (i = 0; i < count; i++)
    {
        item->counter = 0;
        item->s_anim = prescript->s_anim;
        item->speed = prescript->speed;
        item->r = item->g = item->b = animation->field_12_rgb;
        item->field_13 = -1;

        item++;
        prescript++;
    }

    anime_loader_helper_8005F6EC(work, animation->field_12_rgb);
    DG_InvisiblePrim(work->prim);

    if (anime_loader_helper_8005F644(work, animation) < 0)
    {
        return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewAnime(MATRIX *world, int map, ANIMATION *animation)
{
    int        count;
    AnimeWork *work;

    count = animation->n_vertices;
    work = (AnimeWork *)GV_NewActor(EXEC_LEVEL, ((sizeof(AnimeItem) + sizeof(SVECTOR)) * count) + sizeof(AnimeWork));
    if (work)
    {
        work->vertices = (SVECTOR *)&work->items[count]; // count vectors after the items
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)anime_Act,
                         (GV_ACTFUNC)anime_Die, "anime.c");
        if (anime_GetResources(work, map, animation) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        else
        {
            work->world = world;
        }
    }

    return (GV_ACT *)work;
}

GV_ACT *NewAnime2(DG_PRIM *prim, int map, ANIMATION *animation)
{
    AnimeWork *work = (AnimeWork *)NewAnime(NULL, map, animation);

    if (work && prim)
    {
        work->prim->world = prim->world;
    }

    return (GV_ACT *)work;
}
