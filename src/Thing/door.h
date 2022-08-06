#ifndef _THING_DOOR_H_
#define _THING_DOOR_H_

#include "Game/GM_Control.h"
#include "Game/game.h"
#include "libgv/libgv.h"

Actor *NewDoor_8006FD00(int name, int where, int argc, char **argv);

struct Actor_Door_TParam_sub
{
    short field_0_x;
    short field_2_z;
    short field_4_y;
    short field_6_param_v2;

    short field_8_x;
    short field_A_z;
    short field_C_y;
    short field_E_param_v1;
};

struct Actor_Door_TParam
{
    struct Actor_Door_TParam_sub field_0;
    struct Actor_Door_TParam_sub field_10;
    struct Actor_Door_TParam_sub field_20;
    int                          field_30[2];
};

struct Actor_Door
{
    Actor                    field_0_actor;
    GM_Control               field_20_ctrl;
    OBJECT_NO_ROTS           field_9C;
    short                    field_C0;
    short                    field_C2;
    int                      field_C4;
    int                      field_C8;
    int                      field_CC;
    int                      field_D0;
    int                      field_D4;
    int                      field_D8;
    int                      field_DC;
    short                    field_E0_where;
    char                     field_E2_maybe_state;
    char                     field_E3;
    char                     field_E4_t_param_v;
    char                     field_E5;
    short                    field_E6_param_w_v;
    short                    field_E8_param_s_v;
    short                    field_EA_param_h_v;
    short                    field_EC_param_v_v;
    short                    field_EE;
    short                    field_F0;
    unsigned short           field_F2_door_counter;
    short                    field_F4_param_g_v;
    short                    field_F6_map_num;
    short                    field_F8_maps[2];
    short                    field_FC_param_u_v;
    unsigned char            field_FE_e_param_v1;
    char                     field_FF_e_param_v2;
    int                      field_100_param_f_v;
    struct Actor_Door_TParam field_104[1];
};

int  door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where);
void door_act_8006F318(struct Actor_Door *pDoor);
void door_kill_8006F718(struct Actor_Door *pDoor);
int  door_read_with_default_value_8006FA28(unsigned char param_char, int defaul_val);
void door_loader_param_h_8006F978(struct Actor_Door *pDoor, int a_param_v);

// TODO: move to hzd.h? but this pTSub struct is weird
int HZD_QueueDynamicSegment2_8006FDDC(int pHzd_f0, struct Actor_Door_TParam_sub *pTSub, int a_param_with_flag);

#endif // _THING_DOOR_H_
