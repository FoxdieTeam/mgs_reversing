// FIXME: copy-pasta of snake/sna_init.c

#include "sna_init.h"
#include "chara/snake/afterse.h"
#include "chara/snake/shadow.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Kojo/demothrd.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Okajima/blood.h"
#include "Bullet/bakudan.h"
#include "Game/hittable.h"
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
#include "Weapon/rifle.h"
#include "Weapon/socom.h"
#include "Weapon/famas.h"
#include "Weapon/rcm.h"
#include "Weapon/bomb.h"
#include "Weapon/mine.h"
#include "SD/g_sound.h"

extern int dword_800ABBA8;
int        SECTION(".sbss") dword_800ABBA8;

extern int gSnaMoveDir_800ABBA4;
int        SECTION(".sbss") gSnaMoveDir_800ABBA4;

extern char *dword_800ABBB4;
char *       SECTION(".sbss") dword_800ABBB4;

extern CONTROL *GM_PlayerControl_800AB9F4;
extern OBJECT  *GM_PlayerBody_800ABA20;

extern SVECTOR *svector_800ABBB8;
SVECTOR *SECTION(".sbss") svector_800ABBB8;

extern int           dword_800ABBBC;
int SECTION(".sbss") dword_800ABBBC;

extern int           dword_800ABBC0;
int SECTION(".sbss") dword_800ABBC0;

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

extern void *dword_800ABBB0;
void *       SECTION(".sbss") dword_800ABBB0;

extern void *GM_BombSeg_800ABBD8;
void *SECTION(".sbss") GM_BombSeg_800ABBD8;

extern SVECTOR *dword_800ABBAC;
SVECTOR *SECTION(".sbss") dword_800ABBAC;

extern short              GM_WeaponChanged_800AB9D8;
extern int                GM_AlertMode_800ABA00;
extern int                GM_GameOverTimer_800AB3D4;
extern int                GM_GameStatus_800AB3CC;
extern SVECTOR            DG_ZeroVector_800AB39C;
extern PlayerStatusFlag   GM_PlayerStatus_800ABA50;
extern GM_Camera          GM_Camera_800B77E8;
extern unsigned short     GM_WeaponTypes_8009D580[];
extern unsigned short     GM_ItemTypes_8009D598[];
extern void              *dword_8009EEA4[];
extern int                GV_Time_800AB330;
extern int                bakudan_count_8009F42C;
extern int                gSnaMoveDir_800ABBA4;
extern int                DG_UnDrawFrameCount_800AB380;
extern int                counter_8009F448;
extern int                dword_800ABA1C;
extern int                tabako_dword_8009F2C0;
extern int                GM_PlayerAddress_800AB9F0;
extern SVECTOR            GM_PlayerPosition_800ABA10;
extern UnkCameraStruct    gUnkCameraStruct_800B77B8;
extern GV_PAD             GV_PadData_800B05C0[4];
extern CONTROL        *tenage_ctrls_800BDD30[16];
extern HITTABLE           c4_actors_800BDD78[C4_COUNT];
extern HITTABLE      stru_800BDE78[8];
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
extern short              GM_Magazine_800AB9EC;
extern short              GM_MagazineMax_800ABA2C;
extern void              *dword_8009EEB0[];
extern void              *dword_8009EEB8[];
extern int                dword_800AB9D4;
extern short              HzdHeights_8009EEC4[];
extern int                DG_CurrentGroupID_800AB968;
extern int                GV_Clock_800AB920;
extern char               dword_8009EF1C[];
extern char               dword_8009EF20[];
extern TSnakeEquipFuncion gSnakeEquips_8009EF8C[];
extern TPlayerActFunction  GM_lpfnPlayerActControl_800AB3DC;
extern TPlayerActFunction  GM_lpfnPlayerActObject2_800AB3E0;
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

Sna_E1 e1_800AB78C = {2u, 6u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 e1_800AB794 = {0u, 0u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 e1_800AB79C = {1u, 5u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 e1_800AB7A4 = {3u, 3u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 e1_800AB7AC = {90u, 90u, 16u, 22u, 43u, 53u, 88u, 89u};
Sna_E1 e1_800AB7B4 = {76u, 76u, 78u, 85u, 25u, 87u, 40u, 41u};
Sna_E1 e1_800AB7BC = {95u, 95u, 99u, 100u, 26u, 102u, 88u, 89u};
Sna_E1 e1_800AB7C4 = {20u, 21u, 84u, 0u, 212u, 3u, 0u, 0u};

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
    {NewFAMAS_80066374, sna_gun_800540D0},
    {NewGrenade_80066A4C, sna_anim_grenade_80058470},
    {NewRCM_80066FF0, sna_gun_800540D0},
    {NewAAM_80067480, sna_anim_stinger_800570C0},
    {NewMine_800677BC, sna_anim_claymore_80057474},
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
    NewBandana_80061E40,
    NULL,
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

int            snainit_item_800A9420 = -1;
SnaInitWork *snainit_actor_800A9424 = NULL;

SVECTOR svector_800AB7CC = {150, 0, 50, 0};
SVECTOR svector_800AB7D4 = {0, 0, 100, 0};
SVECTOR svector_800AB7DC = {-1024, 0, 0, 0};
SVECTOR svector_800AB7E4 = {5, 500, 80, 0};
SVECTOR svector_800AB7EC = {0, 0, 800, 0};
SVECTOR svector_800AB7F4 = {0, 100, -300, 0};
SVECTOR svector_800AB7FC = {0, 0, -300, 0};

#define RIFLE_TEBURE_TIME   90 // delay before camera shake
#define TEBURE              122
#define GetAction( work ) (work->field_9C_obj.action_flag)
#define EndMotion( work ) (work->field_9C_obj.is_end != 0)
#define SET                 work->field_9B4_action_table->field_10->field_0
#define DispEmpty( work ) (work->field_9A0 = 4)

void sub_8004EB74(SnaInitWork *work)
{
    if (GM_Camera_800B77E8.first_person == 0)
    {
        if (work->field_9B0_pad_ptr->dir == (short)-1)
        {
            work->field_A20 = -6;
        }
        else
        {
            work->field_A20 = -3;
        }
    }

    GM_Camera_800B77E8.first_person = 1;
    work->field_A56 = 0;
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_FIRST_PERSON);

    if (!(work->field_920_tbl_8009D580 & 0x200))
    {
        sd_set_cli(0x01ffff20, 0);
    }
}

void sna_8004EC00(SnaInitWork *work)
{
    if (GM_Camera_800B77E8.first_person == 1)
    {
        work->field_A20 = 6;
    }

    GM_Camera_800B77E8.first_person = 0;
    work->field_A56 = 0;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_FIRST_PERSON_CAN_LR_PEEK | PLAYER_FIRST_PERSON);
    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK16);

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sd_set_cli(0x01ffff21, 0);
    }
}

void sna_8004EC8C(SnaInitWork *work)
{
    ushort v2; // $v1

    sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK12);
    work->field_A28 = 460;
    GM_Camera_800B77E8.first_person = 1;
    v2 = *(ushort *)&e1_800AB7C4.field_4;
    work->field_A20 = -6;
    work->field_9D0[2] = 320;
    work->field_9D0[4] = v2;
    work->field_9D0[6] = v2;
    sd_set_cli(0x01ffff20, 0);
}

void sub_8004ED08(SnaInitWork *work)
{
    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK12);
    work->field_A28 = 0x1c2;
    GM_Camera_800B77E8.first_person = 0; // weapon related?
    work->field_A20 = 6;
    sna_8004EB14(work);
    sd_set_cli(0x01ffff21, 0);
}

void sna_act_helper2_helper3_8004ED6C(SnaInitWork *work)
{
    if (work->field_A20 != 0)
    {
        if (work->field_A20 >= 1)
        {

            if ((GM_Camera_800B77E8.first_person == 0) && (--work->field_A20 == 0))
            {
                DG_VisibleObjs(work->field_9C_obj.objs);

                if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4))
                {
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
                }
            }
        }
        else if ((GM_Camera_800B77E8.first_person != 0) && (++work->field_A20 == 0))
        {
            DG_InvisibleObjs(work->field_9C_obj.objs);
        }
    }
}

void sna_8004EE28(SnaInitWork *snake)
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

    vx = (vec.vx / 16) * 16;
    gUnkCameraStruct_800B77B8.rotate2.vx = vx;
}

void sub_8004EEB0(SnaInitWork *work)
{
    short sVar1;
    int   iVar2;
    int   arg0;

    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        arg0 = work->control.turn.vy;
        if (GV_DiffDirS(arg0, gSnaMoveDir_800ABBA4))
        {
            iVar2 = GV_NearDiffP(arg0, gSnaMoveDir_800ABBA4);
            sVar1 = sub_8002646C(iVar2, gSnaMoveDir_800ABBA4, 0x40);
            work->control.turn.vy = sVar1;
        }
    }
}

void sna_8004EF14(SnaInitWork *work)
{
    int actionFlag;
    int diff;
    int y;

    y = work->control.turn.vy;

    diff = GV_DiffDirS(y, gSnaMoveDir_800ABBA4);
    if (diff == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        y = work->field_9B4_action_table->field_0->field_1;
        SetAction_8004E22C(work, y, 4);
    }
    else
    {
        short sVar2;
        int   iVar4;

        if (diff < 0)
        {
            actionFlag = work->field_9B4_action_table->field_4->field_8;
        }
        else
        {
            actionFlag = work->field_9B4_action_table->field_4->field_9;
        }

        SetAction_8004E22C(work, actionFlag, 4);
        iVar4 = GV_NearDiffP(y, gSnaMoveDir_800ABBA4);
        sVar2 = sub_8002646C(iVar4, gSnaMoveDir_800ABBA4, 0x40);
        work->control.turn.vy = sVar2;
    }
}

int sub_8004EFE4(SnaInitWork *work, int param_2)
{
    int      ret;
    SVECTOR *vec; // not sure if correct

    if (param_2 == 1)
    {
        vec = (SVECTOR *)&work->field_180.field_04_info1;
    }
    else
    {
        vec = (SVECTOR *)&work->field_180.field_1C_info2;
    }

    if (param_2 == 1)
    {
        ret = GetAction(work);
    }
    else
    {
        ret = work->field_9C_obj.field_10;
    }

    if (vec->vx + vec->vy == 1)
    {
        return ret;
    }

    return -1;
}

void sna_8004F034(SnaInitWork *work, unsigned int bits)
{
    if ( bits != work->field_180.field_04_info1.field_8 )
    {
        work->field_180.field_1C_info2.field_8 = ~bits;
        work->field_180.field_04_info1.field_8 = bits;
        if ( bits == 0xFFFF && sub_8004EFE4(work, 2) >= 0 )
        {
            work->field_180.interp = 4;
            work->field_180.field_1C_info2.field_14 = 2;
        }
    }
}

void sna_act_helper2_helper4_8004F090(SnaInitWork *work, int param_2)
{
    int    iVar1;
    MATRIX mtx;

    DG_SetPos_8001BC44(&work->field_9C_obj.objs->objs[6].world);
    DG_MovePos_8001BD20(&svector_800AB7D4);
    DG_RotatePos_8001BD64(&svector_800AB7DC);
    ReadRotMatrix(&mtx);

    iVar1 = -1;
    switch (param_2)
    {
    case 3:
        iVar1 = 0;
        break;
    case 1:
    case 4:
        iVar1 = 1;
        break;
    case 2:
        iVar1 = 2;
        break;
    }

    if (iVar1 >= 0)
    {
        NewBlood_80072728(&mtx, iVar1);
    }
}

void sub_8004F14C(SnaInitWork *work)
{
    work->field_91C_weapon_idx = WEAPON_NONE;
    GM_CurrentWeaponId = WEAPON_NONE;

    if (work->field_908_weapon_actor != 0)
    {
        GV_DestroyActorQuick(work->field_908_weapon_actor);
    }

    work->field_908_weapon_actor = 0;
    work->field_920_tbl_8009D580 = GM_WeaponTypes_8009D580[0];
    work->field_918_n_bullets = 0;
    work->field_9B4_action_table = &actions_no_weapon_8009ED70;
    work->field_90C_pWeaponFn = &sna_anim_chokethrow_begin1_80054210;
    work->field_910 = 0;
    work->field_926 = 0;
    work->field_924 = 0;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) != 0)
    {
        work->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH |
                                          PLAYER_FIRST_PERSON_CAN_LR_PEEK | PLAYER_FIRST_PERSON);
    }
    else
    {
        sna_8004EC00(work);
    }
}

void sub_8004F204(SnaInitWork *work)
{
    if (work->field_9A4_item_actor != 0)
    {
        GV_DestroyActorQuick(work->field_9A4_item_actor);
    }

    work->field_9A4_item_actor = 0;
    work->field_9A8_current_item = ITEM_NONE;
    GM_CurrentItemId = ITEM_NONE;
    work->field_9AC = GM_ItemTypes_8009D598[0];

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) != 0)
    {
        work->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH |
                                          PLAYER_FIRST_PERSON_CAN_LR_PEEK | PLAYER_FIRST_PERSON);
    }
    else
    {
        sna_8004EC00(work);
    }

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_CB_BOX);
}

void sna_set_invuln_8004F2A0(SnaInitWork *work, char invuln_frames)
{
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_INVULNERABLE);
    work->field_A24_invuln_frames = invuln_frames;
    work->field_89C_pTarget->class &= ~0x96;
}

void sna_clear_invuln_8004F2EC(SnaInitWork *work)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_INVULNERABLE);
    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK1);
    work->field_89C_pTarget->class |= TARGET_FLAG;
}

void sub_8004F338(SnaInitWork *work)
{
    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        work->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH
                                          | PLAYER_FIRST_PERSON_CAN_LR_PEEK
                                          | PLAYER_FIRST_PERSON);
    }
    else
    {
        sna_8004EC00(work);
    }

    sna_clear_invuln_8004F2EC(work);
    work->field_A24_invuln_frames = 0;
    sna_sub_8004E41C(work, 2);
    GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, 0);
    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK9);
    work->field_9C0 = 0;
    sna_8004E260(work, 0, 4, 0);
    DG_InvisiblePrim(work->field_92C);

    GM_ExitBehindCamera_80030AEC();

    GM_PlayerStatus_800ABA50 &= PLAYER_CAN_USE_CONTROLLER_PORT_2 | PLAYER_UNK4000000 |
                                PLAYER_GAMEOVER | PLAYER_CB_BOX | PLAYER_INTRUDE |
                                PLAYER_UNK4 | PLAYER_SQUAT | PLAYER_GROUND;

    if ((work->field_920_tbl_8009D580 & 0x200) != 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_FIRST_PERSON);
    }

    work->field_A28 = 0x1c2;
    work->field_894_flags1 &= (SNA_FLAG1_UNK20 | SNA_FLAG1_UNK28 | SNA_FLAG1_UNK29);
    work->control.skip_flag &= ~CTRL_BOTH_CHECK;
}

void sub_8004F454(SnaInitWork *work)
{
    int i;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING | PLAYER_PREVENT_FIRST_PERSON |
                                      PLAYER_KNOCKING);
    GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, NULL);

    for (i = 0; i < (int)(sizeof(work->field_718) / sizeof(SVECTOR)); i++) // 16
    {
        work->field_718[i] = DG_ZeroVector_800AB39C;
    }

    sna_8004E260(work, 0, 4, 0);
    sna_sub_8004E41C(work, 2);
    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK26);
    DG_InvisiblePrim(work->field_92C);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) == 0)
    {
        work->field_A28 = 450;
        GM_ExitBehindCamera_80030AEC();
    }

    work->control.skip_flag &= ~CTRL_BOTH_CHECK;
}

int sna_8004F544(SnaInitWork *work, SVECTOR param_2, int a3, int a4, int a5)
{
    MATRIX mtx;
    SVECTOR vec1;
    SVECTOR vec2;
    SVECTOR vec3;

    int bVar1;
    int iVar2;

    vec1 = param_2;

    vec3.vy = 0;
    vec3.vx = 0;
    vec3.vz = a3;

    ReadRotMatrix(&mtx);
    DG_SetPos2_8001BC8C(&param_2, &work->control.turn);
    DG_PutVector_8001BE48(&vec3, &vec2, 1);
    DG_SetPos_8001BC44(&mtx);

    iVar2 = sub_8004E51C(&vec1, work->control.map->hzd, a4, a5);

    bVar1 = a3 < iVar2;

    if (a3 < 0)
    {
        a3 = -a3;
        bVar1 = a3 < iVar2;
    }

    if (bVar1)
    {
        iVar2 = -1;
    }

    return iVar2;
}

int sna_8004F628(SnaInitWork *work, SVECTOR *param_2, int param_3, int param_4, int param_5, int param_6)
{
    SVECTOR vec;

    DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
    DG_PutVector_8001BE48(param_2, &vec, 1);

    if (param_6 >= 1)
    {
        vec.vy = work->control.levels[0] + param_6;
    }

    return sna_8004F544(work, vec, param_3, param_4, param_5) >= 0;
}

static inline int sna_update_life_helper_8004F6E8(int health, int item)
{
    int temp;

    if ((health == 0) &&
        (GM_GameOverTimer_800AB3D4 == 0) &&
        (item == ITEM_RATION) &&
        (GM_Items[ITEM_RATION] > 0) &&
        !GM_FrozenItemsState)
    {
        temp = (GM_DifficultyFlag > DIFFICULTY_EASY) ? 256 : 384;

        if (GM_DifficultyFlag < DIFFICULTY_EASY)
        {
            temp = GM_SnakeMaxHealth;
        }

        health = temp;

        if (health > GM_SnakeMaxHealth)
        {
            health = GM_SnakeMaxHealth;
        }

        GM_Items[ITEM_RATION] -= 1;

        if (GM_Items[ITEM_RATION] == 0)
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        GM_TotalRationsUsed += 1;
        GM_SeSet2_80032968(0, 63, SE_RECOVER_LIFE);
    }

    return health;
}

void UpdateLife_8004F6E8(SnaInitWork *work)
{
    TARGET *target;
    int     health;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4))
    {
        target = work->field_89C_pTarget;

        if (target->field_28 > 0)
        {
            target->field_26_hp += target->field_28;

            sna_act_unk2_80051170(work->field_89C_pTarget);
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK25);
        }

        return;
    }

    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK23))
    {
        return;
    }

    if (sna_check_flags1_8004E31C(work,SNA_FLAG1_UNK25) &&
        (GM_SnakeCurrentHealth == work->field_89C_pTarget->field_26_hp))
    {
        return;
    }

    if ((work->field_9A8_current_item == ITEM_B_ARMOR) && (work->field_89C_pTarget->a_mode == 1))
    {
        work->field_89C_pTarget->field_28 /= 2;
        work->field_89C_pTarget->field_26_hp += work->field_89C_pTarget->field_28;
        work->field_89C_pTarget->field_28 = 0;
    }

    health = work->field_89C_pTarget->field_26_hp + GM_SnakeCurrentHealth - work->field_A22_snake_current_health;

    if (health > GM_SnakeMaxHealth)
    {
        health = GM_SnakeMaxHealth;
    }

    if (health < 0)
    {
        health = 0;
    }

    if (work->field_89C_pTarget->field_44 != 10)
    {
        health = sna_update_life_helper_8004F6E8(health, work->field_9A8_current_item);
    }
    else
    {
        health = 0;
    }

    work->field_89C_pTarget->field_26_hp = health;
    work->field_A22_snake_current_health = health;
    GM_SnakeCurrentHealth = health;

    sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK25);
}

void sna_8004F8E4(SnaInitWork *work, int a2)
{
    GV_MSG msg;

    if ((GM_GameOverTimer_800AB3D4 == -1) || (GM_GameOverTimer_800AB3D4 == 0))
    {
        // スネーク
        msg.address = GV_StrCode("スネーク");
        msg.message_len = 6;
        msg.message[0] = 48650;
        msg.message[1] = a2;
        msg.message[2] = -1;
        msg.message[3] = -1;
        msg.message[4] = 2;
        msg.message[5] = 2042;

        work->field_7A4_msgs[work->field_7A0_msg_count] = msg;
        work->field_7A0_msg_count++;

        GM_GameOverTimer_800AB3D4 = 0;
        GM_GameOver_8002B6C8();

        GM_GameStatus_800AB3CC |= STATE_PADRELEASE;
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);

        if (work->field_A70 >= 0)
        {
            GCL_ForceExecProc(work->field_A70, NULL);
        }

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX))
        {
            sub_8004F204(work);
        }
    }
}

int sna_act_unk_helper4_8004FA3C(void)
{
    if (GM_SnakeCurrentHealth == 0 || GM_GameOverTimer_800AB3D4 != 0)
    {
        return 1;
    }

    return 0;
}

int sna_current_item_8004FB38(void)
{
    if (snainit_actor_800A9424)
    {
        return snainit_actor_800A9424->field_9A8_current_item;
    }

    return snainit_item_800A9420;
}

int sna_ration_available_8004FB4C(void)
{
    if ((snainit_actor_800A9424->field_9A8_current_item == ITEM_RATION) &&
        (GM_Items[ITEM_RATION] > 0) &&
        (GM_FrozenItemsState == 0))
    {
        return 1;
    }

    return 0;
}

SVECTOR ** sub_8004FB90(void)
{
    return &svector_800ABBB8;
}

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

void GM_CheckShukanReverseAnalog_8004FC70(unsigned char *pInput)
{
    if ((GM_GameStatusFlag & 0x1000) != 0)
    {
        *pInput = ~*pInput;
    }
}

int sub_8004FCB8(SnaInitWork *work, MATRIX *pMtx, int param_3)
{
    TARGET *pTarget;
    SVECTOR    vec;
    SVECTOR    vec_arr[2];

    pTarget = &work->field_8A0_target;
    GM_SetTarget_8002DC74(pTarget, 4, PLAYER_SIDE, (SVECTOR *)&pMtx->m[1][1]);
    DG_RotVector_8001BE98((SVECTOR *)&pMtx->m[2][2], &vec, 1);
    GM_Target_8002DCCC(pTarget, 3, param_3, pMtx->t[1], pMtx->t[2], &vec);
    DG_PutVector_8001BE48((SVECTOR *)&pMtx->m[0], &vec, 1);

    vec_arr[0].vx = work->field_9C_obj.objs->objs[5].world.t[0];
    vec_arr[0].vy = work->field_9C_obj.objs->objs[5].world.t[1];
    vec_arr[0].vz = work->field_9C_obj.objs->objs[5].world.t[2];
    vec_arr[1] = vec;

    if ( sub_8004E51C(vec_arr, work->control.map->hzd, 15, 1) < 0 )
    {
        GM_MoveTarget_8002D500(pTarget, &vec);
        return GM_PowerTarget_8002D7DC(pTarget);
    }

    return 0;
}

int sna_8004FDE8(SnaInitWork *work, Target_Data *pTargetData)
{
    int flags = 0x2;
    TARGET *pTarget;
    SVECTOR vec;
    SVECTOR vecs[2];

    if (pTargetData->field_18 == 0x40)
    {
        flags = 0x40;
    }

    GM_SetTarget_8002DC74(&work->field_8A0_target, flags, PLAYER_SIDE, &pTargetData->field_8_size);
    GM_Target_8002DCB4(&work->field_8A0_target, pTargetData->field_18, pTargetData->field_1C, &work->field_8F4, &work->field_8FC);
    DG_PutVector_8001BE48(&pTargetData->field_0, &vec, 1);
    GM_MoveTarget_8002D500(&work->field_8A0_target, &vec);

    work->field_8E8_pTarget = NULL;

    if (flags == 2)
    {
        pTarget = GM_CaptureTarget_8002D530(&work->field_8A0_target);
    }
    else
    {
        pTarget = GM_C4Target_8002D620(&work->field_8A0_target);
    }

    if (pTarget)
    {
        if (pTarget->class & 0x20)
        {
            pTarget->damaged &= ~flags;
            pTarget->field_2A += pTargetData->field_1C;
            return 0;
        }

        vecs[0] = work->control.mov;
        vecs[1] = pTarget->center;

        if (sub_8004E51C(vecs, work->control.map->hzd, 15, 1) < 0)
        {
            work->field_8E8_pTarget = pTarget;
            return 1;
        }

        pTarget->damaged &= ~flags;
        pTarget->field_2A += pTargetData->field_1C;
    }

    return 0;
}

int sna_act_helper2_helper5_8004FF88(SnaInitWork *work)
{
    void *pAnim;

    if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_IN_DEMO)) && (GM_AlertMode_800ABA00 != 3))
    {
        if (!GM_CheckPlayerStatusFlag_8004E29C(0x20001304) &&
            !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK9) &&
            (GM_SnakeCurrentHealth != 0) &&
            (GM_GameOverTimer_800AB3D4 == 0) &&
            (GM_StreamStatus_80037CD8() == -1) &&
            (work->field_9C_obj.field_10 == 0))
        {
            pAnim = work->field_9B8_fn_anim;

            if ((pAnim == sna_anim_idle_8005275C) ||
                (pAnim == sna_anim_crouch_800527DC) ||
                (pAnim == sna_anim_prone_idle_800528BC) ||
                (pAnim == sna_anim_wall_idle_and_c4_80052A5C) ||
                (pAnim == sna_anim_wall_crouch_80052CCC) ||
                (pAnim == sna_anim_duct_move_80054424))
            {
                return 1;
            }
        }
    }

    return 0;
}

int sna_8005009C(SnaInitWork *work)
{
    GV_PAD *pPad = work->field_9B0_pad_ptr;
    int tbl = work->field_920_tbl_8009D580;
    unsigned short press = pPad->press;
    unsigned short input = press;
    void *pAnimFn;

    if (!(tbl & 0x100))
    {
        input = pPad->status;
    }

    if (input & PAD_SQUARE)
    {
        work->field_910 = 0;

        if (tbl & 0x10)
        {
            sna_start_anim_8004E1F4(work, work->field_90C_pWeaponFn);
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            return 1;
        }

        if (tbl & 8)
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING))
            {
                pAnimFn = sna_anim_rungun_80056C3C;
            }
            else
            {
                pAnimFn = sna_anim_shoot_weapon_80056B88;
            }

            sna_start_anim_8004E1F4(work, pAnimFn);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_PREVENT_ITEM_SWITCH);
        }
        else
        {
            if ((input & PAD_CROSS) && (work->field_9B0_pad_ptr->dir >= 0))
            {
                pAnimFn = sna_anim_rungun_80056C3C;
            }
            else
            {
                pAnimFn = sna_anim_shoot_weapon_80056B88;
            }

            sna_start_anim_8004E1F4(work, pAnimFn);
        }

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_FIRST_PERSON);
        return 1;
    }

    if ((press & PAD_CIRCLE) && ((work->field_9B4_action_table->field_10->field_2 ^ 0x88) != 0))
    {
        sna_start_anim_8004E1F4(work, sna_anim_punch_80058C10);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
        return 1;
    }

    return 0;
}

void sna_check_knock_800501F8(SnaInitWork *work, int time)
{
    void *func;

    if (time >= 8)
    {
        if (work->field_91C_weapon_idx != WEAPON_C4 || GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING) != 0)
        {
            if ((work->field_9B0_pad_ptr->press & PAD_CIRCLE) != 0)
            {
                func = sna_knock_80054D68;
                sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK9);
                work->field_9C0 = func;
                work->field_9C4 = 0;
            }
        }
    }
}

void sna_8005027C(SnaInitWork *work, int time)
{
    SVECTOR *pVec;

    if (work->field_91C_weapon_idx != WEAPON_C4)
    {
        return;
    }

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING))
    {
        work->control.turn.vy = dword_800ABBD0;
    }

    if ((time < 8) || !(work->field_9B0_pad_ptr->press & PAD_SQUARE) || (work->field_9C0 == sna_80057378))
    {
        return;
    }

    if ((*work->field_918_n_bullets != 0) && (bakudan_count_8009F42C < 16))
    {
        pVec = &stru_8009EFD4[0];

        if (work->field_A26_stance != SNA_STANCE_STANDING)
        {
            pVec = &stru_8009EFD4[1];
        }

        if (sna_8004F628(work, pVec, 300, 12, 81, -1) > 0)
        {
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK9);
            work->field_9C0 = sna_80057378;
            work->field_9C4 = 0;
            return;
        }
    }

    GM_SeSet2_80032968(0, 63, SE_BUZZER);
}

int sna_prone_check_standup_80050398(SnaInitWork *work)
{
    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) != 0 && !sna_8004E808(work, 1, 0, -622, 1500))
    {
        work->field_A28 = 450;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, sna_anim_prone_standup_80053D74);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_2, 4);
        work->control.turn.vy = work->control.rot.vy;
        return 1;
    }

    return 0;
}

void sna_80050440(SnaInitWork *work)
{
    CONTROL *pCtrl;
    unsigned short *pArr;
    int inDuct;
    int i;

    // TODO: There is probably a better way to match this...
    SnaInitWork *work2;
    int a;

    if ((GM_GameOverTimer_800AB3D4 == 0) && (GM_SnakeCurrentHealth != 0))
    {
        pCtrl = &work->control;
        pArr = pCtrl->field_10_events.field_8_array;

        inDuct = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_INTRUDE);

        for (i = pCtrl->field_10_events.field_6_count; i > 0; pArr++, i--)
        {
            if (*pArr == 0x73D2)
            {
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_INTRUDE);
                break;
            }
        }

        if (!inDuct)
        {
            if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
            {
                return;
            }

            sna_8004EC8C(work);
            // TODO: There is probably a better way to match this...
            work2 = work;
            a = 4;
            dword_800ABA1C = 0x100;
        }
        else
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
            {
                return;
            }

            sub_8004ED08(work);
            // TODO: There is probably a better way to match this...
            work2 = work;
            a = 4;
            dword_800ABA1C = 0;
        }

        sna_set_flags1_8004E2F4(work2, a);

        work->control.turn.vy = work->control.rot.vy;
    }
}

void sna_80050568(SnaInitWork *work)
{
    SVECTOR  diff;
    DG_OBJS *objs;
    short    dir;

    sna_80050440(work);

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        return;
    }

    objs = work->field_9C_obj.objs;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->control.step.vz = 0;
    work->control.step.vx = 0;

    DG_InvisibleObjs(objs);

    sna_start_anim_8004E1F4(work, sna_anim_duct_move_80054424);
    work->field_A54.prone_bool_thing = 0;
    sna_set_invuln_8004F2A0(work, 24);
    sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK1);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_UNK200 |PLAYER_UNK100);
    sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
    SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 0);

    objs = work->field_9C_obj.objs;
    diff.vx = objs->objs[6].world.t[0] - objs->objs[0].world.t[0];

    objs = work->field_9C_obj.objs;
    diff.vz = objs->objs[6].world.t[2] - objs->objs[0].world.t[2];

    dir = GV_VecDir2(&diff);
    work->control.turn.vy = dir;
    work->control.rot.vy = dir;
    work->control.skip_flag &= ~CTRL_BOTH_CHECK;
}

void snake_vr_sna_init_80053198(SnaInitWork *work, int time);

void sna_knockdown_getup_80050668(SnaInitWork *work)
{
    SVECTOR vec;
    int var_a2;
    int var_a3;
    int dir;
    DG_OBJS *pObjs;

    var_a2 = 500;

    if (work->field_A54.knockdown_thing == 1)
    {
        var_a2 = 2;
        var_a3 = -630;
    }
    else
    {
        var_a3 = -18;
    }

    if (!sna_8004E808(work, 1, var_a2, var_a3, 1500))
    {
        sna_set_invuln_8004F2A0(work, 0);
        sna_start_anim_8004E1F4(work, &sna_anim_knockdown_getup_80054A10);
    }
    else
    {
        work->field_A54.knockdown_thing = 0;

        sna_set_invuln_8004F2A0(work, 24);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK1);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_UNK200 | PLAYER_UNK100);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK5 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK2);

        DG_VisibleObjs(work->field_9C_obj.objs);

        if (GetAction(work) == 0x45)
        {
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);

            // TODO: Duplication is probably from an inline
            pObjs = work->field_9C_obj.objs;
            vec.vx = pObjs->objs[6].world.t[0] - pObjs->objs[0].world.t[0];

            pObjs = work->field_9C_obj.objs;
            vec.vz = pObjs->objs[6].world.t[2] - pObjs->objs[0].world.t[2];

            dir = GV_VecDir2(&vec);
            work->control.turn.vy = dir;
            work->control.rot.vy = dir;

            sna_start_anim_8004E1F4(work, &sna_anim_prone_idle_800528BC);
        }
        else
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_UNK200);
            sna_set_invuln_8004F2A0(work, 0);
            sna_set_flags1_8004E2F4(work, 4);
            sna_start_anim_8004E1F4(work, &snake_vr_sna_init_80053198);
        }
    }
}

int sub_800507D8(SnaInitWork *work)
{
    if (dword_800ABBC4 == 0 && work->field_A38_local_data == 0)
    {
        work->field_A28 = 450;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_KNOCKING | PLAYER_ON_WALL | PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK9);
        work->field_9C0 = NULL;
        sna_8004E260(work, 0, 4, 0);
        GM_ExitBehindCamera_80030AEC();
        return 1;
    }

    return 0;
}

void CheckMessage0_80050878(SnaInitWork *work)
{
    int ret;
    int length;
    GV_MSG *pEntry;
    GV_MSG *pMsg;
    unsigned short id;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_THROWING) &&
        (GM_SnakeCurrentHealth != 0) &&
        (GM_GameOverTimer_800AB3D4 == 0) &&
        !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4))
    {
        sna_start_anim_8004E1F4(work, &sna_act_helper3_helper_80056650);
        sna_set_invuln_8004F2A0(work, 0);
        sna_act_unk2_80051170(work->field_89C_pTarget);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_THROWING);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK4);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK28);
    }

    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK20))
    {
        return;
    }

    ret = GV_ReceiveMessage(work->control.name, &pMsg);

    if (ret == 0)
    {
        return;
    }

    length = ret;

    pEntry = &work->field_7A4_msgs[work->field_7A0_msg_count];
    pMsg = (pMsg + length) - 1;

    for (; length > 0; work->field_7A0_msg_count++, pMsg--, pEntry++, length--)
    {
        if (work->field_7A0_msg_count == 8)
        {
            break;
        }

        id = pMsg->message[0];

        if ((id == 0x937A) || (id == 0x70FB) || (id == 0x3238) || (id == 0xBE0A))
        {
            if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4))
            {
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK4);
            }
        }

        *pEntry = *pMsg;
    }
}

static inline void sna_act_unk_helper_80050A64(SnaInitWork *work, GV_MSG *pMsg, int var_s4)
{
    int flags;
    int len;
    UnkSnakeStruct2 *pStr;

    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK28))
    {
        return;
    }

    flags = 0;
    len = pMsg->message_len;
    pStr = &work->field_9E4;

    pMsg->message_len = 0;
    pStr->field_9E4 = pMsg->message[1];
    pStr->field_9E6 = -1;
    pStr->field_9E8 = -1;
    pStr->field_9EA = -1;
    pStr->field_9EC_flags3 = 0;

    if (len > 2)
    {
        pStr->field_9E6 = pMsg->message[2];
    }

    if (len > 3)
    {
        pStr->field_9E8 = pMsg->message[3];
    }

    if (len > 4)
    {
        pStr->field_9EA = pMsg->message[4];
    }

    if (len > 5)
    {
        flags = pStr->field_9EC_flags3 = pMsg->message[5];
    }

    if (sna_act_unk_helper4_8004FA3C() && (var_s4 == 0))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4);
        pMsg->message_len = 0;
        printf("force act cancel %d\n", pMsg->message[1]);
    }
    else
    {
        pStr->field_9F2 = 0;

        if (var_s4 != 0)
        {
            pStr->field_9F2 = 1;
        }

        if (!(flags & 0x80))
        {
            if (!work->field_A5A)
            {
                return;
            }

            GM_ConfigMotionControl_80034F08(&work->field_9C_obj, &work->field_180, work->field_A5A,
                                            &work->field_1D0[0], &work->field_1D0[17], &work->control,
                                            (SVECTOR *)&work->field_698_joint_rotations);
        }

        if (flags & 4)
        {
            if (len <= 6)
            {
                return;
            }

            pStr->field_9EE = work->control.mov.vy - pMsg->message[6];
        }
        else
        {
            pStr->field_9EE = work->control.levels[0];
        }

        if (flags & 1)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(2);
            sub_8004ED08(work);
        }

        if (flags & 0x10)
        {
            work->control.skip_flag |= CTRL_SKIP_TRAP;
        }

        pStr->field_9F0 = 1;

        sna_start_anim_8004E1F4(work, &sna_anim_dying_80055524);
        GM_SetPlayerStatusFlag_8004E2B4(4);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK28);
    }
}

static inline void sna_act_unk_helper2_80050A64(SnaInitWork *work, GV_MSG *pMsg)
{
    UnkSnakeStruct2 *pStr;

    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK28))
    {
        return;
    }

    pStr = &work->field_9E4;

    pStr->field_9E8 = -1;
    pStr->field_9F4.vx = pMsg->message[1];
    pStr->field_9F4.vy = pMsg->message[2];
    pStr->field_9F4.vz = pMsg->message[3];
    pStr->field_9F4.pad = pMsg->message[4];
    pStr->field_9EC_flags3 = 0;

    if (pMsg->message_len > 5)
    {
        pStr->field_9EC_flags3 = pMsg->message[5];
    }

    if (sna_act_unk_helper4_8004FA3C() && !(pStr->field_9EC_flags3 & 0x400))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4);
        pMsg->message_len = 0;
        printf("run move cancel\n");
    }
    else
    {
        if (pMsg->message_len > 6)
        {
            pStr->field_9E8 = pMsg->message[6];
        }

        if (pStr->field_9EC_flags3 & 4)
        {
            work->control.skip_flag |= CTRL_SKIP_TRAP;
        }

        pStr->field_9F0 = 0;
        sna_start_anim_8004E1F4(work, &sna_anim_mini_cutscene_800559D8);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK28);
        pMsg->message_len = 0;
    }
}

static inline void sna_act_unk_helper3_80050A64(SnaInitWork *work, GV_MSG *pMsg)
{
    UnkSnakeStruct2 *pStr;

    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK28))
    {
        return;
    }

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4);
        pMsg->message_len = 0;
    }
    else
    {
        pStr = &work->field_9E4;

        work->field_9FC = work->field_9B8_fn_anim;
        pStr->field_9EE = 0;
        pStr->field_9E8 = -1;
        pStr->field_9EA = pMsg->message[1];
        pStr->field_9EC_flags3 = 0;

        if (pMsg->message_len > 2)
        {
            pStr->field_9E8 = pMsg->message[2];
        }

        if (pMsg->message_len > 3)
        {
            pStr->field_9EC_flags3 = pMsg->message[3];
        }

        if (sna_act_unk_helper4_8004FA3C() && !(pStr->field_9EC_flags3 & 0x400))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4);
            pMsg->message_len = 0;
            printf("force stance cancel\n");
        }
        else
        {
            if (pStr->field_9EC_flags3 & 4)
            {
                work->control.skip_flag |= CTRL_SKIP_TRAP;
            }

            sna_start_anim_8004E1F4(work, &sna_act_unk_helper3_80055DD8);
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK28);
            pMsg->message_len = 0;
            pStr->field_9F0 = 0;
        }
    }
}

void sna_act_unk_80050A64(SnaInitWork *work)
{
    HZD_VEC vec;
    GV_MSG *pMsg;
    GV_MSG *pMsgIter;
    int msgCount;
    int count;
    int state;

    if ((work->field_7A0_msg_count == 0) || sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK18))
    {
        return;
    }

    msgCount = 0;
    pMsgIter = work->field_7A4_msgs;
    pMsg = work->field_7A4_msgs;

    for (count = work->field_7A0_msg_count; count > 0; count--, pMsg++)
    {
        switch (pMsg->message[0])
        {
        case 0xc000:
            pMsg->message_len = 0;
            break;

        case 0x937a:
            state = 0;
            goto helper3;

        case 0xbe0a:
            state = 1;
helper3:
            sna_act_unk_helper_80050A64(work, pMsg, state);
            break;

        case 0x70fb:
            sna_act_unk_helper2_80050A64(work, pMsg);
            break;

        case 0x3238:
            sna_act_unk_helper3_80050A64(work, pMsg);
            break;

        case 0x5e8b:
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK19);
            pMsg->message_len = 0;
            break;

        case 0x9a1f:
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK19);
            pMsg->message_len = 0;
            break;

        case HASH_KILL:
            GV_DestroyActor(&work->actor);
            pMsg->message_len = 0;
            break;

        case 0x2580:
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PAD_OFF);
            pMsg->message_len = 0;
            break;

        case 0xaf6a:
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PAD_OFF);
            pMsg->message_len = 0;
            break;

        case 0x8012:
            tabako_dword_8009F2C0 = pMsg->message[1];
            pMsg->message_len = 0;
            break;

        case 0x62b6:
            work->control.mov.vx = pMsg->message[1];
            work->control.mov.vy = pMsg->message[2];
            work->control.mov.vz = pMsg->message[3];
            work->control.step = DG_ZeroVector_800AB39C;
            sub_8004E588(work->control.map->hzd, &work->control.mov, &vec);
            work->control.levels[0] = vec.long_access[0];
            work->control.levels[1] = vec.long_access[1];
            pMsg->message_len = 0;
            break;

        case HASH_SLOW:
            if (pMsg->message[1] == HASH_ON)
            {
                sna_set_flags1_8004E2F4(work, SNA_FLAG2_UNK27);
                pMsg->message_len = 0;
            }
            else
            {
                sna_clear_flags1_8004E308(work, SNA_FLAG2_UNK27);
                pMsg->message_len = 0;
            }

            break;

        default:
            pMsg->message_len = 0;
            break;
        }


        if (pMsg->message_len != 0)
        {
            *pMsgIter = *pMsg;
            pMsgIter++;
            msgCount++;
        }
    }

    work->field_7A0_msg_count = msgCount;
}

void sna_act_unk2_80051170(TARGET *param_1)
{
    param_1->field_28 = 0;
    param_1->field_2A = 0;
    param_1->damaged &= ~(0x80 | 0x04);
    param_1->field_2C_vec = DG_ZeroVector_800AB39C;
    param_1->field_44 = -1;
    param_1->a_mode = 0;
}

static inline int sna_weapon_switching_helper_800511BC(SnaInitWork *work)
{
    if (sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK5))
    {
        return 0;
    }

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX | PLAYER_UNK200 | PLAYER_UNK100 | PLAYER_UNK4))
    {
        return 0;
    }

    if (!(work->field_920_tbl_8009D580 & 0x200) && GM_CheckPlayerStatusFlag_8004E29C(PLAYER_FIRST_PERSON))
    {
        return 0;
    }

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) || (GM_GameStatus_800AB3CC & STATE_PADRELEASE))
    {
        if (GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200)
        {
            return 0;
        }
    }

    return 1;
}

static inline int sna_weapon_switching_helper2_800511BC(SnaInitWork *work, int callback)
{
    WeaponCreateEntry *pWeaponEntry;
    GV_ACT * (*pWeaponCreateFn)(void *, void *, int, void *, int);
    GV_ACT *pWeaponActor;

    pWeaponActor = work->field_908_weapon_actor;

    if (pWeaponActor)
    {
        GV_DestroyActorQuick(pWeaponActor);
    }

    pWeaponEntry = &gSnakeWeapons_8009EF3C[GM_CurrentWeaponId + 1];
    pWeaponCreateFn = pWeaponEntry->mCreateActorFn;
    pWeaponActor = NULL;

    if (pWeaponCreateFn)
    {
        pWeaponActor = pWeaponCreateFn(&work->control, &work->field_9C_obj, 4, &work->field_914_trigger, 1);

        if (!pWeaponActor)
        {
            work->field_908_weapon_actor = 0;
            return -1;
        }
    }

    if (work->field_91C_weapon_idx == WEAPON_NIKITA)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_ITEM_SWITCH);
    }

    if (work->field_90C_pWeaponFn == &sna_anim_grenade_80058470)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_PREVENT_ITEM_SWITCH);
    }

    work->field_91C_weapon_idx = GM_CurrentWeaponId;

    if (callback)
    {
        GM_CallSystemCallbackProc_8002B570(3, GM_CurrentWeaponId);
    }

    work->field_920_tbl_8009D580 = GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1];

    if (GM_CurrentWeaponId >= 0)
    {
        work->field_918_n_bullets = &GM_Weapons[GM_CurrentWeaponId];
    }

    work->field_90C_pWeaponFn = pWeaponEntry->mStateFn;

    work->field_910 = 0;
    work->field_926 = 0;
    work->field_924 = 0;
    work->field_908_weapon_actor = pWeaponActor;
    work->field_9B4_action_table = &weapon_actions_8009ED8C[GM_CurrentWeaponId];

    return 0;
}

void sna_weapon_switching_800511BC(SnaInitWork *work, int callback)
{
    int temp_s1_2;

    if (GM_CurrentWeaponId != work->field_91C_weapon_idx)
    {
        GM_WeaponChanged_800AB9D8 = 1;
    }

    if (!GM_WeaponChanged_800AB9D8)
    {
        return;
    }

    if (!sna_weapon_switching_helper_800511BC(work))
    {
        return;
    }

    if (!(work->field_920_tbl_8009D580 & 0x1000) && (GM_CurrentWeaponId == work->field_91C_weapon_idx))
    {
        return;
    }

    if (sna_weapon_switching_helper2_800511BC(work, callback) < 0)
    {
        return;
    }

    temp_s1_2 = work->field_920_tbl_8009D580;
    GM_WeaponChanged_800AB9D8 = 0;

    if (temp_s1_2 & 0x200)
    {
        sub_8004EB74(work);
    }
    else if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sna_8004EC00(work);
    }

    if (temp_s1_2 & 0x20)
    {
        sna_start_anim_8004E1F4(work, work->field_90C_pWeaponFn);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_ON_WALL);
    }
    else if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sna_start_anim_8004E1F4(work, &sna_anim_duct_move_80054424);
    }
    else if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL))
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING))
        {
            sna_start_anim_8004E1F4(work, &sna_anim_wall_move_80052BA8);
        }
        else
        {
            sna_start_anim_8004E1F4(work, dword_8009EEB0[work->field_A26_stance]);
        }
    }
    else if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING))
    {
        sna_start_anim_8004E1F4(work, dword_8009EEB8[work->field_A26_stance]);
    }
    else
    {
        sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
    }

    sub_8004F454(work);
}

static inline int sna_helper_800515BC(SnaInitWork *work)
{
    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4) )
    {
        return 0;
    }

    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK6) )
    {
        return 0;
    }

    if ( (GM_CurrentItemId == ITEM_BANDANA) && (work->field_90C_pWeaponFn == &sna_80057A90) )
    {
        return 0;
    }

    if ( (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) ||
         ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31)) == STATE_PADRELEASE)) &&
         ((GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 2) != 0) )
    {
        return 0;
    }

    return 1;
}

void sna_800515BC(SnaInitWork *work, int a2)
{
    int itemType;
    int temp_s4;
    GV_ACT *pItemActor;
    TSnakeEquipFuncion *ppfnEquip;
    TSnakeEquipFuncion pfnEquip;
    int temp_s0_2;
    int var_s2;

    if ( !sna_helper_800515BC(work) )
    {
        return;
    }

    if ( GM_CurrentItemId == work->field_9A8_current_item )
    {
        return;
    }

    itemType = GM_ItemTypes_8009D598[GM_CurrentItemId + 1];

    if ( GM_CheckPlayerStatusFlag_8004E29C(0x300) && ((itemType & 0x8000) != 0) )
    {
        return;
    }

    temp_s4 = work->field_9AC;
    pItemActor = work->field_9A4_item_actor;

    if ( pItemActor )
    {
        GV_DestroyActorQuick(pItemActor);
    }

    ppfnEquip = &gSnakeEquips_8009EF8C[GM_CurrentItemId];
    pItemActor = NULL;

    if ( ((itemType & 0x8000) != 0) && (*ppfnEquip != 0) )
    {
        pfnEquip = *ppfnEquip;

        if ( (GM_CurrentItemId == 2) || (GM_CurrentItemId == 3) || (GM_CurrentItemId == 4) )
        {
            pItemActor = pfnEquip(&work->control, &work->field_9C_obj, 0);
        }
        else
        {
            pItemActor = pfnEquip(&work->control, &work->field_9C_obj, 6);
        }

        if ( !pItemActor )
        {
            work->field_9A4_item_actor = NULL;
            return;
        }
    }

    GM_ClearPlayerStatusFlag_8004E2D4(0x401000);

    work->field_9A8_current_item = GM_CurrentItemId;

    if ( a2 != 0 )
    {
        GM_CallSystemCallbackProc_8002B570(4, GM_CurrentItemId);
    }

    work->field_9AC = itemType;
    work->field_9A4_item_actor = pItemActor;

    if ( (itemType & 1) != 0 )
    {
        if ( GM_CurrentItemId == ITEM_SCOPE )
        {
            sna_start_anim_8004E1F4(work, &sna_anim_scope_80055334);
        }
        else if ( GM_CurrentItemId == ITEM_CAMERA )
        {
            sna_start_anim_8004E1F4(work, &sna_anim_jpegcam_800553CC);
        }
        else
        {
            sna_start_anim_8004E1F4(work, &sna_anim_box_idle_800553EC);
            GM_SetPlayerStatusFlag_8004E2B4(0x401000);
        }

        GM_ClearPlayerStatusFlag_8004E2D4(0x10010);
    }
    else
    {
        if ( ((work->field_920_tbl_8009D580 & 0x200) == 0) && ((temp_s4 & 1) != 0) )
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);

            if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) )
            {
                sna_start_anim_8004E1F4(work, &sna_anim_duct_move_80054424);
            }
            else if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) )
            {
                sna_start_anim_8004E1F4(work, dword_8009EEB0[work->field_A26_stance]);
            }
            else
            {
                sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
            }
        }

        if ( work->field_8E8_pTarget && (work->field_9B8_fn_anim != &sna_anim_throw_800589C8) )
        {
            sna_start_anim_8004E1F4(work, &sna_anim_choke_hold_80059154);
        }
    }

    if ((itemType & 2) != 0)
    {
        sub_8004EB74(work);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_SWITCH);
    } else if ( !(work->field_920_tbl_8009D580 & 0x200) &&
                !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sna_8004EC00(work);
    }

    temp_s0_2 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING);

    var_s2 = 0;
    if ( (work->control.skip_flag & CTRL_BOTH_CHECK) && ((itemType & 1) == 0) )
    {
        var_s2 = 1;
    }

    sub_8004F454(work);

    if ( temp_s0_2 != 0 )
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
    }

    if ( var_s2 != 0 )
    {
        work->control.skip_flag |= CTRL_BOTH_CHECK;
    }

    if ( GM_CheckPlayerStatusFlag_8004E29C(0x300) )
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_SWITCH);

        if  ( (work->field_9B8_fn_anim == &sna_anim_knockdown_80054710) || GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK200) )
        {
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
        }
    }
}

void sna_anim_idle_8005275C(SnaInitWork *work, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        work->field_A26_stance = SNA_STANCE_STANDING;

        work->field_9C8_anim_update_fn_3p = sna_fn_80052E58;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;

        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = work->field_9B4_action_table->field_0->field_1;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_0->field_0;
        }

        SetAction_8004E22C(work, action_flag, 4);
    }
}

void sna_anim_crouch_800527DC(SnaInitWork *work, int time)
{
    int sound;

    if (time == 0)
    {
        if (work->field_A26_stance != SNA_STANCE_CROUCH)
        {
            sound = SE_CHANGE_STANCE;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
            {
                sound = 183;
            }
            GM_SeSet_80032858(&work->control.mov, sound);
        }

        work->field_9C8_anim_update_fn_3p = sna_anim_crouch_helper_80053014;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_2, 4);
        work->field_A2C.vy = -128;
    }

    if ((time == 0 && work->field_A26_stance != SNA_STANCE_STANDING) ||
        (time == 4 && work->field_A26_stance == SNA_STANCE_STANDING))
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_SQUAT);
        work->field_A26_stance = SNA_STANCE_CROUCH;
    }
}

void sna_anim_prone_idle_800528BC(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_A26_stance = SNA_STANCE_GROUND;
        work->field_A28 = 450;
        work->field_9C8_anim_update_fn_3p = sna_fn_800531F4;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);
    }
}

void sna_anim_run_8005292C(SnaInitWork *work, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_80053360;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = work->field_9B4_action_table->field_4->field_7;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_4->field_0;
        }
        SetAction_8004E22C(work, action_flag, 4);
    }
}

void sna_anim_prone_move_800529C0(SnaInitWork *work, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        work->field_A28 = 450;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        work->field_9C8_anim_update_fn_3p = sna_fn_800535B8;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;
        if (work->field_A54.prone_bool_thing)
        {
            action_flag = work->field_9B4_action_table->field_4->field_4;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_4->field_3;
        }
        SetAction_8004E22C(work, action_flag, 4);
        work->field_A54.prone_bool_thing = 0;
    }
    sna_80050440(work);
}

void sna_anim_wall_idle_and_c4_80052A5C(SnaInitWork *work, int time)
{
    int sVar3;
    int sound;

    if (time == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) == 0)
        {
            sound = SE_WALLPRESS;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
            {
                sound = 183;
            }
            GM_SeSet_80032858(&work->control.mov, sound);
            work->control.turn.vy = dword_800ABBD0 - 2048;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_ON_WALL);
        }

        sVar3 = work->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;

        work->field_9C8_anim_update_fn_3p = sna_anim_wall_idle_and_c4_helper_800537D4;
        work->field_A28 = sVar3;
        work->field_A26_stance = 0;
        work->field_9CC_anim_update_fn_1p = sub_8005230C;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_4, 4);
    }

    GM_CheckBehindCamera_80030B3C(work->control.map->hzd, &work->control);

    if (work->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        (work->control).step.vx += pVec_800ABBCC->vx / 8;
        (work->control).step.vz += pVec_800ABBCC->vz / 8;
        work->field_A3A++;
    }
}

void sna_anim_wall_move_80052BA8(SnaInitWork *work, int time)
{
    int action;

    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING | PLAYER_ON_WALL);
        work->field_9C8_anim_update_fn_3p = sna_anim_wall_move_helper_800538CC;
        work->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (work->field_A54.wall_thing == 2)
        {
            action = work->field_9B4_action_table->field_4->field_5;
        }
        else
        {
            action = work->field_9B4_action_table->field_4->field_6;
        }

        work->field_A28 = 300;
        work->field_A54.wall_thing = 0;
        SetAction_8004E22C(work, action, 4);
        work->control.turn.vy = dword_800ABBD0 - 2048;
    }

    if (work->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        work->control.step.vx += pVec_800ABBCC->vx / 8;
        work->control.step.vz += pVec_800ABBCC->vz / 8;
        work->field_A3A++;
    }
}

void sna_anim_wall_crouch_80052CCC(SnaInitWork *work, int time)
{
    int sound;
    int sound2;

    if (time == 0)
    {
        if (work->field_A26_stance != SNA_STANCE_CROUCH)
        {
            sound = SE_CHANGE_STANCE;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
            {
                sound = 183;
            }
            GM_SeSet_80032858(&work->control.mov, sound);
        }

        work->field_A26_stance = SNA_STANCE_CROUCH;
        work->field_9C8_anim_update_fn_3p = sna_anim_wall_crouch_helper_80053A54;
        work->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) == 0)
        {
            sound2 = SE_WALLPRESS;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
            {
                sound2 = 0xb7;
            }
            GM_SeSet_80032858(&work->control.mov, sound2);
            work->control.turn.vy = dword_800ABBD0 - 2048;
        }

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_SQUAT | PLAYER_ON_WALL);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_5, 4);

        work->field_A28 = work->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;
    }

    GM_CheckBehindCamera_80030B3C(((work->control).map)->hzd, &work->control);

    if (work->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        work->control.step.vx += pVec_800ABBCC->vx / 8;
        work->control.step.vz += pVec_800ABBCC->vz / 8;
        work->field_A3A++;
    }
}

void sna_fn_80052E58(SnaInitWork *work, int time)
{
    int action;
    int diff;

    if (sna_8005009C(work))
    {
        return;
    }

    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        sna_start_anim_8004E1F4(work, sna_anim_crouch_800527DC);
        return;
    }

    if (GM_AlertMode_800ABA00 >= 3)
    {
        action = work->field_9B4_action_table->field_0->field_1;
    }
    else
    {
        action = work->field_9B4_action_table->field_0->field_0;
    }

    SetAction_8004E22C(work, action, 4);

    if (work->field_A38_local_data > 0)
    {
        work->field_A38_local_data--;
    }

    if (work->field_A38_local_data == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && work->field_79C == 2))
        {
            sna_start_anim_8004E1F4(work, sna_anim_wall_idle_and_c4_80052A5C);
        }
        else
        {
            diff = GV_DiffDirAbs(work->control.turn.vy, gSnaMoveDir_800ABBA4);
            if (diff > 256)
            {
                work->field_A38_local_data = diff / 1024 + 1;
            }
            else
            {
                sna_start_anim_8004E1F4(work, sna_anim_run_begin_80053B88);
            }

            work->control.turn.vy = gSnaMoveDir_800ABBA4;
        }
    }
}

void sna_anim_crouch_helper_80053014(SnaInitWork *work, int time)
{
    int diff;
    int sound;

    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        if (sna_8004E808(work, 0, 0, 0, 1100) == 0)
        {
            work->control.turn.vy = work->control.rot.vy;

            sound = SE_CHANGE_STANCE;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
            {
                sound = 183;
            }

            GM_SeSet_80032858(&work->control.mov, sound);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        }
    }
    else
    {
        if (work->field_A38_local_data > 0)
        {
            work->field_A38_local_data--;
        }

        if (work->field_A38_local_data == 0 && gSnaMoveDir_800ABBA4 >= 0)
        {
            if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && work->field_79C == 2))
            {
                sna_start_anim_8004E1F4(work, sna_anim_wall_crouch_80052CCC);
            }
            else
            {
                diff = GV_DiffDirAbs(work->control.turn.vy, gSnaMoveDir_800ABBA4);
                if (diff > 256)
                {
                    work->field_A38_local_data = diff / 1024 + 1;
                }
                else
                {
                    sna_start_anim_8004E1F4(work, sna_anim_prone_begin_80053BE8);
                }

                work->control.turn.vy = gSnaMoveDir_800ABBA4;
            }
        }
    }
}

void sna_fn_800531F4(SnaInitWork *work, int time)
{
    if (work->field_A38_local_data > 0)
    {
        work->field_A38_local_data -= 1;
    }

    if (!sna_prone_check_standup_80050398(work) && work->field_A38_local_data == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && work->field_79C == 2))
        {
            if (sna_8004E808(work, 0, 0, 0, 1500) == 0)
            {
                work->control.turn.vy = work->control.rot.vy;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND);
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_SQUAT | PLAYER_ON_WALL);
                sna_start_anim_8004E1F4(work, sna_anim_wall_crouch_80052CCC);
            }
        }
        else
        {
            if (sub_8004E458(work->control.turn.vy, gSnaMoveDir_800ABBA4) == 3)
            {
                work->field_A54.prone_bool_thing = 1;
            }
            else
            {
                work->field_A54.prone_bool_thing = 0;
            }

            sna_start_anim_8004E1F4(work, sna_anim_prone_move_800529C0);
        }
    }
}

void sna_80053360(SnaInitWork *work, int time)
{
    int angle;

    if (sna_8005009C(work))
    {
        return;
    }

    if (work->field_9B0_pad_ptr->press & PAD_CROSS)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, &sna_anim_crouch_800527DC);
        return;
    }

    if (gSnaMoveDir_800ABBA4 < 0)
    {
        if (++work->field_A3A >= 5)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
            return;
        }
    }
    else
    {
        work->field_A3A = 0;
    }


    if ((dword_800ABBC4 == 1) || ((dword_800ABBC4 != 0) && (work->field_79C == 2)))
    {
        if (++work->field_A38_local_data >= 3)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(work, &sna_anim_wall_idle_and_c4_80052A5C);
            return;
        }
    }
    else
    {
        work->field_A38_local_data = 0;
    }

    if (work->field_A38_local_data == 0)
    {
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            angle = sub_8004E4C0(work, gSnaMoveDir_800ABBA4);
        }
        else
        {
            angle = work->control.turn.vy;
        }
    }
    else
    {
        angle = gSnaMoveDir_800ABBA4;

        if (angle < 0)
        {
            angle = work->control.turn.vy;
        }
    }

    if (GV_DiffDirAbs(work->control.turn.vy, angle) > 1048)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
        work->control.turn.vy = angle;
        return;
    }

    work->control.turn.vy = angle;
    sub_8004EA50(work, angle);

    if (GM_AlertMode_800ABA00 >= 3)
    {
        SetAction_8004E22C(work, work->field_9B4_action_table->field_4->field_7, 4);
    }
    else
    {
        SetAction_8004E22C(work, work->field_9B4_action_table->field_4->field_0, 4);
    }
}

void sna_fn_800535B8(SnaInitWork *work, int time)
{
    int var_s0;
    int temp_s2;
    int temp_s3;
    unsigned char var_a1;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sna_start_anim_8004E1F4(work, &sna_anim_enter_duct_80053E9C);
        sna_set_invuln_8004F2A0(work, 0);
        return;
    }

    if (!sna_prone_check_standup_80050398(work))
    {
        if (gSnaMoveDir_800ABBA4 < 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);
            sna_start_anim_8004E1F4(work, &sna_anim_prone_idle_800528BC);
            return;
        }


        if ((dword_800ABBC4 == 1) || ((dword_800ABBC4 != 0) && (work->field_79C == 2)))
        {
            if (!sna_8004E808(work, 0, 0, 0, 1500))
            {
                work->control.turn.vy = work->control.rot.vy;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND | PLAYER_MOVING);
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_ON_WALL | PLAYER_SQUAT);
                sna_start_anim_8004E1F4(work, &sna_anim_wall_crouch_80052CCC);
            }
        }
        else
        {
            temp_s3 = work->field_9B4_action_table->field_4->field_3;
            temp_s2 = work->field_9B4_action_table->field_4->field_4;

            if (GetAction(work) == temp_s2)
            {
                var_s0 = gSnaMoveDir_800ABBA4 + 2048;
            }
            else
            {
                var_s0 = gSnaMoveDir_800ABBA4;
            }

            if (sub_8004E458(work->control.turn.vy, var_s0) == 3)
            {
                var_s0 += 2048;
                var_a1 = temp_s3;

                if (GetAction(work) == var_a1)
                {
                    var_a1 = temp_s2;
                }

                SetAction_8004E22C(work, (var_a1), 4);
            }

            work->control.turn.vy = sub_8004E4C0(work, var_s0);
        }
    }
}

void sna_anim_wall_idle_and_c4_helper_800537D4(SnaInitWork *work, int time)
{
    if (work->field_A38_local_data != 0)
    {
        work->field_A38_local_data--;
    }

    if (sub_800507D8(work))
    {
        return;
    }

    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK9))
    {
        sna_start_anim_8004E1F4(work, &sna_anim_wall_crouch_80052CCC);
        return;
    }

    if ((dword_800ABBC4 == 2) || (dword_800ABBC4 == 4))
    {
        work->field_A54.wall_thing = dword_800ABBC4;
        sna_start_anim_8004E1F4(work, &sna_anim_wall_move_80052BA8);
    }

    if ((dword_800ABBD0 - 2048) != work->control.rot.vy)
    {
        work->field_A3A = 0;
        work->control.turn.vy = dword_800ABBD0 - 2048;
    }

    sna_check_knock_800501F8(work, time);
    sna_8005027C(work, time);
}

void sna_anim_wall_move_helper_800538CC(SnaInitWork *work, int time)
{
    int var_s1;

    if (work->field_A38_local_data != 0)
    {
        work->field_A38_local_data--;
    }

    if (sub_800507D8(work))
    {
        return;
    }

    GM_CheckBehindCamera_80030B3C(work->control.map->hzd, &work->control);

    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK9))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, &sna_anim_wall_crouch_80052CCC);
        return;
    }

    if (dword_800ABBC4 == 1)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, &sna_anim_wall_idle_and_c4_80052A5C);
        return;
    }

    if (((dword_800ABBD0 - 2048) != work->control.rot.vy) || (pVec_800ABBC8 != pVec_800ABBCC))
    {
        work->field_A3A = 0;
        work->control.turn.vy = dword_800ABBD0 - 2048;
    }

    sna_check_knock_800501F8(work, time);
    sna_8005027C(work, time);

    if (dword_800ABBC4 == 2)
    {
        var_s1 = work->field_9B4_action_table->field_4->field_5;
    }
    else
    {
        var_s1 = work->field_9B4_action_table->field_4->field_6;
    }

    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
    SetAction_8004E22C(work, var_s1, 4);
}

void sna_anim_wall_crouch_helper_80053A54(SnaInitWork *work, int time)
{
    int var_s0;

    if (work->field_A38_local_data != 0)
    {
        work->field_A38_local_data--;
    }

    if (sub_800507D8(work))
    {
        return;
    }

    if ((work->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK9))
    {
        if (!sna_8004E808(work, 0, 0, 0, 1100))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT);
            var_s0 = SE_CHANGE_STANCE;

            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER))
            {
                var_s0 = 183;
            }

            GM_SeSet_80032858(&work->control.mov, var_s0);
            sna_start_anim_8004E1F4(work, &sna_anim_wall_idle_and_c4_80052A5C);
        }
    }
    else
    {
        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_05) && ((dword_800ABBD0 - 2048) != work->control.rot.vy))
        {
            work->field_A3A = 0;
            work->control.turn.vy = dword_800ABBD0 - 2048;
        }

        sna_check_knock_800501F8(work, time);
        sna_8005027C(work, time);
    }
}

void sna_fn_nothing_80053B80(SnaInitWork *work, int time)
{
}

void sna_anim_run_begin_80053B88(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_80054318;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_anim_prone_begin_80053BE8(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        sna_set_flags1_8004E2F4(work, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_0, 4);
        work->field_A26_stance = SNA_STANCE_GROUND;
        work->control.skip_flag |= CTRL_BOTH_CHECK | CTRL_SKIP_TRAP;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
    }

    if (time == 7)
    {
        work->control.skip_flag &= ~CTRL_SKIP_TRAP;
    }

    switch (work->field_A38_local_data)
    {
    case 0:
        if (work->field_798_p_height < 250)
        {
            work->control.skip_flag &= ~CTRL_BOTH_CHECK;
        }

        if (EndMotion(work))
        {
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);
            work->field_A38_local_data = 1;
        }
        break;
    case 1:
        sna_80050440(work);

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) != 0)
        {
            sna_start_anim_8004E1F4(work, sna_anim_enter_duct_80053E9C);
            sna_set_invuln_8004F2A0(work, 0);
            SetAction_8004E22C(work, work->field_9B4_action_table->field_4->field_3, 4);
        }
        else
        {
            sna_clear_flags1_8004E308(work, 0x30);
            sna_start_anim_8004E1F4(work, sna_anim_prone_idle_800528BC);
        }
    }
}

void sna_anim_prone_standup_80053D74(SnaInitWork *work, int time)
{
    int sound;

    if (time == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND);
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_2, 4);

        sound = SE_CHANGE_STANCE;
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
        {
            sound = 183;
        }
        GM_SeSet_80032858(&work->control.mov, sound);
        sna_set_flags1_8004E2F4(work, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }

    if (work->control.height >= 250)
    {
        work->control.skip_flag |= CTRL_BOTH_CHECK;
    }

    if (work->control.height > 500)
    {
        work->field_A26_stance = SNA_STANCE_STANDING;
    }

    if (time == 2)
    {
        work->control.turn.vx = 0;
    }

    if (time == 7)
    {
        work->control.skip_flag |= CTRL_SKIP_TRAP;
    }

    if (EndMotion(work))
    {
        work->control.skip_flag &= ~(CTRL_BOTH_CHECK | CTRL_SKIP_TRAP);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_anim_enter_duct_80053E9C(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_800543A8;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
        sna_set_flags1_8004E2F4(work, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) == 0 &&
            GetAction(work) == work->field_9B4_action_table->field_4->field_4)
        {
            work->field_A38_local_data = 48;
        }
        else
        {
            work->field_A38_local_data = 24;
        }
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
    }

    if (time == work->field_A38_local_data)
    {
        sna_clear_invuln_8004F2EC(work);
        sna_80050440(work);
        sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) != 0)
        {
            sna_start_anim_8004E1F4(work, sna_anim_duct_move_80054424);
        }
        else
        {
            sna_start_anim_8004E1F4(work, sna_anim_prone_idle_800528BC);
        }
    }
}

void sub_80053FAC(SnaInitWork *work, int time)
{
    short          vec_y;      // $v1
    unsigned short pad_status; // $s1

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_3, 2);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_FIRST_PERSON);
        vec_y = work->field_A54.prone_bool_thing;
        work->field_A54.prone_bool_thing = 0;
        work->field_90C_pWeaponFn = sna_gun_800540D0;
        work->field_910 = 0;
        work->field_926 = 0;
        work->field_924 = 0;
        work->control.turn.vy = vec_y;
        sna_8004E260(work, 0, 4, 0);
    }

    pad_status = work->field_9B0_pad_ptr->status;
    if (work->field_9C_obj.is_end || (pad_status & PAD_SQUARE) == 0)
    {
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
        work->field_910 = 0;
        if ((pad_status & PAD_SQUARE) != 0)
        {
            GM_SeSet_80032858(&work->control.mov, SE_READY_WEAPON);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_FIRST_PERSON);
            sna_start_anim_8004E1F4(work, sna_anim_shoot_weapon_80056B88);
            work->field_90C_pWeaponFn = sub_80057BF0;
            work->field_910 = 0;
            work->field_926 = 0;
            work->field_924 = 0;
        }
        else
        {
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        }
    }
}

void sna_gun_800540D0(SnaInitWork *work, int time)
{
    int iVar1;
    int a4;

    if (time == 0)
    {
        iVar1 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING);
        a4 = 0xffff;
        if (iVar1 != 0)
        {
            a4 = 0x3fe;
        }
        sna_8004E260(work, SET, 4, a4);
        work->field_A38_local_data = 0;
    }

    if ((work->field_9B0_pad_ptr->release & PAD_SQUARE) != 0)
    {
        work->field_A38_local_data = 1;
    }

    if ((work->field_9B0_pad_ptr->status & PAD_SQUARE) != 0)
    {
        work->field_926++;
    }
    else
    {
        work->field_926 = 0;
    }

    if (time == 8)
    {
        work->field_90C_pWeaponFn = sub_80057BF0;
        work->field_910 = 0;
        work->field_926 = 0;
        work->field_924 = 0;
    }
}

void sna_bomb_800541A8(SnaInitWork *work)
{
    void *pFn; // $a1

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
    work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
    work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
    if (sna_8004FDE8(work, &stru_8009EFE4[0]))
    {
        pFn = sna_800571B8;
    }
    else
    {
        pFn = sna_80057118;
    }
    sna_start_anim_8004E1F4(work, pFn);
}

// or sna_no_weapon_80054210 ?
void sna_anim_chokethrow_begin1_80054210(SnaInitWork *work, int time)
{
    void *pFn;
    work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
    work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        pFn = sna_anim_throw_800589C8;
    }
    else
    {
        pFn = sna_anim_chokethrow_begin2_80058C80;
    }
    sna_start_anim_8004E1F4(work, pFn);
}

void snake_vr_sna_init_80053198(SnaInitWork *work, int time)
{
    short new_y; // $v0

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, 134, 4);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK26);
    }

    if (work->field_9C_obj.is_end)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_UNK200);
        sna_start_anim_8004E1F4(work, sna_anim_prone_idle_800528BC);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 0);
        new_y = work->control.turn.vy + 2048;
        work->control.turn.vy = new_y;
        work->control.rot.vy = new_y;
        sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK26));
        sna_clear_invuln_8004F2EC(work);
    }
}

void sna_80054318(SnaInitWork *work, int time)
{
    if (time == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_start_anim_8004E1F4(work, sna_anim_run_8005292C);
        return;
    }

    if (work->field_9C_obj.is_end)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        return;
    }
}

void sna_fn_800543A8(SnaInitWork *work, int time)
{
    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) && time >= 16)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
        if (sna_prone_check_standup_80050398(work))
        {
            sna_clear_invuln_8004F2EC(work);
            sna_clear_flags1_8004E308(
                work, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6 | SNA_FLAG1_UNK10));
        }
    }
}

void sna_anim_duct_move_80054424(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sub_8005688C;
        work->field_9CC_anim_update_fn_1p = sub_80052468;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);
    }
    work->field_A60.vy = work->control.levels[0] + 150;
}

void sna_anim_duct_idle_80054488(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        work->field_9C8_anim_update_fn_3p = sub_80056928;
        work->field_9CC_anim_update_fn_1p = sub_80052468;
    }
    work->field_A60.vy = work->control.levels[0] + 250;
    sna_80050440(work);
}

void sna_anim_shot_flinch_800544E0(SnaInitWork *work, int time)
{
    int action_flag;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052540;
        sna_set_invuln_8004F2A0(work, 0);

        if (work->field_89C_pTarget->field_26_hp < 1)
        {
            GM_SeSet2_80032968(0, 0x3f, SE_PLAYEROUT);
            sna_8004F8E4(work, work->field_A26_stance == SNA_STANCE_GROUND ? 125 : 128);
        }

        if (work->field_A26_stance == SNA_STANCE_GROUND)
        {
            action_flag = work->field_9B4_action_table->field_C->field_8;
        }
        else if ((GV_Time_800AB330 & 1) != 0)
        {
            action_flag = work->field_9B4_action_table->field_C->field_0;
            work->field_A26_stance = SNA_STANCE_STANDING;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_C->field_1;
            work->field_A26_stance = SNA_STANCE_STANDING;
        }

        SetAction_8004E22C(work, action_flag, 4);
    }

    if (EndMotion(work))
    {
        sna_set_invuln_8004F2A0(work, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK100 | PLAYER_PREVENT_WEAPON_SWITCH);
        sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
    }

    if (work->field_A26_stance == SNA_STANCE_GROUND)
    {
        sna_80050568(work);
    }
}

void sna_act_helper2_helper7_80054648(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        sna_set_invuln_8004F2A0(work, 0);
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_800525F8;

        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_4, 4);

        if (work->field_89C_pTarget->field_26_hp <= 0)
        {
            GM_SeSet2_80032968(0, 63, SE_PLAYEROUT);
            sna_8004F8E4(work, 128);
        }
    }

    if (work->field_9C_obj.is_end)
    {
        sna_set_invuln_8004F2A0(work, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK100);
        sna_start_anim_8004E1F4(work, sna_anim_box_idle_800553EC);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK6);
    }
}

// knocked down by grenade etc
void sna_anim_knockdown_80054710(SnaInitWork *work, int time)
{
    int bVar1;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_A26_stance = SNA_STANCE_STANDING;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052540;
        sna_set_invuln_8004F2A0(work, 0);

        bVar1 = work->field_9B4_action_table->field_C->field_2;
        work->field_A54.prone_bool_thing = 1;

        SetAction_8004E22C(work, bVar1, 4);

        if (work->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_SeSet2_80032968(0, 0x3f, SE_PLAYEROUT);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);
        }

        work->control.skip_flag |= CTRL_BOTH_CHECK;
    }

    if (work->control.height < 500)
    {
        work->field_A26_stance = SNA_STANCE_GROUND;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
    }

    if (work->field_798_p_height < 250)
    {
        work->control.skip_flag &= ~CTRL_BOTH_CHECK;
    }

    if (EndMotion(work))
    {
        sna_set_invuln_8004F2A0(work, 32);
        sna_start_anim_8004E1F4(work, sna_anim_knockdown_idle_80054930);
    }
    else
    {
        if (time < 12 && work->field_A54.prone_bool_thing == 1)
        {
            work->control.turn.vy += 170;
        }

        if (time > 16)
        {
            GV_NearExp8V(&work->field_A2C.vx, &DG_ZeroVector_800AB39C.vx, 3);
        }

        if ((work->field_A54.prone_bool_thing == 1 && time == 12) ||
            (work->field_A54.prone_bool_thing == 2 && time == 0x14))
        {
            GM_SeSetMode_800329C4(&work->control.mov, SE_HIT_FLOOR, GM_SEMODE_BOMB);
        }

        work->control.step.vx = work->field_A2C.vx;
        work->control.step.vz = work->field_A2C.vz;
        sna_80050568(work);
    }
}

void sna_anim_knockdown_idle_80054930(SnaInitWork *work, int time)
{
    int   local_field_A54; // $v1
    int   action_flag;     // $a1
    short v5;              // $a1

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_knockdown_check_getup_80056A1C;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052540;
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK5);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK200 | PLAYER_GROUND);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK100);
        local_field_A54 = work->field_A54.prone_bool_thing;
        work->field_A26_stance = SNA_STANCE_GROUND;
        if (local_field_A54 == 1)
        {
            action_flag = work->field_9B4_action_table->field_C->field_4;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_C->field_5;
        }
        SetAction_8004E22C(work, action_flag, 4);
        if (work->field_89C_pTarget->field_26_hp <= 0)
        {
            v5 = 127;
            if (work->field_A54.prone_bool_thing == 1)
            {
                v5 = 126;
            }
            sna_8004F8E4(work, v5);
        }
        sna_80050568(work);
    }
}

void sna_anim_knockdown_getup_80054A10(SnaInitWork *work, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052540;
        if (work->field_A54.prone_bool_thing == 1)
        {
            action_flag = work->field_9B4_action_table->field_C->field_6;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_C->field_7;
        }
        SetAction_8004E22C(work, action_flag, 4);
        work->field_A54.prone_bool_thing = 0;
    }

    if (work->control.height >= 250)
    {
        work->control.skip_flag |= CTRL_BOTH_CHECK;
    }

    if (work->control.height >= 501)
    {
        work->field_A26_stance = SNA_STANCE_STANDING;
    }

    if (time == 2)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND);
        work->control.turn.vx = 0;
    }

    if (work->field_9C_obj.is_end)
    {
        sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
        sna_set_invuln_8004F2A0(work, 24);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_UNK200);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK1);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        work->control.skip_flag &= ~CTRL_BOTH_CHECK;
    }
}

void sna_anim_knockdown_shot_80054B50(SnaInitWork *work)
{
    work->field_9C8_anim_update_fn_3p = sna_knockdown_check_getup_80056A1C;
    work->field_9CC_anim_update_fn_1p = sna_fn_80052540;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK100);

    if (work->field_89C_pTarget->field_26_hp <= 0 && !GM_GameOverTimer_800AB3D4)
    {
        GM_SeSet2_80032968(0, 63, SE_PLAYEROUT);
        sna_8004F8E4(work, work->field_A54.prone_bool_thing == 1 ? 126 : 127);
    }
    else
    {
        sna_set_invuln_8004F2A0(work, 32);
    }

    sna_start_anim_8004E1F4(work, sna_anim_knockdown_idle_80054930);
}

// shot by tank while proned
void sna_anim_knockdown_shot_tank_80054C08(SnaInitWork *work, int time)
{
    char bVar1;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_80052540;
        sna_set_invuln_8004F2A0(work, 0);

        if (work->field_A54.prone_bool_thing == 1)
        {
            bVar1 = work->field_9B4_action_table->field_C->field_A;
        }
        else
        {
            bVar1 = work->field_9B4_action_table->field_C->field_B;
        }

        SetAction_8004E22C(work, bVar1, 4);

        if (work->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_SeSet2_80032968(0, 0x3f, SE_PLAYEROUT);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);
        }
    }

    if (EndMotion(work))
    {
        sna_set_invuln_8004F2A0(work, 32);
        sna_start_anim_8004E1F4(work, sna_anim_knockdown_idle_80054930);
    }
    else
    {
        if (time == 12)
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
        }

        if (time > 16)
        {
            GV_NearExp8V(&work->field_A2C.vx, &DG_ZeroVector_800AB39C.vx, 3);
        }

        work->control.step.vx = work->field_A2C.vx;
        work->control.step.vz = work->field_A2C.vz;
        sna_80050568(work);
    }
}

void sna_knock_80054D68(SnaInitWork *work, int time)
{
    SVECTOR vec;

    int var_a1;
    int var_t0;
    int temp_v0;
    int noise;
    int code;
    HZD_FLR *seg;

    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_KNOCKING);

        if (dword_800ABBC4 == 4)
        {
            var_a1 = work->field_9B4_action_table->field_0->field_7;
        }
        else
        {
            var_a1 = work->field_9B4_action_table->field_0->field_6;
        }

        GM_ConfigObjectOverride_80034D30(&work->field_9C_obj, var_a1, 0, 4, 1022);

        if (((work->field_91C_weapon_idx >= 0) && (work->field_91C_weapon_idx < 2)) || (work->field_91C_weapon_idx == 3))
        {
            var_t0 = 0x578;

            if (work->field_A26_stance != 0)
            {
                var_t0 = 0x302;
            }
        }
        else
        {
            var_t0 = 0x325;

            if (work->field_A26_stance != 0)
            {
                var_t0 = 0x15E;
            }
        }

        vec.vz = -150;
        vec.vy = 0;
        vec.vx = (dword_800ABBC4 == 4) ? 300 : -300;

        if (sna_8004F628(work, &vec, -250, 12, 0x41, var_t0))
        {
            temp_v0 = sub_80028830();
            code = (temp_v0 >> 8) & 7;

            if (code < 4)
            {
                seg = sub_80028820();
                printf("seg %d %d %d %d : ", seg->b1.x, seg->b1.z, seg->b1.y, seg->b1.h);
                printf("%d %d %d %d\n", seg->b2.x, seg->b2.z, seg->b2.y, seg->b2.h);
                printf("code %d\n", code);

                temp_v0 = GM_GetNoiseSound_8002E614(temp_v0, 0);
                noise = temp_v0;
                NewAfterse_800604C0(noise, 6);
            }
        }
    }

    if ((work->field_9C_obj.field_1C != 0) || (work->field_9C_obj.field_10 == 0))
    {
        sna_8004E260(work, 0, 4, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_KNOCKING);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK9);
        work->field_9C0 = NULL;
    }
}

void snake_vr_sna_init_800565C8(SnaInitWork *work, int time);

void sna_act_helper2_helper_80054EFC(SnaInitWork *work, int pTime)
{
    int            time2;
    int            status;
    unsigned char  actionFlag;
    SnaInitWork *actor;
    int            time;

    actor = work;
    time = pTime;

    if (time == 0)
    {
        actor->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        actor->field_9CC_anim_update_fn_1p = snake_vr_sna_init_800565C8;

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_GROUND))
        {
            actionFlag = actor->field_9B4_action_table->field_14->field_1;
        }
        else
        {
            actionFlag = actor->field_9B4_action_table->field_14->field_0;
        }

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_SQUAT))
        {
            sna_8004E260(actor, actionFlag, 4, 0x3FE);
            actor->field_A38_local_data = 1;
        }
        else
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
            {
                actor->field_A38_local_data = 2;
            }

            SetAction_8004E22C(actor, actionFlag, 4);
        }

        sna_set_flags1_8004E2F4(actor, SNA_FLAG1_UNK26);
    }

    if (time == 8)
    {
        if (actor->field_A26_stance == 2)
        {
            NewPadVibration_8005D58C(dword_8009EF08, 1);
            NewPadVibration_8005D58C(dword_8009EF10, 2);
        }
        else
        {
            NewPadVibration_8005D58C(dword_8009EEF8, 1);
            NewPadVibration_8005D58C(dword_8009EF00, 2);
        }
    }

    if ((time == 6 && actor->field_A26_stance == 2) ||
        (time == 0 && actor->field_A26_stance != 2))
    {
        GM_SeSetMode_800329C4(&actor->control.mov, SE_SNEEZE, GM_SEMODE_BOMB);
        GM_SetNoise(0x64, 0x10, &actor->control.mov);
    }

    status = 0;
    if (time >= 25)
    {
        status = actor->field_9B0_pad_ptr->status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT);
    }

    switch (actor->field_A38_local_data)
    {
    case 0:
        if (actor->field_9C_obj.is_end != 0 || status != 0)
        {
            sna_clear_flags1_8004E308(actor, SNA_FLAG1_UNK26);
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) != 0)
            {
                sna_start_anim_8004E1F4(actor, sna_anim_wall_idle_and_c4_80052A5C);
                return;
            }
            sna_start_anim_8004E1F4(actor, dword_8009EEA4[actor->field_A26_stance]);
            return;
        }
        return;
    case 1:
        if (actor->field_9C_obj.field_1C != 0 || status != 0)
        {
            sna_clear_flags1_8004E308(actor, SNA_FLAG1_UNK26);
            sna_8004E260(actor, 0, 4, 0);
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_ON_WALL) != 0)
            {
                sna_start_anim_8004E1F4(actor, sna_anim_wall_crouch_80052CCC);
                return;
            }
            sna_start_anim_8004E1F4(actor, sna_anim_crouch_800527DC);
            return;
        }
        break;
    case 2:
        actor->field_A60.vy = actor->control.levels[0] + 150;
        if (time >= 19)
        {
            time2 = 40 - time;
            if (time2 == 0 || status != 0)
            {
                sna_clear_flags1_8004E308(actor, SNA_FLAG1_UNK26);
                sna_start_anim_8004E1F4(actor, sna_anim_duct_move_80054424);
                return;
            }
            actor->field_A60.vy += GV_RandS(16) * time2;
        }
        break;
    }
}

void sna_anim_scope_80055334(SnaInitWork *param_1, int time)
{
    int action_flag;
    int sVar2;

    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        param_1->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        if (param_1->field_A26_stance == SNA_STANCE_STANDING)
        {
            action_flag = 0x87;
        }
        else
        {
            action_flag = sna_8004EAA8(param_1, param_1->field_A26_stance);
        }

        SetAction_8004E22C(param_1, action_flag, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
    }

    sVar2 = param_1->field_A2A;
    if (sVar2 < dword_800ABBDC)
    {
        sVar2 = dword_800ABBDC;
    }
    else if (dword_800ABBD4 < sVar2)
    {
        sVar2 = dword_800ABBD4;
    }

    param_1->control.turn.vx = sVar2;
}

void sna_anim_jpegcam_800553CC(SnaInitWork *work, int time)
{
    sna_anim_scope_80055334(work, time);
}

void sna_anim_box_idle_800553EC(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_80056A54;
        work->field_9CC_anim_update_fn_1p = sna_fn_800525F8;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND | PLAYER_SQUAT);
        work->field_A26_stance = SNA_STANCE_STANDING;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_2, 4);
    }
}

void sna_anim_box_move_8005544C(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_80056AD8;
        work->field_9CC_anim_update_fn_1p = sna_fn_800525F8;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        GM_ConfigControlInterp_80026244(&work->control, 4);
    }
}

void sna_anim_box_stop_800554B4(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_800525F8;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_4, 4);
    }

    if (work->field_9C_obj.is_end)
    {
        sna_start_anim_8004E1F4(work, sna_anim_box_idle_800553EC);
    }
}

void sna_anim_dying_80055524(SnaInitWork *work, int time)
{
    UnkSnakeStruct2 *unk2 = &work->field_9E4;

    if (time == 0)
    {
        int f9e6;

        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        sub_8004F338(work);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_PAD_OFF);

        if ((unk2->field_9EC_flags3 & 0x400) == 0) // TODO: make flags enum for flags3
        {
            if ((unk2->field_9EC_flags3 & 0x4000) != 0)
            {
                work->control.field_38 = -2;
                work->control.field_36 = -2;
                work->field_A28 = -2;
            }
            else
            {
                work->control.field_38 = -1;
                work->control.field_36 = -1;
                work->field_A28 = -1;
            }
        }

        sna_set_invuln_8004F2A0(work, 0);
        GetAction(work) = -1;
        SetAction_8004E22C(work, unk2->field_9E4, 4);

        f9e6 = unk2->field_9E6;
        if (f9e6 >= 0)
        {
            work->control.turn.vy = f9e6;
            work->control.rot.vy = f9e6;
        }

        work->field_A38_local_data = -1;
        work->field_A3A = -1;

        if ((unk2->field_9EC_flags3 & 0x1000) == 0)
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX) == 0)
            {
                if ((work->field_9AC & 2) != 0)
                {
                    if ((GM_GameOverTimer_800AB3D4 == 0 && unk2->field_9F2 == 0) ||
                        sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK29) != 0)
                    {
                        work->field_A38_local_data = work->field_9A8_current_item;
                        sub_8004F204(work);
                    }
                    else
                    {
                        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK4000000);
                    }
                }
            }
            else
            {
                work->field_A38_local_data = work->field_9A8_current_item;
                sub_8004F204(work);
            }

            if ((work->field_920_tbl_8009D580 & 0x200) != 0)
            {
                if (GM_GameOverTimer_800AB3D4 != 0 || unk2->field_9F2 != 0)
                {
                    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK4000000);
                }
                else
                {
                    work->field_A3A = work->field_91C_weapon_idx;
                    sub_8004F14C(work);
                }
            }
            else if (work->field_91C_weapon_idx != -1 && GM_CurrentWeaponId == WEAPON_NONE)
            {
                sub_8004F14C(work);
            }
        }

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT);
    }

    if ((unk2->field_9EC_flags3 & 0x200) != 0 && work->control.height < 500)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
    }
    else
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND);
        work->control.turn.vx = 0;
    }

    if ((unk2->field_9EC_flags3 & 2) == 0)
    {
        work->field_A2C = DG_ZeroVector_800AB39C;
    }

    if ((unk2->field_9EC_flags3 & 0x4000) == 0)
    {
        if ((unk2->field_9EC_flags3 & 2) == 0)
        {
            int   level;
            int   new_height;
            short y_pos;

            new_height = (unsigned short)work->field_9C_obj.field_18 - (-unk2->field_9EE + work->control.levels[0]);
            level = work->control.levels[0];
            work->control.height = new_height;
            y_pos = new_height + level;

            work->control.mov.vy = y_pos;
            work->field_9C_obj.objs->world.t[1] = y_pos;

            DG_GetLightMatrix2_8001A5D8(&work->control.mov, &work->field_848_lighting_mtx);
        }
    }
    else
    {
        HZD_VEC vec;
        sub_8004E588(work->control.map->hzd, &work->control.mov, &vec);
        work->control.levels[0] = vec.long_access[0];
        work->control.levels[1] = vec.long_access[1];
    }

    if (work->field_9C_obj.is_end)
    {
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK22);

        if ((unk2->field_9EC_flags3 & 0x20) == 0)
        {
            work->control.skip_flag &= ~CTRL_SKIP_TRAP;
        }

        if ((unk2->field_9EC_flags3 & 0x100) != 0)
        {
            work->field_180.interp = 15;
            work->field_180.field_04_info1.field_14 = 0;
            work->field_9B8_fn_anim = sna_fn_nothing_80053B80;
            work->field_9BC_anim_frame = 0;
            work->field_A3A = 0;
            work->field_A38_local_data = 0;
        }
        else
        {
            int stance;
            int fa38;
            int fa3a;

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND | PLAYER_PREVENT_WEAPON_ITEM_SWITCH |
                                              PLAYER_PAD_OFF);
            sna_clear_invuln_8004F2EC(work);

            stance = unk2->field_9EA;
            fa38 = work->field_A38_local_data;
            fa3a = work->field_A3A;

            if (stance < SNA_STANCE_STANDING)
            {
                if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
                {
                    stance = work->field_A26_stance;
                }
                else
                {
                    stance = SNA_STANCE_UNK;
                }
            }

            if ((unk2->field_9EC_flags3 & 0x1000) != 0)
            {
                sna_start_anim_8004E1F4(work, sna_anim_box_idle_800553EC);
                work->field_A26_stance = SNA_STANCE_STANDING;
            }
            else
            {
                if (stance < SNA_STANCE_UNK)
                {
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
                    {
                        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_INTRUDE);
                        sub_8004ED08(work);
                    }

                    work->field_A26_stance = stance;
                    sna_start_anim_8004E1F4(work, dword_8009EEA4[stance]);
                }
                else
                {
                    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
                    {
                        work->field_A26_stance = SNA_STANCE_GROUND;
                        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_INTRUDE | PLAYER_GROUND);
                        sna_8004EC8C(work);
                    }

                    sna_start_anim_8004E1F4(work, sna_anim_duct_move_80054424);
                }

                if ((unk2->field_9EC_flags3 & 8) == 0)
                {
                    if (fa38 >= 0)
                    {
                        GM_CurrentItemId = fa38;

                        if ((unsigned int)(fa38 - 2) < 3)
                        {
                            work->field_A26_stance = SNA_STANCE_STANDING;
                        }
                    }
                    if (fa3a >= 0)
                    {
                        GM_CurrentWeaponId = fa3a;
                        GM_WeaponChanged_800AB9D8 = 1;

                        if (fa3a == WEAPON_PSG1)
                        {
                            work->field_A26_stance = SNA_STANCE_GROUND;
                        }
                    }
                }
            }
        }
    }
}

// things like "a surveillance camera??" where player control is halted
void sna_anim_mini_cutscene_800559D8(SnaInitWork *work, int time)
{
    SVECTOR vec;

    UnkSnakeStruct2 *pStr = &work->field_9E4;
    int weapon;
    int item;
    int stance;
    unsigned char action;

    short temp_v0;
    short temp_v1_2;
    short temp_v0_2;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = &sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = &sna_fn_nothing_80053B80;

        sub_8004F338(work);

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
        sna_set_invuln_8004F2A0(work, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_GROUND | PLAYER_SQUAT);

        work->field_A00.field_0_ivec.vz = -1;
        work->field_A00.field_0_ivec.vx = GM_PlayerAddress_800AB9F0;
        work->field_A00.field_0_ivec.pad = GM_PlayerAddress_800AB9F0;

        sna_act_unk_helper2_helper2_800605DC(&work->field_A00, work->control.map->hzd, &work->field_9E4.field_9F4);
        temp_v0 = HZD_GetAddress_8005C6C4(work->control.map->hzd, &work->field_9E4.field_9F4,  work->field_A00.field_0_ivec.vy);

        temp_v1_2 = (temp_v0 >> 8) & 0xff;
        temp_v0_2 = temp_v0 & 0xff;

        if ((temp_v1_2 == 0xff) || (temp_v0_2 == 0xff) || (temp_v1_2 != temp_v0_2))
        {
            pStr->field_9EC_flags3 |= 0x200;
        }

        if (pStr->field_9EC_flags3 & 0x200)
        {
            GV_SubVec3(&pStr->field_9F4, &work->control.mov, &vec);
            work->control.turn.vy = GV_VecDir2(&vec);
            work->control.field_38 = -1;
            work->control.field_36 = -1;
            work->field_A28 = -1;
        }

        work->field_A38_local_data = -1;

        if (!(pStr->field_9EC_flags3 & 0x100) && ((GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX)) || (work->field_9AC & 2)))
        {
            work->field_A38_local_data = work->field_9A8_current_item;
            sub_8004F204(work);
        }

        work->field_A3A = -1;

        if (work->field_920_tbl_8009D580 & 0x200)
        {
            work->field_A3A = work->field_91C_weapon_idx;
            sub_8004F14C(work);
        }

        if (pStr->field_9EC_flags3 & 0x100)
        {
            stance = SNA_STANCE_STANDING;
            action = work->field_9B4_action_table->field_18->field_3;
        }
        else if (pStr->field_9EC_flags3 & 1)
        {
            stance = SNA_STANCE_GROUND;
            action = work->field_9B4_action_table->field_4->field_3;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
        }
        else
        {
            stance = SNA_STANCE_STANDING;
            action = work->field_9B4_action_table->field_4->field_0;
        }

        work->field_A26_stance = stance;

        SetAction_8004E22C(work, action, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
    }

    if (!(pStr->field_9EC_flags3 & 0x200))
    {
        work->field_A00.field_0_ivec.vx = GM_PlayerAddress_800AB9F0;
        sna_unk_helper2_helper_8006070C(&work->field_A00, &work->control);
    }

    GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);
    GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);

    if (sna_act_unk_helper2_helper3_80060684(&work->field_A00, &work->control.mov) < pStr->field_9F4.pad)
    {
        sna_clear_invuln_8004F2EC(work);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK22);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);

        if (pStr->field_9EC_flags3 & 0x200)
        {
            work->control.field_38 = 450;
            work->control.field_36 = 450;
            work->field_A28 = 450;
        }

        if (!(pStr->field_9EC_flags3 & 2))
        {
            item = work->field_A38_local_data;
            weapon = work->field_A3A;

            if (item >= 0)
            {
                GM_CurrentItemId = item;

                if ((item == ITEM_C_BOX_A) || (item == ITEM_C_BOX_B) || (item == ITEM_C_BOX_C))
                {
                    work->field_A26_stance = SNA_STANCE_STANDING;
                }
            }

            if (weapon >= 0)
            {
                GM_CurrentWeaponId = weapon;
                GM_WeaponChanged_800AB9D8 = 1;

                if (weapon == WEAPON_PSG1)
                {
                    work->field_A26_stance = SNA_STANCE_GROUND;
                }
                else if (weapon == WEAPON_STINGER)
                {
                    work->field_A26_stance = SNA_STANCE_STANDING;
                }
            }
        }

        if (!(pStr->field_9EC_flags3 & 8))
        {
            work->control.skip_flag &= ~CTRL_SKIP_TRAP;
        }

        if (pStr->field_9EC_flags3 & 1)
        {
            sna_80050440(work);
            sna_clear_flags1_8004E308(work, 4);
        }

        if (pStr->field_9EC_flags3 & 0x100)
        {
            sna_start_anim_8004E1F4(work, &sna_anim_box_stop_800554B4);
        }
        else
        {
            sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
        }

        if (pStr->field_9E8 >= 0)
        {
            work->control.turn.vy = pStr->field_9E8;
        }
    }
}

// similar to above, seems freeze snake and make him look at a certain direction or track something
// triggers on first elevator ride at dock and right before mantis fight to look at meryl
// PERMUTER
static inline void sna_act_unk_helper3_helper_80055DD8(SnaInitWork *work, UnkSnakeStruct2 *pStr)
{
  SnaInitWork *work2;
  char new_var;
  int action;
  int field_9E4;
  work2 = work;
  action = work->field_9C_obj.action_flag;
  if (!(((action != work->field_9B4_action_table->field_8->field_0) || work->field_9C_obj.is_end) && ((action != work->field_9B4_action_table->field_8->field_2) || work2->field_9C_obj.is_end)))
  {
      pStr->field_9E4 = 1;
  } else {
    work2 = work;
    if (((((action == work->field_9B4_action_table->field_C->field_6) && (work->field_9C_obj.is_end == 0)) || ((action == work->field_9B4_action_table->field_C->field_7) && (work2->field_9C_obj.is_end == 0))) || ((action == work->field_9B4_action_table->field_C->field_2) && work->field_9C_obj.is_end)) || ((action == work->field_9B4_action_table->field_C->field_3) && work2->field_9C_obj.is_end))
    {
      if ((action == work->field_9B4_action_table->field_C->field_2) && work->field_9C_obj.is_end)
      {
        SetAction_8004E22C(work, 71, 4);
      }
      if ((action == work->field_9B4_action_table->field_C->field_3) && work->field_9C_obj.is_end)
      {
        SetAction_8004E22C(work, 72, 4);
      }
          field_9E4 = 2;

    }
    else
      if ((((action == work->field_9B4_action_table->field_C->field_4) || (action == work->field_9B4_action_table->field_C->field_5)) || (action == work->field_9B4_action_table->field_C->field_A)) || (action == work->field_9B4_action_table->field_C->field_B))
    {
      field_9E4 = 3;
    }
    else
      if (((action == work->field_9B4_action_table->field_C->field_2) && (work->field_9C_obj.is_end == 0)) || ((action == (new_var = work->field_9B4_action_table->field_C->field_3)) && (work->field_9C_obj.is_end == 0)))
    {
      field_9E4 = 4;
    }
    else
    {
      field_9E4 = 0;
    }
    pStr->field_9E4 = field_9E4;
  }
}

static inline void sna_act_unk_helper3_helper2_80055DD8(SnaInitWork *work)
{
    switch (work->field_9E4.field_9EA)
    {
    case 0:
        switch (work->field_A26_stance)
        {
        case SNA_STANCE_STANDING:
            if (++work->field_9E4.field_9EE >= 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_9E4.field_9E4 = 6;
            }
            break;

        case SNA_STANCE_CROUCH:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_0, 4);

            if (++work->field_9E4.field_9EE == 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_9E4.field_9E4 = 6;
            }

            break;

        case SNA_STANCE_GROUND:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_2, 4);

            if (work->field_9C_obj.is_end != 0)
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_0, 4);
                work->field_9E4.field_9E4 = 6;
            }
            break;
        }
        break;

    case 1:
        switch (work->field_A26_stance)
        {
        case SNA_STANCE_STANDING:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_2, 4);

            if (++work->field_9E4.field_9EE == 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_9E4.field_9E4 = 6;
            }
            break;

        case SNA_STANCE_CROUCH:
            if (++work->field_9E4.field_9EE == 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_9E4.field_9E4 = 6;
            }
            break;

        case SNA_STANCE_GROUND:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_2, 4);

            if (work->field_9C_obj.is_end != 0)
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_2, 4);
                work->field_A26_stance = SNA_STANCE_STANDING;
            }
            break;
        }
        break;

    case 2:
        switch (work->field_A26_stance)
        {
        case SNA_STANCE_STANDING:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_2, 4);

            if (++work->field_9E4.field_9EE == 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_A26_stance = SNA_STANCE_CROUCH;
            }
            break;

        case SNA_STANCE_CROUCH:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_0, 4);

            if (work->field_9C_obj.is_end != 0)
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);
                work->field_9E4.field_9E4 = 6;
            }
            break;

        case SNA_STANCE_GROUND:
            if (++work->field_9E4.field_9EE == 4)
            {
                work->field_9E4.field_9EE = 0;
                work->field_9E4.field_9E4 = 6;
            }
        }
        break;
    }
}

void sna_act_unk_helper3_80055DD8(SnaInitWork *work, int time)
{
    UnkSnakeStruct2 *pStr;
    int              height;
    int              stance;
    int              action_flag;
    int              item;
    int              weapon;

    pStr = &work->field_9E4;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = &sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = &sna_fn_nothing_80053B80;

        sub_8004F338(work);

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_PAD_OFF);
        sna_set_invuln_8004F2A0(work, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT | PLAYER_GROUND);

        work->field_A38_local_data = ITEM_NONE;

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX) || (work->field_9AC & 2))
        {
            work->field_A38_local_data = work->field_9A8_current_item;
            sub_8004F204(work);
        }

        work->field_A3A = WEAPON_NONE;

        if (work->field_920_tbl_8009D580 & 0x200)
        {
            work->field_A3A = work->field_91C_weapon_idx;
            sub_8004F14C(work);
        }

        if (pStr->field_9EA != 2)
        {
            work->control.turn.vx = 0;
        }

        sna_act_unk_helper3_helper_80055DD8(work, pStr);
    }

    height = work->control.height;
    stance = pStr->field_9EA;

    switch (stance)
    {
    case 0:
        if (height > 500)
        {
            work->field_A26_stance = SNA_STANCE_STANDING;
        }
        break;

    case 1:
        if (height < 500)
        {
            work->field_A26_stance = stance;
        }
        break;

    case 2:
        if (height < 500)
        {
            work->field_A26_stance = stance;
        }
        break;
    }

    switch(pStr->field_9E4)
    {
    case 0:
        SetAction_8004E22C(work, sna_8004EAA8(work, work->field_A26_stance), 4);
        pStr->field_9E4 = 5;
        break;

    case 1:
        if (work->field_9C_obj.is_end != 0)
        {
            SetAction_8004E22C(work, sna_8004EAA8(work, work->field_A26_stance), 4);
            pStr->field_9E4 = 5;
        }
        break;

    case 2:
        if (work->field_9C_obj.is_end != 0)
        {
            SetAction_8004E22C(work, sna_8004EAA8(work, 0), 4);
            work->field_A26_stance = 0;
            pStr->field_9E4 = 5;
        }
        break;

    case 3:
        if (work->field_A54.prone_bool_thing == 1)
        {
            action_flag = work->field_9B4_action_table->field_C->field_6;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_C->field_7;
        }

        work->field_A54.prone_bool_thing = 0;
        SetAction_8004E22C(work, action_flag, 4);
        pStr->field_9E4 = 2;
        break;

    case 4:
        if (work->field_9C_obj.is_end != 0)
        {
            if (work->field_A54.prone_bool_thing == 1)
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_C->field_6, 4);
            }
            else
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_C->field_7, 4);
            }

            pStr->field_9E4 = 2;
        }
        break;

    case 5:
        sna_act_unk_helper3_helper2_80055DD8(work);
        break;

    case 6:
        work->field_A26_stance = pStr->field_9EA;

        if (work->field_A26_stance == SNA_STANCE_CROUCH)
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_SQUAT);
        }
        else if (work->field_A26_stance == SNA_STANCE_GROUND)
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
        }

        sna_clear_invuln_8004F2EC(work);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_set_flags1_8004E2F4(work, 0x200000);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_PAD_OFF);

        if (!(pStr->field_9EC_flags3 & 0x2))
        {
            item = work->field_A38_local_data;
            weapon = work->field_A3A;

            if (item >= 0)
            {
                GM_CurrentItemId = item;

                if (item == ITEM_C_BOX_A || item == ITEM_C_BOX_B || item == ITEM_C_BOX_C)
                {
                    work->field_A26_stance = SNA_STANCE_STANDING;
                }
            }

            if (weapon >= 0)
            {
                GM_CurrentWeaponId = weapon;
                GM_WeaponChanged_800AB9D8 = 1;

                if (weapon == WEAPON_PSG1)
                {
                    work->field_A26_stance = SNA_STANCE_GROUND;
                }
                else if (weapon == WEAPON_STINGER)
                {
                    work->field_A26_stance = SNA_STANCE_STANDING;
                }
            }
        }

        if (!(pStr->field_9EC_flags3 & 0x8))
        {
            work->control.skip_flag &= ~CTRL_SKIP_TRAP;
        }

        sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);

        if (pStr->field_9E8 >= 0)
        {
            work->control.turn.vy = pStr->field_9E8;
        }
        break;
    }
}

void sna_act_helper3_helper_80056650(SnaInitWork *work, int time)
{
    int            result;
    int            footstepsFrame; // guessed

    if (time == 0)
    {
        int *status = &GM_GameStatus_800AB3CC;

        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        *status |= STATE_PADRELEASE;

        sub_8004F338(work);
        work->control.skip_flag &= ~CTRL_SKIP_TRAP;
        sna_set_invuln_8004F2A0(work, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT | PLAYER_GROUND);
        sub_8004F14C(work);
        sub_8004F204(work);
        work->field_A26_stance = 0;
        SetAction_8004E22C(work, 3, 1);
    }

    if (!work->field_908_weapon_actor)
    {
        GV_ACT *timerBomb;
        timerBomb = NewTimerBomb_80066ACC(&work->control, &work->field_9C_obj, 4,
                                           &work->field_914_trigger, 1);
        work->field_908_weapon_actor = timerBomb;
        work->field_924 = 0;
        SetAction_8004E22C(work, 0x3c, 4);

        if (!work->field_908_weapon_actor)
        {
            return;
        }
    }

    result = 1;
    footstepsFrame = work->field_180.field_04_info1.field_2_footstepsFrame;
    switch (work->field_924)
    {
    case 0:
        if (EndMotion(work))
        {
            SetAction_8004E22C(work, 3, 1);
            work->field_924 = 1;
        }
        break;
    case 1:
        SetAction_8004E22C(work, 0x32, 1);
        work->field_924 = 2;
        break;
    case 2:
        if (footstepsFrame == 6)
        {
            result = 3;
            work->field_924 = 3;
        }
        break;
    case 3:
        result = 0;

        if (EndMotion(work))
        {
            sna_clear_invuln_8004F2EC(work);
            GM_GameStatus_800AB3CC &= ~STATE_PADRELEASE;
            GV_DestroyActorQuick(work->field_908_weapon_actor);
            work->field_908_weapon_actor = NULL;
            work->field_924 = 0;
            work->field_9E4.field_9F0 = 0;
            sna_set_flags1_8004E2F4(work, 0x200000);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        }
        break;
    }

    work->field_914_trigger = result;
}


void sub_8005684C(SnaInitWork *work)
{
    int y;

    if ((work->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_RIGHT)) == 0)
    {
        return;
    }

    y = work->control.turn.vy;
    if ((work->field_9B0_pad_ptr->status & PAD_LEFT) != 0)
    {
        y += 32;
    }
    else
    {
        y -= 32;
    }
    work->control.turn.vy = y;
}

void sub_8005688C(SnaInitWork *work, int time)
{
    int action_flag; // $a1

    if ((work->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
    {
        if ((work->field_9B0_pad_ptr->status & PAD_UP) != 0)
        {
            action_flag = work->field_9B4_action_table->field_4->field_3;
        }
        else
        {
            action_flag = work->field_9B4_action_table->field_4->field_4;
        }
        SetAction_8004E22C(work, action_flag, 4);
        sna_start_anim_8004E1F4(work, sna_anim_duct_idle_80054488);
    }
    else
    {
        sub_8005684C(work);
    }
}

void sub_80056928(SnaInitWork *param_1, int time)
{
    char bVar1;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) == 0)
    {
        sna_start_anim_8004E1F4(param_1, sna_anim_enter_duct_80053E9C);
        sna_set_invuln_8004F2A0(param_1, 0);
    }
    else
    {
        if ((param_1->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) == 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(param_1, sna_anim_duct_move_80054424);
            SetAction_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_3, 4);
        }
        else
        {
            if ((param_1->field_9B0_pad_ptr->status & PAD_UP) != 0)
            {
                bVar1 = param_1->field_9B4_action_table->field_4->field_3;
            }
            else
            {
                bVar1 = param_1->field_9B4_action_table->field_4->field_4;
            }

            SetAction_8004E22C(param_1, bVar1, 4);
            sub_8005684C(param_1);
        }
    }
}

void sna_knockdown_check_getup_80056A1C(SnaInitWork *work, int time)
{
    if (work->field_9B0_pad_ptr->press)
    {
        sna_knockdown_getup_80050668(work);
    }
}

void sna_80056A54(SnaInitWork *work, int time)
{
    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_start_anim_8004E1F4(work, sna_anim_box_move_8005544C);
    }
}

void sna_fn_80056AD8(SnaInitWork *work, int time)
{
    if (gSnaMoveDir_800ABBA4 < 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, sna_anim_box_stop_800554B4);
    }
    else
    {
        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        work->control.turn.vy = (short)gSnaMoveDir_800ABBA4;
    }
}

void sna_80051A10(SnaInitWork *work, SVECTOR *pPos, SVECTOR *pOut, SVECTOR *pVec)
{
    MATRIX rot;
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR vec3;
    SVECTOR vec4;

    int len;

    ReadRotMatrix(&rot);
    DG_SetPos2_8001BC8C(pPos, &work->control.rot);
    DG_PutVector_8001BE48(pVec, pVec, 1);
    SetRotMatrix(&rot);

    vec = *pPos;
    vec2 = *pVec;

    if (sub_8004E51C(&vec, work->control.map->hzd, 15, 1) < 0)
    {
        vec2 = *pVec;
    }

    GV_SubVec3(&vec2, pPos, &vec3);
    len = GV_VecLen3(&vec3);

    if ((len - work->field_A28) <= 0)
    {
        vec3 = *pPos;
    }
    else
    {
        GV_LenVec3(&vec3, &vec4, len, len - work->field_A28);
        GV_AddVec3(pPos, &vec4, &vec3);
    }

    *pOut = vec3;
}

int sna_80051BA4(SnaInitWork *work)
{
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR vec3;

    GV_PAD *pPad = work->field_9B0_pad_ptr;
    unsigned short press = pPad->press;
    unsigned short release = pPad->release;

    if (pPad->status & (PAD_R1 | PAD_L1))
    {
        if (press & PAD_R1)
        {
            work->field_A56 = 8;
        }

        if (press & PAD_L1)
        {
            work->field_A56 = 4;
        }

        if (release & PAD_R1)
        {
            work->field_A56 = 4;
        }

        if (release & PAD_L1)
        {
            work->field_A56 = 8;
        }

        vec2 = vec = DG_ZeroVector_800AB39C;
        vec2.vx = 1280;
        vec.vx = -1280;
        vec3 = work->field_A60;

        sna_80051A10(work, &vec3, &work->field_A3C, &vec2);
        sna_80051A10(work, &vec3, &work->field_A44, &vec);

        if (!sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK16))
        {
            work->field_A58 = 8;
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK16);
        }
        else if (work->field_A56 & 4)
        {
            work->field_A60 = work->field_A3C;

        }
        else if (work->field_A56 & 8)
        {
            work->field_A60 = work->field_A44;
        }

        return 1;
    }

    if (work->field_A58 > 0)
    {
        if (--work->field_A58 == 0)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK16);
            return 0;
        }

        return 1;
    }

    return 0;
}

void sna_80051DA0(SnaInitWork *work)
{
    unsigned int status = work->field_9B0_pad_ptr->status;
    unsigned char ldy = work->field_9B0_pad_ptr->left_dy;
    short *temp_s4;
    int var_s1;
    int var_s2;
    int var_s0;
    int temp_v0;
    int temp_a1;
    short var_a0;
    short var_a2;

    // status is passed using the wrong type here
    GM_CheckShukanReverse_8004FBF8((unsigned short *)&status);
    GM_CheckShukanReverseAnalog_8004FC70(&ldy);

    temp_s4 = work->field_9D0;
    var_s2 = temp_s4[4];
    var_s1 = -temp_s4[3];

    if (work->field_9D0[0] == 0)
    {
        if (work->field_A26_stance == SNA_STANCE_GROUND)
        {
            var_s0 = work->field_A2A;
        }
        else
        {
            var_s0 = 0;
        }
    }
    else
    {
        var_s0 = work->control.turn.vx;
    }

    if (work->field_A26_stance == SNA_STANCE_GROUND)
    {
        if (work->field_91C_weapon_idx == WEAPON_PSG1)
        {
            temp_v0 = work->field_A2A;
            var_s1 += temp_v0;
            var_s2 += temp_v0;
        }
        else
        {
            var_s1 += var_s0;
            var_s2 += var_s0;
        }
    }

    if (var_s1 < dword_800ABBDC)
    {
        var_s1 = dword_800ABBDC;
    }

    if (var_s2 > dword_800ABBD4)
    {
        var_s2 = dword_800ABBD4;
    }

    temp_a1 = sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK15);
    var_a2 = 1;
    var_a0 = 1;

    if (status & PAD_UP)
    {
        if (temp_a1 & 0xff)
        {
            var_a0 = 64 - ldy;
            var_a2 = 64;
        }

        var_s0 -= (temp_s4[5] * (var_a0 & 0xff)) / var_a2;
    }
    else if (status & PAD_DOWN)
    {
        if (temp_a1 & 0xff)
        {
            var_a0 = ldy + 64;
            var_a2 = 63;
        }

        var_s0 += (temp_s4[6] * (var_a0 & 0xff)) / var_a2;
    }


    if (var_s0 < var_s1)
    {
        var_s0 = var_s1;
    }

    if (var_s2 < var_s0)
    {
        var_s0 = var_s2;
    }

    work->control.turn.vx = var_s0;
}

void sna_80051FD0(SnaInitWork *work)
{
    int          iVar1;
    ushort       uVar2;
    unsigned int uVar3;
    short        sVar4;
    short        sVar5;
    int          iVar6;
    short     *short_arr;

    short_arr = work->field_9D0;
    uVar2 = work->field_9B0_pad_ptr->status;
    if ((uVar2 & (PAD_LEFT | PAD_RIGHT)) != 0)
    {
        iVar1 = work->control.turn.vy;
        uVar3 = sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK15);
        sVar4 = 1;
        sVar5 = 1;
        if (uVar2 & PAD_LEFT)
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x40;
                sVar5 = 0x40 - (*((unsigned char *)((short *)work->field_9B0_pad_ptr + 7)));
            }
            iVar6 = ((int)short_arr[8]) * (sVar5 & 0xff);
            iVar1 += iVar6 / sVar4;
        }
        else
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x3f;
                sVar5 = (*((unsigned char *)((short *)work->field_9B0_pad_ptr + 7))) + 0x40;
            }
            iVar6 = ((int)short_arr[7]) * (sVar5 & 0xff);
            iVar1 -= iVar6 / sVar4;
        }
        work->control.turn.vy = iVar1;
    }
}

void sna_fn_80052120(SnaInitWork *work, int time)
{
    unsigned short press;
    int            sound;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) != 0)
    {
        sna_8004EC00(work);
        sna_set_invuln_8004F2A0(work, 0);
        sna_start_anim_8004E1F4(work, sna_anim_enter_duct_80053E9C);
    }
    else
    {
        press = work->field_9B0_pad_ptr->press;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        SetAction_8004E22C(work, sna_8004EAA8(work, (int)work->field_A26_stance), 4);

        if ((work->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            sna_8004EC00(work);
            sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
        }
        else
        {
            if (sna_80051BA4(work))
            {
                return;
            }

            sna_80051DA0(work);
            sna_80051FD0(work);

            if ((press & PAD_CROSS) != 0)
            {
                switch (work->field_A26_stance)
                {
                case 0:
                    sna_start_anim_8004E1F4(work, sna_anim_crouch_800527DC);
                    break;
                case 2:
                    if (sna_8004E808(work, 1, 0, -0x26e, 0x5dc) != 0)
                    {
                        return;
                    }
                default:
                    if (sna_8004E808(work, 0, 0, 0, 0x5dc) != 0)
                    {
                        return;
                    }

                    work->control.turn.vy = work->control.rot.vy;
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT | PLAYER_GROUND);

                    sound = SE_CHANGE_STANCE;
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) != 0)
                    {
                        sound = 183;
                    }

                    GM_SeSet_80032858(&work->control.mov, sound);
                    sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
                    break;
                }
            }
        }
    }
}

void sub_8005230C(SnaInitWork *work, int time)
{
    int            action;
    unsigned short status;
    unsigned short press;

    status = work->field_9B0_pad_ptr->status;
    press = work->field_9B0_pad_ptr->press;

    if ((status & PAD_TRIANGLE) == 0)
    {
        sna_8004EC00(work);
        work->field_A38_local_data = 2;
    }
    else
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING) != 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);

            if (work->field_A26_stance == SNA_STANCE_STANDING)
            {
                action = work->field_9B4_action_table->field_0->field_4;
            }
            else
            {
                action = work->field_9B4_action_table->field_0->field_5;
            }

            SetAction_8004E22C(work, action, 4);
        }
        if (((press & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) != 0) ||
            ((status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) == 0))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_ON_WALL);
            work->field_A28 = 0x1c2;
            sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
            GM_ExitBehindCamera_80030AEC();
        }

        if (!sna_80051BA4(work) && (press & PAD_CROSS) != 0)
        {
            if (work->field_A26_stance == SNA_STANCE_STANDING)
            {
                sna_start_anim_8004E1F4(work, sna_anim_wall_crouch_80052CCC);
            }
            else
            {
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT);
                sna_start_anim_8004E1F4(work, sna_anim_wall_idle_and_c4_80052A5C);
            }
        }
    }
}

void sub_80052468(SnaInitWork *work, int time)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) == 0)
    {
        work->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH |
                                          PLAYER_FIRST_PERSON_CAN_LR_PEEK | PLAYER_FIRST_PERSON);
        sna_set_invuln_8004F2A0(work, 0);
        sna_start_anim_8004E1F4(work, sna_anim_enter_duct_80053E9C);
    }
    else
    {
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_3, 4);

        if ((work->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            work->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH |
                                              PLAYER_FIRST_PERSON_CAN_LR_PEEK | PLAYER_FIRST_PERSON);
            sna_start_anim_8004E1F4(work, sna_anim_duct_move_80054424);
        }

        sna_80051DA0(work);
        sna_80051FD0(work);
    }
}

void sna_fn_80052540(SnaInitWork *work, int time)
{
    if ((work->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        sna_8004EC00(work);
    }

    if (work->field_9B8_fn_anim == sna_anim_knockdown_idle_80054930 &&
        ((work->field_9B0_pad_ptr->press & ~PAD_TRIANGLE) != 0))
    {
        sna_knockdown_getup_80050668(work);
    }

    gUnkCameraStruct_800B77B8.eye.vy += 320;
    sna_8004EE28(work);
}

void sna_fn_800525F8(SnaInitWork *work, int time)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
    if (work->field_9B8_fn_anim != sna_anim_box_idle_800553EC)
    {
        if (work->field_9C_obj.is_end)
        {
            SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_2, 4);
        }
    }

    if (!(work->field_9B0_pad_ptr->status & PAD_TRIANGLE))
    {
        sna_8004EC00(work);
        work->control.turn.vx = 0;
    }
    else
    {
        sna_80051DA0(work);
        sna_80051FD0(work);
    }
}

void snake_vr_sna_init_800565C8(SnaInitWork *work, int time)
{
    if (!(work->field_9B0_pad_ptr->status & PAD_TRIANGLE))
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
        {
            work->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH
                                              | PLAYER_FIRST_PERSON_CAN_LR_PEEK
                                              | PLAYER_FIRST_PERSON);
        }
        else
        {
            sna_8004EC00(work);
        }
    }

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE))
    {
        sna_8004EE28(work);
    }
}

void sna_anim_shoot_weapon_80056B88(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_anim_shoot_weapon_helper_80057590;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_1, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
    }
}

void sna_anim_rungun_begin_80056BDC(SnaInitWork *param_1, int time)
{
    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_anim_rungun_begin_helper_800577B4;
        param_1->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        SetAction_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_anim_rungun_80056C3C(SnaInitWork *param_1, int time)
{
    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_anim_rungun_helper_80057844;
        param_1->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        SetAction_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_0, 4);
    }
}

void sna_anim_nikita_80056C9C(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_4, 4);
        sna_8004E260(work, 0, 4, 0);

        if (*work->field_918_n_bullets == 0)
        {
            work->field_A38_local_data = 1;
        }
    }

    if (EndMotion(work))
    {
        SetAction_8004E22C(work, SET, 4);
    }

    if (work->field_A38_local_data != 0 || time >= 24)
    {
        if (work->field_A38_local_data != 0 || time == 24)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_ITEM_SWITCH);
        }

        if (dword_8009F46C[0] == 0)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        }
    }
}

static inline int sna_anim_psg1_helper_80056DDC(void)
{
    return 1;
}

void sna_anim_psg1_80056DDC(SnaInitWork *work, int time)
{
    MATRIX rotation;

    if (time == 0)
    {
        work->field_A44.pad = 0;
        work->field_A52 = 0;

        work->field_9C8_anim_update_fn_3p = &sna_anim_psg1_helper_80057FD4;
        work->field_9CC_anim_update_fn_1p = &sna_anim_psg1_helper_80057FD4;

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_set_invuln_8004F2A0(work, 0);

        GM_Camera_800B77E8.first_person = 0;
        work->field_A20 = sna_anim_psg1_helper_80056DDC();

        switch (work->field_A26_stance)
        {
        case 0:
            SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_2, 4);
            work->field_A2C.vy = -128;
            work->field_A3A = 0;
            break;

        case 1:
            work->field_A3A = 1;
            break;

        case 2:
            work->field_A3A = 3;
            break;
        }
    }

    if (work->field_A3A < 3)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
    }

    switch (work->field_A3A)
    {
    case 0:
        if (time == 4)
        {
            work->field_A3A = 1;
        }

        break;

    case 1:
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_SQUAT);
        work->field_A26_stance = 1;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_8->field_0, 4);
        work->field_A3A = 2;
        work->control.skip_flag |= (CTRL_BOTH_CHECK | CTRL_SKIP_TRAP);
        break;

    case 2:
        if (work->field_798_p_height < 250)
        {
            work->control.skip_flag &= ~CTRL_BOTH_CHECK;
        }

        if (work->field_180.field_04_info1.field_2_footstepsFrame == 7)
        {
            work->control.skip_flag &= ~CTRL_SKIP_TRAP;
        }

        if (EndMotion(work))
        {
            work->field_A3A = 3;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND);
            work->field_A26_stance = 2;
        }

        break;

    case 3:
        sub_8004EB74(work);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_SQUAT);
        sna_clear_invuln_8004F2EC(work);
        work->control.turn.vx = work->field_A2A;
        SetAction_8004E22C(work, SET, 4);
        work->field_A3A = 4;
        break;

    default:
        DG_SetPos_8001BC44(&work->field_9C_obj.objs->objs[4].world);
        DG_MovePos_8001BD20(&svector_800AB7E4);
        ReadRotMatrix(&rotation);

        work->field_A60.vx = rotation.t[0];
        work->field_A60.vy = rotation.t[1];
        work->field_A60.vz = rotation.t[2];

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INVULNERABLE) && (GM_Camera_800B77E8.first_person != 0))
        {
            gUnkCameraStruct_800B77B8.eye.vy += GV_RandU(16) * work->field_A24_invuln_frames;
        }

        break;
    }
}

void sna_anim_stinger_800570C0(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = OP_ShootStinger_80058378;
        work->field_9CC_anim_update_fn_1p = OP_ShootStinger_80058378;
        SetAction_8004E22C(work, SET, 4);
        work->field_A26_stance = SNA_STANCE_STANDING;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_GROUND |
                                          PLAYER_SQUAT);
    }
}

void sna_80057118(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        if (bakudan_count_8009F42C >= 16)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
            GM_SeSet2_80032968(0, 0x3f, SE_BUZZER);
            return;
        }

        work->field_9C8_anim_update_fn_3p = sub_80058644;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_5, 4);
    }

    sub_8004E9D0(work);
}

void sna_800571B8(SnaInitWork *work, int time)
{
    SVECTOR   *vec1;
    TARGET *pGVar3;
    SVECTOR   *vec2;

    vec2 = &work->field_8EC_vec;

    if (time == 0)
    {
        if (bakudan_count_8009F42C >= 16)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
            work->field_8E8_pTarget->damaged &= ~(0x40);
            work->field_8E8_pTarget = NULL;
            return;
        }

        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_6, 4);
        pGVar3 = work->field_8E8_pTarget;
        DG_PutVector_8001BE48(&svector_800AB7EC, vec2, 1);
        GV_SubVec3(&pGVar3->center, vec2, vec2);

        vec2->vx /= 4;
        vec2->vy /= 4;
        vec2->vz /= 4;
    }

    vec1 = &work->control.step;

    if (time < 4)
    {
        GV_AddVec3(vec1, vec2, vec1);
    }

    if (time == 6)
    {
        GM_SeSet_80032858(&work->control.mov, SE_C4_PUT);
        NewBakudan_8006A6CC(work->field_8E8_pTarget->field_20, &svector_800AB7F4, 1, 1, work->field_8E8_pTarget);
        work->field_914_trigger = 5;
        work->field_8E8_pTarget->damaged &= ~(0x40);
        work->field_8E8_pTarget = 0;
    }

    if (EndMotion(work))
    {
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
    }
}

void sna_80057378(SnaInitWork *work, int time)
{
    int action;
    int stance;

    stance = work->field_A26_stance;
    work->control.turn.vy = dword_800ABBA8;

    if (time == 0)
    {
        if (stance == 0)
        {
            action = work->field_9B4_action_table->field_10->field_6;
        }
        else
        {
            action = work->field_9B4_action_table->field_10->field_7;
        }

        sna_8004E260(work, action, 4, 0xffff);
    }

    if ((stance == SNA_STANCE_STANDING && time == 6) || (stance == SNA_STANCE_CROUCH && time == 14))
    {
        work->field_914_trigger = 3;
        GM_BombSeg_800ABBD8 = dword_800ABBB0;
    }

    if (work->field_9C_obj.field_1C != 0 || work->field_9C_obj.field_10 == 0)
    {
        sna_8004E260(work, 0, 4, 0);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK9);
        work->field_9C0 = NULL;
    }
}
void sna_anim_claymore_80057474(SnaInitWork *work, int time)
{
    int              i;
    int              down_count;
    TARGET *targets;

    if (time == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        GM_Target_8002E374(&down_count, &targets);

        if (counter_8009F448 == 8 || down_count == 64)
        {
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
            GM_SeSet2_80032968(0, 63, SE_BUZZER);
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            return;
        }

        work->field_9C8_anim_update_fn_3p = sna_anim_claymore_helper_80058780;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, SET, 4);

        for (i = 0; i < (int)(sizeof(work->field_718) / sizeof(SVECTOR)); i++) // 16
        {
            work->field_718[i] = DG_ZeroVector_800AB39C;
        }

        GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, work->field_718);
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK26);
    }

    sub_8004E9D0(work);
}

static inline int sna_anim_shoot_weapon_helper_helper_80057590(SnaInitWork *work)
{
    if ((work->field_9B4_action_table->field_10->field_3 == 136) ||
        (work->field_90C_pWeaponFn == &sna_80057A90))
    {
        return 0;
    }

    return 1;
}

void sna_anim_shoot_weapon_helper_80057590(SnaInitWork *work, int time)
{
    unsigned short status;
    int diff;

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PREVENT_FIRST_PERSON))
    {
        sna_8004E260(work, 0, 4, 0);
        sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
        return;
    }

    if (gSnaMoveDir_800ABBA4 < 0)
    {
        SetAction_8004E22C(work, work->field_9B4_action_table->field_0->field_1, 4);
        return;
    }

    status = work->field_9B0_pad_ptr->status;

    if ((sub_8004E458(work->control.turn.vy, gSnaMoveDir_800ABBA4) == 3) &&
        sna_anim_shoot_weapon_helper_helper_80057590(work))
    {
        work->field_A54.prone_bool_thing = gSnaMoveDir_800ABBA4;
        sna_start_anim_8004E1F4(work, &sub_80053FAC);
    }
    else if ((status & PAD_CROSS) || (work->field_920_tbl_8009D580 & 8))
    {
        if (work->field_A38_local_data > 0)
        {
            work->field_A38_local_data--;
        }

        if (work->field_A38_local_data == 0)
        {
            diff = GV_DiffDirAbs(work->control.turn.vy, gSnaMoveDir_800ABBA4);
            if (diff > 256)
            {
                work->field_A38_local_data = (diff / 1024) + 1;
            }
            else
            {
                sna_start_anim_8004E1F4(work, &sna_anim_rungun_begin_80056BDC);
            }

            work->control.turn.vy = gSnaMoveDir_800ABBA4;
        }
    }
    else
    {
        sna_8004EF14(work);
    }
}

void sna_anim_rungun_begin_helper_800577B4(SnaInitWork *work, int time)
{
    if (time == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_start_anim_8004E1F4(work, sna_anim_rungun_80056C3C);
    }
    else
    {
        if (work->field_9C_obj.is_end)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(work, sna_anim_shoot_weapon_80056B88);
        }
    }
}

void sna_anim_rungun_helper_80057844(SnaInitWork *work, int time)
{
    int angle;

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PREVENT_FIRST_PERSON))
    {
        sna_8004E260(work, 0, 4, 0);
        sna_start_anim_8004E1F4(work, sna_anim_run_8005292C);
        return;
    }

    if (gSnaMoveDir_800ABBA4 < 0 || (!(work->field_920_tbl_8009D580 & 8) && !(work->field_9B0_pad_ptr->status & PAD_CROSS)))
    {
        if (++work->field_A3A >= 5)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(work, sna_anim_shoot_weapon_80056B88);
            return;
        }
    }
    else
    {
        work->field_A3A = 0;
    }

    if (gSnaMoveDir_800ABBA4 < 0)
    {
        angle = work->control.turn.vy;
    }
    else
    {
        angle = sub_8004E4C0(work, gSnaMoveDir_800ABBA4);
    }

    work->control.turn.vy = angle;
    sub_8004EA50(work, angle);
}

void sna_auto_aim_800579A0(SnaInitWork *work)
{
    int unk;
    int out_x_copy;
    int snake_not_moving;
    int out_x;
    int out_y;
    int diff;

    // loops enemies and finds candidate to aim at, returns angle to auto turn/aim to
    // melee also uses this in a different func
    HomingTarget_2_80032EAC(&work->field_9C_obj.objs->objs[6].world,
                            work->control.rot.vy, // input snake horizontal facing angle
                            &out_y, &out_x, work->control.map->index,
                            work->field_890_autoaim_max_dist,
                            work->field_892_autoaim_min_angle); // min angle to activate auto aim

    // ?
    unk = work->field_718[2].vx;
    diff = unk - out_x;
    if (diff >= 65)
    {
        out_x = unk - 64;
    }
    else if (diff < -64)
    {
        out_x = unk + 64;
    }

    // ?
    out_x_copy = out_x;
    work->field_718[2].vx = out_x;
    work->field_718[6].vx = out_x;
    snake_not_moving = gSnaMoveDir_800ABBA4 < 0;
    work->field_718[7].vx = 3 * out_x_copy / 2; // maybe aim gun/head up/down??

    if (snake_not_moving && out_y >= 0) // if not moving, set snake turn angle
    {
        work->control.turn.vy = out_y;
    }
}

void sna_80057A90(SnaInitWork *work, int time)
{
    int bits;
    int ammo, magSize;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING))
    {
        bits = 0x3fe;
    }
    else
    {
        bits = 0xffff;
    }

    if (time == 0)
    {
        GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, NULL);
        NewAnime_8005DDE0(&work->field_9C_obj.objs->objs[4].world);
        sna_8004E260(work, work->field_9B4_action_table->field_10->field_1, 4, bits);

        ammo = GM_MagazineMax_800ABA2C;
        magSize = GM_Weapons[work->field_91C_weapon_idx];

        if (ammo > 0 && ammo < magSize)
        {
            magSize = ammo;
        }

        GM_MagazineMax_800ABA2C = ammo;
        GM_Magazine_800AB9EC = magSize;
    }

    sna_8004F034(work, bits);

    if (time == 16)
    {
        GM_SeSet_80032858(&work->control.mov, SE_RELOAD);
    }

    if (work->field_9C_obj.field_1C != 0)
    {
        if (!(work->field_9B0_pad_ptr->status & PAD_SQUARE))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_FIRST_PERSON);
            sna_8004E260(work, 0, 4, 0);
            sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
            work->field_90C_pWeaponFn = sna_gun_800540D0;
        }
        else
        {
            work->field_90C_pWeaponFn = sub_80057BF0;
        }

        work->field_910 = 0;
        work->field_926 = 0;
        work->field_924 = 0;
    }
}

void sub_80057BF0(SnaInitWork *work, int time)
{
    int var_s4;
    int temp_s3;
    int var_s2;
    int status;
    int release;
    int trg;

    var_s4 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING) ? 0x3FE : 0xFFFF;
    temp_s3 = work->field_920_tbl_8009D580;
    var_s2 = 0;

    if (time == 0)
    {
        sna_8004E260(work, SET, 4, var_s4);
        GM_SeSet_80032858(&work->control.mov, SE_READY_WEAPON);

        var_s2 = work->field_A38_local_data;
        work->field_924 = 0;

        if (temp_s3 & 2)
        {
            GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, work->field_718);
        }
    }

    sna_8004F034(work, var_s4);

    if ( (GM_Magazine_800AB9EC == 0) && (GM_MagazineMax_800ABA2C != 0) && (GM_Weapons[work->field_91C_weapon_idx] > 0) )
    {
        work->field_90C_pWeaponFn = &sna_80057A90;
        work->field_910 = 0;
        work->field_926 = 0;
        work->field_924 = 0;
        return;
    }

    if ( (temp_s3 & 2) != 0 )
    {
        sna_auto_aim_800579A0(work);
    }

    status = work->field_9B0_pad_ptr->status;
    release = work->field_9B0_pad_ptr->release;

    trg = 1;

    if ( (temp_s3 & 1) ? (status & PAD_SQUARE) : (release & PAD_SQUARE) )
    {
        var_s2 = 1;
    }

    if ( (GM_GameStatus_800AB3CC & STATE_PADRELEASE) ||
         GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) ||
         (DG_UnDrawFrameCount_800AB380 > 0) )
    {
        var_s2 = 0;
    }

    if ( var_s2 != 0 )
    {
        trg |= 2;
    }

    work->field_914_trigger = trg;

    switch ( work->field_924 )
    {
    case 0:
        if ( trg & 2 )
        {
            if ( *work->field_918_n_bullets == 0 )
            {
                DispEmpty(work);

                if ( temp_s3 & 1 )
                {
                    work->field_924 = 2;
                    break;
                }
            }

            work->field_924 = 1;
            sna_8004E260(work, work->field_9B4_action_table->field_10->field_4, 2, var_s4);

            if ( temp_s3 & 0x80 )
            {
                GM_ClearPlayerStatusFlag_8004E2D4(0x810);

                if ( dword_8009F470 != 0 )
                {
                    GM_SeSet2_80032968(0, 63, SE_BUZZER);
                    work->field_914_trigger &= ~2;
                    sna_8004E260(work, 0, 4, 0);
                    sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
                }
                else
                {
                    sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
                    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PREVENT_ITEM_SWITCH);
                    sna_start_anim_8004E1F4(work, &sna_anim_nikita_80056C9C);
                }

                return;
            }
        }
        break;

    case 1:
        if ( work->field_9C_obj.field_1C != 0 )
        {
            if ( (temp_s3 & 1) == 0 )
            {
                work->field_924 = 0;
                sna_8004E260(work, SET, 2, var_s4);
            }
            else if ( *work->field_918_n_bullets == 0 )
            {
                DispEmpty(work);
                work->field_924 = 2;
                sna_8004E260(work, SET, 2, var_s4);
            }
        }
        break;

    case 2:
        work->field_914_trigger = trg & ~2;
        break;
    }

    if ( (status & 0x80) == 0 )
    {
        if ( (++work->field_926 > 4) || (temp_s3 & 1) )
        {
            work->field_90C_pWeaponFn = &sna_gun_800540D0;
            work->field_910 = 0;
            work->field_926 = 0;
            work->field_924 = 0;

            GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, NULL);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_FIRST_PERSON);
        }
    }
    else
    {
        work->field_926 = 0;
    }
}

void sna_anim_psg1_helper_80057FD4(SnaInitWork* work, int time)
{
    int trg;
    int ammo;
    int mag_size;
    short dpad_status;
    int val;
    short *pShortArr;
    int rx, ry;

    if ( work->field_A3A < 3 )
    {
        return;
    }

    trg = 1;

    if ( work->field_A34 != 0 )
    {
        if ( (--work->field_A34 & 0xFF) != 4 )
        {
            return;
        }

        GM_SeSet_80032858(&work->control.mov, SE_RELOAD);

        ammo = GM_Weapons[WEAPON_PSG1];
        mag_size = 5;

        if ( mag_size < ammo )
        {
            ammo = mag_size;
        }

        GM_MagazineMax_800ABA2C = mag_size;
        GM_Magazine_800AB9EC = ammo;
    }

    if ( (GM_Magazine_800AB9EC == 0) && (GM_Weapons[WEAPON_PSG1] > 0) )
    {
        work->field_A34 = 24;
        return;
    }

    if ( (work->field_9B0_pad_ptr->release & PAD_SQUARE) &&
         !(GM_GameStatus_800AB3CC & STATE_PADRELEASE) &&
         !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) &&
         (DG_UnDrawFrameCount_800AB380 == 0) )
    {
        trg |= 2;

        if ( *work->field_918_n_bullets == 0 )
        {
            DispEmpty(work);
        }
    }

    work->field_914_trigger = trg;

    dpad_status = work->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP);
    if ( dpad_status != 0 )
    {
        val = 1;

        if ( work->field_A52 == dpad_status )
        {
            if ( !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK15) )
            {
                if ( work->field_A44.pad < 10000 )
                {
                    work->field_A44.pad++;
                }

                if ( work->field_A44.pad > 16 )
                {
                    val = 3;
                }
            }
            else
            {
                val = 3;
            }
        }
        else
        {
            work->field_A44.pad = 0;
            work->field_A52 = dpad_status;
        }

        pShortArr = work->field_9D0;
        pShortArr[0] = 1;
        pShortArr[3] = 0x78;
        pShortArr[4] = 0x78;
        pShortArr[5] = val;
        pShortArr[6] = val;
        pShortArr[7] = val;
        pShortArr[8] = val;

        sna_80051DA0(work);
        sna_80051FD0(work);
        sna_8004EB14(work);
    }
    else
    {
        work->field_A52 = 0;
        work->field_A44.pad = 0;
    }

    rx = work->field_9C_obj.objs->rots[0].vx;
    ry = work->field_9C_obj.objs->rots[0].vy;

    if ( GetAction(work) == 0x7A )
    {
        work->control.turn.vy += ry - work->field_924;
        work->control.turn.vx += rx - work->field_926;
    }

    work->field_924 = ry;
    work->field_926 = rx;

    if ( GM_TranquilizerTimer > 0 )
    {
        if ( (time % 48) == 0 )
        {
            NewPadVibration_8005D58C(dword_8009EF20, 2);
            work->field_A35_vibtime2 = 2;
        }
        else if ( (work->field_A35_vibtime2 != 0) &&
                  (--work->field_A35_vibtime2 == 0) )
        {
            GM_SeSet2_80032968(0, 63, SE_HEARTBEAT);
        }
    }
    else if ( (time & 0x1F) == 0 )
    {
        NewPadVibration_8005D58C(dword_8009EF1C, 2);
        work->field_A35_vibtime2 = 2;
    }
    else if ( (work->field_A35_vibtime2 > 0) &&
              (--work->field_A35_vibtime2 == 0) )
    {
        GM_SeSet2_80032968(0, 63, SE_HEARTBEAT);
    }

    if ( GetAction(work) == SET )
    {
        if ( ++work->field_A38_local_data == RIFLE_TEBURE_TIME )
        {
            work->field_A38_local_data = 0;

            if ( GM_TranquilizerTimer <= 0 )
            {
                GM_StatusEvent &= ~EV_Tranquilizer;
                SetAction_8004E22C(work, TEBURE, 4);
            }
        }
    }
    else if ( EndMotion(work) ||
              (GM_StatusEvent & EV_Tranquilizer) )
    {
        SetAction_8004E22C(work, SET, 4);
    }
}

void OP_ShootStinger_80058378(SnaInitWork *work, int time)
{
    short *ws; // WATCH_SET *ws
    int    trg;

    trg = 1; // 1 = WEAPON_TAKE

    if ((work->field_9B0_pad_ptr->release & PAD_SQUARE) &&
        !(GM_GameStatus_800AB3CC & STATE_PADRELEASE) &&
        !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF))
    {
        if ( *work->field_918_n_bullets > 0 )
        {
            trg |= 2; // |= WEAPON_TRIG
        }
        else
        {
            GM_SeSet_80032858(&work->control.mov, SE_KARASHT);
            DispEmpty(work);
        }
    }

    work->field_914_trigger = trg;

    if ( work->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP) )
    {
        ws = work->field_9D0;
        ws[0] = 1; // ws->type = WATCH_TYPE_STILL
        ws[3] = 0x200;
        ws[4] = 0x200;
        ws[5] = 0x20;
        ws[6] = 0x20;
        ws[7] = 0x20;
        ws[8] = 0x20;

        sna_80051DA0(work);
        sna_80051FD0(work);
        sna_8004EB14(work);
    }
}

void sna_anim_grenade_80058470(SnaInitWork *work, int time)
{
    int bits;
    int uVar2;
    int res;

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_MOVING) )
    {
        bits = 0x3fe;
    }
    else
    {
        bits = 0xffff;
    }

    if (time == 0)
    {
        sna_8004E260(work, SET, 4, bits);
        work->field_924 = 0;
        GM_SeSet_80032858(&(work->control).mov, SE_PINNUKI);
    }

    sna_8004F034(work, bits);
    res = 1;

    uVar2 = work->field_180.field_1C_info2.field_2_footstepsFrame;

    switch (work->field_924)
    {
    case 0:
        if (work->field_9C_obj.field_1C != 0)
        {
            sna_8004E260(work, work->field_9B4_action_table->field_0->field_0, 1, bits);
            work->field_924 = 1;
        }

        break;
    case 1:
        if (!(work->field_9B0_pad_ptr->status & PAD_SQUARE) && (DG_UnDrawFrameCount_800AB380 == 0))
        {
            sna_8004E260(work, work->field_9B4_action_table->field_10->field_4, 1, bits);
            work->field_924 = 2;
        }

        break;
    case 2:
        if (uVar2 == 7)
        {
            res = 3;
            work->field_924 = 3;
        }

        break;
    case 3:
        res = 0;

        if ((uVar2 > 11) && (work->field_9B0_pad_ptr->status & PAD_SQUARE))
        {
            work->field_910 = 0;
            return;
        }


        if (work->field_9C_obj.field_1C != 0)
        {
            sna_8004E260(work, 0, 4, 0);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_PREVENT_FIRST_PERSON | PLAYER_PREVENT_ITEM_SWITCH | PLAYER_PREVENT_WEAPON_SWITCH);
        }

        break;
    }

    work->field_914_trigger = res;
}

void sub_80058644(SnaInitWork *work, int time)
{
    int iVar1;

    work->field_914_trigger = 1;

    if (time >= 10)
    {
        iVar1 = (int)work->field_A38_local_data;
        if (iVar1 == 0)
        {
            sub_8004EEB0(work);
        }

        if ((work->field_9B0_pad_ptr->status & PAD_SQUARE) == 0 && iVar1 == 0 && DG_UnDrawFrameCount_800AB380 == 0)
        {
            iVar1 = sub_8004E5E8(work, 0x80);
            if (iVar1 == 1)
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_8, 1);
                work->field_A38_local_data = 1;
                work->field_914_trigger |= 2;
            }
            else if (iVar1 == 2)
            {
                GM_SeSet2_80032968(0, 0x3f, SE_BUZZER);
            }
        }

        if ((iVar1 == 1 && EndMotion(work)) || iVar1 == 2)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
        }

        work->field_A2C.vy = -100;
    }
}

void sna_anim_claymore_helper_80058780(SnaInitWork *work, int time)
{
    int var_s1;
    int x, y;
    int w;
    POLY_GT4 *pPoly;
    int i, j;

    work->field_914_trigger = 1; // 1 = WEAPON_TAKE

    if ( time < 10 )
    {
        return;
    }

    var_s1 = work->field_A38_local_data;

    if ( var_s1 == 0 )
    {
        sub_8004EEB0(work);

        DG_GroupPrim(work->field_92C, DG_CurrentGroupID_800AB968);
        DG_VisiblePrim(work->field_92C);
        DG_PutPrim_8001BE00(&work->field_92C->world);

        if ( !(work->field_9B0_pad_ptr->status & PAD_SQUARE) && (DG_UnDrawFrameCount_800AB380 == 0) )
        {
            var_s1 = sub_8004E5E8(work, 0x40);

            if ( var_s1 == 1 )
            {
                SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_4, 1);
                work->field_A38_local_data = 1;
                work->field_914_trigger |= 2; // 2 = WEAPON_TRIG
            }
            else if ( var_s1 == 2 )
            {
                GM_SeSet2_80032968(0, 63, SE_BUZZER);
            }
        }
    }

    y = GV_Time_800AB330 & 63;

    if ( y > 32 )
    {
        y = 64 - y;
    }

    x = work->field_928->off_x;
    w = x + 63;
    y += work->field_928->off_y;

    pPoly = &work->field_92C->packs[GV_Clock_800AB920]->poly_gt4;

    for ( i = 0; i < 2; i++ )
    {
        pPoly->u0 = x;
        pPoly->v0 = y;
        pPoly->u1 = w;
        pPoly->v1 = y;
        pPoly->u2 = x;
        pPoly->v2 = y;
        pPoly->u3 = w;
        pPoly->v3 = y;
        pPoly++;
    }

    if ( ((var_s1 == 1) && (EndMotion(work))) || (var_s1 == 2) )
    {
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK26 | SNA_FLAG1_UNK3);
        DG_InvisiblePrim(work->field_92C);
        sna_start_anim_8004E1F4(work, &sna_anim_idle_8005275C);
        GM_ConfigMotionAdjust_80035008(&work->field_9C_obj, NULL);

        for ( j = 0; j < 16; j++ )
        {
            work->field_718[j] = DG_ZeroVector_800AB39C;
        }
    }

    work->field_A2C.vy = -100;
}

void sna_anim_throw_800589C8(SnaInitWork *work, int time)
{
    Target_Data *pVec; // $s3
    int bClear; // $s4
    Sna_ActionTable *field_9B4_action_table; // $v1
    int action_flag; // $s0
    TARGET *field_8E8_pTarget; // $s0
    SVECTOR* pTmp;

    if ( time == 0)
    {
        pVec = &stru_8009EFE4[1];
        bClear = 0;
        field_9B4_action_table = work->field_9B4_action_table;
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        action_flag = field_9B4_action_table->field_10->field_4;
        if ( !sna_8004FDE8(work, pVec) )
        {
            action_flag = work->field_9B4_action_table->field_10->field_5;
            pVec = &stru_8009EFE4[2];

            if ( !sna_8004FDE8(work, pVec) )
            {
                bClear = 1;
                work->field_A38_local_data = 1;
                action_flag = work->field_9B4_action_table->field_0->field_1;
            }
        }
        GM_ClearPlayerStatusFlag_8004E2D4(16);
        SetAction_8004E22C(work, action_flag, 4);

        work->field_8FC = work->control.rot;
        work->field_8FC.vy += 2048;

         pTmp = &work->field_8EC_vec;
        if ( !bClear )
        {
            field_8E8_pTarget = work->field_8E8_pTarget;
            DG_PutVector_8001BE48(&pVec->field_0, pTmp, 1);
            GV_SubVec3(&field_8E8_pTarget->center, pTmp, pTmp);
            pTmp->vx /= 4;
            pTmp->vy /= 4;
            pTmp->vz /= 4;
        }
        else
        {

            *pTmp = DG_ZeroVector_800AB39C;
        }
    }

    if ( time < 4 )
    {
        GV_AddVec3(
            &work->control.step,
            &work->field_8EC_vec,
            &work->control.step);
    }

    if ( work->field_9C_obj.is_end || (work->field_A38_local_data == 1 && time == 4) )
    {
        sna_sub_8004E41C(work, 2);
        sna_clear_flags1_8004E308(work, 4);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
    }

}

void sna_anim_punch_80058C10(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_anim_punch_helper_800591F4;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        SetAction_8004E22C(work, work->field_9B4_action_table->field_10->field_2, 1);
        work->field_A38_local_data = 0;
        sna_set_flags1_8004E2F4(work, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_anim_chokethrow_begin2_80058C80(SnaInitWork *work, int time)
{
    int        bClear;            // $s0
    TARGET *field_8E8_pTarget; // $v1
    int        action_flag;       // $a1
    SVECTOR   *p;

    if (time == 0)
    {
        work->field_904_frames_last_choke = 0;
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        bClear = 0;
        work->field_A54.choke_count = 0;

        if (!sna_8004FDE8(work, &stru_8009EFE4[3]))
        {
            bClear = 1;
            work->field_A38_local_data = 1;
        }

        p = &work->field_8EC_vec;
        if (!bClear)
        {

            field_8E8_pTarget = work->field_8E8_pTarget;

            field_8E8_pTarget->field_2A--;

            DG_SetPos2_8001BC8C(&field_8E8_pTarget->center, &work->control.rot);

            DG_PutVector_8001BE48(&svector_800AB7FC, p, 1);
            DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
            GV_SubVec3(p, &work->control.mov, p);
            p->vx /= 4;
            p->vy /= 4;
            p->vz /= 4;
            action_flag = work->field_9B4_action_table->field_18->field_0;
        }
        else
        {
            work->field_8EC_vec = DG_ZeroVector_800AB39C;
            action_flag = work->field_9B4_action_table->field_0->field_1;
        }
        SetAction_8004E22C(work, action_flag, 4);
    }

    if (time < 4)
    {
        ++work->field_904_frames_last_choke;
        GV_AddVec3(&work->control.step, &work->field_8EC_vec,
                            &work->control.step);
    }
    else
    {
        if (work->field_A38_local_data)
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        }
        else
        {
            work->field_89C_pTarget->size.vx = 150;
            sna_start_anim_8004E1F4(work, sna_anim_choke_80058E88);
        }
    }
}

void sna_anim_choke_80058E88(SnaInitWork *work, int time)
{
    short action_flag; // $s0

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_anim_choke_helper_8005951C;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        action_flag = work->field_9B4_action_table->field_18->field_0;
        SetAction_8004E22C(work, action_flag, 4);
        work->field_8E8_pTarget->a_mode = action_flag;
    }
}

void sna_anim_choke_rechoke_80058EF4(SnaInitWork *work, int time)
{
    short bVar1;

    if (time == 0 || (work->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        GetAction(work) = -1;
        work->field_9C8_anim_update_fn_3p = sna_anim_choke_rechoke_helper_8005961C;
        work->field_904_frames_last_choke = 0;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        bVar1 = work->field_9B4_action_table->field_10->field_6;
        SetAction_8004E22C(work, bVar1, 4);
        work->field_8E8_pTarget->a_mode = bVar1;
    }
}

void sna_anim_choke_kill_80058F88(SnaInitWork *work, int time)
{
    TARGET *field_8E8_pTarget; // $s0
    int        action_flag;       // $s1

    if (time == 0)
    {
        field_8E8_pTarget = work->field_8E8_pTarget;
        action_flag = work->field_9B4_action_table->field_10->field_7;

        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;

        SetAction_8004E22C(work, action_flag, 4);

        field_8E8_pTarget->a_mode = action_flag;
        field_8E8_pTarget->field_28 = 5;
        field_8E8_pTarget->field_2A--;
        work->field_A54.choke_count = 0;
    }

    if (work->field_9C_obj.is_end)
    {
        sna_sub_8004E41C(work, 2);
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
    }
}

void sna_anim_choke_drag_80059054(SnaInitWork *work, int time)
{
    int bVar2;
    int iVar3;

    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        bVar2 = work->field_9B4_action_table->field_18->field_1;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_MOVING);
        SetAction_8004E22C(work, bVar2, 4);
        work->field_8E8_pTarget->a_mode = bVar2;
    }

    iVar3 = work->field_904_frames_last_choke + 1;
    work->field_904_frames_last_choke = iVar3;

    if ((gSnaMoveDir_800ABBA4 < 0 || ((work->field_9B0_pad_ptr->status & PAD_SQUARE) == 0)))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
        sna_start_anim_8004E1F4(work, sna_anim_choke_80058E88);
    }
    else
    {
        if (!((work->field_8E8_pTarget->field_26_hp > 0) &&
              ((iVar3 < 0x5a && work->field_8E8_pTarget->field_42 != 0))))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_MOVING);
            sna_start_anim_8004E1F4(work, sna_anim_choke_80058E88);
            return;
        }
        else
        {
            work->control.turn.vy = gSnaMoveDir_800ABBA4 + 0x800;
        }
    }
}

void sna_anim_choke_hold_80059154(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = sna_fn_nothing_80053B80;
        work->field_9CC_anim_update_fn_1p = sna_fn_nothing_80053B80;
        SetAction_8004E22C(work, work->field_9B4_action_table->field_18->field_6, 4);
    }

    if (EndMotion(work))
    {
        sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
    }
}

void sub_800591BC(SnaInitWork *work)
{
    sna_start_anim_8004E1F4(work, sna_anim_idle_8005275C);
    sna_clear_flags1_8004E308(work, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
}

void sna_anim_punch_helper_800591F4(SnaInitWork *work, int time)
{
    int x, y;
    int sound;

    if ( time == 0 )
    {
        HomingTarget_2_80032EAC(&work->field_9C_obj.objs->objs[6].world,
                                work->control.rot.vy,
                                &x, &y, work->control.map->index,
                                2000, 1024);

        if ( x >= 0 )
        {
            work->control.turn.vy = x;
        }
    }

    if ( time == 4 )
    {
        sub_8004FCB8(work, &stru_8009F064, 3);

        sound = SE_PUNCH_SWING;
        if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) )
        {
            sound = 182;
        }

        GM_SeSet_80032858(&work->control.mov, sound);
        GM_SetNoise(time, 2, &work->control.mov);
    }

    if ( time == 6 )
    {
        if ( !(work->field_A38_local_data & 0x20) )
        {
            sub_800591BC(work);
            return;
        }

        work->field_A38_local_data &= ~0x20;
    }

    if ( time == 11 )
    {
        sub_8004FCB8(work, &stru_8009F084, 3);

        sound = SE_PUNCH_SWING;
        if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) )
        {
            sound = 182;
        }

        GM_SeSet_80032858(&work->control.mov, sound);
        GM_SetNoise(4, 2, &work->control.mov);
    }

    if ( time == 13 )
    {
        if ( !(work->field_A38_local_data & 0x20) )
        {
            sub_800591BC(work);
            return;
        }

        work->field_A38_local_data = 0;
    }

    if ( time == 22 )
    {
        sub_8004FCB8(work, &stru_8009F0A4, 4);

        sound = SE_KICK_SWING;
        if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNDERWATER) )
        {
            sound = 182;
        }

        GM_SeSet_80032858(&work->control.mov, sound);
        GM_SetNoise(4, 2, &work->control.mov);
    }

    if ( EndMotion(work) )
    {
        sub_800591BC(work);
        return;
    }

    work->field_A38_local_data |= work->field_9B0_pad_ptr->press;

    if ( (work->field_9B0_pad_ptr->press & PAD_CROSS) != 0 )
    {
        sub_800591BC(work);
    }
}

void sna_anim_choke_helper_8005951C(SnaInitWork *work, int time)
{
    int   sinceLastChoke;
    short press;
    short status;

    sinceLastChoke = ++work->field_904_frames_last_choke;

    if (((work->field_8E8_pTarget->field_26_hp < 1 || sinceLastChoke >= 90) ||
         work->field_8E8_pTarget->field_42 == 0))
    {
        sna_sub_8004E41C(work, 2);
        sna_start_anim_8004E1F4(work, sna_anim_choke_hold_80059154);
        sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
        return;
    }

    press = work->field_9B0_pad_ptr->press;
    status = work->field_9B0_pad_ptr->status;

    if ((press & PAD_SQUARE) != 0)
    {
        sna_start_anim_8004E1F4(work, sna_anim_choke_rechoke_80058EF4);
    }
    else if ((status & PAD_SQUARE) == 0)
    {
        // A38 is snake stop movement frames, counts down
        if (++work->field_A38_local_data >= 9)
        {
            sna_sub_8004E41C(work, 2);
            sna_start_anim_8004E1F4(work, sna_anim_choke_hold_80059154);
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
        }
    }
    else
    {
        work->field_A38_local_data = 0;
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            sna_start_anim_8004E1F4(work, sna_anim_choke_drag_80059054);
        }
    }
}

void sna_anim_choke_rechoke_helper_8005961C(SnaInitWork *work, int time)
{
    if (time == 0 || (work->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        work->field_8E8_pTarget->field_2A--;

        if (++work->field_A54.choke_count >= 10) // feels good
        {
            // TODO: fix data when vibrate is figured out
            NewPadVibration_8005D58C(dword_8009EF24, 1);
            NewPadVibration_8005D58C(dword_8009EF2C, 2);
            sna_start_anim_8004E1F4(work, sna_anim_choke_kill_80058F88);
            return;
        }
    }

    if (work->field_9C_obj.is_end == 0 && work->field_8E8_pTarget->field_42 != 0)
    {
        return;
    }

    sna_start_anim_8004E1F4(work, sna_anim_choke_80058E88);
}

static inline int sna_init_main_logic_helper_helper_helper_800596FC(RECT *a, RECT *b)
{
    int test1;
    int test2;

    test1 = a->x * b->x + a->y * b->y;
    test2 = test1;

    if (test1 < 0)
    {
        return 1;
    }

    if (test2 > a->x * a->x + a->y * a->y)
    {
        return 1;
    }

    return 0;
}

static inline int sna_init_main_logic_helper_helper_800596FC(SnaInitWork *work)
{
    HZD_FLR  *local_40[2];
    RECT      rect[2]; // Maybe vecs
    CONTROL  *pCtrl;
    SVECTOR  *pPosition;
    HZD_FLR  *floor;
    int       iVar9;
    int       iVar10;
    int       iVar17;
    int       iVar19;
    int       iVar11;
    int       i;
    int       result;
    char     *pChk;

    result = -1;
    pCtrl = &work->control;
    pPosition = &pCtrl->mov;

    if (pCtrl->field_58 == 1)
    {
        if (!(pCtrl->field_5A[0] & 0x40))
        {
            floor = pCtrl->field_70[0];

            rect[1].x = pPosition->vx - floor->b1.x;
            rect[1].y = pPosition->vz - floor->b1.z;
            rect[0].x = floor->b2.x - floor->b1.x;
            rect[0].y = floor->b2.z - floor->b1.z;

            if (!sna_init_main_logic_helper_helper_helper_800596FC(&rect[0], &rect[1]))
            {
                result = 0;
                work->field_79C = 1;
            }
        }
    }
    else
    {
        pChk = work->control.field_5A;
        iVar9 = 0;

        for (i = 0; i < 2; i++, pChk++)
        {
            floor = pCtrl->field_70[i];
            local_40[i] = floor;

            if (*pChk & 0x40)
            {
                continue;
            }

            rect[1].x = pPosition->vx - floor->b1.x;
            rect[1].y = pPosition->vz - floor->b1.z;
            rect[0].x = floor->b2.x - floor->b1.x;
            rect[0].y = floor->b2.z - floor->b1.z;

            if (!sna_init_main_logic_helper_helper_helper_800596FC(&rect[0], &rect[1]))
            {
                result = i;
                iVar9++;
                work->field_79C = 1;
            }
        }

        if (iVar9 >= 2)
        {
            iVar11 = GV_VecLen3(&pCtrl->field_60_vecs_ary[0]);
            iVar10 = GV_VecLen3(&pCtrl->field_60_vecs_ary[1]);
            iVar17 = GV_VecDir2(&pCtrl->field_60_vecs_ary[0]);
            iVar19 = GV_VecDir2(&pCtrl->field_60_vecs_ary[1]);

            if (GV_DiffDirAbs(iVar17, iVar19) < 512)
            {
                work->field_79C = 1;
                result = iVar11;
                return result >= iVar10;
            }

            work->field_79C = 2;
            result = 2;
        }
    }

    return result;
}

static inline void sna_init_main_logic_helper_800596FC(SnaInitWork *work)
{
    int         dir;
    signed char cVar4;
    int         iVar9;
    int         iVar10;
    int         result;
    int         diff;

    gSnaMoveDir_800ABBA4 = work->field_9B0_pad_ptr->dir;
    pVec_800ABBC8 = pVec_800ABBCC;
    dword_800ABBAC = 0;
    dword_800ABBC4 = 0;
    dword_800ABBB0 = 0;
    pVec_800ABBCC = 0;
    dword_800ABBA8 = -1;
    dword_800ABBD0 = -1;

    dir = gSnaMoveDir_800ABBA4;

    work->field_79C = 0;
    cVar4 = work->control.field_58;

    if (cVar4 <= 0)
    {
        return;
    }

    dword_800ABBAC = &work->control.field_60_vecs_ary[0];
    dword_800ABBB4 = &work->control.field_5A[0];
    dword_800ABBA8 = GV_VecDir2(&work->control.field_60_vecs_ary[0]);

    if ((*dword_800ABBB4 & 0x40) == 0)
    {
        pVec_800ABBCC = dword_800ABBAC;
        dword_800ABBB0 = work->control.field_70[0];
        dword_800ABBD0 = dword_800ABBA8;
    }

    if (dir < 0)
    {
        return;
    }

    if (cVar4 != 1)
    {
        iVar9 = GV_VecDir2(&work->control.field_60_vecs_ary[1]);
        iVar10 = GV_DiffDirAbs(dir, dword_800ABBA8);

        if (GV_DiffDirAbs(dir, iVar9) < iVar10)
        {
            dword_800ABBAC = &work->control.field_60_vecs_ary[1];
            dword_800ABBB4 = &work->control.field_5A[1];
            dword_800ABBA8 = GV_VecDir2(&work->control.field_60_vecs_ary[1]);

            if ((*dword_800ABBB4 & 0x40) == 0)
            {
                pVec_800ABBCC = dword_800ABBAC;
                dword_800ABBB0 = work->control.field_70[1];
                dword_800ABBD0 = dword_800ABBA8;
            }
        }
    }

    result = sna_init_main_logic_helper_helper_800596FC(work);

    if (result == -1)
    {
        pVec_800ABBCC = 0;
        dword_800ABBD0 = -1;
        return;
    }

    if (result != 2)
    {
        pVec_800ABBCC = &work->control.field_60_vecs_ary[result];
        dword_800ABBD0 = GV_VecDir2(pVec_800ABBCC);
        dword_800ABBB0 = work->control.field_70[result];
    }

    diff = GV_DiffDirS(dir, dword_800ABBD0);

    if ((diff >= -896) && (diff <= 896))
    {
        dword_800ABBC4 = 1;

        if (diff >= 0)
        {
            if (diff > 256)
            {
                dword_800ABBC4 = 4;
            }
        }
        else if (diff < -256)
        {
            dword_800ABBC4 = 2;
        }
    }
}

static inline void sna_init_main_logic_helper2_800596FC(SnaInitWork *work)
{
    int iVar9;
    int iVar8;

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_GROUND))
    {
        work->field_A2A = 0;
    }
    else if (!svector_800ABBB8 || (svector_800ABBB8->pad == 2))
    {
        work->field_A2A = 0;

        if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_FIRST_PERSON))
        {
            work->control.turn.vx = 0;
        }
    }
    else
    {
        iVar8 = sub_8004E930(work, 750);
        iVar9 = iVar8 - work->field_A2A;

        if (iVar9 >= 0)
        {
            if (iVar9 < 16)
            {
                goto inside;
            }
        }
        else
        {
            iVar9 = work->field_A2A - iVar8;

            if (iVar9 < 16)
            {
inside:
                iVar8 = work->field_A2A;
            }
        }

        work->field_A2A = iVar8;

        if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_FIRST_PERSON))
        {
            (work->control).turn.vx = iVar8;
        }
    }
}

static inline void sna_init_main_logic_helper3_800596FC(SnaInitWork *work)
{
    int iVar9;
    int sVar5;
    int iVar8;
    int uVar13;
    int new_var;

    int     msgs;
    GV_MSG *pMsg;
    int     hash;
    TARGET *pTarget;

    if (!sna_check_flags1_8004E31C(work, 0x200000))
    {
        return;
    }

    uVar13 = work->field_9E4.field_9EC_flags3;

    if (work->field_9E4.field_9F0 != 0)
    {
        work->control.field_38 = 450;
        work->control.field_36 = 450;
        work->field_A28 = 450;

        if ((uVar13 & 0x4002) == 0)
        {
            new_var = work->field_9E4.field_9EE;
            iVar9 = work->control.levels[0];
            iVar8 = (unsigned short)work->field_9C_obj.field_18 - (iVar9 - new_var);
            work->control.height = iVar8;
            iVar8 = iVar8 + iVar9;
            work->control.mov.vy = iVar8;
            work->field_9C_obj.objs->world.t[1] = work->control.mov.vy;
            DG_GetLightMatrix2_8001A5D8(&work->control.mov, &work->field_848_lighting_mtx);
        }
        else if ((uVar13 & 0x100) == 0)
        {
            work->control.height = dword_8009EECC[work->field_A26_stance];
        }

        work->field_9C_obj.field_18 = work->control.height;
        sVar5 = work->field_9E4.field_9E8;

        if (sVar5 >= 0)
        {
            if (GV_DiffDirAbs(sVar5, work->control.rot.vy) > 1536)
            {
                work->control.rot.vy = sVar5;
            }

            work->control.turn.vy = sVar5;
        }

        if ((uVar13 & 0x80) == 0)
        {
            GM_ConfigMotionControl_80034F08(
                &work->field_9C_obj,
                &work->field_180,
                0x992d,
                work->field_1D0,
                work->field_1D0 + 17,
                &work->control,
                &work->field_698_joint_rotations.field_0_lower_body
            );

            work->field_9C_obj.action_flag = -1;
        }

        if ((uVar13 & 0x800) != 0)
        {
            SetAction_8004E22C(work, sna_8004EAA8(work, work->field_A26_stance), 0);
        }

        work->field_9E4.field_9F0 = 0;
    }

    msgs = work->field_7A0_msg_count;
    pMsg = work->field_7A4_msgs;

    while (msgs > 0)
    {
        hash = pMsg->message[0];

        if ((hash == 0x937a) || (hash == 0x70fb) || (hash == 0x3238) || (hash == 0xbe0a))
        {
            pTarget = work->field_89C_pTarget;

            if (pTarget->field_28 > 0)
            {
                pTarget->field_26_hp += pTarget->field_28;
                sna_act_unk2_80051170(work->field_89C_pTarget);
            }

            sna_set_invuln_8004F2A0(work, 0);
            goto exit;
        }

        msgs--;
        pMsg++;
    }

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4);

exit:
    sna_clear_flags1_8004E308(work, 0x8200000);
}

static inline int sna_init_main_logic_helper4_helper_800596FC(SnaInitWork *work)
{
    if (sna_check_flags1_8004E31C(work, 1) ||
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_FIRST_PERSON | PLAYER_INTRUDE))
    {
        return 0;
    }

    return 1;
}

static inline int sna_init_main_logic_helper4_helper2_800596FC(SnaInitWork *work)
{
    if (sna_check_flags1_8004E31C(work, 2) ||
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) ||
        (work->field_920_tbl_8009D580 & 0x200))
    {
        return 0;
    }

    return 1;
}

static inline int sna_init_main_logic_helper4_helper3_800596FC(int f3e)
{
    if ((f3e == 1) || (f3e == 3) || (f3e == 8))
    {
        return 0;
    }

    return 1;
}

static inline int sna_init_main_logic_helper4_helper4_800596FC(SnaInitWork *work)
{
    if (sna_check_flags1_8004E31C(work, 2) ||
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) ||
        (work->field_920_tbl_8009D580 & 0x200))
    {
        return 0;
    }

    return 1;
}

static inline void sna_init_main_logic_helper4_800596FC(SnaInitWork *work)
{
    int     iframes;
    TARGET *pTarget;
    int     iVar8;
    int     bVar6;
    int     iVar9;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INVULNERABLE))
    {
        iframes = work->field_A24_invuln_frames;

        if (iframes != 0)
        {
            if (--iframes > 0)
            {
                if (sna_init_main_logic_helper4_helper_800596FC(work))
                {
                    if ((iframes & 3) != 0)
                    {
                        DG_VisibleObjs(work->field_9C_obj.objs);
                    }
                    else
                    {
                        DG_InvisibleObjs(work->field_9C_obj.objs);
                    }
                }

                if ((GM_Camera_800B77E8.first_person != 0) &&
                    (!sna_init_main_logic_helper4_helper2_800596FC(work) || (work->field_9AC & 0x2)) &&
                    !sna_check_flags1_8004E31C(work, 1))
                {
                    gUnkCameraStruct_800B77B8.eye.vy += GV_RandS(16) * iframes;
                }
            }
            else
            {
                sna_clear_invuln_8004F2EC(work);
            }

            work->field_A24_invuln_frames = iframes;
        }
        else
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4000000))
            {
                DG_VisibleObjs(work->field_9C_obj.objs);
            }

            if (GM_Camera_800B77E8.first_person != 0)
            {
                DG_InvisibleObjs(work->field_9C_obj.objs);
            }
            else
            {
                DG_VisibleObjs(work->field_9C_obj.objs);
            }
        }
    }
    else
    {
        pTarget = work->field_89C_pTarget;

        if (pTarget->damaged & 0x6)
        {
            iVar8 = pTarget->a_mode;
            bVar6 = sna_init_main_logic_helper4_helper3_800596FC(iVar8);

            if (sna_init_main_logic_helper4_helper4_800596FC(work) && (bVar6 || !(work->field_9AC & 0x2)))
            {
                work->control.skip_flag &= ~CTRL_SKIP_TRAP;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_SQUAT | PLAYER_ON_WALL | PLAYER_PREVENT_ITEM_SWITCH);
                sna_clear_flags1_8004E308(work, 0x30);
                sna_clear_flags1_8004E308(work, 0x100);
                work->field_9C0 = 0;
                work->field_A28 = 0x1c2;

                if ((work->field_920_tbl_8009D580 & 0x4) &&
                    GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PREVENT_FIRST_PERSON) &&
                    (work->field_924 != 3))
                {
                    work->field_914_trigger |= 0x9;
                }

                sub_8004F454(work);

                if (work->field_90C_pWeaponFn == &sna_80057A90)
                {
                    work->field_90C_pWeaponFn = &sna_gun_800540D0;
                    work->field_910 = 0;
                    work->field_926 = 0;
                    work->field_924 = 0;
                }

                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK100 | PLAYER_PREVENT_WEAPON_SWITCH);

                if (!bVar6)
                {
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK200))
                    {
                        sna_set_flags1_8004E2F4(work, 0x4);
                        sna_start_anim_8004E1F4(work, &sna_anim_knockdown_shot_80054B50);
                    }
                    else if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CB_BOX))
                    {
                        sna_set_flags1_8004E2F4(work, 0x20);
                        sna_start_anim_8004E1F4(work, &sna_act_helper2_helper7_80054648);
                    }
                    else
                    {
                        sna_start_anim_8004E1F4(work, &sna_anim_shot_flinch_800544E0);
                    }

                    GM_SeSet2_80032968(0, 63, SE_PLAYER_DAMAGE_LIGHT);

                    NewPadVibration_8005D58C(dword_8009EED4, 1);
                    NewPadVibration_8005D58C(dword_8009EED8, 2);
                }
                else
                {
                    work->field_A2C = pTarget->field_2C_vec;
                    work->field_A2C.vx /= 2;
                    work->field_A2C.vy /= 4;
                    work->field_A2C.vz /= 2;

                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_GROUND | PLAYER_UNK200))
                    {
                        if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK200))
                        {
                            work->field_A54.knockdown_thing = 1;
                        }

                        sna_start_anim_8004E1F4(work, &sna_anim_knockdown_shot_tank_80054C08);
                    }
                    else
                    {
                        sna_start_anim_8004E1F4(work, &sna_anim_knockdown_80054710);
                    }

                    if (work->field_9AC & 0x1)
                    {
                        sub_8004F204(work);
                    }

                    GM_SeSet2_80032968(0, 63, SE_PLAYER_DAMAGE_HEAVY);

                    NewPadVibration_8005D58C(dword_8009EEE0, 1);
                    NewPadVibration_8005D58C(dword_8009EEE4, 2);

                    sna_8004EC00(work);
                    sna_set_flags1_8004E2F4(work, 0x4);
                }

                sna_act_helper2_helper4_8004F090(work, iVar8);
            }
            else
            {
                sna_set_invuln_8004F2A0(work, 0x20);

                if (pTarget->field_28 > 0)
                {
                    sna_act_helper2_helper4_8004F090(work, pTarget->a_mode);
                }

                switch (iVar8)
                {
                case 1:
                case 3:
                    GM_SeSet2_80032968(0, 63, SE_PLAYER_DAMAGE_LIGHT);
                    NewPadVibration_8005D58C(dword_8009EED4, 1);
                    NewPadVibration_8005D58C(dword_8009EED8, 2);
                    break;

                default:
                    GM_SeSet2_80032968(0, 63, SE_PLAYER_DAMAGE_HEAVY);
                    NewPadVibration_8005D58C(dword_8009EEE0, 1);
                    NewPadVibration_8005D58C(dword_8009EEE4, 2);
                    break;
                }


                if ((pTarget->field_26_hp < 1) && ((GM_GameOverTimer_800AB3D4 > -2) && (GM_GameOverTimer_800AB3D4 < 1)))
                {
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE | PLAYER_GROUND))
                    {
                        iVar9 = 0x7d;
                    }
                    else
                    {
                        iVar9 = 0x80;
                        work->control.rot.vx = 0;
                        work->control.turn.vx = 0;
                    }

                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK200))
                    {
                        if (work->field_A54.choke_count == 1)
                        {
                            iVar9 = 0x7e;
                        }
                        else
                        {
                            iVar9 = 0x7f;
                        }
                    }

                    GM_SeSet2_80032968(0, 63, SE_PLAYEROUT);
                    sna_8004F8E4(work, iVar9);
                }
            }

            sna_act_unk2_80051170(pTarget);

            if (GM_Camera_800B77E8.first_person != 0)
            {
                work->control.turn.vy += GV_RandS(512);
            }
        }
        else if (pTarget->damaged & 0x80)
        {
            sna_act_unk2_80051170(pTarget);
        }
    }
}

static inline void sna_init_main_logic_helper5_800596FC(SnaInitWork *work)
{
    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_GAMEOVER))
    {
        if (((work->field_9C_obj.action_flag == 128) && (work->field_180.field_04_info1.field_2_footstepsFrame == 49)) ||
            ((work->field_9C_obj.action_flag == 127) && (work->field_180.field_04_info1.field_2_footstepsFrame == 72)))
        {
            NewPadVibration_8005D58C(dword_8009EEF0, 1);
            NewPadVibration_8005D58C(dword_8009EEF4, 2);

            if (work->field_9C_obj.action_flag == 128)
            {
                GM_SeSetMode_800329C4(&work->control.mov, SE_HIT_FLOOR, GM_SEMODE_BOMB);
            }
        }

        if ((work->field_7A0_msg_count == 0) &&
            !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK4) &&
            (GM_StreamStatus_80037CD8() != 2))
        {
            GM_StreamPlayStop_80037D64();
            sna_set_flags1_8004E2F4(work, 0x40000);
            GM_GameOverTimer_800AB3D4 = 1;
        }
    }
    else if (GM_GameOverTimer_800AB3D4 > 0)
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;

        if (GM_GameOverTimer_800AB3D4 == 2)
        {
            sna_set_flags1_8004E2F4(work, 0x80000);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GAMEOVER);
            sna_set_invuln_8004F2A0(work, 0);
            GM_GameOverTimer_800AB3D4 = -1;
        }
    }
}

static inline int sna_init_main_logic_helper6_helper_800596FC(SnaInitWork *work, int flags)
{
    if (dword_8009F46C[0] != 0 ||
        sna_check_flags1_8004E31C(work, 0x4) ||
        GM_CheckPlayerStatusFlag_8004E29C(flags) ||
        work->field_9CC_anim_update_fn_1p == &sna_fn_nothing_80053B80)
    {
        return 0;
    }

    return 1;
}

static inline int sna_init_main_logic_helper6_helper2_800596FC(SnaInitWork *work)
{
    if ((work->field_920_tbl_8009D580 & 0x200) ||
        (work->field_9AC & 0x2) ||
        sna_check_flags1_8004E31C(work, 0x4) ||
        sna_sub_8004E358(work, 0x100))
    {
        return 0;
    }

    return 1;
}

static inline int sna_init_main_logic_helper6_helper3_800596FC(SnaInitWork *work)
{
    if ((work->field_920_tbl_8009D580 & 0x200) ||
        (work->field_9AC & 0x2) ||
        sna_check_flags1_8004E31C(work, 0x4) ||
        sna_sub_8004E358(work, 0x100))
    {
        return 0;
    }

    return 1;
}

static inline void sna_init_main_logic_helper6_800596FC(SnaInitWork *work)
{
    if ((work->field_9B0_pad_ptr->press & PAD_TRIANGLE) &&
        sna_init_main_logic_helper6_helper_800596FC(work, PLAYER_FIRST_PERSON | PLAYER_PREVENT_FIRST_PERSON))
    {
        sub_8004EB74(work);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_FIRST_PERSON_CAN_LR_PEEK);
    }
}

void sna_init_main_logic_800596FC(SnaInitWork *work)
{
    int             vy;
    GV_PAD         *pPad;
    unsigned char  *pAxis;
    int             i;
    int             frame;
    int             hzd_count;
    unsigned short *pHzdVal;

    work->field_798_p_height = work->control.height;

    vy = work->field_9C_obj.field_18;
    work->control.height = vy;

    if ( vy < 500 )
    {
        vy = 500;
    }

    if ( vy > 700 )
    {
        vy = 700;
    }

    work->field_89C_pTarget->size.vy = vy;

    if ( (work->field_A2C.vy < 0) && (work->control.field_57 != 0) )
    {
        work->field_A2C.vy = 0;
    }

    work->field_A2C.vy -= 32;

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_UNK80) )
    {
        return;
    }

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) )
    {
        work->field_9B0_pad_ptr = &GV_PadData_8009F0C4;
    }

    work->field_914_trigger = 0;
    work->control.turn.vz = 0;

    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK15);

    pPad = work->field_9B0_pad_ptr;

    if ( pPad->analog != 0 && (pPad->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) )
    {
        pAxis = &pPad->left_dx;

        for ( i = 0; i < 2; i++, pAxis++ )
        {
            if ( (*pAxis < 64) || (*pAxis > 192) )
            {
                sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK15);
                break;
            }
        }
    }

    sna_init_main_logic_helper_800596FC(work);
    sna_init_main_logic_helper2_800596FC(work);
    sna_init_main_logic_helper3_800596FC(work);
    sna_init_main_logic_helper4_800596FC(work);

    if ( GM_StatusEvent & EV_CommonCold )
    {
        if ( !(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_IN_DEMO)) &&
             !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PAD_OFF) &&
             (work->field_A5C < 900) )
        {
            work->field_A5C++;
        }

        if ( sna_act_helper2_helper5_8004FF88(work) && (work->field_A5C == 900) )
        {
            work->field_A5C = 0;
            sna_start_anim_8004E1F4(work, &sna_act_helper2_helper_80054EFC);
        }
    }

    sna_weapon_switching_800511BC(work, 1);
    sna_800515BC(work, 1);

    if ( !GM_CheckPlayerStatusFlag_8004E29C(0x1304) &&
         ((work->field_9AC & 2) == 0) &&
         ((work->field_920_tbl_8009D580 & 0x4000) != 0) &&
         (*work->field_918_n_bullets == 0))
    {
        *work->field_918_n_bullets = -1;
        GM_CurrentWeaponId = WEAPON_NONE;
        work->field_90C_pWeaponFn = &sna_anim_chokethrow_begin1_80054210;
        work->field_910 = 0;
        work->field_926 = 0;
        work->field_924 = 0;
        GM_WeaponChanged_800AB9D8 = 1;
        work->field_920_tbl_8009D580 = GM_WeaponTypes_8009D580[0];
        work->field_918_n_bullets = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(0x600000);
    }

    sna_act_unk_80050A64(work);
    sna_init_main_logic_helper5_800596FC(work);
    sna_act_helper2_helper3_8004ED6C(work);

    frame = work->field_9BC_anim_frame++;
    work->field_9B8_fn_anim(work, frame);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_FIRST_PERSON))
    {
        work->field_9CC_anim_update_fn_1p(work, frame);
    }
    else
    {
        work->field_9C8_anim_update_fn_3p(work, frame);
    }

    if ((work->field_920_tbl_8009D580 & 0x40) &&
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_PREVENT_FIRST_PERSON))
    {
        work->field_910++;
        work->field_90C_pWeaponFn(work, work->field_910 - 1);
    }

    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK9) )
    {
        work->field_9C4++;
        work->field_9C0(work, work->field_9C4 - 1);
    }

    work->control.field_36 = GV_NearExp4(work->control.field_36, work->field_A28);
    work->control.step.vy = work->field_A2C.vy;

    sna_init_main_logic_helper6_800596FC(work);

    if ( GM_StreamStatus_80037CD8() == 2 )
    {
        if ( sub_8004EFE4(work, 1) >= 0 )
        {
            work->field_180.field_04_info1.field_14 = 1;
        }

        sna_act_helper2_helper2_80033054(CHARA_SNAKE, &work->field_718[6]);

        if ( !work->field_9C_obj.objs->adjust && (work->field_180.field_04_info1.field_14 == 1) )
        {
            GV_AddVec3(&work->field_698_joint_rotations.field_30_neck2,
                                &work->field_718[6],
                                &work->field_698_joint_rotations.field_30_neck2);
        }
    }

    GM_PlayerAction_800ABA40 = work->field_9C_obj.action_flag;
    dword_800AB9D4 = work->field_180.field_04_info1.field_2_footstepsFrame;
    GM_PlayerStance = work->field_A26_stance;

    if ( GM_TranquilizerTimer > 0 )
    {
        GM_TranquilizerTimer--;
    }

    GM_ClearPlayerStatusFlag_8004E2D4(0x42000000);

    hzd_count = work->control.field_10_events.field_6_count;
    pHzdVal = work->control.field_10_events.field_8_array;

    while ( hzd_count > 0 )
    {
        if ( *pHzdVal == 0x375E )
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_DEADORDYING);
        }
        else if ( *pHzdVal == 0xF715 )
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK2000000);
        }

        hzd_count -= 1;
        pHzdVal += 1;
    }

    if ( work->field_9A0 != 0 )
    {
        addPrim(DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920], &work->field_950[GV_Clock_800AB920]);
        work->field_9A0--;
    }

    snake_weapon_idx_800BDCBA = work->field_91C_weapon_idx;
    snake_weapon_max_ammo_800BDCBC = *work->field_918_n_bullets;
    snake_mag_size_800BDCB8 = GM_Magazine_800AB9EC;
}

static inline int sna_act_helper_8005AD10(SnaInitWork *work)
{
    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK19) )
    {
        CheckMessage0_80050878(work);
        sna_act_unk_80050A64(work);

        if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK19) )
        {
            sna_act_unk2_80051170(work->field_89C_pTarget);

            dword_800AB9D4 = 0;
            DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
            DG_PutObjs_8001BDB8(work->field_9C_obj.objs);
            return 1;
        }
    }

    return 0;
}

static inline void sna_act_helper2_8005AD10(SnaInitWork *work)
{
    SVECTOR vec;

    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK24) && !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK28) )
    {
        vec = work->field_A68;
        GV_NearExp8V(&vec.vx, &DG_ZeroVector_800AB39C.vx, 3);

        if ( GV_VecLen3(&vec) > 8 )
        {
            work->field_A68 = vec;
        }

        work->control.step.vx = work->field_A68.vx;
        work->control.step.vz = work->field_A68.vz;

        if ( work->control.field_57 & 1 )
        {
            sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK24);
        }
    }

    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK26) )
    {
        work->control.step.vz = 0;
        work->control.step.vx = 0;
    }
}

void sna_act_8005AD10(SnaInitWork *work)
{
    SVECTOR vec;
    SVECTOR vec2;
    TARGET *pTarget;
    int height;
    int level;
    TARGET *pTarget2;

    if ( sna_act_helper_8005AD10(work) )
    {
        return;
    }

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_CAN_USE_CONTROLLER_PORT_2) )
    {
        if ( ((GV_PadData_800B05C0 + 1)->status | (GV_PadData_800B05C0 + 1)->release) != 0 )
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_USING_CONTROLLER_PORT_2);
            work->field_9B0_pad_ptr = &GV_PadData_800B05C0[1];
        }
        else if ( (GV_PadData_800B05C0->status | GV_PadData_800B05C0->release) != 0 )
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_USING_CONTROLLER_PORT_2);
            work->field_9B0_pad_ptr = &GV_PadData_800B05C0[0];
        }
    }
    else
    {
        work->field_9B0_pad_ptr = &GV_PadData_800B05C0[0];
    }

    pTarget = work->field_89C_pTarget;

    if ( pTarget->damaged & 8 )
    {
        GV_AddVec3(&pTarget->field_34_vec, &work->control.step, &work->control.step);
        pTarget->damaged &= ~0x8;
        pTarget->field_34_vec = DG_ZeroVector_800AB39C;
    }

    height = (short)work->field_9C_obj.field_18;

    GM_ActMotion_80034A7C(&work->field_9C_obj);
    sna_act_helper2_8005AD10(work);

    level = work->control.levels[0];
    work->control.hzd_height = HzdHeights_8009EEC4[work->field_A26_stance] + level;

    if ( (work->control.skip_flag & CTRL_BOTH_CHECK) && (work->field_798_p_height < 750) )
    {
        work->control.hzd_height = work->control.mov.vy;
    }

    /* しゃがみ天井突き抜け防止 */
    if ( (work->field_A26_stance != SNA_STANCE_STANDING) && (height >= 500) )
    {
        work->control.height = 496;
    }

    UpdateLife_8004F6E8(work);
    CheckSnakeDead_8004E384(work);
    CheckMessage0_80050878(work);

    GM_ActControl_80025A7C(&work->control);

    dword_800ABBBC = 0;
    do {} while (0);
    svector_800ABBB8 = NULL;
    dword_800ABBC0 = 0;

    if ( work->control.field_36 != -2 )
    {
        sub_800298C0(&svector_800ABBB8);

        if ( svector_800ABBB8 )
        {
            dword_800ABBC0 = svector_800ABBB8[5].pad;
        }
    }

    if ( ((level - work->control.levels[0]) >= 250) && !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK28) )
    {
        if ( !svector_800ABBB8 || (svector_800ABBB8->pad == 2) )
        {
            sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK24);
            work->field_A68 = work->control.step;
            work->field_A68.vy = 0;
        }
    }

    if ( work->control.field_36 == -2 )
    {
        work->control.mov.vy += work->field_9C_obj.field_18 - height;
        DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
    }

    GM_ActObject_80034AF4(&work->field_9C_obj);

    sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK25);
    DG_GetLightMatrix2_8001A5D8(&work->control.mov, &work->field_848_lighting_mtx);
    *work->field_88C = dword_800ABA1C == 0;
    GM_MoveTarget_8002D500(work->field_89C_pTarget, &work->control.mov);

    vec2 = work->control.mov;

    if ( !sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK12) )
    {
        vec2.vy = work->field_9C_obj.objs->objs[6].world.t[1];
    }

    if (work->field_A26_stance == SNA_STANCE_GROUND)
    {
        vec2.vy += 320;
    }

    work->field_A60 = vec2;

    gUnkCameraStruct_800B77B8.rotate2 = work->control.rot;
    gUnkCameraStruct_800B77B8.rotate2.vy &= 0xFFF;

    sna_init_main_logic_800596FC(work);

    pTarget2 = work->field_89C_pTarget;
    pTarget2->field_2C_vec = work->control.step;
    GM_PushTarget_8002DA14(pTarget2);

    if (GM_Camera_800B77E8.first_person != 0)
    {
        GV_NearExp4V(&gUnkCameraStruct_800B77B8.eye.vx, &work->field_A60.vx, 3);
    }
    else
    {
        gUnkCameraStruct_800B77B8.eye = vec2;
    }

    GM_PlayerPosition_800ABA10 = vec = work->control.mov;

    if ( sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK16) )
    {
        GM_PlayerPosition_800ABA10 = work->field_A60;
        GM_MoveTarget_8002D500(work->field_89C_pTarget, &work->field_A60);
    }

    vec.vy = level = work->control.levels[0];
    GM_PlayerAddress_800AB9F0 = work->field_844 = HZD_GetAddress_8005C6C4(work->control.map->hzd, &vec, work->field_844);

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_INTRUDE) )
    {
        if ( gUnkCameraStruct_800B77B8.eye.vy < (level + 150) )
        {
            gUnkCameraStruct_800B77B8.eye.vy = level + 150;
        }
        else if ( gUnkCameraStruct_800B77B8.eye.vy > (level + 250) )
        {
            gUnkCameraStruct_800B77B8.eye.vy = level + 250;
        }
    }

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_UNK4000);

    if ( GM_CheckPlayerStatusFlag_8004E29C(3) )
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_UNK4000);
    }
}

void sna_kill_8005B52C(SnaInitWork *work)
{
    CONTROL      *pCtrl;
    DG_PRIM      *pPrims;
    GV_ACT       *pShadow;
    GV_ACT       *pWeapon;
    GV_ACT       *pItem;

    pCtrl = &work->control;
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->field_9C_obj);
    GM_FreeTarget_8002D4B0(work->field_89C_pTarget);

    pPrims = work->field_92C;
    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }

    GM_PlayerStance = work->field_A26_stance;

    pShadow = work->field_888_pShadow;
    if (pShadow)
    {
        GV_DestroyOtherActor(pShadow);
    }

    pWeapon = work->field_908_weapon_actor;
    if (pWeapon)
    {
        GV_DestroyOtherActor(pWeapon);
    }

    pItem = work->field_9A4_item_actor;
    if (pItem)
    {
        GV_DestroyOtherActor(pItem);
    }

    if (GM_PlayerControl_800AB9F4 == pCtrl)
    {
        GM_PlayerControl_800AB9F4 = 0;
    }

    if (GM_PlayerBody_800ABA20 == &work->field_9C_obj)
    {
        GM_PlayerBody_800ABA20 = 0;
    }

    snainit_actor_800A9424 = NULL;
}

static inline int sna_LoadSnake2(SnaInitWork *work)
{
    SVECTOR  *temp_s1;
    SVECTOR  *temp_s2;
    DG_PRIM  *pPrim;
    DG_TEX   *pTex;
    POLY_GT4 *pPoly;
    int      i, j;

    temp_s1 = &work->field_930;
    pPrim = DG_GetPrim(22, 2, 0, temp_s1, 0);

    if (!pPrim)
    {
        return -1;
    }

    pTex = DG_GetTexture_8001D830(PCX_LSIGHT);
    work->field_928 = pTex;

    if (!pTex)
    {
        return -1;
    }

    pPrim->field_2E_k500 = 500;

    for (i = 0; i < 2; i++)
    {
        pPoly = &pPrim->packs[i]->poly_gt4;

        for (j = 0; j < 2; j++)
        {
            LSTORE(0, &pPoly->r0);
            LSTORE(0x808080, &pPoly->r1);
            LSTORE(0, &pPoly->r2);
            LSTORE(0x808080, &pPoly->r3);
            setPolyGT4(pPoly);
            setSemiTrans(pPoly, 1);
            pPoly->tpage = pTex->tpage;
            pPoly->clut = pTex->clut;
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
    work->field_92C = pPrim;
    return 0;
}

static inline void sna_LoadSnake3(SnaInitWork *work)
{
    u_short t1, t2;
    short   stance;
    short   temp_a1;
    int     temp_v1_3;
    int     var_s0_2;
    int     var_v_2;

    stance = work->field_A26_stance = GM_PlayerStance;
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

    work->field_844 = -1;
    work->field_91C_weapon_idx = -2;

    sna_weapon_switching_800511BC(work, 0);

    work->field_9A8_current_item = ITEM_NONE;

    sna_800515BC(work, 0);

    work->field_9B4_action_table = &weapon_actions_8009ED8C[GM_CurrentWeaponId];
    work->field_A28 = 450;
    work->field_A44 = work->control.mov;
    work->field_A60 = work->control.mov;

    gUnkCameraStruct_800B77B8.eye = work->field_A60;

    if (GCL_GetOption('o')) // oar
    {
        work->field_A5A = GCL_StrToInt(GCL_GetParamResult());
    }

    work->field_890_autoaim_max_dist = 6000;

    if (GCL_GetOption('l')) // len
    {
        work->field_890_autoaim_max_dist = GCL_StrToInt(GCL_GetParamResult());
    }

    work->field_892_autoaim_min_angle = 512;

    if (GCL_GetOption('r')) // rot
    {
        work->field_892_autoaim_min_angle = GCL_StrToInt(GCL_GetParamResult());
    }

    dword_800ABBDC = -1023;
    dword_800ABBD4 = 1023;

    if (GCL_GetOption('t')) // turn
    {
        dword_800ABBDC = GCL_StrToInt(GCL_GetParamResult());
        dword_800ABBD4 = GCL_StrToInt(GCL_GetParamResult());
    }

    work->field_A70 = -1;

    if (GCL_GetOption('e')) // exec
    {
        work->field_A70 = GCL_StrToInt(GCL_GetParamResult());
    }

    temp_a1 = work->field_A26_stance;

    if (temp_a1 == 3)
    {
        work->field_A26_stance = 2;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_GROUND | PLAYER_INTRUDE);
        DG_InvisibleObjs(work->field_9C_obj.objs);
        sna_8004EC8C(work);
        sna_start_anim_8004E1F4(work, &sna_anim_duct_move_80054424);
        GM_Camera_800B77E8.first_person = 2;
        var_v_2 = sna_8004EAA8(work, 2);
    }
    else
    {
        var_s0_2 = sna_8004EAA8(work, temp_a1);

        if ((work->field_9AC & 1) || (work->field_920_tbl_8009D580 & 0x20))
        {
            if ((unsigned int)(work->field_9A8_current_item - 2) < 3)
            {
                var_s0_2 = 4;
            }
        }
        else
        {
            sna_start_anim_8004E1F4(work, dword_8009EEA4[work->field_A26_stance]);
        }

        var_v_2 = var_s0_2;
    }

    GM_ConfigObjectAction_80034CD4(&work->field_9C_obj, var_v_2, 0, 0);
    GM_ActMotion_80034A7C(&work->field_9C_obj);

    temp_v1_3 = (short)work->field_9C_obj.field_18;

    work->field_798_p_height = temp_v1_3;
    work->control.height = temp_v1_3;

    work->field_9B0_pad_ptr = GV_PadData_800B05C0;
}

static inline void sna_LoadSnake4( POLY_FT4 *packs, int n_packs, DG_TEX *tex )
{
    char u, v;
    int  i;

    u = tex->off_x;
    v = tex->off_y;

    for ( i = 0; i < n_packs; i ++ )
    {
        setPolyFT4( packs );
        setSemiTrans( packs, 1 );
        setRGB0( packs, 128, 128, 128 );
        setXY4( packs, 255, 164, 303, 164, 255, 176, 303, 176 );
        setUV4( packs, u, v, u + 48, v, u, v + 12, u + 48, v + 12 );
        packs->tpage = tex->tpage;
        packs->clut = tex->clut;
        packs ++ ;
    }
}

static inline int sna_LoadSnake(SnaInitWork *work, int scriptData, int scriptBinds)
{
    CONTROL    *pCtrl;
    OBJECT        *pObject;
    TARGET *pTarget;
    HITTABLE *pJiraiUnk;
    SVECTOR       shadow;
    SVECTOR       vec;
    SVECTOR       *pVec;
    int           tmp, model, i;
    char          *param_pos, *param_dir;

    pCtrl = &work->control;
    if (GM_InitControl_8002599C(pCtrl, scriptData, scriptBinds) < 0)
    {
        return -1;
    }

    param_pos = (char*)GCL_GetOption('p'); // pos
    param_dir = (char*)GCL_GetOption('d'); // dir
    GM_ConfigControlString_800261C0(pCtrl, param_pos, param_dir);
    GM_ConfigControlHazard_8002622C(pCtrl, 0, 450, 450);

    tmp = 1;
    pCtrl->field_59 = tmp;

    GM_ConfigControlAttribute_8002623C(pCtrl, tmp);
    GM_ConfigControlTrapCheck_80026308(pCtrl);


    pObject = &work->field_9C_obj;

    model = KMD_SNAKE;
    if (GCL_GetOption('m')) // model
    {
        model = GCL_StrToInt(GCL_GetParamResult());
    }

    GM_InitObject_80034A18(pObject, model, BODY_FLAG, OAR_SNAKE);

    GM_ConfigObjectJoint_80034CB4(pObject);
    GM_ConfigMotionControl_80034F08(pObject,
                                    &work->field_180,
                                    OAR_SNAKE,
                                    &work->field_1D0[0],
                                    &work->field_1D0[17],
                                    pCtrl,
                                    (SVECTOR *)&work->field_698_joint_rotations);
    GM_ConfigObjectLight_80034C44(pObject, &work->field_848_lighting_mtx);

    GM_PlayerControl_800AB9F4 = pCtrl;
    GM_PlayerPosition_800ABA10 = work->control.mov;
    GM_PlayerBody_800ABA20 = pObject;

    sna_8004EB14(work);

    if (sna_LoadSnake2(work) < 0)
    {
        return -1;
    }

    sna_LoadSnake3(work);

    pVec = &vec;
    setVector(pVec, 300, 650, 300);

    pTarget = work->field_89C_pTarget = GM_AllocTarget_8002D400();

    GM_SetTarget_8002DC74(pTarget, 159, PLAYER_SIDE, pVec);
    GM_Target_8002DCCC(pTarget, 1, -1, GM_SnakeCurrentHealth, 0, &DG_ZeroVector_800AB39C);
    GM_Target_8002DCB4(pTarget, 0, 0, &work->field_8F4, &work->field_8FC);
    GM_MoveTarget_8002D500(pTarget, &work->control.mov);

    work->field_A22_snake_current_health = GM_SnakeCurrentHealth;

    sna_LoadSnake4(work->field_950, 2, DG_GetTexture_8001D830(PCX_EMPTY2));

    shadow.vx  = 0;
    shadow.vy  = 6;
    shadow.vz  = 12;
    shadow.pad = 15;

    work->field_888_pShadow = NewShadow2_80060384(pCtrl, pObject, shadow, &work->field_88C);

    dword_800ABA1C = 0;
    GM_BombSeg_800ABBD8 = 0;

    for (i = 0; i < 16; i++)
    {
        tenage_ctrls_800BDD30[i] = NULL;
    }

    dword_800BDD28 = 0;
    tenage_ctrls_count_800BDD70 = 0;

    pJiraiUnk = c4_actors_800BDD78;
    i = 0;

    while (i < C4_COUNT)
    {
        i++;
        pJiraiUnk->type = WEAPON_C4;
        pJiraiUnk->actor = NULL;
        pJiraiUnk++;
    }

    dword_8009F434 = 0;
    bakudan_count_8009F42C = 0;

    pJiraiUnk = stru_800BDE78;
    i = 0;

    while (i < 8)
    {
        i++;
        pJiraiUnk->type = WEAPON_CLAYMORE;
        pJiraiUnk->actor = NULL;
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
        sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK29);
    }

    return 0;
}

// Unused strings left in binary for some reason
const char aPosDDD[] = "pos %d %d %d\n";
const char aTurnDDD[] = "turn %d %d %d\n";
const char aCeilFloorDD[] = "ceil floor %d %d\n";
const char aStatus4x[] = "status %4x\n";
const char aWeaponD[] = "weapon %d\n";
const char aItemD[] = "item %d\n";
const char aFlag4x[] = "flag %4x\n";
const char aStanceD[] = "stance %d\n";
const char aPadtoD[] = "padto %d\n";
const char aTrapCheckD[] = "trap check %d\n";
const char aPadX[] = "pad %x\n";
const char aKaze[] = "kaze \n";

GV_ACT *sna_NewSnake_8005B650(int name, int where, int argc, char **argv)
{
    SnaInitWork *work;

    work = (SnaInitWork *)GV_NewActor(5, sizeof(SnaInitWork));
    if (!work)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor,
                     (TActorFunction)&sna_act_8005AD10,
                     (TActorFunction)&sna_kill_8005B52C,
                     "../snake_vr/sna_init.c");

    if (sna_LoadSnake(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    snainit_actor_800A9424 = work;
    return &work->actor;
}
