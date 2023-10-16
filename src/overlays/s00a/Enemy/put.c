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

extern const char *s00a_off_800C33F4[];
extern const char *s00a_off_800C33F8[];
extern const char *s00a_off_800C33FC[];

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

    work->next_node = s00a_command_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}