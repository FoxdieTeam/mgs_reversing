int stgfd_io_act_helper_80074F44(char* arg0, int arg1, short arg2, short arg3, int arg4) {
    *(int*)(arg0 + 0x24) = arg1;
    *(short*)(arg0 + 0x34) = arg2;
    *(short*)(arg0 + 0x36) = arg3;
    *(short*)(arg0 + 0x38) = (short)arg4;
    return arg4;
}