#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"
#include "pocket.h"

/* Same as in onoda/rank/rank.c, though size is different */
typedef struct _TEXT
{
    /* 0x00 */ SPRT  sprt[ 2 ];          /* per GV_Clock */
    /* 0x28 */ SPRT  outline[ 2 ][ 4 ];  /* sprt shifted by small offsets, per GV_Clock */
    /* 0xC8 */ char *string;             /* pending string, rendered then cleared */
    /* 0xCC */ short visible;
    /* 0xCE */ short unused;
    /* 0xD0 */ short x;
    /* 0xD2 */ short y;
    /* 0xD4 */ short w;
    /* 0xD6 */ short h;
    /* 0xD8 */ short font_x;
    /* 0xDA */ short font_y;
    /* 0xDC */ short clut_x;
    /* 0xDE */ short clut_y;
} TEXT;

#define PKT_MAX_TEXTS 24

typedef struct PKT_FONT
{
    /* 0x0000 */ int      font_x;
    /* 0x0004 */ int      font_y;
    /* 0x0008 */ int      clut_x;
    /* 0x000C */ int      clut_y;
    /* 0x0010 */ KCB      kcb[ PKT_MAX_TEXTS ];
    /* 0x0430 */ int      n_texts;
    /* 0x0434 */ TEXT     text[ PKT_MAX_TEXTS ];
    /* 0x1934 */ DR_TPAGE tpage[ 3 ];
} PKT_FONT;

typedef struct _Work
{
    /* 0x0000 */ GV_ACT      actor;
    /* 0x0020 */ int         time;
    /* 0x0024 */ int         state;
    /* 0x0028 */ int         field_28;
    /* 0x002C */ int         field_2C;
    /* 0x0030 */ PKT_FONT    font;
    /* 0x197C */ char        pad197C[ 0x14 ];
    /* 0x1990 */ DG_PRIM    *prim_ft4;
    /* 0x1994 */ DG_PRIM    *prim_gt4;
    /* 0x1998 */ int         n_requests;
    /* 0x199C */ PKT_REQUEST requests[ PKT_MAX_REQUESTS ];
    /* 0x19BC */ GV_PAD     *pad;
    /* 0x19C0 */ u_int       flags;
    /* 0x19C4 */ int         field_19C4;
    /* 0x19C8 */ int         procs[ 4 ];
    /* 0x19D8 */ int         exit_proc;  /* not set by this file */
    /* 0x19DC */ char        pad19DC[ 0x18 ];
    /* 0x19F4 */ int         field_19F4;
    /* 0x19F8 */ int         field_19F8; /* GCL option 'f' */
    /* 0x19FC */ int         field_19FC;
} Work;

extern MenuPrim      rank_dword_800E1978;
extern Menu_Triangle rank_dword_800CB454;
extern TextConfig    rank_dword_800E1998;
extern PKT_JOB      *rank_dword_800E59F4; /* job list */

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0E4C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D0ECC.s")

void rank_800D11EC( void )
{
    menu_draw_triangle( &rank_dword_800E1978, &rank_dword_800CB454 );
}

void rank_800D1218( int x, int y, int flags )
{
    TextConfig *config;

    config = &rank_dword_800E1998;
    config->xpos = x;
    config->ypos = y;
    config->flags = flags;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1230.s")

void rank_800D128C( int r, int g, int b, int a3 )
{
    TextConfig *config;
    int         packed;
    int         code;

    config = &rank_dword_800E1998;

    if ( a3 == 0 )
    {
        packed = r | ( g << 8 ) | ( b << 16 );
        code = 0x64000000;
    }
    else
    {
        packed = r | ( g << 8 ) | ( b << 16 );
        code = 0x2C000000;
    }

    config->color = packed | code;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D12D0.s")

void rank_800D1380( void )
{
    MenuPrim *prim;

    prim = &rank_dword_800E1978;
    prim->ot = DG_Chanl( 1 )->ot[ GV_Clock ];
    prim->next = prim->buf[ GV_Clock ];
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D13B8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D152C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1670.s")

void rank_800D1988( PKT_FONT *font, int index, int color )
{
    KCB *kcb;

    kcb = &font->kcb[ index ];
    font_set_color( kcb, 0, color, 0 );
    font_clut_update( kcb );
}

void *rank_800D19D8( KCB *kcb )
{
    return kcb->cbuffer;
}

void rank_800D19E4( PKT_FONT *font )
{
    int i;

    for ( i = 0; i < font->n_texts; i++ )
    {
        rank_800D1988( font, i, 0 );
    }
}

void rank_800D1A40( Work *work, int index )
{
    rank_800D1988( &work->font, index, 0x6739 );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1A64.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1AF4.s")
PKT_JOB *rank_800D1AF4( int id );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1B78.s")

void *rank_800D1C10( int count, int flag )
{
    int size;

    size = sizeof( POLY_GT4 );
    if ( flag == 0 )
    {
        size = sizeof( POLY_FT4 );
    }

    return GV_Malloc( count * size );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1C44.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D1E00.s")
void rank_800D1FC0( Work *work, int id, int state )
{
    if ( work->n_requests != PKT_MAX_REQUESTS )
    {
        work->requests[ work->n_requests ].id = id;
        work->requests[ work->n_requests ].state = state;
        work->n_requests++;
    }
}

void rank_800D2004( Work *work )
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
            for ( job = rank_dword_800E59F4; job; job = job->next )
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

PKT_JOB *rank_800D20B0( int id, int count, int flag, int a3 )
{
    PKT_JOB *job;
    void    *buf;

    job = rank_800D1AF4( id );
    if ( !job )
    {
        return 0;
    }

    job->n_prims = count;
    job->gouraud = flag;
    job->field_1C = a3;

    if ( count > 0 )
    {
        buf = rank_800D1C10( count, flag );
        if ( !buf )
        {
            return 0;
        }

        job->prims = buf;
    }

    job->id = id;
    return job;
}

PKT_JOB *rank_800D2144( int id )
{
    PKT_JOB *job;

    for ( job = rank_dword_800E59F4; job; job = job->next )
    {
        if ( job->id == id )
        {
            return job;
        }
    }

    return 0;
}

void rank_800D2188( int id, int mask )
{
    rank_800D2144( id )->flags |= mask;
}

/* Set the color of a POLY_FT4, keeping its semi-transparency bit */
void rank_800D21BC( POLY_FT4 *poly, unsigned int color )
{
    unsigned int code;

    code = poly->code;
    code &= 2;
    code |= 0x2C;
    code <<= 24;
    color |= code;
    LSTORE( color, &poly->r0 );
}

void rank_800D21DC( Work *work )
{
    long argv[ 1 ];

    argv[ 0 ] = 0;
    rank_800D2078( work->exit_proc, argv, 1 );
    GV_DestroyActor( work );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2218.s")

void rank_800D23F0( void )
{
    /* do nothing */
}

void rank_800D23F8( Work *work )
{
    if ( work->state == 0 )
    {
        rank_800D2188( 0, 4 );
    }
}

void rank_800D2428( Work *work )
{
    if ( work->state == 0 )
    {
        rank_800D2188( 0, 1 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2458.s")

void rank_800D2544( Work *work )
{
    if ( work->state == 0 )
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
    PKT_JOB *job;

    job = rank_800D2144( 1 );
    job->field_13 = 1;
    job->field_1C = arg0;
}

void rank_800D2864( void )
{
    PKT_JOB *job;

    job = rank_800D2144( 1 );
    job->field_13 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D2888.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D28D4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3678.s")

void rank_800D369C( Work *work )
{
    int time;
    int state;

    time = work->time;
    state = work->state;

    if ( time <= 999999 )
    {
        work->time = time + 1;
    }

    if ( state == 0 && time == 0 )
    {
        rank_800D1FC0( work, 0, 1 );
        rank_800D1FC0( work, 1, 1 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3708.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D38D8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3A28.s")

void rank_800D3B04( Work *work )
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

void rank_800D28D4( void *work, PKT_JOB *job );

int rank_800D3C44( Work *work )
{
    PKT_JOB *job;

    job = rank_800D20B0( 0, 4, 0, 2 );
    if ( !job )
    {
        return -1;
    }

    job->func = rank_800D28D4;
    work->field_28 = -1;
    work->field_2C = 0;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3CA4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3E18.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D3F94.s")
int  rank_800D3F94( Work *work, int map );
void rank_800D38D8( Work *work );
void rank_800D3A28( Work *work );

extern int        rank_dword_800E59F0;
extern const char rank_dword_800E098C[];

void *rank_800D4084( int a0, int a1 )
{
    Work *work;

    rank_dword_800E59F0 = 0;
    GM_GameStatus |= STATE_ALL_OFF;
    rank_dword_800E59F4 = 0;

    work = GV_NewActor( 6, sizeof( Work ) );
    if ( work )
    {
        GV_SetNamedActor( work, rank_800D38D8, rank_800D3A28, rank_dword_800E098C );

        if ( rank_800D3F94( work, a1 ) < 0 )
        {
            GV_DestroyActor( work );
            return 0;
        }
    }

    return work;
}
