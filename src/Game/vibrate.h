#ifndef _VIBRATE_H_
#define _VIBRATE_H_

#include "libgv/libgv.h"

typedef struct      Actor_Vibrate
{
    GV_ACT          actor;
    char            field_20_flags;
    char            field_21_increment;
    short           field_22_timer;
    unsigned char   *field_24_pData;
} Actor_Vibrate;

int                 vibrate_act_helper_8005D358(Actor_Vibrate *);
int                 vibrate_act_helper_8005D3A4(Actor_Vibrate *);
void                vibrate_act_8005D424(Actor_Vibrate *);

Actor_Vibrate       *vibrate_init_8005D508(int);
Actor_Vibrate       *NewPadVibration_8005D58C(unsigned char *, int);

#endif // _VIBRATE_H_
