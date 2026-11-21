#include "zako.h"

#include "enemy/asiato.h"

/*---------------------------------------------------------------------------*/

void s11i_asiato_800CD7DC(Work *work)
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

void s11i_asiato_800CD808(Work *work)
{
    if (work->modetime[7] & 0x4)
    {
        if (work->target->damaged & (TARGET_POWER | TARGET_CAPTURE))
        {
            work->modetime[6] |= 0x4;
        }
        else if (work->touch.damaged & TARGET_TOUCH)
        {
            if ((GM_PlayerStatus & (PLAYER_CB_BOX | PLAYER_MOVE)) != PLAYER_CB_BOX)
            {
                work->modetime[6] |= 0xC;
            }
        }
    }
}

int s11i_asiato_800CD88C(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to)
{
    int to_addr, from_addr;

    from_addr = HZD_GetAddress(hzd, from, -1);
    to_addr = HZD_GetAddress(hzd, to, -1);

    from_addr &= 0xFF;
    to_addr &= 0xFF;

    return HZD_ZoneDistance(hzd, from_addr, to_addr);
}

void s11i_asiato_800CD8EC(Work *work)
{
    CONTROL *control;

    if ( !( work->modetime[7] & 0x1 ) )
    {
        return;
    }

    if ( work->act_status & 0x68 )
    {
        return;
    }

    control = &work->control;

    if ( !( control->map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( GM_NoisePower == 0 )
    {
        return;
    }

    switch ( GM_NoisePower )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) < 500 )
        {
            break;
        }
        return;

    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) < 8000 )
        {
            break;
        }
        return;

    case 255:
        break;

    case 100:
        if ( GV_DiffVec3( &GM_NoisePosition, &control->mov ) < 8000 &&
             s11i_asiato_800CD88C( control->map->hzd, &control->mov, &GM_NoisePosition ) < 300 )
        {
            work->modetime[6] |= 1;
            GM_NoiseLength = 0;
            GM_NoisePower = 0;
        }
        return;

    default:
        return;
    }

    work->modetime[6] |= 1;
}

void s11i_asiato_800CDA6C( Work *work )
{
    if ( !( work->modetime[7] & 0x2 ) )
    {
        return;
    }

    if (work->vision.pad != 2)
    {
        return;
    }

    if ( !( GM_PlayerStatus & PLAYER_CB_BOX ) )
    {
        return;
    }

    if ( ( GV_DiffVec3( &work->player_pos, &GM_PlayerPosition ) > 50 ) || ( work->player_dir != GM_WhereList[0]->rot.vy ) )
    {
        if ( ZAKO11FCommand.alert_mode == TOP_COMM_ALERT )
        {
            return;
        }

        work->player_pos = GM_PlayerPosition;
        work->player_dir = GM_WhereList[0]->rot.vy;
        work->modetime[6] |= 0x2;
    }
    else if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition ) < 1500 )
    {
        work->modetime[6] |= 0x40;
    }

    work->vision.pad = 0;
    work->modetime[6] |= 0x80;
}

void s11i_asiato_800CDB94( Work *work )
{
    HZD_HDL *hzd;
    CONTROL *control;
    VISION  *vision;

    if ( !( work->modetime[7] & 0x10 ) )
    {
        return;
    }

    control = &work->control;
    if ( work->think2 == 5 )
    {
        return;
    }

    hzd = work->control.map->hzd;
    vision = &work->vision;
    if ( !( AsiatoCheck( hzd, &control->mov ) ) )
    {
        return;
    }

    if ( SearchNearAsiato( hzd, &control->mov, vision->facedir, vision->range, vision->length ) < 0 )
    {
        return;
    }

    work->modetime[6] |= 0x10;
}

void s11i_asiato_800CDC40( Work *work )
{
    work->modetime[6] = 0;
    s11i_asiato_800CD8EC( work );

    if ( ZAKO11FCommand.alert_mode != TOP_COMM_ALERT )
    {
        s11i_asiato_800CD808( work );
        s11i_asiato_800CDA6C( work );
        s11i_asiato_800CDB94( work );
    }
}

void s11i_asiato_800CDC94( Work *work )
{
    switch ( work->vision.pad )
    {
    case 0:
        if ( work->field_B94 != 2 || !( GM_PlayerStatus & PLAYER_INTRUDE ) || work->vision.length == 0 )
        {
            work->field_B94 = 0;
            work->alert_level -= 4;
        }
        break;

    case 1:
        work->field_B94 = 1;
        work->alert_level--;
        break;

    case 2:
        work->field_B94 = 2;
        work->alert_level++;
        break;
    }

    if ( work->alert_level < 0 )
    {
        work->alert_level = 0;
    }
    else if ( work->alert_level > 255 )
    {
        work->alert_level = 255;
    }
}

void s11i_asiato_800CDD64( Work *work )
{
    SVECTOR  diff;
    SVECTOR *mov;
    SVECTOR *pos;
    int      dir, dis;
    int      height;
    MAP     *map;

    mov = &work->control.mov;
    pos = &GM_PlayerPosition;
    GV_SubVec3( pos, mov, &diff );

    dir = ratan2( pos->vx - work->control.mov.vx, pos->vz - work->control.mov.vz ) & 0xfff;
    work->sn_dir = dir;
    dis = GV_VecLen3( &diff );

    work->sn_dis = dis;

    height = pos->vy - work->control.mov.vy;
    if ( height < 0 )
    {
        height = work->control.mov.vy - pos->vy;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) || GM_PlayerStatus & PLAYER_INTRUDE )
    {
        work->vision.pad = 0;
        return;
    }

    if ( ZAKO11FCommand.time % ZAKO11FCommand.n_watchers == work->param.index )
    {
        if ( ZAKO11F_EYE_LENGTH + 2000 < dis )
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
        if ( HZD_OnlineHazardCheck( map->hzd, pos, mov, HZD_CHK_ALL, HZD_SEG_NO_PLAYER ) )
        {
            work->vision.pad = 0;
            return;
        }

        if ( !( GM_OnlineTargetCheckAny( mov, pos, map->index, &diff ) ) )
        {
            if ( work->vision.length < dis )
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
}

/*---------------------------------------------------------------------------*/

void Zako11FActionMain( Work *work )
{
     if ( work->act.motion1 <= 48 )
     {
        s11i_asiato_800CD7DC( work );
        s11i_asiato_800CDD64( work );
        s11i_asiato_800CDC40( work );
        s11i_asiato_800CDC94( work );
        Zako11FThink( work );
        ZAKO11F_ExecPutChars( work );
    }

    ZAKO11F_ActionUpdate( work );
}

void Zako11FPushMove( Work *work )
{
    TARGET  *target;
    int      ang;
    int      set;
    CONTROL *control;

    target = work->target;
    ang = 0;

    if ( !( target->damaged & TARGET_PUSH ) )
    {
        return;
    }

    GV_AddVec3( &target->offset, &work->control.step, &work->control.step );
    target->damaged &= ~TARGET_PUSH;

    set = work->act.motion1;
    if ( set != 1 && set != 2 )
    {
        return;
    }

    if ( target->offset.pad )
    {
        if ( GV_Time & 256 )
        {
            ang = target->offset.pad * 1024;
            if ( !( work->param.index & 1 ) )
            {
                ang = ( target->offset.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->param.index & 1 )
            {
                ang = ( target->offset.pad + 2 ) * 1024;
            }
            else
            {
                ang = target->offset.pad * 1024;
            }
        }

        ang &= 0xFFF;
    }

    control = &work->control;
    control->turn.vy = ang;
    control->r_sphere = GV_NearExp2( control->r_sphere, work->act.field_1C );
}
