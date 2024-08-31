#include "libgv.h"
#include "linker.h"

short TimeInv_8009D528[] = {
    0x0, 0x800, 0x555, 0x400, 0x333, 0x2AA, 0x249, 0x200,
    0x1C7, 0x199, 0x174, 0x155, 0x13B, 0x124, 0x111, 0x100
};

int GV_NearExp2(int from, int to)
{
    int diff = to - from;

    if ((diff <= -2) || (diff >= 2))
    {
        return from + diff / 2;
    }

    return to;
}

int GV_NearExp4(int from, int to)
{
    int diff = to - from;

    if ((diff > -4) && (diff < 4))
    {
        return to;
    }

    return from + diff / 4;
}

int GV_NearExp8(int from, int to)
{
    int diff = to - from;

    if ((diff > -8) && (diff < 8))
    {
        return to;
    }

    return from + diff / 8;
}

int GV_NearDiffP(int from, int to)
{
    return to + FP_Subtract(from, to);
}

int sub_80026440(int from, int to, int range)
{
    int iVar1;

    iVar1 = to - range;

    if ((from < iVar1) || (iVar1 = to + range, from > iVar1))
    {
        from = iVar1;
    }

    return from;
}

static inline int sub_8002646C_helper(int a, int b, int range)
{
    int new_a;

    if (a < b)
    {
        new_a = a + range;
        if (new_a >= b)
        {
            return b;
        }
    }
    else
    {
        new_a = a - range;
        if (b >= new_a)
        {
            return b;
        }
    }
    return new_a;
}

int sub_8002646C(int a, int b, int range)
{
    return sub_8002646C_helper(a, b, range);
}

int GV_NearTime(int from, int to, int interp)
{
    int diff;

    if (interp > 15)
    {
        interp = 15;
    }

    interp = TimeInv_8009D528[interp];

    if (interp == 0)
    {
        return to;
    }

    diff = to - from;
    return ((diff * interp) / 4096) + from;
}

int GV_NearExp2P(int from, int to)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(from, to);

    iVar2 = to - (to + uVar1);

    if (iVar2 + 1 >= 3U)
    {
        return to + uVar1 + (iVar2 / 2);
    }

    return to;
}

int GV_NearExp4P(int from, int to)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(from, to);

    iVar2 = to - (to + uVar1);

    if ((iVar2 + 3 < 7U))
    {
        return to;
    }

    return to + uVar1 + (iVar2 / 4);
}

int GV_NearExp8P(int from, int to)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(from, to);

    iVar2 = to - (to + uVar1);

    if ((iVar2 + 7 < 15U))
    {
        return to;
    }

    return to + uVar1 + (iVar2 / 8);
}

int GV_NearTimeP(int from, int to, int interp)
{
    short var_a0;
    int   var_v0;

    var_v0 = to;

    if (interp > 15)
    {
        interp = 15;
        var_v0 = to;
    }

    interp = TimeInv_8009D528[interp];
    var_a0 = FP_Subtract(from, var_v0);

    to = var_v0 + var_a0;

    if (interp == 0)
    {
        return var_v0;
    }

    var_v0 = (var_v0 - to) * interp;
    return (var_v0 / 4096) + to;
}

void GV_NearExp2V(short *from, short *to, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *from;
        cb = *to;

        diff = cb - ca;

        if ((diff > -2) && (diff < 2))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 2;
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearExp4V(short *from, short *to, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *from;
        cb = *to;

        diff = cb - ca;

        if ((diff > -4) && (diff < 4))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 4;
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearExp8V(short *from, short *to, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *from;
        cb = *to;

        diff = cb - ca;

        if ((diff > -8) && (diff < 8))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 8;
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearPhaseV(short *from, short *to, int count)
{
    int   output;
    short diff;

    while(--count >= 0)
    {
        diff = FP_Subtract(*from, *to);

        output = *to + diff;
        *from = output;

        from++;
        to++;
    }
}

void GV_NearRangeV(short *from, short *to, int range, int count)
{
    for (; --count >= 0; from++, to++)
    {
        int result = *from;

        if (*to - range > result)
        {
            result = *to - range;
        }
        else if (*to + range < result)
        {
            result = *to + range;
        }

        *from = result;
    }
}

void GV_NearSpeedV(short *from, short *to, int range, int count)
{
    int output;
    int input;
    int final_output;

    while (--count >= 0)
    {
        output = *from;
        input  = *to;

        if (output < input)
        {
            final_output = output + range;

            if (input <= output + range)
            {
                output = (short)input;
            }
            else
            {
                output = final_output;
            }
        }
        else
        {
            final_output = output - range;

            if (input < final_output)
            {
                output = final_output;
            }
            else
            {
                output = input;
            }
        }

        *from++ = output;
        to++;
    }
}

void GV_NearTimeSV(short *from, short *to, int interp, int count)
{
    short fraction;
    int   input;
    int   output;

    if (interp > 15)
    {
        interp = 15;
    }

    interp = TimeInv_8009D528[interp];
    fraction = interp;

    while (--count >= 0)
    {
        output = *from;

        do {} while (0);

        input  = *to;

        if (fraction != 0)
        {
            input = (input - output) * fraction / 4096;
            input += output;
        }

        *from++ = input;
        to++;
    }
}

void GV_NearExp2PV(short *from, short *to, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *to + FP_Subtract(*from, *to);
        diff2 = *to - diff;

        if ((diff2 > -2) && (diff2 < 2))
        {
            mid = *to;
        }
        else
        {
            mid = diff + (diff2 / 2);
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearExp4PV(short *from, short *to, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *to + FP_Subtract(*from, *to);
        diff2 = *to - diff;

        if ((diff2 > -4) && (diff2 < 4))
        {
            mid = *to;
        }
        else
        {
            mid = diff + (diff2 / 4);
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearExp8PV(short *from, short *to, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *to + FP_Subtract(*from, *to);
        diff2 = *to - diff;

        if ((diff2 > -8) && (diff2 < 8))
        {
            mid = *to;
        }
        else
        {
            mid = diff + (diff2 / 8);
        }

        *from++ = mid;
        to++;
    }
}

void GV_NearExp2SV(short *from, short *to, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = from;
    var_a1 = to;

    while (--count >= 0)
    {
        temp_t1 = *var_a0;

        do {} while (0);

        ret = *var_a1;
        var_v1 = (*var_a1 - *var_a0) / 2;

        if ((-range >= var_v1) || (var_v1 >= range))
        {
            ret = temp_t1 + var_v1;
        }

        *var_a0++ = ret;
        var_a1++;
    }
}

void GV_NearExp4SV(short *from, short *to, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = from;
    var_a1 = to;

    while (--count >= 0)
    {
        temp_t1 = *var_a0;

        do {} while (0);

        ret = *var_a1;
        var_v1 = (*var_a1 - *var_a0) / 4;

        if ((-range >= var_v1) || (var_v1 >= range))
        {
            ret = temp_t1 + var_v1;
        }

        *var_a0++ = ret;
        var_a1++;
    }
}

void GV_NearExp8SV(short *from, short *to, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = from;
    var_a1 = to;

    while (--count >= 0)
    {
        temp_t1 = *var_a0;

        do {} while (0);

        ret = *var_a1;
        var_v1 = (*var_a1 - *var_a0) / 8;

        if ((-range >= var_v1) || (var_v1 >= range))
        {
            ret = temp_t1 + var_v1;
        }

        *var_a0++ = ret;
        var_a1++;
    }
}

void GV_NearTimePV(short *from, short *to, int interp, int count)
{
    short temp_t1;
    short temp_t2;

    int var_v0;
    int temp_v1_2;
    int var_v0_2;

    if (interp > 15)
    {
        interp = 15;
    }

    interp = TimeInv_8009D528[interp];

    for (count--; count >= 0; count--)
    {
        temp_t2 = *from;
        temp_t1 = *to;

        temp_v1_2 = temp_t1 + FP_Subtract(temp_t2, temp_t1);

        if (interp == 0)
        {
            var_v0 = temp_t1;
        }
        else
        {
            var_v0_2 = (temp_t1 - temp_v1_2) * interp;
            var_v0 = ((var_v0_2) / 4096) + temp_v1_2;
        }

        *from++ = var_v0;
        to++;
    }
}
