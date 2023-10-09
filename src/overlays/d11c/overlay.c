#include "libgcl/libgcl.h"
#include "Thing/door.h"
#include "Equip/kogaku2.h"
#include "../s16b/Enemy/wall.h"

GCL_ActorTableEntry d11cOverlayCharas[] = 
{
    { 0x1AD3, (TGCL_ActorCreateFn)0x800C3B34 },
    { 0xB997, NewDoor_8006FD00 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800C6614 },
    { 0xEC77, NewWall_800C3718 },
    { 0x5A50, (TGCL_ActorCreateFn)0x800C4E5C },
    { 0x0003, (TGCL_ActorCreateFn)0x800C5DA0 },
    { 0x0004, (TGCL_ActorCreateFn)0x800C5DA0 },
    { 0x000F, (TGCL_ActorCreateFn)0x800C48A4 },
    { 0x001A, (TGCL_ActorCreateFn)NewKogaku2_800615FC },
    { 0x001B, (TGCL_ActorCreateFn)NewKogaku3_80061708 },
    { 0, 0 }
};

int d11c_dword_800C3260 = 0x006BD182;
int d11c_dword_800C3264 = 0x71F13223;

// Takabe/cinema.c
unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

const char d11c_aTexparseerror_800C66EC[] = "TEX:PARSE ERROR\n";
const char d11c_aLampc_800C6700[] = "lamp.c";

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = "wall.c";

const char d11c_aShadow_800C6734[] = "shadow";
const char d11c_aDemokagec_800C673C[] = "demokage.c";
const char d11c_dword_800C6748[] = {'g', 'a', 's', '_'};
const char d11c_dword_800C674C[] = {'e', 'f', 'c', 't'};
const char d11c_dword_800C6750[] = {'.', 'c', 0x0, ','};
const char d11c_dword_800C6754[] = {'f', 'a', 'd', 'e'};
const char d11c_dword_800C6758[] = {'i', 'o', '.', 'c'};
const char d11c_dword_800C675C[] = {0x0, 'J', 'h', 0xd};
const char aCinemaC[] = {'c', 'i', 'n', 'e', 'm', 'a', '.', 'c', 0x0, '\n', 'R', 'p'};
