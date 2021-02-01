

void sub_8004E330(int param_1, unsigned int param_2)

{
    *(unsigned int *)(param_1 + 0x898) = *(unsigned int *)(param_1 + 0x898) | param_2;
    return;
}
