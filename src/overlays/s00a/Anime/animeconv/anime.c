#include "Anime/animeconv/anime.h"

extern ANIMATION anm_breath_800C32E8;
extern ANIMATION anm_unknown_800C3304;

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
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
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
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
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
    speed->vx = GV_RandU_80017090( 16 );
    speed->vy = GV_RandS_800170BC( 16 ) + 20;
    speed->vz = GV_RandS_800170BC( 8 );

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_unknown_800C3304;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}