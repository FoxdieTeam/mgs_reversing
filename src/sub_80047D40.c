extern void         GV_FreeMemory_80015FD0(int, void*);

void sub_80047D40(int param_1)
{
    GV_FreeMemory_80015FD0(0, *(void **)(param_1 + 0x218));
    *(int *)(param_1 + 0x218) = 0;
    return;
}
 
 
