#include "common.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

const char s00a_dword_800DFBE0[] = 
{ 
    0x00, 0x49, 0x02, 0x00, 
    0x07, 0x00, 0x29, 0x01,
    0xFE, 0x0C, 0x00, 0x06,
    0x08, 0x06, 0x06, 0x06,
    0x01, 0xFF, 0x02, 0x00,
    0x01, 0x0D, 0x0C, 0x00,
    0x23, 0x08, 0xFF, 0xFF,
    0xFF, 0x0A, 0x00, 0x08,
    0x00, 0x08, 0x01, 0xFF,
    0x02, 0x00, 0x01, 0x0D,
    0x0F, 0x0A, 0xFF, 0x38,
    0xFF, 0x38, 0x01, 0xFE,
    0x0C, 0x00, 0x06, 0x08,
    0x06, 0x06, 0x06, 0x01,
    0xFF, 0x02, 0x00, 0x01,
    0x0D, 0x0C, 0x00, 0x23,
    0x08, 0xFF, 0xFF, 0xFF,
    0x0A, 0x00, 0x06, 0x00,
    0x06, 0x01, 0xFF, 0x02,
    0x00, 0x01, 0x0D, 0x0F
};

  
  

const char s00a_dword_800DFC30[] =
{ 
    0x00, 0x2C, 0x01, 0x00,
    0x05, 0x01, 0xFE, 0x0C,
    0x00, 0x03, 0x08, 0x06,
    0x06, 0x06, 0x01, 0xFF,
    0x02, 0x00, 0x01, 0x0D,
    0x0C, 0x00, 0x10, 0x08,
    0xFF, 0xFF, 0xFF, 0x0A,
    0x00, 0x04, 0x00, 0x04,
    0x01, 0xFF, 0x02, 0x00,
    0x01, 0x0A, 0x00, 0x04,
    0x00, 0x04, 0x01, 0xFF,
    0x02, 0x00, 0x01, 0x0D,
    0x0F 
};

ANIMATION anm_breath_800C32E8  = { PCX_SMOKE, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (char *)s00a_dword_800DFBE0 };
ANIMATION anm_unknown_800C3304 = { PCX_SMOKE, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (char *)s00a_dword_800DFC30 };

void AN_Breath_800C3AA8( MATRIX *matrix )
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

    anm = &anm_breath_800C32E8;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void AN_Breath_2_800C3B10( MATRIX *matrix )
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

    anm = &anm_breath_800C32E8;
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

    anm = &anm_unknown_800C3304;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}