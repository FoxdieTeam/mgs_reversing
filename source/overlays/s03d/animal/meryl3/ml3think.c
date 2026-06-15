#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    char            pad_0[0x20];
    SVECTOR         field_20;       /* 0x020 */
    char            pad_28[0x4C - 0x28];
    MAP            *field_4C;       /* 0x04C */
    char            pad_50[0x5A - 0x50];
    short           field_5A;       /* 0x05A */
    char            pad_5C[0x9C - 0x5C];
    char           *field_9C;       /* 0x09C */
    char            pad_A0[0xB6 - 0xA0];
    short           field_B6;       /* 0x0B6 */
    char            pad_B8[0x8E4 - 0xB8];
    short           field_8E4;      /* 0x8E4 */
    char            pad_8E6[0xAC8 - 0x8E6];
    short           field_AC8;      /* 0xAC8 */
    short           field_ACA;      /* 0xACA */
    short           field_ACC;      /* 0xACC */
    char            pad_ACE[0xAD0 - 0xACE];
    int             field_AD0;      /* 0xAD0 */
    char            pad_AD4[0xAD8 - 0xAD4];
    int             field_AD8;      /* 0xAD8 */
    int             field_ADC;      /* 0xADC */
    char            pad_AE0[0xAE6 - 0xAE0];
    short           field_AE6;      /* 0xAE6 */
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xB04 - 0xAEA];
    int             field_B04;      /* 0xB04 */
    signed char     field_B08;      /* 0xB08 */
    char            pad_B09[0xB0B - 0xB09];
    signed char     field_B0B;      /* 0xB0B */
    unsigned char   field_B0C[0xB26 - 0xB0C];   /* 0xB0C */
    short           field_B26;      /* 0xB26 */
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB48 - 0xB2C];
    SVECTOR         field_B48;      /* 0xB48 */
    char            pad_B50[0xB58 - 0xB50];
    int             field_B58;      /* 0xB58 */
    int             field_B5C;      /* 0xB5C */
    int             field_B60;      /* 0xB60 */
    int             field_B64;      /* 0xB64 */
    SVECTOR         field_B68;      /* 0xB68 */
    int             field_B70;      /* 0xB70 */
    char            pad_B74[0xB90 - 0xB74];
    int             field_B90;      /* 0xB90 */
    unsigned short  field_B94;      /* 0xB94 */
} Work;

void s03d_800D3F14(void *dest, SVECTOR *pos, const char *name, int flag);
void s03d_800D2CCC(Work *work);
void ZakoCom_800D4088(void);

int s03d_800D3184(Work *work);
void s03d_800D367C(Work *work);
void s03d_800D2C68(Work *work);
void s03d_800D3ACC(Work *work);
void s03d_800D0C90(Work *work, int arg);
int s03d_800D2DBC(Work *work);

extern int s03d_dword_800C3B68;
extern int s03d_dword_800DC2F8;
extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern int s03d_dword_800DC308;
extern int s03d_dword_800DC32C;

const char s03d_dword_800DBAB0[] = {'k', 'i', 'r', 'a'};
const char s03d_dword_800DBAB4[] = {'r', 'i', '0', '1'};
const char s03d_dword_800DBAB8[] = {0x0, 0x0, 0x0, 0x0};
const char s03d_dword_800DBABC[] = {0x0, 0x0, 0x0, 0x0};

void s03d_800D2C20(Work *work)
{
    work->field_B5C = s03d_dword_800DC2FC;
    work->field_B48 = *(SVECTOR *)&s03d_dword_800DC308;
    work->field_B60 = s03d_dword_800DC300;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2C68.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2CCC.s")
void s03d_800D2D44(Work *work)
{
    work->field_ACA = 2;
    work->field_ACC = 9;
    work->field_AC8 = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
}
void s03d_800D2D68(Work *work)
{
    work->field_AC8 = 0;
    work->field_ACA = 0;
    work->field_ACC = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
}
int s03d_800D2D84(SVECTOR *a, SVECTOR *b)
{
    SVECTOR diff;

    GV_SubVec3(b, a, &diff);
    diff.vy = 0;
    return GV_VecDir2(&diff);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2DBC.s")
int s03d_800D307C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        s03d_800D0C90(work, 0);
        GM_SeSet(&work->field_20, 0x53);
        s03d_800D3F14(work->field_9C + 0x270, &work->field_20, s03d_dword_800DBAB0, 0);
    }
    if (work->field_AD0 < 20)
    {
        work->field_AD8 |= 0x20;
        work->field_AD0++;
        return 0;
    }
    return 1;
}
int s03d_800D311C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        GM_SeSet(&work->field_20, 0x53);
        s03d_800D0C90(work, 0);
    }
    if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3184.s")
int s03d_800D31F4(Work *work, int range)
{
    SVECTOR local;
    int dx = work->field_B48.vx - work->field_20.vx;
    int dz;

    local.vx = dx;
    dz = work->field_B48.vz - work->field_20.vz;
    local.vz = dz;
    if (-range < dx && dx < range && -range < dz && dz < range)
    {
        return 1;
    }
    work->field_AE6 = GV_VecDir2(&local);
    work->field_AD0++;
    return 0;
}
int s03d_800D327C(Work *work)
{
    s03d_800D2C20(work);
    if (work->field_4C->index != work->field_B60)
    {
        return -1;
    }
    if (work->field_AD0 & 0x10)
    {
        work->field_B70 = HZD_GetAddress(work->field_4C->hzd, &work->field_20, -1);
        if (HZD_ReachTo(work->field_4C->hzd, work->field_B70, work->field_B5C) >= 2)
        {
            return -1;
        }
    }
    return s03d_800D31F4(work, 0x5DC);
}
int s03d_800D3310(Work *work)
{
    if (work->field_B08 == 2)
    {
        work->field_AD8 |= 0x20000;
    }
    else
    {
        work->field_AD8 |= 0x10000;
    }
    if (work->field_AD0 < 4)
    {
        if ((work->field_AD0 & 1) != 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}
int s03d_800D3390(Work *work)
{
    work->field_AD8 |= 0x20000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x80000;
    }
    else if (work->field_AD0 == 8)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
int s03d_800D33E8(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 30)
    {
        work->field_AD8 |= 0x100000;
        work->field_B68 = ((SVECTOR *)&s03d_dword_800C3B68)[work->field_B08];
    }
    else if (work->field_B6 != 0)
    {
        return 1;
    }
    work->field_AE6 = s03d_800D2D84(&work->field_20, &((SVECTOR *)&s03d_dword_800C3B68)[work->field_B08]);
    work->field_AD0++;
    return 0;
}
int s03d_800D34AC(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x200000;
    }
    else if (work->field_B6 != 0)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
int s03d_800D3508(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 < 10)
    {
        if ((work->field_AD0 & 1) == 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 20)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
int s03d_800D3570(Work *work)
{
    if (work->field_B08 == 2)
    {
        work->field_AD8 |= 0x20000;
    }
    else
    {
        work->field_AD8 |= 0x10000;
    }
    work->field_AE6 = work->field_B94;
    if (s03d_dword_800DC2F8 < 7)
    {
        if (s03d_dword_800DC2F8 >= 4)
        {
            return 0;
        }
    }
    if (work->field_AD0 == 0x10)
    {
        work->field_AD0 += GV_RandU(0xE);
    }
    if (work->field_AD0 >= 0x21)
    {
        if (work->field_B64 < 0xBB9 && (GM_PlayerStatus & 2))
        {
            return 9;
        }
        if (work->field_B90 < 0x3E8 && !(GM_PlayerStatus & 0x1060))
        {
            return 0xA;
        }
        return 6;
    }
    work->field_AD0++;
    return 0;
}
void s03d_800D367C(Work *work)
{
    switch (s03d_dword_800DC2F8)
    {
    case 9:
        if (work->field_B04 >= 0xF)
        {
            break;
        }
        /* fallthrough */
    case 8:
        if (work->field_AD0 < 0x1F)
        {
            break;
        }
        /* fallthrough */
    case 0:
    case 4:
    case 5:
    case 7:
    case 12:
        s03d_800D2CCC(work);
        work->field_AD0 = 0;
        return;
    case 10:
        s03d_800D2D44(work);
        work->field_AD0 = 0;
        return;
    }
    work->field_AD0++;
}
const char s03d_dword_800DBAF4[] = {0x0, 0x0, 0x0, 0x0};


void s03d_800D3724(Work *work)
{
    if (work->field_ACC == 0)
    {
        s03d_800D367C(work);
    }
}
void s03d_800D3754(Work *work)
{
    switch (work->field_ACC)
    {
    case 1:
        if (s03d_800D307C(work) != 0)
        {
            s03d_800D2CCC(work);
            if (s03d_dword_800DC32C != 0)
            {
                work->field_AE8 = 0xF6;
            }
            else
            {
                work->field_AE8 = 0xF0;
            }
            work->field_B28 = 0xFF;
        }
        break;
    case 2:
        if (s03d_800D311C(work) != 0)
        {
            work->field_ACA = 3;
            work->field_ACC = 0xD;
            work->field_ADC = 1;
            work->field_AE8 = 0xF0;
            work->field_AC8 = 0;
            work->field_AD0 = 0;
            work->field_B28 = 0xFF;
        }
        break;
    case 3:
        if (s03d_800D311C(work) != 0)
        {
            s03d_800D2CCC(work);
            work->field_AE8 = 0xF0;
            work->field_B28 = 0xFF;
        }
        break;
    }
}
void s03d_800D3848(Work *work)
{
    switch (work->field_ACC)
    {
    case 6:
        if (s03d_800D3310(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 7:
        if (s03d_800D3390(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 9:
        if (s03d_800D33E8(work) != 0)
        {
            s03d_800D2D68(work);
            work->field_AD0 = 0;
        }
        break;
    case 10:
        if (s03d_800D34AC(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 11:
        if (s03d_800D3508(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 12:
    {
        int r = s03d_800D3570(work);

        if (r != 0)
        {
            work->field_ACC = r;
            work->field_AD0 = 0;
        }
        if (work->field_B26 != 2)
        {
            if (HZD_InsideZone(work->field_4C->hzd, &work->field_20, work->field_B0C[work->field_B0B]) == 0)
            {
                s03d_800D2CCC(work);
            }
        }
        break;
    }
    }
    if (work->field_B26 == 2)
    {
        ZakoCom_800D4088();
        work->field_B28 = 0xFF;
    }
}
const char s03d_dword_800DBB14[] = {0x0, 0x0, 0x0, 0x0};


void s03d_800D3984(Work *work)
{
    switch (work->field_ACC)
    {
    case 4:
        s03d_800D2C20(work);
        if (s03d_800D3184(work) != 0)
        {
            work->field_ACC = 5;
            work->field_AD0 = 0;
        }
        break;
    case 5:
        {
            int r = s03d_800D327C(work);

            if (r < 0)
            {
                work->field_ACC = 4;
                work->field_AD0 = 0;
            }
            else if (r > 0)
            {
                work->field_ACA = 2;
                work->field_ACC = 0xC;
                work->field_AD0 = 0;
            }
        }
        break;
    }
    if (work->field_B90 < work->field_B64)
    {
        if (work->field_B64 >= 0x1B58 || work->field_B26 == 2)
        {
            work->field_ACA = 2;
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
    }
    if (work->field_B26 == 2)
    {
        work->field_B28 = 0xFF;
    }
    ZakoCom_800D4088();
}
void s03d_800D3A7C(Work *work)
{
    if (work->field_ACC == 13)
    {
        if (s03d_800D3184(work))
        {
            work->field_ACA = 2;
            work->field_ACC = 12;
            work->field_AD0 = 0;
        }
    }
}
void s03d_800D3ACC(Work *work)
{
    switch (work->field_ACA)
    {
    case 0:
        s03d_800D3724(work);
        break;
    case 1:
        s03d_800D3984(work);
        break;
    case 2:
        s03d_800D3848(work);
        break;
    case 3:
        s03d_800D3A7C(work);
        break;
    case 4:
        s03d_800D3754(work);
        break;
    }
}
const char s03d_dword_800DBB2C[] = {0xaf, 0x0, 'd', 0x0};
const char s03d_dword_800DBB30[] = {'^', 0x1, 0xc8, 0x0};
const char s03d_dword_800DBB34[] = {'k', 'i', 'r', 'a'};
const char s03d_dword_800DBB38[] = {'r', 'i', 0x0, 0x0};
const char s03d_dword_800DBB3C[] = {'e', 'y', 'e', 'f'};
const char s03d_dword_800DBB40[] = {'l', 'a', 's', 'h'};
const char s03d_dword_800DBB44[] = {'.', 'c', 0x0, 0xb4};
const char s03d_dword_800DBB48[12] = "dareda!!\n";
const char s03d_dword_800DBB54[16] = "nanno otoda!!\n";
const char s03d_dword_800DBB64[16] = "tadano hakoka\n";
const char s03d_dword_800DBB74[20] = "kono asiatoha??\n";
const char s03d_dword_800DBB88[16] = "kinoseika !!\n";
const char s03d_dword_800DBB98[8] = "itazo \n";
const char s03d_dword_800DBBA0[12] = "kottida!!\n";
const char s03d_dword_800DBBAC[20] = "haitini modoruzo!!\n";
const char s03d_dword_800DBBC0[16] = "kottida !!\n";
const int s03d_dword_800DBBD0 = 0x800D4730;
const int s03d_dword_800DBBD4 = 0x800D4740;
const int s03d_dword_800DBBD8 = 0x800D4750;
const int s03d_dword_800DBBDC = 0x800D4760;
const int s03d_dword_800DBBE0 = 0x800D4770;
const int s03d_dword_800DBBE4 = 0x800D4780;
const int s03d_dword_800DBBE8 = 0x800D4790;
const int s03d_dword_800DBBEC = 0x800D47A0;
const char s03d_dword_800DBBF0[32] = "%d reset_enemy_num[%d ]\n";
const int s03d_dword_800DBC10 = 0x800D4F14;
const int s03d_dword_800DBC14 = 0x800D4F5C;
const int s03d_dword_800DBC18 = 0x800D5008;
const int s03d_dword_800DBC1C = 0x800D5090;
const int s03d_dword_800DBC20 = 0x800D50D0;
const int s03d_dword_800DBC24 = 0x800D5164;
const int s03d_dword_800DBC28 = 0x800D51A8;
const int s03d_dword_800DBC2C = 0x800D53D8;
const int s03d_dword_800DBC30 = 0x800D5268;
const int s03d_dword_800DBC34 = 0x800D52A4;
const int s03d_dword_800DBC38 = 0x800D52B8;
const int s03d_dword_800DBC3C = 0x800D52F0;
const int s03d_dword_800DBC40 = 0x800D5324;
const int s03d_dword_800DBC44 = 0x800D5344;
const int s03d_dword_800DBC48 = 0x800D53A8;
const int s03d_dword_800DBC4C = 0x800D53D8;
const char s03d_dword_800DBC50[32] = "Err Err Err Sound Buff Over !!\n";
const char s03d_dword_800DBC70[] = {'z', 'o', 'n', 'e'};
const char s03d_dword_800DBC74[] = {'=', '%', 'd', ' '};
const char s03d_dword_800DBC78[] = {0x0, 0x0, 0x0, 0x0};
const char s03d_dword_800DBC7C[] = {'z', 'a', 'k', 'o'};
const char s03d_dword_800DBC80[] = {'c', 'o', 'm', '.'};
const char s03d_dword_800DBC84[] = {'c', 0x0, 0x0, 0xf};

void s03d_800D3B5C(Work *work)
{
    work->field_AE6 = -1;
    work->field_5A = 5;
    work->field_AD8 = 0;
    work->field_B28 = 0xFF;
    if (work->field_AC8 == 0)
    {
        work->field_8E4 = 1;
        s03d_800D3ACC(work);
    }
}
