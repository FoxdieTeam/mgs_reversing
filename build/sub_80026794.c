void sub_80026794(short *param_1, short *param_2, int param_3)
{
    int            var_a0;
    int            iVar1;
    unsigned short uVar1;
    short          iVar2;

    for (param_3--; param_3 >= 0; param_3--)
    {

        var_a0 = *param_1 - *param_2;
        uVar1 = var_a0 & 0xfff;

        if (((short)uVar1) > 0x800)
        {
            uVar1 |= 0xf000;
        }

        iVar2 = uVar1;
        iVar1 = *param_2 + iVar2;
        *param_1 = iVar1;

        param_1++;
        param_2++;
    }

    return;
}