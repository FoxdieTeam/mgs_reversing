#include "libgcl/libgcl.h"
#include "Anime/animeconv/anime.h"
#include "libgcl/hash.h"

extern const char aRation_800DFE94[];
extern const char aSocombullet_800DFE80[];
extern const char aFamasbullet_800DFE6C[];

GCL_ActorTableEntry s00aOverlayCharas[] =
{
    { 0x63AA, (TGCL_ActorCreateFn)0x800D872C },
    { 0xCBF8, (TGCL_ActorCreateFn)0x800C37EC },
    { 0xFED1, (TGCL_ActorCreateFn)0x8005D508 },
    { 0x4170, (TGCL_ActorCreateFn)0x800C3A1C },
    { 0x3F9A, (TGCL_ActorCreateFn)0x800DF424 },
    { 0x7BC2, (TGCL_ActorCreateFn)0x800DF6AC },
    { 0x51C6, (TGCL_ActorCreateFn)0x800DFA88 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800DE4D8 },
    { 0x3ED7, (TGCL_ActorCreateFn)0x800DCFD4 },
    { 0xB103, (TGCL_ActorCreateFn)0x800DEBEC },
    { 0x92BC, (TGCL_ActorCreateFn)0x800D3808 },
    { 0x02C4, (TGCL_ActorCreateFn)0x800D1A70 },
    { 0xEC77, (TGCL_ActorCreateFn)0x800D3118 },
    { 0xBA52, (TGCL_ActorCreateFn)0x800DEEE0 },
    { 0x30CE, (TGCL_ActorCreateFn)0x800D7A2C },
    { 0xC6D7, (TGCL_ActorCreateFn)0x800D0908 },
    { 0xDBA3, (TGCL_ActorCreateFn)0x800DACCC },
    { 0x6E9A, (TGCL_ActorCreateFn)0x800C5034 },
    { 0x170C, (TGCL_ActorCreateFn)0x800D2BEC },
    { 0x32E5, (TGCL_ActorCreateFn)0x800C3E50 },
    { 0x2ABC, (TGCL_ActorCreateFn)0x800D9F30 },
    { 0xD4A5, (TGCL_ActorCreateFn)0x800D5234 },
    { 0x81EA, (TGCL_ActorCreateFn)0x800D8244 },
    { 0x7FF7, (TGCL_ActorCreateFn)0x800DDB34 },
    { 0x1A02, (TGCL_ActorCreateFn)0x800D5D9C },
    { 0x5D64, (TGCL_ActorCreateFn)0x800DE9C8 },
    { 0xA12E, (TGCL_ActorCreateFn)0x800DD4A8 },
    { 0, 0 }
};

extern const char s00a_dword_800DFBE0[];
extern const char s00a_dword_800DFC30[];

ANIMATION anm_breath_800C32E8  = { 0x512D, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, s00a_dword_800DFBE0 };
ANIMATION anm_unknown_800C3304 = { 0x512D, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, s00a_dword_800DFC30 };

RECT rect_800C3320 = { 1000, 1000, 2000, 2000 };

int s00a_dword_800C3328[8]  = { 2500, 3500, 4000, 5000, 5500, 5600, 5700, 5800 };
unsigned short s00a_dword_800C3348[8] = { 450, 15, 30, 60, 90, 0, 32001, 30000 };

short ActTable_800C3358[54] =
{
    0x13, 0x14, 0x0A, 0x16, 0x09, 0x22, 0x23, 0x24, 0x2D,
    0x0D, 0x0C, 0x1A, 0x0F, 0x0E, 0x10, 0x1B, 0x08, 0x2E,
    0x32, 0x15, 0x1E, 0x1F, 0x20, 0x21, 0x25, 0x34, 0x35,
    0x19, 0x05, 0x02, 0x2A, 0x04, 0x27, 0x28, 0x06, 0x07,
    0x26, 0x03, 0x29, 0x11, 0x12, 0x2B, 0x17, 0x18, 0x1C,
    0x1D, 0x00, 0x01, 0x33, 0x11, 0x12, 0x2B, 0x16, 0x0B
};

SVECTOR s00a_dword_800C33C4 = { -150,  0, 300 };
SVECTOR s00a_dword_800C33CC = { 0,  -550, 950 };
SVECTOR s00a_dword_800C33D4 = { 0,     0, 100 };
SVECTOR s00a_dword_800C33DC = { -1024, 0,   0 };
SVECTOR s00a_dword_800C33E4 = { 0,     0, 100 };
SVECTOR s00a_dword_800C33EC = { -1024, 0,   0 };

const char *s00a_off_800C33F4 = aRation_800DFE94;
const char *s00a_off_800C33F8 = aSocombullet_800DFE80;
const char *s00a_off_800C33FC = aFamasbullet_800DFE6C;

int PutFuncList_800C3400[4] = { 0x800C9414, 0x800C94B8, 0x800C9600, 0x800C963C };

SVECTOR s00a_dword_800C3410 = { 5, -500, 80 };

extern const char s00a_dword_800DFEB4[];
extern const char s00a_dword_800E0018[];
extern const char s00a_dword_800E011C[];
extern const char s00a_dword_800E0220[];

ANIMATION s00a_dword_800C3418 = { 0xDCD3, 1, 1, 1, 1, 500, 1, 80, 80,   0, 0, s00a_dword_800DFEB4 };
ANIMATION s00a_dword_800C3434 = { 0xFAD3, 1, 1, 1, 1, 500, 1, 80, 80,   0, 0, s00a_dword_800E0018 };
ANIMATION s00a_dword_800C3450 = { 0xFAD3, 1, 1, 1, 1, 500, 1, 80, 80,   0, 0, s00a_dword_800E011C };
ANIMATION s00a_dword_800C346C = { 0x1968, 1, 1, 1, 1,   0, 1, 70, 70, 255, 0, s00a_dword_800E0220 };

short s00a_dword_800C3488 = 0xDCD3;
short s00a_dword_800C348A = 0xFAD3;
short s00a_dword_800C348C = 0x1968;
short s00a_dword_800C348E = 0x0000;

extern const char s00a_dword_800E0288[];
extern const char s00a_dword_800E02AC[];
extern const char s00a_dword_800E054C[];
extern const char s00a_dword_800E05A8[];
extern const char s00a_dword_800E05F0[];

ANIMATION s00a_dword_800C3490 = { 0xF314, 1, 1,  1, 1, 800, 3, 600, 600, 250, 0, s00a_dword_800E0288 };
ANIMATION s00a_dword_800C34AC = { 0xCAFE, 1, 1,  1, 1,   0, 1, 200, 200, 128, 0, s00a_dword_800E02AC };
ANIMATION s00a_dword_800C34C8 = { 0x4184, 1, 1,  1, 1,   0, 5,  10,  10, 128, 0, s00a_dword_800E054C };
ANIMATION s00a_dword_800C34E4 = { 0x512D, 8, 4, 30, 1,   0, 1,  10,  10, 255, 0, s00a_dword_800E05A8 };
ANIMATION s00a_dword_800C3500 = { 0xF7BB, 1, 1,  1, 1,   0, 1,   2,   2,   0, 0, s00a_dword_800E05F0 };

short s00a_dword_800C351C[4] = { 100, 50, 25, 10 };

int s00a_dword_800C3524[32] =
{
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00002000, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000100, 0x00800000,
    0x01000000, 0x04000000, 0x08000000, 0x00000000,
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00002000, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x0000001F
};

SVECTOR ENEMY_TARGET_SIZE_800C35A4  = { 300, 1000, 300 };
SVECTOR ENEMY_TARGET_FORCE_800C35AC = { 0, 0, 0 };
SVECTOR ENEMY_ATTACK_SIZE_800C35B4  = { 800, 500, 800 };
SVECTOR ENEMY_ATTACK_FORCE_800C35BC = { 100, 0, 0 };
SVECTOR ENEMY_TOUCH_SIZE_800C35C4   = { 300, 800, 300 };
SVECTOR ENEMY_TOUCH_FORCE_800C35CC  = { 0, 0, 0, 0 };
SVECTOR COM_NO_POINT_800C35D4       = { 30000, 30000, 30000 };

int s00a_dword_800C35DC = 0x00000101;
int s00a_dword_800C35E0 = 0x000001FF;
int s00a_dword_800C35E4 = 0x000009C4;
int s00a_dword_800C35E8 = 0x00000DAC;
int s00a_dword_800C35EC = 0x00000FA0;
int s00a_dword_800C35F0 = 0x00001388;
int s00a_dword_800C35F4 = 0x0000157C;
int s00a_dword_800C35F8 = 0x000015E0;
int s00a_dword_800C35FC = 0x00001644;
int s00a_dword_800C3600 = 0x000016A8;

SVECTOR eyeflash_svec = {0, 80, 50, 0};

SVECTOR svec_800C360C[2] = {{0, 80, 80, 0}, {0, 20, 500, 0}};

RECT smoke_rect = {500, 1000, 1000, 2000};

RECT glight_rect = {40, 40, 80, 80};
SVECTOR glight_svec = {0, 65136, 60, 0};

unsigned short elevator_hash_800C3634[4] = {0xACDC, 0x085B, 0x804B, 0xDBC9};

char elevator_vib_800C363C[] = {0x00, 0x02, 0x7F, 0x02, 0x00, 0x00, 0x00, 0x00};
char elevator_vib_800C3644[] = {0x87, 0x04, 0x55, 0x01, 0x69, 0x01, 0x7D, 0x08,
                                0x5F, 0x08, 0x46, 0x0A, 0x37, 0x0C, 0x2D, 0x0E,
                                0x00, 0x00, 0x00, 0x00};
char elevator_vib_800C3658[] = {0x7F, 0x04, 0x00, 0x00};
char elevator_vib_800C365C[] = {0xA5, 0x06, 0x4B, 0x08, 0x2D, 0x0C, 0x00, 0x00};


//OPEN_MES, CLOSE_MES
unsigned short mes_list_800C3664[] = { 0x43D3, 0x4235 };
SVECTOR mouth_offset_800C3668 = { 0, 0, 100 };
RECT rect_800C3670 = { 50, 50, 100, 100 };
unsigned short mes_list_800C3678[] = { 0xD182, 0x006B };

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

const char aPadC_800DFBCC[] = "pad.c";
const short s00a_dword_800DFBD2 = 0x4E5F;
const char aBreathC_800DFBD4[] = "breath.c";
const char s00a_dword_800DFBDD = 0xC;
const char s00a_dword_800DFBDE = 0xD;
const char s00a_dword_800DFBDF = 0x0;
const char s00a_dword_800DFBE0[] = {0x0, 'I', 0x2, 0x0};
const char s00a_dword_800DFBE4[] = {0x7, 0x0, ')', 0x1};
const char s00a_dword_800DFBE8[] = {0xfe, 0xc, 0x0, 0x6};
const char s00a_dword_800DFBEC[] = {0x8, 0x6, 0x6, 0x6};
const char s00a_dword_800DFBF0[] = {0x1, 0xff, 0x2, 0x0};
const char s00a_dword_800DFBF4[] = {0x1, 0xd, 0xc, 0x0};
const char s00a_dword_800DFBF8[] = {'#', 0x8, 0xff, 0xff};
const char s00a_dword_800DFBFC[] = {0xff, '\n', 0x0, 0x8};
const char s00a_dword_800DFC00[] = {0x0, 0x8, 0x1, 0xff};
const char s00a_dword_800DFC04[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC08[] = {0xf, '\n', 0xff, '8'};
const char s00a_dword_800DFC0C[] = {0xff, '8', 0x1, 0xfe};
const char s00a_dword_800DFC10[] = {0xc, 0x0, 0x6, 0x8};
const char s00a_dword_800DFC14[] = {0x6, 0x6, 0x6, 0x1};
const char s00a_dword_800DFC18[] = {0xff, 0x2, 0x0, 0x1};
const char s00a_dword_800DFC1C[] = {0xd, 0xc, 0x0, '#'};
const char s00a_dword_800DFC20[] = {0x8, 0xff, 0xff, 0xff};
const char s00a_dword_800DFC24[] = {'\n', 0x0, 0x6, 0x0};
const char s00a_dword_800DFC28[] = {0x6, 0x1, 0xff, 0x2};
const char s00a_dword_800DFC2C[] = {0x0, 0x1, 0xd, 0xf};
const char s00a_dword_800DFC30[] = {0x0, ',', 0x1, 0x0};
const char s00a_dword_800DFC34[] = {0x5, 0x1, 0xfe, 0xc};
const char s00a_dword_800DFC38[] = {0x0, 0x3, 0x8, 0x6};
const char s00a_dword_800DFC3C[] = {0x6, 0x6, 0x1, 0xff};
const char s00a_dword_800DFC40[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC44[] = {0xc, 0x0, 0x10, 0x8};
const char s00a_dword_800DFC48[] = {0xff, 0xff, 0xff, '\n'};
const char s00a_dword_800DFC4C[] = {0x0, 0x4, 0x0, 0x4};
const char s00a_dword_800DFC50[] = {0x1, 0xff, 0x2, 0x0};
const char s00a_dword_800DFC54[] = {0x1, '\n', 0x0, 0x4};
const char s00a_dword_800DFC58[] = {0x0, 0x4, 0x1, 0xff};
const char s00a_dword_800DFC5C[] = {0x2, 0x0, 0x1, 0xd};
const char s00a_dword_800DFC60[] = {0xf, 0x0, 0x0, 0x0};
const char aSfex_800DFC64[] = "sfex0236";
const char aEmitterc_800DFC70[] = "emitter.c";
const char aErrerrerrsettimeover_800DFC7C[] = "Err Err Err  Set time Over\n";
const char aErrerrerrsetdirover_800DFC98[] = "Err Err Err  Set Dir Over\n";
const char aErrnotenoughwork_800DFCB4[] = "Err not enough work !!\n";
const char aWatcharcactionpointerr_800DFCCC[] = "watchar.c : action point Err\n";
const char aWatcherc_800DFCEC[] = "watcher.c";
