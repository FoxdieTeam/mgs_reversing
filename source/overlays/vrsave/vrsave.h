#ifndef _VRSAVE_H
#define _VRSAVE_H

#include "menu/menuman.h"
#include "menu/radio.h"

/* VR revision of the SELECT_INFO menu entry: 0x28 bytes instead of 0x24. */
typedef struct VR_MENU_CURPOS
{
    char mes[ 32 ];
    int  num;
    int  field_24;
} VR_MENU_CURPOS;

typedef struct VR_SELECT_INFO
{
    short       xofs;
    short       yofs;
    short       current;
    short       top;
    char        max_num;
    short       move_dir;
    short       move_dir_delay;
    short       field_E;
    short       width;
    short       height;
    short       enable;
    short       open_count;
    short       field_18;
    KCB        *kcb;
    const char *message;
    VR_MENU_CURPOS menu[ 0 ];
} VR_SELECT_INFO;

#endif
