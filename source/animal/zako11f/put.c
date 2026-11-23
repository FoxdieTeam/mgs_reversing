#include "zako.h"

#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "game/item.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

extern void *AN_Breath( MATRIX *world );
extern void *AN_PunchFog( SVECTOR *pos );
extern void *AN_HeadMark( MATRIX* world, int mark );

/*---------------------------------------------------------------------------*/

static void PutSound( Work *work );
static void PutBreath( Work *work );
static void PutLaserSight( Work *work );
static void PutBullet( Work *work );
static void PutBulletEx( Work *work );

static SVECTOR s11i_800C33B4 = {0, 0, 100};
static SVECTOR s11i_800C33BC = {-1024, 0, 0};
static SVECTOR s11i_800C33C4 = {0, 0, 100};
static SVECTOR s11i_800C33CC = {-1024, 0, 0};

static char *ItemText[] = {
    "RATION",
    "SOCOM/BULLET * 12",
    "FA-MAS/BULLET * 25"
};

static void *PutChars[] = {
    PutSound,
    PutBreath,
    PutLaserSight,
    PutBullet,
    PutBulletEx
};

static SVECTOR s11i_800C33F4 = {5, -500, 80, 0};
static SVECTOR s11i_800C33FC = {5, -500, 80, 0};

/*---------------------------------------------------------------------------*/

void ZAKO11F_PutBlood(Work *work, int unit, int count)
{
    MATRIX world;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&s11i_800C33B4);
    DG_RotatePos(&s11i_800C33BC);
    ReadRotMatrix(&world);
    NewBlood(&world, count);
}

void ZAKO11F_PutFog(Work *work)
{
    MATRIX  world;
    SVECTOR pos;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s11i_800C33C4 );
    DG_RotatePos( &s11i_800C33CC );
    ReadRotMatrix( &world );

    pos.vx = world.t[ 0 ];
    pos.vy = world.t[ 1 ];
    pos.vz = world.t[ 2 ];

    AN_PunchFog( &pos );
}

void ZAKO11F_PutItem( Work *work )
{
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    ITEM_INFO item;

    svec = work->act.field_0C;
    rand = 10;
    ctrl = &work->control;
    svec.vx += GV_RandU( rand );
    svec.vy += 100;
    rand = GV_RandU( rand );
    svec.vz += rand;
    rand = GV_RandU( 4 );

    switch ( rand )
    {
    case 0:
    case 1:
        item.type   = 4;
        item.id     = IT_Ration;
        item.num = 1;
        item.message  = ItemText[0];
        break;
    case 2:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = ItemText[0];
        }
        else
        {
            //Socom bullets
            item.type = 2;
            item.id = WP_Socom;
            item.num = 12;
            item.message  = ItemText[1];
        }
        break;
    case 3:
        //famas
        if ( GM_FamasFlag < 0  )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = ItemText[0];
        }
        else
        {
            item.id     = WP_Famas;
            item.type   = 2;
            item.num = 25;
            item.message  = ItemText[2];
        }
        break;
    }
    item.time = 900;
    NewItemPut( &ctrl->mov, &svec, &item );
}

void ZAKO11F_PutMark( Work *work, int mark )
{
    MATRIX *world;

    if (!(work->control.map->index & GM_PlayerMap))
    {
        return;
    }

    world = &work->body.objs->objs[6].world;

    if (mark == 0)
    {
        GM_SeSet(&work->control.mov, SE_EXCLAMATION);
    }

    if (work->mark_time != 0)
    {
        GV_DestroyActor(work->mark);
    }

    work->mark = AN_HeadMark(world, mark);
    work->mark_time = 30;
}

/*---------------------------------------------------------------------------*/

static void PutSound( Work *work )
{
    int action;
    int frame;
    int step1, step2;

    action = work->act.motion1;
    frame = work->m_ctrl.info1.frame;
    step1 = 160 + (work->param.index % 4) * 2;
    step2 = 160 + (work->param.index % 4) * 2 + 1;

    if (action == 1)
    {
        if (frame == 22)
        {
            GM_SeSet(&work->control.mov, step2);
        }
        else if (frame == 11)
        {
            GM_SeSet(&work->control.mov, step1);
        }
    }
    else if (action == 2)
    {
        if (frame == 16)
        {
            GM_SeSet(&work->control.mov, step2);
        }
        else if (frame == 8)
        {
            GM_SeSet(&work->control.mov, step1);
        }
    }
}

static void PutBreath( Work *work )
{
    int frame;

    if ( ZAKO11FCommand.alert_mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( work->act.motion2 == 20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->act.motion2 == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->act.motion2 == 19 )
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
        if ( ( GV_Time % 64 ) == ( work->param.index * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
}

static void PutLaserSight( Work *work )
{
    if ( work->vision.pad == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

static void PutBullet( Work *work )
{
    SVECTOR rot;
    MATRIX  local;
    MATRIX *world;

    rot = DG_ZeroVector;
    rot.vz = GV_RandU( 128 );

    world = &work->body.objs->objs[4].world;

    DG_SetPos( world );
    DG_MovePos( &s11i_800C33F4 );
    DG_RotatePos( &rot );

    rot.vx = GV_RandS( 16 ) + 1024;
    rot.vz = 0;

    DG_RotatePos( &rot );
    ReadRotMatrix( &local );

    if ( GV_Time & 3 )
    {
        NewBulletEx(BULLET_RECOILSPARK, &local, ENEMY_SIDE, 1, 0, 0xA, work->param.damage, 10000, 750);
    }
    else
    {
        NewBulletEx(BULLET_RECOILSPARK | BULLET_NO_HZD, &local, ENEMY_SIDE, 1, 0, 0xA, work->param.damage, 10000, 750);
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );

    AN_BulletSmoke( world, 0 );
    AN_FamasFlash( &local );

    ZAKO11F_ClearPutChar( work, PutBullet );
}

static void PutBulletEx( Work *work )
{
    SVECTOR rot;
    MATRIX  local;
    MATRIX *world;

    rot.vx = 1024;
    rot.vy = 0;
    rot.vz = GV_RandS( 16 );

    world = &work->body.objs->objs[4].world;

    DG_SetPos( world );
    DG_MovePos( &s11i_800C33FC );
    DG_RotatePos( &rot );
    ReadRotMatrix( &local );

    NewBulletEx(BULLET_FLASH | BULLET_RECOILSPARK | BULLET_BLAST, &local, ENEMY_SIDE, 1, 0, 0x1E, work->param.damage2, 40000, 1500);

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );

    AN_BulletSmoke( world, 0 );
    AN_FamasFlash( &local );

    ZAKO11F_ClearPutChar( work, PutBulletEx );
}

/*---------------------------------------------------------------------------*/

int ZAKO11F_SetPutChar( Work *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->putchar[ i ] == NULL )
        {
            work->putchar[ i ] = PutChars[ idx ];
            return 1;
        }
    }

    return 0;
}

int ZAKO11F_ClearPutChar( Work *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->putchar[ i ] == func )
        {
            work->putchar[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

void ZAKO11F_ExecPutChars( Work *work )
{
    int i;
    void ( *func )( Work * );

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->putchar[i] )
        {
            func = work->putchar[i];
            func( work );
        }
    }
}
