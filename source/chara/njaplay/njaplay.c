// "njaplay.c": the player (Snake / cyborg ninja) of the VR ninja missions (vcd_n01..n03). The code is a heavily modified
// copy of chara/snake/snake.c + chara/snake_vr/sna_init.c (the Work is 0xA0 bytes smaller: no weapons, no scope, no
// shadow polygons; VR_NINJA selects that Work in snake_vr/sna_init.h) plus the NinjaPlay actor.
//
// FIXME: only part of the functions are C so far (marked "// @ADDRESS" = original address in the overlay), the others are
// relocatable asm (INCLUDE_ASM_RELOC, reloc/njaplay.json, build/gen_reloc_obj.py) so that the object stays shared by
// vcd_n01, vcd_n02 and vcd_n03.

#define VR_NINJA

#include "mgstype.h"
#include "chara/snake_vr/sna_init.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/blood.h"
#include "okajima/spark.h"
#include "strcode.h"
#include "equip/equip.h"
#include "takabe/windcrcl.h"

// bss of the object (the sbss variables of the main exe version are plain bss here, in the order of the original). The
// "njp_" prefix keeps the symbols apart from the identical variables of the exe.
SnaInitWork *SECTION(".bss") njp_snainit_actor;
short        SECTION(".bss") njp_dword_800ABBDC;
short        SECTION(".bss") njp_dword_800ABBD4;
int          SECTION(".bss") njp_gSnaMoveDir_800ABBA4;
int          SECTION(".bss") njp_dword_800ABBA8;
int          SECTION(".bss") njp_bss_16;
int          SECTION(".bss") njp_bss_20;
char        *SECTION(".bss") njp_dword_800ABBB4;
int          SECTION(".bss") njp_bss_28;
int          SECTION(".bss") njp_bss_32;
int          SECTION(".bss") njp_bss_36;
int          SECTION(".bss") njp_bss_40;
int          SECTION(".bss") njp_dword_800ABBC4;
SVECTOR     *SECTION(".bss") njp_pVec_800ABBC8;
SVECTOR     *SECTION(".bss") njp_pVec_800ABBCC;
int          SECTION(".bss") njp_dword_800ABBD0;
int          SECTION(".bss") njp_bss_60;

// data of the object (see the end of the file)
extern u_char  njp_dword_8009EED4[4];
extern u_char  njp_dword_8009EED8[8];
extern u_char  njp_dword_8009EEE0[4];
extern u_char  njp_dword_8009EEE4[12];
extern u_char  njp_dword_8009EF24[8];
extern u_char  njp_dword_8009EF2C[8];
extern short   njp_word_8009EFC0[];
extern SVECTOR njp_svector_800AB7D4;
extern SVECTOR njp_svector_800AB7DC;
extern SVECTOR njp_front_probe[3];
extern SVECTOR njp_stru_8009EFD4[3][2];
extern Target_Data njp_stru_8009EFE4;
extern SVECTOR njp_svector_800AB7FC;

void njp_FreeTargets(SnaInitWork *work);

void njp_sna_anim_spin_end_800C4E38(SnaInitWork *work, int time);
void njp_sna_anim_idle_800C4200(SnaInitWork *work, int time);
void njp_sna_anim_idle_update_800C44CC(SnaInitWork *work, int time);
void njp_sna_anim_800C4A38(SnaInitWork *work, int time);
void njp_sna_anim_800C4A90(SnaInitWork *work, int time);
void njp_sna_anim_800C4B44(SnaInitWork *work, int time);
void njp_800C495C(SnaInitWork *work);
void njp_sna_anim_update_800C5C18(SnaInitWork *work, int time);
void njp_sna_anim_update_800C5D4C(SnaInitWork *work, int time);
void njp_sna_anim_slash_update_800C5E9C(SnaInitWork *work, int time);
void njp_sna_anim_update_800C5F20(SnaInitWork *work, int time);
void njp_800C60E4(SnaInitWork *work, int time);
void njp_sna_move_targets_800C5A70(SnaInitWork *work);
int njp_sna_check_hits_800C5B18(SnaInitWork *work);
void njp_800C65D4(SnaInitWork *work);
void njp_sna_anim_crouch_wall_update_800C4750(SnaInitWork *work, int time);
void njp_sna_anim_spin_800C4BA4(SnaInitWork *work, int time);
void njp_800C5150(SnaInitWork *work, int time);
void njp_sna_anim_chokethrow_begin2_80058C80(SnaInitWork *work, int time);
void njp_sna_anim_wall_move_update_800C47EC(SnaInitWork *work, int time);
void njp_sna_fp_update_800C6994(SnaInitWork *work, int time);
void njp_800C6CA4(SnaInitWork *work, int time);
void njp_nop_800C48EC(SnaInitWork *work, int time);
void njp_sna_anim_run_update_800C45CC(SnaInitWork *work, int time);
void njp_sna_fp_update_800C6900(SnaInitWork *work, int time);
extern int snainit_item_800A9420;

// shared with the p_sphere of the other VR overlays
extern void *s08b_p_sphere_800D9834(DG_OBJS **pobjs, int *state);

#define GetAction( work ) (work->body.action)
#define SEGMENT_ATR ( HZD_SEG_NO_COLLIDE )
#define TARGET_FLAG ( TARGET_CAPTURE | TARGET_POWER | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

// @800C258C njp_sna_start_anim_8004E1F4
void njp_sna_start_anim_8004E1F4(SnaInitWork *work, void *pFn)
{
    short vec_x = 0;
    work->field_9B8_fn_anim = pFn;
    work->field_9BC_anim_frame = 0;
    work->field_A3A = 0;
    work->field_A38_local_data = 0;

    if ((GM_PlayerStatus & PLAYER_GROUND) != 0)
    {
        vec_x = work->field_A2A;
    }

    work->control.turn.vx = vec_x;
    work->control.turn.vz = 0;
}

// @800C25C4 njp_SetAction_8004E22C
void njp_SetAction_8004E22C(SnaInitWork *work, int action_flag, int interp)
{
    if (GetAction(work) != action_flag)
    {
        GM_ConfigObjectAction(&work->body, action_flag, 0, interp);
    }
}

// @800C25F8 njp_sna_8004E260
void njp_sna_8004E260(SnaInitWork *work, int a2, int interp, int a4)
{
    if (work->body.action2 != a2)
    {
        GM_ConfigObjectOverride(&work->body, a2, 0, interp, a4);
    }
}

// @800C2634 njp_GM_CheckPlayerStatusFlag
int njp_GM_CheckPlayerStatusFlag(int flag)
{
    return (GM_PlayerStatus & flag) != 0;
}

// @800C264C njp_GM_SetPlayerStatusFlag
int njp_GM_SetPlayerStatusFlag(int flag)
{
    int new;

    new = GM_PlayerStatus | flag;
    GM_PlayerStatus = new;
    return new;
}

// @800C2664 njp_GM_ClearPlayerStatusFlag
void njp_GM_ClearPlayerStatusFlag(int flag)
{
    GM_PlayerStatus &= ~flag;
}

// @800C267C njp_sna_set_flags1_8004E2F4
void njp_sna_set_flags1_8004E2F4(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

// @800C2690 njp_sna_clear_flags1_8004E308
void njp_sna_clear_flags1_8004E308(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

// @800C26A4 njp_sna_check_flags1_8004E31C
int njp_sna_check_flags1_8004E31C(SnaInitWork *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}

// @800C26B8 njp_CheckSnakeDead_8004E384
void njp_CheckSnakeDead_8004E384(SnaInitWork *snake)
{
    if ((GM_Vitality == 0) || (GM_GameOverTimer != 0))
    {
        snake->control.skip_flag |= CTRL_SKIP_TRAP;
        njp_GM_SetPlayerStatusFlag(PLAYER_PAD_OFF | PLAYER_MENU_DISABLE);
        njp_sna_set_flags1_8004E2F4(snake, SNA_FLAG1_UNK23);
        GM_GameStatus |= (STATE_MENU_DISABLE | STATE_PADRELEASE);

        if (GM_GameOverTimer != -2)
        {
            njp_sna_set_flags1_8004E2F4(snake, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        }
    }
}

// @800C274C njp_sna_sub_8004E41C
void njp_sna_sub_8004E41C(SnaInitWork *snake, unsigned short flags)
{
    TARGET *target = snake->field_8E8_pTarget;

    if (target != NULL)
    {
        target->damaged &= ~flags;
        snake->field_8E8_pTarget = 0;
        snake->field_A54.choke_count = 0;
        snake->field_89C_pTarget->size.vx = 300;
    }
}

// @800C2788 njp_sub_8004E4C0
int njp_sub_8004E4C0(SnaInitWork *work, int param_2)
{
    int iVar1;

    if (-1 < njp_dword_800ABBA8)
    {
        if ((*njp_dword_800ABBB4 & 0x40) != 0)
        {
            return param_2;
        }
        iVar1 = (param_2 - njp_dword_800ABBA8) & 0xfff;
        if (iVar1 < 0x400)
        {
            param_2 = njp_dword_800ABBA8 + 0x400;
        }
        if (iVar1 > 0xc00)
        {
            param_2 = njp_dword_800ABBA8 - 0x400;
        }
    }
    return param_2;
}

// @800C27E8 njp_sna_line_check
int njp_sna_line_check(SVECTOR *line, HZD_HDL *hzd, int flag, int exclude)
{
    if (HZD_OnlineHazardCheck(hzd, &line[0], &line[1], flag, exclude) == 0)
    {
        return -1;
    }

    HZD_GetOnlinePoint(&line[1]);
    GV_SubVec3(&line[1], line, line);
    return GV_VecLen3(line);
}

// @800C2854 njp_sub_8004E588
void njp_sub_8004E588(HZD_HDL *param_1, SVECTOR *param_2, int *levels)
{
    unsigned int uVar1;

    uVar1 = HZD_LevelHazardCheck(param_1, param_2, HZD_CHK_FLOOR);
    HZD_GetLevelHeight(levels);
    if ((uVar1 & 1) == 0)
    {
        levels[0] = -32767;
    }
    if ((uVar1 & 2) == 0)
    {
        levels[1] = 32767;
    }
}

// @800C28B4 njp_sub_8004EA50
void njp_sub_8004EA50(SnaInitWork *work, int param_2)
{
    int iVar1 = GV_DiffDirS(param_2, work->control.rot.vy);

    if (iVar1 > 128)
    {
        iVar1 = 128;
    }
    else if (iVar1 < -128)
    {
        iVar1 = -128;
    }

    work->control.turn.vz = iVar1;
}

// @800C290C njp_sub_8004E5E8
int njp_sub_8004E5E8(SnaInitWork *work, int flag)
{
    return 2;
}

// @800C2914 njp_sna_8004EB14
void njp_sna_8004EB14(SnaInitWork *work)
{
    memcpy(&work->field_9D0, &njp_word_8009EFC0, sizeof(work->field_9D0));
}

// @800C2974 njp_sub_8004EB74
void njp_sub_8004EB74(SnaInitWork *work)
{
    if (GM_Camera.first_person == 0)
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

    GM_Camera.first_person = 1;
    work->field_A56 = 0;
    njp_GM_SetPlayerStatusFlag(PLAYER_MENU_DISABLE | PLAYER_WATCH);

    sd_set_cli(0x01ffff20, SD_ASYNC);
}

// @800C29E4 njp_sna_8004EC00
void njp_sna_8004EC00(SnaInitWork *work)
{
    if (GM_Camera.first_person == 1)
    {
        work->field_A20 = 6;
    }

    GM_Camera.first_person = 0;
    work->field_A56 = 0;

    njp_GM_ClearPlayerStatusFlag(PLAYER_NORMAL_WATCH | PLAYER_WATCH);
    njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK16);

    if (!njp_GM_CheckPlayerStatusFlag(PLAYER_INTRUDE))
    {
        sd_set_cli(0x01ffff21, SD_ASYNC);
    }
}

// @800C2A58 njp_sna_act_helper2_helper3_8004ED6C
void njp_sna_act_helper2_helper3_8004ED6C(SnaInitWork *work)
{
    if (work->field_A20 != 0)
    {
        if (work->field_A20 >= 1)
        {

            if ((GM_Camera.first_person == 0) && (--work->field_A20 == 0))
            {
                DG_VisibleObjs(work->body.objs);

                if (!njp_GM_CheckPlayerStatusFlag(PLAYER_ACT_ONLY))
                {
                    njp_GM_ClearPlayerStatusFlag(PLAYER_MENU_DISABLE);
                }
            }
        }
        else if ((GM_Camera.first_person != 0) && (++work->field_A20 == 0))
        {
            DG_InvisibleObjs(work->body.objs);
        }
    }
}

// @800C2B14 njp_sna_8004EE28
void njp_sna_8004EE28(SnaInitWork *snake)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR vec;
    int     vx;
    MATRIX *world = &snake->body.objs->objs[6].world;

    ReadRotMatrix(&mat1);
    DG_TransposeMatrix(&mat1, &mat2);
    MulMatrix0(&mat2, world, &mat2);
    DG_MatrixRotZYX(&mat2, &vec);
    SetRotMatrix(&mat1);

    vx = (vec.vx / 16) * 16;
    GM_SnakeCamera.rotate2.vx = vx;
}

// @800C2B9C njp_sub_8004EFE4
int njp_sub_8004EFE4(SnaInitWork *work, int set)
{
    MOTION_INFO *info;
    int          action;

    if (set == 1)
    {
        info = &work->m_ctrl.info1;
    }
    else
    {
        info = &work->m_ctrl.info2;
    }

    if (set == 1)
    {
        action = GetAction(work);
    }
    else
    {
        action = work->body.action2;
    }

    if (info->frames_left + info->frame == 1)
    {
        return action;
    }

    return -1;
}

// @800C2BEC njp_sna_8004F034
void njp_sna_8004F034(SnaInitWork *work, unsigned int bits)
{
    if ( bits != work->m_ctrl.info1.mask )
    {
        work->m_ctrl.info2.mask = ~bits;
        work->m_ctrl.info1.mask = bits;
        if ( bits == 0xFFFF && njp_sub_8004EFE4(work, 2) >= 0 )
        {
            work->m_ctrl.interp = 4;
            work->m_ctrl.info2.field_14 = 2;
        }
    }
}

// @800C2C48 njp_sna_act_helper2_helper4_8004F090
void njp_sna_act_helper2_helper4_8004F090(SnaInitWork *work, int param_2)
{
    int    iVar1;
    MATRIX mtx;

    DG_SetPos(&work->body.objs->objs[6].world);
    DG_MovePos(&njp_svector_800AB7D4);
    DG_RotatePos(&njp_svector_800AB7DC);
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
        NewBlood(&mtx, iVar1);
    }
}

// @800C2CFC njp_sub_8004F204
void njp_sub_8004F204(SnaInitWork *work)
{
    if (work->field_9A4_item_actor != 0)
    {
        GV_DestroyActorQuick(work->field_9A4_item_actor);
    }

    work->field_9A4_item_actor = 0;
    work->field_9A8_current_item = IT_None;
    GM_Item = IT_None;
    work->field_9AC = GM_ItemTypes[0];

    njp_sna_8004EC00(work);
    njp_GM_ClearPlayerStatusFlag(PLAYER_WEAPON_DISABLE | PLAYER_CB_BOX);
}

// @800C2D68 njp_sna_set_invuln_8004F2A0
void njp_sna_set_invuln_8004F2A0(SnaInitWork *work, char invuln_frames)
{
    njp_GM_SetPlayerStatusFlag(PLAYER_INVINCIBLE);
    work->field_A24_invuln_frames = invuln_frames;
    work->field_89C_pTarget->class &= ~0x96;
}

// @800C2DB4 njp_sna_clear_invuln_8004F2EC
void njp_sna_clear_invuln_8004F2EC(SnaInitWork *work)
{
    njp_GM_ClearPlayerStatusFlag(PLAYER_INVINCIBLE);
    njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK1);
    work->field_89C_pTarget->class |= TARGET_FLAG;
}

// @800C2E00 njp_sub_8004F338
void njp_sub_8004F338(SnaInitWork *work)
{
    if (njp_GM_CheckPlayerStatusFlag(PLAYER_INTRUDE))
    {
        work->field_A56 = 0;
        njp_GM_ClearPlayerStatusFlag(PLAYER_MENU_DISABLE
                                 | PLAYER_NORMAL_WATCH
                                 | PLAYER_WATCH);
    }
    else
    {
        njp_sna_8004EC00(work);
    }

    njp_sna_clear_invuln_8004F2EC(work);
    work->field_A24_invuln_frames = 0;
    njp_sna_sub_8004E41C(work, 2);
    GM_ConfigMotionAdjust(&work->body, 0);
    njp_sna_8004E260(work, 0, 4, 0);

    GM_ExitBehindCamera();

    GM_PlayerStatus &= PLAYER_SECOND_AVAILABLE | PLAYER_NOT_SIGHT |
                       PLAYER_GAME_OVER | PLAYER_CB_BOX | PLAYER_INTRUDE |
                       PLAYER_ACT_ONLY | PLAYER_SQUAT | PLAYER_GROUND;

    work->field_A28 = 0x1c2;
    work->field_894_flags1 &= (SNA_FLAG1_UNK20 | SNA_FLAG1_UNK28 | SNA_FLAG1_UNK29);
    work->control.skip_flag &= ~CTRL_BOTH_CHECK;
    njp_FreeTargets(work);
    GM_GameStatus &= ~STATE_DAMAGED;
    work->njp_mode = 3;
}

// @800C2EF0 njp_sub_8004F454
void njp_sub_8004F454(SnaInitWork *work)
{
    int i;

    njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE | PLAYER_ATTACK | PLAYER_CHECK_WALL);
    GM_ConfigMotionAdjust(&work->body, NULL);

    for (i = 0; i < SNAKEJOINT_NUM; i++)
    {
        work->adjust[i] = DG_ZeroVector;
    }

    njp_sna_8004E260(work, 0, 4, 0);
    njp_sna_sub_8004E41C(work, 2);
    njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK13 | SNA_FLAG1_UNK26 | SNA_FLAG1_UNK30);

    if (njp_GM_CheckPlayerStatusFlag(PLAYER_CAUTION) == 0)
    {
        work->field_A28 = 450;
        GM_ExitBehindCamera();
    }

    work->control.skip_flag &= ~CTRL_BOTH_CHECK;
    njp_FreeTargets(work);
    GM_GameStatus &= ~STATE_DAMAGED;
    work->njp_mode = 3;
}

// @800C2FE4 njp_UpdateLife_8004F6E8
void njp_UpdateLife_8004F6E8(SnaInitWork *work)
{
    int health;

    if (njp_sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK23))
    {
        return;
    }

    if (njp_sna_check_flags1_8004E31C(work,SNA_FLAG1_UNK25) &&
        (GM_Vitality == work->field_89C_pTarget->vital))
    {
        return;
    }

    if ((work->field_9A8_current_item == IT_BodyArmor) && (work->field_89C_pTarget->a_mode == 1))
    {
        work->field_89C_pTarget->damage /= 2;
        work->field_89C_pTarget->vital += work->field_89C_pTarget->damage;
        work->field_89C_pTarget->damage = 0;
    }

    health = work->field_89C_pTarget->vital + GM_Vitality - work->field_A22_snake_current_health;

    if (health > GM_VitalityMax)
    {
        health = GM_VitalityMax;
    }

    if (health < 0)
    {
        health = 0;
    }

    if (work->field_89C_pTarget->weapon == WP_Max)
    {
        health = 0;
    }

    work->field_89C_pTarget->vital = health;
    work->field_A22_snake_current_health = health;
    GM_Vitality = health;

    njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK25);
}

// @800C3118 njp_sna_8004F8E4
void njp_sna_8004F8E4(SnaInitWork *work, int a2)
{
    GV_MSG msg;

    if ((GM_GameOverTimer == -1) || (GM_GameOverTimer == 0))
    {
        // スネーク
        msg.address = GV_StrCode("スネーク");
        msg.message_len = 6;
        msg.message[0] = HASH_GO_MOTION;
        msg.message[1] = a2;
        msg.message[2] = -1;
        msg.message[3] = -1;
        msg.message[4] = 2;
        msg.message[5] = 2042;

        work->field_7A4_msgs[work->field_7A0_msg_count] = msg;
        work->field_7A0_msg_count++;

        GM_GameOverTimer = 0;
        GM_GameOver();

        GM_GameStatus |= STATE_PADRELEASE;
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);

        if (work->field_A70 >= 0)
        {
            GCL_ForceExecProc(work->field_A70, NULL);
        }

        if (njp_GM_CheckPlayerStatusFlag(PLAYER_CB_BOX))
        {
            njp_sub_8004F204(work);
        }
    }
}

// @800C3270 njp_sna_800C3270
void njp_sna_800C3270(SnaInitWork *work)
{
    if ((GM_GameOverTimer == -1) || (GM_GameOverTimer == 0))
    {
        GM_GameOverTimer = 0;
        GM_GameOver();

        GM_GameStatus |= STATE_PADRELEASE;
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);

        if (work->field_A70 >= 0)
        {
            GCL_ForceExecProc(work->field_A70, NULL);
        }
    }
}

// @800C32E4 njp_sna_act_unk_helper4_8004FA3C
int njp_sna_act_unk_helper4_8004FA3C(void)
{
    if (GM_Vitality == 0 || GM_GameOverTimer != 0)
    {
        return 1;
    }

    return 0;
}

// @800C3318 njp_sna_800C3318
void njp_sna_800C3318(SnaInitWork *work)
{
    MATRIX stackData;

    stackData = DG_ZeroMatrix;
    stackData.t[0] = work->control.mov.vx;
    stackData.t[1] = 0x14;
    stackData.t[2] = work->control.mov.vz;

    NewWindcrcl_800CF784(&stackData, 0xc8, 0x64, 0x12c, 0xa);

    work->njp_mode = 2;
    s08b_p_sphere_800D9834(&work->body.objs, &work->njp_mode);
}

// @800C33C8 njp_sna_stealth_800C33C8
// optical camouflage (stealth): L1 toggles it, it drains the energy of the target and is switched off when empty
void njp_sna_stealth_800C33C8(SnaInitWork *work)
{
    int item;

    if (njp_GM_CheckPlayerStatusFlag(PLAYER_WATCH))
    {
        return;
    }

    if (work->field_9B0_pad_ptr->press & PAD_L1)
    {
        work->field_9A8_current_item = IT_Stealth;
    }

    if (work->field_9A4_item_actor)
    {
        work->field_89C_pTarget->vital--;

        if ((work->field_89C_pTarget->vital & 0x3f) == 0)
        {
            GM_GameStatus |= STATE_DAMAGED;
        }

        if ((work->field_89C_pTarget->vital <= 0) && (GM_GameOverTimer == 0))
        {
            njp_sub_8004F454(work);
            njp_sna_set_invuln_8004F2A0(work, 0);
            GM_GameOverTimer = -1;
            njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_spin_end_800C4E38);
            work->njp_mode = 3;
            work->field_9A8_current_item = IT_Stealth;
        }
    }

    if (work->field_9A4_item_actor)
    {
        if (GM_Item == IT_None)
        {
            work->field_9A8_current_item = IT_Stealth;
        }
    }

    item = work->field_9A8_current_item;

    if (item == IT_Stealth)
    {
        if (work->field_9A4_item_actor == NULL)
        {
            work->field_9A4_item_actor = NewKogaku2(&work->control, &work->body, 6);

            if (work->field_9A4_item_actor == NULL)
            {
                return;
            }

            GM_SeSetMode(&work->control.mov, 78, 1);
            dword_800ABA1C = 1;
            GM_Item = item;
            snainit_item_800A9420 = item;
        }
        else
        {
            GV_DestroyActorQuick(work->field_9A4_item_actor);
            GM_SeSetMode(&work->control.mov, 78, 1);
            dword_800ABA1C = 0;
            work->field_9A4_item_actor = NULL;
            GM_Item = IT_None;
            snainit_item_800A9420 = IT_None;
        }

        work->field_9A8_current_item = 0;
    }
}

// @800C35BC njp_sna_800C35BC
// adds a step of "len" in direction "dir" to the movement
void njp_sna_800C35BC(SnaInitWork *work, int dir, int len)
{
    MATRIX  mtx;
    SVECTOR rot;

    if (dir >= 0)
    {
        rot.vz = 0;
        rot.vx = 0;
        rot.vy = dir;
        RotMatrixYXZ(&rot, &mtx);
        rot.vy = 0;
        rot.vx = 0;
        rot.vz = len;
        ApplyMatrixSV(&mtx, &rot, &rot);
        GV_AddVec3(&work->control.step, &rot, &work->control.step);
    }
}

// @800C3640 njp_sna_se_800C3640
void njp_sna_se_800C3640(SVECTOR *pos, int type, int param)
{
    int se = 0;

    switch (type)
    {
    case 5:
        if (param == 0)
        {
            se = 168;
        }
        else if (param == 10)
        {
            se = 169;
        }
        break;

    case 13:
        if (param == 3)
        {
            se = 205;
        }
        break;

    case 14:
        if (param == 3 || param == 14)
        {
            se = 205;
        }
        break;
    }

    if (se != 0)
    {
        GM_SeSetMode(pos, se, 1);
    }
}

// @800C36EC njp_sna_se_800C36EC
void njp_sna_se_800C36EC(SVECTOR *pos, int type, int param)
{
    int se = 0;

    if (type == 26)
    {
        if (param == 3 || param == 14)
        {
            se = 205;
        }
    }

    if (se != 0)
    {
        GM_SeSetMode(pos, se, 1);
    }
}

// @800C3738 njp_sna_8004FDE8
int njp_sna_8004FDE8(SnaInitWork *work, Target_Data *pTargetData)
{
    TARGET *pTarget;
    SVECTOR vec;
    SVECTOR vecs[2];

    GM_SetTarget(&work->field_8A0_target, TARGET_CAPTURE, PLAYER_SIDE, &pTargetData->field_8_size);
    GM_SetCaptureTarget(&work->field_8A0_target, pTargetData->field_18, pTargetData->field_1C, &work->field_8F4, &work->field_8FC);
    DG_PutVector(&pTargetData->field_0, &vec, 1);
    GM_MoveTarget(&work->field_8A0_target, &vec);

    work->field_8E8_pTarget = NULL;

    pTarget = GM_CaptureTarget(&work->field_8A0_target);

    if (pTarget)
    {
        if (pTarget->class & 0x20)
        {
            pTarget->damaged &= ~TARGET_CAPTURE;
            pTarget->faint += pTargetData->field_1C;
            return 0;
        }

        vecs[0] = work->control.mov;
        vecs[1] = pTarget->center;

        if (njp_sna_line_check(vecs, work->control.map->hzd, HZD_CHK_ALL, SEGMENT_ATR) < 0)
        {
            work->field_8E8_pTarget = pTarget;
            return 1;
        }

        pTarget->damaged &= ~TARGET_CAPTURE;
        pTarget->faint += pTargetData->field_1C;
    }

    return 0;
}

// @800C3898 njp_sna_800C3898
// sword attack: "line" are two points in the space of the hand, if the line is not blocked a damaging target is put at its end
void njp_sna_800C3898(SnaInitWork *work, SVECTOR *line)
{
    TARGET  target;
    SVECTOR pos[2];
    SVECTOR size;
    MATRIX  mtx;

    ReadRotMatrix(&mtx);
    DG_SetPos(&work->body.objs->objs[4].world);
    DG_PutVector(line, pos, 2);
    SetRotMatrix(&mtx);

    if (GM_OnlineTargetCheck(&pos[0], &pos[1], work->control.map->index, &pos[1], 1))
    {
        size.vx = size.vy = size.vz = 100;
        GM_SetTarget(&target, 4, PLAYER_SIDE, &size);
        GM_SetPowerTarget(&target, POWER_DECREASE, 1, 256, 0, &DG_ZeroVector);
        GM_MoveTarget(&target, &pos[1]);
        GM_PowerTarget(&target);

        mtx.t[0] = pos[1].vx;
        mtx.t[1] = pos[1].vy;
        mtx.t[2] = pos[1].vz;
    }
}

// @800C399C njp_sna_800C399C
void njp_sna_800C399C(SnaInitWork *work)
{
    TARGET  target;
    SVECTOR size;

    size = work->field_89C_pTarget->size;
    GM_SetTarget(&target, 4, PLAYER_SIDE, &size);
    GM_SetPowerTarget(&target, POWER_DECREASE, 1, 256, 0, &DG_ZeroVector);
    GM_MoveTarget(&target, &work->control.mov);
    GM_PowerTarget(&target);
}

// @800C3A30 njp_sna_select_action_800C3A30
// starts a ninja action (jump, slash, ...) from the pad, returns 1 if one was started
int njp_sna_select_action_800C3A30(SnaInitWork *work)
{
    u_short status = work->field_9B0_pad_ptr->status;
    u_short press = work->field_9B0_pad_ptr->press;

    if ((status & PAD_CIRCLE) && work->control.grounded)
    {
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3 | SNA_FLAG1_UNK30);

        if (njp_gSnaMoveDir_800ABBA4 >= 0)
        {
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4A90);
        }
        else
        {
            njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK5);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4A38);
        }
    }
    else if ((press & PAD_CROSS) && work->control.grounded)
    {
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
        njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK5);
        njp_sna_start_anim_8004E1F4(work, njp_800C5150);
    }
    else if (press & PAD_SQUARE)
    {
        if (status & PAD_UDLR)
        {
            njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
            njp_GM_SetPlayerStatusFlag(PLAYER_ATTACK);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4B44);
        }
        else
        {
            njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
            njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_chokethrow_begin2_80058C80);
        }
    }
    else if (press & PAD_R1)
    {
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK3);
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_spin_800C4BA4);
    }
    else
    {
        return 0;
    }

    return 1;
}

// @800C3B98 njp_sub_800507D8
int njp_sub_800507D8(SnaInitWork *work)
{
    if (njp_dword_800ABBC4 == 0 && work->field_A38_local_data == 0)
    {
        work->field_A28 = 450;
        njp_GM_ClearPlayerStatusFlag(PLAYER_CHECK_WALL | PLAYER_CAUTION | PLAYER_MOVE);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
        njp_sna_8004E260(work, 0, 4, 0);
        GM_ExitBehindCamera();
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_0.s")
//ASM-END

// @800C41B4 njp_sna_clear_target_800C41B4
void njp_sna_clear_target_800C41B4(TARGET *target)
{
    target->damage = 0;
    target->faint = 0;
    target->damaged &= ~0x84;
    target->force = DG_ZeroVector;
    target->weapon = -1;
    target->a_mode = 0;
}

// @800C4200 njp_sna_anim_idle_800C4200
void njp_sna_anim_idle_800C4200(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_idle_update_800C44CC;
        work->field_A26_stance = STAND;
        work->field_9CC_anim_update_fn_1p = njp_sna_fp_update_800C6900;
        njp_SetAction_8004E22C(work, 2, 4);
    }
}

// @800C4244 njp_sna_anim_run_begin_80053B88
void njp_sna_anim_run_begin_80053B88(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_run_update_800C45CC;
        work->field_9CC_anim_update_fn_1p = njp_sna_fp_update_800C6900;
        njp_GM_SetPlayerStatusFlag(PLAYER_MOVE);
        njp_SetAction_8004E22C(work, 5, 4);
    }
}

// @800C4298 njp_sna_anim_wall_crouch_80052CCC
void njp_sna_anim_wall_crouch_80052CCC(SnaInitWork *work, int time)
{
    int sound;

    if (time == 0)
    {
        if (njp_GM_CheckPlayerStatusFlag(PLAYER_CAUTION) == 0)
        {
            sound = SE_WALLPRESS;
            if (njp_GM_CheckPlayerStatusFlag(PLAYER_IN_THE_WATER) != 0)
            {
                sound = 183;
            }
            GM_SeSet(&work->control.mov, sound);
            work->control.turn.vy = njp_dword_800ABBD0 - 2048;
            njp_GM_SetPlayerStatusFlag(PLAYER_CAUTION);
        }

        work->field_A28 = 300;
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_crouch_wall_update_800C4750;
        work->field_A26_stance = STAND;
        work->field_9CC_anim_update_fn_1p = njp_sna_fp_update_800C6994;
        njp_SetAction_8004E22C(work, 21, 4);
    }

    GM_CheckBehindCamera(work->control.map->hzd, &work->control);

    if (work->field_A3A < 8 && njp_pVec_800ABBCC != NULL)
    {
        work->control.step.vx += njp_pVec_800ABBCC->vx / 8;
        work->control.step.vz += njp_pVec_800ABBCC->vz / 8;
        work->field_A3A++;
    }
}

// @800C43CC njp_sna_anim_wall_move_80052BA8
void njp_sna_anim_wall_move_80052BA8(SnaInitWork *work, int time)
{
    int action;

    if (time == 0)
    {
        njp_GM_SetPlayerStatusFlag(PLAYER_MOVE | PLAYER_CAUTION);
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_wall_move_update_800C47EC;
        work->field_9CC_anim_update_fn_1p = njp_sna_fp_update_800C6994;

        if (work->field_A54.wall_thing == 2)
        {
            action = 22;
        }
        else
        {
            action = 23;
        }

        work->field_A28 = 300;
        work->field_A54.wall_thing = 0;
        njp_SetAction_8004E22C(work, action, 4);
        work->control.turn.vy = njp_dword_800ABBD0 - 2048;
    }

    if (work->field_A3A < 8 && njp_pVec_800ABBCC != NULL)
    {
        work->control.step.vx += njp_pVec_800ABBCC->vx / 8;
        work->control.step.vz += njp_pVec_800ABBCC->vz / 8;
        work->field_A3A++;
    }
}

// @800C44CC njp_sna_anim_idle_update_800C44CC
void njp_sna_anim_idle_update_800C44CC(SnaInitWork *work, int time)
{
    int diff;

    if (njp_sna_select_action_800C3A30(work))
    {
        return;
    }

    if (work->field_A38_local_data > 0)
    {
        work->field_A38_local_data--;
    }

    if (work->field_A38_local_data == 0 && njp_gSnaMoveDir_800ABBA4 >= 0)
    {
        if (njp_dword_800ABBC4 == 1 || (njp_dword_800ABBC4 != 0 && work->field_79C == 2))
        {
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_wall_crouch_80052CCC);
        }
        else
        {
            diff = GV_DiffDirAbs(work->control.turn.vy, njp_gSnaMoveDir_800ABBA4);
            if (diff > 256)
            {
                work->field_A38_local_data = diff / 1024 + 1;
            }
            else
            {
                njp_sna_start_anim_8004E1F4(work, njp_sna_anim_run_begin_80053B88);
            }

            work->control.turn.vy = njp_gSnaMoveDir_800ABBA4;
        }
    }
}

// @800C45CC njp_sna_anim_run_update_800C45CC
void njp_sna_anim_run_update_800C45CC(SnaInitWork *work, int time)
{
    int angle;

    if (njp_sna_select_action_800C3A30(work))
    {
        return;
    }

    if (njp_gSnaMoveDir_800ABBA4 < 0)
    {
        if (++work->field_A3A >= 5)
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
            return;
        }
    }
    else
    {
        work->field_A3A = 0;
    }

    if ((njp_dword_800ABBC4 == 1) || ((njp_dword_800ABBC4 != 0) && (work->field_79C == 2)))
    {
        if (++work->field_A38_local_data >= 3)
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_wall_crouch_80052CCC);
            return;
        }
    }
    else
    {
        work->field_A38_local_data = 0;
    }

    if (work->field_A38_local_data == 0)
    {
        if (njp_gSnaMoveDir_800ABBA4 >= 0)
        {
            angle = njp_sub_8004E4C0(work, njp_gSnaMoveDir_800ABBA4);
        }
        else
        {
            angle = work->control.turn.vy;
        }
    }
    else
    {
        angle = njp_gSnaMoveDir_800ABBA4;

        if (angle < 0)
        {
            angle = work->control.turn.vy;
        }
    }

    if (GV_DiffDirAbs(work->control.turn.vy, angle) > 1048)
    {
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
        work->control.turn.vy = angle;
        return;
    }

    work->control.turn.vy = angle;
    njp_sub_8004EA50(work, angle);
}

// @800C4750 njp_sna_anim_crouch_wall_update_800C4750
void njp_sna_anim_crouch_wall_update_800C4750(SnaInitWork *work, int time)
{
    if (work->field_A38_local_data != 0)
    {
        work->field_A38_local_data--;
    }

    if (njp_sub_800507D8(work))
    {
        return;
    }

    if (njp_dword_800ABBC4 == 2 || njp_dword_800ABBC4 == 4)
    {
        work->field_A54.wall_thing = njp_dword_800ABBC4;
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_wall_move_80052BA8);
    }

    if ((njp_dword_800ABBD0 - 2048) != work->control.rot.vy)
    {
        work->field_A3A = 0;
        work->control.turn.vy = njp_dword_800ABBD0 - 2048;
    }
}

// @800C47EC njp_sna_anim_wall_move_update_800C47EC
void njp_sna_anim_wall_move_update_800C47EC(SnaInitWork *work, int time)
{
    int action;

    if (work->field_A38_local_data != 0)
    {
        work->field_A38_local_data--;
    }

    if (njp_sub_800507D8(work))
    {
        return;
    }

    GM_CheckBehindCamera(work->control.map->hzd, &work->control);

    if (njp_dword_800ABBC4 == 1)
    {
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_wall_crouch_80052CCC);
        return;
    }

    if (((njp_dword_800ABBD0 - 2048) != work->control.rot.vy) || (njp_pVec_800ABBC8 != njp_pVec_800ABBCC))
    {
        work->field_A3A = 0;
        work->control.turn.vy = njp_dword_800ABBD0 - 2048;
    }

    if (njp_dword_800ABBC4 == 2)
    {
        action = 22;
    }
    else
    {
        action = 23;
    }

    njp_GM_SetPlayerStatusFlag(PLAYER_MOVE);
    njp_SetAction_8004E22C(work, action, 4);
}

// @800C48EC njp_nop_800C48EC
void njp_nop_800C48EC(SnaInitWork *work, int time)
{
}

// @800C48F4 njp_FreeTargets
void njp_FreeTargets(SnaInitWork *work)
{
    int i;

    for (i = 0; i < work->njp_num_targets; i++)
    {
        GM_FreeTarget(work->njp_targets[i]);
    }

    work->njp_num_targets = 0;
}

// @800C495C njp_800C495C
// allocates the extra targets of the ninja (freed by njp_FreeTargets)
void njp_800C495C(SnaInitWork *work)
{
    SVECTOR size;
    TARGET *target;
    int     i;

    size.vx = size.vz = 160;
    size.vy = 650;

    if (work->njp_num_targets != 0)
    {
        njp_FreeTargets(work);
    }

    for (i = 0; i < 3; i++)
    {
        target = GM_AllocTarget();
        work->njp_targets[i] = target;

        if (target == NULL)
        {
            break;
        }

        work->njp_num_targets++;
        GM_SetTarget(target, 21, PLAYER_SIDE, &size);
        GM_SetPowerTarget(target, POWER_DECREASE, -1, 1024, 0, &DG_ZeroVector);
    }
}

// @800C4A38 njp_sna_anim_800C4A38
void njp_sna_anim_800C4A38(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_update_800C5C18;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 3, 4);
        work->field_A38_local_data = -1;
        njp_800C495C(work);
    }
}

// @800C4A90 njp_sna_anim_800C4A90
void njp_sna_anim_800C4A90(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_update_800C5D4C;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 24, 4);
        njp_GM_SetPlayerStatusFlag(PLAYER_MOVE);
        work->field_A38_local_data = -1;
        njp_800C495C(work);
    }
}

// @800C4AF0 njp_sna_anim_800C4AF0
void njp_sna_anim_800C4AF0(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_slash_update_800C5E9C;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 14, 4);
        njp_sna_set_invuln_8004F2A0(work, 0);
    }
}

// @800C4B44 njp_sna_anim_800C4B44
void njp_sna_anim_800C4B44(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_sna_anim_update_800C5F20;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        work->control.turn.vy = njp_gSnaMoveDir_800ABBA4;
        njp_SetAction_8004E22C(work, 13, 4);
        njp_sna_set_invuln_8004F2A0(work, 0);
    }
}

// @800C4BA4 njp_sna_anim_spin_800C4BA4
// the two damaging targets of the spin attack
static inline void njp_sna_spin_targets(SnaInitWork *work)
{
    TARGET  target;
    SVECTOR size;

    size.vx = size.vz = 750;
    size.vy = 200;
    GM_SetTarget(&target, 4, PLAYER_SIDE, &size);
    GM_SetPowerTarget(&target, POWER_DECREASE, 2, 256, 0, &DG_ZeroVector);
    GM_MoveTarget(&target, &work->control.mov);
    GM_PowerTarget(&target);

    size.vx = size.vz = 1500;
    size.vy = 200;
    GM_SetTarget(&target, 4, PLAYER_SIDE, &size);
    GM_SetPowerTarget(&target, POWER_DECREASE, 2, 1, 5, &DG_ZeroVector);
    GM_MoveTarget(&target, &work->control.mov);
    GM_PowerTarget(&target);
}

// spinning sword attack (R1): two damaging targets of different sizes at the position of the ninja
void njp_sna_anim_spin_800C4BA4(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_nop_800C48EC;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 12, 4);
        GM_SeSetMode(&work->control.mov, 198, 1);
        njp_sna_800C3318(work);
    }

    if (time % 10 == 0)
    {
        GM_SeSetMode(&work->control.mov, 208, 1);
    }

    njp_sna_spin_targets(work);

    work->field_A38_local_data++;

    if (work->field_A38_local_data == 24)
    {
        work->njp_mode = 3;
    }

    if (work->field_A38_local_data == 32)
    {
        GM_SeSetMode(&work->control.mov, 198, 1);
        work->field_A38_local_data = 0;
        njp_sna_800C3318(work);
    }

    work->field_89C_pTarget->vital--;

    if ((work->field_89C_pTarget->vital & 0x3f) == 0)
    {
        GM_GameStatus |= STATE_DAMAGED;
    }

    if ((work->field_89C_pTarget->vital <= 0) && (GM_GameOverTimer == 0))
    {
        njp_sna_set_invuln_8004F2A0(work, 0);
        GM_GameOverTimer = -1;
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK20);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_spin_end_800C4E38);
        work->njp_mode = 3;
    }
    else if (!(work->field_9B0_pad_ptr->status & PAD_R1))
    {
        njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
        work->njp_mode = 3;
    }
}

// @800C4E38 njp_sna_anim_spin_end_800C4E38
void njp_sna_anim_spin_end_800C4E38(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_nop_800C48EC;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 19, 4);
    }

    switch (work->field_A38_local_data)
    {
    case 0:
        if (work->body.is_end != 0)
        {
            njp_SetAction_8004E22C(work, 12, 4);
            GM_SeSetMode(&work->control.mov, 199, 1);
            njp_sna_800C3318(work);
            njp_sna_spin_targets(work);
            work->field_A38_local_data++;
        }
        break;

    case 1:
        if (work->field_A3A % 10 == 0)
        {
            GM_SeSetMode(&work->control.mov, 208, 1);
        }

        work->field_A3A++;

        if (work->field_A3A == 24)
        {
            njp_sna_800C3270(work);
            work->njp_mode = 3;
        }

        if (work->field_A3A == 32)
        {
            njp_sna_800C3318(work);
            njp_sna_spin_targets(work);
        }
        break;
    }
}

// @800C5104 njp_DG_ObjsMinY_800C5104
// lowest y of the models of the objects
int njp_DG_ObjsMinY_800C5104(DG_OBJS *objs)
{
    DG_OBJ *obj;
    int     min;
    int     n;
    int     i;

    obj = objs->objs;
    min = 100000;
    n = objs->n_models;

    for (i = 0; i < n; i++)
    {
        if (obj->world.t[1] < min)
        {
            min = obj->world.t[1];
        }

        obj++;
    }

    return min;
}

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_1.s")
//ASM-END

// @800C54EC njp_sna_anim_800C54EC
void njp_sna_anim_800C54EC(SnaInitWork *work, int time)
{
    if (time == 0)
    {
        work->field_9C8_anim_update_fn_3p = njp_800C60E4;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_SetAction_8004E22C(work, 5, 4);
        njp_sna_8004E260(work, 26, 4, 1022);
        work->field_A38_local_data = 1;
    }
}

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_2.s")
//ASM-END

// @800C5A70 njp_sna_move_targets_800C5A70
// moves the extra targets to the probe points in front of the ninja
void njp_sna_move_targets_800C5A70(SnaInitWork *work)
{
    SVECTOR probe[3];
    MATRIX  mtx;
    int     i;

    ReadRotMatrix(&mtx);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(njp_front_probe, probe, 3);

    for (i = 0; i < work->njp_num_targets; i++)
    {
        GM_MoveTarget(work->njp_targets[i], &probe[i]);
    }

    SetRotMatrix(&mtx);
}

// @800C5B18 njp_sna_check_hits_800C5B18
// checks if the extra targets were hit, returns the number of hits
int njp_sna_check_hits_800C5B18(SnaInitWork *work)
{
    MATRIX  mtx;
    TARGET *target;
    int     hits;
    int     i;

    hits = 0;

    if (njp_GM_CheckPlayerStatusFlag(PLAYER_INVINCIBLE))
    {
        return hits;
    }

    for (i = 0; i < work->njp_num_targets; i++)
    {
        target = work->njp_targets[i];

        if ((target->damaged & TARGET_POWER) && target->a_mode == 1)
        {
            target->damaged &= ~TARGET_POWER;
            target->a_mode = 0;
            target->vital = 1024;
            ReadRotMatrix(&mtx);
            hits++;
            mtx.t[0] = target->center.vx;
            mtx.t[1] = target->center.vy;
            mtx.t[2] = target->center.vz;
            GM_SeSetMode(&work->control.mov, 211, 1);
            NewSpark(&mtx, 1);
        }
    }

    return hits;
}

// @800C5C18 njp_sna_anim_update_800C5C18
void njp_sna_anim_update_800C5C18(SnaInitWork *work, int time)
{
    work->njp_field_9E4 = 2;
    njp_sna_move_targets_800C5A70(work);

    if (njp_sna_check_hits_800C5B18(work))
    {
        if (++work->field_A38_local_data >= 3)
        {
            work->field_A38_local_data = 0;
        }

        njp_SetAction_8004E22C(work, work->field_A38_local_data + 16, 0);
    }

    if (work->body.is_end != 0)
    {
        njp_SetAction_8004E22C(work, 3, 4);
        work->field_A38_local_data = -1;
    }

    if (!(work->field_9B0_pad_ptr->status & PAD_CIRCLE))
    {
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4AF0);
        njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3 | SNA_FLAG1_UNK30);
        njp_GM_SetPlayerStatusFlag(PLAYER_ATTACK);
        njp_FreeTargets(work);
    }
    else if (njp_gSnaMoveDir_800ABBA4 >= 0)
    {
        work->control.turn.vy = njp_gSnaMoveDir_800ABBA4;

        if (work->field_A3A++ >= 2)
        {
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4A90);
            njp_GM_SetPlayerStatusFlag(PLAYER_MOVE);
            njp_FreeTargets(work);
        }
    }
}

// @800C5D4C njp_sna_anim_update_800C5D4C
void njp_sna_anim_update_800C5D4C(SnaInitWork *work, int time)
{
    int angle;

    njp_sna_move_targets_800C5A70(work);

    if (njp_sna_check_hits_800C5B18(work))
    {
        if (++work->field_A38_local_data >= 3)
        {
            work->field_A38_local_data = 0;
        }

        njp_sna_8004E260(work, work->field_A38_local_data + 16, 0, 1022);
        njp_sna_8004F034(work, 1022);
    }

    if (work->body.time2 != 0)
    {
        njp_sna_8004E260(work, 0, 4, 0);
        work->field_A38_local_data = -1;
    }

    if (!(work->field_9B0_pad_ptr->status & PAD_CIRCLE))
    {
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C54EC);
        njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3 | SNA_FLAG1_UNK30);
        njp_GM_SetPlayerStatusFlag(PLAYER_ATTACK);
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        njp_sna_8004E260(work, 0, 4, 0);
        njp_FreeTargets(work);
    }
    else if (njp_gSnaMoveDir_800ABBA4 < 0)
    {
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_800C4A38);
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        njp_sna_8004E260(work, 0, 4, 0);
        njp_FreeTargets(work);
    }
    else
    {
        angle = njp_sub_8004E4C0(work, njp_gSnaMoveDir_800ABBA4);
        work->control.turn.vy = angle;
        njp_sub_8004EA50(work, angle);
    }
}

// @800C5E9C njp_sna_anim_slash_update_800C5E9C
void njp_sna_anim_slash_update_800C5E9C(SnaInitWork *work, int time)
{
    work->njp_field_9E4 = 2;

    if (time >= 3)
    {
        if (time == 16)
        {
            njp_sna_clear_invuln_8004F2EC(work);
        }

        njp_sna_800C3898(work, njp_stru_8009EFD4[0]);
        njp_sna_800C399C(work);

        if (work->body.is_end != 0)
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_ATTACK);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
        }
    }
}

// @800C5F20 njp_sna_anim_update_800C5F20
void njp_sna_anim_update_800C5F20(SnaInitWork *work, int time)
{
    if (time >= 5 && time < 16)
    {
        work->njp_field_9E4 = 2;
    }

    if (time == 0)
    {
        njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK13);
        work->field_A2C.vy = 0;
    }

    if (time < 10)
    {
        njp_sna_800C35BC(work, njp_gSnaMoveDir_800ABBA4, 96);
        work->field_798_p_height = 0;
        work->control.skip_flag |= CTRL_BOTH_CHECK;
    }

    if (time == 10)
    {
        work->control.skip_flag &= ~CTRL_BOTH_CHECK;
        njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK13);
    }

    if (time >= 3)
    {
        if (time == 10)
        {
            njp_sna_clear_invuln_8004F2EC(work);
        }

        if (time >= 10 && work->field_A3A == 0 && (work->control.grounded & 1))
        {
            GM_SeSetMode(&work->control.mov, 210, 1);
            work->field_A3A = 1;
        }

        njp_sna_800C3898(work, njp_stru_8009EFD4[1]);
        njp_sna_800C399C(work);

        if (work->body.is_end != 0 ||
            (work->body.action == 13 && work->m_ctrl.info1.frame >= 16 && njp_gSnaMoveDir_800ABBA4 >= 0))
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_ATTACK);
            njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);

            if (njp_gSnaMoveDir_800ABBA4 >= 0)
            {
                njp_sna_start_anim_8004E1F4(work, njp_sna_anim_run_begin_80053B88);
            }
            else
            {
                njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
                njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
            }
        }
    }
}

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_3.s")
//ASM-END

// @800C6244 njp_sna_80051A10
void njp_sna_80051A10(SnaInitWork *work, SVECTOR *pPos, SVECTOR *pOut, SVECTOR *pVec)
{
    MATRIX rot;
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR vec3;
    SVECTOR vec4;

    int len;

    ReadRotMatrix(&rot);
    DG_SetPos2(pPos, &work->control.rot);
    DG_PutVector(pVec, pVec, 1);
    SetRotMatrix(&rot);

    vec = *pPos;
    vec2 = *pVec;

    if (njp_sna_line_check(&vec, work->control.map->hzd, HZD_CHK_ALL, SEGMENT_ATR) < 0)
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

// @800C63D8 njp_sna_80051BA4
int njp_sna_80051BA4(SnaInitWork *work)
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

        vec2 = vec = DG_ZeroVector;
        vec2.vx = 1280;
        vec.vx = -1280;
        vec3 = work->field_A60;

        njp_sna_80051A10(work, &vec3, &work->field_A3C, &vec2);
        njp_sna_80051A10(work, &vec3, &work->field_A44, &vec);

        if (!njp_sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK16))
        {
            work->field_A58 = 8;
            njp_sna_set_flags1_8004E2F4(work, SNA_FLAG1_UNK16);
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
            njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK16);
            return 0;
        }

        return 1;
    }

    return 0;
}

// @800C65D4 njp_800C65D4
void njp_800C65D4(SnaInitWork *work)
{
    unsigned short status = work->field_9B0_pad_ptr->status;
    unsigned char ldy = work->field_9B0_pad_ptr->left_dy;
    short *temp_s4;
    int var_s1;
    int var_s2;
    int var_s0;
    int temp_a1;
    short var_a0;
    short var_a2;

    GM_CheckShukanReverse(&status);
    GM_CheckShukanReverseAnalog(&ldy);

    temp_s4 = work->field_9D0;
    var_s2 = temp_s4[4];
    var_s1 = -temp_s4[3];

    if (work->field_9D0[0] == 0)
    {
        var_s0 = 0;
    }
    else
    {
        var_s0 = work->control.turn.vx;
    }

    if (var_s1 < njp_dword_800ABBDC)
    {
        var_s1 = njp_dword_800ABBDC;
    }

    if (var_s2 > njp_dword_800ABBD4)
    {
        var_s2 = njp_dword_800ABBD4;
    }

    temp_a1 = njp_sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK15);
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

// @800C67B0 njp_sna_80051FD0
void njp_sna_80051FD0(SnaInitWork *work)
{
    int          iVar1;
    u_short      uVar2;
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
        uVar3 = njp_sna_check_flags1_8004E31C(work, SNA_FLAG1_UNK15);
        sVar4 = 1;
        sVar5 = 1;
        if (uVar2 & PAD_LEFT)
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x40;
                sVar5 = 0x40 - work->field_9B0_pad_ptr->left_dx;
            }
            iVar6 = ((int)short_arr[8]) * (sVar5 & 0xff);
            iVar1 += iVar6 / sVar4;
        }
        else
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x3f;
                sVar5 = work->field_9B0_pad_ptr->left_dx + 0x40;
            }
            iVar6 = ((int)short_arr[7]) * (sVar5 & 0xff);
            iVar1 -= iVar6 / sVar4;
        }
        work->control.turn.vy = iVar1;
    }
}

// @800C6900 njp_sna_fp_update_800C6900
void njp_sna_fp_update_800C6900(SnaInitWork *work, int time)
{
    njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
    njp_SetAction_8004E22C(work, 2, 4);

    if ((work->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        njp_sna_8004EC00(work);
        njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
    }
    else
    {
        if (njp_sna_80051BA4(work))
        {
            return;
        }

        njp_800C65D4(work);
        njp_sna_80051FD0(work);
    }
}

// @800C6994 njp_sna_fp_update_800C6994
void njp_sna_fp_update_800C6994(SnaInitWork *work, int time)
{
    u_short status = work->field_9B0_pad_ptr->status;
    u_short press = work->field_9B0_pad_ptr->press;

    if ((status & PAD_TRIANGLE) == 0)
    {
        njp_sna_8004EC00(work);
        work->field_A38_local_data = 2;
    }
    else
    {
        if (njp_GM_CheckPlayerStatusFlag(PLAYER_MOVE) != 0)
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
            njp_SetAction_8004E22C(work, 21, 4);
        }

        if (((press & PAD_UDLR) != 0) || ((status & PAD_UDLR) == 0))
        {
            njp_GM_ClearPlayerStatusFlag(PLAYER_CAUTION);
            work->field_A28 = 0x1c2;
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
            GM_ExitBehindCamera();
        }

        njp_sna_80051BA4(work);
    }
}

// @800C6A60 njp_sna_fp_update_800C6A60
void njp_sna_fp_update_800C6A60(SnaInitWork *work, int time)
{
    if ((work->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        njp_sna_8004EC00(work);
    }

    GM_SnakeCamera.position.vy += 320;
    njp_sna_8004EE28(work);
}

// @800C6AC0 njp_sna_anim_chokethrow_begin2_80058C80
void njp_sna_anim_chokethrow_begin2_80058C80(SnaInitWork *work, int time)
{
    int        bClear;            // $s0
    TARGET *field_8E8_pTarget; // $v1
    int        action_flag;       // $a1
    SVECTOR   *p;

    if (time == 0)
    {
        work->field_904_frames_last_choke = 0;
        work->field_9C8_anim_update_fn_3p = njp_nop_800C48EC;
        work->field_9CC_anim_update_fn_1p = njp_nop_800C48EC;
        njp_GM_ClearPlayerStatusFlag(PLAYER_MOVE);
        bClear = 0;
        work->field_A54.choke_count = 0;

        if (!njp_sna_8004FDE8(work, &njp_stru_8009EFE4))
        {
            bClear = 1;
            work->field_A38_local_data = 1;
        }

        p = &work->field_8EC_vec;
        if (!bClear)
        {

            field_8E8_pTarget = work->field_8E8_pTarget;

            field_8E8_pTarget->faint--;

            DG_SetPos2(&field_8E8_pTarget->center, &work->control.rot);

            DG_PutVector(&njp_svector_800AB7FC, p, 1);
            DG_SetPos2(&work->control.mov, &work->control.rot);
            GV_SubVec3(p, &work->control.mov, p);
            p->vx /= 4;
            p->vy /= 4;
            p->vz /= 4;
            action_flag = 25;
        }
        else
        {
            work->field_8EC_vec = DG_ZeroVector;
            action_flag = 3;
        }
        njp_SetAction_8004E22C(work, action_flag, 4);
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
            njp_sna_clear_flags1_8004E308(work, SNA_FLAG1_UNK3);
            njp_sna_start_anim_8004E1F4(work, njp_sna_anim_idle_800C4200);
        }
        else
        {
            work->field_89C_pTarget->size.vx = 150;
            njp_sna_start_anim_8004E1F4(work, njp_800C6CA4);
        }
    }
}

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_4.s")
//ASM-END

// @DATA
// FIXME: the data is defined after the code on purpose: the code was compiled with only the type alignment of the
// tables known (e.g. the 20 byte copy of njp_word_8009EFC0 is done with lwl/lwr).
u_char njp_dword_8009EED4[4] = {127, 4, 0, 0}; // pad vibration data
u_char njp_dword_8009EED8[8] = {225, 1, 255, 2, 0, 0, 0, 0};
u_char njp_dword_8009EEE0[4] = {127, 6, 0, 0};
u_char njp_dword_8009EEE4[12] = {225, 1, 255, 4, 225, 2, 75, 8, 0, 0, 0, 0};
u_char njp_dword_8009EF24[8] = {0, 2, 127, 2, 0, 0, 0, 0};
u_char njp_dword_8009EF2C[8] = {60, 2, 200, 4, 40, 2, 0, 0};

short njp_word_8009EFC0[10] = {0, 500, 0, 320, 400, 320, 400, 32, 32, 0};

SVECTOR njp_svector_800AB7D4 = {0, 0, 100, 0};
SVECTOR njp_svector_800AB7DC = {-1024, 0, 0, 0};

SVECTOR njp_front_probe[3] = {{-300, 0, 400, 0}, {0, 0, 400, 0}, {300, 0, 400, 0}};

SVECTOR njp_stru_8009EFD4[3][2] = {
    {{10, -75, 0, 0}, {10, -75, -930, 0}},
    {{10, -75, 0, 0}, {10, -75, -1130, 0}},
    {{10, -75, 0, 0}, {10, -75, -930, 0}},
};

Target_Data njp_stru_8009EFE4 = {{0, 0, 0, 0}, {501, 600, 501, 0}, 0, 0, 7, 0};

SVECTOR njp_svector_800AB7FC = {0, 0, -300, 0};

// FIXME: the pad of this build is 4 bytes smaller than GV_PAD (the analog stick part is missing), the data ends here
typedef struct NjpPad
{
    u_short status;
    u_short press;
    u_short release;
    u_short quick;
    short   dir;
    short   analog;
} NjpPad;

NjpPad njp_GV_PadData_8009F0C4 = {0, 0, 0, 0, -1, 0};
















































