#include "sna_init.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "map/map.h"
#include "Game/object.h"
#include "Kojo/demothrd.h"
#include "Game/game.h"
#include "unknown.h"
#include "Okajima/blood.h"
#include "Bullet/bakudan.h"
#include "homing_target.h"
#include "vibrate.h"
#include "psyq.h"

extern SVECTOR stru_8009EFC0;
extern SVECTOR stru_8009EFC8;
extern int     dword_8009EFD0;

extern Target_Data stru_8009EFE4;

extern Sna_E1 e1_800AB7C4;
Sna_E1        SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int        SECTION(".sbss") dword_800ABBA8;

extern int gSnaMoveDir_800ABBA4;
int        SECTION(".sbss") gSnaMoveDir_800ABBA4;

extern int dword_800ABBB4;
int        SECTION(".sbss") dword_800ABBB4;

extern GM_Control *gSnaControl_800AB9F4;
extern OBJECT     *dword_800ABA20;

extern int dword_800ABBB8;
int        SECTION(".sbss") dword_800ABBB8;

extern int dword_800ABB9C[2];
int        SECTION(".sbss") dword_800ABB9C[2];

extern int dword_800ABBC4;
int        SECTION(".sbss") dword_800ABBC4;

extern SVECTOR *pVec_800ABBCC;
SVECTOR        *SECTION(".sbss") pVec_800ABBCC;

extern int dword_800ABBD0;
int        SECTION(".sbss") dword_800ABBD0;

extern short dword_800ABBDC;
short        SECTION(".sbss") dword_800ABBDC;

extern short dword_800ABBD4;
short        SECTION(".sbss") dword_800ABBD4;

extern int dword_800ABBB0;
int        SECTION(".sbss") dword_800ABBB0;

extern GM_Target *GM_BombSeg_800ABBD8; // probably wrong type?
GM_Target        *SECTION(".sbss") GM_BombSeg_800ABBD8;

extern int                GM_AlertMode_800ABA00;
extern GameState_800B4D98 gGameState_800B4D98;
extern int                GM_GameOverTimer_800AB3D4;
extern int                GM_GameStatus_800AB3CC;
extern SVECTOR            DG_ZeroVector_800AB39C;
extern PlayerStatusFlag   GM_PlayerStatus_800ABA50;
extern Target_Data        stru_8009F044;
extern SVECTOR            stru_800AB7FC;
extern short              dword_800B7800[];
extern SVECTOR            dword_800AB7D4;
extern SVECTOR            dword_800AB7DC;
extern unsigned short     GM_WeaponTypes_8009D580[];
extern Sna_ActionTable    actions_no_weapon_8009ED70;
extern int                GM_ItemTypes_8009D598[];
extern int                dword_8009EEA4[];
extern int                GV_Time_800AB330;
extern int                used_counter_8009F42C;
extern SVECTOR            dword_800AB7EC;
extern SVECTOR            dword_800AB7F4;
extern int                gSnaMoveDir_800ABBA4;
extern int                DG_UnDrawFrameCount_800AB380;
extern int                dword_8009EF24[];
extern int                dword_8009EF2C[];
extern SVECTOR            dword_800AB7CC;

void sna_init_start_anim_8004E1F4(Actor_SnaInit *pActor, void *pFn)
{
    short vec_x = 0;
    pActor->field_9B8_fn_anim = pFn;
    pActor->field_9BC_anim_frame = 0;
    pActor->field_A3A = 0;
    pActor->field_A38 = 0;

    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_PRONE) != 0)
    {
        vec_x = pActor->field_A2A;
    }

    pActor->field_20_ctrl.field_4C_turn_vec.vx = vec_x;
    pActor->field_20_ctrl.field_4C_turn_vec.vz = 0;
}

void sna_init_8004E22C(Actor_SnaInit *pActor, int action_flag, int interp)
{
    if (pActor->field_9C_obj.action_flag != action_flag)
    {
        GM_ConfigObjectAction_80034CD4(&pActor->field_9C_obj, action_flag, 0, interp);
    }
}

void sna_init_8004E260(Actor_SnaInit *pActor, int a2, int interp, int a4)
{
    if (pActor->field_9C_obj.field_10 != a2)
    {
        GM_ConfigObjectOverride_80034D30(&pActor->field_9C_obj, a2, 0, interp, a4);
    }
}

int GM_CheckPlayerStatusFlag_8004E29C(PlayerStatusFlag arg0)
{
    return (GM_PlayerStatus_800ABA50 & arg0) != 0;
}

int GM_SetPlayerStatusFlag_8004E2B4(PlayerStatusFlag arg0)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus_800ABA50 | arg0;
    GM_PlayerStatus_800ABA50 = temp_v0;
    return temp_v0;
}

void GM_ClearPlayerStatusFlag_8004E2D4(PlayerStatusFlag flag)
{
    GM_PlayerStatus_800ABA50 &= ~flag;
}

void sna_init_set_flags1_8004E2F4(Actor_SnaInit *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void sna_init_clear_flags1_8004E308(Actor_SnaInit *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int sna_init_check_flags1_8004E31C(Actor_SnaInit *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}

void sna_init_set_flags2_8004E330(Actor_SnaInit *snake, SnaFlag2 flag)
{
    snake->field_898_flags2 |= flag;
}

void sna_init_clear_flags2_8004E344(Actor_SnaInit *snake, SnaFlag2 flags)
{
    snake->field_898_flags2 &= ~flags;
}

unsigned int sna_init_sub_8004E358(Actor_SnaInit *snake, SnaFlag2 param_2)
{
    unsigned int result = 0;

    if (gGameState_800B4D98.field_BE != 0)
    {
        result = (((unsigned int)snake->field_898_flags2 & param_2) != result);
    }

    return result;
}

void sna_init_check_dead_8004E384(Actor_SnaInit *snake)
{
    if ((gGameState_800B4D98.field_16_snake_current_health == 0) || (GM_GameOverTimer_800AB3D4 != 0))
    {
        snake->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags1_8004E2F4(snake, SNA_FLAG1_UNK23);
        GM_GameStatus_800AB3CC |= 0x10080000;

        if (GM_GameOverTimer_800AB3D4 != -2)
        {
            sna_init_set_flags1_8004E2F4(snake, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        }
    }
}

void sna_init_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags)
{
    GM_Target *target = snake->field_8E8_pTarget;

    if (target != NULL)
    {
        target->field_6_flags &= ~flags;
        snake->field_8E8_pTarget = 0;
        snake->field_A54.choke_count = 0;
        snake->field_89C_pTarget->field_10_size.vx = 300;
    }
}

// ... categorize move/turn direction by angle?
// param_1: snake->field_20_ctrl.field_4C_turn_vec.vy
// param_2: gSnaMoveDir_800ABBA4
int sub_8004E458(short param_1, int param_2)
{
    short uVar2;

    if (param_2 < 0)
    {
        return 0;
    }

    uVar2 = (param_2 - param_1) & 0xFFF;

    if (uVar2 < 0x800)
    {
        if (uVar2 < 0x100)
        {
            return 1;
        }
        else if (uVar2 > 0x500)
        {
            return 3;
        }

        return 4;
    }
    else
    {
        if (uVar2 > 0xF00)
        {
            return 1;
        }
        else if (uVar2 < 0xB00)
        {
            return 3;
        }

        return 2;
    }
}

int sub_8004E4C0(int unused, int param_2)
{
    int iVar1;

    if (-1 < dword_800ABBA8)
    {
        if ((*(char *)dword_800ABBB4 & 0x40) != 0)
        {
            return param_2;
        }
        iVar1 = (param_2 - dword_800ABBA8) & 0xfff;
        if (iVar1 < 0x400)
        {
            param_2 = dword_800ABBA8 + 0x400;
        }
        if (iVar1 > 0xc00)
        {
            param_2 = dword_800ABBA8 - 0x400;
        }
    }
    return param_2;
}

int sub_8004E51C(SVECTOR *param_1, void *param_2, int param_3, int param_4)
{
    if (sub_80028454(param_2, param_1, &param_1[1], param_3, param_4) == 0)
    {
        return -1;
    }
    sub_80028890(&param_1[1]);
    GV_SubVec3_80016D40(&param_1[1], param_1, param_1);
    return GV_VecLen3_80016D80(param_1);
}

void sub_8004E588(HZD_MAP *param_1, SVECTOR *param_2, int *param_3)
{
    unsigned int uVar1;

    uVar1 = sub_800296C4(param_1, param_2, 3);
    sub_800298DC(param_3);
    if ((uVar1 & 1) == 0)
    {
        *param_3 = 0xffff8001;
    }
    if ((uVar1 & 2) == 0)
    {
        param_3[1] = 0x7fff;
    }
}

int sub_8004E5E8(Actor_SnaInit *pActor, int flag)
{
    int     i;
    SVECTOR vec;
    int     unk1[2];
    int     unk2[2];

    vec.vx = pActor->field_9C_obj.objs->objs[4].world.t[0];
    vec.vy = pActor->field_9C_obj.objs->objs[4].world.t[1];
    vec.vz = pActor->field_9C_obj.objs->objs[4].world.t[2];

    DG_SetPos2_8001BC8C(&vec, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutVector_8001BE48(&dword_800AB7CC, &vec, 1);
    sub_8004E588(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &vec, unk1);

    i = -1;

    if ((sub_80029A2C() & flag) == 0)
    {
        sub_800298C0(unk2);

        if (vec.vy - unk1[0] < 350)
        {
            i = 0;
        }
        else if (unk1[1] - vec.vy < 125)
        {
            i = 1;
        }

        if (i >= 0)
        {
            if (!unk2[i])
            {
                GM_BombSeg_800ABBD8 = 0;
            }
            else
            {
                GM_BombSeg_800ABBD8 = (GM_Target *)(unk2[i] & ~0x80000000);
            }

            return 1;
        }
    }

    return 2;
}

#pragma INCLUDE_ASM("asm/sub_8004E71C.s") // 236 bytes

// https://decomp.me/scratch/P8McA
#pragma INCLUDE_ASM("asm/sub_8004E808.s") // 296 bytes

int sub_8004E930(Actor_SnaInit *snake, int arg1)
{
    int     int0;
    int     int1;
    SVECTOR vec0;
    SVECTOR vec1;

    vec0.vy = 0;
    vec0.vx = 0;
    vec0.vz = (short)arg1;
    DG_PutVector_8001BE48(&vec0, &vec0, 1);

    int1 = HZD_SlopeFloorLevel_800298F8(&vec0.vx, dword_800ABBB8);
    int1 -= snake->field_20_ctrl.field_78;

    vec1.vx = int1;
    vec1.vz = SquareRoot0_80092708(arg1 * arg1 - int1 * int1);
    int0 = -GV_VecDir2_80016EF8(&vec1);

    if (int0 < -0x800)
    {
        int0 += 0x1000;
    }

    return int0;
}

void sub_8004E9D0(Actor_SnaInit *pActor)
{
    int iVar1;

    if (dword_800ABBB8 != 0)
    {
        iVar1 = sub_8004E930(pActor, 500);
        iVar1 = iVar1 / 2;
    }
    else
    {
        iVar1 = 0;
    }

    pActor->field_718[1].vx = GV_NearExp2_80026384(pActor->field_718[1].vx, iVar1);
    pActor->field_718[4].vx = GV_NearExp2_80026384(pActor->field_718[4].vx, -iVar1);
    pActor->field_718[9].vx = GV_NearExp2_80026384(pActor->field_718[9].vx, -iVar1);
}

void sub_8004EA50(int param_1, int param_2)
{
    unsigned int uVar1;

    uVar1 = GV_DiffDirS_8001704C(param_2, (int)*(short *)(param_1 + 0x2a));
    if ((int)uVar1 >= 0x81)
    {
        uVar1 = 0x80;
    }
    else if ((int)uVar1 < -0x80)
    {
        uVar1 = 0xffffff80;
    }
    *(short *)(param_1 + 0x70) = (short)uVar1;
    return;
}

int sna_init_8004EAA8(Actor_SnaInit *pActor, int a2)
{
    if (a2 == 0)
    {
        return pActor->field_9B4_action_table->field_0->field_0;
    }

    if (a2 == 1)
    {
        return pActor->field_9B4_action_table->field_0->field_2;
    }

    if (a2 == 2)
    {
        return pActor->field_9B4_action_table->field_0->field_3;
    }

    return -1;
}

#pragma INCLUDE_ASM("asm/sub_8004EB14.s") // 96 bytes

void sub_8004EB74(Actor_SnaInit *pActor)
{
    if (dword_800B7800[5] == 0)
    {
        if (pActor->field_9B0_pad_ptr->dir == (short)-1)
        {
            pActor->field_A20 = -6;
        }
        else
        {
            pActor->field_A20 = -3;
        }
    }

    dword_800B7800[5] = 1;
    pActor->field_A56 = 0;
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON);

    if (gGameState_800B4D98.field_BE == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
    }

    sd_set_cli_800887EC(0x1ffff20, 0);
}

// TODO: Not confirmed if this structure is correct yet
demothrd_2Vec SECTION(".word_800B77E8") stru_800B77E8[9];

void sna_init_8004EC00(Actor_SnaInit *pActor)
{
    if (stru_800B77E8[2].field_0.vy == 1)
    {
        pActor->field_A20 = 6;
    }

    stru_800B77E8[2].field_0.vy = 0;
    pActor->field_A56 = 0;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
    sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK16);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        sd_set_cli_800887EC(0x1ffff21, 0);
    }

    sna_init_clear_flags2_8004E344(pActor, (SNA_FLAG2_UNK5 | SNA_FLAG2_UNK6));
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK400);
}

void sna_init_8004EC8C(Actor_SnaInit *pActor)
{
    ushort v2; // $v1

    sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK12);
    pActor->field_A28 = 460;
    dword_800B7800[5] = 1;
    v2 = *(ushort *)&e1_800AB7C4.field_4;
    pActor->field_A20 = -6;
    pActor->field_9D0[0].vz = 320;
    pActor->field_9D0[1].vx = v2;
    pActor->field_9D0[1].vz = v2;
    sd_set_cli_800887EC(0x1FFFF20, 0);
    sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK5);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON);
}

void sub_8004ED08(Actor_SnaInit *pActor)
{
    sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK12);
    pActor->field_A28 = 0x1c2;
    dword_800B7800[5] = 0; // weapon related?
    pActor->field_A20 = 6;
    sub_8004EB14(pActor);
    sd_set_cli_800887EC(0x1ffff21, 0);
    sna_init_clear_flags2_8004E344(pActor, (SNA_FLAG2_UNK5 | SNA_FLAG2_UNK6));
}

void sna_init_act_helper2_helper3_8004ED6C(Actor_SnaInit *snake)
{
    if (snake->field_A20 != 0)
    {
        if (snake->field_A20 >= 1)
        {

            if ((dword_800B7800[5] == 0) && (--snake->field_A20 == 0))
            {
                (snake->field_9C_obj).objs->flag &= -0x81;
                if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK4))
                {
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
                }
            }
        }
        else if ((dword_800B7800[5] != 0) && (++snake->field_A20 == 0))
        {
            (snake->field_9C_obj).objs->flag |= 0x80;
        }
    }
}

UnkMaybeCameraStruct SECTION(".gUnkMaybeCameraStruct_800B77B8") gUnkMaybeCameraStruct_800B77B8;
void                 sna_init_8004EE28(Actor_SnaInit *snake)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR vec;
    int     vx;
    MATRIX *world = &snake->field_9C_obj.objs->objs[6].world;

    ReadRotMatrix_80092DD8(&mat1);
    DG_TransposeMatrix_8001EAD8(&mat1, &mat2);
    MulMatrix0_80092A48(&mat2, world, &mat2);
    DG_MatrixRotZYX_8001E92C(&mat2, &vec);
    SetRotMatrix_80093218(&mat1);
    vx = vec.vx;
    if (vx < 0)
    {
        vx += 0xf;
    }
    vx &= 0xfff0;
    gUnkMaybeCameraStruct_800B77B8.field_28_aim_assist.vx = vx;
}

void sub_8004EEB0(Actor_SnaInit *pActor)
{
    short sVar1;
    int   iVar2;
    int   arg0;

    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        arg0 = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        if (GV_DiffDirS_8001704C(arg0, gSnaMoveDir_800ABBA4))
        {
            iVar2 = sub_80026418(arg0, gSnaMoveDir_800ABBA4);
            sVar1 = sub_8002646C(iVar2, gSnaMoveDir_800ABBA4, 0x40);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = sVar1;
        }
    }
}

// https://decomp.me/scratch/k2Awn regswap
#pragma INCLUDE_ASM("asm/sub_8004EF14.s") // 208 bytes

int sub_8004EFE4(Actor_SnaInit *pActor, int param_2)
{
    int      ret;
    SVECTOR *vec; // not sure if correct

    if (param_2 == 1)
    {
        vec = (SVECTOR *)&pActor->field_180.field_04;
    }
    else
    {
        vec = (SVECTOR *)&pActor->field_180.field_1C;
    }

    if (param_2 == 1)
    {
        ret = pActor->field_9C_obj.action_flag;
    }
    else
    {
        ret = pActor->field_9C_obj.field_10;
    }

    if (vec->vx + vec->vy == 1)
    {
        return ret;
    }

    return -1;
}

void sna_init_8004F034(Actor_SnaInit *pActor, unsigned int bits)
{
    if ( bits != pActor->field_180.field_04.field_8 )
    {
        pActor->field_180.field_1C.field_8 = ~bits;
        pActor->field_180.field_04.field_8 = bits;
        if ( bits == 0xFFFF && sub_8004EFE4(pActor, 2) >= 0 )
        {
            pActor->field_180.interp = 4;
            pActor->field_180.field_1C.field_14 = 2;
        }
    }
}

void sna_init_act_helper2_helper4_8004F090(Actor_SnaInit *pActor, int param_2)
{
    int    iVar1;
    MATRIX mtx;

    DG_SetPos_8001BC44(&pActor->field_9C_obj.objs->objs[6].world);
    DG_MovePos_8001BD20(&dword_800AB7D4);
    DG_RotatePos_8001BD64(&dword_800AB7DC);
    ReadRotMatrix_80092DD8(&mtx);

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

void sub_8004F14C(Actor_SnaInit *param_1)
{
    param_1->field_91C_weapon_idx = WEAPON_NONE;
    gGameState_800B4D98.field_1C_equipped_weapon = WEAPON_NONE;

    if (param_1->field_908_weapon_actor != 0)
    {
        GV_DestroyActorQuick_80015164(param_1->field_908_weapon_actor);
    }

    param_1->field_908_weapon_actor = 0;
    param_1->field_920_tbl_8009D580 = GM_WeaponTypes_8009D580[0];
    param_1->field_918_pWeaponState = 0;
    param_1->field_9B4_action_table = &actions_no_weapon_8009ED70;
    param_1->field_90C_pWeaponFn = sna_init_anim_chokethrow_begin1_80054210;
    param_1->field_910 = 0;
    param_1->field_926 = 0;
    param_1->field_924 = 0;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        param_1->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    }
    else
    {
        sna_init_8004EC00(param_1);
    }
}

void sub_8004F204(Actor_SnaInit *param_1)
{
    if (param_1->field_9A4_item_actor != 0)
    {
        GV_DestroyActorQuick_80015164(param_1->field_9A4_item_actor);
    }

    param_1->field_9A4_item_actor = 0;
    param_1->field_9A8 = -1;
    gGameState_800B4D98.field_1E_equipped_item = -1;
    param_1->field_9AC = (unsigned short)GM_ItemTypes_8009D598[0];

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        param_1->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    }
    else
    {
        sna_init_8004EC00(param_1);
    }

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK1000);
}

void sna_init_set_invuln_8004F2A0(Actor_SnaInit *pActor, char invuln_frames)
{
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_INVULNERABLE);
    pActor->field_A24_invuln_frames = invuln_frames;
    pActor->field_89C_pTarget->field_0_flags &= ~0x96u;
}

void sna_init_clear_invuln_8004F2EC(Actor_SnaInit *snake)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_INVULNERABLE);
    sna_init_clear_flags1_8004E308(snake, SNA_FLAG1_UNK1);
    snake->field_89C_pTarget->field_0_flags |= 0x9e;
}

void sub_8004F338(Actor_SnaInit *param_1)
{
    int iVar2;

    iVar2 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT);
    if (iVar2 != 0)
    {

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
        param_1->field_A56 = 0;
    }
    else
    {
        sna_init_8004EC00(param_1);
    }

    sna_init_clear_invuln_8004F2EC(param_1);
    param_1->field_A24_invuln_frames = 0;
    sna_init_sub_8004E41C(param_1, 2);
    GM_ConfigMotionAdjust_80035008(&param_1->field_9C_obj, 0);
    sna_init_clear_flags1_8004E308(param_1, SNA_FLAG1_UNK9);
    param_1->field_9C0 = 0;
    sna_init_8004E260(param_1, 0, 4, 0);
    param_1->field_92C->def = (DG_DEF *)((int)param_1->field_92C->def | 0x100);
    GM_ExitBehindCamera_80030AEC();

    GM_PlayerStatus_800ABA50 &= PLAYER_STATUS_CAN_USE_CONTROLLER_PORT_2 | PLAYER_STATUS_UNK4000000 |
                                PLAYER_STATUS_GAMEOVER | PLAYER_STATUS_UNK1000 | PLAYER_STATUS_FIRST_PERSON_DUCT |
                                PLAYER_STATUS_UNK4 | PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE;

    if ((param_1->field_920_tbl_8009D580 & 0x200U) != 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON);
    }

    param_1->field_A28 = 0x1c2;
    param_1->field_894_flags1 &= (SNA_FLAG1_UNK20 | SNA_FLAG1_UNK28 | SNA_FLAG1_UNK29);
    param_1->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK9);
}

#pragma INCLUDE_ASM("asm/sub_8004F454.s")      // 240 bytes
#pragma INCLUDE_ASM("asm/sub_8004F544.s")      // 228 bytes
#pragma INCLUDE_ASM("asm/sub_8004F628.s")      // 192 bytes
#pragma INCLUDE_ASM("asm/OPERATOR_8004F6E8.s") // 508 bytes
#pragma INCLUDE_ASM("asm/sna_init_8004F8E4.s") // 344 bytes

int sna_act_unk_helper4_8004FA3C(void)
{
    if (gGameState_800B4D98.field_16_snake_current_health == 0 || GM_GameOverTimer_800AB3D4 != 0)
    {
        return 1;
    }
    return 0;
}

void sna_init_8004FA74(Actor_SnaInit *param_1)
{
    sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                      PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK);
}

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = snake->field_9B0_pad_ptr->status;
    sna_init_80051FD0(snake);
    if (action & PAD_DOWN)
    {
        sna_init_set_flags2_8004E330(snake, SNA_FLAG2_UNK1);
    }
}

void sub_8004FAE8(Actor_SnaInit *snake)
{
    SVECTOR vec;

    DG_MatrixRotYXZ_8001E734(&snake->field_9C_obj.objs->objs[6].world, &vec);
    gUnkMaybeCameraStruct_800B77B8.field_28_aim_assist = vec;
}

int sub_8004FB38(void)
{
    return *(int *)(dword_800ABB9C[1] + 0x9a8);
}

#pragma INCLUDE_ASM("asm/sub_8004FB4C.s") // 68 bytes

int *sub_8004FB90(void)
{
    return &dword_800ABBB8;
}

unsigned char SECTION(".gRadioMemory_800BDB38") gBulNames_800BDC78[64];

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

    if ((gGameState_800B4D98.field_04_flags & 0x1000) != 0 && (GM_GameStatus_800AB3CC & 0x40000000) == 0)
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
            *pInput |= 0x1000u;
        }
    }
}

void GM_CheckShukanReverseAnalog_8004FC70(unsigned char *pInput)
{
    if ((gGameState_800B4D98.field_04_flags & 0x1000) != 0 && (GM_GameStatus_800AB3CC & 0x40000000) == 0)
    {
        *pInput = ~*pInput;
    }
}

int sub_8004FCB8(Actor_SnaInit *snake, UnkSnakeStruct *unkSnakeStruct, int param_3)
{
    int        sub_8004E51C_result;
    GM_Target *pTarget;
    SVECTOR    vec;
    SVECTOR    vec_arr[2];

    pTarget = &snake->field_8A0_target;
    GM_SetTarget_8002DC74(pTarget, 4, 1, &unkSnakeStruct->field_0_vectors[1]);
    DG_RotVector_8001BE98(&unkSnakeStruct->field_0_vectors[2], &vec, 1);
    GM_Target_8002DCCC(pTarget, 3, param_3, unkSnakeStruct->field_18_ints[0], unkSnakeStruct->field_18_ints[1], &vec);
    DG_PutVector_8001BE48(unkSnakeStruct->field_0_vectors, &vec, 1);
    vec_arr[0].vx = snake->field_9C_obj.objs->objs[5].world.t[0];
    vec_arr[0].vy = snake->field_9C_obj.objs->objs[5].world.t[1];
    vec_arr[0].vz = snake->field_9C_obj.objs->objs[5].world.t[2];
    vec_arr[1] = vec;
    sub_8004E51C_result = sub_8004E51C(vec_arr, ((snake->field_20_ctrl).field_2C_map)->field_8_hzd, 0xf, 1);
    if (sub_8004E51C_result < 0)
    {
        GM_Target_SetVector_8002D500(pTarget, &vec);
        return sub_8002D7DC(pTarget);
    }
    return 0;
}

#pragma INCLUDE_ASM("asm/sna_init_8004FDE8.s")                                 // 416 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper5_8004FF88.s") // 276 bytes
#pragma INCLUDE_ASM("asm/sub_8005009C.s")                                      // 348 bytes

void sna_init_check_knock_800501F8(Actor_SnaInit *pActor, int anim_frame)
{
    void *func;

    if (anim_frame >= 8)
    {
        if (pActor->field_91C_weapon_idx != WEAPON_C4 || GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING) != 0)
        {
            if ((pActor->field_9B0_pad_ptr->press & PAD_CIRCLE) != 0)
            {
                func = sna_init_knock_80054D68;
                sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK9);
                pActor->field_9C0 = func;
                pActor->field_9C4 = 0;
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/sub_8005027C.s") // 284 bytes

int sna_init_prone_check_standup_80050398(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0 && sub_8004E808(pActor, 1, 0, 0xfffffd92, 1500) == 0)
    {

        pActor->field_A28 = 450;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_standup_80053D74);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_2, 4);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/sna_init_80050440.s") // 296 bytes

void sna_init_80050568(Actor_SnaInit *pActor)
{
    short    dir;
    DG_OBJS *pDVar3;
    SVECTOR  local_10;

    sna_init_80050440(pActor);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        pDVar3 = pActor->field_9C_obj.objs;
        pActor->field_20_ctrl.field_4C_turn_vec.vz = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
        pActor->field_20_ctrl.field_44_movementVector.vz = 0;
        pActor->field_20_ctrl.field_44_movementVector.vx = 0;
        pDVar3->flag |= 0x80;
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
        pActor->field_A54.prone_bool_thing = 0;
        sna_init_set_invuln_8004F2A0(pActor, 24);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK1);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200 |
                                          PLAYER_STATUS_UNK100);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);

        pDVar3 = (pActor->field_9C_obj).objs;
        // TODO: clean this up
        local_10.vx = *(short *)&pDVar3[8].movs - *(short *)pDVar3[1].world.t;
        pDVar3 = (pActor->field_9C_obj).objs;
        local_10.vz = pDVar3[9].world.m[0][2] - *(short *)(pDVar3[1].world.t + 2);

        dir = GV_VecDir2_80016EF8(&local_10);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dir;
        pActor->field_20_ctrl.field_8_rotator.vy = dir;
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_knockdown_getup_80050668.s") // 368 bytes

int sub_800507D8(Actor_SnaInit *param_1)
{
    int ret;

    if (dword_800ABBC4 == 0 && param_1->field_A38 == 0)
    {
        param_1->field_A28 = 0x1c2;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_KNOCKING | PLAYER_STATUS_ON_WALL | PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(param_1, (void *)dword_8009EEA4[param_1->field_A26_fn_stance_idx]);
        sna_init_clear_flags1_8004E308(param_1, SNA_FLAG1_UNK9);
        param_1->field_9C0 = NULL;
        sna_init_8004E260(param_1, 0, 4, 0);
        GM_ExitBehindCamera_80030AEC();
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_80050878.s") // 492 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_80050A64.s")          // 1804 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk2_80051170.s")         // 76 bytes
#pragma INCLUDE_ASM("asm/sna_init_weapon_switching_800511BC.s")        // 1024 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_800515BC.s")             // 1108 bytes
#pragma INCLUDE_ASM("asm/sub_80051A10.s")                              // 404 bytes
#pragma INCLUDE_ASM("asm/sub_80051BA4.s")                              // 508 bytes
#pragma INCLUDE_ASM("asm/sna_init_80051DA0.s")                         // 560 bytes

void sna_init_80051FD0(Actor_SnaInit *pActor)
{
    int          iVar1;
    ushort       uVar2;
    unsigned int uVar3;
    short        sVar4;
    short        sVar5;
    int          iVar6;
    SVECTOR     *vec_arr;

    vec_arr = pActor->field_9D0;
    uVar2 = pActor->field_9B0_pad_ptr->status;
    if ((uVar2 & (PAD_LEFT | PAD_RIGHT)) != 0)
    {
        iVar1 = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        uVar3 = sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK15);
        sVar4 = 1;
        sVar5 = 1;
        if (uVar2 & PAD_LEFT)
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x40;
                sVar5 = 0x40 - (*((unsigned char *)((short *)pActor->field_9B0_pad_ptr + 7)));
            }
            iVar6 = ((int)vec_arr[2].vx) * (sVar5 & 0xff);
            iVar1 += iVar6 / sVar4;
        }
        else
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x3f;
                sVar5 = (*((unsigned char *)((short *)pActor->field_9B0_pad_ptr + 7))) + 0x40;
            }
            iVar6 = ((int)vec_arr[1].pad) * (sVar5 & 0xff);
            iVar1 -= iVar6 / sVar4;
        }
        pActor->field_20_ctrl.field_4C_turn_vec.vy = iVar1;
    }
}

void sna_init_fn_80052120(Actor_SnaInit *pActor, int anim_frame)
{
    unsigned short press;
    int            sound;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        if (gGameState_800B4D98.field_BE == 0)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }

        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
    }
    else
    {
        press = pActor->field_9B0_pad_ptr->press;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, sna_init_8004EAA8(pActor, (int)pActor->field_A26_fn_stance_idx), 4);

        if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            if (gGameState_800B4D98.field_BE == 0)
            {
                sna_init_8004EC00(pActor);
            }
            else
            {
                sna_init_8004FA74(pActor);
            }

            sna_init_start_anim_8004E1F4(pActor, (void *)dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
        }
        else
        {
            if (sub_80051BA4(pActor) != 0)
            {
                return;
            }

            sna_init_80051DA0(pActor);
            sna_init_80051FD0(pActor);

            if ((press & PAD_CROSS) != 0)
            {
                switch (pActor->field_A26_fn_stance_idx)
                {
                case 0:
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_crouch_800527DC);
                    break;
                case 2:
                    if (sub_8004E808(pActor, 1, 0, -0x26e, 0x5dc) != 0)
                    {
                        return;
                    }
                default:
                    if (sub_8004E808(pActor, 0, 0, 0, 0x5dc) != 0)
                    {
                        return;
                    }

                    pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE);

                    sound = 8;
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
                    {
                        sound = 0xb7;
                    }

                    GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
                    break;
                }
            }
        }
    }
}

void sub_8005230C(Actor_SnaInit *pActor)
{
    int            action;
    unsigned short status;
    unsigned short press;

    status = pActor->field_9B0_pad_ptr->status;
    press = pActor->field_9B0_pad_ptr->press;

    if ((status & PAD_TRIANGLE) == 0)
    {
        sna_init_8004EC00(pActor);
        pActor->field_A38 = 2;
    }
    else
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING) != 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);

            if (pActor->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
            {
                action = pActor->field_9B4_action_table->field_0->field_4;
            }
            else
            {
                action = pActor->field_9B4_action_table->field_0->field_5;
            }

            sna_init_8004E22C(pActor, action, 4);
        }
        if (((press & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) != 0) ||
            ((status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) == 0))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_ON_WALL);
            pActor->field_A28 = 0x1c2;
            sna_init_start_anim_8004E1F4(pActor, (void *)dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
            GM_ExitBehindCamera_80030AEC();
        }

        if (sub_80051BA4(pActor) == 0 && (press & PAD_CROSS) != 0)
        {
            if (pActor->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
            else
            {
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_idle_and_c4_80052A5C);
            }
        }
    }
}

void sub_80052468(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        pActor->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
    }
    else
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);

        if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                              PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
            sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK6);
        }

        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
    }
}

void sna_init_fn_80052540(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        if (gGameState_800B4D98.field_BE == 0)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
    }

    if (pActor->field_9B8_fn_anim == sna_init_anim_knockdown_idle_80054930 &&
        ((pActor->field_9B0_pad_ptr->press & ~PAD_TRIANGLE) != 0))
    {
        sna_init_knockdown_getup_80050668(pActor);
    }

    gUnkMaybeCameraStruct_800B77B8.field_2 += 320;
    sna_init_8004EE28(pActor);
}

void sna_init_fn_800525F8(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    if (pActor->field_9B8_fn_anim != sna_init_anim_box_idle_800553EC)
    {
        if (pActor->field_9C_obj.field_1A)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_2, 4);
        }
    }

    if (!(pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE))
    {
        if (!gGameState_800B4D98.field_BE)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }
    else
    {
        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
    }
}

void sna_init_act_helper2_helper_helper_800526BC(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH |
                                              PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        }
        else if (!gGameState_800B4D98.field_BE)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
    }

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
    {
        sna_init_8004EE28(pActor);
    }
}

void sna_init_anim_idle_8005275C(Actor_SnaInit *pActor, int anim_frame)
{
    int action_flag; // $a1

    if (anim_frame == 0)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_80052E58;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;

        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = pActor->field_9B4_action_table->field_0->field_1;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_0->field_0;
        }

        sna_init_8004E22C(pActor, action_flag, 4);
    }
}

void sna_init_anim_crouch_800527DC(Actor_SnaInit *param_1, int anim_frame)
{
    int sound;

    if (anim_frame == 0)
    {
        if (param_1->field_A26_fn_stance_idx != SNA_STANCE_CROUCH)
        {
            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&param_1->field_20_ctrl.field_0_position, sound);
        }

        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_crouch_helper_80053014;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_2, 4);
        param_1->field_A2E = -128;
    }

    if ((anim_frame == 0 && param_1->field_A26_fn_stance_idx != SNA_STANCE_STANDING) ||
        (anim_frame == 4 && param_1->field_A26_fn_stance_idx == SNA_STANCE_STANDING))
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING);
        param_1->field_A26_fn_stance_idx = SNA_STANCE_CROUCH;
    }
}

void sna_init_anim_prone_idle_800528BC(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        pActor->field_A28 = 450;
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800531F4;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
}

void sna_init_anim_run_8005292C(Actor_SnaInit *pActor, int anim_frame)
{
    int action_flag; // $a1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_80053360;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_7;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_0;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
    }
}

void sna_init_anim_prone_move_800529C0(Actor_SnaInit *pActor, int anim_frame)
{
    int action_flag; // $a1

    if (anim_frame == 0)
    {
        pActor->field_A28 = 450;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800535B8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        if (pActor->field_A54.prone_bool_thing)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54.prone_bool_thing = 0;
    }
    sna_init_80050440(pActor);
}

void sna_init_anim_wall_idle_and_c4_80052A5C(Actor_SnaInit *pActor, int anim_frame)
{
    int sVar3;
    int sound;

    if (anim_frame == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_ON_WALL) == 0)
        {
            sound = 7;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_ON_WALL);
        }

        sVar3 = pActor->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;

        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_idle_and_c4_helper_800537D4;
        pActor->field_A28 = sVar3;
        pActor->field_A26_fn_stance_idx = 0;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_4, 4);
    }

    GM_CheckBehindCamera_80030B3C(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl);

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        (pActor->field_20_ctrl).field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        (pActor->field_20_ctrl).field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }

    return;
}

void sna_init_anim_wall_move_80052BA8(Actor_SnaInit *pActor, int anim_frame)
{
    int action;

    if (anim_frame == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING | PLAYER_STATUS_ON_WALL);
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_move_helper_800538CC;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (pActor->field_A54.wall_thing == 2)
        {
            action = pActor->field_9B4_action_table->field_4->field_5;
        }
        else
        {
            action = pActor->field_9B4_action_table->field_4->field_6;
        }

        pActor->field_A28 = 300;
        pActor->field_A54.wall_thing = 0;
        sna_init_8004E22C(pActor, action, 4);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
    }

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        pActor->field_20_ctrl.field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        pActor->field_20_ctrl.field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }
}

void sna_init_anim_wall_crouch_80052CCC(Actor_SnaInit *pActor, int anim_frame)
{
    int sound;
    int sound2;

    if (anim_frame == 0)
    {
        if (pActor->field_A26_fn_stance_idx != SNA_STANCE_CROUCH)
        {
            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
        }

        pActor->field_A26_fn_stance_idx = SNA_STANCE_CROUCH;
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_crouch_helper_80053A54;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_ON_WALL) == 0)
        {
            sound2 = 7;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound2 = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound2);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
        }

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_ON_WALL);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_5, 4);

        pActor->field_A28 = pActor->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;
    }

    GM_CheckBehindCamera_80030B3C(((pActor->field_20_ctrl).field_2C_map)->field_8_hzd, &pActor->field_20_ctrl);

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        pActor->field_20_ctrl.field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        pActor->field_20_ctrl.field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }
}

void sna_init_fn_80052E58(Actor_SnaInit *pActor)
{
    int action;
    int diff;

    if (sub_8005009C() != 0)
    {
        return;
    }

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_crouch_800527DC);
        return;
    }

    if (GM_AlertMode_800ABA00 >= 3)
    {
        action = pActor->field_9B4_action_table->field_0->field_1;
    }
    else
    {
        action = pActor->field_9B4_action_table->field_0->field_0;
    }

    sna_init_8004E22C(pActor, action, 4);

    if (pActor->field_A38 > 0)
    {
        pActor->field_A38--;
    }

    if (pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_idle_and_c4_80052A5C);
        }
        else
        {
            if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
            {
                diff = GV_DiffDirAbs_8001706C(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4);
                if (diff > 256)
                {
                    pActor->field_A38 = diff / 1024 + 1;
                }
                else
                {
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_begin_80053B88);
                }

                pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4;
            }
            else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_begin_80053B88);
            }
            else
            {
                sna_init_80051FD0(pActor);
            }
        }
    }
}

void sna_init_anim_crouch_helper_80053014(Actor_SnaInit *pActor)
{
    int diff;
    int sound;

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        if (sub_8004E808(pActor, 0, 0, 0, 1100) == 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;

            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }

            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
    }
    else
    {
        if (pActor->field_A38 > 0)
        {
            pActor->field_A38--;
        }

        if (pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
        {
            if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
            else
            {
                if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
                {
                    diff = GV_DiffDirAbs_8001706C(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4);
                    if (diff > 256)
                    {
                        pActor->field_A38 = diff / 1024 + 1;
                    }
                    else
                    {
                        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_begin_80053BE8);
                    }

                    pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4;
                }
                else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
                {
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_begin_80053BE8);

                    if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
                    {
                        pActor->field_20_ctrl.field_4C_turn_vec.vy += 2048;
                    }
                }
                else
                {
                    sna_init_80051FD0(pActor);
                }
            }
        }
    }
}

void sna_init_fn_800531F4(Actor_SnaInit *pActor)
{
    if (pActor->field_A38 > 0)
    {
        pActor->field_A38 -= 1;
    }

    if (!sna_init_prone_check_standup_80050398(pActor) && pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
        {
            if (sub_8004E808(pActor, 0, 0, 0, 1500) == 0)
            {
                pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_ON_WALL);
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
        }
        else
        {
            if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
            {
                if (sub_8004E458(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4) == 3)
                {
                    pActor->field_A54.prone_bool_thing = 1;
                }
                else
                {
                    pActor->field_A54.prone_bool_thing = 0;
                }

                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_move_800529C0);
            }
            else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_move_800529C0);
            }
            else
            {
                sna_init_80051FD0(pActor);
                pActor->field_20_ctrl.field_4C_turn_vec.vx = pActor->field_A2A;
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/sna_init_80053360.s")                                          // 600 bytes
#pragma INCLUDE_ASM("asm/sna_init_fn_800535B8.s")                                       // 540 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_idle_and_c4_helper_800537D4.s") // 248 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_move_helper_800538CC.s")        // 392 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_crouch_helper_80053A54.s")      // 300 bytes

void sna_init_fn_nothing_80053B80(void)
{
}

void sna_init_anim_run_begin_80053B88(Actor_SnaInit *param_1, int anim_frame)
{
    if (anim_frame == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_80054318;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_init_anim_prone_begin_80053BE8(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_0, 4);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        pActor->field_20_ctrl.field_55_flags |= (CONTROL_FLAG_UNK8 | CONTROL_FLAG_UNK2);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
    }

    if (anim_frame == 7)
    {
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK2;
    }

    switch (pActor->field_A38)
    {
    case 0:
        if (pActor->field_798 < 0xfa)
        {
            pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
        }

        if (pActor->field_9C_obj.field_1A != 0)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
            pActor->field_A38 = 1;
        }
        break;
    case 1:
        sna_init_80050440(pActor);

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
            sna_init_set_invuln_8004F2A0(pActor, 0);
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_4->field_3, 4);
        }
        else
        {
            sna_init_clear_flags1_8004E308(pActor, 0x30);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        }
    }
}

void sna_init_anim_prone_standup_80053D74(Actor_SnaInit *pActor, int anim_frame)
{
    int sound;

    if (anim_frame == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_2, 4);

        sound = 8;
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
        {
            sound = 0xb7;
        }
        GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }

    if (pActor->field_20_ctrl.field_32_height >= 250)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height > 500)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
    }

    if (anim_frame == 2)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (anim_frame == 7)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        pActor->field_20_ctrl.field_55_flags &= ~(CONTROL_FLAG_UNK8 | CONTROL_FLAG_UNK2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_init_anim_enter_duct_80053E9C(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800543A8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0 &&
            pActor->field_9C_obj.action_flag == pActor->field_9B4_action_table->field_4->field_4)
        {
            pActor->field_A38 = 48;
        }
        else
        {
            pActor->field_A38 = 24;
        }
    }

    if (anim_frame == pActor->field_A38)
    {
        sna_init_clear_invuln_8004F2EC(pActor);
        sna_init_80050440(pActor);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK9);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        }
    }
}

void sub_80053FAC(Actor_SnaInit *pActor, int anim_frame)
{
    short          vec_y;      // $v1
    unsigned short pad_status; // $s1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_3, 2);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK3);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
        vec_y = pActor->field_A54.prone_bool_thing;
        pActor->field_A54.prone_bool_thing = 0;
        pActor->field_90C_pWeaponFn = sna_init_gun_800540D0;
        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = vec_y;
        sna_init_8004E260(pActor, 0, 4, 0);
    }

    pad_status = pActor->field_9B0_pad_ptr->status;
    if (pActor->field_9C_obj.field_1A || (pad_status & PAD_SQUARE) == 0)
    {
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        pActor->field_910 = 0;
        if ((pad_status & PAD_SQUARE) != 0)
        {
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 9);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
            pActor->field_90C_pWeaponFn = sub_80057BF0;
            pActor->field_910 = 0;
            pActor->field_926 = 0;
            pActor->field_924 = 0;
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
    }
}

void sna_init_gun_800540D0(Actor_SnaInit *pActor, int anim_frame)
{
    int iVar1;
    int a4;

    if (anim_frame == 0)
    {
        iVar1 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING);
        a4 = 0xffff;
        if (iVar1 != 0)
        {
            a4 = 0x3fe;
        }
        sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_10->field_0, 4, a4);
        pActor->field_A38 = 0;
    }

    if ((pActor->field_9B0_pad_ptr->release & PAD_SQUARE) != 0)
    {
        pActor->field_A38 = 1;
    }

    if ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) != 0)
    {
        pActor->field_926++;
    }
    else
    {
        pActor->field_926 = 0;
    }

    if (anim_frame == 8)
    {
        pActor->field_90C_pWeaponFn = sub_80057BF0;
        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
    }
}

void sna_init_bomb_800541A8(Actor_SnaInit *pActor)
{
    void *pFn; // $a1

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
    if (sna_init_8004FDE8(pActor, &stru_8009EFE4))
    {
        pFn = sna_init_800571B8;
    }
    else
    {
        pFn = sna_init_80057118;
    }
    sna_init_start_anim_8004E1F4(pActor, pFn);
}

// or sna_init_no_weapon_80054210 ?
void sna_init_anim_chokethrow_begin1_80054210(Actor_SnaInit *pActor)
{
    void *pFn;
    pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        pFn = sna_init_anim_throw_800589C8;
    }
    else
    {
        pFn = sna_init_anim_chokethrow_begin2_80058C80;
    }
    sna_init_start_anim_8004E1F4(pActor, pFn);
}

void sna_init_8005425C(Actor_SnaInit *pActor, int anim_frame)
{
    short new_y; // $v0

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, 134, 4);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK26);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);
        new_y = pActor->field_20_ctrl.field_4C_turn_vec.vy + 2048;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = new_y;
        pActor->field_20_ctrl.field_8_rotator.vy = new_y;
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK26));
        sna_init_clear_invuln_8004F2EC(pActor);
    }
}

void sna_init_80054318(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_8005292C);
        return;
    }

    if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
    {
        sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK1);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        return;
    }
}

void sna_init_fn_800543A8(Actor_SnaInit *pActor, int anim_frame)
{
    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) && anim_frame >= 16)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        if (sna_init_prone_check_standup_80050398(pActor))
        {
            sna_init_clear_invuln_8004F2EC(pActor);
            sna_init_clear_flags1_8004E308(
                pActor, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6 | SNA_FLAG1_UNK10));
            sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK9);
        }
    }
}

void sna_init_anim_duct_move_80054424(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sub_8005688C;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78 + 150;
}

void sna_init_anim_duct_idle_80054488(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        pActor->field_9C8_anim_update_fn_3p = sub_80056928;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78 + 250;
    sna_init_80050440(pActor);
}

void sna_init_anim_shot_flinch_800544E0(Actor_SnaInit *pActor, int anim_frame)
{
    int action_flag;

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if (pActor->field_89C_pTarget->field_26_hp < 1)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            sna_init_8004F8E4(pActor, pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND ? 125 : 128);
        }

        if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_8;
        }
        else if ((GV_Time_800AB330 & 1) != 0)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_0;
            pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_1;
            pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        }

        sna_init_8004E22C(pActor, action_flag, 4);
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100 | PLAYER_STATUS_PREVENT_WEAPON_SWITCH);
        sna_init_start_anim_8004E1F4(pActor, (void *)dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
    }

    if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
    {
        sna_init_80050568(pActor);
    }
}

void sna_init_act_helper2_helper7_80054648(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 0);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;

        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_4, 4);

        if (pActor->field_89C_pTarget->field_26_hp <= 0)
        {
            GM_Sound_80032968(0, 63, 0x1Au);
            sna_init_8004F8E4(pActor, 128);
        }
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK6);
    }
}

void sna_init_act_helper2_helper8_80054710(Actor_SnaInit *pActor, int anim_frame)
{
    int bVar1;

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if ((GV_Time_800AB330 & 1) != 0)
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_2;
            pActor->field_A54.prone_bool_thing = 1;
        }
        else
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_3;
            pActor->field_A54.prone_bool_thing = 2;
        }

        sna_init_8004E22C(pActor, bVar1, 4);

        if (pActor->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK20);
        }

        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height < 500)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
    }

    if (pActor->field_798 < 250)
    {
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
    }
    else
    {
        if (anim_frame < 12 && pActor->field_A54.prone_bool_thing == 1)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy += 170;
        }

        if (anim_frame > 16)
        {
            sub_80026734(&pActor->field_A2C, &DG_ZeroVector_800AB39C, 3);
        }

        if ((pActor->field_A54.prone_bool_thing == 1 && anim_frame == 12) ||
            (pActor->field_A54.prone_bool_thing == 2 && anim_frame == 0x14))
        {
            sub_800329C4(&pActor->field_20_ctrl, 51, 1);
        }

        pActor->field_20_ctrl.field_44_movementVector.vx = pActor->field_A2C;
        pActor->field_20_ctrl.field_44_movementVector.vz = pActor->field_A30;
        sna_init_80050568(pActor);
    }
}

void sna_init_anim_knockdown_idle_80054930(Actor_SnaInit *pActor, int anim_frame)
{
    int   local_field_A54; // $v1
    int   action_flag;     // $a1
    short v5;              // $a1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_knockdown_check_getup_80056A1C;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK5);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK200 | PLAYER_STATUS_PRONE);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        local_field_A54 = pActor->field_A54.prone_bool_thing;
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        if (local_field_A54 == 1)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_4;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_5;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        if (pActor->field_89C_pTarget->field_26_hp <= 0)
        {
            v5 = 127;
            if (pActor->field_A54.prone_bool_thing == 1)
            {
                v5 = 126;
            }
            sna_init_8004F8E4(pActor, v5);
        }
        sna_init_80050568(pActor);
    }
}

void sna_init_anim_knockdown_getup_80054A10(Actor_SnaInit *pActor, int anim_frame)
{
    int action_flag; // $a1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        if (pActor->field_A54.prone_bool_thing == 1)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_6;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_7;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54.prone_bool_thing = 0;
    }

    if (pActor->field_20_ctrl.field_32_height >= 250)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height >= 501)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
    }

    if (anim_frame == 2)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
        sna_init_set_invuln_8004F2A0(pActor, 24);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK1);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }
}

void sna_init_anim_knockdown_shot_80054B50(Actor_SnaInit *pActor)
{
    pActor->field_9C8_anim_update_fn_3p = sna_init_knockdown_check_getup_80056A1C;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);

    if (pActor->field_89C_pTarget->field_26_hp <= 0 && !GM_GameOverTimer_800AB3D4)
    {
        GM_Sound_80032968(0, 63, 0x1Au);
        sna_init_8004F8E4(pActor, pActor->field_A54.prone_bool_thing == 1 ? 126 : 127);
    }
    else
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
    }

    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
}

void sna_init_act_helper2_helper10_80054C08(Actor_SnaInit *pActor, int anim_frame)
{
    char bVar1;

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if (pActor->field_A54.prone_bool_thing == 1)
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_A;
        }
        else
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_B;
        }

        sna_init_8004E22C(pActor, bVar1, 4);

        if (pActor->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK20);
        }
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
    }
    else
    {
        if (anim_frame == 12)
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
        }

        if (anim_frame > 16)
        {
            sub_80026734((short *)&pActor->field_A2C, &DG_ZeroVector_800AB39C, 3);
        }

        pActor->field_20_ctrl.field_44_movementVector.vx = pActor->field_A2C;
        pActor->field_20_ctrl.field_44_movementVector.vz = pActor->field_A30;
        sna_init_80050568(pActor);
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_knock_80054D68.s")              // 404 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_80054EFC.s") // 1080 bytes

void sna_init_anim_scope_80055334(Actor_SnaInit *param_1, int anim_frame)
{
    int action_flag;
    int sVar2;

    if (anim_frame == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        if (param_1->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
        {
            action_flag = 0x87;
        }
        else
        {
            action_flag = sna_init_8004EAA8(param_1, param_1->field_A26_fn_stance_idx);
        }

        sna_init_8004E22C(param_1, action_flag, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
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

    param_1->field_20_ctrl.field_4C_turn_vec.vx = sVar2;
}

void sna_init_anim_jpegcam_800553CC(Actor_SnaInit *pActor, int anim_frame)
{
    sna_init_anim_scope_80055334(pActor, anim_frame);
}

void sna_init_anim_box_idle_800553EC(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_80056A54;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_CROUCHING);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_2, 4);
    }
}

void sna_init_anim_box_move_8005544C(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_80056AD8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        GM_ConfigControlInterp_80026244(&pActor->field_20_ctrl, 4);
    }
}

void sna_init_anim_box_stop_800554B4(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_4, 4);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_dying_80055524.s") // 1204 bytes

// things like "a surveillance camera??" where player control is halted
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_mini_cutscene_800559D8.s") // 1024 bytes

// similar to above, seems freeze snake and make him look at a certain direction or track something
// triggers on first elevator ride at dock and right before mantis fight to look at meryl
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper3_80055DD8.s") // 2168 bytes

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_helper_80056650.s") // 508 bytes

void sub_8005684C(Actor_SnaInit *pActor)
{
    int y;

    if ((pActor->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_RIGHT)) == 0)
    {
        return;
    }

    y = pActor->field_20_ctrl.field_4C_turn_vec.vy;
    if ((pActor->field_9B0_pad_ptr->status & PAD_LEFT) != 0)
    {
        y += 32;
    }
    else
    {
        y -= 32;
    }
    pActor->field_20_ctrl.field_4C_turn_vec.vy = y;
}

void sub_8005688C(Actor_SnaInit *pActor)
{
    int action_flag; // $a1

    if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
    {
        if ((pActor->field_9B0_pad_ptr->status & PAD_UP) != 0)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_idle_80054488);
    }
    else
    {
        sub_8005684C(pActor);
    }
}

void sub_80056928(Actor_SnaInit *param_1)
{
    char bVar1;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        sna_init_start_anim_8004E1F4(param_1, sna_init_anim_enter_duct_80053E9C);
        sna_init_set_invuln_8004F2A0(param_1, 0);
    }
    else
    {
        if ((param_1->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) == 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(param_1, sna_init_anim_duct_move_80054424);
            sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_3, 4);
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

            sna_init_8004E22C(param_1, bVar1, 4);
            sub_8005684C(param_1);
        }
    }
}

void sna_init_knockdown_check_getup_80056A1C(Actor_SnaInit *pActor)
{
    if (pActor->field_9B0_pad_ptr->press)
    {
        sna_init_knockdown_getup_80050668(pActor);
    }
}

void sna_init_80056A54(Actor_SnaInit *pActor)
{
    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
    {
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_move_8005544C);
        }
    }
    else
    {
        if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_move_8005544C);
        }

        sub_8004FA9C(pActor);
    }
}

void sna_init_fn_80056AD8(Actor_SnaInit *pActor)
{
    if (gSnaMoveDir_800ABBA4 < 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_stop_800554B4);
    }
    else
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);

        if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = (short)gSnaMoveDir_800ABBA4;
        }
        else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) == 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_stop_800554B4);
        }
        else
        {
            sub_8004FA9C(pActor);
        }
    }
}

void sna_init_anim_shoot_weapon_80056B88(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_shoot_weapon_helper_80057590;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_1, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    }
}

void sna_init_anim_rungun_begin_80056BDC(Actor_SnaInit *param_1, int anim_frame)
{
    if (anim_frame == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_rungun_begin_helper_800577B4;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_init_anim_rungun_80056C3C(Actor_SnaInit *param_1, int anim_frame)
{
    if (anim_frame == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_rungun_helper_80057844;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_0, 4);
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_nikita_80056C9C.s") // 320 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_80056DDC.s")   // 740 bytes

void sna_init_anim_stinger_800570C0(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_stinger_helper_80058378;
        pActor->field_9CC_anim_update_fn_1p = sna_init_anim_stinger_helper_80058378;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_0, 4);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_PRONE |
                                          PLAYER_STATUS_CROUCHING);
    }
}

void sna_init_80057118(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        if (used_counter_8009F42C >= 16)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
            GM_Sound_80032968(0, 0x3f, 0x23);
            return;
        }

        pActor->field_9C8_anim_update_fn_3p = sub_80058644;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_5, 4);
    }

    sub_8004E9D0(pActor);
}

void sna_init_800571B8(Actor_SnaInit *pActor, int anim_frame)
{
    SVECTOR   *vec1;
    GM_Target *pGVar3;
    SVECTOR   *vec2;

    vec2 = &pActor->field_8EC_vec;

    if (anim_frame == 0)
    {
        if (used_counter_8009F42C >= 16)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
            pActor->field_8E8_pTarget->field_6_flags &= ~(0x40);
            pActor->field_8E8_pTarget = NULL;
            return;
        }

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_6, 4);
        pGVar3 = pActor->field_8E8_pTarget;
        DG_PutVector_8001BE48(&dword_800AB7EC, vec2, 1);
        GV_SubVec3_80016D40(&pGVar3->field_8_vec, vec2, vec2);

        vec2->vx /= 4;
        vec2->vy /= 4;
        vec2->vz /= 4;
    }

    vec1 = &pActor->field_20_ctrl.field_44_movementVector;

    if (anim_frame < 4)
    {
        GV_AddVec3_80016D00(vec1, vec2, vec1);
    }

    if (anim_frame == 6)
    {
        GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 49);
        NewBakudan_8006A6CC(pActor->field_8E8_pTarget->field_20, &dword_800AB7F4, 1, 1, pActor->field_8E8_pTarget);
        pActor->field_914 = 5;
        pActor->field_8E8_pTarget->field_6_flags &= ~(0x40);
        pActor->field_8E8_pTarget = 0;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    }
}

void sna_init_80057378(Actor_SnaInit *pActor, int anim_frame)
{
    int action;
    int stance;

    stance = pActor->field_A26_fn_stance_idx;
    pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBA8;

    if (anim_frame == 0)
    {
        if (stance == 0)
        {
            action = pActor->field_9B4_action_table->field_10->field_6;
        }
        else
        {
            action = pActor->field_9B4_action_table->field_10->field_7;
        }

        sna_init_8004E260(pActor, action, 4, 0xffff);
    }

    if ((stance == SNA_STANCE_STANDING && anim_frame == 6) || (stance == SNA_STANCE_CROUCH && anim_frame == 14))
    {
        pActor->field_914 = 3;
        GM_BombSeg_800ABBD8 = (GM_Target *)dword_800ABBB0;
    }

    if (pActor->field_9C_obj.field_1C != 0 || pActor->field_9C_obj.field_10 == 0)
    {
        sna_init_8004E260(pActor, 0, 4, 0);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK9);
        pActor->field_9C0 = NULL;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_80057474.s")            // 284 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shoot_weapon_helper_80057590.s") // 548 bytes

void sna_init_anim_rungun_begin_helper_800577B4(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_rungun_80056C3C);
    }
    else
    {
        if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
        {
            sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK1);
        }

        if (pActor->field_9C_obj.field_1A)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
        }
    }
}

// https://decomp.me/scratch/rNvHM
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_rungun_helper_80057844.s") // 348 bytes

void sna_init_auto_aim_800579A0(Actor_SnaInit *pActor)
{
    int unk;
    int out_x_copy;
    int snake_not_moving;
    int out_x;
    int out_y;
    int diff;

    // loops enemies and finds candidate to aim at, returns angle to auto turn/aim to
    // melee also uses this in a different func
    HomingTarget_2_80032EAC(&pActor->field_9C_obj.objs->objs[6].world,
                            pActor->field_20_ctrl.field_8_rotator.vy, // input snake horizontal facing angle
                            &out_y, &out_x, pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit,
                            pActor->field_890_autoaim_max_dist,
                            pActor->field_892_autoaim_min_angle); // min angle to activate auto aim

    // ?
    unk = pActor->field_718[2].vx;
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
    pActor->field_718[2].vx = out_x;
    pActor->field_718[6].vx = out_x;
    snake_not_moving = gSnaMoveDir_800ABBA4 < 0;
    pActor->field_718[7].vx = 3 * out_x_copy / 2; // maybe aim gun/head up/down??

    if (snake_not_moving && out_y >= 0) // if not moving, set snake turn angle
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy = out_y;
    }

    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5))
    {
        gUnkMaybeCameraStruct_800B77B8.field_28_aim_assist.vx = out_x;
    }
}

// https://decomp.me/scratch/bbu8N
#pragma INCLUDE_ASM("asm/sub_80057A90.s") // 352 bytes

#pragma INCLUDE_ASM("asm/sub_80057BF0.s")                                   // 996 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_helper_80057FD4.s") // 932 bytes

void sna_init_anim_stinger_helper_80058378(Actor_SnaInit *pActor)
{
    int      iVar2;
    SVECTOR *vec;

    iVar2 = 1;
    if (((pActor->field_9B0_pad_ptr->release & PAD_SQUARE) != 0 && (GM_GameStatus_800AB3CC & 0x10000000) == 0) &&
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK20000000) == 0)
    {
        if (pActor->field_918_pWeaponState[0] >= 1)
        {
            iVar2 = 3;
        }
        else
        {
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 4);
            pActor->field_9A0 = 4;
        }
    }

    pActor->field_914 = iVar2;

    if ((pActor->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) != 0)
    {
        vec = pActor->field_9D0;
        vec[0].vx = 1;
        vec[0].pad = 0x200;
        vec[1].vx = 0x200;
        vec[1].vy = 0x20;
        vec[1].vz = 0x20;
        vec[1].pad = 0x20;
        vec[2].vx = 0x20;

        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
        sub_8004EB14(pActor);
    }
}

// https://decomp.me/scratch/b53h8
#pragma INCLUDE_ASM("asm/sub_80058470.s") // 468 bytes

void sub_80058644(Actor_SnaInit *pActor, int anim_frame)
{
    int iVar1;

    pActor->field_914 = 1;

    if (anim_frame >= 10)
    {
        iVar1 = (int)pActor->field_A38;
        if (iVar1 == 0)
        {
            sub_8004EEB0(pActor);
        }

        if ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) == 0 && iVar1 == 0 && DG_UnDrawFrameCount_800AB380 == 0)
        {
            iVar1 = sub_8004E5E8(pActor, 0x80);
            if (iVar1 == 1)
            {
                sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_8, 1);
                pActor->field_A38 = 1;
                pActor->field_914 |= 2;
            }
            else if (iVar1 == 2)
            {
                GM_Sound_80032968(0, 0x3f, 0x23);
            }
        }

        if ((iVar1 == 1 && pActor->field_9C_obj.field_1A != 0) || iVar1 == 2)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }

        pActor->field_A2E = -100;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_helper_80058780.s") // 584 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_throw_800589C8.s")           // 584 bytes

void sna_init_anim_punch_80058C10(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_punch_helper_800591F4;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_2, 1);
        pActor->field_A38 = 0;
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_init_anim_chokethrow_begin2_80058C80(Actor_SnaInit *pActor, int anim_frame)
{
    int        bClear;            // $s0
    GM_Target *field_8E8_pTarget; // $v1
    int        action_flag;       // $a1
    SVECTOR   *p;

    if (anim_frame == 0)
    {
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        bClear = 0;
        pActor->field_A54.choke_count = 0;

        if (!sna_init_8004FDE8(pActor, &stru_8009F044))
        {
            bClear = 1;
            pActor->field_A38 = 1;
        }

        p = &pActor->field_8EC_vec;
        if (!bClear)
        {

            field_8E8_pTarget = pActor->field_8E8_pTarget;

            field_8E8_pTarget->field_2A--;

            DG_SetPos2_8001BC8C(&field_8E8_pTarget->field_8_vec, &pActor->field_20_ctrl.field_8_rotator);

            DG_PutVector_8001BE48(&stru_800AB7FC, p, 1);
            DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_rotator);
            GV_SubVec3_80016D40(p, &pActor->field_20_ctrl.field_0_position, p);
            p->vx /= 4;
            p->vy /= 4;
            p->vz /= 4;
            action_flag = pActor->field_9B4_action_table->field_18->field_0;
        }
        else
        {
            pActor->field_8EC_vec = DG_ZeroVector_800AB39C;
            action_flag = pActor->field_9B4_action_table->field_0->field_1;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
    }

    if (anim_frame < 4)
    {
        ++pActor->field_904_frames_last_choke;
        GV_AddVec3_80016D00(&pActor->field_20_ctrl.field_44_movementVector, &pActor->field_8EC_vec,
                            &pActor->field_20_ctrl.field_44_movementVector);
    }
    else
    {
        if (pActor->field_A38)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
        else
        {
            pActor->field_89C_pTarget->field_10_size.vx = 150;
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
        }
    }
}

void sna_init_anim_choke_80058E88(Actor_SnaInit *pActor, int anim_frame)
{
    short action_flag; // $s0

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_choke_helper_8005951C;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        action_flag = pActor->field_9B4_action_table->field_18->field_0;
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_8E8_pTarget->field_3E = action_flag;
    }
}

void sna_init_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int anim_frame)
{
    short bVar1;

    if (anim_frame == 0 || (pActor->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        pActor->field_9C_obj.action_flag = -1;
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_choke_rechoke_helper_8005961C;
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        bVar1 = pActor->field_9B4_action_table->field_10->field_6;
        sna_init_8004E22C(pActor, bVar1, 4);
        pActor->field_8E8_pTarget->field_3E = bVar1;
    }
}

/*
void sna_init_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int anim_frame)
{
    Sna_ActionTable *field_9B4_action_table; // $v1
    short action_flag; // $s0

    if (anim_frame == 0)
    {
        if (!(pActor->field_9B0_pad_bits[1] & 0x80))
        {
        field_9B4_action_table = pActor->field_9B4_action_table;

        pActor->field_9C_obj.action_flag = -1;
        pActor->field_9C8_anim_update_fn_3p = sub_8005961C;
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        action_flag = field_9B4_action_table->field_10->field_6;
        sna_init_8004E22C(pActor, field_9B4_action_table->field_10->field_6, 4);
        pActor->field_8E8_pTarget->field_3E = action_flag;
        }
    }
}
*/

void sna_init_anim_choke_kill_80058F88(Actor_SnaInit *pActor, int anim_frame)
{
    GM_Target *field_8E8_pTarget; // $s0
    int        action_flag;       // $s1

    if (anim_frame == 0)
    {
        field_8E8_pTarget = pActor->field_8E8_pTarget;
        action_flag = pActor->field_9B4_action_table->field_10->field_7;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        sna_init_8004E22C(pActor, action_flag, 4);

        field_8E8_pTarget->field_3E = action_flag;
        field_8E8_pTarget->field_28 = 5;
        field_8E8_pTarget->field_2A--;
        pActor->field_A54.choke_count = 0;
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_sub_8004E41C(pActor, 2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
    }

    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5))
    {
        sub_8004FAE8(pActor);
    }
}

void sna_init_anim_choke_drag_80059054(Actor_SnaInit *pActor, int anim_frame)
{
    int bVar2;
    int iVar3;

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        bVar2 = pActor->field_9B4_action_table->field_18->field_1;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, bVar2, 4);
        pActor->field_8E8_pTarget->field_3E = bVar2;
    }

    iVar3 = pActor->field_904_frames_last_choke + 1;
    pActor->field_904_frames_last_choke = iVar3;

    if ((gSnaMoveDir_800ABBA4 < 0 || ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) == 0)))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
    }
    else
    {
        if (!((pActor->field_8E8_pTarget->field_26_hp > 0) &&
              ((iVar3 < 0x5a && pActor->field_8E8_pTarget->field_42 != 0))))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
            return;
        }
        else
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4 + 0x800;
        }
    }
}

void sna_init_anim_choke_hold_80059154(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_6, 4);
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    }
}

void sub_800591BC(Actor_SnaInit *pActor)
{
    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_punch_helper_800591F4.s") // 808 bytes

void sna_init_anim_choke_helper_8005951C(Actor_SnaInit *pActor)
{
    int   sinceLastChoke;
    short press;
    short status;

    sinceLastChoke = ++pActor->field_904_frames_last_choke;

    if (((pActor->field_8E8_pTarget->field_26_hp < 1 || sinceLastChoke >= 90) ||
         pActor->field_8E8_pTarget->field_42 == 0))
    {
        sna_init_sub_8004E41C(pActor, 2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_hold_80059154);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        return;
    }

    press = pActor->field_9B0_pad_ptr->press;
    status = pActor->field_9B0_pad_ptr->status;

    if ((press & PAD_SQUARE) != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_rechoke_80058EF4);
    }
    else if ((status & PAD_SQUARE) == 0)
    {
        // A38 is snake stop movement frames, counts down
        if (++pActor->field_A38 >= 9)
        {
            sna_init_sub_8004E41C(pActor, 2);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_hold_80059154);
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        }
    }
    else
    {
        pActor->field_A38 = 0;
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_drag_80059054);
        }
    }
}

void sna_init_anim_choke_rechoke_helper_8005961C(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0 || (pActor->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        pActor->field_8E8_pTarget->field_2A--;

        if (++pActor->field_A54.choke_count >= 10) // feels good
        {
            vibrate_init2_8005D58C(dword_8009EF24, 1);
            vibrate_init2_8005D58C(dword_8009EF2C, 2);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_kill_80058F88);
            return;
        }
    }

    if (pActor->field_9C_obj.field_1A == 0 && pActor->field_8E8_pTarget->field_42 != 0)
    {
        return;
    }

    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_main_logic_800596FC.s") // 5652 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_8005AD10.s")        // 2076 bytes

void sna_init_kill_8005B52C(Actor_SnaInit *pActor)
{
    GM_Control *pCtrl;   // $s2
    DG_OBJS    *pObjs;   // $s0
    Actor      *pShadow; // $a0
    Actor      *pWeapon; // $a0
    Actor      *pItem;   // $a0

    if ((pActor->field_898_flags2 & 0x1000) != 0)
    {
        gGameState_800B4D98.field_BE = 1;
    }

    pCtrl = &pActor->field_20_ctrl;
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    GM_FreeTarget_8002D4B0(pActor->field_89C_pTarget);

    pObjs = pActor->field_92C;
    if (pObjs)
    {
        DG_DequeuePrim_800182E0(pActor->field_92C);
        DG_FreePrim_8001BC04(pObjs);
    }

    gGameState_800B4D98.field_20_snake_stance = pActor->field_A26_fn_stance_idx;

    pShadow = pActor->field_888_pShadow;
    if (pShadow)
    {
        GV_DestroyOtherActor_800151D8(pShadow);
    }

    pWeapon = pActor->field_908_weapon_actor;
    if (pWeapon)
    {
        GV_DestroyOtherActor_800151D8(pWeapon);
    }

    pItem = pActor->field_9A4_item_actor;
    if (pItem)
    {
        GV_DestroyOtherActor_800151D8(pItem);
    }

    if (gSnaControl_800AB9F4 == pCtrl)
    {
        gSnaControl_800AB9F4 = 0;
    }

    if (dword_800ABA20 == &pActor->field_9C_obj)
    {
        dword_800ABA20 = 0;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_init_8005B650.s") // 2356 bytes
