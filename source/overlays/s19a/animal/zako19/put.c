#include "zako.h"

#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "game/item.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

extern void *AN_Breath( MATRIX *world );
extern void *AN_Fog( SVECTOR *pos );
extern void *AN_HeadMark( MATRIX* world, int mark );

/*---------------------------------------------------------------------------*/

static void PutSound( Work *work );
static void PutBreath( Work *work );
static void PutLaserSight( Work *work );
static void PutBullet( Work *work );

static SVECTOR BloodPos = {0, 0, 100};
static SVECTOR BloodRot = {-1024, 0, 0};

static SVECTOR FogPos = {0, 0, 100};
static SVECTOR FogRot = {-1024, 0, 0};

static char *ItemText[] = {
    "RATION",
    "SOCOM/BULLET * 12",
    "FA-MAS/BULLET * 25",
};

static void *PutChars[] = {
    PutSound,
    PutBreath,
    PutLaserSight,
    PutBullet,
};

static SVECTOR BulletPos = {5, -500, 80};

/*---------------------------------------------------------------------------*/

void ZAKO19_PutBlood( Work *work, int unit, int count )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ unit ].world );
    DG_MovePos( &BloodPos );
    DG_RotatePos( &BloodRot );
    ReadRotMatrix( &world );
    NewBlood( &world, count );
}

void ZAKO19_PutFog( Work *work )
{
    MATRIX world;
    SVECTOR pos;

    DG_SetPos( &work->body.objs->objs[ 1 ].world );
    DG_MovePos( &FogPos );
    DG_RotatePos( &FogRot );
    ReadRotMatrix( &world );
    DG_COPY_VEC( &pos, (VECTOR *)world.t );
    AN_Fog( &pos );
}

void ZAKO19_PutItem( Work *work )
{
    SVECTOR step;
    ITEM_INFO info;
    SVECTOR *pos;

    pos = &work->control.mov;

    step = work->act.field_0C;
    step.vx += GV_RandU( 10 );
    step.vy += 100;
    step.vz += GV_RandU( 10 );

    switch ( GV_RandU( 4 ) )
    {
    case 0:
    case 1:
        info.message = ItemText[ 0 ];
        info.type = 4;
        info.id = IT_Ration;
        info.num = 1;
        break;
    case 2:
        if ( GM_Weapons[ WP_Socom ] < 0 )
        {
            info.message = ItemText[ 0 ];
            info.type = 4;
            info.id = IT_Ration;
            info.num = 1;
        }
        else
        {
            info.message = ItemText[ 1 ];
            info.type = 2;
            info.id = WP_Socom;
            info.num = 12;
        }
        break;
    case 3:
        if ( GM_Weapons[ WP_Famas ] < 0 )
        {
            info.message = ItemText[ 0 ];
            info.type = 4;
            info.id = IT_Ration;
            info.num = 1;
        }
        else
        {
            info.message = ItemText[ 2 ];
            info.type = 2;
            info.id = WP_Famas;
            info.num = 25;
        }
        break;
    }

    info.time = 900;
    NewItemPut( pos, &step, &info );
}

void ZAKO19_PutMark( Work *work, int mark )
{
    MATRIX *world;

    if ( !( work->control.map->index & GM_PlayerMap ) ) return;
    world = &work->body.objs->objs[ 6 ].world;

    if ( mark == 0 ) GM_SeSet( &work->control.mov, SE_EXCLAMATION );
    if ( work->mark_time != 0 ) GV_DestroyActor( work->mark );

    work->mark = AN_HeadMark( world, mark );
    work->mark_time = 30;
}

/*---------------------------------------------------------------------------*/

static void PutSound( Work *work )
{
    int motion, frame;
    int se1, se2;

    motion = work->act.motion1;
    frame = work->m_ctrl.info1.frame;

    se1 = ( ( work->param.index % 4 ) * 2 ) + 0xA0;
    se2 = ( ( work->param.index % 4 ) * 2 ) + 0xA1;

    if ( motion == 1 )
    {
        if ( frame == 22 )
        {
            GM_SeSet( &work->control.mov, se2 );
        }
        else if ( frame == 11 )
        {
            GM_SeSet( &work->control.mov, se1 );
        }
    }
    else if ( motion == 2 )
    {
        if ( frame == 16 )
        {
            GM_SeSet( &work->control.mov, se2 );
        }
        else if ( frame == 8 )
        {
            GM_SeSet( &work->control.mov, se1 );
        }
    }
}

static void PutBreath( Work *work )
{
    int frame;

    if ( ZAKO19Command.alert_mode == 1 ) return;
    if ( !( work->control.map->index & GM_PlayerMap ) ) return;

    if ( work->act.motion2 == 20 )
    {
        if ( work->m_ctrl.info2.frame == 31 )
        {
            AN_Breath( &work->body.objs->objs[ 6 ].world );
        }
    }
    else if ( work->act.motion2 == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 15 || frame == 35 || frame == 50 || frame == 60 ||
             frame == 70 || frame == 74 || frame == 78 )
        {
            AN_Breath( &work->body.objs->objs[ 6 ].world );
        }
    }
    else if ( work->act.motion2 == 19 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 30  || frame == 40 || frame == 50 || frame == 60 ||
             frame == 70  || frame == 80 || frame == 90 || frame == 95 ||
             frame == 100 || frame == 105 )
        {
            AN_Breath( &work->body.objs->objs[ 6 ].world );
        }
    }
    else
    {
        if ( ( GV_Time % 64 ) == ( work->param.index * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[ 6 ].world );
        }
    }
}

static void PutLaserSight( Work *work )
{
    if ( work->vision.pad != 2 ) return;
    NewLSight( &GM_PlayerPosition, &work->control.mov, MAKE_RGB( 143, 0, 0 ) );
}

static void PutBullet( Work *work )
{
    SVECTOR rot;
    MATRIX bullet_pos;
    MATRIX *world;
    int flag;

    rot = DG_ZeroVector;
    rot.vz = GV_RandU( 128 );

    world = &work->body.objs->objs[ 4 ].world;
    DG_SetPos( world );
    DG_MovePos( &BulletPos );
    DG_RotatePos( &rot );
    rot.vx = GV_RandS( 16 ) + 1024;
    rot.vz = 0;
    DG_RotatePos( &rot );
    ReadRotMatrix( &bullet_pos );

    if ( GV_Time % 4 )
    {
        flag = BULLET_RECOILSPARK;
        NewBulletEx( flag, &bullet_pos, ENEMY_SIDE, 1, 0, 10, work->param.damage, 10000, 750 );
    }
    else
    {
        flag = BULLET_RECOILSPARK | BULLET_NO_HZD;
        NewBulletEx( flag, &bullet_pos, ENEMY_SIDE, 1, 0, 10, work->param.damage, 10000, 750 );
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );
    AN_BulletSmoke( world, 0 );
    AN_FamasFlash( &bullet_pos );

    ZAKO19_ClearPutChar( work, PutBullet );
}

/*---------------------------------------------------------------------------*/

int ZAKO19_SetPutChar( Work *work, int index )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putchar[ i ] == NULL )
        {
            work->putchar[ i ] = PutChars[ index ];
            return 1;
        }
    }

    return 0;
}

int ZAKO19_ClearPutChar( Work *work, void *func )
{
    int i;
    
    for ( i = 0; i < 8; i++ )
    {
        if ( work->putchar[ i ] == func )
        {
            work->putchar[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

void ZAKO19_ExecPutChars( Work *work )
{
    int i;
    void ( *func )( Work * );

    for ( i = 0; i < 8; i++ )
    {
        func = work->putchar[ i ];
        if ( func != NULL ) func( work );
    }
}
