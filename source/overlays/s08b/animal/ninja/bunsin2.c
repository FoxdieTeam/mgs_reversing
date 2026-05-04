#include "game/game.h"
#include "game/target.h"

typedef struct _BunshinClone
{
    int  field_0;
    char pad[0x104 - sizeof(int)];
} BunshinClone;

typedef struct _BunshinWork
{
    GV_ACT       actor;          // 0x000
    OBJECT       body;           // 0x020
    char         pad_after_body[0x748 - 0x20 - sizeof(OBJECT)];
    SVECTOR      field_748;      // 0x748
    char         pad_to_7DC[0x7DC - 0x748 - sizeof(SVECTOR)];
    DG_OBJS     *field_7DC;      // 0x7DC
    char         pad_to_8C4[0x8C4 - 0x7DC - sizeof(DG_OBJS *)];
    TARGET      *field_8C4;      // 0x8C4
    char         pad_before_clones[0x920 - 0x8C4 - sizeof(TARGET *)];
    BunshinClone clones[16];     // 0x920 (16 * 0x104 = 0x1040, ends at 0x1960)
    char         pad1b[0x1964 - 0x1960];
    short        field_1964;
    short        field_1966;
    SVECTOR      field_1968;     // 0x1968
    int          field_1970;     // 0x1970
    char         pad1d[0x1988 - 0x1970 - sizeof(int)];
    int          field_1988;     // 0x1988
    SVECTOR      field_198C;     // 0x198C
    char         pad2[0x19A8 - 0x198C - sizeof(SVECTOR)];
    int          field_19A8;
    char         pad2b[0x19B0 - 0x19A8 - sizeof(int)];
    int          field_19B0;
    int          field_19B4;
    char         pad3[0x19CC - 0x19B4 - sizeof(int)];
    int          field_19CC;
    int          field_19D0;
    char         pad4[0x19F4 - 0x19D0 - sizeof(int)];
    int          field_19F4;     // 0x19F4
    int          field_19F8;     // 0x19F8
    char         pad5[0x1A28 - 0x19F8 - sizeof(int)];
    int          field_1A28;     // 0x1A28
    int          field_1A2C;     // 0x1A2C
    char         pad6[0x1A40 - 0x1A2C - sizeof(int)];
    void        *field_1A40[8];  // 0x1A40
} BunshinWork;

int Bunsin2_800C8F04(void) 
{
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8FF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C908C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9120.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C933C.s")
int s08b_bunsin2_800C9514(BunshinWork *work)
{
    TARGET *target = work->field_8C4;

    if (target->damaged & TARGET_POWER)
    {
        int ret = target->a_mode;
        target->damage = 0;
        target->damaged = 0;
        return ret;
    }
    return -1;
}
extern int s08b_bunsin2_800C933C(BunshinWork *work);

int s08b_bunsin2_800C9548(BunshinWork *work)
{
    if (s08b_bunsin2_800C933C(work))
    {
        work->field_8C4->class = TARGET_AVAIL;
        return 1;
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9978.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9B38.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9BF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CA8F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAA78.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAB50.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAD28.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAE14.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAF6C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAFF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB0A8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB158.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB210.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB2AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB38C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB444.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB52C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB7A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB914.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBAA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBCEC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBE30.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC080.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC2F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC434.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC578.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC71C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC7EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC90C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCA4C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCAF0.s")
extern void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);

void s08b_bunsin2_800CCD18(BunshinWork *work)
{
    sna_act_helper2_helper2_80033054(
        (unsigned short)work->body.rots[1].vz,
        &work->field_748);
}
extern unsigned int jimctrl_helper_80037F68(unsigned int header);

void s08b_bunsin2_800CCD40(BunshinWork *work)
{
    work->field_19F4 = 0;
    work->field_19F4 = jimctrl_helper_80037F68(
        (unsigned short)work->body.rots[1].vz) & 0xFF;
}
void s08b_bunsin2_800CCD74(BunshinWork *work)
{
    if (work->field_19F8 == 0)
    {
        work->field_7DC->flag |= DG_FLAG_INVISIBLE;
    }
    else
    {
        work->field_7DC->flag &= ~DG_FLAG_INVISIBLE;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCDBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCE34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCF8C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD000.s")

int s08b_bunsin2_800CD298(int a, int b, int c)
{
    if (b < a) b = a;
    if (c < b) c = b;
    return c;
}

int s08b_bunsin2_800CD2C0(int a, int b, int c)
{
    if (a < b) b = a;
    if (b < c) c = b;
    return c;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD2E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD544.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD5AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD614.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD690.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD770.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD808.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD87C.s")
extern void s08b_bunsin2_800CD87C(void);
extern int  s08b_bunsin2_800CD95C(BunshinWork *work, int target);

void s08b_bunsin2_800CD8D8(BunshinWork *work)
{
    work->field_7DC->flag &= ~DG_FLAG_INVISIBLE;
    s08b_bunsin2_800CD95C(work, (int)s08b_bunsin2_800CD87C);
}
extern int s08b_dword_800C3418;

int s08b_bunsin2_800CD914(BunshinWork *work, int idx)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (work->field_1A40[i] == NULL)
        {
            work->field_1A40[i] = ((void **)&s08b_dword_800C3418)[idx];
            return 1;
        }
    }
    return 0;
}
int s08b_bunsin2_800CD95C(BunshinWork *work, int target)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if ((int)work->field_1A40[i] == target)
        {
            work->field_1A40[i] = NULL;
            return 1;
        }
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD990.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD9F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDA40.s")
extern void s08b_bunsin2_800CDA40(BunshinWork *work);
extern void s08b_bunsin2_800CD9F0(BunshinWork *work);
extern void s08b_bunsin2_800D4ED0(BunshinWork *work);
extern void s08b_bunsin2_800CD000(BunshinWork *work);
extern void s08b_bunsin2_800CD990(BunshinWork *work);

void s08b_bunsin2_800CDB10(BunshinWork *work)
{
    s08b_bunsin2_800CDA40(work);
    s08b_bunsin2_800CD9F0(work);
    s08b_bunsin2_800D4ED0(work);
    s08b_bunsin2_800CD000(work);
    s08b_bunsin2_800CD990(work);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDB54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDBAC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDDD8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDE74.s")
extern int     GM_PlayerAddress;
extern SVECTOR GM_PlayerPosition;

void s08b_bunsin2_800CDF68(BunshinWork *work)
{
    work->field_1968 = GM_PlayerPosition;
    work->field_1970 = GM_PlayerAddress;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDFA0.s")
void s08b_bunsin2_800CDFF8(BunshinWork *work)
{
    work->field_1968 = work->field_198C;
    work->field_1970 = work->field_1988;
}
extern int s08b_dword_800C358C;
extern int s08b_dword_800C3594;

void s08b_bunsin2_800CE024(BunshinWork *work)
{
    work->field_1968 = *(SVECTOR *)&s08b_dword_800C358C;
    work->field_1970 = s08b_dword_800C3594 | (s08b_dword_800C3594 << 8);
}
extern int s08b_dword_800C3454;
extern int s08b_dword_800C3458;

void s08b_bunsin2_800CE064(BunshinWork *work)
{
    work->field_1968 = *(SVECTOR *)&s08b_dword_800C3458;
    work->field_1970 = s08b_dword_800C3454 | (s08b_dword_800C3454 << 8);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE0A4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE180.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE21C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE2E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE398.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE584.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE800.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE8A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE9BC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEA34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEB40.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CECB4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEE18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEE68.s")
int s08b_bunsin2_800CEEB8(BunshinWork *work, int arg1)
{
    SVECTOR vec;
    int     dx, dz;

    dx = work->field_1968.vx - *(short *)&work->body.objs;
    vec.vx = dx;
    dz = work->field_1968.vz - *(short *)&work->body.flag;
    vec.vz = dz;

    if (dx > -arg1 && dx < arg1 && dz > -arg1 && dz < arg1)
    {
        return 1;
    }
    work->field_19B4 = GV_VecDir2(&vec);
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEF34.s")
int s08b_bunsin2_800CEF94(BunshinClone *p, int n, int initial)
{
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sum += p->field_0;
        p++;
    }
    return sum + initial;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEFC0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEFF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF150.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF254.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF354.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF464.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF54C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF660.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF704.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF880.s")

int s08b_bunsin2_800CF950(void)
{
    return 1;
}

int s08b_bunsin2_800CF958(void)
{
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF960.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFA30.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFA80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFB98.s")
void s08b_bunsin2_800CFC64(BunshinWork *work)
{
    work->field_19D0++;
    s08b_bunsin2_800CEEB8(work, 500);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFC90.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFCF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFD88.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFDE0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFE54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0004.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0078.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D018C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0200.s")
int s08b_bunsin2_800D0278(BunshinWork *work)
{
    if (work->field_19D0 >= 0x79)
    {
        return 1;
    }
    return work->field_19A8;
}
int s08b_bunsin2_800D02A0(BunshinWork *work)
{
    int v = ++work->field_19D0;
    if (v == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}
int s08b_bunsin2_800D02E8(BunshinWork *work)
{
    int v = ++work->field_19D0;
    if (v == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0330.s")
int s08b_bunsin2_800D0410(BunshinWork *work)
{
    if (!(GM_GameStatus & STATE_CHAFF))
    {
        return 1;
    }
    work->field_19B0 = 27;
    work->field_19D0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D044C.s")
int s08b_bunsin2_800D0530(BunshinWork *work)
{
    int v;

    v = work->field_19D0;
    work->field_19B0 = 22;
    v++;
    work->field_19D0 = v;
    return v >= 0x1F;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0550.s")
int s08b_bunsin2_800D0688(BunshinWork *work)
{
    return work->field_19D0++;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D06A0.s")

int s08b_bunsin2_800D0720(BunshinWork *work)
{
    int val;

    val = work->field_1968.pad;
    return val & 0x1F;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D072C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0784.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0814.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0864.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D08C8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D093C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D09C4.s")
int s08b_bunsin2_800D0A54(BunshinWork *work)
{
    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    if (work->field_1A2C < 2000)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0A90.s")
void s08b_bunsin2_800D0B1C(BunshinWork *work)
{
    work->field_19B0 = 7;
    if (work->field_19D0 >= 11)
    {
        work->field_19CC = 5;
        work->field_19D0 = 0;
    }
    else
    {
        work->field_19D0++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0B4C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0CD8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0D80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0EB8.s")
int s08b_bunsin2_800D0F54(BunshinWork *work)
{
    work->field_19B0 = 7;
    work->field_19B4 = work->field_1A28;
    if (work->field_19D0 >= 11)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0F88.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1014.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D10C4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1138.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D11A8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1218.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D125C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D12A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D12EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1348.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D138C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1400.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1514.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1638.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1738.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D17F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D195C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1A18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1AF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1CF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1D44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1F9C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2104.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2158.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D21B8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D231C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2420.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2510.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2600.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2860.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D29DC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2B24.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2BFC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2DB0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2EA0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2F80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3064.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D30E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3160.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D31EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3394.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3468.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D367C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D37F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D38F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D39F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3A84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3B00.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3C44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3CCC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3EA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3F5C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D401C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4128.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D41DC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D42D8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D43D8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4460.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D44D0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D452C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4638.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D468C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D47E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4884.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4984.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4A34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4AF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4C84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4D18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4DA8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4E3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4ED0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4FBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D53E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5434.s")
extern int s08b_dword_800C3610;
extern int s08b_dword_800C3614;
extern int s08b_dword_800C3618;

void s08b_bunsin2_800D5498(void)
{
    int v;

    v = s08b_dword_800C3614;
    if (v != 0)
    {
        v--;
        s08b_dword_800C3614 = v;
        if (v == 0)
        {
            s08b_dword_800C3618 = 0;
            s08b_dword_800C3610 = 0;
        }
    }
}
void s08b_bunsin2_800D54CC(void *arg0)
{
    int i;
    char *p = (char *)arg0;
    for (i = 0; i < 16; i++)
    {
        int *q = *(int **)(p + 0x88);
        *q |= 2;
        p += 0x5C;
    }
}
void s08b_bunsin2_800D54FC(DG_OBJS *objs)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        objs->objs[i].model->flags &= ~DG_FLAG_PAINT;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5530.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5600.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5734.s")
extern void s08b_bunsin2_800D5530(BunshinWork *work);
extern void s08b_bunsin2_800D5600(BunshinWork *work);
extern void s08b_bunsin2_800D5734(BunshinWork *work);

void s08b_bunsin2_800D57F0(BunshinWork *work)
{
    s08b_bunsin2_800D5530(work);
    s08b_bunsin2_800D5600(work);
    s08b_bunsin2_800D5734(work);
    DG_GetLightMatrix2(*(SVECTOR **)((char *)work + 0x108),
                       (MATRIX *)((char *)work + 0x1540));
}
void s08b_bunsin2_800D5830(BunshinWork *work)
{
    GM_FreeObject(&work->body);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5850.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D594C.s")
