// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5D54), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern RECT                        vrtitle_dword_800C1B74;
extern char                       *vrtitle_dword_800D9D68;
extern char                       *MGS_MemoryCardName; /* in main.c */

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

void vrtitle_800CDBB0(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&vrtitle_dword_800C1B74, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &vrtitle_dword_800C1B74, 960, 510);
        font_set_kcb(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer(ptr_local_kcb, allocated_kcb + 1);
        font_set_color(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color(ptr_local_kcb, 2, 0x3a4b, 0);
        // font_set_color(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        vrtitle_dword_800D9D68 = NULL;
    }
}
