#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "SD/sd.h"
#include "Game/game.h"
#include "common.h"

typedef struct Ending2Work
{
    GV_ACT  actor;
    int     field_20;
    int     field_24;
    int     field_28;
    int     field_2C;
    int     field_30;
    int     field_34;
    int     field_38;
    int     field_3C;
    int     field_40;
    int     field_44;
    int     field_48;
    int     field_4C;
    int     field_50;
    int     field_54;
    int     field_58;
    int     field_5C;
    char    pad_60[0x325C];
    DISPENV field_325C;
} Ending2Work;

#define EXEC_LEVEL 5

int THING_Gcl_GetIntDefault(char param, int def);
int THING_Gcl_GetInt(char param);

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
int roll_dword_800C32BC = 0x00000267;
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

int SECTION("overlay.bss") roll_dword_800C9EE0;
int SECTION("overlay.bss") roll_dword_800C9EE4;
int SECTION("overlay.bss") roll_dword_800C9EE8;
int SECTION("overlay.bss") roll_dword_800C9EEC;
int SECTION("overlay.bss") roll_dword_800C9EF0;
int SECTION("overlay.bss") roll_dword_800C9EF4;
int SECTION("overlay.bss") roll_dword_800C9EF8;
int SECTION("overlay.bss") roll_dword_800C9EFC;
int SECTION("overlay.bss") roll_dword_800C9F00;
int SECTION("overlay.bss") roll_dword_800C9F04;
int SECTION("overlay.bss") roll_dword_800C9F08;
int SECTION("overlay.bss") roll_dword_800C9F0C;
int SECTION("overlay.bss") roll_dword_800C9F10;
int SECTION("overlay.bss") roll_dword_800C9F14;
int SECTION("overlay.bss") roll_dword_800C9F18;
int SECTION("overlay.bss") roll_dword_800C9F1C;
int SECTION("overlay.bss") roll_dword_800C9F20;
int SECTION("overlay.bss") roll_dword_800C9F24;
int SECTION("overlay.bss") roll_dword_800C9F28;
int SECTION("overlay.bss") roll_dword_800C9F2C;
int SECTION("overlay.bss") roll_dword_800C9F30;
int SECTION("overlay.bss") roll_dword_800C9F34;
int SECTION("overlay.bss") roll_dword_800C9F38;
int SECTION("overlay.bss") roll_dword_800C9F3C;
int SECTION("overlay.bss") roll_dword_800C9F40;
int SECTION("overlay.bss") roll_dword_800C9F44;
int SECTION("overlay.bss") roll_dword_800C9F48;
int SECTION("overlay.bss") roll_dword_800C9F4C;
int SECTION("overlay.bss") roll_dword_800C9F50;
int SECTION("overlay.bss") roll_dword_800C9F54;
int SECTION("overlay.bss") roll_dword_800C9F58;
int SECTION("overlay.bss") roll_dword_800C9F5C;

int SECTION("overlay.bss") stack_800C9F60[0x100];

int SECTION("overlay.bss") roll_dword_800CA360;
int SECTION("overlay.bss") roll_dword_800CA364;
int SECTION("overlay.bss") roll_dword_800CA368;
int SECTION("overlay.bss") roll_dword_800CA36C;

u_long SECTION("overlay.bss") ending2_image_800CA370[2][320 * 2 * 2];

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C5DC0.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C5E54.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C5EAC.s")

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
        XA_Stop_800888B4();
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
            XA_Stop_800888B4();
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

    XA_Start_80088868();

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

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6814.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6834.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6854.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C691C.s")

void Ending2_800C6968(Ending2Work *work) // TODO: I guessed that it's work
{
    int yoff;

    yoff = (work->field_24 + 320) % 320;

    ending2_image_rects_800C9ED0[GV_Clock_800AB920] = ending2_orig_image_rect_800C324C;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].w = 320;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].h = 2;
    ending2_image_rects_800C9ED0[GV_Clock_800AB920].y += yoff;

    SwEnterCriticalSection();
    LoadImage(&ending2_image_rects_800C9ED0[GV_Clock_800AB920], ending2_image_800CA370[GV_Clock_800AB920]);
    SwExitCriticalSection();

    work->field_24 = (work->field_24 + 2) % 320;
}

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6AA4.s")
#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6C40.s")

// polys is an array of (at least) 40 POLY_FT4;
// tpages argument contains 2 shorts
void Ending2_800C6C9C(POLY_FT4 *polys, short *tpages, char *pOt)
{
    POLY_FT4 *scratch;
    int       y;
    int       x;
    short     tpage;

    scratch = (POLY_FT4 *)getScratchAddr(0);

    setPolyFT4(scratch);
    setRGB0(scratch, 80, 80, 80);

    tpage = tpages[0];

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
            scratch->tpage = tpages[1];
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C6E00.s")

// Jump table used in roll_ending2_800C71D8
const int SECTION("overlay.rdata") jpt_800C9ACC[] = {0x800C72C0, 0x800C7300, 0x800C74E8, 0x800C752C, 0x800C7554};

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C71D8.s")
void roll_ending2_800C71D8(Ending2Work *work);

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
    ClearImage(&rect, 0U, 0U, 0U);

    DrawSync(0);

    dispenv = DG_GetDisplayEnv_80017978();
    *dispenv = work->field_325C;

    SetDefDrawEnv(&drawenv, 0, 0, 0x140, 0xE0);

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

#pragma INCLUDE_ASM("asm/overlays/roll/roll_ending2_800C77F8.s")
int roll_ending2_800C77F8(Ending2Work *work, int);

GV_ACT *NewEnding2_800C7BE8(int arg0)
{
    Ending2Work *work;

    work = (Ending2Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Ending2Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)roll_ending2_800C71D8,
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
        roll_ending2_800C77F8(work, arg0);
    }
    return &work->actor;
}
