#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/camera.h"
#include "Game/game.h"
#include "Takabe/thing.h"

typedef struct WaterAreaWork
{
    GV_ACT actor;
    int where;            //0x20
    int name;             //0x24
    SVECTOR bound[2];     //0x28
    CVECTOR color;        //0x38
    int snake_catch;      //0x3C
    int splash_flag;      //0x40
    int field_44;         //0x44
    int field_48;         //0x48
    int field_4C;         //0x4C
    int proc_id;          //0x50
} WaterAreaWork;

extern void    NewSplash2_800DB4E0( int angy, SVECTOR *pos, int noripple );
extern void   *NewRipple_800D7F30( MATRIX *, int );
extern GV_ACT *NewWaterView_800DBE04(int name, int where, SVECTOR *arg2, CVECTOR *color);

extern unsigned int     GM_PlayerStatus_800ABA50;
extern int              GM_GameOverTimer_800AB3D4;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern MATRIX           DG_ZeroMatrix_8009D430;
extern int              DG_FrameRate_8009D45C;
extern CONTROL         *tenage_ctrls_800BDD30[16];
extern int              tenage_ctrls_count_800BDD70;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;


//OPEN_MES, CLOSE_MES
unsigned short mes_list_800C3664[] = { 0x43D3, 0x4235 };
SVECTOR mouth_offset_800C3668 = { 0, 0, 100 };

int BoundInCheck_800DA5B4( SVECTOR *bound, SVECTOR *check )
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

void ExecProc_800DA644( int proc_id, int mode )
{
    GCL_ARGS    args ;
    long        data = mode ;
    if ( proc_id == 0 ) return ;
    args.argc = 1 ;
    args.argv = &data ;
    GCL_ExecProc_8001FF2C( proc_id, &args );
}

void WaterAreaAct_800DA67C( WaterAreaWork *work )
{
    //static SVECTOR    mouth_offset = {0,0,100};
    //SVECTOR       pos, snake_pos ;
    SVECTOR     snake_pos ;
    CONTROL   **ctrl;
    int         flag ;
    MATRIX      mtx;
    MATRIX     *eye;
    int         i;
    //OPERATOR() ;
    mtx = DG_ZeroMatrix_8009D430;

    /* メッセージチェック */
    switch ( THING_Msg_CheckMessage( ( unsigned short )work->name, 2, mes_list_800C3664 ) ){
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

    flag = BoundInCheck_800DA5B4( work->bound, &GM_PlayerControl_800AB9F4->mov );

    if ( work->snake_catch == 0  )
    {
        if ( flag )
        {
            /* スネーク中心部の水中バウンドチェック */
            snake_pos = GM_PlayerControl_800AB9F4->mov ;
            snake_pos.vy = work->bound[1].vy; /* 水面に座標を合わせる */
            if ( work->splash_flag )
            {
                NewSplash2_800DB4E0( GM_PlayerControl_800AB9F4->rot.vy + 2048, &snake_pos, 0 );
                GM_SeSet_80032858( &snake_pos, 0xB0 );
                if ( work->field_44 == NULL )
                {
                    GM_SetNoise(0x64, 2, &snake_pos );
                }
                work->splash_flag = 0;
            }
            else
            {
                GM_SeSet_80032858( &snake_pos, 0xB1 );
            }
            work->snake_catch = 1;
            GM_PlayerStatus_800ABA50 |= 0x1000000;
        }

    }
    else
    {
        if ( !flag )
        {
            /* スネーク中心部の水中バウンドチェック */
            snake_pos = GM_PlayerControl_800AB9F4->mov ;
            snake_pos.vy = work->bound[1].vy; /* 水面に座標を合わせる */
            GM_SeSet_80032858( &snake_pos, 0xB1 );
            if ( work->field_44 == NULL )
            {
                GM_SetNoise(0x64, 2, &snake_pos );
            }
            work->snake_catch = 0;
            GM_PlayerStatus_800ABA50 &= ~( 0x1000000 );
        }

    }
    snake_pos = GM_PlayerControl_800AB9F4->mov ;

    if ( GM_PlayerStatus_800ABA50 & 2 )
    {
        snake_pos = gUnkCameraStruct_800B77B8.field_0;
    }
    else
    {
        if ( GM_PlayerStatus_800ABA50 & 0x40 )
        {
            snake_pos.vy += 0x140;
        }
        else
        {
            snake_pos.vy = GM_PlayerBody_800ABA20->objs->objs[6].world.m[3][3];
        }
    }

    flag = BoundInCheck_800DA5B4( work->bound, &snake_pos );

    if ( !work->field_48 )
    {
        if ( flag )
        {
            ExecProc_800DA644( work->proc_id, 0x2A74 );
            work->field_48 = 1;
        }
    }
    else
    {
        if ( !flag && !GM_GameOverTimer_800AB3D4 )
        {
            DG_SetPos2_8001BC8C( &snake_pos, &GM_PlayerControl_800AB9F4->rot );
            DG_PutVector_8001BE48( &mouth_offset_800C3668, &snake_pos, 1 );
            GM_SeSet_80032858( &snake_pos, 0xB3 );
            ExecProc_800DA644( work->proc_id, 0xF26E );
            work->field_48 = 0;
        }
    }

    eye = &DG_Chanl(0)->field_30_eye;
    snake_pos.vx = eye->t[0];
    snake_pos.vy = eye->t[1];
    snake_pos.vz = eye->t[2];
    flag = BoundInCheck_800DA5B4( work->bound, &snake_pos );

    if ( !work->field_4C )
    {
        if ( flag )
        {
            GM_SeSet2_80032968( 0, 0x3F, 0xB2 );
            ExecProc_800DA644( work->proc_id, 0xF6D8 );
            work->field_4C = 1;
            if ( !(GM_PlayerStatus_800ABA50 & 2) )
            {
                DG_FrameRate_8009D45C = 3;
            }
        }
    }
    else
    {
        if ( !flag )
        {
            GM_Sound_80032C48( 0xff0000fe, 0 );
            ExecProc_800DA644( work->proc_id, 0xBED3 );
            work->field_4C = 0;
            DG_FrameRate_8009D45C = 2;
        }
    }

    if ( !tenage_ctrls_count_800BDD70 ) return;

    ctrl = tenage_ctrls_800BDD30;
    for ( i = 16 ; i > 0 ; --i, ctrl++ )
    {
        if (*ctrl)
        {
            if ( BoundInCheck_800DA5B4( work->bound, &( (*ctrl)->mov  ) ) )
            {
                mtx.t[0] = (*ctrl)->mov.vx;
                mtx.t[1] = work->bound[1].vy;
                mtx.t[2] = (*ctrl)->mov.vz;
                NewRipple_800D7F30( &mtx, 2048 );
                (*ctrl)->mov.pad = 1;
            }
        }
    }
}

void WaterAreaDie_800DABC8( void )
{
}


int WaterAreaGetResources_800DABD0( WaterAreaWork *work, int name, int where )
{
    work->color.r = 0x64;
    work->color.g = 0x80;
    work->color.b = 0x78;

    if ( GCL_GetOption_80020968( 'b' ) )
    {
        GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &work->bound[0] );
        GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &work->bound[1] );
    }

    if ( GCL_GetOption_80020968( 'c' ) )
    {
        work->color.r = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.g = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.b = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->field_44 = THING_Gcl_GetInt('s');
    work->proc_id  = THING_Gcl_GetInt('e');

    NewWaterView_800DBE04( name, where, work->bound, &work->color );
    return 0;
}

GV_ACT * NewWaterArea_800DACCC(int name, int where, int argc, char **argv)
{
    WaterAreaWork *work ;

    work = (WaterAreaWork *)GV_NewActor_800150E4( 5, sizeof( WaterAreaWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )WaterAreaAct_800DA67C, ( TActorFunction )WaterAreaDie_800DABC8, "wt_area.c" );
        if ( WaterAreaGetResources_800DABD0( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
        work->where = where;
        work->name  = name;
    }
    return &work->actor;
}
