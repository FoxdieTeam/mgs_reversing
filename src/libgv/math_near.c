#include "libgv.h"
#include "linker.h"

extern short word_8009D528[];

int GV_NearExp2_80026384(int a, int b)
{
    int diff = b - a;
    
    if ((diff <= -2) || (diff >= 2))
    {
        return a + diff / 2;
    }
  
    return b;
}

int GV_NearExp4_800263B0(int a, int b)
{
    int diff = b - a;
    
    if ((diff > -4) && (diff < 4))
    {
        return b;
    }

    return a + diff / 4;
}

int GV_NearExp8_800263E4(int a, int b)
{
    int diff = b - a;
    
    if ((diff > -8) && (diff < 8))
    {
        return b;
    }

    return a + diff / 8;
}

int sub_80026418(int arg0, int arg1)
{
    short phi_v1;

    phi_v1 = FP_Subtract(arg0, arg1);

    return arg1 + phi_v1;
}

int sub_80026440(int param_1, int param_2, int param_3)
{
    int iVar1;

    iVar1 = param_2 - param_3;
    if ((param_1 < iVar1) || (iVar1 = param_2 + param_3, iVar1 < param_1))
    {
        param_1 = iVar1;
    }
    return param_1;
}

#pragma INCLUDE_ASM("asm/libgv/sub_8002646C.s") // 68 bytes

int sub_800264B0(int param_1, int param_2, int param_3)
{
    int var_a2;
    int var_v0;


    var_a2 = param_3;
    if (var_a2 > 15)
    { 
        var_a2 = 15;
    }

    var_a2 = word_8009D528[var_a2];  
    if (var_a2 == 0)
    {
        return param_2;
    }
    
    var_v0 = (param_2 - param_1) * var_a2;
    
    return (var_v0 / 4096) + param_1;
}

int GV_NearExp2P_80026504(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);
    
    iVar2 = b - (b + uVar1);

    if (iVar2 + 1 >= 3U)
    {
        return b + uVar1 + (iVar2 / 2);
    }

    return b;
}

int GV_NearExp4P_80026554(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);

    iVar2 = b - (b + uVar1);

    if ((iVar2 + 3 < 7U))
    {
        return b;
    }

    return b + uVar1 + (iVar2 / 4);
}

int GV_NearExp8P_800265AC(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);

    iVar2 = b - (b + uVar1);

    if ((iVar2 + 7 < 15U))
    {
        return b;
    }

    return b + uVar1 + (iVar2 / 8);
}

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

void GV_NearExp2V_8002667C(short *a, short *b, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *a;
        cb = *b;
        
        diff = cb - ca;
        
        if ((diff > -2) && (diff < 2))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 2;
        }

        *a++ = mid;
        b++;
    } 
}

void GV_NearExp4V_800266D4(short *a, short *b, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *a;
        cb = *b;
        
        diff = cb - ca;
        
        if ((diff > -4) && (diff < 4))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 4;
        }

        *a++ = mid;
        b++;
    } 
}

void GV_NearExp8V_80026734(short *a, short *b, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *a;
        cb = *b;
        
        diff = cb - ca;
        
        if ((diff > -8) && (diff < 8))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 8;
        }

        *a++ = mid;
        b++;
    } 
}

void sub_80026794(short *pOutput, short *pInput, int total)
{
    int   output;
    short diff;

    while(--total >= 0)
    {
        diff = FP_Subtract(*pOutput, *pInput);
        
        output = *pInput + diff;
        *pOutput = output;

        pOutput++;
        pInput++;
    }
}

void sub_800267EC(short *arr_a, short *arr_b, int val, int len)
{
    for (; --len >= 0; arr_a++, arr_b++)
    {
        int result = *arr_a;

        if (*arr_b - val > result)
        {
            result = *arr_b - val;
        }
        else if (*arr_b + val < result)
        {
            result = *arr_b + val;
        }

        *arr_a = result;
    }
}

void sub_80026840(short *pOutput, short *pInput, int range, int count)
{
    int output;
    int input;
    int final_output;

    while (--count >= 0)
    {
        output = *pOutput;
        input  = *pInput;

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

        *pOutput++ = output;
        pInput++;
    }
}

void sub_800268AC(short *pOutput, short *pInput, int index, int count)
{
    short fraction;
    int   input;
    int   output;

    if (index > 15)
    {
        index = 15;
    }

    index = word_8009D528[index];
    fraction = index;

    while (--count >= 0)
    {
        output = *pOutput;

        do {} while (0);

        input  = *pInput;
        
        if (fraction != 0)
        {
            input = (input - output) * fraction / 4096;
            input += output;
        }

        *pOutput++ = input;
        pInput++;
    }
}

void GV_NearExp2PV_80026924(short *a, short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -2) && (diff2 < 2))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 2);
        }
        
        *a++ = mid;
        b++;
    }
}

void GV_NearExp4PV_800269A0(short *a, short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -4) && (diff2 < 4))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 4);
        }
        
        *a++ = mid;
        b++;
    }
}

void GV_NearExp8PV_80026A24(short *a, short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -8) && (diff2 < 8))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 8);
        }
        
        *a++ = mid;
        b++;
    }
}

void GV_NearExp2SV_80026AA8(short *arg0, short *arg1, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = arg0;
    var_a1 = arg1;

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

void GV_NearExp4SV_80026B04(short *arg0, short *arg1, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = arg0;
    var_a1 = arg1;

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

void GV_NearExp8SV_80026B64(short *arg0, short *arg1, int range, int count)
{
    int    temp_t1;
    short *var_a0;
    short *var_a1;
    int    var_v1;
    int    ret;

    var_a0 = arg0;
    var_a1 = arg1;

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
