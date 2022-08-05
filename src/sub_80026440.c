

int sub_80026440(int param_1, int param_2, int param_3)

{
    int iVar1;

    iVar1 = param_2 - param_3;
    if ((param_1 < iVar1) || (iVar1 = param_2 + param_3, iVar1 < param_1))
    {
        param_1 = iVar1;
    }
    return param_1;
}
