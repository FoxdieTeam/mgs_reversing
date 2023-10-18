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

ANIMATION anm_breath_800C32E8  = { 20781, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (const char*)0x800DFBE0 };
ANIMATION anm_unknown_800C3304 = { 20781, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (const char*)0x800DFC30 };
RECT rect_800C3320 = { 1000, 1000, 2000, 2000 };
int s00a_dword_800C3328[8] = { 2500, 3500, 4000, 5000, 5500, 5600, 5700, 5800 };
unsigned short s00a_dword_800C3348[8] = { 450, 15, 30, 60, 90, 0, 32001, 30000 };

short ActTable_800C3358[54] =
{
    0x13,
    0x14,
    0x0A,
    0x16,
    0x09,
    0x22,
    0x23,
    0x24,
    0x2D,
    0x0D,
    0x0C,
    0x1A,
    0x0F,
    0x0E,
    0x10,
    0x1B,
    0x08,
    0x2E,
    0x32,
    0x15,
    0x1E,
    0x1F,
    0x20,
    0x21,
    0x25,
    0x34,
    0x35,
    0x19,
    0x05,
    0x02,
    0x2A,
    0x04,
    0x27,
    0x28,
    0x06,
    0x07,
    0x26,
    0x03,
    0x29,
    0x11,
    0x12,
    0x2B,
    0x17,
    0x18,
    0x1C,
    0x1D,
    0x00,
    0x01,
    0x33,
    0x11,
    0x12,
    0x2B,
    0x16,
    0x0B
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


int s00a_dword_800C3418 = 0x0001DCD3;
int s00a_dword_800C341C = 0x00010001;
int s00a_dword_800C3420 = 0x01F40001;
int s00a_dword_800C3424 = 0x00500001;
int s00a_dword_800C3428 = 0x00000050;
int s00a_dword_800C342C = 0x00000000;
int s00a_dword_800C3430 = 0x800DFEB4;

int s00a_dword_800C3434 = 0x0001FAD3;
int s00a_dword_800C3438 = 0x00010001;
int s00a_dword_800C343C = 0x01F40001;
int s00a_dword_800C3440 = 0x00500001;
int s00a_dword_800C3444 = 0x00000050;
int s00a_dword_800C3448 = 0x00000000;
int s00a_dword_800C344C = 0x800E0018;

int s00a_dword_800C3450 = 0x0001FAD3;
int s00a_dword_800C3454 = 0x00010001;
int s00a_dword_800C3458 = 0x01F40001;
int s00a_dword_800C345C = 0x00500001;
int s00a_dword_800C3460 = 0x00000050;
int s00a_dword_800C3464 = 0x00000000;
int s00a_dword_800C3468 = 0x800E011C;
int s00a_dword_800C346C = 0x00011968;
int s00a_dword_800C3470 = 0x00010001;
int s00a_dword_800C3474 = 0x00000001;
int s00a_dword_800C3478 = 0x00460001;
int s00a_dword_800C347C = 0x00FF0046;
int s00a_dword_800C3480 = 0x00000000;
int s00a_dword_800C3484 = 0x800E0220;

short s00a_dword_800C3488 = 0xDCD3;
short s00a_dword_800C348A = 0xFAD3;

int s00a_dword_800C348C = 0x00001968;
int s00a_dword_800C3490 = 0x0001F314;
int s00a_dword_800C3494 = 0x00010001;
int s00a_dword_800C3498 = 0x03200001;
int s00a_dword_800C349C = 0x02580003;
int s00a_dword_800C34A0 = 0x00FA0258;
int s00a_dword_800C34A4 = 0x00000000;
int s00a_dword_800C34A8 = 0x800E0288;
int s00a_dword_800C34AC = 0x0001CAFE;
int s00a_dword_800C34B0 = 0x00010001;
int s00a_dword_800C34B4 = 0x00000001;
int s00a_dword_800C34B8 = 0x00C80001;
int s00a_dword_800C34BC = 0x008000C8;
int s00a_dword_800C34C0 = 0x00000000;
int s00a_dword_800C34C4 = 0x800E02AC;
int s00a_dword_800C34C8 = 0x00014184;
int s00a_dword_800C34CC = 0x00010001;
int s00a_dword_800C34D0 = 0x00000001;
int s00a_dword_800C34D4 = 0x000A0005;
int s00a_dword_800C34D8 = 0x0080000A;
int s00a_dword_800C34DC = 0x00000000;
int s00a_dword_800C34E0 = 0x800E054C;
int s00a_dword_800C34E4 = 0x0008512D;
int s00a_dword_800C34E8 = 0x001E0004;
int s00a_dword_800C34EC = 0x00000001;
int s00a_dword_800C34F0 = 0x000A0001;
int s00a_dword_800C34F4 = 0x00FF000A;
int s00a_dword_800C34F8 = 0x00000000;
int s00a_dword_800C34FC = 0x800E05A8;
int s00a_dword_800C3500 = 0x0001F7BB;
int s00a_dword_800C3504 = 0x00010001;
int s00a_dword_800C3508 = 0x00000001;
int s00a_dword_800C350C = 0x00020001;
int s00a_dword_800C3510 = 0x00000002;
int s00a_dword_800C3514 = 0x00000000;
int s00a_dword_800C3518 = 0x800E05F0;
int s00a_dword_800C351C = 0x00320064;
int s00a_dword_800C3520 = 0x000A0019;
int s00a_dword_800C3524 = 0x00000000;
int s00a_dword_800C3528 = 0x00000001;
int s00a_dword_800C352C = 0x00000002;
int s00a_dword_800C3530 = 0x00000004;
int s00a_dword_800C3534 = 0x00002000;
int s00a_dword_800C3538 = 0x00000040;
int s00a_dword_800C353C = 0x00000080;
int s00a_dword_800C3540 = 0x00000200;
int s00a_dword_800C3544 = 0x00000400;
int s00a_dword_800C3548 = 0x00000800;
int s00a_dword_800C354C = 0x00000100;
int s00a_dword_800C3550 = 0x00800000;
int s00a_dword_800C3554 = 0x01000000;
int s00a_dword_800C3558 = 0x04000000;
int s00a_dword_800C355C = 0x08000000;
int s00a_dword_800C3560 = 0x00000000;
int s00a_dword_800C3564 = 0x00000000;
int s00a_dword_800C3568 = 0x00000001;
int s00a_dword_800C356C = 0x00000002;
int s00a_dword_800C3570 = 0x00000004;
int s00a_dword_800C3574 = 0x00002000;
int s00a_dword_800C3578 = 0x00000040;
int s00a_dword_800C357C = 0x00000080;
int s00a_dword_800C3580 = 0x00000200;
int s00a_dword_800C3584 = 0x00000400;
int s00a_dword_800C3588 = 0x00000800;
int s00a_dword_800C358C = 0x00000000;
int s00a_dword_800C3590 = 0x00000000;
int s00a_dword_800C3594 = 0x00000000;
int s00a_dword_800C3598 = 0x00000000;
int s00a_dword_800C359C = 0x00000000;
int s00a_dword_800C35A0 = 0x0000001F;


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
int s00a_dword_800C3604 = 0x00500000;
int s00a_dword_800C3608 = 0x00000032;
int s00a_dword_800C360C = 0x00500000;
int s00a_dword_800C3610 = 0x00000050;
int s00a_dword_800C3614 = 0x00140000;
int s00a_dword_800C3618 = 0x000001F4;
int s00a_dword_800C361C = 0x03E801F4;
int s00a_dword_800C3620 = 0x07D003E8;
int s00a_dword_800C3624 = 0x00280028;
int s00a_dword_800C3628 = 0x00500050;
int s00a_dword_800C362C = 0xFE700000;
int s00a_dword_800C3630 = 0x0000003C;
int s00a_dword_800C3634 = 0x085BACDC;
int s00a_dword_800C3638 = 0xDBC9804B;
int s00a_dword_800C363C = 0x027F0200;
int s00a_dword_800C3640 = 0x00000000;
int s00a_dword_800C3644 = 0x01550487;
int s00a_dword_800C3648 = 0x087D0169;
int s00a_dword_800C364C = 0x0A46085F;
int s00a_dword_800C3650 = 0x0E2D0C37;
int s00a_dword_800C3654 = 0x00000000;
int s00a_dword_800C3658 = 0x0000047F;
int s00a_dword_800C365C = 0x084B06A5;
int s00a_dword_800C3660 = 0x00000C2D;

//OPEN_MES, CLOSE_MES
unsigned short mes_list_800C3664[] = { 0x43D3, 0x4235 };
SVECTOR mouth_offset_800C3668 = { 0, 0, 100 };
RECT rect_800C3670 = { 50, 50, 100, 100 };
unsigned short mes_list_800C3678[] = { 0xD182, 0x006B };

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

const char s00a_dword_800DFB9C[] = {0x2, 0x0, 0x2, '$'};
const char s00a_dword_800DFBA0[] = {0x3, 0x0, 0x82, 0xa0};
const char s00a_dword_800DFBA4[] = {0x2, 0x0, 0xa0, 0x10};
const char s00a_dword_800DFBA8[] = {0x0, 0xe6, 0x3, '<'};
const char s00a_dword_800DFBAC[] = {0x2, 0x0, 'c', '4'};
const char s00a_dword_800DFBB0[] = {'+', 0x10, 0x6, 0x0};
const char s00a_dword_800DFBB4[] = {'%', 0x10, 'b', 0x0};
const char s00a_dword_800DFBB8[] = {0x4, 0x0, 0x82, 0xac};
const char s00a_dword_800DFBBC[] = {0x8, 0x0, 0xe0, 0x3};
const char s00a_dword_800DFBC0[] = {0x8, 0x0, 0x80, 0xac};
const char s00a_dword_800DFBC4[] = {0x0, 0x0, 0x0, 0x0};
const char s00a_dword_800DFBC8[] = {0x0, 0x0, 0x0, 0x0};

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
