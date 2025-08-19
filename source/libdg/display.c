#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg.h"
#include "common.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"

/*** data ***/
STATIC VECTOR SECTION(".data") DG_UpVector = {0, -4096, 0, 0};

/*** $gp ***/
int DG_UnDrawFrameCount = 0;
STATIC int DG_CurrentBuffer = -1;

STATIC int SECTION(".sbss") gClipHeights_800AB960[2];
int   SECTION(".sbss") DG_CurrentGroupID;
short SECTION(".sbss") DG_ClipMin[2];
short SECTION(".sbss") DG_ClipMax[2];

/*** bss ***/
extern DISPENV g_dispenv;
extern VECTOR  DG_RightVector_800B0620;

void DG_InitDispEnv(int x, short y, short w, short h, int clipH)
{
    DISPENV *dispenv = &g_dispenv;
    RECT    *disp;
    RECT    *screen;

    disp = &dispenv->disp;
    screen = &dispenv->screen;

    setRECT(disp, x, y, w, h);
    setRECT(screen, 0, 0, 256, SCREEN_HEIGHT);

    dispenv->isinter = 0;
    dispenv->isrgb24 = 0;

    // For some reason lets overwrite what we already setup
    dispenv->screen.y = 8;
    dispenv->screen.h = FRAME_HEIGHT;

    gClipHeights_800AB960[0] = x;
    gClipHeights_800AB960[1] = x + clipH;
}

void DG_ChangeReso(int flag)
{
#if 0
    DRAWENV drawenv;

    if ((flag & 1) == 0) {
        g_dispenv.disp.w = 320;
        g_dispenv.screen.x = 0;
        g_dispenv.screen.w = 255;
    } else {
        g_dispenv.disp.w = 384;
        g_dispenv.screen.x = 26;
        g_dispenv.screen.w = 212;
    }

    if ((flag & 2) == 0) {
        g_dispenv.screen.h = 256;
    } else {
        g_dispenv.screen.h = 224;
    }

    g_dispenv.screen.y = 16;

    if ((flag & 4) == 0) {
        g_dispenv.disp.y = 0;
        g_dispenv.disp.h = 256;
    } else {
        g_dispenv.disp.h = 224;
        g_dispenv.disp.y = (g_dispenv.screen.h - 224) / 2;
    }

    if ((flag & 8) != 0) {
        PutDispEnv(&g_dispenv);
    }

    SetDefDrawEnv(&drawenv, 0, 0, 320, g_dispenv.disp.h);
    drawenv.isbg = 1;
    DG_SetRenderChanlDrawEnv(-1, &drawenv);
#endif
}

void DG_RenderPipeline_Init(void)
{
    DG_ClearChanlSystem(0);
    DG_ClearChanlSystem(1);
    DG_RenderPipeline(0);
    DG_RenderPipeline(1);
}

void DG_SwapFrame(void)
{
    int activeBuffer = GV_Clock;

    if ((GV_PauseLevel & 8) != 0 || DG_UnDrawFrameCount > 0)
    {
        if (DG_CurrentBuffer < 0)
        {
            DG_CurrentBuffer = activeBuffer;
        }
        if ((GV_PauseLevel & 8) == 0)
        {
            --DG_UnDrawFrameCount;
        }
    }
    else if (DG_CurrentBuffer < 0 || activeBuffer != DG_CurrentBuffer)
    {
        DISPENV *p = &g_dispenv;
        p->disp.x = gClipHeights_800AB960[activeBuffer];

        PutDispEnv(&g_dispenv);
        if (!DG_HikituriFlagOld)
        {
            DG_DrawOTag(1 - activeBuffer);
        }
        DG_CurrentBuffer = -1;
    }
    GV_ClearMemorySystem(activeBuffer);
    if (!DG_HikituriFlagOld)
    {
        GV_ClearMemorySystem(GV_NORMAL_MEMORY);
    }
    MENU_ResetSystem();
    DG_ClearChanlSystem(activeBuffer);
    DG_ClearTmpLight();
}

void DG_RenderFrame(void)
{
    DG_RenderPipeline(GV_Clock);
}

void DG_LookAt(DG_CHANL *chanl, SVECTOR *eye, SVECTOR *center, int clip_distance)
{
    VECTOR  forward;
    VECTOR  up;
    VECTOR  right;
    MATRIX *view;

    chanl->clip_distance = clip_distance;

    view = &chanl->eye;
    view->t[0] = eye->vx;
    view->t[1] = eye->vy;
    view->t[2] = eye->vz;

    forward.vx = (signed short)(((u_short)center->vx - (u_short)eye->vx));
    forward.vy = (signed short)(((u_short)center->vy - (u_short)eye->vy));
    forward.vz = (signed short)(((u_short)center->vz - (u_short)eye->vz));

    OuterProduct12(&DG_UpVector, &forward, &right);

    if (!right.vx && !right.vy && !right.vz)
    {
        right = DG_RightVector_800B0620;
    }
    else
    {
        DG_RightVector_800B0620 = right;
    }

    VectorNormal(&right, &right);
    VectorNormal(&forward, &forward);

    OuterProduct12(&forward, &right, &up);

    view->m[0][0] = right.vx;
    view->m[0][1] = up.vx;
    view->m[0][2] = forward.vx;

    view->m[1][0] = right.vy;
    view->m[1][1] = up.vy;
    view->m[1][2] = forward.vy;

    view->m[2][0] = right.vz;
    view->m[2][1] = up.vz;
    view->m[2][2] = forward.vz;

    DG_TransposeMatrix(view, &chanl->eye_inv);

    forward.vx = -view->t[0];
    forward.vy = -view->t[1];
    forward.vz = -view->t[2];

    ApplyMatrixLV(&chanl->eye_inv, &forward, (VECTOR *)chanl->eye_inv.t);
}

void DG_AdjustOverscan(MATRIX *matrix)
{
    matrix->m[1][0] = (matrix->m[1][0] * 58) / 64;
    matrix->m[1][1] = (matrix->m[1][1] * 58) / 64;
    matrix->m[1][2] = (matrix->m[1][2] * 58) / 64;
    matrix->t[1] = (matrix->t[1] * 58) / 64;
}

void DG_Clip(RECT *clip_rect, int dist)
{
    int x_tmp;
    int y_tmp;

    gte_SetGeomScreen(dist);

    x_tmp = clip_rect->x;
    DG_ClipMin[0] = x_tmp;
    DG_ClipMax[0] = clip_rect->w + x_tmp - 1;

    y_tmp = clip_rect->y;
    DG_ClipMin[1] = y_tmp;
    DG_ClipMax[1] = clip_rect->h + y_tmp - 1;
}

void DG_ApplyMatrix(MATRIX *world, MATRIX *in)
{
    MATRIX out;

    gte_SetRotMatrix(world);

    gte_ldclmv(in);
    gte_rtir();
    gte_stclmv(&out);

    gte_ldclmv(&in->m[0][1]);
    gte_rtir();
    gte_stclmv(&out.m[0][1]);

    gte_ldclmv(&in->m[0][2]);
    gte_rtir();
    gte_stclmv(&out.m[0][2]);

    gte_SetTransMatrix(world);

    gte_ldlv0(in->t);
    gte_rt();
    gte_stlvnl(out.t);

    DG_AdjustOverscan(&out);

    gte_SetRotMatrix(&out);
    gte_SetTransMatrix(&out);
}

void DG_OffsetDispEnv(int offset)
{
    g_dispenv.screen.y += offset;
    g_dispenv.screen.h -= offset;
    PutDispEnv(&g_dispenv);
    g_dispenv.screen.y -= offset;
    g_dispenv.screen.h += offset;
}

void DG_ClipDispEnv(int x, int y)
{
    RECT screen;

    screen = g_dispenv.screen;
    g_dispenv.screen.x = 128 - x / 2;
    g_dispenv.screen.w = x;
    g_dispenv.screen.y = 120 - y / 2;
    g_dispenv.screen.h = y;
    PutDispEnv(&g_dispenv);
    g_dispenv.screen = screen;
}

void DG_DisableClipping(void)
{
    DRAWENV drawenv;

    DG_InitDrawEnv(&drawenv,
        g_dispenv.disp.x, g_dispenv.disp.y,
        g_dispenv.disp.w, g_dispenv.disp.h);
    PutDrawEnv(&drawenv);
}

void DG_FadeScreen(int amount)
{
    DR_TPAGE tpage;
    TILE     tile;

    DG_DisableClipping();

    setDrawTPage(&tpage, 1, 1, GetTPage(0, 2, 0, 0));
    DrawPrim(&tpage);

    tile.x0 = 0;
    tile.y0 = 0;
    tile.w = FRAME_WIDTH;
    tile.h = FRAME_HEIGHT;
    LSTORE(amount << 16 | amount << 8 | amount, &tile.r0);
    setTile(&tile);
    setSemiTrans(&tile, 1);
    DrawPrim(&tile);
}

// guessed function name
DISPENV *DG_GetDisplayEnv(void)
{
    return &g_dispenv;
}
