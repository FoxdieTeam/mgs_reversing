#include <stddef.h> // for NULL
#include "Anime/animeconv/anime.h"
#include "strcode.h"

extern SVECTOR DG_ZeroVector_800AB39C;

const char anim_data_800E46F8[] = {
    0x00, 0x1f, 0x04, 0x00, 0x0b, 0x00, 0x0f, 0x00,
    0x18, 0x00, 0x21, 0x02, 0x00, 0x01, 0x0f, 0x0a,
    0xff, 0xce, 0xff, 0xce, 0x02, 0x00, 0x01, 0x0f,
    0x0a, 0xff, 0x9c, 0xff, 0x9c, 0x02, 0x00, 0x01,
    0x0f, 0x0a, 0xff, 0x6a, 0xff, 0x6a, 0x02, 0x00,
    0x01, 0x0f, 0x00, 0x00,
};

const char anim_data_800E4724[] = {
    0x00, 0x10, 0x01, 0x00, 0x05, 0x02, 0x00, 0x01,
    0x08, 0xf0, 0xf0, 0xf0, 0x0a, 0x03, 0xe8, 0x03,
    0xe8, 0x02, 0x00, 0x01, 0x0f, 0x00, 0x00, 0x00,
};

const char anim_data_800E473C[] = {
    0x00, 0x08, 0x01, 0x00, 0x05, 0x0c, 0x00, 0x3c,
    0x02, 0x00, 0x01, 0x0d, 0x0f, 0x00, 0x00, 0x00,
};

const char anim_data_800E474C[] = {
    0x00, 0x0d, 0x02, 0x00, 0x07, 0x00, 0x0b, 0x02,
    0x00, 0x01, 0x0f, 0x0a, 0xfe, 0x70, 0xfe, 0x70,
    0x02, 0x00, 0x01, 0x0f,
};

const char anim_data_800E4760[] = {
    0x00, 0x04, 0x01, 0x00, 0x05, 0x02, 0x00, 0x01,
    0x0f, 0x00, 0x00, 0x00,
};

const char anim_data_800E476C[] = {
    0x00, 0x13, 0x01, 0x00, 0x05, 0x08, 0xc8, 0xc8,
    0xff, 0x02, 0x00, 0x01, 0x0c, 0x00, 0x1f, 0x08,
    0xfa, 0xfa, 0xf8, 0x02, 0x00, 0x01, 0x0d, 0x0f,
};

ANIMATION anm_800C3C04 = {PCX_RCM_L, 1, 1, 1, 1, 230, 1, 300, 300, 255, NULL, (char *)anim_data_800E46F8};
ANIMATION anm_800C3C20 = {PCX_RCM_L, 1, 1, 1, 1, 230, 1, 1000, 1000, 32, NULL, (char *)anim_data_800E4724};
ANIMATION anm_800C3C3C = {PCX_RCM_L, 1, 1, 1, 1, 500, 1, 200, 200, 255, NULL, (char *)anim_data_800E473C};
ANIMATION anm_800C3C58 = {PCX_RCM_L, 1, 1, 1, 1, 500, 1, 2000, 2000, 64, NULL, (char *)anim_data_800E474C};
ANIMATION anm_800C3C74 = {PCX_RCM_L, 1, 1, 1, 1, 0, 0, 20, 20, 255, NULL, (char *)anim_data_800E4760};
ANIMATION anm_800C3C90 = {PCX_W_BONBORI, 1, 1, 1, 1, 230, 1, 0, 0, 255, NULL, (char *)anim_data_800E476C};


void s01a_object_800D93BC(short *arg0)
{
    PRESCRIPT prescript;
    SVECTOR  *pos, *speed;

    pos = &prescript.pos;

    pos->vx = arg0[10];
    pos->vy = arg0[12];
    pos->vz = arg0[14];

    speed = &prescript.speed;

    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm_800C3C04.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D9424(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C04.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D94A8(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C3C.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C3C);
}

void s01a_object_800D952C(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C58.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C58);
}

void s01a_object_800D95B0(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C74.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C74);
}

void s01a_object_800D9634(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C20.pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C20);
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

    NewAnime_8005FBC8(NULL, 0, &anm);
}
