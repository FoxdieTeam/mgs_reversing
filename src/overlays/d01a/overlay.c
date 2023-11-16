#include "libgcl/libgcl.h"

GCL_ActorTableEntry d01aOverlayCharas[] = 
{
    { 0x30CE, (TGCL_ActorCreateFn)0x800CCA94 },
    { 0x73EA, (TGCL_ActorCreateFn)0x800C506C },
    { 0x170C, (TGCL_ActorCreateFn)0x800CA6C4 },
    { 0x32E5, (TGCL_ActorCreateFn)0x800C46F4 },
    { 0x4811, (TGCL_ActorCreateFn)0x800CA0D0 },
    { 0xF50F, (TGCL_ActorCreateFn)0x800C7090 },
    { 0x18E3, (TGCL_ActorCreateFn)0x800C4424 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800CE9C8 },
    { 0x0003, (TGCL_ActorCreateFn)0x800CDA74 },
    { 0x0004, (TGCL_ActorCreateFn)0x800CDA74 },
    { 0x000E, (TGCL_ActorCreateFn)0x800C34A0 },
    { 0x000F, (TGCL_ActorCreateFn)0x800CAD98 },
    { 0x001E, (TGCL_ActorCreateFn)0x800CF6BC },
    { 0x0021, (TGCL_ActorCreateFn)0x800CEFF8 },
    { 0x0025, (TGCL_ActorCreateFn)0x800CD530 },
    { 0x0045, (TGCL_ActorCreateFn)0x800D06F0 },
    { 0, 0 }
};

int d01a_dword_800C3290 = 0x0008512D;
int d01a_dword_800C3294 = 0x001E0004;
int d01a_dword_800C3298 = 0x012C0001;
int d01a_dword_800C329C = 0x01F40001;
int d01a_dword_800C32A0 = 0x000001F4;
int d01a_dword_800C32A4 = 0x00000000;
int d01a_dword_800C32A8 = 0x800D0BEC;
int d01a_dword_800C32AC = 0x0008512D;
int d01a_dword_800C32B0 = 0x001E0004;
int d01a_dword_800C32B4 = 0x012C0001;
int d01a_dword_800C32B8 = 0x01F40001;
int d01a_dword_800C32BC = 0x000001F4;
int d01a_dword_800C32C0 = 0x00000000;
int d01a_dword_800C32C4 = 0x800D0C3C;

SVECTOR snow_svec_800C3854 = {-5000, 0, -10000, 0};
SVECTOR snow_svec_800C385C = {5000, 8000, 10000, 0};
SVECTOR snow_svec_800C3864 = {0, -50, 0, 0};
RECT    snow_rect_800C386C = {0, 0, 2, 2};

RECT rect_800C3320 = { 1000, 1000, 2000, 2000 };

int d01a_dword_800C32F0 = 0x0001479F;
int d01a_dword_800C32F4 = 0x00010001;
int d01a_dword_800C32F8 = 0x00E60001;
int d01a_dword_800C32FC = 0x012C0001;
int d01a_dword_800C3300 = 0x00FF012C;
int d01a_dword_800C3304 = 0x00000000;
int d01a_dword_800C3308 = 0x800D0D68;
int d01a_dword_800C330C = 0x0001479F;
int d01a_dword_800C3310 = 0x00010001;
int d01a_dword_800C3314 = 0x00E60001;
int d01a_dword_800C3318 = 0x03E80001;
int d01a_dword_800C331C = 0x002003E8;
int d01a_dword_800C3320 = 0x00000000;
int d01a_dword_800C3324 = 0x800D0D94;
int d01a_dword_800C3328 = 0x0001479F;
int d01a_dword_800C332C = 0x00010001;
int d01a_dword_800C3330 = 0x01F40001;
int d01a_dword_800C3334 = 0x00C80001;
int d01a_dword_800C3338 = 0x00FF00C8;
int d01a_dword_800C333C = 0x00000000;
int d01a_dword_800C3340 = 0x800D0DAC;
int d01a_dword_800C3344 = 0x0001479F;
int d01a_dword_800C3348 = 0x00010001;
int d01a_dword_800C334C = 0x01F40001;
int d01a_dword_800C3350 = 0x07D00001;
int d01a_dword_800C3354 = 0x004007D0;
int d01a_dword_800C3358 = 0x00000000;
int d01a_dword_800C335C = 0x800D0DBC;
int d01a_dword_800C3360 = 0x0001479F;
int d01a_dword_800C3364 = 0x00010001;
int d01a_dword_800C3368 = 0x00000001;
int d01a_dword_800C336C = 0x00140000;
int d01a_dword_800C3370 = 0x00FF0014;
int d01a_dword_800C3374 = 0x00000000;
int d01a_dword_800C3378 = 0x800D0DD0;
int d01a_dword_800C337C = 0x0001A9CD;
int d01a_dword_800C3380 = 0x00010001;
int d01a_dword_800C3384 = 0x00E60001;
int d01a_dword_800C3388 = 0x00000001;
int d01a_dword_800C338C = 0x00FF0000;
int d01a_dword_800C3390 = 0x00000000;
int d01a_dword_800C3394 = 0x800D0DDC;
int d01a_dword_800C3398 = 0x03E8012C;
int d01a_dword_800C339C = 0x0000012C;
int d01a_dword_800C33A0 = 0x00000000;
int d01a_dword_800C33A4 = 0x00000000;
int d01a_dword_800C33A8 = 0x01F40320;
int d01a_dword_800C33AC = 0x00000320;
int d01a_dword_800C33B0 = 0x00000064;
int d01a_dword_800C33B4 = 0x00000000;
int d01a_dword_800C33B8 = 0x0320012C;
int d01a_dword_800C33BC = 0x0000012C;
int d01a_dword_800C33C0 = 0x00000000;
int d01a_dword_800C33C4 = 0x00000000;
int d01a_dword_800C33C8 = 0x75307530;
int d01a_dword_800C33CC = 0x00007530;
int d01a_dword_800C33D0 = 0x00000101;
int d01a_dword_800C33D4 = 0x000001FF;
int d01a_dword_800C33D8 = 0x000009C4;
int d01a_dword_800C33DC = 0x00000DAC;
int d01a_dword_800C33E0 = 0x00000FA0;
int d01a_dword_800C33E4 = 0x00001388;
int d01a_dword_800C33E8 = 0x0000157C;
int d01a_dword_800C33EC = 0x000015E0;
int d01a_dword_800C33F0 = 0x00001644;
int d01a_dword_800C33F4 = 0x000016A8;
int d01a_dword_800C33F8 = 0x07D003E8;
int d01a_dword_800C33FC = 0x000005DC;
int d01a_dword_800C3400 = 0x07D005DC;
int d01a_dword_800C3404 = 0x000005DC;
int d01a_dword_800C3408 = 0x03E801F4;
int d01a_dword_800C340C = 0x07D003E8;

const char d01a_dword_800D0BEC[] = {0x0, 'I', 0x2, 0x0};
const char d01a_dword_800D0BF0[] = {0x7, 0x0, ')', 0x1};
const char d01a_dword_800D0BF4[] = {0xfe, 0xc, 0x0, 0x6};
const char d01a_dword_800D0BF8[] = {0x8, 0x6, 0x6, 0x6};
const char d01a_dword_800D0BFC[] = {0x1, 0xff, 0x2, 0x0};
const char d01a_dword_800D0C00[] = {0x1, 0xd, 0xc, 0x0};
const char d01a_dword_800D0C04[] = {'#', 0x8, 0xff, 0xff};
const char d01a_dword_800D0C08[] = {0xff, '\n', 0x0, 0x8};
const char d01a_dword_800D0C0C[] = {0x0, 0x8, 0x1, 0xff};
const char d01a_dword_800D0C10[] = {0x2, 0x0, 0x1, 0xd};
const char d01a_dword_800D0C14[] = {0xf, '\n', 0xff, '8'};
const char d01a_dword_800D0C18[] = {0xff, '8', 0x1, 0xfe};
const char d01a_dword_800D0C1C[] = {0xc, 0x0, 0x6, 0x8};
const char d01a_dword_800D0C20[] = {0x6, 0x6, 0x6, 0x1};
const char d01a_dword_800D0C24[] = {0xff, 0x2, 0x0, 0x1};
const char d01a_dword_800D0C28[] = {0xd, 0xc, 0x0, '#'};
const char d01a_dword_800D0C2C[] = {0x8, 0xff, 0xff, 0xff};
const char d01a_dword_800D0C30[] = {'\n', 0x0, 0x6, 0x0};
const char d01a_dword_800D0C34[] = {0x6, 0x1, 0xff, 0x2};
const char d01a_dword_800D0C38[] = {0x0, 0x1, 0xd, 0xf};
const char d01a_dword_800D0C3C[] = {0x0, ',', 0x1, 0x0};
const char d01a_dword_800D0C40[] = {0x5, 0x1, 0xfe, 0xc};
const char d01a_dword_800D0C44[] = {0x0, 0x3, 0x8, 0x6};
const char d01a_dword_800D0C48[] = {0x6, 0x6, 0x1, 0xff};
const char d01a_dword_800D0C4C[] = {0x2, 0x0, 0x1, 0xd};
const char d01a_dword_800D0C50[] = {0xc, 0x0, 0x10, 0x8};
const char d01a_dword_800D0C54[] = {0xff, 0xff, 0xff, '\n'};
const char d01a_dword_800D0C58[] = {0x0, 0x4, 0x0, 0x4};
const char d01a_dword_800D0C5C[] = {0x1, 0xff, 0x2, 0x0};
const char d01a_dword_800D0C60[] = {0x1, '\n', 0x0, 0x4};
const char d01a_dword_800D0C64[] = {0x0, 0x4, 0x1, 0xff};
const char d01a_dword_800D0C68[] = {0x2, 0x0, 0x1, 0xd};
const char d01a_dword_800D0C6C[] = {0xf, 0x0, 0x0, 0x0};
