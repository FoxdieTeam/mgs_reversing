#include "linker.h"
#include "libdg.h"

extern void GV_Free_80016230(void *ptr);

void Prim_free_colour_buffer_80032110(DG_OBJS *pPrim)
{
    CVECTOR *pBuffer = pPrim->objs[0].rgbs;
    if (pBuffer)
    {
        GV_Free_80016230(pBuffer);
        pPrim->objs[0].rgbs = 0;
    }
}
