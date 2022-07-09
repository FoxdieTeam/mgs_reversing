extern unsigned int GV_DiffDirS_8001704C(int param_1, int param_2);

void sub_8004EA50(int param_1, int param_2)
{
    unsigned int uVar1;

    uVar1 = GV_DiffDirS_8001704C(param_2, (int) *(short *)(param_1 + 0x2a));
    if ((int)uVar1 >= 0x81)
    {
        uVar1 = 0x80;
    }
    else if ((int)uVar1 < -0x80)
    {
        uVar1 = 0xffffff80;
    }
    *(short *)(param_1 + 0x70) = (short)uVar1;
    return;
}
