#include "game/game.h"
#include "libgcl/libgcl.h"
#include "menu/radar.h"
#include "menu/radio.h"
#include "strcode.h"

STATIC RadioUnknown digit_font_large =
{
    {{1, 0, 7, 2}, {0, 1, 2, 7}, {7, 1, 2, 7}, {1, 7, 7, 2}, {0, 9, 2, 6}, {7, 9, 2, 6}, {1, 14, 7, 2}},
    0x182589,
    0x818
};

STATIC RadioUnknown digit_font_small =
{
    {{1, 0, 5, 2}, {0, 1, 2, 5}, {5, 1, 2, 5}, {1, 5, 5, 2}, {0, 7, 2, 5}, {5, 7, 2, 5}, {1, 11, 5, 2}},
    0x182589,
    0x818
};

STATIC u_char digit_x[] = {0x03, 0x0D, 0x1B, 0x25, 0x33, 0x3B};
STATIC u_char digit_y[] = {0x20, 0x20, 0x20, 0x20, 0x23, 0x23};
STATIC u_char colon_pos[] = {0x18, 0x24, 0x18, 0x2B, 0x30, 0x25, 0x30, 0x2C};
STATIC u_char frame_lines[] = {0x01, 0x1D, 0x43, 0x01, 0x01, 0x32, 0x43, 0x01};

int     SECTION(".bss") countdown_time;
int     SECTION(".bss") countdown_proc;
DG_TEX *SECTION(".bss") warn1_texture;
DG_TEX *SECTION(".bss") warn2_texture;

STATIC void draw_image(MenuPrim *prim, int x, int y, int shade, DG_TEX *tex)
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

static void draw_countdown(MenuWork *work, u_long *ot)
{
    RadioUnknown *font;
    u_char       *rect;
    int           time;
    int           i;
    int           base;
    int           value;
    int           tens;
    int           color;
    int           shade;

    time = countdown_time * 100 / 30;

    if (countdown_time > 0)
    {
        if (--countdown_time == 0)
        {
            exec_countdown_proc();
        }
    }

    for (i = 0; i < 8; i += 2)
    {
        TILE *tile;

        NEW_PRIM(tile, work);

        tile->x0 = colon_pos[i] - 34;
        tile->y0 = colon_pos[i + 1] - 26;
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

    font = &digit_font_small;
    base = 100;

    for (i = 5; i >= 0; i -= 2)
    {
        value = time % base;
        tens = value / 10;
        time /= base;
        sub_8003FD50(work->prim, digit_x[i] - 34, digit_y[i] - 26, value % 10, font, 1);
        sub_8003FD50(work->prim, digit_x[i - 1] - 34, digit_y[i - 1] - 26, tens, font, 1);

        font = &digit_font_large;
        base = 60;
    }

    rect = frame_lines;
    for (i = 2; i > 0; i--)
    {
        TILE *tile;

        NEW_PRIM(tile, work);

        tile->x0 = rect[0] - 34;
        tile->y0 = rect[1] - 26;

        LSTORE(0x182589, &tile->r0);
        tile->w = rect[2];
        tile->h = rect[3];
        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(ot, tile);

        rect += 4;
    }

    {
        DR_TPAGE *tpage;

        NEW_PRIM(tpage, work);
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 960, 256));
        addPrim(ot, tpage);
    }

    shade = GV_Time % 16;
    if (shade < 8)
    {
        shade = 128 - shade * 16;
    }
    else
    {
        shade = 128;
    }

    draw_image(work->prim, -34, -25, shade, warn1_texture);
    draw_image(work->prim, -33, -13, 128, warn2_texture);

    {
        TILE *tile;

        NEW_PRIM(tile, work);
        tile->x0 = -34;
        tile->w = 69;
        tile->y0 = -26;
        tile->h = 52;
        LSTORE(0xDE, &tile->r0);
        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(ot, tile);
    }

    {
        DR_TPAGE *tpage;

        NEW_PRIM(tpage, work);
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(ot, tpage);
    }
}


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
        MENU_SetRadarFunc(draw_countdown);
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
