#include <stddef.h> // for NULL
#include "Anime/animeconv/anime.h"
#include "strcode.h"

const char s00a_dword_800DFBE0[] = {0x0, 'I', 0x2, 0x0};
const char s00a_dword_800DFBE4[] = {0x7, 0x0, ')', 0x1};
const char s00a_dword_800DFBE8[] = {0xfe, 0xc, 0x0, 0x6};
const char s00a_dword_800DFBEC[] = {0x8, 0x6, 0x6, 0x6};
const char s00a_dword_800DFBF0[] = {0x1, 0xff, 0x2, 0x0};
const char s00a_dword_800DFBF4[] = {0x1, 0xd, 0xc, 0x0};
const char s00a_dword_800DFBF8[] = {'#', 0x8, 0xff, 0xff};
const char s00a_dword_800DFBFC[] = {0xff, '\n', 0x0, 0x8};
const char s00a_dword_800DFC00[] = {0x0, 0x8, 0x1, 0xff};
const char s00a_dword_800DFC04[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC08[] = {0xf, '\n', 0xff, '8'};
const char s00a_dword_800DFC0C[] = {0xff, '8', 0x1, 0xfe};
const char s00a_dword_800DFC10[] = {0xc, 0x0, 0x6, 0x8};
const char s00a_dword_800DFC14[] = {0x6, 0x6, 0x6, 0x1};
const char s00a_dword_800DFC18[] = {0xff, 0x2, 0x0, 0x1};
const char s00a_dword_800DFC1C[] = {0xd, 0xc, 0x0, '#'};
const char s00a_dword_800DFC20[] = {0x8, 0xff, 0xff, 0xff};
const char s00a_dword_800DFC24[] = {'\n', 0x0, 0x6, 0x0};
const char s00a_dword_800DFC28[] = {0x6, 0x1, 0xff, 0x2};
const char s00a_dword_800DFC2C[] = {0x0, 0x1, 0xd, 0xf};

const char s00a_dword_800DFC30[] = {0x0, ',', 0x1, 0x0};
const char s00a_dword_800DFC34[] = {0x5, 0x1, 0xfe, 0xc};
const char s00a_dword_800DFC38[] = {0x0, 0x3, 0x8, 0x6};
const char s00a_dword_800DFC3C[] = {0x6, 0x6, 0x1, 0xff};
const char s00a_dword_800DFC40[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC44[] = {0xc, 0x0, 0x10, 0x8};
const char s00a_dword_800DFC48[] = {0xff, 0xff, 0xff, '\n'};
const char s00a_dword_800DFC4C[] = {0x0, 0x4, 0x0, 0x4};
const char s00a_dword_800DFC50[] = {0x1, 0xff, 0x2, 0x0};
const char s00a_dword_800DFC54[] = {0x1, '\n', 0x0, 0x4};
const char s00a_dword_800DFC58[] = {0x0, 0x4, 0x1, 0xff};
const char s00a_dword_800DFC5C[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC60[] = {0xf};

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
    anm->pre_script = &pre;

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
    speed->vx = GV_RandU( 16 );
    speed->vy = GV_RandS( 16 ) + 20;
    speed->vz = GV_RandS( 8 );

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_unknown_800C3304;
    anm->pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}