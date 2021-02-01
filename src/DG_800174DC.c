

void DG_800174DC(int param_1)

{
    int iVar1;

    iVar1 = *(short *)(param_1 + 6) * 0x3a;
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 0x3f;
    }
    *(short *)(param_1 + 6) = (short)(iVar1 >> 6);
    iVar1 = *(short *)(param_1 + 8) * 0x3a;
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 0x3f;
    }
    *(short *)(param_1 + 8) = (short)(iVar1 >> 6);
    iVar1 = *(short *)(param_1 + 10) * 0x3a;
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 0x3f;
    }
    *(short *)(param_1 + 10) = (short)(iVar1 >> 6);
    iVar1 = *(int *)(param_1 + 0x18) * 0x3a;
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 0x3f;
    }
    *(int *)(param_1 + 0x18) = iVar1 >> 6;
    return;
}
