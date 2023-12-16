#include "../../../s00a/Enemy/enemy.h"

extern int     ZAKOCOM_PlayerAddress_800DF3B8;
extern SVECTOR ZAKOCOM_PlayerPosition_800DF278;
extern int     ZAKOCOM_PlayerMap_800DF3BC;

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

    GV_SubVec3_80016D40(arg1, arg0, &svec);
    svec.vy = 0;
    return GV_VecDir2_80016EF8(&svec);
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
    
    hzd = work->control.field_2C_map->field_8_hzd;
    
    if ( work->target_map == work->control.field_2C_map->field_0_map_index_bit )
    {
        target_pos = &work->target_pos;
        addr = work->target_addr;
    }
    else
    {
        target_pos = &work->target_pos;
        temp_addr  = s11e_zk11ecom_800D9B60( work->control.field_2C_map->field_0_map_index_bit , work->target_map );
        zone = &hzd->f00_header->navmeshes[ temp_addr ];
        target_pos->vx = zone->x;
        target_pos->vy = zone->y;
        target_pos->vz = zone->z;
        addr = (temp_addr << 8) | temp_addr;
    }
    
    ctrl = &work->control;
    work->field_C0C = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, work->field_C0C );
    addr2 = work->field_C0C;
    reach = HZD_ReachTo_8005C89C( hzd, addr2, work->field_C10 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;

        if ( HZD_ReachTo_8005C89C( hzd, addr2, addr ) < 2 )
        {
                if ( work->target_map == work->control.field_2C_map->field_0_map_index_bit )
                {
                        work->field_C1C = *target_pos;
                        work->field_C10 = addr;
            
                        GV_SubVec3_80016D40( &work->field_C1C, &ctrl->field_0_mov, &svec );
            
                        work->pad.dir = GV_VecDir2_80016EF8( &svec );
                        return -1;    
                }
            
                addr2 = s11e_zk11ecom_800D9B60( work->target_map, ctrl->field_2C_map->field_0_map_index_bit );
                ctrl->field_2C_map = Map_FromId_800314C0( work->target_map );
                zone = &ctrl->field_2C_map->field_8_hzd->f00_header->navmeshes[ addr2 ];
                work->control.field_0_mov.vx = zone->x;
                ctrl->field_0_mov.vy = zone->y;
                ctrl->field_0_mov.vz = zone->z;
                work->field_C0C = -1;
                work->field_BF0 = -1;
                return ctrl->field_8_rot.vy;
        }

        addr3 = HZD_LinkRoute_8005C974( hzd, addr2, addr, &ctrl->field_0_mov );
        zone = &hzd->f00_header->navmeshes[ addr3 ];
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

    GV_SubVec3_80016D40( &work->field_C1C, &work->control.field_0_mov, &svec );
    target_pos = &svec;
    return GV_VecDir2_80016EF8( target_pos );    
}

extern void ZAKO11E_PutMark_800D7C10( ZakoWork *work, int mark );
extern void NewEyeflash_800D0CF4( MATRIX *, SVECTOR *, const char *, int );

extern const char s11e_aKirari_800DEC14[];

int s11e_zk11ecom_800D8DC4( ZakoWork* work )
{
    if ( work->count3 == 0 )
    {
        ZAKO11E_PutMark_800D7C10( work, 0 );
        GM_SeSet_80032858(  &work->control.field_0_mov, 0x53);
        NewEyeflash_800D0CF4( &work->body.objs->objs[6].world, &work->control.field_0_mov, s11e_aKirari_800DEC14, 0 );
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
        GM_SeSet_80032858(  &work->control.field_0_mov, 0x53 );
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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8FC4.s")
int s11e_zk11ecom_800D8FC4( ZakoWork *work )
{
    MAP *map;
    s11e_zk11ecom_800D89A0( work );

    map = work->control.field_2C_map;

    if ( !( map->field_0_map_index_bit == work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->field_C0C = HZD_GetAddress_8005C6C4( map->field_8_hzd, &work->control.field_0_mov, -1 );
        if ( HZD_ReachTo_8005C89C( work->control.field_2C_map->field_8_hzd, work->field_C0C, work->target_addr ) > 1 )
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

    work->pad.dir = s11e_zk11ecom_800D8ACC( &work->control.field_0_mov, &s11e_dword_800C36B4[ work->field_B74 ] );
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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9280.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D92EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9334.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D937C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D94C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9510.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9530.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9560.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9654.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D97D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D98D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9928.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D99B8.s")