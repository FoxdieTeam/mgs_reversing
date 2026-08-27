#ifndef __MGS_GAME_JIMCTRL_H__
#define __MGS_GAME_JIMCTRL_H__

#define array_800B933C_SIZE 7

#include "libgv/libgv.h"

typedef struct
{
    u_short       field_0;
    char          field_2;
    unsigned char field_3;
} array_800B933C_child;

unsigned int jimctrl_helper_80037F68(unsigned int);

void *NewJimakuControl(u_long flags);

int                   jimctrl_80038688(void);
array_800B933C_child *jimctrl_80038698(void);

#endif // __MGS_GAME_JIMCTRL_H__
