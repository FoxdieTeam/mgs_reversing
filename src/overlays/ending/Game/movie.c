#include "common.h"
#include "psyq.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"
#include "SD/sd.h"

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
    void          *f48;
    u_long        *f4C;
    int            f50;
    void          *vlc;
    void          *ring;
    void          *dctin[2];
    void          *dctout[2];
} MovieWork;

static MovieWork movie_work;
static int       movie_unused;

extern int DG_FrameRate_8009D45C;
extern int DG_UnDrawFrameCount_800AB380;
extern int GM_GameStatus_800AB3CC;
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
    u_long   *unk;

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
        GV_AllocMemory2_80015ED8(0, size, &work->f48);
        GV_CopyMemory_800160D8(addr, work->f48, size);

        font = work->f48;
        font2 = font;

        unk = (u_long *)(font + *(short *)(font + 0xA));
        if ((unk[0] == 0) && (unk[1] == 0) && (unk[2] == 0))
        {
            unk = NULL;
        }

        work->f4C = unk;
        work->f50 = 0;

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

#pragma INCLUDE_ASM("asm/overlays/ending/MovieAct_800C491C.s")
void MovieAct_800C491C(MovieWork *work);

void MovieAct_800C4C00(MovieWork *work)
{
    int i;
    int status;

    if (work->f2C-- > 0)
    {
        DG_FreeObjectQueue_800183D4();
        return;
    }

    XA_Start_80088868();

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
        XA_Stop_800888B4();
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

#pragma INCLUDE_ASM("asm/overlays/ending/NewMovie_800C4E24.s")
GV_ACT * NewMovie_800C4E24(void);

GV_ACT * NewMovie_800C4F34(void)
{
    MovieWork *work;

    work = (MovieWork *)NewMovie_800C4E24();
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
