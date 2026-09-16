#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    /* 0x000 */ GV_ACT actor;
    /* 0x020 */ char   pad20[ 0x4 ];
} Work;

int s11a_dword_800C39C0 = 0x05DC012C;
int s11a_dword_800C39C4 = 0x0000012C;
int s11a_dword_800C39C8 = 0x00000000;
int s11a_dword_800C39CC = 0x00000000;
int s11a_dword_800C39D0 = 0x01F40320;
int s11a_dword_800C39D4 = 0x00000320;
int s11a_dword_800C39D8 = 0x00000064;
int s11a_dword_800C39DC = 0x00000000;
int s11a_dword_800C39E0 = 0x0320012C;
int s11a_dword_800C39E4 = 0x0000012C;
int s11a_dword_800C39E8 = 0x00000000;
int s11a_dword_800C39EC = 0x00000000;
int s11a_dword_800C39F0 = 0x75307530;
int s11a_dword_800C39F4 = 0x00007530;
int s11a_dword_800C39F8 = 0x00000FA0;
int s11a_dword_800C39FC = 0x00000000;
int s11a_dword_800C3A00 = 0x00000A01;
int s11a_dword_800C3A04 = 0x00000AFF;

const char s11a_dword_800D83FC[] = "dareda!!\n";
const char s11a_dword_800D8408[] = "nanno otoda!!\n";
const char s11a_dword_800D8418[] = "tadano hakoka\n";
const char s11a_dword_800D8428[] = "kono asiatoha??\n";
const char s11a_dword_800D843C[] = "kinoseika !!\n";
const char s11a_dword_800D844C[] = "itazo \n";
const char s11a_dword_800D8454[] = "kottida!!\n";
const char s11a_dword_800D8460[] = "haitini modoruzo!!\n";
const char s11a_dword_800D8474[] = "kottida !!\n";

const char s11a_dword_800D8480[] = {0x0, 0x0, 0x0, 0x0};

const int s11a_dword_800D8484 = 0x800D25FC;
const int s11a_dword_800D8488 = 0x800D260C;
const int s11a_dword_800D848C = 0x800D261C;
const int s11a_dword_800D8490 = 0x800D262C;
const int s11a_dword_800D8494 = 0x800D263C;
const int s11a_dword_800D8498 = 0x800D264C;
const int s11a_dword_800D849C = 0x800D265C;
const int s11a_dword_800D84A0 = 0x800D266C;

const char s11a_dword_800D84A4[] = " FLAG1!!\n";
const char s11a_dword_800D84B0[] = " FLAG2!!\n";
const char s11a_dword_800D84BC[] = " FLAG3!!\n";
const char s11a_dword_800D84C8[] = " FLAG4!!\n";
const char s11a_dword_800D84D4[] = " FLAG5!!\n";
const char s11a_dword_800D84E0[] = " FLAG6!!\n";
const char s11a_dword_800D84EC[] = " FLAG7!!\n";
const char s11a_dword_800D84F8[] = " FLAG8!!\n";
const char s11a_dword_800D8504[] = " FLAG9!!\n";
const char s11a_dword_800D8510[] = " FLAG10!!\n";

const int s11a_dword_800D851C = 0x800D2CBC;
const int s11a_dword_800D8520 = 0x800D2E04;
const int s11a_dword_800D8524 = 0x800D2E40;
const int s11a_dword_800D8528 = 0x800D2E7C;
const int s11a_dword_800D852C = 0x800D2EBC;
const int s11a_dword_800D8530 = 0x800D2EFC;
const int s11a_dword_800D8534 = 0x800D2F3C;
const int s11a_dword_800D8538 = 0x800D2F7C;
const int s11a_dword_800D853C = 0x800D2FE0;
const int s11a_dword_800D8540 = 0x800D3020;
const int s11a_dword_800D8544 = 0x800D3060;
const int s11a_dword_800D8548 = 0x800D310C;
const int s11a_dword_800D854C = 0x800D310C;
const int s11a_dword_800D8550 = 0x800D310C;
const int s11a_dword_800D8554 = 0x800D310C;
const int s11a_dword_800D8558 = 0x800D310C;
const int s11a_dword_800D855C = 0x800D30C8;
const int s11a_dword_800D8560 = 0x800D310C;

const char s11a_dword_800D8564[] = "zone=%d ";

int SECTION(".bss") s11a_dword_800D8A58;
int SECTION(".bss") s11a_dword_800D8A5C;
int SECTION(".bss") s11a_dword_800D8A60;
int SECTION(".bss") s11a_dword_800D8A64;
int SECTION(".bss") s11a_dword_800D8A68;
int SECTION(".bss") s11a_dword_800D8A6C;
int SECTION(".bss") s11a_dword_800D8A70;
int SECTION(".bss") s11a_dword_800D8A74;
int SECTION(".bss") s11a_dword_800D8A78;
int SECTION(".bss") s11a_dword_800D8A7C;
int SECTION(".bss") s11a_dword_800D8A80;
int SECTION(".bss") s11a_dword_800D8A84;
int SECTION(".bss") s11a_dword_800D8A88;
int SECTION(".bss") s11a_dword_800D8A8C;
int SECTION(".bss") s11a_dword_800D8A90;
int SECTION(".bss") s11a_dword_800D8A94;
int SECTION(".bss") s11a_dword_800D8A98;
int SECTION(".bss") s11a_dword_800D8A9C;
int SECTION(".bss") s11a_dword_800D8AA0;
int SECTION(".bss") s11a_dword_800D8AA4;
int SECTION(".bss") s11a_dword_800D8AA8;
int SECTION(".bss") s11a_dword_800D8AAC;
int SECTION(".bss") s11a_dword_800D8AB0;
int SECTION(".bss") s11a_dword_800D8AB4;
int SECTION(".bss") s11a_dword_800D8AB8;
int SECTION(".bss") s11a_dword_800D8ABC;
int SECTION(".bss") s11a_dword_800D8AC0;
int SECTION(".bss") s11a_dword_800D8AC4;
int SECTION(".bss") s11a_dword_800D8AC8;
int SECTION(".bss") s11a_dword_800D8ACC;
int SECTION(".bss") s11a_dword_800D8AD0;
int SECTION(".bss") s11a_dword_800D8AD4;
int SECTION(".bss") s11a_dword_800D8AD8;
int SECTION(".bss") s11a_dword_800D8ADC;
int SECTION(".bss") s11a_dword_800D8AE0;
int SECTION(".bss") s11a_dword_800D8AE4;
int SECTION(".bss") s11a_dword_800D8AE8;
int SECTION(".bss") s11a_dword_800D8AEC;
int SECTION(".bss") s11a_dword_800D8AF0;
int SECTION(".bss") s11a_dword_800D8AF4;
int SECTION(".bss") s11a_dword_800D8AF8;
int SECTION(".bss") s11a_dword_800D8AFC;
int SECTION(".bss") s11a_dword_800D8B00;
int SECTION(".bss") s11a_dword_800D8B04;
int SECTION(".bss") s11a_dword_800D8B08;
int SECTION(".bss") s11a_dword_800D8B0C;
int SECTION(".bss") s11a_dword_800D8B10;
int SECTION(".bss") s11a_dword_800D8B14;
int SECTION(".bss") s11a_dword_800D8B18;
int SECTION(".bss") s11a_dword_800D8B1C;
int SECTION(".bss") s11a_dword_800D8B20;
int SECTION(".bss") s11a_dword_800D8B24;
int SECTION(".bss") s11a_dword_800D8B28;
int SECTION(".bss") s11a_dword_800D8B2C;
int SECTION(".bss") s11a_dword_800D8B30;
int SECTION(".bss") s11a_dword_800D8B34;
int SECTION(".bss") s11a_dword_800D8B38;
int SECTION(".bss") s11a_dword_800D8B3C;
int SECTION(".bss") s11a_dword_800D8B40;
int SECTION(".bss") s11a_dword_800D8B44;
int SECTION(".bss") s11a_dword_800D8B48;
int SECTION(".bss") s11a_dword_800D8B4C;
int SECTION(".bss") s11a_dword_800D8B50;
int SECTION(".bss") s11a_dword_800D8B54;
int SECTION(".bss") s11a_dword_800D8B58;
int SECTION(".bss") s11a_dword_800D8B5C;
int SECTION(".bss") s11a_dword_800D8B60;
int SECTION(".bss") s11a_dword_800D8B64;
int SECTION(".bss") s11a_dword_800D8B68;
int SECTION(".bss") s11a_dword_800D8B6C;
int SECTION(".bss") s11a_dword_800D8B70;
int SECTION(".bss") s11a_dword_800D8B74;
int SECTION(".bss") s11a_dword_800D8B78;
int SECTION(".bss") s11a_dword_800D8B7C;
int SECTION(".bss") s11a_dword_800D8B80;
int SECTION(".bss") s11a_dword_800D8B84;
int SECTION(".bss") s11a_dword_800D8B88;
int SECTION(".bss") s11a_dword_800D8B8C;
int SECTION(".bss") s11a_dword_800D8B90;
int SECTION(".bss") s11a_dword_800D8B94;

/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2010.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2054.s")

void s11a_800D2074( int arg0 )
{
    s11a_dword_800D8B84 = arg0;
}

void s11a_800D2080( int arg0 )
{
    s11a_dword_800D8B80 = arg0;
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D208C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D20D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2150.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D21C4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2224.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D227C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2298.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D22D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D232C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2380.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D23D4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2428.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D247C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D250C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2560.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D25C4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2688.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D276C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2878.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2890.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D28F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2A50.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2B3C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2B90.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2BF4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D2C3C.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D313C.s")
void s11a_800D313C( Work *work );

void s11a_800D31A4( Work *work )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D31AC.s")
void s11a_800D31AC( Work *work, int name, int where );

void *NewZako11ACommander( int arg0, int arg1 )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, s11a_800D313C, s11a_800D31A4, "zk11acom.c" );
        s11a_800D31AC( work, arg0, arg1 );
    }
    return (void *)work;
}
