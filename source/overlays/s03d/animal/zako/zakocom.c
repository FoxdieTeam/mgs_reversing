#include "common.h"
#include "game/game.h"
#include "mts/mts.h" // for fprintf
#include "libgcl/libgcl.h" // for GCL_NextStr, GCL_StrToInt
#include "game/vibrate.h" // for NewPadVibration

extern int s03d_dword_800DC2E0;
extern int s03d_dword_800DC2E8;
extern int s03d_dword_800DC2EC;
extern int s03d_dword_800DC310;
extern int s03d_dword_800DC31C;
extern const char s03d_dword_800DBB48[];
extern const char s03d_dword_800DBB54[];
extern const char s03d_dword_800DBB64[];
extern const char s03d_dword_800DBB74[];
extern const char s03d_dword_800DBB88[];
extern const char s03d_dword_800DBB98[];
extern const char s03d_dword_800DBBA0[];
extern const char s03d_dword_800DBBAC[];
extern const char s03d_dword_800DBBC0[];

extern unsigned char s03d_dword_800C3B98[4];
extern unsigned char s03d_dword_800C3B9C[4];
extern int s03d_dword_800DC2F4;
extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern SVECTOR s03d_dword_800DC308;
extern int s03d_dword_800DC424;
extern const char s03d_dword_800DBC50[];
extern CONTROL *GM_WhereList[96];

typedef struct _ZakoActor
{
    char            pad_0[0xAE8];
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xB28 - 0xAEA];
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB64 - 0xB2C];
    int             field_B64;      /* 0xB64 */
    char            pad_B68[0xB90 - 0xB68];
    int             field_B90;      /* 0xB90 */
} ZakoActor;

typedef struct _ZakoComEntry
{
    int             field_0;        /* 0x00 */
    int             field_4;        /* 0x04 */
    int             field_8;        /* 0x08 */
    ZakoActor      *field_C;        /* 0x0C - zako actor work */
} ZakoComEntry;                     /* 0x10 */

typedef struct _ZakoComMgr
{
    char            pad_0[0x8];
    int             count;          /* 0x08 */
    char            pad_C[0x18 - 0xC];
    int             field_18;       /* 0x18 */
    int             field_1C;       /* 0x1C */
    char            pad_20[0x24 - 0x20];
    int             field_24;       /* 0x24 */
    int             field_28;       /* 0x28 */
    SVECTOR         field_2C;       /* 0x2C */
    short           field_34;       /* 0x34 */
    char            pad_36[0x38 - 0x36];
    short           field_38;       /* 0x38 */
    char            pad_3A[0x40 - 0x3A];
    int             field_40;       /* 0x40 */
    char            pad_44[0x60 - 0x44];
    int             field_60;       /* 0x60 */
    int             field_64;       /* 0x64 */
    char            pad_68[0x8C - 0x68];
    ZakoComEntry    entries[8];     /* 0x8C - 0x10C */
    int             field_10C;      /* 0x10C */
    char            pad_110[0x124 - 0x110];
    int             field_124[8];   /* 0x124 */
} ZakoComMgr;

#define ZAKOCOM_MGR ((ZakoComMgr *)&s03d_dword_800DC310)

extern const char s03d_dword_800DBBF0[];
extern int printf(const char *format, ...);
extern int s03d_dword_800C3BC0;
void s03d_800D42DC(void);
int s03d_800D46F8(int cmd);

int ZakoCom_800D3FF4(ZakoActor *actor)
{
    ZakoComMgr *mgr = ZAKOCOM_MGR;
    int i;

    for (i = 0; i < 8; i++)
    {
        if (mgr->entries[i].field_C == 0)
        {
            mgr->entries[i].field_C = actor;
            mgr->entries[i].field_4 = 2;
            return i;
        }
    }
    return -1;
}
int ZakoCom_800D4038(void)
{
    int v = s03d_dword_800DC2E0;

    s03d_dword_800DC2E0 = v + 1;
    return v;
}

void ZakoCom_800D4050(int idx)
{
    int *base = &s03d_dword_800DC310;

    base[idx * 4 + 0x98 / 4] = 0;
    base[idx * 4 + 0x90 / 4] = 1;
}

void ZakoCom_800D4070(int value)
{
    s03d_dword_800DC2EC = value;
}

void ZakoCom_800D407C(int value)
{
    s03d_dword_800DC2E8 = value;
}
void ZakoCom_800D4088(void)
{
    ZakoComMgr *mgr = ZAKOCOM_MGR;

    mgr->field_24 = s03d_dword_800DC2FC;
    mgr->field_2C = s03d_dword_800DC308;
    mgr->field_28 = s03d_dword_800DC300;
}
void ZakoCom_800D40D4(void)
{
    int addr = HZD_GetAddress(GM_WhereList[0]->map->hzd, &GM_NoisePosition, -1);
    ZakoComMgr *mgr = ZAKOCOM_MGR;

    mgr->field_24 = addr;
    mgr->field_2C = GM_NoisePosition;
    mgr->field_28 = GM_PlayerMap;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D414C.s")
void ZakoCom_800D41C0(void)
{
    if (s03d_dword_800DC2F4 > 0)
    {
        NewPadVibration(s03d_dword_800C3B98, 1);
        NewPadVibration(s03d_dword_800C3B9C, 2);
        s03d_dword_800DC2F4--;
    }
    else
    {
        s03d_dword_800DC2F4 = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4224.s")
int ZakoCom_800D4284(int arg0, short *out)
{
    short *p = out;
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != 0)
    {
        *p = GCL_StrToInt(str);
        p++;
        count++;
    }

    return count;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D42DC.s")
int ZakoCom_800D43CC(int arg)
{
    return s03d_dword_800DC31C % arg;
}

void ZakoCom_800D440C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
}
void ZakoCom_800D4460(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
}
void ZakoCom_800D44B4(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
}
void ZakoCom_800D4508(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
}
void ZakoCom_800D455C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
}
void ZakoCom_800D45B0(int *out)
{
    switch (ZakoCom_800D43CC(3))
    {
    case 0:
        fprintf(1, s03d_dword_800DBB98);
        out[0] = 0x82;
        break;
    case 1:
        fprintf(1, s03d_dword_800DBBA0);
        out[0] = 0x81;
        break;
    case 2:
        fprintf(1, s03d_dword_800DBBA0);
        out[0] = 0x81;
        break;
    }
}
void ZakoCom_800D4640(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBBAC);
        out[0] = 0x85;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBBAC);
        out[0] = 0x85;
    }
}
void ZakoCom_800D4694(int *out)
{
    switch (ZakoCom_800D43CC(2))
    {
    case 0:
        fprintf(1, s03d_dword_800DBBC0);
        out[0] = 0x81;
        break;
    case 1:
        out[0] = 0;
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D46F8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D47BC.s")
void ZakoCom_800D490C(ZakoComMgr *mgr)
{
    int i;
    int min;
    int best;

    s03d_dword_800C3BC0--;
    if (s03d_dword_800C3BC0 < 0)
    {
        s03d_dword_800C3BC0 = 0;
    }
    if (s03d_dword_800C3BC0 > 0)
    {
        return;
    }
    min = 100000;
    best = 0;
    for (i = 0; i < mgr->count; i++)
    {
        if (mgr->entries[i].field_4 == 2)
        {
            ZakoActor *w = mgr->entries[i].field_C;

            if (w->field_AE8 != 0 && w->field_B90 < min)
            {
                best = w->field_AE8;
                min = w->field_B90;
            }
            w->field_AE8 = 0;
        }
    }
    if (best != 0)
    {
        s03d_dword_800C3BC0 = 0x1E;
        GM_SeSet2(0, 0x30, s03d_800D46F8(best));
    }
}
void ZakoCom_800D49F0(ZakoComEntry *e, int idx)
{
    int state = e->field_8;

    switch (state)
    {
    case 0:
        if (e->field_4 == 1)
        {
            e->field_8 = 1;
            e->field_0 = 1;
            printf(s03d_dword_800DBBF0, idx, ++ZAKOCOM_MGR->field_60);
        }
        break;
    case 1:
        e->field_0--;
        if (e->field_0 <= 0)
        {
            e->field_8 = 2;
            e->field_0 = 0;
        }
        break;
    case 2:
    {
        ZakoComMgr *mgr = ZAKOCOM_MGR;

        switch (mgr->field_1C)
        {
        case 0:
            if (mgr->field_10C & 1)
            {
                s03d_800D42DC();
                e->field_4 = state;
                e->field_8 = 0;
            }
            break;
        case 1:
            if (mgr->field_60 < 16)
            {
                s03d_800D42DC();
                e->field_4 = state;
                e->field_8 = 0;
            }
            break;
        }
        break;
    }
    }
}
int ZakoCom_800D4B08(int a, int b)
{
    if (a < b)
    {
        a = b;
    }
    return a;
}
void ZakoCom_800D4B20(int targetval, ZakoComMgr *mgr)
{
    int v = mgr->field_18;

    if (v - targetval >= 5)
    {
        mgr->field_18 = v - 4;
    }
    else
    {
        mgr->field_18 = targetval;
    }
    if (mgr->field_18 < s03d_dword_800DC2EC)
    {
        mgr->field_18 = s03d_dword_800DC2EC;
    }
    ZakoCom_800D4070(0);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4B84.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4CE0.s")
void ZakoCom_800D4DD4(void)
{
    int addr = GM_PlayerAddress;

    if ((addr & 0xFF) == ((addr >> 8) & 0xFF) && (addr & 0xFF) != 0xFF)
    {
        s03d_dword_800DC2FC = addr;
        s03d_dword_800DC308 = GM_PlayerPosition;
        s03d_dword_800DC300 = GM_PlayerMap;
    }
}
int ZakoCom_800D4E48(char *str)
{
    int count = 0;

    if (str != 0)
    {
        do
        {
            int proc = GCL_StrToInt(str);

            str = GCL_NextStr();
            GCL_ExecProc(proc, NULL);
            count++;
        } while (str != 0);
    }

    return count;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4EAC.s")
int ZakoCom_800D5484(int arg0, int *out)
{
    int *p = out;
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != 0)
    {
        *p = GCL_StrToInt(str);
        p++;
        count++;
    }

    return count;
}
int ZakoCom_800D54DC(void)
{
    char *opt = GCL_GetOption('s');

    if (opt == 0)
    {
        return 0;
    }
    if (ZakoCom_800D5484((int)opt, &s03d_dword_800DC424) < 4)
    {
        return 0;
    }
    fprintf(0, s03d_dword_800DBC50);
    return -1;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D5538.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D55C8.s")
