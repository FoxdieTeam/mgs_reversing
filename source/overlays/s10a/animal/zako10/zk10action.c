#include "zako10.h"

extern ZAKO10_COMMAND Zako10Command;

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/bullet.h"

extern int ZAKO10_EYE_LENGTH;

extern void  NewLSight( SVECTOR *from, SVECTOR *to, int color );
extern void  AN_Breath( MATRIX * );
extern void  AN_BulletSmoke( MATRIX *, int );
extern void  AN_FamasFlash( MATRIX * );

extern int  Zako10CheckDamage( Zako10Work *work );
extern int  Zako10CheckPad( Zako10Work *work );
extern int  Zako10CheckDir( int dir, int dist );
extern void Zako10ReviseReadyGun( Zako10Work *work );

void Zako10ActStandStill( Zako10Work *work, int time );
void s10a_zk10action_800CA7E8( Zako10Work *work, int time );
void s10a_zk10action_800CACFC( Zako10Work *work, int time );
void s10a_zk10action_800CADAC( Zako10Work *work, int time );
void s10a_zk10action_800CADB4( Zako10Work *work, int time );
void s10a_zk10action_800CADBC( Zako10Work *work, int time );

void ZAKO10_PutSound( Zako10Work *work );
void ZAKO10_PutBreath( Zako10Work *work, int arg1 );
void ZAKO10_PutLSight( Zako10Work *work );
void ZAKO10_PutBullet( Zako10Work *work );
int  ZAKO10_SetPutChar( Zako10Work *work, int idx );
int  ZAKO10_ClearPutChar( Zako10Work *work, void *func );

short Zako10ActTable[54] =
{
    0, 1, 1, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 0
};

void *Zako10PutFuncList[4] =
{
    ZAKO10_PutSound,
    ZAKO10_PutBreath,
    ZAKO10_PutLSight,
    ZAKO10_PutBullet
};

SVECTOR Zako10BulletOffset = { 5, -500, 80, 0 };

/*** Inlines *****************************************************************/

static inline void UnsetMode( Zako10Work *work )
{
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), Zako10ActTable[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( Zako10Work *work, int n_action, int interp )
{
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), Zako10ActTable[ n_action ], 0, interp );
}

/*****************************************************************************/

void Zako10ActStandStill(Zako10Work* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( Zako10Command.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO10_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( Zako10CheckDamage( work ) || Zako10CheckPad( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetZako10Mode( work, s10a_zk10action_800CA7E8 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir =work->control.rot.vy;
}

void s10a_zk10action_800CA7E8( Zako10Work* work, int time )
{
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int field_8E0;
    int dir;
    SVECTOR* svec;

    SetTargetClass( work->target, TARGET_FLAG );

    if ( Zako10Command.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO10_EYE_LENGTH ;

    if ( Zako10CheckDamage( work ) || Zako10CheckPad( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->unknown.last_set;
    svec = work->control.vecs;

    if ( (work->pad.mode & 0x1) && ( work->unknown.last_set != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->n_touches;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2( &ctrl->vecs[1] );
                if ( GV_DiffDirAbs( dir, tmp ) < GV_DiffDirAbs( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetZako10Mode( work, Zako10ActStandStill);
        UnsetMode( work ) ;
        return;
    }


    switch ( Zako10CheckDir( dir, dist ) )
    {
    case 1:
        dir = (dist - 1024) & 0xFFF;
        break;
    case 2:
        dir = (dist + 1024) & 0xFFF;
        break;
    }


    if ( !work->body.objs->bound_mode )
    {
        do { ctrl->rot.vy = dir; } while (0); //probably a macro
    }
    ctrl->turn.vy = dir;
    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 100;
    }

    ctrl->step.vx = (interval * rsin( dir )) / 4096;

    ctrl->step.vz = (interval * rcos( dir )) / 4096;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CAA80( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAA88( Zako10Work *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO10_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( Zako10CheckDamage( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetZako10Mode( work, Zako10ActStandStill );
        return;
    }

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CAB70( Zako10Work *work, int time )
{
}

void Zako10ActReadyGun( Zako10Work* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO10_EYE_LENGTH ;
    press = work->pad.press;

    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, ACTION3, ACTINTERP ) ;
        }
        else
        {
            SetAction( work, ACTION5, ACTINTERP );
        }
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
        GM_SeSetMode( &work->control.mov, 0xB2, GM_SEMODE_BOMB ) ;
    }

    Zako10ReviseReadyGun( work );
    if ( Zako10CheckDamage( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetZako10Mode( work, Zako10ActStandStill ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetZako10ModeFields( work, s10a_zk10action_800CACFC ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetZako10Mode( work, s10a_zk10action_800CADAC ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetZako10ModeFields( work, s10a_zk10action_800CADB4 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetZako10ModeFields( work, s10a_zk10action_800CADBC ) ;
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CACFC( Zako10Work* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO10_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ZAKO10_SetPutChar( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    Zako10ReviseReadyGun( work );

    if ( Zako10CheckDamage( work ) )
    {
        return ;
    }

    SetZako10ModeFields( work, Zako10ActReadyGun );
}

void s10a_zk10action_800CADAC( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CADB4( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CADBC( Zako10Work *work, int time )
{
}

void Zako10ActionUpdate( Zako10Work *work )
{
    short       v0;
    int         time_prev;
    ZAKO10ACTION  action;
    CONTROL    *ctrl;
    WatcherUnk *unk;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    unk = &work->unknown;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    ctrl   = &work->control;

    work->field_C34  = 0;

    ctrl->height = ( work->body.height * work->scale ) / 4096 ;
    ctrl->hzd_height = ctrl->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = Zako10ActStandStill;
        work->action = Zako10ActStandStill;
    }

    action( work, time_prev );
    action = work->action2;

    if ( action )
    {
        time_prev = work->time2;
        work->time2++;
        action( work, time_prev );
    }

    if ( !unk->field_1E )
    {
        ctrl->r_sphere = GV_NearExp2( ctrl->r_sphere, unk->field_1C );
    }
    else
    {
        ctrl->r_sphere = -1;
    }

    if ( work->target->class & TARGET_POWER )
    {
        work->hom->flag = TRUE;
    }
    else
    {
        work->hom->flag = FALSE;
    }

    if ( unk->field_04 < 0 && ctrl->grounded )
    {
        unk->field_04 = 0;
    }

    v0 = unk->field_04 - 16;
    unk->field_04 = v0;
    ctrl->step.vy = v0;

    if ( work->mark_time > 0 )
    {
        work->mark_time--;
    }
}

void s10a_zk10action_800CAF50( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF58( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF60( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF68( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF70( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF78( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF80( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF88( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF90( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAF98( Zako10Work *work, int time )
{
}

void s10a_zk10action_800CAFA0( Zako10Work *work, int time )
{
}

void ZAKO10_PutMark( Zako10Work *work, int mark )
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

void ZAKO10_PutSound( Zako10Work* work )
{
    int a1, a3;
    int a2;
    int v1;

    a3 = work->unknown.last_set;
    a2 = work->m_ctrl.info1.frame;

    v1 = ( ( work->param.index % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->param.index % 4 ) * 2 ) + 0xA1;

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

void ZAKO10_PutBreath( Zako10Work *work, int arg1 )
{
    int frame;
    if ( Zako10Command.mode == TOP_COMM_ALERT )
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
        if ( ( GV_Time % 64 ) == ( work->param.index * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
}

void ZAKO10_PutLSight( Zako10Work* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

void ZAKO10_PutBullet( Zako10Work *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vx = GV_RandS( 16 );
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos( mat );
    DG_MovePos( &Zako10BulletOffset );
    DG_RotatePos( &svec );
    ReadRotMatrix( &local_mat );

    if ( GV_Time & 3 )
    {
        NewBulletEnemy( &local_mat, ENEMY_SIDE, 1, 0, 1 );
    }
    else
    {
        NewBulletEnemy( &local_mat, ENEMY_SIDE, 1, 0, 0 );
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );
    AN_BulletSmoke( mat, 0 );
    AN_FamasFlash( &local_mat );
    ZAKO10_ClearPutChar( work, ZAKO10_PutBullet );
}

int ZAKO10_SetPutChar( Zako10Work *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = Zako10PutFuncList[ idx ];
            return 1;
        }
    }
    return 0;
}

int ZAKO10_ClearPutChar( Zako10Work *work, void *func )
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

void ZAKO10_ExecPutChar( Zako10Work* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            ZAKO10PUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}
