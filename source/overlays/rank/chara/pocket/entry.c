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

void rank_800D128C( int a0, int a1, int a2, int a3 )
{
    int *vars;
    int  packed;
    int  code;

    vars = &rank_dword_800E1998;

    if ( a3 != 0 )
        goto nonzero;

    packed = a0 | ( a1 << 8 ) | ( a2 << 16 );
    code = 0x64000000;
    goto combine;

nonzero:
    packed = a0 | ( a1 << 8 ) | ( a2 << 16 );
    code = 0x2C000000;

combine:
    vars[ 3 ] = packed | code;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D12D0.s")

void rank_800D1380( void )
{
    MenuPrim *prim;

    prim = (MenuPrim *)&rank_dword_800E1978;
    prim->ot = DG_Chanl( 1 )->ot[ GV_Clock ];
    prim->next = prim->buf[ GV_Clock ];
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D13B8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D152C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1670.s")

void rank_800D1988( char *a0, int a1, int a2 )
{
    KCB *kcb;
    int  offset;

    offset = a1 * 44 + 0x10;
    kcb = (KCB *)( a0 + offset );
    font_set_color( kcb, 0, a2, 0 );
    font_clut_update( kcb );
}

void *rank_800D19D8( KCB *kcb )
{
    return kcb->cbuffer;
}

void rank_800D19E4( char *a0 )
{
    int i;

    for ( i = 0; i < *(int *)( a0 + 0x430 ); i++ )
    {
        rank_800D1988( a0, i, 0 );
    }
}

void rank_800D1A40( char *a0, int a1 )
{
    rank_800D1988( a0 + 0x30, a1, 0x6739 );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1A64.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1AF4.s")
void *rank_800D1AF4( int id );

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

void rank_800D1FC0( char *work, int a1, int a2 )
{
    int idx;
    int addr;

    idx = *(int *)( work + 0x1998 );

    if ( idx != 8 )
    {
        addr = ( int )work + idx * 4;
        *(short *)( addr + 0x199C ) = a1;
        addr = *(int *)( work + 0x1998 ) * 4;
        *(short *)( work + addr + 0x199E ) = a2;
        *(int *)( work + 0x1998 ) = *(int *)( work + 0x1998 ) + 1;
    }
}

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

void *rank_800D20B0( int id, int count, int flag, int a3 )
{
    char *work;
    void *buf;

    work = rank_800D1AF4( id );
    if ( !work )
    {
        return 0;
    }

    *(short *)( work + 0x10 ) = count;
    work[ 0x12 ] = flag;
    work[ 0x1C ] = a3;

    if ( count > 0 )
    {
        buf = rank_800D1C10( count, flag );
        if ( !buf )
        {
            return 0;
        }

        *(int *)( work + 0x20 ) = (int)buf;
    }

    *(short *)( work + 0x24 ) = id;
    return work;
}

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

void rank_800D21DC( char *work )
{
    long arg;

    arg = 0;
    rank_800D2078( *(int *)( work + 0x19D8 ), &arg, 1 );
    GV_DestroyActor( work );
}

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
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D28D4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3678.s")

void rank_800D369C( char *work )
{
    int count;
    int flag;

    count = *(int *)( work + 0x20 );
    flag = *(int *)( work + 0x24 );

    if ( count <= 0xF423F )
    {
        *(int *)( work + 0x20 ) = count + 1;
    }

    if ( flag == 0 && count == 0 )
    {
        rank_800D1FC0( work, 0, 1 );
        rank_800D1FC0( work, 1, 1 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3708.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D38D8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3A28.s")

void rank_800D3B04( char *work )
{
    int   i;
    char *str;
    int  *dst;

    if ( GCL_GetOption( 'p' ) )
    {
        i = 0;
        dst = (int *)( work + 0x19C8 );

        for ( ;; )
        {
            str = GCL_NextStr();

            if ( !str )
            {
                break;
            }

            if ( i == 4 )
            {
                break;
            }

            *dst++ = GCL_StrToInt( str );
            i++;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3B7C.s")

extern void rank_800D28D4( void );

int rank_800D3C44( char *work )
{
    char *act;

    act = rank_800D20B0( 0, 4, 0, 2 );
    if ( !act )
    {
        return -1;
    }

    *(void **)( act + 8 ) = rank_800D28D4;
    *(int *)( work + 0x28 ) = -1;
    *(int *)( work + 0x2C ) = 0;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3CA4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3E18.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3F94.s")
int  rank_800D3F94( void *work, int map );
void rank_800D38D8( void );
void rank_800D3A28( void );

extern int        rank_dword_800E59F0;
extern const char rank_dword_800E098C[];

void *rank_800D4084( int a0, int a1 )
{
    void *work;

    rank_dword_800E59F0 = 0;
    GM_GameStatus |= STATE_ALL_OFF;
    rank_dword_800E59F4 = 0;

    work = GV_NewActor( 6, 0x1A00 );
    if ( work )
    {
        GV_SetNamedActor( work, (void *)rank_800D38D8, (void *)rank_800D3A28, rank_dword_800E098C );

        if ( rank_800D3F94( work, a1 ) < 0 )
        {
            GV_DestroyActor( work );
            return 0;
        }
    }

    return work;
}
