

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);

void d_bloodr_kill_80072BD4(int param_1)

{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x20);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}
