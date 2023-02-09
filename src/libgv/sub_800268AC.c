extern short word_8009D528[];

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
    
    return;
}