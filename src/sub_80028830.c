#define SCRPAD_ADDR 0x1F800000

int sub_80028830(void)
{
    short *scratchpad = (short *)SCRPAD_ADDR;
    return scratchpad[0x68 / sizeof(short)];
}
