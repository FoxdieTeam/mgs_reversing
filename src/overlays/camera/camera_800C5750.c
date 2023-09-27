#include "libgv/libgv.h"

extern void *camera_dword_800D075C;

void camera_800C5750(void)
{
    GV_FreeMemory_80015FD0(2, camera_dword_800D075C);
}
