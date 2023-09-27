#include "libdg/libdg.h"

void camera_800C5D2C(SPRT *pPrim)
{
    LSTORE(0x80808080, &pPrim->r0);
    setSprt(pPrim);
    setClut(pPrim, 960, 510);
} 
