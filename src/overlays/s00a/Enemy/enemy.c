#include "enemy.h"

void s00a_command_800C9878( WatcherWork* work )
{
    VISION  *vision = &work->vision;
    SVECTOR *svec   = &work->control.field_3C;
    
    svec->vx = vision->facedir;
    svec->vy = vision->length;
    svec->vz = vision->field_B8E * 2;
    svec->pad = 0;
}

extern int GM_PlayerStatus_800ABA50;

void s00a_command_800C98A4( WatcherWork *work )
{
    unsigned short flags;
    if ( !( work->field_BA3 & 4 ) )
    {
        return;
    }

    flags = work->target->field_6_flags;
    if ( flags & 6 )
    {
        work->field_BA1 |= 4;
        return;
    }

    flags = work->field_94C.field_6_flags;
    if ( flags & 0x80 )
    {
        work->field_94C.field_6_flags &= ~( 0x80 );
        if ( ( GM_PlayerStatus_800ABA50 & 0x1010 ) == 0x1000 )
        {
            return;
        }
        work->field_BA1 |= 12;
    }    
}

extern int GM_NoisePower_800ABA24;
extern int dword_800ABA0C;
extern int claymore_map_800AB9DC;
extern SVECTOR GM_NoisePosition_800AB9F8;
extern int COM_NOISEMODE_DIS_800E0F38;
extern int COM_NoiseMinDisID_800E0D44;
extern int GM_NoiseLength_800ABA30;

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
    if ( !GM_NoisePower_800ABA24 )
    {
        return;
    }
    
    
    
    if ( GM_NoisePower_800ABA24 == 0xFF )
    {
        
        if ( !( ctrl->field_2C_map->field_0_map_index_bit & claymore_map_800AB9DC ) && 
           ( !( ctrl->field_2C_map->field_0_map_index_bit & dword_800ABA0C ) || 
             !( claymore_map_800AB9DC & dword_800ABA0C ) ) )
        {
            return;
        }
    }
    else
    {
        if ( !( ctrl->field_2C_map->field_0_map_index_bit & dword_800ABA0C ) )
        {
            return;
        }
    }

    switch ( GM_NoisePower_800ABA24 )
    {
    case 5:
        if ( GV_DistanceVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < 1500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DistanceVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < COM_NOISEMODE_DIS_800E0F38 )
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
            GM_NoiseLength_800ABA30 = 0;
            GM_NoisePower_800ABA24  = 0;
            return;
        }
        return;
    default: 
        return;
    }
    work->field_BA1 |= 1;
}

extern SVECTOR GM_PlayerPosition_800ABA10;
extern CONTROL *GM_WhereList_800B56D0[94];

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

    if ( work->vision.field_B92 == 2 && ( ( GM_PlayerStatus_800ABA50 & 0x1010 ) == 0x1000 ) )
    {
        if ( ( GV_DistanceVec3_80016E84( &work->field_BA4, &GM_PlayerPosition_800ABA10 ) > 50 ) || ( work->field_BAC != GM_WhereList_800B56D0[0]->field_8_rotator.vy ) )
        {
            if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
            {
                work->field_BA4 = GM_PlayerPosition_800ABA10;
                work->field_BAC = GM_WhereList_800B56D0[0]->field_8_rotator.vy;
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
            if ( GV_DistanceVec3_80016E84( &work->control.field_0_mov, &GM_PlayerPosition_800ABA10 ) < 1500 )
            {
                work->field_BA2 |= 0x40;
            }
        }      
        work->vision.field_B92 = 0;
        work->field_BA2 |= 0x80;
    }
    
    work->field_BA1 |= work->field_BA2;
}

extern int AsiatoCheck_800D16C0( HZD_HDL*, SVECTOR* );
extern int SearchNearAsiato_800D13B0( HZD_HDL*, SVECTOR*, short, short, short );

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

    hzd = work->control.field_2C_map->field_8_hzd;
    vision = &work->vision;
    if ( !( AsiatoCheck_800D16C0( hzd, &ctrl->field_0_mov ) ) )
    {
        return;
    }
    
    if ( SearchNearAsiato_800D13B0( hzd, &ctrl->field_0_mov, vision->facedir, vision->field_B8E, vision->length ) < 0 )
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