#include "../../../s00a/Enemy/enemy.h"

extern SVECTOR ZAKOCOM_PlayerPosition_800D5AF0;
extern int     ZAKOCOM_PlayerAddress_800D5C50;
extern int     ZAKOCOM_PlayerMap_800D5C54;

void s11i_zk11fcom_800CF9E4( Zako11FWork *work )
{
    work->target_addr = ZAKOCOM_PlayerAddress_800D5C50;
    work->target_pos  = ZAKOCOM_PlayerPosition_800D5AF0;
    work->target_map  = ZAKOCOM_PlayerMap_800D5C54;
}

void s11i_zk11fcom_800CFA2C( Zako11FWork *work )
{
    int      addr;
    int      index;
    HZD_ZON *zone;

    addr = work->field_B78;

    index = addr << 1;
    index = index + addr;
    zone = (HZD_ZON *)((char *)work->control.map->hzd->header->zones + index * 8);

    work->target_addr = addr | addr << 8;

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFA88.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFAF4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFB10.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFB64.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFE24.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFEA4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFF0C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800CFF7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0004.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0098.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D00EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0148.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D020C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0274.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D02BC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D039C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D03E4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D05D4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0628.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0674.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D06A4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D078C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D098C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0A88.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0B1C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0BAC.s")
