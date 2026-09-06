#ifndef __MGS_GAME_JIMCTRL_H__
#define __MGS_GAME_JIMCTRL_H__

#define PAKU_MAX 7

#include "libgv/libgv.h"

typedef struct
{
    u_short id;
    u_char  eye;
    u_char  mouth;
} PAKU;

unsigned int jimctrl_helper_80037F68(unsigned int);

void *NewJimakuControl(u_long flags);

int   jimctrl_80038688(void);
PAKU *jimctrl_80038698(void);

#endif // __MGS_GAME_JIMCTRL_H__
