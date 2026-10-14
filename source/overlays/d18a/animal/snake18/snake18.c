#include "mgstype.h"
#include "chara/snake/shadow.h"
#include "game/game.h"
#include "game/vibrate.h"
#include "libgcl/libgcl.h"
#include "okajima/blood.h"
#include "menu/menuman.h"
#include "anime/animconv/anime.h"
#include "strcode.h"
#include "equip/equip.h"
#include "okajima/d_blood.h"
#include "takabe/goggle.h"
#include "takabe/goggleir.h"
#include "weapon/weapon.h"

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
    u_char aim;
    u_char reload;
    u_char punch;
    u_char setup;
    u_char shoot;
    u_char field_5;
    u_char field_6;
    u_char field_7;
    u_char field_8;
    u_char field_9;
    u_char field_A;
    u_char field_B;
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

/* camera/turn parameters (word_8009EFC0 in sna_init.c) */
typedef struct _Snake18Init
{
    short mode;      // 0x0
    short field_2;   // 0x2
    short field_4;   // 0x4
    short look_min;  // 0x6
    short look_max;  // 0x8
    short look_up;   // 0xA
    short look_down; // 0xC
    short turn_r;    // 0xE
    short turn_l;    // 0x10
    short field_12;  // 0x12
} Snake18Init;

/* queue of forced actions (message from the script) */
typedef struct _Snake18Queue
{
    u_short n_acts;     // 0x8D8
    u_short action[4];  // 0x8DA: motion numbers
    short   dir[4];     // 0x8E2
    short   end_dir;    // 0x8EA
    short   end_stance; // 0x8EC
} Snake18Queue;

typedef struct _Snake18Work Snake18Work;

typedef void (*Snake18Func)(Snake18Work *work, int time);

struct _Snake18Work
{
    GV_ACT         actor;            // 0x000
    CONTROL        control;          // 0x020
    OBJECT         body;             // 0x09C
    MOTION_CONTROL m_ctrl;           // 0x180
    MOTION_SEGMENT m_segs1[17];      // 0x1D0
    MOTION_SEGMENT m_segs2[17];      // 0x434
    SVECTOR        rots[16];         // 0x698
    SVECTOR        adjust[16];       // 0x718
    int            hzd_address;      // 0x798
    MATRIX         light[2];         // 0x79C
    void          *shadow;           // 0x7DC
    int           *enable_shadow;    // 0x7E0
    int            flags;            // 0x7E4
    TARGET        *target;           // 0x7E8
    TARGET         attack;           // 0x7EC: punch / capture
    TARGET        *victim;           // 0x834: target being held or punched
    SVECTOR        f838;             // 0x838
    int            f840;             // 0x840
    char           pad_844[0x4];
    SVECTOR        f848;             // 0x848
    GV_ACT        *weapon_actor;     // 0x850
    Snake18Func    weapon_state;     // 0x854
    int            weapon_time;      // 0x858
    u_long         trigger;          // 0x85C
    short         *n_bullets;        // 0x860
    int            weapon;           // 0x864
    int            weapon_flags;     // 0x868
    short          f86C;             // 0x86C
    short          f86E;             // 0x86E
    DG_TEX        *lsight_tex;       // 0x870
    DG_PRIM       *lsight_prim;      // 0x874
    SVECTOR        lsight_verts[4];  // 0x878
    GV_ACT        *item_actor;       // 0x898
    int            item;             // 0x89C
    int            item_flags;       // 0x8A0
    GV_PAD        *pad;              // 0x8A4
    ACTPACK18     *actpack;          // 0x8A8
    Snake18Func    anim;             // 0x8AC
    int            anim_time;        // 0x8B0
    Snake18Func    f8B4;             // 0x8B4
    int            f8B8;             // 0x8B8: frame counter of f8B4
    Snake18Func    update_3p;        // 0x8BC
    Snake18Func    update_1p;        // 0x8C0: first person
    Snake18Init    f8C4;             // 0x8C4
    Snake18Queue   force_act;        // 0x8D8
    short          f8EE;             // 0x8EE
    int            f8F0;             // 0x8F0
    int            f8F4;             // 0x8F4
    short          f8F8;             // 0x8F8
    short          last_vital;       // 0x8FA
    u_char         invuln;           // 0x8FC: invincibility frames
    u_char         f8FD;             // 0x8FD
    short          stance;           // 0x8FE
    short          r_sphere;         // 0x900
    short          f902;             // 0x902
    SVECTOR        f904;             // 0x904
    char           vib1;             // 0x90C: frames of pad vibration 1
    char           vib2;             // 0x90D: frames of pad vibration 2
    char           f90E;             // 0x90E
    char           pad_90F;
    short          local_data;       // 0x910
    short          local_data2;      // 0x912
    SVECTOR        f914;             // 0x914 (peek target position)
    SVECTOR        f91C;             // 0x91C (saved control.mov)
    short          f924;             // 0x924
    short          f926;             // 0x926
    short          f928;             // 0x928
    unsigned short f92A;             // 0x92A
    unsigned short f92C;             // 0x92C
    short          f92E;             // 0x92E
    int            side;             // 0x930
    int            f934;             // 0x934
    SVECTOR        f938;             // 0x938
}; /* 0x940 */

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
    void       *(*mCreateActorFn)(CONTROL *, OBJECT *, int, u_long *, int);
    Snake18Func mStateFn;
} WeaponCreateEntry;

extern int counter_8009F448;
extern void *NewBakudan(); /* called with 4 arguments here */
extern SVECTOR svector_8009F478;



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
void d18a_snake18_800CB7BC(Snake18Work *work, Snake18Func func);
void d18a_snake18_800CB7D0(Snake18Work *work, int arg1);
void d18a_snake18_800CB838(Snake18Work *work);
void d18a_snake18_800CB888(Snake18Work *work);
int d18a_snake18_800CB908(Snake18Work *work, PUNCH *arg1);
int d18a_snake18_800CB9CC(Snake18Work *arg0, PUNCH *arg1);
int d18a_snake18_800CBA64(Snake18Work *work, PUNCH *arg1);
void d18a_snake18_800CBB34(Snake18Work *work);
int d18a_snake18_800CBBC8(Snake18Work *work);
void d18a_snake18_800CBD34(Snake18Work *work);
void d18a_snake18_800CBD80(Snake18Work *work);
void d18a_snake18_800CBE58(Snake18Work *work);
void d18a_snake18_800CBEC0(Snake18Work *work);
void d18a_snake18_800CBF98(Snake18Work *work);
void d18a_snake18_800CC008(Snake18Work *work);
void d18a_snake18_800CC010(Snake18Work *work);
void d18a_snake18_800CC174(Snake18Work *work, GV_MSG *msg);
int d18a_snake18_800CC288(SVECTOR *pos, short *out);
int d18a_snake18_800CC3C8(int area);
int d18a_snake18_800CC410(Snake18Work *work);
int d18a_snake18_800CC490(Snake18Work *work);
void d18a_snake18_800CC6CC(Snake18Work *work);
void d18a_snake18_800CC7F4(Snake18Work *work);
void d18a_snake18_800CC8B0(Snake18Work *work, char arg1);
void d18a_snake18_800CC8E0(Snake18Work *arg0);
void d18a_snake18_800CC90C(Snake18Work *work);
void d18a_snake18_800CCB0C(TARGET *target);
void d18a_snake18_800CCB50(Snake18Work *work);
void d18a_snake18_800CCF30(Snake18Work *work);
void d18a_snake18_800CD040(Snake18Work *work);
void d18a_snake18_800CD2C4(Snake18Work *work, int item);
void d18a_snake18_800CD4C0(Snake18Work *work);
void d18a_snake18_800CD64C(Snake18Work *work, int arg1);
void d18a_snake18_800CD768(Snake18Work *work, int arg1);
void d18a_snake18_800CD808(Snake18Work *work, int arg1);
void d18a_snake18_800CD888(Snake18Work *work, int arg1);
void d18a_snake18_800CD930(Snake18Work *work, int arg1);
void d18a_snake18_800CD9A8(Snake18Work *work, int time);
void d18a_snake18_800CDB04(Snake18Work *work, int time);
void d18a_snake18_800CDC3C(Snake18Work *work, int time);
void d18a_snake18_800CDD4C(Snake18Work *work, int time);
void d18a_snake18_800CDE8C(Snake18Work *work, int time);
void d18a_snake18_800CDFC8(Snake18Work *work, int time);
void d18a_snake18_800CE09C(Snake18Work *work, int time);
void d18a_snake18_800CE210(Snake18Work *work, int time);
void d18a_snake18_800CE38C(Snake18Work *work, int time);
void d18a_snake18_800CE4E4(Snake18Work *work, int time);
void d18a_snake18_800CE6B0(Snake18Work *work, int time);
void d18a_snake18_800CE7BC(Snake18Work *work, int time);
void d18a_snake18_800CE7C4(Snake18Work *work, int arg1);
void d18a_snake18_800CE834(Snake18Work *work, int arg1);
void d18a_snake18_800CE8E0(Snake18Work *work, int arg1);
void d18a_snake18_800CE998(Snake18Work *work, int arg1);
void d18a_snake18_800CEA84(Snake18Work *work, int arg1);
void d18a_snake18_800CEB78(Snake18Work *work, int arg1);
void d18a_snake18_800CEC68(Snake18Work *work, int time);
void d18a_snake18_800CECE0(Snake18Work *work, int time);
void d18a_snake18_800CED2C(Snake18Work *work, int arg1);
void d18a_snake18_800CEDB0(Snake18Work *work, int time);
void d18a_snake18_800CEE60(Snake18Work *work);
void d18a_snake18_800CEEAC(Snake18Work *work, int arg1);
void d18a_snake18_800CEF0C(Snake18Work *work, int arg1);
void d18a_snake18_800CEF44(Snake18Work *work, int arg1);
void d18a_snake18_800CF03C(Snake18Work *work, int time);
void d18a_snake18_800CF198(Snake18Work *work, int time);
void d18a_snake18_800CF39C(Snake18Work *work, int time);
void d18a_snake18_800CF574(Snake18Work *work, int time);
void d18a_snake18_800CF718(Snake18Work *work, int time);
void d18a_snake18_800CF744(Snake18Work *work, int time);
void d18a_snake18_800CF850(Snake18Work *work, int time);
void d18a_snake18_800CF990(Snake18Work *work, int time);
void d18a_snake18_800CFB04(Snake18Work *work, int time);
void d18a_snake18_800CFD18(Snake18Work *work, int time);
void d18a_snake18_800CFEE8(Snake18Work *work, int arg1);
void d18a_snake18_800CFF5C(Snake18Work *work, int arg1);
void d18a_snake18_800CFFD4(Snake18Work *work, int arg1);
void d18a_snake18_800D0054(Snake18Work *work, int arg1);
void d18a_snake18_800D00E0(Snake18Work *work, int arg1);
void d18a_snake18_800D01D8(Snake18Work *work, int time);
void d18a_snake18_800D0974(Snake18Work *work);
void d18a_snake18_800D09B4(Snake18Work *work, int time);
void d18a_snake18_800D0A10(Snake18Work *work, int time);
void d18a_snake18_800D0AF8(Snake18Work *work, int time);
void d18a_snake18_800D0B4C(Snake18Work *work, int time);
void d18a_snake18_800D0B84(Snake18Work *work, int time);
int d18a_snake18_800D0BF4(Snake18Work *work);
void d18a_snake18_800D0E3C(Snake18Work *work);
void d18a_snake18_800D1064(Snake18Work *work);
void d18a_snake18_800D11A8(Snake18Work *work);
void d18a_snake18_800D1300(Snake18Work *work);
void d18a_snake18_800D1424(Snake18Work *work, int time);
void d18a_snake18_800D1598(Snake18Work *work, int time);
void d18a_snake18_800D1750(Snake18Work *work, int time);
void d18a_snake18_800D1814(Snake18Work *work, int time);
void d18a_snake18_800D18EC(Snake18Work *work, int time);
void d18a_snake18_800D198C(Snake18Work *work, int amount);
void d18a_snake18_800D1A08(Snake18Work *work);
void d18a_snake18_800D1A6C(Snake18Work *work, int arg1);
void d18a_snake18_800D1ACC(Snake18Work *work, int arg1);
void d18a_snake18_800D1B3C(Snake18Work *work, int arg1);
void d18a_snake18_800D1BAC(Snake18Work *work, int time);
void d18a_snake18_800D1CE8(Snake18Work *work, int time);
void d18a_snake18_800D1F90(Snake18Work *work, int time);
void d18a_snake18_800D200C(Snake18Work *work, int time);
void d18a_snake18_800D20EC(Snake18Work *work, int time);
void d18a_snake18_800D22C8(Snake18Work *work, int a1);
void d18a_snake18_800D23F0(Snake18Work *work, int time);
void d18a_snake18_800D24CC(Snake18Work *work, int time);
void d18a_snake18_800D2660(Snake18Work *work, int arg1);
void d18a_snake18_800D26E4(Snake18Work *work, int time);
void d18a_snake18_800D281C(Snake18Work *work);
void d18a_snake18_800D28CC(Snake18Work *work, int time);
void d18a_snake18_800D2A80(Snake18Work *work, int time);
void d18a_snake18_800D2D88(Snake18Work *work, int time);
void d18a_snake18_800D2F70(Snake18Work *work, int time);
void d18a_snake18_800D3024(Snake18Work *work, int time);
void d18a_snake18_800D3218(Snake18Work *work, int time);
void d18a_snake18_800D3330(Snake18Work *work, int time);
void d18a_snake18_800D3508(Snake18Work *work, int time);
void d18a_snake18_800D3774(Snake18Work *work, int time);
void d18a_snake18_800D37FC(Snake18Work *work, int time);
void d18a_snake18_800D3A1C(Snake18Work *work, int time);
void d18a_snake18_800D3A9C(Snake18Work *work, int time);
void d18a_snake18_800D3B1C(Snake18Work *work, int time);
void d18a_snake18_800D3C14(Snake18Work *work, int time);
void d18a_snake18_800D3D0C(Snake18Work *work, int time);
void d18a_snake18_800D3ED0(Snake18Work *work, int time);
void d18a_snake18_800D3FE8(Snake18Work *work, int time);
void d18a_snake18_800D4084(Snake18Work *work);
void d18a_snake18_800D40F0(Snake18Work *work);
void d18a_snake18_800D4388(Snake18Work *work);
void d18a_snake18_800D46CC(Snake18Work *work);
int d18a_snake18_800D4784(Snake18Work *work);
void d18a_snake18_800D48FC(Snake18Work *work);
int d18a_snake18_800D49FC(Snake18Work *work);
int d18a_snake18_800D4B84(Snake18Work *work);
int d18a_snake18_800D4BA4(Snake18Work *work);
int d18a_snake18_800D4C44(Snake18Work *work, int name, int where);
void *d18a_snake18_800D4E94(int name, int where);

static inline void d18a_snake18_SetAction(Snake18Work *work, int action, int interp)
{
    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, interp);
    }
}

static inline void d18a_snake18_SetOverride(Snake18Work *work, int action, int interp, int mask)
{
    if (work->body.action2 != action)
    {
        GM_ConfigObjectOverride(&work->body, action, 0, interp, mask);
    }
}

static inline void d18a_snake18_StartAnim(Snake18Work *work, Snake18Func func)
{
    work->anim = func;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

extern int bakudan_count_8009F42C;
extern int printf(/* const char *format, ... */);

ACTSTILL18 snake18_none_still = {2, 6, 16, 22, 26, 32, 112, 113};
ACTSTILL18 snake18_socom_still = {0, 0, 15, 22, 25, 31, 55, 56};
ACTSTILL18 snake18_famas_still = {1, 5, 15, 22, 25, 31, 55, 56};
ACTSTILL18 snake18_grenade_still = {3, 3, 16, 22, 26, 32, 55, 56};
ACTSTILL18 snake18_c4_still = {114, 114, 16, 22, 58, 32, 55, 56};
ACTSTILL18 snake18_nikita_still = {91, 91, 93, 107, 25, 109, 55, 56};
ACTSTILL18 snake18_claymore_still = {119, 119, 123, 124, 26, 126, 112, 113};

ACTMOVE18 snake18_none_move = {12, 104, 19, 23, 24, 29, 30, 35, 36, 12, 0, 0, {0, 0, 0, 0}};
ACTMOVE18 snake18_socom_move = {10, 8, 17, 23, 24, 27, 28, 33, 34, 95, 132, 133, {0, 0, 0, 0}};
ACTMOVE18 snake18_famas_move = {11, 9, 18, 23, 24, 27, 28, 33, 34, 88, 136, 137, {0, 0, 0, 0}};
ACTMOVE18 snake18_nikita_move = {90, 92, 94, 23, 24, 27, 28, 33, 34, 90, 0, 0, {0, 0, 0, 0}};
ACTMOVE18 snake18_c4_move = {116, 115, 117, 23, 24, 29, 30, 110, 111, 116, 0, 0, {0, 0, 0, 0}};
ACTMOVE18 snake18_claymore_move = {121, 120, 122, 125, 24, 29, 30, 127, 128, 121, 0, 0, {0, 0, 0, 0}};
ACTMOVE18 snake18_grenade_move = {130, 129, 19, 23, 24, 29, 30, 35, 36, 130, 0, 0, {0, 0, 0, 0}};

ACTTRANS18 snake18_all_trans = {20, 21, 106, 0};

ACTDAMAGE18 snake18_none_damage = {{78, 80, 82, 83, 84, 85, 86, 87, 81, 153, 154, 155, 156, 157, 0, 0}};
ACTDAMAGE18 snake18_socom_damage = {{76, 79, 82, 83, 84, 85, 86, 87, 81, 153, 0, 0, 0, 0, 0, 0}};
ACTDAMAGE18 snake18_famas_damage = {{77, 105, 82, 83, 84, 85, 86, 87, 81, 153, 0, 0, 0, 0, 0, 0}};

ACTATTACK18 snake18_none_attack = {158, 158, 48, 158, 49, 50, 51, 52, 0, 0, 0, 0};
ACTATTACK18 snake18_socom_attack = {57, 66, 48, 60, 62, 0, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_famas_attack = {5, 67, 47, 61, 63, 0, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_stinger_attack = {89, 158, 158, 158, 131, 0, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_nikita_attack = {89, 158, 47, 61, 96, 0, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_c4_attack = {58, 158, 158, 158, 68, 70, 64, 69, 71, 0, 0, 0};
ACTATTACK18 snake18_claymore_attack = {72, 158, 158, 158, 73, 74, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_grenade_attack = {75, 158, 48, 158, 65, 0, 0, 0, 0, 0, 0, 0};
ACTATTACK18 snake18_psg1_attack = {59, 158, 158, 158, 158, 0, 0, 0, 0, 0, 0, 0};

u_char snake18_special1[8][4] = {
    {141, 0, 0, 0},
    {138, 0, 0, 0},
    {139, 0, 0, 0},
    {158, 0, 0, 0},
    {140, 0, 0, 0},
    {142, 0, 0, 0},
    {143, 0, 0, 0},
    {144, 0, 0, 0},
};

ACTSPECIAL18 snake18_special2 = {{7, 13, 4, 14, 37, 53, 54, 145}};

ACTPACK18 snake18_actions_no_weapon = {&snake18_none_still, &snake18_none_move, &snake18_all_trans, &snake18_none_damage, &snake18_none_attack, snake18_special1[0], &snake18_special2};

ACTPACK18 snake18_weapon_actions[10] = {
    {&snake18_socom_still, &snake18_socom_move, &snake18_all_trans, &snake18_socom_damage, &snake18_socom_attack, snake18_special1[1], &snake18_special2},
    {&snake18_famas_still, &snake18_famas_move, &snake18_all_trans, &snake18_famas_damage, &snake18_famas_attack, snake18_special1[2], &snake18_special2},
    {&snake18_grenade_still, &snake18_grenade_move, &snake18_all_trans, &snake18_none_damage, &snake18_grenade_attack, snake18_special1[7], &snake18_special2},
    {&snake18_nikita_still, &snake18_nikita_move, &snake18_all_trans, &snake18_famas_damage, &snake18_nikita_attack, snake18_special1[4], &snake18_special2},
    {&snake18_famas_still, &snake18_famas_move, &snake18_all_trans, &snake18_famas_damage, &snake18_stinger_attack, snake18_special1[3], &snake18_special2},
    {&snake18_claymore_still, &snake18_claymore_move, &snake18_all_trans, &snake18_none_damage, &snake18_claymore_attack, snake18_special1[6], &snake18_special2},
    {&snake18_c4_still, &snake18_c4_move, &snake18_all_trans, &snake18_none_damage, &snake18_c4_attack, snake18_special1[5], &snake18_special2},
    {&snake18_grenade_still, &snake18_grenade_move, &snake18_all_trans, &snake18_none_damage, &snake18_grenade_attack, snake18_special1[7], &snake18_special2},
    {&snake18_grenade_still, &snake18_grenade_move, &snake18_all_trans, &snake18_none_damage, &snake18_grenade_attack, snake18_special1[7], &snake18_special2},
    {&snake18_none_still, NULL, &snake18_all_trans, &snake18_none_damage, &snake18_psg1_attack, snake18_special1[3], &snake18_special2},
};

int d18a_dword_800C37E0 = 980;

Snake18Func d18a_dword_800C37E4[] = {d18a_snake18_800CD64C, d18a_snake18_800CD768, d18a_snake18_800CD808};
void *d18a_dword_800C37F0[] = {d18a_snake18_800CD9A8, d18a_snake18_800CDC3C};

short d18a_dword_800C37F8[] = {750, 250, 250, 0};

char d18a_dword_800C3800[] = {127, 4, 0, 0};
char d18a_dword_800C3804[] = {225, 1, 255, 2, 0, 0, 0, 0};
char d18a_dword_800C380C[] = {127, 6, 0, 0};
char d18a_dword_800C3810[] = {225, 1, 255, 4, 225, 2, 75, 8, 0, 0, 0, 0};
char d18a_dword_800C381C[] = {0, 11, 127, 1, 0, 0, 0, 0};
char d18a_dword_800C3824[] = {85, 4, 45, 6, 165, 1, 0, 0};
char d18a_dword_800C382C[] = {0, 25, 127, 2, 0, 0, 0, 0};
char d18a_dword_800C3834[] = {120, 6, 0, 19, 120, 4, 0, 0};

Snake18Init d18a_dword_800C383C = {0, 500, 0, 320, 400, 320, 400, 32, 32, 0};

SVECTOR d18a_dword_800C3850 = {0, 0, 100, 0};
SVECTOR d18a_dword_800C3858 = {-1024, 0, 0, 0};

char d18a_dword_800C3860[] = {1, 1, 0, 0};
char d18a_dword_800C3864[] = {255, 1, 0, 0};

SVECTOR d18a_dword_800C3868 = {2500, 10000, 500, 0};

WeaponCreateEntry d18a_dword_800C3870[] = {
    {NULL, d18a_snake18_800CECE0},
    {NewSOCOM, d18a_snake18_800CEB78},
    {NewFAMAS, d18a_snake18_800CEB78},
    {NewGrenade, d18a_snake18_800D3024},
    {NewRCM, d18a_snake18_800CEB78},
    {NewAAM, d18a_snake18_800D1F90},
    {NewMine, d18a_snake18_800D23F0},
    {NewBomb, d18a_snake18_800CEC68},
    {NewStanGrenade, d18a_snake18_800D3024},
    {NewChaffGrenade, d18a_snake18_800D3024},
    {NewRifle, d18a_snake18_800D1CE8},
};

void *d18a_dword_800C38C8[] = {
    NewTabako,
    NewScope,
    NewBox,
    NewBox,
    NewBox,
    NewBox,
    NewGoggle,
    NewGoggleIr,
    NewGasMask,
    NewBodyArmor,
    NewKetchap,
    NewKogaku2,
    NULL,
    NULL,
};

PUNCH d18a_dword_800C3900 = {{0, 0, 300, 0}, {400, 600, 400, 0}, {0, 0, 0, 0}, 64, 0};

short d18a_dword_800C3920[] = {1104, 469, 139, 0};

SVECTOR d18a_dword_800C3928[2] = {{1024, 0, 0, 0}, {-1024, 0, 0, 0}};
SVECTOR d18a_dword_800C3938 = {5, -500, 80, 0};
SVECTOR d18a_dword_800C3940 = {0, 0, 300, 0};
SVECTOR d18a_dword_800C3948 = {0, 100, -300, 0};

PUNCH d18a_dword_800C3950[2] = {
    {{-400, 0, 600, 0}, {400, 600, 400, 0}, {0, 0, 0, 0}, 36, 5},
    {{400, 0, 600, 0}, {400, 600, 400, 0}, {0, 0, 0, 0}, 36, 5},
};

PUNCH d18a_dword_800C3990 = {{0, 0, 0, 0}, {400, 600, 400, 0}, {0, 0, 0, 0}, 7, 0};

SVECTOR d18a_dword_800C39B0 = {0, 0, 0, 0};

PUNCH d18a_dword_800C39B8[3] = {
    {{-200, 200, 500, 0}, {300, 400, 400, 0}, {5, 0, 50, 0}, 0, 1},
    {{200, 200, 500, 0}, {300, 400, 400, 0}, {-5, 0, 50, 0}, 0, 1},
    {{0, 200, 600, 0}, {500, 400, 500, 0}, {0, 0, 100, 0}, 0, 3},
};

GV_PAD d18a_dword_800C3A18 = {0, 0, 0, 0, -1, 0, 0, 0, 0, 0};

SVECTOR d18a_dword_800C3A28 = {300, 750, 300, 0};

GV_MSG   SECTION(".bss") d18a_dword_800DAEA0[4];
int      SECTION(".bss") d18a_dword_800DAEF0;
int      SECTION(".bss") d18a_dword_800DAEF4;
SVECTOR *SECTION(".bss") d18a_dword_800DAEF8;
char    *SECTION(".bss") d18a_dword_800DAEFC;
HZD_FLR *SECTION(".bss") d18a_dword_800DAF00[2];
int      SECTION(".bss") d18a_dword_800DAF08;
int      SECTION(".bss") d18a_dword_800DAF0C;
void    *SECTION(".bss") d18a_dword_800DAF10;


void d18a_snake18_800CABEC( Snake18Work *work )
{
    GV_PAD *pad;
    u_char *analog;
    int i;

    work->flags &= ~0x4000;

    pad = work->pad;
    if ( pad->analog != 0 && ( pad->status & PAD_UDLR ) != 0 )
    {
        analog = &pad->right_dx;
        for ( i = 0; i < 4; i++ )
        {
            if ( (u_char)( *analog - 80 ) > 96 )
            {
                work->flags |= 0x4000;
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

    temp_s1 = work->stance;
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
        return work->actpack->still->stand;
    }
    else if (arg1 == 1)
    {
        return work->actpack->still->squat;
    }
    else if (arg1 == 2)
    {
        return work->actpack->still->crouch;
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
    if (work->flags & 0x8000)
    {
        work->flags &= ~0x8000;
        work->control.mov = work->f91C;
    }
}

void d18a_snake18_800CB3E8(Snake18Work *work)
{
    work->flags |= 0x800;
    work->r_sphere = 0x1C2;
    GM_Camera.first_person = 1;
    work->f8F8 = -4;
    work->f8C4.look_max = d18a_dword_800C37E0;
    work->f8C4.look_down = d18a_dword_800C37E0;
    work->f8C4.field_4 = 0x140;
}

void d18a_snake18_800CB42C(Snake18Work *work)
{
    work->r_sphere = 0x1C2;
    work->flags &= ~0x800;
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
        action = work->actpack->still->setup;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
        return;
    }
    else if (diff < 0)
    {
        action = work->actpack->move->turn_l;
    }
    else
    {
        action = work->actpack->move->turn_r;
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

void d18a_snake18_800CB7BC(Snake18Work *work, Snake18Func func)
{
    work->weapon_state = func;
    work->weapon_time = 0;
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
    if (!(work->weapon_flags & 4) && (GM_PlayerStatus & PLAYER_ATTACK) && (work->f86C != 3))
    {
        work->trigger |= 9;
    }
}

void d18a_snake18_800CB888(Snake18Work *work)
{
    if (work->vib1 != 0)
    {
        NewPadVibration(d18a_dword_800C3860, 1);
        work->vib1--;
    }

    if (work->vib2 != 0)
    {
        NewPadVibration(d18a_dword_800C3864, 2);
        work->vib2--;
        return;
    }

    work->f90E = 0;
}

int d18a_snake18_800CB908(Snake18Work *work, PUNCH *arg1)
{
    TARGET *t = &work->attack;
    SVECTOR sp18;
    int     mode;

    GM_SetTarget(t, 4, work->side, &arg1->size);
    DG_RotVector(&arg1->field_10, &sp18, 1);

    mode = arg1->faint;
    if (mode == 1)
        GM_SetPowerTarget(t, 3, 3, arg1->life, mode, &sp18);
    else
        GM_SetPowerTarget(t, 3, 4, arg1->life, mode, &sp18);

    DG_PutVector(&arg1->field_0, &sp18, 1);
    GM_MoveTarget(t, &sp18);
    return GM_PowerTarget(t);
}

int d18a_snake18_800CB9CC(Snake18Work *arg0, PUNCH *arg1)
{
    SVECTOR sp18;
    TARGET *temp_s1;

    temp_s1 = &arg0->attack;
    GM_SetTarget(temp_s1, 2, arg0->side, &arg1->size);
    GM_SetCaptureTarget(temp_s1, arg1->life, arg1->faint, &arg0->f840, &arg0->f848);
    DG_PutVector(&arg1->field_0, &sp18, 1);
    GM_MoveTarget(temp_s1, &sp18);
    arg0->victim = GM_CaptureTarget(temp_s1);
    return arg0->victim != NULL;
}
int d18a_snake18_800CBA64(Snake18Work *work, PUNCH *arg1)
{
    TARGET *target;
    SVECTOR vec;
    TARGET *t;

    target = &work->attack;
    GM_SetTarget(target, 0x40, work->side, &arg1->size);
    GM_SetCaptureTarget(target, arg1->life, 0, &work->f840, &work->f848);
    DG_PutVector(&arg1->field_0, &vec, 1);
    GM_MoveTarget(target, &vec);
    t = GM_C4Target(target);
    work->victim = t;
    if (t == NULL)
    {
        return 0;
    }
    if (t->class & 0x20)
    {
        t->damaged &= ~0x40;
        work->victim = 0;
        return 0;
    }
    return 1;
}
static inline int d18a_snake18_CanWatch(Snake18Work *work, int flags)
{
    if (work->update_1p == d18a_snake18_800CE7BC || (GM_PlayerStatus & flags) || (work->flags & 4) || dword_8009F46C[0])
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
    int            tbl = work->weapon_flags;
    unsigned short input = press;

    if (!(tbl & 0x100))
    {
        input = work->pad->status;
    }

    if (press & PAD_CIRCLE)
    {
        if ((work->actpack->attack->punch ^ 0x9E) != 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800D3774);
            work->flags |= 4;
        }
        return 1;
    }

    if (work->weapon >= 0 && *work->n_bullets == 0)
    {
        return 0;
    }

    if (input & PAD_SQUARE)
    {
        work->weapon_time = 0;

        if (tbl & 0x10)
        {
            d18a_snake18_StartAnim(work, work->weapon_state);
            work->flags |= 4;
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
    if ( work->weapon != 6 && work->pad->press & PAD_CIRCLE )
    {
        work->f8B4 = d18a_snake18_800CF990;
        work->f8B8 = 0;
        work->flags |= 0x100;
    }
}

void d18a_snake18_800CBD80(Snake18Work *work)
{
    if (work->weapon != 6)
    {
        return;
    }
    if (*work->n_bullets == 0)
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

    work->r_sphere = 0x1C2;
    work->f8B4 = d18a_snake18_800D22C8;
    work->f8B8 = 0;
    work->flags |= 0x100;
}

void d18a_snake18_800CBE58(Snake18Work *work)
{
    int state = work->weapon;
    if (state == 5 || state == 6 || state == 2 || state == 7 || state == 8)
    {
        short *p = work->n_bullets;
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
        if (work->anim == d18a_dword_800C37E4[i])
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
            work->anim = d18a_snake18_800CFB04;
            work->anim_time = 0;
            work->local_data2 = 0;
            work->local_data = 0;
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
    work->flags |= 0x100;
}

void d18a_snake18_800CC008(Snake18Work *work)
{
    /* do nothing */
}

static inline int d18a_snake18_IsCrouching(Snake18Work *work)
{
    int action;

    if (work->flags & 0x200)
    {
        return 0;
    }

    action = work->body.action;
    if (action == work->actpack->move->crouch || action == work->actpack->move->crouch_backwards ||
        action == work->actpack->trans->crouch)
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

    if (work->body.action == work->actpack->trans->crouch)
    {
        action = work->actpack->move->crouch;
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

    queue = &work->force_act;
    n = queue->n_acts;
    if (n == 4)
    {
        return;
    }

    a = -1;
    b = -1;
    *(queue->action + n) = msg->message[1]; /* not action[n]: that changes the code */
    p = &queue->dir[n];
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

    queue->n_acts = ++n;
    queue->end_dir = a;
    queue->end_stance = b;
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
int d18a_snake18_800CC490(Snake18Work *work)
{
    SVECTOR  near;
    SVECTOR  unused;
    short    dir;
    GV_MSG  *msg;
    CONTROL *control;
    int      area;
    int      seg_flag;
    TARGET  *target;

    if (GM_PlayerStatus & PLAYER_ACT_ONLY)
    {
        return 0;
    }

    /* FIXME: empty loop forces a label that keeps the redundant "move $a0, $s3" */
    while (1)
    {
        break;
    }
    control = &work->control;
    msg = d18a_dword_800DAEA0;
    work->control.msg = msg;
    {
        if (d18a_snake18_800CC410(work))
        {
            area = d18a_snake18_800CC288(&control->mov, &dir);
            work->f8F0 = d18a_snake18_800CC3C8(area);

            seg_flag = (area & 1) ? 0x20 : 0x10;
            if (!HZD_NearHazardCheck(control->map->hzd, &control->mov, 5000, 4, seg_flag))
            {
                printf(" Err Err Err Liquid Near Err !! \n");
            }
            else
            {
                HZD_GetNearVector(&near);
            }

            control->mov.vx += near.vx;
            control->mov.vy += near.vy;
            control->mov.vz += near.vz;
            work->f938 = control->mov;

            control->step.vx = 0;
            control->step.vz = 0;
            printf("snake pos1 %d %d %d \n", control->mov.vx, control->mov.vy, control->mov.vz);
            printf("work->height %d levels%d \n", work->control.height, control->levels[0]);

            if (control->levels[0] < 5000)
            {
                control->mov.vx = 2500;
                control->mov.vy = 12000;
                control->mov.vz = -1500;
                control->levels[0] = 9600;
            }

            target = work->target;
            work->f8F4 = 0;
            target->class &= ~TARGET_PUSH;

            msg->message_len = 5;
            msg->message[0] = HASH_MOTION;
            msg->message[1] = work->f8F0 * 3 + 2;
            msg->message[2] = dir;
            msg->message[3] = dir;
            msg->message[4] = 0;
            msg++;

            msg->message_len = 5;
            msg->message[0] = HASH_MOTION;
            msg->message[1] = work->f8F0 * 3 + 1;
            msg->message[2] = dir;
            msg->message[3] = dir;
            msg->message[4] = 0;
            msg++;

            msg->message_len = 5;
            msg->message[0] = HASH_MOTION;
            msg->message[1] = work->f8F0 * 3;
            msg->message[2] = dir;
            msg->message[3] = dir;
            msg->message[4] = 0;

            return control->n_msg = 3;
        }
    }

    return 0;
}
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
                work->f8C4.look_max = d18a_dword_800C37E0;
                work->f8C4.look_down = d18a_dword_800C37E0;
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
    if (work->force_act.n_acts == 0)
    {
        return;
    }

    GM_ConfigMotionControl(&work->body, &work->m_ctrl, work->f92A,
                           work->m_segs1, work->m_segs2, &work->control, work->rots);

    work->anim = d18a_snake18_800D01D8;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->f8EE = work->control.height;
    GM_PlayerStatus |= 4;
    d18a_snake18_800CB378(work);
}

void d18a_snake18_800CC8B0(Snake18Work *work, char arg1)
{
    int     mask = PLAYER_INVINCIBLE;
    TARGET *target = work->target;
    GM_PlayerStatus |= mask;
    work->invuln = arg1;
    target->class &= 0xFF61;
}

void d18a_snake18_800CC8E0(Snake18Work *arg0)
{
    TARGET *target = arg0->target;
    short   class = target->class;
    GM_PlayerStatus &= ~PLAYER_INVINCIBLE;
    target->class = class | 0x9E;
}

static inline int d18a_snake18_CanBlink(Snake18Work *work)
{
    if ((work->flags & 1) || (GM_PlayerStatus & (PLAYER_WATCH | PLAYER_INTRUDE)))
    {
        return 0;
    }

    return 1;
}

static inline int d18a_snake18_NoShake(Snake18Work *work)
{
    if ((work->flags & 2) || (GM_PlayerStatus & (PLAYER_CB_BOX | PLAYER_INTRUDE)) || (work->weapon_flags & 0x200) ||
        (work->item == 1))
    {
        return 0;
    }

    return 1;
}

void d18a_snake18_800CC90C(Snake18Work *work)
{
    int iframes;

    iframes = work->invuln;
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
        else if (!(work->flags & 0x10000))
        {
            d18a_snake18_800CC8E0(work);
            work->flags &= ~1;
        }

        work->invuln = iframes;
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
            work->flags &= ~0x10000;
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

    target = work->target;
    damaged = target->damaged;

    if (damaged & (TARGET_POWER | TARGET_CAPTURE))
    {
        a_mode = target->a_mode;

        if (d18a_snake18_NoShake(work))
        {
            GM_PlayerStatus |= PLAYER_DAMAGED;

            if (work->victim)
            {
                work->victim->damaged &= ~TARGET_CAPTURE;
                work->victim = 0;
                work->f924 = 0;
            }

            d18a_snake18_800CB838(work);
            DG_InvisiblePrim(work->lsight_prim);
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

                work->flags &= ~4;
            }
            else
            {
                work->f904 = target->force;
                d18a_snake18_StartAnim(work, d18a_snake18_800CF198);
                d18a_snake18_800CB378(work);
                work->flags |= 4;
                GM_SeSet(&work->control.mov, 0x19);

                if (!(GM_GameStatus & STATE_STUN))
                {
                    NewPadVibration(d18a_dword_800C380C, 1);
                    NewPadVibration(d18a_dword_800C3810, 2);
                }
            }

            work->r_sphere = 0x1C2;
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

            if (work->target->vital <= 0)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800CF39C);
            }
        }

        work->f90E = 0xFF;
        work->vib2 = 8;
        d18a_snake18_800CCB0C(target);
    }
    else if (damaged & TARGET_TOUCH)
    {
        d18a_snake18_800CC8B0(work, 0x20);
        d18a_snake18_800CCB0C(target);
        work->f90E = 0xFF;
        work->vib2 = 8;
    }
}

void d18a_snake18_800CCF30(Snake18Work *work)
{
    WeaponCreateEntry *e;
    void *(*fn)(CONTROL *, OBJECT *, int, u_long *, int);
    int wid;
    void *actor = work->weapon_actor;

    if (actor)
    {
        GV_DestroyActor(actor);
    }

    actor = NULL;
    work->weapon = GM_Weapon;
    wid = GM_Weapon;
    work->weapon_flags = GM_WeaponTypes[wid + 1];

    e = &d18a_dword_800C3870[wid + 1];
    if (GM_Weapon >= 0)
    {
        work->n_bullets = &GM_Weapons[ GM_Weapon ];
    }

    d18a_snake18_800CB7BC(work, e->mStateFn);
    fn = e->mCreateActorFn;
    if (fn)
    {
        actor = fn(&work->control, &work->body, 4, &work->trigger, work->side);
    }
    work->weapon_actor = actor;

    work->actpack = &snake18_weapon_actions[GM_Weapon];
}
void d18a_snake18_800CD040(Snake18Work *work)
{
    int tbl;
    int ok;

    if (!GM_WeaponChanged)
    {
        return;
    }

    if ((GM_PlayerStatus & (PLAYER_CB_BOX | PLAYER_DAMAGED | PLAYER_ACT_ONLY)) || (work->flags & 0x10) ||
        (!(work->weapon_flags & 0x200) && (GM_PlayerStatus & PLAYER_WATCH)) || dword_8009F46C[0] ||
        (GM_Weapon == WP_Stinger && (GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_GROUND))))
    {
fail:
        ok = 0;
    }
    else if ((GM_Weapon == WP_Stinger || GM_Weapon == WP_Rifle) && work->item == 1)
    {
        // goto kept: a second "ok = 0" (or one merged condition) changes the branch/delay slot code
        goto fail;
    }
    else
    {
        ok = 1;
        if (GM_PlayerStatus & PLAYER_CAUTION)
        {
            ok = GM_Weapon != WP_Rifle;
        }
    }

    if (!ok)
    {
        return;
    }

    GM_WeaponChanged = 0;
    d18a_snake18_800CCF30(work);

    tbl = work->weapon_flags;
    if (tbl & 0x200)
    {
        d18a_snake18_800CB34C(work);
    }
    else if (!(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        d18a_snake18_800CB378(work);
    }

    if (tbl & 0x20)
    {
        d18a_snake18_StartAnim(work, work->weapon_state);
    }
    else if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
    }
    else if (GM_PlayerStatus & PLAYER_CAUTION)
    {
        d18a_snake18_StartAnim(work, d18a_dword_800C37F0[work->stance]);
    }
    else
    {
        d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
    }

    GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_ATTACK | PLAYER_CHECK_WALL);

    if (work->body.action2 != 0)
    {
        GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
    }

    DG_InvisiblePrim(work->lsight_prim);
    work->flags &= ~4;
    work->flags &= ~2;

    if (work->victim)
    {
        work->victim->damaged &= ~TARGET_CAPTURE;
        work->victim = 0;
        work->f924 = 0;
    }

    if (!(GM_PlayerStatus & PLAYER_CAUTION))
    {
        GM_ExitBehindCamera();
    }
}
typedef void *(*Snake18EquipFn)(CONTROL *, OBJECT *, int);

void d18a_snake18_800CD2C4(Snake18Work *work, int item)
{
    GV_ACT        *actor;
    int            type;
    Snake18EquipFn equip;
    Snake18EquipFn *pfn;

    actor = work->item_actor;
    if (actor)
    {
        GV_DestroyActorQuick(actor);
    }

    work->item = item;
    pfn = (Snake18EquipFn *)&d18a_dword_800C38C8[item];
    type = work->item_flags = GM_ItemTypes[item + 1];
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

    work->item_actor = actor;

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
    else if (!(work->weapon_flags & 0x200))
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
        }
        else if (GM_PlayerStatus & PLAYER_CAUTION)
        {
            d18a_snake18_StartAnim(work, d18a_dword_800C37F0[work->stance]);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
        }
    }

    if (type & 2)
    {
        d18a_snake18_800CB34C(work);
    }
    else if (!(work->weapon_flags & 0x200) && !(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        d18a_snake18_800CB378(work);
    }
}
static inline int d18a_snake18_CanSwitchItem(Snake18Work *work)
{
    if ((GM_PlayerStatus & (PLAYER_DAMAGED | PLAYER_ACT_ONLY)) || (work->flags & 0x20) ||
        ((GM_Item == IT_Box1 || GM_Item == IT_Box2 || GM_Item == IT_Box3) && (GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_GROUND))))
    {
fail:
        return 0;
    }

    if ((GM_Item == IT_Scope || GM_Item == IT_Box1 || GM_Item == IT_Box2 || GM_Item == IT_Box3) && ((work->weapon_flags & 0x200) || dword_8009F46C[0]))
    {
        // goto kept: a second "return 0" gets cross-jumped to the end, moving the shared fail block
        goto fail;
    }

    return 1;
}

void d18a_snake18_800CD4C0(Snake18Work *work)
{
    if (!d18a_snake18_CanSwitchItem(work))
    {
        return;
    }

    if (GM_Item == work->item)
    {
        return;
    }

    d18a_snake18_800CD2C4(work, GM_Item);
    GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_ATTACK | PLAYER_CHECK_WALL);

    if (work->body.action2 != 0)
    {
        GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
    }

    if (work->victim)
    {
        work->victim->damaged &= ~TARGET_CAPTURE;
        work->victim = 0;
        work->f924 = 0;
    }

    work->flags &= ~4;
    work->flags &= ~2;
    DG_InvisiblePrim(work->lsight_prim);

    if (!(GM_PlayerStatus & PLAYER_CAUTION))
    {
        GM_ExitBehindCamera();
    }
}

void d18a_snake18_800CD64C(Snake18Work *work, int arg1)
{
    int   new_action;
    ACTSTILL18 *still;

    if (arg1 == 0)
    {
        work->update_3p = d18a_snake18_800CDD4C;
        work->stance = 0;
        work->update_1p = d18a_snake18_800D1424;

        if (GM_AlertMode == 3 || GM_AlertMode == 4)
        {
            new_action = work->actpack->still->setup;
        }
        else
        {
            new_action = work->actpack->still->stand;
        }
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }

    still = work->actpack->still;
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

    if (work->stance == 0)
    {
        GM_SeSet(&work->control.mov, 8);
    }
    work->stance = 1;

    work->update_3p = d18a_snake18_800CDE8C;
    work->update_1p = d18a_snake18_800D1424;
    GM_PlayerStatus |= 0x20;

    new_action = work->actpack->still->squat;
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
    work->stance = 2;
    work->r_sphere = 0x1C2;
    work->update_3p = d18a_snake18_800CDFC8;
    work->update_1p = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_GROUND;
    new_action = work->actpack->still->crouch;
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

    work->update_3p = d18a_snake18_800CE09C;
    work->update_1p = d18a_snake18_800D1424;
    GM_PlayerStatus |= 0x10;

    if (GM_AlertMode == 3)
    {
        new_action = work->actpack->move->aim;
    }
    else
    {
        new_action = work->actpack->move->stand;
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
    work->r_sphere = 0x1C2;
    work->update_3p = d18a_snake18_800CE210;
    work->update_1p = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_MOVE;
    new_action = work->actpack->move->crouch;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
}

void d18a_snake18_800CD9A8(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE38C;
        work->update_1p = d18a_snake18_800D1598;
        GM_PlayerStatus |= PLAYER_CAUTION;
        work->stance = 0;

        action = work->actpack->still->against_wall;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        work->r_sphere = 300;
        work->control.turn.vy = d18a_dword_800DAEF4 - 0x800;
    }

    if (!(GM_GameStatus & STATE_BEHIND_CAMERA) && (d18a_dword_800DAEF4 - 0x800) != work->control.rot.vy)
    {
        work->local_data2 = 0;
        work->control.turn.vy = d18a_dword_800DAEF4 - 0x800;
    }

    GM_CheckBehindCamera(work->control.map->hzd, &work->control);

    if (work->local_data2 < 8 && d18a_dword_800DAEF8 != NULL)
    {
        work->control.step.vx += d18a_dword_800DAEF8->vx / 8;
        work->control.step.vz += d18a_dword_800DAEF8->vz / 8;
        work->local_data2++;
    }
}

void d18a_snake18_800CDB04(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE4E4;
        GM_PlayerStatus |= PLAYER_MOVE | PLAYER_CAUTION;
        work->update_1p = d18a_snake18_800D1598;

        if (work->f924 == 2)
        {
            action = work->actpack->move->against_wall_r;
        }
        else
        {
            action = work->actpack->move->against_wall_l;
        }

        work->f924 = 0;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        work->control.turn.vy = d18a_dword_800DAEF4 - 0x800;
    }

    if (time < 8 && d18a_dword_800DAEF8 != NULL)
    {
        work->control.step.vx += d18a_dword_800DAEF8->vx / 8;
        work->control.step.vz += d18a_dword_800DAEF8->vz / 8;
    }
}

void d18a_snake18_800CDC3C(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->stance = 1;
        work->update_3p = d18a_snake18_800CE6B0;
        work->update_1p = d18a_snake18_800D1598;
        GM_PlayerStatus |= PLAYER_SQUAT | PLAYER_CAUTION;

        action = work->actpack->still->squat_against_wall;
        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        work->r_sphere = 300;
    }

    GM_CheckBehindCamera(work->control.map->hzd, &work->control);

    if (time < 8 && d18a_dword_800DAEF8 != NULL)
    {
        work->control.step.vx += d18a_dword_800DAEF8->vx / 8;
        work->control.step.vz += d18a_dword_800DAEF8->vz / 8;
    }
}
void d18a_snake18_800CDD4C(Snake18Work *work, int time)
{
    int action;

    if (d18a_snake18_800CBBC8(work))
    {
        return;
    }

    if (work->pad->press & PAD_CROSS)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD768);
        return;
    }

    if (work->local_data > 0)
    {
        work->local_data--;
    }

    if (work->local_data != 0 || d18a_dword_800DAEF0 < 0)
    {
        return;
    }

    if (d18a_dword_800DAF0C == 1)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD9A8);
        return;
    }

    if (GM_AlertMode == 3)
    {
        action = work->actpack->still->setup;
    }
    else
    {
        action = work->actpack->still->stand;
    }

    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    work->control.turn.vy = d18a_dword_800DAEF0;
    d18a_snake18_StartAnim(work, d18a_snake18_800CE7C4);
}

void d18a_snake18_800CDE8C(Snake18Work *work, int time)
{
    int dir;
    int diff;

    if (work->pad->press & PAD_CROSS)
    {
        GM_SeSet(&work->control.mov, 8);
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        GM_PlayerStatus &= ~PLAYER_SQUAT;
        return;
    }

    dir = d18a_dword_800DAEF0;
    if (dir < 0)
    {
        return;
    }

    if (d18a_dword_800DAF0C == 1)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        return;
    }

    if (dir != work->control.turn.vy)
    {
        diff = (dir - work->control.turn.vy) & 0xFFF;
        if (diff > 0x800)
        {
            diff -= 0x1000;
        }
        work->local_data = ((diff >= 0) ? diff : -diff) / 512 + 1;
        work->control.turn.vy = d18a_dword_800DAEF0;
        return;
    }

    if (work->local_data > 0)
    {
        work->local_data--;
    }

    if (work->local_data == 0)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CE834);
        GM_PlayerStatus &= ~PLAYER_SQUAT;
    }
}

void d18a_snake18_800CDFC8(Snake18Work *work, int time)
{
    if ((work->pad->press & PAD_CROSS) && !d18a_snake18_800CAF20(work))
    {
        work->r_sphere = 0x1C2;
        d18a_snake18_StartAnim(work, d18a_snake18_800CE8E0);
        GM_PlayerStatus &= ~PLAYER_GROUND;
        return;
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        return;
    }

    if (d18a_dword_800DAF0C == 1)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        GM_PlayerStatus &= ~PLAYER_GROUND;
        return;
    }

    d18a_snake18_StartAnim(work, d18a_snake18_800CD930);
}
void d18a_snake18_800CE09C(Snake18Work *work, int time)
{
    int action;
    int dir;

    if (d18a_snake18_800CBBC8(work))
    {
        return;
    }

    if (work->pad->press & PAD_CROSS)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD768);
        GM_PlayerStatus &= ~PLAYER_MOVE;
        return;
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        if (++work->local_data2 >= 5)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            GM_PlayerStatus &= ~PLAYER_MOVE;
            return;
        }
    }
    else
    {
        work->local_data2 = 0;
    }

    if (d18a_dword_800DAF0C == 1)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD9A8);
        GM_PlayerStatus &= ~PLAYER_MOVE;
        return;
    }

    work->local_data = 0;

    if (GM_AlertMode == 3)
    {
        action = work->actpack->move->aim;
    }
    else
    {
        action = work->actpack->move->stand;
    }

    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        dir = work->control.turn.vy;
    }
    else
    {
        dir = d18a_snake18_800CAEC0(work, d18a_dword_800DAEF0);
    }

    work->control.turn.vy = dir;
    d18a_snake18_800CB228(work, dir);
}

void d18a_snake18_800CE210(Snake18Work *work, int time)
{
    int dir;
    int backwards;
    int forwards;
    int action;

    if ((work->pad->press & PAD_CROSS) && !d18a_snake18_800CAF20(work))
    {
        work->r_sphere = 0x1C2;
        d18a_snake18_StartAnim(work, d18a_snake18_800CE8E0);
        GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_GROUND);
        return;
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD808);
        GM_PlayerStatus &= ~PLAYER_MOVE;
        return;
    }

    if (d18a_dword_800DAF0C == 1 && !d18a_snake18_800CAF20(work))
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_GROUND);
        return;
    }

    backwards = work->actpack->move->crouch_backwards;
    forwards = work->actpack->move->crouch;

    if (work->body.action == backwards)
    {
        dir = d18a_dword_800DAEF0 + 0x800;
    }
    else
    {
        dir = d18a_dword_800DAEF0;
    }

    if (d18a_snake18_800CAC68(work->control.turn.vy, dir) == 3)
    {
        dir += 0x800;
        action = forwards;
        if (work->body.action == action)
        {
            action = backwards;
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
    }

    work->control.turn.vy = d18a_snake18_800CAEC0(work, dir);
}

void d18a_snake18_800CE38C(Snake18Work *work, int time)
{
    if (work->local_data != 0)
    {
        work->local_data--;
    }

    if (d18a_dword_800DAF0C == 0 && work->local_data == 0)
    {
        work->r_sphere = 0x1C2;
        GM_PlayerStatus &= ~PLAYER_CAUTION;
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        GM_ExitBehindCamera();
        return;
    }

    if (work->pad->press & PAD_CROSS)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        return;
    }

    if ((d18a_dword_800DAF0C == 2 || d18a_dword_800DAF0C == 4) && !d18a_snake18_800CB134(work) &&
        !(GM_GameStatus & STATE_BEHIND_CAMERA))
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDB04);
        work->f924 = d18a_dword_800DAF0C;
    }

    d18a_snake18_800CBD34(work);
    d18a_snake18_800CBD80(work);
}
void d18a_snake18_800CE4E4(Snake18Work *work, int time)
{
    int action;

    if (work->local_data != 0)
    {
        work->local_data--;
    }

    if (d18a_dword_800DAF0C == 0 && work->local_data == 0)
    {
        work->r_sphere = 0x1C2;
        GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_CAUTION);
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        GM_ExitBehindCamera();
        return;
    }

    GM_CheckBehindCamera(work->control.map->hzd, &work->control);

    if (work->pad->press & PAD_CROSS)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        GM_PlayerStatus &= ~PLAYER_MOVE;
        return;
    }

    if (d18a_dword_800DAF0C == 1 || d18a_snake18_800CB134(work) || (GM_GameStatus & STATE_BEHIND_CAMERA))
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD9A8);
        GM_PlayerStatus &= ~PLAYER_MOVE;
        return;
    }

    work->control.turn.vy = d18a_dword_800DAEF4 - 0x800;
    d18a_snake18_800CBD34(work);
    d18a_snake18_800CBD80(work);

    if (d18a_dword_800DAF0C == 2)
    {
        action = work->actpack->move->against_wall_r;
    }
    else
    {
        action = work->actpack->move->against_wall_l;
    }

    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }
}
void d18a_snake18_800CE6B0(Snake18Work *work, int time)
{
    /* one temporary for both values: being set twice, the 0x1C2 register is
       no "birth" for the scheduler, which keeps "li $v0,0x1c2" in the bnez
       delay slot (800CE38C writes the constant directly) */
    int tmp;

    if (work->local_data != 0)
    {
        work->local_data--;
    }

    if (d18a_dword_800DAF0C == 0 && work->local_data == 0)
    {
        tmp = 0x1C2;
        work->r_sphere = tmp;
        GM_PlayerStatus &= ~PLAYER_CAUTION;
        d18a_snake18_StartAnim(work, d18a_snake18_800CD768);
        GM_ExitBehindCamera();
        return;
    }

    tmp = work->pad->press;
    if (tmp & PAD_CROSS)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD9A8);
        GM_PlayerStatus &= ~PLAYER_SQUAT;
    }

    work->control.turn.vy = d18a_dword_800DAEF4 - 0x800;
    d18a_snake18_800CBD34(work);
    d18a_snake18_800CBD80(work);
}

void d18a_snake18_800CE7BC(Snake18Work *work, int time)
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
    work->update_3p = d18a_snake18_800CED2C;
    work->update_1p = d18a_snake18_800D1424;
    GM_PlayerStatus |= PLAYER_MOVE;
    new_action = work->actpack->move->setup;
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
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus |= 0x40;
        new_action = work->actpack->trans->crouch;
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
        work->stance = 2;
    }

    if (work->body.is_end != 0)
    {
        work->anim = d18a_snake18_800CD808;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
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
        work->stance = 0;
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        new_action = work->actpack->trans->stand;
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
        work->anim = d18a_snake18_800CD64C;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void d18a_snake18_800CE998(Snake18Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->update_3p = d18a_snake18_800CEDB0;
        work->update_1p = d18a_snake18_800CE7BC;
        d18a_snake18_800CC8B0(work, 0);
        work->flags |= 0x232;
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
    work->flags &= ~0x232;

    if (GM_PlayerStatus & 2)
    {
        work->anim = d18a_snake18_800CEF0C;
    }
    else
    {
        work->anim = d18a_snake18_800CD930;
    }
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void d18a_snake18_800CEA84(Snake18Work *work, int arg1)
{
    int            new_action;
    unsigned short save_924;

    if (arg1 == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        new_action = work->actpack->attack->setup;
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 2);
        }

        work->m_ctrl.info2.mask = -1;
        work->flags |= 6;
        save_924 = work->f924;
        work->m_ctrl.info1.mask = 0;
        work->f924 = 0;
        GM_PlayerStatus &= ~0x800;
        work->control.turn.vy = save_924;
    }

    if (work->body.is_end != 0)
    {
        work->weapon_time = 0;
        GM_PlayerStatus |= 0x800;
        work->flags &= ~6;
        GM_SeSet(&work->control.mov, 0x2F);

        work->anim = d18a_snake18_800D1A6C;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
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
        new_action = work->actpack->attack->aim;
        if (work->body.action2 != new_action)
        {
            GM_ConfigObjectOverride(&work->body, new_action, 0, 4, mask);
        }
        work->local_data = 0;
    }

    if (work->pad->release & 0x80)
    {
        work->local_data = 1;
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
        d18a_snake18_800CB7BC(work, d18a_snake18_800D2A80);
    }
}
void d18a_snake18_800CEC68(Snake18Work *work, int time)
{
    GM_PlayerStatus &= ~PLAYER_NORMAL; /* no-op, but generates a load */
    work->update_3p = d18a_snake18_800CE7BC;
    work->update_1p = d18a_snake18_800CE7BC;

    if (d18a_snake18_800CBA64(work, &d18a_dword_800C3900))
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D20EC);
    }
    else
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D200C);
    }
}

void d18a_snake18_800CECE0(Snake18Work *work, int time)
{
    work->update_3p = d18a_snake18_800CE7BC;
    work->update_1p = d18a_snake18_800CE7BC;

    if (d18a_dword_800DAEF0 >= 0)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3508);
    }
    else
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D37FC);
    }
}

void d18a_snake18_800CED2C(Snake18Work *work, int arg1)
{
    if (arg1 == 2 && d18a_dword_800DAEF0 >= 0)
    {
        work->anim = d18a_snake18_800CD888;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (work->body.is_end == 0)
    {
        return;
    }

    work->anim = d18a_snake18_800CD64C;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x10;
}

void d18a_snake18_800CEDB0(Snake18Work *work, int time)
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
    work->r_sphere = 0x1C2;
    d18a_snake18_800CC8E0(work);
    work->anim = d18a_snake18_800CE8E0;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x50;
    work->flags &= ~0x212;
}
void d18a_snake18_800CEE60(Snake18Work *work)
{
    int arg;
    if (((unsigned char *)&work->flags)[1] & 1)
    {
        arg = work->f8B8;
        work->f8B8 = arg + 1;
        work->f8B4(work, arg);
    }
}

void d18a_snake18_800CEEAC(Snake18Work *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }

    {
        ACTPACK18 *t = work->actpack;
        int new_act;
        work->update_3p = d18a_snake18_800D09B4;
        work->update_1p = d18a_snake18_800D1750;
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

    work->update_3p = d18a_snake18_800D0A10;
    status = GM_PlayerStatus;
    work->update_1p = d18a_snake18_800D1750;
    GM_PlayerStatus = status | PLAYER_MOVE;
}

void d18a_snake18_800CEF44(Snake18Work *work, int arg1)
{
    int new_action;

    if (arg1 == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        d18a_snake18_800CC8B0(work, 0);
        new_action = work->actpack->damage->field_0[9];
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
        work->anim = d18a_snake18_800CF744;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_DAMAGED;
    }
}
void d18a_snake18_800CF03C(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800D1814;

        if (work->target->vital <= 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CF39C);
            return;
        }

        if (work->stance == 2)
        {
            action = work->actpack->damage->field_0[8];
        }
        else if (GV_Time & 1)
        {
            action = work->actpack->damage->field_0[0];
            work->stance = 0;
        }
        else
        {
            action = work->actpack->damage->field_0[1];
            work->stance = 0;
        }

        work->body.action = -1;
        if (action != work->body.action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        d18a_snake18_800CB7D0(work, 6);
    }

    if (work->body.is_end)
    {
        d18a_snake18_800CC8B0(work, 0x20);
        GM_PlayerStatus &= ~PLAYER_DAMAGED;

        if (work->stance == 2)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD808);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        }
    }
}
void d18a_snake18_800CF198(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        if (work->target->vital <= 0 && GM_GameOverTimer == 0)
        {
            GM_SeSet(&work->control.mov, 0x1A);
            GM_GameOver();
            GM_GameOverTimer = -3;
        }

        if (work->stance == 2)
        {
            d18a_snake18_800CB7D0(work, 6);
            GM_PlayerStatus &= ~PLAYER_DAMAGED;
            d18a_snake18_800CC8B0(work, 0x20);
            d18a_snake18_StartAnim(work, d18a_snake18_800CF744);
            return;
        }

        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800D1814;
        d18a_snake18_800CC8B0(work, 0);

        if (GV_Time & 1)
        {
            action = work->actpack->damage->field_0[2];
            work->f924 = 1;
        }
        else
        {
            action = work->actpack->damage->field_0[3];
            work->f924 = 2;
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        d18a_snake18_800CB7D0(work, 6);
    }

    if (work->body.is_end)
    {
        GM_PlayerStatus &= ~PLAYER_DAMAGED;
        d18a_snake18_800CC8B0(work, 0x20);
        d18a_snake18_StartAnim(work, d18a_snake18_800CF744);
        return;
    }

    if (time < 12 && work->f924 == 1)
    {
        work->control.turn.vy += 170;
    }

    if (time > 16)
    {
        GV_NearExp8V(&work->f904.vx, &DG_ZeroVector.vx, 3);
    }

    if (time == 24 && work->stance == 0)
    {
        GM_SeSetMode(&work->control.mov, 0x33, GM_SEMODE_BOMB);
    }

    work->control.step.vx = work->f904.vx;
    work->control.step.vz = work->f904.vz;
}
void d18a_snake18_800CF39C(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        GM_SeSet(&work->control.mov, 0x1A);
        GM_GameStatus |= STATE_PADRELEASE;
        work->flags |= 0x12;

        if (work->f924 != 1 && work->f924 != 2)
        {
            work->f924 = 1;
        }

        if (work->stance == 2)
        {
            if (work->f924 == 1)
            {
                action = work->actpack->damage->field_0[10];
            }
            else
            {
                action = work->actpack->damage->field_0[12];
            }
        }
        else
        {
            work->f924 = 1;
            action = work->actpack->damage->field_0[13];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        d18a_snake18_800CC8B0(work, 0);

        if (GM_GameOverTimer == 0)
        {
            GM_GameOver();
            GM_GameOverTimer = -3;
        }
    }

    if (work->body.is_end)
    {
        printf(" work->global_data = %d \n ", work->f924);

        if (work->f924 == 1)
        {
            action = work->actpack->damage->field_0[4];
        }
        else
        {
            action = work->actpack->damage->field_0[5];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CF718);

        if (GM_GameOverTimer == -3)
        {
            GM_GameOverTimer = 1;
        }
    }
}
void d18a_snake18_800CF574(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        d18a_snake18_800CC8B0(work, 0);
        GM_GameStatus |= STATE_PADRELEASE;
        work->flags |= 0x12;

        if (work->f924 != 1 && work->f924 != 2)
        {
            work->f924 = 1;
        }

        if (work->f924 == 1)
        {
            action = work->actpack->damage->field_0[11];
        }
        else
        {
            action = work->actpack->damage->field_0[12];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        if (GM_GameOverTimer == 0)
        {
            GM_GameOver();
            GM_GameOverTimer = -3;
        }
    }

    if (time == 45 && GM_GameOverTimer == -3)
    {
        GM_GameOverTimer = 1;
    }

    if (work->body.is_end)
    {
        if (work->f924 == 1)
        {
            action = work->actpack->damage->field_0[4];
        }
        else
        {
            action = work->actpack->damage->field_0[5];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CF718);
    }
}

void d18a_snake18_800CF718(Snake18Work *work, int time)
{
    if (time == 0x258)
    {
        GM_GameOverTimer = 0;
        GM_GameOver();
    }
}

void d18a_snake18_800CF744(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->stance = 2;
        work->flags |= 0x12;
        GM_PlayerStatus |= PLAYER_GROUND | PLAYER_DOWNED;

        if (work->f924 != 1 && work->f924 != 2)
        {
            work->f924 = 1;
        }

        if (work->f924 == 1)
        {
            action = work->actpack->damage->field_0[4];
        }
        else
        {
            action = work->actpack->damage->field_0[5];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        if (work->target->vital <= 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CF574);
            return;
        }

        work->update_3p = d18a_snake18_800D0AF8;
        work->update_1p = d18a_snake18_800D1814;
    }
}

void d18a_snake18_800CF850(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800D1814;
        GM_PlayerStatus &= ~PLAYER_GROUND;
        d18a_snake18_800CC8B0(work, 0);

        if (work->f924 == 1)
        {
            action = work->actpack->damage->field_0[6];
        }
        else
        {
            action = work->actpack->damage->field_0[7];
        }

        if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        work->f924 = 0;
    }

    if (time == 2)
    {
        work->control.turn.vx = 0;
        work->stance = 0;
    }

    if (work->body.is_end)
    {
        work->flags &= ~0x16;
        d18a_snake18_800CC8B0(work, 0x18);
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        work->flags |= 1;
        GM_PlayerStatus &= ~PLAYER_DOWNED;
    }
}
void d18a_snake18_800CF990(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        GM_PlayerStatus |= PLAYER_CHECK_WALL;

        if (d18a_dword_800DAF0C == 4)
        {
            action = work->actpack->still->tap_wall_l;
        }
        else
        {
            action = work->actpack->still->tap_wall_r;
        }

        GM_ConfigObjectOverride(&work->body, action, 0, 4, 0x3FE);
        GM_SeSet(&work->control.mov, 0x37);
        GM_SetNoise(100, 16, &work->control.mov);
    }

    if (work->body.time2 != 0 || work->body.action2 == 0)
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }

        GM_PlayerStatus &= ~PLAYER_CHECK_WALL;
        work->f8B4 = 0;
        work->flags &= ~0x100;
    }
}

void d18a_snake18_800CFB04(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800D198C;

        if (GM_PlayerStatus & PLAYER_CB_BOX)
        {
            action = work->actpack->special2->field_0[7];
        }
        else
        {
            action = work->actpack->special1[0];
        }

        if (action == 0x9E || work->stance == 2)
        {
            work->local_data = 32;
        }
        else if (work->body.action != action)
        {
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }

        GM_SeSet(&work->control.mov, 0x37);
        GM_SetNoise(100, 16, &work->control.mov);
    }

    if (work->local_data != 0)
    {
        if (--work->local_data == 0)
        {
            if (GM_PlayerStatus & PLAYER_INTRUDE)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
            }
            else
            {
                d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
            }
        }
        else
        {
            GM_SnakeCamera.position.vy += GV_RandU(16) * work->local_data;
        }
    }
    else if (work->body.is_end)
    {
        if (GM_PlayerStatus & PLAYER_CB_BOX)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CFF5C);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
        }
    }
}

void d18a_snake18_800CFD18(Snake18Work *work, int time)
{
    int action;
    int ground;

    if (time == 0)
    {
        ground = work->stance == 2;

        if (GM_PlayerStatus & PLAYER_CB_BOX)
        {
            action = work->actpack->special2->field_0[7];
        }
        else
        {
            action = work->actpack->special1[0];
        }

        if (action == 0x9E || ground == 1)
        {
            GM_SeSet(&work->control.mov, 0x37);
            GM_SetNoise(100, 16, &work->control.mov);
            work->f8B4 = 0;
            work->flags &= ~0x100;
            return;
        }

        GM_ConfigObjectOverride(&work->body, action, 0, 4, 0x3FE);
        GM_SeSet(&work->control.mov, 0x37);
        GM_SetNoise(100, 16, &work->control.mov);
    }

    if (work->body.time2 != 0)
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }

        work->f8B4 = 0;
        work->flags &= ~0x100;
    }
}

void d18a_snake18_800CFEE8(Snake18Work *work, int arg1)
{
    int new_action;
    if (arg1 != 0)
    {
        return;
    }
    work->update_3p = d18a_snake18_800CE7BC;
    work->update_1p = d18a_snake18_800CE7BC;
    new_action = d18a_snake18_800CB280(work, work->stance);
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
    work->update_3p = d18a_snake18_800D0B4C;
    actpack = work->actpack;
    work->update_1p = d18a_snake18_800D18EC;
    work->stance = 0;
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
    work->update_3p = d18a_snake18_800D0B84;
    actpack = work->actpack;
    work->update_1p = d18a_snake18_800D18EC;
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
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;

        new_action = work->actpack->special2->field_0[4];
        if (work->body.action != new_action)
        {
            GM_ConfigObjectAction(&work->body, new_action, 0, 4);
        }
    }

    if (work->body.is_end != 0)
    {
        work->anim = d18a_snake18_800CFF5C;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
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
        work->r_sphere = -2;
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800D1814;
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
        work->anim = d18a_snake18_800D01D8;
        work->f8F4 = 1;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
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
void d18a_snake18_800D01D8(Snake18Work *work, int time)
{
    int action;
    int r;
    int two;
    int base;
    int done;
    int dir;
    int stance;
    CONTROL *control;

    if (GM_GameLevel == 3)
    {
        if (time == 0 && GM_GameOverTimer == 0)
        {
            GM_SeSet(&work->control.mov, 0x1A);
            GM_GameOver();
            GM_GameOverTimer = -3;
        }

        if (time == 15 && GM_GameOverTimer == -3)
        {
            GM_GameOverTimer = 1;
        }

        if (time < 60)
        {
            work->control.levels[0] -= time * 16;
        }
    }

    if (time == 0)
    {
        work->body.action = -1;

        if (work->f8F4)
        {
            d18a_snake18_SetAction(work, work->force_act.action[1], 4);

            work->anim_time = 120;
            work->local_data = 1;
            work->force_act.n_acts = 2;
        }
        else
        {
            d18a_snake18_SetAction(work, work->force_act.action[0], 4);
        }

        dir = work->force_act.dir[0];
        if (dir >= 0)
        {
            work->control.turn.vy = dir;
            work->control.rot.vy = dir;
        }

        printf(d18a_aForceactdirdactiondnactsd_800DA6C8, dir, work->body.action, work->force_act.n_acts);

        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus &= ~(PLAYER_SQUAT | PLAYER_GROUND);
        GM_ConfigControlHazard(&work->control, 0, -2, -2);
        work->r_sphere = -2;
        d18a_snake18_800CC8B0(work, 0);
        work->flags |= 0x234;

        if (work->victim)
        {
            work->victim->damaged &= ~TARGET_CAPTURE;
            work->victim = 0;
            work->f924 = 0;
        }

        work->f8B4 = 0;
        work->flags &= ~0x100;

        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }

        *work->enable_shadow = 0;
        printf(d18a_aSnakeposddd_800DA6F0, work->control.mov.vx, work->control.mov.vy, work->control.mov.vz);
        printf(d18a_aSnakesetactiond_800DA708, work->body.action);
    }

    two = 2;
    action = work->body.action;
    base = work->f8F0;

    // a switch (action % 3) with the case value 2 held in a register; gotos kept: a real switch
    // compares against an immediate 2 (slti) and nested ifs place the case bodies inline
    if (action % 3 != 1)
    {
        if (action % 3 < two)
        {
            if (action % 3 == 0)
            {
                goto case0;
            }
        }
        else if (action % 3 == two)
        {
            goto case2;
        }
    }

    goto next;

case0:
    if (work->m_ctrl.info1.frame == 1 && GM_GameLevel != 3)
    {
        GM_SeSet(&work->control.mov, 0xB2);
    }

    if (work->m_ctrl.info1.frame == 15 && GM_GameLevel != 3)
    {
        GM_SeSet(&work->control.mov, 0x18);
    }

    if (work->m_ctrl.info1.frame == 2 && !(GM_GameStatus & STATE_STUN))
    {
        NewPadVibration(d18a_dword_800C381C, 1);
        NewPadVibration(d18a_dword_800C3824, 2);
    }
    goto next;

case2:
    if (work->m_ctrl.info1.frame == 1 && !(GM_GameStatus & STATE_STUN))
    {
        NewPadVibration(d18a_dword_800C382C, 1);
        NewPadVibration(d18a_dword_800C3834, 2);
    }

    if (work->m_ctrl.info1.frame == 12)
    {
        GM_SeSet(&work->control.mov, 0xB3);
    }

next:
    done = 0;

    if (action == base * 3 + 1)
    {
        unsigned short press = work->pad->press;

        if ((press & PAD_U) && time >= 31 && time < 119)
        {
            work->anim_time = 120;
        }

        if (press & PAD_ABXY)
        {
            work->anim_time++;
        }

        if (GM_GameLevel != 3 && time >= 126)
        {
            done = 1;
        }
    }
    else if (work->body.is_end)
    {
        done = 1;
    }

    if (!done)
    {
        return;
    }

    if (--work->force_act.n_acts != 0)
    {
        work->local_data++;

        dir = work->force_act.dir[work->local_data];
        if (dir >= 0)
        {
            work->control.rot.vy = dir;
            work->control.turn.vy = dir;
        }

        d18a_snake18_SetAction(work, work->force_act.action[work->local_data], 4);

        if (work->force_act.action[work->local_data] == base * 3 + 1)
        {
            d18a_snake18_800CC8E0(work);
            work->target->class &= ~TARGET_PUSH;
        }
        else
        {
            d18a_snake18_800CC8B0(work, 0);
        }

        printf(d18a_aNextmotiondlocaldatad_800DA724, work->force_act.action[work->local_data], work->local_data);
        return;
    }

    control = &work->control;
    GM_ConfigControlHazard(control, d18a_dword_800C37F8[work->stance], 450, 450);
    work->r_sphere = 450;
    d18a_snake18_800CC8E0(work);
    work->flags &= ~0x206;
    work->flags &= ~0x30;
    GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_ATTACK | PLAYER_CAUTION);
    DG_InvisiblePrim(work->lsight_prim);
    GM_ExitBehindCamera();
    GM_ConfigMotionControl(&work->body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2,
                           control, work->rots);

    dir = work->force_act.end_dir;
    if (dir >= 0)
    {
        work->control.rot.vy = dir;
        work->control.turn.vy = dir;
    }

    stance = work->force_act.end_stance;
    work->body.action = -1;

    if (stance < 0)
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            stance = 3;
        }
        else
        {
            stance = work->stance;
        }
    }

    if (stance < 3)
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            GM_PlayerStatus &= ~PLAYER_INTRUDE;
            d18a_snake18_800CB42C(work);
        }

        work->stance = stance;
        d18a_snake18_SetAction(work, d18a_snake18_800CB280(work, stance), 4);

        d18a_snake18_StartAnim(work, d18a_dword_800C37E4[stance]);
    }
    else
    {
        if (!(GM_PlayerStatus & PLAYER_INTRUDE))
        {
            work->stance = 2;
            GM_PlayerStatus |= PLAYER_INTRUDE | PLAYER_GROUND;
            d18a_snake18_800CB3E8(work);
        }

        d18a_snake18_SetAction(work, d18a_snake18_800CB280(work, 2), 4);

        d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
    }

    *work->enable_shadow = 1;
    work->control.height = work->body.height = d18a_dword_800C3920[work->stance];
    GM_PlayerStatus &= ~PLAYER_ACT_ONLY;
    d18a_snake18_800CC8B0(work, 0x18);
    work->flags |= 1;
}

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

void d18a_snake18_800D09B4(Snake18Work *work, int time)
{
    u_short status;

    status = work->pad->status;
    if ( status & ( PAD_UP | PAD_DOWN ) )
    {
        work->anim = d18a_snake18_800CEF0C;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        d18a_snake18_800D0974( work );
    }
}

void d18a_snake18_800D0A10(Snake18Work *work, int time)
{
    int status;
    int flag;
    int new_action;

    status = GM_PlayerStatus;
    if (!(status & 2))
    {
        work->anim = d18a_snake18_800CE998;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    flag = (unsigned short)work->pad->status;
    if (!(flag & (PAD_U | PAD_D)))
    {
        GM_PlayerStatus = status & ~0x10;
        work->anim = d18a_snake18_800CEEAC;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (flag & PAD_U)
    {
        new_action = work->actpack->move->crouch;
    }
    else
    {
        new_action = work->actpack->move->crouch_backwards;
    }
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }
    d18a_snake18_800D0974(work);
}

void d18a_snake18_800D0AF8(Snake18Work *work, int time)
{
    if ( work->pad->press & ~PAD_TRIANGLE )
    {
        work->anim = d18a_snake18_800CF850;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_GROUND;
    }
}

void d18a_snake18_800D0B4C(Snake18Work *work, int time)
{
    if (d18a_dword_800DAEF0 < 0)
    {
        return;
    }

    work->anim = d18a_snake18_800CFFD4;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void d18a_snake18_800D0B84(Snake18Work *work, int time)
{
    int state = d18a_dword_800DAEF0;
    if (state < 0)
    {
        work->anim = d18a_snake18_800D0054;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~PLAYER_MOVE;
    }
    else
    {
        work->control.turn.vy = d18a_snake18_800CAEC0(work, state);
    }
}

int d18a_snake18_800D0BF4(Snake18Work *work)
{
    SVECTOR vec;
    SVECTOR pos;
    int     press;
    int     status;

    press = work->pad->press;
    status = work->pad->status;

    if (press & (PAD_L1 | PAD_R1))
    {
        if (press & PAD_L1)
        {
            vec = d18a_dword_800C3928[0];
        }
        else
        {
            vec = d18a_dword_800C3928[1];
        }

        work->local_data = (press & PAD_L1) ? PAD_L1 : PAD_R1;
        DG_RotVector(&vec, &vec, 1);

        if (work->f926 == 0)
        {
            GV_AddVec3(&work->control.mov, &vec, &work->f914);
            work->f91C = work->control.mov;
            work->flags |= 0x8000;
        }
        else
        {
            GV_AddVec3(&work->f91C, &vec, &work->f914);
        }

        work->f926 = 4;
        work->f928 = work->control.mov.vy;
    }

    if (status & work->local_data)
    {
        if (work->f926 == 4)
        {
            pos = work->control.mov;
            GV_NearExp4V(&pos.vx, &work->f914.vx, 3);
            GV_SubVec3(&pos, &work->control.mov, &work->control.step);

            work->control.mov.vy = work->f928;
            DG_SetPos2(&work->control.mov, &work->control.rot);
            ReadRotMatrix(&work->body.objs->world);
            work->f904.vy = 0;
            return 1;
        }
    }
    else if (work->f926 > 0)
    {
        GV_NearTimeV(&work->control.mov.vx, &work->f91C.vx, work->f926, 3);

        if (--work->f926 == 0)
        {
            work->control.mov = work->f91C;
            work->flags &= ~0x8000;
        }

        work->control.mov.vy = work->f928;
        DG_SetPos2(&work->control.mov, &work->control.rot);
        ReadRotMatrix(&work->body.objs->world);
        work->f904.vy = 0;
        return 1;
    }

    work->local_data = 0;
    return 0;
}
void d18a_snake18_800D0E3C(Snake18Work *work)
{
    Snake18Init   *init = &work->f8C4;
    int            min;
    int            max;
    unsigned short status;
    int            angle;
    int            n;
    int            d;

    min = -init->look_min;
    max = init->look_max;
    status = work->pad->status;

    if (work->f8C4.mode == 0)
    {
        if (work->stance == 2)
        {
            angle = work->f902;
        }
        else
        {
            angle = 0;
        }
    }
    else
    {
        angle = work->control.turn.vx;
    }

    if (work->stance == 2)
    {
        min += angle;
        max += angle;

        if (min < -1023)
        {
            min = -1023;
        }

        if (max > 1023)
        {
            max = 1023;
        }
    }

    if (!(GM_Configuration & 0x1000))
    {
        if (status & PAD_UP)
        {
            n = (work->flags & 0x4000) ? 0x50 - work->pad->left_dy : 1;
            d = (work->flags & 0x4000) ? 0x50 : 1;
            angle -= init->look_up * (n & 0xFF) / d;
        }
        else if (status & PAD_DOWN)
        {
            n = (work->flags & 0x4000) ? work->pad->left_dy + 0x50 : 1;
            d = (work->flags & 0x4000) ? 0x4F : 1;
            angle += init->look_down * (n & 0xFF) / d;
        }
    }
    else
    {
        /* inverted vertical controls */
        if (status & PAD_DOWN)
        {
            n = (work->flags & 0x4000) ? 0x50 - work->pad->left_dy : 1;
            d = (work->flags & 0x4000) ? 0x50 : 1;
            angle -= init->look_up * (n & 0xFF) / d;
        }
        else if (status & PAD_UP)
        {
            n = (work->flags & 0x4000) ? work->pad->left_dy + 0x50 : 1;
            d = (work->flags & 0x4000) ? 0x4F : 1;
            angle += init->look_down * (n & 0xFF) / d;
        }
    }

    if (angle < min)
    {
        angle = min;
    }

    if (max < angle)
    {
        angle = max;
    }

    work->control.turn.vx = angle;
}
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
        if (work->flags & 0x4000)
            n = 0x50 - work->pad->left_dx;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x50;
        else
            d = 1;

        turn += init->turn_l * (n & 0xFF) / d;
    }
    else
    {
        if (work->flags & 0x4000)
            n = work->pad->left_dx + 0x50;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x4F;
        else
            d = 1;

        turn -= init->turn_r * (n & 0xFF) / d;
    }

    work->control.turn.vy = turn;
}
void d18a_snake18_800D11A8(Snake18Work *work)
{
    GV_PAD        *pad;
    unsigned short status;
    int            min;
    int            max;
    int            angle;
    int            n;
    int            d;

    min = work->f902 - 120;
    max = work->f902 + 120;
    angle = work->control.turn.vx;
    pad = work->pad;
    status = pad->status;

    if (min < -1023)
    {
        min = -1023;
    }

    if (max > 1023)
    {
        max = 1023;
    }

    if (status & PAD_UP)
    {
        if (work->flags & 0x4000)
            n = 0x50 - pad->left_dy;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x50;
        else
            d = 1;

        angle -= ((n & 0xFF) << 1) / d;
    }
    else if (status & PAD_DOWN)
    {
        if (work->flags & 0x4000)
            n = pad->left_dy + 0x50;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x4F;
        else
            d = 1;

        angle += ((n & 0xFF) << 1) / d;
    }

    if (angle < min)
    {
        angle = min;
    }

    if (max < angle)
    {
        angle = max;
    }

    work->control.turn.vx = angle;
}
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

        if (work->flags & 0x4000)
            n = 0x50 - pad->left_dx;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x50;
        else
            d = 1;

        turn += ((n & 0xFF) << 1) / d;
    }
    else
    {
        int n;
        int d;

        if (work->flags & 0x4000)
            n = pad->left_dx + 0x50;
        else
            n = 1;

        if (work->flags & 0x4000)
            d = 0x4F;
        else
            d = 1;

        turn -= ((n & 0xFF) << 1) / d;
    }

    work->control.turn.vy = turn;
}
void d18a_snake18_800D1424(Snake18Work *work, int time)
{
    unsigned short status;
    unsigned short press;
    int            height;

    status = work->pad->status;
    press = work->pad->press;

    GM_PlayerStatus &= ~PLAYER_MOVE;
    d18a_snake18_SetAction(work, d18a_snake18_800CB280(work, work->stance), 4);

    height = (work->stance == 2) ? 320 : 0;
    work->f8C4.field_4 = height;
    GM_SnakeCamera.position.vy += height;

    if (!(status & PAD_TRIANGLE))
    {
        d18a_snake18_800CB378(work);
        d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
        return;
    }

    d18a_snake18_800D0E3C(work);
    d18a_snake18_800D1064(work);

    if (press & PAD_CROSS)
    {
        if (work->stance == 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD768);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            GM_PlayerStatus &= ~(PLAYER_SQUAT | PLAYER_GROUND);
        }
    }
}

void d18a_snake18_800D1598(Snake18Work *work, int time)
{
    unsigned short press;
    int            action;

    press = work->pad->press;

    if (!(work->pad->status & PAD_TRIANGLE))
    {
        d18a_snake18_800CB378(work);
        work->local_data = 2;
        return;
    }

    if (GM_PlayerStatus & PLAYER_MOVE)
    {
        GM_PlayerStatus &= ~PLAYER_MOVE;

        if (work->stance == 0)
        {
            action = work->actpack->still->against_wall;
        }
        else
        {
            action = work->actpack->still->squat_against_wall;
        }

        d18a_snake18_SetAction(work, action, 4);
    }

    if ((work->pad->press & PAD_UDLR) || !(work->pad->status & PAD_UDLR))
    {
        GM_PlayerStatus &= ~PLAYER_CAUTION;
        d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
        GM_ExitBehindCamera();
        return;
    }

    if (press & PAD_CROSS)
    {
        if (work->stance == 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CDC3C);
        }
        else
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD9A8);
            GM_PlayerStatus &= ~PLAYER_SQUAT;
        }
    }
}

void d18a_snake18_800D1750(Snake18Work *work, int time)
{
    int new_action;

    GM_PlayerStatus &= ~0x10;
    new_action = work->actpack->still->crouch;
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }

    if (!(work->pad->status & PAD_X))
    {
        work->f926 = 0;
        work->anim = d18a_snake18_800CEEAC;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_PlayerStatus &= ~0x8001;
    }

    d18a_snake18_800D0E3C(work);
    d18a_snake18_800D1064(work);
}

void d18a_snake18_800D1814(Snake18Work *work, int time)
{
    if (!(work->pad->status & PAD_X))
    {
        d18a_snake18_800CB378(work);
    }

    if (work->anim == d18a_snake18_800CF744)
    {
        if (work->pad->press & ~PAD_X)
        {
            work->anim = d18a_snake18_800CF850;
            work->anim_time = 0;
            work->local_data2 = 0;
            work->local_data = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_PlayerStatus &= ~0x40;
        }
    }

    GM_SnakeCamera.position.vy += 0x140;

    if (work->anim != d18a_snake18_800CF03C)
    {
        d18a_snake18_800CB514(work);
    }
}

void d18a_snake18_800D18EC(Snake18Work *work, int time)
{
    int new_action;

    GM_PlayerStatus &= ~0x10;
    new_action = work->actpack->special2->field_0[2];
    if (work->body.action != new_action)
    {
        GM_ConfigObjectAction(&work->body, new_action, 0, 4);
    }

    if (work->pad->status & PAD_X)
    {
        return;
    }

    d18a_snake18_800CB378(work);
    work->anim = d18a_snake18_800CFF5C;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
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

    if ((work->weapon_flags & 0x40) && (GM_PlayerStatus & PLAYER_ATTACK))
    {
        func = work->weapon_state;
        if (func != NULL)
        {
            arg = work->weapon_time;
            work->weapon_time = arg + 1;
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
        ACTPACK18 *t = work->actpack;
        int new_act;
        work->update_3p = d18a_snake18_800D24CC;
        work->update_1p = d18a_snake18_800CE7BC;
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
        work->update_3p = d18a_snake18_800D2660;
        t = work->actpack;
        work->update_1p = d18a_snake18_800CE7BC;
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
        work->update_3p = d18a_snake18_800D26E4;
        t = work->actpack;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus |= PLAYER_MOVE;
        new_act = t->move->stand;
        if (work->body.action != new_act)
        {
            GM_ConfigObjectAction(&work->body, new_act, 0, 4);
        }
    }
}

void d18a_snake18_800D1BAC(Snake18Work *work, int time)
{
    SVECTOR diff;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        d18a_snake18_SetAction(work, work->actpack->attack->shoot, 4);

        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }
    }

    if (work->body.is_end)
    {
        d18a_snake18_SetAction(work, work->actpack->attack->aim, 4);
    }

    if (time >= 8)
    {
        if (dword_8009F46C[0] == 0)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            work->flags &= ~4;
        }
        else
        {
            GV_SubVec3(&svector_8009F478, &work->control.mov, &diff);
            work->control.turn.vy = GV_VecDir2(&diff);
        }
    }
}

void d18a_snake18_800D1CE8(Snake18Work *work, int time)
{
    MATRIX mat;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800D2D88;
        work->update_1p = d18a_snake18_800D2D88;
        GM_Camera.first_person = 0;
        work->f8F8 = 0;
        GM_PlayerStatus = (GM_PlayerStatus & ~PLAYER_MOVE) | PLAYER_MENU_DISABLE;

        switch (work->stance)
        {
        case 0:
            d18a_snake18_SetAction(work, work->actpack->still->squat, 4);
            work->f904.vy = -128;
            work->local_data2 = 0;
            break;

        case 1:
            work->local_data2 = 1;
            break;

        case 2:
            work->local_data2 = 3;
            break;
        }
    }

    switch (work->local_data2)
    {
    case 0:
        if (time == 4)
        {
            work->local_data2 = 1;
        }
        break;

    case 1:
        work->stance = 1;
        GM_PlayerStatus |= PLAYER_SQUAT;
        d18a_snake18_SetAction(work, work->actpack->trans->crouch, 4);
        work->local_data2 = 2;
        break;

    case 2:
        if (work->body.is_end)
        {
            work->local_data2 = 3;
        }
        break;

    case 3:
        GM_Camera.first_person = 1;
        work->f8F8 = -4;
        GM_PlayerStatus |= PLAYER_GROUND;
        d18a_snake18_800CB34C(work);
        work->stance = 2;
        work->control.turn.vx = work->f902;
        GM_PlayerStatus &= ~(PLAYER_SQUAT | PLAYER_MENU_DISABLE);
        d18a_snake18_SetAction(work, work->actpack->attack->aim, 4);
        work->local_data2 = 4;
        break;

    default:
        DG_SetPos(&work->body.objs->objs[4].world);
        DG_MovePos(&d18a_dword_800C3938);
        ReadRotMatrix(&mat);

        GM_SnakeCamera.position.vx = mat.t[0];
        GM_SnakeCamera.position.vy = mat.t[1];
        GM_SnakeCamera.position.vz = mat.t[2];

        if ((GM_PlayerStatus & PLAYER_INVINCIBLE) && GM_Camera.first_person != 0)
        {
            GM_SnakeCamera.position.vy += GV_RandU(16) * work->invuln;
        }
        break;
    }
}
void d18a_snake18_800D1F90(Snake18Work *work, int time)
{
    if (time == 0)
    {
        work->update_3p = d18a_snake18_800D2F70;
        work->update_1p = d18a_snake18_800D2F70;
        d18a_snake18_SetAction(work, work->actpack->attack->aim, 4);
        work->stance = 0;
        GM_PlayerStatus &= ~(PLAYER_SQUAT | PLAYER_GROUND | PLAYER_MENU_DISABLE);
    }
}

void d18a_snake18_800D200C(Snake18Work *work, int time)
{
    if (time == 0)
    {
        if (bakudan_count_8009F42C >= 16 || (d18a_dword_800DAF08 & 1))
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            return;
        }

        work->update_3p = d18a_snake18_800D3218;
        work->update_1p = d18a_snake18_800CE7BC;
        work->stance = 1;
        work->flags |= 4;
        GM_PlayerStatus |= PLAYER_SQUAT;
        d18a_snake18_SetAction(work, work->actpack->attack->field_5, 4);
        GM_PlayerStatus &= ~PLAYER_MOVE;
    }
}

void d18a_snake18_800D20EC(Snake18Work *work, int time)
{
    SVECTOR *vec;
    TARGET  *target;

    vec = &work->f838;

    if (time == 0)
    {
        if (bakudan_count_8009F42C >= 16)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            return;
        }

        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        work->flags |= 4;
        d18a_snake18_SetAction(work, work->actpack->attack->field_6, 4);

        target = work->victim;
        DG_PutVector(&d18a_dword_800C3940, vec, 1);
        GV_SubVec3(&target->center, vec, vec);

        vec->vx /= 4;
        vec->vy /= 4;
        vec->vz /= 4;
    }

    if (time < 4)
    {
        GV_AddVec3(&work->control.step, vec, &work->control.step);
    }

    if (time == 6)
    {
        GM_SeSet(&work->control.mov, 0x31);
        NewBakudan(work->victim->body, &d18a_dword_800C3948, 1, work->side);
        work->trigger = 5;
        work->victim->damaged &= ~0x40;
        work->victim = 0;
    }

    if (work->body.is_end)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        work->flags &= ~4;
    }
}
void d18a_snake18_800D22C8(Snake18Work *work, int a1)
{
    int s1 = work->stance;

    work->control.turn.vy = *(unsigned short *)&d18a_dword_800DAEF4;

    if (a1 == 0)
    {
        int act;

        if (s1 == 0)
            act = work->actpack->attack->field_6;
        else
            act = work->actpack->attack->field_7;

        if (work->body.action2 != act)
        {
            GM_ConfigObjectOverride(&work->body, act, 0, 4, 0xFFFF);
        }
    }

    if ((s1 == 0 && a1 == 6) || (s1 == 1 && a1 == 0xE))
    {
        work->trigger = 3;
    }

    if (work->body.time2 != 0 || work->body.action2 == 0)
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }
        work->f8B4 = 0;
        work->flags &= ~0x100;
    }
}
void d18a_snake18_800D23F0(Snake18Work *work, int time)
{
    if (time == 0)
    {
        if (counter_8009F448 == 8 || (d18a_dword_800DAF08 & 1))
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            return;
        }

        work->update_3p = d18a_snake18_800D3330;
        work->update_1p = d18a_snake18_800CE7BC;
        work->stance = 1;
        work->flags |= 4;
        GM_PlayerStatus |= PLAYER_SQUAT;
        d18a_snake18_SetAction(work, work->actpack->attack->aim, 4);
        GM_PlayerStatus &= ~PLAYER_MOVE;
    }
}

static inline int d18a_snake18_CanTurnShoot(Snake18Work *work)
{
    if (work->actpack->attack->setup == 0x9E || work->weapon_state == d18a_snake18_800D28CC)
    {
        return 0;
    }

    return 1;
}

void d18a_snake18_800D24CC(Snake18Work *work, int time)
{
    GM_PlayerStatus &= ~PLAYER_MOVE;

    if (!(GM_PlayerStatus & PLAYER_ATTACK))
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        return;
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        d18a_snake18_SetAction(work, work->actpack->still->setup, 4);
        return;
    }

    GM_PlayerStatus |= PLAYER_MOVE;

    if ((work->pad->status & PAD_CROSS) || (work->weapon_flags & 8))
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D1ACC);
        return;
    }

    if (d18a_snake18_800CAC68(work->control.turn.vy, d18a_dword_800DAEF0) == 3 && d18a_snake18_CanTurnShoot(work))
    {
        work->f924 = d18a_dword_800DAEF0;
        d18a_snake18_StartAnim(work, d18a_snake18_800CEA84);
        return;
    }

    d18a_snake18_800CB60C(work);
}
void d18a_snake18_800D2660(Snake18Work *work, int arg1)
{
    if (arg1 == 2 && d18a_dword_800DAEF0 >= 0)
    {
        work->anim = d18a_snake18_800D1B3C;
        work->anim_time = 0;
        work->local_data2 = 0;
        work->local_data = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (work->body.is_end == 0)
    {
        return;
    }

    work->anim = d18a_snake18_800D1A6C;
    work->anim_time = 0;
    work->local_data2 = 0;
    work->local_data = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_PlayerStatus &= ~0x10;
}
void d18a_snake18_800D26E4(Snake18Work *work, int time)
{
    int dir;

    if (!(GM_PlayerStatus & PLAYER_ATTACK))
    {
        if (work->body.action2 != 0)
        {
            GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CD888);
        return;
    }

    if (d18a_dword_800DAEF0 < 0 || (!(work->weapon_flags & 8) && !(work->pad->status & PAD_CROSS)))
    {
        if (++work->local_data2 >= 5)
        {
            GM_PlayerStatus &= ~PLAYER_MOVE;
            d18a_snake18_StartAnim(work, d18a_snake18_800D1A6C);
            return;
        }
    }
    else
    {
        work->local_data2 = 0;
    }

    if (d18a_dword_800DAEF0 < 0)
    {
        dir = work->control.turn.vy;
    }
    else
    {
        dir = d18a_snake18_800CAEC0(work, d18a_dword_800DAEF0);
    }

    work->control.turn.vy = dir;
    d18a_snake18_800CB228(work, dir);
}
void d18a_snake18_800D281C(Snake18Work *work)
{
    int yaw;
    int pitch;
    int diff;

    GM_GetHomingTarget(&work->body.objs->objs[6].world, work->control.rot.vy,
                       &yaw, &pitch, work->control.map->index);

    diff = work->adjust[2].vx - pitch;
    if (diff >= 0x41)
        pitch = work->adjust[2].vx - 0x40;
    else if (diff < -0x40)
        pitch = work->adjust[2].vx + 0x40;

    work->adjust[2].vx = pitch;
    work->adjust[6].vx = pitch;
    work->adjust[7].vx = pitch * 3 / 2;

    if (yaw >= 0)
    {
        work->control.turn.vy = yaw;
    }
}
void d18a_snake18_800D28CC(Snake18Work *work, int time)
{
    int mask;
    int ammo;
    int mag_size;

    if (GM_PlayerStatus & PLAYER_MOVE)
    {
        mask = 0x3FE;
    }
    else
    {
        mask = 0xFFFF;
    }

    if (time == 0)
    {
        GM_ConfigMotionAdjust(&work->body, NULL);
        NewAnime_8005DDE0(&work->body.objs->objs[4].world);
        d18a_snake18_SetOverride(work, work->actpack->attack->reload, 4, mask);
    }

    d18a_snake18_800CB760(work, mask);

    if (time == 16)
    {
        ammo = GM_MagazineMax;
        mag_size = GM_Weapons[work->weapon];

        if (ammo > 0 && ammo < mag_size)
        {
            mag_size = ammo;
        }

        GM_MagazineMax = ammo;
        GM_Magazine = mag_size;
        GM_SeSet(&work->control.mov, 0x2F);
    }

    if (work->body.time2 != 0)
    {
        d18a_snake18_800CB7BC(work, d18a_snake18_800D2A80);

        if (!(work->pad->status & PAD_SQUARE))
        {
            GM_PlayerStatus &= ~PLAYER_ATTACK;

            if (work->body.action2 != 0)
            {
                GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
            }

            d18a_snake18_800CB7BC(work, d18a_snake18_800CEB78);
            d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
        }
    }
}

void d18a_snake18_800D2A80(Snake18Work *work, int time)
{
    int            mask;
    int            tbl;
    int            fire;
    unsigned short status;
    unsigned short release;
    int            trg;

    mask = (GM_PlayerStatus & PLAYER_MOVE) ? 0x3FE : 0xFFFF;
    tbl = work->weapon_flags;
    fire = 0;

    if (time == 0)
    {
        d18a_snake18_SetOverride(work, work->actpack->attack->aim, 4, mask);
        fire = work->local_data;
        work->f86C = 0;

        if (tbl & 2)
        {
            GM_ConfigMotionAdjust(&work->body, work->adjust);
        }
    }

    d18a_snake18_800CB760(work, mask);

    if (GM_Magazine == 0 && GM_MagazineMax != 0 && GM_Weapons[work->weapon] > 0)
    {
        d18a_snake18_800CB7BC(work, d18a_snake18_800D28CC);
        return;
    }

    if (d18a_dword_800DAEF0 < 0 && (tbl & 2))
    {
        d18a_snake18_800D281C(work);
    }

    status = work->pad->status;
    release = work->pad->release;
    trg = 1;

    if (((tbl & 1) && (status & PAD_SQUARE)) || (release & PAD_SQUARE))
    {
        fire = 1;
    }

    if (fire)
    {
        trg |= 2;
    }

    work->trigger = trg;

    switch (work->f86C)
    {
    case 0:
        if (trg & 2)
        {
            work->f86C = 1;
            d18a_snake18_SetOverride(work, work->actpack->attack->shoot, 2, mask);

            if (tbl & 0x80)
            {
                d18a_snake18_StartAnim(work, d18a_snake18_800D1BAC);
                GM_PlayerStatus &= ~(PLAYER_MOVE | PLAYER_ATTACK);
                work->flags |= 4;
                return;
            }
        }
        break;

    case 1:
        if (work->body.time2 != 0 && !(tbl & 1))
        {
            work->f86C = 0;
            d18a_snake18_SetOverride(work, work->actpack->attack->aim, 2, mask);
        }
        break;
    }

    if (!(status & PAD_SQUARE) || *work->n_bullets == 0)
    {
        if (++work->f86E >= 5 || (tbl & 1))
        {
            d18a_snake18_800CB7BC(work, d18a_snake18_800CEB78);
            GM_ConfigMotionAdjust(&work->body, NULL);
            GM_PlayerStatus &= ~PLAYER_ATTACK;
        }
    }
    else
    {
        work->f86E = 0;
    }
}
void d18a_snake18_800D2D88(Snake18Work *work, int time)
{
    int     ammo;
    int     max;
    SVECTOR *rots;
    int     rx;
    int     ry;

    if (work->local_data2 < 3)
    {
        return;
    }

    if (GM_Magazine == 0 && (ammo = GM_Weapons[WP_Rifle]) > 0)
    {
        max = GM_MagazineMax;
        if (max > 0 && max < ammo)
        {
            ammo = max;
        }

        GM_MagazineMax = max;
        GM_Magazine = ammo;
    }

    work->trigger = (work->pad->release & PAD_SQUARE) ? 3 : 1;

    if (work->pad->status & PAD_UDLR)
    {
        d18a_snake18_800D11A8(work);
        d18a_snake18_800D1300(work);
    }

    rots = work->body.objs->rots;
    rx = rots->vx;
    ry = rots->vy;

    if (work->body.action == 0x98)
    {
        work->control.turn.vy += ry - work->f86C;
        work->control.turn.vx += rx - work->f86E;
    }

    work->f86C = ry;
    work->f86E = rx;

    if (GM_TranquilizerTimer > 0)
    {
        GM_TranquilizerTimer--;
    }

    if (work->body.action == work->actpack->attack->aim)
    {
        if (++work->local_data == 90)
        {
            work->local_data = 0;

            if (GM_TranquilizerTimer <= 0)
            {
                GM_StatusEvent &= ~EV_Tranquilizer;
                d18a_snake18_SetAction(work, 0x98, 4);
            }
        }
    }
    else if (work->body.is_end || (GM_StatusEvent & EV_Tranquilizer))
    {
        d18a_snake18_SetAction(work, work->actpack->attack->aim, 4);
    }
}

void d18a_snake18_800D2F70(Snake18Work *work, int time)
{
    int          trg;
    Snake18Init *init;

    trg = 1;
    if ((work->pad->release & PAD_SQUARE) && *work->n_bullets > 0)
    {
        trg = 3;
    }

    work->trigger = trg;

    if (work->pad->status & PAD_UDLR)
    {
        init = &work->f8C4;
        init->mode = 1;
        init->look_min = 0x200;
        init->look_max = 0x200;
        init->look_up = 32;
        init->look_down = 32;
        init->turn_r = 32;
        init->turn_l = 32;
        d18a_snake18_800D0E3C(work);
        d18a_snake18_800D1064(work);
        d18a_snake18_800CB2EC(work);
    }
}

void d18a_snake18_800D3024(Snake18Work *work, int time)
{
    int mask;
    int trg;
    int frame;

    mask = (GM_PlayerStatus & PLAYER_MOVE) ? 0x3FE : 0xFFFF;

    if (time == 0)
    {
        d18a_snake18_SetOverride(work, work->actpack->attack->aim, 4, mask);
        work->f86C = 0;
        GM_SeSet(&work->control.mov, 0x2C);
    }

    d18a_snake18_800CB760(work, mask);

    trg = 1;
    frame = work->m_ctrl.info2.frame;

    switch (work->f86C)
    {
    case 0:
        if (work->body.time2 != 0)
        {
            d18a_snake18_SetOverride(work, work->actpack->still->stand, 1, mask);
            work->f86C = 1;
        }
        break;

    case 1:
        if (!(work->pad->status & PAD_SQUARE))
        {
            d18a_snake18_SetOverride(work, work->actpack->attack->shoot, 1, mask);
            work->f86C = 2;
        }
        break;

    case 2:
        if (frame == 6)
        {
            trg = 3;
            work->f86C = 3;
        }
        break;

    case 3:
        trg = 0;

        if (work->body.time2 != 0)
        {

            if (work->body.action2 != 0)
            {
                GM_ConfigObjectOverride(&work->body, 0, 0, 4, 0);
            }

            GM_PlayerStatus &= ~PLAYER_ATTACK;
        }
        break;
    }

    work->trigger = trg;
}
void d18a_snake18_800D3218(Snake18Work *work, int time)
{
    int done;

    work->trigger = 1;

    if (time < 6)
    {
        return;
    }

    done = work->local_data;
    if (done == 0)
    {
        d18a_snake18_800CB59C(work);
    }

    if (!(work->pad->status & PAD_SQUARE) && done == 0)
    {
        d18a_snake18_SetAction(work, work->actpack->attack->field_8, 1);
        done = 1;
        work->local_data = done;
        work->trigger |= 2;
    }

    if (done != 0 && work->body.is_end)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        GM_PlayerStatus &= ~PLAYER_SQUAT;
        work->flags &= ~4;
    }

    work->f904.vy = -100;
}

void d18a_snake18_800D3330(Snake18Work *work, int time)
{
    int       done;
    int       x;
    int       y;
    int       w;
    POLY_GT4 *poly;
    int       i;

    work->trigger = 1;

    if (time < 6)
    {
        return;
    }

    done = work->local_data;
    if (done == 0)
    {
        d18a_snake18_800CB59C(work);

        DG_GroupPrim(work->lsight_prim, DG_CurrentGroupID);
        DG_VisiblePrim(work->lsight_prim);
        DG_PutPrim(work->lsight_prim);

        if (!(work->pad->status & PAD_SQUARE))
        {
            d18a_snake18_SetAction(work, work->actpack->attack->shoot, 1);
            done = 1;
            work->local_data = done;
            work->trigger |= 2;
        }
    }

    y = GV_Time & 63;
    if (y > 32)
    {
        y = 64 - y;
    }

    x = work->lsight_tex->off_x;
    w = x + 63;
    y += work->lsight_tex->off_y;

    poly = work->lsight_prim->packs[GV_Time & 1];
    for (i = 0; i < 2; i++)
    {
        setUV4(poly, x, y, w, y, x, y, w, y);
        poly++;
    }

    if (done != 0 && work->body.is_end)
    {
        work->flags &= ~4;
        GM_PlayerStatus &= ~PLAYER_SQUAT;
        DG_InvisiblePrim(work->lsight_prim);
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
    }

    work->f904.vy = -100;
}

void d18a_snake18_800D3508(Snake18Work *work, int time)
{
    PUNCH   *punch;
    SVECTOR *vec;
    int      action;
    TARGET *target;

    if (time == 0)
    {
        punch = d18a_dword_800C3950;
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus &= ~PLAYER_MOVE;
        action = work->actpack->attack->shoot;

        if (!d18a_snake18_800CB9CC(work, punch))
        {
            punch++;
            action = work->actpack->attack->field_5;

            if (!d18a_snake18_800CB9CC(work, punch))
            {
                d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
                work->flags &= ~4;
                return;
            }
        }

        if (work->victim->class & 0x20)
        {
            if (work->victim)
            {
                work->victim->damaged &= ~TARGET_CAPTURE;
                work->victim = 0;
                work->f924 = 0;
            }

            d18a_snake18_StartAnim(work, d18a_dword_800C37E4[work->stance]);
            work->flags &= ~4;
            return;
        }

        work->flags |= 4;
        d18a_snake18_SetAction(work, action, 4);

        work->f848 = work->control.rot;
        work->f848.vy += 0x800;

        vec = &work->f838;
        target = work->victim;
        DG_PutVector(&punch->field_0, vec, 1);
        GV_SubVec3(&target->center, vec, vec);

        vec->vx /= 4;
        vec->vy /= 4;
        vec->vz /= 4;
    }

    if (time < 4)
    {
        GV_AddVec3(&work->control.step, &work->f838, &work->control.step);
    }

    if (work->body.is_end)
    {
        work->flags &= ~4;

        if (work->victim)
        {
            work->victim->damaged &= ~TARGET_CAPTURE;
            work->victim = 0;
            work->f924 = 0;
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
    }
}
void d18a_snake18_800D3774(Snake18Work *work, int time)
{
    if (time == 0)
    {
        work->update_3p = d18a_snake18_800D3D0C;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus &= ~PLAYER_MOVE;
        d18a_snake18_SetAction(work, work->actpack->attack->punch, 1);
        work->local_data = 0;
        work->flags |= 4;
    }
}

void d18a_snake18_800D37FC(Snake18Work *work, int time)
{
    SVECTOR *rot;
    SVECTOR *vec;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        GM_PlayerStatus &= ~PLAYER_MOVE;
        work->f924 = 0;

        if (!d18a_snake18_800CB9CC(work, &d18a_dword_800C3990) || (work->victim->class & 0x20) ||
            (GM_PlayerStatus & PLAYER_INVINCIBLE))
        {
            if (work->victim)
            {
                work->victim->damaged &= ~TARGET_CAPTURE;
                work->victim = 0;
                work->f924 = 0;
            }

            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            work->flags &= ~4;
            return;
        }

        vec = &work->f838;
        rot = &work->control.rot;
        DG_SetPos2(&work->victim->center, rot);

        DG_PutVector(&d18a_dword_800C39B0, vec, 1);
        DG_SetPos2(&work->control.mov, rot);
        GV_SubVec3(vec, &work->control.mov, vec);

        vec->vx /= 4;
        vec->vy /= 4;
        vec->vz /= 4;

        d18a_snake18_SetAction(work, work->actpack->special2->field_0[0], 4);
        work->flags |= 4;
    }

    if (time < 4)
    {
        GV_AddVec3(&work->control.step, &work->f838, &work->control.step);
    }
    else
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3A1C);
    }
}

void d18a_snake18_800D3A1C(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800D3ED0;
        work->update_1p = d18a_snake18_800CE7BC;
        action = work->actpack->special2->field_0[0];
        d18a_snake18_SetAction(work, action, 4);
        work->victim->a_mode = action;
    }
}
void d18a_snake18_800D3A9C(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800D3FE8;
        work->update_1p = d18a_snake18_800CE7BC;
        action = work->actpack->attack->field_6;
        d18a_snake18_SetAction(work, action, 4);
        work->victim->a_mode = action;
    }
}

void d18a_snake18_800D3B1C(Snake18Work *work, int time)
{
    int     action;
    TARGET *target;

    if (time == 0)
    {
        action = work->actpack->attack->field_7;
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        target = work->victim;
        d18a_snake18_SetAction(work, action, 4);
        target->a_mode = action;
        target->damage = 5;
        target->faint--;
        work->f924 = 0;
    }

    if (work->body.is_end)
    {
        if (work->victim)
        {
            work->victim->damaged &= ~TARGET_CAPTURE;
            work->victim = 0;
            work->f924 = 0;
        }

        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        work->flags &= ~4;
    }
}

void d18a_snake18_800D3C14(Snake18Work *work, int time)
{
    int action;

    if (time == 0)
    {
        work->update_3p = d18a_snake18_800CE7BC;
        work->update_1p = d18a_snake18_800CE7BC;
        action = work->actpack->special2->field_0[1];
        GM_PlayerStatus |= PLAYER_MOVE;
        d18a_snake18_SetAction(work, action, 4);
        work->victim->a_mode = action;
    }

    if (d18a_dword_800DAEF0 < 0 || !(work->pad->status & PAD_SQUARE) || work->victim->vital <= 0)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3A1C);
        return;
    }

    work->control.turn.vy = d18a_dword_800DAEF0 + 0x800;
}
void d18a_snake18_800D3D0C(Snake18Work *work, int time)
{
    int yaw;
    int pitch;

    GM_GetHomingTarget2(&work->body.objs->objs[6].world, work->control.rot.vy, &yaw, &pitch,
                        work->control.map->index, 2000, 512);

    if (yaw >= 0)
    {
        work->control.turn.vy = yaw;
    }

    if (time == 4)
    {
        GM_SeSet(&work->control.mov, d18a_snake18_800CB908(work, &d18a_dword_800C39B8[0]) ? 0x34 : 0x38);
    }

    if (time == 8)
    {
        if (!(work->local_data & PAD_CIRCLE))
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            GM_PlayerStatus &= ~PLAYER_ATTACK;
            work->flags &= ~4;
            return;
        }

        work->local_data &= ~PAD_CIRCLE;
    }

    if (time == 11)
    {
        GM_SeSet(&work->control.mov, d18a_snake18_800CB908(work, &d18a_dword_800C39B8[1]) ? 0x34 : 0x38);
    }

    if (time == 13)
    {
        if (!(work->local_data & PAD_CIRCLE))
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
            GM_PlayerStatus &= ~PLAYER_ATTACK;
            work->flags &= ~4;
            return;
        }

        work->local_data = 0;
    }

    if (time == 22)
    {
        GM_SeSet(&work->control.mov, d18a_snake18_800CB908(work, &d18a_dword_800C39B8[2]) ? 0x35 : 0x39);
    }

    if (work->body.is_end)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        GM_PlayerStatus &= ~PLAYER_ATTACK;
        work->flags &= ~4;
        return;
    }

    work->local_data |= work->pad->press;
    GM_PlayerStatus |= PLAYER_ATTACK;
}

static inline void d18a_snake18_ReleaseCapture(Snake18Work *work)
{
    if (work->victim)
    {
        work->victim->damaged &= ~TARGET_CAPTURE;
        work->victim = 0;
        work->f924 = 0;
    }

    d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
    work->flags &= ~4;
}

void d18a_snake18_800D3ED0(Snake18Work *work, int time)
{
    unsigned short press;
    unsigned short status;

    if (work->victim->vital <= 0)
    {
        d18a_snake18_ReleaseCapture(work);
        return;
    }

    if (!(work->victim->class & TARGET_CAPTURE))
    {
        d18a_snake18_ReleaseCapture(work);
        return;
    }

    press = work->pad->press;
    status = work->pad->status;

    if (press & PAD_SQUARE)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3A9C);
        work->flags &= ~4;
        return;
    }

    if (!(status & PAD_SQUARE))
    {
        if (++work->local_data >= 9)
        {
            d18a_snake18_ReleaseCapture(work);
        }
        return;
    }

    work->local_data = 0;

    if (d18a_dword_800DAEF0 >= 0)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3C14);
    }
}
void d18a_snake18_800D3FE8(Snake18Work *work, int time)
{
    if (time == 0 || (work->pad->press & PAD_SQUARE))
    {
        work->victim->faint--;

        if (++work->f924 >= 11)
        {
            d18a_snake18_StartAnim(work, d18a_snake18_800D3B1C);
            return;
        }
    }

    if (work->body.is_end)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800D3A1C);
    }
}
void d18a_snake18_800D4084(Snake18Work *work)
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
void d18a_snake18_800D40F0(Snake18Work *work)
{
    int height;
    int frame;

    height = work->body.height;
    work->control.height = height;

    if (height < 500)
    {
        height = 500;
    }

    work->target->size.vy = height;

    if (work->f904.vy < 0 && work->control.grounded)
    {
        work->f904.vy = 0;
    }

    work->f904.vy -= 32;

    if (GM_PlayerStatus & PLAYER_NOT_PLAYABLE)
    {
        return;
    }

    if (GM_PlayerStatus & PLAYER_PAD_OFF)
    {
        work->pad = &d18a_dword_800C3A18;
    }

    work->trigger = 0;
    d18a_snake18_800CB030(work);
    work->control.turn.vz = 0;
    d18a_snake18_800CACD0(work);
    d18a_snake18_800CC6CC(work);
    d18a_snake18_800CBEC0(work);
    d18a_snake18_800CBF98(work);
    d18a_snake18_800CC008(work);
    d18a_snake18_800CC010(work);
    d18a_snake18_800CCB50(work);
    d18a_snake18_800CB888(work);
    d18a_snake18_800CD040(work);
    d18a_snake18_800CD4C0(work);
    d18a_snake18_800CBE58(work);
    d18a_snake18_800CB470(work);
    d18a_snake18_800CC7F4(work);

    if (GV_PadData[1].status & PAD_CIRCLE)
    {
        MENU_Locate(32, 16, 0);
        MENU_Printf("pos %d %d %d\n", work->control.mov.vx, work->control.mov.vy, work->control.mov.vz);
        MENU_Printf("ceil floor %d %d\n", work->control.levels[1], work->control.levels[0]);
        MENU_Printf("status %4x\n", GM_PlayerStatus);
        MENU_Printf("weapon %d\n", work->weapon);
        MENU_Printf("item %d\n", work->item);
        MENU_Printf("flag %4x\n", work->flags);
        MENU_Printf("stance %d\n", work->stance);

        if (GM_StatusEvent & EV_CommonCold)
        {
            MENU_Printf("kaze \n");
        }
    }

    frame = work->anim_time++;
    work->anim(work, frame);

    ((GM_PlayerStatus & PLAYER_WATCH) ? work->update_1p : work->update_3p)(work, frame);

    d18a_snake18_800D1A08(work);
    d18a_snake18_800CEE60(work);

    work->control.r_sphere = GV_NearExp4(work->control.r_sphere, work->r_sphere);
    work->control.step.vy = work->f904.vy;

    GM_PlayerAction = work->body.action;
    dword_800AB9D4 = work->m_ctrl.info1.frame;

    d18a_snake18_800D4084(work);
    d18a_snake18_800CBB34(work);

    if (work->target->vital <= 0)
    {
        work->control.seg_flag = 4;
    }
}
static inline void d18a_snake18_UpdateLife(Snake18Work *work)
{
    TARGET *target;
    int     vitality;

    target = work->target;
    vitality = target->vital;
    vitality += GM_Vitality - work->last_vital;
    if (vitality > GM_VitalityMax)
    {
        vitality = GM_VitalityMax;
    }

    target->vital = vitality;
    work->last_vital = vitality;
    GM_Vitality = vitality;
    if (GM_Vitality < 0)
    {
        GM_Vitality = 0;
    }
}

void d18a_snake18_800D4388(Snake18Work *work)
{
    SVECTOR pos;
    TARGET *target;
    long   *t;
    TARGET *target2;

    if ((work->pad->status & PAD_CROSS) && (work->pad->press & PAD_CIRCLE))
    {
        if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
        {
            printf("first\n");
            GM_PlayerStatus &= ~PLAYER_SECOND_CONTROLLER;
        }
        else
        {
            printf("second\n");
            GM_PlayerStatus |= PLAYER_SECOND_CONTROLLER;
        }
    }

    work->pad = &GV_PadData[0];
    d18a_snake18_800CABEC(work);

    target = work->target;
    if (target->damaged & TARGET_PUSH)
    {
        GV_AddVec3(&target->offset, &work->control.step, &work->control.step);
        target->damaged &= ~TARGET_PUSH;
        target->offset = DG_ZeroVector;
    }

    work->control.hzd_height = d18a_dword_800C37F8[work->stance] + work->control.levels[0];

    GM_ActMotion(&work->body);
    GM_ActControl(&work->control);

    if (GM_PlayerStatus & PLAYER_ACT_ONLY)
    {
        work->control.mov.vy = work->body.height + work->control.levels[0];
        DG_SetPos2(&work->control.mov, &work->control.rot);
    }

    GM_ActObject(&work->body);
    DG_GetLightMatrix2(&work->control.mov, work->light);
    GM_MoveTarget(work->target, &work->control.mov);

    if (work->flags & 0x800)
    {
        GM_SnakeCamera.position = work->control.mov;
    }
    else
    {
        t = work->body.objs->objs[6].world.t;
        GM_SnakeCamera.position.vx = t[0];
        GM_SnakeCamera.position.vy = t[1];
        GM_SnakeCamera.position.vz = t[2];
    }

    GM_SnakeCamera.rotate2 = work->control.rot;
    GM_SnakeCamera.rotate2.vy &= 0xFFF;

    GM_PlayerPosition = work->control.mov;

    pos = work->control.mov;
    pos.vy = work->control.levels[0];
    GM_PlayerAddress = work->hzd_address = HZD_GetAddress(work->control.map->hzd, &pos, work->hzd_address);

    d18a_snake18_UpdateLife(work);

    d18a_snake18_800D40F0(work);

    target2 = work->target;
    target2->force = work->control.step;
    GM_PushTarget(target2);
}
void d18a_snake18_800D46CC(Snake18Work *work)
{
    GV_DestroyOtherActor(work->shadow);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);

    GM_FreePrim(work->lsight_prim);

    GM_PlayerStance = work->stance;

    if (GM_PlayerControl == &work->control)
    {
        GM_PlayerControl = 0;
    }

    if (GM_PlayerBody == &work->body)
    {
        GM_PlayerBody = 0;
    }
}
int d18a_snake18_800D4784(Snake18Work *work)
{
    SVECTOR  *verts;
    SVECTOR  *verts2;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_GT4 *poly;
    int       i, j;

    verts = work->lsight_verts;
    prim = GM_MakePrim(DG_PRIM_LINE_GT2, 2, verts, NULL);
    if (!prim)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("lsight"));
    work->lsight_tex = tex;
    if (!tex)
    {
        return -1;
    }

    prim->raise = 500;

    for (i = 0; i < 2; i++)
    {
        poly = prim->packs[i];

        for (j = 0; j < 2; j++)
        {
            LSTORE(COLOR_BLACK, &poly->r0);
            LSTORE(COLOR_GRAY, &poly->r1);
            LSTORE(COLOR_BLACK, &poly->r2);
            LSTORE(COLOR_GRAY, &poly->r3);
            setPolyGT4(poly);
            setSemiTrans(poly, 1);
            poly->tpage = tex->tpage;
            poly->clut = tex->clut;
            poly++;
        }
    }

    verts2 = verts + 2;

    verts[2].vx = -100;
    verts[0].vx = -100;
    verts[3].vy = -300;
    verts2[0].vy = -300;
    verts[1].vy = -300;
    verts[0].vy = -300;
    verts2[0].vz = 300;
    verts[0].vz = 300;
    verts[1].vx = -800;
    verts[1].vz = 2000;
    verts[3].vx = 800;
    verts[3].vz = 2000;

    DG_InvisiblePrim(prim);
    work->lsight_prim = prim;
    return 0;
}

void d18a_snake18_800D48FC(Snake18Work *work)
{
    short stance;

    stance = work->stance = GM_PlayerStance;

    if (work->item == IT_Box1 || work->item == IT_Box2 || work->item == IT_Box3)
    {
        d18a_snake18_StartAnim(work, d18a_snake18_800CFF5C);
        return;
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        d18a_snake18_800CB3E8(work);
        d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
        return;
    }

    switch (stance)
    {
    case 1:
        d18a_snake18_StartAnim(work, d18a_snake18_800CD768);
        break;

    case 2:
        d18a_snake18_StartAnim(work, d18a_snake18_800CD808);
        break;

    case 3:
        work->stance = 2;
        GM_PlayerStatus |= PLAYER_INTRUDE | PLAYER_GROUND;
        d18a_snake18_800CB3E8(work);
        d18a_snake18_StartAnim(work, d18a_snake18_800CEEAC);
        break;

    default:
        d18a_snake18_StartAnim(work, d18a_snake18_800CD64C);
        break;
    }
}

int d18a_snake18_800D49FC(Snake18Work *work)
{
    char *opt;

    work->hzd_address = -1;
    work->flags = 0;
    work->weapon_actor = NULL;
    work->weapon_state = NULL;
    work->trigger = 0;
    work->weapon = -1;
    work->weapon_flags = 0;
    GM_WeaponChanged = 1;
    d18a_snake18_800CD040(work);

    work->item_actor = NULL;
    work->item = -1;
    work->item_flags = 0;
    d18a_snake18_800CD4C0(work);

    if (d18a_snake18_800D4784(work) < 0)
    {
        return -1;
    }

    work->actpack = &snake18_weapon_actions[GM_Weapon];
    work->anim_time = 0;
    work->f8B8 = 0;
    work->f8B4 = NULL;
    work->update_3p = NULL;
    work->update_1p = NULL;
    work->f8F8 = 0;
    work->invuln = 0;
    work->f8FD = 0;
    work->r_sphere = 450;
    work->local_data2 = 0;
    work->local_data = 0;
    work->f924 = 0;
    work->f914 = DG_ZeroVector;
    work->f91C = work->control.mov;
    work->f934 = 0;
    work->f92C = 0;
    work->f92E = 0;
    work->vib1 = 0;
    work->vib2 = 0;
    work->f90E = 0;

    opt = GCL_GetOption('o');
    if (opt)
    {
        work->f92A = GCL_StrToInt(opt);
    }
    else
    {
        work->f92A = 0;
    }

    d18a_snake18_800D48FC(work);
    GM_ConfigObjectAction(&work->body, d18a_snake18_800CB280(work, work->stance), 0, 0);
    return 0;
}


int d18a_snake18_800D4B84( Snake18Work *work )
{
    d18a_snake18_800CB2EC( work );
    return 0;
}

int d18a_snake18_800D4BA4(Snake18Work *work)
{
    TARGET *target = GM_AllocTarget();
    work->target = target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x9F, work->side, &d18a_dword_800C3A28);
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
        work->side = HZD_SEG_NO_COLLIDE;
        work->pad = &GV_PadData[ 0 ];
    }
    else
    {
        work->side = HZD_SEG_NO_NAVIGATE;
        work->pad = &GV_PadData[ 1 ];
    }

    ctrl = &work->control;
    if ( GM_InitControl( ctrl, name, where ) < 0 )
    {
        return -1;
    }

    seg_flag = HZD_SEG_NO_COLLIDE;

    GM_ConfigControlString( ctrl, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlHazard( ctrl, d18a_dword_800C37F8[0], 450, 450 );
    ctrl->seg_flag = seg_flag;
    GM_ConfigControlAttribute( ctrl, RADAR_VISIBLE );
    GM_ConfigControlTrapCheck( ctrl );

    body = &work->body;
    if ( work->side == seg_flag )
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


void *d18a_snake18_800D4E94(int name, int where)
{
    Snake18Work *work = GV_NewActor(GV_ACTOR_PREV, sizeof(Snake18Work));
    if (work == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(&work->actor, d18a_snake18_800D4388, d18a_snake18_800D46CC,
                     "snake18.c");
    if (d18a_snake18_800D4C44(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }
    return work;
}
