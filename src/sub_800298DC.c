#define SCRPAD_ADDR 0x1f800000

void sub_800298DC(int* arg0) {
    int* blah = (int*)SCRPAD_ADDR;
    arg0[0] = blah[0x11];
    arg0[1] = blah[0x12];
}
