// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C4BAC, camera_800C4D20), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern int vrtitle_dword_800D9D3C;
extern int vrtitle_dword_800D9D40;

extern char vrtitle_dword_800D9660[];
extern char vrtitle_dword_800D9654[];
extern const char vrtitle_dword_800D9410[];
extern const char vrtitle_dword_800D942C[];
extern int vrtitle_dword_800D9D08;
extern int vrtitle_dword_800D9D0C;
extern int vrtitle_dword_800D9D10;
extern int vrtitle_dword_800D9D14;

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

int vrtitle_800CC9E8(MEMCARD *card, int index) {

    char         *buffer;
    int           result;
    int           retries;
    int           i;

    GM_PadResetDisable = 1;
    buffer = GV_AllocMemory(2, 0x2000);

    if (!buffer) {
        printf((char *)vrtitle_dword_800D9410);
    }

    result = 0;
    retries = 4;

    vrtitle_dword_800D9D08 = (int)buffer;
    vrtitle_dword_800D9D0C = (int)buffer;

    for (; retries > 0; retries--) {
        memcard_read(card->port, card->files[index].name, 0, buffer, 0x2000);

        while (memcard_status() > 0) {
            mts_wait_vbl(2);
        }

        if (memcard_status() == 0) {
            *(char *)&vrtitle_dword_800D9D10 = card->port;
            for (i = 0; i < 24; i++) {
                /* per-iteration scope for p710 is required for the match */
                char *p710 = (char *)&vrtitle_dword_800D9D14;
                p710[i] = card->files[index].name[i];
            }
            printf((char *)vrtitle_dword_800D942C, *(unsigned char *)&vrtitle_dword_800D9D10, (char *)&vrtitle_dword_800D9D14);
            result = 1;
            break;
        }
    }

    GM_PadResetDisable = 0;
    return result;
}

int vrtitle_800CCB5C(int arg0) {

    vrtitle_dword_800D9D3C = arg0;
    printf(vrtitle_dword_800D9654, arg0);

    mts_slp_tsk();
    printf(vrtitle_dword_800D9660, vrtitle_dword_800D9D40);

    return vrtitle_dword_800D9D40;
}
