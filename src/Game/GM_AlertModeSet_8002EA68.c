#include "game.h"
#include "linker.h"

extern char byte_8009D698[];

extern short GM_RadarMode_800ABA80;
short SECTION(".sbss") GM_RadarMode_800ABA80;

void GM_AlertModeSet_8002EA68(int a1)
{
    if (a1 > GM_RadarMode_800ABA80)
    {
        GM_RadarMode_800ABA80 = a1;
        GM_CallSystemCallbackProc_8002B570(2, byte_8009D698[a1]);
    }
}
