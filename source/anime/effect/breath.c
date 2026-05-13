#include "common.h"
#include "libgv/libgv.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anm_breath_data[] = {
    0x00,0x49,0x02,0x00, 0x07,0x00,0x29,0x01,
    0xfe,0x0c,0x00,0x06, 0x08,0x06,0x06,0x06,
    0x01,0xff,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x23,0x08,0xff,0xff, 0xff,0x0a,0x00,0x08,
    0x00,0x08,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0f,0x0a,0xff,0x38, 0xff,0x38,0x01,0xfe,
    0x0c,0x00,0x06,0x08, 0x06,0x06,0x06,0x01,
    0xff,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x23,
    0x08,0xff,0xff,0xff, 0x0a,0x00,0x06,0x00,
    0x06,0x01,0xff,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_breath_form = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    500,                        // size_w
    500,                        // size_h
    0,                          // v
    NULL,                       // pre_script
    (char *)anm_breath_data     // script
};

/*---------------------------------------------------------------------------*/

static const char anm_unknown_data[] = {
    0x00,0x2c,0x01,0x00, 0x05,0x01,0xfe,0x0c,
    0x00,0x03,0x08,0x06, 0x06,0x06,0x01,0xff,
    0x02,0x00,0x01,0x0d, 0x0c,0x00,0x10,0x08,
    0xff,0xff,0xff,0x0a, 0x00,0x04,0x00,0x04,
    0x01,0xff,0x02,0x00, 0x01,0x0a,0x00,0x04,
    0x00,0x04,0x01,0xff, 0x02,0x00,0x01,0x0d,
    0x0f
};

static ANIMATION anm_unknown = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    500,                        // size_w
    500,                        // size_h
    0,                          // v
    NULL,                       // pre_script
    (char *)anm_unknown_data    // script
};

/*---------------------------------------------------------------------------*/

void AN_Breath( MATRIX *matrix )
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *speed;

    pre.pos.vx = matrix->t[0];
    pre.pos.vy = matrix->t[1];
    pre.pos.vz = matrix->t[2];

    speed = &pre.speed;
    speed->vx = 10;
    speed->vy = 10;
    speed->vz = 0;

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_breath_form;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void AN_Breath_2( MATRIX *matrix )
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *speed;

    pre.pos.vx = matrix->t[0];
    pre.pos.vy = matrix->t[1];
    pre.pos.vz = matrix->t[2];

    speed = &pre.speed;
    speed->vx = 3;
    speed->vy = 3;
    speed->vz = 0;

    pre.scr_num = 1;
    pre.s_anim = 0;

    anm = &anm_breath_form;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void AN_Unknown_800C3B7C( MATRIX *matrix )
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *speed;

    pre.pos.vx = matrix->t[0];
    pre.pos.vy = matrix->t[1];
    pre.pos.vz = matrix->t[2];

    speed = &pre.speed;
    speed->vx = GV_RandU( 16 );
    speed->vy = GV_RandS( 16 ) + 20;
    speed->vz = GV_RandS( 8 );

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_unknown;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}
