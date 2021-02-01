

extern void sub_8004E2D4(unsigned int param_1);
extern void sub_8004E308(int param_1, unsigned int param_2);

void sub_8004F2EC(int param_1)

{
    sub_8004E2D4(0x800000);
    sub_8004E308(param_1, 1);
    **(unsigned short **)(param_1 + 0x89c) = **(unsigned short **)(param_1 + 0x89c) | 0x9e;
    return;
}
