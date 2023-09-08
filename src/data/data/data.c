#include "linker.h"
#include "data.h"

#include "data/rdata/rdata.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Menu/menuman.h"
#include "libdg/libdg.h"
#include "Thing/door.h"
#include "mts/mts_new.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "Game/control.h"
#include "chara/snake/sna_init.h"
#include "libgcl/hash.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "Bullet/blast.h"
#include "Equip/jpegcam.h"
#include "Menu/radar.h"
#include "Game/item.h"

// sdata

extern const char  aSAVEPHOTO[];

extern const char  aSnaChest1[];
extern const char  aSnaChest2[];
extern const char  aSnaChest3[];
extern const char  aSnaHip1[];
extern const char  aSnaArmer1[];
extern const char  aSnaArmer2[];
extern const char  aSnaArmer3[];
extern const char  aSnaArmer4[];

extern const char  aCbBox11[];
extern const char  aCbBox12[];
extern const char  aCbBox41[];
extern const char  aCbBox42[];
extern const char  aCbBox21[];
extern const char  aCbBox22[];
extern const char  aCbBox41[];
extern const char  aCbBox42[];

extern const char  aSnaFace[];
extern const char  aSnaFace2[];
extern const char  aSnaFace3[];

extern const char  aSnaMf1[];
extern const char  aSnaMf2[];
extern const char  aSnaMf3[];

short word_8009EFC0[] = {0, 500, 0, 320, 400, 320, 400, 32, 32, 0};

SVECTOR stru_8009EFD4[2] = {{-100, 200, 200, 0}, {-150, 18, 200, 0}};

Target_Data stru_8009EFE4[4] =
{
    {{0, 0, 300, 0}, {400, 600, 400, 0}, 0, 0, 64, 0}, // TODO: Might not be part of this array, might be its own element
    {{-400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{0, 0, 0, 0}, {501, 600, 501, 0}, 0, 0, 7, 0}
};

MATRIX stru_8009F064 = {{{-200, 200, 600}, {0, 400, 200}, {400, 0, 5}}, {50, 0, 1}};
MATRIX stru_8009F084 = {{{200, 200, 600}, {0, 400, 200}, {400, 0, -5}}, {50, 0, 1}};
MATRIX stru_8009F0A4 = {{{0, 200, 600}, {0, 500, 250}, {500, 0, 0}}, {100, 0, 3}};

GV_PAD GV_PadData_8009F0C4 = {0, 0, 0, 0, -1, 0, 0, 0, 0, 0};

struct ANIMATION SECTION(".data") stru_8009F0D4 = {-8302, 2, 2, 4, 1, 0, 5, 50, 50, 250, 0, (void *)0x800124A8};
struct ANIMATION SECTION(".data") stru_8009F0F0 = {20781, 8, 4, 30, 1, 300, 1, 400, 400, 32, 0, (void *)0x8001253C};
struct ANIMATION SECTION(".data") stru_8009F10C = {-6964, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (void *)0x800125CC};
struct ANIMATION SECTION(".data") stru_8009F128 = {-6964, 2, 2, 4, 1, 300, 1, 1400, 1400, 128, 0, (void *)0x800125F4};
struct ANIMATION SECTION(".data") stru_8009F144 = {-6964, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (void *)0x8001261C};
struct ANIMATION SECTION(".data") stru_8009F160 = {-370, 2, 2, 3, 1, 300, 1, 600, 600, 100, 0, (void *)0x80012628};
struct ANIMATION SECTION(".data") stru_8009F17C = {32332, 2, 2, 4, 1, 200, 5, 100, 100, 128, 0, (void *)0x80012634};
struct ANIMATION SECTION(".data") stru_8009F198 = {20781, 8, 4, 30, 8, 0, 3, 2200, 2200, 77, 0, (void *)0x80012708};
struct ANIMATION SECTION(".data") stru_8009F1B4 = {20781, 8, 4, 30, 1, 0, 1, 1000, 1000, 77, 0, (void *)0x80012728};
struct ANIMATION SECTION(".data") stru_8009F1D0 = {20781, 8, 4, 30, 4, 0, 1, 2200, 2200, 128, 0, (void *)0x80012750};
struct ANIMATION SECTION(".data") stru_8009F1EC = {20781, 8, 4, 30, 1, 1000, 3, 400, 400, 128, 0, (void *)0x800127A4};
struct ANIMATION SECTION(".data") stru_8009F208 = {20781, 8, 4, 30, 1, 1000, 3, 30, 30, 10, 0, (void *)0x800127D0};

int SECTION(".data") dword_8009F224 = 0;

TAnimeVMFn SECTION(".data") anime_fn_table_8009F228[] = {
    anime_fn_0_8005EC1C, anime_fn_1_8005ED0C, anime_fn_2_8005ED74, anime_fn_3_8005EDDC, anime_fn_4_8005EE44,
    anime_fn_5_8005EEA4, anime_fn_6_8005EF04, anime_fn_7_8005EFF8, anime_fn_8_8005F0F0, anime_fn_9_8005F180,
    anime_fn_10_8005F288, anime_fn_11_8005F2F4, anime_fn_12_8005F37C, anime_fn_13_8005F408, anime_fn_14_8005F438};

// TODO: Warning without const, but can't be const else would end up in rdata section?
const char *SECTION(".data") off_8009F264[4] = {aSnaChest1, aSnaChest2, aSnaChest3, aSnaHip1};
const char *SECTION(".data") off_8009F274[4] = {aSnaArmer1, aSnaArmer2, aSnaArmer3, aSnaArmer4};

int SECTION(".data") dword_8009F284 = 0;

const char *SECTION(".data") off_8009F288[8] = {aCbBox11, aCbBox12, aCbBox41, aCbBox42, aCbBox21, aCbBox22, aCbBox41, aCbBox42};

// TODO: Ditto const stuff
const char *SECTION(".data") off_8009F2A8[3] = {aSnaFace, aSnaFace2, aSnaFace3};
const char *SECTION(".data") off_8009F2B4[3] = {aSnaMf1, aSnaMf2, aSnaMf3};

int     SECTION(".data") dword_8009F2C0 = 0;
short   SECTION(".data") scope_created_8009F2C4 = 0;
SVECTOR SECTION(".data") svec_8009F2C8 = {0, 0, 0, 0};
int     SECTION(".data") dword_8009F2D0[] = {0, 0xC80};

menu_save_mode_data SECTION(".data") stru_8009F2D8 = {{0x43, 4}, 0, 2, (char *)aSAVEPHOTO, (void *)jpegcam_unk1_80063704, (void *)jpegcam_unk2_80063888, (void *)jpegcam_unk3_800638B4};

char SECTION(".data") gJpegcamZigZagTable_8009F2EC[64] = {
    0x00, 0x01, 0x08, 0x10, 0x09, 0x02, 0x03, 0x0A,
    0x11, 0x18, 0x20, 0x19, 0x12, 0x0B, 0x04, 0x05,
    0x0C, 0x13, 0x1A, 0x21, 0x28, 0x30, 0x29, 0x22,
    0x1B, 0x14, 0x0D, 0x06, 0x07, 0x0E, 0x15, 0x1C,
    0x23, 0x2A, 0x31, 0x38, 0x39, 0x32, 0x2B, 0x24,
    0x1D, 0x16, 0x0F, 0x17, 0x1E, 0x25, 0x2C, 0x33,
    0x3A, 0x3B, 0x34, 0x2D, 0x26, 0x1F, 0x27, 0x2E,
    0x35, 0x3C, 0x3D, 0x36, 0x2F, 0x37, 0x3E, 0x3F
};

char SECTION(".data") gJpegcamQuantTable_8009F32C[64] = {
    0x02, 0x10, 0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22,
    0x10, 0x10, 0x16, 0x18, 0x1B, 0x1D, 0x22, 0x25,
    0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x22, 0x26,
    0x16, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x25, 0x28,
    0x16, 0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30,
    0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30, 0x3A,
    0x1A, 0x1B, 0x1D, 0x22, 0x26, 0x2E, 0x38, 0x45,
    0x1B, 0x1D, 0x23, 0x26, 0x2E, 0x38, 0x45, 0x53
};

TMat8x8B SECTION(".data") gJpegcamMatrix1_8009F36C = {
    {0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D},
    {0x3F, 0x35, 0x23, 0x0C, 0xF4, 0xDD, 0xCB, 0xC1},
    {0x3B, 0x18, 0xE8, 0xC5, 0xC5, 0xE8, 0x18, 0x3B},
    {0x35, 0xF4, 0xC1, 0xDD, 0x23, 0x3F, 0x0C, 0xCB},
    {0x2D, 0xD3, 0xD3, 0x2D, 0x2D, 0xD3, 0xD3, 0x2D},
    {0x23, 0xC1, 0x0C, 0x35, 0xCB, 0xF4, 0x3F, 0xDD},
    {0x18, 0xC5, 0x3B, 0xE8, 0xE8, 0x3B, 0xC5, 0x18},
    {0x0C, 0xDD, 0x35, 0xC1, 0x3F, 0xCB, 0x23, 0xF4}
};
SVECTOR SECTION(".data") dword_8009F3AC = {0, 0, 0, 0};
SVECTOR SECTION(".data") stru_8009F3B4[2] = {{0, 0, 3200, 0}, {20, -370, 60, 0}};
SVECTOR SECTION(".data") stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
SVECTOR SECTION(".data") stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

int        SECTION(".data") dword_8009F3E4[] = {0x7A643B88, 0xF83D7A64};
int        SECTION(".data") dword_8009F3EC[] = {0x800000, 0x96};
int        SECTION(".data") dword_8009F3F4[] = {0x320000, 0xC8};
int        SECTION(".data") dword_8009F3FC[] = {0x200000, 0x20, 0x1180000, 0x50};

char       SECTION(".data") byte_8009F40C[] = {0, 2, 127, 4, 0};
char       SECTION(".data") byte_8009F414[] = {145, 4, 75, 10, 0};

SVECTOR    SECTION(".data") dword_8009F41C[2] = {{0, 0, 0, 0}, {0, 0, 3000, 0}};
int        SECTION(".data") used_counter_8009F42C = 0;
int        SECTION(".data") dword_8009F430 = 0;
int        SECTION(".data") dword_8009F434 = 0;
SVECTOR    SECTION(".data") svector_8009F438 = {3072, 0, 0, 0};
int        SECTION(".data") dword_8009F440 = 0;
int        SECTION(".data") dword_8009F444 = 0;
int        SECTION(".data") counter_8009F448 = 0;
SVECTOR    SECTION(".data") svec_8009F44C = {0xFD8F, 0xFF06, 0x2EE, 0};
SVECTOR    SECTION(".data") svec_8009F454 = {0xFE0C, 0xFF06, 0x2EE, 0};
SVECTOR    SECTION(".data") svec_8009F45C = {0x1F4, 0xC8, 0x1F4, 0};
SVECTOR    SECTION(".data") svec_8009F464 = {0x12C, 0xC8, 0x12C, 0};
int        SECTION(".data") dword_8009F46C = 0;
int        SECTION(".data") dword_8009F470 = 0;
int        SECTION(".data") dword_8009F474 = 0;
SVECTOR    SECTION(".data") svector_8009F478 = {0, 0, 0, 0};
int        SECTION(".data") dword_8009F480 = 0;
short      SECTION(".data") Nik_Blast_8009F484 = 0;
SVECTOR    SECTION(".data") svector_8009F488 = {100, 100, 100, 0};
int        SECTION(".data") dword_8009F490 = 0;
SVECTOR    SECTION(".data") svector_8009F494 = {0, 0, 0, 0};
int        SECTION(".data") dword_8009F49C = 0;
SVECTOR    SECTION(".data") svector_8009F4A0 = {0, -800, 0, 0};
SVECTOR    SECTION(".data") svector_8009F4A8 = {0, -350, 0, 0};
SVECTOR    SECTION(".data") svector_8009F4B0 = {0, -100, -70, 0};

Blast_Data SECTION(".data") blast_data_8009F4B8 = {0x100, 5, 0x3E8, 0x7D0, 2};
Blast_Data SECTION(".data") blast_data_8009F4CC = {0x100, 5, 0x3E8, 0x7D0, 6};
Blast_Data SECTION(".data") blast_data_8009F4E0 = {0x100, 5, 0x3E8, 0x7D0, 5};
Blast_Data SECTION(".data") blast_data_8009F4F4 = {0x100, 5, 0x3E8, 0x7D0, 4};
Blast_Data SECTION(".data") blast_data_8009F508 = {0x100, 5, 0x3E8, 0x7D0, 3};
Blast_Data SECTION(".data") blast_data_8009F51C = {0x100, 5, 0x3E8, 0x7D0, -1};
Blast_Data SECTION(".data") blast_data_8009F530 = {0x400, 5, 0x3E8, 0x7D0, 10};
Blast_Data SECTION(".data") blast_data_8009F544 = {0, 0, 1, 1, -1};

SVECTOR SECTION(".data") svector_8009F558[2] = {{100, 0, 0, 0}, {2000, 2000, 4000, 4000}};

ANIMATION SECTION(".data") stru_8009F568 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BAC};
ANIMATION SECTION(".data") stru_8009F584 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BEC};
ANIMATION SECTION(".data") stru_8009F5A0 = {-21358, 4, 4, 16, 1, 2000, 1, 500, 500, 128, NULL, (void *)0x80012C2C};
ANIMATION SECTION(".data") stru_8009F5BC = {-21358, 4, 4, 16, 1, 2000, 1, 200, 200, 128, NULL, (void *)0x80012C6C};
ANIMATION SECTION(".data") stru_8009F5D8 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012CAC};

int SECTION(".data") door_where_8009F5F4 = 0;

char  SECTION(".data") byte_8009F5F8[] = {0, 0, 0, 0};
short SECTION(".data") word_8009F5FC = 1;
int   SECTION(".data") dword_8009F600 = 0;
int   SECTION(".data") dword_8009F604 = 0xFFFFFFFF;
int   SECTION(".data") dword_8009F608 = 0;

RECT SECTION(".data") a22dd_8009F60C = {50, 50, 100, 100};

ANIMATION SECTION(".data") stru_8009F614 = {31572, 1, 1, 1, 1, 500, 3, 300, 300, 200, NULL, (void *)0x80012E84};

SVECTOR SECTION(".data") stru_8009F630[4] = {{20, 0, 0, 0}, {-20, 0, 0, 0}, {0, 20, 0, 0}, {0, -20, 0, 0}};

SVECTOR SECTION(".data") stru_8009F650[2] = {{0, 0, 200, 0}, {0, 0, 10000, 0}};

SVECTOR SECTION(".data") stru_8009F660 = {100, 100, 100, 0};

int SECTION(".data") gSparkRandomTableIndex_8009F668 = 0xFFFFFFFF;
int SECTION(".data") gSparkRandomTableIndex2_8009F66C = 0;

struct ANIMATION SECTION(".data") stru_8009F670 = {
    19692, 1, 1, 1, 1, 500, 3, 800, 800, 128, 0, (void *)animation_data_80012F2C};
struct ANIMATION SECTION(".data") stru_8009F68C = {
    21926, 1, 1, 1, 1, 500, 3, 600, 600, 180, 0, (void *)animation_data_80012F50};

int     SECTION(".data") dword_8009F6A8 = 0;

SVECTOR SECTION(".data") svec_8009F6AC[4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

SVECTOR SECTION(".data") svec_8009F6CC = {0, 400, 0, 0};
VECTOR  SECTION(".data") vec_8009F6D4 = {0, 0, 0, 0};
SVECTOR SECTION(".data") svec_8009F6E4 = {0, 55536, 0, 0};
SVECTOR SECTION(".data") svec_8009F6EC = {100, 100, 100, 0};
SVECTOR SECTION(".data") svec_8009F6F4 = {0, 0, 0, 0};
SVECTOR SECTION(".data") svec_8009F6FC = {0, 400, 0, 0};
RECT    SECTION(".data") rect_8009F704 = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F70C = {768, 196, 256, 2};
short   SECTION(".data") word_8009F714[] = {0, 0};
RECT    SECTION(".data") rect_8009F718 = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F720 = {768, 196, 256, 2};
int     SECTION(".data") dword_8009F728 = 0;
RECT    SECTION(".data") rect_8009F72C = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F734 = {768, 196, 256, 2};

ANIMATION SECTION(".data") stru_8009F73C = {20781, 8, 4, 30, 1, 1000, 3, 500, 500, 255, NULL, (void *)0x8001345C};
ANIMATION SECTION(".data") stru_8009F758 = {20781, 8, 4, 30, 3, 0, 1, 1000, 1000, 64, NULL, (void *)0x80013488};
ANIMATION SECTION(".data") stru_8009F774 = {20781, 8, 4, 30, 8, 0, 3, 2200, 2200, 255, NULL, (void *)0x800134DC};
ANIMATION SECTION(".data") stru_8009F790 = {9287, 2, 2, 4, 1, 300, 1, 5000, 5000, 128, NULL, (void *)0x80013510};

SVECTOR SECTION(".data") svector_8009F7AC = {0, 255, 0, 0};