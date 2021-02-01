

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);
extern void sub_80034BF8(unsigned int *param_1);

void rcm_kill_80066E68(int param_1)

{
    int iVar1;

    sub_80034BF8((unsigned int *)(param_1 + 0x20));
    iVar1 = *(int *)(param_1 + 0x5c);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}
