#include "libgcl/libgcl.h"
#include "Thing/door.h"
#include "Equip/kogaku2.h"
#include "../s16b/Enemy/wall.h"
#include "libgcl/hash.h"

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

// Takabe/gas_efct.c
unsigned short gas_efct_msgs[] = {0xD182, 0x006B};

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

// Takabe/cinema.c
unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

// Game/lamp.c
const char aTexparseerror[] = "TEX:PARSE ERROR\n";
const char aLampC[] = "lamp.c";

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = "wall.c";

// Enemy/demokage.c
const char aShadow[] = "shadow";
const char aDemokageC[] = "demokage.c";

// Takabe/gas_efct.c
const char aGasEfctC[] = {'g', 'a', 's', '_', 'e', 'f', 'c', 't', '.', 'c', '\x00', ','};

// Takabe/fadeio.c
const char aFadeioC[] = {'f', 'a', 'd', 'e', 'i', 'o', '.', 'c', 0x0, 'J', 'h', 0xd};

const char aCinemaC[] = {'c', 'i', 'n', 'e', 'm', 'a', '.', 'c', 0x0, '\n', 'R', 'p'};
