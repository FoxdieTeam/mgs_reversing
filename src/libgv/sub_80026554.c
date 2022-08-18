int sub_80026554(int param_1, int param_2)
{
    short uVar1;
    int   iVar2;

    uVar1 = (param_1 - param_2) & 0xfff;

    if (uVar1 > 0x800)
    {
        uVar1 |= 0xf000;
    }

    iVar2 = param_2 - (param_2 + uVar1);

    if (iVar2 + 3 < 7U)
    {
        return param_2;
    }

    return param_2 + uVar1 + (iVar2 / 4);
}
