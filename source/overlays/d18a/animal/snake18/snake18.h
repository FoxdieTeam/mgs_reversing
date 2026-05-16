#ifndef __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__
#define __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "game/control.h"
#include "game/target.h"

typedef struct _Snake18Type
{
    char *str;
    char *str2;
} Snake18Type;

typedef struct _Snake18Work
{
    GV_ACT  actor;       // 0x000
    CONTROL control;     // 0x020
    OBJECT  body;        // 0x09C
    char    pad_184[0x184 - 0x09C - sizeof(OBJECT)];
    SVECTOR f184;        // 0x184
    int     f18C;        // 0x18C
    char    pad_19C[0x19C - 0x18C - sizeof(int)];
    SVECTOR f19C;        // 0x19C
    int     f1A4;        // 0x1A4
    char    pad_1B0[0x1B0 - 0x1A4 - sizeof(int)];
    short   f1B0;        // 0x1B0
    char    pad_1C0[0x1C0 - 0x1B0 - sizeof(short)];
    int     f1C0;        // 0x1C0
    char    pad_7E4[0x7E4 - 0x1C0 - sizeof(int)];
    int     f7E4;        // 0x7E4
    short  *f7E8;        // 0x7E8 (pointer slot, used by 800CC8E0 etc.)
    TARGET  f7EC;        // 0x7EC
    char    pad_834[0x834 - 0x7EC - sizeof(TARGET)];
    int     f834;        // 0x834
    char    pad_840[0x840 - 0x834 - sizeof(int)];
    int    *f840;        // 0x840
    char    pad_848[0x848 - 0x840 - sizeof(int *)];
    SVECTOR f848;        // 0x848
    char    pad_854[0x854 - 0x848 - sizeof(SVECTOR)];
    int     f854;        // 0x854
    int     f858;        // 0x858
    int     f85C;        // 0x85C
    short  *f860;        // 0x860
    int     f864;        // 0x864
    char    pad_868[0x868 - 0x864 - sizeof(int)];
    int     f868;        // 0x868
    short   f86C;        // 0x86C
    short   f86E;        // 0x86E
    char    pad_8A4[0x8A4 - 0x86E - sizeof(short)];
    short  *f8A4;        // 0x8A4
    Snake18Type *f8A8;   // 0x8A8
    void   *f8AC;        // 0x8AC (callback pointer)
    int     f8B0;        // 0x8B0
    void   *f8B4;        // 0x8B4 (callback pointer)
    int     f8B8;        // 0x8B8
    void   *f8BC;        // 0x8BC (callback pointer)
    void   *f8C0;        // 0x8C0 (callback pointer)
    char    pad_8C8[0x8C8 - 0x8C0 - sizeof(void *)];
    short   f8C8;        // 0x8C8
    char    pad_8CC[0x8CC - 0x8C8 - sizeof(short)];
    short   f8CC;        // 0x8CC
    char    pad_8D0[0x8D0 - 0x8CC - sizeof(short)];
    short   f8D0;        // 0x8D0
    char    pad_8F8[0x8F8 - 0x8D0 - sizeof(short)];
    short   f8F8;        // 0x8F8
    char    pad_8FC[0x8FC - 0x8F8 - sizeof(short)];
    char    f8FC;        // 0x8FC
    char    pad_900[0x900 - 0x8FC - sizeof(char)];
    short   f900;        // 0x900
    char    pad_90C[0x90C - 0x900 - sizeof(short)];
    char    f90C;        // 0x90C
    char    f90D;        // 0x90D
    char    f90E;        // 0x90E
    char    pad_910[0x910 - 0x90E - sizeof(char)];
    short   f910;        // 0x910
    short   f912;        // 0x912
    char    pad_930[0x930 - 0x912 - sizeof(short)];
    int     f930;        // 0x930
} Snake18Work;

#endif // __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__
