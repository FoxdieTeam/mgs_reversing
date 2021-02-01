

extern void sub_8004E330(int param_1, unsigned int param_2);
extern void sub_80051FD0(int param_1);

void sub_8004FA9C(int param_1)

{
    unsigned short uVar1;

    uVar1 = **(unsigned short **)(param_1 + 0x9b0);
    sub_80051FD0(param_1);
    if ((uVar1 & 0x4000) != 0)
    {
        sub_8004E330(param_1, 1);
    }
    return;
}
