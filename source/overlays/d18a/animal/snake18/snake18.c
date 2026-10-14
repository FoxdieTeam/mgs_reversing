#include "mgstype.h"
#include "chara/snake/shadow.h"
#include "game/game.h"
#include "game/vibrate.h"
#include "libgcl/libgcl.h"
#include "okajima/blood.h"
#include "strcode.h"

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define BODY_DATA   GV_StrCode( "sne_nude" )
#define BODY_DATA2  GV_StrCode( "ippanhei" )
#define MOTION_DATA GV_StrCode( d18a_aSnevs_800DA744 )


/* motion number tables (indices into the oar motion file), see sna_init.c */
typedef struct _ACTSTILL18
{
    u_char stand;
    u_char setup;
    u_char squat;
    u_char crouch;
    u_char against_wall;
    u_char squat_against_wall;
    u_char tap_wall_r;
    u_char tap_wall_l;
} ACTSTILL18;

typedef struct _ACTMOVE18
{
    u_char stand;
    u_char setup;
    u_char squat;
    u_char crouch;
    u_char crouch_backwards;
    u_char against_wall_r;
    u_char against_wall_l;
    u_char field_7;
    u_char field_8;
    u_char aim;
    u_char turn_l;
    u_char turn_r;
    u_char pad[4];
} ACTMOVE18;

typedef struct _ACTTRANS18
{
    u_char crouch;
    u_char squat;
    u_char stand;
    u_char pad;
} ACTTRANS18;

typedef struct _ACTDAMAGE18
{
    u_char field_0[16];
} ACTDAMAGE18;

typedef struct _ACTATTACK18
{
    u_char field_0[12];
} ACTATTACK18;

typedef struct _ACTSPECIAL18
{
    u_char field_0[8];
} ACTSPECIAL18;

typedef struct _ACTPACK18
{
    ACTSTILL18   *still;
    ACTMOVE18    *move;
    ACTTRANS18   *trans;
    ACTDAMAGE18  *damage;
    ACTATTACK18  *attack;
    u_char       *special1;
    ACTSPECIAL18 *special2;
} ACTPACK18;

typedef struct _Snake18Init
{
    char    pad_4[4];
    short   f4;          // 0x8C8 in Snake18Work
    char    pad_8[2];
    short   f8;          // 0x8CC
    char    pad_C[2];
    short   fC;          // 0x8D0
    short   fE;          // 0x8D2
    short   f10;         // 0x8D4
    char    pad_12[2];
} Snake18Init;

typedef struct _Snake18Queue
{
    u_short count;      // 0x8D8
    short   field_2[4]; // 0x8DA
    short   field_A[4]; // 0x8E2
    short   field_12;   // 0x8EA
    short   field_14;   // 0x8EC
} Snake18Queue;

typedef struct _Snake18Work
{
    GV_ACT         actor;         // 0x000
    CONTROL        control;       // 0x020
    OBJECT         body;          // 0x09C
    MOTION_CONTROL m_ctrl;        // 0x180
    MOTION_SEGMENT m_segs1[17];   // 0x1D0
    MOTION_SEGMENT m_segs2[17];   // 0x434
    SVECTOR        rots[16];      // 0x698
    char           pad_718[0x728 - 0x718];
    short          f728;          // 0x728
    char           pad_72A[0x748 - 0x728 - sizeof(short)];
    short          f748;          // 0x748
    char           pad_74A[0x750 - 0x748 - sizeof(short)];
    short          f750;          // 0x750
    char           pad_752[0x79C - 0x750 - sizeof(short)];
    MATRIX         light[2];      // 0x79C
    void          *shadow;        // 0x7DC
    int           *enable_shadow; // 0x7E0

    int     f7E4;        // 0x7E4
    short  *f7E8;        // 0x7E8 (pointer slot, used by 800CC8E0 etc.)
    TARGET  f7EC;        // 0x7EC
    char    pad_834[0x834 - 0x7EC - sizeof(TARGET)];
    int     f834;        // 0x834
    char    pad_840[0x840 - 0x834 - sizeof(int)];
    int     f840;        // 0x840
    char    pad_848[0x848 - 0x840 - sizeof(int)];
    SVECTOR f848;        // 0x848
    void   *f850;        // 0x850
    int     f854;        // 0x854
    int     f858;        // 0x858
    int     f85C;        // 0x85C
    short  *f860;        // 0x860
    int     f864;        // 0x864
    char    pad_868[0x868 - 0x864 - sizeof(int)];
    int     f868;        // 0x868
    short   f86C;        // 0x86C
    short   f86E;        // 0x86E
    char    pad_870[0x874 - 0x86E - sizeof(short)];
    DG_PRIM *f874;       // 0x874
    char    pad_878[0x898 - 0x878];
    GV_ACT *f898;        // 0x898 (item actor)
    int     f89C;        // 0x89C
    int     f8A0;        // 0x8A0
    GV_PAD *pad;         // 0x8A4
    ACTPACK18 *f8A8;   // 0x8A8
    void   *f8AC;        // 0x8AC (callback pointer)
    int     f8B0;        // 0x8B0
    void   *f8B4;        // 0x8B4 (callback pointer)
    int     f8B8;        // 0x8B8
    void   *f8BC;        // 0x8BC (callback pointer)
    void   *f8C0;        // 0x8C0 (callback pointer)
    Snake18Init f8C4;    // 0x8C4 (20-byte init block; .f4=0x8C8 .f8=0x8CC .fC=0x8D0)
    Snake18Queue f8D8;   // 0x8D8
    short   f8EE;        // 0x8EE
    char    pad_8F0[0x8F0 - 0x8EE - sizeof(short)];
    int     f8F0;        // 0x8F0
    int     f8F4;        // 0x8F4
    short   f8F8;        // 0x8F8
    char    pad_8FC[0x8FC - 0x8F8 - sizeof(short)];
    u_char  f8FC;        // 0x8FC (invincibility frames)
    u_char  f8FD;        // 0x8FD
    short   f8FE;        // 0x8FE
    short   f900;        // 0x900
    short   f902;        // 0x902
    SVECTOR f904;        // 0x904
    char    f90C;        // 0x90C
    char    f90D;        // 0x90D
    char    f90E;        // 0x90E
    char    pad_910[0x910 - 0x90E - sizeof(char)];
    short   f910;        // 0x910
    short   f912;        // 0x912
    char    pad_91C[0x91C - 0x912 - sizeof(short)];
    SVECTOR f91C;        // 0x91C (saved control.mov)
    char    pad_924[0x924 - 0x91C - sizeof(SVECTOR)];
    short   f924;        // 0x924
    short   f926;        // 0x926
    char    pad_928[0x92A - 0x926 - sizeof(short)];
    unsigned short f92A; // 0x92A
    unsigned short f92C; // 0x92C
    short   f92E;        // 0x92E
    int     f930;        // 0x930
    int     f934;        // 0x934
    SVECTOR f938;        // 0x938
} Snake18Work;

typedef struct _PUNCH
{
    SVECTOR field_0;
    SVECTOR size;
    SVECTOR field_10;
    int     life;
    int     faint;
} PUNCH;

typedef struct WeaponCreateEntry
{
    void *mCreateActorFn;
    void *mStateFn;
} WeaponCreateEntry;

extern int      d18a_dword_800C37E0;
extern short    d18a_dword_800C37F8;
extern SVECTOR  d18a_dword_800C3850;
extern SVECTOR  d18a_dword_800C3858;
extern char     d18a_dword_800C3800[];
extern char     d18a_dword_800C3804[];
extern char     d18a_dword_800C380C[];
extern char     d18a_dword_800C3810[];
extern char     d18a_dword_800C3860[];
extern char     d18a_dword_800C3864[];
extern int      d18a_dword_800DAEF0;
extern int      d18a_dword_800DAEF4;
extern char    *d18a_dword_800DAEFC;
extern HZD_FLR *d18a_dword_800DAF00[2];
extern GV_MSG   d18a_dword_800DAEA0[3];
extern void    *d18a_dword_800DAF10;
extern SVECTOR *d18a_dword_800DAEF8;
extern int      d18a_dword_800DAF08;
extern int      d18a_dword_800DAF0C;


extern void *d18a_dword_800C37E4[];
extern void *d18a_dword_800C37F0[];
extern void *d18a_dword_800C38C8[];

extern int dword_8009F46C[];

/* function prototypes */
void d18a_snake18_800CABEC(Snake18Work *work);
int d18a_snake18_800CAC68(int arg0, int arg1);
void d18a_snake18_800CACD0(Snake18Work *work);
int d18a_snake18_800CAEC0(Snake18Work *work, int state);
int d18a_snake18_800CAF20(Snake18Work *work);
void d18a_snake18_800CB030(Snake18Work *work);
int d18a_snake18_800CB134(Snake18Work *work);
int d18a_snake18_800CB1C8(Snake18Work *work);
void d18a_snake18_800CB228(Snake18Work *work, int arg1);
int d18a_snake18_800CB280(Snake18Work *work, int arg1);
void d18a_snake18_800CB2EC(Snake18Work *work);
void d18a_snake18_800CB34C(Snake18Work *work);
void d18a_snake18_800CB378(Snake18Work *work);
void d18a_snake18_800CB3E8(Snake18Work *work);
void d18a_snake18_800CB42C(Snake18Work *work);
void d18a_snake18_800CB470(Snake18Work *work);
void d18a_snake18_800CB514(Snake18Work *work);
void d18a_snake18_800CB59C(Snake18Work *work);
void d18a_snake18_800CB60C(Snake18Work *work);
int d18a_snake18_800CB710(Snake18Work *work, int a1);
void d18a_snake18_800CB760(Snake18Work *work, int arg1);
void d18a_snake18_800CB7BC(Snake18Work *work, int arg1);
void d18a_snake18_800CB7D0(Snake18Work *work, int arg1);
void d18a_snake18_800CB838(Snake18Work *work);
void d18a_snake18_800CB888(Snake18Work *work);
void d18a_snake18_800CB908(Snake18Work *work, PUNCH *arg1);
int d18a_snake18_800CB9CC(Snake18Work *arg0, PUNCH *arg1);
int d18a_snake18_800CBA64(Snake18Work *work, PUNCH *arg1);
void d18a_snake18_800CBB34(Snake18Work *work);
int d18a_snake18_800CBBC8(Snake18Work *work);
void d18a_snake18_800CBD34(Snake18Work *work);
void d18a_snake18_800CBD80(Snake18Work *work);
void d18a_snake18_800CBE58(Snake18Work *work);
void d18a_snake18_800CBEC0(Snake18Work *work);
void d18a_snake18_800CBF98(Snake18Work *work);
void d18a_snake18_800CC008(void);
void d18a_snake18_800CC010(Snake18Work *work);
void d18a_snake18_800CC174(Snake18Work *work, GV_MSG *msg);
int d18a_snake18_800CC288(SVECTOR *pos, short *out);
int d18a_snake18_800CC3C8(int area);
int d18a_snake18_800CC410(Snake18Work *work);
int d18a_snake18_800CC490(); /* asm */
void d18a_snake18_800CC6CC(Snake18Work *work);
void d18a_snake18_800CC7F4(Snake18Work *work);
void d18a_snake18_800CC8B0(Snake18Work *work, char arg1);
void d18a_snake18_800CC8E0(Snake18Work *arg0);
void d18a_snake18_800CC90C(Snake18Work *work);
void d18a_snake18_800CCB0C(TARGET *target);
void d18a_snake18_800CCB50(); /* asm */
void d18a_snake18_800CCF30(Snake18Work *work);
void d18a_snake18_800CD040(); /* asm */
void d18a_snake18_800CD2C4(); /* asm */
void d18a_snake18_800CD4C0(); /* asm */
void d18a_snake18_800CD64C(Snake18Work *work, int arg1);
void d18a_snake18_800CD768(Snake18Work *work, int arg1);
void d18a_snake18_800CD808(Snake18Work *work, int arg1);
void d18a_snake18_800CD888(Snake18Work *work, int arg1);
void d18a_snake18_800CD930(Snake18Work *work, int arg1);
void d18a_snake18_800CD9A8(); /* asm */
void d18a_snake18_800CDB04(); /* asm */
void d18a_snake18_800CDC3C(); /* asm */
void d18a_snake18_800CDD4C(); /* asm */
void d18a_snake18_800CDE8C(); /* asm */
void d18a_snake18_800CDFC8(); /* asm */
void d18a_snake18_800CE09C(); /* asm */
void d18a_snake18_800CE210(); /* asm */
void d18a_snake18_800CE38C(); /* asm */
void d18a_snake18_800CE4E4(); /* asm */
void d18a_snake18_800CE6B0(); /* asm */
void d18a_snake18_800CE7BC(void);
void d18a_snake18_800CE7C4(Snake18Work *work, int arg1);
void d18a_snake18_800CE834(Snake18Work *work, int arg1);
void d18a_snake18_800CE8E0(Snake18Work *work, int arg1);
void d18a_snake18_800CE998(Snake18Work *work, int arg1);
void d18a_snake18_800CEA84(Snake18Work *work, int arg1);
void d18a_snake18_800CEB78(Snake18Work *work, int arg1);
void d18a_snake18_800CEC68(); /* asm */
void d18a_snake18_800CECE0(); /* asm */
void d18a_snake18_800CED2C(Snake18Work *work, int arg1);
void d18a_snake18_800CEDB0(Snake18Work *work);
void d18a_snake18_800CEE60(Snake18Work *work);
void d18a_snake18_800CEEAC(Snake18Work *work, int arg1);
void d18a_snake18_800CEF0C(Snake18Work *work, int arg1);
void d18a_snake18_800CEF44(Snake18Work *work, int arg1);
void d18a_snake18_800CF03C(); /* asm */
void d18a_snake18_800CF198(); /* asm */
void d18a_snake18_800CF39C(); /* asm */
void d18a_snake18_800CF574(); /* asm */
void d18a_snake18_800CF718(int arg0, int arg1);
void d18a_snake18_800CF744(); /* asm */
void d18a_snake18_800CF850(); /* asm */
void d18a_snake18_800CF990(); /* asm */
void d18a_snake18_800CFB04(); /* asm */
void d18a_snake18_800CFD18(); /* asm */
void d18a_snake18_800CFEE8(Snake18Work *work, int arg1);
void d18a_snake18_800CFF5C(Snake18Work *work, int arg1);
void d18a_snake18_800CFFD4(Snake18Work *work, int arg1);
void d18a_snake18_800D0054(Snake18Work *work, int arg1);
void d18a_snake18_800D00E0(Snake18Work *work, int arg1);
void d18a_snake18_800D01D8(); /* asm */
void d18a_snake18_800D0974(Snake18Work *work);
void d18a_snake18_800D09B4(Snake18Work *work);
void d18a_snake18_800D0A10(Snake18Work *work);
void d18a_snake18_800D0AF8(Snake18Work *work);
void d18a_snake18_800D0B4C(Snake18Work *work);
void d18a_snake18_800D0B84(Snake18Work *work);
void d18a_snake18_800D0BF4(); /* asm */
void d18a_snake18_800D0E3C(); /* asm */
void d18a_snake18_800D1064(Snake18Work *work);
void d18a_snake18_800D11A8(); /* asm */
void d18a_snake18_800D1300(Snake18Work *work);
void d18a_snake18_800D1424(); /* asm */
void d18a_snake18_800D1598(); /* asm */
void d18a_snake18_800D1750(Snake18Work *work);
void d18a_snake18_800D1814(Snake18Work *work);
void d18a_snake18_800D18EC(Snake18Work *work);
void d18a_snake18_800D198C(Snake18Work *work, int amount);
void d18a_snake18_800D1A08(Snake18Work *work);
void d18a_snake18_800D1A6C(Snake18Work *work, int arg1);
void d18a_snake18_800D1ACC(Snake18Work *work, int arg1);
void d18a_snake18_800D1B3C(Snake18Work *work, int arg1);
void d18a_snake18_800D1BAC(); /* asm */
void d18a_snake18_800D1CE8(); /* asm */
void d18a_snake18_800D1F90(); /* asm */
void d18a_snake18_800D200C(); /* asm */
void d18a_snake18_800D20EC(); /* asm */
void d18a_snake18_800D22C8(Snake18Work *work, int a1);
void d18a_snake18_800D23F0(); /* asm */
void d18a_snake18_800D24CC(); /* asm */
void d18a_snake18_800D2660(Snake18Work *work, int arg1);
void d18a_snake18_800D26E4(); /* asm */
void d18a_snake18_800D281C(Snake18Work *work);
void d18a_snake18_800D28CC(); /* asm */
void d18a_snake18_800D2A80(); /* asm */
void d18a_snake18_800D2D88(); /* asm */
void d18a_snake18_800D2F70(); /* asm */
void d18a_snake18_800D3024(); /* asm */
void d18a_snake18_800D3218(); /* asm */
void d18a_snake18_800D3330(); /* asm */
void d18a_snake18_800D3508(); /* asm */
void d18a_snake18_800D3774(); /* asm */
void d18a_snake18_800D37FC(); /* asm */
void d18a_snake18_800D3A1C(); /* asm */
void d18a_snake18_800D3A9C(); /* asm */
void d18a_snake18_800D3B1C(); /* asm */
void d18a_snake18_800D3C14(); /* asm */
void d18a_snake18_800D3D0C(); /* asm */
void d18a_snake18_800D3ED0(); /* asm */
void d18a_snake18_800D3F3C(); /* asm */
void d18a_snake18_800D3FE8(); /* asm */
void d18a_snake18_800D4084(void);
void d18a_snake18_800D40F0(); /* asm */
void d18a_snake18_800D4388(); /* asm */
void d18a_snake18_800D46CC(Snake18Work *work);
void d18a_snake18_800D4784(); /* asm */
void d18a_snake18_800D48FC(); /* asm */
int d18a_snake18_800D49FC(); /* asm */
int d18a_snake18_800D4B84(Snake18Work *work);
int d18a_snake18_800D4BA4(Snake18Work *work);
int d18a_snake18_800D4C44(Snake18Work *work, int name, int where);
int d18a_snake18_800D4E94(int arg1, int arg2);

static inline void d18a_snake18_StartAnim(Snake18Work *work, void *func)
{
    work->f8AC = func;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

extern Snake18Init d18a_dword_800C383C;
extern int bakudan_count_8009F42C;
extern int printf(/* const char *format, ... */);
extern SVECTOR d18a_dword_800C3868;
extern ACTPACK18    d18a_dword_800C36C8[];
extern WeaponCreateEntry d18a_dword_800C3878[];
extern SVECTOR d18a_dword_800C3A28;

void d18a_snake18_800CABEC( Snake18Work *work )
{
    GV_PAD *pad;
    u_char *analog;
    int i;

    work->f7E4 &= ~0x4000;

    pad = work->pad;
    if ( pad->analog != 0 && ( pad->status & PAD_UDLR ) != 0 )
    {
        analog = &pad->right_dx;
        for ( i = 0; i < 4; i++ )
        {
            if ( (u_char)( *analog - 80 ) > 96 )
            {
                work->f7E4 |= 0x4000;
                return;
            }
            analog++;
        }
    }
}

int d18a_snake18_800CAC68(int arg0, int arg1)
{
    int temp_v1;

    if (arg1 < 0)
    {
        return 0;
    }

    temp_v1 = (arg1 - arg0) & 0xFFF;

    if (temp_v1 < 0x800)
    {
        if (temp_v1 < 0x100)
        {
            return 1;
        }

        if (temp_v1 >= 0x501)
        {
            return 3;
        }

        return 4;
    }

    if (temp_v1 >= 0xF01)
    {
        return 1;
    }

    if (temp_v1 < 0xB00)
    {
        return 3;
    }

    return 2;
}

void d18a_snake18_800CACD0(Snake18Work *work)
{
    int dir;
    int n_touches;
    int dir2;
    int diff;
    int diff2;

    d18a_dword_800DAEF8 = NULL;
    d18a_dword_800DAEF4 = -1;
    d18a_dword_800DAF0C = 0;
    d18a_dword_800DAF10 = NULL;

    d18a_dword_800DAEF0 = work->pad->dir;
    d18a_dword_800DAF08 = 0;
    d18a_dword_800DAF00[1] = NULL;
    d18a_dword_800DAF00[0] = NULL;
    dir = d18a_dword_800DAEF0;

    if (work->control.r_sphere != -2)
    {
        HZD_GetLevelHazard(d18a_dword_800DAF00);
        if (d18a_dword_800DAF00[0])
        {
            d18a_dword_800DAF08 = d18a_dword_800DAF00[0]->p4.h;
        }
    }

    n_touches = work->control.n_touches;
    if (n_touches <= 0)
    {
        return;
    }

    d18a_dword_800DAEF8 = &work->control.vecs[0];
    d18a_dword_800DAEFC = &work->control.atrs[0];
    d18a_dword_800DAEF4 = GV_VecDir2(&work->control.vecs[0]);
    d18a_dword_800DAF10 = work->control.segs[0];

    if (dir < 0)
    {
        return;
    }

    if (n_touches != 1)
    {
        dir2 = GV_VecDir2(&work->control.vecs[1]);
        diff2 = GV_DiffDirAbs(dir, d18a_dword_800DAEF4);
        if (GV_DiffDirAbs(dir, dir2) < diff2)
        {
            d18a_dword_800DAEF8 = &work->control.vecs[1];
            d18a_dword_800DAEF4 = dir2;
            d18a_dword_800DAF10 = work->control.segs[1];
            d18a_dword_800DAEFC++;
        }
    }

    if (*d18a_dword_800DAEFC & 0x40)
    {
        return;
    }

    diff = GV_DiffDirS(dir, d18a_dword_800DAEF4);
    if (diff >= -896 && diff <= 896)
    {
        d18a_dword_800DAF0C = 1;
        if (diff >= 0)
        {
            if (diff > 256)
            {
                d18a_dword_800DAF0C = 4;
            }
        }
        else if (diff < -256)
        {
            d18a_dword_800DAF0C = 2;
        }
    }
}
int d18a_snake18_800CAEC0(Snake18Work *work, int state)
{
    int base;
    int diff;

    if (*d18a_dword_800DAEFC & 0x40)
    {
        return state;
    }

    base = d18a_dword_800DAEF4;
    if (base >= 0)
    {
        diff = (state - base) & 0xFFF;
        if (diff < 0x400)
        {
            state = base + 0x400;
        }
        if (diff >= 0xC01)
        {
            state = base - 0x400;
        }
    }

    return state;
}

int d18a_snake18_800CAF20(Snake18Work *work)
{
    int      levels[2];
    SVECTOR  sp18;
    CONTROL *control;
    int      temp;

    control = &work->control;
    if ((control->levels[1] - control->mov.vy) >= 0x5DC)
    {
        sp18.vy = 0;
        sp18.vx = 0;
        sp18.vz = 0xC8;

        DG_PutVector(&sp18, &sp18, 1);
        levels[0] = 0;
        temp = 0x7FFF;
        levels[1] = temp;
        HZD_LevelHazardCheck(control->map->hzd, &sp18, HZD_CHK_FLOOR);
        HZD_GetLevelHeight(levels);

        if ((levels[1] - sp18.vy) >= 0x5DC)
        {
            sp18.vy = 0;
            sp18.vx = 0;
            sp18.vz = -0x3E8;

            DG_PutVector(&sp18, &sp18, 1);
            levels[0] = 0;
            levels[1] = temp;
            HZD_LevelHazardCheck(control->map->hzd, &sp18, HZD_CHK_FLOOR);
            HZD_GetLevelHeight(levels);

            return (levels[1] - sp18.vy) < 0x5DC;
        }
    }

    return 1;
}

void d18a_snake18_800CB030(Snake18Work *work)
{
    SVECTOR  vec;
    SVECTOR  sp18;
    short    temp_s1;
    int      temp_v0;
    int      var_v1;
    HZD_FLR *temp_a1;

    temp_s1 = work->f8FE;
    if (temp_s1 != 2)
    {
        work->f902 = 0;
        return;
    }

    vec.vy = 0;
    vec.vx = 0;
    vec.vz = 0x2EE;
    DG_PutVector(&vec, &vec, 1);

    temp_a1 = d18a_dword_800DAF00[0];

    if ((temp_a1 == NULL) || (temp_a1->b1.h == temp_s1))
    {
        work->f902 = 0;
        if (!(GM_PlayerStatus & PLAYER_WATCH))
        {
            work->control.turn.vx = 0;
        }
    }
    else
    {
        temp_v0 = HZD_SlopeFloorLevel(&vec, temp_a1) - work->control.levels[0];
        sp18.vx = temp_v0;
        sp18.vz = SquareRoot0(0x89544 - (temp_v0 * temp_v0));
        var_v1 = -GV_VecDir2(&sp18);

        if (var_v1 < -0x800)
        {
            var_v1 += 0x1000;
        }

        work->f902 = var_v1;

        if (!(GM_PlayerStatus & PLAYER_WATCH))
        {
            work->control.turn.vx = var_v1;
        }
    }
}

int d18a_snake18_800CB134(Snake18Work *work)
{
    int temp_s0;
    int temp_s0_2;
    int temp_s0_3;

    if (work->control.n_touches < 2)
    {
        return 0;
    }

    temp_s0 = GV_VecDir2(&work->control.vecs[0]);
    temp_s0_2 = GV_VecDir2(&work->control.vecs[1]);
    temp_s0_3 = GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0);

    if (((GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0_2) + 0x380) < 0x701U))
    {
        if (((temp_s0_3 + 0x380) < 0x701U))
        {
            return 1;
        }
    }

    return 0;
}

int d18a_snake18_800CB1C8(Snake18Work *work)
{
    char    *p;
    HZD_FLR *floor;
    int      min;
    int      max;
    int      cur;

    p = d18a_dword_800DAEFC;
    if (*p & 0x90)
    {
        return 0;
    }

    floor = d18a_dword_800DAF10;
    min = floor->b1.y;
    max = min + floor->b1.h;
    cur = work->control.mov.vy;

    if (cur > min && cur < max)
    {
        return 1;
    }
    return 0;
}

void d18a_snake18_800CB228(Snake18Work *work, int arg1)
{
    int var_v1;

    var_v1 = GV_DiffDirS(arg1, work->control.rot.vy);

    if (var_v1 >= 0x81)
    {
        var_v1 = 0x80;
    }
    else if (var_v1 < -0x80)
    {
        var_v1 = -0x80;
    }

    work->control.turn.vz = var_v1;
}

int d18a_snake18_800CB280(Snake18Work *work, int arg1)
{
    if (arg1 == 0)
    {
        return work->f8A8->still->stand;
    }
    else if (arg1 == 1)
    {
        return work->f8A8->still->squat;
    }
    else if (arg1 == 2)
    {
        return work->f8A8->still->crouch;
    }

    return -1;
}

void d18a_snake18_800CB2EC(Snake18Work *work)
{
    work->f8C4 = d18a_dword_800C383C;
}

void d18a_snake18_800CB34C( Snake18Work *work )
{
    GM_Camera.first_person = 1;
    work->f926 = 0;
    work->f8F8 = -4;
    GM_PlayerStatus |= ( PLAYER_WATCH | PLAYER_MENU_DISABLE );
}
void d18a_snake18_800CB378(Snake18Work *work)
{
    GM_Camera.first_person = 0;
    work->f8F8 = 4;
    work->f926 = 0;
    GM_PlayerStatus &= ~1;
    if (work->f7E4 & 0x8000)
    {
        work->f7E4 &= ~0x8000;
        work->control.mov = work->f91C;
    }
}

void d18a_snake18_800CB3E8(Snake18Work *work)
{
    work->f7E4 |= 0x800;
    work->f900 = 0x1C2;
    GM_Camera.first_person = 1;
    work->f8F8 = -4;
    work->f8C4.f8 = d18a_dword_800C37E0;
    work->f8C4.fC = d18a_dword_800C37E0;
    work->f8C4.f4 = 0x140;
}

void d18a_snake18_800CB42C(Snake18Work *work)
{
    work->f900 = 0x1C2;
    work->f7E4 &= ~0x800;
    GM_Camera.first_person = 0;
    work->f8F8 = 4;
    d18a_snake18_800CB2EC(work);
}
void d18a_snake18_800CB470(Snake18Work *work)
{
    if (work->f8F8 == 0)
    {
        return;
    }
    if (work->f8F8 > 0)
    {
        if (GM_Camera.first_person != 0)
        {
            return;
        }
        work->f8F8 -= 1;
        if (work->f8F8 != 0)
        {
            return;
        }
        GM_PlayerStatus &= ~0x8000;
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
    }
    else
    {
        if (GM_Camera.first_person == 0)
        {
            return;
        }
        work->f8F8 += 1;
        if (work->f8F8 != 0)
        {
            return;
        }
        work->body.objs->flag |= DG_FLAG_INVISIBLE;
    }
}
void d18a_snake18_800CB514(Snake18Work *work)
{
    MATRIX   sp10;
    MATRIX   sp30;
    SVECTOR  sp50;
    MATRIX  *mat;
    int      angle;

    mat = &work->body.objs->objs[6].world;

    ReadRotMatrix(&sp10);
    DG_TransposeMatrix(&sp10, &sp30);
    MulMatrix0(&sp30, mat, &sp30);
    DG_MatrixRotZYX(&sp30, &sp50);
    SetRotMatrix(&sp10);

    angle = sp50.vx;
    if (angle < 0)
        angle += 0xF;
    angle &= 0xFFF0;

    GM_SnakeCamera.rotate2.vx = angle;
}

void d18a_snake18_800CB59C(Snake18Work *work)
{
    short temp_s0;

    if (d18a_dword_800DAEF0 >= 0)
    {
        temp_s0 = work->control.turn.vy;

        if (GV_DiffDirS(temp_s0, d18a_dword_800DAEF0) != 0)
        {
            work->control.turn.vy = GV_NearSpeed(GV_NearPhase(temp_s0, d18a_dword_800DAEF0), d18a_dword_800DAEF0, 0x40);
        }
    }
}

void d18a_snake18_800CB60C(Snake18Work *work)
{
    int turn;
    int diff;
    int action;

    turn = work->control.turn.vy;
    diff = GV_DiffDirS(turn, d18a_dword_800DAEF0);

    if (diff == 0)
    {
        GM_PlayerStatus &= ~0x10;
        action = work->f8A8->still->setup;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
        return;
    }
    else if (diff < 0)
    {
        action = work->f8A8->move->turn_l;
    }
    else
    {
        action = work->f8A8->move->turn_r;
    }

    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    turn = GV_NearPhase(turn, d18a_dword_800DAEF0);
    work->control.turn.vy = GV_NearSpeed(turn, d18a_dword_800DAEF0, 0x40);
}

int d18a_snake18_800CB710( Snake18Work *work, int a1 )
{
    MOTION_INFO *info;
    int action;

    info = ( a1 == 1 ) ? &work->m_ctrl.info1 : &work->m_ctrl.info2;
    action = ( a1 == 1 ) ? work->body.action : work->body.action2;

    if ( ( info->frames_left + info->frame ) == 1 )
    {
        return action;
    }

    return -1;
}

void d18a_snake18_800CB760( Snake18Work *work, int arg1 )
{
    if ( arg1 != work->m_ctrl.info1.mask )
    {
        work->m_ctrl.info2.mask = ~arg1;
        work->m_ctrl.info1.mask = arg1;

        if ( ( arg1 == 0xFFFF ) && ( d18a_snake18_800CB710( work, 2 ) >= 0 ) )
        {
            work->m_ctrl.interp = 4;
            work->m_ctrl.info2.field_14 = 2;
        }
    }
}

void d18a_snake18_800CB7BC(Snake18Work *work, int arg1)
{
    work->f854 = arg1;
    work->f858 = 0;
    work->f86E = 0;
    work->f86C = 0;
}

void d18a_snake18_800CB7D0(Snake18Work *work, int arg1)
{
    MATRIX *mat;
    MATRIX  sp10;

    mat = &work->body.objs->objs[arg1].world;

    DG_SetPos(mat);
    DG_MovePos(&d18a_dword_800C3850);
    DG_RotatePos(&d18a_dword_800C3858);
    ReadRotMatrix(&sp10);
    NewBlood(&sp10, 1);
}

void d18a_snake18_800CB838(Snake18Work *work)
{
    if (!(work->f868 & 4) && (GM_PlayerStatus & PLAYER_ATTACK) && (work->f86C != 3))
    {
        work->f85C = (int)(work->f85C | 9);
    }
}

void d18a_snake18_800CB888(Snake18Work *work)
{
    if (work->f90C != 0)
    {
        NewPadVibration(d18a_dword_800C3860, 1);
        work->f90C = (unsigned char)(work->f90C - 1);
    }

    if (work->f90D != 0)
    {
        NewPadVibration(d18a_dword_800C3864, 2);
        work->f90D = (unsigned char)(work->f90D - 1);
        return;
    }

    work->f90E = 0;
}

void d18a_snake18_800CB908(Snake18Work *work, PUNCH *arg1)
{
    TARGET *t = &work->f7EC;
    SVECTOR sp18;
    int     mode;

    GM_SetTarget(t, 4, work->f930, &arg1->size);
    DG_RotVector(&arg1->field_10, &sp18, 1);

    mode = arg1->faint;
    if (mode == 1)
        GM_SetPowerTarget(t, 3, 3, arg1->life, mode, &sp18);
    else
        GM_SetPowerTarget(t, 3, 4, arg1->life, mode, &sp18);

    DG_PutVector(&arg1->field_0, &sp18, 1);
    GM_MoveTarget(t, &sp18);
    GM_PowerTarget(t);
}

int d18a_snake18_800CB9CC(Snake18Work *arg0, PUNCH *arg1)
{
    SVECTOR sp18;
    TARGET *temp_s1;
    int     temp_v0;

    temp_s1 = &arg0->f7EC;
    GM_SetTarget(temp_s1, 2, arg0->f930, (SVECTOR *)((char *)arg1 + 0x8));
    GM_SetCaptureTarget(temp_s1, arg1->life, arg1->faint, &arg0->f840, &arg0->f848);
    DG_PutVector((SVECTOR *)arg1, &sp18, 1);
    GM_MoveTarget(temp_s1, &sp18);
    temp_v0 = (int)GM_CaptureTarget(temp_s1);
    arg0->f834 = temp_v0;
    return temp_v0 != 0;
}
int d18a_snake18_800CBA64(Snake18Work *work, PUNCH *arg1)
{
    TARGET *target;
    SVECTOR vec;
    TARGET *t;

    target = &work->f7EC;
    GM_SetTarget(target, 0x40, work->f930, (SVECTOR *)((char *)arg1 + 0x8));
    GM_SetCaptureTarget(target, arg1->life, 0, &work->f840, &work->f848);
    DG_PutVector((SVECTOR *)arg1, &vec, 1);
    GM_MoveTarget(target, &vec);
    t = GM_C4Target(target);
    work->f834 = (int)t;
    if (t == NULL)
    {
        return 0;
    }
    if (t->class & 0x20)
    {
        t->damaged &= ~0x40;
        work->f834 = 0;
        return 0;
    }
    return 1;
}
static inline int d18a_snake18_CanWatch(Snake18Work *work, int flags)
{
    if (work->f8C0 == d18a_snake18_800CE7BC || (GM_PlayerStatus & flags) || (work->f7E4 & 4) || dword_8009F46C[0])
    {
        return 0;
    }
    return 1;
}

void d18a_snake18_800CBB34(Snake18Work *work)
{
    if ((work->pad->press & PAD_TRIANGLE) &&
        d18a_snake18_CanWatch(work, PLAYER_WATCH | PLAYER_ACT_ONLY | PLAYER_ATTACK))
    {
        d18a_snake18_800CB34C(work);
    }
}

int d18a_snake18_800CBBC8(Snake18Work *work)
{
    unsigned short press = work->pad->press;
    int            tbl = work->f868;
    unsigned short input = press;

    if (!(tbl & 0x100))
    {
        input = work->pad->status;
    }

    if (press & PAD_CIRCLE)
    {
        if ((work->f8A8->attack->field_0[2] ^ 0x9E) != 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800D3774);
            work->f7E4 |= 4;
        }
        return 1;
    }

    if (work->f864 >= 0 && *work->f860 == 0)
    {
        return 0;
    }

    if (input & PAD_SQUARE)
    {
        work->f858 = 0;

        if (tbl & 0x10)
        {
            d18a_snake18_StartAnim(work, (void *)work->f854);
            work->f7E4 |= 4;
            return 1;
        }

        if (tbl & 8)
        {
            d18a_snake18_StartAnim(work, (GM_PlayerStatus & PLAYER_MOVE) ? d18a_snake18_800D1B3C : d18a_snake18_800D1A6C);
        }
        else
        {
            d18a_snake18_StartAnim(work, (input & PAD_CROSS) ? d18a_snake18_800D1B3C : d18a_snake18_800D1A6C);
        }

        GM_PlayerStatus |= PLAYER_ATTACK;
        return 1;
    }

    return 0;
}

void d18a_snake18_800CBD34( Snake18Work *work )
{
    if ( work->f864 != 6 && work->pad->press & PAD_CIRCLE )
    {
        work->f8B4 = d18a_snake18_800CF990;
        work->f8B8 = 0;
        work->f7E4 |= 0x100;
    }
}

void d18a_snake18_800CBD80(Snake18Work *work)
{
    if (work->f864 != 6)
    {
        return;
    }
    if (*work->f860 == 0)
    {
        return;
    }
    if (bakudan_count_8009F42C >= 0x10)
    {
        return;
    }
    if (!(GM_PlayerStatus & 0x10))
    {
        work->control.turn.vy = d18a_dword_800DAEF4;
    }
    if (!(work->pad->press & PAD_Y))
    {
        return;
    }
    if (work->f8B4 == d18a_snake18_800D22C8)
    {
        return;
    }
    if (d18a_snake18_800CB1C8(work) <= 0)
    {
        return;
    }

    work->f900 = 0x1C2;
    work->f8B4 = d18a_snake18_800D22C8;
    work->f8B8 = 0;
    work->f7E4 |= 0x100;
}

void d18a_snake18_800CBE58(Snake18Work *work)
{
    int state = work->f864;
    if (state == 5 || state == 6 || state == 2 || state == 7 || state == 8)
    {
        short *p = work->f860;
        if (*p == 0)
        {
            *p = -1;
            GM_Weapon = -1;
            GM_WeaponChanged = 1;
        }
    }
}

static inline int d18a_snake18_CBEC0_check(Snake18Work *work)
{
    unsigned int i;

    if (!(GM_StatusEvent & 1))        return 0;
    if (GM_AlertMode != 0)            return 0;
    if (GM_PlayerStatus & 0x814)      return 0;
    if (GM_PlayerStatus & 0x11002)    return 1;

    for (i = 0; i < 3; i++)
    {
        if (work->f8AC == d18a_dword_800C37E4[i])
        {
            return 1;
        }
    }

    return 0;
}

void d18a_snake18_800CBEC0(Snake18Work *work)
{
    if (d18a_snake18_CBEC0_check(work))
    {
        work->f92C++;
        if ((unsigned short)work->f92C >= 0x78)
        {
            work->f92C = 0;
            work->f8AC = d18a_snake18_800CFB04;
            work->f8B0 = 0;
            work->f912 = 0;
            work->f910 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

void d18a_snake18_800CBF98(Snake18Work *work)
{
    unsigned short counter;
    if (!(GM_StatusEvent & 2)) return;
    if (GM_PlayerStatus & PLAYER_ACT_ONLY) return;

    counter = work->f92E + 1;
    work->f92E = counter;
    if (counter < 300) return;

    work->f92E = 0;
    work->f8B4 = d18a_snake18_800CFD18;
    work->f8B8 = 0;
    work->f7E4 |= 0x100;
}

void d18a_snake18_800CC008(void)
{
    /* do nothing */
}

static inline int d18a_snake18_IsCrouching(Snake18Work *work)
{
    int action;

    if (work->f7E4 & 0x200)
    {
        return 0;
    }

    action = work->body.action;
    if (action == work->f8A8->move->crouch || action == work->f8A8->move->crouch_backwards ||
        action == work->f8A8->trans->crouch)
    {
        return 1;
    }

    return 0;
}

void d18a_snake18_800CC010(Snake18Work *work)
{
    unsigned short *names;
    int             i;
    int             status;
    int             action;

    if (!d18a_snake18_IsCrouching(work))
    {
        return;
    }

    status = GM_PlayerStatus;
    status &= ~PLAYER_INTRUDE;
    names = work->control.evt.inside;
    for (i = work->control.evt.n_inside; i > 0; i--, names++)
    {
        if (*names == 0x73D2)
        {
            status |= PLAYER_INTRUDE;
        }
    }

    if (status == GM_PlayerStatus)
    {
        return;
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        GM_PlayerStatus &= ~PLAYER_INTRUDE;
        return;
    }

    if (work->body.action == work->f8A8->trans->crouch)
    {
        action = work->f8A8->move->crouch;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
    }

    GM_PlayerStatus |= PLAYER_INTRUDE;
    d18a_snake18_StartAnim(work, d18a_snake18_800CE998);
}
void d18a_snake18_800CC174(Snake18Work *work, GV_MSG *msg)
{
    Snake18Queue *queue;
    int           len;
    int           n;
    int           a;
    int           b;
    short        *p;

    if (GM_PlayerStatus & PLAYER_ACT_ONLY)
    {
        return;
    }

    if (work->f92A == 0)
    {
        return;
    }

    len = msg->message_len;
    if (len < 2)
    {
        return;
    }

    queue = &work->f8D8;
    n = queue->count;
    if (n == 4)
    {
        return;
    }

    a = -1;
    b = -1;
    *(queue->field_2 + n) = msg->message[1];
    p = &queue->field_A[n];
    if (len < 3)
    {
        *p = -1;
    }
    else
    {
        *p = msg->message[2];
    }

    if (len >= 4)
    {
        a = msg->message[3];
        if (len >= 5)
        {
            b = msg->message[4];
        }
        if (len >= 6 && msg->message[5] == 1)
        {
            GM_PlayerStatus &= ~PLAYER_INTRUDE;
            d18a_snake18_800CB42C(work);
        }
    }

    queue->count = ++n;
    queue->field_12 = a;
    queue->field_14 = b;
}

int d18a_snake18_800CC288(SVECTOR *pos, short *out)
{
    int vz = pos->vz;
    int vx = pos->vx;

    if (vz >= 0x128F)
    {
        printf("climb area  0 \n");
        *out = 0x800;
        return 0;
    }
    if (vz < -0x4E2)
    {
        printf("climb area  4 \n");
        *out = 0xFE8;
        return 4;
    }
    if (vx < -0x2EE)
    {
        printf("climb area  3 \n");
        *out = 0x400;
        return 3;
    }
    if (vx < 0x4E2)
    {
        printf("climb area  2 \n");
        *out = 0x6D2;
        return 2;
    }
    if (vx < 0x9C4)
    {
        printf("climb area  1 \n");
        *out = 0x480;
        return 1;
    }
    if (vx < 0xCB2)
    {
        printf("climb area  7 \n");
        *out = 0xB42;
        return 7;
    }
    else if (vx < 0x157C)
    {
        printf("climb area  6 \n");
        *out = 0x911;
        return 6;
    }
    else
    {
        printf("climb area  5 \n");
        *out = 0xBE8;
        return 5;
    }
}
int d18a_snake18_800CC3C8(int area)
{
    switch (area)
    {
    case 2:
    case 5:
    case 6:
    case 7:
        return 0;

    case 0:
    case 1:
    case 3:
        return 1;

    case 4:
        return 2;
    }

    return 0;
}

int d18a_snake18_800CC410(Snake18Work *work)
{
    SVECTOR near;

    if (work->control.vecs[0].pad == 1)
    {
        return 1;
    }

    if (HZD_OnlineHazardCheck(work->control.map->hzd, &work->control.mov,
                              &d18a_dword_800C3868, HZD_CHK_F_SEGMENT, 4) == 0)
    {
        return 0;
    }

    HZD_GetOnlineVector(&near);

    if (near.vx == 0)
    {
        if (near.vz == 0)
        {
            return 0;
        }
    }
    return 1;
}
const char d18a_aErrerrerrliquidnearerr_800DA648[] = " Err Err Err Liquid Near Err !! \n";
const char d18a_aSnakeposddd_800DA66C[] = "snake pos1 %d %d %d \n";
const char d18a_aWorkheightdlevelsd_800DA684[] = "work->height %d levels%d \n";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC490.s")
#define HASH_DESTROY 0xA7DE /* GV_StrCode("destroy") */
#define HASH_TURN_SPEED    0xC77A

void d18a_snake18_800CC6CC(Snake18Work *work)
{
    GV_MSG *msg;
    int     n;
    int     i;
    int     len;

    n = work->control.n_msg;
    if (!n)
    {
        n = d18a_snake18_800CC490(work);
        if (!n)
        {
            return;
        }
    }

    msg = (work->control.msg + n) - 1;
    for (i = n; i > 0; i--, msg--)
    {
        len = msg->message_len;
        switch (msg->message[0])
        {
        case HASH_TURN_SPEED:
            if (len >= 2 && (GM_PlayerStatus & PLAYER_INTRUDE))
            {
                d18a_dword_800C37E0 = msg->message[1];
                work->f8C4.f8 = d18a_dword_800C37E0;
                work->f8C4.fC = d18a_dword_800C37E0;
            }
            break;

        case HASH_DESTROY:
            GV_DestroyActor(&work->actor);
            break;

        case HASH_MOTION:
            d18a_snake18_800CC174(work, msg);
            break;
        }
    }
}
void d18a_snake18_800CC7F4(Snake18Work *work)
{
    if (GM_PlayerStatus & 4)
    {
        return;
    }
    if (work->f92A == 0)
    {
        return;
    }
    if (work->f8D8.count == 0)
    {
        return;
    }

    GM_ConfigMotionControl(&work->body, &work->m_ctrl, work->f92A,
                           work->m_segs1, work->m_segs2, &work->control, work->rots);

    work->f8AC = d18a_snake18_800D01D8;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->f8EE = work->control.height;
    GM_PlayerStatus |= 4;
    d18a_snake18_800CB378(work);
}

void d18a_snake18_800CC8B0(Snake18Work *work, char arg1)
{
    int    mask = PLAYER_INVINCIBLE;
    short *p    = work->f7E8;
    GM_PlayerStatus |= mask;
    work->f8FC = arg1;
    *p &= 0xFF61;
}

void d18a_snake18_800CC8E0(Snake18Work *arg0)
{
    short *p = arg0->f7E8;
    short v = *p;
    GM_PlayerStatus &= ~PLAYER_INVINCIBLE;
    *p = v | 0x9E;
}

static inline int d18a_snake18_CanBlink(Snake18Work *work)
{
    if ((work->f7E4 & 1) || (GM_PlayerStatus & (PLAYER_WATCH | PLAYER_INTRUDE)))
    {
        return 0;
    }

    return 1;
}

static inline int d18a_snake18_NoShake(Snake18Work *work)
{
    if ((work->f7E4 & 2) || (GM_PlayerStatus & (PLAYER_CB_BOX | PLAYER_INTRUDE)) || (work->f868 & 0x200) ||
        (work->f89C == 1))
    {
        return 0;
    }

    return 1;
}

void d18a_snake18_800CC90C(Snake18Work *work)
{
    int iframes;

    iframes = work->f8FC;
    if (iframes != 0)
    {
        if (--iframes > 0)
        {
            if (d18a_snake18_CanBlink(work))
            {
                if (iframes & 3)
                {
                    DG_VisibleObjs(work->body.objs);
                }
                else
                {
                    DG_InvisibleObjs(work->body.objs);
                }
            }

            if (GM_Camera.first_person != 0 && !d18a_snake18_NoShake(work))
            {
                GM_SnakeCamera.position.vy += GV_RandU(16) * iframes;
            }
        }
        else if (!(work->f7E4 & 0x10000))
        {
            d18a_snake18_800CC8E0(work);
            work->f7E4 &= ~1;
        }

        work->f8FC = iframes;
    }
    else if (GM_Camera.first_person != 0)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }

    iframes = work->f8FD;
    if (iframes != 0)
    {
        if (--iframes == 0)
        {
            d18a_snake18_800CC8E0(work);
            work->f7E4 &= ~0x10000;
        }

        work->f8FD = iframes;
    }
}

void d18a_snake18_800CCB0C(TARGET *target)
{
    target->damaged &= ~(TARGET_CAPTURE | TARGET_POWER | TARGET_TOUCH);
    target->damage = 0;
    target->faint = 0;
    target->force = DG_ZeroVector;
}

void d18a_snake18_800CCB50(Snake18Work *work)
{
    TARGET *target;
    int     damaged;
    int     a_mode;

    if (GM_PlayerStatus & PLAYER_INVINCIBLE)
    {
        d18a_snake18_800CC90C(work);
        return;
    }

    target = (TARGET *)work->f7E8;
    damaged = target->damaged;

    if (damaged & (TARGET_POWER | TARGET_CAPTURE))
    {
        a_mode = target->a_mode;

        if (d18a_snake18_NoShake(work))
        {
            GM_PlayerStatus |= PLAYER_DAMAGED;

            if (work->f834)
            {
                ((TARGET *)work->f834)->damaged &= ~TARGET_CAPTURE;
                work->f834 = 0;
                work->f924 = 0;
            }

            d18a_snake18_800CB838(work);
            DG_InvisiblePrim(work->f874);
            GM_ConfigMotionAdjust(&work->body, NULL);
            GM_ExitBehindCamera();

            if (GM_PlayerStatus & PLAYER_ACT_ONLY)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800D00E0);
            }
            else if (damaged & TARGET_CAPTURE)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800CEF44);
            }
            else if (a_mode == 1 || a_mode == 3)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800CF03C);
                GM_SeSet(&work->control.mov, 0x26);

                if (!(GM_GameStatus & STATE_STUN))
                {
                    NewPadVibration(d18a_dword_800C3800, 1);
                    NewPadVibration(d18a_dword_800C3804, 2);
                }

                work->f7E4 &= ~4;
            }
            else
            {
                work->f904 = target->force;
                d18a_snake18_StartAnim(work, d18a_snake18_800CF198);
                d18a_snake18_800CB378(work);
                work->f7E4 |= 4;
                GM_SeSet(&work->control.mov, 0x19);

                if (!(GM_GameStatus & STATE_STUN))
                {
                    NewPadVibration(d18a_dword_800C380C, 1);
                    NewPadVibration(d18a_dword_800C3810, 2);
                }
            }

            work->f900 = 0x1C2;
            GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_SQUAT | PLAYER_ATTACK | PLAYER_MENU_DISABLE |
                                 PLAYER_CAUTION | PLAYER_CHECK_WALL);

            if (work->body.action2 != 0)
            {
                GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
            }
        }
        else
        {
            d18a_snake18_800CC8B0(work, 0x20);
            d18a_snake18_800CB7D0(work, 6);
            GM_SeSet(&work->control.mov, 0x26);

            if (!(GM_GameStatus & STATE_STUN))
            {
                if (a_mode == 1 || a_mode == 3)
                {
                    NewPadVibration(d18a_dword_800C3800, 1);
                    NewPadVibration(d18a_dword_800C3804, 2);
                }
                else
                {
                    NewPadVibration(d18a_dword_800C380C, 1);
                    NewPadVibration(d18a_dword_800C3810, 2);
                }
            }

            if (((TARGET *)work->f7E8)->vital <= 0)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800CF39C);
            }
        }

        work->f90E = 0xFF;
        work->f90D = 8;
        d18a_snake18_800CCB0C(target);
    }
    else if (damaged & TARGET_TOUCH)
    {
        d18a_snake18_800CC8B0(work, 0x20);
        d18a_snake18_800CCB0C(target);
        work->f90E = 0xFF;
        work->f90D = 8;
    }
}

void d18a_snake18_800CCF30(Snake18Work *work)
{
    WeaponCreateEntry *e;
    void *(*fn)(CONTROL *, OBJECT *, int, int *, int);
    int wid;
    void *actor = work->f850;

    if (actor)
    {
        GV_DestroyActor(actor);
    }

    actor = NULL;
    work->f864 = GM_Weapon;
    wid = GM_Weapon;
    work->f868 = GM_WeaponTypes[wid + 1];

    e = &d18a_dword_800C3878[wid];
    if (GM_Weapon >= 0)
    {
        work->f860 = &GM_Weapons[ GM_Weapon ];
    }

    d18a_snake18_800CB7BC(work, (int)e->mStateFn);
    fn = e->mCreateActorFn;
    if (fn)
    {
        actor = fn(&work->control, &work->body, 4, &work->f85C, work->f930);
    }
    work->f850 = actor;

    work->f8A8 = &d18a_dword_800C36C8[GM_Weapon];
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD040.s")
typedef void *(*Snake18EquipFn)(CONTROL *, OBJECT *, int);

void d18a_snake18_800CD2C4(Snake18Work *work, int item)
{
    GV_ACT        *actor;
    int            type;
    Snake18EquipFn equip;
    Snake18EquipFn *pfn;

    actor = work->f898;
    if (actor)
    {
        GV_DestroyActorQuick(actor);
    }

    work->f89C = item;
    pfn = (Snake18EquipFn *)&d18a_dword_800C38C8[item];
    type = work->f8A0 = GM_ItemTypes[item + 1];
    GM_PlayerStatus &= ~PLAYER_CB_BOX;
    actor = NULL;

    if ((type & 0x8000) && *pfn)
    {
        equip = *pfn;
        if (item == IT_Box1 || item == IT_Box2 || item == IT_Box3)
        {
            GM_PlayerStatus |= PLAYER_CB_BOX;
            actor = equip(&work->control, &work->body, 0);
        }
        else
        {
            actor = equip(&work->control, &work->body, 6);
        }
    }

    work->f898 = actor;

    if (type & 1)
    {
        if (item == IT_Scope)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CFEE8);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CFF5C);
        }
    }
    else if (!(work->f868 & 0x200))
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
        }
        else if (GM_PlayerStatus & PLAYER_CAUTION)
        {
            d18a_snake18_StartAnim(work, d18a_dword_800C37F0[work->f8FE]);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->f8FE]);
        }
    }

    if (type & 2)
    {
        d18a_snake18_800CB34C(work);
    }
    else if (!(work->f868 & 0x200) && !(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        d18a_snake18_800CB378(work);
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD4C0.s")

void d18a_snake18_800CD64C(Snake18Work *work, int arg1)
{
    int   new_action;
    ACTSTILL18 *still;

    if (arg1 == 0)
    {
        work->f8BC = d18a_snake18_800CDD4C;
        work->f8FE = 0;
        work->f8C0 = d18a_snake18_800D1424;

        if (GM_AlertMode == 3 || GM_AlertMode == 4)
        {
            new_action = work->f8A8->still->setup;
        }
        else
        {
            new_action = work->f8A8->still->stand;
        }
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }

    still = work->f8A8->still;
    if (work->body.action == still->stand)
    {
        if (GM_AlertMode == 3 || GM_AlertMode == 4)
        {
            new_action = still->setup;
            if (work->body.action != new_action)
            {
                GM_ConfigObjectAction(&work->body, new_action, 0, 4);
            }
        }
    }

    if (work->control.mov.vy < 0x1770)
    {
        work->control.mov.vx = 0x7D0;
        work->control.mov.vy = 0x2F44;
        work->control.mov.vz = 0x1F4;
    }
}

void d18a_snake18_800CD768(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 != 0)
    {
        return;
    }

    if (work->f8FE == 0)
    {
        GM_SeSet(&work->control.mov, 8);
    }
    work->f8FE = 1;

    work->f8BC = d18a_snake18_800CDE8C;
    work->f8C0 = d18a_snake18_800D1424;
    GM_PlayerStatus |= 0x20;

    new_action = work->f8A8->still->squat;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }

    work->f904.vy = -0x80;
}

void d18a_snake18_800CD808(Snake18Work *work, int arg1)
{
    int new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f8FE = 2;
    work->f900 = 0x1C2;
    work->f8BC = d18a_snake18_800CDFC8;
    work->f8C0 = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_GROUND;
    new_action = work->f8A8->still->crouch;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}

void d18a_snake18_800CD888(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 != 0)
    {
        return;
    }

    work->f8BC = d18a_snake18_800CE09C;
    work->f8C0 = d18a_snake18_800D1424;
    GM_PlayerStatus |= 0x10;

    if (GM_AlertMode == 3)
    {
        new_action = work->f8A8->move->aim;
    }
    else
    {
        new_action = work->f8A8->move->stand;
    }

    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}

void d18a_snake18_800CD930(Snake18Work *work, int arg1)
{
    int new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f900 = 0x1C2;
    work->f8BC = d18a_snake18_800CE210;
    work->f8C0 = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_MOVE;
    new_action = work->f8A8->move->crouch;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD9A8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDB04.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDC3C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDD4C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDE8C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDFC8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE09C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE210.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE38C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE4E4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE6B0.s")

void d18a_snake18_800CE7BC(void)
{
    /* do nothing */
}

void d18a_snake18_800CE7C4(Snake18Work *work, int arg1)
{
    int new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f8BC = d18a_snake18_800CED2C;
    work->f8C0 = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_MOVE;
    new_action = work->f8A8->move->setup;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}
void d18a_snake18_800CE834(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        GM_SeSet(&work->control.mov, 8);
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800CE7BC;
        GM_PlayerStatus |= 0x40;
        new_action = work->f8A8->trans->crouch;
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
        work->f8FE = 2;
    }

    if (work->body.is_end != 0)
    {
        work->f8AC = d18a_snake18_800CD808;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void d18a_snake18_800CE8E0(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        GM_SeSet(&work->control.mov, 8);
        work->f8FE = 0;
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800CE7BC;
        new_action = work->f8A8->trans->stand;
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }

    if (arg1 == 2)
    {
        work->control.turn.vx = 0;
    }

    if (work->body.is_end != 0)
    {
        work->f8AC = d18a_snake18_800CD64C;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void d18a_snake18_800CE998(Snake18Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->f8BC = d18a_snake18_800CEDB0;
        work->f8C0 = d18a_snake18_800CE7BC;
        d18a_snake18_800CC8B0(work, 0);
        work->f7E4 |= 0x232;
        if (GM_PlayerStatus & 2)
        {
            d18a_snake18_800CB3E8(work);
        }
        else
        {
            d18a_snake18_800CB42C(work);
        }
    }

    if (arg1 != 0x18)
    {
        return;
    }

    printf(" kore5 \n ");
    d18a_snake18_800CC8E0(work);
    work->f7E4 &= ~0x232;

    if (GM_PlayerStatus & 2)
    {
        work->f8AC = d18a_snake18_800CEF0C;
    }
    else
    {
        work->f8AC = d18a_snake18_800CD930;
    }
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void d18a_snake18_800CEA84(Snake18Work *work, int arg1)
{
    int            new_action;
    unsigned short save_924;

    if (arg1 == 0)
    {
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800CE7BC;
        new_action = work->f8A8->attack->field_0[3];
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 2);
        }

        work->m_ctrl.info2.mask = -1;
        work->f7E4 |= 6;
        save_924 = work->f924;
        work->m_ctrl.info1.mask = 0;
        work->f924 = 0;
        GM_PlayerStatus &= ~0x800;
        work->control.turn.vy = save_924;
    }

    if (work->body.is_end != 0)
    {
        work->f858 = 0;
        GM_PlayerStatus |= 0x800;
        work->f7E4 &= ~6;
        GM_SeSet(&work->control.mov, 0x2F);

        work->f8AC = d18a_snake18_800D1A6C;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void d18a_snake18_800CEB78(Snake18Work *work, int arg1)
{
    int mask;
    int new_action;

    if (arg1 == 0)
    {
        mask = (GM_PlayerStatus & 0x10) ? 0x3FE : 0xFFFF;
        new_action = work->f8A8->attack->field_0[0];
        if (work->body.action2 != new_action)
        {
            GM_ConfigObjectOverride(&work->body, new_action, 0, 4, mask);
        }
        work->f910 = 0;
    }

    if (work->pad->release & 0x80)
    {
        work->f910 = 1;
    }

    if (work->pad->status & 0x80)
    {
        work->f86E += 1;
    }
    else
    {
        work->f86E = 0;
    }

    if (arg1 == 4)
    {
        d18a_snake18_800CB7BC(work, (int)d18a_snake18_800D2A80);
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEC68.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CECE0.s")

void d18a_snake18_800CED2C(Snake18Work *work, int arg1)
{
    if (arg1 == 2 && d18a_dword_800DAEF0 >= 0)
    {
        work->f8AC = d18a_snake18_800CD888;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (work->body.is_end == 0)
    {
        return;
    }

    work->f8AC = d18a_snake18_800CD64C;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x10;
}

void d18a_snake18_800CEDB0(Snake18Work *work)
{
    if (GM_PlayerStatus & 2)
    {
        return;
    }
    if (!(work->pad->press & PAD_B))
    {
        return;
    }
    if (d18a_snake18_800CAF20(work) != 0)
    {
        return;
    }
    work->f900 = 0x1C2;
    d18a_snake18_800CC8E0(work);
    work->f8AC = d18a_snake18_800CE8E0;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x50;
    work->f7E4 &= ~0x212;
}
void d18a_snake18_800CEE60(Snake18Work *work)
{
    int arg;
    if (((unsigned char *)&work->f7E4)[1] & 1)
    {
        arg = work->f8B8;
        work->f8B8 = arg + 1;
        ((void (*)(Snake18Work *, int))work->f8B4)(work, arg);
    }
}

void d18a_snake18_800CEEAC(Snake18Work *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }

    {
        ACTPACK18 *t = work->f8A8;
        int new_act;
        work->f8BC = d18a_snake18_800D09B4;
        work->f8C0 = d18a_snake18_800D1750;
        new_act = t->still->crouch;
        if (work->body.action != new_act)
        {
            GM_ConfigObjectAction(&work->body, new_act, 0, 4);
        }
    }
}

void d18a_snake18_800CEF0C(Snake18Work *work, int arg1)
{
    int status;

    if (arg1 != 0)
    {
        return;
    }

    work->f8BC = d18a_snake18_800D0A10;
    status = GM_PlayerStatus;
    work->f8C0 = d18a_snake18_800D1750;
    GM_PlayerStatus = status | PLAYER_MOVE;
}

void d18a_snake18_800CEF44(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800CE7BC;
        d18a_snake18_800CC8B0(work, 0);
        new_action = work->f8A8->damage->field_0[9];
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }
    if (arg1 == 0x14)
    {
        GM_SeSet(&work->control.mov, 0x26);
    }
    if (arg1 == 0x2D)
    {
        GM_SeSet(&work->control.mov, 0x33);
    }
    if (work->body.is_end != 0)
    {
        d18a_snake18_800CC8B0(work, 0x20);
        work->f924 = 2;
        work->f8AC = d18a_snake18_800CF744;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_DAMAGED;
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF03C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF198.s")
const char d18a_aWorkglobaldatad_800DA6AC[] = " work->global_data = %d \n ";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF39C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF574.s")

void d18a_snake18_800CF718(int arg0, int arg1)
{
    if (arg1 == 0x258)
    {
        GM_GameOverTimer = 0;
        GM_GameOver();
    }
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF744.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF850.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF990.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFB04.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFD18.s")

void d18a_snake18_800CFEE8(Snake18Work *work, int arg1)
{
    int new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f8BC = d18a_snake18_800CE7BC;
    work->f8C0 = d18a_snake18_800CE7BC;
    new_action = d18a_snake18_800CB280(work, work->f8FE);
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
    GM_PlayerStatus &= ~PLAYER_MENU_DISABLE;
}

void d18a_snake18_800CFF5C(Snake18Work *work, int arg1)
{
    ACTPACK18 *actpack;
    int        new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f8BC = d18a_snake18_800D0B4C;
    actpack = work->f8A8;
    work->f8C0 = d18a_snake18_800D18EC;
    work->f8FE = 0;
    GM_PlayerStatus &= ~(PLAYER_GROUND | PLAYER_SQUAT);
    new_action = actpack->special2->field_0[2];
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}

void d18a_snake18_800CFFD4(Snake18Work *work, int arg1)
{
    ACTPACK18 *actpack;
    int        new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->f8BC = d18a_snake18_800D0B84;
    actpack = work->f8A8;
    work->f8C0 = d18a_snake18_800D18EC;
    GM_PlayerStatus |= PLAYER_MOVE;
    new_action = actpack->special2->field_0[3];
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
    GM_ConfigControlInterp(&work->control, 4);
}
void d18a_snake18_800D0054(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800CE7BC;

        new_action = work->f8A8->special2->field_0[4];
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }

    if (work->body.is_end != 0)
    {
        work->f8AC = d18a_snake18_800CFF5C;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void d18a_snake18_800D00E0(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        GM_SeSet(&work->control.mov, 0x26);
        GM_ConfigControlHazard(&work->control, 0, -2, -2);
        work->f900 = -2;
        work->f8BC = d18a_snake18_800CE7BC;
        work->f8C0 = d18a_snake18_800D1814;
        d18a_snake18_800CC8B0(work, 0);
        work->body.action = -1;
        new_action = work->f8F0 + 9;
        if (new_action != -1)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
        d18a_snake18_800CB7D0(work, 4);
    }

    if (work->body.is_end != 0)
    {
        work->f8AC = d18a_snake18_800D01D8;
        work->f8F4 = 1;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~0x100;
    }
}
const char d18a_aForceactdirdactiondnactsd_800DA6C8[] = "force act dir=%d action=%d n_acts=%d\n";
const char d18a_aSnakeposddd_800DA6F0[] = "snake pos2 %d %d %d \n";
const char d18a_aSnakesetactiond_800DA708[] = " snake set action = %d \n";
const char d18a_aNextmotiondlocaldatad_800DA724[] = "next motion=%d  local_data=%d\n";
const char d18a_aSnevs_800DA744[] = "sne_18vs";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D01D8.s")

void d18a_snake18_800D0974( Snake18Work *work )
{
    u_short status;

    status = work->pad->status;
    if ( status & ( PAD_LEFT | PAD_RIGHT ) )
    {
        int turn;

        turn = work->control.turn.vy;
        if ( status & PAD_LEFT )
        {
            turn += 32;
        }
        else
        {
            turn -= 32;
        }

        work->control.turn.vy = turn;
    }
}

void d18a_snake18_800D09B4( Snake18Work *work )
{
    u_short status;

    status = work->pad->status;
    if ( status & ( PAD_UP | PAD_DOWN ) )
    {
        work->f8AC = d18a_snake18_800CEF0C;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        d18a_snake18_800D0974( work );
    }
}

void d18a_snake18_800D0A10(Snake18Work *work)
{
    int status;
    int flag;
    int new_action;

    status = GM_PlayerStatus;
    if (!(status & 2))
    {
        work->f8AC = d18a_snake18_800CE998;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    flag = (unsigned short)work->pad->status;
    if (!(flag & (PAD_U | PAD_D)))
    {
        GM_PlayerStatus = status & ~0x10;
        work->f8AC = d18a_snake18_800CEEAC;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (flag & PAD_U)
    {
        new_action = work->f8A8->move->crouch;
    }
    else
    {
        new_action = work->f8A8->move->crouch_backwards;
    }
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
    d18a_snake18_800D0974(work);
}

void d18a_snake18_800D0AF8( Snake18Work *work)
{
    if ( work->pad->press & ~PAD_TRIANGLE )
    {
        work->f8AC = d18a_snake18_800CF850;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_GROUND;
    }
}

void d18a_snake18_800D0B4C(Snake18Work *work)
{
    if (d18a_dword_800DAEF0 < 0)
    {
        return;
    }

    work->f8AC = d18a_snake18_800CFFD4;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void d18a_snake18_800D0B84(Snake18Work *work)
{
    int state = d18a_dword_800DAEF0;
    if (state < 0)
    {
        work->f8AC = d18a_snake18_800D0054;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_MOVE;
    }
    else
    {
        work->control.turn.vy = d18a_snake18_800CAEC0(work, state);
    }
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0BF4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0E3C.s")
void d18a_snake18_800D1064(Snake18Work *work)
{
    unsigned short  status = work->pad->status;
    int             turn;
    int             n;
    int             d;
    Snake18Init    *init = &work->f8C4;

    if (!(status & 0xA000))
    {
        return;
    }

    turn = work->control.turn.vy;

    if (status & 0x8000)
    {
        if (work->f7E4 & 0x4000)
            n = 0x50 - work->pad->left_dx;
        else
            n = 1;

        if (work->f7E4 & 0x4000)
            d = 0x50;
        else
            d = 1;

        turn += init->f10 * (n & 0xFF) / d;
    }
    else
    {
        if (work->f7E4 & 0x4000)
            n = work->pad->left_dx + 0x50;
        else
            n = 1;

        if (work->f7E4 & 0x4000)
            d = 0x4F;
        else
            d = 1;

        turn -= init->fE * (n & 0xFF) / d;
    }

    work->control.turn.vy = turn;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D11A8.s")
void d18a_snake18_800D1300(Snake18Work *work)
{
    GV_PAD         *pad = work->pad;
    unsigned short  status = pad->status;
    int             turn;

    if (!(status & 0xA000))
    {
        return;
    }

    turn = work->control.turn.vy;

    if (status & 0x8000)
    {
        int n;
        int d;

        if (work->f7E4 & 0x4000)
            n = 0x50 - pad->left_dx;
        else
            n = 1;

        if (work->f7E4 & 0x4000)
            d = 0x50;
        else
            d = 1;

        turn += ((n & 0xFF) << 1) / d;
    }
    else
    {
        int n;
        int d;

        if (work->f7E4 & 0x4000)
            n = pad->left_dx + 0x50;
        else
            n = 1;

        if (work->f7E4 & 0x4000)
            d = 0x4F;
        else
            d = 1;

        turn -= ((n & 0xFF) << 1) / d;
    }

    work->control.turn.vy = turn;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1424.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1598.s")

void d18a_snake18_800D1750(Snake18Work *work)
{
    int new_action;

    GM_PlayerStatus &= ~0x10;
    new_action = work->f8A8->still->crouch;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }

    if (!(work->pad->status & PAD_X))
    {
        work->f926 = 0;
        work->f8AC = d18a_snake18_800CEEAC;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~0x8001;
    }

    d18a_snake18_800D0E3C(work);
    d18a_snake18_800D1064(work);
}

void d18a_snake18_800D1814(Snake18Work *work)
{
    if (!(work->pad->status & PAD_X))
    {
        d18a_snake18_800CB378(work);
    }

    if (work->f8AC == d18a_snake18_800CF744)
    {
        if (work->pad->press & ~PAD_X)
        {
            work->f8AC = d18a_snake18_800CF850;
            work->f8B0 = 0;
            work->f912 = 0;
            work->f910 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_PlayerStatus &= ~0x40;
        }
    }

    GM_SnakeCamera.position.vy += 0x140;

    if (work->f8AC != d18a_snake18_800CF03C)
    {
        d18a_snake18_800CB514(work);
    }
}

void d18a_snake18_800D18EC(Snake18Work *work)
{
    int new_action;

    GM_PlayerStatus &= ~0x10;
    new_action = work->f8A8->special2->field_0[2];
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }

    if (work->pad->status & PAD_X)
    {
        return;
    }

    d18a_snake18_800CB378(work);
    work->f8AC = d18a_snake18_800CFF5C;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void d18a_snake18_800D198C(Snake18Work *work, int amount)
{
    int scale;

    if (!(work->pad->status & PAD_X))
    {
        d18a_snake18_800CB378(work);
    }

    if (amount < 0x21)
    {
        scale = 0x20 - amount;
    }
    else
    {
        scale = 0;
    }

    GM_SnakeCamera.position.vy += GV_RandU(0x10) * scale;
}
void d18a_snake18_800D1A08(Snake18Work *work)
{
    int arg;
    void (*func)(Snake18Work *, int);

    if ((work->f868 & 0x40) && (GM_PlayerStatus & PLAYER_ATTACK))
    {
        func = (void (*)(Snake18Work *, int))work->f854;
        if (func != NULL)
        {
            arg = work->f858;
            work->f858 = arg + 1;
            func(work, arg);
        }
    }
}

void d18a_snake18_800D1A6C(Snake18Work *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }

    {
        ACTPACK18 *t = work->f8A8;
        int new_act;
        work->f8BC = d18a_snake18_800D24CC;
        work->f8C0 = d18a_snake18_800CE7BC;
        new_act = t->still->setup;
        if (work->body.action != new_act)
        {
            GM_ConfigObjectAction(&work->body, new_act, 0, 4);
        }
    }
}

void d18a_snake18_800D1ACC(Snake18Work *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }

    {
        ACTPACK18 *t;
        int new_act;
        work->f8BC = d18a_snake18_800D2660;
        t = work->f8A8;
        work->f8C0 = d18a_snake18_800CE7BC;
        GM_PlayerStatus |= PLAYER_MOVE;
        new_act = t->move->setup;
        if (work->body.action != new_act)
        {
            GM_ConfigObjectAction(&work->body, new_act, 0, 4);
        }
    }
}

void d18a_snake18_800D1B3C(Snake18Work *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }

    {
        ACTPACK18 *t;
        int new_act;
        work->f8BC = d18a_snake18_800D26E4;
        t = work->f8A8;
        work->f8C0 = d18a_snake18_800CE7BC;
        GM_PlayerStatus |= PLAYER_MOVE;
        new_act = t->move->stand;
        if (work->body.action != new_act)
        {
            GM_ConfigObjectAction(&work->body, new_act, 0, 4);
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1BAC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1CE8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1F90.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D200C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D20EC.s")
void d18a_snake18_800D22C8(Snake18Work *work, int a1)
{
    int s1 = work->f8FE;

    work->control.turn.vy = *(unsigned short *)&d18a_dword_800DAEF4;

    if (a1 == 0)
    {
        int act;

        if (s1 == 0)
            act = work->f8A8->attack->field_0[6];
        else
            act = work->f8A8->attack->field_0[7];

        if (work->body.action2 != act)
        {
            GM_ConfigObjectOverride(&work->body, act, 0, 4, 0xFFFF);
        }
    }

    if ((s1 == 0 && a1 == 6) || (s1 == 1 && a1 == 0xE))
    {
        work->f85C = 3;
    }

    if (work->body.time2 != 0 || work->body.action2 == 0)
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }
        work->f8B4 = 0;
        work->f7E4 &= ~0x100;
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D23F0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D24CC.s")
void d18a_snake18_800D2660(Snake18Work *work, int arg1)
{
    if (arg1 == 2 && d18a_dword_800DAEF0 >= 0)
    {
        work->f8AC = d18a_snake18_800D1B3C;
        work->f8B0 = 0;
        work->f912 = 0;
        work->f910 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (work->body.is_end == 0)
    {
        return;
    }

    work->f8AC = d18a_snake18_800D1A6C;
    work->f8B0 = 0;
    work->f912 = 0;
    work->f910 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x10;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D26E4.s")
void d18a_snake18_800D281C(Snake18Work *work)
{
    int yaw;
    int pitch;
    int diff;

    GM_GetHomingTarget(&work->body.objs->objs[6].world, work->control.rot.vy,
                       &yaw, &pitch, work->control.map->index);

    diff = work->f728 - pitch;
    if (diff >= 0x41)
        pitch = work->f728 - 0x40;
    else if (diff < -0x40)
        pitch = work->f728 + 0x40;

    work->f728 = pitch;
    work->f748 = pitch;
    work->f750 = pitch * 3 / 2;

    if (yaw >= 0)
    {
        work->control.turn.vy = yaw;
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D28CC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2A80.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2D88.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2F70.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3024.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3218.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3330.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3508.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3774.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D37FC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3A1C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3A9C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3B1C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3C14.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3D0C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3ED0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3F3C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D3FE8.s")
void d18a_snake18_800D4084(void)
{
    int s = GM_PlayerStatus & 0x10054;
    if (s != 0x10)
    {
        return;
    }
    if (dword_800AB9D4 == 8)
    {
        GM_SeSet(&GM_PlayerPosition, 0xA9);
    }
    else if (dword_800AB9D4 == s)
    {
        GM_SeSet(&GM_PlayerPosition, 0xA8);
    }
}
const char d18a_aPosddd_800DA750[] = "pos %d %d %d\n";
const char d18a_aCeilfloordd_800DA760[] = "ceil floor %d %d\n";
const char d18a_aStatusx_800DA774[] = "status %4x\n";
const char d18a_aWeapond_800DA780[] = "weapon %d\n";
const char d18a_aItemd_800DA78C[] = "item %d\n";
const char d18a_aFlagx_800DA798[] = "flag %4x\n";
const char d18a_aStanced_800DA7A4[] = "stance %d\n";
const char d18a_aKaze_800DA7B0[] = "kaze \n";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D40F0.s")
const char d18a_aFirst_800DA7B8[] = "first\n";
const char d18a_aSecond_800DA7C0[] = "second\n";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4388.s")
void d18a_snake18_800D46CC(Snake18Work *work)
{
    GV_DestroyOtherActor(work->shadow);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget((TARGET *)work->f7E8);

    GM_FreePrim(work->f874);

    GM_PlayerStance = work->f8FE;

    if (GM_PlayerControl == &work->control)
    {
        GM_PlayerControl = 0;
    }

    if (GM_PlayerBody == &work->body)
    {
        GM_PlayerBody = 0;
    }
}
const char d18a_aLsight_800DA7C8[] = "lsight";
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4784.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D48FC.s")

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D49FC.s")

int d18a_snake18_800D4B84( Snake18Work *work )
{
    d18a_snake18_800CB2EC( work );
    return 0;
}

int d18a_snake18_800D4BA4(Snake18Work *work)
{
    TARGET *target = GM_AllocTarget();
    work->f7E8 = (short *)target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x9F, work->f930, &d18a_dword_800C3A28);
    GM_SetPowerTarget(target, 1, -1, GM_Vitality, 0, &DG_ZeroVector);
    GM_SetCaptureTarget(target, 0, 0, &work->f840, &work->f848);
    return 0;
}

int d18a_snake18_800D4C44( Snake18Work *work, int name, int where )
{
    SVECTOR  shadow;
    CONTROL *ctrl;
    OBJECT  *body;
    char    *opt;
    int      seg_flag;

    if ( name == GV_StrCode( "スネーク" ) )
    {
        work->f930 = HZD_SEG_NO_COLLIDE;
        work->pad = &GV_PadData[ 0 ];
    }
    else
    {
        work->f930 = HZD_SEG_NO_NAVIGATE;
        work->pad = &GV_PadData[ 1 ];
    }

    ctrl = &work->control;
    if ( GM_InitControl( ctrl, name, where ) < 0 )
    {
        return -1;
    }

    seg_flag = HZD_SEG_NO_COLLIDE;

    GM_ConfigControlString( ctrl, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlHazard( ctrl, d18a_dword_800C37F8, 450, 450 );
    ctrl->seg_flag = seg_flag;
    GM_ConfigControlAttribute( ctrl, RADAR_VISIBLE );
    GM_ConfigControlTrapCheck( ctrl );

    body = &work->body;
    if ( work->f930 == seg_flag )
    {
        opt = GCL_GetOption( 'm' );
        if ( opt != NULL )
        {
            GM_InitObject( body, GCL_StrToInt( opt ), BODY_FLAG, MOTION_DATA );
        }
        else
        {
            GM_InitObject( body, BODY_DATA, BODY_FLAG, MOTION_DATA );
        }
    }
    else
    {
        GM_InitObject( body, BODY_DATA2, BODY_FLAG, MOTION_DATA );
    }

    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl( body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, &work->control, work->rots );
    GM_ConfigObjectLight( body, work->light );

    if ( d18a_snake18_800D4B84( work ) < 0 )
    {
        return -1;
    }

    if ( d18a_snake18_800D49FC( work ) < 0 )
    {
        return -1;
    }

    if ( d18a_snake18_800D4BA4( work ) < 0 )
    {
        return -1;
    }

    GM_PlayerControl = ctrl;
    GM_PlayerBody = body;

    shadow.vx = 0;
    shadow.vy = 6;
    shadow.vz = 12;
    shadow.pad = 15;
    work->shadow = NewShadow2( ctrl, body, shadow, &work->enable_shadow );
    if ( work->shadow == NULL )
    {
        return -1;
    }

    return 0;
}

const char d18a_dword_800DA7F4[] = "snake18.c";

int d18a_snake18_800D4E94(int arg1, int arg2)
{
    GV_ACT *act = (GV_ACT *)GV_NewActor(4, 0x940);
    if (act == NULL)
    {
        return 0;
    }
    GV_SetNamedActor(act, d18a_snake18_800D4388, d18a_snake18_800D46CC,
                     d18a_dword_800DA7F4);
    if (d18a_snake18_800D4C44((Snake18Work *)act, arg1, arg2) < 0)
    {
        GV_DestroyActor(act);
        return 0;
    }
    return (int)act;
}
