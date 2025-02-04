#include <stdio.h>

#include "meryl72.h"

extern int GV_Time;

#define TH1_PHASE0 0
#define TH1_PHASE1 1
#define TH1_PHASE2 2
#define TH1_PHASE3 3

void s03b_boxall_800C969C(int map, int name);
void s03b_boxall_800C96E8(void);

void s07c_meryl72_unk2_800CC9A8(Meryl72Work *work)
{
    work->target_addr = work->player_addr;
    work->target_pos  = work->player_pos;
    work->target_map  = work->player_map;
}

void s07c_meryl72_unk2_800CC9E0(Meryl72Work *work)
{
    int x;

    x = work->next_node + 1;
    if ( x >= work->n_patrols )
    {
        x = 0;
    }
    work->next_node   = x;
    work->target_pos  = work->nodes[ x ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map  = work->start_map;
}

void s07c_meryl72_unk2_800CCA68(Meryl72Work *work)
{
    work->target_pos  = work->nodes[ work->next_node ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map  = work->start_map;
}

void s07c_meryl72_unk2_800CCAD8( Meryl72Work* work )
{
    work->target_pos.vx = -5500;
    work->target_pos.vz = -18000;
    work->target_pos.vy =  0;
    work->target_addr   = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map    = work->start_map;
}

void s07c_meryl72_unk2_800CCB2C( Meryl72Work *work, int index )
{
    int proc_id;

    proc_id = work->fC1C[ index ];
    if ( proc_id >= 0 )
    {
        GCL_ExecProc( proc_id, NULL );
    }
}

int s07c_meryl72_unk2_800CCB64( Meryl72Work *work )
{
    SVECTOR  diff;
    SVECTOR *mov;
    HZD_HDL *hzd;
    int      to_addr, from_addr;
    int      reach;
    int      link;
    HZD_ZON *zone;

    mov = &work->control.mov;
    hzd = work->control.map->hzd;

    to_addr = work->target_addr;
    from_addr = HZD_GetAddress( hzd, mov, work->fB5C );

    work->fB5C = from_addr;
    reach = HZD_ReachTo( hzd, from_addr, work->fB60 );

    if ( to_addr != work->fB4C || reach <= 0 )
    {
        work->fB4C = to_addr;

        if ( HZD_ReachTo( hzd, from_addr, to_addr ) < 2 )
        {
            work->fB6C = work->target_pos;
            work->fB60 = to_addr;
            GV_SubVec3(&work->fB6C, mov, &diff);
            work->pad.dir = GV_VecDir2(&diff);
            return -1;
        }

        link = HZD_LinkRoute( hzd, from_addr, to_addr, mov );
        zone = &hzd->header->zones[ link ];

        work->fB6C.vx = zone->x;
        work->fB6C.vy = zone->y;
        work->fB6C.vz = zone->z;

        work->fB60 = ( link & 0xff ) | ( ( link & 0xff ) << 8 );
    }

    GV_SubVec3( &work->fB6C, &work->control.mov, &diff );
    return GV_VecDir2( &diff );
}

int s07c_meryl72_unk2_800CCCC8( Meryl72Work *work )
{
    if ( ( work->count3 % 32 ) == 0 )
    {
        work->fB5C = -1;
        work->fB4C = -1;
        s07c_meryl72_unk2_800CCB64( work );
    }

    work->pad.dir = s07c_meryl72_unk2_800CCB64( work );
    return work->pad.dir < 0;
}

int s07c_meryl72_unk2_800CCD1C(Meryl72Work *work, int range)
{
    SVECTOR diff;
    int     dx, dz;

    diff.vx = dx = work->target_pos.vx - work->control.mov.vx;
    diff.vz = dz = work->target_pos.vz - work->control.mov.vz;

    if (dx > -range && dx < range && dz > -range && dz < range)
    {
        return 1;
    }

    work->pad.dir = GV_VecDir2(&diff);
    return 0;
}

void s07c_meryl72_unk2_800CCD98( Meryl72Work *work )
{
    if ( !work->fB96 )
    {
        if ( work->count3 == 0 )
        {
            s07c_meryl72_unk2_800CCB2C( work, 1 ) ;
            GM_GameStatus |= PLAYER_SECOND_AVAILABLE;
        }

        if ( work->count3 == 1 )
        {
            work->pad.dir = work->sn_dir;
            GM_GameStatus |= ( PLAYER_SECOND_AVAILABLE | PLAYER_WEAPON_DISABLE | PLAYER_TIMERBOMB_THROWN | PLAYER_CHECK_WALL | PLAYER_GAME_OVER ) ;
        }

        if ( work->count3 == 60 )
        {
            GM_VoxStream( work->voices[ 0 ], 0 ) ;
        }

        if ( work->count3 > 60 && GM_StreamStatus() == -1 )
        {
            s07c_meryl72_unk2_800CCB2C( work, 0 );
            s07c_meryl72_unk2_800CCB2C( work, 4 );
            work->think3 = 1;
            work->count3 = 0;
            return;
        }
    }
    else
    {
        work->next_node = 2;
        s07c_meryl72_unk2_800CC9E0( work );
        work->think1 = 1;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        return;
    }
    work->count3++;
}

void s07c_meryl72_unk2_800CCEC4(Meryl72Work *work)
{
    if (work->count3 > 30 && GM_StreamStatus() == -1)
    {
        if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
        {
            GM_VoxStream(work->voices[6], 0);
        }

        work->think3 = 4;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CCF5C(Meryl72Work *work)
{
    if (work->count3 > 60 && GM_StreamStatus() == -1)
    {
        work->think2 = 1;
        work->think3 = 2;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CCFE0(Meryl72Work *work)
{
    if (work->fC08 == 2)
    {
        work->think3 = 2;
        work->count3 = 0;
    }
    else if (work->count3 > 6000 && work->act_status & 0x1)
    {
        work->think3 = 2;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CD038(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->count3 == 0)
    {
        if (GM_PlayerStatus & (PLAYER_GROUND | PLAYER_SQUAT))
        {
            work->pad.press |= 0x800000;
        }
        else if (GM_PlayerStatus & PLAYER_CB_BOX)
        {
            work->pad.press |= 0x1000000;

            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(work->voices[12], 0);
            }
        }
        else
        {
            work->pad.press |= 0x400000;
        }

        work->fC0E -= 2;
        if (work->fC0E < 0)
        {
            work->fC0E = 0;
        }

        printf(" binta dis=%d\n", work->sn_dis);
    }

    if (work->fC08 == 3)
    {
        work->think3 = 8;
        work->count3 = 0;
    }
    else if (work->count3 > 300)
    {
        work->think3 = 8;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CD14C(Meryl72Work *work)
{
    int tick;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if (work->fC08 == 1)
    {
        work->think3 = 6;
        work->count3 = 0;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
        }
    }
    else
    {
        if (work->count3 == 0 && GM_StreamStatus() == -1)
        {
            tick = GV_Time % 2;
            GM_VoxStream(work->voices[13 + tick], 0);
        }

        if (work->count3 > 30)
        {
            if (GM_StreamStatus() == -1)
            {
                s07c_meryl72_unk2_800CCA68(work);
                work->think2 = 2;
                work->think3 = 4;
                work->count3 = 0;
            }
        }
        else
        {
            work->count3++;
        }
    }
}

void s07c_meryl72_unk2_800CD260(Meryl72Work *work)
{
    if (work->count3 == 0)
    {
        s07c_meryl72_unk2_800CC9E0(work);
    }

    if (s07c_meryl72_unk2_800CCD1C(work, 350))
    {
        if (work->next_node == 2)
        {
            work->think3 = 4;
            work->count3 = 0;
            return;
        }

        s07c_meryl72_unk2_800CC9E0(work);
    }

    work->count3++;
}

void s07c_meryl72_unk2_800CD2E0(Meryl72Work *work)
{
    if (work->count3 == 0)
    {
        s07c_meryl72_unk2_800CC9E0(work);
    }

    if (work->count3 == 30)
    {
        GM_GameStatus &= ~STATE_PADRELEASE;
        GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
        s03b_boxall_800C96E8();
    }

    if (s07c_meryl72_unk2_800CCD1C(work, 350))
    {
        work->think3 = 4;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

int s07c_meryl72_unk2_800CD380(SVECTOR *pos)
{
    if (pos->vx < 5500 || pos->vx > 7000 || pos->vz < -10500 || pos->vz > -8000)
    {
        return 0;
    }

    return 1;
}

int s07c_meryl72_unk2_800CD3C4(SVECTOR *pos)
{
    if (pos->vx < 5500 || pos->vx > 7000 || pos->vz < -8500 || pos->vz > -7000)
    {
        return 0;
    }

    return 1;
}

void s07c_meryl72_unk2_800CD408(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("スネーク");
    msg.message[0] = GV_StrCode("run_move");
    msg.message[1] = 6500;
    msg.message[2] = 500;
    msg.message[3] = 58036;
    msg.message[4] = 500;
    msg.message[5] = 0;
    msg.message[6] = 0;
    msg.message_len = 7;

    GV_SendMessage(&msg);
}

void s07c_meryl72_unk2_800CD474(Meryl72Work *work)
{
    switch (work->fAF4)
    {
    case 0:
        if (work->count3 == 0)
        {
            work->pad.dir = 3076;
            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
        }

        if (s07c_meryl72_unk2_800CD380(&GM_PlayerPosition) && GM_SnakeCurrentHealth != 0)
        {
            s07c_meryl72_unk2_800CD408();
            s03b_boxall_800C969C(0, 60000);
            work->fAF4 = 100;
            work->count3 = 0;
            GM_GameStatus |= STATE_PADRELEASE;
            GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
        }
        break;

    case 100:
        if (work->count3 > 30 && (s07c_meryl72_unk2_800CD3C4(&GM_PlayerPosition) || work->count3 > 120) && work->act_status & 0x1)
        {
            work->pad.dir = work->sn_dir;

            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(work->voices[1], 0);
            }

            s07c_meryl72_unk2_800CCB2C(work, 2);
            work->fAF4 = 1;
        }
        break;

    case 101:
        break;

    case 1:
        if (work->count3 < 140)
        {
            work->pad.press |= 0x2000000;
        }

        if (work->count3 > 60 && GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->voices[2], 0);
            work->count3 = 0;
            work->fAF4 = 2;
            s07c_meryl72_unk2_800CCB2C(work, 3);
            return;
        }

        if (GM_GameOverTimer != 0)
        {
            if (GM_StreamStatus() != -1)
            {
                GM_StreamPlayStop();
            }

            s07c_meryl72_unk2_800CCB2C(work, 4);
            work->fAF4 = 255;
        }
        break;

    case 2:
        if (work->count3 > 60 && GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->voices[3], 0);
            work->count3 = 0;
            work->fAF4 = 3;
        }

        if (GM_GameOverTimer != 0)
        {
            if (GM_StreamStatus() != -1)
            {
                GM_StreamPlayStop();
            }

            s07c_meryl72_unk2_800CCB2C(work, 4);
            work->fAF4 = 255;
        }
        break;

    case 3:
        if (work->count3 > 60 && GM_StreamStatus() == -1)
        {
            s07c_meryl72_unk2_800CCB2C(work, 4);
            work->think1 = 1;
            work->think2 = 2;
            work->think3 = 1;
            work->count3 = 0;
            work->fC04 = 0;
            return;
        }
        break;
    }

    work->count3++;
}

int s07c_meryl72_unk2_800CD76C(int xmin, int zmin, int xmax, int zmax)
{
    int x, z;

    if (!(GM_PlayerStatus & PLAYER_CAUTION))
    {
        return 0;
    }

    x = GM_PlayerPosition.vx;
    z = GM_PlayerPosition.vz;

    if (x < xmin || x > xmax || z < zmin  || z > zmax)
    {
        return 0;
    }

    return 1;
}

int s07c_meryl72_unk2_800CD7C4(void)
{
    if (GM_PlayerPosition.vz < -14000 &&
        GM_PlayerPosition.vx > -6000 &&
        GM_PlayerPosition.vx < -4000)
    {
        return 1;
    }

    return 0;
}

void s07c_meryl72_unk2_800CD80C(Meryl72Work *work)
{
    CONTROL *control;

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (GM_StreamStatus() != -1)
    {
        work->count3 = 0;
    }

    if (work->count3 > 60)
    {
        if (s07c_meryl72_unk2_800CD76C(-1000, -9000, 1500, -8500))
        {
            if (work->fC10[0] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[4], 0);
                }

                work->fC10[0] = 1800;
            }
        }
        else if (s07c_meryl72_unk2_800CD76C(5500, -9000, 7000, -8500))
        {
            if (work->fC10[1] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[5], 0);
                }

                work->fC10[1] = 1800;
            }
        }
        else if (s07c_meryl72_unk2_800CD76C(-9000, -9000, -7500, -8500))
        {
            if (work->fC10[2] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[5], 0);
                }

                work->fC10[2] = 1800;
            }
        }
    }

    if (work->count3 > 60 && work->fC0A > 150)
    {
        work->think3 = 5;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
    else if (work->fC04 > 3600 || s07c_meryl72_unk2_800CD7C4())
    {
        work->think1 = 2;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        work->fC04 = 0;
    }
    else
    {
        if ((work->count3 % 32) == 0)
        {
            control = &work->control;
            if (!HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[0]))
            {
                work->think3 = 2;
                work->count3 = 0;
            }
        }

        work->pad.press |= 0x10000;
        work->pad.dir = work->sn_dir;
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CDA88(Meryl72Work *work)
{
    work->fC0A = 0;

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
        }

        return;
    }

    if (work->count3 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
            {
                GM_VoxStream(work->voices[work->fC0C + 7], 0);
            }

            printf(" mitumete voice = %d \n", work->fC0C + 7);

            if (++work->fC0E > 14)
            {
                work->fC0E = 14;
            }

            if (++work->fC0C > 4)
            {
                work->fC0C = 0;
            }
        }
        else
        {
            work->think3 = 4;
            work->count3 = 0;
            return;
        }
    }

    if (work->count3 > 60 && GM_StreamStatus() == -1)
    {
        work->think3 = 4;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x10000;
        work->pad.dir = work->sn_dir;
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CDC34(Meryl72Work *work)
{
    if (GM_StreamStatus() != -1)
    {
        work->count3 = 0;
    }

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->count3 > 15)
    {
        if (s07c_meryl72_unk2_800CD76C(1000, -9000, 1500, -8500))
        {
            if (work->fC10[0] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[4], 0);
                }

                work->fC10[0] = 1800;
            }
        }
        else if (s07c_meryl72_unk2_800CD76C(5500, -9000, 7000, -8500))
        {
            if (work->fC10[1] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[5], 0);
                }

                work->fC10[1] = 1800;
            }
        }
        else if (s07c_meryl72_unk2_800CD76C(-9000, -9000, -7500, -8500))
        {
            if (work->fC10[2] == 0)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream(work->voices[5], 0);
                }

                work->fC10[2] = 1800;
            }
        }
    }

    if (work->count3 > 60 && work->fC0A > 150)
    {
        work->think3 = 5;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
    else if (work->fC04 > 3600 && !(work->modetime[6] & 0x4) && !(GM_GameStatus & STATE_STUN))
    {
        work->think1 = 3;
        work->think2 = 0;
        work->think3 = 0;
        GM_GameStatus |= STATE_PADRELEASE;
        work->count3 = 0;
        work->fC04 = 0;
    }
    else if (work->sn_dis > 3000 && !(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        work->think2 = 1;
        work->think3 = 2;
        work->count3 = 0;
    }
    else
    {
        work->pad.press |= 0x4000000;
        work->pad.dir = work->sn_dir;
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CDEC4(Meryl72Work *work)
{
    CONTROL *control;

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->count3 == 0)
    {
        s07c_meryl72_unk2_800CCAD8(work);
    }

    control = &work->control;
    if ((work->count3 % 32) == 0 && !HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[1]))
    {
        work->think2 = 1;
        work->think3 = 2;
        work->count3 = 0;
    }

    if (work->count3 > 60 && work->fC0A > 150)
    {
        work->think3 = 5;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x4000000;
        work->pad.dir = work->sn_dir;
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CDFC8(Meryl72Work *work)
{
    int think2_next;

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->sn_dis > 3000)
    {
        work->pad.mode = 1;
    }
    else
    {
        work->pad.mode = 0;
    }

    s07c_meryl72_unk2_800CC9A8(work);

    if (s07c_meryl72_unk2_800CCCC8(work))
    {
        work->think3 = 3;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else if (work->sn_dis < 2000 && work->vision.field_06 == 2)
    {
        think2_next = work->vision.field_06;
        work->think2 = think2_next;
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE08C(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CCCC8(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else if (work->fC04 > 3600)
    {
        work->think1 = 2;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        work->fC04 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE124(Meryl72Work *work)
{
    s07c_meryl72_unk2_800CC9A8(work);

    if (s07c_meryl72_unk2_800CCCC8(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else if (work->sn_dis < 1000 && work->vision.field_06 == 2)
    {
        work->think3 = 7;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE198(Meryl72Work *work)
{
    if (work->count3 == 0)
    {
        s07c_meryl72_unk2_800CCAD8(work);
    }

    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (s07c_meryl72_unk2_800CCCC8(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE218(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->sn_dis > 3000)
    {
        work->pad.mode = 1;
    }
    else
    {
        work->pad.mode = 0;
    }

    s07c_meryl72_unk2_800CC9A8(work);

    if (work->count3 & 32)
    {
        work->fB5C = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);

        if (HZD_ReachTo(work->control.map->hzd, work->fB5C, work->target_addr) >= 2)
        {
            work->think3 = 2;
            work->count3 = 0;
            return;
        }
    }

    if (s07c_meryl72_unk2_800CCD1C(work, 2000) > 0)
    {
        work->think2 = 2;
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE314(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CCD1C(work, 300) > 0)
    {
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else if (work->fC04 > 3600)
    {
        work->think1 = 2;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        work->fC04 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE3BC(Meryl72Work *work)
{
    int in_range;

    s07c_meryl72_unk2_800CC9A8(work);

    in_range = s07c_meryl72_unk2_800CCD1C(work, 1000);
    if (in_range < 0 || work->vision.field_06 != 2)
    {
        work->think3 = 2;
        work->count3 = 0;
    }
    else if (in_range > 0)
    {
        printf(" stop dis=%d\n", work->sn_dis);
        work->think3 = 7;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CE450(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->count3 & 32)
    {
        work->fB5C = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);

        if (HZD_ReachTo(work->control.map->hzd, work->fB5C, work->target_addr) >= 2)
        {
            work->think3 = 2;
            work->count3 = 0;
            return;
        }
    }

    if (s07c_meryl72_unk2_800CCD1C(work, 300) > 0)
    {
        work->think2 = 2;
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
         work->count3++;
    }
}

void s07c_meryl72_unk2_800CE524(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 0:
        s07c_meryl72_unk2_800CCD98(work);
        break;

    case 1:
        s07c_meryl72_unk2_800CD260(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CD474(work);
        break;
    }

    work->fC34 = 30;
}

void s07c_meryl72_unk2_800CE5AC(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 0:
        s07c_meryl72_unk2_800CCEC4(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CCF5C(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE5FC(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 2:
        s07c_meryl72_unk2_800CDFC8(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CE218(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE64C(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 2:
        s07c_meryl72_unk2_800CE198(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CE450(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE69C(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 1:
        s07c_meryl72_unk2_800CD2E0(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CE08C(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CE314(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CD80C(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CDA88(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE738(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 6:
        s07c_meryl72_unk2_800CCFE0(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CE124(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CE3BC(work);
        break;

    case 7:
        s07c_meryl72_unk2_800CD038(work);
        break;

    case 8:
        s07c_meryl72_unk2_800CD14C(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE7D4(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 4:
        s07c_meryl72_unk2_800CDC34(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CDA88(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE824(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 4:
        s07c_meryl72_unk2_800CDEC4(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CDA88(work);
        break;
    }
}

void Think1_Phase0_800CE874( Meryl72Work* work )
{
    if (work->think2 == 0)
    {
        s07c_meryl72_unk2_800CE524( work );
    }
}

void Think1_Phase1_800CE8A4( Meryl72Work* work )
{
    switch (work->think2)
    {
    case 2:
        s07c_meryl72_unk2_800CE69C( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void Think1_Phase2_800CE8F4( Meryl72Work* work )
{
    switch ( work->think2 )
    {
    case 1:
        s07c_meryl72_unk2_800CE5FC( work );
        return;
    case 2:
        s07c_meryl72_unk2_800CE7D4( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void Think1_Phase3_800CE970( Meryl72Work* work )
{
    switch ( work->think2 )
    {
    case 0:
        s07c_meryl72_unk2_800CE5AC( work );
        return;
    case 1:
        s07c_meryl72_unk2_800CE64C( work );
        return;
    case 2:
        s07c_meryl72_unk2_800CE824( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void	Meryl72Think_800CEA04( Meryl72Work* work )
{
	int	i ;

	work->pad.dir = -1 ;
	work->pad.press = 0 ;
/*
	if ( ToilletArea( &ENEMYPOS ) ) {
		work->control.radar_atr = RADAR_SIGHT | RADAR_ALL_MAP ;
	} else {
		work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP ;
	}
*/

	switch ( work->think1 ) {
	    case TH1_PHASE0 :		/* トイレから出る */
			Think1_Phase0_800CE874( work ) ;
		break ;
	    case TH1_PHASE1 :		/* スネークが準備するまで待つ */
			Think1_Phase1_800CE8A4( work ) ;
		break ;
	    case TH1_PHASE2 :		/* スネークについていく */
			Think1_Phase2_800CE8F4( work ) ;
		break ;
	    case TH1_PHASE3 :		/* 所.. */
            Think1_Phase3_800CE970( work ) ;
        break ;
    }

    for ( i = 0 ; i < 3 ; i++ )
    {
        if ( --work->fC10[i] < 0 )
        {
            work->fC10[i] = 0 ;
        }
    }
}
