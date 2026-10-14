#include "mgstype.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"

extern const char s08b_aNinja_800E3714[];

void s08b_bunsin2_800CD614();
void s08b_bunsin2_800CD690();
void s08b_bunsin2_800CD770();
void s08b_bunsin2_800CD808();
void s08b_bunsin2_800CD87C();
void s08b_bunsin2_800CD8D8();

MENU_BAR_CONF s08b_dword_800C3380 = {s08b_aNinja_800E3714, {0x10, 0x6F, 0x9F}, {0x1F, 0xDF, 0x7F}, 0};
int s08b_dword_800C338C = 255; /* life shown by the life bar */

SVECTOR s08b_dword_800C3390 = {300, 1500, 300, 0};  /* target size */
SVECTOR s08b_dword_800C3398 = {0, 0, -1000, 0};    /* power target offset */

/* motion indices */
short s08b_dword_800C33A0[40] = {
     0,  2, 18, 10, 40,  3,  4,  5,  1,  0, 11, 12, 19, 20, 21, 22, 34, 30, 23, 24,
    27, 28, 43, 13, 14, 15, 25, 26, 35, 36, 37, 38, 32, 33, 39, 25, 41, 42, 44, 45
};

SVECTOR s08b_dword_800C33F0 = {0, 0, 0, 0};
SVECTOR s08b_dword_800C33F8 = {0, 0, 100, 0};
SVECTOR s08b_dword_800C3400 = {-1024, 0, 0, 0};
SVECTOR s08b_dword_800C3408 = {0, 0, 100, 0};
SVECTOR s08b_dword_800C3410 = {-1024, 0, 0, 0};

void (*s08b_dword_800C3418[])() = {
    s08b_bunsin2_800CD614,
    s08b_bunsin2_800CD690,
    s08b_bunsin2_800CD770,
    s08b_bunsin2_800CD808,
    s08b_bunsin2_800CD87C,
    s08b_bunsin2_800CD8D8
};

SVECTOR s08b_dword_800C3430 = {5, -500, 80, 0};

int s08b_dword_800C3438 = 0;
int s08b_dword_800C343C = 0;
int s08b_dword_800C3440 = 0;
int s08b_dword_800C3444 = 0;
int s08b_dword_800C3448 = 0;
int s08b_dword_800C344C = 0;
int s08b_dword_800C3450 = 0;
int s08b_dword_800C3454 = 18;

SVECTOR s08b_dword_800C3458 = {2000, 1000, 0, 0};

SVECTOR s08b_dword_800C3460[6] = {
    {4000, 1000, 6000, 0}, {-8000, 1000, -4000, 0}, {6200, 1000, 0, 0},
    {2000, 1000, 0, 0}, {-2500, 1000, 0, 0}, {-11000, 1000, -2250, 0}
};

SVECTOR s08b_dword_800C3490[4] = {
    {-7000, 1000, 500, 0}, {3500, 1000, -500, 0}, {3500, 1000, 6000, 0}, {-7000, 1000, 6000, 0}
};

SVECTOR s08b_dword_800C34B0[9] = {
    {-1000, 1000, 2000, 0}, {4000, 1000, 6500, 0}, {-5500, 1000, -1500, 0},
    {3000, 1000, -2500, 0}, {-6000, 1000, -1500, 0}, {2000, 1000, -1500, 0},
    {-1500, 1000, 3000, 0}, {-7000, 1000, 5500, 0}, {4000, 1000, 4500, 0}
};

SVECTOR s08b_dword_800C34F8[3] = {
    {-4500, 1000, -2000, 0}, {0, 1000, 2000, 0}, {1000, 1000, -2000, 0}
};

short s08b_dword_800C3510[2][2] = {{10, 16}, {13, 45}};

/* route graph: node followed by up to three neighbours (0xFF: none) */
u_char s08b_dword_800C3518[20][4] = {
    { 0, 10, 23,   30}, { 2,  5, 34, 0xFF}, { 4,  6, 14, 0xFF}, { 5,  2, 34, 0xFF},
    { 6,  4, 14, 0xFF}, { 8, 12, 33,   35}, {10,  0, 23,   30}, {12,  8, 33,   35},
    {14,  4,  6, 0xFF}, {16, 18, 28, 0xFF}, {18, 16, 28, 0xFF}, {23,  0, 10,   30},
    {28, 16, 18, 0xFF}, {29, 31, 32, 0xFF}, {30,  0, 10,   23}, {31, 29, 32, 0xFF},
    {32, 29, 31, 0xFF}, {33,  8, 12,   35}, {34,  2,  5, 0xFF}, {35,  8, 12,   33}
};

SVECTOR s08b_dword_800C3568[4] = {
    {4000, 1000, 6000, 0}, {3000, 1000, -1000, 0}, {-7500, 1000, 6500, 0}, {-7500, 1000, -1500, 0}
};

int     s08b_dword_800C3588 = 0;
SVECTOR s08b_dword_800C358C = {-2000, 2000, -1250, 0};
int     s08b_dword_800C3594 = 74;

const char s08b_aNinja_800E3714[] = "NINJA";
const int s08b_dword_800E371C = 0x800C8054;
const int s08b_dword_800E3720 = 0x800C8064;
const int s08b_dword_800E3724 = 0x800C80C4;
const int s08b_dword_800E3728 = 0x800C8074;
const int s08b_dword_800E372C = 0x800C80CC;
const int s08b_dword_800E3730 = 0x800C8084;
const int s08b_dword_800E3734 = 0x800C8094;
const int s08b_dword_800E3738 = 0x800C80A4;
const int s08b_dword_800E373C = 0x800C80B4;
const char s08b_aNjafist_800E3740[] = "nja_fist";
const char s08b_aNjab_800E374C[] = "nja_08b";
const char s08b_aKatana_800E3754[] = "katana";
const char s08b_aShadow_800E375C[] = "shadow";
const char s08b_aErrerrerrsoundbuffover_800E3764[] = "Err Err Err Sound Buff Over !!\n";
const char s08b_aNumd_800E3784[] = "@@@@ num=%d \n";
const char s08b_aPunchdamaged_800E3794[] = " punch damage=%d \n";
const char s08b_aKickdamaged_800E37A8[] = " kick damage=%d \n";
const char s08b_aSlashdamaged_800E37BC[] = " slash damage=%d \n";
const char s08b_aJumpdamaged_800E37D0[] = " jump damage=%d \n";
const char s08b_aEledamaged_800E37E4[] = " ele damage=%d \n";
const char s08b_aNinjac_800E37F8[] = "ninja.c";

const int s08b_dword_800E3800 = 0x800C9154;
const int s08b_dword_800E3804 = 0x800C9174;
const int s08b_dword_800E3808 = 0x800C9184;
const int s08b_dword_800E380C = 0x800C9194;
const int s08b_dword_800E3810 = 0x800C91A4;
const int s08b_dword_800E3814 = 0x800C91B4;
const int s08b_dword_800E3818 = 0x800C91C4;
const int s08b_dword_800E381C = 0x800C91D4;
const int s08b_dword_800E3820 = 0x800C91E4;
const int s08b_dword_800E3824 = 0x800C9204;
const int s08b_dword_800E3828 = 0x800C9334;
const int s08b_dword_800E382C = 0x800C9244;
const int s08b_dword_800E3830 = 0x800C9254;
const int s08b_dword_800E3834 = 0x800C9264;
const int s08b_dword_800E3838 = 0x800C9274;
const int s08b_dword_800E383C = 0x800C9284;
const int s08b_dword_800E3840 = 0x800C9294;
const int s08b_dword_800E3844 = 0x800C92A4;
const int s08b_dword_800E3848 = 0x800C92B4;
const int s08b_dword_800E384C = 0x800C92C4;
const int s08b_dword_800E3850 = 0x800C91F4;
const int s08b_dword_800E3854 = 0x800C9214;
const int s08b_dword_800E3858 = 0x800C9224;
const int s08b_dword_800E385C = 0x800C9234;
const int s08b_dword_800E3860 = 0x800C92D4;
const int s08b_dword_800E3864 = 0x800C92E4;
const int s08b_dword_800E3868 = 0x800C92F4;
const int s08b_dword_800E386C = 0x800C9304;
const int s08b_dword_800E3870 = 0x800C9314;
const int s08b_dword_800E3874 = 0x800C9324;
const char s08b_aWeaponxxamodexx_800E3878[] = "WEAPON=0x%x a_mode=0x%x \n";
const char s08b_dword_800E3894[] = {'8', 0xff, 0xc8, 0x0};
const char s08b_dword_800E3898[] = {0xc8, 0x0, 0x0, 0x0};
const char s08b_dword_800E389C[] = {'8', 0xff, 0xc, 0xfe};
const char s08b_dword_800E38A0[] = {0x90, 0x1, 0x0, 0x0};
const char s08b_dword_800E38A4[] = {0x0, 0x0, 0xc, 0xfe};
const char s08b_dword_800E38A8[] = {0x0, 0x0, 0x0, 0x0};
const char s08b_dword_800E38AC[] = {0xf4, 0x1, 0x90, 0x1};
const char s08b_dword_800E38B0[] = {' ', 0x3, 0x0, 0x0};
const char s08b_dword_800E38B4[] = {0xb8, 0xb, 0xd0, 0x7};
const char s08b_dword_800E38B8[] = {0xb8, 0xb, 0x0, 0x0};
const char s08b_dword_800E38BC[] = {0xe8, 0x3, 0xd0, 0x7};
const char s08b_dword_800E38C0[] = {0xe8, 0x3, 0x0, 0x0};
const char s08b_dword_800E38C4[] = {0xdc, 0x5, 0xd0, 0x7};
const char s08b_dword_800E38C8[] = {0xdc, 0x5, 0x0, 0x0};
const char s08b_dword_800E38CC[] = {0xd0, 0x7, 0xd0, 0x7};
const char s08b_dword_800E38D0[] = {0xd0, 0x7, 0x0, 0x0};
const char s08b_dword_800E38D4[] = {0x5, 0x0, 0x0, 0x0};
const char s08b_a_800E38D8[] = "2";
const char s08b_dword_800E38DC[] = {0x0, 0x0, 0x0, 0x0};
const int s08b_dword_800E38E0 = 0x800C9828;
const int s08b_dword_800E38E4 = 0x800C9854;
const int s08b_dword_800E38E8 = 0x800C986C;
const int s08b_dword_800E38EC = 0x800C9898;
const int s08b_dword_800E38F0 = 0x800C98C4;
const int s08b_dword_800E38F4 = 0x800C98DC;
const int s08b_dword_800E38F8 = 0x800C98DC;
const char s08b_dword_800E38FC[] = {0x0, 0x0, 0x0, 0x0};
const int s08b_dword_800E3900 = 0x800C99CC;
const int s08b_dword_800E3904 = 0x800C99DC;
const int s08b_dword_800E3908 = 0x800C9A04;
const int s08b_dword_800E390C = 0x800C9A14;
const int s08b_dword_800E3910 = 0x800C9A24;
const int s08b_dword_800E3914 = 0x800C9A44;
const int s08b_dword_800E3918 = 0x800C9A44;
const int s08b_dword_800E391C = 0x800C9A44;
const char s08b_aJumpfctrlturnvyd_800E3920[] = " jumpf ctrl turn vy =%d \n";
const char s08b_aPunchdamagelifedcombod_800E393C[] = "Punch Damage life = %d combo %d\n";

int SECTION(".bss") s08b_dword_800E4314;
int SECTION(".bss") s08b_dword_800E4318;
int SECTION(".bss") s08b_dword_800E431C;
int SECTION(".bss") s08b_dword_800E4320;
int SECTION(".bss") s08b_dword_800E4324;
int SECTION(".bss") s08b_dword_800E4328;
int SECTION(".bss") s08b_dword_800E432C;
int SECTION(".bss") s08b_dword_800E4330;
int SECTION(".bss") s08b_dword_800E4334;
int SECTION(".bss") s08b_dword_800E4338;
int SECTION(".bss") s08b_dword_800E433C;
int SECTION(".bss") s08b_dword_800E4340;
