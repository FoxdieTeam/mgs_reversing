#include "common.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Takabe/thing.h"

typedef struct WaterArea2Work
{
    GV_ACT  actor;
    int     where;        //0x20
    int     name;         //0x24
    SVECTOR bound[2];     //0x28
    char    field_38;     //0x38
    char    field_39;     //0x39
    char    field_3A;     //0x3A
    char    field_3B;     //0x3B
    int     snake_catch;  //0x3C
    int     splash_flag;  //0x40
    int     field_44;     //0x44
    int     field_48;     //0x48
    int     field_4C;     //0x4C
    int     proc_id;      //0x50
} WaterArea2Work;

extern void             NewSplash2_800DB6F0( int angy, SVECTOR *pos, int noripple );
extern void            *NewRipple_800D7F30( MATRIX *, int );
extern void            *NewWaterView_800DBE04( int name, int where, int argc, char **argv );

extern unsigned int     GM_PlayerStatus_800ABA50;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern SVECTOR          GM_NoisePosition_800AB9F8;
extern int              GM_NoiseLength_800ABA30;
extern int              GM_NoisePower_800ABA24;

//OPEN_MES, CLOSE_MES
unsigned short mes_list_800C3410[] = { 0x43D3, 0x4235 };
SVECTOR mouth_offset_800C3414 = { 0, 0, 100, 0 };

int WaterArea2BoundInCheck_800CEA48(SVECTOR *bound, SVECTOR *check)
{
    if ( !(check->vx <= bound[0].vx)  )
    {
        if ( check->vx < bound[1].vx )
        {
            if ( !(check->vy <= bound[0].vy) )
            {
                if ( check->vy < bound[1].vy )
                {
                    if ( !(check->vz <= bound[0].vz) )
                    {
                        if ( !(check->vz >= bound[1].vz) )
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

void WaterArea2ExecProc_800CEAD8(int proc_id, int mode)
{
    GCL_ARGS args;
    long     data;

    data = mode;

    if (proc_id == 0)
    {
        return;
    }

    args.argc = 1;
    args.argv = &data;
    GCL_ExecProc(proc_id, &args);
}

void WaterArea2Act_800CEB10(WaterArea2Work *work)
{
    SVECTOR snake_pos;
    SVECTOR snake_floor;
    int     flag;
    MATRIX *eye;
    MATRIX *world;

    /* メッセージチェック */
    switch ( THING_Msg_CheckMessage( ( unsigned short )work->name, 2, mes_list_800C3410 ) ){
      case 0:
        /* 水しぶき有効 */
        work->splash_flag = 1 ;
        break ;
      case 1:
        /* 水しぶき無効 */
        work->splash_flag = 0 ;
        break ;
    }

    if ( GM_PlayerControl_800AB9F4 == NULL ) return ;
    /* スネーク中心部の水中バウンドチェック */
    snake_floor = GM_PlayerControl_800AB9F4->mov ;
    snake_floor.vy -= GM_PlayerControl_800AB9F4->height / 2;

    flag = WaterArea2BoundInCheck_800CEA48( work->bound, &snake_floor );

    if (work->snake_catch == 0)
    {
        /* スネークが飛び込んだかどうかをチェック */
        if (flag)
        {
            snake_pos = snake_floor;
            snake_pos.vy = work->bound[1].vy; /* 水面に座標を合わせる */

            if (work->splash_flag)
            {
                NewSplash2_800DB6F0( GM_PlayerControl_800AB9F4->rot.vy + 2048, &snake_pos, 0 );
                work->splash_flag = 0;
            }

            GM_SeSet(&snake_pos, 176);

            if (work->field_44 == 0)
            {
                GM_SetNoise(0x64, 2, &snake_pos);
            }

            work->snake_catch = 1;
        }
    }
    else if (!flag)
    {
        snake_pos = snake_floor;
        snake_pos.vy = work->bound[1].vy; /* 水面に座標を合わせる */

        if (work->field_44 == 0)
        {
            GM_SetNoise(0x64, 2, &snake_pos);
        }

        work->snake_catch = 0;
    }

    if (GM_PlayerStatus_800ABA50 & 0x42)
    {
        world = &GM_PlayerBody_800ABA20->objs->objs[0].world;
    }
    else
    {
        world = &GM_PlayerBody_800ABA20->objs->objs[6].world;
    }

    snake_pos.vx = world->t[0];
    snake_pos.vy = world->t[1];
    snake_pos.vz = world->t[2];

    flag = WaterArea2BoundInCheck_800CEA48( work->bound, &snake_pos );

    if (!work->field_48)
    {
        if (flag)
        {
            WaterArea2ExecProc_800CEAD8( work->proc_id, 0x2A74 );
            work->field_48 = 1;
        }
    }
    else if ( !flag && !GM_GameOverTimer )
    {
        DG_SetPos2( &snake_pos, &GM_PlayerControl_800AB9F4->rot );
        DG_PutVector( &mouth_offset_800C3414, &snake_pos, 1 );
        GM_SeSet( &snake_pos, 0xB3 );
        WaterArea2ExecProc_800CEAD8( work->proc_id, 0xF26E );
        work->field_48 = 0;
    }

    eye = &DG_Chanl(0)->field_30_eye;
    snake_pos.vx = eye->t[0];
    snake_pos.vy = eye->t[1];
    snake_pos.vz = eye->t[2];

    flag = WaterArea2BoundInCheck_800CEA48( work->bound, &snake_pos );

    if ( !work->field_4C )
    {
        if ( flag )
        {
            GM_SeSet2( 0, 0x3F, 0xB2 );
            WaterArea2ExecProc_800CEAD8( work->proc_id, 0xF6D8 );
            work->field_4C = 1;
        }
    }
    else if ( !flag )
    {
        GM_SetSound( 0xff0000fe, SD_ASYNC );
        WaterArea2ExecProc_800CEAD8( work->proc_id, 0xBED3 );
        work->field_4C = 0;
    }

    if ((GM_NoisePower_800ABA24 == 0xFF) &&
        (GM_NoiseLength_800ABA30 == 0x1F) &&
        WaterArea2BoundInCheck_800CEA48(work->bound, &GM_NoisePosition_800AB9F8))
    {
        GM_SeSetMode(&GM_NoisePosition_800AB9F8, 0xB5, GM_SEMODE_BOMB);
    }
}

void WaterArea2Die_800CEF64(WaterArea2Work *work)
{
}

int WaterArea2GetResources_800CEF6C( WaterArea2Work *work, int name, int where )
{
    work->field_38 = 0x64;
    work->field_39 = 0x80;
    work->field_3A = 0x78;

    if ( GCL_GetOption( 'b' ) )
    {
        GCL_StrToSV( GCL_GetParamResult(), &work->bound[0] );
        GCL_StrToSV( GCL_GetParamResult(), &work->bound[1] );
    }

    if ( GCL_GetOption( 'c' ) )
    {
        work->field_38 = GCL_StrToInt(GCL_GetParamResult());
        work->field_39 = GCL_StrToInt(GCL_GetParamResult());
        work->field_3A = GCL_StrToInt(GCL_GetParamResult());
    }

    work->field_44 = THING_Gcl_GetInt('s');
    work->proc_id  = THING_Gcl_GetInt('e');

    NewWaterView_800DBE04( name, where, (int)work->bound, (char **)&work->field_38 );
    return 0;
}

void *NewWaterArea2_800DACCC( int name, int where, int argc, char **argv )
{
    WaterArea2Work *work ;

    work = (WaterArea2Work *)GV_NewActor( 5, sizeof( WaterArea2Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( GV_ACTFUNC )WaterArea2Act_800CEB10, ( GV_ACTFUNC )WaterArea2Die_800CEF64, "wt_area2.c" );
        if ( WaterArea2GetResources_800CEF6C( work, name, where ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
        work->where = where;
        work->name  = name;
    }
    return (void *)work ;
}
