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
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    300,                        // field_A
    1,                          // field_C
    500,                        // field_E_xw
    500,                        // field_10_yh
    0,                          // field_12_rgb
    NULL,                       // pre_script
    (char *)anm_breath_data     // field_18_ptr
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
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    300,                        // field_A
    1,                          // field_C
    500,                        // field_E_xw
    500,                        // field_10_yh
    0,                          // field_12_rgb
    NULL,                       // pre_script
    (char *)anm_unknown_data    // field_18_ptr
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
