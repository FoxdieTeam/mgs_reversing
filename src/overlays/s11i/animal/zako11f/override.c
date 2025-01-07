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

const int s11i_dword_800D5738 = 0x800D04FC;
const int s11i_dword_800D573C = 0x800D05C0;
const int s11i_dword_800D5740 = 0x800D0578;
const int s11i_dword_800D5744 = 0x800D0554;
const int s11i_dword_800D5748 = 0x800D0594;
const int s11i_dword_800D574C = 0x800D0570;
const int s11i_dword_800D5750 = 0x800D055C;
const char s11i_dword_800D5754[] = {0x0, 0x0, 0x0, 0x0};
const int s11i_dword_800D5758 = 0x800D07D8;
const int s11i_dword_800D575C = 0x800D07F0;
const int s11i_dword_800D5760 = 0x800D095C;
const int s11i_dword_800D5764 = 0x800D0808;
const int s11i_dword_800D5768 = 0x800D0828;
const int s11i_dword_800D576C = 0x800D0840;
const int s11i_dword_800D5770 = 0x800D0858;
const int s11i_dword_800D5774 = 0x800D0870;
const int s11i_dword_800D5778 = 0x800D08DC;
const int s11i_dword_800D577C = 0x800D088C;
const int s11i_dword_800D5780 = 0x800D0B54;
const int s11i_dword_800D5784 = 0x800D0B64;
const int s11i_dword_800D5788 = 0x800D0B74;
const int s11i_dword_800D578C = 0x800D0B84;
const int s11i_dword_800D5790 = 0x800D0B94;

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
