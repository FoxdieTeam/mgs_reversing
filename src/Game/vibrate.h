#ifndef _VIBRATE_H_
#define _VIBRATE_H_

#include "libgv/libgv.h"

struct Actor_Vibrate
{
    Actor          field_0_actor;
    char           field_20_flags;
    char           field_21_increment;
    short          field_22_timer;
    unsigned char *field_24_pData;
};

int                   vibrate_act_helper_8005D358(struct Actor_Vibrate *);
int                   vibrate_act_helper_8005D3A4(struct Actor_Vibrate *);
void                  vibrate_act_8005D424(struct Actor_Vibrate *);
struct Actor_Vibrate *vibrate_init_8005D508(int);
struct Actor_Vibrate *vibrate_init2_8005D58C(unsigned char *, int);

#endif // _VIBRATE_H_
