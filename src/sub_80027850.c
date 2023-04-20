int sub_80027850(int mult)
{
    short  x, y, z;
    short *scratch1, *scratch2, *scratch3, *scratch4;

    scratch1 = (short *)0x1F80001C;
    scratch2 = (short *)0x1F80004C;
    scratch3 = (short *)0x1F80000C;

    x = scratch2[0] = scratch3[0] + (scratch1[0] * mult) / 256;
    z = scratch2[2] = scratch3[2] + (scratch1[2] * mult) / 256;
    y = scratch2[1] = scratch3[1] + (scratch1[1] * mult) / 256;

    if (*(short *)0x1F800048 != 0)
    {
        scratch4 = (short *)0x1F800034;
        if (x < scratch4[0] - 32 || scratch4[4] + 32 < x)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        scratch4 = (short *)0x1F800034;
        if (y < scratch4[1] - 32 || scratch4[5] + 32 < y)
        {
            return 0;
        }
        else
        {
            return 2;
        }
    }
}
