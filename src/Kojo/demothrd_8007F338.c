

void demothrd_8007F338(int param_1)

{
    if (param_1 != 0)
    {
        *(int *)param_1 = param_1;
        *(int *)(param_1 + 4) = param_1;
    }
    return;
}
