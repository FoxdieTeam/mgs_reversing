/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 雪嵐
 */

/******************************************************************************
 * included
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"
#include "anime/animconv/anime.h"

#include "common.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagSNOWSTORM
{
    GV_ACT      actor;
    int         nName;
    int         nMap;
    SVECTOR     svectMin;
    SVECTOR     svectMax;
    int         nDivisor;
    int         nSStormRaise;
    BOOL        bActive;
    int         nTime;
    SVECTOR     pos;
    ANIMATION   animation;
    char        script[ 80 ];
    PRESCRIPT   preScript;
} SNOWSTORM, *LPSNOWSTORM;

/******************************************************************************
 * locals
 */

static char sstorm_script[] = {
    0x00,0x10,0x01,0x00, 0x05,0x01,0xFE,0x0C,
    0x00,0x00,0x01,0xFF, 0x08,0x00,0x00,0x00,
    0x02,0x00,0x01,0x0D, 0x0F
};

/******************************************************************************
 * functions
 */

static void Act( LPSNOWSTORM lpAct );
static void Die( LPSNOWSTORM lpAct );
static int CheckMessage( u_short name, int n_mes_list, u_short *mes_list );

/******************************************************************************
 * publics
 */

void *NewSnowStorm( int nName, int nMap )
{
    LPSNOWSTORM lpAct;
    SVECTOR pos, rot;
    char *str;

    lpAct = GV_NewActor( GV_ACTOR_USER, sizeof(SNOWSTORM) );
    if ( lpAct == NULL ) return NULL;

    GV_SetNamedActor( &lpAct->actor, Act, Die, "sstorm.c" );

    lpAct->bActive = TRUE;
    lpAct->nDivisor = 4;
    lpAct->nName = nName;
    lpAct->nMap = nMap;
    lpAct->nSStormRaise = 2000;

    if ( GCL_GetOption( 'a' ) )
    {
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMin.vx = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMin.vy = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMin.vz = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMax.vx = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMax.vy = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->svectMax.vz = GCL_StrToInt( str );
    }

    if ( GCL_GetOption( 'e' ) )
    {
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->nDivisor = GCL_StrToInt( str );
        if ( ( str = GCL_NextStr() ) != NULL ) lpAct->nSStormRaise = GCL_StrToInt( str );
    }

    if ( GCL_GetOption( 'p' ) )
    {
        if ( ( str = GCL_NextStr() ) != NULL ) rot.vx = GCL_StrToInt( str ) * 4096 / 360;
        if ( ( str = GCL_NextStr() ) != NULL ) rot.vy = GCL_StrToInt( str ) * 4096 / 360;
        if ( ( str = GCL_NextStr() ) != NULL ) rot.vz = GCL_StrToInt( str ) * 4096 / 360;
        if ( ( str = GCL_NextStr() ) != NULL )
        {
            pos.vx = 0;
            pos.vy = 0;
            pos.vz = 0;
            DG_SetPos2( &pos, &rot );
            pos.vz = GCL_StrToInt( str ) / 3;
            DG_PutVector( &pos, &pos, 1 );
            lpAct->pos.vx = pos.vx;
            lpAct->pos.vy = pos.vy;
            lpAct->pos.vz = pos.vz;
        }
    }

    lpAct->animation.size_w = lpAct->svectMax.vx - lpAct->svectMin.vx;
    lpAct->animation.size_w = MAX( lpAct->animation.size_w, lpAct->svectMax.vy - lpAct->svectMin.vy );
    lpAct->animation.size_w = MAX( lpAct->animation.size_w, lpAct->svectMax.vz - lpAct->svectMin.vz );
    lpAct->animation.texdev_x = 1;
    lpAct->animation.texdev_y = 1;
    lpAct->animation.n_anime = 1;
    lpAct->animation.unit_num = 1;
    lpAct->animation.amb = 3;
    lpAct->animation.v = 255;
    lpAct->animation.pre_script = &lpAct->preScript;
    lpAct->animation.script = lpAct->script;
    lpAct->animation.raise = lpAct->nSStormRaise;
    lpAct->animation.size_h = lpAct->animation.size_w;

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act( LPSNOWSTORM lpAct )
{
    VECTOR pos;
    SVECTOR speed, rot;
    u_short mes_list[ 2 ];
    int length, lo, hi;
    u_int xw;

    GM_CurrentMap = lpAct->nMap;
    lpAct->nTime++;

    mes_list[ 0 ] = GV_StrCode( "run" );
    mes_list[ 1 ] = GV_StrCode( "stop" );

    switch ( CheckMessage( lpAct->nName, 2, mes_list ) )
    {
    case 0:
        lpAct->bActive = TRUE;
        printf( "s-end\n" );
        break;
    case 1:
        lpAct->bActive = FALSE;
        printf( "s-start\n" );
        break;
    }

    if ( lpAct->bActive == FALSE || ( lpAct->nTime % lpAct->nDivisor ) != 0 ) return;

    if ( GM_lpsvectWind == NULL )
    {
        lpAct->preScript.speed = lpAct->pos;
    }
    else
    {
        lpAct->preScript.speed = *GM_lpsvectWind;
    }

    pos.vx = lpAct->svectMin.vx + ( rand() & 255 ) * ( lpAct->svectMax.vx - lpAct->svectMin.vx ) / 256;
    pos.vy = lpAct->svectMin.vy + ( rand() & 255 ) * ( lpAct->svectMax.vy - lpAct->svectMin.vy ) / 256;
    pos.vz = lpAct->svectMin.vz + ( rand() & 255 ) * ( lpAct->svectMax.vz - lpAct->svectMin.vz ) / 256;

    speed = lpAct->preScript.speed;
    speed.vx = ABS( speed.vx );
    speed.vy = ABS( speed.vy );
    speed.vz = ABS( speed.vz );

    if ( speed.vx > speed.vy && speed.vz < speed.vx )
    {
        if ( lpAct->preScript.speed.vx < 0 )
        {
            pos.vx = lpAct->svectMax.vx + lpAct->animation.size_w / 4;
        }
        else
        {
            pos.vx = lpAct->svectMin.vx - lpAct->animation.size_w / 4;
        }
    }
    else if ( speed.vy > speed.vx && speed.vz < speed.vy )
    {
        if ( lpAct->preScript.speed.vy < 0 )
        {
            pos.vy = lpAct->svectMax.vy + lpAct->animation.size_w / 4;
        }
        else
        {
            pos.vy = lpAct->svectMin.vy - lpAct->animation.size_w / 4;
        }
    }
    else
    {
        if ( lpAct->preScript.speed.vz < 0 )
        {
            pos.vz = lpAct->svectMax.vz + lpAct->animation.size_w / 4;
        }
        else
        {
            pos.vz = lpAct->svectMin.vz - lpAct->animation.size_w / 4;
        }
    }

    pos.vx += GM_PlayerPosition.vx;
    pos.vy += GM_PlayerPosition.vy;
    pos.vz += GM_PlayerPosition.vz;

    if ( GM_PlayerStatus & PLAYER_WATCH )
    {
        speed.vx = gUnkCameraStruct2_800B7868.target.vx - gUnkCameraStruct2_800B7868.position.vx;
        speed.vy = gUnkCameraStruct2_800B7868.target.vy - gUnkCameraStruct2_800B7868.position.vy;
        speed.vz = gUnkCameraStruct2_800B7868.target.vz - gUnkCameraStruct2_800B7868.position.vz;

        rot.vx = -ratan2( speed.vy, SquareRoot0( speed.vx * speed.vx + speed.vz * speed.vz ) );
        rot.vy = ratan2( speed.vx, speed.vz );
        rot.vz = 0;

        memset( &speed, 0, sizeof(SVECTOR) );
        DG_SetPos2( &speed, &rot );

        speed.vz = lpAct->animation.size_w * 2 / 3;
        DG_PutVector( &speed, &speed, 1 );

        pos.vx += speed.vx;
        pos.vy += speed.vy;
        pos.vz += speed.vz;
    }

    pos.vx = MIN( pos.vx, 32000 );
    pos.vx = MAX( pos.vx, -32000 );
    pos.vy = MIN( pos.vy, 32000 );
    pos.vy = MAX( pos.vy, -32000 );
    pos.vz = MIN( pos.vz, 32000 );
    pos.vz = MAX( pos.vz, -32000 );

    lpAct->preScript.pos.vx = pos.vx;
    lpAct->preScript.pos.vy = pos.vy;
    lpAct->preScript.pos.vz = pos.vz;

    length = SquareRoot0( lpAct->preScript.speed.vx * lpAct->preScript.speed.vx +
                          lpAct->preScript.speed.vy * lpAct->preScript.speed.vy +
                          lpAct->preScript.speed.vz * lpAct->preScript.speed.vz );

    memcpy( lpAct->script, sstorm_script, sizeof(sstorm_script) );
    xw = lpAct->animation.size_w / length + 1;
    lo = xw >> 8;
    hi = ( xw & 0xFF ) << 8;
    SSTOREL( ( lo & 0xFF ) | hi, &lpAct->script[ 8 ] );

    switch ( rand() % 3 )
    {
    case 0:
        lpAct->animation.tex = GV_StrCode( "snow_ex1" );
        break;
    case 1:
        lpAct->animation.tex = GV_StrCode( "snow_ex2" );
        break;
    case 2:
        lpAct->animation.tex = GV_StrCode( "snow_ex3" );
        break;
    }

    NewAnime( NULL, NULL, &lpAct->animation );
}

static void Die( LPSNOWSTORM lpAct )
{
    /* do nothing */
}

static int CheckMessage( u_short name, int n_mes_list, u_short *mes_list )
{
    GV_MSG *msg;
    int found, n_msg, i;

    found = -1;
    n_msg = GV_ReceiveMessage( name, &msg );

    for ( ; n_msg > 0; n_msg--, msg++ )
    {
        for ( i = 0; i < n_mes_list; i++ )
        {
            if ( msg->message[ 0 ] == mes_list[ i ] ) found = i;
        }
    }

    return found;
}
