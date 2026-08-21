#define __LIBDG_DISPLAY_C__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg.h"
#include "common.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"

/*** data ***/
STATIC VECTOR SECTION(".data") Lower = {0, -4096, 0, 0};

/*** $gp ***/
int DG_UnDrawFrameCount = 0;
STATIC int DG_LastWhich = -1;

STATIC int SECTION(".sbss") gClipHeights_800AB960[2];
int   SECTION(".sbss") DG_CurrentGroupID;
short SECTION(".sbss") DG_ClipMin[2];
short SECTION(".sbss") DG_ClipMax[2];

/*** bss ***/
extern DISPENV g_dispenv;
extern VECTOR  prev_vx;

void DG_InitDisplay( int x, int y, int w, int h, int shift )
{
    DISPENV *env;
    RECT *disp, *screen;

    env = &g_dispenv;
    disp = &env->disp;
    screen = &env->screen;

    setRECT( disp, x, y, w, h );
    setRECT( screen, 0, 0, 256, SCREEN_HEIGHT );
    env->isinter = 0;
    env->isrgb24 = 0;
    env->screen.y = 8;
    env->screen.h = FRAME_HEIGHT;

    gClipHeights_800AB960[ 0 ] = x;
    gClipHeights_800AB960[ 1 ] = x + shift;
}

void DG_ChangeReso( int flag )
{
#if 0
    DRAWENV env;

    if ( flag & 1 )
    {
        g_dispenv.disp.w = 384;
        g_dispenv.screen.x = 26;
        g_dispenv.screen.w = 212;
    }
    else
    {
        g_dispenv.disp.w = 320;
        g_dispenv.screen.x = 0;
        g_dispenv.screen.w = 255;
    }

    if ( flag & 2 )
    {
        g_dispenv.screen.h = 224;
    }
    else
    {
        g_dispenv.screen.h = 256;
    }

    g_dispenv.screen.y = 16;

    if ( flag & 4 )
    {
        g_dispenv.disp.h = 224;
        g_dispenv.disp.y = ( g_dispenv.screen.h - 224 ) / 2;
    }
    else
    {
        g_dispenv.disp.y = 0;
        g_dispenv.disp.h = 256;
    }

    if ( flag & 8 )
    {
        PutDispEnv( &g_dispenv );
    }

    SetDefDrawEnv( &env, 0, 0, 320, g_dispenv.disp.h );
    env.isbg = 1;
    DG_SetDrawEnv( -1, &env );
#endif
}

void DG_InitFrameSystem( void )
{
    DG_ClearChanlSystem( 0 );
    DG_ClearChanlSystem( 1 );
    DG_SortChanlSystem( 0 );
    DG_SortChanlSystem( 1 );
}

void DG_StartFrame( void )
{
    int which;
    
    which = GV_Clock;

    if ( ( GV_PauseLevel & GV_PAUSE_READERROR ) || DG_UnDrawFrameCount > 0 )
    {
        if ( DG_LastWhich < 0 ) DG_LastWhich = which;
        if ( !( GV_PauseLevel & GV_PAUSE_READERROR ) ) DG_UnDrawFrameCount--;
    }
    else
    {
        if ( DG_LastWhich < 0 || which != DG_LastWhich )
        {
            g_dispenv.disp.x = gClipHeights_800AB960[ which ];
            PutDispEnv( &g_dispenv );

            if ( !DG_HikituriFlagOld ) DG_DrawChanlSystem( 1 - which );
            DG_LastWhich = -1;
        }
    }

    GV_ClearMemorySystem( which );
    if ( !DG_HikituriFlagOld ) GV_ClearMemorySystem(GV_NORMAL_MEMORY);

    MENU_ResetSystem();

    DG_ClearChanlSystem( which );
    DG_ClearTmpLight();
}

void DG_EndFrame( void )
{
    DG_SortChanlSystem( GV_Clock );
}

void DG_MakeCameraMatrix( DG_CHANL *chanl, SVECTOR *from, SVECTOR *to, int screen )
{
    VECTOR z_vec, y_vec, x_vec;
    MATRIX *mat, *mat2;

    chanl->screen = screen;

    mat = &chanl->eye;
    mat->t[ 0 ] = from->vx;
    mat->t[ 1 ] = from->vy;
    mat->t[ 2 ] = from->vz;

    z_vec.vx = (short)( to->vx - from->vx );
    z_vec.vy = (short)( to->vy - from->vy );
    z_vec.vz = (short)( to->vz - from->vz );
    OuterProduct12( &Lower, &z_vec, &x_vec );
    if ( x_vec.vx == 0 && x_vec.vy == 0 && x_vec.vz == 0 )
    {
        x_vec = prev_vx;
    }
    else
    {
        prev_vx = x_vec;
    }

    VectorNormal( &x_vec, &x_vec );
    VectorNormal( &z_vec, &z_vec );
    OuterProduct12( &z_vec, &x_vec, &y_vec );
    mat->m[ 0 ][ 0 ] = x_vec.vx;
    mat->m[ 0 ][ 1 ] = y_vec.vx;
    mat->m[ 0 ][ 2 ] = z_vec.vx;
    mat->m[ 1 ][ 0 ] = x_vec.vy;
    mat->m[ 1 ][ 1 ] = y_vec.vy;
    mat->m[ 1 ][ 2 ] = z_vec.vy;
    mat->m[ 2 ][ 0 ] = x_vec.vz;
    mat->m[ 2 ][ 1 ] = y_vec.vz;
    mat->m[ 2 ][ 2 ] = z_vec.vz;

    mat2 = &chanl->eye_inv;
    DG_TransposeMatrix( mat, mat2 );
    z_vec.vx = -mat->t[ 0 ];
    z_vec.vy = -mat->t[ 1 ];
    z_vec.vz = -mat->t[ 2 ];
    ApplyMatrixLV( mat2, &z_vec, (VECTOR *)mat2->t );
}

void DG_AdjustOverscan( MATRIX *mat )
{
    mat->m[ 1 ][ 0 ] = ( mat->m[ 1 ][ 0 ] * 58 ) / 64;
    mat->m[ 1 ][ 1 ] = ( mat->m[ 1 ][ 1 ] * 58 ) / 64;
    mat->m[ 1 ][ 2 ] = ( mat->m[ 1 ][ 2 ] * 58 ) / 64;
    mat->t[ 1 ] = ( mat->t[ 1 ] * 58 ) / 64;
}

void DG_Clip( RECT *rect, int dist )
{
    int x, y;

    gte_SetGeomScreen( dist );

    x = rect->x;
    DG_ClipMin[ 0 ] = x;
    DG_ClipMax[ 0 ] = x + rect->w - 1;
    y = rect->y;
    DG_ClipMin[ 1 ] = y;
    DG_ClipMax[ 1 ] = y + rect->h - 1;
}

void DG_ApplyMatrix( MATRIX *world, MATRIX *in )
{
    MATRIX out;

    gte_SetRotMatrix( world );

    gte_ldclmv( &in->m[ 0 ][ 0 ] );
    gte_rtir();
    gte_stclmv( &out.m[ 0 ][ 0 ] );

    gte_ldclmv( &in->m[ 0 ][ 1 ] );
    gte_rtir();
    gte_stclmv( &out.m[ 0 ][ 1 ] );

    gte_ldclmv( &in->m[ 0 ][ 2 ] );
    gte_rtir();
    gte_stclmv( &out.m[ 0 ][ 2 ] );

    gte_SetTransMatrix( world );

    gte_ldlv0( in->t );
    gte_rt();
    gte_stlvnl( out.t );

    DG_AdjustOverscan( &out );

    gte_SetRotMatrix( &out );
    gte_SetTransMatrix( &out );
}

void DG_OffsetDispEnv( int offset )
{
    g_dispenv.screen.y += offset;
    g_dispenv.screen.h -= offset;
    PutDispEnv( &g_dispenv );
    g_dispenv.screen.y -= offset;
    g_dispenv.screen.h += offset;
}

void DG_ClipDispEnv( int x, int y )
{
    RECT old;

    old = g_dispenv.screen;

    g_dispenv.screen.x = 128 - x / 2;
    g_dispenv.screen.w = x;
    g_dispenv.screen.y = 120 - y / 2;
    g_dispenv.screen.h = y;
    PutDispEnv( &g_dispenv );

    g_dispenv.screen = old;
}

void DG_DisableClipping( void )
{
    DRAWENV env;

    DG_SetDefDrawEnv( &env, g_dispenv.disp.x, g_dispenv.disp.y, g_dispenv.disp.w, g_dispenv.disp.h );
    PutDrawEnv( &env );
}

void DG_FadeScreen( int amount )
{
    DR_TPAGE tpage;
    TILE tile;

    DG_DisableClipping();

    setDrawTPage( &tpage, 1, 1, GetTPage( 0, 2, 0, 0 ) );
    DrawPrim( &tpage );

    tile.x0 = 0;
    tile.y0 = 0;
    tile.w = FRAME_WIDTH;
    tile.h = FRAME_HEIGHT;
    LSTORE( amount << 16 | amount << 8 | amount, &tile.r0 );
    setTile( &tile);
    setSemiTrans( &tile, 1 );
    DrawPrim( &tile );
}

DISPENV *DG_GetDisplayEnv( void )
{
    return &g_dispenv;
}
