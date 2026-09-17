#include "animal/zako11a/zako.h"

extern void s11a_800CD00C( Work *work );
extern void s11a_800D1B48( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE3C8.s")
void s11a_800CE3C8( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE428.s")
void s11a_800CE428( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE454.s")
void s11a_800CE454( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE4D8.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE538.s")
void s11a_800CE538( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE6B8.s")
void s11a_800CE6B8( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE7E0.s")
void s11a_800CE7E0( Work *work );

void s11a_800CE88C( Work *work )
{
    work->field_B98[ 6 ] = 0;
    s11a_800CE538( work );

    if ( ZAKO11ACommand.alert_mode != 1 )
    {
        s11a_800CE454( work );
        s11a_800CE6B8( work );
        s11a_800CE7E0( work );
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CE8E0.s")
void s11a_800CE8E0( Work *work );

void s11a_800CE9B0( Work *work )
{
    SVECTOR tmp;
    CONTROL *control;
    SVECTOR *pos;
    int dir, len, height;
    MAP *map;

    control = &work->control;
    pos = &GM_PlayerPosition;
    GV_SubVec3( pos, &control->mov, &tmp );

    dir = ratan2( pos->vx - work->control.mov.vx,
                  pos->vz - work->control.mov.vz ) & 4095;
    work->field_C30 = dir;

    len = GV_VecLen3( &tmp );
    work->field_C2C = len;

    height = ABS( pos->vy - work->control.mov.vy );

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        work->field_B8E = 0;
        return;
    }

    if ( GM_PlayerStatus & PLAYER_INTRUDE )
    {
        work->field_B8E = 0;
        return;
    }

    if ( ( ZAKO11ACommand.time % ZAKO11ACommand.n_watchers ) != work->param.index )
    {
        return;
    }

    if ( ( ZAKO11A_EYE_LENGTH + 2000 ) < len )
    {
        work->field_B8E = 0;
        return;
    }

    if ( height > 2000 )
    {
        work->field_B8E = 0;
        return;
    }

    if ( len >= 500 && GV_DiffDirAbs( work->field_B88, dir ) >= work->field_B8A )
    {
        work->field_B8E = 0;
        return;
    }

    map = work->control.map;
    if ( !HZD_OnlineHazardCheck( map->hzd, pos, &control->mov, HZD_CHK_ALL, HZD_SEG_NO_PLAYER ) &&
         !GM_OnlineTargetCheckAny( &control->mov, pos, map->index, &tmp ) )
    {
        if ( work->field_B8C < len )
        {
            work->field_B8E = 1;
        }
        else
        {
            work->field_B8E = 2;
        }
    }
    else
    {
        work->field_B8E = 0;
    }
}

void Zako11AActionMain( Work *work )
{
    if ( work->act.last_set <= 48 )
    {
        s11a_800CE428( work );
        s11a_800CE9B0( work );
        s11a_800CE88C( work );
        s11a_800CE8E0( work );
        s11a_800D1B48( work );
        s11a_800CE3C8( work );
    }

    s11a_800CD00C( work );
}

void Zako11APushMove( Work *work )
{
    TARGET *trg;
    int turn, last_set;
    CONTROL *control;

    trg = work->target;
    turn = 0;

    if ( !( trg->damaged & TARGET_PUSH ) ) return;

    GV_AddVec3( &trg->offset, &work->control.step, &work->control.step );
    trg->damaged &= ~TARGET_PUSH;

    last_set = work->act.last_set;
    if ( last_set == 1 || last_set == 2 )
    {
        if ( trg->offset.pad != 0 )
        {
            if ( GV_Time & 256 )
            {
                if ( work->param.index & 1 )
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
                if ( work->param.index & 1 )
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

        control = &work->control;
        control->turn.vy = turn;
        control->r_sphere = GV_NearExp2( control->r_sphere, work->act.field_1C );
    }
}
