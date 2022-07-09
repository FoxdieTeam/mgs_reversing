 void sub_8004E41C(int param_1, unsigned short param_2)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x8e8);
    if (iVar1 != 0)
    {
        *(unsigned short *)(iVar1 + 6) = *(unsigned short *)(iVar1 + 6) & ~param_2;
        *(int *)(param_1 + 0x8e8) = 0;
        *(short *)(param_1 + 0xa54) = 0;
        *(short *)(*(int *)(param_1 + 0x89c) + 0x10) = 300;
    }
    return;
}
