#ifndef __MGS_FMT_DMO_H__
#define __MGS_FMT_DMO_H__
// clang-format off

#include <sys/types.h>

/* might be a union, same as 0x36 */
typedef struct {
    int      field_0;
    int      field_4_type;
    short    field_8_x;
    short    field_A_y;
    short    field_C_z;
    short    field_E_x;
    short    field_10_y;
    short    field_12_z;
    int      field_14_type;
    int      field_18_xy;
    int      field_1C_zpad;
    int      field_20;
    char     field_24;
    char     field_25;
    char     field_26;
    char     field_27;
    short    field_28;
    short    field_2A;
    int      field_2C;
    short    field_30;
    short    field_32;
} DMO_CHA;

typedef struct {
    int      type;
    short    visible;
    short    rot_x;
    short    rot_y;
    short    rot_z;
    short    pos_x;
    short    pos_y;
    short    pos_z;
    short    n_rots;
    short   *rots;
} DMO_ADJ;

typedef struct {
    u_int    tag;
    int      frame;
    short    eye_x;
    short    eye_y;
    short    eye_z;
    short    center_x;
    short    center_y;
    short    center_z;
    short    roll;
    short    clip_dist;
    short    n_charas;
    DMO_CHA *chara;
    short    n_adjusts;
    DMO_ADJ *adjust;
} DMO_DAT;

typedef struct {
    int      cache_id;
    int      filename;
} DMO_MAP;

typedef struct {
    int      type;
    int      flag;
    int      cache_id;
    int      filename;
    int      name;
} DMO_MDL;

typedef struct {
    u_int    tag;
    int      frame;
    int      n_frames;
    int      n_maps;
    int      n_models;
    DMO_MAP *maps;
    DMO_MDL *models;
} DMO_DEF;

// clang-format on
#endif // __MGS_FMT_DMO_H__
