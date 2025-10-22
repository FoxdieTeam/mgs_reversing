#include "enemy.h"

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "linkvar.h"
#include "strcode.h"

#define SEGMENT_ATR ( HZD_SEG_NO_PLAYER )

extern CONTROL *GM_WhereList[94];

extern ENEMY_COMMAND EnemyCommand_800E0D98;

extern int       COM_NOISEMODE_DIS_800E0F38;
extern int       COM_NoiseMinDisID_800E0D44;
extern int       COM_ALERT_DECREMENT_800E0F60;
extern int       COM_EYE_LENGTH_800E0D8C;

extern int sna_current_item_8004FB38(void);
extern int AsiatoCheck_800D16C0( HZD_HDL*, SVECTOR* );
extern int SearchNearAsiato_800D13B0( HZD_HDL*, SVECTOR*, short, short, short );

void s00a_command_800C9878( WatcherWork* work )
{
    VISION     *vision = &work->vision;
    RADAR_CONE *cone   = &work->control.radar_cone;

    cone->dir = vision->facedir;
    cone->len = vision->length;
    cone->ang = vision->angle * 2;
    cone->_pad = 0;
}

void s00a_command_800C98A4( WatcherWork *work )
{
    unsigned short flags;
    if ( !( work->field_BA3 & 4 ) )
    {
        return;
    }

    flags = work->target->damaged;
    if ( flags & 6 )
    {
        work->field_BA1 |= 4;
        return;
    }

    flags = work->field_94C.damaged;
    if ( flags & 0x80 )
    {
        work->field_94C.damaged &= ~( 0x80 );
        if ( ( GM_PlayerStatus & ( PLAYER_MOVE | PLAYER_CB_BOX ) ) == PLAYER_CB_BOX )
        {
            return;
        }
        work->field_BA1 |= 12;
    }
}

void s00a_command_800C9930( WatcherWork* work )
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
    if ( !GM_NoisePower )
    {
        return;
    }



    if ( GM_NoisePower == 0xFF )
    {

        if ( !( ctrl->map->index & GM_ClaymoreMap ) &&
           ( !( ctrl->map->index & GM_PlayerMap ) ||
             !( GM_ClaymoreMap & GM_PlayerMap ) ) )
        {
            return;
        }
    }
    else
    {
        if ( !( ctrl->map->index & GM_PlayerMap ) )
        {
            return;
        }
    }

    switch ( GM_NoisePower )
    {
    case 5:
        if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 1500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < COM_NOISEMODE_DIS_800E0F38 )
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        if ( work->field_B78 == COM_NoiseMinDisID_800E0D44 )
        {
            work->field_BA1 |= 1;
            GM_NoiseLength = 0;
            GM_NoisePower  = 0;
            return;
        }
        return;
    default:
        return;
    }
    work->field_BA1 |= 1;
}

void s00a_command_800C9ACC( WatcherWork *work )
{
    if ( !( work->field_BA3 & 2 ) )
    {
        return;
    }

    if ( EnemyCommand_800E0D98.mode == 2 && EnemyCommand_800E0D98.field_0x10 == 300 )
    {
        return;
    }

    if ( EnemyCommand_800E0D98.field_0x0C % EnemyCommand_800E0D98.field_0x08 == work->field_B78 )
    {
        work->field_BA2 = 0;
    }

    if ( work->vision.field_B92 == 2 && ( ( GM_PlayerStatus & ( PLAYER_MOVE | PLAYER_CB_BOX ) ) == PLAYER_CB_BOX ) )
    {
        if ( ( GV_DiffVec3( &work->field_BA4, &GM_PlayerPosition ) > 50 ) || ( work->field_BAC != GM_WhereList[0]->rot.vy ) )
        {
            if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
            {
                work->field_BA4 = GM_PlayerPosition;
                work->field_BAC = GM_WhereList[0]->rot.vy;
                work->field_BA1 |= 0x2;
            }
            else
            {
                work->field_BA1 |= work->field_BA2;
                return;
            }
        }
        else
        {
            if ( GV_DiffVec3( &work->control.mov, &GM_PlayerPosition ) < 1500 )
            {
                work->field_BA2 |= 0x40;
            }
        }
        work->vision.field_B92 = 0;
        work->field_BA2 |= 0x80;
    }

    work->field_BA1 |= work->field_BA2;
}

void s00a_command_800C9C7C( WatcherWork* work )
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

    work->field_BA1 |= 16;
}

void s00a_command_800C9D28( WatcherWork* work )
{
    work->field_BA1 = 0;
    s00a_command_800C9930( work );

    if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
    {
        s00a_command_800C98A4( work );
        s00a_command_800C9ACC( work );
        s00a_command_800C9C7C( work );
    }
}

void s00a_command_800C9D7C( WatcherWork* work )
{
    int val;
    val = work->vision.field_B92;
    switch ( val )
    {
        case 0:
            if ( work->field_B94 != 2 || GM_PlayerStatus & PLAYER_HIDDEN || !( GM_PlayerStatus & ( PLAYER_INTRUDE | PLAYER_NOHIDDEN ) ) || work->vision.length == 0 )
            {
                work->field_B94 = 0;
                work->alert_level -= COM_ALERT_DECREMENT_800E0F60;
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

void s00a_command_800C9E68( WatcherWork* work )
{
    int x;
    int dir;
    int dis;
    int diff;
    short *flag;
    SVECTOR *pos;
    SVECTOR svec;
    CONTROL *ctrl;
    MAP *map;

    flag = &work->vision.field_B92;
    ctrl = &work->control;
    pos = &GM_PlayerPosition;
    GV_SubVec3( pos, &ctrl->mov, &svec );

    dir = GV_VecDir2( &svec );
    work->sn_dir = dir;
    dis = GV_VecLen3( &svec );

    work->sn_dis = dis;
    if ( dis == 0 )
    {
        dis = 1;
    }

    diff = pos->vy - work->control.mov.vy;
    if ( diff < 0 )
    {
        diff = work->control.mov.vy - pos->vy;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) || GM_PlayerStatus & ( PLAYER_INTRUDE | PLAYER_HIDDEN ) )
    {
        work->vision.field_B92 = 0;
        return;
    }

    if ( EnemyCommand_800E0D98.field_0x0C % EnemyCommand_800E0D98.field_0x08 == work->field_B78 )
    {
        x = 2000;
        //ridiculous, but its the only way it matches
        if ( COM_EYE_LENGTH_800E0D8C + x >= dis )
        {
            if ( x >= diff )
            {
                if ( dis < 500 || GV_DiffDirAbs( work->vision.facedir, dir ) < work->vision.angle )
                {
                    map = work->control.map;
                    if ( !( HZD_LineCheck( map->hzd, pos, &ctrl->mov, HZD_CHECK_ALL, SEGMENT_ATR ) ) )
                    {
                        if ( !( sub_8002E2A8( &ctrl->mov, pos, map->index, &svec ) ) )
                        {
                            if ( work->vision.length < dis )
                            {
                                work->vision.field_B92 = 1;
                            }
                            else
                            {
                                flag[0] = 2;
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

    if ( sna_current_item_8004FB38() == IT_Stealth && work->param_blood != 83 )
    {
        flag[0] = 0;
    }
}

void EnemyActionMain_800CA07C( WatcherWork *work )
{
     if ( work->unknown.last_set < 0x31 )
     {
        s00a_command_800C9878( work );
        s00a_command_800C9E68(work);
        s00a_command_800C9D28(work);
        s00a_command_800C9D7C(work);
        Enemy_Think_800CE99C(work);
        ENE_ExecPutChar_800C9818(work);
    }

    s00a_command_800C82B0(work);
}

void EnemyPushMove_800CA0E8( WatcherWork *work )
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
            if ( !( work->field_B78 & 1 ) )
            {
                s1 = ( target->offset.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->field_B78 & 1 )
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
    ctrl->step_size = GV_NearExp2( ctrl->step_size, work->unknown.field_1C );
}
