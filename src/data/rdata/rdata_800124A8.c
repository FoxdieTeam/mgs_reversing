#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "linker.h"

const char SECTION(".rdata") aGrenadeC[] = "grenade.c";
const char SECTION(".rdata") aClaymore_0[] = "claymore";
const char SECTION(".rdata") aLockOn[] = "LOCK_ON\n";
const char SECTION(".rdata") aStnsightC[] = "stnsight.c";
const char SECTION(".rdata") aRfsightC[] = "rfsight.c";
const char SECTION(".rdata") aTenageC[] = "tenage.c";
const char SECTION(".rdata") aBakudanC[] = "bakudan.c";
const char SECTION(".rdata") aClaymore_1[] = "CLAYMORE";
const char SECTION(".rdata") aFull_0[] = "FULL";
const char SECTION(".rdata") aClaymore_2[] = "claymore";
const char SECTION(".rdata") aJiraiC[] = "jirai.c";
const char SECTION(".rdata") aEnemy[] = "ENEMY\n";
const char SECTION(".rdata") aD_4[] = "%d";               // 80012B80
const char SECTION(".rdata") aSocomF[] = "socom_f";       // 80012B84
const char SECTION(".rdata") rRmissileC[] = "rmissile.c"; // 80012B8C
const char SECTION(".rdata") aRmissileC[] = "amissile.c"; // 80012B98
const char SECTION(".rdata") aBlastC[] = "blast.c";       // 80012BA4

const unsigned char SECTION(".rdata") animation_data_80012BAC[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char SECTION(".rdata") animation_data_80012BEC[64] = {
    0u,   59u,  1u,   0u, 5u,  1u, 0u,   2u, 0u,  1u, 12u, 0u,  4u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 12u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   8u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u,  1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char SECTION(".rdata") animation_data_80012C2C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  2u,  88u, 2u,  88u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,  50u, 0u,  50u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 40u, 0u, 40u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,  13u, 15u};

const unsigned char SECTION(".rdata") animation_data_80012C6C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  0u,  200u, 0u,  200u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   20u, 0u,   20u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 20u, 0u, 20u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u, 15u};

const unsigned char SECTION(".rdata") animation_data_80012CAC[290] = {
    1u,   23u,  4u,   0u,   11u,  0u,   75u,  0u,   144u, 0u,   217u, 1u,   0u,   2u,   0u,  1u,   12u,  0u,   2u,
    1u,   255u, 10u,  4u,   176u, 4u,   176u, 2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,  255u, 10u,  0u,   200u,
    0u,   200u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,  100u, 8u,   248u, 248u,
    248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u,  1u,
    0u,   2u,   0u,   1u,   1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u, 3u,   232u, 3u,   232u,
    2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   180u, 0u,   180u, 2u,  0u,   1u,   13u,  12u,
    0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,  1u,   10u,  0u,   80u,
    0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   2u,   1u,  0u,   2u,   0u,   1u,
    13u,  1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  3u,   32u,  3u,  32u,  2u,   0u,   1u,
    13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   160u, 0u,   160u, 2u,   0u,   1u,   13u, 12u,  0u,   7u,   1u,
    255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,  80u,  0u,   80u,  8u,
    248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   3u,   1u,   0u,   2u,   0u,  1u,   13u,  1u,   0u,
    2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  2u,   88u,  2u,   88u,  2u,   0u,  1u,   13u,  12u,  0u,
    6u,   1u,   255u, 10u,  0u,   140u, 0u,   140u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,  1u,   255u, 10u,  0u,
    100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u, 8u,   248u, 248u, 248u,
    2u,   0u,   1u,   13u,  15u};

const char SECTION(".rdata") aOpen[] = " open!! \n";                     // 80012DD0
const char SECTION(".rdata") aClose[] = " close!! \n";                   // 80012DDC
const char SECTION(".rdata") aDoorCloseD[] = "door:close %d\n";          // 80012DE8
const char SECTION(".rdata") aCancel[] = "cancel\n";                     // 80012DF8
const char SECTION(".rdata") aDoorOpenD[] = "door:open %d\n";            // 80012E00
const char SECTION(".rdata") aSnakeDoorX[] = "Snake Door %X\n";          // 80012E10
const char SECTION(".rdata") aDoorOpencancel[] = "door:opencancel %d\n"; // 80012E20
const char SECTION(".rdata") aCloseDoorX[] = "close door %X\n";
const char SECTION(".rdata") aCloseDoorX_0[] = "CLOSE door %X\n";
const char SECTION(".rdata") aDoorC[] = "door.c";

const char SECTION(".rdata") aSgtrect3C[] = "sgtrect3.c";

// AN_Blood_Mist_80072934
const char SECTION(".rdata") aStringFormat[] = "%s";
const char SECTION(".rdata") aSightC[] = "sight.c";

const char SECTION(".rdata") aBlood_1[] = "blood_1";
const char SECTION(".rdata") aBloodC[] = "blood.c";
const int  SECTION(".rdata") aS_2_80012E68[] = {0x12A00,   0x2FE0105, 0x80100,    0xCB0B0,    0xAFF0105, 0x64006400,
                                                0xD010002, 0x105000C, 0x1E000AFF, 0xE8081E00, 0x2F8F8,   0xF0D01};
