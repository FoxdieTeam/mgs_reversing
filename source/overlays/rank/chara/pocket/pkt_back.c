#include "game/game.h"
#include "libgcl/libgcl.h"
#include "pocket.h"

typedef struct _Work
{
    /* 0x00 */ GV_ACT      actor;
    /* 0x20 */ int         time;
    /* 0x24 */ int         state;
    /* 0x28 */ int         field_28;
    /* 0x2C */ DG_PRIM    *prim_ft4;
    /* 0x30 */ DG_PRIM    *prim_gt4;
    /* 0x34 */ int         n_requests;
    /* 0x38 */ PKT_REQUEST requests[ PKT_MAX_REQUESTS ];
    /* 0x58 */ GV_PAD     *pad;
    /* 0x5C */ u_int       flags;
    /* 0x60 */ int         field_60;
    /* 0x64 */ int         procs[ 1 ];
    /* 0x68 */ int         field_68;
} Work;

extern int         rank_dword_800E1970; /* number of jobs */
extern PKT_JOB    *rank_dword_800E1974; /* job list */
extern const char  rank_dword_800E07DC[];

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE0C.s")
PKT_JOB *rank_800CEE0C( void );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEE90.s")
void rank_800CEE90( PKT_JOB *job );

void *rank_800CEF28( int count, int flag )
{
    int size;

    size = sizeof( POLY_GT4 );
    if ( flag == 0 )
    {
        size = sizeof( POLY_FT4 );
    }

    return GV_Malloc( count * size );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CEF5C.s")
void rank_800CF11C( Work *work, int id, int state )
{
    if ( work->n_requests != PKT_MAX_REQUESTS )
    {
        work->requests[ work->n_requests ].id = id;
        work->requests[ work->n_requests ].state = state;
        work->n_requests++;
    }
}

void rank_800CF160( Work *work )
{
    PKT_REQUEST *request;
    PKT_JOB     *job;
    int          i;

    request = work->requests;
    i = 0;
    if ( work->n_requests > 0 )
    {
        do
        {
            for ( job = rank_dword_800E1974; job; job = job->next )
            {
                if ( job->id == request->id )
                {
                    job->state = request->state;
                    break;
                }
            }
            request++;
        } while ( work->n_requests > ++i );
    }
    work->n_requests = 0;
}

void rank_800CF1D4( PKT_JOB *job )
{
    job->field_13 = 0;
    job->state = 0;
    job->time2 = 0;
    job->time = 0;
    job->field_18 = 0;
    job->field_14 = 0;
    job->flags = 0;
}

PKT_JOB *rank_800CF1F4( int id, int count, int flag, int a3 )
{
    PKT_JOB *job;
    void    *buf;

    job = rank_800CEE0C();
    if ( !job )
    {
        return 0;
    }

    job->n_prims = count;
    job->gouraud = flag;
    job->field_1C = a3;

    if ( count > 0 )
    {
        buf = rank_800CEF28( count, flag );
        if ( !buf )
        {
            return 0;
        }

        job->prims = buf;
    }

    job->id = id;
    return job;
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

/* Change the semi-transparency rate of a poly's tpage */
void rank_800CF2F0( POLY_FT4 *poly, int abr )
{
    int            tpage;
    unsigned short tpage2;

    tpage = tpage2 = poly->tpage;
    poly->tpage = ( tpage & 0x180 ) | ( ( abr & 3 ) << 5 ) | ( poly->tpage & 0x10 ) | ( poly->tpage & 0xF ) | ( tpage & 0x800 );
}

PKT_JOB *rank_800CF328( int id )
{
    PKT_JOB *job;

    for ( job = rank_dword_800E1974; job; job = job->next )
    {
        if ( job->id == id )
        {
            return job;
        }
    }

    return 0;
}

void rank_800CF36C( int id, int mask )
{
    rank_800CF328( id )->flags &= ~mask;
}

void rank_800CF3A0( int id )
{
    rank_800CF1D4( rank_800CF328( id ) );
}

void rank_800CF3C8( Work *work )
{
    GCL_ExecProc( work->procs[ 0 ], NULL );
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

void rank_800D090C( Work *work )
{
    DG_PRIM *prim;

    if ( rank_dword_800E1970 > 0 )
    {
        do
        {
            rank_800CEE90( rank_dword_800E1974 );
        } while ( rank_dword_800E1970 > 0 );
    }

    prim = work->prim_ft4;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }

    prim = work->prim_gt4;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }
}

void rank_800D09AC( Work *work )
{
    int   i;
    char *str;
    int  *dst;

    if ( GCL_GetOption( 'p' ) )
    {
        i = 0;
        dst = work->procs;

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
int rank_800D0A24( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0A70.s")
int rank_800D0A70( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0ABC.s")
int rank_800D0ABC( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0B08.s")
int rank_800D0B08( Work *work );

int rank_800D0B54( Work *work )
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
int  rank_800D0BC0( Work *work );
void rank_800D0820( Work *work );

int rank_800D0D24( Work *work, int map )
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

    work->pad = &GV_PadData[ 2 ];
    work->state = 0;
    work->flags |= 0x100000;
    rank_800D0820( work );
    return 0;
}

void *rank_800D0DA0( int a0, int a1 )
{
    Work *work;

    rank_dword_800E1970 = 0;
    GM_GameStatus |= STATE_ALL_OFF;
    rank_dword_800E1974 = 0;

    work = GV_NewActor( 5, sizeof( Work ) );
    if ( work )
    {
        GV_SetNamedActor( work, rank_800D0820, rank_800D090C, rank_dword_800E07DC );

        if ( rank_800D0D24( work, a1 ) < 0 )
        {
            GV_DestroyActor( work );
            return 0;
        }
    }

    return work;
}
