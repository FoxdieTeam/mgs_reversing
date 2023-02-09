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

    return;
}