#include "common.h"
#include "psyq.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"
#include "SD/sound.h"
#include "mts/pad/pad.h"

typedef struct _MovieWork
{
    GV_ACT         actor;
    FS_MOVIE_FILE *file;
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
    int            proc;
    void          *font;
    int           *jimaku;
    int            jimaku_length;
    void          *vlc;
    void          *ring;
    void          *dctin[2];
    void          *dctout[2];
} MovieWork;

static MovieWork movie_work;

extern int DG_FrameRate_8009D45C;
extern int DG_UnDrawFrameCount_800AB380;
extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;

static inline int MovieType(void)
{
    if (GM_GameStatusFlag & 0x100)
    {
        return 1;
    }

    return (GM_GameStatusFlag & 0x100) ? 1 : 2;
}

static inline void MovieIntToPos(int i, CdlLOC *p)
{
    int temp;

    temp = i / 75;

    p->sector = itob(i % 75);
    p->second = itob(temp % 60);
    p->minute = itob(temp / 60);
}

void Movie_800C4484(int pos)
{
    CdlLOC loc;

    do
    {
        MovieIntToPos(pos, &loc);
        while (CdControl(CdlSetloc, (u_char *)&loc, NULL) == 0);
    } while (CdRead2(CdlModeStream2 | CdlModeSpeed | CdlModeRT) == 0);
}

int Movie_800C45F4(MovieWork *work)
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

            if ((work->file->field_2_frame - 2) >= header->frameCount)
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
        GV_AllocMemory2_80015ED8(0, size, &work->font);
        GV_CopyMemory_800160D8(addr, work->font, size);

        font = work->font;
        font2 = font;

        jimaku = (int *)(font + *(short *)(font + 0xA));
        if ((jimaku[0] == 0) && (jimaku[1] == 0) && (jimaku[2] == 0))
        {
            jimaku = NULL;
        }

        work->jimaku = jimaku;
        work->jimaku_length = 0;

        font_set_font_addr_80044BC0(3, font2 + *(int *)(font + 0xC));
        work->ticks = mts_get_tick_count_8008BBB0();
        ret = -1;
    }

free:
    StFreeRing(addr);
    return ret;
}

void Movie_800C47E8(void)
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

void Movie_800C4878(int shade)
{
    TILE      tile;
    DR_TPAGE  tpage;
    DR_TPAGE *tpagep;
    TILE     *tilep;

    tpagep = &tpage;
    setDrawTPage(tpagep, 1, 0, getTPage(0, 2, 0, 0));
    DrawPrim(tpagep);

    tilep = &tile;
    shade = __clamp(shade, 0, 255);
    LSTORE((shade << 16) | (shade << 8) | shade, &tilep->r0);
    setTile(tilep);
    setSemiTrans(tilep, 1);
    setXY0(tilep, 0, 24);
    setWH(tilep, 320, 160);
    DrawPrim(&tile);

    DrawSync(0);
}

void MovieAct_800C491C(MovieWork *work)
{
    RECT *rect;
    int   status;
    int   start;
    int   elapsed;
    int  *jimaku;
    int   skip;
    int   div;
    int   shade;

    DrawSync(0);

    rect = &work->rect;
    rect->x = (GV_Clock_800AB920 == 0) ? 304 : -16;
    rect->y = 24;
    rect->w = 16;
    rect->h = __min(work->height, 224);

    work->f2C = 0;
    work->f38 = rect->x + work->width;

    DecDCTout(work->dctout[work->dctout_index], work->height * 8);
    DecDCTin(work->dctin[work->dctin_index], 2);

    while ((status = Movie_800C45F4(work)) < 0);

    if (status != 0)
    {
        start = VSync(-1);
        while (work->f2C == 0)
        {
            if ((VSync(-1) - start) > 120)
            {
                status = 0;
                break;
            }
        }
    }

    elapsed = mts_get_tick_count_8008BBB0() - work->ticks;
    elapsed = (elapsed * 105) / 256;

    jimaku = work->jimaku;
    if (jimaku != NULL)
    {
        if (work->jimaku_length == 0)
        {
            if (elapsed >= jimaku[1])
            {
                menu_JimakuWrite_800494E8((char *)jimaku + 16, 0);
                work->jimaku_length = jimaku[1] + jimaku[2];
            }
        }
        else if (elapsed >= work->jimaku_length)
        {
            menu_JimakuClear_80049518();
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
        shade = ((work->f40 - work->n_frames) * 255) / work->f40;
        Movie_800C4878(shade);
    }
    else if (work->f42 < work->n_frames)
    {
        div = work->file->field_2_frame - 1;
        div -= work->f42;
        shade = ((work->n_frames - work->f42) * 255) / div;
        Movie_800C4878(shade);
    }

    if (mts_read_pad_8008C25C(0) & PAD_CROSS)
    {
        status = 0;
    }

    if (status == 0)
    {
        stop_xa_sd_800888B4();
        DecDCToutCallback(0);
        GV_DestroyActor_800151C8(&work->actor);
        DG_UnDrawFrameCount_800AB380 = 2;
    }
}

void MovieAct_800C4C00(MovieWork *work)
{
    int i;
    int status;

    if (work->f2C-- > 0)
    {
        DG_FreeObjectQueue_800183D4();
        return;
    }

    start_xa_sd_80088868();

    GV_ResetPacketMemory_80014BD8();
    GV_AllocMemory2_80015ED8(0, 0x11000, &work->vlc);
    GV_AllocMemory2_80015ED8(0, 0x10000, &work->ring);

    for (i = 0; i < 2; i++)
    {
        GV_AllocMemory2_80015ED8(1, 0x17800, &work->dctin[i]);
        GV_AllocMemory2_80015ED8(0, 0x1E00, &work->dctout[i]);
    }

    DecDCTReset(0);
    DecDCToutCallback(Movie_800C47E8);

    StSetRing(work->ring, 32);
    StSetStream(0, 0, 0xFFFFFFFF, NULL, NULL);

    Movie_800C4484(work->file->field_4_pos);

    DecDCTvlcBuild(work->vlc);

    work->actor.mFnUpdate = (TActorFunction)MovieAct_800C491C;
    work->dctin_index = 0;
    work->dctout_index = 0;

    DG_FrameRate_8009D45C = 1;

    work->ticks = mts_get_tick_count_8008BBB0();

    do
    {
        status = Movie_800C45F4(work);
    } while (status < 0);

    if (status == 0)
    {
        stop_xa_sd_800888B4();
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void MovieDie_800C4D78(MovieWork *work)
{
    DecDCToutCallback(NULL);
    StUnSetRing();
    CdControlB(CdlPause, NULL, NULL);

    GV_ResetPacketMemory_80014BD8();

    GV_PauseLevel_800AB928 &= ~1;

    DG_ResetObjectQueue_8001844C();
    DG_FrameRate_8009D45C = 2;

    work->file = NULL;

    menu_JimakuClear_80049518();

    DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_32;

    if (work->proc >= 0)
    {
        GCL_ExecProc_8001FF2C(work->proc, NULL);
    }
}

GV_ACT * NewMovie_800C4E24(unsigned int code)
{
    FS_MOVIE_FILE *file;
    int            frame;

    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_32;

    if (movie_work.file != NULL)
    {
        return NULL;
    }

    GV_ZeroMemory_8001619C(&movie_work, sizeof(MovieWork));
    printf("MOVIE %d\n", code);

    file = FS_GetMovieInfo_8002399C(code);
    if (file == NULL)
    {
        printf("NOT FOUND\n");
        return NULL;
    }

    GV_InitActor_800150A8(1, &movie_work.actor, NULL);
    GV_SetNamedActor_8001514C(&movie_work.actor, (TActorFunction)MovieAct_800C4C00, (TActorFunction)MovieDie_800C4D78, "movie.c");

    movie_work.file = file;
    movie_work.f2C = 1;
    movie_work.f40 = 1;

    frame = file->field_2_frame;

    DG_UnDrawFrameCount_800AB380 = 1;

    movie_work.proc = -1;
    movie_work.f40 = 11;

    GV_PauseLevel_800AB928 |= 1;

    movie_work.f42 = frame - 1;
    movie_work.n_frames = 0;
    movie_work.f42 = frame - 11;

    return &movie_work.actor;
}

GV_ACT * NewMovie_800C4F34(unsigned int code)
{
    MovieWork *work;

    work = (MovieWork *)NewMovie_800C4E24(code);
    if (work == NULL)
    {
        return NULL;
    }

    if (GCL_GetOption_80020968('i'))
    {
        work->f40 += GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('o'))
    {
        work->f42 -= GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('p'))
    {
        work->proc = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    return &work->actor;
}
