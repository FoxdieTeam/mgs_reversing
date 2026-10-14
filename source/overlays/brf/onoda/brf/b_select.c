#include "game/game.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

typedef struct _Work
{
    GV_ACT  actor;            /* 0x000, size 0x20 */
    DG_PRIM *field_20;        /* 0x020 */
    DG_PRIM *field_24;        /* 0x024 */
    char   pad_28[0x4];       /* 0x028 */
    char   field_2C[44];      /* 0x02C */
    char   field_58[9];       /* 0x058 */
    char   pad_61[0xF];       /* 0x061 */
    int    field_70;          /* 0x070 */
    int    field_74;          /* 0x074 */
    char   pad_78[0x4];       /* 0x078 */
    int    field_7C;          /* 0x07C */
    int    field_80[16];      /* 0x080 */
    char   pad_C0[0xC];       /* 0x0C0 */
    int    field_CC;          /* 0x0CC */
    int    field_D0;          /* 0x0D0 */
    int    field_D4;          /* 0x0D4 */
    void  *field_D8;          /* 0x0D8 */
    void  *field_DC;          /* 0x0DC */
    int    field_E0;          /* 0x0E0 */
    void  *field_E4;          /* 0x0E4 */
    char   field_E8[0x40];    /* 0x0E8 */
    DG_TEX field_128[64];     /* 0x128 */
    int    field_428[64];     /* 0x428 */
    int    field_528;         /* 0x528 */
    int    field_52C[64];     /* 0x52C */
    int    field_62C[64];     /* 0x62C */
    int    field_72C;         /* 0x72C */
    int      field_730[19];   /* 0x730 */
    int      field_77C;       /* 0x77C */
    POLY_FT4 field_780[44];   /* 0x780 */
    POLY_FT4 field_E60[9];    /* 0xE60 */
    char     pad_FC8[0xC];    /* 0xFC8 */
    int    field_FD4;         /* 0xFD4 */
    int    field_FD8;         /* 0xFD8 */
    int    field_FDC;         /* 0xFDC */
    int    field_FE0;         /* 0xFE0 */
    char   pad_FE4[0x4];      /* 0xFE4 */
} Work;

typedef struct
{
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
    short         field_4;
    short         field_6;
} BrfStage;

extern int brf_dword_800C3470;
extern int brf_dword_800C33E4;
void *NewBriefingGraph(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);
void *NewBriefingCount(int map, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

void brf_800C5230(Work *work)
{
    BrfStage stage;
    int      idx;
    int      f0, f1, f2, f3, f4, f6;

    idx = work->field_CC;
    stage = ((BrfStage *)&brf_dword_800C3470)[idx];
    f0 = stage.field_0;
    f1 = stage.field_1;
    f2 = stage.field_2;
    f3 = stage.field_3;
    f4 = stage.field_4;
    f6 = stage.field_6;
    work->field_77C = (&brf_dword_800C33E4)[idx];
    work->field_D8 = NewBriefingGraph(work->field_E0, work->field_528, (int)work->field_428, (int)work->field_128, idx,
                                      work->field_77C, work->field_72C, (int)work->field_62C, (int)work->field_52C);
    work->field_DC = NewBriefingCount(work->field_E0, f0, f1, f2, work->field_77C - 100, f3, f4, f6);
}

typedef struct
{
    char *name;
    int   offset;
    int   size;
} BrfResource;

extern int brf_dword_800C321C;
extern const char brf_dword_800E1088[];

void brf_800C5350(Work *work, int idx)
{
    BrfResource *table = (BrfResource *)&brf_dword_800C321C;
    BrfResource *e = &table[idx];

    printf((char *)brf_dword_800E1088, e->name);
    work->field_E4 = PACK_ADDR0;
    FS_LoadFileRequest(FS_FILE_BRF, e->offset, e->size, PACK_ADDR0);
    while (FS_LoadFileSync() > 0)
    {
        mts_wait_vbl(1);
    }
}
extern int brf_dword_800C3300;

void brf_800C53E4(Work *work, int idx)
{
    BrfResource *table = (BrfResource *)&brf_dword_800C3300;
    BrfResource *e = &table[idx];

    printf((char *)brf_dword_800E1088, e->name);
    work->field_E4 = PACK_ADDR0;
    FS_LoadFileRequest(FS_FILE_BRF, e->offset, e->size, PACK_ADDR0);
    while (FS_LoadFileSync() > 0)
    {
        mts_wait_vbl(1);
    }
}
void brf_800C5478(Work *work, int id, int tp, int abr, RECT *img, RECT *pal, int col)
{
    DG_TEX *tex;
    int     n;
    int     x, y, w, h;
    int     cx, cy;
    int     tpage;

    work->field_428[work->field_528] = id;
    n = work->field_528;
    work->field_528 = n + 1;
    tex = &work->field_128[n];

    tex->id = id;
    tex->col = col;

    x = img->x;
    y = img->y;

    cx = pal->x;
    cy = pal->y;

    w = x;
    tpage = ((x / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->tpage = tpage;
    tex->clut = cy << 6 | cx >> 4;

    x %= 64;

    w = img->w;
    h = img->h;

    if (tp == 0)
    {
        x *= 4;
        w *= 4;
    }
    else
    {
        x *= 2;
        w *= 2;
    }

    tex->off_x = x;
    tex->off_y = y % 256;
    tex->w = w - 1;
    tex->h = h - 1;
}

void brf_800C5584(Work *work, int id, int tp, int abr, RECT *img, RECT *pal, int col, int a7)
{
    DG_TEX *tex;
    int     n;
    int     x, y, w, h;
    int     cx, cy;
    int     tpage;

    work->field_62C[work->field_72C] = id;
    work->field_52C[work->field_72C] = a7;
    work->field_72C++;
    work->field_428[work->field_528] = id;
    n = work->field_528;
    work->field_528 = n + 1;
    tex = &work->field_128[n];

    tex->id = id;
    tex->col = col;

    x = img->x;
    y = img->y;

    cx = pal->x;
    cy = pal->y;

    w = x;
    tpage = ((x / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->tpage = tpage;
    tex->clut = cy << 6 | cx >> 4;

    x %= 64;

    w = img->w;
    h = img->h;

    if (tp == 0)
    {
        x *= 4;
        w *= 4;
    }
    else
    {
        x *= 2;
        w *= 2;
    }

    tex->off_x = x;
    tex->off_y = y % 256;
    tex->w = w - 1;
    tex->h = h - 1;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C56C0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5A68.s")
void brf_800C56C0(Work *work, void *data, int cache_id);
extern const char brf_dword_800E10D4[];

void brf_800C5DE4(Work *work)
{
    char *p = (char *)work->field_E4;
    int count = *(int *)p;
    char *dst;
    char c;
    int n;

    p += 4;
    do
    {
        c = *p++;
        work->field_E8[0] = c;
        dst = &work->field_E8[1];
        if (c != 0)
        {
            do
            {
                c = *p++;
                *dst++ = c;
            } while (c != 0);
        }
        p += (4 - ((int)p & 3)) & 3;
        n = *(int *)p;
        p += 4;
        brf_800C56C0(work, p, GV_CacheID3(work->field_E8));
        count--;
        n++;
        p += n;
    } while (count > 0);
    printf((char *)brf_dword_800E10D4);
}
void brf_800C5A68(Work *work, void *data, int cache_id);
extern const char brf_dword_800E10F8[];

void brf_800C5EAC(Work *work)
{
    char *p = (char *)work->field_E4;
    int count = *(int *)p;
    char *dst;
    char c;
    int n;

    p += 4;
    do
    {
        c = *p++;
        work->field_E8[0] = c;
        dst = &work->field_E8[1];
        if (c != 0)
        {
            do
            {
                c = *p++;
                *dst++ = c;
            } while (c != 0);
        }
        p += (4 - ((int)p & 3)) & 3;
        n = *(int *)p;
        p += 4;
        brf_800C5A68(work, p, GV_CacheID3(work->field_E8));
        count--;
        n++;
        p += n;
    } while (count > 0);
    printf((char *)brf_dword_800E10F8);
}
void brf_800C5F74(Work *work)
{
    int i;

    work->field_528 = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->field_428[i] = 0;
    }

    work->field_72C = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->field_62C[i] = 0;
    }
}
void brf_800C5350(Work *work, int idx);
void brf_800C5DE4(Work *work);

void brf_800C5FB4(Work *work, int arg)
{
    brf_800C5350(work, arg);
    brf_800C5DE4(work);
}

void brf_800C53E4(Work *work, int idx);
void brf_800C5EAC(Work *work);

void brf_800C5FE0(Work *work, int arg)
{
    brf_800C53E4(work, arg);
    brf_800C5EAC(work);
}
typedef struct
{
    short sel;
    short arg;
} BrfDispatch;

extern int brf_dword_800C3430;

void brf_800C600C(Work *work)
{
    int idx = work->field_70 - 9;
    BrfDispatch e = ((BrfDispatch *)&brf_dword_800C3430)[idx];
    int arg = e.arg;

    if (e.sel == 0)
    {
        brf_800C5FB4(work, arg);
    }
    else if (e.sel == 1)
    {
        brf_800C5FB4(work, arg);
        brf_800C5FE0(work, arg);
    }
}
void brf_800C609C(Work *work, int sel, int arg)
{
    if (sel == 0)
    {
        brf_800C5FB4(work, arg);
    }
    else if (sel == 1)
    {
        brf_800C5FB4(work, arg);
        brf_800C5FE0(work, arg);
    }
}
void brf_800C60FC(Work *work)
{
    int i;
    int found;

    GV_PauseLevel |= GV_PAUSE_STOP;
    DG_StopMainChanlSystem();
    GV_ResetPacketMemory();
    brf_800C5F74(work);

    switch (work->field_70)
    {
    case 0:
    case 4:
        brf_800C609C(work, 1, 0x10);
        break;
    case 8:
        if (work->field_D4 == 0)
        {
            brf_800C609C(work, 1, 0x11);
        }
        else
        {
            found = 0;
            for (i = 0; i < 16; i++)
            {
                if (work->field_80[i] == 0)
                {
                    found = 1;
                }
            }
            if (!found)
            {
                brf_800C609C(work, 0, 0x12);
            }
        }
        break;
    default:
        brf_800C600C(work);
        break;
    }

    GV_ResetPacketMemory();
    GV_PauseLevel &= ~GV_PAUSE_STOP;
    DG_RestartMainChanlSystem();
}

void brf_800C6228(Work *work, int a1, int a2)
{
    GM_SeSet2(0, 0x3F, 0xB7);
    brf_800C60FC(work);
    GM_VoxStream(work->field_730[a1], 0x40000000);
    work->field_74 = work->field_70;
    work->field_70 = a2;
    work->field_D0 = 0;
    work->field_CC = a1;
    GM_SetSound(0x01FFFF0B, 0);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C62B0.s")
void brf_800C65C8(Work *work)
{
    int i = 8;
    char *p = (char *)work + i;

    for (; i >= 0; i--, p--)
    {
        p[0x58] = 0;
    }
}
void brf_800C65E8(Work *work)
{
    int i = 0x2B;
    char *p = (char *)work + i;

    for (; i >= 0; i--, p--)
    {
        p[0x2C] = 0;
    }
    brf_800C65C8(work);
}
void brf_800C6620(Work *work)
{
    work->field_FD4 = 0;
    work->field_FD8 = 0;
    work->field_FDC = 0;
    work->field_FE0 = 0;
}
void brf_800C6634(Work *work)
{
    POLY_FT4 *poly = work->field_780;
    int i;

    for (i = 0; i < 16; i++)
    {
        if (work->field_80[i] == 1)
        {
            poly[i + 9].r0 = 0x46;
            poly[i + 9].g0 = 0x50;
            poly[i + 9].b0 = 0x4B;
        }
    }

    if (work->field_80[1] == 1)
    {
        poly[27].r0 = 0x46; poly[27].g0 = 0x50; poly[27].b0 = 0x4B;
        poly[28].r0 = 0x46; poly[28].g0 = 0x50; poly[28].b0 = 0x4B;
    }
    if (work->field_80[3] == 1)
    {
        poly[29].r0 = 0x46; poly[29].g0 = 0x50; poly[29].b0 = 0x4B;
        poly[30].r0 = 0x46; poly[30].g0 = 0x50; poly[30].b0 = 0x4B;
    }
    if (work->field_80[5] == 1)
    {
        poly[31].r0 = 0x46; poly[31].g0 = 0x50; poly[31].b0 = 0x4B;
        poly[32].r0 = 0x46; poly[32].g0 = 0x50; poly[32].b0 = 0x4B;
    }
    if (work->field_80[10] == 1)
    {
        poly[33].r0 = 0x46; poly[33].g0 = 0x50; poly[33].b0 = 0x4B;
        poly[34].r0 = 0x46; poly[34].g0 = 0x50; poly[34].b0 = 0x4B;
    }
    if (work->field_80[13] == 1)
    {
        poly[35].r0 = 0x46; poly[35].g0 = 0x50; poly[35].b0 = 0x4B;
        poly[36].r0 = 0x46; poly[36].g0 = 0x50; poly[36].b0 = 0x4B;
    }
    if (work->field_80[15] == 1)
    {
        poly[37].r0 = 0x46; poly[37].g0 = 0x50; poly[37].b0 = 0x4B;
        poly[38].r0 = 0x46; poly[38].g0 = 0x50; poly[38].b0 = 0x4B;
    }
    if (work->field_80[0] == 1 && work->field_80[1] == 1)
    {
        poly[5].r0 = 0x46;
        poly[5].g0 = 0x50;
        poly[5].b0 = 0x4B;
    }
    if (work->field_80[2] == 1 && work->field_80[3] == 1 && work->field_80[4] == 1 &&
        work->field_80[5] == 1 && work->field_80[6] == 1)
    {
        poly[6].r0 = 0x46;
        poly[6].g0 = 0x50;
        poly[6].b0 = 0x4B;
    }
    if (work->field_80[7] == 1 && work->field_80[8] == 1 && work->field_80[9] == 1 &&
        work->field_80[10] == 1 && work->field_80[11] == 1 && work->field_80[12] == 1 &&
        work->field_80[13] == 1 && work->field_80[14] == 1 && work->field_80[15] == 1)
    {
        poly[7].r0 = 0x46;
        poly[7].g0 = 0x50;
        poly[7].b0 = 0x4B;
    }
}
void brf_800C68EC(Work *work, int a1, int a2, int a3)
{
    work->field_FD8 = work->field_70;
    work->field_FD4 = a1;
    work->field_FDC = a2;
    work->field_70 = a2;
    work->field_D0 = 0;
    work->field_FE0 = a3;
    GM_SeSet2(0, 0x3F, 0x1F);
}
void brf_800C6930(Work *work, int idx1, int idx2, int base_y)
{
    POLY_FT4 *p = work->field_780;
    int x0, x3;

    x0 = p[idx1].x0;
    x3 = p[idx1].x3;
    p[idx1].y0 = base_y + 0xA;
    p[idx1].y1 = base_y + 0xA;
    p[idx1].y2 = base_y + 0xB;
    p[idx1].y3 = base_y + 0xB;
    p[idx1].x0 = x0;
    p[idx1].x1 = x3;
    p[idx1].x2 = x0;
    p[idx1].x3 = x3;

    x0 = p[idx2].x0;
    x3 = p[idx2].x3;
    p[idx2].y0 = base_y - 4;
    p[idx2].y1 = base_y - 4;
    p[idx2].y2 = base_y + 0xA;
    p[idx2].y3 = base_y + 0xA;
    p[idx2].x0 = x0;
    p[idx2].x1 = x3;
    p[idx2].x2 = x0;
    p[idx2].x3 = x3;
}
int brf_800C69B4(Work *work, int idx, int y, int h)
{
    POLY_FT4 *p = work->field_780;
    int x0 = p[idx].x0;
    int x3 = p[idx].x3;

    p[idx].y0 = y;
    p[idx].y1 = y;
    p[idx].y2 = y + 0xD;
    p[idx].y3 = y + 0xD;
    p[idx].x0 = x0;
    p[idx].x1 = x3;
    p[idx].x2 = x0;
    p[idx].x3 = x3;
    return y + h;
}
void brf_800C69FC(Work *work, int lo, int hi)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int color;

    if (d < lo) return;
    if (hi < d) return;

    work->field_2C[0] = 3;
    work->field_2C[1] = 3;
    work->field_2C[43] = 3;

    color = (d - lo) * 8;

    p[0].x0 = -0xA0; p[0].y0 = -0x70;
    p[0].x1 = 0;     p[0].y1 = -0x70;
    p[0].x2 = -0xA0; p[0].y2 = 0x70;
    p[0].x3 = 0;     p[0].y3 = 0x70;
    p[0].r0 = color; p[0].g0 = color; p[0].b0 = color;

    p[1].x0 = 0;     p[1].y0 = -0x70;
    p[1].x1 = 0xA0;  p[1].y1 = -0x70;
    p[1].x2 = 0;     p[1].y2 = 0;
    p[1].x3 = 0xA0;  p[1].y3 = 0;
    p[1].r0 = color; p[1].g0 = color; p[1].b0 = color;

    p[43].x0 = 0;    p[43].y0 = 0;
    p[43].x1 = 0xA0; p[43].y1 = 0;
    p[43].x2 = 0;    p[43].y2 = 0x70;
    p[43].x3 = 0xA0; p[43].y3 = 0x70;
    p[43].r0 = color; p[43].g0 = color; p[43].b0 = color;
}
void brf_800C6AD0(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int xl;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    xl = -70 - (d - a1) * 24;
    p[2].x0 = xl;
    p[2].y0 = -12;
    p[2].x1 = xl + 140;
    p[2].y1 = -12;
    p[2].x2 = xl;
    p[2].y2 = 0;
    p[2].x3 = xl + 140;
    p[2].y3 = 0;
    p[3].x0 = xl;
    p[3].y0 = -12;
    p[3].x1 = xl + 140;
    p[3].y1 = -12;
    p[3].x2 = xl;
    p[3].y2 = 0;
    p[3].x3 = xl + 140;
    p[3].y3 = 0;
}
void brf_800C6B54(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    q = -12 - (d - a1) * 83 / 3;
    p[2].x0 = -142;
    p[2].y0 = q;
    p[2].x1 = -2;
    p[2].y1 = q;
    p[2].x2 = -142;
    p[2].y2 = q + 12;
    p[2].x3 = -2;
    p[2].y3 = q + 12;
    p[3].x0 = -142;
    p[3].y0 = q;
    p[3].x1 = -2;
    p[3].y1 = q;
    p[3].x2 = -142;
    p[3].y2 = q + 12;
    p[3].x3 = -2;
    p[3].y3 = q + 12;
}
void brf_800C6C00(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int diff;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_2C[4] = 1;
    diff = d - a1;
    p[4].x0 = -142;
    p[4].y0 = diff * 13 - 95;
    p[4].x1 = -22;
    p[4].y1 = diff * 13 - 95;
    p[4].x2 = -142;
    p[4].y2 = diff * 13 - 78;
    p[4].x3 = -22;
    p[4].y3 = diff * 13 - 78;
}
void brf_800C6C74(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_2C[5] = 1;
    q = (d - a1) * 46 / 3;
    p[5].x0 = -142;
    p[5].y0 = q - 95;
    p[5].x1 = -46;
    p[5].y1 = q - 95;
    p[5].x2 = -142;
    p[5].y2 = q - 78;
    p[5].x3 = -46;
    p[5].y3 = q - 78;
}
void brf_800C6D04(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_2C[6] = 1;
    q = (d - a1) * 66 / 4;
    p[6].x0 = -142;
    p[6].y0 = q - 95;
    p[6].x1 = -22;
    p[6].y1 = q - 95;
    p[6].x2 = -142;
    p[6].y2 = q - 78;
    p[6].x3 = -22;
    p[6].y3 = q - 78;
}
void brf_800C6D7C(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_2C[7] = 1;
    q = (d - a1) * 86 / 5;
    p[7].x0 = -142;
    p[7].y0 = q - 95;
    p[7].x1 = -46;
    p[7].y1 = q - 95;
    p[7].x2 = -142;
    p[7].y2 = q - 78;
    p[7].x3 = -46;
    p[7].y3 = q - 78;
}
void brf_800C6E14(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_2C[8] = 1;
    q = (d - a1) * 23;
    p[8].x0 = -142;
    p[8].y0 = q - 95;
    p[8].x1 = -86;
    p[8].y1 = q - 95;
    p[8].x2 = -142;
    p[8].y2 = q - 83;
    p[8].x3 = -86;
    p[8].y3 = q - 83;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6E88.s")
const char brf_dword_800E0F3C[] = {'s', '1', '8', 'v'};
const char brf_dword_800E0F40[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F44[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F48[] = {'s', '1', '7', 'v'};
const char brf_dword_800E0F4C[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F50[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F54[] = {'s', '1', '6', 'v'};
const char brf_dword_800E0F58[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F5C[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F60[] = {'s', '1', '5', 'v'};
const char brf_dword_800E0F64[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F68[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F6C[] = {'s', '1', '4', 'v'};
const char brf_dword_800E0F70[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F74[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F78[] = {'s', '1', '3', 'v'};
const char brf_dword_800E0F7C[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F80[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F84[] = {'s', '1', '2', 'v'};
const char brf_dword_800E0F88[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F8C[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F90[] = {'s', '1', '1', 'v'};
const char brf_dword_800E0F94[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0F98[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0F9C[] = {'s', '1', '0', 'v'};
const char brf_dword_800E0FA0[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FA4[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FA8[] = {'s', '0', '9', 'v'};
const char brf_dword_800E0FAC[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FB0[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FB4[] = {'s', '0', '8', 'v'};
const char brf_dword_800E0FB8[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FBC[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FC0[] = {'s', '0', '7', 'v'};
const char brf_dword_800E0FC4[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FC8[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FCC[] = {'s', '0', '6', 'v'};
const char brf_dword_800E0FD0[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FD4[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FD8[] = {'s', '0', '5', 'v'};
const char brf_dword_800E0FDC[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FE0[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FE4[] = {'s', '0', '4', 'v'};
const char brf_dword_800E0FE8[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FEC[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FF0[] = {'s', '0', '3', 'v'};
const char brf_dword_800E0FF4[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E0FF8[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E0FFC[] = {'s', '0', '2', 'v'};
const char brf_dword_800E1000[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1004[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1008[] = {'s', '0', '1', 'v'};
const char brf_dword_800E100C[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1010[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1014[] = {'s', '0', '0', 'v'};
const char brf_dword_800E1018[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E101C[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1020[] = {'s', '1', '7', 'c'};
const char brf_dword_800E1024[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1028[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E102C[] = {'s', '1', '6', 'c'};
const char brf_dword_800E1030[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1034[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1038[] = {'s', '1', '5', 'c'};
const char brf_dword_800E103C[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1040[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1044[] = {'s', '1', '3', 'c'};
const char brf_dword_800E1048[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E104C[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1050[] = {'s', '1', '1', 'c'};
const char brf_dword_800E1054[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1058[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E105C[] = {'s', '1', '0', 'c'};
const char brf_dword_800E1060[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1064[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1068[] = {'s', '0', '8', 'c'};
const char brf_dword_800E106C[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1070[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1074[] = {'t', 'm', 'p', '.'};
const char brf_dword_800E1078[] = {'d', 'b', 'l', 0x0};
const char brf_dword_800E107C[] = {'s', '0', '0', 'c'};
const char brf_dword_800E1080[] = {'.', 'd', 'b', 'l'};
const char brf_dword_800E1084[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1088[] = {'B', 'r', 'i', 'e'};
const char brf_dword_800E108C[] = {'f', 'i', 'n', 'g'};
const char brf_dword_800E1090[] = {' ', 'T', 'e', 'x'};
const char brf_dword_800E1094[] = {'t', 'u', 'r', 'e'};
const char brf_dword_800E1098[] = {' ', 'L', 'o', 'a'};
const char brf_dword_800E109C[] = {'d', '_', 'S', 't'};
const char brf_dword_800E10A0[] = {'a', 'r', 't', ' '};
const char brf_dword_800E10A4[] = {'%', 's', '\n', 0x0};
const char brf_dword_800E10A8[] = {'C', 'a', 'n', 'n'};
const char brf_dword_800E10AC[] = {'o', 't', ' ', 'A'};
const char brf_dword_800E10B0[] = {'l', 'l', 'o', 'c'};
const char brf_dword_800E10B4[] = {' ', 'E', 'x', 'p'};
const char brf_dword_800E10B8[] = {'a', 'n', 's', 'i'};
const char brf_dword_800E10BC[] = {'o', 'n', ' ', 'M'};
const char brf_dword_800E10C0[] = {'e', 'm', 'o', 'r'};
const char brf_dword_800E10C4[] = {'y', '!', ' ', 's'};
const char brf_dword_800E10C8[] = {'i', 'z', 'e', ' '};
const char brf_dword_800E10CC[] = {'=', ' ', '%', 'd'};
const char brf_dword_800E10D0[] = {'\n', 0x0, 0x0, 0x0};
const char brf_dword_800E10D4[] = {'B', 'r', 'i', 'e'};
const char brf_dword_800E10D8[] = {'f', 'i', 'n', 'g'};
const char brf_dword_800E10DC[] = {' ', 'T', 'e', 'x'};
const char brf_dword_800E10E0[] = {'t', 'u', 'r', 'e'};
const char brf_dword_800E10E4[] = {' ', 'V', 'R', 'A'};
const char brf_dword_800E10E8[] = {'M', ' ', 'S', 'e'};
const char brf_dword_800E10EC[] = {'t', '_', 'F', 'i'};
const char brf_dword_800E10F0[] = {'n', 'i', 's', 'h'};
const char brf_dword_800E10F4[] = {'!', '\n', 0x0, 0x0};
const char brf_dword_800E10F8[] = {'B', 'r', 'i', 'e'};
const char brf_dword_800E10FC[] = {'f', 'i', 'n', 'g'};
const char brf_dword_800E1100[] = {' ', 'T', 'e', 'x'};
const char brf_dword_800E1104[] = {'t', 'u', 'r', 'e'};
const char brf_dword_800E1108[] = {' ', 'M', 'a', 'i'};
const char brf_dword_800E110C[] = {'n', 'M', 'e', 'm'};
const char brf_dword_800E1110[] = {'o', 'r', 'y', ' '};
const char brf_dword_800E1114[] = {'L', 'o', 'a', 'd'};
const char brf_dword_800E1118[] = {'_', 'F', 'i', 'n'};
const char brf_dword_800E111C[] = {'i', 's', 'h', '!'};
const char brf_dword_800E1120[] = {'\n', 0x0, 0x0, 0x0};

void brf_800C731C(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;
    int y0, y3;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    switch (work->field_74)
    {
    case 5:
    case 9:
    case 10:
        work->field_2C[25] = 1;
        y0 = p[25].y0;
        y3 = p[25].y3;
        q = (d - a1) * 11;
        p[25].x0 = -46;
        p[25].x1 = q - 46;
        p[25].x2 = -46;
        p[25].x3 = q - 46;
        p[25].y0 = y0;
        p[25].y1 = y0;
        p[25].y2 = y3;
        p[25].y3 = y3;
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        work->field_2C[39] = 1;
        y0 = p[39].y0;
        y3 = p[39].y3;
        q = (d - a1) * 44 / 6;
        p[39].x0 = -24;
        p[39].x2 = -24;
        p[39].y0 = y0;
        p[39].y1 = y0;
        p[39].y2 = y3;
        p[39].y3 = y3;
        p[39].x1 = q - 24;
        p[39].x3 = q - 24;
        break;
    default:
        work->field_2C[41] = 1;
        y0 = p[41].y0;
        y3 = p[41].y3;
        q = (d - a1) * 11;
        p[41].x0 = -46;
        p[41].x1 = q - 46;
        p[41].x2 = -46;
        p[41].x3 = q - 46;
        p[41].y0 = y0;
        p[41].y1 = y0;
        p[41].y2 = y3;
        p[41].y3 = y3;
        break;
    }
}
const char brf_dword_800E1150[] = {0x0, 0x0, 0x0, 0x0};
void brf_800C7488(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;
    int y0, y3;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    switch (work->field_74)
    {
    case 5:
    case 9:
    case 10:
        work->field_2C[26] = 1;
        y0 = p[26].y0;
        y3 = p[26].y3;
        p[26].x0 = (d - a1) * 11 - 47;
        p[26].x1 = (d - a1) * 11 - 43;
        p[26].x2 = (d - a1) * 11 - 47;
        p[26].x3 = (d - a1) * 11 - 43;
        p[26].y0 = y0;
        p[26].y1 = y0;
        p[26].y2 = y3;
        p[26].y3 = y3;
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        work->field_2C[40] = 1;
        y0 = p[40].y0;
        y3 = p[40].y3;
        p[40].y0 = y0;
        p[40].y1 = y0;
        p[40].y2 = y3;
        p[40].y3 = y3;
        q = (d - a1) * 44 / 6;
        p[40].x0 = q - 25;
        p[40].x1 = q - 21;
        p[40].x2 = q - 25;
        p[40].x3 = q - 21;
        break;
    default:
        work->field_2C[42] = 1;
        y0 = p[42].y0;
        y3 = p[42].y3;
        p[42].x0 = (d - a1) * 11 - 47;
        p[42].x1 = (d - a1) * 11 - 43;
        p[42].x2 = (d - a1) * 11 - 47;
        p[42].x3 = (d - a1) * 11 - 43;
        p[42].y0 = y0;
        p[42].y1 = y0;
        p[42].y2 = y3;
        p[42].y3 = y3;
        break;
    }
}
const char brf_dword_800E1180[] = {0x0, 0x0, 0x0, 0x0};
const int brf_dword_800E1184 = 0x800C7648;
const int brf_dword_800E1188 = 0x800C7878;
const int brf_dword_800E118C = 0x800C7878;
const int brf_dword_800E1190 = 0x800C7878;
const int brf_dword_800E1194 = 0x800C7648;
const int brf_dword_800E1198 = 0x800C7648;
const int brf_dword_800E119C = 0x800C7708;
const int brf_dword_800E11A0 = 0x800C7708;
const int brf_dword_800E11A4 = 0x800C7708;
const int brf_dword_800E11A8 = 0x800C7708;
const int brf_dword_800E11AC = 0x800C7708;
const char brf_dword_800E11B0[] = {0x0, 0x0, 0x0, 0x0};
const int brf_dword_800E11B4 = 0x800C7D58;
const int brf_dword_800E11B8 = 0x800C7D64;
const int brf_dword_800E11BC = 0x800C7EC4;
const int brf_dword_800E11C0 = 0x800C7DA4;
const int brf_dword_800E11C4 = 0x800C7DF0;
const int brf_dword_800E11C8 = 0x800C7E0C;
const int brf_dword_800E11CC = 0x800C7E5C;
const int brf_dword_800E11D0 = 0x800C7E78;
const int brf_dword_800E11D4 = 0x800C7EC4;
const char brf_dword_800E11D8[] = {0x0, 0x0, 0x0, 0x0};
const int brf_dword_800E11DC = 0x800C8314;
const int brf_dword_800E11E0 = 0x800C8338;
const int brf_dword_800E11E4 = 0x800C8358;
const int brf_dword_800E11E8 = 0x800C83E8;
const int brf_dword_800E11EC = 0x800C8748;
const int brf_dword_800E11F0 = 0x800C8794;
const int brf_dword_800E11F4 = 0x800C8810;
const int brf_dword_800E11F8 = 0x800C888C;
const int brf_dword_800E11FC = 0x800C8910;
const int brf_dword_800E1200 = 0x800C895C;
const int brf_dword_800E1204 = 0x800C89CC;
const int brf_dword_800E1208 = 0x800C8A2C;
const int brf_dword_800E120C = 0x800C8AA8;
const int brf_dword_800E1210 = 0x800C8B20;
const int brf_dword_800E1214 = 0x800C8BD0;
const int brf_dword_800E1218 = 0x800C8C48;
const int brf_dword_800E121C = 0x800C8CC4;
const int brf_dword_800E1220 = 0x800C8D24;
const int brf_dword_800E1224 = 0x800C8D9C;
const int brf_dword_800E1228 = 0x800C8E30;
const int brf_dword_800E122C = 0x800C8EA8;
const int brf_dword_800E1230 = 0x800C8F20;
const int brf_dword_800E1234 = 0x800C8FD0;
const int brf_dword_800E1238 = 0x800C9038;
const int brf_dword_800E123C = 0x800C90E8;
const int brf_dword_800E1240 = 0x800C847C;
const int brf_dword_800E1244 = 0x800C918C;
const int brf_dword_800E1248 = 0x800C91B4;
const int brf_dword_800E124C = 0x800C924C;
const int brf_dword_800E1250 = 0x800C9404;
const int brf_dword_800E1254 = 0x800C9278;
const int brf_dword_800E1258 = 0x800C92A4;
const int brf_dword_800E125C = 0x800C92CC;
const int brf_dword_800E1260 = 0x800C93F0;
const int brf_dword_800E1264 = 0x800C9340;
const int brf_dword_800E1268 = 0x800C9374;
const int brf_dword_800E126C = 0x800C93F0;
const int brf_dword_800E1270 = 0x800C9314;
const char brf_dword_800E1274[] = {'i', 'n', 'i', 't'};
const char brf_dword_800E1278[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E127C[] = {'b', 'r', '_', 'b'};
const char brf_dword_800E1280[] = {'a', 'c', 'k', '_'};
const char brf_dword_800E1284[] = {'l', 0x0, 0x0, 0x0};
const char brf_dword_800E1288[] = {'b', 'r', '_', 'b'};
const char brf_dword_800E128C[] = {'a', 'c', 'k', '_'};
const char brf_dword_800E1290[] = {'r', 'u', 0x0, 0x0};
const char brf_dword_800E1294[] = {'b', 'r', '_', 'b'};
const char brf_dword_800E1298[] = {'r', 'f', 0x0, 0x0};
const char brf_dword_800E129C[] = {'b', 'r', '_', 'f'};
const char brf_dword_800E12A0[] = {'0', '0', 0x0, 0x0};
const char brf_dword_800E12A4[] = {'b', 'r', '_', 'f'};
const char brf_dword_800E12A8[] = {'0', '1', 0x0, 0x0};
const char brf_dword_800E12AC[] = {'b', 'r', '_', 'f'};
const char brf_dword_800E12B0[] = {'0', '2', 0x0, 0x0};
const char brf_dword_800E12B4[] = {'b', 'r', '_', 'f'};
const char brf_dword_800E12B8[] = {'0', '3', 0x0, 0x0};
const char brf_dword_800E12BC[] = {'b', 'r', '_', 'e'};
const char brf_dword_800E12C0[] = {'x', 'i', 't', 0x0};
const char brf_dword_800E12C4[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12C8[] = {'0', '0', 0x0, 0x0};
const char brf_dword_800E12CC[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12D0[] = {'0', '1', 0x0, 0x0};
const char brf_dword_800E12D4[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12D8[] = {'0', '2', 0x0, 0x0};
const char brf_dword_800E12DC[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12E0[] = {'0', '3', 0x0, 0x0};
const char brf_dword_800E12E4[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12E8[] = {'0', '4', 0x0, 0x0};
const char brf_dword_800E12EC[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12F0[] = {'0', '5', 0x0, 0x0};
const char brf_dword_800E12F4[] = {'b', 'r', '_', 's'};
const char brf_dword_800E12F8[] = {'0', '6', 0x0, 0x0};
const char brf_dword_800E12FC[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1300[] = {'0', '7', 0x0, 0x0};
const char brf_dword_800E1304[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1308[] = {'0', '8', 0x0, 0x0};
const char brf_dword_800E130C[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1310[] = {'0', '9', 0x0, 0x0};
const char brf_dword_800E1314[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1318[] = {'1', '0', 0x0, 0x0};
const char brf_dword_800E131C[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1320[] = {'1', '1', 0x0, 0x0};
const char brf_dword_800E1324[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1328[] = {'1', '2', 0x0, 0x0};
const char brf_dword_800E132C[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1330[] = {'1', '3', 0x0, 0x0};
const char brf_dword_800E1334[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1338[] = {'1', '4', 0x0, 0x0};
const char brf_dword_800E133C[] = {'b', 'r', '_', 's'};
const char brf_dword_800E1340[] = {'1', '5', 0x0, 0x0};
const char brf_dword_800E1344[] = {'b', 'r', '_', 'l'};
const char brf_dword_800E1348[] = {'i', 'n', 'e', '1'};
const char brf_dword_800E134C[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E1350[] = {'b', 'r', '_', 'l'};
const char brf_dword_800E1354[] = {'i', 'n', 'e', '2'};
const char brf_dword_800E1358[] = {0x0, 0x0, 0x0, 0x0};
const char brf_dword_800E135C[] = {'b', 'r', '_', 'b'};
const char brf_dword_800E1360[] = {'a', 'c', 'k', '_'};
const char brf_dword_800E1364[] = {'r', 'd', 0x0, 0x0};
const char brf_dword_800E1368[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E136C[] = {'l', 'u', 0x0, 0x0};
const char brf_dword_800E1370[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E1374[] = {'r', 'u', 0x0, 0x0};
const char brf_dword_800E1378[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E137C[] = {'l', 'd', 0x0, 0x0};
const char brf_dword_800E1380[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E1384[] = {'r', 'd', 0x0, 0x0};
const char brf_dword_800E1388[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E138C[] = {'u', 0x0, 0x0, 0x0};
const char brf_dword_800E1390[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E1394[] = {'d', 0x0, 0x0, 0x0};
const char brf_dword_800E1398[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E139C[] = {'l', 0x0, 0x0, 0x0};
const char brf_dword_800E13A0[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E13A4[] = {'r', 0x0, 0x0, 0x0};
const char brf_dword_800E13A8[] = {'c', 'u', 'r', '_'};
const char brf_dword_800E13AC[] = {'c', 0x0, 0x0, 0x0};
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C75F0.s")
void brf_800C62B0(Work *work, int x, int y, int w, int h, int a5, int a6);

void brf_800C7B28(Work *work, int arg)
{
    POLY_FT4 *p = work->field_780;
    int idx = work->field_74;
    int x0, x3, y0, y3;

    if (work->field_D0 < arg)
    {
        return;
    }
    x0 = p[idx].x0;
    x3 = p[idx].x3;
    y0 = p[idx].y0;
    y3 = p[idx].y3;
    brf_800C62B0(work, x0, y0, x3 - x0, y3 - y0, 0x80, 1);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7B94.s")
void brf_800C7F20(Work *work)
{
    work->field_2C[9] = 0;
    work->field_2C[10] = 0;
    work->field_2C[25] = 0;
    work->field_2C[26] = 0;
    work->field_2C[27] = 0;
    work->field_2C[28] = 0;
}
void brf_800C7F3C(Work *work)
{
    work->field_2C[9] = 1;
    if (work->field_80[0] == 1)
    {
        work->field_2C[10] = 1;
        work->field_2C[27] = 1;
        work->field_2C[28] = 1;
    }
    work->field_2C[25] = 1;
    work->field_2C[26] = 1;
}
void brf_800C7F6C(Work *work)
{
    work->field_2C[11] = 0;
    work->field_2C[12] = 0;
    work->field_2C[13] = 0;
    work->field_2C[14] = 0;
    work->field_2C[15] = 0;
    work->field_2C[29] = 0;
    work->field_2C[30] = 0;
    work->field_2C[31] = 0;
    work->field_2C[32] = 0;
    work->field_2C[39] = 0;
    work->field_2C[40] = 0;
}
void brf_800C7F9C(Work *work)
{
    work->field_2C[11] = 1;
    work->field_2C[13] = 1;
    work->field_2C[15] = 1;
    if (work->field_80[2] == 1)
    {
        work->field_2C[12] = 1;
        work->field_2C[29] = 1;
        work->field_2C[30] = 1;
    }
    if (work->field_80[4] == 1)
    {
        work->field_2C[14] = 1;
        work->field_2C[31] = 1;
        work->field_2C[32] = 1;
    }
    work->field_2C[39] = 1;
    work->field_2C[40] = 1;
}
void brf_800C7FF0(Work *work)
{
    work->field_2C[16] = 0;
    work->field_2C[17] = 0;
    work->field_2C[18] = 0;
    work->field_2C[19] = 0;
    work->field_2C[20] = 0;
    work->field_2C[21] = 0;
    work->field_2C[22] = 0;
    work->field_2C[23] = 0;
    work->field_2C[24] = 0;
    work->field_2C[33] = 0;
    work->field_2C[34] = 0;
    work->field_2C[35] = 0;
    work->field_2C[36] = 0;
    work->field_2C[37] = 0;
    work->field_2C[38] = 0;
    work->field_2C[41] = 0;
    work->field_2C[42] = 0;
}
void brf_800C8038(Work *work)
{
    work->field_2C[16] = 1;
    work->field_2C[17] = 1;
    work->field_2C[18] = 1;
    if (work->field_80[9] == 1)
    {
        work->field_2C[19] = 1;
        work->field_2C[33] = 1;
        work->field_2C[34] = 1;
    }
    work->field_2C[20] = 1;
    work->field_2C[21] = 1;
    if (work->field_80[12] == 1)
    {
        work->field_2C[22] = 1;
        work->field_2C[35] = 1;
        work->field_2C[36] = 1;
    }
    work->field_2C[23] = 1;
    if (work->field_80[14] == 1)
    {
        work->field_2C[24] = 1;
        work->field_2C[37] = 1;
        work->field_2C[38] = 1;
    }
    work->field_2C[41] = 1;
    work->field_2C[42] = 1;
}
void brf_800C80A8(Work *work)
{
    brf_800C7F20(work);
}
void brf_800C80C8(Work *work)
{
    brf_800C7F3C(work);
}
void brf_800C80E8(Work *work)
{
    brf_800C7FF0(work);
}
void brf_800C8108(Work *work)
{
    brf_800C8038(work);
}
void brf_800C8128(Work *work)
{
    brf_800C7F20(work);
    brf_800C7F9C(work);
}
void brf_800C8154(Work *work)
{
    brf_800C7F6C(work);
    brf_800C7F3C(work);
}
void brf_800C8180(Work *work)
{
    brf_800C7F6C(work);
    brf_800C8038(work);
}
void brf_800C81AC(Work *work)
{
    brf_800C7FF0(work);
    brf_800C7F9C(work);
}
void brf_800C81D8(Work *work)
{
    int i;
    int found;

    work->field_70 = 8;

    if (work->field_D4 == 0)
    {
        brf_800C6228(work, 0x11, 0x1F);
        return;
    }

    if (work->field_7C == 0)
    {
        found = 0;
        for (i = 0; i < 16; i++)
        {
            if (work->field_80[i] == 0)
            {
                found = 1;
            }
        }
        if (!found)
        {
            brf_800C6228(work, 0x12, 0x22);
            return;
        }
    }

    work->field_70 = 0x1D;
    GM_SeSet2(0, 0x3F, 0x21);
    brf_800C65C8(work);
    work->field_D0 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C829C.s")
void brf_800C95B4(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->field_780;
    dst = work->field_20->packs[GV_Clock];
    for (i = 0; i < 44; i++)
    {
        *dst = *src;
        *(unsigned short *)dst = work->field_2C[i] << 8;
        src++;
        dst++;
    }

    src = work->field_E60;
    dst = work->field_24->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        *(unsigned short *)dst = work->field_58[i] << 8;
        src++;
        dst++;
    }
}

void brf_800C829C(Work *work);
void brf_800C95B4(Work *work);

void brf_800C96DC(Work *work) // Act
{
    if (GV_PauseLevel != GV_PAUSE_READERROR)
    {
        brf_800C829C(work);
        brf_800C95B4(work);
        work->field_D0++;
    }
}

extern const char brf_dword_800E1274[];

void brf_800C972C(Work *work) // Die
{
    GM_FreePrim(work->field_20);
    GM_FreePrim(work->field_24);
    GV_InitResidentMemory();
    GV_InitCacheSystem();
    DG_ClearResidentTexture();
    GM_SetArea(GV_StrCode(brf_dword_800E1274), (char *)brf_dword_800E1274);
    GM_LoadRequest = 1;
}

void brf_800C97CC(int prim, POLY_FT4 *poly, int xl, int yt, int xr, int yb, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0x80, 0x80, 0x80);
    setXY4(poly, xl, yt, xr, yt, xl, yb, xr, yb);
    SetSemiTrans(poly, abe);
}
void brf_800C983C(int prim, int tex_id, POLY_FT4 *poly, int xl, int yt, int xr, int yb, int abe, int orient)
{
    DG_TEX *tex;

    brf_800C97CC(prim, poly, xl, yt, xr, yb, abe);
    tex = DG_GetTexture(tex_id);

    if (orient == 0)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w + 1;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h + 1;
        poly->u3 = u + w + 1;
        poly->v3 = v + h + 1;
    }
    else if (orient == 1)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w + 1;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h;
        poly->u3 = u + w + 1;
        poly->v3 = v + h;
    }
    else if (orient == 2)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h + 1;
        poly->u3 = u + w;
        poly->v3 = v + h + 1;
    }
    else if (orient == 3)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h;
        poly->u3 = u + w;
        poly->v3 = v + h;
    }
    else
    {
        return;
    }

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C99C0.s")
int brf_800C99C0(Work *work, int where); // GetResources

void *NewBriefingSelect(int name, int where)
{
    Work *work;

    GM_GameStatus |= (STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_PAUSE_OFF | STATE_RADIO_OFF);

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, brf_800C96DC, brf_800C972C, "b_select.c");
        if (brf_800C99C0(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
