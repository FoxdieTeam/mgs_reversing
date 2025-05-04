#include "camshake.h"

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"

extern int  GM_CameraShakeOffset;

/*----------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT  actor;
    int     map;        //0x20
    int     name;       //0x24
    SVECTOR pos;        //0x28
    int     radius;     //0x30
    int     strength;   //0x34
    int     time;       //0x38
    int     time2;      //0x3C
    int     count;      //0x40
    int     pad;        //0x44
} Work;

/*----------------------------------------------------------------*/

static void Act( Work *work )
{
    int tmp;
    int length;
    SVECTOR diff;
    SVECTOR *target_pos;

    GM_SetCurrentMap( work->map );
    work->count--;

    if ( work->count < 0 )
    {
        GV_DestroyActor( &( work->actor ) );
        return;
    }

    target_pos = &GM_PlayerPosition;

    diff.vx = tmp = ( target_pos->vx - work->pos.vx ) >> 2 ; length = tmp * tmp ;
    diff.vy = tmp = ( target_pos->vy - work->pos.vy ) >> 2 ; length += tmp * tmp ;
    diff.vz = tmp = ( target_pos->vz - work->pos.vz ) >> 2 ; length += tmp * tmp ;
    length = SquareRoot0( length ) << 2 ;

    /* 範囲外チェック */
    if ( length > work->radius ) return ;

    tmp = ( work->radius -  length ) * ( work->count * work->strength / work->time ) / work->radius ;

    GM_CameraShakeOffset += ( rand() * tmp ) >> 15 ;
}

static void Die( void )
{
    //OPERATOR() ;
}

/*----------------------------------------------------------------*/

static int GetResources_S( Work *work, int name, int where )
{
    /* 初期化 */
    work->map = where ;
    work->name = name ;

    {/* オプション処理１ */
        /* 開始座標設定 */
        THING_Gcl_GetSVector( 'p', &work->pos );
        /* 減衰半径設定 */
        work->radius        = THING_Gcl_GetInt( 'r' );
        /* 最大振幅設定 */
        work->strength      = THING_Gcl_GetInt( 's' );
        /* 持続時間設定 */
        work->time          = THING_Gcl_GetInt( 'l' );
        work->time2         = THING_Gcl_GetInt( 't' );

        work->count = work->time;
    }
    return 0;
}

/*----------------------------------------------------------------*/

void *NewCameraShake(int name, int where, int argc, char **argv)
{
    Work *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "camshake.c" );
        if ( GetResources_S( work, name, where ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
    }
    return (void *)work;
}
