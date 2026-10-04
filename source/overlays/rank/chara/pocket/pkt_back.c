#include "game/game.h"
#include "libgcl/libgcl.h"

extern int         rank_dword_800E1970;
extern int         rank_dword_800E1974;
extern const char  rank_dword_800E07DC[];

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE0C.s")
void *rank_800CEE0C( void );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE90.s")
void rank_800CEE90( char *node );

void *rank_800CEF28( int count, int flag )
{
    int size;

    size = 0x34;
    if ( flag == 0 )
    {
        size = 0x28;
    }

    return GV_Malloc( count * size );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEF5C.s")

void rank_800CF11C( char *work, int a1, int a2 )
{
    int idx;
    int addr;

    idx = *(int *)( work + 0x34 );

    if ( idx != 8 )
    {
        addr = ( int )work + idx * 4;
        *(short *)( addr + 0x38 ) = a1;
        addr = *(int *)( work + 0x34 ) * 4;
        *(short *)( work + addr + 0x3A ) = a2;
        *(int *)( work + 0x34 ) = *(int *)( work + 0x34 ) + 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF160.s")

void rank_800CF1D4( char *work )
{
    work[ 0x13 ] = 0;
    *(short *)( work + 0x26 ) = 0;
    *(short *)( work + 0x0E ) = 0;
    *(short *)( work + 0x0C ) = 0;
    *(int *)( work + 0x18 ) = 0;
    *(int *)( work + 0x14 ) = 0;
    *(short *)( work + 0x1E ) = 0;
}

void *rank_800CF1F4( int id, int count, int flag, int a3 )
{
    char *work;
    void *buf;

    work = rank_800CEE0C();
    if ( !work )
    {
        return 0;
    }

    *(short *)( work + 0x10 ) = count;
    work[ 0x12 ] = flag;
    work[ 0x1C ] = a3;

    if ( count > 0 )
    {
        buf = rank_800CEF28( count, flag );
        if ( !buf )
        {
            return 0;
        }

        *(int *)( work + 0x20 ) = (int)buf;
    }

    *(short *)( work + 0x24 ) = id;
    return work;
}

int rank_800CF288( int max )
{
    int pow2;
    int half;
    int diff;
    int result;

    half = max;
    pow2 = 1;

    if ( max >= 2 )
    {
        do
        {
            half /= 2;
            pow2 *= 2;
        } while ( half >= 2 );
    }

    pow2 *= 2;
    diff = pow2 - max;

    do
    {
        result = GV_RandU( pow2 ) - diff;
    } while ( result < 0 );

    return result;
}

void rank_800CF2F0( unsigned short *work, int a1 )
{
    int            tpage;
    unsigned short tpage2;

    tpage = tpage2 = work[ 0xB ];
    work[ 0xB ] = ( tpage & 0x180 ) | ( ( a1 & 3 ) << 5 ) | ( work[ 0xB ] & 0x10 ) | ( work[ 0xB ] & 0xF ) | ( tpage & 0x800 );
}

char *rank_800CF328( int id )
{
    char *iter;

    for ( iter = (char *)rank_dword_800E1974; iter; iter = *(char **)( iter + 4 ) )
    {
        if ( *(unsigned short *)( iter + 0x24 ) == id )
        {
            return iter;
        }
    }

    return 0;
}

void rank_800CF36C( int id, int mask )
{
    unsigned short *flags;

    flags = (unsigned short *)( rank_800CF328( id ) + 0x1E );
    *flags &= ~mask;
}

void rank_800CF3A0( int id )
{
    rank_800CF1D4( rank_800CF328( id ) );
}

void rank_800CF3C8( char *work )
{
    GCL_ExecProc( *(int *)( work + 0x64 ), NULL );
    GV_DestroyActor( work );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF3FC.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF938.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CFBD8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CFD00.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CFF1C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D007C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0258.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D03E8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D04A8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0648.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0820.s")
void rank_800CEE90( char *node );

void rank_800D090C( char *work )
{
    void *prim;

    if ( rank_dword_800E1970 > 0 )
    {
        do
        {
            rank_800CEE90( (char *)rank_dword_800E1974 );
        } while ( rank_dword_800E1970 > 0 );
    }

    prim = *(void **)( work + 0x2C );
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }

    prim = *(void **)( work + 0x30 );
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }
}

void rank_800D09AC( char *work )
{
    int   i;
    char *str;
    int  *dst;

    if ( GCL_GetOption( 'p' ) )
    {
        i = 0;
        dst = (int *)( work + 0x64 );

        for ( ;; )
        {
            str = GCL_NextStr();

            if ( !str )
            {
                break;
            }

            if ( i == 1 )
            {
                break;
            }

            *dst++ = GCL_StrToInt( str );
            i++;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0A24.s")
int rank_800D0A24( char *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0A70.s")
int rank_800D0A70( char *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0ABC.s")
int rank_800D0ABC( char *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0B08.s")
int rank_800D0B08( char *work );

int rank_800D0B54( char *work )
{
    if ( rank_800D0B08( work ) < 0 )
    {
        return -1;
    }

    if ( rank_800D0ABC( work ) < 0 )
    {
        return -1;
    }

    if ( rank_800D0A70( work ) < 0 )
    {
        return -1;
    }

    if ( rank_800D0A24( work ) < 0 )
    {
        return -1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0BC0.s")
int  rank_800D0BC0( char *work );
void rank_800D0820( char *work );

int rank_800D0D24( char *work, int map )
{
    GM_CurrentMap = map;
    rank_800D09AC( work );

    if ( rank_800D0B54( work ) < 0 )
    {
        return -1;
    }

    if ( rank_800D0BC0( work ) < 0 )
    {
        return -1;
    }

    *(GV_PAD **)( work + 0x58 ) = &GV_PadData[ 2 ];
    *(int *)( work + 0x24 ) = 0;
    *(unsigned int *)( work + 0x5C ) |= 0x100000;
    rank_800D0820( work );
    return 0;
}

void *rank_800D0DA0( int a0, int a1 )
{
    void *work;

    rank_dword_800E1970 = 0;
    GM_GameStatus |= STATE_ALL_OFF;
    rank_dword_800E1974 = 0;

    work = GV_NewActor( 5, 0x6C );
    if ( work )
    {
        GV_SetNamedActor( work, (void *)rank_800D0820, (void *)rank_800D090C, rank_dword_800E07DC );

        if ( rank_800D0D24( work, a1 ) < 0 )
        {
            GV_DestroyActor( work );
            return 0;
        }
    }

    return work;
}
