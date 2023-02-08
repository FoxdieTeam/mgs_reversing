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