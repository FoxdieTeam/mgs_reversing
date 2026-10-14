#ifndef __MGS_KOJO_HIND_H__
#define __MGS_KOJO_HIND_H__

#include "game/game.h"

typedef struct HindWork
{
    GV_ACT        actor;
    CONTROL       control;
    OBJECT        body;
    OBJECT        missile1;
    OBJECT        missile2;
    MATRIX        body_light[2];
    MATRIX        missile1_light[2];
    MATRIX        missile2_light[2];
    TARGET       *target1;
    TARGET       *target2;
    TARGET       *target3;
    int           first_frame;      /* set by NewHindBoss, cleared after the first HindAct */
    int           field_418;
    /* 'r' */
    int           rotor_rpm;
    int           tail_rotor_rpm;
    /* 'e' (km/h, per second, degrees) */
    int           field_424;
    int           field_428;
    int           field_42C;
    /* 'd' */
    int           hits_max;         /* stinger hits to kill */
    int           hits;
    int           invuln_time;      /* frames of invulnerability after a hit */
    int           field_43C;
    int           field_440;
    int           field_444;
    /* 'g' : machine gun */
    int           gun_interval;
    int           gun_max_pitch;
    int           gun_max_yaw;
    int           gun_pitch_margin;
    int           gun_yaw_margin;
    int           gun_size;         /* NewBulletEx size/length/speed */
    int           gun_damage;
    int           gun_length;
    int           gun_speed;
    /* 'm' : missiles */
    int           field_46C;
    int           field_470;
    int           missile_interval;
    int           field_478;
    int           field_47C;
    int           field_480;
    int           field_484;
    int           field_488;
    int           field_48C;
    SVECTOR      *missile_target;
    /* 'p' */
    int           field_494;
    int           field_498;
    int           field_49C;
    int           field_4A0;
    short         field_4A4;
    short         field_4A6;
    short         field_4A8;
    short         field_4AA;
    int           mode;             /* 'b' */
    int           field_4B0;        /* 'w' */
    int           rotor_speed;
    int           tail_rotor_speed;
    VECTOR        field_4BC;
    char          pad_4CC[0x4DC - 0x4CC];
    VECTOR        field_4DC;        /* 'p' speed rotated by the initial turn */
    char          pad_4EC[0x500 - 0x4EC];
    int           field_500;
    int           gun_timer;
    int           missile_timer;
    int           invuln_timer;
    int           field_510;
    int           field_514;
    VECTOR        field_518;
    VECTOR        field_528;
    VECTOR        field_538;
    VECTOR        field_548;
    VECTOR        area_min;         /* bounding box of the map's walls and floors */
    VECTOR        area_max;
    int           end_proc;
    TARGET        field_57C;
    int           field_5C4;
    int           field_5C8;
    int           field_5CC;
    int           field_5D0;
    int           field_5D4;
    int           field_5D8;
    int           field_5DC;
    int           field_5E0;
    int           field_5E4;
    int           field_5E8;
    int           field_5EC;
    int           field_5F0;
    int           field_5F4;
    int           field_5F8;
    VECTOR        field_5FC;
    VECTOR        field_60C;
    VECTOR        field_61C;
    VECTOR        field_62C;
    SVECTOR       field_63C;
    SVECTOR       field_644;
    int           field_64C;
    int           damage;
    int           life;
    int           field_658;
    SVECTOR       field_65C;
    SVECTOR       field_664;
    int           field_66C;
    int           field_670;

    int     nMissileDemoMode;     /* 動くミサイル用デモ */
    int     nMissileDemoMode2;    /* 動くミサイル用デモ */
    OBJECT  move_missile_body;    /* Mi24ハインドのミサイルモデル３番（実際に飛ぶ） */
    VECTOR  move_missile_pos_v;
    SVECTOR move_missile_pos_blast;
    SVECTOR move_missile_pos_help;
    SVECTOR move_missile_pos_help2;
    SVECTOR move_missile_rot;
    SVECTOR move_missile_target_pos;
    MATRIX  move_missile_light[2];
    SVECTOR move_missile_pos;
    SVECTOR move_missile_pos_delay;

    /* ライフゲージ用 */
    MENU_BAR_CONF life_conf;
    int           life_total;
    int           fight_start_flag;

    /* 音用 */
    int vox_ids[48];
    int field_8BC;
    int field_8C0;
    int field_8C4;
    int field_8C8;
    int field_8CC;

    int      field_8D0;
    int      field_8D4;
    int      last_time;
    int      last_time2;
    void    *cinema_screen;
    GV_ACT  *field_8E4;
    GV_ACT  *field_8E8;
    int      field_8EC;
    int      field_8F0;
    int      last_item;
    int      last_weapon;
    int      field_8FC;
    int      field_900;
    int      field_904;
    SVECTOR  field_908;
    SVECTOR  field_910;
    SVECTOR  field_918;
    SVECTOR  field_920;
    int      field_928;
    int      field_92C;
    int      field_930;
    int      name;
    int      field_938;
    int      field_93C;
    int      field_940;
    int      field_944;
    int      field_948;
    int      field_94C;
    int      field_950;
    int      field_954;
    int      field_958;
    int      field_95C;
    int      field_960;
    SVECTOR  field_964;
    int      field_96C;
    SVECTOR  field_970[32];
    SVECTOR *field_A70;
    int      field_A74;
    SVECTOR  field_A78;
} HindWork;

#endif // __MGS_KOJO_HIND_H__
