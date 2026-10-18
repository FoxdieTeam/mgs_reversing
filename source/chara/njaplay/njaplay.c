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
int          SECTION(".bss") njp_bss_44;
int          SECTION(".bss") njp_bss_48;
int          SECTION(".bss") njp_bss_52;
int          SECTION(".bss") njp_bss_56;
int          SECTION(".bss") njp_bss_60;

// data of the object (.data), in the order of the original
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

#define GetAction( work ) (work->body.action)
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

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_0.s")
//ASM-END

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

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_1.s")
//ASM-END

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

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay_2.s")
//ASM-END

