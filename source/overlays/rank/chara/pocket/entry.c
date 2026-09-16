#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"

extern int rank_dword_800E1978;
extern int rank_dword_800CB454;
extern int rank_dword_800E1998;
extern int rank_dword_800E59F4;

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
void rank_800D1988( char *a0, int a1, int a2 );

void *rank_800D19D8( KCB *kcb )
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D19E4.s")

void rank_800D1A40( char *a0, int a1 )
{
    rank_800D1988( a0 + 0x30, a1, 0x6739 );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1A64.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1AF4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1B78.s")

void *rank_800D1C10( int count, int flag )
{
    int size;

    size = 0x34;
    if ( flag == 0 )
    {
        size = 0x28;
    }

    return GV_Malloc( count * size );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1C44.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1E00.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1FC0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2004.s")

int rank_800D2078( int proc_id, long *argv, int argc )
{
    GCL_ARGS  args;
    GCL_ARGS *pArgs;

    pArgs = NULL;
    if ( argc )
    {
        pArgs = &args;
        args.argc = argc;
        args.argv = argv;
    }

    return GCL_ExecProc( proc_id, pArgs );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D20B0.s")

char *rank_800D2144( int id )
{
    char *iter;

    for ( iter = (char *)rank_dword_800E59F4; iter; iter = *(char **)( iter + 4 ) )
    {
        if ( *(unsigned short *)( iter + 0x24 ) == id )
        {
            return iter;
        }
    }

    return 0;
}

void rank_800D2188( int id, int mask )
{
    unsigned short *flags;

    flags = (unsigned short *)( rank_800D2144( id ) + 0x1E );
    *flags |= mask;
}

void rank_800D21BC( unsigned char *a0, unsigned int a1 )
{
    unsigned int v0;

    v0 = a0[ 7 ];
    v0 &= 2;
    v0 |= 0x2C;
    v0 <<= 24;
    a1 |= v0;
    *(unsigned int *)( a0 + 4 ) = a1;
}

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

void rank_800D2544( int *work )
{
    if ( work[ 9 ] == 0 )
    {
        rank_800D2188( 0, 2 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2574.s")

void rank_800D263C( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2644.s")

void rank_800D2830( int arg0 )
{
    char *ptr;

    ptr = rank_800D2144( 1 );
    ptr[ 0x13 ] = 1;
    ptr[ 0x1C ] = arg0;
}

void rank_800D2864( void )
{
    char *ptr;

    ptr = rank_800D2144( 1 );
    ptr[ 0x13 ] = 0;
}

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
