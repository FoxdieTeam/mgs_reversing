#define __LIBDG_CHANL_C__

#include "libdg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>
#include "common.h"

static DG_CHANLFUNC DG_ChanlUnits[] = {
    DG_ScreenChanl,
    DG_BoundChanl,
    DG_TransChanl,
    DG_ShadeChanl,
    DG_PrimChanl,
    DG_DivideChanl,
    DG_SortChanl
};

static int stop_chanl_system_flag = FALSE;
static int SECTION(".sbss") unused;
static int SECTION(".sbss") chanl_shift;

static CVECTOR SECTION(".sbss") bg_color;

short SECTION(".sbss") N_ChanlPerfMax;
short SECTION(".sbss") DG_EndTime;
short SECTION(".sbss") DG_StartTime;

extern DG_CHANL DG_Chanls[ 3 ];

extern u_long ot_background[ 68 ];
extern u_long ot_primitive[ 516 ];
extern u_long ot_overlay[ 4 ];

extern void *obj_queue_background[ 8 ];
extern void *obj_queue_primitive[ 256 ];

extern DR_ENV bg_drawenv[ 2 ];

extern u_long *DG_DivideBuffer[ 256 ];
extern u_short DG_ChanlTime[ 32 ];

static void EndFrame( void )
{
    DG_EndTime = GetRCnt( RCntCNT1 );
}

static void SetParam( DG_CHANL *cp, u_long *ot, int ot_size, void **queue, short queue_size, short link, short dblbuf )
{
    int size;

    size = ( 1 << ot_size ) + 1;

    cp->ot[ 0 ] = ot;
    cp->ot[ 1 ] = &ot[ size ];
    cp->objs_index = 0;
    cp->queue = (DG_OBJS **)queue;
    cp->ot_size = ot_size;
    cp->dirty = 0;
    cp->prim_index = queue_size;
    cp->queue_size = queue_size;
    cp->link = link;
    cp->dblbuf = dblbuf;
}

static void CopyDrawEnv( DG_CHANL *cp, DRAWENV *envp, int isbg )
{
    int shift;
    DRAWENV env;

    env = *envp;
    shift = cp->dblbuf ? chanl_shift : 0;

    cp->new_clip_rect.x = env.clip.x - env.ofs[ 0 ];
    cp->new_clip_rect.y = env.clip.y - env.ofs[ 1 ];
    cp->new_clip_rect.w = env.clip.w;
    cp->new_clip_rect.h = env.clip.h;
    SetDrawEnv( cp->new_env, &env );

    env.clip.x += shift;
    env.ofs[ 0 ] += shift;
    SetDrawEnv( &cp->new_env[ 1 ], &env );

    if ( isbg )
    {
        env.isbg = 0;
        SetDrawEnv( &bg_drawenv[ 1 ], &env );

        env.clip.x -= shift;
        env.ofs[ 0 ] -= shift;
        SetDrawEnv( &bg_drawenv[ 0 ], &env );
    }
}

static void FlushDrawEnv( DG_CHANL *cp, int which )
{
    cp->clip_rect = cp->new_clip_rect;
    cp->env1[ which ] = cp->new_env[ which ];
}

/*---------------------------------------------------------------------------*/

void DG_InitChanlSystem( int shift )
{
    DG_CHANL *cp;
    DRAWENV env;

    DrawSyncCallback( EndFrame );
    chanl_shift = shift;

    /* channel 0 */
    cp = DG_Chanls;
    SetParam( cp, ot_background, 5, obj_queue_background, 8, -1, 1 );
    DG_SetDefDrawEnv( &env, 0, 0, FRAME_WIDTH, FRAME_HEIGHT );
    env.isbg = 1;
    CopyDrawEnv( cp, &env, 1 );
    FlushDrawEnv( cp, 0 );
    FlushDrawEnv( cp, 1 );

    /* channel 1 */
    cp++;
    SetParam( cp, ot_primitive, 8, obj_queue_primitive, 256, 16, 1 );
    DG_SetDefDrawEnv( &env, 0, 0, FRAME_WIDTH, FRAME_HEIGHT );
    env.ofs[ 0 ] = 160;
    env.ofs[ 1 ] = 112;
    CopyDrawEnv( cp, &env, 0 );
    FlushDrawEnv( cp, 0 );
    FlushDrawEnv( cp, 1 );
    cp->env2[ 0 ] = bg_drawenv[ 0 ];
    cp->env2[ 1 ] = bg_drawenv[ 1 ];

    /* channel 2 */
    cp++;
    SetParam( cp, ot_overlay, 0, NULL, 0, 8, 1 );
    DG_SetDefDrawEnv( &env, 0, 0, FRAME_WIDTH, FRAME_HEIGHT );
    CopyDrawEnv( cp, &env, 0 );
    FlushDrawEnv( cp, 0 );
    FlushDrawEnv( cp, 1 );
    cp->env2[ 0 ] = bg_drawenv[ 0 ];
    cp->env2[ 1 ] = bg_drawenv[ 1 ];
}

void DG_DrawChanlSystem( int which )
{
    DG_ChanlTime[ 0 ] = DG_StartTime;
    DG_StartTime = GetRCnt( RCntCNT1 );

    /* channels 1 and 2 are linked into channel 0 */
    DrawOTag( &DG_Chanls[ 0 ].env1[ which ].tag );
}

void DG_ClearChanlSystem( int which )
{
    int i, size;
    DG_CHANL *cp;
    u_long *ot, *ot_end, *chain;
    DR_ENV *env1, *env2;

    cp = DG_Chanls;

    for ( i = 3 ; i > 0; i-- )
    {
        size = ( 1 << cp->ot_size ) + 1;

        ot = cp->ot[ which ];
        ot_end = &ot[ size - 1 ];

        /* the ot is in reverse order */
        ClearOTagR( ot, size );

        if ( cp->dirty > 0 )
        {
            FlushDrawEnv( cp, which );
            cp->dirty--;
        }

        env1 = &cp->env1[ which ];
        env2 = &cp->env2[ which ];

        /* execute the channel in the order env1 -> ot -> env2 */
        catPrim( env1, ot_end );
        catPrim( ot, env2 );

        if ( cp->link >= 0 )
        {
            /* link this channel into the background channel */
            chain = DG_Chanls[ 0 ].ot[ which ];
            chain += cp->link;
            addPrims( chain, env1, env2 );
        }
        else
        {
            termPrim( env2 );
        }

        cp++;
    }
}

void DG_SortChanlSystem( int which )
{
    int i, num;
    u_short *time;
    DG_CHANLFUNC *func;

    time = &DG_ChanlTime[ 1 ];

    if ( stop_chanl_system_flag )
    {
        // Store the counter and set as 2 valid items
        *time = GetRCnt( RCntCNT1 );
        N_ChanlPerfMax = 2;
    }
    else
    {
        GV_ZeroMemory( DG_DivideBuffer, sizeof(DG_DivideBuffer) );
        func = DG_ChanlUnits;

        if ( !DG_HikituriFlag )
        {
            /* run all channels */
            num = 7;
        }
        else
        {
            /* run screen channel */
            num = 1;
        }

        for ( i = num; i > 0; i-- )
        {
            *time++ = GetRCnt( RCntCNT1 );
            ( *func )( &DG_Chanls[ 1 ], which );
            func++;
        }

        *time++ = GetRCnt( RCntCNT1 );
        N_ChanlPerfMax = time - DG_ChanlTime;
    }
}

void DG_SetDrawEnv( int chanl, DRAWENV *env )
{
    DG_CHANL *cp;

    cp = &DG_Chanls[ chanl + 1 ];
    CopyDrawEnv( cp, env, 0 );
    cp->dirty = 2;
}

/*---------------------------------------------------------------------------*/

int DG_QueueObjs( DG_OBJS *objs )
{
    int which, n;
    DG_CHANL *cp;

    which = objs->chanl + 1;
    cp = &DG_Chanls[ which ];

    n = cp->objs_index;
    if ( n >= cp->prim_index ) return -1;
    cp->queue[ n++ ] = objs;
    cp->objs_index = n;
    return 0;
}

void DG_DequeueObjs( DG_OBJS *objs )
{
    int which, n, i;
    DG_CHANL *cp;
    void **oque;

    which = objs->chanl + 1;
    cp = &DG_Chanls[ which ];

    oque = (void **)cp->queue;
    n = cp->objs_index;
    for ( i = n; i > 0; i-- )
    {
        if ( *oque == objs ) goto found;
        oque++;
    }
    return;
found:
    for ( --i; i > 0; i-- )
    {
        oque[ 0 ] = oque[ 1 ];
        oque++;
    }
    cp->objs_index = --n;
}

int DG_QueuePrim( DG_PRIM *prim )
{
    int which, n;
    DG_CHANL *cp;

    which = prim->chanl + 1;
    cp = &DG_Chanls[ which ];

    n = cp->prim_index;
    if ( n <= cp->objs_index ) return -1;
    cp->queue[ --n ] = (DG_OBJS *)prim;
    cp->prim_index = n;
    return 0;
}

void DG_DequeuePrim( DG_PRIM *prim )
{
    int which, n, i;
    DG_CHANL *cp;
    void **oque;

    which = prim->chanl + 1;
    cp = &DG_Chanls[ which ];

    n = cp->prim_index;
    oque = (void **)&cp->queue[ cp->queue_size ];
    for ( i = cp->queue_size - n; i > 0; i-- )
    {
        oque--;
        if ( *oque == prim ) goto found;
    }
    return;
found:
    for ( --i; i > 0; i-- )
    {
        oque[ 0 ] = oque[ -1 ];
        oque--;
    }
    cp->prim_index = ++n;
}

/*---------------------------------------------------------------------------*/

void DG_SetDefDrawEnv( DRAWENV *env, int x, int y, int w, int h )
{
    setRECT( &env->clip, x, y, w, h );
    env->ofs[ 0 ] = x;
    env->ofs[ 1 ] = y;
    env->dtd = 1;
    env->dfe = 0;
    setRECT( &env->tw, 0, 0, 0, 0 );
    setRGB0( env, 0, 0, 0 );
    env->tpage = 0;
    env->isbg = 0;
}

void DG_StopMainChanlSystem( void )
{
    int i;
    DG_CHANL *cp;
    DG_OBJS **queue, *objs;

    cp = &DG_Chanls[ 1 ];
    queue = (DG_OBJS **)cp->queue;

    stop_chanl_system_flag = TRUE;

    for ( i = cp->objs_index; i > 0; i-- )
    {
        objs = *queue++;
        DG_FreeObjsPacket( objs, 0 );
        DG_FreeObjsPacket( objs, 1 );
    }
}

void DG_RestartMainChanlSystem( void )
{
    stop_chanl_system_flag = FALSE;
    DG_UnDrawFrameCount = 1;
}

/*---------------------------------------------------------------------------*/

static void SetBackgroundColor( int r, int g, int b )
{
    DG_CHANL *cp;
    DRAWENV env;

    cp = DG_Chanls;
    DG_SetDefDrawEnv( &env, 0, 0, FRAME_WIDTH, FRAME_HEIGHT );
    env.isbg = 1;
    setRGB0( &env, r, g, b );
    CopyDrawEnv( cp, &env, 1 );
    cp->dirty = 2;
}

void DG_SetBackGroundColor( int r, int g, int b )
{
    bg_color.r = r;
    bg_color.b = b;
    bg_color.g = g;
    SetBackgroundColor( r, g, b );
}

void DG_BackGroundBlack( void )
{
    SetBackgroundColor( 0, 0, 0 );
}

void DG_BackGroundNormal( void )
{
    SetBackgroundColor( bg_color.r, bg_color.g, bg_color.b);
}

void DG_SetBackgroundPrim( void *prim )
{
    P_TAG *tag;

    tag = (P_TAG *)prim;
    setRGB0( tag, bg_color.r, bg_color.g, bg_color.b );
}

/*---------------------------------------------------------------------------*/

DG_CHANLFUNC DG_SetChanlSystemUnits( int num, DG_CHANLFUNC addr )
{
    DG_CHANLFUNC old_addr;

    old_addr = DG_ChanlUnits[ num ];
    DG_ChanlUnits[ num ] = addr;
    return old_addr;
}
