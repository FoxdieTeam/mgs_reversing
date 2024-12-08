#include "common.h"
#include "Game/camera.h"

short ActTable_800C3310[58] =
{ 
    0x10, 0x11, 0x11, 0x18, 0x10, 0x10, 0x10, 0x10,
    0x18, 0x12, 0x13, 0x1B, 0x1C, 0x1D, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x01, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x14, 0x1A, 0x19, 0x15,
    0x0A, 0x0B, 0x0C, 0x0D, 0x08, 0x16, 0x17, 0x10,
    0x04, 0x04, 0x04, 0x02, 0x17, 0x05, 0x09, 0x05,
    0x0E, 0x0F, 0x0E, 0x0F, 0x06, 0x07, 0x05, 0x09,
    0x05, 0x18
};

int s07c_dword_800C3384 = 0x00000401;
int s07c_dword_800C3388 = 0x000004FF;

SVECTOR s07c_dword_800C338C= { -150, 0, 300 };

int s07c_dword_800C3394 = 0x00000000;
int s07c_dword_800C3398 = 0x00000064;
int s07c_dword_800C339C = 0x0000FC00;
int s07c_dword_800C33A0 = 0x00000000;
int s07c_dword_800C33A4 = 0x00000000;
int s07c_dword_800C33A8 = 0x00000064;
int s07c_dword_800C33AC = 0x0000FC00;
int s07c_dword_800C33B0 = 0x00000000;
int s07c_dword_800C33B4 = 0x800CB404;
int s07c_dword_800C33B8 = 0x800CB40C;
int s07c_dword_800C33BC = 0x800CB468;
int s07c_dword_800C33C0 = 0x800CB4F0;
int s07c_dword_800C33C4 = 0x800CB414;
int s07c_dword_800C33C8 = 0xFE0C0005;
int s07c_dword_800C33CC = 0x00000050;

const SVECTOR rp_shift_800D4830  = { -200,  100, 900 };
const SVECTOR rp_shift2_800D4838 = { -200, -500, 600 };
const SVECTOR force_800D4840     = { 5, 0, 100 };
const SVECTOR size_800D4848      = { 400, 200, 400 };
const char s07c_aNokezoriend_800D4850[] = " nokezori end!!\n";
const char s07c_dword_800D4864[] = {0x0, 0x0, 0x0, 0x0};
const int s07c_dword_800D4868 = 0x800CA5CC;
const int s07c_dword_800D486C = 0x800CA638;
const int s07c_dword_800D4870 = 0x800CA870;
const int s07c_dword_800D4874 = 0x800CA790;
const int s07c_dword_800D4878 = 0x800CA734;
const int s07c_dword_800D487C = 0x800CA7EC;
const int s07c_dword_800D4880 = 0x800CA844;
const char s07c_dword_800D4884[] = {0x0, 0x0, 0x0, 0x0};
const int s07c_dword_800D4888 = 0x800CA930;
const int s07c_dword_800D488C = 0x800CA910;
const int s07c_dword_800D4890 = 0x800CA958;
const int s07c_dword_800D4894 = 0x800CA930;
const int s07c_dword_800D4898 = 0x800CA930;
const int s07c_dword_800D489C = 0x800CA958;
const char s07c_dword_800D48A0[] = {'n', 'o', 'i', 's'};
const char s07c_dword_800D48A4[] = {'e', ' ', 'd', 'i'};
const char s07c_dword_800D48A8[] = {'s', ' ', ' ', '='};
const char s07c_dword_800D48AC[] = {'%', 'd', ',', '\n'};
const char s07c_dword_800D48B0[] = {0x0, 0x0, 0xb2, 0xaf};

int SECTION("overlay.bss") s07c_dword_800D5274;
GM_Camera SECTION("overlay.bss") meryl72_camera_800D5278;
int SECTION("overlay.bss") s07c_dword_800D52F4;
SVECTOR SECTION("overlay.bss") meryl72_800D52F8;
int SECTION("overlay.bss") meryl72_800D5300;
int SECTION("overlay.bss") s07c_dword_800D5304;
