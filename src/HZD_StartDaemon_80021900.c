#include "idaTypes.h"
#include "dgd.h"

extern int  HZD_LoadInitHzd_800219F4(int a1);

void HZD_StartDaemon_80021900(void)
{
    GV_SetLoader_80015418(0x68, (TFileExtHandler)&HZD_LoadInitHzd_800219F4);
}
