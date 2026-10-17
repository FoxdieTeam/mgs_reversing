#include "zako10.h"

extern ZAKO10_COMMAND Zako10Command;

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

#define SEGMENT_ATR ( HZD_SEG_NO_PLAYER )

extern int ZAKO10_EYE_LENGTH;

// in enemy/asiato.c
extern int AsiatoCheck( HZD_HDL *, SVECTOR * );
extern int SearchNearAsiato( HZD_HDL *, SVECTOR *, short, short, short );

void Zako10SetRadarParam( Zako10Work* work )
{
    VISION     *vision = &work->vision;
    RADAR_SIGHT_PARAM *r_param   = &work->control.radar_param;

    r_param->dir = vision->facedir;
    r_param->dis = vision->length;
    r_param->range = vision->angle * 2;
    r_param->r = 0;
}

void s10a_zk10enemy_800CB478( Zako10Work *work )
{
    unsigned short flags;
    if ( !( work->modetime[7] & 4 ) )
    {
        return;
    }

    flags = work->target->damaged;
    if ( flags & 6 )
    {
        work->modetime[6] |= 4;
        return;
    }

    flags = work->field_94C.damaged;
    if ( flags & 0x80 )
    {
        if ( ( GM_PlayerStatus & ( PLAYER_MOVE | PLAYER_CB_BOX ) ) == PLAYER_CB_BOX )
        {
            return;
        }
        work->modetime[6] |= 12;
    }
}

int s10a_zk10enemy_800CB4FC( HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2 )
{
    int from;
    int to;

    from = HZD_GetAddress( hzd, pos, -1 );

    //TODO: fix
    do
    {
        to = HZD_GetAddress( hzd, pos2, -1 );
        do {
            return HZD_ZoneDistance( hzd, from & 0xFF, to & 0xFF );
        } while (0);
    } while (0);
}

void s10a_zk10enemy_800CB55C( Zako10Work* work )
{
    CONTROL *ctrl;
    if ( !( work->modetime[7] & 1 ) )
    {
        return;
    }

    if ( work->act_status & 0x68 )
    {
        return;
    }

    ctrl = &work->control;


    if ( !( ctrl->map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( !GM_NoisePower )
    {
        return;
    }

    switch ( GM_NoisePower )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 8000 )
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 8000 && s10a_zk10enemy_800CB4FC( ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition ) < 300  )
        {
            work->modetime[6] |= 1;
            GM_NoiseLength = 0;
            GM_NoisePower  = 0;
            return;
        }
        return;
    default:
        return;
    }
    work->modetime[6] |= 1;
}

void s10a_zk10enemy_800CB6DC( Zako10Work *work )
{

    if ( work->modetime[7] & 2 && work->vision.field_B92 == 2 && ( ( GM_PlayerStatus & PLAYER_CB_BOX ) == PLAYER_CB_BOX ) )
    {
        if ( ( GV_DiffVec3( &work->field_BA0, &GM_PlayerPosition ) > 50 ) || ( work->field_BA8 != GM_WhereList[0]->rot.vy ) )
        {
            if ( Zako10Command.mode != TOP_COMM_ALERT )
            {
                work->field_BA0 = GM_PlayerPosition;
                work->field_BA8 = GM_WhereList[0]->rot.vy;
                work->modetime[6] |= 0x2;
            }
            else
            {
                return;
            }
        }
        else
        {
            if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition ) < 1500 )
            {
                work->modetime[6] |= 0x40;
            }
        }
        work->vision.field_B92 = 0;
        work->modetime[6] |= 0x80;
    }
}

void s10a_zk10enemy_800CB804( Zako10Work* work )
{
    HZD_HDL *hzd;
    CONTROL *ctrl;
    VISION  *vision;

    if ( !( work->modetime[7] & 16 ) )
    {
        return;
    }

    ctrl = &work->control;
    if ( work->think2 == 5 )
    {
        return;
    }

    hzd = work->control.map->hzd;
    vision = &work->vision;
    if ( !( AsiatoCheck( hzd, &ctrl->mov ) ) )
    {
        return;
    }

    if ( SearchNearAsiato( hzd, &ctrl->mov, vision->facedir, vision->angle, vision->length ) < 0 )
    {
        return;
    }

    work->modetime[6] |= 16;
}

void s10a_zk10enemy_800CB8B0( Zako10Work* work )
{
    work->modetime[6] = 0;
    s10a_zk10enemy_800CB55C( work );

    if ( Zako10Command.mode != TOP_COMM_ALERT )
    {
        s10a_zk10enemy_800CB478( work );
        s10a_zk10enemy_800CB6DC( work );
        s10a_zk10enemy_800CB804( work );
    }
}

void s10a_zk10enemy_800CB904( Zako10Work* work )
{
    int val;
    val = work->vision.field_B92;
    switch ( val )
    {
        case 0:
            if ( work->field_B90 != 2 || !( GM_PlayerStatus & PLAYER_INTRUDE ) || work->vision.length == 0 )
            {
                work->field_B90 = 0;
                work->alert_level -= 4;
            }
            break;
        case 1:
            work->field_B90 = val;
            work->alert_level -= 1;
            break;
        case 2:
            work->field_B90 = val;
            work->alert_level += 1;
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

void Zako10CheckSight( Zako10Work* work )
{
    int dir;
    int dis;
    int diff;
    SVECTOR *pos;
    SVECTOR svec;
    CONTROL *ctrl;
    MAP *map;

    ctrl = &work->control;
    pos = &GM_PlayerPosition;
    GV_SubVec3( pos, &ctrl->mov, &svec );

    dir = GV_VecDir2( &svec );
    work->sn_dir = dir;
    dis = GV_VecLen3( &svec );

    work->sn_dis = dis;

    diff = pos->vy - work->control.mov.vy;
    if ( diff < 0 )
    {
        diff = work->control.mov.vy - pos->vy;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) || GM_PlayerStatus & PLAYER_INTRUDE )
    {
        work->vision.field_B92 = 0;
        return;
    }

    if ( Zako10Command.counter % Zako10Command.n_watchers == work->param.index )
    {
        //ridiculous, but its the only way it matches
        if ( ZAKO10_EYE_LENGTH + 2000 >= dis )
        {
            if ( 2000 >= diff )
            {
                if ( dis < 500 || GV_DiffDirAbs( work->vision.facedir, dir ) < work->vision.angle )
                {
                    map = work->control.map;
                    if ( !( HZD_OnlineHazardCheck( map->hzd, pos, &ctrl->mov, HZD_CHK_ALL, SEGMENT_ATR ) ) )
                    {
                        if ( !( GM_OnlineTargetCheckAny( &ctrl->mov, pos, map->index, &svec ) ) )
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
                    else
                    {
                        work->vision.field_B92 = 0;
                    }
                }
                else
                {
                    work->vision.field_B92 = 0;
                }
            }
            else
            {
                work->vision.field_B92 = 0;
            }
        }
        else
        {
            work->vision.field_B92 = 0;
        }
    }
}

extern void Zako10Think( Zako10Work * );
extern void Zako10ActionUpdate( Zako10Work * );
extern void ZAKO10_ExecPutChar( Zako10Work* work );

void Zako10ActionMain( Zako10Work *work )
{
     if ( work->unknown.last_set < 0x31 )
     {
        Zako10SetRadarParam( work );
        Zako10CheckSight( work );
        s10a_zk10enemy_800CB8B0( work );
        s10a_zk10enemy_800CB904( work );
        Zako10Think( work );
        ZAKO10_ExecPutChar( work );
    }

    Zako10ActionUpdate( work );
}

void Zako10PushMove( Zako10Work *work )
{
    int s1;
    CONTROL *ctrl;
    TARGET *target;

    target = work->target;
    s1 = 0;
    if ( !( target->damaged & 0x8 ) )
    {
        return;
    }

    GV_AddVec3( &target->offset, &work->control.step, &work->control.step );
    target->damaged &= ~( 0x8 );

    if ( work->unknown.last_set - 1 >= 2u )
    {
        return;
    }

    if ( target->offset.pad )
    {
        if ( GV_Time & 256 )
        {
            s1 = target->offset.pad * 1024;
            if ( !( work->param.index & 1 ) )
            {
                s1 = ( target->offset.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->param.index & 1 )
            {
                s1 = ( target->offset.pad + 2 ) * 1024;
            }
            else
            {
                s1 = target->offset.pad * 1024;
            }
        }
        s1 &= 0xFFF;
    }

    ctrl = &work->control;
    ctrl->turn.vy = s1;
    ctrl->r_sphere = GV_NearExp2( ctrl->r_sphere, work->unknown.field_1C );
}
