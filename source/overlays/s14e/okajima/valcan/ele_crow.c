#include "libgcl/libgcl.h"
#include "game/game.h"

/*----------------------------------------------------------------------------*/

typedef struct _CROW {
    /* 0x000 */ char pad0[ 0x3E0 ];
} CROW;

typedef struct _Work {
    /* 0x000 */ GV_ACT actor;
    /* 0x020 */ char   pad20[ 0x1AC ];
} Work;

const int s14e_dword_800DD374 = 0x800D3818;
const int s14e_dword_800DD378 = 0x800D383C;
const int s14e_dword_800DD37C = 0x800D3868;
const int s14e_dword_800DD380 = 0x800D3944;
const int s14e_dword_800DD384 = 0x800D39D0;
const int s14e_dword_800DD388 = 0x800D3A70;
const int s14e_dword_800DD38C = 0x800D3A9C;
const int s14e_dword_800DD390 = 0x800D45D4;
const int s14e_dword_800DD394 = 0x800D3B18;
const int s14e_dword_800DD398 = 0x800D3B38;
const int s14e_dword_800DD39C = 0x800D3E4C;
const int s14e_dword_800DD3A0 = 0x800D45D4;
const int s14e_dword_800DD3A4 = 0x800D45D4;
const int s14e_dword_800DD3A8 = 0x800D45D4;
const int s14e_dword_800DD3AC = 0x800D3F04;
const int s14e_dword_800DD3B0 = 0x800D3F2C;
const int s14e_dword_800DD3B4 = 0x800D45D4;
const int s14e_dword_800DD3B8 = 0x800D45D4;
const int s14e_dword_800DD3BC = 0x800D45D4;
const int s14e_dword_800DD3C0 = 0x800D3FC4;
const int s14e_dword_800DD3C4 = 0x800D4000;
const int s14e_dword_800DD3C8 = 0x800D4044;
const int s14e_dword_800DD3CC = 0x800D45D4;
const int s14e_dword_800DD3D0 = 0x800D45D4;
const int s14e_dword_800DD3D4 = 0x800D45D4;
const int s14e_dword_800DD3D8 = 0x800D45D4;
const int s14e_dword_800DD3DC = 0x800D45D4;
const int s14e_dword_800DD3E0 = 0x800D45D4;
const int s14e_dword_800DD3E4 = 0x800D45D4;
const int s14e_dword_800DD3E8 = 0x800D4060;
const int s14e_dword_800DD3EC = 0x800D409C;
const int s14e_dword_800DD3F0 = 0x800D4260;
const int s14e_dword_800DD3F4 = 0x800D4284;
const int s14e_dword_800DD3F8 = 0x800D42FC;
const int s14e_dword_800DD3FC = 0x800D4334;
const int s14e_dword_800DD400 = 0x800D45D4;
const int s14e_dword_800DD404 = 0x800D4340;
const int s14e_dword_800DD408 = 0x800D4374;
const int s14e_dword_800DD40C = 0x800D4570;

const char s14e_dword_800DD410[] = "crow";
const char s14e_dword_800DD418[] = "ele_crow.c";

/*----------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D2DC8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D2E10.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D2F60.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D2FE0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D3034.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D308C.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D30F4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D31F8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D3274.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D33F4.s")

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D342C.s")

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D47D4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D4AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D4CA8.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800D4D50.s")
