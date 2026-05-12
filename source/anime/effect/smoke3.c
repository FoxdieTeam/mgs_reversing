#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E31C8[] = {
    0x00,0x15,0x01,0x00, 0x05,0x01,0xfe,0x0c,
    0x00,0x0a,0x01,0xff, 0x0a,0x00,0x06,0x00,
    0x06,0x08,0xfa,0xfa, 0xfa,0x02,0x00,0x01,
    0x0d,0x0f,0x00,0x00
};

static ANIMATION anm_800C370C = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    8,                          // n_verts
    500,                        // raise
    3,                          // amb
    300,                        // size_w
    300,                        // size_h
    64,                         // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E31C8 // script
};

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E31E4[] = {
    0x00,0x90,0x04,0x00, 0x0b,0x00,0x2c,0x00,
    0x51,0x00,0x76,0x0c, 0x00,0x05,0x01,0xff,
    0x0a,0x00,0x32,0x00, 0x32,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x0a, 0x01,0xff,0x0a,0x00,
    0x64,0x00,0x64,0x08, 0xf4,0xf4,0xf4,0x02,
    0x00,0x01,0x0d,0x0f, 0x08,0x00,0xc0,0xc0,
    0x0c,0x00,0x05,0x01, 0xff,0x0a,0x00,0x32,
    0x00,0x32,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x0a,0x01,0xff,0x0a, 0x00,0x64,0x00,0x64,
    0x08,0xf4,0xfa,0xfa, 0x02,0x00,0x01,0x0d,
    0x0f,0x08,0xe0,0x00, 0xe0,0x0c,0x00,0x05,
    0x01,0xff,0x0a,0x00, 0x32,0x00,0x32,0x02,
    0x00,0x01,0x0d,0x0c, 0x00,0x0a,0x01,0xff,
    0x0a,0x00,0x64,0x00, 0x64,0x08,0xf7,0xf4,
    0xf7,0x02,0x00,0x01, 0x0d,0x0f,0x08,0xe0,
    0xe0,0x00,0x0c,0x00, 0x05,0x01,0xff,0x0a,
    0x00,0x32,0x00,0x32, 0x02,0x00,0x01,0x0d,
    0x0c,0x00,0x0a,0x01, 0xff,0x0a,0x00,0x64,
    0x00,0x64,0x08,0xf7, 0xf7,0xf4,0x02,0x00,
    0x01,0x0d,0x0f,0x00
};

static ANIMATION anm_800C3728 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    500,                        // raise
    1,                          // amb
    300,                        // size_w
    300,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E31E4 // script
};

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E3280[] = {
    0x00,0x25,0x01,0x00, 0x05,0x08,0xff,0xff,
    0xff,0x0c,0x00,0x05, 0x01,0xff,0x0a,0x00,
    0x32,0x00,0x32,0x02, 0x00,0x01,0x0d,0x0c,
    0x00,0x0a,0x01,0xff, 0x0a,0x00,0x64,0x00,
    0x64,0x08,0xf4,0xf4, 0xf4,0x02,0x00,0x01,
    0x0d,0x0f,0x00,0x00
};

static ANIMATION anm_800C3744 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    500,                        // raise
    1,                          // amb
    300,                        // size_w
    300,                        // size_h
    0,                          // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E3280 // script
};

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E32AC[] = {
    0x00,0x13,0x01,0x00, 0x05,0x0c,0x00,0x09,
    0x01,0xff,0x0a,0x00, 0x78,0x00,0x78,0x08,
    0xe7,0xe7,0xe7,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_800C3760 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    500,                        // raise
    3,                          // amb
    300,                        // size_w
    300,                        // size_h
    255,                        // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E32AC // script
};

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E32C4[] = {
    0x00,0x36,0x02,0x00, 0x07,0x00,0x1c,0x01,
    0xfe,0x0c,0x00,0x07, 0x0a,0x01,0x2c,0x01,
    0x2c,0x01,0xff,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0d,0x0f, 0x01,0xfe,0x0a,0x01,
    0xf4,0x01,0xf4,0x08, 0xbe,0xbe,0xbe,0x02,
    0x00,0x01,0x0c,0x00, 0x0f,0x0a,0x00,0xc8,
    0x00,0xc8,0x01,0xff, 0x08,0xf0,0xf0,0xf0,
    0x02,0x00,0x01,0x0d, 0x0f,0x00,0x00,0x00
};

static ANIMATION anm_800C377C = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    0,                          // raise
    1,                          // amb
    800,                        // size_w
    800,                        // size_h
    64,                         // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E32C4 // script
};

/*---------------------------------------------------------------------------*/

static const char s13a_dword_800E3304[] = {
    0x00,0x15,0x01,0x00, 0x05,0x01,0xfe,0x0c,
    0x00,0x07,0x0a,0xff, 0xe2,0xff,0xe2,0x01,
    0xff,0x08,0xf8,0xf8, 0xf8,0x02,0x00,0x01,
    0x0d,0x0f
};

static ANIMATION anm_800C3798 = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    0,                          // raise
    1,                          // amb
    400,                        // size_w
    400,                        // size_h
    32,                         // v
    NULL,                       // pre_script
    (char *)s13a_dword_800E3304 // script
};

/*---------------------------------------------------------------------------*/

void AN_Unknown_800DC4B4(SVECTOR *pos, int ang)
{
    SVECTOR    rot;
    SVECTOR    speed;
    char       unused[0x20];
    PRESCRIPT  pre[8];
    ANIMATION *anm;
    int        i;

    rot.vx = 0;
    rot.vz = 0;

    for (i = 0; i < 8; i++, pos++)
    {
        pre[i].pos = *pos;
        pre[i].scr_num = 0;
        pre[i].s_anim = 0;

        speed.vx = 0;
        speed.vy = 0;
        speed.vz = GV_RandU(32) + 50;

        rot.vy = ang + GV_RandS(32);

        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&speed, &pre[i].speed, 1);
    }

    anm = &anm_800C370C;
    anm->pre_script = pre;
    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800DC5B4(SVECTOR *pos, SVECTOR *speed, int script)
{
    PRESCRIPT  pre;
    SVECTOR   *ppos;
    ANIMATION *anm;

    ppos = &pre.pos;
    ppos->vx = pos->vx + GV_RandS(32);
    ppos->vy = pos->vy + GV_RandS(32);
    ppos->vz = pos->vz + GV_RandS(32);
    pre.speed = *speed;
    pre.scr_num = script;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3728;
    anm->pre_script = &pre;
    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800DC6AC(SVECTOR *pos, SVECTOR *speed, char r, char g, char b)
{
    PRESCRIPT  pre;
    SVECTOR   *ppos;
    ANIMATION *anm;

    ppos = &pre.pos;
    ppos->vx = pos->vx + GV_RandS(32);
    ppos->vy = pos->vy + GV_RandS(32);
    ppos->vz = pos->vz + GV_RandS(32);
    pre.scr_num = 0;
    pre.speed = *speed;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3744;
    anm->pre_script = &pre;
    anm->script[6] = r;
    anm->script[7] = g;
    anm->script[8] = b;
    anm->script[34] = -((r - 1) / 10);
    anm->script[35] = -((g - 1) / 10);
    anm->script[36] = -((b - 1) / 10);
    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800DC860(SVECTOR *pos, SVECTOR *speed)
{
    PRESCRIPT  pre;
    SVECTOR   *ppos;
    ANIMATION *anm;

    ppos = &pre.pos;
    ppos->vx = pos->vx + GV_RandS(32);
    ppos->vy = pos->vy + GV_RandS(32);
    ppos->vz = pos->vz + GV_RandS(32);
    pre.speed = *speed;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3760;
    anm->pre_script = &pre;
    NewAnime(NULL, 0, &anm_800C3760);
}

void AN_Unknown_800DC94C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    SVECTOR   *speed;
    ANIMATION *anm;

    pre.pos = *pos;
    speed = &pre.speed;
    speed->vx = 0;
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;
    pre.scr_num = 1;
    pre.s_anim = 0;

    anm = &anm_800C377C;
    anm->pre_script = &pre;
    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800DC9C8(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_800C3798;
    anm->pre_script = &pre;
    NewAnime(NULL, 0, anm);
}
