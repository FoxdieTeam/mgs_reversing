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

typedef struct RADAR_CONE
{
    unsigned short dir;
    unsigned short len;
    unsigned short ang;
    unsigned short _pad;
} RADAR_CONE;

typedef struct CONTROL
{
    SVECTOR     mov; // current position
    SVECTOR     rot; // current orientation (4096 = 2Pi rad)
    HZD_EVT     event;
    MAP        *map;
    u_short     name;
    short       height; // offset to mov.vy
    short       hzd_height;
    short       step_size; // squared
    short       field_38; // never used, value usually matches step_size
    u_short     radar_atr;
    RADAR_CONE  radar_cone;
    SVECTOR     step; // movement vector
    SVECTOR     turn; // rotation vector (4096 = 2Pi rad)
    signed char interp;    // turn speed
    char        skip_flag; // CTRL_...
    signed char n_messages;
    signed char level_flag;   // 1 = below floor, 2 = above ceiling
    signed char touch_flag;   // > 0 if collision detected
    char        exclude_flag; // exclude all surfaces where (flag & exclude_flag) != 0
    char        nearflags[2];
    GV_MSG     *messages;
    SVECTOR     nearvecs[2];
    void       *nears[2];  // HZD_SEG when tagged, HZD_FLR when untagged
    short       levels[2]; // floor and ceiling heights
} CONTROL;

#define MAX_CONTROLS 96

/* control.c */
// int  GM_ControlPushBack(CONTROL *control);
// void GM_ControlRemove(CONTROL *control);
void GM_InitWhereSystem(void);
int  GM_InitControl(CONTROL *control, int scriptData, int scriptBinds);
void GM_ActControl(CONTROL *control);
void GM_FreeControl(CONTROL *control);
void GM_ConfigControlVector(CONTROL *control, SVECTOR *pos, SVECTOR *rot);
void GM_ConfigControlMatrix(CONTROL *control, MATRIX *matrix);
void GM_ConfigControlString(CONTROL *control, char *param_pos, char *param_dir);
void GM_ConfigControlHazard(CONTROL *control, short height, short f36, short f38);
void GM_ConfigControlAttribute(CONTROL *control, int radar_atr);
void GM_ConfigControlInterp(CONTROL *control, char interp);
int  GM_CheckControlTouches(CONTROL *control, int param_2);
// void GM_ConfigControlRadarparam(CONTROL *control, u_short dir, u_short len, u_short ang, u_short pad);
void GM_ConfigControlTrapCheck(CONTROL *control);
GV_MSG *GM_CheckMessage(GV_ACT *actor, int msgType, int toFind);

#endif // __MGS_GAME_CONTROL_H__
