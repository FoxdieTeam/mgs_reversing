#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/target.h"
#include "Game/game.h"
#include "Game/homing.h"
#include "Game/object.h"
#include "Okajima/blood.h"

typedef struct DogWork
{
    GV_ACT   actor;
    int      field_20;
    int      field_24;
    CONTROL  field_28[3];
    OBJECT   field_19C[3];
    char     pad448[0xD40];
    TARGET  *field_1188[3];
    TARGET   field_1194[3];
    HOMING  *field_126C[3];
    short    field_1278;
    char     pad127A[0x21A];
    int      field_1494[3];
    char     pad14A0[0x14];
    int      unk14B4;
    int      field_14B8[3];
    char     pad14C4[0x28];
    int      field_14EC[3];
    int      field_14F8[3];
    char     pad1504[0xC];
    int      field_1510[3];
    char     pad151C[0xC];
    int      field_1528;
    char     pad152C[0x30];
    int      field_155C[3];
    char     pad1568[0x24];
    int      field_158C[3];
    char     pad1598[0x24];
    int      field_15BC[3];
    char     pad15C8[0x38];
    int      field_1600;
    char     pad1604[0xC];
    int      field_1610;
    char     pad1614[0x68];
    DG_PRIM *field_167C[3];
    char     pad1688[0x10];
    int      field_1698[3];
    char     pad16A4[0xD0];
    int      field_1774;
    char     pad1778[0x38];
    int      field_17B0;
    int      field_17B4;
    char     pad17B8[0x30];
} DogWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

int s12c_dword_800C3430 = 0x000001F4;
int s12c_dword_800C3434 = 0x000003E8;
int s12c_dword_800C3438 = 0x0000FE0C;
int s12c_dword_800C343C = 0x000003E8;
int s12c_dword_800C3440 = 0x000000FA;
int s12c_dword_800C3444 = 0x000001F4;
int s12c_dword_800C3448 = 0x0000FF06;
int s12c_dword_800C344C = 0x000001F4;

SVECTOR s12c_dword_800C3450 = {0, 0, 100};
SVECTOR s12c_dword_800C3458 = {64512, 0, 0};

const int  s12c_dword_800D9AD4 = 0x800CAD30;
const int  s12c_dword_800D9AD8 = 0x800CAD44;
const int  s12c_dword_800D9ADC = 0x800CAD30;
const int  s12c_dword_800D9AE0 = 0x800CAD30;
const int  s12c_dword_800D9AE4 = 0x800CAD30;
const int  s12c_dword_800D9AE8 = 0x800CAD30;
const int  s12c_dword_800D9AEC = 0x800CAD30;
const int  s12c_dword_800D9AF0 = 0x800CAD30;
const int  s12c_dword_800D9AF4 = 0x800CAD30;
const int  s12c_dword_800D9AF8 = 0x800CAD30;
const int  s12c_dword_800D9AFC = 0x800CAD44;
const int  s12c_dword_800D9B00 = 0x800CAD44;
const int  s12c_dword_800D9B04 = 0x800CAD44;
const int  s12c_dword_800D9B08 = 0x800CAD44;
const int  s12c_dword_800D9B0C = 0x800CAD44;
const int  s12c_dword_800D9B10 = 0x800CAD44;
const int  s12c_dword_800D9B14 = 0x800CAD44;
const int  s12c_dword_800D9B18 = 0x800CAD30;
const int  s12c_dword_800D9B1C = 0x800CAD30;
const int  s12c_dword_800D9B20 = 0x800CAD30;
const int  s12c_dword_800D9B24 = 0x800CAD44;
const int  s12c_dword_800D9B28 = 0x800CAD30;
const int  s12c_dword_800D9B2C = 0x800CAD30;
const int  s12c_dword_800D9B30 = 0x800CAD30;
const int  s12c_dword_800D9B34 = 0x800CAD30;
const int  s12c_dword_800D9B38 = 0x800CAD30;
const int  s12c_dword_800D9B3C = 0x800CAD44;
const int  s12c_dword_800D9B40 = 0x800CAD44;
const int  s12c_dword_800D9B44 = 0x800CAD30;
const char s12c_dword_800D9B48[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9B4C = 0x800CBE4C;
const int  s12c_dword_800D9B50 = 0x800CBE6C;
const int  s12c_dword_800D9B54 = 0x800CBECC;
const int  s12c_dword_800D9B58 = 0x800CC164;
const int  s12c_dword_800D9B5C = 0x800CC164;
const int  s12c_dword_800D9B60 = 0x800CBF4C;
const int  s12c_dword_800D9B64 = 0x800CC164;
const int  s12c_dword_800D9B68 = 0x800CC164;
const int  s12c_dword_800D9B6C = 0x800CC164;
const int  s12c_dword_800D9B70 = 0x800CC164;
const int  s12c_dword_800D9B74 = 0x800CC164;
const int  s12c_dword_800D9B78 = 0x800CC164;
const int  s12c_dword_800D9B7C = 0x800CC164;
const int  s12c_dword_800D9B80 = 0x800CC164;
const int  s12c_dword_800D9B84 = 0x800CBFA4;
const int  s12c_dword_800D9B88 = 0x800CC164;
const int  s12c_dword_800D9B8C = 0x800CC164;
const int  s12c_dword_800D9B90 = 0x800CC000;
const int  s12c_dword_800D9B94 = 0x800CC164;
const int  s12c_dword_800D9B98 = 0x800CC164;
const int  s12c_dword_800D9B9C = 0x800CC104;
const int  s12c_dword_800D9BA0 = 0x800CC164;
const int  s12c_dword_800D9BA4 = 0x800CC164;
const int  s12c_dword_800D9BA8 = 0x800CC164;
const int  s12c_dword_800D9BAC = 0x800CC164;
const int  s12c_dword_800D9BB0 = 0x800CC164;
const int  s12c_dword_800D9BB4 = 0x800CC164;
const int  s12c_dword_800D9BB8 = 0x800CC120;
const int  s12c_dword_800D9BBC = 0x800CC208;
const int  s12c_dword_800D9BC0 = 0x800CC228;
const int  s12c_dword_800D9BC4 = 0x800CC288;
const int  s12c_dword_800D9BC8 = 0x800CC520;
const int  s12c_dword_800D9BCC = 0x800CC520;
const int  s12c_dword_800D9BD0 = 0x800CC308;
const int  s12c_dword_800D9BD4 = 0x800CC520;
const int  s12c_dword_800D9BD8 = 0x800CC520;
const int  s12c_dword_800D9BDC = 0x800CC520;
const int  s12c_dword_800D9BE0 = 0x800CC520;
const int  s12c_dword_800D9BE4 = 0x800CC520;
const int  s12c_dword_800D9BE8 = 0x800CC520;
const int  s12c_dword_800D9BEC = 0x800CC520;
const int  s12c_dword_800D9BF0 = 0x800CC520;
const int  s12c_dword_800D9BF4 = 0x800CC360;
const int  s12c_dword_800D9BF8 = 0x800CC520;
const int  s12c_dword_800D9BFC = 0x800CC520;
const int  s12c_dword_800D9C00 = 0x800CC3BC;
const int  s12c_dword_800D9C04 = 0x800CC520;
const int  s12c_dword_800D9C08 = 0x800CC520;
const int  s12c_dword_800D9C0C = 0x800CC4C0;
const int  s12c_dword_800D9C10 = 0x800CC520;
const int  s12c_dword_800D9C14 = 0x800CC520;
const int  s12c_dword_800D9C18 = 0x800CC520;
const int  s12c_dword_800D9C1C = 0x800CC520;
const int  s12c_dword_800D9C20 = 0x800CC520;
const int  s12c_dword_800D9C24 = 0x800CC520;
const int  s12c_dword_800D9C28 = 0x800CC4DC;
const int  s12c_dword_800D9C2C = 0x800CC5C4;
const int  s12c_dword_800D9C30 = 0x800CC5E4;
const int  s12c_dword_800D9C34 = 0x800CC898;
const int  s12c_dword_800D9C38 = 0x800CC898;
const int  s12c_dword_800D9C3C = 0x800CC898;
const int  s12c_dword_800D9C40 = 0x800CC748;
const int  s12c_dword_800D9C44 = 0x800CC898;
const int  s12c_dword_800D9C48 = 0x800CC898;
const int  s12c_dword_800D9C4C = 0x800CC898;
const int  s12c_dword_800D9C50 = 0x800CC898;
const int  s12c_dword_800D9C54 = 0x800CC898;
const int  s12c_dword_800D9C58 = 0x800CC898;
const int  s12c_dword_800D9C5C = 0x800CC898;
const int  s12c_dword_800D9C60 = 0x800CC898;
const int  s12c_dword_800D9C64 = 0x800CC7A4;
const int  s12c_dword_800D9C68 = 0x800CC898;
const int  s12c_dword_800D9C6C = 0x800CC898;
const int  s12c_dword_800D9C70 = 0x800CC834;
const int  s12c_dword_800D9C74 = 0x800CC898;
const int  s12c_dword_800D9C78 = 0x800CC898;
const int  s12c_dword_800D9C7C = 0x800CC898;
const int  s12c_dword_800D9C80 = 0x800CC898;
const int  s12c_dword_800D9C84 = 0x800CC898;
const int  s12c_dword_800D9C88 = 0x800CC898;
const int  s12c_dword_800D9C8C = 0x800CC898;
const int  s12c_dword_800D9C90 = 0x800CC898;
const int  s12c_dword_800D9C94 = 0x800CC898;
const int  s12c_dword_800D9C98 = 0x800CC898;
const int  s12c_dword_800D9C9C = 0x800CC898;
const int  s12c_dword_800D9CA0 = 0x800CC898;
const int  s12c_dword_800D9CA4 = 0x800CC898;
const int  s12c_dword_800D9CA8 = 0x800CC898;
const int  s12c_dword_800D9CAC = 0x800CC898;
const int  s12c_dword_800D9CB0 = 0x800CC898;
const int  s12c_dword_800D9CB4 = 0x800CC898;
const int  s12c_dword_800D9CB8 = 0x800CC898;
const int  s12c_dword_800D9CBC = 0x800CC898;
const int  s12c_dword_800D9CC0 = 0x800CC818;
const int  s12c_dword_800D9CC4 = 0x800CC93C;
const int  s12c_dword_800D9CC8 = 0x800CC95C;
const int  s12c_dword_800D9CCC = 0x800CCC20;
const int  s12c_dword_800D9CD0 = 0x800CCC20;
const int  s12c_dword_800D9CD4 = 0x800CCC20;
const int  s12c_dword_800D9CD8 = 0x800CCAAC;
const int  s12c_dword_800D9CDC = 0x800CCC20;
const int  s12c_dword_800D9CE0 = 0x800CCC20;
const int  s12c_dword_800D9CE4 = 0x800CCC20;
const int  s12c_dword_800D9CE8 = 0x800CCC20;
const int  s12c_dword_800D9CEC = 0x800CCC20;
const int  s12c_dword_800D9CF0 = 0x800CCC20;
const int  s12c_dword_800D9CF4 = 0x800CCC20;
const int  s12c_dword_800D9CF8 = 0x800CCC20;
const int  s12c_dword_800D9CFC = 0x800CCB1C;
const int  s12c_dword_800D9D00 = 0x800CCC20;
const int  s12c_dword_800D9D04 = 0x800CCC20;
const int  s12c_dword_800D9D08 = 0x800CCBBC;
const int  s12c_dword_800D9D0C = 0x800CCC20;
const int  s12c_dword_800D9D10 = 0x800CCC20;
const int  s12c_dword_800D9D14 = 0x800CCC20;
const int  s12c_dword_800D9D18 = 0x800CCC20;
const int  s12c_dword_800D9D1C = 0x800CCC20;
const int  s12c_dword_800D9D20 = 0x800CCC20;
const int  s12c_dword_800D9D24 = 0x800CCC20;
const int  s12c_dword_800D9D28 = 0x800CCC20;
const int  s12c_dword_800D9D2C = 0x800CCC20;
const int  s12c_dword_800D9D30 = 0x800CCC20;
const int  s12c_dword_800D9D34 = 0x800CCC20;
const int  s12c_dword_800D9D38 = 0x800CCC20;
const int  s12c_dword_800D9D3C = 0x800CCC20;
const int  s12c_dword_800D9D40 = 0x800CCC20;
const int  s12c_dword_800D9D44 = 0x800CCC20;
const int  s12c_dword_800D9D48 = 0x800CCC20;
const int  s12c_dword_800D9D4C = 0x800CCC20;
const int  s12c_dword_800D9D50 = 0x800CCC20;
const int  s12c_dword_800D9D54 = 0x800CCC20;
const int  s12c_dword_800D9D58 = 0x800CCBA0;
const int  s12c_dword_800D9D5C = 0x800CCCD0;
const int  s12c_dword_800D9D60 = 0x800CCD34;
const int  s12c_dword_800D9D64 = 0x800CCE48;
const int  s12c_dword_800D9D68 = 0x800CDBA0;
const int  s12c_dword_800D9D6C = 0x800CCEF8;
const int  s12c_dword_800D9D70 = 0x800CCF40;
const int  s12c_dword_800D9D74 = 0x800CD258;
const int  s12c_dword_800D9D78 = 0x800CD454;
const int  s12c_dword_800D9D7C = 0x800CDBA0;
const int  s12c_dword_800D9D80 = 0x800CDBA0;
const int  s12c_dword_800D9D84 = 0x800CDBA0;
const int  s12c_dword_800D9D88 = 0x800CD480;
const int  s12c_dword_800D9D8C = 0x800CDBA0;
const int  s12c_dword_800D9D90 = 0x800CD5D0;
const int  s12c_dword_800D9D94 = 0x800CDBA0;
const int  s12c_dword_800D9D98 = 0x800CDBA0;
const int  s12c_dword_800D9D9C = 0x800CDBA0;
const int  s12c_dword_800D9DA0 = 0x800CD68C;
const int  s12c_dword_800D9DA4 = 0x800CDBA0;
const int  s12c_dword_800D9DA8 = 0x800CDBA0;
const int  s12c_dword_800D9DAC = 0x800CD808;
const int  s12c_dword_800D9DB0 = 0x800CDBA0;
const int  s12c_dword_800D9DB4 = 0x800CDBA0;
const int  s12c_dword_800D9DB8 = 0x800CDBA0;
const int  s12c_dword_800D9DBC = 0x800CDBA0;
const int  s12c_dword_800D9DC0 = 0x800CDBA0;
const int  s12c_dword_800D9DC4 = 0x800CDBA0;
const int  s12c_dword_800D9DC8 = 0x800CD8F4;
const int  s12c_dword_800D9DCC = 0x800CDBA0;
const int  s12c_dword_800D9DD0 = 0x800CDBA0;
const int  s12c_dword_800D9DD4 = 0x800CDBA0;
const int  s12c_dword_800D9DD8 = 0x800CDBA0;
const int  s12c_dword_800D9DDC = 0x800CDABC;
const char s12c_dword_800D9DE0[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9DE4 = 0x800CDD10;
const int  s12c_dword_800D9DE8 = 0x800CDD20;
const int  s12c_dword_800D9DEC = 0x800CE008;
const int  s12c_dword_800D9DF0 = 0x800CE008;
const int  s12c_dword_800D9DF4 = 0x800CE008;
const int  s12c_dword_800D9DF8 = 0x800CDDB4;
const int  s12c_dword_800D9DFC = 0x800CE008;
const int  s12c_dword_800D9E00 = 0x800CE008;
const int  s12c_dword_800D9E04 = 0x800CE008;
const int  s12c_dword_800D9E08 = 0x800CE008;
const int  s12c_dword_800D9E0C = 0x800CE008;
const int  s12c_dword_800D9E10 = 0x800CE008;
const int  s12c_dword_800D9E14 = 0x800CE008;
const int  s12c_dword_800D9E18 = 0x800CE008;
const int  s12c_dword_800D9E1C = 0x800CDDE8;
const int  s12c_dword_800D9E20 = 0x800CE008;
const int  s12c_dword_800D9E24 = 0x800CE008;
const int  s12c_dword_800D9E28 = 0x800CDE04;
const int  s12c_dword_800D9E2C = 0x800CE008;
const int  s12c_dword_800D9E30 = 0x800CE008;
const int  s12c_dword_800D9E34 = 0x800CDECC;
const int  s12c_dword_800D9E38 = 0x800CE008;
const int  s12c_dword_800D9E3C = 0x800CE008;
const int  s12c_dword_800D9E40 = 0x800CE008;
const int  s12c_dword_800D9E44 = 0x800CE008;
const int  s12c_dword_800D9E48 = 0x800CE008;
const int  s12c_dword_800D9E4C = 0x800CE008;
const int  s12c_dword_800D9E50 = 0x800CDF1C;
const int  s12c_dword_800D9E54 = 0x800CE008;
const int  s12c_dword_800D9E58 = 0x800CE008;
const int  s12c_dword_800D9E5C = 0x800CE008;
const int  s12c_dword_800D9E60 = 0x800CE008;
const int  s12c_dword_800D9E64 = 0x800CDF50;
const int  s12c_dword_800D9E68 = 0x800CDF70;
const int  s12c_dword_800D9E6C = 0x800CDFAC;
const int  s12c_dword_800D9E70 = 0x800CDFF0;
const int  s12c_dword_800D9E74 = 0x800CE2F8;
const int  s12c_dword_800D9E78 = 0x800CE330;
const int  s12c_dword_800D9E7C = 0x800CEA2C;
const int  s12c_dword_800D9E80 = 0x800CEA2C;
const int  s12c_dword_800D9E84 = 0x800CEA2C;
const int  s12c_dword_800D9E88 = 0x800CE618;
const int  s12c_dword_800D9E8C = 0x800CEA2C;
const int  s12c_dword_800D9E90 = 0x800CEA2C;
const int  s12c_dword_800D9E94 = 0x800CEA2C;
const int  s12c_dword_800D9E98 = 0x800CEA2C;
const int  s12c_dword_800D9E9C = 0x800CEA2C;
const int  s12c_dword_800D9EA0 = 0x800CEA2C;
const int  s12c_dword_800D9EA4 = 0x800CEA2C;
const int  s12c_dword_800D9EA8 = 0x800CEA2C;
const int  s12c_dword_800D9EAC = 0x800CE658;
const int  s12c_dword_800D9EB0 = 0x800CE6E8;
const int  s12c_dword_800D9EB4 = 0x800CEA2C;
const int  s12c_dword_800D9EB8 = 0x800CE7F8;
const int  s12c_dword_800D9EBC = 0x800CEA2C;
const int  s12c_dword_800D9EC0 = 0x800CEA2C;
const int  s12c_dword_800D9EC4 = 0x800CEA2C;
const int  s12c_dword_800D9EC8 = 0x800CEA2C;
const int  s12c_dword_800D9ECC = 0x800CEA2C;
const int  s12c_dword_800D9ED0 = 0x800CEA2C;
const int  s12c_dword_800D9ED4 = 0x800CEA2C;
const int  s12c_dword_800D9ED8 = 0x800CEA2C;
const int  s12c_dword_800D9EDC = 0x800CEA2C;
const int  s12c_dword_800D9EE0 = 0x800CE940;
const int  s12c_dword_800D9EE4 = 0x800CEA2C;
const int  s12c_dword_800D9EE8 = 0x800CEA2C;
const int  s12c_dword_800D9EEC = 0x800CEA2C;
const int  s12c_dword_800D9EF0 = 0x800CEA2C;
const int  s12c_dword_800D9EF4 = 0x800CEA2C;
const int  s12c_dword_800D9EF8 = 0x800CEA2C;
const int  s12c_dword_800D9EFC = 0x800CE950;
const int  s12c_dword_800D9F00 = 0x800CE9F4;
const int  s12c_dword_800D9F04 = 0x800CEA14;
const char s12c_dword_800D9F08[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9F0C = 0x800CECB4;
const int  s12c_dword_800D9F10 = 0x800CED2C;
const int  s12c_dword_800D9F14 = 0x800CF554;
const int  s12c_dword_800D9F18 = 0x800CF554;
const int  s12c_dword_800D9F1C = 0x800CF554;
const int  s12c_dword_800D9F20 = 0x800CF554;
const int  s12c_dword_800D9F24 = 0x800CF06C;
const int  s12c_dword_800D9F28 = 0x800CF0C4;
const int  s12c_dword_800D9F2C = 0x800CF554;
const int  s12c_dword_800D9F30 = 0x800CF2AC;
const int  s12c_dword_800D9F34 = 0x800CF554;
const int  s12c_dword_800D9F38 = 0x800CF554;
const int  s12c_dword_800D9F3C = 0x800CF554;
const int  s12c_dword_800D9F40 = 0x800CF554;
const int  s12c_dword_800D9F44 = 0x800CF4A0;
const char s12c_dword_800D9F48[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9F4C = 0x800CF750;
const int  s12c_dword_800D9F50 = 0x800CF7B4;
const int  s12c_dword_800D9F54 = 0x800CFA10;
const int  s12c_dword_800D9F58 = 0x800CFA10;
const int  s12c_dword_800D9F5C = 0x800CFA10;
const int  s12c_dword_800D9F60 = 0x800CF7D0;
const int  s12c_dword_800D9F64 = 0x800CF7FC;
const int  s12c_dword_800D9F68 = 0x800CFA10;
const int  s12c_dword_800D9F6C = 0x800CFA10;
const int  s12c_dword_800D9F70 = 0x800CFA10;
const int  s12c_dword_800D9F74 = 0x800CFA10;
const int  s12c_dword_800D9F78 = 0x800CFA10;
const int  s12c_dword_800D9F7C = 0x800CFA10;
const int  s12c_dword_800D9F80 = 0x800CFA10;
const int  s12c_dword_800D9F84 = 0x800CF8F8;
const int  s12c_dword_800D9F88 = 0x800CFA10;
const int  s12c_dword_800D9F8C = 0x800CFA10;
const int  s12c_dword_800D9F90 = 0x800CF9A0;
const int  s12c_dword_800D9F94 = 0x800CFAA8;
const int  s12c_dword_800D9F98 = 0x800CFAB8;
const int  s12c_dword_800D9F9C = 0x800D0298;
const int  s12c_dword_800D9FA0 = 0x800D0298;
const int  s12c_dword_800D9FA4 = 0x800D0298;
const int  s12c_dword_800D9FA8 = 0x800CFF50;
const int  s12c_dword_800D9FAC = 0x800CFF80;
const int  s12c_dword_800D9FB0 = 0x800CFF90;
const int  s12c_dword_800D9FB4 = 0x800D0298;
const int  s12c_dword_800D9FB8 = 0x800D0298;
const int  s12c_dword_800D9FBC = 0x800D0298;
const int  s12c_dword_800D9FC0 = 0x800D0298;
const int  s12c_dword_800D9FC4 = 0x800D0298;
const int  s12c_dword_800D9FC8 = 0x800D0298;
const int  s12c_dword_800D9FCC = 0x800D0298;
const int  s12c_dword_800D9FD0 = 0x800D0298;
const int  s12c_dword_800D9FD4 = 0x800D0298;
const int  s12c_dword_800D9FD8 = 0x800D0298;
const int  s12c_dword_800D9FDC = 0x800D0298;
const int  s12c_dword_800D9FE0 = 0x800D0298;
const int  s12c_dword_800D9FE4 = 0x800D0298;
const int  s12c_dword_800D9FE8 = 0x800D0298;
const int  s12c_dword_800D9FEC = 0x800D0298;
const int  s12c_dword_800D9FF0 = 0x800D0298;
const int  s12c_dword_800D9FF4 = 0x800D0298;
const int  s12c_dword_800D9FF8 = 0x800D0298;
const int  s12c_dword_800D9FFC = 0x800D0298;
const int  s12c_dword_800DA000 = 0x800D0298;
const int  s12c_dword_800DA004 = 0x800D0298;
const int  s12c_dword_800DA008 = 0x800D0298;
const int  s12c_dword_800DA00C = 0x800D0298;
const int  s12c_dword_800DA010 = 0x800D0298;
const int  s12c_dword_800DA014 = 0x800D0298;
const int  s12c_dword_800DA018 = 0x800D0298;
const int  s12c_dword_800DA01C = 0x800D0298;
const int  s12c_dword_800DA020 = 0x800D0298;
const int  s12c_dword_800DA024 = 0x800D0298;
const int  s12c_dword_800DA028 = 0x800D0298;
const int  s12c_dword_800DA02C = 0x800CFFBC;
const int  s12c_dword_800DA030 = 0x800CFFF4;
const int  s12c_dword_800DA034 = 0x800D00C8;
const int  s12c_dword_800DA038 = 0x800D011C;
const int  s12c_dword_800DA03C = 0x800D012C;
const int  s12c_dword_800DA040 = 0x800D020C;
const int  s12c_dword_800DA044 = 0x800D1B44;
const int  s12c_dword_800DA048 = 0x800D18C0;
const int  s12c_dword_800DA04C = 0x800D19C0;
const int  s12c_dword_800DA050 = 0x800D1A28;
const int  s12c_dword_800DA054 = 0x800D1AA4;
const int  s12c_dword_800DA058 = 0x800D1AFC;
const int  s12c_dword_800DA05C = 0x800D1B94;
const int  s12c_dword_800DA060 = 0x800D1BBC;
const int  s12c_dword_800DA064 = 0x800D1BD4;
const int  s12c_dword_800DA068 = 0x800D1BEC;
const int  s12c_dword_800DA06C = 0x800D1C0C;
const int  s12c_dword_800DA070 = 0x800D1C2C;
const int  s12c_dword_800DA074 = 0x800D1C54;
const int  s12c_dword_800DA078 = 0x800D1D14;
const int  s12c_dword_800DA07C = 0x800D1C8C;
const int  s12c_dword_800DA080 = 0x800D1CA4;
const int  s12c_dword_800DA084 = 0x800D1CDC;
const int  s12c_dword_800DA088 = 0x800D1CEC;
const int  s12c_dword_800DA08C = 0x800D1CFC;
const int  s12c_dword_800DA090 = 0x800D1D0C;
const int  s12c_dword_800DA094 = 0x800D1C40;
const char s12c_aHappy_800DA098[] = "happy";
const char s12c_aUnhappy_800DA0A0[] = "unhappy";
const char s12c_aTrap_800DA0A8[] = "trap";
const char s12c_dword_800DA0B0[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800DA0B4 = 0x800D203C;
const int  s12c_dword_800DA0B8 = 0x800D203C;
const int  s12c_dword_800DA0BC = 0x800D203C;
const int  s12c_dword_800DA0C0 = 0x800D203C;
const int  s12c_dword_800DA0C4 = 0x800D2038;
const int  s12c_dword_800DA0C8 = 0x800D203C;
const int  s12c_dword_800DA0CC = 0x800D2038;
const int  s12c_dword_800DA0D0 = 0x800D203C;
const int  s12c_dword_800DA0D4 = 0x800D2038;
const int  s12c_dword_800DA0D8 = 0x800D2038;
const int  s12c_dword_800DA0DC = 0x800D2038;
const int  s12c_dword_800DA0E0 = 0x800D2038;
const int  s12c_dword_800DA0E4 = 0x800D2038;
const int  s12c_dword_800DA0E8 = 0x800D2038;
const int  s12c_dword_800DA0EC = 0x800D2038;
const char s12c_aWolfdog_800DA0F0[] = "wolfdog";
const char s12c_aWolfdog_800DA0F8[] = "wolfdog2";
const char s12c_aShadow_800DA104[] = "shadow";
const char s12c_aDoglow_800DA10C[] = "dog_low";

extern GV_PAD           GV_PadData_800B05C0[4];

void *AN_Unknown_800CA1EC(MATRIX *mat, int mark);
void *AN_Unknown_800CA320(MATRIX *mat, int mark);

void Dog_800C9E4C(DogWork *work, int index)
{
    int mod;

    mod = work->field_155C[index] % 32;
    switch (index)
    {
    case 0:
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_28[0].mov, 0xA0, GM_SEMODE_NORMAL);
        }
        else if (mod == 15)
        {
            GM_SeSetMode(&work->field_28[0].mov, 0xA1, GM_SEMODE_NORMAL);
        }
        break;
    case 1:
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_28[1].mov, 0xA2, GM_SEMODE_NORMAL);
        }
        else if (mod == 15)
        {
            GM_SeSetMode(&work->field_28[1].mov, 0xA3, GM_SEMODE_NORMAL);
        }
        break;
    case 2:
        if (mod == 0 || mod == 15)
        {
            GM_SeSetMode(&work->field_28[2].mov, 0xA6, GM_SEMODE_NORMAL);
        }
        else if (mod == 7 || mod == 23)
        {
            GM_SeSetMode(&work->field_28[2].mov, 0xA7, GM_SEMODE_NORMAL);
        }
        break;
    }
}

void Dog_800C9F48(DogWork *work, int index)
{
    if (work->field_155C[index] & 7)
    {
        return;
    }

    switch (index)
    {
    case 0:
        GM_SeSetMode(&work->field_28[0].mov, 0xA4, GM_SEMODE_NORMAL);
        break;
    case 1:
        GM_SeSetMode(&work->field_28[1].mov, 0xA5, GM_SEMODE_NORMAL);
        break;
    }
}

void Dog_800C9FAC(DogWork *work, int index)
{
    work->field_15BC[index] = 0;
    DG_InvisiblePrim(work->field_167C[index]);
    DG_InvisibleObjs(work->field_19C[index].objs);
}

void Dog_800CA000(DogWork *work, int index)
{
    work->field_15BC[index] = 1;
    DG_VisiblePrim(work->field_167C[index]);
    DG_VisibleObjs(work->field_19C[index].objs);
}

void Dog_800CA058(DogWork *work)
{
    if (work->field_1774 > 0)
    {
        GM_PadVibration = 1;
        GM_PadVibration2 = 0xFF;
        work->field_1774--;
    }
    else
    {
        work->field_1774 = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA098.s")

// Duplicate of d03a_red_alrt_800C437C
int Dog_800CA3C0(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA458.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA4B4.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA758.s")

void Dog_800CA93C(DogWork *work)
{
    if (GV_PadData_800B05C0->press != 0)
    {
        work->field_1600++;
    }
    else
    {
        work->field_1600 = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA96C.s")

int Dog_800CAB34(DogWork *work, int arg1)
{
    if (arg1 == 0 || (arg1 == 1 && work->field_1528 < 2000))
    {
        return 1;
    }
    return 0;
}

void Dog_800CAB68(DogWork *work, int index, int hp)
{
    TARGET *target;

    if (GM_PlayerStatus & (PLAYER_NOT_PLAYABLE | PLAYER_DAMAGED | PLAYER_INVINCIBLE))
    {
        return;
    }

    target = &work->field_1194[index];
    target->field_26_hp = hp;
    target->field_2C_vec.vx = GV_RandU(32);
    target->field_2C_vec.vy = GV_RandU(32);
    target->field_2C_vec.vz = GV_RandU(32);
    GM_MoveTarget(target, &GM_PlayerPosition);
    GM_PowerTarget(target);
}

int Dog_800CABF4(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR sp10;
    int     vy;
    int     len;

    GV_SubVec3(arg1, arg0, &sp10);
    arg2->vy = ratan2(sp10.vx, sp10.vz) & 0xFFF;
    vy = sp10.vy;
    sp10.vy = 0;
    len = GV_VecLen3(&sp10);
    arg2->vx = (ratan2(len, vy) & 0xFFF) - 0x400;
    arg2->vz = 0;
    return len;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CAC84.s")
int s12c_dog_800CAC84(DogWork *work, int, int);

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CAD8C.s")

void s12c_dog_800CAEC8(DogWork *work, int index, int mark)
{
    CONTROL *control;

    if (work->field_14B8[index] <= 0)
    {
        work->field_14B8[index] = 0x3C;
        switch (index)
        {
        case 0:
            AN_Unknown_800CA1EC(&work->field_19C[0].objs->objs[5].world, mark);
            control = &work->field_28[0];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0x84);
            }
            break;
        case 1:
            AN_Unknown_800CA1EC(&work->field_19C[1].objs->objs[5].world, mark);
            control = &work->field_28[1];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0xBB);
            }
            break;
        case 2:
            AN_Unknown_800CA320(&work->field_19C[2].objs->objs[5].world, mark);
            control = &work->field_28[2];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0xBC);
            }
            break;
        }
    }
}

void Dog_800CAFB0(DogWork *work, int index)
{
    SVECTOR svec1;
    SVECTOR svec2;
    TARGET *target1;
    TARGET *target2;

    if (index == 2)
    {
        svec1.vx = 300;
        svec1.vy = 1000;
        svec1.vz = 300;
        svec2.vx = 40;
        svec2.vy = 200;
        svec2.vz = 40;
    }
    else
    {
        svec1.vx = 500;
        svec1.vy = 1000;
        svec1.vz = 500;
        svec2.vx = 500;
        svec2.vy = 500;
        svec2.vz = 500;
    }
    target1 = work->field_1188[index];
    GM_SetTarget(target1, 0x1D, 2, &svec1);
    GM_Target_8002DCCC(target1, 1, -1, work->unk14B4, 0xFF, &DG_ZeroVector);

    target2 = &work->field_1194[index];
    GM_SetTarget(target2, 4, 2, &svec2);
    GM_Target_8002DCCC(target2, 0, 2, 0, 0, &DG_ZeroVector);
}

void Dog_800CB0C8(int *arg0, int arg1, int arg2)
{
    *arg0 = ((*arg0 * (arg2 - 1)) + arg1) / arg2;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CB114.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CB180.s")

void Dog_800CB23C(DogWork *work, int arg1, int field_1510, int index)
{
    if (work->field_1494[index] != arg1)
    {
        s12c_dog_800CAC84(work, index, arg1);
        work->field_1494[index] = arg1;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg1], 0, 4);
    }
    else if (work->field_19C[index].is_end == 1)
    {
        if (work->field_1494[index] != 13)
        {
            work->field_14EC[index] = -1;
        }
        else
        {
            work->field_14EC[index] = 0;
        }
        work->field_1510[index] = field_1510;
    }
}

void Dog_800CB324(DogWork *work, int arg1, int arg2, int field_1510, int index)
{
    if (work->field_1494[index] != arg1)
    {
        work->field_1494[index] = arg1;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg1], 0, 4);
    }
    else if (work->field_19C[index].is_end == 1)
    {
        if (work->field_1494[index] != 13)
        {
            work->field_14EC[index] = -1;
        }
        else
        {
            work->field_14EC[index] = 0;
        }
        work->field_1494[index] = arg2;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg2], 0, 4);
        work->field_1510[index] = field_1510;
    }
}

void s12c_dog_800CB42C(DogWork *work, int index1, int arg2, int arg3, int index2, unsigned int arg5)
{
    int temp_a0;

    temp_a0 = work->field_1494[index2];
    if (temp_a0 != index1)
    {
        s12c_dog_800CAC84(work, index2, index1);
        work->field_1494[index2] = index1;
        GM_ConfigObjectAction(&work->field_19C[index2], work->field_1698[index1], 0, 4);
    }
    else if (work->field_19C[index2].is_end == 1)
    {
        if (temp_a0 != 13)
        {
            work->field_14EC[index2] = -1;
        }
        else
        {
            work->field_14EC[index2] = 0;
        }
        if (GV_RandU(arg5) != 0)
        {
            work->field_1510[index2] = arg2;
        }
        else
        {
            work->field_1510[index2] = arg3;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CB54C.s")

void Dog_800CB6DC(DogWork *work, int arg1, int arg2)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (work->field_14F8[i] != 9)
        {
            work->field_14F8[i] = arg1;
            work->field_1510[i] = arg2;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CB714.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CB97C.s")

void Dog_800CBBE8(DogWork *work, int index)
{
    MATRIX  rot;
    SVECTOR pos;

    DG_SetPos(&GM_PlayerBody->objs[1].world);

    pos.vx = GV_RandU(0x800U);
    pos.vy = GV_RandU(0x1000U);
    pos.vz = 0;

    DG_RotatePos(&pos);

    ReadRotMatrix(&rot);
    NewBlood(&rot, 2);

    if (GV_RandU(16) == 0)
    {
        if (GV_RandU(2))
        {
            GM_SeSet(&work->field_28[index].mov, 0xB3);
        }
        else
        {
            GM_SeSet(&work->field_28[index].mov, 0xB4);
        }
    }
    else if (GV_RandU(2))
    {
        GM_SeSet(&work->field_28[index].mov, 0xB9);
    }
    else
    {
        GM_SeSet(&work->field_28[index].mov, 0xBA);
    }
}

void Dog_800CBCF4(DogWork *work, int arg1)
{
    MATRIX  rot;
    SVECTOR svec;

    DG_SetPos(&work->field_19C[arg1].objs->objs[6].world);

    svec.vx = GV_RandU(0x800);
    svec.vy = GV_RandU(0x1000);
    svec.vz = 0;
    DG_RotatePos(&svec);

    ReadRotMatrix(&rot);
    NewBlood(&rot, 2);

    if (GV_RandU(2) != 0)
    {
        GM_SeSetMode(&work->field_28[arg1].mov, 0xB9, GM_SEMODE_NORMAL);
    }
    else
    {
        GM_SeSetMode(&work->field_28[arg1].mov, 0xBA, GM_SEMODE_NORMAL);
    }

    work->field_1610 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CBDC4.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC180.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC53C.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC8B4.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CCC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CDBC4.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CE034.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CE194.s")

void DogExecProc_800CEB2C(DogWork *work, int param)
{
    GCL_ARGS args;
    long     data[1];

    data[0] = work->field_17B4;

    args.argc = 1;
    args.argv = data;

    if (work->field_17B0 != -1)
    {
        GCL_ForceExecProc(work->field_17B0, &args);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CEB74.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CF578.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CF6CC.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CFA30.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0374.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0680.s")

int Dog_800D0BC4(DogWork *work)
{
    int i;

    if (!(GM_GameStatus & STATE_STUN))
    {
        return 0;
    }

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        if ((work->field_14F8[i] < 8 || work->field_14F8[i] > 9) && work->field_14F8[i] != 12 &&
            work->field_14F8[i] != 13 && work->field_14F8[i] != 10 && work->field_14F8[i] != 11)
        {
            work->field_158C[i] = 200;
            work->field_14F8[i] = 4;
            work->field_1510[i] = 0;
        }
    }
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0C78.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0F30.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D11D4.s")

void Dog_800D1638(DogWork *work, int obj_index, int blood_count, int index)
{
    MATRIX rot;

    DG_SetPos(&work->field_19C[index].objs->objs[obj_index].world);
    DG_MovePos(&s12c_dword_800C3450);
    DG_RotatePos(&s12c_dword_800C3458);
    ReadRotMatrix(&rot);
    NewBlood(&rot, blood_count);
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D16C0.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D187C.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D1B54.s")

// Modified s00a_watcher_800C4138
void Dog_800D1D24(DG_OBJS *objs, DG_DEF *def)
{
    int     i;
    DG_OBJ *obj;
    DG_FreeObjsPacket(objs, 0);
    DG_FreeObjsPacket(objs, 1);

    objs->def = def;
    obj = objs->objs;
    for (i = 0; i < 18; i++)
    {
        obj->model = &def->model[i];
        obj->n_packs = def->model[i].n_faces;
        obj++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D1DA0.s")
void s12c_dog_800D1DA0(DogWork *work);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D20A0.s")

void DogDie_800D2798(DogWork *work)
{
    // https://i.kym-cdn.com/photos/images/newsfeed/001/464/596/d38.jpg
    int i;

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        GM_FreeControl(&work->field_28[i]);
        GM_FreeObject(&work->field_19C[i]);
        GM_FreePrim(work->field_167C[i]);
        GM_FreeTarget(work->field_1188[i]);
        GM_FreeHomingTarget(work->field_126C[i]);
    }
}

// Duplicate of Eventmouse_800C9890
void Dog_800D2864(POLY_FT4 *poly, DG_TEX *tex)
{
    int x, y, w, h;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(poly, x, y, w, h);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

int DogGetSvec_800D28C4(char *opt, SVECTOR *out)
{
    char *res;

    res = GCL_GetParamResult();

    if (res == NULL)
    {
        return 0;
    }

    GCL_StrToSV(res, out);
    return 1;
}

// Duplicate of UjiGetInts_800C3A3C
int DogGetInts_800D2904(char *opt, int *out)
{
    int   count;
    int  *out2;
    char *result;

    count = 0;
    out2 = out;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        *out2++ = GCL_StrToInt(result);
        count++;
    }

    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D295C.s")
int s12c_dog_800D295C(DogWork *work, int, int);

void *NewDog_800D33C8(int arg0, int arg1)
{
    DogWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(DogWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s12c_dog_800D1DA0, DogDie_800D2798, "dog.c");
        if (s12c_dog_800D295C(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
