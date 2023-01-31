#include "GM_Control.h"

void HZD_SetEvent_80029AB4(Res_Control_unknown *param_1, short param_2)
{
    int    i;
    unsigned short *tmp;

    param_1->field_0_scriptData_orHashedName = param_2;
    param_1->field_6_count = 0;
    param_1->field_4_trigger_Hash_Name_or_camera_w = 0;
    param_1->field_2_name_hash = 0;

    tmp = param_1->field_8_array;

    for (i = 6; i > 0; i--)
    {
        *tmp++ = 0;
    }

    param_1->field_14_vec.vz = 0;
    param_1->field_14_vec.vy = 0;
    param_1->field_14_vec.vx = 0;
}
