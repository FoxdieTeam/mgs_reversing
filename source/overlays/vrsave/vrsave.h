#ifndef _VRSAVE_H
#define _VRSAVE_H

#include "menu/menuman.h"
#include "menu/radio.h"
#include "libgv/libgv.h"
#include <libgte.h>
#include <libgpu.h>

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

/* One item (button) of the VR save menu. */
typedef struct VR_SAVEMNGR_ITEM
{
    unsigned int flags;      /* 0x00 */
    RECT         rect;       /* 0x04: highlight rectangle */
    int          field_0C;   /* 0x0C */
    int          field_10;   /* 0x10 */
    int          tex_id;     /* 0x14 */
    int          proc;       /* 0x18: GCL proc executed when chosen */
    short        limit;      /* 0x1C: number of animation steps to wait */
    char         pad_1E[0x06];
    RECT         frame_rect; /* 0x24: rectangle the menu frame moves to when this item is selected */
    char         pad_2C[0x0A];
    short        step;       /* 0x36: animation step */
    u_char       state;      /* 0x38 */
    char         pad_39[0x03];
    POLY_FT4     polys[2];   /* 0x3C: highlight (double buffered) */
} VR_SAVEMNGR_ITEM;          /* 0x8C */

/* Work of the VR save manager actor ("savemngr.c"), see vrsave_800CBA1C. */
#define VR_SAVEMNGR_FRAME_POLYS 8 /* corners and edges of the menu frame */
#define VR_SAVEMNGR_WORK_SIZE   0x31C

typedef struct VR_SAVEMNGR_WORK
{
    GV_ACT   actor;                                      /* 0x00 */
    int      timer;                                      /* 0x20 */
    POLY_FT4 polys[2][VR_SAVEMNGR_FRAME_POLYS];          /* 0x24: menu frame (double buffered) */
    TILE     tiles[2];                                   /* 0x2A4: menu frame background */
    RECT     rect;                                       /* 0x2C4: current frame rectangle */
    short    cur_item;                                   /* 0x2CC: item the frame is on */
    short    next_item;                                  /* 0x2CE: item the frame moves to */
    short    state;                                      /* 0x2D0 */
    char     pad_2D2[0x0E];
    int      mission;                                    /* 0x2E0 */
    int      field_2E4;
    int      field_2E8;
    int      field_2EC;
    int      field_2F0;
    int      field_2F4;
    char     pad_2F8[0x14];
    int      field_30C;
    int      flags;                                      /* 0x310: bit 2: memory card present */
    int      score;                                      /* 0x314 */
    int      field_318;
} VR_SAVEMNGR_WORK;

#endif
