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

void vrtitle_800D03D8(MenuPrim *prim, SELECT_INFO *info, char *arg2)
{
    char sp10[64];

    sprintf(sp10, arg2);
    vrtitle_800D0200(prim, (CaptionInfo *)info, sp10);
    vrtitle_800D0188(prim, info);
}

void vrtitle_800D042C(int *arg0, int r, int g, int b)
{
    arg0[3] = (r | (g << 8) | (b << 16) | (GPU_CODE_SPRT << 24));
}

void vrtitle_800D044C(void)
{
    short sp0[4];
    SPRT *sprt;

    // Let's waste cycles by puting unused stuff on stack:
    sp0[0] = 976;
    sp0[1] = 511;
    sp0[2] = 16;
    sp0[3] = 1;

    sprt = &vrtitle_dword_800D9D84;
    LSTORE(0x80808080, &sprt->r0);
    setUV0(sprt, 0, 242);
    setWH(sprt, 8, 6);
    setSprt(sprt);
    setClut(sprt, 976, 511);
}

void vrtitle_800D04C0(Work *work)
{
    int i;

    for (i = 3; i >= 0; i--)
    {
        work->field_654[i] = 0;
    }

    for (i = 8; i >= 0; i--)
    {
        work->field_664[i] = NULL;
    }

    for (i = 0x19; i >= 0; i--)
    {
        work->field_688[i] = NULL;
    }
}
