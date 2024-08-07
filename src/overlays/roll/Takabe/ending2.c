#include "common.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "SD/sd.h"
#include "Takabe/thing.h"

typedef struct Ending2Pair
{
    short tpage1;
    short tpage2;
} Ending2Pair;

typedef struct Ending2Prims
{
    DR_TPAGE    tpages[4];
    SPRT        field_20[120];
    char        pad980[0x320]; // maybe the previous array is actually larger than needed?
    Ending2Pair field_CA0[3];
    POLY_FT4    field_CAC[40];
    char        pad12EC[0x640]; // maybe the previous array is actually larger than needed?
} Ending2Prims;

typedef struct Ending2Work
{
    GV_ACT       actor;
    int          field_20;
    int          field_24;
    int          field_28;
    int          field_2C;
    int          field_30;
    int          field_34;
    int          field_38;
    int          field_3C;
    int          field_40;
    int          field_44;
    int          field_48;
    int          field_4C;
    short       *field_50; // FIXME: figure out this type
    int         *field_54; // FIXME: figure out this type
    int         *field_58; // FIXME: figure out this type
    int          field_5C;
    int          field_60;
    Ending2Prims field_64[2];
    DISPENV      field_325C;
} Ending2Work;

#define EXEC_LEVEL 5

extern int DG_FrameRate_8009D45C;
extern int DG_UnDrawFrameCount_800AB380;
extern int GV_Clock_800AB920;

// Similar in usage to struct in movie.c
// (but different order of fields)
typedef struct _Ending2MovieWork
{
    int            field_0; // 0
    FS_MOVIE_FILE *file;    // 4
    RECT           rect;
    volatile int   field_10; // (f2C in movie.c)
    int            field_14;
    int            field_18;
    int            field_1C;
    int            field_20;
    int            field_24;
    short          width;        // 28
    short          height;       // 2A
    short          field_2C;     // 2C (f38 in movie.c)
    short          dctin_index;  // 2E
    short          dctout_index; // 30
    short          n_frames;     // 32
    void          *vlc;          // 34
    void          *ring;         // 38
    void          *dctin[2];     // 3C
    void          *dctout[2];    // 44
} Ending2MovieWork;

int roll_dword_800C3244 = 0x00FF0000;
int roll_dword_800C3248 = 0x00010010;

RECT ending2_orig_image_rect_800C324C = {640, 0, 320, 1};
RECT moviework_rects_800C3254[3] = {{0, 320, 320, 160}, {320, 320, 320, 160}, {640, 320, 320, 160}};

Ending2MovieWork moviework_800C326C = {0};

int roll_dword_800C32B8 = 0x00000140;
int roll_dword_800C32BC[1] = {0x00000267}; // unknown how large
int roll_dword_800C32C0 = 0x00000633;
int roll_dword_800C32C4 = 0x000008DB;
int roll_dword_800C32C8 = 0x00000E1A;
int roll_dword_800C32CC = 0x00001278;
int roll_dword_800C32D0 = 0x0000158D;
int roll_dword_800C32D4 = 0x00001AD2;
int roll_dword_800C32D8 = 0x00001D50;
int roll_dword_800C32DC = 0x00002331;
int roll_dword_800C32E0 = 0x000026B4;
int roll_dword_800C32E4 = 0x00002A8C;
int roll_dword_800C32E8 = 0x00002CB9;
int roll_dword_800C32EC = 0x00002F35;
int roll_dword_800C32F0 = 0x00003174;
int roll_dword_800C32F4 = 0x00003360;
int roll_dword_800C32F8 = 0x000037F4;
int roll_dword_800C32FC = 0x00003B9A;
int roll_dword_800C3300 = 0x00003D6B;
int roll_dword_800C3304 = 0x00003EFB;
int roll_dword_800C3308 = 0x00004104;
int roll_dword_800C330C = 0x000045CE;
int roll_dword_800C3310 = 0x000048BC;
int roll_dword_800C3314 = 0x00004A2D;
int roll_dword_800C3318 = 0x00004BA6;
int roll_dword_800C331C = 0x00004D11;
int roll_dword_800C3320 = 0xFFFFFFFF;

int SECTION("overlay.bss") start_800C9EC0;

int SECTION("overlay.bss") roll_dword_800C9EC4;
int SECTION("overlay.bss") roll_dword_800C9EC8;
int SECTION("overlay.bss") roll_dword_800C9ECC;

RECT SECTION("overlay.bss") ending2_image_rects_800C9ED0[2];
RECT SECTION("overlay.bss") ending2_800C9EE0[2][8];

int SECTION("overlay.bss") stack_800C9F60[0x100];

int SECTION("overlay.bss") roll_dword_800CA360;
int SECTION("overlay.bss") roll_dword_800CA364;
int SECTION("overlay.bss") roll_dword_800CA368;
int SECTION("overlay.bss") roll_dword_800CA36C;

u_short SECTION("overlay.bss") ending2_image_800CA370[5120];

char * roll_ending2_800C5DC0(char *dst, char *src, int count)
{
    int   i, j;
    char  flag;
    int   len;
    char *bptr;

    for (i = 0; i < count; i += len)
    {
        flag = *src & 0x80;
        len = *src & 0x7F;
        src++;

        if (flag)
        {
            bptr = dst - *src++;
            for (j = 0; j < len; j++)
            {
                *dst++ = *bptr++;
            }
        }
        else
        {
            for (j = 0; j < len; j++)
            {
                *dst++ = *src++;
            }
        }
    }

    return src;
}

char * roll_ending2_800C5E54(char *dst, char *src, int count)
{
    int i;

    if (*src++ & 0xC0)
    {
        for (i = 0; i < count; i++)
        {
            *dst++ = 0;
        }

        return src;
    }

    return roll_ending2_800C5DC0(dst, src, count);
}

void roll_ending2_800C5EAC(short *dst, char *indices, short *src, int count)
{
    int i;
    int index;

    for (i = 0; i < count; i += 2)
    {
        index = *indices++;
        *dst++ = src[index & 0xF];
        *dst++ = src[index >> 4];
    }
}

static inline void MovieIntToPos(int i, CdlLOC *p)
{
    int temp;

    temp = i / 75;

    p->sector = itob(i % 75);
    p->second = itob(temp % 60);
    p->minute = itob(temp / 60);
}

// Identical to Movie_800C4484
void Ending2Movie_800C5F00(int pos)
{
    CdlLOC loc;

    do
    {
        MovieIntToPos(pos, &loc);
        while (CdControl(CdlSetloc, (u_char *)&loc, NULL) == 0)
            ;
    } while (CdRead2(CdlModeStream2 | CdlModeSpeed | CdlModeRT) == 0);
}

// Based on Movie_800C45F4
int Ending2Movie_800C6070()
{
    u_long           *addr;
    StHEADER         *header;
    u_short           type;
    int               ret;
    Ending2MovieWork *moviework;

    moviework = &moviework_800C326C;

    ret = -1;
    start_800C9EC0 = VSync(-1);
    while (StGetNext(&addr, (u_long **)&header) != 0)
    {
        if ((VSync(-1) - start_800C9EC0) > 300)
        {
            return 0;
        }
    }

    type = header->type;

    if (type == 0x8001)
    {
        moviework->n_frames = header->frameCount;

        if (header->frameCount < (moviework->file->field_2_frame - 1))
        {
            moviework->width = header->width;
            moviework->height = header->height;

            moviework->dctin_index = 1 - moviework->dctin_index;

            DecDCTvlc2(addr, moviework->dctin[moviework->dctin_index], moviework->vlc);
            ret = 1;
        }
        else
        {
            return 0;
        }
    }

    StFreeRing(addr);
    return ret;
}

// Nearly identical to Movie_800C47E8
void Ending2Movie_800C6184(void)
{
    u_long           *breakdraw;
    Ending2MovieWork *moviework;

    moviework = &moviework_800C326C;

    moviework->rect.x += 16;
    breakdraw = BreakDraw();
    LoadImage(&moviework->rect, moviework->dctout[moviework->dctout_index]);

    if (breakdraw && breakdraw != (u_long *)-1)
    {
        DrawOTag(breakdraw);
    }

    moviework->dctout_index = 1 - moviework->dctout_index;

    if (moviework->rect.x < moviework->field_2C)
    {
        DecDCTout(moviework->dctout[moviework->dctout_index], moviework->height * 8);
        return;
    }

    moviework->field_10 = 1;
}

void Ending2Movie_800C6240(void)
{
    char pad[8];
    int  status;

    Ending2MovieWork *moviework;
    RECT             *rect;

    moviework = &moviework_800C326C;

    mts_set_vsync_task_800892B8();

    moviework->dctin_index = 0;
    moviework->dctout_index = 0;
    moviework->field_14 = 0;
    moviework->field_18 = 2;

    do
    {
        status = Ending2Movie_800C6070();
    } while (status < 0);

    if (status == 0)
    {
        stop_xa_sd_800888B4();
        moviework_800C326C.field_0 = -1;
        return;
    }

    moviework_800C326C.field_24 = mts_get_tick_count_8008BBB0();
    moviework_800C326C.field_0 = 2;
    moviework->field_10 = 1;

    rect = &moviework->rect;

    while (1)
    {
        moviework->rect = moviework_rects_800C3254[moviework->field_14];
        moviework->rect.x -= 16;
        rect->w = 16;
        rect->h = __min(moviework->height, 160);
        moviework->field_2C = moviework->rect.x + moviework->width;
        if (moviework_800C326C.field_1C != 0)
        {
            moviework->field_10 = 0;

            DecDCTout(moviework->dctout[moviework->dctout_index], moviework->height * 8);
            DecDCTin(moviework->dctin[moviework->dctin_index], 2);

            do
            {
                status = Ending2Movie_800C6070();
            } while (status < 0);

            while (moviework->field_10 == 0)
            {
                DecDCToutSync(0);
            }
        }
        else
        {
            status = 1;
        }

        if (status == 0 || moviework->field_20 != 0)
        {
            stop_xa_sd_800888B4();
            moviework_800C326C.field_0 = -1;
            mts_8008B51C();
        }

        moviework->field_18 = moviework->field_14;
        moviework->field_14++;

        if (moviework->field_14 >= 3)
        {
            moviework->field_14 = 0;
        }
    }
}

void Ending2Movie_800C6460(void)
{
    int i;

    if (moviework_800C326C.field_10-- > 0)
    {
        DG_FreeObjectQueue_800183D4();
        return;
    }

    start_xa_sd_80088868();

    GV_ResetPacketMemory_80014BD8();
    GV_AllocMemory2_80015ED8(0, 0x11000, &moviework_800C326C.vlc);
    GV_AllocMemory2_80015ED8(0, 0x10000, &moviework_800C326C.ring);

    for (i = 0; i < 2; i++)
    {
        GV_AllocMemory2_80015ED8(1, 0x17800, &moviework_800C326C.dctin[i]);
        GV_AllocMemory2_80015ED8(0, 0x1E00, &moviework_800C326C.dctout[i]);
    }

    DecDCTReset(0);
    DecDCToutCallback(&Ending2Movie_800C6184);

    StSetRing(moviework_800C326C.ring, 32);
    StSetStream(0, 0, 0xFFFFFFFF, NULL, NULL);

    DecDCTvlcBuild(moviework_800C326C.vlc);

    Ending2Movie_800C5F00(moviework_800C326C.file->field_4_pos);

    moviework_800C326C.field_0 = 1;
    moviework_800C326C.field_1C = 0;
    moviework_800C326C.field_20 = 0;

    mts_set_stack_check_8008B648(6, mts_stack_end(stack_800C9F60), sizeof(stack_800C9F60));
    mts_sta_tsk_8008B47C(6, Ending2Movie_800C6240, mts_stack_end(stack_800C9F60));
}

void Ending2_800C65C4(Ending2Work *work)
{
    while (mts_get_task_status_8008B618(6) != 0)
    {
        moviework_800C326C.field_20 = 1;
        mts_wait_vbl_800895F4(1);
    }
    DecDCToutCallback(0);
    StUnSetRing();
    CdControlB(9, NULL, NULL);
    GV_ResetPacketMemory_80014BD8();
    DG_ResetObjectQueue_8001844C();
    moviework_800C326C.file = NULL;
    DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
}

void Ending2_800C665C(int movieId)
{
    FS_MOVIE_FILE *file;

    if (moviework_800C326C.file == NULL)
    {
        GV_ZeroMemory_8001619C(&moviework_800C326C, sizeof(Ending2MovieWork));
        printf("MOVIE %d\n", movieId);
        file = FS_GetMovieInfo_8002399C(movieId);
        if (file == NULL)
        {
            printf("NOT FOUND\n");
            return;
        }
        moviework_800C326C.field_0 = 0;
        moviework_800C326C.file = file;
        moviework_800C326C.field_10 = 1;
    }
}

void Ending2_800C66EC(Ending2Work *work)
{
    if (work->field_40 == 0)
    {
        Ending2Movie_800C6460();
    }
    else
    {
        GM_VoxStream_80037E40(work->field_4C, 0x40000000);
        moviework_800C326C.field_0 = 1;
    }
}

void Ending2_800C673C(Ending2Work *work)
{
    if (work->field_40 == 0)
    {
        Ending2_800C65C4(work);
    }
    else
    {
        GM_StreamPlayStop_80037D64();
    }
}

int Ending2_800C677C(Ending2Work *work)
{
    int status;

    if (work->field_40 != 0)
    {
        status = GM_StreamStatus_80037CD8();
        switch (moviework_800C326C.field_0)
        {
        case 1:
            if (status == 1)
            {
                GM_StreamPlayStart_80037D1C();
                moviework_800C326C.field_0 = 2;
            }
            break;

        case 2:
            if (status == -1)
            {
                moviework_800C326C.field_0 = status;
            }
            break;

        case 0:
            break;
        }
    }

    return moviework_800C326C.field_0;
}

int * roll_ending2_800C6814(void *arg0, void *arg1, int arg2)
{
    return (int *)roll_ending2_800C5E54(arg0, arg1, arg2);
}

void roll_ending2_800C6834(u_short *arg0, void *arg1, void *arg2, int arg3)
{
    return roll_ending2_800C5EAC(arg0, arg1, arg2, arg3);
}

void roll_ending2_800C6854(u_short *dst, char *indices, u_short *src, int count)
{
    char   *indices2;
    int     i;
    int     index0, index1;
    u_short a, b;
    u_short res;

    indices2 = indices + 256;
    for (i = 0; i < count; i += 2)
    {
        index0 = *indices++;
        index1 = *indices2++;

        a = src[index0 & 0xF];
        b = src[index1 & 0xF];

        res = a & b;
        res |= (a | b) & 0x8000;
        a ^= b;
        res += (a >> 1) & 0xBDEF;
        *dst++ = res;

        a = src[index0 >> 4];
        b = src[index1 >> 4];

        res = a & b;
        res |= (a | b) & 0x8000;
        a ^= b;
        res += (a >> 1) & 0x3DEF;
        *dst++ = res;
    }
}

// Similar to EdTelop_800C4F80
void Ending2_800C691C(int offset, int count)
{
    u_long *ptr;
    int     i;

    ptr = (u_long *)((short *)ending2_image_800CA370 + offset);
    for (i = count / 2; i > 0; i -= 4)
    {
        ptr[3] = 0;
        ptr[2] = 0;
        ptr[1] = 0;
        ptr[0] = 0;
        ptr += 4;
    }
}

void Ending2_800C6968(Ending2Work *work) // TODO: I guessed that it's work
{
    int yoff;

    yoff = (work->field_24 + 320) % 320;

    ending2_image_rects_800C9ED0[GV_Clock_800AB920] = ending2_orig_image_rect_800C324C;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].w = 320;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].h = 2;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].y += yoff;

    SwEnterCriticalSection();
    LoadImage(&ending2_image_rects_800C9ED0[GV_Clock_800AB920], (u_long *)&ending2_image_800CA370[GV_Clock_800AB920 * 2560]);
    SwExitCriticalSection();

    work->field_24 = (work->field_24 + 2) % 320;
}

void roll_ending2_800C6AA4(Ending2Work *work, int count)
{
    int i;
    int yoff;

    for (i = 0; i < count; i++)
    {
        yoff = (work->field_24 + 320 + i) % 320;

        ending2_800C9EE0[GV_Clock_800AB920][i] = ending2_orig_image_rect_800C324C;
        ending2_800C9EE0[GV_Clock_800AB920][i].w = 320;
        ending2_800C9EE0[GV_Clock_800AB920][i].h = 1;
        ending2_800C9EE0[GV_Clock_800AB920][i].y += yoff;

        SwEnterCriticalSection();
        LoadImage(&ending2_800C9EE0[GV_Clock_800AB920][i], (u_long *)&ending2_image_800CA370[GV_Clock_800AB920 * 2560 + i * 320]);
        SwExitCriticalSection();
    }

    work->field_24 = (work->field_24 + count) % 320;
}

int Ending2_800C6C40(Ending2Work *work)
{
    // FIMXE: figure out the type of field_50, field_54
    short *temp_v1;
    int    zero;

    zero = 0;

    temp_v1 = (short *)work->field_50;
    temp_v1 = (short *)((char *)temp_v1 + (((int *)temp_v1)[0x24 / 4] + 0x28));
    work->field_50 = temp_v1;
    work->field_54 = (int *)((char *)temp_v1 + 0x28);
    roll_dword_800CA360 = temp_v1[1] * 2;
    roll_dword_800C32B8 = temp_v1[zero];
    work->field_20 = 0;
    return ++work->field_2C < work->field_28;
}

// polys is an array of (at least) 40 POLY_FT4;
void Ending2_800C6C9C(POLY_FT4 *polys, Ending2Pair *tpages, char *pOt)
{
    POLY_FT4 *scratch;
    int       y;
    int       x;
    short     tpage;

    scratch = (POLY_FT4 *)getScratchAddr(0);

    setPolyFT4(scratch);
    setRGB0(scratch, 80, 80, 80);

    tpage = tpages->tpage1;

    setXY4(scratch, 0, 0, 8, 0, 0, 320, 8, 320);
    setUV4(scratch, 0, 64, 8, 64, 0, 224, 8, 224);

    scratch->tpage = tpage;

    x = 0;
    y = 0;
    while (x < 320)
    {
        scratch->x0 = x;
        scratch->x2 = x;
        x += 8;

        scratch->u0 = y;
        scratch->u2 = y;
        y += 8;

        scratch->x1 = x;
        scratch->u1 = y;

        scratch->x3 = x;
        scratch->u3 = y;

        *polys = *scratch;

        addPrim(pOt, polys);
        polys++;

        if (y > 192)
        {
            y -= 192;
            scratch->tpage = tpages->tpage2;
        }
    }
}

// polys is an array of (at least) 120 SPRT;
void Ending2_800C6E00(SPRT *polys, Ending2Prims *prims, int arg2, char *pOt, int shade)
{
    DR_TPAGE *tpages[4];
    int       u0;
    int       x0;

    SPRT *scratch;
    SPRT *scratch2;

    scratch = (SPRT *)getScratchAddr(0);

    setSprt(&scratch[0]);
    scratch[0].x0 = 0;
    scratch[0].y0 = 0;
    scratch[0].u0 = 0;
    scratch[0].v0 = 0;
    scratch[0].w = 8;
    scratch[0].h = 0x100;

    setRGB0(&scratch[0], shade, shade, shade);

    scratch[2] = scratch[1] = scratch[0];

    if (arg2 < 0x100)
    {
        scratch[0].y0 = 0;
        scratch[0].v0 = arg2;
        scratch[0].h = 256 - arg2;

        scratch[1].y0 = 320 - arg2;
        scratch[1].v0 = 0;
        scratch[1].h = arg2;

        scratch[2].y0 = 256 - arg2;
        scratch[2].v0 = 0;
        scratch[2].h = 64;

        tpages[0] = &prims->tpages[0];
        tpages[1] = &prims->tpages[1];
        tpages[2] = &prims->tpages[2];
        tpages[3] = &prims->tpages[3];
    }
    else
    {
        scratch[0].y0 = 0;
        scratch[0].v0 = arg2;
        scratch[0].h = 320 - arg2;

        scratch[1].y0 = 576 - arg2;
        scratch[1].v0 = 0;
        scratch[1].h = arg2 - 256;

        scratch[2].y0 = 320 - arg2;
        scratch[2].v0 = 0;
        scratch[2].h = 256;

        tpages[0] = &prims->tpages[2];
        tpages[1] = &prims->tpages[3];
        tpages[2] = &prims->tpages[0];
        tpages[3] = &prims->tpages[1];
    }

    x0 = 0;
    u0 = 0;

    scratch2 = &scratch[1];
    while (x0 < 320)
    {
        scratch2->x0 = x0;
        scratch[0].x0 = x0;
        x0 += 8;
        scratch2->u0 = u0;
        scratch[0].u0 = u0;
        u0 += 8;

        *polys = scratch[0];
        addPrim(pOt, polys);
        polys++;

        *polys = scratch[1];
        addPrim(pOt, polys);

        polys++;
        if (u0 > 192)
        {
            u0 -= 192;
            addPrim(pOt, tpages[0]);
        }
    }

    addPrim(pOt, tpages[1]);

    x0 = 0;
    u0 = 0;
    while (x0 < 320)
    {
        scratch[2].x0 = x0;
        x0 += 8;
        scratch[2].u0 = u0;
        u0 += 8;

        *polys = scratch[2];
        addPrim(pOt, polys);
        polys++;

        if (u0 > 192)
        {
            u0 -= 192;
            addPrim(pOt, tpages[2]);
        }
    }

    addPrim(pOt, tpages[3]);
}

void Ending2Act_800C71D8(Ending2Work *work)
{
    int             shade;
    Ending2Prims   *prims;
    int            *var_s1;
    int             temp_s0;
    char           *pOt;
    int             i;
    int             i2;
    unsigned short *var_a0, *var_a0_2;
    unsigned char   var_s6;
    void           *scratch1;
    int             count;
    int             new_framerate;

    shade = 150;

    switch (Ending2_800C677C(work))
    {
    case 0:
        Ending2_800C66EC(work);
        break;

    case 1:
        work->field_44 = mts_get_tick_count_8008BBB0();
        break;

    case 2:
    default:
        work->field_34++;
        temp_s0 = mts_get_tick_count_8008BBB0() - work->field_44;
        Ending2_800C691C(GV_Clock_800AB920 * 256 * 10, 960);

        scratch1 = (void *)0x1F800000;

        switch (work->field_20)
        {
        case 0:
            if (roll_dword_800C32BC[work->field_2C] < temp_s0)
            {
                work->field_20 = 1;
            }
            roll_ending2_800C6AA4(work, 3);
            break;

        case 1:
            count = 3;

            var_a0 = (unsigned short *)0x1F800200;
            var_a0_2 = work->field_50 + 2;
            for (i2 = 16; i2 > 0; i2--)
            {
                *var_a0++ = *var_a0_2++;
            }

            var_a0_2 = (unsigned short *)0x1F800200;

            for (i = 0; i < count; i++, roll_dword_800CA360--)
            {
                if (!(roll_dword_800CA360 & 1))
                {
                    var_s6 = *work->field_54;
                    var_s1 = work->field_54;
                    work->field_54 = roll_ending2_800C6814(scratch1, var_s1, *work->field_50 / 2);
                    if (!(var_s6 & 0xC0))
                    {
                        roll_ending2_800C6834(&ending2_image_800CA370[GV_Clock_800AB920 * 2560] + i * 320, scratch1,
                                              var_a0_2, roll_dword_800C32B8);
                    }
                }
                else
                {
                    if (i == 0)
                    {
                        var_s6 = *work->field_54;
                        work->field_54 = roll_ending2_800C6814(scratch1, work->field_54, *work->field_50 / 2);
                    }

                    var_s1 = work->field_54 = work->field_54; // ???
                    var_s6 = var_s6 | *var_s1;
                    work->field_54 = roll_ending2_800C6814(scratch1 + 0x100, var_s1, *work->field_50 / 2);
                    if (!(var_s6 & 0xC0))
                    {
                        roll_ending2_800C6854(&ending2_image_800CA370[GV_Clock_800AB920 * 2560] + i * 320, scratch1,
                                              var_a0_2, roll_dword_800C32B8);
                    }
                    work->field_54 = var_s1;
                }
            }

            work->field_54 = var_s1;

            roll_ending2_800C6AA4(work, 3);

            if (roll_dword_800CA360 < 4)
            {
                if (Ending2_800C6C40(work) == 0)
                {
                    work->field_20 = 2;
                    work->field_30 = 0;
                }
            }
            break;

        case 2:
            roll_dword_800C32B8 = 320;
            if (--work->field_30 < 0)
            {
                if (moviework_800C326C.field_0 == -1)
                {
                    work->field_20 = 4;
                    work->field_30 = 40;
                }
            }
            break;

        case 3:
            if (--work->field_30 <= 0)
            {
                work->field_20 = 0;
                moviework_800C326C.field_1C = 1;
            }
            return;

        case 4:
            roll_dword_800C32B8 = 320;
            shade = (shade * work->field_30) / 40;
            if (--work->field_30 < 0)
            {
                GV_DestroyActor_800151C8(&work->actor);
                return;
            }
            break;
        }

        prims = &work->field_64[GV_Clock_800AB920];
        new_framerate = 2;
        pOt = DG_ChanlOTag(1);
        Ending2_800C6E00(prims->field_20, prims, work->field_24, pOt, shade);
        Ending2_800C6C9C(prims->field_CAC, &prims->field_CA0[moviework_800C326C.field_18], pOt);
        DG_FrameRate_8009D45C = new_framerate;
        if (work->field_38 >= 0 && work->field_38 <= 1 && work->field_20 == 1)
        {
            work->field_3C++;
        }
        if (++work->field_38 >= 3)
        {
            work->field_38 = 0;
        }
        break;
    }
}

void Ending2Die_800C76BC(Ending2Work *work)
{
    RECT     rect;
    DRAWENV  drawenv;
    DISPENV *dispenv;

    Ending2_800C673C(work);

    DrawSync(0);

    rect.x = 0;
    rect.y = 0;
    rect.w = 960;
    rect.h = 512;
    ClearImage(&rect, 0, 0, 0);

    DrawSync(0);

    dispenv = DG_GetDisplayEnv_80017978();
    *dispenv = work->field_325C;

    SetDefDrawEnv(&drawenv, 0, 0, 320, 224);

    DG_80018128(-1, &drawenv);
    DG_80018128(1, &drawenv);

    DrawSync(0);

    if (work->field_40 == 0)
    {
        sd_set_cli_800887EC(-19, 0);
    }

    DG_FrameRate_8009D45C = 2;

    if (work->field_5C != 0)
    {
        GCL_ExecProc_8001FF2C(work->field_5C, NULL);
    }
}

void Ending2GetResources_800C77F8(Ending2Work *work, int field_48)
{
    RECT     rect;
    DRAWENV  drawenv;
    DISPENV *dispenv;
    int      i, j;
    int      tpage, tpage2;
    int     *field_58;
    int      zero;

    work->field_48 = field_48;

    rect.x = 0;
    rect.y = 0;
    rect.w = 960;
    rect.h = 512;
    ClearImage(&rect, 0, 0, 0);

    DrawSync(0);

    dispenv = DG_GetDisplayEnv_80017978();
    work->field_325C = *dispenv;
    dispenv->disp.y = 4;
    dispenv->disp.h = 320;
    dispenv->screen.h = 158;
    dispenv->isinter = 1;
    dispenv->screen.y += 28;

    PutDispEnv(dispenv);

    SetDefDrawEnv(&drawenv, 0, 0, 320, 320);
    drawenv.isbg = 1;
    drawenv.dfe = 1;

    DG_80018128(-1, &drawenv);

    drawenv.isbg = 0;
    DG_80018128(1, &drawenv);

    DrawSync(0);

    ClearImage(&moviework_rects_800C3254[2], 0, 0, 0);

    DG_UnDrawFrameCount_800AB380 = 1;
    DG_FrameRate_8009D45C = 1;
    GM_GameStatus_800AB3CC |= 0x104A2000;

    work->field_58 = GV_GetCache_8001538C(GV_CacheID_800152DC(0xEAE8, 'r')); // FIXME: figure out the type of field_58, it could be a custom type!!! (as is the case with 'r' resources...)

    work->field_20 = 3;
    work->field_24 = 0;
    work->field_2C = 0;
    work->field_28 = work->field_58[0];

    field_58 = work->field_58;
    work->field_50 = (short *)(field_58 + 1);
    work->field_54 = field_58 + 11;

    zero = 0;
    roll_dword_800CA360 = work->field_50[1] * 2;
    roll_dword_800C32B8 = work->field_50[zero];

    tpage = getTPage(2, 0, ending2_orig_image_rect_800C324C.x, ending2_orig_image_rect_800C324C.y);
    tpage2 = getTPage(2, 0, ending2_orig_image_rect_800C324C.x + 192, ending2_orig_image_rect_800C324C.y);
    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->field_64[i].tpages[0], 1, 1, tpage);
        setDrawTPage(&work->field_64[i].tpages[1], 1, 1, tpage2);
    }

    tpage = getTPage(2, 0, ending2_orig_image_rect_800C324C.x, ending2_orig_image_rect_800C324C.y + 256);
    tpage2 = getTPage(2, 0, ending2_orig_image_rect_800C324C.x + 192, ending2_orig_image_rect_800C324C.y + 256);
    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->field_64[i].tpages[2], 1, 1, tpage);
        setDrawTPage(&work->field_64[i].tpages[3], 1, 1, tpage2);
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            work->field_64[i].field_CA0[j].tpage1 =
                getTPage(2, 0, moviework_rects_800C3254[j].x, moviework_rects_800C3254[j].y & 0x100);

            work->field_64[i].field_CA0[j].tpage2 =
                getTPage(2, 0, moviework_rects_800C3254[j].x + 192, moviework_rects_800C3254[j].y & 0x100);
        }
    }

    if (work->field_40 == 0)
    {
        Ending2_800C665C(work->field_48);
        sd_set_cli_800887EC(-0x14, 0);
    }
    else
    {
        Ending2_800C665C(0);
    }
}

GV_ACT *NewEnding2_800C7BE8(int arg0)
{
    Ending2Work *work;

    work = (Ending2Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Ending2Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Ending2Act_800C71D8,
                                  (TActorFunction)Ending2Die_800C76BC, "ending2.c");
        work->field_5C = THING_Gcl_GetInt('p');
        work->field_30 = THING_Gcl_GetIntDefault('w', 660);
        work->field_4C = THING_Gcl_GetInt('v');
        if (work->field_4C == 0)
        {
            work->field_40 = 0;
        }
        else
        {
            work->field_40 = 1;
        }
        Ending2GetResources_800C77F8(work, arg0);
    }
    return &work->actor;
}
