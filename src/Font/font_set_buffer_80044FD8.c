

void font_set_buffer_80044FD8(int param_1, int param_2)

{
    *(int *)(param_1 + 0x28) = param_2;
    *(int *)(param_1 + 0x14) = param_2 + 0x20;
    return;
}
