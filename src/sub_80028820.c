#define SCRPAD_ADDR 0x1F800000

int sub_80028820(void)
{
    int *scratchpad = (int *)SCRPAD_ADDR;
    return scratchpad[0x64 / sizeof(int)];
}
