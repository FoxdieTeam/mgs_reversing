#include "game/game.h"
#include "menu/radio.h"

extern int rank_dword_800E1978;
extern int rank_dword_800CB454;
extern int rank_dword_800E1998;

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0E4C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0ECC.s")

void rank_800D11EC( void )
{
    menu_draw_triangle( (MenuPrim *)&rank_dword_800E1978, (Menu_Triangle *)&rank_dword_800CB454 );
}

void rank_800D1218( int a0, int a1, int a2 )
{
    int *vars;

    vars = &rank_dword_800E1998;
    vars[ 0 ] = a0;
    vars[ 1 ] = a1;
    vars[ 2 ] = a2;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1230.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D128C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D12D0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1380.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D13B8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D152C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1670.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1988.s")

void *rank_800D19D8( KCB *kcb )
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D19E4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1A40.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1A64.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1AF4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1B78.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1C10.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1C44.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1E00.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1FC0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2004.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2078.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D20B0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2144.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2188.s")
void rank_800D2188( int a0, int a1 );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D21BC.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D21DC.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2218.s")

void rank_800D23F0( void )
{
    /* do nothing */
}

void rank_800D23F8( int *work )
{
    if ( work[ 9 ] == 0 )
    {
        rank_800D2188( 0, 4 );
    }
}

void rank_800D2428( int *work )
{
    if ( work[ 9 ] == 0 )
    {
        rank_800D2188( 0, 1 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2458.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2544.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2574.s")

void rank_800D263C( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2644.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2830.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2864.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2888.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3678.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D369C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3708.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D38D8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3A28.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3B04.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3B7C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3C44.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3CA4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3E18.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3F94.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D4084.s")
