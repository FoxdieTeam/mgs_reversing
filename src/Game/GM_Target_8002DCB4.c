void GM_Target_8002DCB4(char* arg0, short arg1, short arg2, int arg3, int arg4) {
    *(int*)(arg0 + 0x18) = arg3;
    *(short*)(arg0 + 0x3e) = arg1;
    *(short*)(arg0 + 0x2a) = arg2;
    *(int*)(arg0 + 0x1c) = arg4;
}
