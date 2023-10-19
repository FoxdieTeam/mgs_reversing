// FIXME: copy-pasta of snake/sna_init.c

#include "sna_init.h"
#include "chara/snake/afterse.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Kojo/demothrd.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "unknown.h"
#include "Okajima/blood.h"
#include "Bullet/bakudan.h"
#include "Bullet/jirai.h"
#include "Game/homing_target.h"
#include "Game/vibrate.h"
#include "psyq.h"
#include "Game/camera.h"
#include "Weapon/grenade.h"
#include "Anime/animeconv/anime.h"
#include "libgcl/hash.h"
#include "Equip/bodyarm.h"
#include "Equip/box.h"
#include "Equip/bandana.h"
#include "Equip/gasmask.h"
#include "Equip/jpegcam.h"
#include "Equip/kogaku2.h"
#include "Equip/scope.h"
#include "Equip/tabako.h"
#include "Okajima/d_blood.h"
#include "Takabe/goggle.h"
#include "Takabe/goggleir.h"
#include "Weapon/aam.h"

extern Sna_E1 e1_800AB7C4;
Sna_E1        SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int        SECTION(".sbss") dword_800ABBA8;

extern int gSnaMoveDir_800ABBA4;
int        SECTION(".sbss") gSnaMoveDir_800ABBA4;

extern char *dword_800ABBB4;
char *       SECTION(".sbss") dword_800ABBB4;

extern CONTROL *GM_PlayerControl_800AB9F4;
extern OBJECT     *GM_PlayerBody_800ABA20;

extern SVECTOR *svector_800ABBB8;
SVECTOR *SECTION(".sbss") svector_800ABBB8;

extern int           dword_800ABBBC;
int SECTION(".sbss") dword_800ABBBC;

extern int           dword_800ABBC0;
int SECTION(".sbss") dword_800ABBC0;

extern Actor_SnaInit *sna_800ABBA0;
Actor_SnaInit *SECTION(".sbss") sna_800ABBA0;

extern int dword_800ABBC4;
int        SECTION(".sbss") dword_800ABBC4;

extern SVECTOR *pVec_800ABBC8;
SVECTOR        *SECTION(".sbss") pVec_800ABBC8;

extern SVECTOR *pVec_800ABBCC;
SVECTOR        *SECTION(".sbss") pVec_800ABBCC;

extern int dword_800ABBD0;
int        SECTION(".sbss") dword_800ABBD0;

extern short dword_800ABBDC;
short        SECTION(".sbss") dword_800ABBDC;

extern short dword_800ABBD4;
short        SECTION(".sbss") dword_800ABBD4;

extern SVECTOR *dword_800ABBB0;
SVECTOR *       SECTION(".sbss") dword_800ABBB0;

extern TARGET *GM_BombSeg_800ABBD8; // probably wrong type?
TARGET *SECTION(".sbss") GM_BombSeg_800ABBD8;

extern Actor_SnaInit *sna_800ABBA0;
Actor_SnaInit *SECTION(".sbss") sna_800ABBA0;

extern SVECTOR *dword_800ABBAC;
SVECTOR *SECTION(".sbss") dword_800ABBAC;

extern short              GM_WeaponChanged_800AB9D8;
extern int                GM_AlertMode_800ABA00;
extern int                GM_GameOverTimer_800AB3D4;
extern int                GM_GameStatus_800AB3CC;
extern SVECTOR            DG_ZeroVector_800AB39C;
extern PlayerStatusFlag   GM_PlayerStatus_800ABA50;
extern SVECTOR            svector_800AB7FC;
extern GM_Camera          GM_Camera_800B77E8;
extern SVECTOR            svector_800AB7D4;
extern SVECTOR            svector_800AB7DC;
extern unsigned short     GM_WeaponTypes_8009D580[];
extern unsigned short     GM_ItemTypes_8009D598[];
extern void              *dword_8009EEA4[];
extern int                GV_Time_800AB330;
extern int                bakudan_count_8009F42C;
extern SVECTOR            svector_800AB7EC;
extern SVECTOR            svector_800AB7F4;
extern int                gSnaMoveDir_800ABBA4;
extern int                DG_UnDrawFrameCount_800AB380;
extern SVECTOR            svector_800AB7CC;
extern int                counter_8009F448;
extern const char         aSnakeEUC[];
extern int                dword_800ABA1C;
extern int                tabako_dword_8009F2C0;
extern int                dword_800AB9F0;
extern SVECTOR            GM_PlayerPosition_800ABA10;
extern UnkCameraStruct    gUnkCameraStruct_800B77B8;
extern GV_PAD             GV_PadData_800B05C0[4];
extern CONTROL        *tenage_ctrls_800BDD30[16];
extern Jirai_unknown      stru_800BDD78[16];
extern Jirai_unknown      stru_800BDE78[8];
extern unsigned char      gBulNames_800BDC78[64];
unsigned char             gBulNames_800BDC78[64];
extern int                dword_8009F440;
extern int                dword_8009F444;
extern int                dword_8009F46C[];
extern int                dword_8009F470;
extern int                dword_8009F474;
extern TARGET *target_800BDF00;
extern int                dword_800BDD28;
extern int                tenage_ctrls_count_800BDD70;
extern int                dword_8009F434;
extern short              d_800AB9EC_mag_size;
extern short              d_800ABA2C_ammo;
extern SVECTOR            svector_800AB7E4;
extern void              *dword_8009EEB0[];
extern void              *dword_8009EEB8[];
extern int                dword_800AB9D4;
extern short              HzdHeights_8009EEC4[];
extern int                DG_CurrentGroupID_800AB968;
extern int                GV_Clock_800AB920;
extern char               dword_8009EF1C[];
extern char               dword_8009EF20[];
extern TSnakeEquipFuncion gSnakeEquips_8009EF8C[];
extern TSnakeActFunction  GM_lpfnPlayerActControl_800AB3DC;
extern TSnakeActFunction  GM_lpfnPlayerActObject2_800AB3E0;
extern char               dword_8009EEE0[];
extern char               dword_8009EEE4[];
extern char               dword_8009EEF0[];
extern char               dword_8009EEF4[];
extern char               dword_8009EED4[];
extern char               dword_8009EED8[];
extern short              snake_weapon_idx_800BDCBA;
extern short              snake_mag_size_800BDCB8;
extern short              snake_weapon_max_ammo_800BDCBC;
extern int                GM_PlayerAction_800ABA40;

extern Actor_SnaInit     *snainit_actor_800A9424;
Actor_SnaInit            *snainit_actor_800A9424;

extern const char aRunMoveCancel[];  // = "run move cancel\n"
extern const char aForceStanceCan[]; // = "force stance cancel\n"
extern const char aForceActCancel[]; // = "force act cancel\n"
extern const char aSnaInitC[];       // = "sna_init.c"

Sna_E2 e2_8009EC64 = {12u, 82u, 19u, 23u, 24u, 29u, 30u, 12u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009EC70 = {10u, 8u, 17u, 23u, 24u, 27u, 28u, 80u, 106u, 107u, 0u, 0u};
Sna_E2 e2_8009EC7C = {11u, 9u, 18u, 23u, 24u, 27u, 28u, 73u, 110u, 111u, 0u, 0u};
Sna_E2 e2_8009EC88 = {75u, 77u, 79u, 23u, 24u, 27u, 28u, 75u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009EC94 = {92u, 91u, 93u, 23u, 24u, 29u, 30u, 92u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ECA0 = {97u, 96u, 98u, 101u, 24u, 29u, 30u, 97u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ECAC = {104u, 103u, 19u, 23u, 24u, 29u, 30u, 104u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ECB8 = {63u, 65u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 e2_8009ECC4 = {61u, 64u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 e2_8009ECD0 = {62u, 83u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 e2_8009ECDC = {136u, 136u, 35u, 136u, 36u, 37u, 38u, 39u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ECE8 = {42u, 51u, 35u, 45u, 47u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ECF4 = {5u, 52u, 34u, 46u, 48u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ED00 = {74u, 136u, 136u, 136u, 105u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

Sna_E2 e2_8009ED0C = {74u, 136u, 34u, 46u, 81u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ED18 = {43u, 136u, 35u, 136u, 53u, 55u, 49u, 54u, 56u, 0u, 0u, 0u};
Sna_E2 e2_8009ED24 = {57u, 136u, 35u, 136u, 58u, 59u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ED30 = {60u, 136u, 35u, 136u, 50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 e2_8009ED3C = {44u, 136u, 136u, 136u, 136u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

Sna_E6 e6_8009ED48[] = {
    {115u, 133u, 0u, 0u},
    {112u, 133u, 0u, 0u},
    {113u, 133u, 0u, 0u},
    {136u, 136u, 0u, 0u},
    {114u, 132u, 0u, 0u},
    {116u, 133u, 0u, 0u},
    {117u, 133u, 0u, 0u},
    {118u, 133u, 0u, 0u}
};

// TODO: Why is this in .data despite fitting into .sdata?
Sna_E1 SECTION(".data") e7_8009ED68 = {7u, 13u, 4u, 14u, 32u, 119u, 124u, 0u};

extern Sna_E1 e1_800AB78C;
extern Sna_E1 e1_800AB7C4;
extern Sna_E1 e1_800AB794;
extern Sna_E1 e1_800AB79C;
extern Sna_E1 e1_800AB7BC;
extern Sna_E1 e1_800AB7AC;
extern Sna_E1 e1_800AB7A4;
extern Sna_E1 e1_800AB7B4;

Sna_ActionTable actions_no_weapon_8009ED70 = {
    &e1_800AB78C, &e2_8009EC64, &e1_800AB7C4, &e2_8009ECB8,
    &e2_8009ECDC, &e6_8009ED48[0], &e7_8009ED68
};

Sna_ActionTable weapon_actions_8009ED8C[10] = {
    {&e1_800AB794, &e2_8009EC70, &e1_800AB7C4, &e2_8009ECC4, &e2_8009ECE8, &e6_8009ED48[1], &e7_8009ED68},
    {&e1_800AB79C, &e2_8009EC7C, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ECF4, &e6_8009ED48[2], &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED48[7], &e7_8009ED68},
    {&e1_800AB7B4, &e2_8009EC88, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ED0C, &e6_8009ED48[4], &e7_8009ED68},
    {&e1_800AB79C, &e2_8009EC7C, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ED00, &e6_8009ED48[3], &e7_8009ED68},
    {&e1_800AB7BC, &e2_8009ECA0, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED24, &e6_8009ED48[6], &e7_8009ED68},
    {&e1_800AB7AC, &e2_8009EC94, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED18, &e6_8009ED48[5], &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED48[7], &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED48[7], &e7_8009ED68},
    {&e1_800AB78C, NULL, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED3C, &e6_8009ED48[3], &e7_8009ED68}};

void *dword_8009EEA4[] = {
    sna_anim_idle_8005275C,
    sna_anim_crouch_800527DC,
    sna_anim_prone_idle_800528BC
};

void *SECTION(".data") dword_8009EEB0[] = {
    sna_anim_wall_idle_and_c4_80052A5C,
    sna_anim_wall_crouch_80052CCC
};

void *dword_8009EEB8[] = {
    sna_anim_run_8005292C,
    sna_anim_run_8005292C,
    sna_anim_prone_move_800529C0
};

short SECTION(".data") HzdHeights_8009EEC4[] = {750, 250, 250, 0};

short SECTION(".data") dword_8009EECC[] = {1100, 496, 136, 0};

char SECTION(".data") dword_8009EED4[] = {127, 4, 0, 0};
char SECTION(".data") dword_8009EED8[] = {225, 1, 255, 2, 0, 0, 0, 0};
char SECTION(".data") dword_8009EEE0[] = {127, 6, 0, 0};
char SECTION(".data") dword_8009EEE4[] = {225, 1, 255, 4, 225, 2, 75, 8, 0, 0, 0, 0};
char SECTION(".data") dword_8009EEF0[] = {127, 1, 0, 0};
char SECTION(".data") dword_8009EEF4[] = {155, 3, 0, 0};
char SECTION(".data") dword_8009EEF8[] = {0, 2, 127, 2, 0, 0, 0, 0};
char SECTION(".data") dword_8009EF00[] = {140, 4, 80, 6, 0, 0, 0, 0};
char SECTION(".data") dword_8009EF08[] = {0, 10, 127, 2, 0, 0, 0, 0};
char SECTION(".data") dword_8009EF10[] = {80, 2, 50, 8, 140, 4, 80, 6, 0, 0, 0, 0};
char SECTION(".data") dword_8009EF1C[] = {196, 4, 0, 0};
char SECTION(".data") dword_8009EF20[] = {148, 4, 0, 0};
char SECTION(".data") dword_8009EF24[] = {0, 2, 127, 2, 0, 0, 0, 0};
char SECTION(".data") dword_8009EF2C[] = {60, 2, 200, 4, 40, 2, 0, 0};

typedef struct WeaponCreateEntry
{
    void *mCreateActorFn;
    void *mStateFn;
} WeaponCreateEntry;

WeaponCreateEntry gSnakeWeapons_8009EF3C[] = {
    {NULL, sna_anim_chokethrow_begin1_80054210},
    {NewSOCOM_80065D74, sna_gun_800540D0},
    {famas_create_80066374, sna_gun_800540D0},
    {grenade_create_80066A4C, sna_anim_grenade_80058470},
    {NewRCM_80066FF0, sna_gun_800540D0},
    {NewAAM_80067480, sna_anim_stinger_800570C0},
    {mine_init_800677BC, sna_anim_claymore_80057474},
    {NewBomb_80067B20, sna_bomb_800541A8},
    {NewStanGrenade_80066A74, sna_anim_grenade_80058470},
    {NewChaffGrenade_80066AA0, sna_anim_grenade_80058470},
    {NewRifle_80068214, sna_anim_psg1_80056DDC}};

TSnakeEquipFuncion gSnakeEquips_8009EF8C[] = {
    NewTabako_80062274,
    NewScope_80063508,
    NewBox_80061C7C,
    NewBox_80061C7C,
    NewBox_80061C7C,
    NewGoggle_8007781C,
    NewGoggleIr_80078E6C,
    NewGasmask_80060C14,
    NewBodyarm_80060940,
    NewKetchap_80072B60,
    NewKogaku2_800615FC,
    NewBandana_80061E40
#ifndef VR_EXE
    , NewJpegcam_80065118
#else
    , NULL
#endif
};

short word_8009EFC0[] = {0, 500, 0, 320, 400, 320, 400, 32, 32, 0};

SVECTOR stru_8009EFD4[2] = {{-100, 200, 200, 0}, {-150, 18, 200, 0}};

Target_Data stru_8009EFE4[4] =
{
    {{0, 0, 300, 0}, {400, 600, 400, 0}, 0, 0, 64, 0}, // TODO: Might not be part of this array, might be its own element
    {{-400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{0, 0, 0, 0}, {501, 600, 501, 0}, 0, 0, 7, 0}
};

MATRIX stru_8009F064 = {{{-200, 200, 600}, {0, 400, 200}, {400, 0, 5}}, {50, 0, 1}};
MATRIX stru_8009F084 = {{{200, 200, 600}, {0, 400, 200}, {400, 0, -5}}, {50, 0, 1}};
MATRIX stru_8009F0A4 = {{{0, 200, 600}, {0, 500, 250}, {500, 0, 0}}, {100, 0, 3}};

GV_PAD GV_PadData_8009F0C4 = {0, 0, 0, 0, -1, 0, 0, 0, 0, 0};

#define RIFLE_TEBURE_TIME   90 // delay before camera shake
#define TEBURE              122
#define GetAction( pActor ) (pActor->field_9C_obj.action_flag)
#define EndMotion( pActor ) (pActor->field_9C_obj.is_end != 0)
#define SET                 pActor->field_9B4_action_table->field_10->field_0
#define DispEmpty( pActor ) (pActor->field_9A0 = 4)
#define SE_KARASHT          4

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004EB94.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004EC18.s")

void sna_8004EC8C(Actor_SnaInit *pActor) // different in VR
{
    ushort v2; // $v1

    sna_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK12);
    pActor->field_A28 = 460;
    GM_Camera_800B77E8.field_22 = 1;
    v2 = *(ushort *)&e1_800AB7C4.field_4;
    pActor->field_A20 = -6;
    pActor->field_9D0[2] = 320;
    pActor->field_9D0[4] = v2;
    pActor->field_9D0[6] = v2;
    sd_set_cli_800887EC(0x1FFFF20, 0);
    // sna_set_flags2_8004E330(pActor, SNA_FLAG2_UNK5);
    // GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_FIRST_PERSON);
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004ECF4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004ED4C.s")

void sna_8004EE28(Actor_SnaInit *snake)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR vec;
    int     vx;
    MATRIX *world = &snake->field_9C_obj.objs->objs[6].world;

    ReadRotMatrix(&mat1);
    DG_TransposeMatrix_8001EAD8(&mat1, &mat2);
    MulMatrix0(&mat2, world, &mat2);
    DG_MatrixRotZYX_8001E92C(&mat2, &vec);
    SetRotMatrix(&mat1);
    vx = vec.vx;
    if (vx < 0)
    {
        vx += 0xf;
    }
    vx &= 0xfff0;
    gUnkCameraStruct_800B77B8.field_28.vx = vx;
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004EE90.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004EEF4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004EFC4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F014.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F070.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F124.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F1D0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F260.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F2AC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F2F8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F400.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F4E4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F5C8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F688.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004F8D8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FA30.s")

int GM_Next_BulName_8004FBA0()
{
    int i;                   // $a0
    for (i = 1; i < 64; i++) // for some reason skip the first one ??
    {
        if (!gBulNames_800BDC78[i])
        {
            gBulNames_800BDC78[i] = 1;
            return i;
        }
    }
    return 0;
}

void GM_ClearBulName_8004FBE4(int idx)
{
    gBulNames_800BDC78[idx] = 0;
}

void GM_CheckShukanReverse_8004FBF8(unsigned short *pInput)
{
    unsigned short old;
    unsigned int   v2; // $v1
    unsigned int   v3; // $v0

    if ((GM_GameStatusFlag & 0x1000) != 0)
    {
        old = *pInput;

        *pInput = old & ~0x5000;

        v2 = old & 0x5000;
        v3 = v2 & 0x1000;

        if (v3)
        {
            *pInput |= 0x4000;
        }

        if (v2 & 0x4000)
        {
            *pInput |= 0x1000;
        }
    }
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FB98.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FBC8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FCF8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FE98.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8004FFAC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80050108.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005018C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800502A8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80050350.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005046C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005056C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800506DC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80050954.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80050968.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80051078.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_weapon_switching_800511BC.s")
void sna_weapon_switching_800511BC(Actor_SnaInit *pActor, int callback);

#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_800515BC.s")
void sna_800515BC(Actor_SnaInit *pActor, int a2);

#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_idle_8005275C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_crouch_800527DC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_prone_idle_800528BC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_run_8005292C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_prone_move_800529C0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_wall_idle_and_c4_80052A5C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_wall_crouch_80052CCC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80051F60.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800520D4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052240.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052350.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052560.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052714.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005280C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052994.s")

void sna_fn_nothing_80053B80(Actor_SnaInit *param_1, int time)
{
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052AC8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052B28.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052CB4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052DDC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80052EE8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_gun_800540D0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_bomb_800541A8.s")

// or sna_no_weapon_80054210 ?
void sna_anim_chokethrow_begin1_80054210(Actor_SnaInit *pActor, int time)
{
    void *pFn;
    pActor->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
    pActor->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        pFn = sna_anim_throw_800589C8;
    }
    else
    {
        pFn = sna_anim_chokethrow_begin2_80058C80;
    }
    sna_start_anim_8004E1F4(pActor, pFn);
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053198.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053254.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800532C0.s")

void sna_anim_duct_move_80054424(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sub_8005688C;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
        SetAction_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78_levels[0] + 150;
}

#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053394.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800533EC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053554.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005361C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053800.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800538E0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053A20.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053AD8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053C38.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80053E44.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800541E4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005427C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005429C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800542FC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80054364.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800543D4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80054888.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80054C88.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80055500.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800556FC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sub_8005688C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800557D8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sub_80052468.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_psg1_80056DDC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_stinger_800570C0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_claymore_80057474.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80056FE8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057198.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057204.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057318.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800573E8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057548.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005792C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057CD0.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_grenade_80058470.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80057F9C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800580D8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_throw_800589C8.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058538.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_anim_chokethrow_begin2_80058C80.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800587AC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058818.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_800588AC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_8005895C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058A5C.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058AC4.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058AFC.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058E24.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80058F24.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/snake_vr_sna_init_80059004.s")
#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_act_8005AD10.s")
void sna_act_8005AD10(Actor_SnaInit *pActor);

#pragma INCLUDE_ASM("asm/chara/snake_vr/sna_kill_8005B52C.s")
void sna_kill_8005B52C(Actor_SnaInit *pActor);

static inline int sna_LoadSnake2(Actor_SnaInit *pActor)
{
    SVECTOR  *temp_s1;
    SVECTOR  *temp_s2;
    DG_PRIM  *pPrim;
    DG_TEX   *pTex;
    POLY_GT4 *pPoly;
    int      i, j;

    temp_s1 = &pActor->field_930;
    pPrim = DG_GetPrim(22, 2, 0, temp_s1, 0);

    if (!pPrim)
    {
        return -1;
    }

    pTex = DG_GetTexture_8001D830(PCX_LSIGHT);
    pActor->field_928 = pTex;

    if (!pTex)
    {
        return -1;
    }

    pPrim->field_2E_k500 = 500;

    for (i = 0; i < 2; i++)
    {
        pPoly = &pPrim->field_40_pBuffers[i]->poly_gt4;

        for (j = 0; j < 2; j++)
        {
            LSTORE(0, &pPoly->r0);
            LSTORE(0x808080, &pPoly->r1);
            LSTORE(0, &pPoly->r2);
            LSTORE(0x808080, &pPoly->r3);
            setPolyGT4(pPoly);
            setSemiTrans(pPoly, 1);
            pPoly->tpage = pTex->field_4_tPage;
            pPoly->clut = pTex->field_6_clut;
            pPoly++;
        }
    }

    // ???
    temp_s2 = temp_s1 + 2;

    temp_s1[2].vx = -100;
    temp_s1[0].vx = -100;
    temp_s1[3].vy = -300;
    temp_s2[0].vy = -300;
    temp_s1[1].vy = -300;
    temp_s1[0].vy = -300;
    temp_s2[0].vz = 300;
    temp_s1[0].vz = 300;
    temp_s1[1].vx = -800;
    temp_s1[1].vz = 2000;
    temp_s1[3].vx = 800;
    temp_s1[3].vz = 2000;

    DG_InvisiblePrim(pPrim);
    pActor->field_92C = pPrim;
    return 0;
}

static inline void sna_LoadSnake3(Actor_SnaInit *pActor)
{
    u_short t1, t2;
    short   stance;
    short   temp_a1;
    int     temp_v1_3;
    int     var_s0_2;
    int     var_v_2;

    stance = pActor->field_A26_stance = GM_SnakeStance;
    if (stance == 3)
    {
        t1 = GM_ItemTypes_8009D598[GM_CurrentItemId + 1];
        t2 = GM_CurrentItemId;

        if ((t1 & 2) || ((t2 - 2) < 3u))
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        if (GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200)
        {
            GM_CurrentWeaponId = WEAPON_NONE;
        }
    }

    pActor->field_844 = -1;
    pActor->field_91C_weapon_idx = -2;

    sna_weapon_switching_800511BC(pActor, 0);

    pActor->field_9A8_current_item = ITEM_NONE;

    sna_800515BC(pActor, 0);

    pActor->field_9B4_action_table = &weapon_actions_8009ED8C[GM_CurrentWeaponId];
    pActor->field_A28 = 450;
    pActor->field_A44 = pActor->field_20_ctrl.field_0_mov;
    pActor->field_A60 = pActor->field_20_ctrl.field_0_mov;

    gUnkCameraStruct_800B77B8.field_0 = pActor->field_A60;

    if (GCL_GetOption_80020968('o')) // oar
    {
        pActor->field_A5A = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    pActor->field_890_autoaim_max_dist = 6000;

    if (GCL_GetOption_80020968('l')) // len
    {
        pActor->field_890_autoaim_max_dist = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    pActor->field_892_autoaim_min_angle = 512;

    if (GCL_GetOption_80020968('r')) // rot
    {
        pActor->field_892_autoaim_min_angle = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    dword_800ABBDC = -1023;
    dword_800ABBD4 = 1023;

    if (GCL_GetOption_80020968('t')) // turn
    {
        dword_800ABBDC = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        dword_800ABBD4 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    pActor->field_A70 = -1;

    if (GCL_GetOption_80020968('e')) // exec
    {
        pActor->field_A70 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    temp_a1 = pActor->field_A26_stance;

    if (temp_a1 == 3)
    {
        pActor->field_A26_stance = 2;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PRONE | PLAYER_FIRST_PERSON_DUCT);
        DG_InvisibleObjs(pActor->field_9C_obj.objs);
        sna_8004EC8C(pActor);
        sna_start_anim_8004E1F4(pActor, &sna_anim_duct_move_80054424);
        GM_Camera_800B77E8.field_22 = 2;
        var_v_2 = sna_8004EAA8(pActor, 2);
    }
    else
    {
        var_s0_2 = sna_8004EAA8(pActor, temp_a1);

        if ((pActor->field_9AC & 1) || (pActor->field_920_tbl_8009D580 & 0x20))
        {
            if ((unsigned int)(pActor->field_9A8_current_item - 2) < 3)
            {
                var_s0_2 = 4;
            }
        }
        else
        {
            sna_start_anim_8004E1F4(pActor, dword_8009EEA4[pActor->field_A26_stance]);
        }

        var_v_2 = var_s0_2;
    }

    GM_ConfigObjectAction_80034CD4(&pActor->field_9C_obj, var_v_2, 0, 0);
    GM_ActMotion_80034A7C(&pActor->field_9C_obj);

    temp_v1_3 = (short)pActor->field_9C_obj.field_18;

    pActor->field_798_p_height = temp_v1_3;
    pActor->field_20_ctrl.field_32_height = temp_v1_3;

    pActor->field_9B0_pad_ptr = GV_PadData_800B05C0;
}

static inline void sna_LoadSnake4( POLY_FT4 *packs, int n_packs, DG_TEX *tex )
{
    char u, v;
    int  i;

    u = tex->field_8_offx;
    v = tex->field_9_offy;

    for ( i = 0; i < n_packs; i ++ )
    {
        setPolyFT4( packs );
        setSemiTrans( packs, 1 );
        setRGB0( packs, 128, 128, 128 );
        setXY4( packs, 255, 164, 303, 164, 255, 176, 303, 176 );
        setUV4( packs, u, v, u + 48, v, u, v + 12, u + 48, v + 12 );
        packs->tpage = tex->field_4_tPage;
        packs->clut = tex->field_6_clut;
        packs ++ ;
    }
}

static inline int sna_LoadSnake(Actor_SnaInit *pActor, int scriptData, int scriptBinds)
{
    CONTROL    *pCtrl;
    OBJECT        *pObject;
    TARGET *pTarget;
    Jirai_unknown *pJiraiUnk;
    Shadow_94     shadow94;
    SVECTOR       vec;
    SVECTOR       *pVec;
    int           tmp, model, i;
    char          *param_pos, *param_dir;

    pCtrl = &pActor->field_20_ctrl;
    if (GM_InitLoader_8002599C(pCtrl, scriptData, scriptBinds) < 0)
    {
        return -1;
    }

    param_pos = (char*)GCL_GetOption_80020968('p'); // pos
    param_dir = (char*)GCL_GetOption_80020968('d'); // dir
    GM_ConfigControlString_800261C0(pCtrl, param_pos, param_dir);
    GM_ConfigControlHazard_8002622C(pCtrl, 0, 450, 450);

    tmp = 1;
    pCtrl->field_59 = tmp;

    GM_ConfigControlAttribute_8002623C(pCtrl, tmp);
    GM_ConfigControlTrapCheck_80026308(pCtrl);


    pObject = &pActor->field_9C_obj;

    model = KMD_SNAKE;
    if (GCL_GetOption_80020968('m')) // model
    {
        model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    GM_InitObject_80034A18(pObject, model, BODY_FLAG, OAR_SNAKE);

    GM_ConfigObjectJoint_80034CB4(pObject);
    GM_ConfigMotionControl_80034F08(pObject,
                                    &pActor->field_180,
                                    OAR_SNAKE,
                                    &pActor->field_1D0[0],
                                    &pActor->field_1D0[17],
                                    pCtrl,
                                    (SVECTOR *)&pActor->field_698_joint_rotations);
    GM_ConfigObjectLight_80034C44(pObject, &pActor->field_848_lighting_mtx);

    GM_PlayerControl_800AB9F4 = pCtrl;
    GM_PlayerPosition_800ABA10 = pActor->field_20_ctrl.field_0_mov;
    GM_PlayerBody_800ABA20 = pObject;

    sna_8004EB14(pActor);

    if (sna_LoadSnake2(pActor) < 0)
    {
        return -1;
    }

    sna_LoadSnake3(pActor);

    pVec = &vec;
    setVector(pVec, 300, 650, 300);

    pTarget = pActor->field_89C_pTarget = GM_AllocTarget_8002D400();

    GM_SetTarget_8002DC74(pTarget, 159, PLAYER_SIDE, pVec);
    GM_Target_8002DCCC(pTarget, 1, -1, GM_SnakeCurrentHealth, 0, &DG_ZeroVector_800AB39C);
    GM_Target_8002DCB4(pTarget, 0, 0, &pActor->field_8F4, &pActor->field_8FC);
    GM_Target_SetVector_8002D500(pTarget, &pActor->field_20_ctrl.field_0_mov);

    pActor->field_A22_snake_current_health = GM_SnakeCurrentHealth;

    sna_LoadSnake4(pActor->field_950, 2, DG_GetTexture_8001D830(PCX_EMPTY2));

    shadow94.objs_offsets[0] = 0;
    shadow94.objs_offsets[1] = 6;
    shadow94.objs_offsets[2] = 12;
    shadow94.objs_offsets[3] = 15;

    pActor->field_888_pShadow = shadow_init2_80060384(pCtrl, pObject, shadow94, &pActor->field_88C);

    dword_800ABA1C = 0;
    GM_BombSeg_800ABBD8 = 0;

    for (i = 0; i < 16; i++)
    {
        tenage_ctrls_800BDD30[i] = NULL;
    }

    dword_800BDD28 = 0;
    tenage_ctrls_count_800BDD70 = 0;

    pJiraiUnk = stru_800BDD78;
    i = 0;

    while (i < 16)
    {
        i++;
        pJiraiUnk->field_0_ypos = 6;
        pJiraiUnk->field_4_pActor = NULL;
        pJiraiUnk++;
    }

    dword_8009F434 = 0;
    bakudan_count_8009F42C = 0;

    pJiraiUnk = stru_800BDE78;
    i = 0;

    while (i < 8)
    {
        i++;
        pJiraiUnk->field_0_ypos = 5;
        pJiraiUnk->field_4_pActor = NULL;
        pJiraiUnk++;
    }

    dword_8009F440 = 0;
    dword_8009F444 = 0;
    counter_8009F448 = 0;
    dword_8009F46C[0] = 0;
    dword_8009F470 = 0;
    dword_8009F474 = 0;
    target_800BDF00 = 0;

   for (i = 0; i < 64; i++)
   {
        gBulNames_800BDC78[i] = 0;
   }

    tabako_dword_8009F2C0 = 0;
    pVec_800ABBCC = NULL;

    if (model == KMD_SNE_WET2) // wet suit in the docks
    {
        sna_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK29);
    }

    return 0;
}

GV_ACT *sna_NewSnake_8005B650(int name, int where, int argc, char **argv)
{
    Actor_SnaInit *pActor;

    pActor = (Actor_SnaInit *)GV_NewActor_800150E4(5, sizeof(Actor_SnaInit));
    if (!pActor)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                              (TActorFunction)&sna_act_8005AD10,
                              (TActorFunction)&sna_kill_8005B52C,
                              aSnaInitC);

    if (sna_LoadSnake(pActor, name, where) < 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return NULL;
    }

    snainit_actor_800A9424 = pActor;
    return &pActor->field_0_actor;
}

// some jump table probably
const char missing_rdata[] = {0xe4, 0x4f, 0x05, 0x80, 0xd4, 0x4f, 0x05, 0x80, 0x0c, 0x50, 0x05, 0x80, 0x48, 0x50, 0x05, 0x80, 0x94, 0x50, 0x05, 0x80, 0xfc, 0x50, 0x05, 0x80, 0xb4, 0x53, 0x05, 0x80};
