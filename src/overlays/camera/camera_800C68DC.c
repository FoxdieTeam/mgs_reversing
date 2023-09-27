#include "libgv/libgv.h"

extern char camera_aCloseinfo_800CFFE0[];

void camera_800C68DC(void *ptr)
{
    printf(camera_aCloseinfo_800CFFE0);
    if (ptr)
    {
        GV_FreeMemory_80015FD0(2, ptr);
    }
}
