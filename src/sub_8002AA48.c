

extern void DG_8001F1DC(void);
extern void GCL_Null_8001FD24(void);
extern void GV_Messge_And_Pad_Init_80014CC8(void);
extern void sub_800389A8(void);

void sub_8002AA48(void)

{
    sub_800389A8();
    GV_Messge_And_Pad_Init_80014CC8();
    DG_8001F1DC();
    GCL_Null_8001FD24();
    return;
}
