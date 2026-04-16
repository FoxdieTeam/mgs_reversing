#include "strcode.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

const char animation_data1[] =
{
    0x00, 0x15, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c,
    0x00, 0x07, 0x0a, 0x00, 0xc8, 0x00, 0xc8, 0x01,
    0xff, 0x08, 0xf8, 0xf8, 0xf8, 0x02, 0x00, 0x01,
    0x0d, 0x0f
};

ANIMATION anm_1 = {PCX_SMOKE, 8, 4, 30, 1, 0, 2, 1500, 1500, 64, NULL, (char *)animation_data1};

const char animation_data2[] =
{
    0x00, 0x36, 0x02, 0x00, 0x07, 0x00, 0x1c, 0x01,
    0xfe, 0x0c, 0x00, 0x07, 0x0a, 0x01, 0x2c, 0x01,
    0x2c, 0x01, 0xff, 0x08, 0xf8, 0xf8, 0xf8, 0x02,
    0x00, 0x01, 0x0d, 0x0f
};

ANIMATION anm_2 = {PCX_SMOKE, 8, 4, 30, 1, 0, 1, 800, 800, 64, NULL, (char *)animation_data2};

void AN_DamageSmoke1(SVECTOR *world)
{
    PRESCRIPT  pre;
    SVECTOR   *pos;
    SVECTOR   *speed;
    ANIMATION *anm;

    pos = &pre.pos;
    speed = &pre.speed;

    pos->vx = world->vx + GV_RandS(512) - 64;
    pos->vy = world->vy + GV_RandS(256) - 128;
    pos->vz = world->vz;

    speed->vx = GV_RandS(64);
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_1;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );

    if ((GV_Time % 4) == 0)
    {
        pos->vx = world->vx + GV_RandS(512) - 64;
        pos->vy = world->vy + GV_RandS(256) - 128;
        pos->vz = world->vz;

        speed->vx = GV_RandS(64);
        speed->vy = GV_RandS(128) + 64;
        speed->vz = 0;

        pre.scr_num = 0;
        pre.s_anim = 0;

        anm = &anm_2;
        anm->pre_script = &pre;

        NewAnime( NULL, 0, anm );
    }
}

void AN_DamageSmoke2(SVECTOR *world)
{
    PRESCRIPT  pre;
    SVECTOR   *pos;
    SVECTOR   *speed;
    ANIMATION *anm;

    pos = &pre.pos;
    speed = &pre.speed;

    pos->vx = world->vx + GV_RandS(2048);
    pos->vy = world->vy;
    pos->vz = world->vz + GV_RandS(2048);

    speed->vx = 0;
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    pre.scr_num = 1;
    pre.s_anim = 0;

    anm = &anm_2;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}
