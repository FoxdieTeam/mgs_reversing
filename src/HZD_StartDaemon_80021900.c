#include "idaTypes.h"
#include "dgd.h"

extern int  HZD_FileHandler_800219F4(int a1);

void HZD_StartDaemon_80021900(void)
{
    GV_SetFileHandler_80015418(0x68, &HZD_FileHandler_800219F4);
}
