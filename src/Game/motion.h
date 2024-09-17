#ifndef _MOTION_H_
#define _MOTION_H_

#include "psyq.h"
#include "libdg/libdg.h"

typedef struct MOTION_INFO
{
    short field_0;
    // Controls the sound of Snake's footsteps; values, ranging from 0x0-0x11 (with intermediary jumps to 0x80 and
    // 0xff), appear to be the current frame of the sound sample (with frame 0x8 corresponding to the hard footstep
    // sound). Disabling any of the reads or writes causes Snake's footsteps no longer to make any noise, such that he
    // can for instance walk in puddles without being heard by enemies.
    short          field_2_footstepsFrame;
    short          field_4;
    short          field_6;
    unsigned int   field_8;
    MOTION_SEGMENT    *field_C_oar_records;
    short          field_10;
    short          field_12;
    short          field_14;
    unsigned short field_16_time;
} MOTION_INFO;

typedef struct _MOTION_CONTROL
{
    DG_OAR     *field_00_oar;   // 0x00
    MOTION_INFO field_04_info1; // 0x04
    MOTION_INFO field_1C_info2; // 0x1C

    // In SnaInitWork, this is a pointer to his CONTROL's rotator (0x20->0x8).
    SVECTOR *field_34; // 0x34

    // In SnaInitWork, this is a pointer to his CONTROL's movement vector (0x20->0x44).
    SVECTOR        *step;     // 0x38
    short *field_3C; // 0x3C
    unsigned long   interp;   // 0x40
    SVECTOR         field_44;
    SVECTOR        *field_4C;
    // todo: padding field here?
} MOTION_CONTROL;

void sub_8003501C(MOTION_CONTROL *m_ctrl, int a1, int motion);
void sub_800350D4(MOTION_CONTROL *m_ctrl, int a1, int motion);
int  Process_Oar_8003518C( MOTION_CONTROL *ctrl, MOTION_INFO *info, int index );
void Kmd_Oar_Inflate_800353E4(MOTION_SEGMENT *pRecord);
int  sub_8003556C(MOTION_CONTROL *m_ctrl);
int  oar_related_800356FC(MOTION_CONTROL *, MOTION_INFO *);
void sub_8003603C(MOTION_CONTROL *pCtrl, MOTION_INFO *pInfo);
int  sub_800360EC(MOTION_CONTROL *pCtrl, MOTION_INFO *pInfo, int a3, int a4);
int negate_rots_800366B8(SVECTOR *arg0, SVECTOR *arg1);

#endif // _MOTION_H_
