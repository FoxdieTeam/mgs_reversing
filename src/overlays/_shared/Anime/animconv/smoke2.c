#include "common.h"
#include "libgv/libgv.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char s03c_dword_800D7B34[] = {
    0x00,0x15,0x01,0x00, 0x05,0x01,0xfe,0x0c,
    0x00,0x07,0x0a,0x00, 0xc8,0x00,0xc8,0x01,
    0xff,0x08,0xf8,0xf8, 0xf8,0x02,0x00,0x01,
    0x0d,0x0f
};

static ANIMATION s03c_dword_800C33DC = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    0,                          // field_A
    2,                          // field_C
    1500,                       // field_E_xw
    1500,                       // field_10_yh
    64,                         // field_12_rgb
    NULL,                       // pre_script
    (char *)s03c_dword_800D7B34 // field_18_ptr
};

/*---------------------------------------------------------------------------*/

static const char s03c_dword_800D7B50[] = {
    0x00,0x36,0x02,0x00, 0x07,0x00,0x1c,0x01,
    0xfe,0x0c,0x00,0x07, 0x0a,0x01,0x2c,0x01,
    0x2c,0x01,0xff,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0x01,
    0xf4,0x01,0xf4,0x08, 0xbe,0xbe,0xbe,0x02,
    0x00,0x01,0x0c,0x00, 0x0f,0x0a,0x00,0xc8,
    0x00,0xc8,0x01,0xff, 0x08,0xf0,0xf0,0xf0,
    0x02,0x00,0x01,0x0d, 0x0f
};

static ANIMATION s03c_dword_800C33F8 = {
    PCX_SMOKE,                  // field_0_texture_hash
    8,                          // field_2
    4,                          // field_4
    30,                         // n_anims
    1,                          // n_vertices
    0,                          // field_A
    1,                          // field_C
    800,                        // field_E_xw
    800,                        // field_10_yh
    64,                         // field_12_rgb
    NULL,                       // pre_script
    (char *)s03c_dword_800D7B50 // field_18_ptr
};

/*---------------------------------------------------------------------------*/

void AN_Unknown_800CCA40(SVECTOR *pos)
{
    PRESCRIPT  prescript;
    SVECTOR   *prepos, *speed;
    ANIMATION *anime;

    prepos = &prescript.pos;
    prepos->vx = pos->vx + GV_RandS(512) - 64;
    prepos->vy = pos->vy + GV_RandS(256) - 128;
    prepos->vz = pos->vz;

    speed = &prescript.speed;
    speed->vx = GV_RandS(64);
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anime = &s03c_dword_800C33DC;
    anime->pre_script = &prescript;
    NewAnime(NULL, NULL, anime);

    if (!(GV_Time & 3))
    {
        prepos->vx = pos->vx + GV_RandS(512) - 64;
        prepos->vy = pos->vy + GV_RandS(256) - 128;
        prepos->vz = pos->vz;

        speed->vx = GV_RandS(64);
        speed->vy = GV_RandS(128) + 64;
        speed->vz = 0;

        prescript.scr_num = 0;
        prescript.s_anim = 0;

        anime = &s03c_dword_800C33F8;
        anime->pre_script = &prescript;
        NewAnime(NULL, NULL, anime);
    }
}

void AN_Unknown_800CCB84(SVECTOR *pos)
{
    PRESCRIPT prescript;
    SVECTOR  *prepos, *speed;

    prepos = &prescript.pos;
    prepos->vx = pos->vx + GV_RandS(2048);
    prepos->vy = pos->vy;
    prepos->vz = pos->vz + GV_RandS(2048);

    speed = &prescript.speed;
    speed->vx = 0;
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    s03c_dword_800C33F8.pre_script = &prescript;

    NewAnime(NULL, NULL, &s03c_dword_800C33F8);
}
