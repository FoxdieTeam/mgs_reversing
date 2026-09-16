#include "game/game.h"
#include "libgcl/libgcl.h"

extern int rank_dword_800E1974;

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE0C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE90.s")

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
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF11C.s")
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

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF1F4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF288.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CF2F0.s")

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
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D090C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D09AC.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0A24.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0A70.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0ABC.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0B08.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0B54.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0BC0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0D24.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0DA0.s")
