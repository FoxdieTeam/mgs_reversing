#include "game/game.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

typedef struct
{
    const char *name;
    int         offset;
    int         size;
} BrfResource;

typedef struct
{
    short type; /* 0: vram files only, 1: vram and main memory files */
    short file;
} BrfLoad;

typedef struct
{
    u_char arg1;
    u_char arg2;
    u_char arg3;
    u_char arg5;
    short  arg6;
    short  arg7;
} BrfCountParam;

typedef struct _Work
{
    GV_ACT     actor;           /* 0x000 */
    DG_PRIM   *prim;            /* 0x020: polys */
    DG_PRIM   *prim2;           /* 0x024: polys2 */
    char       pad_28[0x4];     /* 0x028 */
    char       flags[44];       /* 0x02C: per-poly visibility of polys */
    char       flags2[9];       /* 0x058: per-poly visibility of polys2 */
    char       pad_61[0xF];     /* 0x061 */
    int        state;           /* 0x070 */
    int        prev_state;      /* 0x074 */
    char       pad_78[0x4];     /* 0x078 */
    int        field_7C;        /* 0x07C */
    int        viewed[16];      /* 0x080: 1 once the briefing item has been played */
    char       pad_C0[0xC];     /* 0x0C0 */
    int        index;           /* 0x0CC: selected briefing index */
    int        time;            /* 0x0D0: frames since the last state change */
    int        field_D4;        /* 0x0D4 */
    void      *graph;           /* 0x0D8: NewBriefingGraph() actor */
    void      *count;           /* 0x0DC: NewBriefingCount() actor */
    int        map;             /* 0x0E0 */
    char      *buf;             /* 0x0E4: loaded file (PACK_ADDR0) */
    char       name[0x40];      /* 0x0E8: name of the texture being set up */
    DG_TEX     textures[64];    /* 0x128 */
    int        tex_ids[64];     /* 0x428 */
    int        n_textures;      /* 0x528 */
    DG_IMAGE  *images[64];      /* 0x52C */
    int        image_ids[64];   /* 0x62C */
    int        n_images;        /* 0x72C */
    int        vox[19];         /* 0x730: voice stream per briefing index */
    int        field_77C;       /* 0x77C: brf_800C33E4[index] */
    POLY_FT4   polys[44];       /* 0x780 */
    POLY_FT4   polys2[9];       /* 0xE60 */
    char       pad_FC8[0xC];    /* 0xFC8 */
    int        field_FD4;       /* 0xFD4 */
    int        field_FD8;       /* 0xFD8: state before the transition */
    int        field_FDC;       /* 0xFDC */
    int        field_FE0;       /* 0xFE0 */
    char       pad_FE4[0x4];    /* 0xFE4 */
} Work;

void *NewBriefingGraph(int map, int n_textures, int *tex_ids, DG_TEX *textures, int index, int arg5, int n_images,
                       int *image_ids, DG_IMAGE **images);
void *NewBriefingCount(int map, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

/* used by brf_800C56C0 */
char *brf_800C3218 = (char *)0x801CD000;

/* "sNNv.dbl": textures loaded into VRAM (brf_800C5350) */
BrfResource brf_vram_files[19] = {
    {"s00v.dbl", 0x4B, 0x33215},
    {"s01v.dbl", 0xB2, 0x165E5},
    {"s02v.dbl", 0xDF, 0x1F785},
    {"s03v.dbl", 0x11E, 0x217FD},
    {"s04v.dbl", 0x161, 0x1D801},
    {"s05v.dbl", 0x19D, 0x2D185},
    {"s06v.dbl", 0x1F8, 0x2D505},
    {"s07v.dbl", 0x253, 0x16725},
    {"s08v.dbl", 0x294, 0x3BF55},
    {"s09v.dbl", 0x30C, 0x2B4A5},
    {"s10v.dbl", 0x37F, 0x424A9},
    {"s11v.dbl", 0x418, 0x3BF55},
    {"s12v.dbl", 0x490, 0x455C9},
    {"s13v.dbl", 0x529, 0x334F5},
    {"s14v.dbl", 0x590, 0x3CAFD},
    {"s15v.dbl", 0x65E, 0x3BB61},
    {"s16v.dbl", 0x743, 0x2D715},
    {"s17v.dbl", 0x7C0, 0x398D5},
    {"s18v.dbl", 0x834, 0x14C5},
};

/* "sNNc.dbl": textures kept in main memory (brf_800C53E4) */
BrfResource brf_main_files[19] = {
    {"s00c.dbl", 0x0, 0x254D9},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"tmp.dbl", 0x0, 0x0},
    {"s08c.dbl", 0x280, 0x9811},
    {"tmp.dbl", 0x0, 0x0},
    {"s10c.dbl", 0x363, 0xDFC9},
    {"s11c.dbl", 0x404, 0x9811},
    {"tmp.dbl", 0x0, 0x0},
    {"s13c.dbl", 0x51B, 0x6CB5},
    {"tmp.dbl", 0x0, 0x0},
    {"s15c.dbl", 0x60A, 0x29D59},
    {"s16c.dbl", 0x6D6, 0x3632D},
    {"s17c.dbl", 0x79E, 0x10AB1},
    {"tmp.dbl", 0x0, 0x0},
};

/* per briefing index, passed to NewBriefingGraph/NewBriefingCount */
int brf_800C33E4[19] = {
    0xA16, 0x2C7, 0x933, 0x59C, 0x505, 0x9F1, 0x913, 0x4E1, 0x819, 0xBF3, 0x975, 0x3C0, 0xB60, 0x93E, 0x7D5, 0xC6E, 0x12FF, 0xD5A, 0x267,
};

/* files to load for the menu states 9.. (brf_800C600C) */
BrfLoad brf_load_table[16] = {
    {1, 0x0},
    {0, 0x1},
    {0, 0x2},
    {0, 0x3},
    {0, 0x4},
    {0, 0x5},
    {0, 0x6},
    {0, 0x7},
    {1, 0x8},
    {0, 0x9},
    {1, 0xA},
    {1, 0xB},
    {0, 0xC},
    {1, 0xD},
    {0, 0xE},
    {1, 0xF},
};

/* NewBriefingCount() parameters per briefing index */
BrfCountParam brf_count_params[19] = {
    {0x0, 0x2, 0x31, 0x1, 0, 0},
    {0x0, 0x9, 0x11, 0x1, 0, 0},
    {0x0, 0x9, 0x29, 0x1, 1, 0},
    {0x0, 0xB, 0x1, 0x1, 1, 0},
    {0x0, 0x14, 0x16, 0x1, 0, 0},
    {0x0, 0x15, 0x5, 0x1, 0, 0},
    {0x0, 0x16, 0x20, 0x1, 0, 0},
    {0x0, 0x4, 0x12, 0x1, 0, 0},
    {0x0, 0x4, 0x3B, 0x1, 1, 1},
    {0x0, 0x6, 0x9, 0x1, 0, 0},
    {0x0, 0x7, 0x36, 0x1, 0, 0},
    {0x0, 0xB, 0x31, 0x1, 1, 1},
    {0x0, 0xC, 0x15, 0x1, 0, 0},
    {0x0, 0xE, 0x1, 0x1, 0, 0},
    {0x0, 0xF, 0x16, 0x1, 0, 0},
    {0x0, 0x10, 0x22, 0x1, 0, 0},
    {0x0, 0x0, 0x0, 0x1, 0, 0},
    {0x0, 0x12, 0x18, 0x1, 0, 0},
    {0x0, 0x17, 0x27, 0x0, 0, 0},
};

void brf_800C5230(Work *work)
{
    BrfCountParam stage;
    int           idx;
    int           f0, f1, f2, f3, f4, f6;

    idx = work->index;
    stage = brf_count_params[idx];
    f0 = stage.arg1;
    f1 = stage.arg2;
    f2 = stage.arg3;
    f3 = stage.arg5;
    f4 = stage.arg6;
    f6 = stage.arg7;
    work->field_77C = brf_800C33E4[idx];
    work->graph = NewBriefingGraph(work->map, work->n_textures, work->tex_ids, work->textures, idx, work->field_77C,
                                   work->n_images, work->image_ids, work->images);
    work->count = NewBriefingCount(work->map, f0, f1, f2, work->field_77C - 100, f3, f4, f6);
}

void brf_800C5350(Work *work, int idx)
{
    BrfResource *table = brf_vram_files;
    BrfResource *e = &table[idx];

    printf("Briefing Texture Load_Start %s\n", e->name);
    work->buf = PACK_ADDR0;
    FS_LoadFileRequest(FS_FILE_BRF, e->offset, e->size, PACK_ADDR0);
    while (FS_LoadFileSync() > 0)
    {
        mts_wait_vbl(1);
    }
}

void brf_800C53E4(Work *work, int idx)
{
    BrfResource *table = brf_main_files;
    BrfResource *e = &table[idx];

    printf("Briefing Texture Load_Start %s\n", e->name);
    work->buf = PACK_ADDR0;
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

    work->tex_ids[work->n_textures] = id;
    n = work->n_textures;
    work->n_textures = n + 1;
    tex = &work->textures[n];

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

void brf_800C5584(Work *work, int id, int tp, int abr, RECT *img, RECT *pal, int col, DG_IMAGE *image)
{
    DG_TEX *tex;
    int     n;
    int     x, y, w, h;
    int     cx, cy;
    int     tpage;

    work->image_ids[work->n_images] = id;
    work->images[work->n_images] = image;
    work->n_images++;
    work->tex_ids[work->n_textures] = id;
    n = work->n_textures;
    work->n_textures = n + 1;
    tex = &work->textures[n];

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
/* used by brf_800C5A68 */
const char brf_dword_800E10A8[44] = "Cannot Alloc Expansion Memory! size = %d\n";

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C56C0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5A68.s")
void brf_800C56C0(Work *work, void *data, int cache_id);

void brf_800C5DE4(Work *work)
{
    char *p = work->buf;
    int count = *(int *)p;
    char *dst;
    char c;
    int n;

    p += 4;
    do
    {
        c = *p++;
        work->name[0] = c;
        dst = &work->name[1];
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
        brf_800C56C0(work, p, GV_CacheID3(work->name));
        count--;
        n++;
        p += n;
    } while (count > 0);
    printf("Briefing Texture VRAM Set_Finish!\n");
}
void brf_800C5A68(Work *work, void *data, int cache_id);

void brf_800C5EAC(Work *work)
{
    char *p = work->buf;
    int count = *(int *)p;
    char *dst;
    char c;
    int n;

    p += 4;
    do
    {
        c = *p++;
        work->name[0] = c;
        dst = &work->name[1];
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
        brf_800C5A68(work, p, GV_CacheID3(work->name));
        count--;
        n++;
        p += n;
    } while (count > 0);
    printf("Briefing Texture MainMemory Load_Finish!\n");
}
void brf_800C5F74(Work *work)
{
    int i;

    work->n_textures = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->tex_ids[i] = 0;
    }

    work->n_images = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->image_ids[i] = 0;
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

void brf_800C600C(Work *work)
{
    int idx = work->state - 9;
    BrfLoad e = brf_load_table[idx];
    int arg = e.file;

    if (e.type == 0)
    {
        brf_800C5FB4(work, arg);
    }
    else if (e.type == 1)
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

    switch (work->state)
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
                if (work->viewed[i] == 0)
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
    GM_VoxStream(work->vox[a1], 0x40000000);
    work->prev_state = work->state;
    work->state = a2;
    work->time = 0;
    work->index = a1;
    GM_SetSound(0x01FFFF0B, 0);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C62B0.s")
void brf_800C65C8(Work *work)
{
    int i = 8;
    char *p = (char *)work + i; /* &work->flags2[i] - 0x58, the indexed loop doesn't match */

    for (; i >= 0; i--, p--)
    {
        p[0x58] = 0;
    }
}
void brf_800C65E8(Work *work)
{
    int i = 0x2B;
    char *p = (char *)work + i; /* &work->flags[i] - 0x2C, the indexed loop doesn't match */

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
    POLY_FT4 *poly = work->polys;
    int i;

    for (i = 0; i < 16; i++)
    {
        if (work->viewed[i] == 1)
        {
            poly[i + 9].r0 = 0x46;
            poly[i + 9].g0 = 0x50;
            poly[i + 9].b0 = 0x4B;
        }
    }

    if (work->viewed[1] == 1)
    {
        poly[27].r0 = 0x46; poly[27].g0 = 0x50; poly[27].b0 = 0x4B;
        poly[28].r0 = 0x46; poly[28].g0 = 0x50; poly[28].b0 = 0x4B;
    }
    if (work->viewed[3] == 1)
    {
        poly[29].r0 = 0x46; poly[29].g0 = 0x50; poly[29].b0 = 0x4B;
        poly[30].r0 = 0x46; poly[30].g0 = 0x50; poly[30].b0 = 0x4B;
    }
    if (work->viewed[5] == 1)
    {
        poly[31].r0 = 0x46; poly[31].g0 = 0x50; poly[31].b0 = 0x4B;
        poly[32].r0 = 0x46; poly[32].g0 = 0x50; poly[32].b0 = 0x4B;
    }
    if (work->viewed[10] == 1)
    {
        poly[33].r0 = 0x46; poly[33].g0 = 0x50; poly[33].b0 = 0x4B;
        poly[34].r0 = 0x46; poly[34].g0 = 0x50; poly[34].b0 = 0x4B;
    }
    if (work->viewed[13] == 1)
    {
        poly[35].r0 = 0x46; poly[35].g0 = 0x50; poly[35].b0 = 0x4B;
        poly[36].r0 = 0x46; poly[36].g0 = 0x50; poly[36].b0 = 0x4B;
    }
    if (work->viewed[15] == 1)
    {
        poly[37].r0 = 0x46; poly[37].g0 = 0x50; poly[37].b0 = 0x4B;
        poly[38].r0 = 0x46; poly[38].g0 = 0x50; poly[38].b0 = 0x4B;
    }
    if (work->viewed[0] == 1 && work->viewed[1] == 1)
    {
        poly[5].r0 = 0x46;
        poly[5].g0 = 0x50;
        poly[5].b0 = 0x4B;
    }
    if (work->viewed[2] == 1 && work->viewed[3] == 1 && work->viewed[4] == 1 &&
        work->viewed[5] == 1 && work->viewed[6] == 1)
    {
        poly[6].r0 = 0x46;
        poly[6].g0 = 0x50;
        poly[6].b0 = 0x4B;
    }
    if (work->viewed[7] == 1 && work->viewed[8] == 1 && work->viewed[9] == 1 &&
        work->viewed[10] == 1 && work->viewed[11] == 1 && work->viewed[12] == 1 &&
        work->viewed[13] == 1 && work->viewed[14] == 1 && work->viewed[15] == 1)
    {
        poly[7].r0 = 0x46;
        poly[7].g0 = 0x50;
        poly[7].b0 = 0x4B;
    }
}
void brf_800C68EC(Work *work, int a1, int a2, int a3)
{
    work->field_FD8 = work->state;
    work->field_FD4 = a1;
    work->field_FDC = a2;
    work->state = a2;
    work->time = 0;
    work->field_FE0 = a3;
    GM_SeSet2(0, 0x3F, 0x1F);
}
void brf_800C6930(Work *work, int idx1, int idx2, int base_y)
{
    POLY_FT4 *p = work->polys;
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
    POLY_FT4 *p = work->polys;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int color;

    if (d < lo) return;
    if (hi < d) return;

    work->flags[0] = 3;
    work->flags[1] = 3;
    work->flags[43] = 3;

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
    POLY_FT4 *p = work->polys;
    int d = work->time;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int diff;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->flags[4] = 1;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->flags[5] = 1;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->flags[6] = 1;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->flags[7] = 1;
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
    POLY_FT4 *p = work->polys;
    int d = work->time;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->flags[8] = 1;
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

void brf_800C731C(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->polys;
    int d = work->time;
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
    switch (work->prev_state)
    {
    case 5:
    case 9:
    case 10:
        work->flags[25] = 1;
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
        work->flags[39] = 1;
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
        work->flags[41] = 1;
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
void brf_800C7488(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->polys;
    int d = work->time;
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
    switch (work->prev_state)
    {
    case 5:
    case 9:
    case 10:
        work->flags[26] = 1;
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
        work->flags[40] = 1;
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
        work->flags[42] = 1;
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
/* jump table of brf_800C75F0 */
const int brf_jt_800E1184[11] __attribute__((aligned(8))) = {
    0x800C7648, 0x800C7878, 0x800C7878, 0x800C7878, 0x800C7648, 0x800C7648,
    0x800C7708, 0x800C7708, 0x800C7708, 0x800C7708, 0x800C7708,
};
/* jump table of brf_800C7B94 */
const int brf_jt_800E11B4[9] __attribute__((aligned(8))) = {
    0x800C7D58, 0x800C7D64, 0x800C7EC4, 0x800C7DA4, 0x800C7DF0, 0x800C7E0C,
    0x800C7E5C, 0x800C7E78, 0x800C7EC4,
};
/* jump table of brf_800C829C */
const int brf_jt_800E11DC[38] __attribute__((aligned(8))) = {
    0x800C8314, 0x800C8338, 0x800C8358, 0x800C83E8, 0x800C8748, 0x800C8794,
    0x800C8810, 0x800C888C, 0x800C8910, 0x800C895C, 0x800C89CC, 0x800C8A2C,
    0x800C8AA8, 0x800C8B20, 0x800C8BD0, 0x800C8C48, 0x800C8CC4, 0x800C8D24,
    0x800C8D9C, 0x800C8E30, 0x800C8EA8, 0x800C8F20, 0x800C8FD0, 0x800C9038,
    0x800C90E8, 0x800C847C, 0x800C918C, 0x800C91B4, 0x800C924C, 0x800C9404,
    0x800C9278, 0x800C92A4, 0x800C92CC, 0x800C93F0, 0x800C9340, 0x800C9374,
    0x800C93F0, 0x800C9314,
};
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C75F0.s")
void brf_800C62B0(Work *work, int x, int y, int w, int h, int a5, int a6);

void brf_800C7B28(Work *work, int arg)
{
    POLY_FT4 *p = work->polys;
    int idx = work->prev_state;
    int x0, x3, y0, y3;

    if (work->time < arg)
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
    work->flags[9] = 0;
    work->flags[10] = 0;
    work->flags[25] = 0;
    work->flags[26] = 0;
    work->flags[27] = 0;
    work->flags[28] = 0;
}
void brf_800C7F3C(Work *work)
{
    work->flags[9] = 1;
    if (work->viewed[0] == 1)
    {
        work->flags[10] = 1;
        work->flags[27] = 1;
        work->flags[28] = 1;
    }
    work->flags[25] = 1;
    work->flags[26] = 1;
}
void brf_800C7F6C(Work *work)
{
    work->flags[11] = 0;
    work->flags[12] = 0;
    work->flags[13] = 0;
    work->flags[14] = 0;
    work->flags[15] = 0;
    work->flags[29] = 0;
    work->flags[30] = 0;
    work->flags[31] = 0;
    work->flags[32] = 0;
    work->flags[39] = 0;
    work->flags[40] = 0;
}
void brf_800C7F9C(Work *work)
{
    work->flags[11] = 1;
    work->flags[13] = 1;
    work->flags[15] = 1;
    if (work->viewed[2] == 1)
    {
        work->flags[12] = 1;
        work->flags[29] = 1;
        work->flags[30] = 1;
    }
    if (work->viewed[4] == 1)
    {
        work->flags[14] = 1;
        work->flags[31] = 1;
        work->flags[32] = 1;
    }
    work->flags[39] = 1;
    work->flags[40] = 1;
}
void brf_800C7FF0(Work *work)
{
    work->flags[16] = 0;
    work->flags[17] = 0;
    work->flags[18] = 0;
    work->flags[19] = 0;
    work->flags[20] = 0;
    work->flags[21] = 0;
    work->flags[22] = 0;
    work->flags[23] = 0;
    work->flags[24] = 0;
    work->flags[33] = 0;
    work->flags[34] = 0;
    work->flags[35] = 0;
    work->flags[36] = 0;
    work->flags[37] = 0;
    work->flags[38] = 0;
    work->flags[41] = 0;
    work->flags[42] = 0;
}
void brf_800C8038(Work *work)
{
    work->flags[16] = 1;
    work->flags[17] = 1;
    work->flags[18] = 1;
    if (work->viewed[9] == 1)
    {
        work->flags[19] = 1;
        work->flags[33] = 1;
        work->flags[34] = 1;
    }
    work->flags[20] = 1;
    work->flags[21] = 1;
    if (work->viewed[12] == 1)
    {
        work->flags[22] = 1;
        work->flags[35] = 1;
        work->flags[36] = 1;
    }
    work->flags[23] = 1;
    if (work->viewed[14] == 1)
    {
        work->flags[24] = 1;
        work->flags[37] = 1;
        work->flags[38] = 1;
    }
    work->flags[41] = 1;
    work->flags[42] = 1;
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

    work->state = 8;

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
            if (work->viewed[i] == 0)
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

    work->state = 0x1D;
    GM_SeSet2(0, 0x3F, 0x21);
    brf_800C65C8(work);
    work->time = 0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C829C.s")
void brf_800C95B4(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->polys;
    dst = work->prim->packs[GV_Clock];
    for (i = 0; i < 44; i++)
    {
        *dst = *src;
        SSTOREL(work->flags[i] << 8, dst);
        src++;
        dst++;
    }

    src = work->polys2;
    dst = work->prim2->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        SSTOREL(work->flags2[i] << 8, dst);
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
        work->time++;
    }
}

void brf_800C972C(Work *work) // Die
{
    GM_FreePrim(work->prim);
    GM_FreePrim(work->prim2);
    GV_InitResidentMemory();
    GV_InitCacheSystem();
    DG_ClearResidentTexture();
    GM_SetArea(GV_StrCode("init"), "init");
    GM_LoadRequest = 1;
}

/* texture names used by brf_800C99C0 */
const char brf_dword_800E127C[12] = "br_back_l";
const char brf_dword_800E1288[12] = "br_back_ru";
const char brf_dword_800E1294[8] = "br_brf";
const char brf_dword_800E129C[8] = "br_f00";
const char brf_dword_800E12A4[8] = "br_f01";
const char brf_dword_800E12AC[8] = "br_f02";
const char brf_dword_800E12B4[8] = "br_f03";
const char brf_dword_800E12BC[8] = "br_exit";
const char brf_dword_800E12C4[8] = "br_s00";
const char brf_dword_800E12CC[8] = "br_s01";
const char brf_dword_800E12D4[8] = "br_s02";
const char brf_dword_800E12DC[8] = "br_s03";
const char brf_dword_800E12E4[8] = "br_s04";
const char brf_dword_800E12EC[8] = "br_s05";
const char brf_dword_800E12F4[8] = "br_s06";
const char brf_dword_800E12FC[8] = "br_s07";
const char brf_dword_800E1304[8] = "br_s08";
const char brf_dword_800E130C[8] = "br_s09";
const char brf_dword_800E1314[8] = "br_s10";
const char brf_dword_800E131C[8] = "br_s11";
const char brf_dword_800E1324[8] = "br_s12";
const char brf_dword_800E132C[8] = "br_s13";
const char brf_dword_800E1334[8] = "br_s14";
const char brf_dword_800E133C[8] = "br_s15";
const char brf_dword_800E1344[12] = "br_line1";
const char brf_dword_800E1350[12] = "br_line2";
const char brf_dword_800E135C[12] = "br_back_rd";
const char brf_dword_800E1368[8] = "cur_lu";
const char brf_dword_800E1370[8] = "cur_ru";
const char brf_dword_800E1378[8] = "cur_ld";
const char brf_dword_800E1380[8] = "cur_rd";
const char brf_dword_800E1388[8] = "cur_u";
const char brf_dword_800E1390[8] = "cur_d";
const char brf_dword_800E1398[8] = "cur_l";
const char brf_dword_800E13A0[8] = "cur_r";
const char brf_dword_800E13A8[8] = "cur_c";

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
