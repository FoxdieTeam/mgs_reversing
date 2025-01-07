#include "../../../s00a/Enemy/enemy.h"

extern int GV_Time;

extern int      GM_ClaymoreMap_800AB9DC;
extern int      GM_PlayerMap_800ABA0C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PlayerStatus_800ABA50;
extern CONTROL *GM_WhereList_800B56D0[96];

extern int             ZAKO11F_EYE_LENGTH_800C3694;
extern ZAKO11F_COMMAND Zako11FCommand_800D5AF8;

int AsiatoCheck_800D16C0( HZD_HDL *, SVECTOR * );
int SearchNearAsiato_800D13B0( HZD_HDL *, SVECTOR *, short, short, short );

void s11i_asiato_800CC39C( Zako11FWork *work );
void s11i_zk11fcom_800D0BAC( Zako11FWork *work ); //Zako11FThink
void ZAKO11F_ExecPutChar_800CD77C( Zako11FWork *work );

void s11i_asiato_800CD7DC(Zako11FWork *work)
{
    VISION     *vision;
    RADAR_CONE *cone;

    vision = &work->vision;
    cone = &work->control.radar_cone;

    cone->dir = vision->facedir;
    cone->len = vision->length;
    cone->ang = vision->angle * 2;
    cone->_pad = 0;
}

void s11i_asiato_800CD808(Zako11FWork *work)
{
    if (work->modetime[7] & 0x4)
    {
        if (work->target->damaged & (TARGET_POWER | TARGET_CAPTURE))
        {
            work->modetime[6] |= 0x4;
        }
        else if (work->field_94C.damaged & TARGET_TOUCH)
        {
            if ((GM_PlayerStatus_800ABA50 & (PLAYER_CB_BOX | PLAYER_MOVING)) != PLAYER_CB_BOX)
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

void s11i_asiato_800CD8EC(Zako11FWork *work)
{
    CONTROL *control;

    if ( !( work->field_BA3 & 0x1 ) )
    {
        return;
    }

    if ( work->act_status & 0x68 )
    {
        return;
    }

    control = &work->control;

    if ( !( control->map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    if ( GM_NoisePower_800ABA24 == 0 )
    {
        return;
    }

    switch ( GM_NoisePower_800ABA24 )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &control->mov ) < 500 )
        {
            break;
        }
        return;

    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &control->mov ) < 8000 )
        {
            break;
        }
        return;

    case 255:
        break;

    case 100:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &control->mov ) < 8000 &&
             s11i_asiato_800CD88C( control->map->hzd, &control->mov, &GM_NoisePosition_800AB9F8 ) < 300 )
        {
            work->field_BA2 |= 1;
            GM_NoiseLength_800ABA30 = 0;
            GM_NoisePower_800ABA24 = 0;
        }
        return;

    default:
        return;
    }

    work->field_BA2 |= 1;
}

void s11i_asiato_800CDA6C( Zako11FWork *work )
{
    if ( !( work->field_BA3 & 0x2 ) )
    {
        return;
    }

    if (work->vision.field_B92 != 2)
    {
        return;
    }

    if ( !( GM_PlayerStatus_800ABA50 & PLAYER_CB_BOX ) )
    {
        return;
    }

    if ( ( GV_DiffVec3( &work->field_BA4, &GM_PlayerPosition_800ABA10 ) > 50 ) || ( work->field_BAC != GM_WhereList_800B56D0[0]->rot.vy ) )
    {
        if ( Zako11FCommand_800D5AF8.mode == TOP_COMM_ALERT )
        {
            return;
        }

        work->field_BA4 = GM_PlayerPosition_800ABA10;
        work->field_BAC = GM_WhereList_800B56D0[0]->rot.vy;
        work->field_BA2 |= 0x2;
    }
    else if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition_800ABA10 ) < 1500 )
    {
        work->field_BA2 |= 0x40;
    }

    work->vision.field_B92 = 0;
    work->field_BA2 |= 0x80;
}

void s11i_asiato_800CDB94( Zako11FWork *work )
{
    HZD_HDL *hzd;
    CONTROL *control;
    VISION  *vision;

    if ( !( work->field_BA3 & 0x10 ) )
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
    if ( !( AsiatoCheck_800D16C0( hzd, &control->mov ) ) )
    {
        return;
    }

    if ( SearchNearAsiato_800D13B0( hzd, &control->mov, vision->facedir, vision->angle, vision->length ) < 0 )
    {
        return;
    }

    work->field_BA2 |= 0x10;
}

void s11i_asiato_800CDC40( Zako11FWork *work )
{
    work->field_BA2 = 0;
    s11i_asiato_800CD8EC( work );

    if ( Zako11FCommand_800D5AF8.mode != TOP_COMM_ALERT )
    {
        s11i_asiato_800CD808( work );
        s11i_asiato_800CDA6C( work );
        s11i_asiato_800CDB94( work );
    }
}

void s11i_asiato_800CDC94( Zako11FWork *work )
{
    switch ( work->vision.field_B92 )
    {
    case 0:
        if ( work->field_B94 != 2 || !( GM_PlayerStatus_800ABA50 & PLAYER_INTRUDE ) || work->vision.length == 0 )
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

void s11i_asiato_800CDD64( Zako11FWork *work )
{
    SVECTOR  diff;
    SVECTOR *mov;
    SVECTOR *pos;
    int      dir, dis;
    int      height;
    MAP     *map;

    mov = &work->control.mov;
    pos = &GM_PlayerPosition_800ABA10;
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

    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) || GM_PlayerStatus_800ABA50 & PLAYER_INTRUDE )
    {
        work->vision.field_B92 = 0;
        return;
    }

    if ( Zako11FCommand_800D5AF8.field_0x0C % Zako11FCommand_800D5AF8.n_watchers == work->field_B74 )
    {
        if ( ZAKO11F_EYE_LENGTH_800C3694 + 2000 < dis )
        {
            work->vision.field_B92 = 0;
            return;
        }

        if ( height > 2000 )
        {
            work->vision.field_B92 = 0;
            return;
        }

        if ( dis >= 500 && GV_DiffDirAbs( work->vision.facedir, dir ) >= work->vision.angle )
        {
            work->vision.field_B92 = 0;
            return;
        }

        map = work->control.map;
        if ( HZD_80028454( map->hzd, pos, mov, 0xF, 0x4 ) )
        {
            work->vision.field_B92 = 0;
            return;
        }

        if ( !( sub_8002E2A8( mov, pos, map->index, &diff ) ) )
        {
            if ( work->vision.length < dis )
            {
                work->vision.field_B92 = 1;
            }
            else
            {
                work->vision.field_B92 = 2;
            }
        }
        else
        {
            work->vision.field_B92 = 0;
        }
    }
}

void Zako11FActionMain_800CDF40( Zako11FWork *work )
{
     if ( work->unknown.last_set <= ACTION48 )
     {
        s11i_asiato_800CD7DC( work );
        s11i_asiato_800CDD64( work );
        s11i_asiato_800CDC40( work );
        s11i_asiato_800CDC94( work );
        s11i_zk11fcom_800D0BAC( work );
        ZAKO11F_ExecPutChar_800CD77C( work );
    }

    s11i_asiato_800CC39C( work );
}

void Zako11FPushMove_800CDFAC( Zako11FWork *work )
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

    GV_AddVec3( &target->field_34_vec, &work->control.step, &work->control.step );
    target->damaged &= ~TARGET_PUSH;

    set = work->unknown.last_set;
    if ( set != ACTION1 && set != ACTION2 )
    {
        return;
    }

    if ( target->field_34_vec.pad )
    {
        if ( GV_Time & 256 )
        {
            ang = target->field_34_vec.pad * 1024;
            if ( !( work->field_B74 & 1 ) )
            {
                ang = ( target->field_34_vec.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->field_B74 & 1 )
            {
                ang = ( target->field_34_vec.pad + 2 ) * 1024;
            }
            else
            {
                ang = target->field_34_vec.pad * 1024;
            }
        }

        ang &= 0xFFF;
    }

    control = &work->control;
    control->turn.vy = ang;
    control->field_36 = GV_NearExp2( control->field_36, work->unknown.field_1C );
}
