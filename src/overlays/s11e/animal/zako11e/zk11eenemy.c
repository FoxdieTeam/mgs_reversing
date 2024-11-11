#include "../../../s00a/Enemy/enemy.h"
#include "libhzd/libhzd.h"

extern ZAKO_COMMAND ZakoCommand_800DF280;
extern int          ZAKO11E_EYE_LENGTH_800C3904;

extern SVECTOR  DG_ZeroVector;
extern int      GM_ClaymoreMap_800AB9DC;
extern SVECTOR  GM_NoisePosition_800AB9F8;
extern int      GM_PlayerMap_800ABA0C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_NoisePower_800ABA24;
extern int      GM_NoiseLength_800ABA30;
extern int      GM_PlayerStatus_800ABA50;
extern CONTROL *GM_WhereList_800B56D0[94];

extern int AsiatoCheck_800D16C0( HZD_HDL*, SVECTOR* );
extern int SearchNearAsiato_800D13B0( HZD_HDL*, SVECTOR*, short, short, short );

void s11e_zk11ecom_800D80E0( ZakoWork* work )
{
    VISION     *vision = &work->vision;
    RADAR_CONE *cone   = &work->control.radar_cone;

    cone->dir = vision->facedir;
    cone->len = vision->length;
    cone->ang = vision->angle * 2;
    cone->_pad = 0;
}

extern int      GM_PlayerStatus_800ABA50;

void s11e_zk11ecom_800D810C( ZakoWork *work )
{
    unsigned short flags;
    if ( !( work->field_BA3 & 4 ) )
    {
        return;
    }

    flags = work->target->damaged;
    if ( flags & 6 )
    {
        work->field_BA2 |= 4;
        return;
    }

    flags = work->field_94C.damaged;
    if ( flags & 0x80 )
    {
        if ( ( GM_PlayerStatus_800ABA50 & 0x1010 ) == 0x1000 )
        {
            return;
        }
        work->field_BA2 |= 12;
    }
}

int s11e_zk11ecom_800D8190( HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2 )
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

extern int GM_ClaymoreMap_800AB9DC;
extern int GM_PlayerMap_800ABA0C;

void s11e_zk11ecom_800D81F0( ZakoWork* work )
{
    CONTROL *ctrl;
    if ( !( work->field_BA3 & 1 ) )
    {
        return;
    }

    if ( work->act_status & 0x68 )
    {
        return;
    }

    ctrl = &work->control;


    if ( !( ctrl->map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    if ( !GM_NoisePower_800ABA24 )
    {
        return;
    }

    switch ( GM_NoisePower_800ABA24 )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &ctrl->mov ) < 500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &ctrl->mov ) < 8000 )
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &ctrl->mov ) < 8000 && s11e_zk11ecom_800D8190( ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition_800AB9F8 ) < 300  )
        {
            work->field_BA2 |= 1;
            GM_NoiseLength_800ABA30 = 0;
            GM_NoisePower_800ABA24  = 0;
            return;
        }
        return;
    default:
        return;
    }
    work->field_BA2 |= 1;
}

void s11e_zk11ecom_800D8370( ZakoWork *work )
{

    if ( work->field_BA3 & 2 && work->vision.field_B92 == 2 && ( ( GM_PlayerStatus_800ABA50 & 0x1000 ) == 0x1000 ) )
    {
        if ( ( GV_DiffVec3( &work->field_BA4, &GM_PlayerPosition_800ABA10 ) > 50 ) || ( work->field_BAC != GM_WhereList_800B56D0[0]->rot.vy ) )
        {
            if ( ZakoCommand_800DF280.mode != TOP_COMM_ALERT )
            {
                work->field_BA4 = GM_PlayerPosition_800ABA10;
                work->field_BAC = GM_WhereList_800B56D0[0]->rot.vy;
                work->field_BA2 |= 0x2;
            }
            else
            {
                return;
            }
        }
        else
        {
            if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition_800ABA10 ) < 1500 )
            {
                work->field_BA2 |= 0x40;
            }
        }
        work->vision.field_B92 = 0;
        work->field_BA2 |= 0x80;
    }
}

void s11e_zk11ecom_800D8498( ZakoWork* work )
{
    HZD_HDL *hzd;
    CONTROL *ctrl;
    VISION  *vision;

    if ( !( work->field_BA3 & 16 ) )
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
    if ( !( AsiatoCheck_800D16C0( hzd, &ctrl->mov ) ) )
    {
        return;
    }

    if ( SearchNearAsiato_800D13B0( hzd, &ctrl->mov, vision->facedir, vision->angle, vision->length ) < 0 )
    {
        return;
    }

    work->field_BA2 |= 16;
}

void s11e_zk11ecom_800D8544( ZakoWork* work )
{
    work->field_BA2 = 0;
    s11e_zk11ecom_800D81F0( work );

    if ( ZakoCommand_800DF280.mode != TOP_COMM_ALERT )
    {
        s11e_zk11ecom_800D810C( work );
        s11e_zk11ecom_800D8370( work );
        s11e_zk11ecom_800D8498( work );
    }
}

void s11e_zk11ecom_800D8598( ZakoWork* work )
{
    int val;
    val = work->vision.field_B92;
    switch ( val )
    {
        case 0:
            if ( work->field_B94 != 2 || !( GM_PlayerStatus_800ABA50 & 2 ) || work->vision.length == 0 )
            {
                work->field_B94 = 0;
                work->alert_level -= 4;
            }
            break;
        case 1:
            work->field_B94 = val;
            work->alert_level -= 1;
            break;
        case 2:
            work->field_B94 = val;
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

void s11e_zk11ecom_800D8668( ZakoWork* work )
{
    int dir;
    int dis;
    int diff;
    SVECTOR *pos;
    SVECTOR svec;
    CONTROL *ctrl;
    MAP *map;

    ctrl = &work->control;
    pos = &GM_PlayerPosition_800ABA10;
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

    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) || GM_PlayerStatus_800ABA50 & 2 )
    {
        work->vision.field_B92 = 0;
        return;
    }

    if ( ZakoCommand_800DF280.field_0x0C % ZakoCommand_800DF280.field_0x08 == work->field_B74 )
    {
        //ridiculous, but its the only way it matches
        if ( ZAKO11E_EYE_LENGTH_800C3904 + 2000 >= dis )
        {
            if ( 2000 >= diff )
            {
                if ( dis < 500 || GV_DiffDirAbs( work->vision.facedir, dir ) < work->vision.angle )
                {
                    map = work->control.map;
                    if ( !( HZD_80028454( map->hzd, pos, &ctrl->mov, 0xF, 0x4 ) ) )
                    {
                        if ( !( sub_8002E2A8( &ctrl->mov, pos, map->index, &svec ) ) )
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

extern void Zako11EThink_800D99B8( ZakoWork * );
extern void s11e_zk11ecom_800D6DDC( ZakoWork * );
extern void ZAKO11E_ExecPutChar_800D8080( ZakoWork* work );

void Zako11EActionMain_800D8830( ZakoWork *work )
{
     if ( work->field_8E0 < 0x31 )
     {
        s11e_zk11ecom_800D80E0( work );
        s11e_zk11ecom_800D8668( work );
        s11e_zk11ecom_800D8544( work );
        s11e_zk11ecom_800D8598( work );
        Zako11EThink_800D99B8( work );
        ZAKO11E_ExecPutChar_800D8080( work );
    }

    s11e_zk11ecom_800D6DDC( work );
}

void Zako11EPushMove_800D889C( ZakoWork *work )
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

    GV_AddVec3( &target->field_34_vec, &work->control.step, &work->control.step );
    target->damaged &= ~( 0x8 );

    if ( work->field_8E0 - 1 >= 2u )
    {
        return;
    }

    if ( target->field_34_vec.pad )
    {
        if ( GV_Time & 256 )
        {
            s1 = target->field_34_vec.pad * 1024;
            if ( !( work->field_B74 & 1 ) )
            {
                s1 = ( target->field_34_vec.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->field_B74 & 1 )
            {
                s1 = ( target->field_34_vec.pad + 2 ) * 1024;
            }
            else
            {
                s1 = target->field_34_vec.pad * 1024;
            }
        }
        s1 &= 0xFFF;
    }

    ctrl = &work->control;
    ctrl->turn.vy = s1;
    ctrl->field_36 = GV_NearExp2( ctrl->field_36, work->field_8E4 );
}