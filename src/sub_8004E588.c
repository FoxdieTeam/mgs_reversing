extern int    sub_800296C4(int param_1, short *param_2, unsigned int param_3);
extern void   sub_800298DC(int *param_1);

void sub_8004E588(int param_1, short *param_2, int *param_3)
{
    unsigned int uVar1;

    uVar1 = sub_800296C4(param_1, param_2, 3);
    sub_800298DC(param_3);
    if ((uVar1 & 1) == 0)
    {
        *param_3 = 0xffff8001;
    }
    if ((uVar1 & 2) == 0)
    {
        param_3[1] = 0x7fff;
    }
    return;
}
