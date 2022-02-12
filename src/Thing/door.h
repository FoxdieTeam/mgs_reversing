#ifndef _THING_DOOR_H_
#define _THING_DOOR_H_

#include "GM_Control.h"
#include "game.h"
#include "actor.h"

Actor* NewDoor_8006FD00(int name, int where, int argc, char **argv);

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
  int field_30[2];
};

struct Actor_Door
{
  Actor field_0_actor;
  Res_Control field_20_ctrl;
  OBJECT_NO_ROTS field_9C;
  short field_C0;
  short field_C2;
  int field_C4;
  int field_C8;
  int field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  short field_E0_where;
  char field_E2_maybe_state;
  char field_E3;
  char field_E4_t_param_v;
  char field_E5;
  short field_E6_param_w_v;
  short field_E8_param_s_v;
  short field_EA_param_h_v;
  short field_EC_param_v_v;
  short field_EE;
  short field_F0;
  unsigned short field_F2_door_counter;
  short field_F4_param_g_v;
  short field_F6_map_num;
  short field_F8_maps[2];
  short field_FC_param_u_v;
  unsigned char field_FE_e_param_v1;
  char field_FF_e_param_v2;
  int field_100_param_f_v;
  struct Actor_Door_TParam field_104[1];
};

#endif // _THING_DOOR_H_
