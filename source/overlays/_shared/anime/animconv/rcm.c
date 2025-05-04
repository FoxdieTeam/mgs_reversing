#include "common.h"
#include "libdg/libdg.h"
#include "Anime/animconv/anime.h"
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
    PCX_RCM_L,                  // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    230,                        // field_A
    1,                          // field_C
    300,                        // field_E_xw
    300,                        // field_10_yh
    255,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E46F8  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E4724[] = {
    0x00,0x10,0x01,0x00, 0x05,0x02,0x00,0x01,
    0x08,0xf0,0xf0,0xf0, 0x0a,0x03,0xe8,0x03,
    0xe8,0x02,0x00,0x01, 0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C20 = {
    PCX_RCM_L,                  // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    230,                        // field_A
    1,                          // field_C
    1000,                       // field_E_xw
    1000,                       // field_10_yh
    32,                         // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E4724  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E473C[] = {
    0x00,0x08,0x01,0x00, 0x05,0x0c,0x00,0x3c,
    0x02,0x00,0x01,0x0d, 0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C3C = {
    PCX_RCM_L,                  // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    500,                        // field_A
    1,                          // field_C
    200,                        // field_E_xw
    200,                        // field_10_yh
    255,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E473C  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E474C[] = {
    0x00,0x0d,0x02,0x00, 0x07,0x00,0x0b,0x02,
    0x00,0x01,0x0f,0x0a, 0xfe,0x70,0xfe,0x70,
    0x02,0x00,0x01,0x0f
};

static ANIMATION anm_800C3C58 = {
    PCX_RCM_L,                  // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    500,                        // field_A
    1,                          // field_C
    2000,                       // field_E_xw
    2000,                       // field_10_yh
    64,                         // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E474C  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E4760[] = {
    0x00,0x04,0x01,0x00, 0x05,0x02,0x00,0x01,
    0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C3C74 = {
    PCX_RCM_L,                  // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    0,                          // field_A
    0,                          // field_C
    20,                         // field_E_xw
    20,                         // field_10_yh
    255,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E4760  // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char anim_data_800E476C[] = {
    0x00,0x13,0x01,0x00, 0x05,0x08,0xc8,0xc8,
    0xff,0x02,0x00,0x01, 0x0c,0x00,0x1f,0x08,
    0xfa,0xfa,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_800C3C90 = {
    PCX_W_BONBORI,              // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    230,                        // field_A
    1,                          // field_C
    0,                          // field_E_xw
    0,                          // field_10_yh
    255,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anim_data_800E476C  // field_18_ptr
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

    memcpy(ptr, anm.field_18_ptr, 32);

    anm.field_18_ptr = ptr;
    anm.pre_script = &pre;
    anm.field_E_xw = arg1;
    anm.field_10_yh = arg1;

    anm.field_18_ptr[6] = arg2;
    anm.field_18_ptr[7] = arg3;
    anm.field_18_ptr[8] = arg4;
    anm.field_18_ptr[14] = arg5;
    anm.field_18_ptr[16] = arg6;
    anm.field_18_ptr[17] = arg7;
    anm.field_18_ptr[18] = arg8;

    NewAnime(NULL, 0, &anm);
}
