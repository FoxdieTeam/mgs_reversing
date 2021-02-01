

extern void bandana_80061D14(int *param_1);

void bandana_kill_80061E1C(int param_1)

{
    bandana_80061D14(*(int **)(param_1 + 0x20));
    return;
}
