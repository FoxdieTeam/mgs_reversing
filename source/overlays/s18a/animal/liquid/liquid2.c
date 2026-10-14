#include "liquid.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "linkvar.h"

/* Liquid's brain and moves (a cut-down copy of the snake code), original file name unknown */

extern void s18a_800CC4F0(void);
extern void s18a_800CC56C(void);
extern void s18a_800CC574(void);

int s18a_dword_800C3318 = 0x00000000;
int s18a_dword_800C331C = 0x00020001;
int s18a_dword_800C3320 = 0x00020025;
int s18a_dword_800C3324 = 0x00260024;
int s18a_dword_800C3328 = 0x00040003;
int s18a_dword_800C332C = 0x00070017;
int s18a_dword_800C3330 = 0x00060005;
int s18a_dword_800C3334 = 0x00080009;
int s18a_dword_800C3338 = 0x000A000B;
int s18a_dword_800C333C = 0x000C001D;
int s18a_dword_800C3340 = 0x0011000D;
int s18a_dword_800C3344 = 0x00130012;
int s18a_dword_800C3348 = 0x0010000F;
int s18a_dword_800C334C = 0x00150014;
int s18a_dword_800C3350 = 0x001B0016;
int s18a_dword_800C3354 = 0x00190018;
int s18a_dword_800C3358 = 0x001E001A;
int s18a_dword_800C335C = 0x0020001F;
int s18a_dword_800C3360 = 0x00220021;
int s18a_dword_800C3364 = 0x001C0023;
int s18a_dword_800C3368 = 0x271009C4;
int s18a_dword_800C336C = 0x000001F4;
int s18a_dword_800C3370 = 0x00000000;
int s18a_dword_800C3374 = 0x0000FC18;
int s18a_dword_800C3378 = 0x00000000;
int s18a_dword_800C337C = 0x00000064;
int s18a_dword_800C3380 = 0x0000FC00;
int s18a_dword_800C3384 = 0x00000000;
void *s18a_dword_800C3388 = (void *)s18a_800CC4F0;
void *s18a_dword_800C338C = (void *)s18a_800CC56C;
void *s18a_dword_800C3390 = (void *)s18a_800CC574;
int s18a_dword_800C3394 = 0xFE0C0005;
int s18a_dword_800C3398 = 0x00000050;
int s18a_dword_800C339C = 0x2EE00C35;
int s18a_dword_800C33A0 = 0x000002EE;
int s18a_dword_800C33A4 = 0x2EE0FF83;
int s18a_dword_800C33A8 = 0x000001F4;
int s18a_dword_800C33AC = 0x2EE00C35;
int s18a_dword_800C33B0 = 0x0000FD12;
int s18a_dword_800C33B4 = 0x2EE0FF83;
int s18a_dword_800C33B8 = 0x0000FE0C;
int s18a_dword_800C33BC = 0x2EE00753;
int s18a_dword_800C33C0 = 0x000002EE;
int s18a_dword_800C33C4 = 0x2EE01405;
int s18a_dword_800C33C8 = 0x000001F4;
int s18a_dword_800C33CC = 0x2EE00753;
int s18a_dword_800C33D0 = 0x0000FD12;
int s18a_dword_800C33D4 = 0x2EE01405;
int s18a_dword_800C33D8 = 0x0000FE0C;
int s18a_dword_800C33DC = 0x2EE01405;
int s18a_dword_800C33E0 = 0x000000FA;
int s18a_dword_800C33E4 = 0x2EE00C35;
int s18a_dword_800C33E8 = 0x0000FC18;
int s18a_dword_800C33EC = 0x2EE01405;
int s18a_dword_800C33F0 = 0x0000FF06;
int s18a_dword_800C33F4 = 0x2EE00C35;
int s18a_dword_800C33F8 = 0x000003E8;
int s18a_dword_800C33FC = 0x2EE0FF83;
int s18a_dword_800C3400 = 0x000000FA;
int s18a_dword_800C3404 = 0x2EE00753;
int s18a_dword_800C3408 = 0x0000FC18;
int s18a_dword_800C340C = 0x2EE0FF83;
int s18a_dword_800C3410 = 0x0000FF06;
int s18a_dword_800C3414 = 0x2EE00753;
int s18a_dword_800C3418 = 0x000003E8;
int s18a_dword_800C341C = 0x2EE00EA6;
int s18a_dword_800C3420 = 0x000004E2;
int s18a_dword_800C3424 = 0x2EE01482;
int s18a_dword_800C3428 = 0x000003E8;
int s18a_dword_800C342C = 0x2EE00EA6;
int s18a_dword_800C3430 = 0x0000FD12;
int s18a_dword_800C3434 = 0x2EE01482;
int s18a_dword_800C3438 = 0x0000FC18;
int s18a_dword_800C343C = 0x2EE003E8;
int s18a_dword_800C3440 = 0x000004E2;
int s18a_dword_800C3444 = 0x2EE0FE0C;
int s18a_dword_800C3448 = 0x000003E8;
int s18a_dword_800C344C = 0x2EE003E8;
int s18a_dword_800C3450 = 0x0000FD12;
int s18a_dword_800C3454 = 0x2EE0FE0C;
int s18a_dword_800C3458 = 0x0000FC18;
int s18a_dword_800C345C = 0x00000000;
int s18a_dword_800C3460 = 0x00000000;
int s18a_dword_800C3464 = 0x00000000;
int s18a_dword_800C3468 = 0x0000000E;
int s18a_dword_800C346C = 0x0000000F;
int s18a_dword_800C3470 = 0x00000006;
int s18a_dword_800C3474 = 0x00000005;
int s18a_dword_800C3478 = 0x00000006;
int s18a_dword_800C347C = 0x00000002;
int s18a_dword_800C3480 = 0x00000000;
int s18a_dword_800C3484 = 0x00000000;
int s18a_dword_800C3488 = 0x00000000;
int s18a_dword_800C348C = 0x00000000;
int s18a_dword_800C3490 = 0x00000000;
int s18a_dword_800C3494 = 0x00000000;
int s18a_dword_800C3498 = 0x00000000;
int s18a_dword_800C349C = 0x00000000;

/*--FUNCS--*/

const int s18a_dword_800E2D84 = 0x6D696C63;
const int s18a_dword_800E2D88 = 0x72612062;
const int s18a_dword_800E2D8C = 0x20206165;
const int s18a_dword_800E2D90 = 0x000A2030;
const int s18a_dword_800E2D94 = 0x6D696C63;
const int s18a_dword_800E2D98 = 0x72612062;
const int s18a_dword_800E2D9C = 0x20206165;
const int s18a_dword_800E2DA0 = 0x000A2034;
const int s18a_dword_800E2DA4 = 0x6D696C63;
const int s18a_dword_800E2DA8 = 0x72612062;
const int s18a_dword_800E2DAC = 0x20206165;
const int s18a_dword_800E2DB0 = 0x000A2033;
const int s18a_dword_800E2DB4 = 0x6D696C63;
const int s18a_dword_800E2DB8 = 0x72612062;
const int s18a_dword_800E2DBC = 0x20206165;
const int s18a_dword_800E2DC0 = 0x000A2032;
const int s18a_dword_800E2DC4 = 0x6D696C63;
const int s18a_dword_800E2DC8 = 0x72612062;
const int s18a_dword_800E2DCC = 0x20206165;
const int s18a_dword_800E2DD0 = 0x000A2031;
const int s18a_dword_800E2DD4 = 0x6D696C63;
const int s18a_dword_800E2DD8 = 0x72612062;
const int s18a_dword_800E2DDC = 0x20206165;
const int s18a_dword_800E2DE0 = 0x000A2037;
const int s18a_dword_800E2DE4 = 0x6D696C63;
const int s18a_dword_800E2DE8 = 0x72612062;
const int s18a_dword_800E2DEC = 0x20206165;
const int s18a_dword_800E2DF0 = 0x000A2036;
const int s18a_dword_800E2DF4 = 0x6D696C63;
const int s18a_dword_800E2DF8 = 0x72612062;
const int s18a_dword_800E2DFC = 0x20206165;
const int s18a_dword_800E2E00 = 0x000A2035;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C722C.s")
const int s18a_dword_800E2E04 = 0x800C73AC;
const int s18a_dword_800E2E08 = 0x800C73CC;
const int s18a_dword_800E2E0C = 0x800C73DC;
const int s18a_dword_800E2E10 = 0x800C73EC;
const int s18a_dword_800E2E14 = 0x800C73FC;
const int s18a_dword_800E2E18 = 0x800C740C;
const int s18a_dword_800E2E1C = 0x800C741C;
const int s18a_dword_800E2E20 = 0x800C742C;
const int s18a_dword_800E2E24 = 0x800C743C;
const int s18a_dword_800E2E28 = 0x800C744C;
const int s18a_dword_800E2E2C = 0x800C745C;
const int s18a_dword_800E2E30 = 0x800C746C;
const int s18a_dword_800E2E34 = 0x800C747C;
const int s18a_dword_800E2E38 = 0x800C748C;
const int s18a_dword_800E2E3C = 0x800C749C;
const int s18a_dword_800E2E40 = 0x800C74AC;
const int s18a_dword_800E2E44 = 0x800C74BC;
const int s18a_dword_800E2E48 = 0x800C74CC;
const int s18a_dword_800E2E4C = 0x800C74DC;
const int s18a_dword_800E2E50 = 0x800C74EC;
const int s18a_dword_800E2E54 = 0x800C74FC;
const int s18a_dword_800E2E58 = 0x800C750C;
const int s18a_dword_800E2E5C = 0x800C751C;
const int s18a_dword_800E2E60 = 0x800C753C;
const int s18a_dword_800E2E64 = 0x800C754C;
const int s18a_dword_800E2E68 = 0x800C755C;
const int s18a_dword_800E2E6C = 0x800C756C;
const int s18a_dword_800E2E70 = 0x800C757C;
const int s18a_dword_800E2E74 = 0x800C757C;
const int s18a_dword_800E2E78 = 0x800C752C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C736C.s")
const int s18a_dword_800E2E7C = 0x50414557;
const int s18a_dword_800E2E80 = 0x303D4E4F;
const int s18a_dword_800E2E84 = 0x20782578;
const int s18a_dword_800E2E88 = 0x6F6D5F61;
const int s18a_dword_800E2E8C = 0x303D6564;
const int s18a_dword_800E2E90 = 0x20782578;
const int s18a_dword_800E2E94 = 0x61665F70;
const int s18a_dword_800E2E98 = 0x3D746E69;
const int s18a_dword_800E2E9C = 0x000A6425;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7584.s")
const int s18a_dword_800E2EA0 = 0x25736F70;
const int s18a_dword_800E2EA4 = 0x64252064;
const int s18a_dword_800E2EA8 = 0x20642520;
const int s18a_dword_800E2EAC = 0x0000000A;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7684.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7878.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7904.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7A18.s")
const int s18a_dword_800E2EB0 = 0x03E8FF38;
const int s18a_dword_800E2EB4 = 0x00000258;
const int s18a_dword_800E2EB8 = 0x03E800C8;
const int s18a_dword_800E2EBC = 0x00000258;
const int s18a_dword_800E2EC0 = 0x03E80000;
const int s18a_dword_800E2EC4 = 0x00000384;
const int s18a_dword_800E2EC8 = 0x00000000;
const int s18a_dword_800E2ECC = 0x00000384;
const int s18a_dword_800E2ED0 = 0xFC180000;
const int s18a_dword_800E2ED4 = 0x000001F4;
const int s18a_dword_800E2ED8 = 0xF4480000;
const int s18a_dword_800E2EDC = 0x000003E8;
const int s18a_dword_800E2EE0 = 0x03E80000;
const int s18a_dword_800E2EE4 = 0x000001F4;
const int s18a_dword_800E2EE8 = 0x03E80000;
const int s18a_dword_800E2EEC = 0x00000000;
const int s18a_dword_800E2EF0 = 0x019000C8;
const int s18a_dword_800E2EF4 = 0x000001F4;
const int s18a_dword_800E2EF8 = 0x019000C8;
const int s18a_dword_800E2EFC = 0x0000012C;
const int s18a_dword_800E2F00 = 0x01F400C8;
const int s18a_dword_800E2F04 = 0x000002BC;
const int s18a_dword_800E2F08 = 0x01F40190;
const int s18a_dword_800E2F0C = 0x000002BC;
const int s18a_dword_800E2F10 = 0x00000000;
const int s18a_dword_800E2F14 = 0x00000032;
const int s18a_dword_800E2F18 = 0x00C80005;
const int s18a_dword_800E2F1C = 0x00000064;
const int s18a_dword_800E2F20 = 0x00000000;
const int s18a_dword_800E2F24 = 0x800C7D44;
const int s18a_dword_800E2F28 = 0x800C7D94;
const int s18a_dword_800E2F2C = 0x800C7DE4;
const int s18a_dword_800E2F30 = 0x800C7E34;
const int s18a_dword_800E2F34 = 0x800C7E84;
const int s18a_dword_800E2F38 = 0x800C7ED4;
const int s18a_dword_800E2F3C = 0x800C7F24;
const int s18a_dword_800E2F40 = 0x800C7FA0;
const int s18a_dword_800E2F44 = 0x800C7FF0;
const int s18a_dword_800E2F48 = 0x800C8040;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7A68.s")
const int s18a_dword_800E2F4C = 0x00C80190;
const int s18a_dword_800E2F50 = 0x00000190;
const int s18a_dword_800E2F54 = 0x00C803E8;
const int s18a_dword_800E2F58 = 0x000003E8;
const int s18a_dword_800E2F5C = 0x03E80000;
const int s18a_dword_800E2F60 = 0x0000FE0C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C80B8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8210.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C82A4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C839C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C84B8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8558.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C863C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8754.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C886C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8990.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8A8C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8BB0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8CD4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8DC4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C8EBC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9044.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C91D4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9384.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9534.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C966C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C97AC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C990C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9A0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9B20.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C9C2C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CA1A4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CA3B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CA440.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CA6E0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CA9FC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CAD88.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB114.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB310.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB418.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB56C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB640.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB780.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB8AC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CB9D0.s")
const int s18a_dword_800E2F64 = 0x30736F70;
const int s18a_dword_800E2F68 = 0x20642520;
const int s18a_dword_800E2F6C = 0x25206425;
const int s18a_dword_800E2F70 = 0x000A2064;
const int s18a_dword_800E2F74 = 0x696C6320;
const int s18a_dword_800E2F78 = 0x7420626D;
const int s18a_dword_800E2F7C = 0x20657079;
const int s18a_dword_800E2F80 = 0x6425203D;
const int s18a_dword_800E2F84 = 0x00000A20;
const int s18a_dword_800E2F88 = 0x72724520;
const int s18a_dword_800E2F8C = 0x72724520;
const int s18a_dword_800E2F90 = 0x72724520;
const int s18a_dword_800E2F94 = 0x71694C20;
const int s18a_dword_800E2F98 = 0x20646975;
const int s18a_dword_800E2F9C = 0x7261654E;
const int s18a_dword_800E2FA0 = 0x72724520;
const int s18a_dword_800E2FA4 = 0x20212120;
const int s18a_dword_800E2FA8 = 0x0000000A;
const int s18a_dword_800E2FAC = 0x800CBC1C;
const int s18a_dword_800E2FB0 = 0x800CBC1C;
const int s18a_dword_800E2FB4 = 0x800CBC00;
const int s18a_dword_800E2FB8 = 0x800CBC1C;
const int s18a_dword_800E2FBC = 0x800CBC38;
const int s18a_dword_800E2FC0 = 0x800CBC00;
const int s18a_dword_800E2FC4 = 0x800CBC00;
const int s18a_dword_800E2FC8 = 0x800CBC00;
const int s18a_dword_800E2FCC = 0x800CBD60;
const int s18a_dword_800E2FD0 = 0x800CBD60;
const int s18a_dword_800E2FD4 = 0x800CBD44;
const int s18a_dword_800E2FD8 = 0x800CBD60;
const int s18a_dword_800E2FDC = 0x800CBD7C;
const int s18a_dword_800E2FE0 = 0x800CBD44;
const int s18a_dword_800E2FE4 = 0x800CBD44;
const int s18a_dword_800E2FE8 = 0x800CBD44;
const int s18a_dword_800E2FEC = 0x800CBDFC;
const int s18a_dword_800E2FF0 = 0x800CBDFC;
const int s18a_dword_800E2FF4 = 0x800CBDE0;
const int s18a_dword_800E2FF8 = 0x800CBDFC;
const int s18a_dword_800E2FFC = 0x800CBE18;
const int s18a_dword_800E3000 = 0x800CBDE0;
const int s18a_dword_800E3004 = 0x800CBDE0;
const int s18a_dword_800E3008 = 0x800CBDE0;
const int s18a_dword_800E300C = 0x72724520;
const int s18a_dword_800E3010 = 0x72724520;
const int s18a_dword_800E3014 = 0x72724520;
const int s18a_dword_800E3018 = 0x71694C20;
const int s18a_dword_800E301C = 0x20646975;
const int s18a_dword_800E3020 = 0x20727245;
const int s18a_dword_800E3024 = 0x0A202121;
const int s18a_dword_800E3028 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CBB50.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CBF38.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC0F0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC1F0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC278.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC2A0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC488.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC4F0.s")
void s18a_800CC56C(void)
{
}

const int s18a_dword_800E302C = 0x800CC5B0;
const int s18a_dword_800E3030 = 0x800CC650;
const int s18a_dword_800E3034 = 0x800CC5C8;
const int s18a_dword_800E3038 = 0x800CC5DC;
const int s18a_dword_800E303C = 0x800CC61C;
const int s18a_dword_800E3040 = 0x800CC5FC;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC574.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC660.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC6A8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC6DC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC73C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC76C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC7BC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC800.s")
const int s18a_dword_800E3044 = 0x253A782C;
const int s18a_dword_800E3048 = 0x3A792064;
const int s18a_dword_800E304C = 0x7A206425;
const int s18a_dword_800E3050 = 0x2064253A;
const int s18a_dword_800E3054 = 0x0000000A;
const int s18a_dword_800E3058 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC830.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC8B0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC8F0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC96C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC9E4.s")
const int s18a_dword_800E305C = 0x800CCA4C;
const int s18a_dword_800E3060 = 0x800CCA58;
const int s18a_dword_800E3064 = 0x800CCA64;
const int s18a_dword_800E3068 = 0x800CCA6C;
const int s18a_dword_800E306C = 0x800CCA7C;
const int s18a_dword_800E3070 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCA20.s")
const int s18a_dword_800E3074 = 0x800CCAB4;
const int s18a_dword_800E3078 = 0x800CCAC4;
const int s18a_dword_800E307C = 0x800CCAD4;
const int s18a_dword_800E3080 = 0x800CCACC;
const int s18a_dword_800E3084 = 0x800CCAD4;
const int s18a_dword_800E3088 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCA88.s")
const int s18a_dword_800E308C = 0x800CCB0C;
const int s18a_dword_800E3090 = 0x800CCB14;
const int s18a_dword_800E3094 = 0x800CCB2C;
const int s18a_dword_800E3098 = 0x800CCB24;
const int s18a_dword_800E309C = 0x800CCB2C;
const int s18a_dword_800E30A0 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCAE0.s")
const int s18a_dword_800E30A4 = 0x800CCB84;
const int s18a_dword_800E30A8 = 0x800CCB64;
const int s18a_dword_800E30AC = 0x800CCB6C;
const int s18a_dword_800E30B0 = 0x800CCB7C;
const int s18a_dword_800E30B4 = 0x800CCB84;
const int s18a_dword_800E30B8 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCB38.s")
const int s18a_dword_800E30BC = 0x800CCBDC;
const int s18a_dword_800E30C0 = 0x800CCBD4;
const int s18a_dword_800E30C4 = 0x800CCBBC;
const int s18a_dword_800E30C8 = 0x800CCBC4;
const int s18a_dword_800E30CC = 0x800CCBDC;
const int s18a_dword_800E30D0 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCB90.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCBE8.s")
const int s18a_dword_800E30D4 = 0x800CCC68;
const int s18a_dword_800E30D8 = 0x800CCC7C;
const int s18a_dword_800E30DC = 0x800CCC90;
const int s18a_dword_800E30E0 = 0x800CCCA4;
const int s18a_dword_800E30E4 = 0x800CCCB8;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCC0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCCE0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCD5C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCDA8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCDEC.s")
const int s18a_dword_800E30E8 = 0x786F7620;
const int s18a_dword_800E30EC = 0x6F686320;
const int s18a_dword_800E30F0 = 0x74616875;
const int s18a_dword_800E30F4 = 0x253D2075;
const int s18a_dword_800E30F8 = 0x000A2064;
const int s18a_dword_800E30FC = 0x786F7620;
const int s18a_dword_800E3100 = 0x69617320;
const int s18a_dword_800E3104 = 0x20756B73;
const int s18a_dword_800E3108 = 0x64253D20;
const int s18a_dword_800E310C = 0x00000A20;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCE24.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CCF48.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD2D8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD4AC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD504.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD544.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD59C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD62C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD6D0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD758.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD7F4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD8B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CD98C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDA40.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDAF8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDBB8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDC40.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDCD4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDD28.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDD68.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDDE0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDEFC.s")
const int s18a_dword_800E3110 = 0x635F6120;
const int s18a_dword_800E3114 = 0x746E756F;
const int s18a_dword_800E3118 = 0x25203D20;
const int s18a_dword_800E311C = 0x000A2064;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDFCC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE0F8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE170.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE314.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE3F8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE4CC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE530.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE584.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE634.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE674.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE6B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE710.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE770.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE858.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE93C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE97C.s")
const int s18a_dword_800E3120 = 0x65726120;
const int s18a_dword_800E3124 = 0x203D2061;
const int s18a_dword_800E3128 = 0x000A6425;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEA0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEB78.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEBC4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CED40.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CED80.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEDCC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEE0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEE58.s")
const char s18a_dword_800E312C[] = "go tekken 1";
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEEBC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEF30.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEF70.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEFE4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF090.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF0EC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF138.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF184.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF1CC.s")
const int s18a_dword_800E3138 = 0x73616870;
const int s18a_dword_800E313C = 0x6C203265;
const int s18a_dword_800E3140 = 0x20656669;
const int s18a_dword_800E3144 = 0x6425203D;
const int s18a_dword_800E3148 = 0x00000A20;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF214.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF338.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF3B0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF470.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF4BC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF508.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF554.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF5DC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF628.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF684.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF6E0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF72C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF778.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF7E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF838.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF884.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF8F0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF94C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF998.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF9E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFA50.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFA90.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFB48.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFB94.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFBE0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFC24.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFC70.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFCB4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFD54.s")
const int s18a_dword_800E314C = 0x800CFE14;
const int s18a_dword_800E3150 = 0x800CFE24;
const int s18a_dword_800E3154 = 0x800CFE34;
const int s18a_dword_800E3158 = 0x800CFE44;
const int s18a_dword_800E315C = 0x800CFE54;
const int s18a_dword_800E3160 = 0x800CFE64;
const int s18a_dword_800E3164 = 0x800CFE74;
const int s18a_dword_800E3168 = 0x800CFE8C;
const int s18a_dword_800E316C = 0x800CFE8C;
const int s18a_dword_800E3170 = 0x800CFE8C;
const int s18a_dword_800E3174 = 0x800CFE8C;
const int s18a_dword_800E3178 = 0x800CFE8C;
const int s18a_dword_800E317C = 0x800CFE8C;
const int s18a_dword_800E3180 = 0x800CFE8C;
const int s18a_dword_800E3184 = 0x800CFE8C;
const int s18a_dword_800E3188 = 0x800CFE8C;
const int s18a_dword_800E318C = 0x800CFE8C;
const int s18a_dword_800E3190 = 0x800CFE8C;
const int s18a_dword_800E3194 = 0x800CFE84;
const int s18a_dword_800E3198 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFDDC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFE9C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFF18.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFF48.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFFB8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0028.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D00C4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0114.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0164.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D01B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D01E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0254.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D02DC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D034C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D03C0.s")
const int s18a_dword_800E319C = 0x800D04A8;
const int s18a_dword_800E31A0 = 0x800D04B8;
const int s18a_dword_800E31A4 = 0x800D0488;
const int s18a_dword_800E31A8 = 0x800D0498;
const int s18a_dword_800E31AC = 0x800D0478;
const int s18a_dword_800E31B0 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0434.s")
const int s18a_dword_800E31B4 = 0x800D054C;
const int s18a_dword_800E31B8 = 0x800D053C;
const int s18a_dword_800E31BC = 0x800D055C;
const int s18a_dword_800E31C0 = 0x800D056C;
const int s18a_dword_800E31C4 = 0x800D0574;
const int s18a_dword_800E31C8 = 0x800D0574;
const int s18a_dword_800E31CC = 0x800D0574;
const int s18a_dword_800E31D0 = 0x800D0574;
const int s18a_dword_800E31D4 = 0x800D0574;
const int s18a_dword_800E31D8 = 0x800D0574;
const int s18a_dword_800E31DC = 0x800D0574;
const int s18a_dword_800E31E0 = 0x800D0574;
const int s18a_dword_800E31E4 = 0x800D0574;
const int s18a_dword_800E31E8 = 0x800D0574;
const int s18a_dword_800E31EC = 0x800D0574;
const int s18a_dword_800E31F0 = 0x800D0574;
const int s18a_dword_800E31F4 = 0x800D0574;
const int s18a_dword_800E31F8 = 0x800D0574;
const int s18a_dword_800E31FC = 0x800D0574;
const int s18a_dword_800E3200 = 0x800D0574;
const int s18a_dword_800E3204 = 0x800D0574;
const int s18a_dword_800E3208 = 0x800D0574;
const int s18a_dword_800E320C = 0x800D0574;
const int s18a_dword_800E3210 = 0x800D0574;
const int s18a_dword_800E3214 = 0x800D0574;
const int s18a_dword_800E3218 = 0x800D052C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D04E8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D059C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D060C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D063C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D066C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D069C.s")
const int s18a_dword_800E321C = 0x800D0740;
const int s18a_dword_800E3220 = 0x800D07C8;
const int s18a_dword_800E3224 = 0x800D0730;
const int s18a_dword_800E3228 = 0x800D07C8;
const int s18a_dword_800E322C = 0x800D07C0;
const int s18a_dword_800E3230 = 0x800D0750;
const int s18a_dword_800E3234 = 0x800D07C8;
const int s18a_dword_800E3238 = 0x800D0760;
const int s18a_dword_800E323C = 0x800D0770;
const int s18a_dword_800E3240 = 0x800D0780;
const int s18a_dword_800E3244 = 0x800D0790;
const int s18a_dword_800E3248 = 0x800D07B0;
const int s18a_dword_800E324C = 0x800D07A0;
const int s18a_dword_800E3250 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D06EC.s")
const int s18a_dword_800E3254 = 0x800D0844;
const int s18a_dword_800E3258 = 0x800D08CC;
const int s18a_dword_800E325C = 0x800D0834;
const int s18a_dword_800E3260 = 0x800D08CC;
const int s18a_dword_800E3264 = 0x800D08B4;
const int s18a_dword_800E3268 = 0x800D08CC;
const int s18a_dword_800E326C = 0x800D08CC;
const int s18a_dword_800E3270 = 0x800D0874;
const int s18a_dword_800E3274 = 0x800D0884;
const int s18a_dword_800E3278 = 0x800D0854;
const int s18a_dword_800E327C = 0x800D0864;
const int s18a_dword_800E3280 = 0x800D08A4;
const int s18a_dword_800E3284 = 0x800D0894;
const int s18a_dword_800E3288 = 0x800D08C4;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D07F0.s")
const int s18a_dword_800E328C = 0x800D0938;
const int s18a_dword_800E3290 = 0x800D09D0;
const int s18a_dword_800E3294 = 0x800D09C8;
const int s18a_dword_800E3298 = 0x800D0948;
const int s18a_dword_800E329C = 0x800D0958;
const int s18a_dword_800E32A0 = 0x800D0988;
const int s18a_dword_800E32A4 = 0x800D0998;
const int s18a_dword_800E32A8 = 0x800D0968;
const int s18a_dword_800E32AC = 0x800D0978;
const int s18a_dword_800E32B0 = 0x800D09A8;
const int s18a_dword_800E32B4 = 0x800D09D0;
const int s18a_dword_800E32B8 = 0x800D09D0;
const int s18a_dword_800E32BC = 0x800D09D0;
const int s18a_dword_800E32C0 = 0x800D09D0;
const int s18a_dword_800E32C4 = 0x800D09B8;
const int s18a_dword_800E32C8 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D08F4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D09F8.s")
const int s18a_dword_800E32CC = 0x800D0AC4;
const int s18a_dword_800E32D0 = 0x800D0AD4;
const int s18a_dword_800E32D4 = 0x800D0AE4;
const int s18a_dword_800E32D8 = 0x800D0AF4;
const int s18a_dword_800E32DC = 0x800D0B0C;
const int s18a_dword_800E32E0 = 0x800D0B04;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0A8C.s")
const int s18a_dword_800E32E4 = 0x800D0B60;
const int s18a_dword_800E32E8 = 0x800D0B80;
const int s18a_dword_800E32EC = 0x800D0B70;
const int s18a_dword_800E32F0 = 0x800D0BA0;
const int s18a_dword_800E32F4 = 0x800D0B90;
const int s18a_dword_800E32F8 = 0x800D0BB0;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0B1C.s")
const int s18a_dword_800E32FC = 0x800D0C0C;
const int s18a_dword_800E3300 = 0x800D0C1C;
const int s18a_dword_800E3304 = 0x800D0C2C;
const int s18a_dword_800E3308 = 0x800D0C4C;
const int s18a_dword_800E330C = 0x800D0C3C;
const int s18a_dword_800E3310 = 0x800D0C5C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0BD0.s")
const int s18a_dword_800E3314 = 0x800D0CB8;
const int s18a_dword_800E3318 = 0x800D0CC8;
const int s18a_dword_800E331C = 0x800D0CD8;
const int s18a_dword_800E3320 = 0x800D0CF8;
const int s18a_dword_800E3324 = 0x800D0CE8;
const int s18a_dword_800E3328 = 0x800D0D08;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0C74.s")
const int s18a_dword_800E332C = 0x800D0DD8;
const int s18a_dword_800E3330 = 0x800D0DE8;
const int s18a_dword_800E3334 = 0x800D0DF8;
const int s18a_dword_800E3338 = 0x800D0E08;
const int s18a_dword_800E333C = 0x800D0E18;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0D28.s")
