#include "../../s00a/Enemy/enemy.h"

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

extern ENEMY_COMMAND EnemyCommand_800E0D98;

extern int sna_current_item_8004FB38(void);
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

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAA00.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAA60.s")
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
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAEAC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAF00.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAFD8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DB1D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DB23C.s")
