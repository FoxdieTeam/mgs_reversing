#include "linker.h"
#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>
#include <inline_c.h>


// re-declare to force GP usage
extern short DG_ClipMin_800AB96C[2];
short SECTION(".sbss") DG_ClipMin_800AB96C[2];

extern short DG_ClipMax_800AB970[2];
short SECTION(".sbss") DG_ClipMax_800AB970[2];

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
