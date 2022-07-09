 extern int  sub_8004EFE4(int param_1, int param_2);

void sub_8004F034(int param_1, unsigned int param_2)
{
    int iVar1;

    if (param_2 != *(unsigned int *)(param_1 + 0x18c))
    {
        *(unsigned int *)(param_1 + 0x1a4) = ~param_2;
        *(unsigned int *)(param_1 + 0x18c) = param_2;
        if ((param_2 == 0xffff) && (iVar1 = sub_8004EFE4(param_1, 2),  -1 < iVar1))
        {
            *(int *)(param_1 + 0x1c0) = 4;
            *(short *)(param_1 + 0x1b0) = 2;
        }
    }
    return;
}
