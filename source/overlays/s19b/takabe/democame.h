#ifndef __S19B_DEMOCAME_H__
#define __S19B_DEMOCAME_H__

#include "game/game.h"

/* One key of a demo camera path (data tables in overlay2.c), the list ends
 * with interp == -1 */
typedef struct _DEMOCAM_KEY
{
    int     interp;     /* 0x00: interpolation (index into the democame.c tables) */
    int     time;       /* 0x04: frames to reach this key */
    int     mode;       /* 0x08: 0: pos = eye, param = center
                                 1: pos = eye, param = rotate.vx, rotate.vy, track
                                 2: pos = center, param = rotate.vx, rotate.vy, track */
    SVECTOR pos;        /* 0x0C */
    SVECTOR param;      /* 0x14 */
    int     flags;      /* 0x1C: which of eye/center/rotate/track follow the key */
} DEMOCAM_KEY;

typedef struct _DemoCamera DemoCamera;

/* Script of a demo camera: fn is called once the camera has run 'frame'
 * frames, the list ends with frame == -1 (set up by jeepdemo.c) */
typedef struct _DEMOCAM_CMD
{
    int  frame;
    void (*fn)(DemoCamera *cam);
} DEMOCAM_CMD;

typedef int  (*DemocameFn1)(int, int, int);
typedef void (*DemocameFn2)(SVECTOR *, SVECTOR *, int);

struct _DemoCamera
{
    GV_ACT       actor;
    SVECTOR      eye;          /* 0x20 */
    SVECTOR      center;       /* 0x28 */
    SVECTOR      rotate;       /* 0x30 */
    int          track;        /* 0x38 */
    int          type;         /* 0x3C */
    SVECTOR     *eye_src;      /* 0x40: overrides eye_key when set */
    SVECTOR     *center_src;   /* 0x44: overrides center_key when set */
    SVECTOR     *rotate_src;   /* 0x48: overrides rotate_key when set */
    int         *track_src;    /* 0x4C: overrides track_key when set */
    SVECTOR      eye_key;      /* 0x50 */
    SVECTOR      center_key;   /* 0x58 */
    SVECTOR      rotate_key;   /* 0x60 */
    int          track_key;    /* 0x68 */
    int          interp;       /* 0x6C */
    int          time;         /* 0x70 */
    int          flags;        /* 0x74 */
    DemocameFn1  near_fn;      /* 0x78 */
    DemocameFn2  near_vec_fn;  /* 0x7C */
    DemocameFn2  near_rot_fn;  /* 0x80 */
    DEMOCAM_KEY *key;          /* 0x84: next key */
    int          done;         /* 0x88 */
    int          n_keys;       /* 0x8C */
    int          frame;        /* 0x90 */
    DEMOCAM_CMD *cmd;          /* 0x94 */
    char         pad_98[0xAC - 0x98];
};

void *NewDemoCamera(DEMOCAM_KEY *keys);

#endif
