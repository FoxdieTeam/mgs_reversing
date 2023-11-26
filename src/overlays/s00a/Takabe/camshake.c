#include "Game/game.h"

typedef struct CameraShakeWork
{
    GV_ACT  actor;
    int     map;      //0x20
    int     name;     //0x24
    SVECTOR pos;      //0x28
    int     radius;   //0x30
    int     strength; //0x34
    int     time;     //0x38
    int     time2;    //0x3C
    int     count;    //0x40
    int     field_44; //0x44
} CameraShakeWork;

extern int THING_Gcl_GetInt( int o );
extern int THING_Gcl_GetSVector( int o, SVECTOR* svec );

extern SVECTOR GM_PlayerPosition_800ABA10;
extern int  GM_CameraShakeOffset_800ABA98;

void CameraShakeAct_800DF4B8( CameraShakeWork* work )
{
    int tmp;
    int length;
    SVECTOR diff;
    SVECTOR *target_pos;

    GM_SetCurrentMap( work->map );
    work->count--;

    if ( work->count < 0 )
    {
        GV_DestroyActor_800151C8( &( work->actor ) );
        return;
    }

    target_pos = &GM_PlayerPosition_800ABA10;

    diff.vx = tmp = ( target_pos->vx - work->pos.vx ) >> 2 ; length = tmp * tmp ;
    diff.vy = tmp = ( target_pos->vy - work->pos.vy ) >> 2 ; length += tmp * tmp ;
    diff.vz = tmp = ( target_pos->vz - work->pos.vz ) >> 2 ; length += tmp * tmp ;
    length = SquareRoot0( length ) << 2 ;

    /* 範囲外チェック */
    if ( length > work->radius ) return ;

    tmp = ( work->radius -  length ) * ( work->count * work->strength / work->time ) / work->radius ;

    GM_CameraShakeOffset_800ABA98 += ( rand() * tmp ) >> 15 ;
}

extern void CameraShakeDie_800DF634()
{

}

int CameraShakeGetResources_S_800DF63C( CameraShakeWork* work, int name, int where )
{
    /* 初期化 */
    work->map = where ;
    work->name = name ;

    /* オプション処理１ */
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
        return 0;
}

void *NewCameraShake_800DF6AC( int name, int where, int argc, char **argv )
{
    CameraShakeWork *work ;

    work = (CameraShakeWork *)GV_NewActor_800150E4( 5, sizeof( CameraShakeWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CameraShakeAct_800DF4B8, ( TActorFunction )CameraShakeDie_800DF634, "camshake.c" );
        if ( CameraShakeGetResources_S_800DF63C( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
    }
    return (void *)work ;
}
