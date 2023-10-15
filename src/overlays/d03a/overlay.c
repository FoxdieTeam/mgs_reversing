#include "libgcl/libgcl.h"
#include "libgcl/hash.h"

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

int d03a_dword_800C3268 = 0x00640064;
int d03a_dword_800C326C = 0x00C800C8;
int d03a_dword_800C3270 = 0x00000000;
int d03a_dword_800C3274 = 0x006BD182;

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

// Takabe/cinema.c
unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

// Enemy/demokage.c
const char aShadow[] = "shadow";
const char aDemokageC[] = "demokage.c";

const char d03a_aUji_800C7974[] = "uji";
const char d03a_dword_800C7978[] = {'u', 'j', 'i', '.'};
const char d03a_dword_800C797C[] = {'c', 0x0, 0x1c, 0x0};
const char d03a_dword_800C7980[] = {0xb3, 0xab, 0xa4, 0xaf};
const char d03a_dword_800C7984[] = {0x0, 0x0, 0x0, 0x0};
const char d03a_dword_800C7988[] = {0xca, 0xc4, 0xa4, 0xe1};
const char d03a_dword_800C798C[] = {0xa4, 0xeb, 0x0, 0x0};
const char d03a_aOpen_800C7990[] = "open";
const char d03a_aClose_800C7998[] = "close";
const char d03a_aKill_800C79A0[] = "kill";
const int d03a_dword_800C79A8 = 0x800C46B8;
const int d03a_dword_800C79AC = 0x800C46C4;
const int d03a_dword_800C79B0 = 0x800C46B8;
const int d03a_dword_800C79B4 = 0x800C46C4;
const int d03a_dword_800C79B8 = 0x800C46C4;
const char d03a_aRedalrtc_800C79BC[] = "red_alrt.c";
const char d03a_aBlurpurec_800C79C8[] = "blurpure.c";
const char d03a_dword_800C79D4[] = {'g', 'a', 's', '_'};
const char d03a_dword_800C79D8[] = {'e', 'f', 'c', 't'};
const char d03a_dword_800C79DC[] = {'.', 'c', 0x0, ' '};

// Takabe/fadeio.c
const char aFadeioC[] = {'f', 'a', 'd', 'e', 'i', 'o', '.', 'c', 0x0, 0x2, '@', 0x0};

// Takabe/cinema.c
const char aCinemaC[] = {'c', 'i', 'n', 'e', 'm', 'a', '.', 'c', 0x0, 0xc, '.', 0x0};
