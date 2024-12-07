#include "meryl72.h"


/****Inlines**********************************************************************************************/
static inline void SetAction( Meryl72Work *work, int n_action, int interp )
{
    extern short    ActTable_800C3310[];
    work->f8BC.field_18 = n_action;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3310[n_action], 0, interp );
}

static inline void UnsetMode( Meryl72Work *work )
{
    extern short    ActTable_800C3310[];
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3310[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
/*********************************************************************************************************/

extern int GM_GameStatus;
extern CONTROL *GM_PlayerControl_800AB9F4 ;
extern SVECTOR GM_PlayerPosition_800ABA10 ;

extern void s07c_meryl72_unk1_800C86EC( Meryl72Work* work, int time ) ;

void ActStandStill_800C8580( Meryl72Work* work, int time )
{
    work->act_status = 1;
    work->vision.length = 4000;

    if ( time == 0 )
    {
        SetAction( work, 0, ACTINTERP ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &( work->rots[ 16 ] ) );  
    }
    
    if ( CheckDamage_800C7F6C( work ) || CheckPad_800C8308( work ) )
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
            SetMode( work, s07c_meryl72_unk1_800C86EC );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = work->control.rot.vy;
    work->target->class |= 0x9E;
}

void s07c_meryl72_unk1_800C86EC( Meryl72Work* work, int time )
{
    int s0;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int dir;
    int cur_act;
    SVECTOR* svec;

    work->act_status = 1;
    work->vision.length = 4000;

    if ( CheckDamage_800C7F6C( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    if ( CheckPad_800C8308( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }
    
    dist = -1;
    dir = work->pad.dir;
    ctrl = &(work->control );
    cur_act = work->f8BC.field_18;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.mode & 0x1) && ( cur_act != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP ) ;
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->field_58;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2( &ctrl->field_60_vecs_ary[1] );
                if ( GV_DiffDirAbs( dir, tmp ) < GV_DiffDirAbs( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetMode( work, ActStandStill_800C8580 );
        UnsetMode( work ) ;
        return;
    }


    switch ( s07c_meryl72_unk1_800C7FCC( dir, dist ) )
    {
    case 1:
        dir = ( dist - 1024 ) & 0xFFF;
        break;
    case 2:
        dir = ( dist + 1024 ) & 0xFFF;
        break;
    }

    if ( !work->body.objs->bound_mode )
    {
        ctrl->rot.vy   = dir;
    }

    ctrl->turn.vy = dir;
    work->vision.facedir = GV_NearExp4P( work->vision.facedir, work->control.rot.vy );
    work->target->class |= TARGET_FLAG;
}

extern void s07c_meryl72_unk1_800CA0EC( Meryl72Work* work, int time ) ;

void s07c_meryl72_unk1_800C88EC( Meryl72Work* work, int time )
{
    if ( time == 0 )
    {
        work->f8BC.field_14 = 4;
        SetAction( work, ACTION41, 4 );
    }

    if ( !( CheckDamage_800C7F6C( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetMode( work, s07c_meryl72_unk1_800CA0EC );
    }
}

void s07c_meryl72_unk1_800C8970( Meryl72Work* work, int time )
{
    work->act_status = 1 ;
    work->target->class |= TARGET_FLAG ;
    work->vision.length = 4000 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( CheckDamage_800C7F6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800C8580 ) ;
        return ;
    }

    work->control.turn.vy = work->sn_dir ;
}

void s07c_meryl72_unk1_800C8A30( Meryl72Work* work, int time )
{
    int dir;

    work->vision.length = 4000 ;
    work->act_status |= 9 ;

    if ( time == 0 )
    {
        GM_GameStatus |= STATE_PADRELEASE;
        SetAction( work, ACTION28, ACTINTERP );
    }

    if ( time == 1 )
    {
        dir = work->sn_dir;
        GM_PlayerControl_800AB9F4->turn.vy = ( dir + 0x800 ) & 0xFFF ;
    }

    if ( time == 98 )
    {
        GM_SeSet( &( work->control.mov ), 0x38 );
        if ( !work->fB94 )
        {
            GM_SeSet( &( work->control.mov ), 0xBD );
        }
        else
        {
            GM_SeSet( &( work->control.mov ), 0xC7 );
        }
    }
    
    if ( time == 101 && AttackForce_800C80DC( work, 0 ) )
    {
        if ( !work->fB94 )
        {
            GM_SeSet( &( work->control.mov ), 0xB0 );
        }
        else
        {
            GM_SeSet( &( work->control.mov ), 0xC8 );
        }
        if ( s07c_meryl72_unk1_800C829C( work ) )
        {
            ExecProc_800C7C58( work, 2 );
        }
    }

    if ( work->body.is_end )
    {
        work->fC08 = 3;
        GM_GameStatus &= ~STATE_PADRELEASE;
        SetMode( work, ActStandStill_800C8580 );
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
    }
}

void s07c_meryl72_unk1_800C8BC4( Meryl72Work* work, int time )
{
    work->vision.length = 4000 ;
    work->act_status |= 9 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION13, ACTINTERP );
    }

    if ( time == 30 )
    {
        GM_SeSetMode( &( work->control.mov ), 0xC1, 1 );
    }

    if ( work->body.is_end )
    {
        work->fC08 = 3;
        SetMode( work, ActStandStill_800C8580 );
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
    }
}

void s07c_meryl72_unk1_800C8C7C( Meryl72Work* work, int time )
{
    int local_time;
    
    work->vision.length = 4000 ;
    work->act_status |= 9 ;

    if ( time == 0 )
    {
        GM_GameStatus |= STATE_PADRELEASE;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time == 90 )
    {
        GM_CurrentItemId = -1;
        GM_SeSet( &( work->control.mov ), 0x14 );
    }

    if ( time == 95 )
    {
        int dir = work->sn_dir;
        GM_PlayerControl_800AB9F4->turn.vy = ( dir + 0x800 ) & 0xFFF ;
    }

    local_time = 95;

    if ( time == 95 )
    {
        SetAction( work, ACTION28, ACTINTERP );
    }

    if ( time == 193 )
    {
        GM_SeSet( &( work->control.mov ), 0x38 );
        if ( !work->fB94 )
        {
            GM_SeSet( &( work->control.mov ), 0xBD );
        }
        else
        {
            GM_SeSet( &( work->control.mov ), 0xC7 );
        }
    }

    if ( time == ( local_time + 101 ) && AttackForce_800C80DC( work, 0 ) )
    {        
        if ( !work->fB94 )
        {
            GM_SeSet( &( work->control.mov ), 0xB0 );
        }
        else
        {
            GM_SeSet( &( work->control.mov ), 0xC8 );
        }
        if ( s07c_meryl72_unk1_800C829C( work ) )
        {
            ExecProc_800C7C58( work, 2 );
        }
    }

    if ( local_time < time && work->body.is_end )
    {
        work->fC08 = 3;
        GM_GameStatus &= ~STATE_PADRELEASE;
        SetMode( work, ActStandStill_800C8580 );
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
    }
}

void s07c_meryl72_unk1_800C8E74( Meryl72Work* work, int time )
{
    work->vision.length = 4000 ;
    work->act_status |= 9 ;

    if ( time == 0 )
    {
        GM_GameStatus |= STATE_PADRELEASE;
        SetAction( work, ACTION28, ACTINTERP );
    }

    if ( time == 50 )
    {
        SetAction( work, ACTION29, ACTINTERP );
    }

    if ( time == 63 )
    {
        GM_SeSet( &( work->control.mov ), 0x38 );
        if ( !work->fB94 )
        {
            GM_SeSet( &( work->control.mov ), 0xBD );
        }
        else
        {
            GM_SeSet( &( work->control.mov ), 0xC7 );
        }
    }

    if ( time == 67 && AttackForce_800C80DC( work, 1 ) )
    {        
        GM_SeSet( &( work->control.mov ), 0x35 );
        if ( s07c_meryl72_unk1_800C829C( work ) )
        {
            ExecProc_800C7C58( work, 2 );
        }
    }

    if ( time > 0x32 && work->body.is_end )
    {
        work->fC08 = 3;
        GM_GameStatus &= ~STATE_PADRELEASE;
        SetMode( work, ActStandStill_800C8580 );
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
    }
}

void s07c_meryl72_unk1_800C9000( Meryl72Work* work, int time )
{

    int press = work->pad.press;
    work->act_status = 1 ;
    work->vision.length = 4000 ;
    
    
    if ( time == 0 )
    {
        SetAction( work, ACTION9, ACTINTERP ) ;
    }

    if ( !CheckDamage_800C7F6C( work ) )
    {
        if ( !(press & 0x02000000) )
        {
            if ( !CheckPad_800C8308( work ) )
            {
                SetMode( work, ActStandStill_800C8580 ) ;
            }
        }
        else
        {
            work->control.turn.vy = work->sn_dir ;
            work->vision.facedir = work->control.rot.vy ;
            work->target->class |= TARGET_FLAG ;
        }
    }
}

void s07c_meryl72_unk1_800C90C8( Meryl72Work* work, int time )
{

    int press = work->pad.press;
    work->act_status = 1 ;
    work->vision.length = 4000 ;
    
    
    if ( time == 0 )
    {
        SetAction( work, ACTION10, ACTINTERP ) ;
    }

    if ( !CheckDamage_800C7F6C( work ) )
    {
        if ( !(press & 0x04000000) )
        {
            if ( !CheckPad_800C8308( work ) )
            {
                SetMode( work, ActStandStill_800C8580 ) ;
            }
        }
        else
        {
            work->control.turn.vy = work->sn_dir;
            work->vision.facedir = work->control.rot.vy;
            work->target->class |= TARGET_FLAG ;
        }
    }
}

void s07c_meryl72_unk1_800C9190( Meryl72Work* work, int time )
{

    int press = work->pad.press;
    work->act_status = 1 ;
    work->vision.length = 4000 ;
    
    
    if ( time == 0 )
    {
        SetAction( work, ACTION11, ACTINTERP ) ;
    }

    if ( !CheckDamage_800C7F6C( work ) )
    {
        if ( !(press & 0x20000000) )
        {
            if ( !CheckPad_800C8308( work ) )
            {
                SetMode( work, ActStandStill_800C8580 ) ;
            }
        }
        else
        {
            work->control.turn.vy = work->sn_dir;
            work->vision.facedir = work->control.rot.vy;
            work->target->class |= TARGET_FLAG ;
        }
    }
}

void s07c_meryl72_unk1_800C9258( Meryl72Work* work, int time )
{
    work->act_status = 1 ;
    work->vision.length = 4000 ;    
    
    if ( time == 0 )
    {
        SetAction( work, ACTION31, ACTINTERP ) ;
    }

    if ( CheckDamage_800C7F6C( work ) ) return ;
    if ( CheckPad_800C8308( work ) )    return ;

    if ( work->body.is_end )
    {
        SetMode( work, ActStandStill_800C8580 ) ;
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
        work->vision.facedir = work->control.rot.vy;
        work->target->class |= TARGET_FLAG ;
    }
}

void s07c_meryl72_unk1_800C9318( Meryl72Work* work, int time )
{
    work->act_status = 1 ;
    work->vision.length = 4000 ;
    
    if ( time == 0 )
    {
        SetAction( work, ACTION12, ACTINTERP ) ;
    }

    if ( CheckDamage_800C7F6C( work ) ) return ;
    if ( CheckPad_800C8308( work ) )    return ;

    if ( work->body.is_end )
    {
        SetMode( work, ActStandStill_800C8580 ) ;
    }
    else
    {
        work->control.turn.vy = work->sn_dir;
        work->vision.facedir = work->control.rot.vy;
        work->target->class |= TARGET_FLAG ;
    }
}

int s07c_meryl72_unk1_800C93D8( Meryl72Work* work )
{
    int diff = GV_DiffDirS( work->control.rot.vy, work->sn_dir );

    if ( diff < 768 && diff > -768 )
    {
        return work->control.turn.vy ;
    }
    
    return work->sn_dir ;
}

void ActReadyGun_800C9428( Meryl72Work* work, int time )
{
    int press;
    work->act_status = 1 ;
    work->target->class |= TARGET_FLAG ;
    work->vision.length = 4000 ;
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
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->rots[16] ) ;
    }

    ReviseReadyGun_800C8020( work );
    if ( CheckDamage_800C7F6C( work ) )
    {
        work->rots[21].vx = 0;
        work->rots[21].vy = 0;
        return ;
    }

    if ( !(press & 0x30000) )
    {
        work->rots[21].vx = 0;
        work->rots[21].vy = 0;
        SetMode( work, ActStandStill_800C8580 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C9594 ) ;
        return ;
    }

    if ( press & 0x80000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C964C ) ;
        return ;
    }

    if ( press & 0x100000 )
    {
        SetMode( work, ActGrenade_800C9790 ) ;
        return ;
    }

    if ( press & 0x200000 )
    {
        SetMode( work, ActGrenade_800C9790 ) ;
        return ;
    }

    work->control.turn.vy = s07c_meryl72_unk1_800C93D8( work ) ;
    work->vision.facedir = work->control.rot.vy + work->rots[21].vy ;
}

void s07c_meryl72_unk1_800C9594( Meryl72Work* work, int time )
{
    work->act_status = 1 ;
    work->target->class |= TARGET_FLAG ;
    work->vision.length = 4000 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        s07c_meryl72_unk1_800CB584( work, 3 ) ; //Meryl_SetPutChar
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->rots[16] ) ;
    }

    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800C7F6C( work ) )
    {
        return ;
    }

    SetMode( work, ActReadyGun_800C9428 );
}

void s07c_meryl72_unk1_800C964C( Meryl72Work *work, int time )
{
    SVECTOR *rot;
    
    work->act_status = 1 ;
    work->target->class |= TARGET_FLAG ;
    work->vision.length = 4000 ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->rots[16] );
    }

    rot = &work->control.rot;
    if ( time == 1  || time == 7 )
    {
        rot->vy = ( rot->vy - 0x100 ) & 0xFFF;
    }

    if ( time == 3  || time == 5 )
    {
        rot->vy = ( rot->vy + 0x100 ) & 0xFFF;
    }

    if ( time == 2  || time == 4 || time == 6 )
    {
        SetAction( work, ACTION6, 0 );
        s07c_meryl72_unk1_800CB584( work, GUNSHOOT ) ;
    }

    if ( CheckDamage_800C7F6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActReadyGun_800C9428 );
    }

    work->control.rot.vy = rot->vy;
}

void ActGrenade_800C9790( Meryl72Work* work, int time )
{
    work->act_status = 1 ;
    work->target->class |= TARGET_FLAG ;
    work->vision.length = 4000 ;

    if ( time == 0 )
    {
        extern  void    *NewGrenadeEnemy_800D2138( CONTROL *, OBJECT *, int, unsigned int *, SVECTOR *, int ) ;

        SetAction( work, GRENADE, ACTINTERP ) ;
        work->subweapon = NewGrenadeEnemy_800D2138( &(work->control), &(work->body), 9, &(work->trigger), &GM_PlayerPosition_800ABA10, ENEMY_SIDE ) ;
    }

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE ;
    }
    if ( time == 17 )
    {
        GM_SeSet( &( work->control.mov ), SE_PINNUKI ) ;
    }
    if ( time == 45 )
    {
        work->trigger |= WEAPON_TRIG2 ;
    }

    if ( CheckDamage_800C7F6C( work ) )
    {
        GV_DestroyActor( work->subweapon ) ;
        return ;
    }


    if ( work->body.is_end )
    {
        GV_DestroyActor( work->subweapon ) ;
        SetMode( work, ActReadyGun_800C9428 ) ;
    }
}