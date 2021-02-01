

int sub_800263E4(int arg0, int arg1)
{
    int temp_v1;
    unsigned int temp_a2;
    int phi_v0;

    temp_v1 = arg1 - arg0;
    temp_a2 = temp_v1 + 7;
    if (temp_a2 < 0xFU)
    {
        return arg1;
    }
    phi_v0 = temp_v1;
    if (temp_v1 < 0)
    {
        phi_v0 = (int)temp_a2;
    }
    return arg0 + (phi_v0 >> 3);
}
