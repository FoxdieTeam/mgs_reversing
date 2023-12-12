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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8ACC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8B04.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8DC4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8E64.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8ECC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8F3C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8FC4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9058.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D90F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9150.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9214.s")
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