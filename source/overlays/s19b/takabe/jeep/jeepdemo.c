#include "game/game.h"
#include "takabe/cinema.h"

typedef struct _Bytes8
{
    char b[8];
} Bytes8;

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3a[0x4C - 0x20];
    int      field_4C;
    char     pad3b[0x54 - 0x4C - sizeof(int)];
    int      field_54;
    char     pad4[0x8];
    OBJECT  *body;
    char     pad5a[0x6C - 0x64];
    int     *field_6C;
    int     *field_70;
    char     pad5b[0x7C - 0x70 - sizeof(int *)];
    int      field_7C;
    MATRIX   world;
    char     pad6[0x88];
    int      field_128;
    char     pad7[0x130 - 0x128 - sizeof(int)];
    int      field_130;
    char     pad8[0x138 - 0x130 - sizeof(int)];
    int      field_138;
    char     pad9[0x140 - 0x138 - sizeof(int)];
    int      field_140;
    char     pad10[0x148 - 0x140 - sizeof(int)];
    int      field_148;
    char     pad11[0x150 - 0x148 - sizeof(int)];
    int      field_150;
    Bytes8   field_154;
    int      field_15C;
    Bytes8   field_160;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

typedef struct _Work
{
    GV_ACT actor;
    char   pad1[0x40 - 0x20];
    void  *field_40;
    void  *field_44;
    char   pad2[0x4C - 0x44 - sizeof(void *)];
    int    field_4C;
} Work;

typedef struct _JeepCamParams
{
    short field_0;
    short field_2;
    short field_4;
    short field_6;
    int   field_8;
    int   field_C;
    int   field_10;
    int   field_14;
    int   field_18;
} JeepCamParams; /* 0x1C, at 0x800DE5C8 */

extern JeepCamParams s19b_JeepCamParams_800DE5C8;
extern void s19b_jlamp_800D0C44(void);

void s19b_jlamp_800D0648(SVECTOR *from, SVECTOR *to, SVECTOR *ang, int *len)
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    *len = GV_VecLen3(&diff);

    ang->vz = 0;
    ang->vy = GV_VecDir2(&diff);
    ang->vx = ratan2(-diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
}

void s19b_jlamp_800D06E0(Work *work)
{
    NewCinemaScreen(300, 0);
    work->field_44 = &Takabe_JeepSystem.field_128;
    Takabe_JeepSystem.field_54 |= 0x10000000;
}

extern void Voicesys_800CE2D0(void);

extern int s19b_dword_800C3760;
extern int s19b_dword_800C3768;

void s19b_jlamp_800D072C(Work *work)
{
    Takabe_JeepSystem.field_4C |= 0x10000;
    work->field_40 = &Takabe_JeepSystem.field_140;
    Takabe_JeepSystem.field_150 = *Takabe_JeepSystem.field_6C;
    Takabe_JeepSystem.field_154 = *(Bytes8 *)&s19b_dword_800C3760;
    work->field_44 = &Takabe_JeepSystem.field_148;
    Takabe_JeepSystem.field_15C = *Takabe_JeepSystem.field_70;
    Takabe_JeepSystem.field_160 = *(Bytes8 *)&s19b_dword_800C3768;
    GM_SeSet(NULL, 0xC4);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D07EC.s")
extern int s19b_dword_800DE5B8;

void s19b_jlamp_800D087C(void)
{
    GV_DestroyActorQuick((GV_ACT *)s19b_dword_800DE5B8);
    Takabe_JeepSystem.field_4C = (Takabe_JeepSystem.field_4C & ~0x10000) | 0x20000;
}
void s19b_jlamp_800D08C8(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_128;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D08F0(void)
{
    GM_GameStatus &= ~0x40000000;
    Takabe_JeepSystem.field_54 &= ~0x10000000;
}
void s19b_jlamp_800D0928(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_130;
    Takabe_JeepSystem.field_4C |= 0x40000;
}
void s19b_jlamp_800D094C(void)
{
    NewCinemaScreen(270, 0);
}

void s19b_jlamp_800D0970(void)
{
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D0990(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_138;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D09B8(Work *work)
{
    work->field_44 = NULL;
    Takabe_JeepSystem.field_4C &= ~0x40000;
}
void s19b_jlamp_800D09DC(void)
{
    GM_SeSet(NULL, 0xB5);
    GM_SetSound(0x01FFFF0B, 0);
    GM_SetSound(0xFF0000FE, 0);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0A20.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0ABC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0C44.s")
void s19b_jlamp_800D0CE0(void)
{
    s19b_JeepCamParams_800DE5C8.field_0 = 0;
    s19b_JeepCamParams_800DE5C8.field_2 = 0x5DC;
    s19b_JeepCamParams_800DE5C8.field_4 = 0x7D0;
    s19b_JeepCamParams_800DE5C8.field_C = 0x7D0;
    s19b_JeepCamParams_800DE5C8.field_8 = 0;
    s19b_JeepCamParams_800DE5C8.field_10 = 0x5DC;
    s19b_JeepCamParams_800DE5C8.field_14 = 0;
    s19b_JeepCamParams_800DE5C8.field_18 = 0;
    GM_SetCameraCallbackFunc(1, s19b_jlamp_800D0C44);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0D40.s")

void s19b_jlamp_800D0FE4(int arg0)
{
    s19b_JeepCamParams_800DE5C8.field_8 = arg0;
}
