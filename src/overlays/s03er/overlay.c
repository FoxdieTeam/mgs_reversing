#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "Anime/animeconv/anime.h"

GCL_ActorTableEntry s03eOverlayCharas[] =
{
    { 0x92BC, (TGCL_ActorCreateFn)0x800C6558 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800CBA94 },
    { 0xEC77, (TGCL_ActorCreateFn)0x800C5E68 },
    { 0xE253, (TGCL_ActorCreateFn)0x800C4AD8 },
    { 0xF5C5, (TGCL_ActorCreateFn)0x800C6EDC },
    { 0x1AD3, (TGCL_ActorCreateFn)0x800C5454 },
    { 0xA9C5, (TGCL_ActorCreateFn)0x800C9190 },
    { 0xA12E, (TGCL_ActorCreateFn)0x800CB2B8 },
    { 0xDD8B, (TGCL_ActorCreateFn)0x800C5748 },
    { 0x51C6, (TGCL_ActorCreateFn)0x800CBE84 },
    { 0x0FAD, (TGCL_ActorCreateFn)0x800C5944 },
    { 0, 0 }
};

unsigned short s03e_dword_800C3268[] = {0x121F, 0x8D5C, HASH_ENTER, HASH_LEAVE, 0x8591, 0x6555, 0x2EAB};

char s03e_dword_800C3278[] = {0x7F, 0x02, 0x00, 0x00};
char s03e_dword_800C327C[] = {0x55, 0x02, 0x6E, 0x02, 0x1E, 0x0E, 0x41, 0x04, 0x7D, 0x06, 0x5F, 0x06, 0x46, 0x08, 0x37, 0x0A, 0x2D, 0x0C, 0x00, 0x00};
char s03e_dword_800C3290[] = {0x00, 0x0A, 0x7F, 0x02, 0x00, 0x1E, 0x7F, 0x02, 0x00, 0x00, 0x00, 0x00};
char s03e_dword_800C329C[] = {0x23, 0x04, 0x4B, 0x04, 0x87, 0x06, 0x41, 0x08, 0x2D, 0x0C, 0x41, 0x06, 0x5F, 0x04, 0x00, 0x00};

// Okajima/uji.c
RECT uji_rect = {100, 100, 200, 200};

int s03e_dword_800C32B4 = 0x00000000;
int s03e_dword_800C32B8 = 0x00000000;
int s03e_dword_800C32BC = 0x00000000;

RECT guncame_rect = {80, 80, 160, 160};
SVECTOR guncame_svec = {300, 300, 300, 0};

extern const char anim_data_800CC124[];
ANIMATION anm_800C3B78 = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 800, 800, 128, NULL, (char *)anim_data_800CC124};

extern const char anim_data_800CC14C[];
ANIMATION anm_800C3B94 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800CC14C};

extern const char anim_data_800CC164[];
ANIMATION anm_800C3BB0 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800CC164};

extern const char anim_data_800CC1CC[];
ANIMATION anm_800C3BCC = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 0, NULL, (char *)anim_data_800CC1CC};

extern const char anim_data_800CC244[];
ANIMATION anm_800C3BE8 = {PCX_SMOKE, 8, 4, 30, 1, 500, 2, 400, 400, 32, NULL, (char *)anim_data_800CC244};

const char s03e_aMessagein_800CBF18[] = "message in\n";
const char s03e_aMessageout_800CBF24[] = "message out\n";
const char s03e_aMessagex_800CBF34[] = "message %X\n";
const char s03e_aNofloorproc_800CBF40[] = "NO FLOOR PROC\n";
const char s03e_aRotd_800CBF50[] = "ROT %d\n";
const char s03e_aReqdoorclose_800CBF58[] = "REQ:DOOR CLOSE\n";
const char s03e_aInitopen_800CBF68[] = "INiTOPEN\n";
const char s03e_dword_800CBF74[] = {0x0, 0x0, 0x0, 0x0};
