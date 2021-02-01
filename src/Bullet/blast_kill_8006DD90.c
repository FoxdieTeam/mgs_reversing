

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);
extern void sub_8007913C(void);

void blast_kill_8006DD90(int param_1)

{
    int iVar1;

    if (*(int *)(param_1 + 0x38) < 2)
    {
        sub_8007913C();
    }
    iVar1 = *(int *)(param_1 + 0x2c);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}
