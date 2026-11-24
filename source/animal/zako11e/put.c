#include "enemy/enemy.h"

#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "game/item.h"
#include "game/vibrate.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

extern void AN_Breath( MATRIX *world );

extern ZAKO_COMMAND ZAKO11ECommand;

static void PutFootNoise( ZakoWork *work );
static void PutBreath( ZakoWork *work );
static void PutSightLine( ZakoWork *work );
static void GunShoot( ZakoWork *work );
static int  UnsetPutChar( ZakoWork *work, void *putchar );

static SVECTOR s11e_dword_800C3670 = {0, 0, 100};
static SVECTOR s11e_dword_800C3678 = {-1024, 0, 0};
static SVECTOR s11e_dword_800C3680 = {0, 0, 100};
static SVECTOR s11e_dword_800C3688 = {-1024, 0, 0};

static char *s11e_dword_800C3690[] = {
    "RATION",
    "SOCOM/BULLET * 12",
    "FA-MAS/BULLET * 25"
};

static void *s11e_dword_800C369C[] = {
    PutFootNoise,
    PutBreath,
    PutSightLine,
    GunShoot
};

static SVECTOR s11e_dword_800C36AC = {5, -500, 80};

/*---------------------------------------------------------------------------*/

void ZAKO11E_PutBlood( ZakoWork *work, int obj_idx, int count )
{
    MATRIX mat;

    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &s11e_dword_800C3670 );
    DG_RotatePos( &s11e_dword_800C3678 );
    ReadRotMatrix( &mat );
    NewBlood( &mat, count );
}

void ZAKO11E_PutDust( ZakoWork *work )
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

void ZAKO11E_PutItem( ZakoWork *work )
{
    SVECTOR step;
    ITEM_INFO item;
    CONTROL *ctrl;

    step = work->unknown.field_0C;
    ctrl = &work->control;

    step.vx += GV_RandU( 10 );
    step.vy += 100;
    step.vz += GV_RandU( 10 );

    GV_RandU( 4 );

    switch ( work->field_B74 )
    {
    case 0:
        item.message = s11e_dword_800C3690[0];
        item.type = 4;
        item.id = IT_Ration;
        item.num = 1;
        break;
    case 1:
    case 2:
    case 3:
        if ( GM_FamasFlag < 0 )
        {
            item.message = s11e_dword_800C3690[1];
            item.type = 2;
            item.id = WP_Socom;
            item.num = 12;
        }
        else
        {
            item.message = s11e_dword_800C3690[2];
            item.type = 2;
            item.id = WP_Famas;
            item.num = 25;
        }
        break;
    }

    item.time = 900;
    NewItemPut( &ctrl->mov, &step, &item );
}

void ZAKO11E_PutMark( ZakoWork *work, int mark )
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

/*---------------------------------------------------------------------------*/

static void PutFootNoise( ZakoWork *work )
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

static void PutBreath( ZakoWork *work )
{
    int frame;

    if ( ZAKO11ECommand.mode == TOP_COMM_ALERT )
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

static void PutSightLine( ZakoWork *work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

static void GunShoot( ZakoWork *work )
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
    UnsetPutChar( work, GunShoot );
}

/*---------------------------------------------------------------------------*/

int ZAKO11E_SetPutChar( ZakoWork *work, int index )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = s11e_dword_800C369C[ index ];
            return 1;
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

static int UnsetPutChar( ZakoWork *work, void *putchar )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == putchar )
        {
            work->field_B00[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

void ZAKO11E_ExecPutChar( ZakoWork *work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            ZAKOPUTFUNC putchar = work->field_B00[i];
            putchar( work );
        }
    }
}
