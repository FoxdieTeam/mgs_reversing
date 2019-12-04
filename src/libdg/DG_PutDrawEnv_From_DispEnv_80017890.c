#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern DISPENV gDispEnv_800B0600;

void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void PutDrawEnv_8008FEC8(DRAWENV*);

void DG_PutDrawEnv_From_DispEnv_80017890(void)
{
    DRAWENV drawEnv;
    DG_Init_DrawEnv_80018384(&drawEnv, gDispEnv_800B0600.disp.x, gDispEnv_800B0600.disp.y, gDispEnv_800B0600.disp.w, gDispEnv_800B0600.disp.h);
    PutDrawEnv_8008FEC8(&drawEnv);
}
