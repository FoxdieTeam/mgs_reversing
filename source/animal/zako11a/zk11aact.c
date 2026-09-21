#include "zako.h"

#include "enemy/asiato.h"

/*---------------------------------------------------------------------------*/

static void SetRadarParam( Work *work )
{
    VISION *vision;
    RADAR_SIGHT_PARAM *r_param;

    vision = &work->vision;
    r_param = &work->control.radar_param;

    r_param->dir = vision->facedir;
    r_param->dis = vision->length;
    r_param->range = vision->range * 2;
    r_param->r = 0;
}

static void CheckTarget( Work *work )
{
    if ( work->modetime[ 7 ] & 0x4 )
    {
        if ( work->target->damaged & ( TARGET_CAPTURE | TARGET_POWER ) )
        {
            work->modetime[ 6 ] |= 0x4;
        }
        else if ( ( work->touch.damaged & TARGET_TOUCH ) &&
                  ( GM_PlayerStatus & ( PLAYER_MOVE | PLAYER_CB_BOX ) ) != PLAYER_CB_BOX )
        {
            work->modetime[ 6 ] |= 0xC;
        }
    }
}

static int ZoneDist( HZD_HDL *hzd, SVECTOR *vec1, SVECTOR *vec2 )
{
    int from, to;

    from = HZD_GetAddress( hzd, vec1, -1 );
    to = HZD_GetAddress( hzd, vec2, -1 );
    from &= 0xFF;
    to &= 0xFF;
    return HZD_ZoneDistance( hzd, from, to );
}

static void CheckNoise( Work *work )
{
    CONTROL *control;

    if ( !( work->modetime[ 7 ] & 0x1 ) ) return;
    if ( work->act_status & 0x68 ) return;

    control = &work->control;
    if ( !( control->map->index & GM_PlayerMap ) ) return;
    if ( GM_NoisePower == 0 ) return;

    switch ( GM_NoisePower )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) < 500 ) work->modetime[ 6 ] |= 0x1;
        break;
    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) < 8000 ) work->modetime[ 6 ] |= 0x1;
        break;
    case 100:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) >= 8000 ) break;
        if ( ZoneDist( control->map->hzd, &control->mov, &GM_NoisePosition ) >= 300 ) break;
        work->modetime[ 6 ] |= 0x1;
        GM_NoiseLength = 0;
        GM_NoisePower = 0;
        break;
    case 255:
        work->modetime[ 6 ] |= 0x1;
        break;
    }
}

static void CheckBox( Work *work )
{
    if ( !( work->modetime[ 7 ] & 0x2 ) ) return;
    if ( work->vision.pad != 2 ) return;
    if ( !( GM_PlayerStatus & PLAYER_CB_BOX ) ) return;

    if ( GV_DiffVec3( &work->player_pos, &GM_PlayerPosition ) > 50 ||
         work->player_dir != GM_WhereList[ 0 ]->rot.vy )
    {
        if ( ZAKO11ACommand.alert_mode == 1 ) return;
        work->player_pos = GM_PlayerPosition;
        work->player_dir = GM_WhereList[ 0 ]->rot.vy;
        work->modetime[ 6 ] |= 0x2;
    }
    else if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition ) < 1500 )
    {
        work->modetime[ 6 ] |= 0x40;
    }

    work->vision.pad = 0;
    work->modetime[ 6 ] |= 0x80;
}

static void CheckAsiato( Work *work )
{
    HZD_HDL *hzd;
    SVECTOR *pos;
    VISION *vis;

    if ( !( work->modetime[ 7 ] & 0x10 ) || work->think2 == 5 ) return;

    hzd = work->control.map->hzd;
    pos = &work->control.mov;
    vis = &work->vision;

    if ( AsiatoCheck( hzd, pos ) &&
         SearchNearAsiato( hzd, pos, vis->facedir, vis->range, vis->length ) >= 0 )
    {
        work->modetime[ 6 ] |= 0x10;
    }
}

static void CheckAlert( Work *work )
{
    work->modetime[ 6 ] = 0;
    CheckNoise( work );

    if ( ZAKO11ACommand.alert_mode != 1 )
    {
        CheckTarget( work );
        CheckBox( work );
        CheckAsiato( work );
    }
}

static void UpdateAlert( Work *work )
{
    switch ( work->vision.pad )
    {
    case 0:
        if ( work->field_B90 != 2 ||
             !( GM_PlayerStatus & PLAYER_INTRUDE ) ||
             work->vision.length == 0 )
        {
            work->field_B90 = 0;
            work->alert_level -= 4;
        }
        break;
    case 1:
        work->field_B90 = 1;
        work->alert_level--;
        break;
    case 2:
        work->field_B90 = 2;
        work->alert_level++;
        break;
    }

    if ( work->alert_level < 0 )
    {
        work->alert_level = 0;
    }
    else if ( work->alert_level  > 255 )
    {
        work->alert_level = 255;
    }
}

static void CheckVision( Work *work )
{
    SVECTOR tmp;
    CONTROL *control;
    SVECTOR *pos;
    int dir, dis, height;
    MAP *map;

    control = &work->control;
    pos = &GM_PlayerPosition;
    GV_SubVec3( pos, &control->mov, &tmp );

    dir = ratan2( pos->vx - work->control.mov.vx,
                  pos->vz - work->control.mov.vz ) & 4095;
    work->sn_dir = dir;

    dis = GV_VecLen3( &tmp );
    work->sn_dis = dis;

    height = ABS( pos->vy - work->control.mov.vy );

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        work->vision.pad = 0;
        return;
    }

    if ( GM_PlayerStatus & PLAYER_INTRUDE )
    {
        work->vision.pad = 0;
        return;
    }

    if ( ( ZAKO11ACommand.time % ZAKO11ACommand.n_watchers ) != work->param.index )
    {
        return;
    }

    if ( dis > ( ZAKO11A_EYE_LENGTH + 2000 ) )
    {
        work->vision.pad = 0;
        return;
    }

    if ( height > 2000 )
    {
        work->vision.pad = 0;
        return;
    }

    if ( dis >= 500 && GV_DiffDirAbs( work->vision.facedir, dir ) >= work->vision.range )
    {
        work->vision.pad = 0;
        return;
    }

    map = work->control.map;
    if ( !HZD_OnlineHazardCheck( map->hzd, pos, &control->mov, HZD_CHK_ALL, HZD_SEG_NO_PLAYER ) &&
         !GM_OnlineTargetCheckAny( &control->mov, pos, map->index, &tmp ) )
    {
        if ( dis > work->vision.length )
        {
            work->vision.pad = 1;
        }
        else
        {
            work->vision.pad = 2;
        }
    }
    else
    {
        work->vision.pad = 0;
    }
}

/*---------------------------------------------------------------------------*/

void Zako11AActionMain( Work *work )
{
    if ( work->act.motion1 <= 48 )
    {
        SetRadarParam( work );
        CheckVision( work );
        CheckAlert( work );
        UpdateAlert( work );
        Zako11AThink( work );
        ZAKO11A_ExecPutChars( work );
    }

    ZAKO11A_ActionUpdate( work );
}

void Zako11APushMove( Work *work )
{
    TARGET *trg;
    int turn, motion1;
    CONTROL *control;

    trg = work->target;
    turn = 0;

    if ( !( trg->damaged & TARGET_PUSH ) ) return;

    GV_AddVec3( &trg->offset, &work->control.step, &work->control.step );
    trg->damaged &= ~TARGET_PUSH;

    motion1 = work->act.motion1;
    if ( motion1 == 1 || motion1 == 2 )
    {
        if ( trg->offset.pad != 0 )
        {
            if ( GV_Time & 256 )
            {
                if ( work->param.index & 1 )
                {
                    turn = trg->offset.pad * 1024;
                }
                else
                {
                    turn = ( trg->offset.pad + 2 ) * 1024;
                }
            }
            else
            {
                if ( work->param.index & 1 )
                {
                    turn = ( trg->offset.pad + 2 ) * 1024;
                }
                else
                {
                    turn = trg->offset.pad * 1024;
                }
            }

            turn &= 4095;
        }

        control = &work->control;
        control->turn.vy = turn;
        control->r_sphere = GV_NearExp2( control->r_sphere, work->act.field_1C );
    }
}
