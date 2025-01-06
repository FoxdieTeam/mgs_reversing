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

VibrateWork *NewVibration(int);
VibrateWork *NewPadVibration(unsigned char *, int);

#endif // _VIBRATE_H_
