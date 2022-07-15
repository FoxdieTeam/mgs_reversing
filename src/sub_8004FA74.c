

extern void GM_ClearPlayerStatusFlag_8004E2D4(unsigned int param_1);
extern void sub_8004E344(int param_1, unsigned int param_2);

void sub_8004FA74(int param_1)

{
    sub_8004E344(param_1, 0x20);
    GM_ClearPlayerStatusFlag_8004E2D4(0x8408);
    return;
}
