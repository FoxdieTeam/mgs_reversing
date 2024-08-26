#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libdg.h"
#include "psyq.h"
#include "Menu/menuman.h"

/**data************************/
VECTOR SECTION(".data") DG_UpVector_8009D34C = {0, -4096, 0, 0};
/******************************/

/**gp***********************************************************************************************/
int DG_UnDrawFrameCount_800AB380 = 0;
int DG_CurrentBuffer_800AB384 = -1;

int   SECTION(".sbss") gClipHeights_800AB960[2];
int   SECTION(".sbss") DG_CurrentGroupID_800AB968;
short SECTION(".sbss") DG_ClipMin_800AB96C[2];
short SECTION(".sbss") DG_ClipMax_800AB970[2];
/***************************************************************************************************/

/**sbss**********************************/
extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;
extern int DG_HikituriFlagOld_8009D464;
/****************************************/

/**bss************************************************************************/
extern DISPENV gDispEnv_800B0600;
extern VECTOR  DG_RightVector_800B0620;
/****************************************************************************/

void DG_InitDispEnv_800170F0(int x, short y, short w, short h, int clipH)
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

void DG_ChangeReso_80017154(void)
{
}

void DG_RenderPipeline_Init_8001715C(void)
{
    DG_ClearChanlSystem_80017E9C(0);
    DG_ClearChanlSystem_80017E9C(1);
    DG_RenderPipeline_80018028(0);
    DG_RenderPipeline_80018028(1);
}

void DG_SwapFrame_80017194()
{
    int activeBuffer = GV_Clock_800AB920;
    if ((GV_PauseLevel_800AB928 & 8) != 0 || DG_UnDrawFrameCount_800AB380 > 0)
    {
        if (DG_CurrentBuffer_800AB384 < 0)
        {
            DG_CurrentBuffer_800AB384 = activeBuffer;
        }
        if ((GV_PauseLevel_800AB928 & 8) == 0)
        {
            --DG_UnDrawFrameCount_800AB380;
        }
    }
    else if (DG_CurrentBuffer_800AB384 < 0 || activeBuffer != DG_CurrentBuffer_800AB384)
    {
        DISPENV *p = &gDispEnv_800B0600;
        p->disp.x = gClipHeights_800AB960[activeBuffer];

        PutDispEnv(&gDispEnv_800B0600);
        if (!DG_HikituriFlagOld_8009D464)
        {
            DG_DrawOTag_80017E4C(1 - activeBuffer);
        }
        DG_CurrentBuffer_800AB384 = -1;
    }
    GV_ClearMemorySystem_80015B4C(activeBuffer);
    if (!DG_HikituriFlagOld_8009D464)
    {
        GV_ClearMemorySystem_80015B4C(2);
    }
    menu_ResetSystem_80038A88();
    DG_ClearChanlSystem_80017E9C(activeBuffer);
    DG_ClearTmpLight_8001A0E4();
}

void DG_RenderPipeline_800172A8(void)
{
    DG_RenderPipeline_80018028(GV_Clock_800AB920);
}

void DG_LookAt_800172D0(DG_CHNL *chnl, SVECTOR *eye, SVECTOR *center, int clip_distance)
{
    VECTOR  forward;
    VECTOR  up;
    VECTOR  right;
    MATRIX *view;

    chnl->field_50_clip_distance = clip_distance;

    view = &chnl->field_30_eye;
    view->t[0] = eye->vx;
    view->t[1] = eye->vy;
    view->t[2] = eye->vz;

    forward.vx = (signed short)(((unsigned short)center->vx - (unsigned short)eye->vx));
    forward.vy = (signed short)(((unsigned short)center->vy - (unsigned short)eye->vy));
    forward.vz = (signed short)(((unsigned short)center->vz - (unsigned short)eye->vz));

    OuterProduct12(&DG_UpVector_8009D34C, &forward, &right);

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

    DG_TransposeMatrix_8001EAD8(view, &chnl->field_10_eye_inv);

    forward.vx = -view->t[0];
    forward.vy = -view->t[1];
    forward.vz = -view->t[2];

    ApplyMatrixLV(&chnl->field_10_eye_inv, &forward, (VECTOR *)chnl->field_10_eye_inv.t);
}

void DG_800174DC(MATRIX *matrix)
{
    matrix->m[1][0] = (matrix->m[1][0] * 58) / 64;
    matrix->m[1][1] = (matrix->m[1][1] * 58) / 64;
    matrix->m[1][2] = (matrix->m[1][2] * 58) / 64;
    matrix->t[1] = (matrix->t[1] * 58) / 64;
}

void DG_Clip_80017594(RECT *pClipRect, int dist)
{
    int xTmp;
    int yTmp;
    gte_SetGeomScreen(dist);
    xTmp = pClipRect->x;
    DG_ClipMin_800AB96C[0] = xTmp;
    DG_ClipMax_800AB970[0] = pClipRect->w + xTmp - 1;
    yTmp = pClipRect->y;
    DG_ClipMin_800AB96C[1] = yTmp;
    DG_ClipMax_800AB970[1] = pClipRect->h + yTmp - 1;
}

void sub_800175E0(MATRIX *matrix, MATRIX *matrix2)
{
    MATRIX matrix3;

    gte_SetRotMatrix(matrix);
    gte_ldclmv(matrix2);
    gte_rtir();

    gte_stclmv(&matrix3);
    gte_ldclmv(&matrix2->m[0][1]);
    gte_rtir();

    gte_stclmv(&matrix3.m[0][1]);
    gte_ldclmv(&matrix2->m[0][2]);
    gte_rtir();

    gte_stclmv(&matrix3.m[0][2]);
    gte_SetTransMatrix(matrix);
    gte_ldlv0(matrix2->t);

    gte_mvmva(1, 0, 0, 0, 0);
    gte_stlvnl(matrix3.t);

    DG_800174DC(&matrix3);
    gte_SetRotMatrix(&matrix3);
    gte_SetTransMatrix(&matrix3);
}

void DG_OffsetDispEnv_80017784(int offset)
{
    gDispEnv_800B0600.screen.y += offset;
    gDispEnv_800B0600.screen.h -= offset;
    PutDispEnv(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen.y -= offset;
    gDispEnv_800B0600.screen.h += offset;
}

void DG_ClipDispEnv_800177EC(int x, int y)
{
    RECT screen; // [sp+10h] [-8h]

    screen = gDispEnv_800B0600.screen;
    gDispEnv_800B0600.screen.x = 128 - x / 2;
    gDispEnv_800B0600.screen.w = x;
    gDispEnv_800B0600.screen.y = 120 - y / 2;
    gDispEnv_800B0600.screen.h = y;
    PutDispEnv(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen = screen;
}

void DG_PutDrawEnv_From_DispEnv_80017890(void)
{
    DRAWENV drawEnv;
    DG_Init_DrawEnv_80018384(&drawEnv, gDispEnv_800B0600.disp.x, gDispEnv_800B0600.disp.y, gDispEnv_800B0600.disp.w,
                             gDispEnv_800B0600.disp.h);
    PutDrawEnv(&drawEnv);
}

void DG_800178D8(int shade)
{
    DR_TPAGE    tpage;
    TILE_PACKED tile;

    DG_PutDrawEnv_From_DispEnv_80017890();

    setDrawTPage(&tpage, 1, 1, GetTPage(0, 2, 0, 0));

    DrawPrim(&tpage);

    tile.w = 0x140;
    tile.h = 0xE0;

    SetPackedRGB(&tile, shade, shade, shade);

    tile.x0 = 0;
    tile.y0 = 0;

    setTile(&tile);
    setSemiTrans(&tile, 1);
    DrawPrim(&tile);
}

// guessed function name
DISPENV *DG_GetDisplayEnv_80017978(void)
{
    return &gDispEnv_800B0600;
}
