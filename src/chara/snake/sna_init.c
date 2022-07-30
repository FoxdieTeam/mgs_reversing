#include "sna_init.h"
#include "Script_tbl_map_8002BB44.h"
#include "libdg.h"
#include "linker.h"
#include "map.h"
#include "object.h"

// TODO: Header
void GM_ConfigControlInterp_80026244(GM_Control *pControl, char f5a);
void GM_ConfigObjectOverride_80034D30(OBJECT *obj, int a1, int motion, int interp, int a4);

extern unsigned int GM_Sound_80032968(int a1, int a2, int a3);

extern SVECTOR stru_8009EFC0;
extern SVECTOR stru_8009EFC8;
extern int dword_8009EFD0;

extern Target_Data stru_8009EFE4;

extern Sna_E1 e1_800AB7C4;
Sna_E1 SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int SECTION(".sbss") dword_800ABBA8;

extern int dword_800ABBA4;
int SECTION(".sbss") dword_800ABBA4;

extern int dword_800ABBB4;
int SECTION(".sbss") dword_800ABBB4;

extern GM_Control *gControl_800AB9F4;
extern OBJECT *dword_800ABA20;

extern int sub_800296C4(int param_1, short *param_2, unsigned int param_3);
extern void sub_800298DC(int *param_1);

extern int HZD_SlopeFloorLevel_800298F8(short *param_1, int arg1);
extern long SquareRoot0_80092708(long a);
extern int GV_VecDir2_80016EF8(SVECTOR *vec);

extern int dword_800ABBB8;
int SECTION(".sbss") dword_800ABBB8;

extern int GM_AlertMode_800ABA00;

extern GameState_800B4D98 gGameState_800B4D98;
extern int GM_GameOverTimer_800AB3D4;
extern int GM_GameStatus_800AB3CC;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int GM_PlayerStatus_800ABA50;
extern Target_Data stru_8009F044;
extern SVECTOR stru_800AB7FC;

extern void GM_ConfigObjectAction_80034CD4(OBJECT *obj, int action_flag, int motion, int interp);
void sub_80032858(SVECTOR *pVec, int a2);
void GV_AddVec3_80016D00(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst);

void sna_init_fn_800535B8(Actor_SnaInit *pActor);
void sna_init_80053360(Actor_SnaInit *pActor);
void sna_init_80050440(Actor_SnaInit *pActor);
void sna_init_fn_800531F4(Actor_SnaInit *pActor);
void sna_init_fn_80052E58(Actor_SnaInit *pActor);
void sna_init_8004EC00(Actor_SnaInit *pActor);
void sna_init_8004EE28(Actor_SnaInit *pActor);
void sna_init_anim_box_idle_800553EC(Actor_SnaInit *pActor, int a2);
void sna_init_80051DA0(Actor_SnaInit *pActor);
void sna_init_80056A54(Actor_SnaInit *pActor);
void sna_init_fn_800525F8(Actor_SnaInit *pActor);
void sna_init_fn_80056AD8(Actor_SnaInit *pActor);
void sna_init_start_anim_8004E1F4(Actor_SnaInit *pActor, void *pFn); // TODO: fn type
void sna_init_800571B8(Actor_SnaInit *pActor, int a2);
void sna_init_80057118(Actor_SnaInit *pActor, int a2);
int sna_init_8004FDE8(Actor_SnaInit *pActor, Target_Data *pVec);
void sna_init_knockdown_check_getup_80056A1C(Actor_SnaInit *pActor);
void sna_init_fn_80052540(Actor_SnaInit *pActor);
void sna_init_8004F8E4(Actor_SnaInit *pActor, int a2);
void sna_init_80050568(Actor_SnaInit *pActor);
int sna_init_prone_check_standup_80050398(Actor_SnaInit *pActor);
void sna_init_anim_throw_800589C8(Actor_SnaInit *pActor, int a2);
void sna_init_knockdown_getup_80050668(Actor_SnaInit *pActor);
void sna_init_anim_chokethrow_begin2_80058C80(Actor_SnaInit *pActor, int a2);
void sna_init_gun_800540D0(Actor_SnaInit *pActor, int a2);
void sna_init_anim_shoot_weapon_80056B88(Actor_SnaInit *pActor, int a2);
void sub_80057BF0(Actor_SnaInit *pActor, int a2);
void sna_init_anim_shoot_weapon_helper_80057590(Actor_SnaInit *pActor);
void sub_8005688C(Actor_SnaInit *pActor);
void sub_80052468(Actor_SnaInit *pActor);
void sna_init_8005684C(Actor_SnaInit *pActor);
void sub_80054424(Actor_SnaInit *pActor, int a2);
void sub_80053E9C(Actor_SnaInit *pActor, int a2);
void sub_8005684C(Actor_SnaInit *pActor);
void sna_init_anim_choke_80058E88(Actor_SnaInit *pActor, int a2);
void sna_init_anim_punch_helper_800591F4(Actor_SnaInit *pActor, int a2);
void sna_init_anim_choke_helper_8005951C(Actor_SnaInit *pActor);
void sna_init_anim_choke_rechoke_helper_8005961C(Actor_SnaInit *pActor, int a2);

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
    if (pActor->field_9C.action_flag != action_flag)
    {
        GM_ConfigObjectAction_80034CD4(&pActor->field_9C, action_flag, 0, interp);
    }
}

void sna_init_8004E260(Actor_SnaInit *pActor, int a2, int interp, int a4)
{
    if (pActor->field_9C.field_10 != a2)
    {
        GM_ConfigObjectOverride_80034D30(&pActor->field_9C, a2, 0, interp, a4);
    }
}

int GM_CheckPlayerStatusFlag_8004E29C(int arg0)
{
    return (GM_PlayerStatus_800ABA50 & arg0) != 0;
}

int GM_SetPlayerStatusFlag_8004E2B4(int arg0)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus_800ABA50 | arg0;
    GM_PlayerStatus_800ABA50 = temp_v0;
    return temp_v0;
}

void GM_ClearPlayerStatusFlag_8004E2D4(int flag)
{
    GM_PlayerStatus_800ABA50 &= ~flag;
}

void sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flags)
{
    snake->field_894_flags |= flags;
}

void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags)
{
    snake->field_894_flags &= ~flags;
}

int sna_init_check_flags_8004E31C(Actor_SnaInit *snake, unsigned int flags)
{
    return (snake->field_894_flags & flags) != 0;
}

void sna_init_8004E330(Actor_SnaInit *snake, unsigned int flag)
{
    snake->field_898_flags = snake->field_898_flags | flag;
}

void sna_init_clear_flags_8004E344(Actor_SnaInit *snake, unsigned int flags)
{
    snake->field_898_flags = snake->field_898_flags & ~flags;
}

unsigned int sna_init_sub_8004E358(Actor_SnaInit *snake, unsigned int param_2)
{
    unsigned int result = 0;

    if (gGameState_800B4D98.field_BE != 0)
    {
        result = (((unsigned int)snake->field_898_flags & param_2) != result);
    }

    return result;
}

void sna_init_check_dead_8004E384(Actor_SnaInit *snake)
{
    if ((gGameState_800B4D98.field_16_snake_current_health == 0) || (GM_GameOverTimer_800AB3D4 != 0))
    {
        (snake->field_20_ctrl).field_55_flags = (snake->field_20_ctrl).field_55_flags | 2;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags_8004E2F4(snake, 0x400000);
        GM_GameStatus_800AB3CC |= 0x10080000;

        if (GM_GameOverTimer_800AB3D4 != -2)
        {
            sna_init_set_flags_8004E2F4(snake, 0x30);
        }
    }
}

void sna_init_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags)
{
    GM_Target *target = snake->field_8E8_pTarget;

    if (target != 0)
    {
        target->field_6_flags &= ~flags;
        snake->field_8E8_pTarget = 0;
        snake->field_A54 = 0;
        snake->field_89C_pTarget->field_10_size.vx = 300;
    }
}

// ... categorize move/turn direction by angle?
// param_1: snake->field_20_ctrl.field_4C_turn_vec.vy
// param_2: _dword_800ABBA4_snake_move_angle (guessed name)
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

int sub_80028454(void *pHzd, SVECTOR *a2, SVECTOR *a3, int a4, int a5);
void sub_80028890(SVECTOR *pVec);
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

void sub_8004E588(int param_1, short *param_2, int *param_3)
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
    return;
}
#pragma INCLUDE_ASM("asm/sub_8004E5E8.s")
#pragma INCLUDE_ASM("asm/sub_8004E71C.s")
#pragma INCLUDE_ASM("asm/sub_8004E808.s")

int sub_8004E930(Actor_SnaInit *snake, int arg1)
{
    int int0;
    int int1;
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

#pragma INCLUDE_ASM("asm/sub_8004E9D0.s")

extern unsigned int GV_DiffDirS_8001704C(int param_1, int param_2);

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

#pragma INCLUDE_ASM("asm/sub_8004EB14.s")

extern short dword_800B7800[];
extern void sd_set_cli_800887EC(int code, int unused);
void sub_8004EB74(Actor_SnaInit *pActor)
{
    if (dword_800B7800[5] == 0)
    {
        if ((short)(pActor->field_9B0_pad_bits[4]) == (short)0xffff)
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

// TODO: this is a struct
short SECTION(".word_800B77E8") word_800B77E8[18]; // dummy size
void sna_init_8004EC00(Actor_SnaInit *pActor)
{
    if (word_800B77E8[17] == 1)
    {
        pActor->field_A20 = 6;
    }

    word_800B77E8[17] = 0;
    pActor->field_A56 = 0;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK8 | PLAYER_STATUS_FIRST_PERSON);
    sna_init_clear_flags_8004E308(pActor, 0x8000);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        sd_set_cli_800887EC(0x1ffff21, 0);
    }

    sna_init_clear_flags_8004E344(pActor, 0x30);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK400);
}

/* extern short dword_800B7800[]; */

extern void sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flag);
extern void sd_set_cli_800887EC(int code, int unused);
extern void sna_init_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sna_init_8004EC8C(Actor_SnaInit *pActor)
{
    ushort v2; // $v1

    sna_init_set_flags_8004E2F4(pActor, 2048);
    pActor->field_A28 = 460;
    dword_800B7800[5] = 1;
    v2 = *(ushort *)&e1_800AB7C4.field_4;
    pActor->field_A20 = -6;
    pActor->field_9D0[0].vz = 320;
    pActor->field_9D0[1].vx = v2;
    pActor->field_9D0[1].vz = v2;
    sd_set_cli_800887EC(0x1FFFF20, 0);
    sna_init_8004E330(pActor, 0x10);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON);
}

void sub_8004EB14(Actor_SnaInit *pActor);
void sub_8004ED08(Actor_SnaInit *pActor)
{
    sna_init_clear_flags_8004E308(pActor, 0x800);
    pActor->field_A28 = 0x1c2;
    dword_800B7800[5] = 0; // weapon related?
    pActor->field_A20 = 6;
    sub_8004EB14(pActor);
    sd_set_cli_800887EC(0x1ffff21, 0);
    sna_init_clear_flags_8004E344(pActor, 0x30);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper3_8004ED6C.s")

// need bss: short 800b77e0
#pragma INCLUDE_ASM("asm/sna_init_8004EE28.s")

int sub_80026418(int arg0, int arg1);
short sub_8002646C(int, int, char); // dummy signature
void sub_8004EEB0(Actor_SnaInit *pActor)
{
    short sVar1;
    int iVar2;
    int arg0;

    if (dword_800ABBA4 >= 0) // snake move angle
    {
        arg0 = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        if (GV_DiffDirS_8001704C(arg0, dword_800ABBA4))
        {
            iVar2 = sub_80026418(arg0, dword_800ABBA4);
            sVar1 = sub_8002646C(iVar2, dword_800ABBA4, 0x40);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = sVar1;
        }
    }
}

// https://decomp.me/scratch/k2Awn regswap
#pragma INCLUDE_ASM("asm/sub_8004EF14.s")

#pragma INCLUDE_ASM("asm/sub_8004EFE4.s")

extern int sub_8004EFE4(Actor_SnaInit *param_1, int param_2);

void sna_init_8004F034(Actor_SnaInit *pActor, unsigned int bits)
{
    if (bits != pActor->field_180.field_0C)
    {
        pActor->field_180.field_24 = ~bits;
        pActor->field_180.field_0C = bits;
        if (bits == 0xFFFF && sub_8004EFE4(pActor, 2) >= 0)
        {
            pActor->field_180.interp = 4;
            pActor->field_180.field_30 = 2;
        }
    }
}

extern int dword_800AB7D4;
extern int dword_800AB7DC;
void DG_MovePos_8001BD20(SVECTOR *svector);
void DG_RotatePos_8001BD64(SVECTOR *svector);
void ReadRotMatrix_80092DD8(MATRIX *m);
void NewBlood_80072728(MATRIX *, int); // dummy signature
void sna_init_act_helper2_helper4_8004F090(Actor_SnaInit *pActor, int param_2)
{
    int iVar1;
    MATRIX mtx;

    DG_SetPos_8001BC44(&pActor->field_9C.objs->objs[6].world);
    DG_MovePos_8001BD20((SVECTOR *)&dword_800AB7D4);
    DG_RotatePos_8001BD64((SVECTOR *)&dword_800AB7DC);
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

extern unsigned short GM_WeaponTypes_8009D580[];
extern Sna_ActionTable actions_no_weapon_8009ED70;
void GV_DestroyActorQuick_80015164(struct Actor *pActor);
void sna_init_anim_chokethrow_begin1_80054210(Actor_SnaInit *pActor);
void sub_8004F14C(Actor_SnaInit *param_1)
{
    param_1->field_91C_weapon_idx = -1;
    gGameState_800B4D98.field_1C_equipped_weapon = -1;

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
                                          PLAYER_STATUS_UNK8 | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags_8004E344(param_1, 0x20);
    }
    else
    {
        sna_init_8004EC00(param_1);
    }
}

extern int GM_ItemTypes_8009D598[];
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
                                          PLAYER_STATUS_UNK8 | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags_8004E344(param_1, 0x20);
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

extern void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags);

void sna_init_clear_invuln_8004F2EC(Actor_SnaInit *snake)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_INVULNERABLE);
    sna_init_clear_flags_8004E308(snake, 1);
    snake->field_89C_pTarget->field_0_flags |= 0x9e;
}

int GM_ConfigMotionAdjust_80035008(OBJECT *pObj, SVECTOR *adjust);
void GM_ExitBehindCamera_80030AEC(void);
void sub_8004F338(Actor_SnaInit *param_1)
{
    int iVar2;

    iVar2 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT);
    if (iVar2 != 0)
    {

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_UNK8 | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags_8004E344(param_1, 0x20);
        param_1->field_A56 = 0;
    }
    else
    {
        sna_init_8004EC00(param_1);
    }

    sna_init_clear_invuln_8004F2EC(param_1);
    param_1->field_A24_invuln_frames = 0;
    sna_init_sub_8004E41C(param_1, 2);
    GM_ConfigMotionAdjust_80035008(&param_1->field_9C, 0);
    sna_init_clear_flags_8004E308(param_1, 0x100);
    param_1->field_9C0 = 0;
    sna_init_8004E260(param_1, 0, 4, 0);
    param_1->field_92C->def = (DG_DEF *)((int)param_1->field_92C->def | 0x100);
    GM_ExitBehindCamera_80030AEC();

    GM_PlayerStatus_800ABA50 &= PLAYER_STATUS_UNK10000000 | PLAYER_STATUS_UNK4000000 | PLAYER_STATUS_UNK2000 |
                                PLAYER_STATUS_UNK1000 | PLAYER_STATUS_FIRST_PERSON_DUCT | PLAYER_STATUS_UNK4 |
                                PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE;

    if ((param_1->field_920_tbl_8009D580 & 0x200U) != 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON);
    }

    param_1->field_A28 = 0x1c2;
    param_1->field_894_flags &= 0x18080000;
    param_1->field_20_ctrl.field_55_flags &= 0xf7;
    sna_init_clear_flags_8004E344(param_1, 0x100);
}

#pragma INCLUDE_ASM("asm/sub_8004F454.s")
#pragma INCLUDE_ASM("asm/sub_8004F544.s")
#pragma INCLUDE_ASM("asm/sub_8004F628.s")

#pragma INCLUDE_ASM("asm/OPERATOR_8004F6E8.s")
#pragma INCLUDE_ASM("asm/sna_init_8004F8E4.s")

int sna_act_unk_helper4_8004FA3C(void)
{
    if (gGameState_800B4D98.field_16_snake_current_health == 0 || GM_GameOverTimer_800AB3D4 != 0)
    {
        return 1;
    }
    return 0;
}

extern void sna_init_clear_flags_8004E344(Actor_SnaInit *param_1, unsigned int param_2);

void sna_init_8004FA74(Actor_SnaInit *param_1)
{
    sna_init_clear_flags_8004E344(param_1, 0x20);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                      PLAYER_STATUS_UNK8);
}

extern void sna_init_80051FD0(Actor_SnaInit *snake);
extern void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = *snake->field_9B0_pad_bits;
    sna_init_80051FD0(snake);
    if (action & 0x4000)
    {
        sna_init_8004E330(snake, 1);
    }
}

#pragma INCLUDE_ASM("asm/sub_8004FAE8.s")
#pragma INCLUDE_ASM("asm/sub_8004FB38.s")
#pragma INCLUDE_ASM("asm/sub_8004FB4C.s")
#pragma INCLUDE_ASM("asm/sub_8004FB90.s")
#pragma INCLUDE_ASM("asm/sub_8004FBA0.s")
#pragma INCLUDE_ASM("asm/Game/GM_ClearBulName_8004FBE4.s")

void GM_CheckShukanReverse_8004FBF8(unsigned short *pInput)
{
    unsigned short old;
    unsigned int v2; // $v1
    unsigned int v3; // $v0

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

#pragma INCLUDE_ASM("asm/sub_8004FCB8.s")
#pragma INCLUDE_ASM("asm/sna_init_8004FDE8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper5_8004FF88.s")
#pragma INCLUDE_ASM("asm/sub_8005009C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_check_knock_800501F8.s")
#pragma INCLUDE_ASM("asm/sub_8005027C.s")

int sub_8004E808(Actor_SnaInit *pActor, int, int, int, int); // dummy signature
void sna_init_anim_prone_standup_80053D74(Actor_SnaInit *param_1, int anim_frame);
int sna_init_prone_check_standup_80050398(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_bits[1] & 0x40) != 0 && sub_8004E808(pActor, 1, 0, 0xfffffd92, 0x5dc) == 0)
    {

        pActor->field_A28 = 450;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_standup_80053D74);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_2, 4);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_vec.vy;
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/sna_init_80050440.s")

void sna_init_80050568(Actor_SnaInit *pActor)
{
    short dir;
    DG_OBJS *pDVar3;
    SVECTOR local_10;

    sna_init_80050440(pActor);
    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        pDVar3 = pActor->field_9C.objs;
        pActor->field_20_ctrl.field_4C_turn_vec.vz = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
        pActor->field_20_ctrl.field_44_vec.vz = 0;
        pActor->field_20_ctrl.field_44_vec.vx = 0;
        pDVar3->flag |= 0x80;
        sna_init_start_anim_8004E1F4(pActor, sub_80054424);
        pActor->field_A54 = 0;
        sna_init_set_invuln_8004F2A0(pActor, 24);
        sna_init_set_flags_8004E2F4(pActor, 1);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200 |
                                          PLAYER_STATUS_UNK100);
        sna_init_clear_flags_8004E308(pActor, 0x16);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);

        pDVar3 = (pActor->field_9C).objs;
        // TODO: clean this up
        local_10.vx = *(short *)&pDVar3[8].movs - *(short *)pDVar3[1].world.t;
        pDVar3 = (pActor->field_9C).objs;
        local_10.vz = pDVar3[9].world.m[0][2] - *(short *)(pDVar3[1].world.t + 2);

        dir = GV_VecDir2_80016EF8(&local_10);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dir;
        pActor->field_20_ctrl.field_8_vec.vy = dir;
        pActor->field_20_ctrl.field_55_flags &= 0xf7;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_knockdown_getup_80050668.s")

extern int dword_800ABBC4;
extern int dword_8009EEA4[];
int SECTION(".sbss") dword_800ABBC4;

int sub_800507D8(Actor_SnaInit *param_1)
{
    int ret;

    if (dword_800ABBC4 == 0 && param_1->field_A38 == 0)
    {
        param_1->field_A28 = 0x1c2;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_KNOCKING | PLAYER_STATUS_ON_WALL | PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(param_1, (void *)dword_8009EEA4[param_1->field_A26_fn_stance_idx]);
        sna_init_clear_flags_8004E308(param_1, 0x100);
        param_1->field_9C0 = 0;
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

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_80050878.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_80050A64.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk2_80051170.s")
#pragma INCLUDE_ASM("asm/sna_init_weapon_switching_800511BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_800515BC.s")
#pragma INCLUDE_ASM("asm/sub_80051A10.s")
#pragma INCLUDE_ASM("asm/sub_80051BA4.s")
#pragma INCLUDE_ASM("asm/sna_init_80051DA0.s")

void sna_init_80051FD0(Actor_SnaInit *snake)
{
    int iVar1;
    ushort uVar2;
    unsigned int uVar3;
    short sVar4;
    short sVar5;
    int iVar6;
    SVECTOR *vec_arr;

    vec_arr = snake->field_9D0;
    uVar2 = *snake->field_9B0_pad_bits;
    if ((uVar2 & 0xa000) != 0)
    {
        iVar1 = snake->field_20_ctrl.field_4C_turn_vec.vy;
        uVar3 = sna_init_check_flags_8004E31C(snake, 0x4000);
        sVar4 = 1;
        sVar5 = 1;
        if (uVar2 & 0x8000)
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x40;
                sVar5 = 0x40 - (*((unsigned char *)(snake->field_9B0_pad_bits + 7)));
            }
            iVar6 = ((int)vec_arr[2].vx) * (sVar5 & 0xff);
            iVar1 += iVar6 / sVar4;
        }
        else
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x3f;
                sVar5 = (*((unsigned char *)(snake->field_9B0_pad_bits + 7))) + 0x40;
            }
            iVar6 = ((int)vec_arr[1].pad) * (sVar5 & 0xff);
            iVar1 -= iVar6 / sVar4;
        }
        snake->field_20_ctrl.field_4C_turn_vec.vy = iVar1;
    }
}

void sna_init_fn_80052120(Actor_SnaInit *pActor, int a2);
#pragma INCLUDE_ASM("asm/sna_init_fn_80052120.s")

#pragma INCLUDE_ASM("asm/sub_8005230C.s")
/* TODO
void sub_8005230C(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);

    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) )
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
        if ( (*pActor->field_9B0_pad_bits & 0x10) == 0 )
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
PLAYER_STATUS_MOVING | PLAYER_STATUS_FIRST_PERSON); sna_init_start_anim_8004E1F4(pActor, sub_80054424);
            sna_init_clear_flags_8004E344(pActor, 0x20);
        }
        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
    }
    else
    {
        pActor->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
PLAYER_STATUS_MOVING | PLAYER_STATUS_FIRST_PERSON); sna_init_8004F2A0(pActor, 0); sna_init_start_anim_8004E1F4(pActor,
sub_80053E9C);
    }
}
*/

#pragma INCLUDE_ASM("asm/sub_80052468.s")

#pragma INCLUDE_ASM("asm/sna_init_fn_80052540.s")

void sna_init_fn_800525F8(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    if (pActor->field_9B8_fn_anim != sna_init_anim_box_idle_800553EC)
    {
        if (pActor->field_9C.field_1A)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_2, 4);
        }
    }

    if (!(*pActor->field_9B0_pad_bits & 0x10))
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
    if ((*pActor->field_9B0_pad_bits & 0x10) == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK8 |
                                              PLAYER_STATUS_FIRST_PERSON);
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
        pActor->field_A26_fn_stance_idx = 0;

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

void sna_init_anim_crouch_helper_80053014(void); // dummy signature
void sna_init_anim_crouch_800527DC(Actor_SnaInit *param_1, int anim_frame)
{
    int a2;

    if (anim_frame == 0)
    {
        if (param_1->field_A26_fn_stance_idx != 1)
        {
            a2 = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                a2 = 0xb7;
            }
            sub_80032858(&param_1->field_20_ctrl.field_0_position, a2);
        }

        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_crouch_helper_80053014;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_2, 4);
        param_1->field_A2E = -128;
    }

    if ((anim_frame == 0 && param_1->field_A26_fn_stance_idx != 0)
        || (anim_frame == 4 && param_1->field_A26_fn_stance_idx == 0))
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING);
        param_1->field_A26_fn_stance_idx = 1;
    }
}

void sna_init_anim_prone_idle_800528BC(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_A26_fn_stance_idx = 2;
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
        if (pActor->field_A54)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54 = 0;
    }
    sna_init_80050440(pActor);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_idle_and_c4_80052A5C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_move_80052BA8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_crouch_80052CCC.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_80052E58.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_crouch_helper_80053014.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_800531F4.s")
#pragma INCLUDE_ASM("asm/sna_init_80053360.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_800535B8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_idle_and_c4_helper_800537D4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_move_helper_800538CC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_crouch_helper_80053A54.s")

void sna_init_fn_nothing_80053B80(void)
{
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_run_begin_80053B88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_begin_80053BE8.s")

void sna_init_anim_prone_standup_80053D74(Actor_SnaInit *param_1, int anim_frame)
{
    int a2;

    if (anim_frame == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        param_1->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_8->field_2, 4);

        a2 = 8;
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
        {
            a2 = 0xb7;
        }
        sub_80032858(&param_1->field_20_ctrl.field_0_position, a2);
        sna_init_set_flags_8004E2F4(param_1, 0x30);
    }

    if (param_1->field_20_ctrl.field_32_height >= 250)
    {
        param_1->field_20_ctrl.field_55_flags |= 8;
    }

    if (param_1->field_20_ctrl.field_32_height > 500)
    {
        param_1->field_A26_fn_stance_idx = 0;
    }

    if (anim_frame == 2)
    {
        param_1->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (anim_frame == 7)
    {
        param_1->field_20_ctrl.field_55_flags |= 2;
    }

    if (param_1->field_9C.field_1A != 0)
    {
        param_1->field_20_ctrl.field_55_flags &= 0xf5;
        sna_init_start_anim_8004E1F4(param_1, sna_init_anim_idle_8005275C);
        sna_init_clear_flags_8004E308(param_1, 0x30);
    }
}

void sna_init_fn_800543A8(Actor_SnaInit *pActor, int a2);

// probably sna_init_anim_prone_first_person
// aka duct moving
void sub_80053E9C(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800543A8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags_8004E2F4(pActor, 0x30);

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0 &&
            pActor->field_9C.action_flag == pActor->field_9B4_action_table->field_4->field_4)
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
        sna_init_clear_flags_8004E308(pActor, 0x34);
        sna_init_clear_flags_8004E344(pActor, 0x100);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sub_80054424);
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        }
    }
}

void sub_80053FAC(Actor_SnaInit *pActor, int anim_frame)
{
    short vec_y;             // $v1
    unsigned short pad_bits; // $s1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_3, 2);
        sna_init_set_flags_8004E2F4(pActor, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
        vec_y = pActor->field_A54;
        pActor->field_A54 = 0;
        pActor->field_90C_pWeaponFn = sna_init_gun_800540D0;
        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = vec_y;
        sna_init_8004E260(pActor, 0, 4, 0);
    }

    pad_bits = *pActor->field_9B0_pad_bits;
    if (pActor->field_9C.field_1A || (pad_bits & 0x80) == 0)
    {
        sna_init_clear_flags_8004E308(pActor, 4);
        pActor->field_910 = 0;
        if ((pad_bits & 0x80) != 0)
        {
            sub_80032858(&pActor->field_20_ctrl.field_0_position, 9);
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

    if ((pActor->field_9B0_pad_bits[2] & 0x80) != 0)
    {
        pActor->field_A38 = 1;
    }

    if ((*pActor->field_9B0_pad_bits & 0x80) != 0)
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
    if (dword_800ABBA4 >= 0)
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
        sna_init_set_flags_8004E2F4(pActor, 0x2000000);
    }

    if (pActor->field_9C.field_1A)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);
        new_y = pActor->field_20_ctrl.field_4C_turn_vec.vy + 2048;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = new_y;
        pActor->field_20_ctrl.field_8_vec.vy = new_y;
        sna_init_clear_flags_8004E308(pActor, 0x2000004);
        sna_init_clear_invuln_8004F2EC(pActor);
    }
}

void sna_init_80054318(Actor_SnaInit *pActor, int anim_frame)
{

    if (anim_frame == 2 && dword_800ABBA4 >= 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_8005292C);
        return;
    }

    if ((*pActor->field_9B0_pad_bits & 0x4000) != 0)
    {
        sna_init_8004E330(pActor, 1);
    }

    if (pActor->field_9C.field_1A)
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
            sna_init_clear_flags_8004E308(pActor, 0x236);
            sna_init_clear_flags_8004E344(pActor, 0x100);
        }
    }
}

void sub_80054424(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sub_8005688C;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78 + 150;
}

extern void sub_80056928(void);

void sna_init_80054488(Actor_SnaInit *pActor, int anim_frame)
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

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shot_flinch_800544E0.s")

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

    if (pActor->field_9C.field_1A)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
        sna_init_clear_flags_8004E308(pActor, 0x20);
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper8_80054710.s")

void sna_init_anim_knockdown_idle_80054930(Actor_SnaInit *pActor, int anim_frame)
{
    int local_field_A54; // $v1
    int action_flag;     // $a1
    short v5;            // $a1

    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_knockdown_check_getup_80056A1C;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_flags_8004E2F4(pActor, 0x10);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK200 | PLAYER_STATUS_PRONE);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        local_field_A54 = pActor->field_A54;
        pActor->field_A26_fn_stance_idx = 2;
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
            if (pActor->field_A54 == 1)
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
        if (pActor->field_A54 == 1)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_6;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_7;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54 = 0;
    }

    if (pActor->field_20_ctrl.field_32_height >= 250)
    {
        pActor->field_20_ctrl.field_55_flags |= 8u;
    }

    if (pActor->field_20_ctrl.field_32_height >= 501)
    {
        pActor->field_A26_fn_stance_idx = 0;
    }

    if (anim_frame == 2)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (pActor->field_9C.field_1A)
    {
        sna_init_clear_flags_8004E308(pActor, 20);
        sna_init_set_invuln_8004F2A0(pActor, 24);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_set_flags_8004E2F4(pActor, 1);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        pActor->field_20_ctrl.field_55_flags &= ~8u;
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
        sna_init_8004F8E4(pActor, pActor->field_A54 == 1 ? 126 : 127);
    }
    else
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
    }

    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper10_80054C08.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_knock_80054D68.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_80054EFC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_scope_80055334.s")

extern void sna_init_anim_scope_80055334(int param_1, int anim_frame);

void sna_init_anim_jpegcam_800553CC(int param_1, int anim_frame)
{
    sna_init_anim_scope_80055334(param_1, anim_frame);
}

void sna_init_anim_box_idle_800553EC(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_80056A54;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_CROUCHING);
        pActor->field_A26_fn_stance_idx = 0;
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

    if (pActor->field_9C.field_1A)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_dying_80055524.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_800559D8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper3_80055DD8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_helper_80056650.s")

void sub_8005684C(Actor_SnaInit *pActor)
{
    int y;

    if ((*pActor->field_9B0_pad_bits & 0xa000) == 0)
    {
        return;
    }

    y = pActor->field_20_ctrl.field_4C_turn_vec.vy;
    if ((*pActor->field_9B0_pad_bits & 0x8000) != 0)
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

    if ((*pActor->field_9B0_pad_bits & 0x5000) != 0)
    {
        if ((*pActor->field_9B0_pad_bits & 0x1000) != 0)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        sna_init_start_anim_8004E1F4(pActor, sna_init_80054488);
    }
    else
    {
        sub_8005684C(pActor);
    }
}

#pragma INCLUDE_ASM("asm/sub_80056928.s")

void sna_init_knockdown_check_getup_80056A1C(Actor_SnaInit *pActor)
{
    if (pActor->field_9B0_pad_bits[1]) // x
    {
        sna_init_knockdown_getup_80050668(pActor);
    }
}

#pragma INCLUDE_ASM("asm/sna_init_80056A54.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_80056AD8.s")

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

void sna_init_anim_rungun_begin_helper_800577B4(void); // dummy signature
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

void sna_init_anim_rungun_helper_80057844(void); // dummy signature
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

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_nikita_80056C9C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_80056DDC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_stinger_800570C0.s")
#pragma INCLUDE_ASM("asm/sna_init_80057118.s")
#pragma INCLUDE_ASM("asm/sna_init_800571B8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_80057474.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shoot_weapon_helper_80057590.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_rungun_begin_helper_800577B4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_rungun_helper_80057844.s")

extern int HomingTarget_2_80032EAC(short *a1, short a2, int *a3, int *a4, int a5, int a6, int a7);

// move to own file when needed / researched
// camera references this is a lot
typedef struct gUnkMaybeCameraStruct_800B77B8_t
{
    int field_0;
    int field_4;
    int field_8;
    short field_C;
    short field_E;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    short field_28_aim_assist; // dont know what this really is
    short field_2A;
    int field_2C;
} gUnkMaybeCameraStruct_800B77B8_t;
STATIC_ASSERT_SIZE(gUnkMaybeCameraStruct_800B77B8_t, 0x30);

gUnkMaybeCameraStruct_800B77B8_t SECTION(".gUnkMaybeCameraStruct_800B77B8") gUnkMaybeCameraStruct_800B77B8;
extern int dword_800ABBA4;

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
    HomingTarget_2_80032EAC(&(pActor->field_9C.objs[8].chanl),    // ?
                            pActor->field_20_ctrl.field_8_vec.vy, // input snake horizontal facing angle
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
    snake_not_moving = dword_800ABBA4 < 0;        // snake move angle
    pActor->field_718[7].vx = 3 * out_x_copy / 2; // maybe aim gun/head up/down??

    if (snake_not_moving && out_y >= 0) // if not moving, set snake turn angle
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy = out_y;
    }

    if (sna_init_sub_8004E358(pActor, 16))
    {
        gUnkMaybeCameraStruct_800B77B8.field_28_aim_assist = out_x;
    }
}

#pragma INCLUDE_ASM("asm/sub_80057A90.s")
#pragma INCLUDE_ASM("asm/sub_80057BF0.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_helper_80057FD4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_stinger_helper_80058378.s")
#pragma INCLUDE_ASM("asm/sub_80058470.s")
#pragma INCLUDE_ASM("asm/sub_80058644.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_helper_80058780.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_throw_800589C8.s")

void sna_init_anim_punch_80058C10(Actor_SnaInit *pActor, int anim_frame)
{
    if (anim_frame == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_punch_helper_800591F4;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_2, 1);
        pActor->field_A38 = 0;
        sna_init_set_flags_8004E2F4(pActor, 48);
    }
}

void sna_init_anim_chokethrow_begin2_80058C80(Actor_SnaInit *pActor, int anim_frame)
{
    int bClear;                   // $s0
    GM_Target *field_8E8_pTarget; // $v1
    int action_flag;              // $a1
    SVECTOR *p;

    if (anim_frame == 0)
    {
        pActor->field_904 = 0;
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        bClear = 0;
        pActor->field_A54 = 0;

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

            DG_SetPos2_8001BC8C(&field_8E8_pTarget->field_8_vec, &pActor->field_20_ctrl.field_8_vec);

            DG_PutVector_8001BE48(&stru_800AB7FC, p, 1);
            DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_vec);
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
        ++pActor->field_904;
        GV_AddVec3_80016D00(&pActor->field_20_ctrl.field_44_vec, &pActor->field_8EC_vec,
                            &pActor->field_20_ctrl.field_44_vec);
    }
    else
    {
        if (pActor->field_A38)
        {
            sna_init_clear_flags_8004E308(pActor, 4);
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

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_rechoke_80058EF4.s")
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

        pActor->field_9C.action_flag = -1;
        pActor->field_9C8_anim_update_fn_3p = sub_8005961C;
        pActor->field_904 = 0;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        action_flag = field_9B4_action_table->field_10->field_6;
        sna_init_8004E22C(pActor, field_9B4_action_table->field_10->field_6, 4);
        pActor->field_8E8_pTarget->field_3E = action_flag;
        }
    }
}
*/

extern void sub_8004FAE8(Actor_SnaInit *pActor);

void sna_init_anim_choke_kill_80058F88(Actor_SnaInit *pActor, int anim_frame)
{
    GM_Target *field_8E8_pTarget; // $s0
    int action_flag;              // $s1

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
        pActor->field_A54 = 0;
    }

    if (pActor->field_9C.field_1A)
    {
        sna_init_sub_8004E41C(pActor, 2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        sna_init_clear_flags_8004E308(pActor, 4);
    }

    if (sna_init_sub_8004E358(pActor, 16))
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

    iVar3 = pActor->field_904 + 1;
    pActor->field_904 = iVar3;

    if ((dword_800ABBA4 < 0 || ((pActor->field_9B0_pad_bits[0] & 0x80) == 0)))
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
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBA4 + 0x800;
        }
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_hold_80059154.s")
#pragma INCLUDE_ASM("asm/sub_800591BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_punch_helper_800591F4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_helper_8005951C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_rechoke_helper_8005961C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_main_logic_800596FC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_8005AD10.s")

void sna_init_kill_8005B52C(Actor_SnaInit *pActor)
{
    GM_Control *pCtrl; // $s2
    DG_OBJS *pObjs;    // $s0
    Actor *pShadow;    // $a0
    Actor *pWeapon;    // $a0
    Actor *pItem;      // $a0

    if ((pActor->field_898_flags & 0x1000) != 0)
    {
        gGameState_800B4D98.field_BE = 1;
    }

    pCtrl = &pActor->field_20_ctrl;
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C);
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

    if (gControl_800AB9F4 == pCtrl)
    {
        gControl_800AB9F4 = 0;
    }

    if (dword_800ABA20 == &pActor->field_9C)
    {
        dword_800ABA20 = 0;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_init_8005B650.s")
