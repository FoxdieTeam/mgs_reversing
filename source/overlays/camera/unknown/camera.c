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
    POLY_FT4 polys_lr[4];
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
    char     padding6[0x10];
    char     field_494C_name[24];
    int      field_4964_name_len;
    int      field_4968;
    int      field_496C;
    int      field_4970;
    char     padding6b[0xC];
    int      field_4980;
    int      field_4984;
    int      field_4988;
    int      field_498C;
    int      field_4990;
    char     field_4994_str[0x14];
    int      field_49A8[4];
    int      field_49B8;
    int      field_49BC;
    char     padding6c[0x8];
    int      field_49C8;
    MEMCARD  *field_49CC;
    int      field_49D0;
    char     field_49D4[9];
    char     field_49DD[3];
    int      f49E0;
    char    *f49E4;
} Work;

extern char *MGS_MemoryCardName; /* in main.c */

/* bss */
u_char                     *SECTION(".bss") camera_photo_buf_800D0700;  /* read pointer into the loaded photo file */
char                       *SECTION(".bss") camera_file_buf_800D0704;   /* photo file buffer (0x4000 bytes) */
u_char                      SECTION(".bss") camera_card_port_800D0708;
int                         SECTION(".bss") camera_dword_800D070C;
char                        SECTION(".bss") camera_file_name_800D0710[24];
int                         SECTION(".bss") camera_dword_800D0728;
DATA_INFO                  *SECTION(".bss") camera_data_info_800D072C;
char                       *SECTION(".bss") camera_stack_800D0730;
int                         SECTION(".bss") camera_dword_800D0734;
int                         SECTION(".bss") camera_request_800D0738;
int                         SECTION(".bss") camera_result_800D073C;
int                         SECTION(".bss") camera_dword_800D0740;
int                         SECTION(".bss") camera_dword_800D0744;
int                         SECTION(".bss") camera_dword_800D0748;
int                         SECTION(".bss") camera_dword_800D074C;
int                         SECTION(".bss") camera_dword_800D0750;
int                         SECTION(".bss") camera_dword_800D0754;
int                         SECTION(".bss") camera_dword_800D0758;
RadioFileModeStru_800ABB7C *SECTION(".bss") camera_dword_800D075C;
char                       *SECTION(".bss") camera_dword_800D0760;
int                         SECTION(".bss") camera_dword_800D0764;
int                         SECTION(".bss") camera_dword_800D0768;
int                         SECTION(".bss") camera_dword_800D076C;
u_char                     *SECTION(".bss") camera_gcl_args_800D0770;
int                         SECTION(".bss") camera_dword_800D0774;
int                         SECTION(".bss") camera_dword_800D0778;
int                         SECTION(".bss") camera_dword_800D077C;
SPRT                        SECTION(".bss") camera_sprt_800D0780;

typedef struct SINREI_PHOTO
{
    int id;     /* texture id */
    int sector; /* BRF file sector */
    int size;
} SINREI_PHOTO;

/* Spirit ("sinrei") photos, indexed by sinrei number - 1 */
SINREI_PHOTO camera_sinrei_photos_800C3218[] = {
    {0x530C, 0x0A1E, 0x2AEB},
    {0xEFCC, 0x0A24, 0x10FF},
    {0x65B7, 0x0A27, 0x1D6A},
    {0x8272, 0x0A2B, 0x2245},
    {0xF00A, 0x0A30, 0x1C05},
    {0x8327, 0x0A34, 0x177A},
    {0xAA2B, 0x0A37, 0x1BF8},
    {0xD137, 0x0A3B, 0x3122},
    {0xBEEA, 0x0A42, 0x20D6},
    {0xFE14, 0x0A47, 0x31BA},
    {0xB8E3, 0x0A4E, 0x23EF},
    {0x3810, 0x0A53, 0x2445},
    {0xCF7C, 0x0A58, 0x2E9D},
    {0xCA9A, 0x0A5E, 0x1FDC},
    {0x7D2A, 0x0A62, 0x1B3A},
    {0xCD2A, 0x0A66, 0x16B0},
    {0xFEEC, 0x0A69, 0x180E},
    {0x6A76, 0x0A6D, 0x2603},
    {0xA8E5, 0x0A72, 0x39F5},
    {0x7299, 0x0A7A, 0x2494},
    {0x11BD, 0x0A7F, 0x1660},
    {0x18D0, 0x0A82, 0x20A3},
    {0x6ACF, 0x0A87, 0x1846},
    {0x61E3, 0x0A8B, 0x1F94},
    {0xD009, 0x0A8F, 0x166B},
    {0x6375, 0x0A92, 0x1E99},
    {0x75FF, 0x0A96, 0x180C},
    {0x68FA, 0x0A9A, 0x1891},
    {0x7B2F, 0x0A9E, 0x1611},
    {0xAC34, 0x0AA1, 0x2603},
    {0xB2F0, 0x0AA6, 0x1593},
    {0x7CA4, 0x0AA9, 0x23A9},
    {0xFA5B, 0x0AAE, 0x21B1},
    {0x69B2, 0x0AB3, 0x25FF},
    {0x2BCF, 0x0AB8, 0x2F26},
    {0x68C8, 0x0ABE, 0x2606},
    {0x82EA, 0x0AC3, 0x20E0},
    {0xA791, 0x0AC8, 0x2965},
    {0x800A, 0x0ACE, 0x2DB5},
    {0xB911, 0x0AD4, 0x4043},
    {0x386B, 0x0ADD, 0x1E0C},
    {0x12E1, 0x0AE1, 0x12BA},
    {0x4B59, 0x0AE4, 0x3601},
};

Menu_Triangle camera_triangle_800C341C = {295, 209, 303, 209, 299, 213, 0x80808080};

int camera_dword_800C342C = 0;
int camera_dword_800C3430 = -1;
int camera_dword_800C3434 = 0;

int camera_clutsAndIcons_800C3438[6][40] = {
    {
        // CLUT for icon 1 (8 * 4 bytes = 32 bytes)
        0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,
        // Icon 1 (32 * 4 bytes = 128 bytes): Snake
        0x12211,    0xEA00310, 0x20000000, 0xEC00331, 0x23210012, 0xEB20243, 0x33332213, 0xEA10134,
        0x44422233, 0xEA10123, 0x34322343, 0xED11212, 0x24444443, 0xEE02221, 0x24444343, 0xEE30132,
        0x23444233, 0xEE00133, 0x22334301, 0xEB00123, 0x21224420, 0xD000113, 0x22100100, 0xA100202,
        0x32112344, 0x1100201, 0x23233200, 0x1000200, 0x2212222,  0x1000220, 0,          0,
    },
    {
        // CLUT for icon 2
        0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,
        // Icon 2: Meryl
        0x11124444, 0x2221131, 0x21000134, 0x2210222, 0x1114,     0x1230,    0x10000124, 0x241,
        0x11123234, 0x20234,   0x43334444, 0x10234,   0x44444444, 0x221233,  0x44444444, 0x1011133,
        0x34444444, 0x2100123, 0x34444334, 0x1110023, 0x33444421, 0x1000012, 0x33433443, 0x100002,
        0x23320211, 0xB001001, 0x13333233, 0xAC10000, 0x1333322,  0xCB10100, 0,          0,
    },
    {
        // CLUT for icon 3
        0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,
        // Icon 3: Otacon
        0x1343023,  0x1102021, 0x13444312, 0x1001020, 0x3444301,  0x120,     0x22343113, 0x10021,
        0x32211213, 0x10012,   0x33334433, 0x21002,   0x24444433, 0x1002002, 0x24444334, 0x2210001,
        0x23444314, 0xB100010, 0x12444302, 0xDA10011, 0x22344421, 0xEBA0002, 0x22212333, 0xEEC1001,
        0x21310100, 0xEC10100, 0x12132344, 0xC312200, 0x2112222,  0x4233101, 0,          0,
    },
    {
        // CLUT for icon 4
        0x2CA51C21, 0x456B3908, 0x5E3151CE, 0x217414EF, 0x363929D6, 0x10550C13, 0x151814B7, 0x19BC195A,
        // Icon 4: Ninja
        0x34455555, 0xFA12022, 0x255300,   0xFA12300, 0x241CD,    0xFA12240, 0x21000BDA, 0xFA11234,
        0x445521CD, 0xFB11223, 0x34455300, 0xFDA1123, 0x33445552, 0xFFA1122, 0x33445551, 0xFFA1112,
        0x12344551, 0xFFB1221, 0x31344551, 0xFFDA122, 0x31334451, 0xFFFA112, 0x22014451, 0xFFFB012,
        0x24213451, 0xFFFB111, 0x22313441, 0xFFFB201, 0x22312341, 0xFFFA310, 0,          0,
    },
    {
        // CLUT for icon 5
        0x14A90425, 0x35B1252D, 0x88A4635, 0x217414EF, 0x363929D6, 0x49035844, 0x2A4139A2, 0x1E8316E0,
        // Icon 5: Mei Ling
        0x10013444, 0xE021020, 0x12221234, 0xA010031, 0x12224,    0x32,      0x10001224, 0x200030,
        0x10022324, 0x410332,  0x32233434, 0x210333,  0x44444444, 0x110233,  0x44444444, 0xA010133,
        0x44444434, 0xCA10133, 0x34444432, 0xECBA023, 0x34433443, 0xEEDD013, 0x33421211, 0xEEED102,
        0x23333222, 0xEEEC101, 0x12334310, 0xEED0100, 0x1233444,  0xEEA1002, 0,          0,
    },
    {
        // CLUT for icon 6
        0x14A90425, 0x35B1252D, 0x88A4635, 0x217414EF, 0x363929D6, 0x44693427, 0x60CD508B, 0x64896CEF,
        // Icon 6: Campbell
        0x11001123, 0xED00210, 0x10000003, 0xEB01100, 0x11201013, 0xB200210, 0x12212124, 0xB020221,
        0x22322234, 0xC211123, 0x44322144, 0xDB10123, 0x33321234, 0xEC01012, 0x23211023, 0xEEB0112,
        0x22122102, 0xEED1121, 0x21222332, 0xEED2122, 0x10121100, 0xEEC0122, 0x10123433, 0xEEA0021,
        0x12222100, 0xEC00021, 0x1221111,  0xEA00102, 0x22222333, 0xB000301, 0,          0
    }
};

char camera_memoryCardFileName_800C37F8[] = "BISLPM-99999        ";

void camera_800C3ED8(Work *);
void camera_800C6054(MenuWork *work, u_long *ot, SELECT_INFO *info);
void camera_800CD790(Work *);
void camera_800CDAB4(Work *);
void camera_800CDF18(Work *);
void camera_800C4394(Work *);
void camera_800CA918(Work *);
void camera_800CC3C8(Work *);
void camera_800CCBB0(Work *);
void camera_800CBDE4(Work *);
int camera_800C73E4(MenuWork *work, GV_PAD *pad);
void camera_800C86BC(Work *work, int x, int y, int w, int h, int color, int unused);

void camera_800C3A7C(unsigned long *runlevel, RECT *pRect)
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

void camera_800C3B9C(int arg0, u_short *out)
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
    hdr = (camera_photo_buf_800D0700[0] << 8) | camera_photo_buf_800D0700[1];
    *out++ = hdr;
    *out++ = 0x3800;
    count = hdr * 4;
    *out++ = (camera_photo_buf_800D0700[2] << 8) | camera_photo_buf_800D0700[3];

    while (i < count)
    {
        b = camera_photo_buf_800D0700[i];
        if (!(b & 0x80))
        {
            if (b == 0xF)
            {
                *out++ = 0xFE00;
                i++;
                c = camera_photo_buf_800D0700[i];
                if (c == 0xF)
                {
                    n++;
                    break;
                }
                i++;
                n += 2;
                run = c; /* required for the match */
                *out = (run << 8) | camera_photo_buf_800D0700[i];
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
            level = (camera_photo_buf_800D0700[i] + (rest << 8)) - 0x100;
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

    printf("out = %x\n", (u_int)out);
}
void camera_800C3D3C(Work *work)
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
void camera_800C3ED8(Work *work)
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
int camera_800C408C(Work *unused, int idx)
{
    SINREI_PHOTO *photos;
    SINREI_PHOTO *photo;
    int           id;
    int           sector;
    int           size;
    void         *buf;
    DG_TEX       *tex;

    photos = camera_sinrei_photos_800C3218;
    photo  = &photos[idx];
    size   = photo->size;
    id     = photo->id;
    sector = photo->sector;
    buf    = GV_Malloc(size);
    FS_LoadFileRequest(FS_FILE_BRF, sector, size, buf);
    while (FS_LoadFileSync() > 0)
    {
        mts_wait_vbl(1);
    }
    printf("Check Texture Id\n");
    tex = DG_GetTexture(id);
    if (tex->id != 0)
    {
        tex->id = 0;
        printf("This Id is Exist. So I clear This ID!\n");
    }
    else
    {
        printf("This Id is not Exist!\n");
    }
    DG_LoadInitPcx(buf, id);
    printf("Texture LoadImage Finish!\n");
    GV_Free(buf);
    return id;
}

void camera_800C4184(Work *work)
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
    tex = DG_GetTexture(camera_800C408C(work, work->field_4934 - 1));
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
    tex = DG_GetTexture(GV_StrCode("cam_ex_flush"));
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

void camera_800C4350(Work* work) {

    printf("This is Sinrei Photo!\n");
    printf("Sinrei No = %d\n", work->field_4934);

    camera_800C4184(work);
}

/*
 * rdata (strings, switch jump tables) of the functions that are still asm.
 * The jump tables hold code addresses inside those functions.
 */
/* rdata of camera_800C4394 */
const char camera_aThisphotodataisfirst_800CFB68[] = "This Photo Data is First\n";
const char camera_aThisphotodataischanged_800CFB84[] = "This Photo Data is Changed\n";
const char camera_aPhotonamenod_800CFBA0[] = "photo name no = %d\n";
const char camera_aPhotonames_800CFBB4[] = "photo name = %s\n";
const char camera_aPhotonod_800CFBC8[] = "photo_no = %d\n";
const char camera_aHeaderx_800CFBD8[] = "header = %x\n";
const char camera_aSinreid_800CFBE8[] = "sinrei = %d\n";
const char camera_aRdgdbd_800CFBF8[] = "r = %d g = %d b = %d\n";
const char camera_aPrdpgdpbd_800CFC10[] = "pr = %d pg = %d pb = %d\n";
const char camera_aCompresx_800CFC2C[] = "comp_res = %x\n";
const int camera_jt_800CFC3C[] __attribute__((aligned(8))) = {
    0x800C44DC, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C44E4, 0x800C4524, 0x800C44EC, 0x800C44F4, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524, 0x800C4524,
    0x800C4524, 0x800C4524, 0x800C4524, 0x800C44FC, 0x800C4504,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C4394.s")
int camera_800C4790(MEMCARD *pMemcard)
{
    char *buffer, *buffer_copy;
    int   size;
    short hours, minutes, seconds;
    int   file;
    int   success;
    int   retries;
    int   flags1, flags2;
    int   i, idx;

    GM_PadResetDisable = TRUE;

    size = camera_data_info_800D072C->blocks_count * MEMCARD_BLOCK_SIZE;
    buffer = GV_AllocMemory(2, size);
    if (!buffer)
    {
        printf("NO MEMORY FOR FILE BODY\n");
    }

    GV_ZeroMemory(buffer, size);

    buffer[0] = 'S';
    buffer[1] = 'C';
    buffer[2] = 0x11;
    buffer[3] = camera_data_info_800D072C->blocks_count;

    idx = camera_data_info_800D072C->field_0[1];
    buffer_copy = buffer;

    if (idx == 0)
    {
        flags2 = GM_ClearFlag;
        idx = flags2;

        if (flags2 >= 4)
        {
            idx = 3;
            if (flags2 == 6)
            {
                idx = 0;
            }
        }

        flags2 |= (GM_Disk - 1) * 8;
    }
    else
    {
        flags2 = idx;
    }

    memcpy(buffer_copy + 96, camera_clutsAndIcons_800C3438[idx], 160);

    hours = (unsigned short)GM_PlayTimeHours;
    seconds = (unsigned short)GM_PlayTimeSeconds;
    minutes = seconds / 60;

    camera_data_info_800D072C->make_title(buffer_copy + 4, pMemcard, hours, minutes);
    strcpy(camera_memoryCardFileName_800C37F8, MGS_MemoryCardName);

    camera_memoryCardFileName_800C37F8[12] = camera_data_info_800D072C->field_0[0];
    camera_memoryCardFileName_800C37F8[13] = (hours / 10) + '0';
    camera_memoryCardFileName_800C37F8[14] = (hours % 10) + '0';
    camera_memoryCardFileName_800C37F8[15] = (minutes / 10) + '0';
    camera_memoryCardFileName_800C37F8[16] = (minutes % 10) + '0';
    camera_memoryCardFileName_800C37F8[17] = flags2 + '@';
    camera_memoryCardFileName_800C37F8[18] = camera_data_info_800D072C->field_2 + '@';

    for (i = 0; i < 16; i++)
    {
        camera_memoryCardFileName_800C37F8[19] = 'A' + i;
        flags1 = 0;
        for (file = 0; file < pMemcard->file_count; file++)
        {
            if (!strcmp(pMemcard->files[file].name, camera_memoryCardFileName_800C37F8))
            {
                flags1 = 1;
            }
        }

        if (!flags1)
        {
            break;
        }
    }

    success = 0;
    camera_data_info_800D072C->make_game_data(buffer_copy + 256);

    for (retries = 4; retries > 0; retries--)
    {
        memcard_write(pMemcard->port, camera_memoryCardFileName_800C37F8, 0, buffer, size);
        while ((i = memcard_status()) > 0)
        {
            mts_wait_vbl(2);
        }

        if (memcard_status() == 0)
        {
            success = 1;
            break;
        }
    }

    GV_FreeMemory(2, buffer);
    GM_PadResetDisable = FALSE;
    return success;
}
int camera_800C4BAC(MEMCARD *card, int index) {

    char         *buffer;
    int           result;
    int           retries;
    int           i;

    GM_PadResetDisable = 1;
    buffer = GV_AllocMemory(2, 0x4000);

    if (!buffer) {
        printf("NO MEMORY FOR FILE BODY\n");
    }

    result = 0;
    retries = 4;

    camera_photo_buf_800D0700 = buffer;
    camera_file_buf_800D0704 = buffer;

    for (; retries > 0; retries--) {
        memcard_read(card->port, card->files[index].name, 0, buffer, 0x4000);

        while (memcard_status() > 0) {
            mts_wait_vbl(2);
        }

        if (memcard_status() == 0) {
            camera_card_port_800D0708 = card->port;
            for (i = 0; i < 24; i++) {
                /* per-iteration scope for p710 is required for the match */
                char *p710 = camera_file_name_800D0710;
                p710[i] = card->files[index].name[i];
            }
            printf("card_no = %d file_name = %s\n", camera_card_port_800D0708, camera_file_name_800D0710);
            result = 1;
            break;
        }
    }

    GM_PadResetDisable = 0;
    return result;
}

const char *camera_saveCaptions_800C3810[] = {
    "\x00", // Different from the other empty strings used below for some reason
    // セーブが完了しました。 (Save completed.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x0c\x91\x07\x91\x08\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // セーブできませんでした。 (Could not save.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
    // エラーが発生しました。 (An error occurred.)
    "\x82\x08\x82\x49\xd0\x06\x81\x0c\x90\x7e\x90\xca\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // 空きブロックがたりません。 (Not enough empty blocks.)
    "\x90\x92\x81\x0d\x82\x36\x82\x4d\xc2\x23\x82\x0f\x81\x0c\x81\x1f\x81\x4a\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // メモリーカードが初期化されていません。 (Memory card is not initialized.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x91\x10\x91\x11\x90\x64\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // セーブしました。 (Saved.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // フォーマットに失敗しました。 (Failed to format.)
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x2b\x91\x09\x91\x0a\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // メモリーカードがさされていません。 (Memory card is not inserted.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x81\x15\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // セーブ中です。 (Saving.)
    "\x82\x1b\xd0\x06\x82\x36\x90\xcd\x81\x27\x81\x19\xd0\x03",
    // メモリーカードをチェックしています。 (Checking memory card.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x52\x82\x21\xc2\x07\xc2\x23\x82\x0f\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
    // フォーマットしています。 (Formatting.)
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
};

const char *camera_loadCaptions_800C3840[] = {
    "\x00", // Different from the other empty strings used below for some reason
    // ロードが完了しました。 (Load completed.)
    "\x82\x4d\xd0\x06\x82\x29\x81\x0c\x91\x07\x91\x08\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // ロードできませんでした。 (Could not load.)
    "\x82\x4d\xd0\x06\x82\x29\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
    // エラーが発生しました。 (An error occurred.)
    "\x82\x08\x82\x49\xd0\x06\x81\x0c\x90\x7e\x90\xca\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // セーブファイルがありません。 (There is no save file.)
    "\x82\x1b\xd0\x06\x82\x36\x82\x35\xc2\x01\x82\x04\x82\x4b\x81\x0c\x81\x02\x81\x4a\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // メモリーカードが初期化されていません。 (Memory card is not initialized.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x91\x10\x91\x11\x90\x64\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // ロードしました。 (Loaded.)
    "\x82\x4d\xd0\x06\x82\x29\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // フォーマットに失敗しました。 (Failed to format.)
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x2b\x91\x09\x91\x0a\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // メモリーカードがさされていません。 (Memory card is not inserted.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x81\x15\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // ロード中です。 (Loading.)
    "\x82\x4d\xd0\x06\x82\x29\x90\xcd\x81\x27\x81\x19\xd0\x03",
    // メモリーカードをチェックしています。 (Checking memory card.)
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x52\x82\x21\xc2\x07\xc2\x23\x82\x0f\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
    // フォーマットしています。 (Formatting.)
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
};

const char *camera_save_prompt_msg_jp_800C3870[] = {
    // 上書きしてよろしいですか？
    "\x91\x0b\x90\x27\x81\x0d\x81\x17\x81\x26\x81\x48\x81\x4d\x81\x17\x81\x04\x81\x27\x81\x19\x81\x0b\xc0\x3f",
    // フォーマットしますか？
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x3e\x81\x19\x81\x0b\xc0\x3f",
};

const char *camera_save_prompt_msg_en_800C3878[] = {"OVERWRITE OK?", "FORMAT OK?"};

int camera_dword_800C3880 = -1;
int camera_dword_800C3884 = 0;

int camera_800C4D20(int arg0) {

    camera_request_800D0738 = arg0;
    printf("REQUEST %X\n", arg0);

    mts_slp_tsk();
    printf("RESULT %X\n", camera_result_800D073C);

    return camera_result_800D073C;
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C4D70.s")
void camera_800C4D70(void);
void camera_800C5308(int arg0) {

    char *temp_v0;

    temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, 2048);
    camera_stack_800D0730 = temp_v0;

    if (temp_v0 == NULL) {

        printf("NO MEMORY FOR STACK\n");
    }

    camera_dword_800D0728 = arg0;
    mts_start_task(MTSID_MEMORY_CARD, camera_800C4D70, camera_stack_800D0730 + 2048, 2048);
}

const char *camera_dword_800C3888[] = {
    NULL,
    NULL,
    "COMPLETE",
    NULL,
    "ERROR"
};

RECT camera_rect_800C389C = {960, 260, 63, 76};

// The small triangle above the files list suggesting that there are more entries.
Menu_Triangle camera_upperTriangle_800C38A4 = {155, 79, 160, 74, 165, 79, 0x80808080};
// The small triangle below the files list suggesting that there are more entries.
Menu_Triangle camera_lowerTriangle_800C38B4 = {156, 184, 160, 188, 164, 184, 0x80808080};

void move_coord_800C5388(int *arr, int len)
{
    int i;

    for (i = 0; i < len; i++, arr += 2)
    {
        arr[0] += arr[1];
    }
}

// Copy of menu_radio_do_file_mode_helper2_helper_8004A4C4
void camera_800C53B8(MenuPrim *prim, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    TextConfig         textConfig;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_8, 2);
        pUnk->field_18 = 0x3d482e;
    }
    textConfig.xpos = pUnk->field_8 >> 16;
    textConfig.ypos = pUnk->field_10 >> 16; // pUnk->field_10 / 65536 wouldn't match
    textConfig.flags = 0x12;
    textConfig.color = pUnk->field_18 | 0x66000000;

    _menu_number_draw_string2(prim, &textConfig, (char *)pUnk->field_4); // TODO: Fix cast
}

// Copy of menu_radio_do_file_mode_helper4_helper_8004A54C
void camera_800C5440(MenuPrim *prim, RadioFileModeStruElem *pElem)
{
    LINE_F2           *pPrim;
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 4);
    }

    if (pUnk->field_4 != pUnk->field_14 || pUnk->field_C != pUnk->field_1C)
    {
        _NEW_PRIM(pPrim, prim);

        LSTORE(pUnk->field_24, &pPrim->r0);
        pPrim->x0 = pUnk->field_4 >> 16;
        pPrim->y0 = pUnk->field_C >> 16;
        pPrim->x1 = pUnk->field_14 >> 16;
        pPrim->y1 = pUnk->field_1C >> 16; // pUnk->field_1C / 65536 wouldn't match
        setLineF2(pPrim);
        addPrim(prim->ot, pPrim);
    }
}

// duplicate of sub_8004A648
void camera_800C553C(MenuPrim *prim, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    int                x, y, w, h;
    TILE              *pTile;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 4);
    }
    x = (pUnk->field_4 >> 16);
    y = (pUnk->field_C >> 16);
    w = pUnk->field_14 >> 16;
    h = pUnk->field_1C >> 16;
    x -= w / 2;
    y -= h / 2;

    _NEW_PRIM(pTile, prim);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(prim->ot, pTile);

    radio_draw_face_frame(prim, x, y, w, h);
    radio_draw_face_frame(prim, x, y, w, h);
}

void camera_800C714C(MenuPrim *prim, SELECT_INFO *info);

// duplicate of menu_radio_do_file_mode_helper3_helper_8004A790
void camera_800C5684(MenuPrim *prim, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16; // TODO: Fix type of field_14
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16; // pUnk->field_C / 65536 wouldn't match
    camera_800C714C(prim, (SELECT_INFO *)pUnk->field_14);
}

// duplicate of init_file_mode_helper2_8004A800
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
void camera_800C56F4()
{
    int i;

    camera_dword_800D075C =
        (RadioFileModeStru_800ABB7C *)GV_AllocMemory(GV_NORMAL_MEMORY, sizeof(RadioFileModeStru_800ABB7C));
    if (camera_dword_800D075C == NULL)
    {
        printf("NO MEMORY FOR OBJ\n");
    }

    for (i = 0; i < 12; i++)
    {
        camera_dword_800D075C->field_0_array[i].field_0 = 0;
    }
}

void camera_800C5750(void)
{
    GV_FreeMemory(GV_NORMAL_MEMORY, camera_dword_800D075C);
}

void camera_800C5778(int idx, int param_2, int param_3, int divisor, int idx2)
{
    RadioFileModeUnk2     *pUnk;
    RadioFileModeStruElem *pElem;

    pUnk = &camera_dword_800D075C->field_c0_array[idx];
    pElem = &camera_dword_800D075C->field_0_array[idx];

    pUnk->field_4 = camera_dword_800C3888[idx2];

    pElem->field_8_pFn = camera_800C53B8;
    pElem->field_C_unk1 = (RadioFileModeUnk1 *)pUnk;

    if (idx2 < 0)
    {
        pElem->field_0 = 0;
        return;
    }

    if (divisor <= 0)
    {
        pUnk->field_8 = param_2 * 65536;
        pUnk->field_10 = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_C = (param_2 * 65536 - pUnk->field_8) / divisor;
        pUnk->field_14 = (param_3 * 65536 - pUnk->field_10) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_18 = 0x748956;
    pElem->field_4 = divisor;
}

void camera_800C5898(int idx, int param_2, int param_3, int divisor, SELECT_INFO *field_14)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &camera_dword_800D075C->field_0_array[idx];
    pUnk = &camera_dword_800D075C->field_220_unk1;

    pElem->field_8_pFn = camera_800C5684;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_14 = (int)field_14;
    pElem->field_4 = divisor;
}

void camera_800C5440(MenuPrim *prim, RadioFileModeStruElem *pElem);

void camera_800C5970(int idx, int param_2, int param_3, int param_4, int param_5, int divisor) // duplicate of menu_radio_do_file_mode_helper4_8004AA68
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &camera_dword_800D075C->field_0_array[idx];

    // callers to this function use idx in range 5..8
    pUnk = &camera_dword_800D075C->field_130_array[idx - 5]; // TODO: really -5?

    pElem->field_8_pFn = camera_800C5440;
    pElem->field_C_unk1 = pUnk;
    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pUnk->field_14 = param_4 * 65536;
        pUnk->field_1C = param_5 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_4 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_5 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_24 = 0x3d482e;
    pElem->field_4 = divisor;
}

void camera_800C5AE8(int index)
{
    camera_dword_800D075C->field_0_array[index].field_0 = 0;
}
void camera_800C5B00(int param_1, int param_2, int param_3, int param_4, int divisor)
{
    RadioFileModeStruElem *pElem;
    RadioFileModeUnk1     *pUnk;

    pElem = &camera_dword_800D075C->field_0_array[11];
    pUnk = (RadioFileModeUnk1 *)&camera_dword_800D075C->field_220_unk1.field_18;

    pElem->field_8_pFn = camera_800C553C;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_1 * 65536;
        pUnk->field_C = param_2 * 65536;
        pUnk->field_14 = param_3 * 65536;
        pUnk->field_1C = param_4 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_1 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_2 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_3 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_4 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pElem->field_4 = divisor;
}

void camera_800C5C54(MenuPrim *prim) // duplicate of menu_radio_do_file_mode_helper6_8004AD40
{
    int                    i;
    RadioFileModeStruElem *pElem;

    pElem = camera_dword_800D075C->field_0_array;
    for (i = 0; i < 12; i++, pElem++)
    {
        if (pElem->field_0 != 0)
        {
            if (pElem->field_4 < 0)
            {
                pElem->field_4++;
            }
            else
            {
                pElem->field_8_pFn(prim, pElem);
                if (pElem->field_0 == 1 && --pElem->field_4 == 0)
                {
                    pElem->field_0 = 2;
                }
            }
        }
    }
}

void camera_800C5D2C(SPRT *sprt) // duplicate of menu/datasave.c: set_sprt_default
{
    LSTORE(0x80808080, &sprt->r0);
    setSprt(sprt);
    setClut(sprt, 960, 510);
}

// duplicate of init_radio_message_board_80040F74
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
// and with one font_set_color missing
void camera_800C5D54(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&camera_rect_800C389C, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &camera_rect_800C389C, 960, 510);
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

        camera_dword_800D0760 = NULL;
    }
}

// duplicate of drawCaption_8004AE3C
void drawCaption_800C5EB4(MenuWork *work, const char *caption)
{
    int  height;
    KCB *kcb;

    kcb = work->field_214_font;

    height = kcb->height;
    kcb->height = 14;
    font_clear(kcb);
    kcb->height = height;

    font_draw_string(kcb, 0, 0, caption, 0);
    font_update(kcb);
}

// duplicate of sub_8004AEA8
void camera_800C5F20(SELECT_INFO *info)
{
    int   top;
    int   i, y;
    int   count;
    int   x, val2;
    KCB  *kcb;
    char  mes[32];
    char *name;

    kcb = info->kcb;
    x = 0;
    font_clear(kcb);

    val2 = 14;
    y = val2;
    count = info->max_num - info->top;
    if (count > 6)
    {
        count = 6;
    }

    top = info->top;
    for (i = 0; i < count; i++, y += 14)
    {
        if (i == 4)
        {
            x = 128;
            y = val2;
        }

        name = info->menu[i + top].mes;
        if (name[0] != '\0')
        {
            camera_data_info_800D072C->make_menu(mes, name);
            font_draw_string(kcb, x, y, mes, 2);
        }
    }

    font_draw_string(kcb, 0, 0, info->message, 0);
    font_update(kcb);
}

// duplicate of show_message_8004AFE4
void camera_800C6054(MenuWork *work, u_long *ot, SELECT_INFO *info)
{
    unsigned int xoff;
    SPRT        *pPrim;
    KCB         *kcb;

    kcb = work->field_214_font;

    NEW_PRIM(pPrim, work);

    camera_800C5D2C(pPrim);

    xoff = kcb->max_width;

    pPrim->y0 = 200;
    pPrim->v0 = 4;
    pPrim->w = 252;
    pPrim->h = 14;
    pPrim->u0 = 0;
    pPrim->x0 = 160 - xoff / 2;

    addPrim(ot, pPrim);
}

/* rdata of camera_800C6110 */
const char camera_aDiscd_800CFF94[] = "DISC %d";
const char camera_aTime_800CFF9C[] = "TIME";
const char camera_aNewfileneeddblocks_800CFFA4[] = "NEW FILE [ NEED %d BLOCK%s ]";
const char camera_aS_800CFFC4[] = "S";
const char camera_dword_800CFFC8[] = "";
const char camera_aFreedblocks_800CFFCC[] = "FREE: %d BLOCK%s";

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C6110.s")

void camera_800C68BC(char *arg0, char *arg1)
{
    strcpy(arg0, arg1 + 0xC);
}

void camera_800C68DC(void *ptr)
{
    printf("close info\n");
    if (ptr)
    {
        GV_FreeMemory(GV_NORMAL_MEMORY, ptr);
    }
}

void camera_800C6918(void **arg0, int arg1)
{
    void *temp_v0;

    if (*arg0 == NULL)
    {
        temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, (arg1 * 0x24) + 0x24);
        *arg0 = temp_v0;
        if (temp_v0 == NULL)
        {
            printf("NO MEMORY FOR INFO\n");
        }
        printf("alloc info %X\n", (u_int)*arg0);
    }
}

// See also updateCurrentEntry_8004B9C4() in datasave.c
void updateCurrentEntry_800C6984(SELECT_INFO *info, int dir)
{
    short top;
    short newIndex;
    int   previousIndex;

    previousIndex = info->current;
    newIndex = info->current + dir;
    info->current = newIndex;
    if (newIndex < 0)
    {
        info->current = 0;
    }
    else if (newIndex >= info->max_num)
    {
        info->current = info->max_num - 1;
    }
    else
    {
        top = info->top;
        if (newIndex < top)
        {
            info->top = newIndex;
        }
        else if (newIndex >= (top + 6))
        {
            info->top = newIndex - 5;
        }
    }
    if (info->current != previousIndex)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
    }
    camera_800C5F20(info);
}

// duplicate of menu_radio_do_file_mode_helper12_8004BA80
int camera_800C6A40(MenuWork *work, MEMCARD *pMemcard, const char *param_3,
                    SELECT_INFO *info)
{
    MENU_CURPOS *pIter;
    MEMCARD_FILE       *pMcFile;
    int                  i;

    pIter = info->menu;

    strcpy(camera_memoryCardFileName_800C37F8, MGS_MemoryCardName);
    camera_memoryCardFileName_800C37F8[12] = camera_data_info_800D072C->field_0[0];

    for (i = 0; i < pMemcard->file_count; i++)
    {
        pMcFile = &pMemcard->files[i];
        printf("FILE %s\n", pMcFile->name);

        if (strncmp(pMcFile->name, camera_memoryCardFileName_800C37F8, 13) == 0)
        {
            camera_800C68BC(pIter->mes, pMcFile->name);
            pIter->num = i;
            pIter++;
        }
    }

    if (camera_dword_800D0728 == 0 && pMemcard->free_blocks >= camera_data_info_800D072C->blocks_count)
    {
        memcpy(pIter->mes, camera_dword_800CFFC8, 1);
        pIter->num = 16;
        pIter++;
    }

    info->kcb = work->field_214_font;
    info->max_num = pIter - info->menu;

    if (camera_data_info_800D072C->field_0[0] != 71)
    {
        if (info->max_num && pIter[-1].num == 16)
        {
            info->current = info->max_num - 1;
        }
        else
        {
            info->current = 0;
        }
    }
    else if (camera_dword_800C342C == -1 || camera_dword_800C342C >= info->max_num)
    {
        if (camera_dword_800D0728 == 0 && info->max_num && pIter[-1].num == 16)
        {
            info->current = info->max_num - 1;
        }
        else
        {
            info->current = 0;
        }
    }
    else
    {
        info->current = camera_dword_800C342C;
    }

    info->top = 0;
    info->message = param_3;
    info->field_E = -1;
    info->xofs = 40;
    info->yofs = 40;
    info->open_count = 8;
    info->move_dir = 0;
    info->field_18 = -1;
    info->height = 240;
    info->enable = 1;
    updateCurrentEntry_800C6984(info, 0);
    return info->max_num != 0;
}

int camera_800C6CCC(GV_PAD *pPad, int *pOut, SELECT_INFO *info)
{
    int newDir;
    int field_20;
    int press;
    int status;

    if (camera_dword_800C3434 != 0)
    {
        camera_dword_800C3434 = 0;
        pPad->press |= PAD_CIRCLE;
    }
    else
    {
        status = pPad->status;
        if (info->max_num != 0)
        {
            if (status & (PAD_DOWN | PAD_UP))
            {
                newDir = 1;
                if (status & PAD_UP)
                {
                    newDir = -1;
                }
                if (info->move_dir == newDir)
                {
                    if (--info->move_dir_delay < 0)
                    {
                        updateCurrentEntry_800C6984(info, newDir);
                        info->move_dir_delay = 2;
                    }
                }
                else
                {
                    updateCurrentEntry_800C6984(info, newDir);
                    info->move_dir_delay = 10;
                    info->move_dir = newDir;
                }
            }
            else
            {
                info->move_dir = 0;
            }
        }
    }

    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
        if (info->max_num == 0)
        {
            *pOut = -1;
            return 1;
        }
        field_20 = info->menu[info->current].num;
        *pOut = field_20;
        if (camera_data_info_800D072C->field_0[0] == 71)
        {
            if (field_20 < 16)
            {
                camera_dword_800C342C = info->current;
            }
            else
            {
                camera_dword_800C342C = -1;
            }
        }
        return 1;
    }
    if (press & PAD_CROSS)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        *pOut = info->field_E;
        return 1;
    }
    return 0;
}

const char *gMemoryCardNames_800C38C4[] = {
    "MEMORY CARD 1",    // 0
    "MEMORY CARD 2"     // 1
};

// duplicate of menu_radio_do_file_mode_helper14_8004BE98
void camera_800C6E78(MenuWork *work, char *param_2, SELECT_INFO *info)
{
    MENU_CURPOS *infoChild;
    int                  idx, idx_copy;
    int                  memoryCardNo;
    int                  bit;
    int                  minusOne;

    infoChild = info->menu;
    idx = -1;
    for (memoryCardNo = 0; memoryCardNo < 2; memoryCardNo++)
    {
        int *new_var;
        new_var = &camera_dword_800C3884;
        bit = 1;
        bit <<= memoryCardNo;

        if (*new_var & bit)
        {
            strcpy(infoChild->mes, gMemoryCardNames_800C38C4[memoryCardNo]);
            infoChild->num = memoryCardNo;
            if (memoryCardNo == camera_dword_800C3430)
            {
                idx = infoChild - info->menu;
            }
            infoChild++;
        }
    }

    idx_copy = idx;
    if (infoChild == info->menu)
    {
        memcpy(&info->menu[0].mes, "NO CARD", 8);
        infoChild->num = 2;
        infoChild = &info->menu[1];
    }

    info->kcb = work->field_214_font;
    info->max_num = infoChild - info->menu;

    if (idx_copy < 0)
    {
        idx_copy = 0;
    }

    minusOne = -1;
    do {} while (0);

    info->xofs = 160;
    info->yofs = 100;
    info->current = idx_copy;
    info->top = 0;
    info->message = param_2;
    info->field_E = minusOne;
    info->width = 128;
    info->field_18 = minusOne;
    info->open_count = 4;
    info->height = 128;
    info->enable = 1;
    info->move_dir = 0;
}

// duplicate of menu_radio_do_file_mode_helper15_8004C04C, but with one missing line
void camera_800C703C(MenuWork *work, const char **srcs, int cnt, int field_4, const char *field_20,
                     SELECT_INFO *info)
{
    KCB                 *kcb;
    const char          *src;
    int                  i;
    MENU_CURPOS *dest;

    dest = info->menu;
    for (i = 0; i < cnt; i++, dest++)
    {
        src = srcs[i];
        strcpy(dest->mes, src);
        dest->num = i;
    }

    kcb = work->field_214_font;

    info->max_num = dest - info->menu;
    info->current = field_4;
    info->top = 0;
    info->message = field_20;
    info->field_E = 1;
    info->xofs = 160;
    info->move_dir = 0;
    info->enable = 1;
    info->yofs = 128;
    info->width = 64;
    info->height = 32;
    // info->field_16 = 4;
    info->kcb = kcb;
}

// duplicate of menu_radio_do_file_mode_helper16_8004C164
void camera_800C714C(MenuPrim *prim, SELECT_INFO *info)
{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (info->enable != 0)
    {
        textConfig.color = 0x66748956;
    }
    else
    {
        textConfig.color = 0x663d482e;
    }
    textConfig.xpos = info->xofs;
    textConfig.ypos = info->yofs;
    _menu_number_draw_string2(prim, &textConfig, info->message);
    if (info->max_num == 1)
    {
        xpos = info->xofs;
    }
    else
    {
        xpos = info->xofs - info->width / 2;
    }
    for (i = 0; i < info->max_num; i++, xpos += info->width)
    {
        textConfig.xpos = xpos;
        ypos = info->yofs;
        textConfig.ypos = ypos + 12;

        if (i == info->current)
        {
            textConfig.color = 0x66748956;
            if (info->enable != 0)
            {
                ypos += 16;
                camera_800C5B00(textConfig.xpos, ypos, info->height, 12, 2);
            }
        }
        else
        {
            textConfig.color = 0x663d482e;
        }
        _menu_number_draw_string2(prim, &textConfig, info->menu[i].mes);
    }
}

int camera_800C72CC(GV_PAD *pPad, int *pOut, SELECT_INFO *info)
{
    int status;
    int press;

    status = pPad->status;
    if (info->max_num >= 2)
    {
        if (status & PAD_LEFT)
        {
            if (info->current != 0)
            {
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                info->current = 0;
            }
        }
        else if ((status & PAD_RIGHT) && info->current == 0)
        {
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            info->current = 1;
        }
    }

    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        *pOut = info->menu[info->current].num;
        GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
        return 1;
    }

    if (press & PAD_CROSS)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        *pOut = info->field_E;
        return 1;
    }

    return 0;
}
/* rdata of camera_800C73E4 */
const char camera_aSaving_800D0044[] = "SAVING...";
const char camera_aNospace_800D0050[] = "NO SPACE";
const char camera_aPhotodata_800D005C[] = "PHOTO DATA";
const char camera_aLoading_800D0068[] = "LOADING...";
const char camera_aNofile_800D0074[] = "NO FILE";
const char camera_aSelectmemorycard_800D007C[] = "SELECT MEMORY CARD";
const char *camera_yes_no_800C38CC[] = {"YES", "NO"};
const char camera_aPresstoexit_800D0098[] = "PRESS * TO EXIT";
const char camera_aResd_800D00A8[] = "Res %d\n";
const char camera_aPresstoselectmemorycard_800D00B0[] = "PRESS * TO SELECT MEMORY CARD";
const char camera_aEndsavemode_800D00D0[] = "END SAVE MODE\n";
const char camera_aEndstated_800D00E0[] = "END STATE %d\n";
const int camera_jt_800D00F4[] __attribute__((aligned(8))) = {
    0x800C74C4, 0x800C7580, 0x800C7B4C, 0x800C7BE8, 0x800C7D7C, 0x800C7CB8,
    0x800C7E64,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C73E4.s")

void camera_800C7FF4(int code, char **pAreaNameForMenu, char **pAreaNameForSaveData)
{
    int i;

    if (code == 0)
    {
        *pAreaNameForMenu = "NO PLACE";
        *pAreaNameForSaveData = "\x81\x40";
    }

    GCL_SetArgTop(camera_gcl_args_800D0770);

    for (i = 0; i < code; i++)
    {
        if (GCL_NextStr() == 0)
        {
            return;
        }
        *pAreaNameForMenu = GCL_GetString((char *)GCL_NextStr());
        if (camera_dword_800D0774 > 0 && camera_dword_800D0728 == 0)
        {
            *pAreaNameForSaveData = GCL_GetString((char *)GCL_NextStr());
        }
    }
}

char camera_dockAreaName_800C38D4[] = { "\x82\x63\x82\x8F\x82\x83\x82\x8B" }; // Ｄｏｃｋ

void camera_800C80E4(char *out, MEMCARD *unused, int hours, int minutes)
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

    if (camera_dword_800D0774 == 0)
    {
        camera_800C7FF4(1, &discard, &areaName);
        areaName = camera_dockAreaName_800C38D4;
    }
    else
    {
        camera_800C7FF4(camera_dword_800D0774, &discard, &areaName);
    }

    /* ＭＧＳ∫ */
    sprintf(out, "%s%s%s%s%s", "\x82\x6C\x82\x66\x82\x72\x81\xE7", "\x81\x40", playTime, "\x81\x40", areaName);
}

void camera_800C8208(char *out, char *in)
{
    sprintf(out, "PHOTO %02d\n", in[6] - 0x40);
}

void jpegcam_initSaveBuffer_800C8234(char *arg0)
{
    int chunkSize;
    int totalSavedSize = 0x100;
    char *buff = arg0;

    GM_SaveCount++;

    while (1)
    {
        chunkSize = GCL_MakeSaveFile(buff);
        totalSavedSize += chunkSize;
        if (totalSavedSize + chunkSize > MEMCARD_BLOCK_SIZE)
        {
            break;
        }
        buff += chunkSize;
        printf("*");
    }
}

void camera_800C5308(int);

DATA_INFO camera_dataInfo_800C38E0 = {
    {0x43, 0},                          // field_0
    0,                                  // field_2
    1,                                  // blocks_count
    "SAVE DATA",                        // field_4_name
    camera_800C80E4,                    // make_title
    camera_800C8208,                    // make_menu
    jpegcam_initSaveBuffer_800C8234     // make_game_data
};

void camera_800C82B0(DATA_INFO *arg0, int arg1)
{
    camera_dword_800D0764 = 0;
    camera_data_info_800D072C = arg0;
    camera_800C56F4();
    camera_800C5308(arg1);
}

void camera_800C82EC(void)
{
    camera_800C82B0(&camera_dataInfo_800C38E0, 1);
}

void camera_800C8314(MenuPrim *prim, SELECT_INFO *info)
{
    DR_TPAGE *pTpage;

    _NEW_PRIM(pTpage, prim);

    setlen(pTpage, 1);
    pTpage->code[0] = 0xE100061F | ((*(int *)((char *)info + 8) >> 3) & 0x60);
    addPrim(prim->ot, pTpage);
}
typedef struct CaptionInfo
{
    int     x;
    u_short y;
    short   field_6;
    int     field_8;
    int     color;
} CaptionInfo;

/* Punctuation glyphs of the caption font: character, unknown */
char camera_dword_800C38F4[][2] = {
    {'.', 2}, {'@', 2}, {':', 2}, {'_', 4}, {'!', 2}, {'?', 6}, {'+', 6},
    {'-', 6}, {'/', 6}, {'*', 6}, {'{', 3}, {'}', 3}, {0, 0}
};

void camera_800C838C(MenuPrim *prim, CaptionInfo *info, char *str)
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
            for (tbl = camera_dword_800C38F4[0];; tbl += 2, u += 8)
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
        *sprt = camera_sprt_800D0780;
        *(int *)&sprt->r0 = color;
        sprt->x0 = x;
        sprt->y0 = info->y;
        sprt->u0 = u;
        sprt->v0 = v;
        x += w;
        addPrim(ot, sprt);
    }
}

void camera_800C8554(int *arg0, int arg1, int arg2, int arg3)
{
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
}

void camera_800C8564(MenuPrim *prim, SELECT_INFO *info, char *arg2)
{
    char sp10[64];

    sprintf(sp10, arg2);
    camera_800C838C(prim, (CaptionInfo *)info, sp10);
    camera_800C8314(prim, info);
}

void camera_800C85B8(int *arg0, int r, int g, int b)
{
    arg0[3] = (r | (g << 8) | (b << 16) | (GPU_CODE_SPRT << 24));
}

void camera_800C85D8(void)
{
    short sp0[4];
    SPRT *sprt;

    // Let's waste cycles by puting unused stuff on stack:
    sp0[0] = 976;
    sp0[1] = 511;
    sp0[2] = 16;
    sp0[3] = 1;

    sprt = &camera_sprt_800D0780;
    LSTORE(0x80808080, &sprt->r0);
    setUV0(sprt, 0, 242);
    setWH(sprt, 8, 6);
    setSprt(sprt);
    setClut(sprt, 976, 511);
}

void camera_800C864C(Work *work)
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

void camera_800C869C(Work *work)
{
    int i;

    for (i = 8; i >= 0; i--)
    {
        work->field_664[i] = NULL;
    }
}
void camera_800C86BC(Work *work, int x, int y, int w, int h, int color, int unused)
{
    POLY_FT4 *p;
    int i;
    int xl0, xl1, xr0, xr1, yt0, yt1, yb0, yb1;
    int xw, yh;

    p = work->polys;
    for (i = 0; i < 9; i++)
    {
        work->field_664[i] = (GV_ACT *)0x400;
        setRGB0(&p[i], color, color, color);
    }

    xw = x + w;
    yh = y + h;
    xl0 = x - 6;   xl1 = x + 2;
    yt0 = y - 6;   yt1 = y + 2;
    xr0 = xw - 2;  xr1 = xw + 6;
    yb0 = yh - 2;  yb1 = yh + 6;

    /* corners */
    setXY4(&p[0], xl0, yt0, xl1, yt0, xl0, yt1, xl1, yt1);
    setXY4(&p[1], xr0, yt0, xr1, yt0, xr0, yt1, xr1, yt1);
    setXY4(&p[2], xl0, yb0, xl1, yb0, xl0, yb1, xl1, yb1);
    setXY4(&p[3], xr0, yb0, xr1, yb0, xr0, yb1, xr1, yb1);
    /* edges */
    setXY4(&p[4], xl1, yt0, xr0, yt0, xl1, yt1, xr0, yt1);
    setXY4(&p[5], xl1, yb0, xr0, yb0, xl1, yb1, xr0, yb1);
    setXY4(&p[6], xl0, yt1, xl1, yt1, xl0, yb0, xl1, yb0);
    setXY4(&p[7], xr0, yt1, xr1, yt1, xr0, yb0, xr1, yb0);
    /* center */
    setXY4(&p[8], xl1, yt1, xr0, yt1, xl1, yb0, xr0, yb0);
}
void camera_800C884C(Work *work, int x, int y, int w, int h, int color, int unused)
{
    POLY_FT4 *p;
    int i;
    int xl0, xl1, xr0, xr1, yt0, yt1, yb0, yb1;
    int xw, yh;

    p = work->polys;
    for (i = 0; i < 9; i++)
    {
        work->field_664[i] = (GV_ACT *)0x200;
        setRGB0(&p[i], color, color, color);
    }

    xw = x + w;
    yh = y + h;
    xl0 = x - 6;   xl1 = x + 2;
    yt0 = y - 6;   yt1 = y + 2;
    xr0 = xw - 2;  xr1 = xw + 6;
    yb0 = yh - 2;  yb1 = yh + 6;

    /* corners */
    setXY4(&p[0], xl0, yt0, xl1, yt0, xl0, yt1, xl1, yt1);
    setXY4(&p[1], xr0, yt0, xr1, yt0, xr0, yt1, xr1, yt1);
    setXY4(&p[2], xl0, yb0, xl1, yb0, xl0, yb1, xl1, yb1);
    setXY4(&p[3], xr0, yb0, xr1, yb0, xr0, yb1, xr1, yb1);
    /* edges */
    setXY4(&p[4], xl1, yt0, xr0, yt0, xl1, yt1, xr0, yt1);
    setXY4(&p[5], xl1, yb0, xr0, yb0, xl1, yb1, xr0, yb1);
    setXY4(&p[6], xl0, yt1, xl1, yt1, xl0, yb0, xl1, yb0);
    setXY4(&p[7], xr0, yt1, xr1, yt1, xr0, yb0, xr1, yb0);
    /* center */
    setXY4(&p[8], xl1, yt1, xr0, yt1, xl1, yb0, xr0, yb0);
}

void camera_800C89DC(Work *work)
{
    POLY_FT4 *p = work->polys_lr;
    int counter = work->field_4938;
    int rgb;

    if (counter < 31)
    {
        return;
    }

    if (counter < 47)
    {
        work->field_654[3] = 0x100;
        rgb = (counter - 30) * 255 / 16;
        p[3].r0 = rgb;
        p[3].g0 = rgb;
        p[3].b0 = rgb;
        return;
    }
    if (counter < 75)
    {
        work->field_654[2] = 0;
        work->field_4934 = 0;
        work->field_688[2] = (GV_ACT *)0x200;
        work->field_688[3] = (GV_ACT *)0x200;
        work->field_688[4] = (GV_ACT *)0x200;
        work->field_688[25] = NULL;
        work->field_688[22] = NULL;
        return;
    }
    if (counter < 91)
    {
        rgb = 0xFF - (counter - 74) * 255 / 16;
        p[3].r0 = rgb;
        p[3].g0 = rgb;
        p[3].b0 = rgb;
        return;
    }

    work->f28 = 3;
    work->f2C = 0;
    work->field_4938 = 0;
    camera_800C86BC(work, -0x90, 0x5A, 0x70, 0xC, 0xFF, 0);
}
/* rdata of camera_800C8AD4 */
const int camera_jt_800D0154[] __attribute__((aligned(8))) = {
    0x800C8C24, 0x800C8C4C, 0x800C8C80, 0x800C8C9C, 0x800C8BCC, 0x800C8C04,
    0x800C8D90, 0x800C8DF4, 0x800C8E7C, 0x800C8F00, 0x800C8F84, 0x800C9008,
    0x800C9088, 0x800C9108, 0x800C918C, 0x800C920C, 0x800C9290, 0x800C9310,
    0x800C9390, 0x800C9410, 0x800C947C, 0x800C94F8, 0x800C957C, 0x800C95F4,
    0x800C9674, 0x800C96F4, 0x800C9774, 0x800C97F4, 0x800C9878, 0x800C98F8,
    0x800C9978, 0x800C99F8, 0x800C9A78, 0x800C9AFC, 0x800C9B6C, 0x800C9BF0,
    0x800C9C74, 0x800C9CF4, 0x800C9D70, 0x800C9DF0, 0x800C9E70, 0x800C9EF4,
    0x800C9F74, 0x800CA074, 0x800C9FF4, 0x800CA174, 0x800CA0F4, 0x800CA1F4,
    0x800CA2F4, 0x800CA274, 0x800CA378, 0x800CA3F8, 0x800CA59C, 0x800CA59C,
    0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C,
    0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C,
    0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C,
    0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C, 0x800CA59C,
    0x800CA608, 0x800CA608, 0x800CA608, 0x800CA608, 0x800CA608, 0x800CA608,
    0x800CA608, 0x800CA608, 0x800CA608, 0x800CA608, 0x800CA674, 0x800CA6D4,
    0x800CA734, 0x800CA794, 0x800CA7F4, 0x800CA854, 0x800CA564, 0x800CA584,
    0x800CA4D4, 0x800CA528,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C8AD4.s")

/* rdata of camera_800CA918 */
const char camera_a_800D02DC[] = "-";
const int camera_jt_800D02E4[] __attribute__((aligned(8))) = {
    0x800CA960, 0x800CAC34, 0x800CACB8, 0x800CAA94, 0x800CAE1C,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CA918.s")

/* rdata of camera_800CB024 */
const int camera_jt_800D02FC[] __attribute__((aligned(8))) = {
    0x800CB070, 0x800CB1E4, 0x800CB384, 0x800CB528, 0x800CB564, 0x800CB5FC,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CB024.s")

/* Colour adjustment screen: draws the +/- values and positions the slider bars */
void camera_800CB8AC(Work *work)
{
    POLY_FT4 *p;
    POLY_FT4 *p2;
    int       value;
    int       x0;
    short     x1;

    p = work->polys_lr;
    p2 = work->polys2;

    work->field_4968 = (work->field_4980 + 100) * 255 / 200;
    work->field_496C = (work->field_4984 + 100) * 255 / 200;
    work->field_4970 = (work->field_4988 + 100) * 255 / 200;

    MENU_Locate(41, 166, 0);
    MENU_Color(86, 137, 116);
    if (work->field_4980 != 0)
    {
        if (work->field_4980 > 0)
        {
            MENU_Printf("+");
        }
        else
        {
            MENU_Printf(camera_a_800D02DC);
        }
    }

    MENU_Locate(41, 178, 0);
    MENU_Color(86, 137, 116);
    if (work->field_4984 != 0)
    {
        if (work->field_4984 > 0)
        {
            MENU_Printf("+");
        }
        else
        {
            MENU_Printf(camera_a_800D02DC);
        }
    }

    MENU_Locate(41, 190, 0);
    MENU_Color(86, 137, 116);
    if (work->field_4988 != 0)
    {
        if (work->field_4988 > 0)
        {
            MENU_Printf("+");
        }
        else
        {
            MENU_Printf(camera_a_800D02DC);
        }
    }

    MENU_Locate(46, 166, 0);
    MENU_Color(86, 137, 116);
    value = work->field_4980;
    if (value >= 0)
    {
        MENU_Printf("%3d", value);
    }
    else
    {
        MENU_Printf("%3d", -value);
    }

    MENU_Locate(46, 178, 0);
    MENU_Color(86, 137, 116);
    value = work->field_4984;
    if (value >= 0)
    {
        MENU_Printf("%3d", value);
    }
    else
    {
        MENU_Printf("%3d", -value);
    }

    MENU_Locate(46, 190, 0);
    MENU_Color(86, 137, 116);
    value = work->field_4988;
    if (value >= 0)
    {
        MENU_Printf("%3d", value);
    }
    else
    {
        MENU_Printf("%3d", -value);
    }

    p[0].r0 = work->field_4968;
    p[0].g0 = work->field_496C;
    p[0].b0 = work->field_4970;
    p[1].r0 = work->field_4968;
    p[1].g0 = work->field_496C;
    p[1].b0 = work->field_4970;
    p[2].r0 = work->field_4968;
    p[2].g0 = work->field_496C;
    p[2].b0 = work->field_4970;

    x0 = (work->field_4980 + 100) * 88 / 200 - 72;
    x1 = (work->field_4980 + 100) * 88 / 200 - 68;
    setXY4(&p2[13], x0, 52, x1, 52, x0, 62, x1, 62);

    x0 = (work->field_4984 + 100) * 88 / 200 - 72;
    x1 = (work->field_4984 + 100) * 88 / 200 - 68;
    setXY4(&p2[14], x0, 64, x1, 64, x0, 74, x1, 74);

    x0 = (work->field_4988 + 100) * 88 / 200 - 72;
    x1 = (work->field_4988 + 100) * 88 / 200 - 68;
    setXY4(&p2[15], x0, 76, x1, 76, x0, 86, x1, 86);
}

void camera_800CBCC8(Work *work)
{
    GV_PAD   *pad   = work->pad;
    int       state = work->field_49BC;
    u_short   press = pad->press;

    switch (state)
    {
    case 0:
        if (press & PAD_RIGHT)
        {
            work->field_49BC = 1;
            camera_800C884C(work, 0x30, 0x5A, 0x26, 0xC, 0xFF, 0);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            break;
        }
        if (press & PAD_CIRCLE)
        {
            work->field_49B8 = 2;
            work->field_4938 = 0;
            camera_800C869C(work);
            GM_SeSet2(0, 0x3F, 0xB1);
            break;
        }
        if (press & PAD_CROSS)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            camera_800C869C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;
    case 1:
        if (press & PAD_LEFT)
        {
            work->field_49BC = 0;
            camera_800C884C(work, 3, 0x5A, 0x1A, 0xC, 0xFF, 0);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            break;
        }
        if (press & PAD_CIRCLE)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            camera_800C869C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
            break;
        }
        if (press & PAD_CROSS)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            camera_800C869C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CBDE4.s")
/* rdata of camera_800CC3C8 */
const int camera_jt_800D031C[] __attribute__((aligned(8))) = {
    0x800CC40C, 0x800CC830, 0x800CC848, 0x800CC578, 0x800CC9D8,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CC3C8.s")

/* rdata of camera_800CCBB0 */
const int camera_jt_800D0334[] __attribute__((aligned(8))) = {
    0x800CCC2C, 0x800CCC78, 0x800CCBDC, 0x800CCC9C, 0x800CCCEC, 0x800CCDC0,
    0x800CCDF8,
};
const int camera_jt_800D0354[] __attribute__((aligned(8))) = {
    0x800CCED4, 0x800CCEAC, 0x800CD090, 0x800CCF00, 0x800CCF28, 0x800CCF50,
    0x800CCFB0, 0x800CCFD8, 0x800CD090, 0x800CD000, 0x800CD028, 0x800CD050,
};

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CCBB0.s")

const char *camera_captions_800C3910[] = {
    // 上書きしてよろしいですか？
    "\x91\x0b\x90\x27\x81\x0d\x81\x17\x81\x26\x81\x48\x81\x4d\x81\x17\x81\x04\x81\x27\x81\x19\x81\x0b\xc0\x3f",
    // セーブ中です。 (Saving.)
    "\x82\x1b\xd0\x06\x82\x36\x90\xcd\x81\x27\x81\x19\xd0\x03",
    // セーブ中にエラーが発生しました。 (An error occurred while saving.)
    "\x82\x1b\xd0\x06\x82\x36\x90\xcd\x81\x2b\x82\x08\x82\x49\xd0\x06\x81\x0c\x90\x7e\x90\xca\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // セーブが完了しました。 (Save completed.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x0c\x91\x07\x91\x08\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // カードが見つかりません。 (Card not found.)
    "\x82\x0b\xd0\x06\x82\x29\x81\x0c\x90\x34\x81\x24\x81\x0b\x81\x4a\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // セーブできませんでした。 (Could not save.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
    // セーブできませんでした。 (Could not save.)
    "\x82\x1b\xd0\x06\x82\x36\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
};
void camera_800CD0A0(MenuPrim *prim, int x, int y, int w, int h)
{
    TILE *pTile;

    _NEW_PRIM(pTile, prim);
    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(prim->ot, pTile);

    radio_draw_face_frame(prim, x, y, w, h);
    radio_draw_face_frame(prim, x, y, w, h);
}
static inline void camera_AddTpage(Work *work)
{
    DR_TPAGE *pTpage;

    pTpage = (DR_TPAGE *)work->field_700.prim->next;
    work->field_700.prim->next += sizeof(DR_TPAGE);
    pTpage->code[0] = 0xE100023F;
    setlen(pTpage, 1);
    addPrim(work->field_924_mOrderingTable, pTpage);
}

void camera_800CD198(Work *work)
{
    u_short press;
    int     dt;

    press = work->pad->press;

    switch (work->field_498C)
    {
    case 0:
        if (work->field_4938 < 5)
        {
            MENU_Locate(100, 90, 16);
            MENU_Color(86, 137, 116);
            MENU_Printf("OVERWRITE OK?");
            camera_800CD0A0((MenuPrim *)&work->field_920, 92, 85, 130, 15);
            return;
        }

        if (work->field_4938 < 10)
        {
            MENU_Locate(100, 90 - (work->field_4938 - 4) * 8, 16);
            MENU_Color(86, 137, 116);
            MENU_Printf("OVERWRITE OK?");
            camera_800CD0A0((MenuPrim *)&work->field_920, 92, 85, 130, 15);
            return;
        }

        if (work->field_4938 == 10)
        {
            MENU_Locate(100, 50, 16);
            MENU_Color(86, 137, 116);
            MENU_Printf("OVERWRITE OK?");
            MENU_Locate(100, 105, 16);
            MENU_Color(46, 72, 61);
            MENU_Printf("YES");
            MENU_Locate(200, 105, 16);
            MENU_Color(192, 192, 192);
            MENU_Printf("NO");
            camera_800CD0A0((MenuPrim *)&work->field_920, 92, 85, 130, 15);
            return;
        }

        if (work->field_4938 < 14)
        {
            MENU_Locate(100, 50, 16);
            MENU_Color(86, 137, 116);
            MENU_Printf("OVERWRITE OK?");
            MENU_Locate(100, 105, 16);
            MENU_Color(46, 72, 61);
            MENU_Printf("YES");
            MENU_Locate(200, 105, 16);
            MENU_Color(192, 192, 192);
            MENU_Printf("NO");
            dt = work->field_4938 - 10;
            camera_800CD0A0((MenuPrim *)&work->field_920, (dt << 5) + 92, dt * 5 + 85, 130 - dt * 30, 15);
            return;
        }

        work->field_498C = 2;
        MENU_Locate(100, 50, 16);
        MENU_Color(86, 137, 116);
        MENU_Printf("OVERWRITE OK?");
        MENU_Locate(100, 105, 16);
        MENU_Color(46, 72, 61);
        MENU_Printf("YES");
        MENU_Locate(200, 105, 16);
        MENU_Color(192, 192, 192);
        MENU_Printf("NO");
        camera_800CD0A0((MenuPrim *)&work->field_920, 188, 100, 40, 15);
        drawCaption_800C5EB4(&work->field_700, work->f49E4);
        work->field_49D0 = 3;
        return;

    case 1:
        MENU_Locate(100, 50, 16);
        MENU_Color(86, 137, 116);
        MENU_Printf("OVERWRITE OK?");
        MENU_Locate(100, 105, 16);
        MENU_Color(192, 192, 192);
        MENU_Printf("YES");
        MENU_Locate(200, 105, 16);
        MENU_Color(46, 72, 61);
        MENU_Printf("NO");
        camera_800CD0A0((MenuPrim *)&work->field_920, 92, 100, 40, 15);
        camera_800C6054(&work->field_700, work->field_924_mOrderingTable, 0);

        camera_AddTpage(work);

        if (press & PAD_RIGHT)
        {
            work->field_498C = 2;
            GM_SeSet2(0, 63, 31);
            return;
        }

        if (press & PAD_CIRCLE)
        {
            work->f28 = 8;
            work->field_49C8 = 0;
            GM_SeSet2(0, 63, 32);
            return;
        }

        if (press & PAD_CROSS)
        {
            GM_SeSet2(0, 63, 33);
            work->f28 = 0;
            GV_FreeMemory(2, camera_file_buf_800D0704);
            camera_800C82EC();
        }
        return;

    case 2:
        MENU_Locate(100, 50, 16);
        MENU_Color(86, 137, 116);
        MENU_Printf("OVERWRITE OK?");
        MENU_Locate(100, 105, 16);
        MENU_Color(46, 72, 61);
        MENU_Printf("YES");
        MENU_Locate(200, 105, 16);
        MENU_Color(192, 192, 192);
        MENU_Printf("NO");
        camera_800CD0A0((MenuPrim *)&work->field_920, 188, 100, 40, 15);
        camera_800C6054(&work->field_700, work->field_924_mOrderingTable, 0);

        camera_AddTpage(work);

        if (press & PAD_LEFT)
        {
            work->field_498C = 1;
            GM_SeSet2(0, 63, 31);
            return;
        }

        if (press & PAD_CIRCLE)
        {
            GM_SeSet2(0, 63, 33);
            work->f28 = 0;
            GV_FreeMemory(2, camera_file_buf_800D0704);
            camera_800C82EC();
            return;
        }

        if (press & PAD_CROSS)
        {
            GM_SeSet2(0, 63, 33);
            work->f28 = 0;
            GV_FreeMemory(2, camera_file_buf_800D0704);
            camera_800C82EC();
        }
        return;
    }
}
/* rdata of camera_800CD790 */
const char camera_aSsss_800D03C4[] = "%s%s%s%s";
const char camera_dword_800D03D0[] = "\x82\x6c\x82\x66\x82\x72";
const char camera_dword_800D03D8[] = "\x8e\xca\x90\x5e\x82\x6d\x82\x8f\x81\x44";

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CD790.s")

void camera_800CDAB4(Work *work)
{
    int ret;
    int i;
    int j;
    int found;
    int diff;
    int status;
    long st;
    int phase;
    char *ref;

    ret = memcard_check(camera_card_port_800D0708);
    printf("res = %x\n", ret);
    if (ret & 0x1000000)
    {
        i = 0;
        work->field_49CC = memcard_files(camera_card_port_800D0708);
        found = i;
        if (work->field_49CC->file_count != 0)
        {
            do
            {
                printf("%s\n", work->field_49CC->files[i].name);
                diff = 0;
                for (j = 0; j < 24; j++)
                {
                    if (work->field_49CC->files[i].name[j] != (ref = camera_file_name_800D0710)[j])
                    {
                        diff = 1;
                    }
                }
                if (diff == 0)
                {
                    printf("find!\n");
                    found = 1;
                }
                i++;
            } while (i < work->field_49CC->file_count);
        }
        if (found)
        {
            work->field_49C8 = 1;
            printf("phase is changed but data find\n");
        }
        else if (work->field_49CC) /* branch duplicated to match */
        {
            work->field_49C8 = 5;
            work->field_4938 = 0;
            printf("phase is changed\n");
            drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[6]);
            work->field_49D0 = 3;
        }
        else
        {
            work->field_49C8 = 5;
            work->field_4938 = 0;
            printf("phase is changed\n");
            drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[6]);
            work->field_49D0 = 3;
        }
    }
    else if (ret != 0)
    {
        printf("phase is changed\n");
        status = ret;
        status = status & 0xFF;
        phase = 3;
        st = status;
        if (st == phase || st == 0x80000000 || st == 1)
        {
            work->field_49C8 = 5;
            work->field_4938 = 0;
            drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[2]);
            work->field_49D0 = phase;
        }
    }
    else
    {
        work->field_49C8 = 1;
        printf("phase is not changed\n");
    }
}
void camera_800CDCA4(Work *work)
{
    MENU_Locate(100, 50, 16);
    MENU_Color(86, 137, 116);
    MENU_Printf("OVERWRITE OK?");

    MENU_Locate(100, 105, 16);
    MENU_Color(192, 192, 192);
    MENU_Printf("YES");

    MENU_Locate(200, 105, 16);
    MENU_Color(46, 72, 61);
    MENU_Printf("NO");

    camera_800CD0A0((MenuPrim *)&work->field_920, 92, 100, 40, 15);

    switch (work->field_49C8)
    {
    case 0:
        drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[1]);
        work->field_49D0 = 1;
        camera_800CDAB4(work);
        break;

    case 1:
        printf("save data delete\n");
        if (memcard_delete(camera_card_port_800D0708, camera_file_name_800D0710))
        {
            printf("delete success\n");
            printf("new memdata get\n");
            work->field_49CC = memcard_files(camera_card_port_800D0708);
            work->field_49C8 = 2;
        }
        else
        {
            printf("delete fail\n");
            drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[2]);
            work->field_49D0 = 3;
        }
        break;

    case 2:
        printf("new data create\n");
        camera_800CD790(work);
        work->field_49C8 = 3;
        break;

    case 3:
        printf("new data write\n");
        memcard_write(work->field_49CC->port, camera_file_name_800D0710, 0, camera_file_buf_800D0704, 0x4000);
        while (memcard_status() > 0)
        {
            mts_wait_vbl(2);
        }
        if (memcard_status() == 0)
        {
            printf("new data write ok\n");
            work->field_49C8 = 4;
            work->field_4938 = 0;
            drawCaption_800C5EB4(&work->field_700, camera_captions_800C3910[3]);
            work->field_49D0 = 3;
        }
        break;

    case 4:
    case 5:
        if (work->field_4938 >= 30)
        {
            work->f28 = 0;
            GV_FreeMemory(2, camera_file_buf_800D0704);
            camera_800C82EC();
        }
        break;
    }
}

void camera_800CDF18(Work *work)
{
    POLY_FT4 *poly;
    int       result;
    int       i;

    poly = work->polys2;

    switch (work->f28)
    {
    case 0:
        result = camera_800C73E4(&work->field_700, &GV_PadData[2]);
        if (result == 1)
        {
            work->f28 = 9;
        }

        if (result == 2)
        {
            work->f28 = 1;
            work->f49E0 = 0;

            for (i = 0; i < 16; i++)
            {
                work->field_494C_name[i] = ' ';
                work->field_4994_str[i] = ' ';
            }

            work->field_494C_name[16] = '\0';
            work->field_4994_str[16] = '\0';
        }
        break;

    case 1:
        camera_800C4394(work);
        work->f28 = 3;

        if (work->field_4934 == 0)
        {
            work->f2C = 0;
            work->field_4938 = 0;
            work->field_688[0] = (GV_ACT *)0x600;
            work->field_688[1] = (GV_ACT *)0x600;
            work->field_688[2] = (GV_ACT *)0x200;
            work->field_688[3] = (GV_ACT *)0x200;
            work->field_688[4] = (GV_ACT *)0x200;
            work->field_688[5] = (GV_ACT *)0x600;
            work->field_688[6] = (GV_ACT *)0x600;
            work->field_688[7] = (GV_ACT *)0x600;
            camera_800C86BC(work, -0x90, 0x5A, 0x70, 0xC, 0xFF, 0);
        }
        else
        {
            work->f2C = 3;
            work->field_4938 = 0;
            work->field_688[0] = (GV_ACT *)0x600;
            work->field_688[1] = (GV_ACT *)0x600;
            work->field_688[16] = (GV_ACT *)0x200;
            work->field_688[17] = (GV_ACT *)0x200;
            work->field_688[18] = (GV_ACT *)0x200;
            work->field_688[19] = (GV_ACT *)0x200;
            work->field_688[5] = (GV_ACT *)0x600;
            work->field_688[6] = (GV_ACT *)0x600;
            work->field_688[7] = (GV_ACT *)0x600;
            camera_800C86BC(work, -0x90, 0x5A, 0x68, 0xC, 0xFF, 0);

            setXY4(&poly[16], -0x90, 0x5A, -0x28, 0x5A, -0x90, 0x66, -0x28, 0x66);
            setXY4(&poly[17], -0x2A, 0x5A, 0x12, 0x5A, -0x2A, 0x66, 0x12, 0x66);
            setXY4(&poly[18], 0x11, 0x5A, 0x65, 0x5A, 0x11, 0x66, 0x65, 0x66);
            setXY4(&poly[19], 0x64, 0x5A, 0x90, 0x5A, 0x64, 0x66, 0x90, 0x66);
        }
        break;

    case 3:
        MENU_Locate(26, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49D4);
        MENU_Locate(75, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49DD);
        camera_800C8554(work->field_49A8, 83, 13, 16);
        camera_800C85B8(work->field_49A8, 86, 137, 116);
        camera_800C8564((MenuPrim *)&work->field_920, (SELECT_INFO *)work->field_49A8, work->field_494C_name);
        camera_800CCBB0(work);
        break;

    case 4:
        MENU_Locate(26, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49D4);
        MENU_Locate(75, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49DD);
        camera_800C8554(work->field_49A8, 83, 13, 16);
        camera_800C85B8(work->field_49A8, 86, 137, 116);
        camera_800C8564((MenuPrim *)&work->field_920, (SELECT_INFO *)work->field_49A8, work->field_494C_name);
        camera_800CA918(work);
        break;

    case 5:
        MENU_Locate(26, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49D4);
        MENU_Locate(75, 14, 0);
        MENU_Color(58, 92, 78);
        MENU_Printf(work->field_49DD);
        camera_800C8554(work->field_49A8, 83, 13, 16);
        camera_800C85B8(work->field_49A8, 86, 137, 116);
        camera_800C8564((MenuPrim *)&work->field_920, (SELECT_INFO *)work->field_49A8, work->field_494C_name);
        camera_800CC3C8(work);
        break;

    case 6:
        camera_800CBDE4(work);
        break;

    case 7:
        camera_800CD198(work);
        break;

    case 8:
        camera_800CDCA4(work);
        if (work->field_49D0 >= 2)
        {
            work->field_49D0--;
        }
        else
        {
            camera_800C6054(&work->field_700, work->field_924_mOrderingTable, 0);
            camera_AddTpage(work);
        }
        break;

    case 9:
        GCL_ExecProc(work->f20, NULL);
        GV_DestroyActor(&work->actor);
        break;
    }
}

void CameraAct_800CE404(Work *work)
{
    work->field_920 = work->field_92C[GV_Clock];
    work->field_924_mOrderingTable = DG_Chanl(1)->ot[GV_Clock];
    camera_800CDF18(work);
    camera_800C3ED8(work);
    work->field_4938++;
}

void CameraDie_800CE470(Work *work)
{
    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    GM_FreePrim(work->prim3);
}

int camera_800CE6EC(Work *work, int where);

void camera_800CE4F8(Work *work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
{
    setPolyFT4(pPoly);
    setRGB0(pPoly, 128, 128, 128);
    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x2 = x0;
    pPoly->x1 = x1;
    pPoly->y2 = y1;
    pPoly->x3 = x1;
    pPoly->y3 = y1;
    SetSemiTrans(pPoly, semiTrans);
}

void camera_800CE568(Work *work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans, int arg9)
{
    DG_TEX *tex;
    camera_800CE4F8(work, pPoly, x0, y0, x1, y1, semiTrans);
    tex = DG_GetTexture(hashCode);

    if (arg9 == 0)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 1)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 2)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 3)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }
}

int CameraGetResources_800CE6EC(Work *work, int map)
{
    POLY_FT4 *poly;
    int       i;

    GM_CurrentMap = map;

    work->prim1 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 4, NULL, NULL);
    work->prim2 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, NULL, NULL);
    work->prim3 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 26, NULL, NULL);

    for (i = 3; i >= 0; i--)
    {
        work->field_654[i] = 0;
    }

    poly = work->polys;
    i = 0;

    camera_800CE568(work, GV_StrCode("cur_lu"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_ru"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_ld"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_rd"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_u"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_d"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_l"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_r"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_c"), poly, 0, 0, 0, 0, 1, 3);
    poly++;
    work->field_664[i] = NULL;
    i++;

    poly = work->polys2;
    i = 0;

    camera_800CE568(work, GV_StrCode("cam_album"), poly, 60, -102, 144, -90, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_frame"), poly, -144, -102, 60, -90, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name"), poly, -144, 90, -32, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color"), poly, -5, 90, 63, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_exit"), poly, 90, 90, 144, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line1"), poly, -144, 84, 144, 86, 0, 2);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line2"), poly, 142, -90, 146, 86, 0, 1);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line3"), poly, -146, -90, -142, 86, 0, 1);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_entry_l"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_entry_r"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_ad"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_name"), poly, -144, 90, -40, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_color"), poly, -42, 90, 18, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exor"), poly, 17, 90, 101, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exit"), poly, 100, 90, 144, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji1_l"), poly, -139, 90, 5, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji1_r"), poly, 5, 90, 133, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji2"), poly, -139, 90, 89, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_name_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_color_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exor_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    if (GCL_GetOption('e') != NULL)
    {
        work->f20 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->f20 = -1;
    }

    for (i = 0; i <= 0; i++)
    {
        work->f49E4 = GCL_GetString(GCL_NextStr());
    }

    work->pad = &GV_PadData[2];
    work->f28 = 0;

    work->field_700.prim = (MenuPrim *)&work->field_920;
    work->field_92C[0] = work->padding5;
    work->field_4938 = 0;
    work->field_92C[1] = work->padding5 + 0x2000;

    camera_800C85D8();
    camera_800C82EC();

    work->f49E0 = 0;
    return 0;
}

void *NewCamera_800CF388(int name, int where, int argc, char **argv)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;
    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, CameraAct_800CE404, CameraDie_800CE470, "camera.c");

        if (CameraGetResources_800CE6EC(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
