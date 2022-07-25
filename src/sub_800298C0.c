#define SCRPAD_ADDR 0x1f800000

void sub_800298C0(int* int_arr)
{
    int* scratchpad = (int*)SCRPAD_ADDR;
    int_arr[0] = scratchpad[15];
    int_arr[1] = scratchpad[16];
}
