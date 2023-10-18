#include "enemy.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"

SVECTOR s00a_dword_800C33D4;
SVECTOR s00a_dword_800C33DC;
SVECTOR s00a_dword_800C33E4;
SVECTOR s00a_dword_800C33EC;

extern void NewBlood_80072728( MATRIX *, int );

void ENE_PutBlood_800C8FF8( WatcherWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos_8001BC44(&work->body.objs->objs[obj_idx].world);
    DG_MovePos_8001BD20( &s00a_dword_800C33D4 );
    DG_RotatePos_8001BD64( &s00a_dword_800C33DC );
    ReadRotMatrix( &mat );
    NewBlood_80072728( &mat, count );
}

void s00a_command_800C9068( WatcherWork* work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos_8001BC44( &work->body.objs->objs[1].world );
    DG_MovePos_8001BD20( &s00a_dword_800C33E4 );
    DG_RotatePos_8001BD64( &s00a_dword_800C33EC );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];
    
    s00a_command_800CA618( &svec );
}

extern char *s00a_off_800C33F4[];
extern char *s00a_off_800C33F8[];
extern char *s00a_off_800C33FC[];

void ENE_PutItem_800C90CC( WatcherWork *work )
{
    int a1;
    int a2;
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    Item_Info item;
    svec = work->field_8D4;
    rand = 8;
    ctrl = &work->control;
    svec.vx += GV_RandU_80017090( rand );
    svec.vy += 100;
    rand = GV_RandU_80017090( rand );
    svec.vz += rand;
   
   switch ( work->local_data )
   {
    case 0:
        rand = GV_RandU_80017090( 4 );
        break;
    case 1:
        rand = 3;
        break;
    case 2:
        rand = 0;
        break;
    case 3:
        rand = 1;
        break;
    case 4:
        rand = 2;
        break;
   }

    a1 = 1;
    switch ( rand )
    {
    default:
        break;
    case 3:
        return;
    case 0:
        //ration
        item.field_4_type   = 4;
        item.field_6_id     = 13;
        item.field_8_amount = 1;
        item.field_0_pName  = s00a_off_800C33F4[0];
        break;
    case 1:
        //socom
        if ( GM_Weapons[0] < 0 ) 
        {
            item.field_4_type   = 4;
            item.field_6_id     = 13;
            item.field_8_amount = 1;
            item.field_0_pName  = s00a_off_800C33F4[0];
        }
        else
        {
            //Socom bullets
            item.field_4_type = 2;
            item.field_6_id = 0;
            if ( work->local_data2 == 0 )
            {
                item.field_8_amount = 12;
                item.field_0_pName  = s00a_off_800C33F8[0];
            }
            else
            {
                a1 = 9;
                if ( work-> local_data2 > 99 )
                {
                    a2 = a1;
                }
                else
                {
                    a1 = work->local_data2 / 10;
                    a2 = work->local_data2 % 10;
                }
                if ( a1 == 0 )
                {
                    s00a_off_800C33F8[0][15] = 0x20;
                }
                else
                {
                    s00a_off_800C33F8[0][15] = a1 + 0x30;
                }
                s00a_off_800C33F4[1][16] = a2 + 0x30;
                item.field_0_pName  = s00a_off_800C33F4[1];
                item.field_8_amount = work->local_data2;
            }
        }
        break;
    case 2:
        //famas
        if ( GM_FamasFlag < 0 || GM_DifficultyFlag < 0 ) 
        {
            item.field_4_type   = 4;
            item.field_6_id     = 13;
            item.field_8_amount = 1;
            item.field_0_pName  = s00a_off_800C33F4[0];
        }
        else
        {
            item.field_4_type   = 2;
            item.field_6_id     = 1;
            item.field_8_amount = 25;
            item.field_0_pName  = s00a_off_800C33FC[0];
        }
        break;
    }
    item.field_A = 450;
    if ( work->param_item == 1 )
    {
        item_init_80034758( &ctrl->field_0_mov, &svec, &item );
    }
}

extern int dword_800ABA0C;

void ENE_PutMark_800C9378( WatcherWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.field_2C_map->field_0_map_index_bit & dword_800ABA0C ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        s00a_command_800CEC40( &work->control.field_0_mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor_800151D8( (GV_ACT*)work->next_node );
    }

    work->next_node = (int)s00a_command_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}

extern short s00a_dword_800E0F12;

void s00a_command_800C9414( WatcherWork* work )
{
    int a1, a3;
    int a2;
    int v1;
    if ( !s00a_dword_800E0F12 ) return;

    a3 = work->field_8E0;
    a2 = work->m_ctrl.field_04_info1.field_2_footstepsFrame;

    v1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA1;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, a1 );
        }
        else if ( a2 == 11 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, v1 );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, a1 );
        }
        else if ( a2 == 8 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, v1 );
        }
    }
}

extern int dword_800ABA0C;
extern int GV_Time_800AB330;

extern void AN_Breath_800C3AA8( MATRIX *, int );

void ENE_PutBreath_800C94B8( WatcherWork *work, int arg1 )
{
    int frame;
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.field_2C_map->field_0_map_index_bit & dword_800ABA0C ) )
    {
        return;
    }

    if ( work->field_8E2 == 20 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , arg1 );
        }
    }
    else if ( work->field_8E2 == 22 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , arg1 );
        }
    }
    else if ( work->field_8E2 == 19 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world, arg1 );
        } 
    }
    else
    {
        if ( ( GV_Time_800AB330 % 64 ) == ( work->field_B78 * 16 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , GV_Time_800AB330 );
        }
    }
}

extern void s00a_lsight_800D1D2C( SVECTOR *, SVECTOR *, int ) ;
extern SVECTOR GM_PlayerPosition_800ABA10;

void ENE_PutLSight_800C9600( WatcherWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        s00a_lsight_800D1D2C( &GM_PlayerPosition_800ABA10, &work->control.field_0_mov, 0x8F );
    }
}

extern void  anime_create_8005D6BC( MATRIX *, int );
extern void  anime_create_8005D604( MATRIX * );
extern void *NewBulletEx_80076708(  int, MATRIX*, int, int, int, int, int, int, int );

extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR s00a_dword_800C3410;

void ENE_PutBulletEx_800C963C( WatcherWork *work )
{
    int damage;
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;
    
    svec = DG_ZeroVector_800AB39C;
    svec.vz = GV_RandU_80017090( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos_8001BC44( mat );
    DG_MovePos_8001BD20( &s00a_dword_800C3410 );
    DG_RotatePos_8001BD64( &svec );

    svec.vx = GV_RandS_800170BC( 16 ) + 1024;
    svec.vz = 0;

    DG_RotatePos_8001BD64( &svec );
    ReadRotMatrix( &local_mat );

    switch ( GM_DifficultyFlag )
    {
    case 1:
        damage = 96;
        break;
    case 2:
    case 3:
        damage = 128;
        break;
    default:
        damage = 64;
        break;
    }
  
    if ( GV_Time_800AB330 & 3 )
    {
        NewBulletEx_80076708( 0x100,  &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }
    else
    {
        NewBulletEx_80076708( 0x1100, &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }

    GM_Sound_800329C4( &work->control.field_0_mov, 0x2D, 1 );
    anime_create_8005D6BC( mat, 0 );
    anime_create_8005D604( &local_mat );
    ENE_ClearPutChar_800C97E4( work, ENE_PutBulletEx_800C963C );
}

extern void *PutFuncList_800C3400[];

int ENE_SetPutChar_800C979C( WatcherWork *work, int idx )
{
    int i;
    
    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = PutFuncList_800C3400[ idx ];
            return 1;
        }
    }
    return 0;
}

int ENE_ClearPutChar_800C97E4( WatcherWork *work, void *func )
{
    int i;
    
    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == func )
        {
            work->field_B00[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void ENE_ExecPutChar_800C9818( WatcherWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            PUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}