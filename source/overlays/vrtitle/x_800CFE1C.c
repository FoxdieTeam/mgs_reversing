// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C7FF4, camera_800C80E4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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
extern int                         vrtitle_dword_800D9D2C;

extern int vrtitle_dword_800D9D2C;

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

extern int        vrtitle_dword_800D9D78;
extern int        vrtitle_dword_800D9D2C;
extern int        vrtitle_dword_800D9D7C;
extern const char vrtitle_dword_800D9850[];
extern const char vrtitle_dword_800D985C[];

extern const char vrtitle_dword_800D9860[];
extern const char vrtitle_dword_800D985C[];
extern const char vrtitle_dword_800D986C[];
extern int        vrtitle_dword_800C1BAC;
extern int        vrtitle_dword_800D9D7C;

typedef struct CaptionInfo
{
    int     x;
    u_short y;
    short   field_6;
    int     field_8;
    int     color;
} CaptionInfo;

void vrtitle_800CFE1C(int code, char **pAreaNameForMenu, char **pAreaNameForSaveData)
{
    int i;

    if (code == 0)
    {
        *pAreaNameForMenu = (char *)vrtitle_dword_800D9850;
        *pAreaNameForSaveData = (char *)vrtitle_dword_800D985C;
    }

    GCL_SetArgTop((unsigned char *)vrtitle_dword_800D9D78);

    for (i = 0; i < code; i++)
    {
        if (GCL_NextStr() == 0)
        {
            return;
        }
        *pAreaNameForMenu = GCL_GetString((char *)GCL_NextStr());
        if (vrtitle_dword_800D9D7C > 0 && vrtitle_dword_800D9D2C == 0)
        {
            *pAreaNameForSaveData = GCL_GetString((char *)GCL_NextStr());
        }
    }
}

void vrtitle_800CFF0C(char *out, MEMCARD *unused, int hours, int minutes)
{
    char  playTime[11];
    char *discard;
    char *areaName;

    playTime[0] = 0x82;
    playTime[1] = (hours / 10) + 0x4F;
    playTime[2] = 0x82;
    playTime[3] = (hours % 10) + 0x4F;
    playTime[4] = 0x81;
    playTime[5] = 0x46;
    playTime[6] = 0x82;
    playTime[7] = (minutes / 10) + 0x4F;
    playTime[8] = 0x82;
    playTime[9] = (minutes % 10) + 0x4F;
    playTime[10] = '\0';

    if (vrtitle_dword_800D9D7C == 0)
    {
        vrtitle_800CFE1C(1, &discard, &areaName);
        areaName = (char *)&vrtitle_dword_800C1BAC;
    }
    else
    {
        vrtitle_800CFE1C(vrtitle_dword_800D9D7C, &discard, &areaName);
    }

    sprintf(out, (char *)vrtitle_dword_800D9860,
            vrtitle_dword_800D986C, vrtitle_dword_800D985C, playTime, vrtitle_dword_800D985C, areaName);
}
