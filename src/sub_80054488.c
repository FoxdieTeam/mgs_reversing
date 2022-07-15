extern void GM_SetPlayerStatusFlag_8004E2B4(unsigned int param_1);
extern void sub_80050440(int param_1);
extern void sub_80056928(void);
extern void sub_80052468(void);

void sub_80054488(int param_1, int param_2)
{
    if (param_2 == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(0x10);
        *(void **)(param_1 + 0x9c8) = (void*)&sub_80056928;
        *(void **)(param_1 + 0x9cc) = (void*)&sub_80052468;
    }
    *(short *)(param_1 + 0xa62) = *(short *)(param_1 + 0x98) + 0xfa;
    sub_80050440(param_1);
    return;
}
