#include "mgrex.h"

/* Metal Gear REX: movement decisions, motion state machine and weapons
 * (the original file name is unknown) */

int s17a_dword_800C5248 = 0x0000FEC0;
int s17a_dword_800C524C = 0x0071FCF4;
int s17a_dword_800C5250 = 0x0000FCF4;
int s17a_dword_800C5254 = 0x00E3FA2E;
int s17a_dword_800C5258 = 0x0000FAB0;
int s17a_dword_800C525C = 0x0155F84E;
int s17a_dword_800C5260 = 0x0000F808;
int s17a_dword_800C5264 = 0x01C7F858;
int s17a_dword_800C5268 = 0x0000F7CC;
int s17a_dword_800C526C = 0x0238F9F2;
int s17a_dword_800C5270 = 0x0000F88A;
int s17a_dword_800C5274 = 0x02AAFB50;
int s17a_dword_800C5278 = 0x00000140;
int s17a_dword_800C527C = 0xFF8FFCA4;
int s17a_dword_800C5280 = 0x00000316;
int s17a_dword_800C5284 = 0xFF1DFA06;
int s17a_dword_800C5288 = 0x00000564;
int s17a_dword_800C528C = 0xFEABF84E;
int s17a_dword_800C5290 = 0x00000802;
int s17a_dword_800C5294 = 0xFE39F858;
int s17a_dword_800C5298 = 0x00000654;
int s17a_dword_800C529C = 0xFDC8F9B6;
int s17a_dword_800C52A0 = 0x0000097E;
int s17a_dword_800C52A4 = 0xFD56FA4C;
int s17a_dword_800C52A8 = 0x00000000;
int s17a_dword_800C52AC = 0x00001388;
int s17a_dword_800C52B0 = 0x00000000;
int s17a_dword_800C52B4 = 0x0000EC78;
int s17a_dword_800C52B8 = 0x00000000;
int s17a_dword_800C52BC = 0x00000000;
int s17a_dword_800C52C0 = 0x00001F40;
int s17a_dword_800C52C4 = 0x00001388;
int s17a_dword_800C52C8 = 0x00000000;
int s17a_dword_800C52CC = 0x0000EC78;
int s17a_dword_800C52D0 = 0x00000000;
int s17a_dword_800C52D4 = 0x000007D0;
int s17a_dword_800C52D8 = 0x0000EC78;
int s17a_dword_800C52DC = 0x0000F830;
int s17a_dword_800C52E0 = 0x0000EC78;
int s17a_dword_800C52E4 = 0x00000FA0;
int s17a_dword_800C52E8 = 0x00001964;
int s17a_dword_800C52EC = 0x0000F060;
int s17a_dword_800C52F0 = 0x00001964;
int s17a_dword_800C52F4 = 0x03E80FA0;
int s17a_dword_800C52F8 = 0x00000FA0;
int s17a_dword_800C52FC = 0x00000000;
int s17a_dword_800C5300 = 0xFFFFF000;
int s17a_dword_800C5304 = 0x00000000;
int s17a_dword_800C5308 = 0x00000000;
int s17a_dword_800C530C = 0x00C8FE00;
int s17a_dword_800C5310 = 0x00000000;
int s17a_dword_800C5314 = 0xFF38FE00;
int s17a_dword_800C5318 = 0x00000000;
int s17a_dword_800C531C = 0xFE4E0190;
int s17a_dword_800C5320 = 0x000013EA;
int s17a_dword_800C5324 = 0xFC92FE70;
int s17a_dword_800C5328 = 0x0000154A;
int s17a_dword_800C532C = 0xFAD60190;
int s17a_dword_800C5330 = 0x000016AA;
int s17a_dword_800C5334 = 0xFE4EFE70;
int s17a_dword_800C5338 = 0x000013EA;
int s17a_dword_800C533C = 0xFC920190;
int s17a_dword_800C5340 = 0x0000154A;
int s17a_dword_800C5344 = 0xFAD6FE70;
int s17a_dword_800C5348 = 0x000016AA;
int s17a_dword_800C534C = 0x00000000;
int s17a_dword_800C5350 = 0xFFFFF000;
int s17a_dword_800C5354 = 0x00000000;
int s17a_dword_800C5358 = 0x00000000;

const int s17a_dword_800E5C84 = 0x00000000;
const int s17a_dword_800E5C88 = 0x00004E20;
const int s17a_dword_800E5C8C = 0x00004E20;
const int s17a_dword_800E5C90 = 0x00000000;
const int s17a_dword_800E5C94 = 0x0000B1E0;
const int s17a_dword_800E5C98 = 0x00000000;
const int s17a_dword_800E5C9C = 0x800DEDA8;
const int s17a_dword_800E5CA0 = 0x800DEDE8;
const int s17a_dword_800E5CA4 = 0x800DEE80;
const int s17a_dword_800E5CA8 = 0x800DEF24;
const int s17a_dword_800E5CAC = 0x800DF000;
const int s17a_dword_800E5CB0 = 0x800DF058;
const int s17a_dword_800E5CB4 = 0x800DF09C;
const int s17a_dword_800E5CB8 = 0x800DF0DC;
const int s17a_dword_800E5CBC = 0x800DF124;
const int s17a_dword_800E5CC0 = 0x800DF178;
const int s17a_dword_800E5CC4 = 0x800DF1B8;
const int s17a_dword_800E5CC8 = 0x800DF268;
const int s17a_dword_800E5CCC = 0x800DF328;
const int s17a_dword_800E5CD0 = 0x800DF360;
const char s17a_dword_800E5CD4[] = "l_hatch2";

#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DD910.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DDFC4.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DE43C.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DE7B4.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DE8CC.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DE900.s")

int s17a_800DEBB4(MGREX_WORK *work, int action, int arg2)
{
    if (work->f1960 == 1 && work->f1954 != action)
    {
        work->f1954 = action;
        work->f1958 = arg2;
        work->f1960 = 0;
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DEBEC.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DEC6C.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DECA8.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DECE4.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DF3E8.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DF720.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DFAE8.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DFF74.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800E0328.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800E0710.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800E085C.s")
