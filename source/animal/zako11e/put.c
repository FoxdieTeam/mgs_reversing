#include "enemy/enemy.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "game/vibrate.h"
#include "okajima/bullet.h"

extern ZAKO_COMMAND ZakoCommand_800DF280;

extern SVECTOR s11e_dword_800C3670;
extern SVECTOR s11e_dword_800C3678;
extern SVECTOR s11e_dword_800C3680;
extern SVECTOR s11e_dword_800C3688;

extern void    NewBlood( MATRIX *, int );

void ZAKO11E_PutBlood_800D7A14( ZakoWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &s11e_dword_800C3670 );
    DG_RotatePos( &s11e_dword_800C3678 );
    ReadRotMatrix( &mat );
    NewBlood( &mat, count );
}

void ZAKO11E_PutFog_800D7A84( ZakoWork *work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s11e_dword_800C3680 );
    DG_RotatePos( &s11e_dword_800C3688 );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    AN_PunchFog( &svec );
}

extern const char *s11e_dword_800C3690[3];

void ZAKO11E_PutItem_800D7AE8( ZakoWork* work )
{
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    ITEM_INFO item;

    svec = work->unknown.field_0C;
    rand = 10;
    ctrl = &work->control;
    svec.vx += GV_RandU( rand );
    svec.vy += 100;
    rand = GV_RandU( rand );
    svec.vz += rand;
    rand = GV_RandU( 4 );

    switch ( work->field_B74 )
    {
    case 0:
        item.type   = 4;
        item.id     = IT_Ration;
        item.num = 1;
        item.message  = s11e_dword_800C3690[0];
        break;
    case 1:
    case 2:
    case 3:
            if ( GM_FamasFlag < 0 )
            {
                item.type   = 2;
                item.message  = s11e_dword_800C3690[1];
                item.id     = WP_Socom;
                item.num = 12;
            }
            else
            {
                item.type = 2;
                item.id = WP_Famas;
                item.message  = s11e_dword_800C3690[2];
                item.num = 25;
            }
            break;
    }
    item.time = 900;
    NewItemPut( &ctrl->mov, &svec, &item );
}

void ZAKO11E_PutMark_800D7C10( ZakoWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
    }

    if ( work->mark_time )
    {
        GV_DestroyActor( work->mark );
    }

    work->mark = AN_HeadMark( mat, mark ) ;
    work->mark_time = 30;
}

void ZAKO11E_PutSound_800D7CAC( ZakoWork* work )
{
    int a1, a3;
    int a2;
    int v1;

    a3 = work->unknown.last_set;
    a2 = work->m_ctrl.info1.frame;

    v1 = ( ( work->field_B74 % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->field_B74 % 4 ) * 2 ) + 0xA1;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSet( &work->control.mov, a1 );
        }
        else if ( a2 == 11 )
        {
            GM_SeSet( &work->control.mov, v1 );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSet( &work->control.mov, a1 );
        }
        else if ( a2 == 8 )
        {
            GM_SeSet( &work->control.mov, v1 );
        }
    }
}

extern void  NewLSight( SVECTOR *from, SVECTOR *to, int color ) ;
extern void  AN_Breath( MATRIX * );

void ZAKO11E_PutBreath_800D7D44( ZakoWork *work, int arg1 )
{
    int frame;
    if ( ZakoCommand_800DF280.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( work->unknown.last_unset == 20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 19 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else
    {
        if ( ( GV_Time % 64 ) == ( work->field_B74 * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
}

void s11e_zk11ecom_800D7E8C( ZakoWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

extern SVECTOR s11e_dword_800C36AC;

extern void AN_BulletSmoke( MATRIX *, int );
extern void AN_FamasFlash( MATRIX * );

extern int ZAKO11E_ClearPutChar_800D804C( ZakoWork *work, void *func );

void ZAKO11E_PutBulletEx_800D7EC8( ZakoWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos( mat );
    DG_MovePos( &s11e_dword_800C36AC );
    DG_RotatePos( &svec );

    svec.vx = GV_RandS( 16 ) + 1024;
    svec.vz = 0;

    DG_RotatePos( &svec );
    ReadRotMatrix( &local_mat );

    if ( GV_Time & 3 )
    {
        NewBulletEx( BULLET_RECOILSPARK,  &local_mat, 2, 1, 0, 0xA, work->field_B84, 0x2710, 0x2EE);
    }
    else
    {
        NewBulletEx( BULLET_RECOILSPARK | BULLET_NO_HZD, &local_mat, 2, 1, 0, 0xA, work->field_B84, 0x2710, 0x2EE);
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );
    AN_BulletSmoke( mat, 0 );
    AN_FamasFlash( &local_mat );
    ZAKO11E_ClearPutChar_800D804C( work, ZAKO11E_PutBulletEx_800D7EC8 );
}

extern void *s11e_dword_800C369C[];

int ZAKO11E_SetPutChar_800D8004( ZakoWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = s11e_dword_800C369C[ idx ];
            return 1;
        }
    }
    return 0;
}

int ZAKO11E_ClearPutChar_800D804C( ZakoWork *work, void *func )
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

void ZAKO11E_ExecPutChar_800D8080( ZakoWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            ZAKOPUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}
