#include "strcode.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

const char anm_dmgsmoke1_form_script[] = {
    0x00,0x15,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x07,0x0a,0x00, 0xc8,0x00,0xc8,0x01,
    0xff,0x08,0xf8,0xf8, 0xf8,0x02,0x00,0x01, 0x0d,0x0f
};

ANIMATION anm_dmgsmoke1_form = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    0,                          // raise
    2,                          // amb
    1500,                       // size_w
    1500,                       // size_h
    64,                         // v
    NULL,                       // pre_script
    (char *)anm_dmgsmoke1_form_script // script
};

const char anm_dmgsmoke2_form_script[] = {
    0x00,0x36,0x02,0x00, 0x07,0x00,0x1c,0x01, 0xfe,0x0c,0x00,0x07, 0x0a,0x01,0x2c,0x01,
    0x2c,0x01,0xff,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

ANIMATION anm_dmgsmoke2_form = {
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
    (char *)anm_dmgsmoke2_form_script // script
};

/*---------------------------------------------------------------------------*/

void AN_DamageSmoke1( SVECTOR *world )
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

    anm = &anm_dmgsmoke1_form;
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

        anm = &anm_dmgsmoke2_form;
        anm->pre_script = &pre;

        NewAnime( NULL, 0, anm );
    }
}

void AN_DamageSmoke2( SVECTOR *world )
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

    anm = &anm_dmgsmoke2_form;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}
