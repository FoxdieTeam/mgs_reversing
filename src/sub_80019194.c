char sub_80019194(char *param_1)
{
    short new_var2;
    int   new_var;
    if ((*(param_1 + 0xb)) == 0)
    {
        return 0;
    }
    new_var2 = *(param_1 + 0x47);
    new_var = (((*(param_1 + 0xb)) & (*(param_1 + 0x1f))) & new_var2) & (*(param_1 + 0x5b));
    return new_var;
}
