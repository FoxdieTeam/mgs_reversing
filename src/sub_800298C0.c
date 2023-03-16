#define SCRPAD_ADDR 0x1f800000

void sub_800298C0(void *ptr)
{
    int *scratchpad = (int *)SCRPAD_ADDR;
    ((int *)ptr)[0] = scratchpad[15];
    ((int *)ptr)[1] = scratchpad[16];
}
