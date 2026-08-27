#ifndef __MGS_G_STRUCT_H__
#define __MGS_G_STRUCT_H__

#ifndef __MGS_GAME_H__
#error "g_struct.h must be included via game.h!"
#endif

#include "fmt_lit.h"
#include "fmt_mot.h"

/*---------------------------------------------------------------------------*/

typedef struct MAP {
    int      index;
    u_short  name;
    u_short  used;
    HZD_HDL *hzd;
    DG_LITS *lit;
    int      zone;
} MAP;

/*---------------------------------------------------------------------------*/

typedef struct RADAR_SIGHT_PARAM {
    u_short dir;
    u_short dis;
    u_short range;
    u_short r;
} RADAR_SIGHT_PARAM;

typedef struct CONTROL {
    SVECTOR     mov; // current position
    SVECTOR     rot; // current orientation (4096 = 2Pi rad)
    HZD_EVT     evt;
    MAP        *map;
    u_short     name;
    short       height; // offset to mov.vy
    short       hzd_height;
    short       r_sphere; // squared
    short       s_sphere; // never used, value usually matches step_size
    u_short     radar_atr;
    RADAR_SIGHT_PARAM radar_param;
    SVECTOR     step; // movement vector
    SVECTOR     turn; // rotation vector (4096 = 2Pi rad)
    signed char interp;    // turn speed
    char        skip_flag; // CTRL_...
    signed char n_msg;
    signed char grounded;   // 1 = below floor, 2 = above ceiling
    signed char n_touches;   // > 0 if collision detected
    char        seg_flag; // exclude all surfaces where (flag & seg_flag) != 0
    char        is_edge[2];
    GV_MSG     *msg;
    SVECTOR     vecs[2];
    HZD_SEG    *segs[2];  // HZD_SEG when tagged, HZD_FLR when untagged
    short       levels[2]; // floor and ceiling heights
} CONTROL;

/*---------------------------------------------------------------------------*/

typedef struct TARGET {
    u_short  class;
    u_short  side;
    u_short  map;
    u_short  damaged;
    SVECTOR  center;
    SVECTOR  size;
    int     *field_18; /* unused */
    SVECTOR *field_1C; /* unused */
    MATRIX  *body;
    short    p_mode;
    short    vital;
    short    damage;
    short    faint;
    SVECTOR  force;
    SVECTOR  offset;
    short    flag;
    short    a_mode;
    short    push_side;
    short    captured;
    int      weapon;
} TARGET;

typedef struct HOMING {
    MATRIX  *world;
    CONTROL *control;
    int      flag;
    int      used;
} HOMING;

/*---------------------------------------------------------------------------*/

typedef struct _MOTION_SEGMENT {
    SVECTOR  base;
    SVECTOR  delta;
    int      interp;
    u_short *stream;
    short    field_18;
    short    field_1A;
    u_char   field_1C;
    char     bit_offset;
    char     x_size;
    char     y_size;
    char     z_size;
} MOTION_SEGMENT;

typedef struct _MOTION_INFO {
    short           frames_left;
    // Controls the sound of Snake's footsteps; values, ranging from 0x0-0x11 (with intermediary jumps to 0x80 and
    // 0xff), appear to be the current frame of the sound sample (with frame 0x8 corresponding to the hard footstep
    // sound). Disabling any of the reads or writes causes Snake's footsteps no longer to make any noise, such that he
    // can for instance walk in puddles without being heard by enemies.
    short           frame;
    short           field_4;
    short           field_6;
    u_long          mask;
    MOTION_SEGMENT *m_segs;
    short           action;
    short           field_12;
    short           field_14; // 0 = init frame, middle frames = 1, 2 = last frame
    u_short         time;
} MOTION_INFO;

typedef struct _MOTION_CONTROL {
    DG_OAR     *oar;
    MOTION_INFO info1;
    MOTION_INFO info2;
    SVECTOR    *rot;    // pointer to the associated CONTROL's rot vector.
    SVECTOR    *step;   // pointer to the associated CONTROL's step vector.
    short      *height; // pointer to the associated OBJECT's height.
    u_long      interp;
    SVECTOR     waist_rot;
    SVECTOR    *rots;   // pointer to the associated OBJECT's per-joint rots.
} MOTION_CONTROL;

/*---------------------------------------------------------------------------*/

typedef struct _OBJECT {
    DG_OBJS        *objs;
    u_long          flag;
    MATRIX         *light;
    u_short         map_name;
    short           action;
    short           action2; // for override actions
    MOTION_CONTROL *m_ctrl;
    short           height;
    short           is_end;
    short           time2;   // for override actions, why not is_end2?
    u_long          pad;     // unused
    SVECTOR         rots[DG_MAX_JOINTS];
} OBJECT;

typedef struct _OBJECT_NO_ROTS {
    DG_OBJS        *objs;
    u_long          flag;
    MATRIX         *light;
    u_short         map_name;
    short           action;
    short           action2; // for override actions
    MOTION_CONTROL *m_ctrl;
    short           height;
    short           is_end;
    short           time2;   // for override actions, why not is_end2?
    u_long          pad;     // unused
} OBJECT_NO_ROTS;

/*---------------------------------------------------------------------------*/

typedef struct HITTABLE {
    int      type;    // Not read from, set as either WP_Claymore or WP_C4
    GV_ACT  *actor;
    CONTROL *control;
    void    *data;    // The thing being collided with, can be walls, floors, targets
} HITTABLE;

/*---------------------------------------------------------------------------*/
#endif // __MGS_G_STRUCT_H__
