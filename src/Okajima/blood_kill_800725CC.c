

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);

void blood_kill_800725CC(int param_1)
{
    int prim;

    prim = *(int *)(param_1 + 0x24);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
