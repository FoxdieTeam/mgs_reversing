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

extern const char anim_data_800CC2AC[];
ANIMATION anm_800C335C = {PCX_B_MARK, 1, 1, 1, 1, 500, 1, 80, 80, 0, NULL, (char *)anim_data_800CC2AC};

extern const char anim_data_800CC410[];
ANIMATION anm_800C3378 = {PCX_Q_MARK, 1, 1, 1, 1, 500, 1, 80, 80, 0, NULL, (char *)anim_data_800CC410};

extern const char anim_data_800CC514[];
ANIMATION anm_800C3394 = {PCX_Q_MARK, 1, 1, 1, 1, 500, 1, 80, 80, 0, NULL, (char *)anim_data_800CC514};

extern const char anim_data_800CC618[];
ANIMATION anm_800C33B0 = {PCX_HEART, 1, 1, 1, 1, 0, 1, 70, 70, 255, NULL, (char *)anim_data_800CC618};

unsigned short s03e_dword_800C33CC[] = {PCX_B_MARK, PCX_Q_MARK, PCX_HEART};

const char s03e_dword_800CBE84[] = {0xe0, 0xff, 0xbd, '\''};
const char s03e_dword_800CBE88[] = {0x14, 0x0, 0xb1, 0xaf};
const char s03e_dword_800CBE8C[] = {'!', 0x88, 0x80, 0x0};
const char s03e_dword_800CBE90[] = {0x18, 0x0, 0xb2, 0xaf};
const char s03e_dword_800CBE94[] = {'!', 0x90, 0xa0, 0x0};
const char s03e_dword_800CBE98[] = {0x5, 0x0, 0x4, '$'};
const char s03e_dword_800CBE9C[] = {'4', 0x0, 0x5, '$'};
const char s03e_dword_800CBEA0[] = {0x1c, 0x0, 0xbf, 0xaf};
const char s03e_dword_800CBEA4[] = {'9', 'T', 0x0, 0xc};
const char s03e_dword_800CBEA8[] = {0x10, 0x0, 0xb0, 0xaf};
const char s03e_dword_800CBEAC[] = {'!', 0x80, '@', 0x0};
const char s03e_dword_800CBEB0[] = {0x12, 0x0, 0x0, 0x12};
const char s03e_dword_800CBEB4[] = {'!', ' ', 0x0, 0x2};
const char s03e_dword_800CBEB8[] = {0xd, 0x80, 0x5, '<'};
const char s03e_dword_800CBEBC[] = {0x98, 0xbc, 0xa5, '$'};
const char s03e_dword_800CBEC0[] = {0xd, 0x80, 0x6, '<'};
const char s03e_dword_800CBEC4[] = {0xc, 0xbd, 0xc6, '$'};
const char s03e_dword_800CBEC8[] = {0xd, 0x80, 0x7, '<'};
const char s03e_dword_800CBECC[] = {'S', 'T', 0x0, 0xc};
const char s03e_dword_800CBED0[] = {0xac, 0xc6, 0xe7, '$'};
const char s03e_dword_800CBED4[] = {'!', ' ', 0x0, 0x2};
const char s03e_dword_800CBED8[] = {'!', '(', ' ', 0x2};
const char s03e_dword_800CBEDC[] = {'n', '/', 0x3, 0xc};
const char s03e_dword_800CBEE0[] = {'!', '0', '@', 0x2};
const char s03e_dword_800CBEE4[] = {0x6, 0x0, 'A', 0x4};
const char s03e_dword_800CBEE8[] = {'!', 0x10, 0x0, 0x2};
const char s03e_dword_800CBEEC[] = {'r', 'T', 0x0, 0xc};
const char s03e_dword_800CBEF0[] = {'!', ' ', 0x0, 0x2};
const char s03e_dword_800CBEF4[] = {0xc0, '/', 0x3, 0x8};
const char s03e_dword_800CBEF8[] = {'!', 0x10, 0x0, 0x0};
const char s03e_dword_800CBEFC[] = {'!', 0x10, 0x0, 0x2};
const char s03e_dword_800CBF00[] = {0x1c, 0x0, 0xbf, 0x8f};
const char s03e_dword_800CBF04[] = {0x18, 0x0, 0xb2, 0x8f};
const char s03e_dword_800CBF08[] = {0x14, 0x0, 0xb1, 0x8f};
const char s03e_dword_800CBF0C[] = {0x10, 0x0, 0xb0, 0x8f};
const char s03e_dword_800CBF10[] = {0x8, 0x0, 0xe0, 0x3};
const char s03e_dword_800CBF14[] = {' ', 0x0, 0xbd, '\''};
const char s03e_aMessagein_800CBF18[] = "message in\n";
const char s03e_aMessageout_800CBF24[] = "message out\n";
const char s03e_aMessagex_800CBF34[] = "message %X\n";
const char s03e_aNofloorproc_800CBF40[] = "NO FLOOR PROC\n";
const char s03e_aRotd_800CBF50[] = "ROT %d\n";
const char s03e_aReqdoorclose_800CBF58[] = "REQ:DOOR CLOSE\n";
const char s03e_aInitopen_800CBF68[] = "INiTOPEN\n";
const char s03e_dword_800CBF74[] = {0x0, 0x0, 0x0, 0x0};
