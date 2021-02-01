

extern void DG_WriteObjPacketRGB_8001A774(int param_1, int param_2);

void kogaku2_kill_helper_80061384(int param_1)

{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = **(int **)(param_1 + 0x20);
    iVar2 = iVar1 + 0x48;
    iVar3 = (int) *(short *)(iVar1 + 0x2e);
    *(unsigned int *)(iVar1 + 0x28) = *(unsigned int *)(iVar1 + 0x28) & 0x80 | *(unsigned int *)(param_1 + 0x28) & 0xffffff7f;
    while (0 < iVar3)
    {
        DG_WriteObjPacketRGB_8001A774(iVar2, 0);
        DG_WriteObjPacketRGB_8001A774(iVar2, 1);
        iVar3 = iVar3 + -1;
        iVar2 = iVar2 + 0x5c;
    }
    return;
}
