#include "enemy/enemy.h"

#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "game/item.h"
#include "okajima/blood.h"

/*---------------------------------------------------------------------------*/

extern ENEMY_COMMAND EnemyCommand;

extern void *AN_Breath( MATRIX *world );
extern void *AN_HeadMark( MATRIX* world, int mark );
extern void *AN_PunchFog( SVECTOR *pos );

/*---------------------------------------------------------------------------*/

static void PutSound( WatcherWork *work );
static void PutBreath( WatcherWork *work );
static void PutSightLine( WatcherWork *work );
static void GunShoot( WatcherWork *work );

static int UnsetPutChar( WatcherWork *work, void *putchar );

static SVECTOR s07a_dword_800C369C = {0, 0, 100};
static SVECTOR s07a_dword_800C36A4 = {-1024, 0, 0};
static SVECTOR s07a_dword_800C36AC = {0, 0, 100};
static SVECTOR s07a_dword_800C36B4 = {-1024, 0, 0};

static char *s07a_dword_800C36BC[] = {
    "RATION x 1",
    "SOCOM x 12",
    "FAMAS x 15"
};

static void *s07a_dword_800C36C8[] = {
    PutSound,
    PutBreath,
    PutSightLine,
    GunShoot
};

static SVECTOR s07a_dword_800C36D8 = {5, -500, 80};

/*---------------------------------------------------------------------------*/

void MERYL_PutBlood( WatcherWork *work, int unit, int count )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ unit ].world );
    DG_MovePos( &s07a_dword_800C369C );
    DG_RotatePos( &s07a_dword_800C36A4 );
    ReadRotMatrix( &world );
    NewBlood( &world, count );
}

void MERYL_PutFog(WatcherWork *work )
{
    MATRIX world;
    SVECTOR pos;

    DG_SetPos( &work->body.objs->objs[ 1 ].world );
    DG_MovePos( &s07a_dword_800C36AC );
    DG_RotatePos( &s07a_dword_800C36B4 );
    ReadRotMatrix( &world );
    DG_COPY_VEC( &pos, (VECTOR *)world.t );
    AN_PunchFog( &pos );
}

void MERYL_PutItem( WatcherWork *work )
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

    switch ( rand )
    {
    case 0:
    case 1:
        item.type   = 4;
        item.id     = IT_Ration;
        item.num = 1;
        item.message  = s07a_dword_800C36BC[0];
        break;
    case 2:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = s07a_dword_800C36BC[0];
        }
        else
        {
            //Socom bullets
            item.type = 2;
            item.id = WP_Socom;
            item.num = 12;
            item.message  = s07a_dword_800C36BC[1];
        }
        break;
    case 3:
        //famas
        if ( GM_FamasFlag < 0  )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = s07a_dword_800C36BC[0];
        }
        else
        {
            item.id     = WP_Famas;
            item.type   = 2;
            item.num = 25;
            item.message  = s07a_dword_800C36BC[2];
        }
        break;
    }
    item.time = 900;
    NewItemPut( &ctrl->mov, &svec, &item );
}

void MERYL_PutMark( WatcherWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        COM_CallBikkuriSe( &work->control.mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor( work->mark );
    }

    work->mark = AN_HeadMark( mat , mark ) ;
    work->mark_time = 30;
}

/*---------------------------------------------------------------------------*/

static int s07a_meryl_unk_800D9A28( SVECTOR *pos )
{
    if ( ( (unsigned short)pos->vx - 0xFA0 >= 0x157Du ) || ( pos->vz < -0x5014 ) || (pos->vz >= -0x251B ) )
    {
        return 0;
    }

    return 1;
}

static void PutSound( WatcherWork *work )
{
    int a3;
    int a2;

    if ( s07a_meryl_unk_800D9A28( &work->control.mov ) && s07a_meryl_unk_800D9A28( &GM_PlayerPosition ) )
    {
        return;
    }

    a3 = work->unknown.last_set;
    a2 = work->m_ctrl.info1.frame;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSetMode( &work->control.mov, 0xB8, GM_SEMODE_REAL );
        }
        else if ( a2 == 11 )
        {
            GM_SeSetMode( &work->control.mov, 0xB7, GM_SEMODE_REAL );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSetMode( &work->control.mov, 0xB8, GM_SEMODE_REAL );
        }
        else if ( a2 == 8 )
        {
            GM_SeSetMode( &work->control.mov, 0xB7, GM_SEMODE_REAL );
        }
    }
}

static void PutBreath( WatcherWork *work )
{
    int frame;
    if ( EnemyCommand.mode == TOP_COMM_ALERT )
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
        if ( ( GV_Time % 64 ) == ( work->field_B78 * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
}

static void PutSightLine( WatcherWork *work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

static void GunShoot( WatcherWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vx = GV_RandS( 16 );
    svec.vz = GV_RandU( 128 );

    mat = &work->body.objs->objs[4].world;
    DG_SetPos( mat );
    DG_MovePos( &s07a_dword_800C36D8 );
    DG_RotatePos( &svec );
    ReadRotMatrix( &local_mat );

    GM_SeSet( &work->control.mov, SE_ENEMY_SHOT );
    AN_BulletSmoke(mat, 0);
    AN_FamasFlash(&local_mat);

    UnsetPutChar( work, GunShoot );
}

/*---------------------------------------------------------------------------*/

int MERYL_SetPutChar( WatcherWork *work, int index )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = s07a_dword_800C36C8[ index ];
            return 1;
        }
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

static int UnsetPutChar( WatcherWork *work, void *putchar )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == putchar )
        {
            work->field_B00[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void MERYL_ExecPutChar( WatcherWork *work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] != NULL )
        {
            PUTFUNC func = work->field_B00[ i ];
            func( work );
        }
    }
}
