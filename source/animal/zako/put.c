#include "zako.h"

#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "game/item.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

extern void *AN_Breath( MATRIX *world );
extern void *AN_HeadMark( MATRIX* world, int mark );
extern void *AN_PunchFog( SVECTOR *pos );
extern void *AN_Sleep( SVECTOR *pos );

/*---------------------------------------------------------------------------*/

static void PutFootNoise( Work *work );
static void PutBreath( Work *work );
static void PutSightLine( Work *work );
static void GunShoot( Work *work );

static int UnsetPutChar( Work *work, PUTCHAR putchar );

static SVECTOR BloodPos = {0, 0, 100};
static SVECTOR BloodRot = {-1024, 0, 0};

static SVECTOR DustPos = {0, 0, 100};
static SVECTOR DustRot = {-1024, 0, 0};

static char *ItemText[] = {
    "RATION",
    "SOCOM/BULLET * 12",
    "FA-MAS/BULLET * 25"
};

static void *PutChars[] = {
    PutFootNoise,
    PutBreath,
    PutSightLine,
    GunShoot
};

static SVECTOR BulletPos = {5, -500, 80};
static SVECTOR BulletRot = {1024, 0, 0};

/*---------------------------------------------------------------------------*/

void ZAKO_PutBlood( Work *work, int unit, int count )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ unit ].world );
    DG_MovePos( &BloodPos );
    DG_RotatePos( &BloodRot );
    ReadRotMatrix( &world );
    NewBlood( &world, count );
}

void ZAKO_PutDust( Work *work )
{
    MATRIX world;
    SVECTOR pos;

    DG_SetPos( &work->body.objs->objs[ 1 ].world );
    DG_MovePos( &DustPos );
    DG_RotatePos( &DustRot );
    ReadRotMatrix( &world );
    DG_COPY_VEC( &pos, (VECTOR *)world.t );
    AN_PunchFog( &pos );
}

void ZAKO_PutItem( Work *work, int type )
{
    SVECTOR step;
    ITEM_INFO info;
    SVECTOR *pos;

    step = work->act.field_0C;
    pos = &work->control.mov;

    switch ( type )
    {
    case 0:
    case 1:
        info.message = ItemText[ 0 ];
        info.type = 4;
        info.id = IT_Ration;
        info.num = 1;
        break;
    case 2:
    case 3:
        info.message = ItemText[ 1 ];
        info.type = 2;
        info.id = WP_Socom;
        info.num = 12;
        break;
    }

    info.time = 900;
    NewItemPut( pos, &step, &info );
}

void ZAKO_PutMark( Work *work, int mark )
{
    if ( work->control.map->index == GM_PlayerMap )
    {
        AN_HeadMark( &work->body.objs->objs[ 6 ].world, mark );
    }
}

/*---------------------------------------------------------------------------*/

static void PutFootNoise( Work *work )
{
    int action, frame, l, r;

    action = work->act.motion1;
    frame = work->m_ctrl.info1.frame;
    l = 160 + ( work->param.index % 4 ) * 2;
    r = 160 + ( work->param.index % 4 ) * 2 + 1;

    if ( action == 1 )
    {
        if ( frame == 22 )
        {
            GM_SeSet( &work->control.mov, r );
        }
        else if ( frame == 11 )
        {
            GM_SeSet( &work->control.mov, l );
        }
    }
    else if ( action == 2 )
    {
        if ( frame == 16 )
        {
            GM_SeSet( &work->control.mov, r );
        }
        else if ( frame == 8 )
        {
            GM_SeSet( &work->control.mov, l );
        }
    }
}

static void PutBreath( Work *work )
{
    if ( ZAKOCommand.field_1C != 1
         && work->control.map->index == GM_PlayerMap
         && ( GV_Time % 64 ) == ( work->param.index * 16 ) )
    {
        AN_Breath( &work->body.objs->objs[ 6 ].world );
    }
}

static void PutSightLine( Work *work )
{
    if ( work->vision.pad == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, MAKE_RGB( 143, 0, 0 ) );
    }
}

static void GunShoot( Work *work )
{
    MATRIX world;
    MATRIX *weapon;

    weapon = &work->body.objs->objs[ 4 ].world;
    DG_SetPos( weapon );
    DG_MovePos( &BulletPos );
    DG_RotatePos( &BulletRot );
    ReadRotMatrix( &world );

    NewBulletEx( BULLET_RECOILSPARK, &world, ENEMY_SIDE, 1, 0, 10, work->param.damage, 10000, 750 );
    GM_SeSet( &work->control.mov, SE_ENEMY_SHOT );

    AN_BulletSmoke( weapon, 0 );
    AN_FamasFlash( &world );

    UnsetPutChar( work, GunShoot );
}

/*---------------------------------------------------------------------------*/

int ZAKO_SetPutChar( Work *work, int index )
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

/*---------------------------------------------------------------------------*/

static int UnsetPutChar( Work *work, PUTCHAR putchar )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putchar[ i ] == putchar )
        {
            work->putchar[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void ZAKO_ExecPutChars( Work *work )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putchar[ i ] != NULL )
        {
            ( work->putchar[ i ] )( work );
        }
    }
}
