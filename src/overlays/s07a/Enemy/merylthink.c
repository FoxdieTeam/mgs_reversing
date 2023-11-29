#include "../../s00a/Enemy/enemy.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern int           GV_Time_800AB330;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern int           GM_AlertLevel_800ABA18;
extern int           GM_PlayerStatus_800ABA50;
extern unsigned int  COM_GameStatus_800E0F3C;
extern SVECTOR       COM_PlayerPosition_800E0F30;
extern SVECTOR       COM_PlayerPositionOne_800E0D48[8];
extern int           COM_PlayerMapOne_800E0F70[8];
extern int           COM_PlayerAddressOne_800E0F40[8];
extern int           COM_VibTime_800E0F68;
extern int           COM_PlayerMap_800E0F1C;
extern int           COM_SHOOTRANGE_800E0D88;
extern int           COM_PlayerAddress_800E0D90;
extern int           COM_PlayerMap_800E0F1C;

extern CONTROL      *GM_WhereList_800B56D0[94];

extern char NearAsiato_800D13A0();

// Identical to s00a_command_800CAACC
void s07a_meryl_unk_800DB340( WatcherWork* work )
{
    work->target_addr = work->start_addr;
    work->target_pos  = work->start_pos;
    work->target_map  = work->start_map;
}

void s07a_meryl_unk_800DB378( WatcherWork* work )
{
    work->target_addr = COM_PlayerAddress_800E0D90;
    work->target_pos  = COM_PlayerPosition_800E0F30;
    work->target_map  = COM_PlayerMap_800E0F1C;
}

void s07a_meryl_unk_800DB3C0( WatcherWork* work )
{
    int addr;
    HZD_ZON *zone;

    addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd, &GM_NoisePosition_800AB9F8, -1 ) & 0xFF;
    work->target_addr = ( addr << 8 ) | addr;
    zone = &GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = COM_PlayerMap_800E0F1C;
}

int s07a_meryl_unk_800DB470( WatcherWork *work, HZD_ZON *zone )
{
    return ( (unsigned short)zone->padding - 2 ) < 2u;
}

extern const char s07a_aOkokokodd_800E2FB0[]; //" okokoko %d -> %d \n";
extern const char s07a_aHazuredd_800E2FC4[];  //" hazure %d -> %d \n";

int s07a_meryl_unk_800DB484( WatcherWork *work, int addr, int addr2 )
{
    SVECTOR svec;
    SVECTOR svec2;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    HZD_ZON *zone2;
    
    hzd = work->control.field_2C_map->field_8_hzd;
    
    zone  = &hzd->f00_header->navmeshes[ addr ];
    zone2 = &hzd->f00_header->navmeshes[ addr2 ];

    if ( zone->y || zone2->y )
    {
        return 0;
    }

    svec.vx = zone->x;
    svec.vy = zone->y + 500;
    svec.vz = zone->z;

    svec2.vx = zone2->x;
    svec2.vy = zone2->y + 500;
    svec2.vz = zone2->z;

    if ( sub_80028454( hzd, &svec, &svec2, 0x8, 0x2 ) != 0 )
    {
        printf(s07a_aOkokokodd_800E2FB0, addr, addr2);
        return 1;
    }

    printf(s07a_aHazuredd_800E2FC4, addr, addr2);
    return 0;
}

extern int sub_8005D168(HZD_HDL *pHzd, int a2, int *a3);
int s00a_command_800CEA9C( int addr );
void s00a_command_800CEA84( int a, int addr );

void s07a_meryl_unk_800DB590( WatcherWork *work )
{
    int i;
    int vx;
    int res;
    int addr;
    CONTROL *ctrl;
    int addr_copy;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    HZD_ZON *zone2;
    HZD_ZON *zone3;
    int unk[5]; //?

    ctrl = &work->control;
    hzd = work->control.field_2C_map->field_8_hzd;

    addr = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, -1 ) & 0xFF;
    zone = &hzd->f00_header->navmeshes[ addr ];
    addr_copy = addr;

    res = sub_8005D168( hzd, addr, unk );
    work->search_flag = 1;

    if ( res > 0 )
    {
        vx = work->control.field_0_mov.vx % res;

        if ( vx < 0 )
        {
            vx = -vx;
        }

        for ( i = 0 ; i < res ; i++ )
        {
            addr  = unk[vx];
            zone2 = &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

            if ( !s07a_meryl_unk_800DB470( work , zone2 ) )
            {                     
                if ( !s07a_meryl_unk_800DB484( work, addr_copy, addr ) )
                {
                    if ( s00a_command_800CEA9C( addr ) )
                    {
                        goto loop;
                    }
                    else
                    {
                        goto end;
                    }
                }
                else
                {
                    goto loop;
                }
                
                if ( s00a_command_800CEA9C( addr ) )
                {
                    goto loop;
                }
                else
                {
end:
                    work->search_flag = 0;
                    s00a_command_800CEA84( work->field_B78, addr );
                    break;
                }
            }
            addr = addr_copy;
loop:
            vx++;
            if ( vx >= res )
            {
                vx = 0;
            }
        }

    }
    else
    {
        work->search_flag = 0;
    }

    zone3 = &hzd->f00_header->navmeshes[ addr ];
    work->target_addr = addr << 8 | addr;

    work->target_pos.vx = zone3->x;
    work->target_pos.vy = zone3->y;
    work->target_pos.vz = zone3->z;
    work->target_map = COM_PlayerMap_800E0F1C;
}

void s07a_meryl_unk_800DB768( WatcherWork* work )
{
        work->target_addr = EnemyCommand_800E0D98.com_addr;
        work->target_pos  = EnemyCommand_800E0D98.com_pos;
        work->target_map  = EnemyCommand_800E0D98.com_map;
}

// Identical to s00a_command_800CB0E0
void s07a_meryl_unk_800DB7A8( WatcherWork* work )
{
    int v0, v1, a2;
    HZD_HDL *hzd;
    void *a1;
    MAP *map;
    HZD_HEADER *hdr;

    v0 = work->field_B7C;
    do {} while (0);
    map = work->control.field_2C_map;
    v1 = v0 << 1;
    v1 = v1 + v0;
    hzd = map->field_8_hzd;
    a2 = v0 << 8;
    hdr = hzd->f00_header;
    v0 = v0 | a2;
    a1 = hdr->navmeshes;
    v1 = v1 << 3;
    work->target_addr = v0;
    a1 = a1  + v1;

    work->target_pos.vx = ((HZD_ZON*)a1)->x;
    work->target_pos.vy = ((HZD_ZON*)a1)->y;
    work->target_pos.vz = ((HZD_ZON*)a1)->z;
    work->target_map = work->start_map;

    //should just be this
    /*
    addr = work->field_B7C;
    work->target_addr = addr | (addr << 8);
    zone = &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
    */
}

// Identical to s00a_command_800CB13C
void s07a_meryl_unk_800DB804( WatcherWork* work )
{
    int x;

    x = work->next_node + 1;
    if ( x >= work->field_9E8 )
    {
        x = 0;
    }
    work->next_node = x;
    work->target_pos = work->nodes[ x ];
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &work->target_pos, -1 );
    work->target_map = work->start_map;
}

extern void AsiatoPos_800D129C( signed char, SVECTOR * );

// Identical to s00a_command_800CB1C4
void s07a_meryl_unk_800DB88C( WatcherWork* work )
{
    AsiatoPos_800D129C( work->field_BA0, &work->target_pos );
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &work->target_pos, -1 );
    work->target_map = work->control.field_2C_map->field_0_map_index_bit;
}

//everything before this probably not in think.c

// Identical to EnemyResetThink_800CB224
void s07a_meryl_unk_800DB8EC( WatcherWork* work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
    work->pad.field_08 = 0;
}

extern SVECTOR s07a_dword_800C3770;

extern const char s07a_aToilletzoned_800E2FD8[];// " toillet zone = %d \n";

void s07a_meryl_unk_800DB908( WatcherWork* work )
{
    int addr;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    
    hzd = work->control.field_2C_map->field_8_hzd;
    addr = HZD_GetAddress_8005C6C4( hzd, &s07a_dword_800C3770, -1 ) & 0xFF;
    printf(s07a_aToilletzoned_800E2FD8, addr);
    zone = &hzd->f00_header->navmeshes[ addr ];
    work->target_addr = addr | ( addr << 8 );

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = COM_PlayerMap_800E0F1C;
}

extern SVECTOR s07a_dword_800C3778;

void s07a_meryl_unk_800DB9B8( WatcherWork* work )
{
    int addr;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    
    hzd = work->control.field_2C_map->field_8_hzd;
    addr = HZD_GetAddress_8005C6C4( hzd, &s07a_dword_800C3778, -1 ) & 0xFF;
    printf(s07a_aToilletzoned_800E2FD8, addr);
    zone = &hzd->f00_header->navmeshes[ addr ];
    work->target_addr = addr | ( addr << 8 );

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = COM_PlayerMap_800E0F1C;
}


void s07a_meryl_unk_800DBA68( WatcherWork* work )
{
    s07a_meryl_unk_800DB908( work );
    work->think1 = 3;
    work->think2 = 0xE;
    work->think3 = 0x25;
    work->count3 = 0;
    work->field_B4C = 0;
    work->pad.field_08 = 1;
}


// Identical to s00a_command_800CB240
void s07a_meryl_unk_800DBAB4( WatcherWork* work )
{
    work->think2 = 7;
    work->think3 = 14;
    work->count3 = 0;
}

// Identical to s00a_command_800CB258
void s07a_meryl_unk_800DBACC( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        work->think1 = 1;
        work->think2 = 8;
        work->think3 = 19;
    }
    else
    {
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28;
        s07a_meryl_unk_800DB7A8( work );
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

// Identical to s00a_command_800CB2C8
void s07a_meryl_unk_800DBB3C( WatcherWork *work )
{

    work->think1 = 1;
    work->think2 = 9;
    work->think3 = 27;
    work->count3 = 32;
    work->pad.field_08 = 1;
}


void s07a_meryl_unk_800DBB68( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        s07a_meryl_unk_800DB768( work );
        work->think1 = 1;

        if ( EnemyCommand_800E0D98.field_0x40 == 1 )
        {
            work->think2 = 8;
            work->think3 = 18;
        }
        else
        {
            work->think2 = 10;
            work->think3 = 29;
        }
    }
    else
    {
        s07a_meryl_unk_800DB7A8( work );
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28;
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}


void s07a_meryl_unk_800DBC08( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 29;
    }
    else
    {
        s07a_meryl_unk_800DB7A8( work );
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28;
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

extern void s07a_meryl_unk_800DBD54( WatcherWork *work );

void s07a_meryl_unk_800DBC78( WatcherWork* work )
{
    EnemyCommand_800E0D98.field_0x40 = 0;
    if ( work->act_status & 4 )
    {
        work->think1 = 2;
        s07a_meryl_unk_800DBD54( work );
        work->pad.field_08 = 0;
        return;
    }

    if ( work->field_B7C != 0xFF )
    {
        if ( !( sub_8005D134( work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov, work->field_B7C ) ) )
        {
            s07a_meryl_unk_800DB7A8( work );
            work->think1 = 2;
            work->think2 = 11;
            work->count3 = 0;
            work->pad.field_08 = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->count3 = 0;
            work->pad.field_08 = 0;
        }
    }
    else
    {
        if ( work->field_BFC >= 5800 )
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->count3 = 0;
            work->pad.field_08 = 0;
            
        }
        else
        {
            work->think1 = 2;
            work->think2 = 11;
            work->count3 = 0;
            work->pad.field_08 = 1;
        }
    } 
}

// Identical to s00a_command_800CB3F0
void s07a_meryl_unk_800DBD54( WatcherWork *work )
{

    work->think2 = 4;

    if ( (work->act_status & 0x10) && (work->field_BA1 & 8) )
    {
        work->think3 = 0xE;
    }
    else
    {
        work->think3 = 4;
    }

    work->count3 = 0;
    work->modetime[2] = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DBD90.s")

// Identical to s00a_command_800CB610
void s07a_meryl_unk_800DBE84( WatcherWork* work )
{
    work->think2 = 2;
    work->think3 = 5;
    work->count3 = 0;
}

// Identical to s00a_command_800CB628
void s07a_meryl_unk_800DBE9C( WatcherWork *work )
{
    work->think2 = 5;
    work->think3 = 5;
    work->field_BA0 = NearAsiato_800D13A0();
    work->count3 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DBED4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DBF40.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DBF84.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DBFC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC00C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC0DC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC18C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC214.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC310.s")

// Identical to s00a_command_800CB6CC
int s07a_meryl_unk_800DC3E0( WatcherWork* work )
{
    int count;
    int v1;

    count = work->l_count;
    v1 = count / 30;
    v1 = v1 + work->field_B78;

    if ( v1 == 1 || v1 == 4 )
    {
        work->pad.press |= 0x2;
    }
    else if ( v1 == 2 || v1 == 5 )
    {
        work->pad.press |= 0x1;
    }

    if ( count > 90 )
    {
        work->l_count = 0;
        return 1;
    }
    else
    {
        work->l_count++;
        return 0;
    }
}

// Identical to s00a_command_800CB770
int s07a_meryl_unk_800DC484( WatcherWork* work )
{
    int count;

    count = work->l_count;

    if ( count == 0 )
    {
        work->control.field_4C_turn.vy = ( work->control.field_4C_turn.vy + 0x800 ) & 0xFFF;
    }

    if ( count == 24 )
    {
        work->control.field_4C_turn.vy = ( work->control.field_4C_turn.vy + 0x800 ) & 0xFFF;
    }

    if ( count > 30 )
    {
        work->l_count = 0;
        return 1;
    }
    else
    {
        work->l_count++;
        return 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC4F4.s")
// Identical to s00a_command_800CB7E0
int s07a_meryl_unk_800DC560( WatcherWork *work )
{
    work->count3++;
    work->pad.dir = work->sn_dir;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC57C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC5B0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC7CC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DC8F0.s")
// Identical to s00a_command_800CBD2C
int s07a_meryl_unk_800DCB24( WatcherWork* work )
{
    int len;
    CONTROL *ctrl;
    GV_MSG  *msg;

    ctrl = &work->control;
    len = ctrl->field_56;
    msg = ctrl->field_5C_mesg;

    for ( ; len > 0 ; len--, msg++ )
    {
        if ( msg->message[0]  == work->field_B4C )
        {
            return 1;
        }
    }
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCB64.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCBF4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCC88.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCCBC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCCEC.s")
int s07a_meryl_unk_800DCD50()
{
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCD58.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCDC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCE48.s")

// Identical to s00a_command_800CC240
int s07a_meryl_unk_800DCED0(SVECTOR* svec, SVECTOR* svec2, int a1) {
    int x, z;

    x = svec->vx - svec2->vx;
    z = svec->vz - svec2->vz;

    if ( -a1 < x || x < a1 || -a1 < z || z < a1 )
    {
        return 0;
    }

    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCF24.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCF78.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DCFD4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD05C.s")
// Identical to s00a_command_800CB6CC
int s07a_meryl_unk_800DD09C( WatcherWork* work )
{
    int count;
    int v1;

    count = work->l_count;
    v1 = count / 30;
    v1 = v1 + work->field_B78;

    if ( v1 == 1 || v1 == 4 )
    {
        work->pad.press |= 0x2;
    }
    else if ( v1 == 2 || v1 == 5 )
    {
        work->pad.press |= 0x1;
    }

    if ( count > 90 )
    {
        work->l_count = 0;
        return 1;
    }
    else
    {
        work->l_count++;
        return 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD140.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD194.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD1EC.s")

// Identical to s00a_command_800CC760
int s07a_meryl_unk_800DD310( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.dir = work->sn_dir;
    }

    if ( work->count3 > 14 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD354.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD3EC.s")

// Identical to s00a_command_800CC8C8
int s07a_meryl_unk_800DD47C( WatcherWork *work )
{
    if ( work->count3 > 2 && work->act_status & 1 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD4C0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD554.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD628.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD680.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD6E8.s")

// Identical to s00a_command_800CCC14
int s07a_meryl_unk_800DD780( WatcherWork *work )
{
    int count;

    count = work->count3;

    work->pad.press |= 0x10000;

    if ( count == 0 )
    {
        work->count3 = GV_RandU_80017090( 8 );
    }

    if ( count < 9 )
    {
        if ( !( count & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }

    if ( count > 11 )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;

}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD818.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD870.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD8D0.s")

// Identical to s00a_command_800CCDA0
int s07a_meryl_unk_800DD92C( WatcherWork *work )
{
    int count;
    work->pad.press |= 0x10000;

    count = work->count3;
    if ( count < 10 )
    {
        if ( !( work->count3 & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }
    else if ( count >= 20 )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD994.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DD9C0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DDA50.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DDADC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DDBA8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DDC60.s")
void s07a_meryl_unk_800DDF0C()
{
}
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DDF14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DE0C8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DE360.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DE61C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DE810.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DE908.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DEAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DEBF8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DED40.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DEE14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DEF1C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF038.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF17C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF234.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF3A0.s")
