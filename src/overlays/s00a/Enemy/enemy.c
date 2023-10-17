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