#include "game/game.h"

int s14e_dword_800C36F8 = 0x05DC012C;
int s14e_dword_800C36FC = 0x0000012C;
int s14e_dword_800C3700 = 0x00000000;
int s14e_dword_800C3704 = 0x00000000;
int s14e_dword_800C3708 = 0x01F40320;
int s14e_dword_800C370C = 0x00000320;
int s14e_dword_800C3710 = 0x00000064;
int s14e_dword_800C3714 = 0x00000000;
int s14e_dword_800C3718 = 0x0320012C;
int s14e_dword_800C371C = 0x0000012C;
int s14e_dword_800C3720 = 0x00000000;
int s14e_dword_800C3724 = 0x00000000;
int s14e_dword_800C3728 = 0x75307530;
int s14e_dword_800C372C = 0x00007530;
int s14e_dword_800C3730 = 0x00000FA0;
int s14e_dword_800C3734 = 0x00000BB8;
int s14e_dword_800C3738 = 0x00000FA0;
int s14e_dword_800C373C = 0x00001B58;
int s14e_dword_800C3740 = 0x00001F40;
int s14e_dword_800C3744 = 0x00001F40;
int s14e_dword_800C3748 = 0x00001F40;
int s14e_dword_800C374C = 0x00001F40;
int s14e_dword_800C3750 = 0x00001F40;
int s14e_dword_800C3754 = 0x00000000;

const char s14e_dword_800DD038[] = "dareda!!\n";
const char s14e_dword_800DD044[] = "nanno otoda!!\n";
const char s14e_dword_800DD054[] = "tadano hakoka\n";
const char s14e_dword_800DD064[] = "kono asiatoha??\n";
const char s14e_dword_800DD078[] = "kinoseika !!\n";
const char s14e_dword_800DD088[] = "itazo \n";
const char s14e_dword_800DD090[] = "kottida!!\n";
const char s14e_dword_800DD09C[] = "haitini modoruzo!!\n";
const char s14e_dword_800DD0B0[] = "kottida !!\n";
const char s14e_dword_800DD0BC[] = {0x0, 0x0, 0x0, 0x0};
const int s14e_dword_800DD0C0 = 0x800CE760;
const int s14e_dword_800DD0C4 = 0x800CE770;
const int s14e_dword_800DD0C8 = 0x800CE780;
const int s14e_dword_800DD0CC = 0x800CE790;
const int s14e_dword_800DD0D0 = 0x800CE7A0;
const int s14e_dword_800DD0D4 = 0x800CE7B0;
const int s14e_dword_800DD0D8 = 0x800CE7C0;
const int s14e_dword_800DD0DC = 0x800CE7D0;
const int s14e_dword_800DD0E0 = 0x800CEEF8;
const int s14e_dword_800DD0E4 = 0x800CEF2C;
const int s14e_dword_800DD0E8 = 0x800CEF60;
const int s14e_dword_800DD0EC = 0x800CEF94;
const int s14e_dword_800DD0F0 = 0x800CEFC8;
const int s14e_dword_800DD0F4 = 0x800CEFFC;
const int s14e_dword_800DD0F8 = 0x800CF030;
const int s14e_dword_800DD0FC = 0x800CF064;
const int s14e_dword_800DD100 = 0x800CF098;
const int s14e_dword_800DD104 = 0x800CF0CC;
const int s14e_dword_800DD108 = 0x800CF100;
const int s14e_dword_800DD10C = 0x800CF134;
const int s14e_dword_800DD110 = 0x800CF21C;
const int s14e_dword_800DD114 = 0x800CF134;
const int s14e_dword_800DD118 = 0x800CF21C;
const int s14e_dword_800DD11C = 0x800CF17C;
const int s14e_dword_800DD120 = 0x800CF21C;
const char s14e_dword_800DD124[] = {'z', 'k', '1', '4'};
const char s14e_dword_800DD128[] = {'c', 'o', 'm', '.'};
const char s14e_dword_800DD12C[] = {'c', 0x0, 0x0, 0xc};

int SECTION(".bss") s14e_dword_800DD688;
int SECTION(".bss") s14e_dword_800DD68C;
int SECTION(".bss") s14e_dword_800DD690;
int SECTION(".bss") s14e_dword_800DD694;
int SECTION(".bss") s14e_dword_800DD698;
int SECTION(".bss") s14e_dword_800DD69C;
int SECTION(".bss") s14e_dword_800DD6A0;
int SECTION(".bss") s14e_dword_800DD6A4;
int SECTION(".bss") s14e_dword_800DD6A8;
int SECTION(".bss") s14e_dword_800DD6AC;
int SECTION(".bss") s14e_dword_800DD6B0;
int SECTION(".bss") s14e_dword_800DD6B4;
int SECTION(".bss") s14e_dword_800DD6B8;
int SECTION(".bss") s14e_dword_800DD6BC;
int SECTION(".bss") s14e_dword_800DD6C0;
int SECTION(".bss") s14e_dword_800DD6C4;
int SECTION(".bss") s14e_dword_800DD6C8;
int SECTION(".bss") s14e_dword_800DD6CC;
int SECTION(".bss") s14e_dword_800DD6D0;
int SECTION(".bss") s14e_dword_800DD6D4;
int SECTION(".bss") s14e_dword_800DD6D8;
int SECTION(".bss") s14e_dword_800DD6DC;
int SECTION(".bss") s14e_dword_800DD6E0;
int SECTION(".bss") s14e_dword_800DD6E4;
int SECTION(".bss") s14e_dword_800DD6E8;
int SECTION(".bss") s14e_dword_800DD6EC;
int SECTION(".bss") s14e_dword_800DD6F0;
int SECTION(".bss") s14e_dword_800DD6F4;
int SECTION(".bss") s14e_dword_800DD6F8;
int SECTION(".bss") s14e_dword_800DD6FC;
int SECTION(".bss") s14e_dword_800DD700;
int SECTION(".bss") s14e_dword_800DD704;
int SECTION(".bss") s14e_dword_800DD708;
int SECTION(".bss") s14e_dword_800DD70C;
int SECTION(".bss") s14e_dword_800DD710;
int SECTION(".bss") s14e_dword_800DD714;
int SECTION(".bss") s14e_dword_800DD718;
int SECTION(".bss") s14e_dword_800DD71C;
int SECTION(".bss") s14e_dword_800DD720;
int SECTION(".bss") s14e_dword_800DD724;
int SECTION(".bss") s14e_dword_800DD728;
int SECTION(".bss") s14e_dword_800DD72C;
int SECTION(".bss") s14e_dword_800DD730;
int SECTION(".bss") s14e_dword_800DD734;
int SECTION(".bss") s14e_dword_800DD738;
int SECTION(".bss") s14e_dword_800DD73C;
int SECTION(".bss") s14e_dword_800DD740;
int SECTION(".bss") s14e_dword_800DD744;
int SECTION(".bss") s14e_dword_800DD748;
int SECTION(".bss") s14e_dword_800DD74C;
int SECTION(".bss") s14e_dword_800DD750;
int SECTION(".bss") s14e_dword_800DD754;
int SECTION(".bss") s14e_dword_800DD758;
int SECTION(".bss") s14e_dword_800DD75C;
int SECTION(".bss") s14e_dword_800DD760;
int SECTION(".bss") s14e_dword_800DD764;
int SECTION(".bss") s14e_dword_800DD768;
int SECTION(".bss") s14e_dword_800DD76C;
int SECTION(".bss") s14e_dword_800DD770;
int SECTION(".bss") s14e_dword_800DD774;
int SECTION(".bss") s14e_dword_800DD778;
int SECTION(".bss") s14e_dword_800DD77C;
int SECTION(".bss") s14e_dword_800DD780;
int SECTION(".bss") s14e_dword_800DD784;
int SECTION(".bss") s14e_dword_800DD788;
int SECTION(".bss") s14e_dword_800DD78C;
int SECTION(".bss") s14e_dword_800DD790;
int SECTION(".bss") s14e_dword_800DD794;
int SECTION(".bss") s14e_dword_800DD798;
int SECTION(".bss") s14e_dword_800DD79C;
int SECTION(".bss") s14e_dword_800DD7A0;
int SECTION(".bss") s14e_dword_800DD7A4;
int SECTION(".bss") s14e_dword_800DD7A8;
int SECTION(".bss") s14e_dword_800DD7AC;
int SECTION(".bss") s14e_dword_800DD7B0;
int SECTION(".bss") s14e_dword_800DD7B4;
int SECTION(".bss") s14e_dword_800DD7B8;
int SECTION(".bss") s14e_dword_800DD7BC;

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE0A0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE0E4.s")

void s14e_800CE104( int arg0 )
{
    s14e_dword_800DD7A4 = arg0;
}

void s14e_800CE110( int arg0 )
{
    s14e_dword_800DD7A0 = arg0;
}

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE11C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE168.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE1E0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE254.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE2B4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE30C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE3FC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE43C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE490.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE4E4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE538.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE58C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE5E0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE670.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE6C4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE728.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE7EC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CE93C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEA20.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEB38.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEB50.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEBB4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CECF0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEDE4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEE58.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CEEBC.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CF244.s")

void s14e_800CF2AC( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CF2B4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CF44C.s")
