#include <stdio.h>
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
extern int GM_GameOverTimer ;
extern SVECTOR DG_ZeroVector ;
extern int GM_AlertMode_800ABA00 ;
extern int GM_PlayerAction_800ABA40 ;
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

void s07c_meryl72_unk1_800C98E0( Meryl72Work* work, int time )
{
    work->target->class |= TARGET_FLAG ;
       
    if ( time == 0 )
    {
        SetAction( work, ACTION24, ACTINTERP ) ;
    }

    if ( !CheckDamage_800C7F6C( work ) && work->body.is_end )
    {
        SetMode( work, ActStandStill_800C8580 ) ;
    }
}

void s07c_meryl72_unk1_800C9970( Meryl72Work* work, int time )
{
    TARGET  *trgt = work->target ;
    CONTROL *ctrl = &work->control ;

    work->f8BC.field_1C = 0 ;

    if ( time == 0 )
    {
        work->fC08 = 1;
        work->f8BC.field_14 = 7 ;
        SetAction( work, ACTION36, ACTINTERP ) ;
    }

    if ( ( time > 7 ) && ( time < 20 )  )
    {
        GM_MoveTarget( &work->target2, &ctrl->mov );
        GM_PowerTarget( &work->target2 ); 
    }

    if ( time == 24 )
    {
        if ( !work->fB94 )
        {
            GM_SeSet( &ctrl->mov, 0xC3 );
        }
        else
        {
            GM_SeSet( &ctrl->mov, 0xC2 );
        }
        GM_SeSet( &ctrl->mov, 0x33 );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07c_meryl72_unk1_800CA0EC ) ;
    }

    if ( time < 24 )
    {
        ctrl->turn = *trgt->field_1C ;
    }
}

extern SVECTOR s07c_dword_800C338C;

void s07c_meryl72_unk1_800C9AB0( Meryl72Work* work )
{
    SVECTOR  svec;

    work->control.turn = GM_PlayerControl_800AB9F4->rot;
    DG_SetPos2( &GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->rot ) ;
    DG_PutVector( &s07c_dword_800C338C, &svec, 1 );
    GV_SubVec3( &svec, &work->control.mov, &work->control.step );
}

extern unsigned char s07c_dword_800C3384[];
extern unsigned char s07c_dword_800C3388[];

void s07c_meryl72_unk1_800C9B30( Meryl72Work* work, int time )
{
    int s2;
    TARGET *target;

    target = work->target;
    s2 = work->f8BC.field_18;

    work->f8BC.field_1C = 0;

    if ( time == 0 )
    {
        work->fC08 = 1;
        work->fAEA = target->field_2A;
        work->fAEC = 0;
        if ( !work->fB94 )
        {
            GM_SeSet( &work->control.mov, 0xBE );
        }
        else
        {
            GM_SeSet( &work->control.mov, 0xC4 );
        }
    }

    if ( work->fAEA != target->field_2A )
    {
        if ( !work->fB94 )
        {
            GM_SeSet( &work->control.mov, 0xBE );
        }
        else
        {
            GM_SeSet( &work->control.mov, 0xC4 );
        }
        work->fAEA = target->field_2A;
    }

    if ( target->damaged & TARGET_POWER )
    {
        s07c_meryl72_unk1_800CB2EC( work, 5, 0 ) ;
        if ( !work->fB94 )
        {
            GM_SeSet( &work->control.mov, 0xC3 );
        }
        else
        {
            GM_SeSet( &work->control.mov, 0xC2);
        }
        target->field_2C_vec = DG_ZeroVector;
        target->field_28 = 0;
        target->damaged = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            work->f8BC.field_14 = 6;
            target->side = ENEMY_SIDE;
            if ( !GM_GameOverTimer && GM_SnakeCurrentHealth > 0 )
            {
                ExecProc_800C7C58( work, 1 ) ;
                GM_GameOver();
                GM_GameOverTimer = -2;
            }
            SetMode( work, s07c_meryl72_unk1_800CA538 );
            target->field_42 = 0;
        }
    }
    
    switch ( GM_PlayerAction_800ABA40 )
    {
    case 0x7:
    case 0xD:
        if( s2 != 0x20 && s2 != 0x1E )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION32, ACTINTERP );
            work->fAEC = 0;
        }

        if ( work->fAEC == 0x32 && target->field_2A > 0 )
        {
            SetAction( work, ACTION30, ACTINTERP );
        }

        if ( s2 == 0x1E && !( work->fAEC & 7  ) )
        {
            NewPadVibration_8005D58C(s07c_dword_800C3384, 1);
            NewPadVibration_8005D58C(s07c_dword_800C3388, 2);
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s07c_meryl72_unk1_800C9AB0( work );
        work->fAEC++;
        break;
    case 0x26:
        if ( s2 != 0x21 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION33, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s07c_meryl72_unk1_800C9AB0( work );
        break;
    case 0x27:
        work->f8BC.field_14 = 5;
        target->side = ENEMY_SIDE;
        target->field_26_hp = 0;
        if ( !GM_GameOverTimer && GM_SnakeCurrentHealth > 0 )
        {
            ExecProc_800C7C58( work, 1 ) ;
            GM_GameOver();
            GM_GameOverTimer = -2;
        }
        SetMode( work, s07c_meryl72_unk1_800CA538 );
        return ;
    default:
        work->f8BC.field_14 = 6 ;
        target->side = ENEMY_SIDE ;
        SetMode( work, s07c_meryl72_unk1_800CA538 ) ;
        return ;
    }

    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0 ;
    }

    work->target->class |= ( TARGET_SEEK | TARGET_POWER ) ;
    work->vision.facedir = work->control.rot.vy ;
}

void s07c_meryl72_unk1_800C9F30( Meryl72Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, ACTION44, ACTINTERP );
    }

    if (work->body.is_end )
    {
        SetMode( work, s07c_meryl72_unk1_800CAA48 );
    }
}

void s07c_meryl72_unk1_800C9F98( Meryl72Work *work, int time )
{
    CONTROL *ctrl;
    int time_offset;

    ctrl = &work->control;
    work->f8BC.field_1C = 0;
    work->vision.length = 0;

    if ( time == 0 )
    {
        work->fC08 = 1 ;
        SetAction( work, ACTION37, ACTINTERP ) ;
        work->target->field_2A = 0;
        if ( GM_StreamStatus_80037CD8() != -1 )
        {
            GM_StreamPlayStop_80037D64();
        }
    }

    if ( CheckDamage_800C7F6C( work ) )
    {
        return ;
    }

    time_offset = 10;

    if ( time == time_offset )
    {
        work->f8BC.field_14 = 2;
        SetAction( work, ACTION38, ACTINTERP ) ;
    }
    else
    {
        work->target->class |= TARGET_FLAG ;
    }

    if ( time == time_offset + 48 )
    {
        GM_SeSet( &ctrl->mov, 0x51 );
    }

    if ( time == time_offset + 74 )
    {
        GM_SeSet( &ctrl->mov, 0x33 );
    }

    if ( time >= time_offset + 50 && work->body.is_end )
    {
        SetMode( work, s07c_meryl72_unk1_800CA0EC ) ;
    }
}

extern void s00a_command_800CA69C( SVECTOR *pos ) ;

void s07c_meryl72_unk1_800CA0EC( Meryl72Work *work, int time )
{
    SVECTOR svec;

    if ( time == 0 )
    {
        if ( work->f8BC.field_14 < 4 )
        {
            if ( work->f8BC.field_14 == 1 )
            {
                SetAction( work, ACTION47, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION45, ACTINTERP );
            }
        }
        else
        {
            SetAction( work, ACTION46, ACTINTERP );
        }

        if ( work->target->field_2A <= 0 )
        {
            work->target->field_2A = 7 ;
            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            s00a_command_800CA69C( &svec ) ; //smoke anim
            work->fAEA = 0x96;
        }
        else
        {
            work->fAEA = 0xA;
        }
    }

    if (s07c_meryl72_unk1_800C7D00( work ) )
    {
         SetMode( work, s07c_meryl72_unk1_800CA278 );
         return;
    }

    if ( work->fAEA < time )
    {
        if ( work->target->field_2A <= 0 )
        {
            work->target->field_2A = work->param.faint;
        }
        SetMode( work, s07c_meryl72_unk1_800CA314 );
        return;
    }

    work->target->class |= 0x22;
}

void s07c_meryl72_unk1_800CA278( Meryl72Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->f8BC.field_14 < 4 )
        {
            SetAction( work, ACTION52, ACTINTERP );
        }
        else
        {
            SetAction( work, ACTION53, ACTINTERP );
        }
        GM_SeSet( &work->control.mov, 0x36 );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07c_meryl72_unk1_800CAA48 );
    }
}

void s07c_meryl72_unk1_800CA314( Meryl72Work* work, int time )
{
    work->f8BC.field_1C = 0;

    if ( time == 0 )
    {
        if ( work->f8BC.field_14 < 4 )
        {
            if ( work->fAEA == 0x96 )
            {
                SetAction( work, ACTION50, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION48, ACTINTERP );
            }
        }
        else
        {
            if ( work->fAEA == 0x96 )
            {
                SetAction( work, ACTION51, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION49, ACTINTERP );
            }
        }
    }

    if ( work->body.is_end )
    {
        work->fC34 = 0x1E;
        SetMode( work, ActStandStill_800C8580 );
        work->fC08 = 2;
    }
}

extern char s07c_aNokezoriend_800D4850[];

void s07c_meryl72_unk1_800CA408( Meryl72Work* work, int time )
{
    TARGET* target;
    work->f8BC.field_1C = 0;
    work->vision.length = 4000;

    if ( CheckDamage_800C7F6C( work ) )
    {
        return ;
    }

    target = work->target;
    if (time == 0 )
    {
        work->fC08 = 1;
        SetAction( work, ACTION20, ACTINTERP ) ;
        if ( !work->fB94 )
        {
            GM_SeSet( &work->control.mov, 0xC3 );
        }
        else
        {
            GM_SeSet( &work->control.mov, 0xC2);
        }

        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, 0x34 );
            s07c_meryl72_unk1_800CB35C( work ); // putfog
        }
        else
        {
            s07c_meryl72_unk1_800CB2EC( work, 5, 0 ); // putblood
        }
    }

    if ( work->body.is_end)
    {
        work->fC34 = 0x1E;
        work->fC08 = 2 ;
        printf( s07c_aNokezoriend_800D4850 ) ;
        SetMode( work, ActStandStill_800C8580 ) ;
    }
    work->target->class |= TARGET_FLAG ;
}

void s07c_meryl72_unk1_800CA538( Meryl72Work *work, int time )
{
    CONTROL* ctrl;
    UNK *unk;
    int s2;

    s2 = 0xF;
    unk = (UNK*)&work->f8BC;
    work->f8BC.field_1C = 0;
    work->control.step = work->target->field_2C_vec;
    ctrl = &work->control;


    
    if ( time == 0 )
    {
        work->fC08 = 1;
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet( &ctrl->mov, 0x34 );
            SetAction( work, ACTION40, ACTINTERP );
            if ( !work->fB94 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 );
            }
            else
            {
                GM_SeSet( &ctrl->mov, 0xC2);
            }
            s07c_meryl72_unk1_800CB2EC( work, 5, 0 );
            work->fAEA = 17;
            s2 = 0x10;
            break;
        case 1:
            SetAction( work, ACTION43, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( !work->fB94 )
                {
                    GM_SeSet( &ctrl->mov, 0xC4 );
                }
                else
                {
                    GM_SeSet( &ctrl->mov, 0xC3);
                }
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
                {
                    s07c_meryl72_unk1_800CB2EC( work, 6, 2 );
                }
                else
                {
                    s07c_meryl72_unk1_800CB2EC( work, 6, 1 );
                }
                if ( work->target->a_mode == 3 )
                {
                    GM_SeSet( &work->control.mov, 0x34 );
                }
            }
            else
            {
                
                if ( !work->fB94 )
                {
                    GM_SeSet( &ctrl->mov, 0xC3 );
                }
                else
                {
                    GM_SeSet( &ctrl->mov, 0xC2) ;
                }
                s07c_meryl72_unk1_800CB2EC( work, 5, 0 );
            }
            work->fAEA = 46;
            s2 = 0xF;
            break;
        case 4:
            if ( !work->fB94 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 );
            }
            else
            {
                GM_SeSet( &ctrl->mov, 0xC2);
            }
            s2 = 0xF;
            SetAction( work, ACTION41, ACTINTERP );
            s07c_meryl72_unk1_800CB2EC( work, 5, 0 );
            work->fAEA = 14;
            break;
        case 3:
            if ( !work->fB94 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 );
            }
            else
            {
                GM_SeSet( &ctrl->mov, 0xC2) ;
            }
            s2 = 0x11;
            SetAction( work, ACTION42, ACTINTERP );
            s07c_meryl72_unk1_800CB2EC( work, 5, 0 );
            work->fAEA = 22;
            break;
        case 5:
            if ( !work->fB94 )
            {
                GM_SeSet( &ctrl->mov, 0xBF );
            }
            else
            {
                GM_SeSet( &ctrl->mov, 0xC5 );
            }
            s2 = 0xF;
            GM_SeSet( &ctrl->mov, 0x90 );
            SetAction( work, ACTION34, ACTINTERP );
            work->fAEA = 67;
            break;
        case 6:
            SetAction( work, ACTION35, ACTINTERP );
            s2 = 0x10;
            work->fAEA = 15;
            break;
        }
        
        if ( GM_StreamStatus_80037CD8() != -1 )
        {
            GM_StreamPlayStop_80037D64();
        }
    }

    if ( time == 2 && work->target->field_26_hp <= 0 )
    {
        GM_GameStatus |= 0x10000000;
        if ( GM_StreamStatus_80037CD8() == -1 )
        {
            GM_VoxStream_80037E40( work->voices[ s2] , 0 );
        }
    }

    
    switch( unk->field_14 )
    {
    case 1:
        if ( time == 24 )
        {
            GM_SeSet( &work->control.mov, 0x51 );
        }
        break;
    case 0:
    case 3:
    case 4:
        if ( time > 6 && time < 30 )
        {
            GM_MoveTarget( &work->target2, &work->control.mov );
            GM_PowerTarget( &work->target2 );
        }
        break;
    case 2:
    case 5:
        break;
    }

    if ( time > 16 && work->control.field_57 )
    {
        work->control.step = DG_ZeroVector;
    }

    if ( time == work->fAEA )
    {
        GM_SeSet( &work->control.mov, 0x33 ) ;
    }

    if ( work->body.is_end )
    {
        work->f8BC.field_1C = 1;
        work->target->field_2C_vec = DG_ZeroVector;
        if ( work->target->field_26_hp <= 0 )
        {
            SetMode( work, s07c_meryl72_unk1_800CAA48 );
        }
        else
        {
            SetMode( work, s07c_meryl72_unk1_800CA0EC );
        }
    }
}

void s07c_meryl72_unk1_800CAA48( Meryl72Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->f8BC.field_14 < 4 )
        {
            if ( work->f8BC.field_14 == 1 )
            {
                SetAction( work, ACTION56, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION54, ACTINTERP );
            }
        }
        else
        {
            SetAction( work, ACTION55, ACTINTERP );
        }
        GM_ConfigControlAttribute( &work->control, 0 );
        work->target->class = TARGET_AVAIL;
    }

    if  ( time > 32 && GM_StreamStatus_80037CD8() == -1 && GM_GameOverTimer == -2 )
    {
        GM_GameOverTimer = 1;
    }

    if ( time == 600 )
    {
        GM_GameOverTimer = 0;
        GM_GameOver();
    }
}

void s07a_meryl_unk_800D9508( Meryl72Work *work )
{
    work->light[0].t[0] += ( work->fC0E * 5 ) ;
}

void s07c_meryl72_unk1_800CAB68( Meryl72Work *work )
{
    if ( work->fC34 > 0)
    {
        work->target->class = TARGET_AVAIL ;
        work->fC34 -= 1 ;
        return;
    }
    work->fC34 = 0;
}

void s07c_meryl72_unk1_800CABA0( Meryl72Work *work )
{
    OBJECT     *body;
    short       v0;
    int         time_prev;
    ACTION      action;
    UNK        *unk;
    CONTROL    *ctrl;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;
    
    unk = &work->f8BC;
    ctrl   = &work->control;
    
    work->f8EC = 0;
    work->fC08 = 0;
    work->act_status = 0;
    work->f8BC.field_1C = 1 ;
    work->fB9C = 0;
    
    body = &work->body;
    action = work->action;
    
    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = ActStandStill_800C8580;
        work->action = ActStandStill_800C8580;
    }
    
    action( work, time_prev );
    action = work->action2;

    if ( action )
    {
        time_prev = work->time2;
        work->time2++;
        action( work, time_prev );
    }

    ctrl->height = body->field_18 ;
    
    if ( !unk->field_1C )
    {
        ctrl->field_36 = GV_NearExp2( ctrl->field_36, unk->field_1A );
    }
    else
    {
        ctrl->field_36 = -1;
    }

    s07c_meryl72_unk1_800CAB68( work );
    s07c_meryl72_unk1_800C80B4( work );
    s07a_meryl_unk_800D9508( work );


    if ( GM_AlertMode_800ABA00 == 3 && work->target->class & TARGET_POWER )
    {
        work->homing->flag = 1;
    }
    else
    {
        work->homing->flag = 0;
    }
    
    if ( unk->field_04 < 0 && ctrl->field_57 )
    {
        unk->field_04 = 0;
    }
    
    v0 = unk->field_04 - 16;
    unk->field_04 = v0;
    ctrl->step.vy = v0;
}
