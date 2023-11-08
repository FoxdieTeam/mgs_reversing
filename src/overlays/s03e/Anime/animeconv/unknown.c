#include "Anime/animeconv/anime.h"

extern SVECTOR DG_ZeroVector_800AB39C;

extern ANIMATION anm_800C335C;
extern ANIMATION anm_800C3378;
extern ANIMATION anm_800C3394;
extern ANIMATION anm_800C33B0;

extern unsigned short s03e_dword_800C33CC[];

void AN_Unknown_800C9CBC(MATRIX *world, int index)
{
    PRESCRIPT  pre;
    ANIMATION *anm;
    SVECTOR   *pos;

    anm = NULL;

    pos = &pre.pos;
    pos->vx = 0;
    pos->vy = 800;
    pos->vz = 0;

    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = 0;

    switch(index)
    {
    case 0:
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C335C;
        break;

    case 1:
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C335C;
        break;

    case 2:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3378;
        break;

    case 3:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3378;
        break;

    case 4:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3394;
        break;

    case 5:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3394;
        break;

    case 6:
        pre.scr_num = 1;
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[2];
        anm = &anm_800C335C;
        break;
    }

    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(world, 0, anm);
}

void AN_Unknown_800C9DF0(MATRIX *world, int index)
{
    PRESCRIPT  pre;
    ANIMATION *anm;
    SVECTOR   *pos;

    anm = NULL;

    pos = &pre.pos;
    pos->vx = 0;
    pos->vy = 600;
    pos->vz = 0;

    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 1;
    pre.s_anim = 0;

    switch(index)
    {
    case 0:
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C335C;
        break;

    case 1:
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C335C;
        break;

    case 2:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3378;
        break;

    case 3:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3378;
        break;

    case 4:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3394;
        break;

    case 5:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3394;
        break;

    case 6:
        pre.scr_num = 2;
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[2];
        anm = &anm_800C335C;
        break;
    }

    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(world, 0, anm);
}

void AN_Unknown_800C9F28(MATRIX *world, int index)
{
    PRESCRIPT  pre;
    ANIMATION *anm;
    SVECTOR   *pos;

    anm = NULL;

    pos = &pre.pos;
    pos->vx = 0;
    pos->vy = 120;
    pos->vz = 0;

    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 2;
    pre.s_anim = 0;

    switch(index)
    {
    case 0:
        pre.scr_num = 3;
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C335C;
        break;

    case 1:
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C335C;
        break;

    case 2:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3378;
        break;

    case 3:
        anm_800C3378.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3378;
        break;

    case 4:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[0];
        anm = &anm_800C3394;
        break;

    case 5:
        anm_800C3394.field_0_texture_hash = s03e_dword_800C33CC[1];
        anm = &anm_800C3394;
        break;

    case 6:
        pre.scr_num = 3;
        anm_800C335C.field_0_texture_hash = s03e_dword_800C33CC[2];
        anm = &anm_800C335C;
        break;
    }

    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(world, 0, anm);
}

void AN_Unknown_800CA064(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_800C33B0;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(NULL, 0, anm);
}
