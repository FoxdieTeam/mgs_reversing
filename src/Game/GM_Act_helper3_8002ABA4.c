

#include "idaTypes.h"

extern int              GV_PauseLevel_800AB928;

extern unsigned int     sub_8002AAEC();
extern unsigned long    sub_8002AB40();

int GM_Act_helper3_8002ABA4(void)
{
    int var1;
    int var2;
    int ret;

    var1 = GV_PauseLevel_800AB928;
    var2 = var1 & ~2;
    ret = var2;
    if (var2 == 0)
    {
        if ((var1 & 2) == 0)
        {
            return sub_8002AB40();
        }
        ret = sub_8002AAEC();
    }
    return ret;
}
