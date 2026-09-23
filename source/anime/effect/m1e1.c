#include "mgstype.h"
#include "game/game.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anm_caterpiller_smoke_form_script[] = {
    0x00,0x27,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x05,0x01,0xff, 0x0a,0x00,0x64,0x00,
    0x64,0x08,0xf1,0xf1, 0xf1,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x05, 0x01,0xff,0x0a,0x01,
    0x2c,0x01,0x2c,0x08, 0xe2,0xe2,0xe2,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_caterpiller_smoke_form = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    1000,                       // raise
    3,                          // amb
    500,                        // size_w
    500,                        // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anm_caterpiller_smoke_form_script // script
};

static const char animation_data_80013488[] = {
    0x00,0x4a,0x02,0x00, 0x07,0x00,0x20,0x01, 0xfe,0x0c,0x00,0x05, 0x01,0xff,0x02,0x00,
    0x01,0x0d,0x0c,0x00, 0x0a,0x01,0xff,0x08, 0xfa,0xfa,0xfa,0x02, 0x00,0x01,0x0d,0x0f,
    0x01,0xfe,0x0c,0x00, 0x04,0x0a,0x01,0x2c, 0x01,0x2c,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x0a,0x0a, 0x00,0x46,0x00,0x46, 0x01,0xff,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x0a,0x01,0xff,0x0a, 0x00,0x50,0x00,0x50, 0x08,0xf0,0xf0,0xf0, 0x02,0x00,0x01,0x0d,
    0x0f
};

static ANIMATION stru_8009F758 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    3,                          // n_verts
    0,                          // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    64,                         // v
    NULL,                       // pre_script
    (char *)animation_data_80013488 // script
};

static const char animation_data_800134DC[] = {
    0x00,0x2c,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x05,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x05,0x01, 0xff,0x0a,0x00,0x05, 0x00,0x05,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x0f,0x01,0xff,0x08, 0xf0,0xf0,0xf0,0x0a, 0x00,0x05,0x00,0x05, 0x02,0x00,0x01,0x0d,
    0x0f
};

static ANIMATION stru_8009F774 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    8,                          // n_verts
    0,                          // raise
    3,                          // amb
    2200,                       // size_w
    2200,                       // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)animation_data_800134DC // script
};

static const char animation_data_80013510[] = {
    0x00,0x49,0x03,0x00, 0x09,0x00,0x1e,0x00, 0x38,0x01,0xfe,0x0c, 0x00,0x04,0x02,0x00,
    0x01,0x0d,0x0c,0x00, 0x04,0x08,0xec,0xec, 0xec,0x02,0x00,0x01, 0x0d,0x0f,0x01,0xfe,
    0x0a,0xfc,0x18,0xfc, 0x18,0x0c,0x00,0x04, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x04,0x08,
    0xec,0xec,0xec,0x02, 0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0xfb, 0x50,0xfb,0x50,0x0c,
    0x00,0x04,0x02,0x00, 0x01,0x0d,0x0c,0x00, 0x04,0x08,0xec,0xec, 0xec,0x02,0x00,0x01,
    0x0d,0x0f
};

static ANIMATION stru_8009F790 = {
    PCX_CANON_SEQ,              // tex
    2,                          // texdev_x
    2,                          // texdev_y
    4,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    5000,                       // size_w
    5000,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)animation_data_80013510 // script
};

/*---------------------------------------------------------------------------*/

void AN_CaterpillerSmoke(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &anm_caterpiller_smoke_form;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void demothrd_2_8007DA94(SVECTOR *pPosition, SVECTOR *pRotation)
{
    SVECTOR    rotation;
    SVECTOR    speed;
    PRESCRIPT  pre[3];
    int        i;
    ANIMATION *anm;

    rotation.vx = 0;
    rotation.vy = pRotation->vy - 512;
    rotation.vz = 0;

    for (i = 0; i < 2; i++)
    {
        pre[i].pos = *pPosition;
        pre[i].pos.vy += 400;

        speed.vx = 0;
        speed.vy = 30;
        speed.vz = 200;

        rotation.vy += 341;

        DG_SetPos2(&DG_ZeroVector, &rotation);
        DG_PutVector(&speed, &speed, 1);

        pre[i].speed = speed;
        pre[i].scr_num = 0;
        pre[i].s_anim = 0;
    }

    anm = &stru_8009F758;
    anm->pre_script = pre;

    pre[2].pos = *pPosition;
    pre[2].pos.vy += 400;
    pre[2].speed = DG_ZeroVector;
    pre[2].scr_num = 1;
    pre[2].s_anim = 0;

    NewAnime( NULL, 0, anm );
}

void sub_8007DC24(SVECTOR *pPosition)
{
    SVECTOR    rotation;
    SVECTOR    speed_in;
    SVECTOR    speed_out;
    PRESCRIPT  pre[8];
    int        i;
    ANIMATION *anm;

    rotation = DG_ZeroVector;
    rotation.vy += GV_RandU(512);

    speed_in = DG_ZeroVector;

    for (i = 0; i < 8; i++)
    {
        pre[i].pos = *pPosition;
        pre[i].pos.vy += 500;

        speed_in.vz = 100;
        rotation.vy += 512;

        DG_SetPos2(&DG_ZeroVector, &rotation);
        DG_PutVector(&speed_in, &speed_out, 1);

        pre[i].speed = speed_out;
        pre[i].scr_num = 0;
    }

    anm = &stru_8009F774;
    anm->pre_script = pre;

    NewAnime( NULL, 0, anm );
}

void sub_8007DD80(short param_1, SVECTOR *pPos)
{
    int i;
    SVECTOR vec1;
    SVECTOR vec2;
    SVECTOR speed_tmp;
    SVECTOR speed;
    PRESCRIPT pre[8];

    vec1 = DG_ZeroVector;
    vec2 = DG_ZeroVector;
    vec1.vy = param_1 - 512;
    speed_tmp = DG_ZeroVector;
    for (i = 0; i < 8; i++)
    {
        pre[i].pos = *pPos;
        pre[i].pos.vy -= 1000;
        speed_tmp.vz = GV_RandU(64) + 100;
        vec1.vy += 0x80;
        vec2.vy = vec1.vy + GV_RandS(0x40);
        DG_SetPos2(&DG_ZeroVector, &vec2);
        DG_PutVector(&speed_tmp, &speed, 1);
        pre[i].speed = speed;
        pre[i].scr_num = 0;
    }

    stru_8009F774.pre_script = pre;
    NewAnime(0, 0, &stru_8009F774);
}

void sub_8007DF10(SVECTOR *pRotation, SVECTOR *pTranslation)
{
    ANIMATION *anm;
    SVECTOR    vin[3];
    SVECTOR    vout[3];
    PRESCRIPT  pre;

    pre.speed = DG_ZeroVector;

    vin[0] = DG_ZeroVector;
    vin[0].vz = 500;

    vin[1] = DG_ZeroVector;
    vin[1].vz = 2000;

    vin[2] = DG_ZeroVector;
    vin[2].vz = 3000;

    DG_SetPos2(pTranslation, pRotation);
    DG_PutVector(vin, vout, 3);

    anm = &stru_8009F790;
    anm->pre_script = &pre;

    pre.pos = vout[0];
    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    pre.pos = vout[1];
    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    pre.pos = vout[2];
    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );
}

void sub_8007E0AC(int y, SVECTOR *pPosition)
{
    ANIMATION *anm;
    SVECTOR    rotation;
    SVECTOR    vin;
    PRESCRIPT  pre[8];
    int        i;

    rotation.vx = 0;
    rotation.vy = y;
    rotation.vz = 0;

    vin = DG_ZeroVector;

    for ( i = 0; i < 8; i++ )
    {
        pre[i].pos = *pPosition;

        vin.vx = GV_RandU(64);
        vin.vz = GV_RandU(64);

        rotation.vz += 512;

        DG_SetPos2(&DG_ZeroVector, &rotation);
        DG_PutVector(&vin, &pre[i].speed, 1);
        pre[i].scr_num = 0;
    }

    anm = &stru_8009F774;
    anm->pre_script = pre;

    NewAnime( NULL, 0, anm );
}
