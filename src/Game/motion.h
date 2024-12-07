#ifndef _MOTION_H_
#define _MOTION_H_

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
    unsigned int    field_8;
    MOTION_SEGMENT *m_segs;
    short           action_flag;
    short           field_12;
    short           field_14;
    unsigned short  time;
} MOTION_INFO;

typedef struct _MOTION_CONTROL
{
    DG_OAR       *oar;
    MOTION_INFO   info1;
    MOTION_INFO   info2;
    SVECTOR      *rot;    // pointer to the associated CONTROL's rot vector.
    SVECTOR      *step;   // pointer to the associated CONTROL's step vector.
    short        *height; // pointer to the associated OBJECT's height.
    unsigned long interp;
    SVECTOR       waist_rot;
    SVECTOR      *rots;   // pointer to the associated OBJECT's per-joint rots.
} MOTION_CONTROL;

void sub_8003501C(MOTION_CONTROL *m_ctrl, int action_flag, int motion);
void sub_800350D4(MOTION_CONTROL *m_ctrl, int action_flag, int motion);
int  Process_Oar_8003518C(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action_flag);
void Kmd_Oar_Inflate_800353E4(MOTION_SEGMENT *m_seg);
int  sub_8003556C(MOTION_CONTROL *m_ctrl);
int  oar_related_800356FC(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info);
void sub_8003603C(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info);
int  sub_800360EC(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action_flag, int motion);
int  negate_rots_800366B8(SVECTOR *arg0, SVECTOR *arg1);

#endif // _MOTION_H_
