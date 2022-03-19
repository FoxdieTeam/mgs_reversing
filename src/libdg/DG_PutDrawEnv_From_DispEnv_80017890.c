#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern DISPENV gDispEnv_800B0600;

void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void PutDrawEnv_8008FEC8(DRAWENV*);
DISPENV* PutDispEnv_80090094(DISPENV*);

void DG_ClipDispEnv_800177EC(int x, int y)
{
    RECT screen; // [sp+10h] [-8h]

    screen = gDispEnv_800B0600.screen;
    gDispEnv_800B0600.screen.x = 128 - x / 2;
    gDispEnv_800B0600.screen.w = x;
    gDispEnv_800B0600.screen.y = 120 - y / 2;
    gDispEnv_800B0600.screen.h = y;
    PutDispEnv_80090094(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen = screen;
}

void DG_PutDrawEnv_From_DispEnv_80017890(void)
{
    DRAWENV drawEnv;
    DG_Init_DrawEnv_80018384(&drawEnv, gDispEnv_800B0600.disp.x, gDispEnv_800B0600.disp.y, gDispEnv_800B0600.disp.w, gDispEnv_800B0600.disp.h);
    PutDrawEnv_8008FEC8(&drawEnv);
}
