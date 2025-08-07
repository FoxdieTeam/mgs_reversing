#ifndef __MGS_GAME_MOTION_H__
#define __MGS_GAME_MOTION_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "fmt_mot.h"
#include "libdg/libdg.h"

typedef struct MOTION_INFO
{
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

typedef struct _MOTION_CONTROL
{
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

void GM_ConfigAction(MOTION_CONTROL *m_ctrl, int action, int frame);
void GM_ConfigActionOverride(MOTION_CONTROL *m_ctrl, int action, int frame);
int  GM_PlayAction(MOTION_CONTROL *m_ctrl);

#endif // __MGS_GAME_MOTION_H__
