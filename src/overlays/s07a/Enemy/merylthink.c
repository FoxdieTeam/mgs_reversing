#include "../../s00a/Enemy/enemy.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern int           GV_Time_800AB330;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern int           GM_AlertLevel_800ABA18;
extern int           GM_PlayerStatus_800ABA50;
extern unsigned int  COM_GameStatus_800E0F3C;
extern int           GM_NoisePower_800ABA24;
extern SVECTOR       COM_PlayerPosition_800E0F30;
extern SVECTOR       COM_PlayerPositionOne_800E0D48[8];
extern int           COM_PlayerMapOne_800E0F70[8];
extern int           COM_PlayerAddressOne_800E0F40[8];
extern int           COM_VibTime_800E0F68;
extern int           COM_PlayerMap_800E0F1C;
extern int           COM_SHOOTRANGE_800E0D88;
extern int           COM_PlayerAddress_800E0D90;
extern int           COM_PlayerMap_800E0F1C;


extern void NewEyeflash_800D0CF4( MATRIX *, SVECTOR *, const char *, int );
void ENE_PutMark_800D998C( WatcherWork *work, int mark );

#define T_NOISE 0

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
    work->pad.mode = 0;
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
    work->pad.mode = 1;
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
    work->pad.mode = 1;
}

// Identical to s00a_command_800CB2C8
void s07a_meryl_unk_800DBB3C( WatcherWork *work )
{

    work->think1 = 1;
    work->think2 = 9;
    work->think3 = 27;
    work->count3 = 32;
    work->pad.mode = 1;
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
    work->pad.mode = 1;
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
    work->pad.mode = 1;
}

extern void s07a_meryl_unk_800DBD54( WatcherWork *work );

void s07a_meryl_unk_800DBC78( WatcherWork* work )
{
    EnemyCommand_800E0D98.field_0x40 = 0;
    if ( work->act_status & 4 )
    {
        work->think1 = 2;
        s07a_meryl_unk_800DBD54( work );
        work->pad.mode = 0;
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
            work->pad.mode = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->count3 = 0;
            work->pad.mode = 0;
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
            work->pad.mode = 0;
            
        }
        else
        {
            work->think1 = 2;
            work->think2 = 11;
            work->count3 = 0;
            work->pad.mode = 1;
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



void s07a_meryl_unk_800DBD90( WatcherWork* work )
{
    switch( GM_NoisePower_800ABA24 )
    {
    case 5:
        work->think2 = 1;
        work->think3 = 8;
        break;
    case 200:
        s07a_meryl_unk_800DB3C0( work );
        work->think2 = 1;

        if (work->act_status & 0x10 )
        {
            work->think3 = 14;
        }
        else
        {
            work->think3 = 5;
        }
        work->modetime[(  T_NOISE  )] = 0;
        break;
    case 255:
        s07a_meryl_unk_800DB3C0( work );
        s00a_command_800CEB54();
        work->think2 = 7;
        work->think3 = 16;
        break;
    default:
    case 100:
        s07a_meryl_unk_800DB3C0( work );
        work->think2 = 1;

        if ( work->act_status & 0x10 )
        {
            work->think3 = 14;
        }
        else
        {
            work->think3 = 5;
        }
        work->modetime[(  T_NOISE  )] = 0;
        break;
    }
    work->count3 = 0;
}

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


void s07a_meryl_unk_800DBED4(WatcherWork* work) {
    
    HZD_HDL* temp_s0;
    int temp_v0;

    temp_s0 = work->control.field_2C_map->field_8_hzd;
    temp_v0 = HZD_GetAddress_8005C6C4(temp_s0, &work->control.field_0_mov, -1);
    work->field_C04 = temp_v0;
    
    if (HZD_ZoneDistance_8005CD1C(temp_s0, temp_v0 & 0xFF, (char)work->target_addr) < 0xC8) {
        
        work->pad.mode = 0;
        return;
    }
    
    work->pad.mode = 1;
}

int s07a_meryl_unk_800DBF40(SVECTOR* vec) {
    
    if (((unsigned short)vec->vx - 4000 >= 5501U) || 
        ((vec->vz < -20500) != 0) || (vec->vz >= -9499)) {
        
        return 0;
    }
    
    return 1;
}

int s07a_meryl_unk_800DBF84(SVECTOR* vec) {
    
    if (((unsigned short)vec->vx - 5500 >= 1501U) || 
        ((vec->vz < -9500) != 0) || (vec->vz >= -7999)) {
        
        return 0;
    }
    
    return 1;
}

int s07a_meryl_unk_800DBFC8(SVECTOR* vec) {
    
    if (((unsigned short)vec->vx - 4500 >= 4001U) || 
        ((vec->vz < -20500) != 0) || (vec->vz >= -15499)) {
        
        return 0;
    }
    
    return 1;
}

extern SVECTOR GM_PlayerPosition_800ABA10;
extern const char s07a_aKroekroekrokeorkdd_800E2FF0[];// = " kroekroekrokeork %d %d\n";

int s07a_meryl_unk_800DC00C( WatcherWork *work )
{
    int count3 = work->count3;
    
    if ( s07a_meryl_unk_800DBF40( &GM_PlayerPosition_800ABA10 ) || s07a_meryl_unk_800DBF84( &GM_PlayerPosition_800ABA10  ) )
    {
        work->count3 = 0;
    }

    if ( EnemyCommand_800E0D98.mode != TOP_COMM_TRAVEL )
    {
        work->count3 = 0;
    }

    if ( s07a_meryl_unk_800DBF40( &work->start_pos ) )
    {
        work->count3 = 0;
    }

    if ( count3 > 180 )
    {
        return 1;
    }

    if ( s07a_meryl_unk_800DBFC8( &work->control.field_0_mov ) == 0 )
    {
        printf( s07a_aKroekroekrokeorkdd_800E2FF0, work->control.field_0_mov.vx , work->control.field_0_mov.vz );
        return 1;
    }
    
    work->count3++;
    return 0;      
}

extern int s07a_meryl_unk_800DCD58(WatcherWork* work);

void s07a_meryl_unk_800DC0DC( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 37:
        if ( s07a_meryl_unk_800DCD58( work ) ) 
        {
            work->think2 = 15;
            work->pad.mode = 0;
            work->think3 = 39;
            work->count3 = 0;
        }
        work->alert_level = 0;
        return;
    case 38:
        if ( s07a_meryl_unk_800DCD58( work ) ) 
        {
            work->think2 = 15;
            work->pad.mode = 0;
            work->think3 = 39;
            work->count3 = 0;
        }        
        if ( work->alert_level > 1 )
        {
            work->count3 = 0;
            s07a_meryl_unk_800DBAB4( work );
        }
    }
}

extern int s07a_meryl_unk_800DCF78( WatcherWork* work ) ;

void s07a_meryl_unk_800DC18C( WatcherWork* work ) 
{
    if ( ( work->think3 == 39 ) && ( s07a_meryl_unk_800DC00C( work ) ) )
    {
        s07a_meryl_unk_800DB9B8( work );
        work->think2 = 0x10;
        work->think3 = 0x28;
        work->count3 = 0;
        work->pad.mode = 0;
    }
    
    if ( s07a_meryl_unk_800DCF78( work ) )
    {
        s07a_meryl_unk_800DB340( work );
        work->next_node = work->field_9E8;
    }
    
    work->alert_level = 0;
}

extern const char s07a_aOuttoilletgoaddrd_800E300C[];

void s07a_meryl_unk_800DC214( WatcherWork *work )
{
    int mode;
    if ( ( work->think3 == 40 ) && ( s07a_meryl_unk_800DCD58( work ) ) )
    {
        s07a_meryl_unk_800DB340( work );
        printf( s07a_aOuttoilletgoaddrd_800E300C, work->target_addr );
        work->next_node = work->field_9E8;
        s07a_meryl_unk_800DB8EC( work );
        work->count3 = 0;
        
    }
    
    if ( s07a_meryl_unk_800DBF40( &GM_PlayerPosition_800ABA10 ) || s07a_meryl_unk_800DBF84( &GM_PlayerPosition_800ABA10  ) || work->alert_level > 1 )
    {
        work->count3 = 0;
        s07a_meryl_unk_800DBAB4( work );
        return;
    }

    mode = EnemyCommand_800E0D98.mode;
    if ( mode == TOP_COMM_ALERT )
    {
        s07a_meryl_unk_800DB908( work );
        work->think2 = 14;
        work->think3 = 37;
        work->count3 = 0;
        work->pad.mode = mode;
        return;
        
    }
    
    work->alert_level = 0;    
}

extern const char s07a_a_800E3028[];// = "0+";
extern const char s07a_a_800E302C[];// = "1+";
extern const char s07a_a_800E3030[];// = "2+";
extern const char s07a_a_800E3034[];// = "3+";

extern void s07a_meryl_unk_800DE810( WatcherWork *work );

void s07a_meryl_unk_800DC310( WatcherWork *work )
{

    switch ( work->think2 ) {                              
    case 14:
        printf( s07a_a_800E3028 );
        s07a_meryl_unk_800DC0DC( work );
        return;
    case 15:
        printf( s07a_a_800E302C );
        s07a_meryl_unk_800DC18C( work );
        return;
    case 16:
        printf( s07a_a_800E3030 );
        s07a_meryl_unk_800DC214( work );
        return;
    case 7:
        printf( s07a_a_800E3034 );
        work->control.field_3A_radar_atr |= 0x1000;
        s07a_meryl_unk_800DE810( work );
        return;
    }
}

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

int s07a_meryl_unk_800DC4F4( WatcherWork *work )
{
    int count3 = work->count3;
    if ( count3 & 31 )
    {
        if ( count3 > 64 )
        {
            return 1;
        }
    }
    else
    {
        work->field_B58 = GV_RandU_80017090( 8 ) << 9;
    }   

    work->pad.dir = work->field_B58;
    work->count3++;
    return 0;    
}

// Identical to s00a_command_800CB7E0
int s07a_meryl_unk_800DC560( WatcherWork *work )
{
    work->count3++;
    work->pad.dir = work->sn_dir;
    return 0;
}

int s07a_meryl_unk_800DC57C( WatcherWork* work )
{
    int count = work->count3;
    if ( count != 0 && (int)work->count3 > 0x20 )
    {
        return 1;
    }

    work->count3++;
    return 0;    
}


int s07a_meryl_unk_800DC5B0( WatcherWork *work )
{
    int temp;
    SVECTOR svec;
    CONTROL *ctrl;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int addr, addr2, addr3;
    int reach;

    ctrl = &work->control;
    hzd  = work->control.field_2C_map->field_8_hzd;
    addr = work->target_addr;

    addr2 = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, work->field_C04 );
    work->field_C04 = addr2;

    reach = HZD_ReachTo_8005C89C( hzd, addr2, work->field_C08 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;
        if ( HZD_ReachTo_8005C89C( hzd, addr2, work->field_BF0 ) < 2 )
        {
            work->field_C14 = work->target_pos;
            work->field_C08 = addr;

            GV_SubVec3_80016D40( &work->field_C14, &ctrl->field_0_mov, &svec );

            work->pad.dir = GV_VecDir2_80016EF8( &svec );
            return -1;
        }

        if ( !( work->field_C00 & 1 ) )
        {
            addr3 = sub_8005CB48( hzd, addr2, addr, &ctrl->field_0_mov );
            zone = &hzd->f00_header->navmeshes[ addr3 ];

            if ( GM_PlayerPosition_800ABA10.vx & 1 )
            {
                work->field_C14.vx = zone->x + 250;
            }
            else
            {
                 work->field_C14.vx = zone->x - 250;
            }

            if ( GM_PlayerPosition_800ABA10.vz & 1 )
            {
                work->field_C14.vz = zone->z + 250;
            }
            else
            {
                 work->field_C14.vz = zone->z - 250;
            }
            work->field_C14.vy = zone->y;
        }
        else
        {
            addr3 = HZD_LinkRoute_8005C974( hzd, addr2, addr, &ctrl->field_0_mov );
            zone = &hzd->f00_header->navmeshes[ addr3 ];
            work->field_C14.vx = zone->x;
            work->field_C14.vy = zone->y;
            work->field_C14.vz = zone->z;
        }
        temp = addr3 & 0xFF;
        work->field_C08 = temp | temp << 8;
    }

    GV_SubVec3_80016D40( &work->field_C14, &work->control.field_0_mov, &svec );
    return GV_VecDir2_80016EF8( &svec );
}

extern const char s07a_aCrootdrootdpatdnpointsd_800E3038[];// = "c_root= %d root %d pat %d n_points = %d \n";

int s07a_meryl_unk_800DC7CC( WatcherWork *work )
{
    int i;
    MAP *map;
    PARAM *param;
    HZD_PAT *patrol;
    HZD_PTP *points;

    map = Map_FromId_800314C0( work->start_map );
    param = ( PARAM * )&work->field_B78;
    patrol = map->field_8_hzd->f00_header->routes;
    patrol = &patrol[ param->root ];

    fprintf( 1, s07a_aCrootdrootdpatdnpointsd_800E3038, param->c_root, param->root, patrol, patrol->n_points );
    work->field_9E8 = patrol->n_points;
    
    if ( work->field_9E8 <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->field_9E8 ; i++ )
    {
        work->nodes[i].vx  = points->x;
        work->nodes[i].vy  = points->y;
        work->nodes[i].vz  = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }

    work->start_pos = work->nodes[0];
    work->start_addr = HZD_GetAddress_8005C6C4( map->field_8_hzd, &work->start_pos, -1 );
    return 0;
}

extern unsigned short s07a_dword_800C36E8[4];
extern int s07a_dword_800C36F0[32];

extern const char s07a_aActdtimeddirdcond_800E3064[];// = "act=%d, time=%d dir=%d con=%d\n";

extern int DirectTrace_800DCE48( WatcherWork *, int );

int s07a_meryl_unk_800DC8F0( WatcherWork *work )
{
    int a2;
    int a0, con;
    int act, time, dir;
    int command;

start:
    //    starting from lo
    //   |con |dir|tim| act   //
    //000|0 00|00 |000|0 0000//

    command = work->target_pos.pad;
    act  = ( command & 0x1F );         //5 bits
    time = ( command & 0xE0 ) >> 5;    //3 bits
    dir  = ( command & 0x300 ) >> 8;   //2 bits
    con  = ( command & 0x1C00 ) >> 10; //3 bits

    if ( work->field_B78 == 2 )
    {
        printf( s07a_aActdtimeddirdcond_800E3064, act, time, dir, con );
    }

    if ( s07a_dword_800C36F0[ act ] == 0x1F )
    {
        work->field_B7E = con + ( dir * 8 );
        return 0;
    }

    if ( time != 6 )
    {

        a2  = GV_Time_800AB330 % 100;
        a0  = con & 3;
        con = con & 4;

        if ( a2 >= s07a_dword_800C36E8[ a0 ] || work->field_B4C == 1 )
        {
            work->field_B4C = 0;
            s07a_meryl_unk_800DB804( work );
            if ( !DirectTrace_800DCE48( work , 350 ) )
            {
                return 0;
            }
            goto start;
        }

        if ( con != 0 )
        {
            work->field_B4C = 1;
        }
    }

    work->pad.time = work->field_BB0[ time ];
    work->pad.tmp  = s07a_dword_800C36F0[ act ];

    if ( COM_GameStatus_800E0F3C & 1 )
    {
        if ( work->pad.tmp == 0x80 || work->pad.tmp == 0x200 || work->pad.tmp == 0x400 || work->pad.tmp == 0x800 )
        {
            work->pad.tmp = 0;
            if ( work->pad.time == 450 )
            {
                work->pad.time = 90;
            }
        }
    }

    if ( act == 0 && time == 0 )
    {
        work->pad.time = 0;
        work->pad.dir = work->control.field_8_rot.vy;
        s07a_meryl_unk_800DB804( work );
        return 0;
    }

    if ( act & 0x10 && act != 0x1F )
    {
        s07a_meryl_unk_800DB804( work );
        return 0;
    }

    work->pad.dir = work->field_BD0[ dir ];
    return 1;
}

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

int s07a_meryl_unk_800DCB64( WatcherWork* work )
{
    if ( work->pad.time == 32001 )
    {
        if ( s07a_meryl_unk_800DCB24( work ) )
        {
            work->field_B4C = 0;
            work->pad.time  = 0;
            return 1;
        }
        work->pad.press |= work->pad.tmp;
        return 0;
    }

    if ( !work->pad.time )
    {
        return 1;
    }

    work->pad.press |= work->pad.tmp;
    work->pad.time--;
    return 0;
}

extern const char s07a_aKirari_800E3084[];// = "kirari01";

int s07a_meryl_unk_800DCBF4( WatcherWork* work )
{
    int count;

    count = work->count3;

    if ( count == 0 )
    {
        ENE_PutMark_800D998C( work, 0 );
        NewEyeflash_800D0CF4( &work->body.objs->objs[6].world, &work->control.field_0_mov, s07a_aKirari_800E3084, 0 );
        COM_VibTime_800E0F68 = 10;
    }

    if ( count < 20 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;

}

int s07a_meryl_unk_800DCC88(SVECTOR* arg0, SVECTOR* arg1 )
{
    SVECTOR svec;

    GV_SubVec3_80016D40(arg1, arg0, &svec);
    return GV_VecDir2_80016EF8(&svec);
}

void s07a_meryl_unk_800DCCBC( WatcherWork* work )
{
    work->pad.dir = s07a_meryl_unk_800DCC88( &work->control.field_0_mov, &work->target_pos );
}

int s07a_meryl_unk_800DCCEC( WatcherWork* work )
{
    if ( work->count3 == 0 )
    {
        ENE_PutMark_800D998C( work, 0 );
        s07a_meryl_unk_800DCCBC( work );
    }

    if ( work->count3 > 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DCD50( void )
{
    return 0;
}

int s07a_meryl_unk_800DCD58(WatcherWork *work) {
    
    short temp_v0;

    if (!(work->count3 & 0x1F)) {
        
        work->field_C04 = -1;
        work->field_BF0 = -1;
        s07a_meryl_unk_800DC5B0(work);
    }
    
    temp_v0 = s07a_meryl_unk_800DC5B0(work);
    work->pad.dir = temp_v0;

    if (work->pad.dir < 0) {

        return 1;
    }

    work->count3 += 1;
    return 0;
}

int s07a_meryl_unk_800DCDC8(WatcherWork *work) {
    
    short temp_v0;

    if (s07a_meryl_unk_800DCD50() == 0) {
        
        if (!(work->count3 & 0x1F)) {
        
            work->field_C04 = -1;
            work->field_BF0 = -1;
            s07a_meryl_unk_800DC5B0(work);
        }
        
        temp_v0 = s07a_meryl_unk_800DC5B0(work);
        work->pad.dir = temp_v0;
        
        if (work->pad.dir >= 0) {
        
            work->count3 += 1;
            return 0;
        }
    }
    
    return 1;
}

int DirectTrace_800DCE48( WatcherWork* work, int a1 )
{
    int x, z;
    SVECTOR svec;


    svec.vx = x = work->target_pos.vx - work->control.field_0_mov.vx;
    svec.vz = z = work->target_pos.vz - work->control.field_0_mov.vz;

    if ( -a1 >= x || x >= a1 || -a1 >= z || z >= a1 )
    {
        work->pad.dir = GV_VecDir2_80016EF8( &svec );
        work->count3++;
        return 0;
    }

    return 1;
}

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

int NextAsiato_800D12D0( HZD_HDL*, signed char, SVECTOR * );

int s07a_meryl_unk_800DCF24( WatcherWork *work )
{
    int x;

    x = NextAsiato_800D12D0( work->control.field_2C_map->field_8_hzd, work->field_BA0, &work->control.field_0_mov );

    if ( x >= 0 )
    {
        work->field_BA0 = x;
        return 1;
    }

    work->field_BA0 = -1;
    return 0;
}

extern const char s07a_aRootchange_800E3090[];// = " Root Change !!\n";

int s07a_meryl_unk_800DCF78( WatcherWork* work )
{

    if ( work->field_B7E != work->field_B7D )
    {
        fprintf( 1, s07a_aRootchange_800E3090 );
        work->field_B7D = work->field_B7E;
        s07a_meryl_unk_800DC7CC( work );
        return 1;
    }

    return 0;
}

int s07a_meryl_unk_800DCFD4( WatcherWork *work )
{
    unsigned int count;
    if ( work->count3 == 0 )
    {
       if ( COM_GameStatus_800E0F3C & 0x2000 )
       {
           work->think3 = 13;
           return 0;
       }

        COM_GameStatus_800E0F3C |= 0x2000;
        work->pad.dir = work->sn_dir;
    }

    count = work->count3;
    
    asm(""); //TODO fix
    if ( work->actend != 0 || count > 300 )
    {
        return 1;
    }

    work->pad.press |= SP_DANBOWLKERI;
    work->count3++;

    return 0;
}

int s07a_meryl_unk_800DD05C( WatcherWork *work )
{
    if ( !( COM_GameStatus_800E0F3C & 0x2000 ) )
    {
        return 1;
    }

    work->pad.press |= 0x4;
    work->count3++;
    return 0;
}

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

int Think3_GoNext_800DD140( WatcherWork* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800DCE48( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}

//#pragma INCLUDE_ASM("asm/overlays/s07a/Think3_BikkuriGetUp_800DD194.s")
int Think3_BikkuriGetUp_800DD194( WatcherWork* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){

        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

//#pragma INCLUDE_ASM("asm/overlays/s07a/Think3_NoiseModeWatch_800DD1EC.s")
int Think3_NoiseModeWatch_800DD1EC( WatcherWork *work )
{

    if( work->count3 == 0)
    {
        if( EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
        {
            if( work->modetime[(  T_NOISE  )]  <= 1 )
            {
                GM_SeSet_80032858( &work->control.field_0_mov, 0xC0);
            }
            if( work->modetime[(  T_NOISE  )]  <= 3 )
            {
                ENE_PutMark_800D998C( work ,BW_MARK );
            }
            work->pad.dir = work->sn_dir;            
        }
        else
        {
            if( work->modetime[(  T_NOISE  )] ) return 1;
            ENE_PutMark_800D998C( work ,BW_MARK );
            work->pad.dir = work->sn_dir;
        }
    }
    else
    {
        work->pad.dir = -1;
    }

    switch( work->modetime[(  T_NOISE  )] )
    {
        case 0:
            if( work->count3 >= 16)
            {
                return 1;
            }
            break;
        case 1:
        case 2:
            if ( work->count3 >= 48 )
            {
                return 1;
            }
            break;
        case 3:
            return 1;
    }
    work->count3++;
    return 0;
}

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

int s07a_meryl_unk_800DD354( WatcherWork *work )
{
    SVECTOR svec;
    GV_SubVec3_80016D40( &GM_NoisePosition_800AB9F8, &work->control.field_0_mov, &svec );
    work->pad.dir = GV_VecDir2_80016EF8( &svec );
    work->pad.press |= 0x02000000;

    if ( work->count3 == 0 )
    {
        ENE_PutMark_800D998C( work, BW_MARK );
    }

    if ( work->count3 > 30 )
    {
        return 1;
    }

    if ( work->field_BA1 & 1 )
    {
        work->count3 = 1;
    }
    else
    {
        work->count3++;
    }

    return 0;
}

int s07a_meryl_unk_800DD3EC( WatcherWork* work )
{
    if ( work->count3 == 0 )
    {
        if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, 0xC0 );
        }
        
        ENE_PutMark_800D998C( work, 5 );
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    if ( work->count3 > 15 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

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

int s07a_meryl_unk_800DD4C0( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.dir = work->sn_dir;
    }

    if ( work->count3 == 30 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xC0 );
        ENE_PutMark_800D998C( work, 5 );
    }

    if ( work->count3 > 29 && s07a_meryl_unk_800DC3E0( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD554( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xC0 );
        ENE_PutMark_800D998C( work, BW_MARK );
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    if ( work->count3 >= 16 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD5D0( WatcherWork *work )
{
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800D998C( work, 5 );
    }

    if ( s07a_meryl_unk_800DC3E0( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD628( WatcherWork *work )
{
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800D998C( work, 5 );
    }

    if ( s07a_meryl_unk_800DC3E0( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD680( WatcherWork *work )
{
    work->pad.press |= 0x4;
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800D998C( work, 5 );
    }

    if ( work->count3 > 120 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD6E8( WatcherWork *work )
{
    MAP *map;
    s07a_meryl_unk_800DB378( work );

    map = work->control.field_2C_map;

    if ( !( map->field_0_map_index_bit & work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->field_C04 = HZD_GetAddress_8005C6C4( map->field_8_hzd, &work->control.field_0_mov, -1 );
        if ( HZD_ReachTo_8005C89C( work->control.field_2C_map->field_8_hzd, work->field_C04, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return DirectTrace_800DCE48( work, 1500 );
}

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

int s07a_meryl_unk_800DD818( WatcherWork *work )
{

    work->pad.press |= 0x20000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x80000;
    }
    else
    {
        if ( work->count3 == 8 )
        {
            return 1;
        }
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD870( WatcherWork *work )
{
    work->pad.press |= 0x10000;
    
    if ( work->count3 != 30) 
    {
        if (work->body.is_end != 0) 
        {
            return 1;
        }
    }
    else
    {
        work->pad.press |= 0x100000;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD8D0( WatcherWork *work )
{
    work->pad.press |= 0x10000;
    
    if ( work->count3 != 0) 
    {
        if (work->body.is_end != 0) 
        {
            return 1;
        }
    }
    else
    {
        work->pad.press |= 0x200000;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

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

int s07a_meryl_unk_800DD994( WatcherWork *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s07a_meryl_unk_800DD9C0( WatcherWork* work )
{
    switch ( work->think4 )
    {
    case 3:
        if ( s07a_meryl_unk_800DC3E0( work ) )
        {
            work->think4 = 4;
            work->count3 = 0;
        }
        work->count3++;
        break;
    case 4:
        if (s07a_meryl_unk_800DC4F4( work ) )
        {
            work->think4 = 3;
            work->count3 = 0;
        }
        break;
    }
    return 0;
}

int s07a_meryl_unk_800DDA50( WatcherWork* work )
{
    switch ( work->think4 )
        {
        case 3:
            if ( s07a_meryl_unk_800DC3E0( work ) )
            {
                work->think4 = 1;
                work->count3 = 0;
                s07a_meryl_unk_800DB378( work );
            }
            work->count3++;
            break;
        case 1:
            if (s07a_meryl_unk_800DCD58( work ) )
            {
                work->think4 = 3;
                work->count3 = 0;
            }
            break;
        }
    return 0;
}

int s07a_meryl_unk_800DDADC( WatcherWork *work )
{
    switch( work->think4 )
    {
        case 0:
            if ( s07a_meryl_unk_800DD09C(work) )
            {
                work->think4 = 2;
                s07a_meryl_unk_800DB590( work );
                work->count3 = 0;
            }
            break;
        case 3:
            if ( s07a_meryl_unk_800DC3E0(work) )
            {
                work->think4 = 2;
                s07a_meryl_unk_800DB590( work );
                work->count3 = 0;
            }
            work->count3++;
            break;
        case 2:
            if ( DirectTrace_800DCE48( work, 250 ) )
            {
                s07a_meryl_unk_800DB590( work );
                work->count3 = 0;
            }
            break;
    }

    return 0;
}

void s07a_meryl_unk_800DDBA8( WatcherWork *work )
{
    if ( work->think3 == 3 && s07a_meryl_unk_800DC57C( work ) )
    {
        s07a_meryl_unk_800DB340( work );
        work->next_node = work->field_9E8;
        s07a_meryl_unk_800DB8EC( work );
        work->pad.mode = 1;
    }

    if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
    }
    else if ( work->field_BA1 & 1 )
    {
        s07a_meryl_unk_800DBD90( work );
    }
    else if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }
}

static inline void set_dir( WatcherWork *work )
{   
    if ( GV_DiffDirAbs_8001706C( work->pad.dir, work->control.field_8_rot.vy ) < 128 )
    {
        work->pad.dir = -1;
    }
}

static inline void think_reset( WatcherWork *work )
{
    s07a_meryl_unk_800DB340( work );
    work->next_node = work->field_9E8;
    s07a_meryl_unk_800DB8EC( work );
}

static inline void think_reset2( WatcherWork *work )
{
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->next_node--;
        s07a_meryl_unk_800DB804( work );
        s07a_meryl_unk_800DB8EC( work );
        s07a_meryl_unk_800DBED4( work );
    }
    else
    {
        s07a_meryl_unk_800DBC78( work );
    }
}

static inline void think_noise_inline( WatcherWork *work )
{
    s07a_meryl_unk_800DB3C0( work );
    s00a_command_800CEB54();
    work->think2 = 7;
    work->think3 = 16;
    work->count3 = 0;
}

void s07a_meryl_unk_800DDC60( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 0:
       if ( s07a_meryl_unk_800DCD58( work ) )
       {
            if (s07a_meryl_unk_800DBF40( &work->control.field_0_mov ) != 0)
            {
                work->think1 = 3;
                work->think2 = 0xF;
                work->think3 = 0x27;
                work->count3 = 0;                
                work->pad.time = 0;
                
            } else 
            {
                work->pad.mode = 0;
                work->think3 = 1;
                work->next_node--;
                s07a_meryl_unk_800DB804( work );
                work->count3 = 0;
                work->pad.time = 0;
            }
       }
        break;
    case 1:
        if ( Think3_GoNext_800DD140( work ) )
        {
            if ( s07a_meryl_unk_800DCF78( work ) )
            {
                think_reset( work );
                return;
            }
            else
            {
                if (s07a_meryl_unk_800DC8F0( work ) )
                {
                    work->think3 = 2;
                }               
                work->count3 = 0;
            }
        }
        else
        {
            if ( work->field_BA1 & 64 )
            {
                s07a_meryl_unk_800DBE84( work );
                work->think3 = 12;
                return;
            }
        }
        break;
    case 2:
        if ( s07a_meryl_unk_800DCB64( work ) )
        {
            if ( s07a_meryl_unk_800DCF78( work ) )
            {
                think_reset( work );
            }
            else
            {
                s07a_meryl_unk_800DB804( work );
                if ( DirectTrace_800DCE48( work, 350 ) )
                {
                    if ( !s07a_meryl_unk_800DC8F0( work ) )
                    {
                        work->think3 = 1;
                    }
                    else
                    {
                        set_dir( work );
                    }
                }
                else
                {
                    work->think3 = 1;
                }
                work->count3 = 0;
            }
        }
        break;
    }


    if ( s07a_meryl_unk_800DCF78( work ) )
    {
        think_reset( work );
    }

    if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
    }
    else if ( work->field_BA1 & 2)
    {
        s07a_meryl_unk_800DBE84( work );
    }
    else if ( work->field_BA1 & 1)
    {
        s07a_meryl_unk_800DBD90( work );
    }
    else if ( work->field_BA1 & 16 )
    {
        s07a_meryl_unk_800DBE9C( work );
    }
    else if ( work->alert_level > 2 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }
    else if ( s07a_meryl_unk_800DBF40( &work->control.field_0_mov ) )
    {
        s07a_meryl_unk_800DBA68( work );
        work->pad.mode = TOP_COMM_TRAVEL;
    }
}

void s07a_meryl_unk_800DDF0C( WatcherWork *work )
{
}

void s07a_meryl_unk_800DDF14( WatcherWork *work )
{
    switch ( work->think3 )
    {
        case 14:
            if ( Think3_BikkuriGetUp_800DD194( work ) )
            {
                work->think3 = 5;
                work->count3 = 0;
            }
            break;
        case 4:
            if ( s07a_meryl_unk_800DD47C( work ) )
            {
                if (s07a_meryl_unk_800DBF40( &work->control.field_0_mov ) != 0)
                {
                    s07a_meryl_unk_800DBA68( work );
                    return;
                }
                work->think3 = 5;
                work->count3 = 0;
            }
            break;
        case 5:
           if (  s07a_meryl_unk_800DD4C0( work ) )
           {
               think_reset2( work );
           }
            
           if (  work->field_BA1 & 1  )
           {
                if ( GM_NoisePower_800ABA24 == 200 || GM_NoisePower_800ABA24 == 255  )
                {
                    think_noise_inline( work );
                }
                return;
           }
           else if ( work->field_BA1 & 2 )
           {
               s07a_meryl_unk_800DBE84( work );
               return;
           }
        break;
    }

    if ( ( *( int * )&work->field_BA0 & 0xC00 ) == 0x400 )
    {
        s07a_meryl_unk_800DBD54( work );
    }
    else if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }
}


void s07a_meryl_unk_800DE0C8( WatcherWork *work )
{
    short x;
    x = work->think3 - 5;
    switch ( x )
    {
    case 0:
        if ( s07a_meryl_unk_800DD3EC( work ) )
        {
            s07a_meryl_unk_800DB378( work );
            work->think3 = 9;
            work->count3 = 0;
            if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
            {
                work->pad.mode = 0;
            }
            else
            {
                work->pad.mode = 1;
            }
        }
        break;
    case 4:
        if ( s07a_meryl_unk_800DCD58( work ) )
        {
            work->think3 = 10;
            work->count3 = 0;
        }
        if ( s07a_meryl_unk_800DCED0( &work->target_pos, &work->control.field_0_mov, 1500 ) )
        {
            work->think3 = 11;
            work->count3 = 0;
        }
        if ( work->sn_dis < 1500 )
        {
            if ( ( signed char )work->field_BA1 & 128 )
            {
                if ( ( work->field_BA1 & 16 ) || work->think1 == 2  )
                {
                    work->think3 = 12;
                    work->count3 = 0;
                }
                else
                {
                    work->think3 = 11; 
                    work->count3 = 0;
                }
            }
        }
        break;
    case 5:
    if  ( DirectTrace_800DCE48( work, 1500 ) )
    {
        work->pad.dir = work->sn_dir;

        if ( ( work->field_BA1 & 16 ) || work->think1 == 2  )
        {
            work->think3 = 12;            
            work->count3 = 0;
        }
        else
        {
            work->think3 = 11;    
            work->count3 = 0;
        }
        
    }
    break;
    case 6:
        if ( s07a_meryl_unk_800DD680( work ) )
        {
            think_reset2( work );
        }
        break;
    case 7:
        if ( s07a_meryl_unk_800DCFD4( work ) )
        {
            think_reset2( work );
        }
        break;
    case 8:
        if ( s07a_meryl_unk_800DD05C( work ) )
        {
            think_reset2( work );
        }
        break;
    }

    if ( work->alert_level > 1 || work->field_BA1 & 2 )
    {
        s07a_meryl_unk_800DBAB4( work );
        return;
    }

    if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
        return;
    }

    if ( work->field_BA1 & 1 )
    {
        if ( (GM_NoisePower_800ABA24 != 100) )
        {
            if ( GM_NoisePower_800ABA24 == 255 )
            {
                think_noise_inline( work );
                return;
            }
        }
        s07a_meryl_unk_800DBAB4( work );
        work->count3 = 0;
        return ;
    }
}

void s07a_meryl_unk_800DE360( WatcherWork *work )
{
    short x;
    x = work->think3 - 5;
    switch ( x )
    {
        case 10:
        if ( Think3_BikkuriGetUp_800DD194( work ) )
        {
            work->think3 = 6;
            work->count3 = 0;
        }
        break;
        case 1:
            if ( s07a_meryl_unk_800DD310( work ) )
            {
                //noise_inline without setting count;
                s07a_meryl_unk_800DB3C0( work );
                s00a_command_800CEB54();
                work->think2 = 7;
                work->think3 = 16;
                break;
            }
        break;
        case 9:
        if ( Think3_BikkuriGetUp_800DD194( work ) )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;
        case 0:
            if ( Think3_NoiseModeWatch_800DD1EC( work ) )
            {
                work->modetime[(  T_NOISE  )]++;
                work->think3 = 9;
                if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL && work->modetime[(  T_NOISE  )] < 2 )
                {
                    work->pad.mode = 0;
                }
                else
                {
                    work->pad.mode = 1;
                }
                work->count3 = 0;
            }
            break;
        case 4:
            if ( s07a_meryl_unk_800DCD58( work ) )
            {
                work->think3 = 11;
                work->count3 = 0;
            }

            if ( work-> count3 > 32 )
            {
                if ( work->field_BA1 & 1 && work->modetime[(  T_NOISE  )] < 3 )
                {
                    s07a_meryl_unk_800DB3C0( work );
                    work->think3 = 5;
                    work->count3 = 0;
                }
            }
        break;
        case 6:
            if ( s07a_meryl_unk_800DD5D0( work ) )
            {
                think_reset2( work );
            }
        break;
        case 3:
            if ( s07a_meryl_unk_800DD354( work ) )
            {
                think_reset2( work );
            }
        break;
    }
    
    if ( work->alert_level > 2 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }
    else if ( work->field_BA1 & 2 )
    {
        s07a_meryl_unk_800DBE84( work );
    }
    else if ( work->field_BA1 & 16 )
    {
        s07a_meryl_unk_800DBE9C( work );
    }
    else if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
    }
    else if ( work->field_BA1 & 1 )
    {
        if ( GM_NoisePower_800ABA24 == 200 || GM_NoisePower_800ABA24 == 255 )
        {
            think_noise_inline( work );
        }
    }
}

extern void CleanAsiato_800D1378();

void s07a_meryl_unk_800DE61C( WatcherWork *work )
{
    switch ( work->think3 )
    {
        case 5:
            if ( s07a_meryl_unk_800DD554( work ) )
            {
                s07a_meryl_unk_800DB88C( work );
                work->think3 = 10;
                work->t_count = 0;
                work->pad.mode = 0;
                work->count3 = 0;
            }
        break;
        case 10:
        work->pad.press |= 0x4;
        if ( DirectTrace_800DCE48( work , 500 ) )
        {
            if ( s07a_meryl_unk_800DCF24( work ) != 0 )
            {
                s07a_meryl_unk_800DB88C( work );
                work->t_count++;
                if ( work->t_count == 12 )
                {
                    work->think3 = 32;
                }
                else
                {
                    work->pad.dir = work->control.field_4C_turn.vy;
                }
                work->count3 = 0;
                break;
            }
            else
            {
                work->think3 = 11;
                CleanAsiato_800D1378();
                work->count3 = 0;
            }
        }
        break;
        case 32:
        if ( s07a_meryl_unk_800DC484( work ) )
        {
            work->think3  = 10;
            work->t_count = 0;
            work->count3  = 0;
        }
        break;
        case 11:
        if ( s07a_meryl_unk_800DD628 ( work ) )
        {
            think_reset2( work );
        }
        break;
    }

    if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4( work );
        CleanAsiato_800D1378();
    }
    else if ( work->field_BA1 & 2 )
    {
        s07a_meryl_unk_800DBE84( work );
    }
    else if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
        CleanAsiato_800D1378();
    }

    else if ( work->field_BA1 & 1 )
    {
        s07a_meryl_unk_800DBD90( work );
        CleanAsiato_800D1378();
    }
}

void s07a_meryl_unk_800DE810( WatcherWork *work )
{
    switch( work->think3 )
    {
    case 14:
        if ( s07a_meryl_unk_800DCBF4( work ) )
        {
            if ( work->act_status & 0x01 )
            {
                if ( GM_PlayerStatus_800ABA50 & 0x1000 )
                {
                    GM_SeSet_80032858( &work->control.field_0_mov, 0xC1 );
                }
                else
                {
                    GM_SeSet_80032858( &work->control.field_0_mov, 0xB5 );
                }
            }
            s07a_meryl_unk_800DBA68( work );
        }
        break;
    case 16:
        if ( s07a_meryl_unk_800DCCEC( work ) )
        {
            s07a_meryl_unk_800DBC08( work );
        }
        break;
    case 17:
        if (s07a_meryl_unk_800DCBF4( work ) != 0)
        {
            s07a_meryl_unk_800DBACC( work );
            ENE_SetGopointLast_800CEB00();
        }
    }
}

void s07a_meryl_unk_800DE908( WatcherWork *work )
{
    int res;
    short x;
    x = work->think3 - 21;
    switch ( x )
    {
    case 0:
        if ( s07a_meryl_unk_800DD780( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s07a_meryl_unk_800DD818( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 3:
        if ( s07a_meryl_unk_800DD870( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 4:
        if ( s07a_meryl_unk_800DD8D0( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 5:
        if ( s07a_meryl_unk_800DD92C( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 6:
        res = s07a_meryl_unk_800DD994( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }
        break;
    }

    if ( ( ( GV_Time_800AB330 / 4 ) % 4 ) != work->field_B78 )
    {
        return;
    }

    if ( work->field_B7C == 0xFF )
    {
        if ( work->field_C04 != COM_PlayerAddress_800E0D90 )
        {
            if ( work->field_BFC < 0xDAD )
            {
                if ( (work->field_BFC + 0x3E8) < work->sn_dis || work->vision.field_B92 != 2 )
                {
                    s07a_meryl_unk_800DBACC( work );
                }
            }
            else
            {
                if (  work->field_BFC < work->sn_dis )
                {
                    s07a_meryl_unk_800DBACC( work );
                }
            }
        }
    }
    else
    {
        if ( work->vision.field_B92 != 2 )
        {
            if (!(sub_8005D134( work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov, work->field_B7C )))
            {
                s07a_meryl_unk_800DBACC(work);
            }
        }
    }
}

void s07a_meryl_unk_800DEAEC( WatcherWork *work )
{
    int res;
    switch ( work->think3 )
    {
        case 18:
        s07a_meryl_unk_800DB378( work );
        if ( s07a_meryl_unk_800DCDC8(work) )
        {
            work->think3 = 19;
            work->count3 = 0;
        }
        break;
        case 19:
        s07a_meryl_unk_800DB378( work );
        if ( s07a_meryl_unk_800DCD58( work ) )
        {
            work->think3 = 20;
            work->count3 = 0;
        }
        break;
        case 20:
        res = s07a_meryl_unk_800DD6E8( work );
        if ( res < 0 )
        {
            work->think3 = 19;
            work->count3 = 0;
        }
        else if ( res > 0 )
        {
            s07a_meryl_unk_800DBB3C( work );
        }
        break;
    }

    if ( work->sn_dis < work->field_BFC )
    {
        if ( ( work->field_BFC >= 0xFA0 ) || ( work->vision.field_B92 == 2 ) )
        {
            s07a_meryl_unk_800DBB3C( work );
        }
    }
}

void s07a_meryl_unk_800DEBF8( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 29:
        if ( s07a_meryl_unk_800DCDC8( work ) )
        {
            work->think3 = 28;
            work->count3 = 0;
        }
    break;
    case 28:
        if ( ( work->field_B7C != 0xFF ) && (char)work->target_addr != (short)work->field_B7C )
        {
            s07a_meryl_unk_800DB7A8( work );
        }
        if ( s07a_meryl_unk_800DCD58( work ) )
        {
            if ( EnemyCommand_800E0D98.field_0x40 == 1  || ( work->field_B7C != 0xFF) )
            {
                s07a_meryl_unk_800DBB3C( work );
            }
            else
            {
                work->think3 = 30;
                work->count3 = 0;
            }
        }
    break;
    case 30:
    break;
    }

    if ( ( work->field_B7C == 0xFF) || EnemyCommand_800E0D98.field_0x40 != 1 )
    {
        if ( work->vision.field_B92 == 2 )
        {
            if ( EnemyCommand_800E0D98.field_0x40 != 1 )
            {
                work->think2 = 7;
                work->think3 = 17;
                work->count3 = 0;
                return;
            }
            work->pad.dir = work->sn_dir;
            s07a_meryl_unk_800DBB3C( work );
            return;
        }
    }
    else
    {
        if ( work->vision.field_B92 == 2 )
        {
            work->pad.dir = work->sn_dir;
            s07a_meryl_unk_800DBB3C( work );
            return;
        }
    }
}

void s07a_meryl_unk_800DED40( WatcherWork* work )
{
    if ( s07a_meryl_unk_800DCD58( work ) )
    {
        work->think2 = 13;
        work->think3 = 34;
        work->think4 = 3;
        work->pad.mode = 0;
        work->count3 = 0;
    }

    if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }

    if ( work->field_BA1 & 2 )
    {
        s07a_meryl_unk_800DBE84( work );
    }

    if ( work->field_BA1 & 1 )
    {
        s07a_meryl_unk_800DBD90( work );
    }

    if ( work->field_BA1 & 16 )
    {
        s07a_meryl_unk_800DBE9C( work );
        work->pad.mode = 0;
    }
    else if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
        work->pad.mode = 0;
    }
}

extern int GM_AlertLevel_800ABA18;

void s07a_meryl_unk_800DEE14( WatcherWork* work )
{
    s07a_meryl_unk_800DB378( work );

    if ( s07a_meryl_unk_800DCD58( work ) || ( work->sn_dis < ( work->field_BFC + 500 ) ) || GM_AlertLevel_800ABA18 < 150 )
    {
        work->think2 = 13;
        work->think3 = 34;
        work->think4 = 0;
        work->pad.mode = 0;
        work->count3 = 0;
    }

    if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4( work );
    }

    if ( work->field_BA1 & 2 )
    {
        s07a_meryl_unk_800DBE84( work );
    }

    if ( work->field_BA1 & 1 )
    {
        s07a_meryl_unk_800DBD90( work );
    }

    if ( work->field_BA1 & 16 )
    {
        s07a_meryl_unk_800DBE9C( work );
        work->pad.mode = 0;
    }
    else if ( work->field_BA1 & 4 )
    {
        s07a_meryl_unk_800DBD54( work );
        work->pad.mode = 0;
    }
}

void s07a_meryl_unk_800DEF1C( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 31:
        s07a_meryl_unk_800DD9C0( work );
        break;
    case 32:
        s07a_meryl_unk_800DC560( work );
        break;
    case 33:
        s07a_meryl_unk_800DDA50( work );
        break;
    case 34:
        s07a_meryl_unk_800DDADC( work );
        break;
    }

    if ( work->alert_level > 1 )
    {
        s07a_meryl_unk_800DBAB4(work);
    }
    if (work->field_BA1 & 2)
    {
        s07a_meryl_unk_800DBE84(work);
    }
    else if (work->field_BA1 & 1)
    {
        s07a_meryl_unk_800DBD90(work);
    }
    else if (work->field_BA1 & 16 )
    {
        s07a_meryl_unk_800DBE9C(work);
    }
    else if (work->field_BA1 & 4)
    {
        s07a_meryl_unk_800DBD54(work);
    }
}

void s07a_meryl_unk_800DF038( WatcherWork *work )
{
    switch( work->think2 )
    {
        case 6:
        s07a_meryl_unk_800DDBA8( work );
        break;
        case 0:
        s07a_meryl_unk_800DDC60( work );
        break;
        case 1:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DE360( work );
        break;
        case 2:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DE0C8( work );
        break;
        case 3:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DDF0C( work );
        break;
        case 4:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DDF14( work );
        break;
        case 5:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DE61C( work );
        break;
        case 7:
            work->control.field_3A_radar_atr |= 0x1000;
            s07a_meryl_unk_800DE810( work );
        break;
    }

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        return;
    }

    if ( work->think2 == 7 )
    {
        work->think1 = 1;
    }
    else
    {
        s07a_meryl_unk_800DBB68( work );
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF17C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF234.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DF3A0.s")
