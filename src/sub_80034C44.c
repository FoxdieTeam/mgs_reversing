

void sub_80034C44(int *param_1, int param_2)

{
    param_1[2] = param_2;
    *(int *)(*param_1 + 0x34) = param_2;
    return;
}
