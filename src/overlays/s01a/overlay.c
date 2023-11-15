#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "Anime/animeconv/anime.h"

GCL_ActorTableEntry s01aOverlayCharas[] =
{
    { 0xAEFB, (TGCL_ActorCreateFn)0x800C4BC8 },
    { 0x0FAD, (TGCL_ActorCreateFn)0x800C51B0 },
    { 0xB4E6, (TGCL_ActorCreateFn)0x800C3FFC },
    { 0x7BC2, (TGCL_ActorCreateFn)0x800E319C },
    { 0xFED1, (TGCL_ActorCreateFn)0x8005D508 },
    { 0x5A50, (TGCL_ActorCreateFn)0x800DF8D8 },
    { 0x4170, (TGCL_ActorCreateFn)0x800C4E4C },
    { 0x3F9A, (TGCL_ActorCreateFn)0x800E2658 },
    { 0x51C6, (TGCL_ActorCreateFn)0x800E3578 },
    { 0xE97E, (TGCL_ActorCreateFn)0x800DCD78 },
    { 0xCB3A, (TGCL_ActorCreateFn)0x800E1DB0 },
    { 0xB103, (TGCL_ActorCreateFn)0x800E1A00 },
    { 0x02C4, (TGCL_ActorCreateFn)0x800D45D0 },
    { 0x92BC, (TGCL_ActorCreateFn)0x800DBAAC },
    { 0x6E90, (TGCL_ActorCreateFn)0x800D67F8 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800E17D0 },
    { 0x3ED7, (TGCL_ActorCreateFn)0x800E0B20 },
    { 0xC6D7, (TGCL_ActorCreateFn)0x800D3468 },
    { 0x6E9A, (TGCL_ActorCreateFn)0x800C7B94 },
    { 0x73EA, (TGCL_ActorCreateFn)0x800C69C0 },
    { 0x170C, (TGCL_ActorCreateFn)0x800DAE90 },
    { 0x8185, (TGCL_ActorCreateFn)0x800DECD8 },
    { 0x4811, (TGCL_ActorCreateFn)0x800DA3A4 },
    { 0xF50F, (TGCL_ActorCreateFn)0x800D92BC },
    { 0x18E3, (TGCL_ActorCreateFn)0x800C6058 },
    { 0xEC77, (TGCL_ActorCreateFn)0x800DB3BC },
    { 0xA12E, (TGCL_ActorCreateFn)0x800E0FF4 },
    { 0, 0 }
};

short tobcnt_lines[] = {
    166, // table length
    19,  93,  39,  93,  19,  93,  18,  98,  39,  93,  38,  98,  31,  98,  38,  98,
    31,  98,  25,  129, 25,  129, 19,  129, 42,  93,  60,  93,  42,  93,  41,  98,
    60,  93,  59,  98,  41,  98,  59,  98,  40,  102, 37,  117, 37,  117, 55,  117,
    55,  117, 58,  102, 40,  102, 46,  102, 52,  102, 58,  102, 44,  112, 46,  102,
    44,  112, 50,  112, 52,  102, 50,  112, 18,  98,  25,  98,  25,  98,  19,  129,
    68,  98,  69,  93,  69,  93,  85,  93,  68,  98,  80,  98,  77,  102, 67,  102,
    67,  102, 64,  117, 64,  117, 79,  117, 79,  117, 84,  113, 85,  109, 82,  105,
    87,  98,  85,  93,  87,  98,  82,  105, 80,  98,  77,  102, 71,  112, 76,  112,
    76,  112, 79,  110, 71,  112, 72,  107, 72,  107, 77,  107, 79,  110, 77,  107,
    85,  109, 84,  113, 86,  117, 102, 117, 91,  93,  107, 93,  90,  98,  106, 98,
    89,  102, 105, 102, 89,  102, 86,  117, 91,  93,  90,  98,  107, 93,  106, 98,
    104, 107, 94,  107, 105, 102, 104, 107, 93,  112, 103, 112, 103, 112, 102, 117,
    93,  112, 94,  107, 122, 93,  135, 93,  122, 93,  112, 105, 130, 117, 116, 117,
    125, 98,  134, 98,  135, 93,  134, 98,  125, 98,  119, 105, 119, 105, 121, 112,
    121, 112, 131, 112, 131, 112, 130, 117, 112, 105, 116, 117, 157, 93,  139, 93,
    134, 117, 152, 117, 138, 98,  156, 98,  143, 102, 141, 112, 141, 112, 147, 112,
    149, 102, 147, 112, 137, 102, 143, 102, 149, 102, 155, 102, 139, 93,  138, 98,
    137, 102, 134, 117, 155, 102, 152, 117, 157, 93,  156, 98,  161, 93,  160, 98,
    161, 93,  167, 93,  170, 102, 172, 106, 174, 98,  175, 93,  175, 93,  181, 93,
    179, 102, 176, 117, 156, 117, 162, 117, 162, 117, 165, 103, 165, 103, 171, 117,
    171, 117, 176, 117, 160, 98,  169, 98,  167, 93,  169, 98,  159, 102, 170, 102,
    159, 102, 156, 117, 174, 98,  180, 98,  173, 102, 172, 106, 173, 102, 179, 102,
    180, 98,  181, 93,  184, 93,  183, 98,  204, 93,  184, 93,  204, 93,  203, 98,
    203, 98,  183, 98,  189, 102, 186, 117, 195, 102, 192, 117, 186, 117, 192, 117,
    189, 102, 195, 102, 205, 102, 202, 117, 207, 93,  213, 93,  211, 102, 208, 117,
    202, 117, 208, 117, 206, 98,  212, 98,  205, 102, 211, 102, 207, 93,  206, 98,
    213, 93,  212, 98,  215, 102, 212, 117, 212, 117, 218, 117, 218, 117, 221, 103,
    217, 93,  223, 93,  223, 93,  225, 98,  225, 98,  216, 98,  215, 102, 226, 102,
    226, 102, 228, 106, 221, 103, 227, 117, 227, 117, 232, 117, 228, 106, 229, 102,
    229, 102, 235, 102, 235, 102, 232, 117, 217, 93,  216, 98,  230, 98,  236, 98,
    230, 98,  231, 93,  236, 98,  237, 93,  231, 93,  237, 93,  239, 102, 236, 117,
    241, 93,  247, 93,  236, 117, 254, 117, 254, 117, 257, 102, 243, 112, 249, 112,
    243, 112, 245, 102, 249, 112, 251, 102, 240, 98,  246, 98,  252, 98,  258, 98,
    239, 102, 245, 102, 251, 102, 257, 102, 253, 93,  259, 93,  241, 93,  240, 98,
    247, 93,  246, 98,  253, 93,  252, 98,  259, 93,  258, 98,  258, 117, 274, 117,
    258, 117, 261, 102, 263, 93,  279, 93,  277, 102, 276, 107, 262, 98,  278, 98,
    261, 102, 277, 102, 263, 93,  262, 98,  279, 93,  278, 98,  266, 107, 276, 107,
    275, 112, 265, 112, 266, 107, 265, 112, 275, 112, 274, 117, 281, 102, 278, 117,
    283, 93,  298, 93,  298, 93,  302, 104, 302, 104, 293, 117, 293, 117, 278, 117,
    282, 98,  293, 98,  293, 98,  295, 104, 295, 104, 289, 112, 289, 112, 285, 112,
    285, 112, 287, 102, 281, 102, 287, 102, 283, 93,  282, 98,  30,  120, 28,  129,
    30,  120, 291, 120, 28,  129, 285, 129
};

short s01a_dword_800C381A = 0x800C;

extern const char s01a_dword_800E3668[];
extern const char s01a_dword_800E36B8[];

ANIMATION anm_breath_800C32E8  = { PCX_SMOKE, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (char *)s01a_dword_800E3668 };
ANIMATION anm_unknown_800C3304 = { PCX_SMOKE, 8, 4, 30, 1, 300, 1, 500, 500, 0, 0, (char *)s01a_dword_800E36B8 };

SVECTOR snow_svec_800C3854 = {-5000, 0, -10000, 0};
SVECTOR snow_svec_800C385C = {5000, 8000, 10000, 0};
SVECTOR snow_svec_800C3864 = {0, -50, 0, 0};
RECT    snow_rect_800C386C = {0, 0, 2, 2};

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

int s01a_dword_800C3910 = 0x0000FF6A;
int s01a_dword_800C3914 = 0x0000012C;
int s01a_dword_800C3918 = 0xFDDA0000;
int s01a_dword_800C391C = 0x000003B6;
int s01a_dword_800C3920 = 0x00000000;
int s01a_dword_800C3924 = 0x00000064;
int s01a_dword_800C3928 = 0x0000FC00;
int s01a_dword_800C392C = 0x00000000;
int s01a_dword_800C3930 = 0x00000000;
int s01a_dword_800C3934 = 0x00000064;
int s01a_dword_800C3938 = 0x0000FC00;
int s01a_dword_800C393C = 0x00000000;
int s01a_dword_800C3940 = 0x800E3954;
int s01a_dword_800C3944 = 0x800E3940;
int s01a_dword_800C3948 = 0x800E392C;
int s01a_dword_800C394C = 0x800CBF74;
int s01a_dword_800C3950 = 0x800CC018;
int s01a_dword_800C3954 = 0x800CC160;
int s01a_dword_800C3958 = 0x800CC19C;
int s01a_dword_800C395C = 0xFE0C0005;
int s01a_dword_800C3960 = 0x00000050;
int s01a_dword_800C3964 = 0x0001DCD3;
int s01a_dword_800C3968 = 0x00010001;
int s01a_dword_800C396C = 0x01F40001;
int s01a_dword_800C3970 = 0x00500001;
int s01a_dword_800C3974 = 0x00000050;
int s01a_dword_800C3978 = 0x00000000;
int s01a_dword_800C397C = 0x800E3974;
int s01a_dword_800C3980 = 0x0001FAD3;
int s01a_dword_800C3984 = 0x00010001;
int s01a_dword_800C3988 = 0x01F40001;
int s01a_dword_800C398C = 0x00500001;
int s01a_dword_800C3990 = 0x00000050;
int s01a_dword_800C3994 = 0x00000000;
int s01a_dword_800C3998 = 0x800E3AD8;
int s01a_dword_800C399C = 0x0001FAD3;
int s01a_dword_800C39A0 = 0x00010001;
int s01a_dword_800C39A4 = 0x01F40001;
int s01a_dword_800C39A8 = 0x00500001;
int s01a_dword_800C39AC = 0x00000050;
int s01a_dword_800C39B0 = 0x00000000;
int s01a_dword_800C39B4 = 0x800E3BDC;
int s01a_dword_800C39B8 = 0x00011968;
int s01a_dword_800C39BC = 0x00010001;
int s01a_dword_800C39C0 = 0x00000001;
int s01a_dword_800C39C4 = 0x00460001;
int s01a_dword_800C39C8 = 0x00FF0046;
int s01a_dword_800C39CC = 0x00000000;
int s01a_dword_800C39D0 = 0x800E3CE0;
int s01a_dword_800C39D4 = 0xFAD3DCD3;
int s01a_dword_800C39D8 = 0x00001968;
int s01a_dword_800C39DC = 0x0001F314;
int s01a_dword_800C39E0 = 0x00010001;
int s01a_dword_800C39E4 = 0x03200001;
int s01a_dword_800C39E8 = 0x02580003;
int s01a_dword_800C39EC = 0x00FA0258;
int s01a_dword_800C39F0 = 0x00000000;
int s01a_dword_800C39F4 = 0x800E3D48;
int s01a_dword_800C39F8 = 0x0001CAFE;
int s01a_dword_800C39FC = 0x00010001;
int s01a_dword_800C3A00 = 0x00000001;
int s01a_dword_800C3A04 = 0x00C80001;
int s01a_dword_800C3A08 = 0x008000C8;
int s01a_dword_800C3A0C = 0x00000000;
int s01a_dword_800C3A10 = 0x800E3D6C;
int s01a_dword_800C3A14 = 0x00014184;
int s01a_dword_800C3A18 = 0x00010001;
int s01a_dword_800C3A1C = 0x00000001;
int s01a_dword_800C3A20 = 0x000A0005;
int s01a_dword_800C3A24 = 0x0080000A;
int s01a_dword_800C3A28 = 0x00000000;
int s01a_dword_800C3A2C = 0x800E400C;
int s01a_dword_800C3A30 = 0x0008512D;
int s01a_dword_800C3A34 = 0x001E0004;
int s01a_dword_800C3A38 = 0x00000001;
int s01a_dword_800C3A3C = 0x000A0001;
int s01a_dword_800C3A40 = 0x00FF000A;
int s01a_dword_800C3A44 = 0x00000000;
int s01a_dword_800C3A48 = 0x800E4068;
int s01a_dword_800C3A4C = 0x0001F7BB;
int s01a_dword_800C3A50 = 0x00010001;
int s01a_dword_800C3A54 = 0x00000001;
int s01a_dword_800C3A58 = 0x00020001;
int s01a_dword_800C3A5C = 0x00000002;
int s01a_dword_800C3A60 = 0x00000000;
int s01a_dword_800C3A64 = 0x800E40B0;
int s01a_dword_800C3A68 = 0x00320064;
int s01a_dword_800C3A6C = 0x000A0019;
int s01a_dword_800C3A70 = 0x00000000;
int s01a_dword_800C3A74 = 0x00000001;
int s01a_dword_800C3A78 = 0x00000002;
int s01a_dword_800C3A7C = 0x00000004;
int s01a_dword_800C3A80 = 0x00002000;
int s01a_dword_800C3A84 = 0x00000040;
int s01a_dword_800C3A88 = 0x00000080;
int s01a_dword_800C3A8C = 0x00000200;
int s01a_dword_800C3A90 = 0x00000400;
int s01a_dword_800C3A94 = 0x00000800;
int s01a_dword_800C3A98 = 0x00000100;
int s01a_dword_800C3A9C = 0x00800000;
int s01a_dword_800C3AA0 = 0x01000000;
int s01a_dword_800C3AA4 = 0x04000000;
int s01a_dword_800C3AA8 = 0x08000000;
int s01a_dword_800C3AAC = 0x00000000;
int s01a_dword_800C3AB0 = 0x00000000;
int s01a_dword_800C3AB4 = 0x00000001;
int s01a_dword_800C3AB8 = 0x00000002;
int s01a_dword_800C3ABC = 0x00000004;
int s01a_dword_800C3AC0 = 0x00002000;
int s01a_dword_800C3AC4 = 0x00000040;
int s01a_dword_800C3AC8 = 0x00000080;
int s01a_dword_800C3ACC = 0x00000200;
int s01a_dword_800C3AD0 = 0x00000400;
int s01a_dword_800C3AD4 = 0x00000800;
int s01a_dword_800C3AD8 = 0x00000000;
int s01a_dword_800C3ADC = 0x00000000;
int s01a_dword_800C3AE0 = 0x00000000;
int s01a_dword_800C3AE4 = 0x00000000;
int s01a_dword_800C3AE8 = 0x00000000;
int s01a_dword_800C3AEC = 0x0000001F;

SVECTOR ENEMY_TARGET_SIZE_800C35A4  = { 300, 1000, 300 };
SVECTOR ENEMY_TARGET_FORCE_800C35AC = { 0, 0, 0 };
SVECTOR ENEMY_ATTACK_SIZE_800C35B4  = { 800, 500, 800 };
SVECTOR ENEMY_ATTACK_FORCE_800C35BC = { 100, 0, 0 };
SVECTOR ENEMY_TOUCH_SIZE_800C35C4   = { 300, 800, 300 };
SVECTOR ENEMY_TOUCH_FORCE_800C35CC  = { 0, 0, 0, 0 };
SVECTOR COM_NO_POINT_800C35D4       = { 30000, 30000, 30000 };

int s01a_dword_800C3B28 = 0x00000101;
int s01a_dword_800C3B2C = 0x000001FF;
int s01a_dword_800C3B30 = 0x000009C4;
int s01a_dword_800C3B34 = 0x00000DAC;
int s01a_dword_800C3B38 = 0x00000FA0;
int s01a_dword_800C3B3C = 0x00001388;
int s01a_dword_800C3B40 = 0x0000157C;
int s01a_dword_800C3B44 = 0x000015E0;
int s01a_dword_800C3B48 = 0x00001644;
int s01a_dword_800C3B4C = 0x000016A8;

// Enemy/eyeflash.c
SVECTOR eyeflash_svec = {0, 80, 50, 0};

// Enemy/grnad_e.c
SVECTOR svec_800C360C[2] = {{0, 80, 80, 0}, {0, 20, 500, 0}};

// Enemy/camera.c
RECT camera_rect_800C3B68 = {120, 120, 240, 240};
SVECTOR camera_svec1_800C3B70 = {300, 300, 300, 0};

extern const char anim_data_800E44D8[];
ANIMATION anm_800C3B78 = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 800, 800, 128, NULL, (char *)anim_data_800E44D8};

extern const char anim_data_800E4500[];
ANIMATION anm_800C3B94 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800E4500};

extern const char anim_data_800E4518[];
ANIMATION anm_800C3BB0 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800E4518};

extern const char anim_data_800E4580[];
ANIMATION anm_800C3BCC = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 0, NULL, (char *)anim_data_800E4580};

extern const char anim_data_800E45F8[];
ANIMATION anm_800C3BE8 = {PCX_SMOKE, 8, 4, 30, 1, 500, 2, 400, 400, 32, NULL, (char *)anim_data_800E45F8};

extern const char anim_data_800E46F8[];
ANIMATION anm_800C3C04 = {0x479F, 1, 1, 1, 1, 230, 1, 300, 300, 255, NULL, (char *)anim_data_800E46F8};

extern const char anim_data_800E4724[];
ANIMATION anm_800C3C20 = {0x479F, 1, 1, 1, 1, 230, 1, 1000, 1000, 32, NULL, (char *)anim_data_800E4724};

extern const char anim_data_800E473C[];
ANIMATION anm_800C3C3C = {0x479F, 1, 1, 1, 1, 500, 1, 200, 200, 255, NULL, (char *)anim_data_800E473C};

extern const char anim_data_800E474C[];
ANIMATION anm_800C3C58 = {0x479F, 1, 1, 1, 1, 500, 1, 2000, 2000, 64, NULL, (char *)anim_data_800E474C};

extern const char anim_data_800E4760[];
ANIMATION anm_800C3C74 = {0x479F, 1, 1, 1, 1, 0, 0, 20, 20, 255, NULL, (char *)anim_data_800E4760};

int s01a_dword_800C3C90 = 0x0001A9CD;
int s01a_dword_800C3C94 = 0x00010001;
int s01a_dword_800C3C98 = 0x00E60001;
int s01a_dword_800C3C9C = 0x00000001;
int s01a_dword_800C3CA0 = 0x00FF0000;
int s01a_dword_800C3CA4 = 0x00000000;
int s01a_dword_800C3CA8 = 0x800E476C;

SVECTOR object_svec1_800C3CAC = {1000, 2000, 1500, 0};
SVECTOR object_svec2_800C3CB4 = {1500, 2000, 1500, 0};

RECT smoke_rect = {500, 1000, 1000, 2000};

RECT glight_rect = {40, 40, 80, 80};
SVECTOR glight_svec = {0, 65136, 60, 0};

short s01a_word_800C3CD4[8] = {31000, 15, 30, 60, 90, 32000, 32001, 30000};

int s01a_dword_800C3CE4 = 0x00010000;
int s01a_dword_800C3CE8 = 0x00030002;
int s01a_dword_800C3CEC = 0x00050004;
int s01a_dword_800C3CF0 = 0x00070006;
int s01a_dword_800C3CF4 = 0x00090008;
int s01a_dword_800C3CF8 = 0x000B000A;
int s01a_dword_800C3CFC = 0x000D000C;
int s01a_dword_800C3D00 = 0xB300000E;

int s01a_dword_800C3D04 = 0x00000000;
int s01a_dword_800C3D08 = 0x00000001;
int s01a_dword_800C3D0C = 0x00000002;
int s01a_dword_800C3D10 = 0x00000004;
int s01a_dword_800C3D14 = 0x00000008;
int s01a_dword_800C3D18 = 0x00000010;
int s01a_dword_800C3D1C = 0x00000020;
int s01a_dword_800C3D20 = 0x00000040;
int s01a_dword_800C3D24 = 0x00000080;
int s01a_dword_800C3D28 = 0x00000100;
int s01a_dword_800C3D2C = 0x00000200;
int s01a_dword_800C3D30 = 0x00000400;
int s01a_dword_800C3D34 = 0x00000800;
int s01a_dword_800C3D38 = 0x00001000;

int s01a_dword_800C3D3C = 0x00000000;
int s01a_dword_800C3D40 = 0x0000000F;
int s01a_dword_800C3D44 = 0x00000000;
int s01a_dword_800C3D48 = 0x00000000;
int s01a_dword_800C3D4C = 0x00000000;
int s01a_dword_800C3D50 = 0x00000000;
int s01a_dword_800C3D54 = 0x00000000;
int s01a_dword_800C3D58 = 0x00000000;
int s01a_dword_800C3D5C = 0x00000000;
int s01a_dword_800C3D60 = 0x00000000;
int s01a_dword_800C3D64 = 0x00000000;
int s01a_dword_800C3D68 = 0x00000000;
int s01a_dword_800C3D6C = 0x00000000;
int s01a_dword_800C3D70 = 0x00000000;
int s01a_dword_800C3D74 = 0x00000000;
int s01a_dword_800C3D78 = 0x0000001D;
int s01a_dword_800C3D7C = 0x0000001E;
int s01a_dword_800C3D80 = 0x0000001F;

RECT blink_tx_rect = {1000, 1000, 2000, 2000};

const char aCancelC[] = {'c', 'a', 'n', 'c', 'e', 'l', '.', 'c', 0x0, 'D', 'G', '_'};

const char aTobcntTitle[] = "title";
const char aTobcntC[] = {'t', 'o', 'b', 'c', 'n', 't', '.', 'c', 0x0, 0x11, 'R', 'e'};

const char aBreathC[] = {'b', 'r', 'e', 'a', 't', 'h', '.', 'c', 0x0, 'v', 'i', 's'};

const char s01a_dword_800E3668[] = {0x0, 'I', 0x2, 0x0};
const char s01a_dword_800E366C[] = {0x7, 0x0, ')', 0x1};
const char s01a_dword_800E3670[] = {0xfe, 0xc, 0x0, 0x6};
const char s01a_dword_800E3674[] = {0x8, 0x6, 0x6, 0x6};
const char s01a_dword_800E3678[] = {0x1, 0xff, 0x2, 0x0};
const char s01a_dword_800E367C[] = {0x1, 0xd, 0xc, 0x0};
const char s01a_dword_800E3680[] = {'#', 0x8, 0xff, 0xff};
const char s01a_dword_800E3684[] = {0xff, '\n', 0x0, 0x8};
const char s01a_dword_800E3688[] = {0x0, 0x8, 0x1, 0xff};
const char s01a_dword_800E368C[] = {0x2, 0x0, 0x1, 0xd};
const char s01a_dword_800E3690[] = {0xf, '\n', 0xff, '8'};
const char s01a_dword_800E3694[] = {0xff, '8', 0x1, 0xfe};
const char s01a_dword_800E3698[] = {0xc, 0x0, 0x6, 0x8};
const char s01a_dword_800E369C[] = {0x6, 0x6, 0x6, 0x1};
const char s01a_dword_800E36A0[] = {0xff, 0x2, 0x0, 0x1};
const char s01a_dword_800E36A4[] = {0xd, 0xc, 0x0, '#'};
const char s01a_dword_800E36A8[] = {0x8, 0xff, 0xff, 0xff};
const char s01a_dword_800E36AC[] = {'\n', 0x0, 0x6, 0x0};
const char s01a_dword_800E36B0[] = {0x6, 0x1, 0xff, 0x2};
const char s01a_dword_800E36B4[] = {0x0, 0x1, 0xd, 0xf};

const char s01a_dword_800E36B8[] = {0x0, ',', 0x1, 0x0};
const char s01a_dword_800E36BC[] = {0x5, 0x1, 0xfe, 0xc};
const char s01a_dword_800E36C0[] = {0x0, 0x3, 0x8, 0x6};
const char s01a_dword_800E36C4[] = {0x6, 0x6, 0x1, 0xff};
const char s01a_dword_800E36C8[] = {0x2, 0x0, 0x1, 0xd};
const char s01a_dword_800E36CC[] = {0xc, 0x0, 0x10, 0x8};
const char s01a_dword_800E36D0[] = {0xff, 0xff, 0xff, '\n'};
const char s01a_dword_800E36D4[] = {0x0, 0x4, 0x0, 0x4};
const char s01a_dword_800E36D8[] = {0x1, 0xff, 0x2, 0x0};
const char s01a_dword_800E36DC[] = {0x1, '\n', 0x0, 0x4};
const char s01a_dword_800E36E0[] = {0x0, 0x4, 0x1, 0xff};
const char s01a_dword_800E36E4[] = {0x2, 0x0, 0x1, 0xd};
const char s01a_dword_800E36E8[] = {0xf, 'k', 's', 'R'};

const char aMotseC[] = "motse.c";
