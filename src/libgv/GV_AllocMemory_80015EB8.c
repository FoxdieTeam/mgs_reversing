
extern unsigned int GV_AllocMemory2_80015ED8(unsigned int, int, int*);

void GV_AllocMemory_80015EB8(int param_1, int param_2)
{
    GV_AllocMemory2_80015ED8(param_1, param_2, (int *)0x2);
    return;
}
