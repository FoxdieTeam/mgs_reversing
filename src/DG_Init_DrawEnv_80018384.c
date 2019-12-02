#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2)
{
    setRECT(&pDrawEnv->clip, clipX1, clipY1, clipX2, clipY2);
    pDrawEnv->ofs[0] = clipX1;
    pDrawEnv->ofs[1] = clipY1;
    pDrawEnv->dtd = 1;
    pDrawEnv->dfe = 0;
    setRECT(&pDrawEnv->tw, 0, 0, 0, 0);
    setRGB0(pDrawEnv, 0, 0, 0);
    pDrawEnv->tpage = 0;
    pDrawEnv->isbg = 0;
}
