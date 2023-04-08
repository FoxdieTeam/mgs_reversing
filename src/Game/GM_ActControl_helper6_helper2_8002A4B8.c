#include "unknown.h"
#include "libhzd/libhzd.h"
#include "Game/control.h"

void GM_ActControl_helper6_helper2_8002A4B8(HZD_MAP *pMap, Res_Control_unknown *arg1)
{
    int    count;
    short *pData;

    pData = (short *)getScratchAddr(7);

    arg1->field_2_name_hash = 0xD5CC;

    for (count = *getScratchAddr(6); count > 0; count--)
    {
        arg1->field_4_trigger_Hash_Name_or_camera_w = *pData++;
        sub_80029D50(pMap, arg1, 0);
    }
}
