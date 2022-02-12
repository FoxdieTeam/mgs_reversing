

extern void DG_8001F1DC(void);
extern void GCL_ResetSystem_8001FD24(void);
extern void GV_ResetSystem_80014CC8(void);
extern void sub_800389A8(void);

void sub_8002AA48(void)

{
    sub_800389A8();
    GV_ResetSystem_80014CC8();
    DG_8001F1DC();
    GCL_ResetSystem_8001FD24();
    return;
}
