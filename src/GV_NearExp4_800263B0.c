

int GV_NearExp4_800263B0(int arg0, int arg1)
{
    int          temp_v1;
    unsigned int temp_a2;
    int          phi_v0;

    temp_v1 = arg1 - arg0;
    temp_a2 = temp_v1 + 3;
    if (temp_a2 < 7U)
    {
        return arg1;
    }
    phi_v0 = temp_v1;
    if (temp_v1 < 0)
    {
        phi_v0 = (int)temp_a2;
    }
    return arg0 + (phi_v0 >> 2);
}
