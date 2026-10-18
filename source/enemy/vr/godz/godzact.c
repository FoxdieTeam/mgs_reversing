// (VR only) this file is empty in the main executable build
// WORK IN PROGRESS, not linked anywhere yet: the action (800C4DB8..800C7FD0) part of the vcd_n05 godzilla soldier. This is the s10a zako10 code
// (renamed, GodzWork layout) and does NOT match the vcd_n05 bytes yet (godzila.c, godzene.c and godzcom.c are done, the
// vcd_n05 asm chunks 800C4308 (check + action), 800C9E84 (think) are still asm). Orig functions and what differs:
// see the commit message / report.
#ifdef VR_EXE
#include "godzila.h"

extern GODZ_COMMAND GodzCommand;

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/bullet.h"

extern int GODZ_EYE_LENGTH;

extern void  NewLSight( SVECTOR *from, SVECTOR *to, int color );
extern void  AN_Breath( MATRIX * );
extern void  AN_BulletSmoke( MATRIX *, int );
extern void  AN_FamasFlash( MATRIX * );

extern int  GodzCheckDamage( GodzWork *work );
extern int  GodzCheckPad( GodzWork *work );
extern int  GodzCheckDir( int dir, int dist );
extern void GodzReviseReadyGun( GodzWork *work );

void GodzActStandStill( GodzWork *work, int time );
void s10a_zk10action_800CA7E8( GodzWork *work, int time );
void s10a_zk10action_800CACFC( GodzWork *work, int time );
void s10a_zk10action_800CADAC( GodzWork *work, int time );
void s10a_zk10action_800CADB4( GodzWork *work, int time );
void s10a_zk10action_800CADBC( GodzWork *work, int time );

void GODZ_PutSound( GodzWork *work );
void GODZ_PutBreath( GodzWork *work, int arg1 );
void GODZ_PutLSight( GodzWork *work );
void GODZ_PutBullet( GodzWork *work );
int  GODZ_SetPutChar( GodzWork *work, int idx );
int  GODZ_ClearPutChar( GodzWork *work, void *func );

short GodzActTable[54] =
{
    0, 1, 1, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 0
};

void *GodzPutFuncList[4] =
{
    GODZ_PutSound,
    GODZ_PutBreath,
    GODZ_PutLSight,
    GODZ_PutBullet
};

SVECTOR GodzBulletOffset = { 5, -500, 80, 0 };

/*** Inlines *****************************************************************/

static inline void UnsetMode( GodzWork *work )
{
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( GodzWork *work, int n_action, int interp )
{
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), GodzActTable[ n_action ], 0, interp );
}

/*****************************************************************************/

void GodzActStandStill(GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->act_status |= 1;

    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        work->targets[0]->class |= TARGET_C4 ;
    }

    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( GodzCheckDamage( work ) || GodzCheckPad( work ) )
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
            SetGodzMode( work, s10a_zk10action_800CA7E8 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir =work->control.rot.vy;
}

void s10a_zk10action_800CA7E8( GodzWork* work, int time )
{
    int x, z;
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int field_8E0;
    int dir;
    SVECTOR* svec;

    SetTargetClass( work->targets[0], TARGET_FLAG );

    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        work->targets[0]->class |= TARGET_C4 ;
    }

    work->vision.length = GODZ_EYE_LENGTH ;

    if ( GodzCheckDamage( work ) || GodzCheckPad( work ) )
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
        SetGodzMode( work, GodzActStandStill);
        UnsetMode( work ) ;
        return;
    }


    switch ( GodzCheckDir( dir, dist ) )
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

    x = interval * rsin( dir );

    if ( x < 0 )
    {
        x += 0xFFF;
    }

    ctrl->step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->step.vz = z >> 12;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CAA80( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAA88( GodzWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetGodzMode( work, GodzActStandStill );
        return;
    }

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CAB70( GodzWork *work, int time )
{
}

void GodzActReadyGun( GodzWork* work, int time )
{
    int press;
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
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

    GodzReviseReadyGun( work );
    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetGodzMode( work, GodzActStandStill ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetGodzModeFields( work, s10a_zk10action_800CACFC ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetGodzMode( work, s10a_zk10action_800CADAC ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetGodzModeFields( work, s10a_zk10action_800CADB4 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetGodzModeFields( work, s10a_zk10action_800CADBC ) ;
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void s10a_zk10action_800CACFC( GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        GODZ_SetPutChar( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    GodzReviseReadyGun( work );

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    SetGodzModeFields( work, GodzActReadyGun );
}

void s10a_zk10action_800CADAC( GodzWork *work, int time )
{
}

void s10a_zk10action_800CADB4( GodzWork *work, int time )
{
}

void s10a_zk10action_800CADBC( GodzWork *work, int time )
{
}

void GodzActionUpdate( GodzWork *work )
{
    short       v0;
    int         time_prev;
    GODZACTION  action;
    CONTROL    *ctrl;
    WatcherUnk *unk;

    work->trigger = 0;
    work->vision.length = 0;
    work->targets[0]->class = TARGET_AVAIL;

    unk = &work->unknown;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    ctrl   = &work->control;

    work->field_C44  = 0;

    ctrl->height = ( work->body.height * work->scale ) / 4096 ;
    ctrl->hzd_height = ctrl->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = GodzActStandStill;
        work->action = GodzActStandStill;
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

    if ( work->targets[0]->class & TARGET_POWER )
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

void s10a_zk10action_800CAF50( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF58( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF60( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF68( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF70( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF78( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF80( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF88( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF90( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAF98( GodzWork *work, int time )
{
}

void s10a_zk10action_800CAFA0( GodzWork *work, int time )
{
}

void GODZ_PutMark( GodzWork *work, int mark )
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

void GODZ_PutSound( GodzWork* work )
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

void GODZ_PutBreath( GodzWork *work, int arg1 )
{
    int frame;
    if ( GodzCommand.mode == TOP_COMM_ALERT )
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

void GODZ_PutLSight( GodzWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

void GODZ_PutBullet( GodzWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vx = GV_RandS( 16 );
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos( mat );
    DG_MovePos( &GodzBulletOffset );
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
    GODZ_ClearPutChar( work, GODZ_PutBullet );
}

int GODZ_SetPutChar( GodzWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == NULL )
        {
            work->field_B10[ i ] = GodzPutFuncList[ idx ];
            return 1;
        }
    }
    return 0;
}

int GODZ_ClearPutChar( GodzWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == func )
        {
            work->field_B10[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void GODZ_ExecPutChar( GodzWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[i] )
        {
            GODZPUTFUNC func = work->field_B10[i];
            func( work );
        }
    }
}
#endif
