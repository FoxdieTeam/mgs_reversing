#include "anime.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/map.h"

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Time_800AB330;
extern int     GV_Clock_800AB920;
extern int     GM_PlayerStatus_800ABA50;

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

AnimeWork * anime_create_8005D604(MATRIX *pMtx)
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

void anime_create_8005D6BC(MATRIX *arg0, int arg1)
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
        sp48.vx = GV_RandU_80017090(32) - 100;
        sp48.vy = GV_RandU_80017090(16) - 10;
        sp48.vz = GV_RandU_80017090(16) + 40;

        DG_SetPos_8001BC44(arg0);
        DG_MovePos_8001BD20(&sp48);
        ReadRotMatrix(&sp28);

        pSpeed->vx = sp28.t[0] - arg0->t[0];
        pSpeed->vy = sp28.t[1] - arg0->t[1];
        pSpeed->vz = sp28.t[2] - arg0->t[2];

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->field_14_pre_script = pPre;

        NewAnime_8005FBC8( NULL, 0, anm );
    }

    rand = GV_RandU_80017090(8);

    if (((rand > 3) && (GM_PlayerStatus_800ABA50 == 0x810)) ||
        ((((dword_8009F224 % mod2) == 0) || (arg1 != 0)) && (GM_PlayerStatus_800ABA50 != 0x810)))
    {
        pPre = &pre;

        sp48.vx = 0;
        sp48.vy = 0;
        sp48.vz = 0;

        DG_SetPos_8001BC44(arg0);
        DG_MovePos_8001BD20(&sp48);
        ReadRotMatrix(&sp28);

        pPre->pos.vx = sp28.t[0];
        pPre->pos.vy = sp28.t[1];
        pPre->pos.vz = sp28.t[2];

        sp48.vx = 0;
        sp48.vy = -10;
        sp48.vz = GV_RandU_80017090(8);

        pSpeed = &pre.speed;

        DG_MovePos_8001BD20(&sp48);
        ReadRotMatrix(&sp28);

        pSpeed->vx = sp28.t[0] - pPre->pos.vx;
        pSpeed->vy = sp28.t[1] - pPre->pos.vy;
        pSpeed->vz = sp28.t[2] - pPre->pos.vz;

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &stru_8009F0F0;
        anm->field_14_pre_script = &pre;

        NewAnime_8005FBC8( NULL, 0, anm );
    }

#ifndef VR_EXE
    if (dword_8009F224++ >= ((mod2 * mod) - 1))
    {
        dword_8009F224 = 0;
    }
#endif
}

void anime_create_8005D988(MATRIX *pMatrix1, MATRIX *pMatrix2, int mode)
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

    DG_SetPos_8001BC44(pMatrix1);
    DG_MovePos_8001BD20(&move);
    ReadRotMatrix(&m);

    pos->vx = m.t[0];
    pos->vy = m.t[1];
    pos->vz = m.t[2];

    move.vx = GV_RandU_80017090(32) - 100;
    move.vy = GV_RandU_80017090(32) + 15;
    move.vz = GV_RandU_80017090(64) + 100;

    DG_MovePos_8001BD20(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[0] - pos->vx;
    speed->vy = m.t[1] - pos->vy;
    speed->vz = m.t[2] - pos->vz;
    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm = &stru_8009F0D4;
    stru_8009F0D4.field_14_pre_script = &prescript;

    NewAnime_8005FBC8(NULL, 0, anm);

    if (mode != 1)
    {
        prescript.speed = DG_ZeroVector_800AB39C;

        randu = GV_RandU_80017090(16);
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
        anm->field_14_pre_script = &prescript;

        move.vx = 0;
        move.vy = -270;
        move.vz = 0;

        DG_SetPos_8001BC44(pMatrix1);
        DG_MovePos_8001BD20(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        prescript.scr_num = 0;
        NewAnime_8005FBC8(NULL, 0, anm);

        move.vx = 0;
        move.vy = -370;
        move.vz = 0;

        DG_SetPos_8001BC44(pMatrix1);
        DG_MovePos_8001BD20(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        prescript.scr_num = 1;
        NewAnime_8005FBC8(NULL, 0, anm);

        move.vx = 0;
        move.vy = -420;
        move.vz = 0;

        DG_SetPos_8001BC44(pMatrix1);
        DG_MovePos_8001BD20(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        prescript.scr_num = 2;
        NewAnime_8005FBC8(NULL, 0, anm);
    }
    else
    {
        DG_SetPos_8001BC44(pMatrix2);

        move.vx = 0;
        move.vy = 0;
        move.vz = 0;

        DG_MovePos_8001BD20(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[0];
        pos->vy = m.t[1];
        pos->vz = m.t[2];

        move.vx = 0;
        move.vy = -10;
        move.vz = GV_RandU_80017090(8);

        DG_MovePos_8001BD20(&move);
        ReadRotMatrix(&m);

        speed->vx = m.t[0] - pos->vx;
        speed->vy = m.t[1] - pos->vy;
        speed->vz = m.t[2] - pos->vz;

        prescript.scr_num = 2;

        anm = &stru_8009F0F0;
        anm->field_14_pre_script = &prescript;

        NewAnime_8005FBC8(NULL, 0, anm);
    }

    DG_SetPos_8001BC44(pMatrix1);

    pos = &prescript.pos;

    move.vx = 0;
    move.vy = 0;
    move.vz = 0;

    DG_MovePos_8001BD20(&move);
    ReadRotMatrix(&m);

    pos->vx = m.t[0];
    pos->vy = m.t[1];
    pos->vz = m.t[2];

    move.vx = 0;
    move.vy = 0;
    move.vz = GV_RandU_80017090(8);

    DG_MovePos_8001BD20(&move);
    ReadRotMatrix(&m);

    speed = &prescript.speed;

    speed->vx = m.t[0] - pos->vx;
    speed->vy = m.t[1] - pos->vy;
    speed->vz = m.t[2] - pos->vz;
    prescript.scr_num = 0;

    anm = &stru_8009F0F0;
    anm->field_14_pre_script = &prescript;

    NewAnime_8005FBC8( NULL, 0, anm );
}

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

void anime_create_8005DE70(MATRIX *pRotation)
{
    SVECTOR    sp10;
    SVECTOR    sp18;
    MATRIX     rotation;
    PRESCRIPT  pre;
    ANIMATION *anm;

    rotation = *pRotation;

    sp10.vx = 0;
    sp10.vy = -1500;
    sp10.vz = 0;

    ApplyMatrixSV(&rotation, &sp10, &sp18);

    pre.pos.vx = pRotation->t[0] + sp18.vx;
    pre.pos.vy = pRotation->t[1] + sp18.vy;
    pre.pos.vz = pRotation->t[2] + sp18.vz;
    pre.speed.vx = 0;
    pre.speed.vy = 0;
    pre.speed.vz = 0;
    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &stru_8009F1B4;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005DF50(SVECTOR *arg0, SVECTOR *arg1)
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
        sp10.vz = GV_RandU_80017090(64) + 150;
        pres[i].pos = *arg0;
        sp18.vy += 128;

        DG_SetPos2_8001BC8C(arg0, &sp18);
        DG_RotVector_8001BE98(&sp10, &pres[i].speed, 1);

        pres[i].scr_num = 0;
        pres[i].s_anim = 0;
    }

    pres[3].pos = *arg0;
    pres[3].speed = DG_ZeroVector_800AB39C;
    pres[3].scr_num = 1;
    pres[3].s_anim = 0;

    stru_8009F1D0.field_14_pre_script = pres;
    NewAnime_8005FBC8( NULL, 0, &stru_8009F1D0 );
}

void anime_create_8005E090(SVECTOR *pPos)
{
    SVECTOR axis;
    SVECTOR speed_in;
    SVECTOR speed_out;
    MATRIX rotation;
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
        speed_in.vz = GV_RandS_800170BC(16) + 40;

        pres[i].s_anim = 0;
        pres[i].pos = *pPos;
        pres[i].scr_num = 0;

        RotMatrixYXZ(&axis, &rotation);
        ApplyMatrixSV(&rotation, &speed_in, &speed_out);

        pres[i].speed.vx = speed_out.vx;
        pres[i].speed.vy = speed_out.vy;
        pres[i].speed.vz = speed_out.vz;
    }

    anm = &stru_8009F198;
    anm->field_14_pre_script = pres;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005E1A0(MATRIX *arg0)
{
    PRESCRIPT  pre;
    int        temp_v0;
    ANIMATION *anm;

    pre.pos.vx = arg0->t[0];
    pre.pos.vy = arg0->t[1];
    pre.pos.vz = arg0->t[2];
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = 0;

    temp_v0 = GV_RandU_80017090(16);

    if (temp_v0 >= 5)
    {
        pre.s_anim = 2;
    }
    else if (temp_v0 > 0)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &stru_8009F10C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005E258(MATRIX *pMatrix)
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
    stru_8009F1B4.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, 0, &stru_8009F1B4);
}

void anime_create_8005E334(MATRIX *pRotation)
{
    PRESCRIPT  pre;
    SVECTOR    translation;
    MATRIX     rotation;
    int        temp_v0;
    PRESCRIPT *pPre;
    ANIMATION *anm;

    pPre = &pre;
    pPre->speed = DG_ZeroVector_800AB39C;

    temp_v0 = GV_RandU_80017090(16);

    if (temp_v0 >= 7)
    {
        pre.s_anim = 3;
    }
    else if (temp_v0 >= 5)
    {
        pre.s_anim = 2;
    }
    else if (temp_v0 >= 3)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &stru_8009F128;
    anm->field_14_pre_script = &pre;

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 300;

    DG_SetPos_8001BC44(pRotation);
    DG_MovePos_8001BD20(&translation);
    ReadRotMatrix(&rotation);

    pPre->pos.vx = rotation.t[0];
    pPre->pos.vy = rotation.t[1];
    pPre->pos.vz = rotation.t[2];

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 750;

    DG_SetPos_8001BC44(pRotation);
    DG_MovePos_8001BD20(&translation);
    ReadRotMatrix(&rotation);

    pPre->pos.vx = rotation.t[0];
    pPre->pos.vy = rotation.t[1];
    pPre->pos.vz = rotation.t[2];

    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    translation.vx = 0;
    translation.vy = 0;
    translation.vz = 990;

    DG_SetPos_8001BC44(pRotation);
    DG_MovePos_8001BD20(&translation);
    ReadRotMatrix(&rotation);

    pPre->pos.vx = rotation.t[0];
    pPre->pos.vy = rotation.t[1];
    pPre->pos.vz = rotation.t[2];

    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005E508(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &stru_8009F1EC;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void anime_create_8005E574(MATRIX *pMtx)
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

void anime_create_8005E774(SVECTOR *pos)
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

void anime_change_prim_8005E7EC(POLY_FT4 *pPrim, DG_TEX *pTexture, int item_f4, AnimeWork *work)
{
    int r, q;
    int x, y, w, h;
    int f40;

    r = item_f4 % work->field_3A_data_2;
    q = item_f4 / work->field_3A_data_2;

    x = pTexture->field_8_offx;
    w = pTexture->field_A_width + 1;
    pPrim->u0 = pPrim->u2 = x + ((w * r) / work->field_3A_data_2);
    pPrim->u1 = pPrim->u3 = x + ((w * (r + 1)) / work->field_3A_data_2) - 1;

    y = pTexture->field_9_offy;
    h = pTexture->field_B_height + 1;
    pPrim->v0 = pPrim->v1 = y + ((h * q) / work->field_3C_data_4);
    pPrim->v2 = pPrim->v3 = y + ((h * (q + 1)) / work->field_3C_data_4) - 1;

    pPrim->tpage = pTexture->field_4_tPage;
    pPrim->clut = pTexture->field_6_clut;

    f40 = work->field_40_data_C;
    if ((f40 & 0xfffc) == 0)
    {
        pPrim->tpage &= ~0x60;
        pPrim->tpage |= work->field_40_data_C << 5;
    }
}

void anime_change_polygon_8005E9E0(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[0];
    if ((work->field_38_active_buff & (GV_Clock_800AB920 + 1)) != 0)
    {
        anime_change_prim_8005E7EC(
            &((POLY_FT4 *)work->field_24_pPrim->packs[GV_Clock_800AB920])[idx],
            work->field_20_pTexture, pItem->field_4, work
        );
        work->field_38_active_buff &= ~(GV_Clock_800AB920 + 1);
    }
}

short anime_read_maybe_randomised_short_8005EA6C(const char *pData, int opCode)
{
    const short temp = (pData[1]) | (pData[0] << 8);
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

void anime_read_vec_8005EB30(SVECTOR *pVec, const char *pData, int opCode)
{
    pVec->vx = anime_read_maybe_randomised_short_8005EA6C(pData, opCode);
    pVec->vy = anime_read_maybe_randomised_short_8005EA6C(pData + 2, opCode);
    pVec->vz = anime_read_maybe_randomised_short_8005EA6C(pData + 4, opCode);
}

void anime_adjust_vec_8005EB98(SVECTOR *pVec, const char *pData, int opCode)
{
    pVec->vx += anime_read_maybe_randomised_short_8005EA6C(pData, opCode);
    pVec->vy += anime_read_maybe_randomised_short_8005EA6C(pData + 2, opCode);
    pVec->vz += anime_read_maybe_randomised_short_8005EA6C(pData + 4, opCode);
}

int anime_fn_0_8005EC1C(AnimeWork *work, int idx)
{
    anime_0x34 *pItem;   // $s0
    int         next_op; // $v1

    pItem = &work->field_4C_items[idx];
    next_op = pItem->field_18_op_code[1];
    if (next_op == 255)
    {
        pItem->field_4++;
        if (pItem->field_4 >= work->field_3E_maybe_data_count)
        {
            pItem->field_4 = 0;
        }
    }
    else
    {
        if (next_op == 254)
        {
            next_op = rand() % work->field_3E_maybe_data_count;
        }
        pItem->field_4 = next_op;
    }
    work->field_38_active_buff = 3;
    pItem->field_18_op_code += 2;
    return 0;
}

int anime_fn_1_8005ED0C(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    pItem->field_0_counter =
        anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 3;
    return 1;
}

int anime_fn_2_8005ED74(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    anime_read_vec_8005EB30(&work->field_48_pPrimVec[idx], pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_3_8005EDDC(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    anime_adjust_vec_8005EB98(&work->field_48_pPrimVec[idx], pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_4_8005EE44(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    anime_read_vec_8005EB30(&pItem->field_8_vec, pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_5_8005EEA4(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    anime_adjust_vec_8005EB98(&pItem->field_8_vec, pItem->field_18_op_code + 1, *pItem->field_18_op_code);
    pItem->field_18_op_code += 7;
    return 0;
}

int anime_fn_6_8005EF04(AnimeWork *work, int idx)
{
    anime_0x34 *pItem;
    int i;
    POLY_FT4 *pPoly;

    pItem = &work->field_4C_items[idx];
    work->field_40_data_C = pItem->field_18_op_code[1];

    if ((work->field_40_data_C & ~0x3) == 0)
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &work->field_24_pPrim->packs[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 1);

            pPoly->tpage &= ~0x60;
            pPoly->tpage |= work->field_40_data_C << 5;
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            pPoly = &work->field_24_pPrim->packs[i]->poly_ft4;
            pPoly += idx;

            setSemiTrans(pPoly, 0);
        }
    }

    pItem->field_18_op_code += 2;
    return 0;
}

int anime_fn_7_8005EFF8(AnimeWork *work, int idx)
{
    anime_0x34   *pItem;   // $a2
    int           i;       // $a0
    const char   *pOpData; // $a1
    unsigned char rgb_incr[3];

    pItem = &work->field_4C_items[idx];
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

void anime_act_helper_8005F094(AnimeWork *work)
{
    int               i;          // $a1
    union Prim_Union *pPrimStart; // $v1
    anime_0x34       *pOffIter;   // $a0
    POLY_FT4         *pPrim;      // $v1

    pPrimStart = work->field_24_pPrim->packs[GV_Clock_800AB920];
    pPrim = &pPrimStart->poly_ft4;
    pOffIter = &work->field_4C_items[0];

    for (i = work->field_42_count; i > 0; i--)
    {
        setRGB0(pPrim, pOffIter->field_10_r, pOffIter->field_11_g, pOffIter->field_12_b);
        pPrim++;
        pOffIter++;
    }
}

int anime_fn_8_8005F0F0(AnimeWork *work, int idx)
{
    anime_0x34 *pItem = &work->field_4C_items[idx];
    short       value = anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, 0);
    DG_SetTmpLight_8001A114(&work->field_48_pPrimVec[idx], 512, value);
    pItem->field_18_op_code += 3;
    return 0;
}

int anime_fn_9_8005F180(AnimeWork *work, int idx)
{
    int         i;                 // $s2
    anime_0x34 *pItem;             // $s3
    const char *opCode_pos;        // $s0
    short       rect_wh_offset[2]; // [sp+10h] [-8h] BYREF
    RECT       *pRect;

    pItem = &work->field_4C_items[idx];
    opCode_pos = pItem->field_18_op_code + 1;
    for (i = 0; i < 2; i++)
    {
        rect_wh_offset[i] = anime_read_maybe_randomised_short_8005EA6C(opCode_pos, 0);
        opCode_pos += 2;
    }

    pRect = &work->field_28_prim_rect;
    pRect->w += rect_wh_offset[0];
    pRect->h += rect_wh_offset[1];
    pRect->x = pRect->w / 2;
    pRect->y = pRect->h / 2;
    pItem->field_18_op_code += 5;
    return 0;
}

int anime_fn_10_8005F288(AnimeWork *work, int idx)
{
    anime_0x34 *pItem; // $s0

    pItem = &work->field_4C_items[idx];
    GM_SeSet_80032858(&work->field_48_pPrimVec[idx], pItem->field_18_op_code[1]);
    pItem->field_18_op_code += 2;
    return 0;
}

int anime_fn_11_8005F2F4(AnimeWork *work, int idx)
{
    anime_0x34 *pItem;                           // $s0
    int         maybe_randomised_short_8005EA6C; // $v0
    int         new_idx;                         // $a0

    pItem = &work->field_4C_items[idx];
    maybe_randomised_short_8005EA6C = anime_read_maybe_randomised_short_8005EA6C(pItem->field_18_op_code + 1, 0);
    pItem->field_13++;
    new_idx = pItem->field_13;
    pItem->field_18_op_code += 3;
    pItem->field_1C[new_idx] = maybe_randomised_short_8005EA6C;
    pItem->field_24_saved_op_code[new_idx] = pItem->field_18_op_code;
    return 0;
}

int anime_fn_12_8005F37C(AnimeWork *work, int idx)
{
    anime_0x34 *pItem;
    int         idx2;

    pItem = &work->field_4C_items[idx];
    idx2 = pItem->field_13;

    if (--pItem->field_1C[idx2] <= 0)
    {
        if (pItem->field_1C[idx2] == 0)
        {
            pItem->field_13--;
            pItem->field_18_op_code++;
        }
        else
        {
            pItem->field_18_op_code = pItem->field_24_saved_op_code[idx2];
        }
    }
    else
    {
        pItem->field_18_op_code = pItem->field_24_saved_op_code[idx2];
    }

    return 0;
}

int anime_fn_13_8005F408(AnimeWork *work, int idx)
{
    anime_0x34 *pItem; // $a2
    pItem = &work->field_4C_items[idx];
    pItem->field_18_op_code = pItem->field_14;
    return 1;
}

int anime_fn_14_8005F438(AnimeWork *work, int idx)
{
    DG_InvisiblePrim(work->field_24_pPrim);
    GV_DestroyActor_800151C8(&work->field_0_actor);
    return 1;
}

void anime_act_helper_8005F46C(SVECTOR *pVec, anime_0x34 *pItem)
{
    pVec->vx += pItem->field_8_vec.vx;
    pVec->vy += pItem->field_8_vec.vy;
    pVec->vz += pItem->field_8_vec.vz;
}

void anime_act_8005F4AC(AnimeWork *work)
{
    anime_0x34  *pItemsIter;        // $s0
    SVECTOR     *field_48_pPrimVec; // $s3
    int          i;                 // $s1
    unsigned int script_op_code;    // $v1
    int          opCodeRet;         // $v0

    pItemsIter = work->field_4C_items;
    DG_VisiblePrim(work->field_24_pPrim);

    field_48_pPrimVec = work->field_48_pPrimVec;
    for (i = 0; i < work->field_42_count; ++i)
    {
        if (pItemsIter->field_0_counter <= 0)
        {
            while (1)
            {
                script_op_code = *pItemsIter->field_18_op_code & 0x7F;
                if (script_op_code > 15)
                {
                    fprintf(1, " SCRIPT ACT ERR!! \n");
                    GV_DestroyActor_800151C8(&work->field_0_actor);
                    break;
                }
                opCodeRet = anime_fn_table_8009F228[script_op_code - 1](work, i);
                if (opCodeRet)
                {
                    break;
                }
            }
        }
        anime_act_helper_8005F46C(field_48_pPrimVec, pItemsIter);
        anime_change_polygon_8005E9E0(work, i);
        ++field_48_pPrimVec;
        --pItemsIter->field_0_counter;
        ++pItemsIter;
    }
    anime_act_helper_8005F094(work);
    GM_CurrentMap_800AB9B0 = work->field_34_map;
    if (work->field_30_mtx)
    {
        DG_SetPos_8001BC44(work->field_30_mtx);
        DG_PutPrim_8001BE00(&work->field_24_pPrim->world);
    }
}

void anime_kill_8005F608(AnimeWork *anime)
{
    DG_PRIM *prim = anime->field_24_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int anime_loader_helper_8005F644(AnimeWork *work, ANIMATION *pAnimation)
{
    const char *opcodes[4];
    const char *pData;
    int         count;
    int         i;
    int         index;
    PRESCRIPT  *pPrescript;
    anime_0x34 *pItem;

    pData = pAnimation->field_18_ptr;
    count = pData[2];

    pData += 3;

    for (i = 0; i < count; pData += 2, i++)
    {
        index = (pData[0] << 8) + pData[1];
        opcodes[i] = &pAnimation->field_18_ptr[index];
    }

    pPrescript = pAnimation->field_14_pre_script;
    pItem = work->field_4C_items;

    for (i = 0; i < work->field_42_count; i++)
    {
        pItem->field_18_op_code = pItem->field_14 = opcodes[pPrescript->scr_num];

        pPrescript++;
        pItem++;
    }

    return 0;
}

void anime_loader_helper_8005F6EC(AnimeWork *work, char shade)
{
    POLY_FT4 *pPolys[2];
    DG_PRIM* pPrim;
    DG_TEX* pTex;
    int f44;
    anime_0x34 *pItem;
    int i, j;
    int r, q;
    POLY_FT4 *pPoly;
    int x, y, w, h;
    int f40;

    pPrim = work->field_24_pPrim;
    pTex = work->field_20_pTexture;

    pPolys[0] = &pPrim->packs[0]->poly_ft4;
    pPolys[1] = &pPrim->packs[1]->poly_ft4;

    f44 = work->field_44_data_A;
    pPrim->field_2E_k500 = f44;

    pItem = work->field_4C_items;

    for (i = 0; i < work->field_42_count; i++)
    {
        r = pItem->field_4 % work->field_3A_data_2;
        q = pItem->field_4 / work->field_3A_data_2;

        for (j = 0; j < 2; j++)
        {
            pPoly = &pPolys[j][i];
            setPolyFT4(pPoly);

            x = pTex->field_8_offx;
            w = pTex->field_A_width + 1;
            pPoly->u0 = pPoly->u2 = x + ((w * r) / work->field_3A_data_2);
            pPoly->u1 = pPoly->u3 = x + ((w * (r + 1)) / work->field_3A_data_2) - 1;

            y = pTex->field_9_offy;
            h = pTex->field_B_height + 1;
            pPoly->v0 = pPoly->v1 = y + ((h * q) / work->field_3C_data_4);
            pPoly->v2 = pPoly->v3 = y + ((h * (q + 1)) / work->field_3C_data_4) - 1;

            pPoly->tpage = pTex->field_4_tPage;
            pPoly->clut = pTex->field_6_clut;

            f40 = work->field_40_data_C;
            if ((f40 & 0xfffc) == 0)
            {
                setSemiTrans(pPoly, 1);
                pPoly->tpage &= ~0x60;
                pPoly->tpage |= work->field_40_data_C << 5;
            }
            else
            {
                setSemiTrans(pPoly, 0);
            }

            setRGB0(pPoly, shade, shade, shade);
        }

        pItem++;
    }
}

int anime_loader_8005F994(AnimeWork *work, int map, ANIMATION *pAnimation)
{
    int count;
    PRESCRIPT *pPrescript;
    int i;
    RECT *pRect;
    anime_0x34 *pItem;

    work->field_38_active_buff = 3;
    work->field_34_map = map;
    work->field_3A_data_2 = pAnimation->field_2;
    work->field_3C_data_4 = pAnimation->field_4;
    work->field_3E_maybe_data_count = pAnimation->field_6;
    work->field_40_data_C = pAnimation->field_C;

    count = pAnimation->field_8_count;
    work->field_42_count = count;
    work->field_44_data_A = pAnimation->field_A;

    pPrescript = pAnimation->field_14_pre_script;

    for (i = 0; i < count; i++)
    {
        work->field_48_pPrimVec[i] = pPrescript->pos;
        pPrescript++;
    }

    pRect = &work->field_28_prim_rect;
    pRect->x = pAnimation->field_E_xw / 2;
    pRect->y = pAnimation->field_10_yh / 2;
    pRect->w = pAnimation->field_E_xw;
    pRect->h = pAnimation->field_10_yh;

    work->field_24_pPrim = DG_GetPrim(0x412, count, 0, work->field_48_pPrimVec, pRect);
    if (!work->field_24_pPrim)
    {
        return -1;
    }

    work->field_20_pTexture = DG_GetTexture_8001D830(pAnimation->field_0_texture_hash);

    pItem = work->field_4C_items;
    pPrescript = pAnimation->field_14_pre_script;

    for (i = 0; i < count; i++)
    {
        pItem->field_0_counter = 0;
        pItem->field_4 = pPrescript->s_anim;
        pItem->field_8_vec = pPrescript->speed;
        pItem->field_10_r = pItem->field_11_g = pItem->field_12_b = pAnimation->field_12_rgb;
        pItem->field_13 = -1;

        pItem++;
        pPrescript++;
    }

    anime_loader_helper_8005F6EC(work, pAnimation->field_12_rgb);
    DG_InvisiblePrim(work->field_24_pPrim);

    if (anime_loader_helper_8005F644(work, pAnimation) < 0)
    {
        return -1;
    }

    return 0;
}

AnimeWork *NewAnime_8005FBC8(MATRIX *pMtx, int map, ANIMATION *pAnimation)
{
    int          count;  // $s1
    AnimeWork *work; // $v0

    count = pAnimation->field_8_count;
    work =
        (AnimeWork *)GV_NewActor_800150E4(6, ((sizeof(anime_0x34) + sizeof(SVECTOR)) * count) + sizeof(AnimeWork));
    if (work)
    {
        work->field_48_pPrimVec = (SVECTOR *)&work->field_4C_items[count]; // count vectors after the items
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)anime_act_8005F4AC,
                                  (TActorFunction)anime_kill_8005F608, "anime.c");
        if (anime_loader_8005F994(work, map, pAnimation) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return NULL;
        }
        else
        {
            work->field_30_mtx = pMtx;
        }
    }
    return work;
}

AnimeWork *sub_8005FCA4(DG_PRIM *pPrim, int map, ANIMATION *pAnimation)
{
    AnimeWork *work = NewAnime_8005FBC8(NULL, map, pAnimation);

    if (work && pPrim)
    {
        work->field_24_pPrim->world = pPrim->world;
    }

    return work;
}
