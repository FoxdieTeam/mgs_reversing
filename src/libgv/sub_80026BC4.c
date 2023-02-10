#include "libgv/libgv.h"

extern short word_8009D528[];

void sub_80026BC4(short* param_1, short* param_2, int param_3, int param_4)
{
    short temp_t1;
    short temp_t2;

    int var_v0;
    int temp_v1_2;
    int var_v0_2;
    
    if (param_3 >= 0x10)
    {
        param_3 = 0xF;
    }
    
    param_3 = word_8009D528[param_3];

    for (param_4--; param_4 >= 0; param_4--)
    {
        temp_t2 = *param_1;
        temp_t1 = *param_2;

        temp_v1_2 = temp_t1 + FP_Subtract(temp_t2, temp_t1);

        if (param_3 == 0)
        {
            var_v0 = temp_t1;
        }
        else
        {
            var_v0_2 = (temp_t1 - temp_v1_2) * param_3;                
            var_v0 = ((var_v0_2) / 4096) + temp_v1_2;
        }

        *param_1++ = var_v0;
        param_2++;
    }
}
