#include "common.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anim_data_800D13CC[] = {
    0x00,0x23,0x02,0x00, 0x07,0x00,0x1a,0x02,
    0x00,0x01,0x08,0x6a, 0x6a,0x6a,0x0c,0x00,
    0x0a,0x08,0xf6,0xf6, 0xf6,0x02,0x00,0x01,
    0x0d,0x0f,0x08,0x6a, 0x6a,0x6a,0x0c,0x00,
    0x05,0x08,0xec,0xec, 0xec,0x02,0x00,0x01,
    0x0d,0x0f
};

static ANIMATION anm_800C32F0 = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    250,                        // raise
    1,                          // amb
    40,                         // size_w
    40,                         // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800D13CC  // script
};
static ANIMATION anm_800C330C = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    2500,                       // raise
    1,                          // amb
    40,                         // size_w
    40,                         // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800D13CC  // script
};

/*---------------------------------------------------------------------------*/

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
    DG_SetPos(pos);
    DG_MovePos(&svec);
    ReadRotMatrix(&mat);

    pos2 = &prescript.pos;
    pos2->vx = mat.t[0];
    pos2->vy = mat.t[1];
    pos2->vz = mat.t[2];

    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C32F0.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C32F0);
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
    DG_SetPos(pos);
    DG_MovePos(&svec);
    ReadRotMatrix(&mat);

    pos2 = &prescript.pos;
    pos2->vx = mat.t[0];
    pos2->vy = mat.t[1];
    pos2->vz = mat.t[2];

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm_800C32F0.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C32F0);
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

    anm_800C330C.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C330C);
}
