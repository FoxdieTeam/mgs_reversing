int sub_80026418(int arg0, int arg1)
{
    int   temp_a0;
    short phi_v1;

    temp_a0 = (arg0 - arg1) & 0xFFF;
    phi_v1 = (short)temp_a0;
    if (temp_a0 >= 0x801)
    {
        phi_v1 = temp_a0 | 0xF000;
    }
    return arg1 + phi_v1;
}
