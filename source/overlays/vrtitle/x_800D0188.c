// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C8314, camera_800C838C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
// Note that there are two "camera.c" actors,
// this is probably not the enemy/camera.c actor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "game/game.h"
#include "mts/mts.h"
#include "mts/taskid.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      f20;
    GV_PAD  *pad;
    int      f28;
    int      f2C;
    DG_PRIM *prim1, *prim2, *prim3;
    POLY_FT4 polys_lr[2];
    char     padding2[0x50];
    POLY_FT4 polys[9];
    POLY_FT4 polys2[26];
    int      field_654[4];
    GV_ACT  *field_664[9];
    GV_ACT  *field_688[26];
    char     padding3[0x10];
    MenuWork field_700;
    void    *field_920;
    u_long  *field_924_mOrderingTable;
    int      field_928;
    void    *field_92C[2];
    char     padding5[0x4000];
    int      field_4934;
    int      field_4938;
    char     padding6[0x2C];
    int      field_4968;
    int      field_496C;
    int      field_4970;
    char     padding6b[0x44];
    int      field_49B8;
    int      field_49BC;
    char     padding6c[0x8];
    int      field_49C8;
    MEMCARD  *field_49CC;
    int      field_49D0;
    char     padding6d[0xC];
    int      f49E0;
    char    *f49E4;
} Work;

extern char                       *MGS_MemoryCardName; /* in main.c */
extern SPRT                        vrtitle_dword_800D9D84;

// Copy of menu_radio_do_file_mode_helper2_helper_8004A4C4

// Copy of menu_radio_do_file_mode_helper4_helper_8004A54C

// duplicate of sub_8004A648

// duplicate of menu_radio_do_file_mode_helper3_helper_8004A790

// duplicate of init_file_mode_helper2_8004A800
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)

// duplicate of init_radio_message_board_80040F74
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
// and with one font_set_color missing

// duplicate of drawCaption_8004AE3C

// duplicate of sub_8004AEA8

// duplicate of show_message_8004AFE4

// See also updateCurrentEntry_8004B9C4() in datasave.c

// duplicate of menu_radio_do_file_mode_helper12_8004BA80

// duplicate of menu_radio_do_file_mode_helper14_8004BE98

// duplicate of menu_radio_do_file_mode_helper15_8004C04C, but with one missing line

// duplicate of menu_radio_do_file_mode_helper16_8004C164

typedef struct CaptionInfo
{
    int     x;
    u_short y;
    short   field_6;
    int     field_8;
    int     color;
} CaptionInfo;

extern int vrtitle_dword_800C1BCC;

void vrtitle_800D0188(MenuPrim *prim, SELECT_INFO *info)
{
    DR_TPAGE *pTpage;

    _NEW_PRIM(pTpage, prim);

    setlen(pTpage, 1);
    pTpage->code[0] = 0xE100061F | ((*(int *)((char *)info + 8) >> 3) & 0x60);
    addPrim(prim->ot, pTpage);
}

void vrtitle_800D0200(MenuPrim *prim, CaptionInfo *info, char *str)
{
    SPRT   *sprt;
    u_long *ot;
    int     x;
    int     color;
    int     c;
    int     u, v, w;
    char   *tbl;

    x = info->x;
    ot = prim->ot;
    color = info->color;

    for (; *str; str++)
    {
        c = *str | 0x20;

        if ((unsigned int)(c - '0') < 10)
        {
            u = (c - '0') * 8;
            v = 0xF8;
            w = 9;
        }
        else if ((unsigned int)(c - 'a') < 26)
        {
            if (c == 'i')
            {
                x += 3;
                u = 0x40;
                v = 0xF2;
                w = 6;
            }
            else
            {
                u = (c - 'a') * 8;
                v = 0xF2;
                w = 9;
            }
        }
        else if (c == ' ')
        {
            x += 9;
            continue;
        }
        else
        {
            u = 0;
            for (tbl = (char *)&vrtitle_dword_800C1BCC;; tbl += 2, u += 8)
            {
                if (*tbl == c)
                {
                    if (c == '!' || c == ':' || c == '[' || c == ']')
                    {
                        x += 3;
                        u += 0x50;
                        v = 0xF8;
                        w = 6;
                    }
                    else
                    {
                        u += 0x50;
                        v = 0xF8;
                        w = 9;
                    }
                    break;
                }
            }
        }

        _NEW_PRIM(sprt, prim);
        *sprt = vrtitle_dword_800D9D84;
        *(int *)&sprt->r0 = color;
        sprt->x0 = x;
        sprt->y0 = info->y;
        sprt->u0 = u;
        sprt->v0 = v;
        x += w;
        addPrim(ot, sprt);
    }
}
