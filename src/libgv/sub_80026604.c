#include "libgv\libgv.h"

extern short word_8009D528[];

int sub_80026604(int arg0, int arg1, int arg2)
{
    short var_a0;
    int   var_v0;

    var_v0 = arg1;

    if (arg2 > 15)
    {
        arg2 = 15;
        var_v0 = arg1;
    }

    arg2 = word_8009D528[arg2];
    var_a0 = FP_Subtract(arg0, var_v0);

    arg1 = var_v0 + var_a0;

    if (arg2 == 0)
    {
        return var_v0;
    }

    var_v0 = (var_v0 - arg1) * arg2;
    return (var_v0 / 4096) + arg1;
}