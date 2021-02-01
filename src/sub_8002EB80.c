

extern int  sub_80026440(int param_1, int param_2, int param_3);

void sub_8002EB80(short *param_1, short *param_2)

{
    int iVar1;

    iVar1 = sub_80026440((int) *param_1, (int) *param_2, 500);
    *param_1 = (short)iVar1;
    iVar1 = sub_80026440((int)param_1[2], (int)param_2[2], 500);
    param_1[2] = (short)iVar1;
    iVar1 = sub_80026440((int)param_1[1], (int)param_2[1], 0x96);
    param_1[1] = (short)iVar1;
    return;
}
