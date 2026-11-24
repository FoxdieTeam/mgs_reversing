#include "zako.h"

#include "mts/mts.h" // for fprintf
#include "enemy/asiato.h"

/*---------------------------------------------------------------------------*/

static SVECTOR s03d_dword_800C3AB0 = {8000, 0, -1000};

/*---------------------------------------------------------------------------*/

static void Zako_800D0FCC( Work *work )
{
    VISION *vision;
    RADAR_SIGHT_PARAM *r_param;

    vision = &work->vision;
    r_param = &work->control.radar_param;

    r_param->dir = vision->facedir;
    r_param->dis = vision->length;
    r_param->range = vision->range;
    r_param->r = 0;
}

void Zako_800D0FF4( Work *work )
{
    if ( work->modetime[ 7 ] & 0x4 )
    {
        if ( work->target->damaged & ( TARGET_POWER | TARGET_CAPTURE ) )
        {
            work->modetime[ 6 ] |= 0x4;
        }

        if ( work->attack.damaged & TARGET_TOUCH )
        {
            work->vision.pad = 2;
        }
    }
}

static int ZoneDist( HZD_HDL *hzd, SVECTOR *from, SVECTOR *to )
{
    int z1, z2;

    z1 = HZD_GetAddress( hzd, from, -1 );
    z2 = HZD_GetAddress( hzd, to, -1 );
    z1 &= 0xFF;
    z2 &= 0xFF;
    return HZD_ZoneDistance( hzd, z1, z2 );
}

void s03d_800D10B4( Work *work )
{
    CONTROL *ctrl;
    int dis;

    ctrl = &work->control;
    if ( ( work->modetime[ 7 ] & 0x1 )
         && ctrl->map->index == GM_PlayerMap
         && GM_NoisePower != 0 )
    {
        switch ( GM_NoisePower )
        {
        case 5:
            if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 500 )
            {
                work->modetime[ 6 ] |= 0x1;
            }
            break;
        case 200:
            if ( GV_DiffVec3( &GM_NoisePosition, &ctrl->mov ) < 4000 )
            {
                work->modetime[ 6 ] |= 0x1;
            }
            break;
        case 100:
            dis = GV_DiffVec3( &GM_NoisePosition, &ctrl->mov );
            fprintf( 1, "noise dis  =%d,\n", dis );

            if ( dis < 4000 )
            {
                dis = ZoneDist( ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition );
                if ( dis < 300 )
                {
                    work->modetime[ 6 ] |= 0x1;
                    GM_NoiseLength = 0;
                    GM_NoisePower = 0;
                }
            }
            break;
        case 255:
            work->modetime[ 6 ] |= 0x1;
            break;
        }
    }
}

void s03d_800D123C( Work *work )
{
    if ( ( work->modetime[ 7 ] & 0x2 )
         && work->vision.pad == 2
         && ( GM_PlayerStatus & PLAYER_CB_BOX ) )
    {
        if ( GV_DiffVec3( &work->player_pos, &GM_PlayerPosition ) > 50
             || work->player_dir != GM_WhereList[ 0 ]->rot.vy )
        {
            if ( ZAKOCommand.field_1C == 1 ) return;
            work->player_pos = GM_PlayerPosition;
            work->player_dir = GM_WhereList[ 0 ]->rot.vy;
            work->modetime[ 6 ] |= 0x2;
        }

        work->vision.pad = 0;
    }
}

void s03d_800D1324( Work *work )
{
    HZD_HDL *hzd;
    VISION *vis;

    if ( ( work->modetime[ 7 ] & 0x10 ) && work->think2 != 5 )
    {
        hzd = work->control.map->hzd;
        vis = &work->vision;

        if ( AsiatoCheck( hzd, &work->control.mov )
             && SearchNearAsiato( hzd, &work->control.mov, vis->facedir, vis->range, vis->length ) >= 0 )
        {
            work->modetime[ 6 ] |= 0x10;
            fprintf( 1, " Asiato mikke!! [%d]\n", NearAsiato() );
        }
    }
}

static void Zako_800D13E8( Work *work )
{
    SVECTOR unused[ 2 ];

    (void)unused;

    work->modetime[ 6 ] = 0;
}

static void s03d_800D13F8( Work *work )
{
    switch ( work->vision.pad )
    {
    case 0:
        if (work->alert_level != 255 || !(GM_PlayerStatus & PLAYER_INTRUDE) )
        {
            work->alert_level -= 4;
        }
        break;
    case 1:
        work->alert_level--;
        break;
    case 2:
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

static void s03d_800D14AC( Work *work )
{
    SVECTOR diff;
    int height;

    GV_SubVec3( &s03d_dword_800C3AB0, &work->control.mov, &diff );
    work->field_B98 = GV_VecDir2( &diff );

    GV_SubVec3( &GM_PlayerPosition, &work->control.mov, &diff );
    diff.vy = 0;
    work->sn_dir = GV_VecDir2( &diff );
    work->sn_dis = GV_VecLen3( &diff );

    height = ABS( GM_PlayerPosition.vy - work->control.mov.vy );

#if 0
    // Compiled out code
#endif

    work->vision.pad = 2;
}

/*---------------------------------------------------------------------------*/

void ZakoActionMain( Work *work )
{
    if ( work->act.motion1 < 45 )
    {
        Zako_800D0FCC( work );
        s03d_800D14AC( work );
        Zako_800D13E8( work );
        s03d_800D13F8( work );
        ZakoThink( work );
        ZAKO_ExecPutChars( work );
    }

    ZAKO_Action( work );
}

void ZakoPushMove( Work *work )
{
    int turn, action;
    TARGET *trg;
    CONTROL *ctrl;

    turn = 0;
    trg = work->target;

    if ( trg->damaged & TARGET_PUSH )
    {
        GV_AddVec3( &trg->offset, &work->control.step, &work->control.step );
        trg->damaged &= ~TARGET_PUSH;

        action = work->act.motion1;
        if ( action == 1 || action == 2 )
        {
            if ( trg->offset.pad != 0 )
            {
                if ( ( GV_Time & 0x100 ) != 0 )
                {
                    if ( work->param.index & 0x1 )
                    {
                        turn = trg->offset.pad * 1024;
                    }
                    else
                    {
                        turn = ( trg->offset.pad + 2 ) * 1024;
                    }
                }
                else
                {
                    if ( work->param.index & 0x1 )
                    {
                        turn = ( trg->offset.pad + 2 ) * 1024;
                    }
                    else
                    {
                        turn = trg->offset.pad * 1024;
                    }
                }

                turn &= 4095;
            }

            ctrl = &work->control;
            ctrl->turn.vy = turn;
            ctrl->r_sphere = GV_NearExp2( ctrl->r_sphere, work->act.field_1A );
        }
    }
}
