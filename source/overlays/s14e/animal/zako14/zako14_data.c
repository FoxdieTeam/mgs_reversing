#include "game/game.h"

int s14e_dword_800C3350 = 0x00140013;
int s14e_dword_800C3354 = 0x0016000A;
int s14e_dword_800C3358 = 0x00220009;
int s14e_dword_800C335C = 0x00240023;
int s14e_dword_800C3360 = 0x000D002D;
int s14e_dword_800C3364 = 0x001A000C;
int s14e_dword_800C3368 = 0x000E000F;
int s14e_dword_800C336C = 0x001B0010;
int s14e_dword_800C3370 = 0x002E0008;
int s14e_dword_800C3374 = 0x00150013;
int s14e_dword_800C3378 = 0x001F001E;
int s14e_dword_800C337C = 0x00210020;
int s14e_dword_800C3380 = 0x00130025;
int s14e_dword_800C3384 = 0x00190013;
int s14e_dword_800C3388 = 0x00020005;
int s14e_dword_800C338C = 0x0004002A;
int s14e_dword_800C3390 = 0x00280027;
int s14e_dword_800C3394 = 0x00070006;
int s14e_dword_800C3398 = 0x00030026;
int s14e_dword_800C339C = 0x00110029;
int s14e_dword_800C33A0 = 0x002B0012;
int s14e_dword_800C33A4 = 0x00180017;
int s14e_dword_800C33A8 = 0x001D001C;
int s14e_dword_800C33AC = 0x00010000;
int s14e_dword_800C33B0 = 0x00110033;
int s14e_dword_800C33B4 = 0x002B0012;
int s14e_dword_800C33B8 = 0x00000016;
int s14e_dword_800C33BC = 0x00000401;
int s14e_dword_800C33C0 = 0x000004FF;
int s14e_dword_800C33C4 = 0x0000FF6A;
int s14e_dword_800C33C8 = 0x0000012C;
int s14e_dword_800C33CC = 0xFD440000;
int s14e_dword_800C33D0 = 0x00000384;
int s14e_dword_800C33D4 = 0x00000000;
int s14e_dword_800C33D8 = 0x00000064;
int s14e_dword_800C33DC = 0x0000FC00;
int s14e_dword_800C33E0 = 0x00000000;
int s14e_dword_800C33E4 = 0x00000000;
int s14e_dword_800C33E8 = 0x00000064;
int s14e_dword_800C33EC = 0x0000FC00;
int s14e_dword_800C33F0 = 0x00000000;
int s14e_dword_800C33F4 = 0x800DCA58;
int s14e_dword_800C33F8 = 0x800DCA44;
int s14e_dword_800C33FC = 0x800DCA30;
int s14e_dword_800C3400 = 0x800CA538;
int s14e_dword_800C3404 = 0x800CA5D0;
int s14e_dword_800C3408 = 0x800CA718;
int s14e_dword_800C340C = 0x800CA754;
int s14e_dword_800C3410 = 0xFE0C0005;
int s14e_dword_800C3414 = 0x00000050;

const int s14e_dword_800DC9A8 = 0x800C6BFC;
const int s14e_dword_800DC9AC = 0x800C6C74;
const int s14e_dword_800DC9B0 = 0x800C6B84;
const int s14e_dword_800DC9B4 = 0x800C6BE4;
const int s14e_dword_800DC9B8 = 0x800C6CAC;
const int s14e_dword_800DC9BC = 0x800C6D00;
const int s14e_dword_800DC9C0 = 0x800C6D00;
const int s14e_dword_800DC9C4 = 0x800C6CC8;
const int s14e_dword_800DC9C8 = 0x800C6CDC;
const char s14e_dword_800DC9CC[] = {'8', 0xff, 0xe8, 0x3};
const char s14e_dword_800DC9D0[] = {'X', 0x2, 0x0, 0x0};
const char s14e_dword_800DC9D4[] = {0x5, 0x0, 0x0, 0x0};
const char s14e_dword_800DC9D8[] = "d";
const char s14e_dword_800DC9DC[] = {0x90, 0x1, 0xe8, 0x3};
const char s14e_dword_800DC9E0[] = {0x90, 0x1, 0x0, 0x0};
const char s14e_dword_800DC9E4[] = " vx=%d vy=%d vz=%d \n";
const char s14e_dword_800DC9FC[] = {0x0, 0x0, 0x0, 0x0};
const int s14e_dword_800DCA00 = 0x800C8DA4;
const int s14e_dword_800DCA04 = 0x800C8DF4;
const int s14e_dword_800DCA08 = 0x800C8EBC;
const int s14e_dword_800DCA0C = 0x800C8E78;
const int s14e_dword_800DCA10 = 0x800C8F00;
const int s14e_dword_800DCA14 = 0x800C8F34;
const int s14e_dword_800DCA18 = 0x800C8F8C;
const int s14e_dword_800DCA1C = 0x800C8FD4;
const int s14e_dword_800DCA20 = 0x800C9014;
const int s14e_dword_800DCA24 = 0x800C8FF4;
const int s14e_dword_800DCA28 = 0x800C9040;
const int s14e_dword_800DCA2C = 0x800C9040;
const char s14e_dword_800DCA30[] = "FA-MAS/BULLET * 25";
const char s14e_dword_800DCA44[] = "SOCOM/BULLET * 12";
const char s14e_dword_800DCA58[] = "RATION";

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6A34.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6AC0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6ADC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6B18.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6D20.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6DB0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6E08.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6E6C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6F40.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6F94.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C701C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C712C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7194.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7398.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7550.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C77F8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7888.s")

void s14e_800C7970( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7978.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7AEC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7B9C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7CD0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7E28.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7F00.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C7FA8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C82D0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8350.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C86D4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8748.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8898.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8A10.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8AD8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8BE8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C8CF8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C924C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C94A8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C95B8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C96AC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9838.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9904.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C99D0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9A68.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9B00.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9BB4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9D20.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9DE8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C9FC0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA000.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA148.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA2E4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA354.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA3B8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA49C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA538.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA718.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA754.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA890.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA8D8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA90C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA96C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CA998.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CAA1C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CAA7C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CABFC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CAD24.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CADD0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CAE24.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CAEF4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CB0BC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CB128.s")
