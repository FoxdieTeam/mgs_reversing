#include "common.h"

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D3EBC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D3F24.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5090.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5114.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D518C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5270.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5354.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5428.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D567C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5910.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D59C0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5A3C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5C38.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5DC0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5EA8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5EDC.s")
typedef struct _DynStack
{
    char  pad[0x70];
    short val_70;
    short val_72;
    short val_74;
    short pad2;
    short val_78;
    short val_7A;
    short val_7C;
} DynStack;

void s15c_dyncon_800D5F68(void *work, int index, int arg2, int a3_val,
                          int sp28, int sp2c, int sp30, int sp34,
                          int sp38, int sp3c)
{
    DynStack *item;

    item = (DynStack *)((char *)work + (index * 156));

    item->val_78 += (short)a3_val;
    item->val_7A += (short)sp28;

    item->val_7C += (short)sp2c;
    item->val_70 += (short)sp30;

    item->val_72 += (short)sp34;
    item->val_74 += (short)sp38;

    s15c_dyncon_800D5EDC(work, arg2, sp3c);
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6004.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D603C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6070.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6128.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D61E0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6434.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7A84.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7D44.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7E30.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7EF4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7F88.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D82FC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8510.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D88C8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D89F8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A34.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A9C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8C9C.s")
