#include "libgcl/hash.h"
#include "Anime/animeconv/anime.h"

const char anim_data_800D13CC[] = {0x0, '#',  0x2, 0x0,  0x7,  0x0,  0x1a, 0x2, 0x0, 0x1, 0x8, 'j', 'j', 'j', 0xc,
                                   0x0, '\n', 0x8, 0xf6, 0xf6, 0xf6, 0x2,  0x0, 0x1, 0xd, 0xf, 0x8, 'j', 'j', 'j',
                                   0xc, 0x0,  0x5, 0x8,  0xec, 0xec, 0xec, 0x2, 0x0, 0x1, 0xd, 0xf, 0x2, 0x8e};

ANIMATION anm_800C32F0 = {PCX_RCM_L, 1, 1, 1, 1, 250, 1, 40, 40, 255, NULL, (char *)anim_data_800D13CC};
ANIMATION anm_800C330C = {PCX_RCM_L, 1, 1, 1, 1, 2500, 1, 40, 40, 255, NULL, (char *)anim_data_800D13CC};

void s08c_800C4194(MATRIX *pos)
{
    PRESCRIPT prescript;
    MATRIX    mat;
    SVECTOR   svec;
    SVECTOR  *pos2, *speed;

    svec.vx = 0;
    svec.vy = 18;
    svec.vz = 130;

    speed = &prescript.speed;
    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;
    DG_SetPos_8001BC44(pos);
    DG_MovePos_8001BD20(&svec);
    ReadRotMatrix(&mat);

    pos2 = &prescript.pos;
    pos2->vx = mat.t[0];
    pos2->vy = mat.t[1];
    pos2->vz = mat.t[2];

    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C32F0.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C32F0);
}

void s08c_800C4220(MATRIX *pos)
{
    PRESCRIPT prescript;
    MATRIX    mat;
    SVECTOR   svec;
    SVECTOR  *pos2, *speed;

    svec.vx = 0;
    svec.vy = 18;
    svec.vz = 130;

    speed = &prescript.speed;
    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;
    DG_SetPos_8001BC44(pos);
    DG_MovePos_8001BD20(&svec);
    ReadRotMatrix(&mat);

    pos2 = &prescript.pos;
    pos2->vx = mat.t[0];
    pos2->vy = mat.t[1];
    pos2->vz = mat.t[2];

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm_800C32F0.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C32F0);
}

void s08c_800C42B0(SVECTOR *pos)
{
    PRESCRIPT prescript;
    MATRIX    mat;
    SVECTOR   svec;
    SVECTOR  *speed;

    prescript.pos.vx = pos->vx;
    prescript.pos.vy = pos->vy;
    prescript.pos.vz = pos->vz;

    svec.vx = 0;
    svec.vy = 18;
    svec.vz = 130;

    speed = &prescript.speed;
    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;

    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C330C.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C330C);
}
