void sub_80024194(int param_1)
{
    int *ptr = (int*)(param_1 - 4);
    int val = *ptr;

    if ((val & 0x80) != 0)
    {
        *(char*)ptr = val & ~0x80;
    }
}
