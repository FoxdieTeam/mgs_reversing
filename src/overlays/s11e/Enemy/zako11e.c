#include "../../s00a/Enemy/enemy.h"

/*
extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern SVECTOR       ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR       ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR       ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR       ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR       ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR       ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR       COM_NO_POINT_800C35D4;
extern int           COM_EYE_LENGTH_800E0D8C;

extern GM_Camera      GM_Camera_800B77E8;
extern int            GM_PlayerMap_800ABA0C;
*/

extern SVECTOR ZAKO_TARGET_SIZE_800C38CC;
extern SVECTOR ZAKO_TARGET_FORCE_800C38D4;
extern SVECTOR ZAKO_ATTACK_SIZE_800C38DC;
extern SVECTOR ZAKO_ATTACK_FORCE_800C38E4;
extern SVECTOR ZAKO_TOUCH_SIZE_800C38EC;
extern SVECTOR ZAKO_TOUCH_FORCE_800C38F4;

extern int ZAKO_EYE_LENGTH_800C3904;
extern SVECTOR ZAKO_NO_POINT_800C38FC;

void s11e_zako11e_800D34C8( void )
{
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D34D0.s")
void s11e_zako11e_800D34D0( DG_OBJS* objs, DG_DEF* def )
{
    int i;
    DG_OBJ *obj;
    DG_FreeObjsPacket_8001ABA8( objs, 0 );
    DG_FreeObjsPacket_8001ABA8( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0 ; i < 16 ; i++ )
    {
        obj->model   = &def->model[ i ];
        obj->n_packs =  def->model[ i ].numFaces_4;
        obj++;
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D354C.s")
extern GM_Camera GM_Camera_800B77E8;
extern int GM_PlayerMap_800ABA0C;

void s11e_zako11e_800D354C( ZakoWork *work )
{
    if ( work->visible )
    {
        if ( work->param_low_poly == 1 )
        {
            if ( GM_GameStatus_800AB3CC & 0x50 || GM_Camera_800B77E8.field_22 )
            {
                if ( work->field_180 != work->param_low_poly )
                {
                    work->field_180 = work->param_low_poly;
                    s11e_zako11e_800D34D0( work->body.objs, work->def );
                }
            }
            else if ( work->field_180 )
            {
                work->field_180 = 0;
                s11e_zako11e_800D34D0( work->body.objs, work->kmd );
            }
        }
        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 1;
        work->field_AFC[0] = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 0;
        work->field_AFC[0] = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3684.s")



//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3800.s")
void s11e_zako11e_800D3800( ZakoWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget_8002DC74( target, ( TARGET_FLAG | TARGET_AVAIL ), ENEMY_SIDE, &ZAKO_TARGET_SIZE_800C38CC );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ZAKO_TARGET_FORCE_800C38D4 );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    work->local_data = work->param_life;
    target2 = &work->field_904;
    GM_SetTarget_8002DC74( target2, TARGET_POWER, PLAYER_SIDE, &ZAKO_ATTACK_SIZE_800C38DC );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ZAKO_ATTACK_FORCE_800C38E4 );

    target2 = &work->field_94C;
    GM_SetTarget_8002DC74( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ZAKO_TOUCH_SIZE_800C38EC );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ZAKO_TOUCH_FORCE_800C38F4 );
}


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3934.s")
void s11e_zako11e_800D3934( ZakoWork* work )
{
    WatcherUnk *s;
    s = (WatcherUnk*)&work->field_8C8;

    GV_ZeroMemory_8001619C(s, 0x24);
    s->field_00 = 0;
    s->field_1C = 0x1C2;
    s->field_1E = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3990.s")
extern void s11e_zako11e_800D3990( ZakoWork *work, int name, int where );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3BD8.s")
extern void s11e_zk11ecom_800D9A64( int );

void s11e_zako11e_800D3BD8( ZakoWork* work )
{
    s11e_zk11ecom_800D9A64( work->field_B74 );
    GM_FreeControl_800260CC( &( work->control ) );
    GM_FreeObject_80034BF8( &( work->body ) );
    GM_FreeObject_80034BF8( &( work->field_7A4 ) );
    GM_FreeTarget_8002D4B0( work->target );
    GV_DestroyActor_800151C8( work->field_AF8 );
    GV_DestroyActor_800151C8( work->field_AF0 );

    HomingTarget_Free_80032CFC( work->hom );
    if ( work->field_C40 )
    {
        GV_DestroyActorQuick_80015164( (GV_ACT*)work->field_C40 );
        work->field_C40 = 0;
    }
    if ( work->field_C44 )
    {
        GV_DestroyActorQuick_80015164( (GV_ACT*)work->field_C44 );
        work->field_C44 = 0;
    }
}
//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3C84.s")
void s11e_zako11e_800D3C84( ZakoWork* work )
{
    s11e_zako11e_800D3BD8( work );
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3CA4.s")
int s11e_zako11e_800D3CA4( ZakoWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.field_2C_map->field_8_hzd->f00_header->routes;
    patrol = &patrol[ work->param_root ];

    work->field_9E8 = patrol->n_points;

    if ( work->field_9E8 <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->field_9E8 ; i++ )
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    return 0;
}


extern void s11e_zako11e_800D3800( ZakoWork *work );

extern int s11e_zk11ecom_800D9A20( ZakoWork *work );
extern void s11e_zk11ecom_800D8004( ZakoWork *work, int put );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3D40.s")
int s11e_zako11e_800D3D40( int opt, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *s = GCL_StrToInt_800209E8( res );
         s++;
    }

    return i;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3D98.s")
int s11e_zako11e_800D3D98( int opt, int* l )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *l = GCL_StrToInt_800209E8( res );
         l++;
    }

    return i;
}


extern unsigned short s11e_dword_800C35DC[8];

extern const char s11e_aErrerrerrsettimeover_800DEAE8[];
extern const char s11e_aErrerrerrsetdirover_800DEB04[];



int s11e_zako11e_800D3DF0( ZakoWork *work )
{
    int i;
    int opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BB0[i] = s11e_dword_800C35DC[i];
    }

    opt = GCL_GetOption_80020968( 't' );
    if ( opt )
    {
        ret = s11e_zako11e_800D3D98( opt, &work->field_BB0[1] );
        if ( ret > 4 )
        {
            printf( s11e_aErrerrerrsettimeover_800DEAE8 ) ;
            return -1;
        }
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        work->field_BD0[i] = i * 1024;
    }

    opt = GCL_GetOption_80020968( 'i' );

    if ( opt )
    {
        ret = s11e_zako11e_800D3D40( opt, work->field_BD0 );
        if ( ret > 4 )
        {
            printf( s11e_aErrerrerrsetdirover_800DEB04 ) ;
            return -1;
        }
    }

    return 0;
}


extern const char s11e_aErrnotenoughwork_800DEB20[];// = "Err not enough work !!\n";
extern const char s11e_aLowporyd_800DEB38[];// = " low[pory=%d\n";
extern const char s11e_aWatcharcactionpointerr_800DEB48[];// = "watchar.c : action point Err\n";

extern int s11e_dword_800C35BC[8];

extern void  GM_ConfigControlRadarparam_800262EC( CONTROL *pControl, unsigned short param_2, unsigned short param_3, int param_4, unsigned short param_5 );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3EC8.s")
void s11e_zako11e_800D3EC8( ZakoWork *work, int name, int where )
{
    int addr;
    int opt;
    int i;

    s11e_zako11e_800D3990( work, name, where ) ;
    work->field_B74 = s11e_zk11ecom_800D9A20( work ) ;

    if ( work->field_B74  << 24 < 0  )
    {
       printf( s11e_aErrnotenoughwork_800DEB20 ) ;
    }

    s11e_zako11e_800D3DF0( work ) ;

    //root
    work->param_root = 0;
    opt = GCL_GetOption_80020968( 'r' );
    if ( opt )
    {
        work->param_root = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //life
    work->param_life = 576;
    opt = GCL_GetOption_80020968( 'l' );
    if ( opt )
    {
        work->param_life = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //faint
    work->param_faint = 7;
    opt = GCL_GetOption_80020968( 'f' );
    if ( opt )
    {
        work->param_faint = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->field_B84 = 64;
    opt = GCL_GetOption_80020968( 'z' );
    if ( opt )
    {
        work->field_B84 = GCL_StrToInt_800209E8( ( char* )opt );
    }
    
    work->param_blood = 65;
    opt = GCL_GetOption_80020968( 'b' );
    if ( opt )
    {
        work->param_blood = GCL_StrToInt_800209E8( ( char* )opt );
    }

    printf( s11e_aLowporyd_800DEB38, work->param_low_poly ) ;
    work->field_B7D = 0xFF;
    
    opt = GCL_GetOption_80020968('g');
    if ( opt )
    {
        work->field_B7D = GCL_StrToInt_800209E8( ( char* )opt );
    }
    if ( work->param_blood == 'Z' )
    {
        work->field_B7D = 0;
    }

    work->field_BFC = s11e_dword_800C35BC[ work->field_B74 ];
    work->field_C00 = work->field_B74;
    work->field_B78 = 0xFF;
    
    opt = GCL_GetOption_80020968( 'n' );
    if ( opt )
    {
        work->field_B78 = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->param_area = 'A';
    opt = GCL_GetOption_80020968( 'a' );
    if (opt != 0)
    {
        work->param_area = GCL_StrToInt_800209E8( ( char* )opt );
    }

    if ( work->param_area == 'S' ) s11e_zk11ecom_800D8004( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption_80020968( 's' ) ) != NULL ) work->scale += GCL_StrToInt_800209E8( ( char* )opt );
    work->param_item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //  work->param.life, work->param.faint, work->param.blood,work->param.area);

    opt = GCL_GetOption_80020968( 'o' );
    if ( opt )
    {
        work->field_C48 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        work->field_C48 = -1;
    }

    
    if( s11e_zako11e_800D3CA4( work ) < 0 ) fprintf( 1, s11e_aWatcharcactionpointerr_800DEB48 );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget_8002D400() ) != NULL ) s11e_zako11e_800D3800( work ) ;

    /*
        思考ルーチン用データを初期化する
    */
    work->think1 = 0 ;
    work->think2 = 0 ;
    work->think3 = 0 ;
    work->think4 = 0 ;
    work->count3 = 0 ;
    work->l_count = 0 ;
    work->t_count = 0 ;
    work->mark_time = 0 ;
    work->next_node = 0 ;
    work->search_flag = 0 ;
    work->act_status = 0 ;
    work->target_pos = work->nodes[ 0 ] ;
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &( work->target_pos ), -1 ) ;
    work->target_map  = GM_CurrentMap_800AB9B0;
    work->alert_level = 0;
    work->visible = 1;
    work->vision.field_B8E = 0x200;
    work->vision.facedir = 0;
    work->field_B94 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision.length = ZAKO_EYE_LENGTH_800C3904;
    work->field_BA4 = ZAKO_NO_POINT_800C38FC;    
    work->subweapon = 0;
    

    work->control.field_0_mov = work->nodes[ 0 ] ;
    work->field_B7B = work->field_B78;
    work->field_C4C = 0;
    //work->faseout = 0;
    work->param_c_root = 0;
    
    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->field_BA3 =  7;
    work->field_BA0 = -1;

    GM_ConfigControlRadarparam_800262EC( &work->control , 0, 0x200, ZAKO_EYE_LENGTH_800C3904, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap_800AB9B0;
    addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &( work->control.field_0_mov ), -1 );

    work->start_addr = addr;
    work->field_C10  = addr;
    work->field_BF0  = addr;

    work->field_C1C = work->start_pos;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D42E0.s")
extern void s11e_zako11e_800D3684();
extern void s11e_zako11e_800D3C84();
extern const char s11e_aZakoec_800DEB68[];
    
void *s11e_zako11e_800D42E0( int name, int where, int argc, char **argv )
{
    ZakoWork *work ;

    work = (ZakoWork *)GV_NewActor_800150E4( 4, sizeof( ZakoWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )s11e_zako11e_800D3684, ( TActorFunction )s11e_zako11e_800D3C84, s11e_aZakoec_800DEB68 );
        s11e_zako11e_800D3EC8( work, name, where );
    }
    return (void *)work ;
}