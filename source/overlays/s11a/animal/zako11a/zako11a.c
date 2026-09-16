#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    /* 0x000 */ GV_ACT actor;
    /* 0x020 */ char   pad20[ 0xC28 ];
} Work;

int s11a_dword_800C33EC = 0x000003E8;
int s11a_dword_800C33F0 = 0x000007D0;
int s11a_dword_800C33F4 = 0x000003E8;
int s11a_dword_800C33F8 = 0x000007D0;
int s11a_dword_800C33FC = 0x00001F40;
int s11a_dword_800C3400 = 0x00001F40;
int s11a_dword_800C3404 = 0x00001F40;
int s11a_dword_800C3408 = 0x00001F40;
int s11a_dword_800C340C = 0x000F012C;
int s11a_dword_800C3410 = 0x003C001E;
int s11a_dword_800C3414 = 0x0000005A;
int s11a_dword_800C3418 = 0x75307D01;

const char s11a_dword_800D7F54[] = "1ID[%d] %d %d %d\n";
const char s11a_dword_800D7F68[] = "2ID[%d] %d %d %d\n";
const char s11a_dword_800D7F7C[] = "ene_11a";
const char s11a_dword_800D7F84[] = "Err Err Err  Set time Over\n";
const char s11a_dword_800D7FA0[] = "Err Err Err  Set Dir Over\n";
const char s11a_dword_800D7FBC[] = "Err not enough work !!\n";
const char s11a_dword_800D7FD4[] = " low[pory=%d\n";
const char s11a_dword_800D7FE4[] = "watchar.c : action point Err\n";

/*---------------------------------------------------------------------------*/

void s11a_800C930C( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9314.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C93AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9428.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C94A4.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C95DC.s")
void s11a_800C95DC( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9728.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9854.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C98B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9ABC.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9B30.s")
void s11a_800C9B30( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9B50.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9BEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9C44.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9C9C.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C9D74.s")
void s11a_800C9D74( Work *work, int name, int where );

void *NewZako11A( int arg0, int arg1 )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, s11a_800C95DC, s11a_800C9B30, "zako11a.c" );
        s11a_800C9D74( work, arg0, arg1 );
    }
    return (void *)work;
}
