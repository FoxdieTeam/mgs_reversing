#include "../../../s00a/Enemy/enemy.h"

#include "libhzd/libhzd.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

extern int     ZAKOCOM_PlayerAddress_800DF3B8;
extern SVECTOR ZAKOCOM_PlayerPosition_800DF278;
extern int     ZAKOCOM_PlayerMap_800DF3BC;
extern ZAKO_COMMAND ZakoCommand_800DF280;

extern SVECTOR  GM_PlayerPosition_800ABA10;
extern SVECTOR  GM_NoisePosition_800AB9F8;
extern CONTROL *GM_WhereList_800B56D0[94];
extern int      GM_PlayerMap_800ABA0C;
extern int      GM_PlayerAddress_800AB9F0;


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D89A0.s")
void s11e_zk11ecom_800D89A0( ZakoWork* work )
{
    work->target_addr = ZAKOCOM_PlayerAddress_800DF3B8;
    work->target_pos  = ZAKOCOM_PlayerPosition_800DF278;
    work->target_map  = ZAKOCOM_PlayerMap_800DF3BC;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D89E8.s")
void s11e_zk11ecom_800D89E8( ZakoWork* work )
{
    int v0, v1, a2;
    HZD_HDL *hzd;
    void *a1;
    MAP *map;
    HZD_HEADER *hdr;

    v0 = work->field_B78;
    do {} while (0);
    map = work->control.map;
    v1 = v0 << 1;
    v1 = v1 + v0;
    hzd = map->hzd;
    a2 = v0 << 8;
    hdr = hzd->header;
    v0 = v0 | a2;
    a1 = hdr->zones;
    v1 = v1 << 3;
    work->target_addr = v0;
    a1 = a1  + v1;

    work->target_pos.vx = ((HZD_ZON*)a1)->x;
    work->target_pos.vy = ((HZD_ZON*)a1)->y;
    work->target_pos.vz = ((HZD_ZON*)a1)->z;
    work->target_map = work->start_map;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8A44.s")
void s11e_zk11ecom_800D8A44( ZakoWork* work )
{
    if ( work->field_B78 == 0xFF )
    {
        work->think2 = 1;
        work->think1 = 0;
        work->think3 = 4;
    }
    else
    {
        work->think2 = 3;
        work->think1 = 0;
        work->think3 = 0x10;
        s11e_zk11ecom_800D89E8( work );
    }
    work->count3 = 0;
    work->pad.mode = TOP_COMM_ALERT;
}


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8AB0.s")
void s11e_zk11ecom_800D8AB0( ZakoWork* work )
{

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->pad.mode = TOP_COMM_ALERT;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8ACC.s")
int s11e_zk11ecom_800D8ACC( SVECTOR* arg0, SVECTOR* arg1 )
{
    SVECTOR svec;

    GV_SubVec3(arg1, arg0, &svec);
    svec.vy = 0;
    return GV_VecDir2(&svec);
}


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8B04.s")
extern SVECTOR GM_PlayerPosition_800ABA10;

extern int s11e_zk11ecom_800D9B60( int map_id, int val );

int s11e_zk11ecom_800D8B04( ZakoWork *work )
{
    int temp;
    int temp_addr;
    SVECTOR svec;
    CONTROL *ctrl;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int addr, addr2, addr3;
    int reach;
    SVECTOR *target_pos;

    hzd = work->control.map->hzd;

    if ( work->target_map == work->control.map->index )
    {
        target_pos = &work->target_pos;
        addr = work->target_addr;
    }
    else
    {
        target_pos = &work->target_pos;
        temp_addr  = s11e_zk11ecom_800D9B60( work->control.map->index , work->target_map );
        zone = &hzd->header->zones[ temp_addr ];
        target_pos->vx = zone->x;
        target_pos->vy = zone->y;
        target_pos->vz = zone->z;
        addr = (temp_addr << 8) | temp_addr;
    }

    ctrl = &work->control;
    work->field_C0C = HZD_GetAddress( hzd, &ctrl->mov, work->field_C0C );
    addr2 = work->field_C0C;
    reach = HZD_ReachTo( hzd, addr2, work->field_C10 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;

        if ( HZD_ReachTo( hzd, addr2, addr ) < 2 )
        {
                if ( work->target_map == work->control.map->index )
                {
                        work->field_C1C = *target_pos;
                        work->field_C10 = addr;

                        GV_SubVec3( &work->field_C1C, &ctrl->mov, &svec );

                        work->pad.dir = GV_VecDir2( &svec );
                        return -1;
                }

                addr2 = s11e_zk11ecom_800D9B60( work->target_map, ctrl->map->index );
                ctrl->map = Map_FromId_800314C0( work->target_map );
                zone = &ctrl->map->hzd->header->zones[ addr2 ];
                work->control.mov.vx = zone->x;
                ctrl->mov.vy = zone->y;
                ctrl->mov.vz = zone->z;
                work->field_C0C = -1;
                work->field_BF0 = -1;
                return ctrl->rot.vy;
        }

        addr3 = HZD_LinkRoute( hzd, addr2, addr, &ctrl->mov );
        zone = &hzd->header->zones[ addr3 ];
        if ( work->field_BFC == 0xFA0 )
        {
            work->field_C1C.vx = zone->x + 0xFA;
            work->field_C1C.vy = zone->y;
            work->field_C1C.vz = zone->z + 0xFA;
        } else
        {
            work->field_C1C.vx = zone->x;
            work->field_C1C.vy = zone->y;
            work->field_C1C.vz = zone->z;
        }

        work->field_C1C.vx = zone->x;
        work->field_C1C.vy = zone->y;
        work->field_C1C.vz = zone->z;

        temp = addr3 & 0xFF;
        work->field_C10 = temp | temp << 8;
    }

    GV_SubVec3( &work->field_C1C, &work->control.mov, &svec );
    target_pos = &svec;
    return GV_VecDir2( target_pos );
}

extern void ZAKO11E_PutMark_800D7C10( ZakoWork *work, int mark );
extern void NewEyeflash_800D0CF4( MATRIX *, SVECTOR *, const char *, int );

extern const char s11e_aKirari_800DEC14[];

int s11e_zk11ecom_800D8DC4( ZakoWork* work )
{
    if ( work->count3 == 0 )
    {
        ZAKO11E_PutMark_800D7C10( work, 0 );
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        NewEyeflash_800D0CF4( &work->body.objs->objs[6].world, &work->control.mov, s11e_aKirari_800DEC14, 0 );
    }

    if ( work->count3 < 20 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;
}


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8E64.s")
int s11e_zk11ecom_800D8E64( ZakoWork* work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        ZAKO11E_PutMark_800D7C10( work, 0 );
    }

    if ( work->count3 > 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8ECC.s")
int s11e_zk11ecom_800D8ECC( ZakoWork  *work)
{

    short temp_v0;

    if (!(work->count3 & 0x1F)) {

        work->field_C0C = -1;
        work->field_BF0 = -1;
        s11e_zk11ecom_800D8B04(work);
    }

    temp_v0 = s11e_zk11ecom_800D8B04(work);
    work->pad.dir = temp_v0;

    if (work->pad.dir < 0) {

        return 1;
    }

    work->count3 += 1;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/DirectTrace_800D8F3C.s")
int DirectTrace_800D8F3C( ZakoWork* work, int a1 )
{
    int x, z;
    SVECTOR svec;


    svec.vx = x = work->target_pos.vx - work->control.mov.vx;
    svec.vz = z = work->target_pos.vz - work->control.mov.vz;

    if ( -a1 >= x || x >= a1 || -a1 >= z || z >= a1 )
    {
        work->pad.dir = GV_VecDir2( &svec );
        work->count3++;
        return 0;
    }

    return 1;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8FC4.s")
int s11e_zk11ecom_800D8FC4( ZakoWork *work )
{
    MAP *map;
    s11e_zk11ecom_800D89A0( work );

    map = work->control.map;

    if ( !( map->index == work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->field_C0C = HZD_GetAddress( map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->field_C0C, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return DirectTrace_800D8F3C( work, 1500 );
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9058.s")
int s11e_zk11ecom_800D9058( ZakoWork *work )
{
    int count;
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    count = work->count3;

    if ( count == 0 )
    {
        work->count3 = GV_RandU( 8 );
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

    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D90F4.s")
int s11e_zk11ecom_800D90F4( ZakoWork *work )
{
    int count;
    work->pad.press |= 0x20000;
    work->pad.dir = 0x800;
    count = work->count3;

    if ( count >= 80 )
    {
        return 1;
    }

    if ( !( count & 2 ) )
    {
        work->pad.press |= 0x80000;
    }

    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9150.s")
extern SVECTOR s11e_dword_800C36B4[];

int s11e_zk11ecom_800D9150( ZakoWork *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 30 )
    {
        work->pad.press |= 0x100000;
        work->field_C04 = s11e_dword_800C36B4[ work->field_B74 ];
    }
    else if ( work->body.is_end )
    {
        return 1;
    }

    work->pad.dir = s11e_zk11ecom_800D8ACC( &work->control.mov, &s11e_dword_800C36B4[ work->field_B74 ] );
    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9214.s")
int s11e_zk11ecom_800D9214( ZakoWork *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x200000;
    }
    else
    {
        if ( work->actend || work->count3 > 30 )
        {
            return 1;
        }
    }

    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9280.s")
int s11e_zk11ecom_800D9280( ZakoWork *work )
{
    int count = work->count3;
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( count < 10 )
    {
        if ( !( count & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }
    else if ( count >= 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D92EC.s")
int s11e_zk11ecom_800D92EC( ZakoWork* work )
{
    int count = work->count3;
    if ( count > 200 )
    {
        return 1;
    }

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9334.s")
int s11e_zk11ecom_800D9334( ZakoWork *work )
{
    if ( work->sn_dis < 800 )
    {
        work->pad.press |= 0x10000;
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}
//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D937C.s")

typedef struct ACTIONPATTERN
{
    int set;
} ACTIONPATTERN;

//extern int s11e_dword_800C36CC[ 2 ][ 16 ];
extern ACTIONPATTERN s11e_dword_800C36CC[ 16 ][ 16 ];
extern int s11e_dword_800DF3B4;
extern int GM_PlayerStatus_800ABA50;


#define ATTACKNEAR_DIS 800

int s11e_zk11ecom_800D937C( ZakoWork *work )
{
    work->pad.press |= 0x10000; //SP_WEAPON?
    work->pad.dir = work->sn_dir;


    if ( work->count3 == 16 )
    {
        work->count3 += GV_RandU( 14 );
    }

    if ( work->count3 > 24 )
    {
        //int nextset = ActionPattern[ ZAKO11A_GameFlag ][ ID ].set ;
        int nextset = s11e_dword_800C36CC[ work->field_B74 ][ s11e_dword_800DF3B4 ].set;
        switch ( nextset )
        {
        case 0:
            if ( work->sn_dis < ATTACKNEAR_DIS && !( GM_PlayerStatus_800ABA50 & 0x1060 ) )
            {
                return 10;
            }
            return 6;
        case 2:
            return 7;
        case 3:
            return 12;
        case 4:
            return 13;
        case 1:
            if ( work->sn_dis < ATTACKNEAR_DIS && GM_PlayerStance == 0 )
            {
                return 10;
    	    }
            return 14;
        }
    }

    work->count3++;
    return 0;
}


extern ACTIONPATTERN s11e_dword_800C37CC[ 16 ][ 16 ];

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D94C0.s")
int s11e_zk11ecom_800D94C0( ZakoWork *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    work->field_B78 = s11e_dword_800C37CC[ work->field_B74 ][ s11e_dword_800DF3B4 ].set;
    return 15;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9510.s")
void s11e_zk11ecom_800D9510( ZakoWork* work )
{
    s11e_zk11ecom_800D8A44( work );
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9530.s")
void s11e_zk11ecom_800D9530( ZakoWork* work )
{
    if ( !work->think3 )
    {
        s11e_zk11ecom_800D9510( work );
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9560.s")
void s11e_zk11ecom_800D9560( ZakoWork *work )
{
    switch( work->think3 )
    {
        case 1:
        if ( s11e_zk11ecom_800D8DC4( work ) )
        {
            s11e_zk11ecom_800D8A44( work );
            if ( ZakoCommand_800DF280.mode == TOP_COMM_TRAVEL )
            {
                work->pad.sound = 240;
            }
            else
            {
                work->pad.sound = 246;
            }
            work->alert_level = 255;
        }
        break;
        case 2:
        if ( s11e_zk11ecom_800D8E64( work ) )
        {
            work->think2 = 3;
            work->think3 = 0x10;
            work->pad.mode = TOP_COMM_ALERT;
            work->pad.sound = 0xF0;
            work->think1 = 0;
            work->count3 = 0;
            work->alert_level = 255;
        }
        break;
        case 3:
        if ( s11e_zk11ecom_800D8E64( work ) )
        {
            s11e_zk11ecom_800D8A44( work );
            work->pad.sound = 240;
            work->alert_level = 255;
        }
    }
}

extern int ZAKO11E_SetGoPointLast_800D9A9C();

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9654.s")
void s11e_zk11ecom_800D9654( ZakoWork *work ) {
    int res;
    short x;
    x = work->think3 - 6;
    switch ( x )
    {
    case 0:
        if ( s11e_zk11ecom_800D9058( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s11e_zk11ecom_800D90F4( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 3:
        if ( s11e_zk11ecom_800D9150( work ) )
        {
            s11e_zk11ecom_800D8AB0( work );
            work->count3 = 0;
        }
        break;
     case 4:
        if ( s11e_zk11ecom_800D9214( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
     case 5:
        if ( s11e_zk11ecom_800D9280( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
     case 6:
        if ( s11e_zk11ecom_800D92EC( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
     case 7:
        if ( s11e_zk11ecom_800D9334( work ) )
        {
            work->think3 = 10;
            work->count3 = 0;
        }
        break;
     case 9:
        res = s11e_zk11ecom_800D937C( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }
        break;
     case 8:
        res = s11e_zk11ecom_800D94C0( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }

        if (!(HZD_8005D134( work->control.map->hzd, &work->control.mov, work->field_B78 )))
        {
            s11e_zk11ecom_800D8A44( work );
        }
        break;
    }

    if ( work->vision.field_B92 == 2 )
    {
        ZAKO11E_SetGoPointLast_800D9A9C();
        work->alert_level = 255;
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D97D8.s")
void s11e_zk11ecom_800D97D8( ZakoWork *work )
{
    int res;
    switch ( work->think3 )
    {
        case 4:
        s11e_zk11ecom_800D89A0( work );
        if ( s11e_zk11ecom_800D8ECC(work) )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;
        case 5:
        res = s11e_zk11ecom_800D8FC4( work ); //ZoneTrace
        if ( res < 0 )
        {
            work->think3 = 4;
            work->count3 = 0;
        }
        else if ( res > 0 )
        {
            work->think2 = 2;     //TH2_ATTACK
            work->think3 = 14;    //TH3_ATTACK_SETUP
            work->count3 = 0;
        }
        break;
    }

    if ( work->sn_dis < ATTACKNEAR_DIS && GM_PlayerStance == 0 )
    {
        work->pad.press |= 0x10000 ; //SP_WEAPON
        work->think2 = 2;      //TH2_ATTACK
        work->think3 = 10 ;    //TH3_ATTACK_NEAR
        work->count3 = 0 ;
        work->pad.dir = work->sn_dir;
    }

    if ( work->vision.field_B92 == 2 )
    {
        work->alert_level = 255;
    }

    ZAKO11E_SetGoPointLast_800D9A9C();
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D98D8.s")
void s11e_zk11ecom_800D98D8( ZakoWork* work )
{
    if ( (work->think3 == 16 ) && s11e_zk11ecom_800D8ECC( work ) )
    {
        work->think2 = 2;
        work->think3 = 14;
        work->count3 = 0;
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9928.s")
void s11e_zk11ecom_800D9928( ZakoWork *work )
{
    switch ( work->think2 )
    {
    case 0:
        s11e_zk11ecom_800D9530( work );
        break;
    case 1:
        s11e_zk11ecom_800D97D8( work );
        break;
    case 2:
        s11e_zk11ecom_800D9654( work );
        break;
    case 3:
        s11e_zk11ecom_800D98D8( work );
        break;
    case 4:
        s11e_zk11ecom_800D9560( work );
        break;
    }
}

void Zako11EThink_800D99B8( ZakoWork* work )
{
    work->pad.dir   = -1;
    work->pad.press =  0;
    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT;

    if ( work->think1 == 0)
    {
        work->field_8E6 = 1;
        s11e_zk11ecom_800D9928( work );
    }

    if ( s11e_dword_800DF3B4 > 0 )
    {
        work->alert_level = 0xFF;
        return;
    }

    work->alert_level = 0;
}
