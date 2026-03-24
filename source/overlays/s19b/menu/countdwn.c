#include "game/game.h"
#include "libgcl/libgcl.h"
#include "menu/radar.h"
#include "menu/radio.h"

RadioUnknown s19b_dword_800C3258 =
{
    {{1, 0, 7, 2}, {0, 1, 2, 7}, {7, 1, 2, 7}, {1, 7, 7, 2}, {0, 9, 2, 6}, {7, 9, 2, 6}, {1, 14, 7, 2}},
    0x182589,
    0x818
};

RadioUnknown s19b_dword_800C327C =
{
    {{1, 0, 5, 2}, {0, 1, 2, 5}, {5, 1, 2, 5}, {1, 5, 5, 2}, {0, 7, 2, 5}, {5, 7, 2, 5}, {1, 11, 5, 2}},
    0x182589,
    0x818
};

u_char s19b_dword_800C32A0[] = {0x03, 0x0D, 0x1B, 0x25, 0x33, 0x3B};
u_char s19b_dword_800C32A8[] = {0x20, 0x20, 0x20, 0x20, 0x23, 0x23};
u_char s19b_dword_800C32B0[] = {0x18, 0x24, 0x18, 0x2B, 0x30, 0x25, 0x30, 0x2C};
u_char s19b_dword_800C32B8[] = {0x01, 0x1D, 0x43, 0x01};

int     SECTION(".bss") countdown_time;
int     SECTION(".bss") countdown_proc;
DG_TEX *SECTION(".bss") warn1_texture;
DG_TEX *SECTION(".bss") warn2_texture;

#define EXEC_LEVEL 5

STATIC void draw_image(MenuPrim *prim, int x, int y, char shade, DG_TEX *tex)
{
    POLY_FT4 *poly;

    _NEW_PRIM(poly, prim);
    DG_SetPacketTexture4(poly, tex);
    setRGB0(poly, shade, shade, shade);
    setXYWH(poly, x, y, tex->w, tex->h);

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    addPrim(prim->mPrimBuf.mOt, poly);
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

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_countdwn_800C3C90.s")
void s19b_countdwn_800C3C90(MenuWork *, u_char *);

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

    work = GV_NewActor(EXEC_LEVEL, sizeof(GV_ACT));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "countdwn.c");
        MENU_SetRadarFunc(s19b_countdwn_800C3C90);
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
        time = GCL_GetNextParamValue() * 30;
    }

    if (GCL_GetOption('p'))
    {
        proc = GCL_GetNextParamValue();
    }

    NewCountdown(time, proc);
}
