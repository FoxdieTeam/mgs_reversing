#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "Okajima/red_alrt.h"

GCL_ActorTableEntry d03aOverlayCharas[] =
{
    { 0xB997, (TGCL_ActorCreateFn)0x8006FD00 },
    { 0xF5C5, (TGCL_ActorCreateFn)0x800C42F8 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800C7240 },
    { 0x0003, (TGCL_ActorCreateFn)0x800C69CC },
    { 0x0004, (TGCL_ActorCreateFn)0x800C69CC },
    { 0x000F, (TGCL_ActorCreateFn)0x800C38E8 },
    { 0x0028, (TGCL_ActorCreateFn)0x800C789C },
    { 0x0037, (TGCL_ActorCreateFn)0x800C4E84 },
    { 0x0038, (TGCL_ActorCreateFn)0x800C4F48 },
    { 0x0042, (TGCL_ActorCreateFn)0x800C5B24 },
    { 0x0044, (TGCL_ActorCreateFn)0x800C54D4 },
    { 0, 0 }
};

RECT uji_rect = {100, 100, 200, 200};

RedAlrtWork *d03a_dword_800C3270 = NULL;

// Takabe/gas_efct.c
unsigned short gas_efct_msgs[] = {0xD182, 0x006B};

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

// Takabe/cinema.c
unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

// Enemy/demokage.c
const char aShadow[] = "shadow";
const char aDemokageC[] = "demokage.c";

const char aUji[] = "uji";
const char aUjiC[] = {'u', 'j', 'i', '.', 'c', 0x00, 0x1c, 0x00};

const char d03a_dword_800C7980[]  = "開く";   // close
const char d03a_dword_800C7988[]  = "閉める"; // open
const char d03a_aOpen_800C7990[]  = "open";
const char d03a_aClose_800C7998[] = "close";
const char d03a_aKill_800C79A0[]  = "kill";
