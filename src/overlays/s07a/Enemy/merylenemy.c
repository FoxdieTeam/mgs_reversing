#include "../../s00a/Enemy/enemy.h"
#include "Game/linkvarbuf.h"

extern int      GV_Time_800AB330;
extern SVECTOR  DG_ZeroVector_800AB39C;
extern int      GM_ClaymoreMap_800AB9DC;
extern SVECTOR  GM_NoisePosition_800AB9F8;
extern int      GM_PlayerMap_800ABA0C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_NoisePower_800ABA24;
extern int      GM_NoiseLength_800ABA30;
extern int      GM_PlayerStatus_800ABA50;
extern CONTROL *GM_WhereList_800B56D0[94];

extern int COM_EYE_LENGTH_800E0D8C;
extern int COM_NOISEMODE_DIS_800E0F38;
extern int COM_ALERT_DECREMENT_800E0F60;

extern ENEMY_COMMAND EnemyCommand_800E0D98;

extern int sna_current_item_8004FB38();
extern int AsiatoCheck_800D16C0( HZD_HDL*, SVECTOR* );
extern int SearchNearAsiato_800D13B0( HZD_HDL*, SVECTOR*, short, short, short );

// Identical to s00a_command_800C9878
void s07a_meryl_unk_800DA948( WatcherWork* work )
{
    VISION  *vision = &work->vision;
    SVECTOR *svec   = &work->control.field_3C;

    svec->vx = vision->facedir;
    svec->vy = vision->length;
    svec->vz = vision->field_B8E * 2;
    svec->pad = 0;
}

// Identical to s00a_command_800C98A4
void s07a_meryl_unk_800DA974( WatcherWork *work )
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

int s07a_meryl_unk_800DAA00( HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2 )
{
    int from;
    int to;

    from = HZD_GetAddress_8005C6C4( hzd, pos, -1 );

    //TODO: fix
    do
    {
        to = HZD_GetAddress_8005C6C4( hzd, pos2, -1 );
            do   {
            return HZD_ZoneDistance_8005CD1C( hzd, from & 0xFF, to & 0xFF );
        } while (0);
    } while (0);
}

void s07a_meryl_unk_800DAA60( WatcherWork* work )
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

        if ( !( ctrl->field_2C_map->field_0_map_index_bit & GM_ClaymoreMap_800AB9DC ) &&
           ( !( ctrl->field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) ||
             !( GM_ClaymoreMap_800AB9DC & GM_PlayerMap_800ABA0C ) ) )
        {
            return;
        }
    }
    else
    {
        if ( !( ctrl->field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
        {
            return;
        }
    }

    switch ( GM_NoisePower_800ABA24 )
    {
    case 5:
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < 1500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < COM_NOISEMODE_DIS_800E0F38 )
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < COM_NOISEMODE_DIS_800E0F38 && ( s07a_meryl_unk_800DAA00( ctrl->field_2C_map->field_8_hzd, &ctrl->field_0_mov, &GM_NoisePosition_800AB9F8 ) < 300 ) )
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

// Based on s00a_command_800C9ACC, with one modification:
// GM_PlayerStatus_800ABA50 & 0x1010 -> GM_PlayerStatus_800ABA50 & 0x1000
void s07a_meryl_unk_800DAC50( WatcherWork *work )
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

    if ( work->vision.field_B92 == 2 && ( ( GM_PlayerStatus_800ABA50 & 0x1000 ) == 0x1000 ) )
    {
        if ( ( GV_DiffVec3_80016E84( &work->field_BA4, &GM_PlayerPosition_800ABA10 ) > 50 ) || ( work->field_BAC != GM_WhereList_800B56D0[0]->field_8_rot.vy ) )
        {
            if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
            {
                work->field_BA4 = GM_PlayerPosition_800ABA10;
                work->field_BAC = GM_WhereList_800B56D0[0]->field_8_rot.vy;
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
            if ( GV_DiffVec3_80016E84( &work->control.field_0_mov, &GM_PlayerPosition_800ABA10 ) < 1500 )
            {
                work->field_BA2 |= 0x40;
            }
        }
        work->vision.field_B92 = 0;
        work->field_BA2 |= 0x80;
    }

    work->field_BA1 |= work->field_BA2;
}

// Identical to s00a_command_800C9C7C
void s07a_meryl_unk_800DAE00( WatcherWork* work )
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

void s07a_meryl_unk_800DAEAC( WatcherWork* work )
{
    work->field_BA1 = 0;
    s07a_meryl_unk_800DAA60( work );

    if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
    {
        s07a_meryl_unk_800DA974( work );
        s07a_meryl_unk_800DAC50( work );
        s07a_meryl_unk_800DAE00( work );
    }
}

void s07a_meryl_unk_800DAF00( WatcherWork* work )
{
    int val;
    val = work->vision.field_B92;
    switch ( val )
    {
        case 0:
            if ( work->field_B94 != 2 || !( GM_PlayerStatus_800ABA50 & 2 ) || work->vision.length == 0 )
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

void s07a_meryl_unk_800DAFD8( WatcherWork* work )
{
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
    pos = &GM_PlayerPosition_800ABA10;
    GV_SubVec3_80016D40( pos, &ctrl->field_0_mov, &svec );

    dir = GV_VecDir2_80016EF8( &svec );
    work->sn_dir = dir;
    dis = GV_VecLen3_80016D80( &svec );

    work->sn_dis = dis;

    diff = pos->vy - work->control.field_0_mov.vy;
    if ( diff < 0 )
    {
        diff = work->control.field_0_mov.vy - pos->vy;
    }

    if ( !( work->control.field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) || GM_PlayerStatus_800ABA50 & 2 )
    {
        work->vision.field_B92 = 0;
        return;
    }

    if ( EnemyCommand_800E0D98.field_0x0C % EnemyCommand_800E0D98.field_0x08 == work->field_B78 )
    {
        //ridiculous, but its the only way it matches
        if ( COM_EYE_LENGTH_800E0D8C + 2000 >= dis )
        {
            if ( 2000 >= diff )
            {
                if ( dis < 500 || GV_DiffDirAbs_8001706C( work->vision.facedir, dir ) < work->vision.field_B8E )
                {
                    map = work->control.field_2C_map;
                    if ( !( sub_80028454( map->field_8_hzd, pos, &ctrl->field_0_mov, 0xF, 0x4 ) ) )
                    {
                        if ( !( sub_8002E2A8( &ctrl->field_0_mov, pos, map->field_0_map_index_bit, &svec ) ) )
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

    if ( GM_CurrentItemId == ITEM_STEALTH )
    {
        flag[0] = 0;
    }
}

extern void s07a_meryl_unk_800DF3A0( WatcherWork * );
extern void ENE_ExecPutChar_800D9DE8( WatcherWork* work );
extern void s07a_meryl_unk_800D952C( WatcherWork *work );

void EnemyActionMain_800DB1D0( WatcherWork *work )
{
     if ( work->field_8E0 < 0x31 )
     {
        s07a_meryl_unk_800DA948( work );
        s07a_meryl_unk_800DAFD8(work);
        s07a_meryl_unk_800DAEAC(work);
        s07a_meryl_unk_800DAF00(work);
        s07a_meryl_unk_800DF3A0(work);
        ENE_ExecPutChar_800D9DE8(work);
    }

    s07a_meryl_unk_800D952C(work);
}

void EnemyPushMove_800DB23C( WatcherWork *work )
{
    int s1;
    CONTROL *ctrl;
    TARGET *target;

    target = work->target;
    s1 = 0;
    if ( !( target->field_6_flags & 0x8 ) )
    {
        return;
    }

    GV_AddVec3_80016D00( &target->field_34_vec, &work->control.field_44_step, &work->control.field_44_step );
    target->field_6_flags &= ~( 0x8 );

    if ( work->field_8E0 - 1 >= 2u )
    {
        return;
    }

    if ( target->field_34_vec.pad )
    {
        if ( GV_Time_800AB330 & 256 )
        {
            s1 = target->field_34_vec.pad * 1024;
            if ( !( work->field_B78 & 1 ) )
            {
                s1 = ( target->field_34_vec.pad + 2 ) * 1024;
            }
        }
        else
        {
            if ( work->field_B78 & 1 )
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
    ctrl->field_4C_turn.vy = s1;
    ctrl->field_36 = GV_NearExp2_80026384( ctrl->field_36, work->field_8E4 );
}