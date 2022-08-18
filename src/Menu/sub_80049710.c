#include "radio.h"

void sub_80049710(int param_1, int param_2, int param_3)
{
    int *data;

    data = sub_8004969C(param_1, param_2);
    if (data)
    {
        if (param_3 >= 0)
        {
            data[0] = param_2;
            data[1] = param_3;
        }

        else
        {
            data[0] = 0;
            data[1] = 0;
        }
    }
}
