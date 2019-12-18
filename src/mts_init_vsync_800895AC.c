#include "linker.h"
#include "mts_new.h"

extern int gMtsVSyncCount_800A3D78;

void mts_init_vsync_helper_800893E8(void);

int VSync_80098108(int);
void VSyncCallback_800983A8(void (*func)());

void mts_init_vsync_800895AC(void)
{
    if (gMtsVSyncCount_800A3D78 == -1)
    {
        gMtsVSyncCount_800A3D78 =  VSync_80098108(-1);
        VSyncCallback_800983A8(mts_init_vsync_helper_800893E8);
    }
}

