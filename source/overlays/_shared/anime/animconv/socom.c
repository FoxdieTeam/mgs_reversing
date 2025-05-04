#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anim_data_800CC124[] = {
    0x00,0x1d,0x03,0x00, 0x09,0x00,0x10,0x00,
    0x1b,0x09,0x0b,0xb8, 0x02,0x00,0x01,0x0f,
    0x07,0x03,0x0a,0xff, 0x38,0xff,0x38,0x02,
    0x00,0x01,0x0f,0x07, 0x03,0x0a,0xfe,0x98,
    0xfe,0xfc,0x02,0x00, 0x01,0x0f
};

static ANIMATION anm_800C3B78 = {
    PCX_SOCOM_F,                // field_0_texture_hash
    2,                          // field_2
    2,                          // field_4
    4,                          // n_anims
    1,                          // n_vertices
    300,                        // field_A
    1,                          // field_C
    800,                        // field_E_xw
    800,                        // field_10_yh
    128,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800CC124  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800CC14C[] = {
    0x00,0x13,0x01,0x00, 0x05,0x0c,0x00,0x07,
    0x01,0xff,0x0a,0x00, 0x46,0x00,0x46,0x08,
    0xf0,0xf0,0xf0,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_800C3B94 = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    500,                        // field_A
    1,                          // field_C
    400,                        // field_E_xw
    400,                        // field_10_yh
    128,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800CC14C  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800CC164[] = {
    0x00,0x5B,0x04,0x00, 0x0b,0x00,0x1e,0x00,
    0x36,0x00,0x4e,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x00,0xc8,0x00, 0xc8,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x01,
    0x90,0x01,0x90,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0x2c,0x01, 0x2c,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x03,
    0x20,0x03,0x20,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0x90,0x01, 0x90,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x04,
    0xb0,0x04,0xb0,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0xf4,0x01, 0xf4,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f
};

static ANIMATION anm_800C3BB0 = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    500,                        // field_A
    1,                          // field_C
    400,                        // field_E_xw
    400,                        // field_10_yh
    128,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800CC164  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800CC1CC[] = {
    0x00,0x6b,0x04,0x00, 0x0b,0x00,0x22,0x00,
    0x3e,0x00,0x5a,0x08, 0xff,0xff,0xff,0x0c,
    0x00,0x07,0x01,0xff, 0x0a,0x00,0xc8,0x00,
    0xc8,0x08,0xf0,0xf0, 0xf0,0x02,0x00,0x01,
    0x0d,0x0f,0x08,0xff, 0xff,0xff,0x0a,0x01,
    0x90,0x01,0x90,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0x2c,0x01, 0x2c,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f,0x08,0xff,
    0xff,0xff,0x0a,0x03, 0x20,0x03,0x20,0x0c,
    0x00,0x07,0x01,0xff, 0x0a,0x01,0x90,0x01,
    0x90,0x08,0xf0,0xf0, 0xf0,0x02,0x00,0x01,
    0x0d,0x0f,0x08,0xff, 0xff,0xff,0x0a,0x04,
    0xb0,0x04,0xb0,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0xf4,0x01, 0xf4,0x08,0xf0,0xf0,
    0xf0,0x02,0x00,0x01, 0x0d,0x0f
};

static ANIMATION anm_800C3BCC = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    500,                        // field_A
    1,                          // field_C
    400,                        // field_E_xw
    400,                        // field_10_yh
    0,                          // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800CC1CC  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800CC244[] = {
    0x00,0x5B,0x04,0x00, 0x0b,0x00,0x1e,0x00,
    0x36,0x00,0x4e,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x00,0xc8,0x00, 0xc8,0x08,0xfc,0xfc,
    0xfc,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x01,
    0x90,0x01,0x90,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0x2c,0x01, 0x2c,0x08,0xfc,0xfc,
    0xfc,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x03,
    0x20,0x03,0x20,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0x90,0x01, 0x90,0x08,0xfc,0xfc,
    0xfc,0x02,0x00,0x01, 0x0d,0x0f,0x0a,0x04,
    0xb0,0x04,0xb0,0x0c, 0x00,0x07,0x01,0xff,
    0x0a,0x01,0xf4,0x01, 0xf4,0x08,0xfc,0xfc,
    0xfc,0x02,0x00,0x01, 0x0d,0x0f
};

static ANIMATION anm_800C3BE8 = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    500,                        // field_A
    2,                          // field_C
    400,                        // field_E_xw
    400,                        // field_10_yh
    32,                         // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800CC244  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

extern ANIMATION stru_8009F0D4;
extern ANIMATION stru_8009F0F0;

void AN_Unknown_800D6898(MATRIX *pos)
{
    PRESCRIPT  pre;
    SVECTOR   *pPos;
    SVECTOR   *pSpeed;
    ANIMATION *anm;
    SVECTOR    sp28;
    MATRIX     sp30;
    int        rnd;

    pPos = &pre.pos;
    pSpeed = &pre.speed;

    pre.speed = DG_ZeroVector;

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

    anm = &anm_800C3B78;
    anm->pre_script = &pre;

    pPos->vx = pos->t[0];
    pPos->vy = pos->t[1];
    pPos->vz = pos->t[2];
    pre.scr_num = 0;

    NewAnime(NULL, 0, anm);

    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 420;

    DG_SetPos(pos);
    DG_MovePos(&sp28);
    ReadRotMatrix(&sp30);

    pPos->vx = sp30.t[0];
    pPos->vy = sp30.t[1];
    pPos->vz = sp30.t[2];
    pre.scr_num = 2;

    NewAnime(NULL, 0, anm);

    if (GV_RandU(16) >= 5)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -800;

        DG_SetPos(pos);
        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = GV_RandU(32) - 100;
        sp28.vy = GV_RandU(32) + 15;
        sp28.vz = GV_RandU(64) + 100;

        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = sp30.t[2] - pPos->vz;
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }

    if (GV_RandU(16) >= 9)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -500;

        DG_SetPos(pos);
        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -GV_RandU(32);

        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = pPos->vz - sp30.t[2];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }
}

void AN_Unknown_800D6BCC(SVECTOR *pos, SVECTOR *rot)
{
    PRESCRIPT  pre;
    SVECTOR   *pPos;
    SVECTOR   *pSpeed;
    ANIMATION *anm;
    SVECTOR    sp28[4];
    SVECTOR    sp48[6]; // The stack has an extra 32 unused bytes
    int        rnd;

    pPos = &pre.pos;
    pSpeed = &pre.speed;

    sp28[0].vx = 0;
    sp28[0].vy = 0;
    sp28[0].vz = 250;

    sp28[1].vx = 0;
    sp28[1].vy = 0;
    sp28[1].vz = 420;

    sp28[2].vx = -100;
    sp28[2].vy = 0;
    sp28[2].vz = -800;

    sp28[3].vx = 0;
    sp28[3].vy = 0;
    sp28[3].vz = -500;

    DG_SetPos2(pos, rot);
    DG_PutVector(sp28, sp28, 4);

    sp48[0].vx = -100 - GV_RandU(32);
    sp48[0].vy = GV_RandU(32) + 15;
    sp48[0].vz = GV_RandS(4);

    sp48[1].vx = 0;
    sp48[1].vy = 0;
    sp48[1].vz = -GV_RandU(32);

    DG_SetPos2(&DG_ZeroVector, rot);
    DG_PutVector(sp48, sp48, 2);

    pre.speed = DG_ZeroVector;

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

    anm = &anm_800C3B78;
    anm->pre_script = &pre;

    *pPos = *pos;
    pre.scr_num = 0;

    NewAnime(NULL, 0, anm);

    *pPos = sp28[1];
    pre.scr_num = 2;

    NewAnime(NULL, 0, anm);

    if (GV_RandU(16) >= 5)
    {
        *pPos = sp28[2];
        *pSpeed = sp48[0];
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }

    if (GV_RandU(16) >= 9)
    {
        *pPos = sp28[3];
        *pSpeed = sp48[1];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }
}

void AN_Unknown_800D6EB0(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3B94;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D6F6C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BB0;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D7028(SVECTOR *pos, int num)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = num;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BE8;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D70E4(SVECTOR *pos, char r, char g, char b)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BCC;
    anm->pre_script = &pre;

    anm->field_18_ptr[12] = r;
    anm->field_18_ptr[13] = g;
    anm->field_18_ptr[14] = b;

    anm->field_18_ptr[35] = r;
    anm->field_18_ptr[36] = g;
    anm->field_18_ptr[37] = b;

    anm->field_18_ptr[63] = r;
    anm->field_18_ptr[64] = g;
    anm->field_18_ptr[65] = b;

    anm->field_18_ptr[91] = r;
    anm->field_18_ptr[92] = g;
    anm->field_18_ptr[93] = b;

    anm->field_18_ptr[26] = -((r - 1) / 7);
    anm->field_18_ptr[27] = -((g - 1) / 7);
    anm->field_18_ptr[28] = -((b - 1) / 7);

    anm->field_18_ptr[54] = -((r - 1) / 7);
    anm->field_18_ptr[55] = -((g - 1) / 7);
    anm->field_18_ptr[56] = -((b - 1) / 7);

    anm->field_18_ptr[82] = -((r - 1) / 7);
    anm->field_18_ptr[83] = -((g - 1) / 7);
    anm->field_18_ptr[84] = -((b - 1) / 7);

    anm->field_18_ptr[110] = -((r - 1) / 7);
    anm->field_18_ptr[111] = -((g - 1) / 7);
    anm->field_18_ptr[112] = -((b - 1) / 7);

    NewAnime(NULL, 0, anm);
}
