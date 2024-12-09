#include "meryl72.h"
#include "Game/linkvarbuf.h"

extern SVECTOR DG_ZeroVector;
extern int     GM_GameStatus;

extern unsigned short GM_WeaponTypes_8009D580[];
extern unsigned short GM_ItemTypes_8009D598[];
extern SVECTOR        GM_PlayerPosition_800ABA10;

extern SVECTOR meryl72_800D52F8;
extern int     meryl72_800D5300;

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CECB4.s")
int s07c_meryl72_unk2_800CECB4(SVECTOR *arg1);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CECEC.s")
void s07c_meryl72_unk2_800CECEC(Meryl72Work *work, int arg2);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CED24.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEE88.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEEDC.s")

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEF58.s")
void s07c_meryl72_unk2_800CEF58(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEF98.s")
void s07c_meryl72_unk2_800CEF98(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF060.s")
void s07c_meryl72_unk2_800CF060(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF144.s")
void s07c_meryl72_unk2_800CF144(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF2A4.s")
void s07c_meryl72_unk2_800CF2A4(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF3AC.s")
void s07c_meryl72_unk2_800CF3AC(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF4C0.s")
void s07c_meryl72_unk2_800CF4C0(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF568.s")
void s07c_meryl72_unk2_800CF568(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF67C.s")
void s07c_meryl72_unk2_800CF67C(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF824.s")
void s07c_meryl72_unk2_800CF824(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF9E0.s")
void s07c_meryl72_unk2_800CF9E0(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFA28.s")
void s07c_meryl72_unk2_800CFA28(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFA98.s")
void s07c_meryl72_unk2_800CFA98(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFB14.s")
void s07c_meryl72_unk2_800CFB14(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFBBC.s")
void s07c_meryl72_unk2_800CFBBC(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFC54.s")
void s07c_meryl72_unk2_800CFC54(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFCA4.s")
void s07c_meryl72_unk2_800CFCA4(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CFD0C.s")
void s07c_meryl72_unk2_800CFD0C(Meryl72Work *work);

void s07c_meryl72_unk2_800CFD80(Meryl72Work *work)
{
    switch (work->fAC0)
    {
    case 0:
        s07c_meryl72_unk2_800CEF58(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF4C0(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CF9E0(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFC54(work);
        break;
    }

    if (s07c_meryl72_unk2_800CECB4(&GM_PlayerPosition_800ABA10))
    {
        work->fABC = 1;
        work->fABE = 0;
        work->fAC0 = 0;

        // Unequip item if it changes camera
        if (GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 0x2)
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        // Unequip weapon if it changes camera
        if (GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200)
        {
            GM_CurrentWeaponId = WEAPON_NONE;
        }

        work->fC38 = 0;
        work->fAC4 = 0;
        work->fC04 = 0;

        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY | GAME_FLAG_BIT_07;
        s07c_meryl72_unk2_800CECEC(work, 0);
    }
}

void s07c_meryl72_unk2_800CFED0(Meryl72Work *work)
{
    switch (work->fAC0)
    {
    case 0:
        s07c_meryl72_unk2_800CEF98(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CFA28(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFCA4(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF568(work);
        break;
    }
}

void s07c_meryl72_unk2_800CFF64(Meryl72Work *work)
{
    switch (work->fAC0)
    {
        case 6:
            s07c_meryl72_unk2_800CF060(work);
            break;

        case 2:
            s07c_meryl72_unk2_800CFB14(work);
            break;

        case 3:
            s07c_meryl72_unk2_800CFD0C(work);
            break;

        case 7:
            s07c_meryl72_unk2_800CF144(work);
            break;

        case 8:
            s07c_meryl72_unk2_800CF2A4(work);
            break;

        case 9:
            s07c_meryl72_unk2_800CF3AC(work);
            break;
    }
}

void s07c_meryl72_unk2_800D0010(Meryl72Work *work)
{
    switch (work->fAC0)
    {
    case 2:
        s07c_meryl72_unk2_800CFA98(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFBBC(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF824(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CF67C(work);
        break;
    }
}

void s07c_meryl72_unk2_800D00A4(Meryl72Work *work)
{
    if (work->fABE == 0)
    {
        s07c_meryl72_unk2_800CFD80(work);
    }
}

void s07c_meryl72_unk2_800D00D4(Meryl72Work *work)
{
    if (work->fABE == 0)
    {
        s07c_meryl72_unk2_800CFED0(work);
    }
}

void s07c_meryl72_unk2_800D0104(Meryl72Work *work)
{
    switch (work->fABE)
    {
    case 2:
        s07c_meryl72_unk2_800D0010(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFF64(work);
        break;
    }
}

void s07c_meryl72_unk2_800D0154(Meryl72Work *work)
{
    int i;

    work->pad.dir = -1;
    work->pad.press = 0;

    switch (work->fABC)
    {
    case 0:
        s07c_meryl72_unk2_800D00A4(work);
        break;

    case 1:
        s07c_meryl72_unk2_800D00D4(work);
        break;

    case 2:
        s07c_meryl72_unk2_800D0104(work);
        break;
    }

    for (i = 0; i < 3; i++)
    {
        if (--work->fC10[i] < 0)
        {
            work->fC10[i] = 0;
        }
    }

    work->fC38++;
}

void s07c_meryl72_unk2_800D0220(void)
{
    meryl72_800D52F8 = DG_ZeroVector;
    meryl72_800D5300 = 0;
}

void s07c_meryl72_unk2_800D025C(void)
{
}
