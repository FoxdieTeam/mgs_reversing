#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include <libpress.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libfs/libfs.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "linkvar.h"
#include "SD/sd_cli.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

typedef struct _MovieWork
{
    GV_ACT         actor;
    FS_MOVIE_FILE *info;
    RECT           rect;
    int            f2C;
    int            ticks;
    short          width;
    short          height;
    short          f38;
    short          dctin_index;
    short          dctout_index;
    short          n_frames;
    short          f40;
    short          f42;
    int            end_proc;
    void          *font;
    int           *jimaku;
    int            jimaku_length;
    void          *vlc;
    void          *ring;
    void          *dctin[2];
    void          *dctout[2];
} MovieWork;

static MovieWork movie_work;

static inline int MovieType(void)
{
    if (GM_GameStatusFlag & 0x100)
    {
        return 1;
    }

    return (GM_GameStatusFlag & 0x100) ? 1 : 2;
}

static inline void int_to_loc(int pos, CdlLOC *loc)
{
    int seconds;

    seconds = pos / 75;
    loc->sector = itob(pos % 75);
    loc->second = itob(seconds % 60);
    loc->minute = itob(seconds / 60);
}

STATIC void Movie_800C4484(int pos)
{
    CdlLOC loc;

    do
    {
        int_to_loc(pos, &loc);
        while (CdControl(CdlSetloc, (u_char *)&loc, NULL) == 0);
    } while (CdRead2(CdlModeStream2 | CdlModeSpeed | CdlModeRT) == 0);
}

STATIC int Movie_800C45F4(MovieWork *work)
{
    u_long   *addr;
    StHEADER *header;
    int       start;
    u_short   type;
    int       ret;
    int       size;
    char     *font;
    char     *font2;
    int      *jimaku;

    start = VSync(-1);
    while (StGetNext(&addr, (u_long **)&header) != 0)
    {
        if ((VSync(-1) - start) > 300)
        {
            return 0;
        }
    }

    type = header->type;

    if (type == 0x8001)
    {
        if (header->frameCount >= work->n_frames)
        {
            work->n_frames = header->frameCount;

            if ((work->info->frame - 2) >= header->frameCount)
            {
                work->width = header->width;
                work->height = header->height;

                work->dctin_index = 1 - work->dctin_index;

                DecDCTvlc2(addr, work->dctin[work->dctin_index], work->vlc);
                ret = 1;
                goto free;
            }
        }

        return 0;
    }

    ret = -1;
    if (type != MovieType())
    {
        if (work->n_frames > 16)
        {
            return 0;
        }

        size = header->nSectors * 2016;
        GV_AllocMemory2(GV_PACKET_MEMORY0, size, &work->font);
        GV_CopyMemory(addr, work->font, size);

        font = work->font;
        font2 = font;

        jimaku = (int *)(font + *(short *)(font + 0xA));
        if ((jimaku[0] == 0) && (jimaku[1] == 0) && (jimaku[2] == 0))
        {
            jimaku = NULL;
        }

        work->jimaku = jimaku;
        work->jimaku_length = 0;

        font_set_font_addr(3, font2 + *(int *)(font + 0xC));
        work->ticks = mts_get_tick_count();
        ret = -1;
    }

free:
    StFreeRing(addr);
    return ret;
}

STATIC void Movie_800C47E8(void)
{
    movie_work.rect.x += 16;
    LoadImage(&movie_work.rect, movie_work.dctout[movie_work.dctout_index]);

    movie_work.dctout_index = 1 - movie_work.dctout_index;

    if (movie_work.rect.x < movie_work.f38)
    {
        DecDCTout(movie_work.dctout[movie_work.dctout_index], movie_work.height * 8);
        return;
    }

    movie_work.f2C = 1;
}

STATIC void set_fade(int fade)
{
    TILE      tile;
    DR_TPAGE  tpage;
    DR_TPAGE *tpagep;
    TILE     *tilep;

    tpagep = &tpage;
    setDrawTPage(tpagep, 1, 0, getTPage(0, 2, 0, 0));
    DrawPrim(tpagep);

    tilep = &tile;
    fade = CLAMP(fade, 0, 255);
    LSTORE((fade << 16) | (fade << 8) | fade, &tilep->r0);
    setTile(tilep);
    setSemiTrans(tilep, 1);
    setXY0(tilep, 0, 24);
    setWH(tilep, 320, 160);
    DrawPrim(&tile);

    DrawSync(0);
}

STATIC void MovieAct_800C491C(MovieWork *work)
{
    RECT *rect;
    int   res_flag;
    int   start;
    int   elapsed;
    int  *jimaku;
    int   skip;
    int   div;
    int   fade;

    DrawSync(0);

    rect = &work->rect;
    rect->x = (GV_Clock == 0) ? 304 : -16;
    rect->y = 24;
    rect->w = 16;
    rect->h = MIN(work->height, 224);

    work->f2C = 0;
    work->f38 = rect->x + work->width;

    DecDCTout(work->dctout[work->dctout_index], work->height * 8);
    DecDCTin(work->dctin[work->dctin_index], 2);

    while ((res_flag = Movie_800C45F4(work)) < 0);

    if (res_flag != 0)
    {
        start = VSync(-1);
        while (work->f2C == 0)
        {
            if ((VSync(-1) - start) > 120)
            {
                res_flag = 0;
                break;
            }
        }
    }

    elapsed = mts_get_tick_count() - work->ticks;
    elapsed = (elapsed * 105) / 256;

    jimaku = work->jimaku;
    if (jimaku != NULL)
    {
        if (work->jimaku_length == 0)
        {
            if (elapsed >= jimaku[1])
            {
                MENU_JimakuWrite((char *)jimaku + 16, 0);
                work->jimaku_length = jimaku[1] + jimaku[2];
            }
        }
        else if (elapsed >= work->jimaku_length)
        {
            MENU_JimakuClear();
            work->jimaku_length = 0;

            skip = jimaku[0];
            jimaku = (int *)((char *)jimaku + skip);
            if (skip == 0)
            {
                jimaku = NULL;
            }

            work->jimaku = jimaku;
        }
    }

    if (work->f40 > work->n_frames)
    {
        fade = ((work->f40 - work->n_frames) * 255) / work->f40;
        set_fade(fade);
    }
    else if (work->f42 < work->n_frames)
    {
        div = work->info->frame - 1;
        div -= work->f42;
        fade = ((work->n_frames - work->f42) * 255) / div;
        set_fade(fade);
    }

    if (mts_read_pad(0) & PAD_CROSS)
    {
        res_flag = 0;
    }

    if (res_flag == 0)
    {
        stop_xa_sd();
        DecDCToutCallback(NULL);
        GV_DestroyActor(&work->actor);
        DG_UnDrawFrameCount = 2;
    }
}

STATIC void MovieAct_800C4C00(MovieWork *work)
{
    int i;
    int status;

    if (work->f2C-- > 0)
    {
        DG_FreeObjectQueue();
        return;
    }

    start_xa_sd();

    GV_ResetPacketMemory();
    GV_AllocMemory2(GV_PACKET_MEMORY0, 0x11000, &work->vlc);
    GV_AllocMemory2(GV_PACKET_MEMORY0, 0x10000, &work->ring);

    for (i = 0; i < 2; i++)
    {
        GV_AllocMemory2(GV_PACKET_MEMORY1, 0x17800, &work->dctin[i]);
        GV_AllocMemory2(GV_PACKET_MEMORY0, 0x1E00, &work->dctout[i]);
    }

    DecDCTReset(0);
    DecDCToutCallback(Movie_800C47E8);

    StSetRing(work->ring, 32);
    StSetStream(0, 0, 0xFFFFFFFF, NULL, NULL);

    Movie_800C4484(work->info->pos);

    DecDCTvlcBuild(work->vlc);

    work->actor.act = (GV_ACTFUNC)MovieAct_800C491C;
    work->dctin_index = 0;
    work->dctout_index = 0;

    DG_FrameRate = 1;

    work->ticks = mts_get_tick_count();

    do
    {
        status = Movie_800C45F4(work);
    } while (status < 0);

    if (status == 0)
    {
        stop_xa_sd();
        GV_DestroyActor(&work->actor);
    }
}

STATIC void MovieDie_800C4D78(MovieWork *work)
{
    DecDCToutCallback(NULL);
    StUnSetRing();
    CdControlB(CdlPause, NULL, NULL);

    GV_ResetPacketMemory();

    GV_PauseLevel &= ~1;

    DG_RestartMainChanlSystem();

    DG_FrameRate = 2;

    work->info = NULL;

    MENU_JimakuClear();

    DG_UnDrawFrameCount = 0x7FFF0000;
    GM_GameStatus &= ~STATE_DEMO;

    if (work->end_proc >= 0)
    {
        GCL_ExecProc(work->end_proc, NULL);
    }
}

void *NewMovie_800C4E24(unsigned int code)
{
    FS_MOVIE_FILE *file;
    int            frame;

    GM_GameStatus |= STATE_DEMO;

    if (movie_work.info != NULL)
    {
        return NULL;
    }

    GV_ZeroMemory(&movie_work, sizeof(MovieWork));
    printf("MOVIE %d\n", code);

    file = FS_GetMovieInfo(code);
    if (file == NULL)
    {
        printf("NOT FOUND\n");
        return NULL;
    }

    GV_InitActor(GV_ACTOR_MANAGER, &movie_work.actor, NULL);
    GV_SetNamedActor(&movie_work.actor, MovieAct_800C4C00, MovieDie_800C4D78, "movie.c");

    movie_work.info = file;
    movie_work.f2C = 1;
    movie_work.f40 = 1;

    frame = file->frame;

    DG_UnDrawFrameCount = 1;

    movie_work.end_proc = -1;
    movie_work.f40 = 11;

    GV_PauseLevel |= 1;

    movie_work.f42 = frame - 1;
    movie_work.n_frames = 0;
    movie_work.f42 = frame - 11;

    return (void *)&movie_work;
}

void *NewMovie_800C4F34(unsigned int code)
{
    MovieWork *work;

    work = (MovieWork *)NewMovie_800C4E24(code);
    if (work == NULL)
    {
        return NULL;
    }

    if (GCL_GetOption('i'))
    {
        work->f40 += GCL_StrToInt(GCL_GetParamResult());
    }

    if (GCL_GetOption('o'))
    {
        work->f42 -= GCL_StrToInt(GCL_GetParamResult());
    }

    if (GCL_GetOption('p'))
    {
        work->end_proc = GCL_StrToInt(GCL_GetParamResult());
    }

    return (void *)work;
}
