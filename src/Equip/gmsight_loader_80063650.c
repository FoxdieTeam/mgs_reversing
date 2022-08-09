extern short word_800BDCC0;

int gmsight_loader_80063650(int param_1)
{
    word_800BDCC0 = 1;
    *(int *)(param_1 + 0x20) = 0;
    return 0;
}
