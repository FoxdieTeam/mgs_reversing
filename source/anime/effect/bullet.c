#include "mgstype.h"
#include "game/game.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char animation_data_800124A8[] = {
    0x00,0x8b,0x03,0x00, 0x09,0x00,0x34,0x00, 0x64,0x01,0xfe,0x02, 0x00,0x01,0x0c,0x00,
    0x08,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x04,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x0a,0xff, 0xf6,0xff,0xf6,0x02,
    0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0xff, 0xf6,0xff,0xf6,0x02, 0x00,0x01,0x0c,0x00,
    0x10,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x04,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x0a,0xff, 0xf6,0xff,0xf6,0x02,
    0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0x00, 0x1e,0x00,0x1e,0x02, 0x00,0x01,0x0c,0x00,
    0x10,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x04,0x01,0xff,0x06, 0x00,0x00,0xff,0xec, 0x00,0x00,0x0a,0xff, 0xf6,0xff,0xf6,0x02,
    0x00,0x01,0x0d,0x0f
};

ANIMATION stru_8009F0D4 = {
    PCX_WT_SUD11,               // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    0,                          // raise
    5,                          // amb
    50,                         // size_w
    50,                         // size_h
    250,                        // v
    NULL,                       // pre_script
    (char *)animation_data_800124A8 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_8001253C[] = {
    0x00,0x83,0x04,0x00, 0x0b,0x00,0x33,0x00, 0x5a,0x00,0x74,0x01, 0xfe,0x01,0xff,0x08,
    0x01,0x01,0x01,0x0c, 0x00,0x05,0x08,0x02, 0x02,0x02,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x14,0x01, 0xff,0x0a,0x00,0x1e, 0x00,0x1e,0x08,0xfe, 0xfe,0xfe,0x02,0x00,
    0x01,0x0d,0x0f,0x01, 0xfe,0x0a,0xfe,0xd4, 0xfe,0xd4,0x0c,0x00, 0x05,0x08,0x02,0x02,
    0x02,0x01,0xff,0x02, 0x00,0x01,0x0d,0x0c, 0x00,0x14,0x01,0xff, 0x0a,0x00,0x1e,0x00,
    0x1e,0x08,0xfe,0xfe, 0xfe,0x02,0x00,0x01, 0x0d,0x0f,0x01,0xfe, 0x0a,0xff,0x9c,0xff,
    0x9c,0x0c,0x00,0x0e, 0x0a,0xff,0xfe,0xff, 0xfe,0x08,0xfe,0xfe, 0xfe,0x01,0xff,0x02,
    0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0x01, 0xf4,0x01,0xf4,0x0c, 0x00,0x1d,0x0a,0x00,
    0x14,0x00,0x14,0x08, 0xff,0xff,0xff,0x01, 0xff,0x02,0x00,0x01, 0x0d,0x0f
};

ANIMATION stru_8009F0F0 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    400,                        // size_w
    400,                        // size_h
    32,                         // v
    NULL,                       // pre_script
    (char *)animation_data_8001253C // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_800125CC[] = {
    0x00,0x1d,0x03,0x00, 0x09,0x00,0x10,0x00, 0x1b,0x09,0x03,0xe8, 0x02,0x00,0x01,0x0f,
    0x07,0x03,0x0a,0xff, 0x38,0xff,0x38,0x02, 0x00,0x01,0x0f,0x07, 0x03,0x0a,0xfe,0xfc,
    0xfe,0xfc,0x02,0x00, 0x01,0x0f
};

static ANIMATION stru_8009F10C = {
    PCX_SOCOM_F,                // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    400,                        // size_w
    400,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_800125CC // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_800125F4[] = {
    0x00,0x1d,0x03,0x00, 0x09,0x00,0x10,0x00, 0x1b,0x09,0x03,0xe8, 0x02,0x00,0x01,0x0f,
    0x07,0x03,0x0a,0xfd, 0xa8,0xfd,0xa8,0x02, 0x00,0x01,0x0f,0x07, 0x03,0x0a,0xfc,0x7c,
    0xfc,0x7c,0x02,0x00, 0x01,0x0f
};

static ANIMATION stru_8009F128 = {
    PCX_SOCOM_F,                // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    1400,                       // size_w
    1400,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_800125F4 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_8001261C[] = {
    0x00,0x04,0x01,0x00, 0x05,0x02,0x00,0x01, 0x0f
};

static ANIMATION stru_8009F144 = {
    PCX_SOCOM_F,                // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    400,                        // size_w
    400,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_8001261C // script
};

/*---------------------------------------------------------------------------*/

static const char anm_gunflash_form_script[] = {
    0x00,0x07,0x01,0x00, 0x05,0x09,0x03,0xe8, 0x02,0x00,0x01,0x0f,
};

static ANIMATION anm_gunflash_form = {
    PCX_FA_FL10,                // tex
    2,                          // texdev_x
    2,                          // texdev_y
    3,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    600,                        // size_w
    600,                        // size_h
    100,                        // v
    NULL,                       // pre_script
    (char *)anm_gunflash_form_script // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_80012634[] = {
    0x00,0xcb,0x02,0x00, 0x07,0x00,0x79,0x0c, 0x00,0x0b,0x06,0x00, 0x00,0xff,0xec,0x00,
    0x00,0x02,0x00,0x01, 0x0d,0x0b,0x2b,0x05, 0x00,0x00,0x00,0x14, 0x00,0x00,0x86,0xff,
    0xf6,0x00,0x01,0xff, 0xf6,0x86,0x00,0x0a, 0x00,0x01,0x00,0x0a, 0x0c,0x00,0x04,0x01,
    0xff,0x02,0x00,0x01, 0x0d,0x06,0x00,0x00, 0xff,0xd8,0x00,0x00, 0x0c,0x00,0x04,0x01,
    0xff,0x02,0x00,0x01, 0x0d,0x06,0x00,0x00, 0x00,0x00,0x00,0x00, 0x0c,0x00,0x02,0x01,
    0xff,0x0b,0x2b,0x02, 0x00,0x02,0x0d,0x0c, 0x00,0x02,0x01,0xff, 0x02,0x00,0x02,0x0d,
    0x05,0x00,0x00,0x00, 0x00,0x00,0x00,0x07, 0x01,0x08,0xd8,0xd8, 0xd8,0x0c,0x00,0x04,
    0x08,0xf0,0xf0,0xf0, 0x02,0x00,0x01,0x0d, 0x0f,0x0c,0x00,0x0b, 0x06,0x00,0x00,0xff,
    0xec,0x00,0x00,0x02, 0x00,0x01,0x0d,0x05, 0x00,0x00,0x00,0x00, 0x00,0x00,0x86,0xff,
    0xec,0x00,0x01,0xff, 0xec,0x86,0x00,0x14, 0x00,0x01,0x00,0x14, 0x0c,0x00,0x02,0x01,
    0xff,0x0b,0x2b,0x02, 0x00,0x01,0x0d,0x0c, 0x00,0x04,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x04,0x01, 0xff,0x02,0x00,0x02, 0x0d,0x05,0x00,0x00, 0x00,0x00,0x00,0x00,
    0x07,0x01,0x08,0xd8, 0xd8,0xd8,0x0c,0x00, 0x04,0x08,0xf0,0xf0, 0xf0,0x02,0x00,0x01,
    0x0d,0x0f
};

static ANIMATION stru_8009F17C = {
    PCX_MAGAZIN,                // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    200,                        // raise
    5,                          // amb
    100,                        // size_w
    100,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_80012634 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_80012708[] = {
    0x00,0x19,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x14,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x0a,0x01, 0xff,0x08,0xf9,0xf9, 0xf9,0x02,0x00,0x01, 0x0d,0x0f
};

static ANIMATION stru_8009F198 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    8,                          // n_verts
    0,                          // raise
    3,                          // amb
    2200,                       // size_w
    2200,                       // size_h
    77,                         // v
    NULL,                       // pre_script
    (char *)animation_data_80012708 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_80012728[] = {
    0x00,0x23,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x0a,0x01,0xff, 0x0a,0x00,0x50,0x00,
    0x50,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x05, 0x0a,0x00,0x50,0x00, 0x50,0x01,0xff,0x08,
    0xf2,0xf2,0xf2,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION stru_8009F1B4 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    0,                          // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    77,                         // v
    NULL,                       // pre_script
    (char *)animation_data_80012728 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_80012750[] = {
    0x00,0x4a,0x02,0x00, 0x07,0x00,0x20,0x01, 0xfe,0x0c,0x00,0x05, 0x01,0xff,0x02,0x00,
    0x01,0x0d,0x0c,0x00, 0x0a,0x01,0xff,0x08, 0xf4,0xf4,0xf4,0x02, 0x00,0x01,0x0d,0x0f,
    0x01,0xfe,0x0c,0x00, 0x04,0x0a,0x01,0x2c, 0x01,0x2c,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x0a,0x0a, 0x00,0x46,0x00,0x46, 0x01,0xff,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x0a,0x01,0xff,0x0a, 0x00,0x50,0x00,0x50, 0x08,0xe7,0xe7,0xe7, 0x02,0x00,0x01,0x0d,
    0x0f
};

static ANIMATION stru_8009F1D0 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    4,                          // n_verts
    0,                          // raise
    1,                          // amb
    2200,                       // size_w
    2200,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_80012750 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_800127A4[] = {
    0x00,0x27,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x05,0x01,0xff, 0x0a,0x00,0x64,0x00,
    0x64,0x08,0xf6,0xf6, 0xf6,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x05, 0x01,0xff,0x0a,0x00,
    0xc8,0x00,0xc8,0x08, 0xf3,0xf3,0xf3,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION stru_8009F1EC = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    1000,                       // raise
    3,                          // amb
    400,                        // size_w
    400,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_800127A4 // script
};

/*---------------------------------------------------------------------------*/

static const char animation_data_800127D0[] = {
    0x00,0x39,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x14,0x01,0xff, 0x0a,0x00,0x01,0x00,
    0x01,0x08,0x05,0x05, 0x05,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x0c, 0x01,0xff,0x0a,0x00,
    0x05,0x00,0x05,0x08, 0xfb,0xfb,0xfb,0x02, 0x00,0x01,0x0d,0x0c, 0x00,0x0a,0x01,0xff,
    0x0a,0x00,0x0a,0x00, 0x0a,0x08,0xfb,0xfb, 0xfb,0x02,0x00,0x01, 0x0d,0x0f
};

static ANIMATION stru_8009F208 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    1000,                       // raise
    3,                          // amb
    30,                         // size_w
    30,                         // size_h
    10,                         // v
    NULL,                       // pre_script
    (char *)animation_data_800127D0 // script
};

int dword_8009F224 = 0;

/*---------------------------------------------------------------------------*/

void *AN_FamasFlash(MATRIX *pMtx)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    int rnd;

    pre.pos.vx = pMtx->t[ 0 ];
    pre.pos.vy = pMtx->t[ 1 ];
    pre.pos.vz = pMtx->t[ 2 ];
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

    anm = &anm_gunflash_form;
    anm->pre_script = &pre;

    return NewAnime( NULL, 0, anm );
}

void AN_BulletSmoke(MATRIX *arg0, int arg1)
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

void AN_SocomFlash(MATRIX *pMatrix1, MATRIX *pMatrix2, int mode)
{
    PRESCRIPT  pre;
    MATRIX     m;
    SVECTOR    move;
    int        randu;
    ANIMATION *anm;
    SVECTOR   *pos;
    SVECTOR   *speed;

    pos = &pre.pos;

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

    speed = &pre.speed;

    speed->vx = m.t[ 0 ] - pos->vx;
    speed->vy = m.t[ 1 ] - pos->vy;
    speed->vz = m.t[ 2 ] - pos->vz;
    pre.scr_num = 1;
    pre.s_anim = 0;

    anm = &stru_8009F0D4;
    stru_8009F0D4.pre_script = &pre;

    NewAnime(NULL, 0, anm);

    if (mode != 1)
    {
        pre.speed = DG_ZeroVector;

        randu = GV_RandU(16);
        if (randu >= 7)
        {
            pre.s_anim = 3;
        }
        else if (randu >= 5)
        {
            pre.s_anim = 2;
        }
        else if (randu >= 3)
        {
            pre.s_anim = 1;
        }
        else
        {
            pre.s_anim = 0;
        }

        anm = &stru_8009F10C;
        anm->pre_script = &pre;

        move.vx = 0;
        move.vy = -270;
        move.vz = 0;

        DG_SetPos(pMatrix1);
        DG_MovePos(&move);
        ReadRotMatrix(&m);

        pos->vx = m.t[ 0 ];
        pos->vy = m.t[ 1 ];
        pos->vz = m.t[ 2 ];

        pre.scr_num = 0;
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

        pre.scr_num = 1;
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

        pre.scr_num = 2;
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

        pre.scr_num = 2;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }

    DG_SetPos(pMatrix1);

    pos = &pre.pos;

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

    speed = &pre.speed;

    speed->vx = m.t[ 0 ] - pos->vx;
    speed->vy = m.t[ 1 ] - pos->vy;
    speed->vz = m.t[ 2 ] - pos->vz;
    pre.scr_num = 0;

    anm = &stru_8009F0F0;
    anm->pre_script = &pre;

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
    PRESCRIPT pre[4];
    int       i;

    sp18.vx = arg1->vx;
    sp18.vy = arg1->vy - 448;
    sp18.vz = arg1->vz;

    sp10.vx = 0;
    sp10.vy = 30;

    for (i = 0; i < 3; i++)
    {
        sp10.vz = GV_RandU(64) + 150;
        pre[ i ].pos = *arg0;
        sp18.vy += 128;

        DG_SetPos2(arg0, &sp18);
        DG_RotVector(&sp10, &pre[ i ].speed, 1);

        pre[ i ].scr_num = 0;
        pre[ i ].s_anim = 0;
    }

    pre[3].pos = *arg0;
    pre[3].speed = DG_ZeroVector;
    pre[3].scr_num = 1;
    pre[3].s_anim = 0;

    stru_8009F1D0.pre_script = pre;
    NewAnime( NULL, 0, &stru_8009F1D0 );
}

void NewAnime_8005E090(SVECTOR *pPos)
{
    SVECTOR axis;
    SVECTOR speed_in;
    SVECTOR speed_out;
    MATRIX rot;
    PRESCRIPT pre[8];
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

        pre[ i ].s_anim = 0;
        pre[ i ].pos = *pPos;
        pre[ i ].scr_num = 0;

        RotMatrixYXZ(&axis, &rot);
        ApplyMatrixSV(&rot, &speed_in, &speed_out);

        pre[ i ].speed.vx = speed_out.vx;
        pre[ i ].speed.vy = speed_out.vy;
        pre[ i ].speed.vz = speed_out.vz;
    }

    anm = &stru_8009F198;
    anm->pre_script = pre;

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
    PRESCRIPT pre;

    m = *pMatrix;
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0;
    ApplyMatrixSV(&m, &vec1, &vec2);
    pre.pos.vx = pMatrix->t[ 0 ] + vec2.vx;
    pre.pos.vy = pMatrix->t[ 1 ] + vec2.vy;
    pre.pos.vz = pMatrix->t[ 2 ] + vec2.vz;
    pre.speed.vx = 0;
    pre.speed.vy = 0;
    pre.speed.vz = 0;
    pre.scr_num = 0;
    pre.s_anim = 0;
    stru_8009F1B4.pre_script = &pre;
    NewAnime(NULL, 0, &stru_8009F1B4);
}

void AN_HeavyFlash(MATRIX *rotation)
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

void AN_RecoilSmoke(SVECTOR *pos)
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
