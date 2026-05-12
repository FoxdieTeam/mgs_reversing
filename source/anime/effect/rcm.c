#include "common.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anim_data_800E46F8[] = {
    0x00,0x1f,0x04,0x00, 0x0b,0x00,0x0f,0x00,
    0x18,0x00,0x21,0x02, 0x00,0x01,0x0f,0x0a,
    0xff,0xce,0xff,0xce, 0x02,0x00,0x01,0x0f,
    0x0a,0xff,0x9c,0xff, 0x9c,0x02,0x00,0x01,
    0x0f,0x0a,0xff,0x6a, 0xff,0x6a,0x02,0x00,
    0x01,0x0f,0x00,0x00
};

static ANIMATION anm_800C3C04 = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    230,                        // raise
    1,                          // amb
    300,                        // size_w
    300,                        // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800E46F8  // script
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E4724[] = {
    0x00,0x10,0x01,0x00, 0x05,0x02,0x00,0x01,
    0x08,0xf0,0xf0,0xf0, 0x0a,0x03,0xe8,0x03,
    0xe8,0x02,0x00,0x01, 0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C20 = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    230,                        // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    32,                         // v
    NULL,                       // pre_script
    (char *)anim_data_800E4724  // script
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E473C[] = {
    0x00,0x08,0x01,0x00, 0x05,0x0c,0x00,0x3c,
    0x02,0x00,0x01,0x0d, 0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C3C = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    500,                        // raise
    1,                          // amb
    200,                        // size_w
    200,                        // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800E473C  // script
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E474C[] = {
    0x00,0x0d,0x02,0x00, 0x07,0x00,0x0b,0x02,
    0x00,0x01,0x0f,0x0a, 0xfe,0x70,0xfe,0x70,
    0x02,0x00,0x01,0x0f
};

static ANIMATION anm_800C3C58 = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    500,                        // raise
    1,                          // amb
    2000,                       // size_w
    2000,                       // size_h
    64,                         // v
    NULL,                       // pre_script
    (char *)anim_data_800E474C  // script
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E4760[] = {
    0x00,0x04,0x01,0x00, 0x05,0x02,0x00,0x01,
    0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C74 = {
    PCX_RCM_L,                  // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    0,                          // raise
    0,                          // amb
    20,                         // size_w
    20,                         // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800E4760  // script
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E476C[] = {
    0x00,0x13,0x01,0x00, 0x05,0x08,0xc8,0xc8,
    0xff,0x02,0x00,0x01, 0x0c,0x00,0x1f,0x08,
    0xfa,0xfa,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_800C3C90 = {
    PCX_W_BONBORI,              // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    230,                        // raise
    1,                          // amb
    0,                          // size_w
    0,                          // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)anim_data_800E476C  // script
};

/*---------------------------------------------------------------------------*/

void s01a_object_800D93BC(MATRIX *world)
{
    PRESCRIPT prescript;
    SVECTOR  *pos, *speed;

    pos = &prescript.pos;

    pos->vx = world->t[0];
    pos->vy = world->t[1];
    pos->vz = world->t[2];

    speed = &prescript.speed;

    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm_800C3C04.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D9424(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C04.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D94A8(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C3C.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C3C);
}

void s01a_object_800D952C(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C58.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C58);
}

void s01a_object_800D95B0(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C74.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C74);
}

void s01a_object_800D9634(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C20.pre_script = &prescript;
    NewAnime(NULL, NULL, &anm_800C3C20);
}

void s01a_object_800D96B8(MATRIX *world, int arg1, char arg2, char arg3, char arg4, char arg5, char arg6, char arg7, char arg8, char *ptr)
{
    ANIMATION anm;
    PRESCRIPT pre;

    memset(&pre, 0, sizeof(PRESCRIPT));

    pre.pos.vx = world->t[0];
    pre.pos.vy = world->t[1];
    pre.pos.vz = world->t[2];

    anm = anm_800C3C90;

    memcpy(ptr, anm.script, 32);

    anm.script = ptr;
    anm.pre_script = &pre;
    anm.size_w = arg1;
    anm.size_h = arg1;

    anm.script[6] = arg2;
    anm.script[7] = arg3;
    anm.script[8] = arg4;
    anm.script[14] = arg5;
    anm.script[16] = arg6;
    anm.script[17] = arg7;
    anm.script[18] = arg8;

    NewAnime(NULL, 0, &anm);
}
