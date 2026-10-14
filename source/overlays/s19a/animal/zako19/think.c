#include "zako.h"

/*---------------------------------------------------------------------------*/

int s19a_dword_800C36C4 = 0x00320064;
int s19a_dword_800C36C8 = 0x000A0019;
int s19a_dword_800C36CC = 0x000F012C;
int s19a_dword_800C36D0 = 0x003C001E;
int s19a_dword_800C36D4 = 0x0000005A;
int s19a_dword_800C36D8 = 0x75300000;
int s19a_dword_800C36DC = 0x00000000;
int s19a_dword_800C36E0 = 0x00000001;
int s19a_dword_800C36E4 = 0x00000002;
int s19a_dword_800C36E8 = 0x00000004;
int s19a_dword_800C36EC = 0x00000004;
int s19a_dword_800C36F0 = 0x00000040;
int s19a_dword_800C36F4 = 0x00000080;
int s19a_dword_800C36F8 = 0x00000200;
int s19a_dword_800C36FC = 0x00000400;
int s19a_dword_800C3700 = 0x00000800;
int s19a_dword_800C3704 = 0x00000100;
int s19a_dword_800C3708 = 0x00010000;
int s19a_dword_800C370C = 0x00000000;
int s19a_dword_800C3710 = 0x00000000;
int s19a_dword_800C3714 = 0x00000000;
int s19a_dword_800C3718 = 0x00000000;
int s19a_dword_800C371C = 0x00000000;
int s19a_dword_800C3720 = 0x00000001;
int s19a_dword_800C3724 = 0x00000002;
int s19a_dword_800C3728 = 0x00000004;
int s19a_dword_800C372C = 0x00000004;
int s19a_dword_800C3730 = 0x00000040;
int s19a_dword_800C3734 = 0x00000080;
int s19a_dword_800C3738 = 0x00000200;
int s19a_dword_800C373C = 0x00000400;
int s19a_dword_800C3740 = 0x00000800;
int s19a_dword_800C3744 = 0x00000000;
int s19a_dword_800C3748 = 0x00000000;
int s19a_dword_800C374C = 0x00000000;
int s19a_dword_800C3750 = 0x00000000;
int s19a_dword_800C3754 = 0x00000000;
int s19a_dword_800C3758 = 0x00000000;

const int s19a_dword_800E01B8 = 0x74617720;
const int s19a_dword_800E01BC = 0x61206863;
const int s19a_dword_800E01C0 = 0x74207463;
const int s19a_dword_800E01C4 = 0x20656D69;
const int s19a_dword_800E01C8 = 0x6425203D;
const int s19a_dword_800E01CC = 0x00200A20;
const char s19a_dword_800E01D0[] = "kirari01";
const int s19a_dword_800E01DC = 0x6F6F5220;
const int s19a_dword_800E01E0 = 0x68432074;
const int s19a_dword_800E01E4 = 0x65676E61;
const int s19a_dword_800E01E8 = 0x0A212120;
const int s19a_dword_800E01EC = 0x00000000;
const int s19a_dword_800E01F0 = 0x800D5AFC;
const int s19a_dword_800E01F4 = 0x800D5B14;
const int s19a_dword_800E01F8 = 0x800D5B8C;
const int s19a_dword_800E01FC = 0x800D5B2C;
const int s19a_dword_800E0200 = 0x800D5B44;
const int s19a_dword_800E0204 = 0x800D5B5C;
const int s19a_dword_800E0208 = 0x800D5B74;
const int s19a_dword_800E020C = 0x00000000;
const int s19a_dword_800E0210 = 0x800D61F4;
const int s19a_dword_800E0214 = 0x800D6204;
const int s19a_dword_800E0218 = 0x800D6220;
const int s19a_dword_800E021C = 0x800D623C;
const int s19a_dword_800E0220 = 0x800D6258;
const int s19a_dword_800E0224 = 0x800D6274;
const int s19a_dword_800E0228 = 0x800D61E4;
const int s19a_dword_800E022C = 0x800D6290;
const int s19a_dword_800E0230 = 0x800D6418;
const int s19a_dword_800E0234 = 0x800D6408;
const int s19a_dword_800E0238 = 0x800D6430;
const int s19a_dword_800E023C = 0x800D6428;
const int s19a_dword_800E0240 = 0x800D6430;
const int s19a_dword_800E0244 = 0x800D6430;
const int s19a_dword_800E0248 = 0x800D6430;
const int s19a_dword_800E024C = 0x800D63D8;
const int s19a_dword_800E0250 = 0x800D63E8;
const int s19a_dword_800E0254 = 0x800D63F8;

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3A4C.s")
void s19a_800D3A4C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3A84.s")
void s19a_800D3A84( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3ACC.s")
void s19a_800D3ACC( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3B48.s")
void s19a_800D3B48( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3B88.s")
void s19a_800D3B88( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3BE4.s")
void s19a_800D3BE4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3C6C.s")
void s19a_800D3C6C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3CCC.s")
void s19a_800D3CCC( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3CE4.s")
void s19a_800D3CE4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3CFC.s")
void s19a_800D3CFC( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3D6C.s")
void s19a_800D3D6C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3DD8.s")
void s19a_800D3DD8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3E9C.s")
void s19a_800D3E9C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3EB4.s")
void s19a_800D3EB4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3F70.s")
void s19a_800D3F70( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3F88.s")
void s19a_800D3F88( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D3FC0.s")
void s19a_800D3FC0( void );

int s19a_800D4058( Work *work )
{
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4060.s")
void s19a_800D4060( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D40CC.s")
void s19a_800D40CC( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D40E8.s")
void s19a_800D40E8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4110.s")
void s19a_800D4110( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4124.s")
void s19a_800D4124( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D43E4.s")
void s19a_800D43E4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4438.s")
void s19a_800D4438( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4530.s")
void s19a_800D4530( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4580.s")
void s19a_800D4580( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D46B8.s")
void s19a_800D46B8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4728.s")
void s19a_800D4728( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4760.s")
void s19a_800D4760( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D479C.s")
void s19a_800D479C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D480C.s")
void s19a_800D480C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4854.s")
void s19a_800D4854( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D48D0.s")
void s19a_800D48D0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D48E0.s")
void s19a_800D48E0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D48F0.s")
void s19a_800D48F0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4960.s")
void s19a_800D4960( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D49E8.s")
void s19a_800D49E8( void );

int s19a_800D4A34( Work *work )
{
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4A3C.s")
void s19a_800D4A3C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4A88.s")
void s19a_800D4A88( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4AF8.s")
void s19a_800D4AF8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4B4C.s")
void s19a_800D4B4C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4BE0.s")
void s19a_800D4BE0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4C7C.s")
void s19a_800D4C7C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4CD8.s")
void s19a_800D4CD8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4D3C.s")
void s19a_800D4D3C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4D98.s")
void s19a_800D4D98( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4E04.s")
void s19a_800D4E04( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4F38.s")
void s19a_800D4F38( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D4FB4.s")
void s19a_800D4FB4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5030.s")
void s19a_800D5030( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D50B0.s")
void s19a_800D50B0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D51A4.s")
void s19a_800D51A4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5210.s")
void s19a_800D5210( void );

void s19a_800D53B8( Work *work )
{
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D53C0.s")
void s19a_800D53C0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5484.s")
void s19a_800D5484( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D555C.s")
void s19a_800D555C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5624.s")
void s19a_800D5624( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D57F4.s")
void s19a_800D57F4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D59B8.s")
void s19a_800D59B8( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5AB0.s")
void s19a_800D5AB0( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5CB4.s")
void s19a_800D5CB4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5DAC.s")
void s19a_800D5DAC( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5E58.s")
void s19a_800D5E58( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5F50.s")
void s19a_800D5F50( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D607C.s")
void s19a_800D607C( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D61A4.s")
void s19a_800D61A4( void );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D649C.s")
void s19a_800D649C( Work *work );


