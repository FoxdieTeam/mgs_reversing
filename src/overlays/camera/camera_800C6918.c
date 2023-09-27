#include "libgv/libgv.h"

extern char camera_aNomemoryforinfo_800CFFEC[];
extern char camera_aAllocinfox_800D0000[];

void camera_800C6918(void **arg0, int arg1)
{
    void *temp_v0;

    if (*arg0 == NULL)
    {
        temp_v0 = GV_AllocMemory_80015EB8(2, (arg1 * 0x24) + 0x24);
        *arg0 = temp_v0;
        if (temp_v0 == NULL)
        {
            printf(camera_aNomemoryforinfo_800CFFEC);
        }
        printf(camera_aAllocinfox_800D0000, *arg0);
    }
}
