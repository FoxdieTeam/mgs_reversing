#ifndef _VIBRATE_H_
#define _VIBRATE_H_

#include "libgv/libgv.h"

typedef struct      VibrateWork
{
    GV_ACT          actor;
    char            field_20_flags;
    char            field_21_increment;
    short           field_22_timer;
    unsigned char   *field_24_pData;
} VibrateWork;

int                 vibrate_act_helper_8005D358(VibrateWork *);
int                 vibrate_act_helper_8005D3A4(VibrateWork *);
void                vibrate_act_8005D424(VibrateWork *);

VibrateWork         *vibrate_init_8005D508(int);
VibrateWork         *NewPadVibration_8005D58C(unsigned char *, int);

#endif // _VIBRATE_H_
