/* same as overlays/s19b/menu/countdwn.c (only the radar drawing function differs in its data addresses) */
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "menu/radar.h"
#include "menu/radio.h"
#include "strcode.h"

RadioUnknown countdwn_segments_big =
{
    {{1, 0, 7, 2}, {0, 1, 2, 7}, {7, 1, 2, 7}, {1, 7, 7, 2}, {0, 9, 2, 6}, {7, 9, 2, 6}, {1, 14, 7, 2}},
    0x182589,
    0x818
};

RadioUnknown countdwn_segments_small =
{
    {{1, 0, 5, 2}, {0, 1, 2, 5}, {5, 1, 2, 5}, {1, 5, 5, 2}, {0, 7, 2, 5}, {5, 7, 2, 5}, {1, 11, 5, 2}},
    0x182589,
    0x818
};

/* position of the digits: minutes, seconds, 1/100 seconds */
u_char countdwn_digit_x[6] = {0x03, 0x0D, 0x1B, 0x25, 0x33, 0x3B};
u_char countdwn_digit_y[6] = {0x20, 0x20, 0x20, 0x20, 0x23, 0x23};

/* the dots between the digits (x, y) */
u_char countdwn_colon_pos[8] = {0x18, 0x24, 0x18, 0x2B, 0x30, 0x25, 0x30, 0x2C};

/* the lines above and below the timer (x, y, w, h) */
u_char countdwn_line_rect[2][4] = {{0x01, 0x1D, 0x43, 0x01}, {0x01, 0x32, 0x43, 0x01}};

int     SECTION(".bss") countdown_time;
int     SECTION(".bss") countdown_proc;
DG_TEX *SECTION(".bss") warn1_texture;
DG_TEX *SECTION(".bss") warn2_texture;

STATIC void draw_image(MenuPrim *prim, int x, int y, char shade, DG_TEX *tex)
{
    POLY_FT4 *poly;

    _NEW_PRIM(poly, prim);
    DG_SetPacketTexture4(poly, tex);
    setRGB0(poly, shade, shade, shade);
    setXYWH(poly, x, y, tex->w, tex->h);

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    addPrim(prim->ot, poly);
}

static void exec_countdown_proc(void)
{
    GCL_ARGS args;
    long     data;

    if (countdown_proc >= 0)
    {
        args.argc = 1;
        args.argv = &data;

        data = countdown_time / 30;

        GCL_ForceExecProc(countdown_proc, &args);
        countdown_proc = -1;
    }
}

/* draws the countdown timer in the radar */
#if 0 /* NON_MATCHING: register allocation */
#define TIMER_X -34
#define TIMER_Y -26

void s19a_800C3AD4(MenuWork *work, u_long *ot)
{
    int           shade;
    TILE         *tile;
    u_char       *rect;
    RadioUnknown *segments;
    int           color;
    int           value;
    int           time;
    int           digit;
    int           i;
    DR_TPAGE     *tpage;
    int           div;

    time = countdown_time * 100 / 30;

    if (countdown_time > 0 && --countdown_time == 0)
    {
        exec_countdown_proc();
    }

    for (i = 0; i < 8; i += 2)
    {
        tile = (TILE *)work->prim->next;
        work->prim->next += sizeof(TILE);

        tile->x0 = countdwn_colon_pos[i] - 34;
        tile->y0 = countdwn_colon_pos[i + 1] - 26;
        tile->w = 1;
        tile->h = 2;

        color = 0x182589;
        if ((time % 100) < 50)
        {
            color = 0x818;
        }

        LSTORE(color, &tile->r0);
        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(ot, tile);
    }

    segments = &countdwn_segments_small;
    div = 100;

    for (i = 5; i >= 0; i -= 2)
    {
        value = time % div;
        time /= div;
        digit = value / 10;

        sub_8003FD50(work->prim, countdwn_digit_x[i] + TIMER_X, countdwn_digit_y[i] + TIMER_Y, value - digit * 10, segments, 1);
        sub_8003FD50(work->prim, countdwn_digit_x[i - 1] + TIMER_X, countdwn_digit_y[i - 1] + TIMER_Y, digit, segments, 1);

        segments = &countdwn_segments_big;
        div = 60;
    }

    rect = countdwn_line_rect[0];
    for (i = 2; i > 0; i--)
    {
        NEW_PRIM(tile, work);

        tile->x0 = rect[0] + TIMER_X;
        LSTORE(0x182589, &tile->r0);
        tile->y0 = rect[1] + TIMER_Y;
        tile->w = rect[2];
        tile->h = rect[3];
        rect += 4;

        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(ot, tile);
    }

    NEW_PRIM(tpage, work);
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 960, 256));
    addPrim(ot, tpage);

    shade = GV_Time % 16;
    if (shade < 8)
    {
        shade = 128 - shade * 16;
    }
    else
    {
        shade = 128;
    }

    draw_image(work->prim, TIMER_X, -25, shade, warn1_texture);
    draw_image(work->prim, -33, -13, 128, warn2_texture);

    NEW_PRIM(tile, work);
    tile->x0 = TIMER_X;
    tile->w = 69;
    tile->y0 = TIMER_Y;
    tile->h = 52;
    LSTORE(0xDE, &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    addPrim(ot, tile);

    NEW_PRIM(tpage, work);
    setDrawTPage(tpage, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(ot, tpage);
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800C3AD4.s")
void s19a_800C3AD4(MenuWork *, u_long *);

int GetCountdownTime(void)
{
    return countdown_time;
}

void SetCountdownTime(int time)
{
    countdown_time = time;
}

static void Die(GV_ACT *work)
{
    MENU_SetRadarFunc(NULL);
    exec_countdown_proc();
}

static void Act(GV_ACT *work)
{
    /* do nothing */
}

void *NewCountdown(int time, int proc)
{
    GV_ACT *work;

    countdown_time = time;
    countdown_proc = proc;

    warn1_texture = DG_GetTexture(PCX_CD_WARN);
    warn2_texture = DG_GetTexture(PCX_CD_KEIKOKU);

    work = GV_NewActor(GV_ACTOR_USER, sizeof(GV_ACT));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "countdwn.c");
        MENU_SetRadarFunc(s19a_800C3AD4);
    }

    return work;
}

void NewCountdownGcl(void)
{
    int time;
    int proc;

    time = 10000;
    proc = -1;

    if (GCL_GetOption('t'))
    {
        time = GCL_GetNextInt() * 30;
    }

    if (GCL_GetOption('p'))
    {
        proc = GCL_GetNextInt();
    }

    NewCountdown(time, proc);
}
