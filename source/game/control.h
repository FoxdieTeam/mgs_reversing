#ifndef __MGS_GAME_CONTROL_H__
#define __MGS_GAME_CONTROL_H__

#include <sys/types.h>
#include <libgte.h>
#include "libgv/libgv.h"
#include "game/map.h"

enum
{
    CTRL_SKIP_MESSAGE    = 0x01,
    CTRL_SKIP_TRAP       = 0x02,
    CTRL_SKIP_NEAR_CHECK = 0x04,
    CTRL_BOTH_CHECK      = 0x08,
}; // can't typedef char enums :(

enum // radar_attr
{
    RADAR_OFF     = 0,
    RADAR_VISIBLE = 0x1,  // Enables dot at entity position
    RADAR_SIGHT   = 0x4,  // Enables vision cone for entities
    RADAR_ALL_MAP = 0x8,
    RADAR_NOISE   = 0x10, // Enables noise at position on radar (e.g. DARPA Chief)
    RADAR_UNK1    = 0x20, // Extends distance before entity is no longer drawn on the radar?
    RADAR_UNK2    = 0x40, // Enables RADAR_SIGHT if within certain height of Snake?
    RADAR_UNK4    = 0x1000,
    RADAR_UNK3    = 0x2000,
};

typedef struct RADAR_SIGHT_PARAM
{
    u_short dir;
    u_short dis;
    u_short range;
    u_short r;
} RADAR_SIGHT_PARAM;

typedef struct CONTROL
{
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

/* control.c */
void GM_InitWhereSystem(void);
int  GM_InitControl(CONTROL *control, int scriptData, int scriptBinds);
void GM_ActControl(CONTROL *control);
void GM_FreeControl(CONTROL *control);
void GM_ConfigControlVector(CONTROL *ctrl, SVECTOR *mov, SVECTOR *rot);
void GM_ConfigControlMatrix(CONTROL *control, MATRIX *world);
void GM_ConfigControlString(CONTROL *control, char *mov, char *rot);
void GM_ConfigControlHazard(CONTROL *ctrl, int height, int r_sphere, int s_sphere);
void GM_ConfigControlAttribute(CONTROL *control, int atr);
void GM_ConfigControlInterp(CONTROL *control, int interp);
int  GM_CheckControlTouches(CONTROL *control, int range);
void GM_ConfigControlRadarparam(CONTROL *ctrl, u_short dir, u_short dis, int range, u_short r);
void GM_ConfigControlTrapCheck(CONTROL *control);
GV_MSG *GM_CheckMessage(void *work, int name, int msgcode);

#endif // __MGS_GAME_CONTROL_H__
