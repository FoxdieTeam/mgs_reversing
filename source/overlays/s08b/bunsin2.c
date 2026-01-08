int s08b_bunsin2_800CF950(void) {
    return 1;
}


int s08b_bunsin2_800D0688(void *obj) {
    int temp;
    int result;
    int *ptr;

    ptr = (int *)((char *)obj + 0x19D0);
    temp = *ptr;
    result = temp;
    temp = temp + 1;
    *ptr = temp;
    return result;
}
