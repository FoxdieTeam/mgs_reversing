#ifndef _THING_DOOR_H_
#define _THING_DOOR_H_

#include "Game/control.h"
#include "Game/game.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"

GV_ACT *NewDoor_8006FD00(int name, int where, int argc, char **argv);

typedef struct Actor_Door_TParam
{
    HZD_SEG field_0[3];
    SVECTOR field_30;
} Actor_Door_TParam;

typedef struct Actor_Door
{
    GV_ACT            field_0_actor;
    CONTROL           field_20_ctrl;
    OBJECT_NO_ROTS    field_9C;
    SVECTOR           field_C0[4]; // Might not be an SVECTOR, it's not used very often
    short             field_E0_where;
    char              field_E2_maybe_state;
    char              field_E3;
    char              field_E4_t_param_v;
    char              field_E5;
    short             field_E6_param_w_v;
    short             field_E8_param_s_v;
    short             field_EA_param_h_v;
    short             field_EC_param_v_v;
    short             field_EE;
    short             field_F0;
    short             field_F2_door_counter;
    short             field_F4_param_g_v;
    short             field_F6_map_num;
    unsigned short    field_F8_maps[2];
    short             field_FC_param_u_v;
    unsigned char     field_FE_sound_effect;
    char              field_FF_e_param_v2;
    int               field_100_param_f_v;
    Actor_Door_TParam field_104[1];
} Actor_Door;

int  door_loader_8006FA60(Actor_Door *pDoor, int name, int where);
void door_act_8006F318(Actor_Door *pDoor);
void door_kill_8006F718(Actor_Door *pDoor);
int  door_read_with_default_value_8006FA28(unsigned char param_char, int defaul_val);
void door_loader_param_h_8006F978(Actor_Door *pDoor, int a_param_v);
void door_init_t_value_8006F7AC(Actor_Door *pDoor, Actor_Door_TParam *pOffset, int, int, int);
void door_loader_t_param_sub_8006F748(HZD_SEG *pSeg, SVECTOR *pVec1, SVECTOR *pVec2, int param_v);

#endif // _THING_DOOR_H_
