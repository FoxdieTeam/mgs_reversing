#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg.h"
#include "common.h"
#include "Menu/menuman.h"

/*** data ***/
STATIC VECTOR SECTION(".data") DG_UpVector = {0, -4096, 0, 0};

/*** $gp ***/
int DG_UnDrawFrameCount = 0;
STATIC int DG_CurrentBuffer = -1;

STATIC int SECTION(".sbss") gClipHeights_800AB960[2];
int   SECTION(".sbss") DG_CurrentGroupID;
short SECTION(".sbss") DG_ClipMin[2];
short SECTION(".sbss") DG_ClipMax[2];

/*** sbss ***/
extern int GV_Clock;
extern int GV_PauseLevel;

/*** bss ***/
extern DISPENV gDispEnv_800B0600;
extern VECTOR  DG_RightVector_800B0620;

void DG_InitDispEnv(int x, short y, short w, short h, int clipH)
{
    DISPENV *pDispEnv = &gDispEnv_800B0600;
    RECT    *pDispRect;
    RECT    *pScreenRect;

    pDispRect = &pDispEnv->disp;
    pScreenRect = &pDispEnv->screen;

    setRECT(pDispRect, x, y, w, h);
    setRECT(pScreenRect, 0, 0, 256, 240);

    pDispEnv->isinter = 0;
    pDispEnv->isrgb24 = 0;

    // For some reason lets overwrite what we already setup
    pDispEnv->screen.y = 8;
    pDispEnv->screen.h = 224;

    gClipHeights_800AB960[0] = x;
    gClipHeights_800AB960[1] = x + clipH;
}

void DG_ChangeReso(int arg0)
{
    /* do nothing */
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
        DISPENV *p = &gDispEnv_800B0600;
        p->disp.x = gClipHeights_800AB960[activeBuffer];

        PutDispEnv(&gDispEnv_800B0600);
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

void DG_RenderPipeline_800172A8(void)
{
    DG_RenderPipeline(GV_Clock);
}

void DG_LookAt(DG_CHANL *chanl, SVECTOR *eye, SVECTOR *center, int clip_distance)
{
    VECTOR  forward;
    VECTOR  up;
    VECTOR  right;
    MATRIX *view;

    chanl->field_50_clip_distance = clip_distance;

    view = &chanl->field_30_eye;
    view->t[0] = eye->vx;
    view->t[1] = eye->vy;
    view->t[2] = eye->vz;

    forward.vx = (signed short)(((unsigned short)center->vx - (unsigned short)eye->vx));
    forward.vy = (signed short)(((unsigned short)center->vy - (unsigned short)eye->vy));
    forward.vz = (signed short)(((unsigned short)center->vz - (unsigned short)eye->vz));

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

    DG_TransposeMatrix(view, &chanl->field_10_eye_inv);

    forward.vx = -view->t[0];
    forward.vy = -view->t[1];
    forward.vz = -view->t[2];

    ApplyMatrixLV(&chanl->field_10_eye_inv, &forward, (VECTOR *)chanl->field_10_eye_inv.t);
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
    gDispEnv_800B0600.screen.y += offset;
    gDispEnv_800B0600.screen.h -= offset;
    PutDispEnv(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen.y -= offset;
    gDispEnv_800B0600.screen.h += offset;
}

void DG_ClipDispEnv(int x, int y)
{
    RECT screen;

    screen = gDispEnv_800B0600.screen;
    gDispEnv_800B0600.screen.x = 128 - x / 2;
    gDispEnv_800B0600.screen.w = x;
    gDispEnv_800B0600.screen.y = 120 - y / 2;
    gDispEnv_800B0600.screen.h = y;
    PutDispEnv(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen = screen;
}

void DG_DisableClipping(void)
{
    DRAWENV dr_env;
    DG_InitDrawEnv(&dr_env,
                   gDispEnv_800B0600.disp.x,
                   gDispEnv_800B0600.disp.y,
                   gDispEnv_800B0600.disp.w,
                   gDispEnv_800B0600.disp.h);
    PutDrawEnv(&dr_env);
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
    tile.w = 320;
    tile.h = 224;
    LSTORE(amount << 16 | amount << 8 | amount, &tile.r0);
    setTile(&tile);
    setSemiTrans(&tile, 1);
    DrawPrim(&tile);
}

// guessed function name
DISPENV *DG_GetDisplayEnv(void)
{
    return &gDispEnv_800B0600;
}
