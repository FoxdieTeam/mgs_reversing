void move_coord_8004A494(int *param_1, int param_2)
{
    int iVar1;

    iVar1 = 0;
    if (0 < param_2)
    {
        do
        {
            iVar1 = iVar1 + 1;
            *param_1 = *param_1 + param_1[1];
            param_1 = param_1 + 2;
        } while (iVar1 < param_2);
        while (iVar1 < param_2)
            ;
    }
    return;
}
