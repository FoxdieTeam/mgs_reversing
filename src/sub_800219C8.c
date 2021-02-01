

void sub_800219C8(int param_1, int param_2, int param_3)

{
    int *piVar1;
    int iVar2;

    iVar2 = param_2 + -1;
    piVar1 = (int *)(param_1 + 4);
    while (-1 < iVar2)
    {
        iVar2 = iVar2 + -1;
        *piVar1 = param_3 + *piVar1;
        piVar1 = piVar1 + 2;
    }
    return;
}
