void sub_80026794(short *pOutput, short *pInput, int total)
{
    int            input_output_diff;
    int            output;
    unsigned short clamped_diff;
    short          clamped_diff_2;

    for (total--; total >= 0; total--)
    {

        input_output_diff = *pOutput - *pInput;
        clamped_diff = input_output_diff & 0xfff;

        if ((short)clamped_diff > 0x800)
        {
            clamped_diff |= 0xf000;
        }

        clamped_diff_2 = clamped_diff;
        output = *pInput + clamped_diff_2;
        *pOutput = output;

        pOutput++;
        pInput++;
    }

    return;
}