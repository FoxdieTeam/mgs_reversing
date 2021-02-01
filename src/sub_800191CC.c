

void sub_800191CC(int param_1)

{
    char bVar1;

    bVar1 = 0;
    if (*(short *)(param_1 + 0xc) < -0xa0)
    {
        bVar1 = 1;
    }
    else 
    {
        if (0xa0 < *(short *)(param_1 + 0xc))
        {
            bVar1 = 2;
        }
    }
    if (*(short *)(param_1 + 0xe) < -0x70)
    {
        bVar1 = bVar1 | 4;
    }
    else 
    {
        if (0x70 < *(short *)(param_1 + 0xe))
        {
            bVar1 = bVar1 | 8;
        }
    }
    if (*(int *)(param_1 + 0x10) == 0)
    {
        bVar1 = bVar1 | 0x10;
    }
    *(char *)(param_1 + 0xb) = bVar1;
    return;
}
