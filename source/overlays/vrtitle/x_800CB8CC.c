// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C3A7C, camera_800C3B9C, camera_800C3D3C, camera_800C3ED8, camera_800C408C, camera_800C4184, camera_800C4350), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern const char vrtitle_dword_800D9254[];
extern const char vrtitle_dword_800D926C[];
extern int vrtitle_dword_800D9D08;
extern const char vrtitle_dword_800D91C8[];

void vrtitle_800CBD28(Work *);

extern int vrtitle_dword_800C14F0[];
extern const char vrtitle_dword_800D91D4[];
extern const char vrtitle_dword_800D91E8[];
extern const char vrtitle_dword_800D9210[];
extern const char vrtitle_dword_800D9228[];

extern const char vrtitle_dword_800D9244[];

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

void vrtitle_800CB8CC(unsigned long *runlevel, RECT *pRect)
{
    int            x, y, w, h;
    int            x2, y2;
    unsigned long *cell;

    DecDCTReset(0);

    x = pRect->x;
    y = pRect->y;
    w = pRect->w;
    h = pRect->h;

    pRect->w = 16;
    pRect->h = 16;

    x2 = x + w;
    y2 = y + h;

    cell = (unsigned long *)0x80182000; // ori

    DecDCTin(runlevel, 0);

    while (pRect->x < x2)
    {
        pRect->y = y;
        while (pRect->y < y2)
        {
            DecDCTout(cell, 128);
            DecDCToutSync(0);
            LoadImage(pRect, cell);
            pRect->y += 16;
        }
        pRect->x += 16;
    }
    pRect->x = x;
    pRect->y = y;
}

void vrtitle_800CB9EC(int arg0, u_short *out)
{
    short  hdr;
    short  n;
    int    count;
    int    rest;
    int    i;
    u_char b;
    int    c;
    u_char run;
    int    level;

    n = 1;
    i = 4;
    hdr = (((u_char *)vrtitle_dword_800D9D08)[0] << 8) | ((u_char *)vrtitle_dword_800D9D08)[1];
    *out++ = hdr;
    *out++ = 0x3800;
    count = hdr * 4;
    *out++ = (((u_char *)vrtitle_dword_800D9D08)[2] << 8) | ((u_char *)vrtitle_dword_800D9D08)[3];

    while (i < count)
    {
        b = ((u_char *)vrtitle_dword_800D9D08)[i];
        if (!(b & 0x80))
        {
            if (b == 0xF)
            {
                *out++ = 0xFE00;
                i++;
                c = ((u_char *)vrtitle_dword_800D9D08)[i];
                if (c == 0xF)
                {
                    n++;
                    break;
                }
                i++;
                n += 2;
                run = c; /* required for the match */
                *out = (run << 8) | ((u_char *)vrtitle_dword_800D9D08)[i];
            }
            else
            {
                *out = (((b & 0xF) - 8) & 0x3FF) | ((b >> 4) << 10);
                n++;
            }
        }
        else
        {
            i++;
            run = (b >> 1) & 0x3F;
            rest = b & 1; /* borrowed as a temp; a fresh local breaks the match */
            level = (((u_char *)vrtitle_dword_800D9D08)[i] + (rest << 8)) - 0x100;
            *out = (run << 10) | (level & 0x3FF);
            n++;
        }
        i++;
        out++;
    }

    rest = hdr * 2 - n;
    for (i = 0; i < rest; i++)
    {
        *out++ = 0xFE00;
    }

    printf((char *)vrtitle_dword_800D91C8, out);
}

void vrtitle_800CBB8C(Work *work)
{
    POLY_FT4 *p;
    int len = 9;
    int code = 0x2C;
    int vmax = 0xB0;
    int umax;
    short y_top = -0x5A;
    short y_bot = 0x56;

    p = &work->polys_lr[0];
    umax = 0x90;
    setlen(p, len);
    setcode(p, code);
    p->u0 = 0;    p->v0 = 0;
    p->u1 = umax; p->v1 = 0;
    p->u2 = 0;    p->v2 = vmax;
    p->u3 = umax; p->v3 = vmax;
    p->tpage = GetTPage(2, 0, 0, 0x100);
    p->r0 = work->field_4968;
    p->g0 = work->field_496C;
    p->b0 = work->field_4970;
    p->x0 = -0x90; p->y0 = y_top;
    p->x1 = 0;     p->y1 = y_top;
    p->x2 = -0x90; p->y2 = y_bot;
    p->x3 = 0;     p->y3 = y_bot;
    SetSemiTrans(p, 0);
    work->field_654[0] = 0x800;

    p = &work->polys_lr[1];
    umax = 0xA0;
    setlen(p, len);
    setcode(p, code);
    p->u0 = 0x10; p->v0 = 0;
    p->u1 = umax; p->v1 = 0;
    p->u2 = 0x10; p->v2 = vmax;
    p->u3 = umax; p->v3 = vmax;
    p->tpage = GetTPage(2, 0, 0x80, 0x100);
    p->r0 = work->field_4968;
    p->g0 = work->field_496C;
    p->b0 = work->field_4970;
    p->x0 = 0;    p->y0 = y_top;
    p->x1 = 0x90; p->y1 = y_top;
    p->x2 = 0;    p->y2 = y_bot;
    p->x3 = 0x90; p->y3 = y_bot;
    SetSemiTrans(p, 0);
    work->field_654[1] = 0x800;
}

void vrtitle_800CBD28(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->polys_lr;
    dst = (POLY_FT4 *)work->prim1->packs[GV_Clock];
    for (i = 0; i < 4; i++)
    {
        *dst = *src;
        *(short *)dst = (short)work->field_654[i];
        src++;
        dst++;
    }

    src = work->polys;
    dst = (POLY_FT4 *)work->prim2->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        *(short *)dst = (short)(int)work->field_664[i];
        src++;
        dst++;
    }

    src = work->polys2;
    dst = (POLY_FT4 *)work->prim3->packs[GV_Clock];
    for (i = 0; i < 26; i++)
    {
        *dst = *src;
        *(short *)dst = (short)(int)work->field_688[i];
        src++;
        dst++;
    }
}

int vrtitle_800CBEDC(Work *unused, int idx)
{
    int   *base;
    int   *entry;
    int    id;
    int    sector;
    int    size;
    void  *buf;
    DG_TEX *tex;

    base   = vrtitle_dword_800C14F0;
    entry  = base + idx * 3;
    size   = entry[2];
    id     = entry[0];
    sector = entry[1];
    buf    = GV_Malloc(size);
    FS_LoadFileRequest(FS_FILE_BRF, sector, size, buf);
    while (FS_LoadFileSync() > 0)
    {
        mts_wait_vbl(1);
    }
    printf((char *)vrtitle_dword_800D91D4);
    tex = DG_GetTexture(id);
    if (tex->id != 0)
    {
        tex->id = 0;
        printf((char *)vrtitle_dword_800D91E8);
    }
    else
    {
        printf((char *)vrtitle_dword_800D9210);
    }
    DG_LoadInitPcx(buf, id);
    printf((char *)vrtitle_dword_800D9228);
    GV_Free(buf);
    return id;
}

void vrtitle_800CBFD4(Work *work)
{
    POLY_FT4 *p;
    DG_TEX   *tex;

    p = &work->polys_lr[2];
    setPolyFT4(p);
    p->r0 = work->field_4968;
    p->g0 = work->field_496C;
    p->b0 = work->field_4970;
    p->x0 = -0x7F; p->y0 = -0x52;
    p->x1 = 0x7F;  p->y1 = -0x52;
    p->x2 = -0x7F; p->y2 = 0x4E;
    p->x3 = 0x7F;  p->y3 = 0x4E;
    tex = DG_GetTexture(vrtitle_800CBEDC(work, work->field_4934 - 1));
    {
        int off_x = tex->off_x;
        int w     = tex->w;
        int off_y = tex->off_y;
        int h     = tex->h;
        int u_right  = off_x + w + 1;
        int v_bottom = off_y + h + 1;
        p->u0 = off_x;
        p->v0 = off_y;
        p->u1 = u_right;
        p->v1 = off_y;
        p->u2 = off_x;
        p->v2 = v_bottom;
        p->u3 = u_right;
        p->v3 = v_bottom;
    }
    p->tpage = tex->tpage;
    p->clut  = tex->clut;
    SetSemiTrans(p, 1);
    work->field_654[2] = 0x600;

    p = &work->polys_lr[3];
    setPolyFT4(p);
    p->r0 = 0;
    p->g0 = 0;
    p->b0 = 0;
    p->x0 = -0xA0; p->y0 = -0x70;
    p->x1 = 0xA0;  p->y1 = -0x70;
    p->x2 = -0xA0; p->y2 = 0x70;
    p->x3 = 0xA0;  p->y3 = 0x70;
    tex = DG_GetTexture(GV_StrCode(vrtitle_dword_800D9244));
    {
        int off_x = tex->off_x;
        int w     = tex->w;
        int off_y = tex->off_y;
        int h     = tex->h;
        int u_right  = off_x + w;
        int v_bottom = off_y + h;
        p->u0 = off_x;
        p->v0 = off_y;
        p->u1 = u_right;
        p->v1 = off_y;
        p->u2 = off_x;
        p->v2 = v_bottom;
        p->u3 = u_right;
        p->v3 = v_bottom;
    }
    p->tpage = tex->tpage;
    p->clut  = tex->clut;
    SetSemiTrans(p, 1);
    work->field_654[3] = 0;
}

void vrtitle_800CC1A0(Work* work) {

    printf((char *)vrtitle_dword_800D9254);
    printf((char *)vrtitle_dword_800D926C, work->field_4934);

    vrtitle_800CBFD4(work);
}
