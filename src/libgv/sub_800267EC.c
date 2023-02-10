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
