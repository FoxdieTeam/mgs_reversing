extern int dword_800B7800[];

static inline int DoIt(int mask)
{
    return dword_800B7800[0] & mask;
}

int camera_act_helper3_helper_8002ED3C(void)
{
    int uVar1;
    int uVar2;

    uVar2 = 0x20;
    uVar1 = DoIt(uVar2);
    while (uVar1)
    {
        uVar2 >>= 1;
        uVar1 = DoIt(uVar2);
    }
    return uVar1;
}
