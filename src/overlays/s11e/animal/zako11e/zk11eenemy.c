#include "../../../s00a/Enemy/enemy.h"

extern ZAKO_COMMAND ZakoCommand_800DF280;

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

extern int AsiatoCheck_800D16C0( HZD_HDL*, SVECTOR* );
extern int SearchNearAsiato_800D13B0( HZD_HDL*, SVECTOR*, short, short, short );


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D80E0.s")
void s11e_zk11ecom_800D80E0( ZakoWork* work )
{
    VISION  *vision = &work->vision;
    SVECTOR *svec   = &work->control.field_3C;

    svec->vx = vision->facedir;
    svec->vy = vision->length;
    svec->vz = vision->field_B8E * 2;
    svec->pad = 0;
}

extern int      GM_PlayerStatus_800ABA50;

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D810C.s")
void s11e_zk11ecom_800D810C( ZakoWork *work )
{
    unsigned short flags;
    if ( !( work->field_BA3 & 4 ) )
    {
        return;
    }

    flags = work->target->field_6_flags;
    if ( flags & 6 )
    {
        work->field_BA2 |= 4;
        return;
    }

    flags = work->field_94C.field_6_flags;
    if ( flags & 0x80 )
    {
        if ( ( GM_PlayerStatus_800ABA50 & 0x1010 ) == 0x1000 )
        {
            return;
        }
        work->field_BA2 |= 12;
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8190.s")
int s11e_zk11ecom_800D8190( HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2 )
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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D81F0.s")
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


    if ( !( ctrl->field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
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
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < 500 )
        {
            break;
        }
        return;
    case 200:
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < 8000 )
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        if ( GV_DiffVec3_80016E84( &GM_NoisePosition_800AB9F8, &ctrl->field_0_mov ) < 8000 && s11e_zk11ecom_800D8190( ctrl->field_2C_map->field_8_hzd, &ctrl->field_0_mov, &GM_NoisePosition_800AB9F8 ) < 300  )
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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8370.s")
void s11e_zk11ecom_800D8370( ZakoWork *work )
{

    if ( work->field_BA3 & 2 && work->vision.field_B92 == 2 && ( ( GM_PlayerStatus_800ABA50 & 0x1000 ) == 0x1000 ) )
    {
        if ( ( GV_DiffVec3_80016E84( &work->field_BA4, &GM_PlayerPosition_800ABA10 ) > 50 ) || ( work->field_BAC != GM_WhereList_800B56D0[0]->field_8_rot.vy ) )
        {
            if ( ZakoCommand_800DF280.mode != TOP_COMM_ALERT )
            {
                work->field_BA4 = GM_PlayerPosition_800ABA10;
                work->field_BAC = GM_WhereList_800B56D0[0]->field_8_rot.vy;
                work->field_BA2 |= 0x2;
            }
            else
            {
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
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8498.s")
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

    work->field_BA2 |= 16;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8544.s")
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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8598.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8668.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8830.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D889C.s")