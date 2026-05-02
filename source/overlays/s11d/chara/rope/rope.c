#include "common.h"

typedef struct _RopeWork
{
    char  pad0[0x28];
    short field_28;
    short field_2A;
    short field_2C;
    char  pad1[0x6E - 0x2C - sizeof(short)];
    short field_6E;
    char  pad2[0xF70 - 0x6E - sizeof(short)];
    int   field_F70;
} RopeWork;

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3D50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3E50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4274.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C42F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4404.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C44A4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C44F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4574.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C45F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4648.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C481C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C486C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4898.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C48C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C48EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4B78.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4ECC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4F84.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4FC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C502C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5298.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C52F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5348.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5410.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C54CC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5538.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5584.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5B10.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5E74.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C61D8.s")
void s11d_rope_800C6240(RopeWork *work)
{
    work->field_6E = 0x800;
    work->field_2C = 0;
    work->field_28 = 0;
    work->field_F70 &= ~0x80;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6264.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C62E0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C634C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6478.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C650C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6544.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6834.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C697C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6B18.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6CD4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6F28.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7138.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7320.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7530.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C766C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7A4C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7B2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7D20.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7EC4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7F8C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8200.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8250.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8364.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C868C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C879C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C882C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C04.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C88.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8EE4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8FDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C90BC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C9134.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C91AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C9500.s")
