

void anime_act_helper_8005F46C(short *param_1, int param_2)

{
    *param_1 = *param_1 + *(short *)(param_2 + 8);
    param_1[1] = param_1[1] + *(short *)(param_2 + 10);
    param_1[2] = param_1[2] + *(short *)(param_2 + 0xc);
    return;
}
