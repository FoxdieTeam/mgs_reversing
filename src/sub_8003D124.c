

extern void*    GV_Malloc_8001620C(int size);
extern void     GV_ZeroMemory_8001619C(void *, int);

int * sub_8003D124(int param_1)

{
    int *piVar1;
    int iVar2;

    iVar2 = param_1 * 8 + 0x20;
    piVar1 = (int *)GV_Malloc_8001620C(iVar2);
    if (piVar1 != (int *)0x0)
    {
        GV_ZeroMemory_8001619C(piVar1, iVar2);
        *piVar1 = param_1;
        piVar1[4] = 0;
    }
    return piVar1;
}
