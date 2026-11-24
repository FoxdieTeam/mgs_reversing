#include "ed_telop.h"

#include "game/game.h"
#include "menu/menuman.h"
#include "takabe/thing.h"

typedef struct _Work {
    GV_ACT actor;
    int    name;
    int    state;
    int    line_count;
    int    time;
    int    fade_time;
    int    display_time;
    int    text;
    int   *data;
    void  *line;
    int    proc;
} Work;

typedef struct _EdTelopPrims {
    DR_TPAGE tpage[2];
    SPRT     sprt[2];
} EdTelopPrims;

static RECT line_rect = {0, 256, 320, 1};
static RECT screen_rect = {0, 256, 320, 160};

static u_short mes_list[] = {0x29B9};

static EdTelopPrims telop_prims[2];
static u_long line_data[160];

char *uncompress_rle( void *, char *, int );
void uncompress_indexed( short *, void *, void *, int );

int NewJimakuDisplay( void )
{
    char *str;
    int time;

    if ( GCL_GetOption( 's' ) == NULL ) return 1;
    str = GCL_GetString( GCL_NextStr() );

    if ( GCL_GetOption( 't' ) )
    {
        time = GCL_GetNextInt();
        MENU_JimakuWrite( str, time );
    }

    return 1;
}

static void ClearLineBuffer( void )
{
    u_long *data;
    int i;

    data = line_data;
    for ( i = 160; i > 0; i -= 4 )
    {
        data[ 3 ] = 0;
        data[ 2 ] = 0;
        data[ 1 ] = 0;
        data[ 0 ] = 0;
        data += 4;
    }
}

static void *ReadLine( short *data, int arg1 )
{
    RECT rect;
    char *ptr;
    int x, y, off, i;
    void *scratch;

    ClearImage( &screen_rect, 0, 0, 0 );

    ptr = (char *)(data + 20);

    ClearLineBuffer();

    x = data[0];
    y = data[1];

    rect = line_rect;

    off = (320 - x) / 2;
    rect.y += (160 - y) / 2;

    scratch = (void *)SCRPAD_ADDR;

    for (i = data[1]; i > 0; i--)
    {
        if (!(*ptr & 0x40))
        {
            ptr = uncompress_rle(scratch, ptr, data[0] / 2);
            uncompress_indexed((short *)line_data + off, scratch, data + 2, data[0]);

            DrawSync(0);
            LoadImage2(&rect, line_data);
        }
        else
        {
            ptr++;
        }

        rect.y++;
    }

    return (char *)data + 40 + *(int *)(data + 18);
}

static void InitPrims( SPRT *sprt, DR_TPAGE *tpage, u_long *ot, int color )
{
    setSprt( sprt );
    setRGB0( sprt, color, color, color );
    setXY0( sprt, 0, 24 );
    setUV0( sprt, 0, 0 );
    setWH( sprt, 256, 160 );
    addPrim( ot, sprt );
    addPrim( ot, tpage );

    tpage++;
    sprt++;

    setSprt( sprt );
    setRGB0( sprt, color, color, color );
    setXY0( sprt, 256, 24 );
    setUV0( sprt, 0, 0 );
    setWH( sprt, 64, 160 );
    addPrim( ot, sprt );
    addPrim( ot, tpage );
}

static void Act( Work *work )
{
    EdTelopPrims *prims;
    DR_TPAGE *tpage;
    SPRT *sprt;
    u_long *ot;
    int end;

    prims = &telop_prims[ GV_Clock ];
    ot = DG_ChanlOTag(1);
    sprt = prims->sprt;
    tpage = prims->tpage;

    end = 0;

    switch ( work->state )
    {
    case 0: /* setup */
        work->line = ReadLine( work->line, 0 );
        work->state = 1;
        work->time = work->fade_time;
        break;
    case 1: /* fade_time in */
        InitPrims( sprt, tpage, ot, 192 - ( --work->time * 192 ) / work->fade_time );

        if ( work->time <= 0 )
        {
            work->state = 2;
            work->time = work->display_time;
        }
        break;
    case 2:
        work->time--;
        InitPrims( sprt, tpage, ot, 192 );

        if ( work->time <= 0 && work->display_time != -1 )
        {
            end = 1;
        }

        switch ( THING_Msg_CheckMessage( work->name, 1, mes_list ) )
        {
        case 0:
            end = 1;
            break;
        case 1:
            break;
        }

        if ( end != 0 )
        {
            work->state = 3;
            work->time = work->fade_time;
        }
        break;
    case 3: /* fade_time out */
        InitPrims( sprt, tpage, ot, ( --work->time * 192 ) / work->fade_time );

        if ( work->time <= 0 )
        {
            if ( ++work->line_count >= *work->data )
            {
                work->state = -1;
            }
            else
            {
                work->state = 4;
                work->time = 15;
            }
        }
        break;
    case 4: /* delay */
        if ( --work->time <= 0 )
        {
            work->state = 0;
        }
        break;
    case -1: /* end */
        ClearImage( &screen_rect, 0, 0, 0 );
        GV_DestroyActor( &work->actor );
        break;
    }
}

static void Die( Work *work )
{
    if ( work->proc != 0 )
    {
        GCL_ExecProc( work->proc, NULL );
    }
}

static void GetResources( Work *work )
{
    char *data;
    int tp0, tp1, i;

    ClearImage( &screen_rect, 0, 0, 0 );

    GM_GameStatus |= ( STATE_PADRELEASE | STATE_PAUSE_ONLY );
    DG_UnDrawFrameCount = 1;

    data = GV_GetCache( GV_CacheID( work->text, 'r' ) );
    work->data = (int *)data;
    work->line = data + 4;

    work->line_count = 0;

    tp0 = getTPage( 2, 0, line_rect.x, line_rect.y );
    tp1 = getTPage( 2, 0, line_rect.x + 256, line_rect.y );

    for ( i = 0; i < 2; i++ )
    {
        setDrawTPage( &telop_prims[ i ].tpage[ 0 ], 0, 0, tp0 );
        setDrawTPage( &telop_prims[ i ].tpage[ 1 ], 0, 0, tp1 );
    }
}

void *NewEndingTelop( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &work->actor, Act, Die, "ed_telop.c" );

        work->name = name;
        work->proc = THING_Gcl_GetInt( 'p' );
        work->fade_time = THING_Gcl_GetIntDefault( 'f', 30 );
        work->display_time = THING_Gcl_GetIntDefault( 'd', 150 );
        work->text = THING_Gcl_GetInt( 't' );

        GetResources( work );
    }

    return (void *)work;
}
