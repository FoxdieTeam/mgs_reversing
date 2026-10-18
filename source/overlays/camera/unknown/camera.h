#ifndef _CAMERA_UNKNOWN_CAMERA_H
#define _CAMERA_UNKNOWN_CAMERA_H

// Work of the "camera.c" file-mode / memory-card menu actor. Shared by the
// main tree camera overlay and the VR revision copies (vrtitle, vrsave).

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "menu/menuman.h"
#include "memcard/memcard.h"

typedef struct _Work
{
    /* 0x0000 */ GV_ACT   actor;
    /* 0x0020 */ int      f20;
    /* 0x0024 */ GV_PAD  *pad;
    /* 0x0028 */ int      f28;
    /* 0x002C */ int      f2C;
    /* 0x0030 */ DG_PRIM *prim1, *prim2, *prim3;
    /* 0x003C */ POLY_FT4 polys_lr[2];
    /* 0x008C */ char     padding2[0x50];
    /* 0x00DC */ POLY_FT4 polys[9];
    /* 0x0244 */ POLY_FT4 polys2[26];
    /* 0x0654 */ int      field_654[4];
    /* 0x0664 */ GV_ACT  *field_664[9];
    /* 0x0688 */ GV_ACT  *field_688[26];
    /* 0x06F0 */ char     padding3[0x10];
    /* 0x0700 */ MenuWork field_700;
    /* 0x0920 */ void    *field_920;
    /* 0x0924 */ u_long  *field_924_mOrderingTable;
    /* 0x0928 */ int      field_928;
    /* 0x092C */ void    *field_92C[2];
    /* 0x0934 */ char     padding5[0x4000];
    /* 0x4934 */ int      field_4934;
    /* 0x4938 */ int      field_4938;
    /* 0x493C */ char     padding6[0x2C];
    /* 0x4968 */ int      field_4968;
    /* 0x496C */ int      field_496C;
    /* 0x4970 */ int      field_4970;
    /* 0x4974 */ char     padding6b[0x44];
    /* 0x49B8 */ int      field_49B8;
    /* 0x49BC */ int      field_49BC;
    /* 0x49C0 */ char     padding6c[0x8];
    /* 0x49C8 */ int      field_49C8;
    /* 0x49CC */ MEMCARD  *field_49CC;
    /* 0x49D0 */ int      field_49D0;
    /* 0x49D4 */ char     padding6d[0xC];
    /* 0x49E0 */ int      f49E0;
    /* 0x49E4 */ char    *f49E4;
} Work;

typedef struct CaptionInfo
{
    /* 0x00 */ int     x;
    /* 0x04 */ u_short y;
    /* 0x06 */ short   field_6;
    /* 0x08 */ int     field_8; // semi-transparency mode bits (see DR_TPAGE code in camera_800C8314)
    /* 0x0C */ int     color;
} CaptionInfo;

#endif
