#include "libgv\libgv.h"

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