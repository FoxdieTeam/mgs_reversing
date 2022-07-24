#include "sna_init.h"
#include "Script_tbl_map_8002BB44.h"
#include "linker.h"
#include "libdg.h"

extern Sna_E1 e1_800AB7C4;
Sna_E1 SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int SECTION(".sbss") dword_800ABBA8;

extern int dword_800ABBB4;
int SECTION(".sbss") dword_800ABBB4;

extern int    sub_800296C4(int param_1, short *param_2, unsigned int param_3);
extern void   sub_800298DC(int *param_1);

extern int HZD_SlopeFloorLevel_800298F8(short *param_1,int arg1);
extern long SquareRoot0_80092708(long a);
extern int GV_VecDir2_80016EF8(SVECTOR *vec);

extern int dword_800ABBB8;
int SECTION(".sbss") dword_800ABBB8;

extern int GM_AlertMode_800ABA00;

extern GameState_800B4D98   gGameState_800B4D98;
extern int                  GM_GameOverTimer_800AB3D4;
extern int                  GM_GameStatus_800AB3CC;

extern int  GM_PlayerStatus_800ABA50;

extern void GM_ConfigObjectAction_80034CD4( OBJECT *obj, int action_flag, int motion, int interp );


void sna_init_fn_800535B8(Actor_SnaInit *pActor);
void sna_init_80053360(Actor_SnaInit *pActor);
void sna_init_80050440(Actor_SnaInit *pActor);

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_start_anim_8004E1F4.s")

void sna_init_8004E22C(int param_1, int param_2, int param_3)
{
    if (*(short *)(param_1 + 0xaa) != param_2)
    {
        GM_ConfigObjectAction_80034CD4((OBJECT *)(param_1 + 0x9c), param_2, 0, param_3);
    }
    return;
}
#pragma INCLUDE_ASM("asm/sub_8004E260.s")

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

void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag)
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
		GM_SetPlayerStatusFlag_8004E2B4(0x20008000);
		sna_init_set_flags_8004E2F4(snake, 0x400000);
		GM_GameStatus_800AB3CC |= 0x10080000;

        if (GM_GameOverTimer_800AB3D4 != -2)
    	{
    		sna_init_set_flags_8004E2F4(snake,0x30);
    	}
	}
}

void sna_init_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags)
{
	GM_Target *target = snake->field_8E8_pTarget;
	
	if (target != 0) {
		target->field_6_flags &= ~flags;
		snake->field_8E8_pTarget = 0;
		snake->field_A54 = 0;
		snake->field_89C_pTarget->field_10_size.vx = 300;
	}
}

#pragma INCLUDE_ASM("asm/sub_8004E458.s")

int sub_8004E4C0(int unused, int param_2)
{
  int iVar1;
  
  if (-1 < dword_800ABBA8) {
    if ((*(char *)dword_800ABBB4 & 0x40) != 0) {
      return param_2;
    }
    iVar1 = (param_2 - dword_800ABBA8) & 0xfff;
    if (iVar1 < 0x400) {
      param_2 = dword_800ABBA8 + 0x400;
    }
    if (iVar1 > 0xc00) {
      param_2 = dword_800ABBA8 - 0x400;
    }
  }
  return param_2;
}

#pragma INCLUDE_ASM("asm/sub_8004E51C.s")

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
	DG_PutVector_8001BE48(&vec0,&vec0,1);

	int1 = HZD_SlopeFloorLevel_800298F8(&vec0.vx,dword_800ABBB8);
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

    uVar1 = GV_DiffDirS_8001704C(param_2, (int) *(short *)(param_1 + 0x2a));
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
#pragma INCLUDE_ASM("asm/sub_8004EAA8.s")
#pragma INCLUDE_ASM("asm/sub_8004EB14.s")
#pragma INCLUDE_ASM("asm/sub_8004EB74.s")
#pragma INCLUDE_ASM("asm/sub_8004EC00.s")

extern short dword_800B7800[];

extern void  sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flag);
extern void  sd_set_cli_800887EC(int code, int unused);
extern void  sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sub_8004EC8C(Actor_SnaInit *snake)
{
    ushort sVar0;
    
    sna_init_set_flags_8004E2F4(snake, 0x800);
    snake->field_A28 = 0x1cc;
    dword_800B7800[5] = 1;
    sVar0 = *(ushort*)&e1_800AB7C4.field_4;
    snake->field_A20 = -6;
    snake->field_9D4 = 0x140;
    snake->field_9D8 = sVar0;
    snake->field_9DC = sVar0;
    sd_set_cli_800887EC(0x1ffff20, 0);
    sna_init_sub_8004E330(snake,0x10);
    GM_ClearPlayerStatusFlag_8004E2D4(1);
}
#pragma INCLUDE_ASM("asm/sub_8004ED08.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper3_8004ED6C.s")
#pragma INCLUDE_ASM("asm/sub_8004EE28.s")
#pragma INCLUDE_ASM("asm/sub_8004EEB0.s")
#pragma INCLUDE_ASM("asm/sub_8004EF14.s")
#pragma INCLUDE_ASM("asm/sub_8004EFE4.s")

extern int  sub_8004EFE4(int param_1, int param_2);

void sub_8004F034(int param_1, unsigned int param_2)
{
    int iVar1;

    if (param_2 != *(unsigned int *)(param_1 + 0x18c))
    {
        *(unsigned int *)(param_1 + 0x1a4) = ~param_2;
        *(unsigned int *)(param_1 + 0x18c) = param_2;
        if ((param_2 == 0xffff) && (iVar1 = sub_8004EFE4(param_1, 2),  -1 < iVar1))
        {
            *(int *)(param_1 + 0x1c0) = 4;
            *(short *)(param_1 + 0x1b0) = 2;
        }
    }
    return;
}
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper4_8004F090.s")
#pragma INCLUDE_ASM("asm/sub_8004F14C.s")
#pragma INCLUDE_ASM("asm/sub_8004F204.s")

void sna_init_8004F2A0(Actor_SnaInit *pActor, char a2)
{
    GM_SetPlayerStatusFlag_8004E2B4(0x800000);
    pActor->field_A24 = a2;
    pActor->field_89C_pTarget->field_0_flags &= ~0x96u;
}

extern void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags);


void sub_8004F2EC(Actor_SnaInit *snake)
{
  GM_ClearPlayerStatusFlag_8004E2D4(0x800000);
  sna_init_clear_flags_8004E308(snake, 1);
  snake->field_89C_pTarget->field_0_flags |= 0x9e;
  return;
}

#pragma INCLUDE_ASM("asm/sub_8004F338.s")
#pragma INCLUDE_ASM("asm/sub_8004F454.s")
#pragma INCLUDE_ASM("asm/sub_8004F544.s")
#pragma INCLUDE_ASM("asm/sub_8004F628.s")


#pragma INCLUDE_ASM("asm/OPERATOR_8004F6E8.s")
#pragma INCLUDE_ASM("asm/sub_8004F8E4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper4_8004FA3C.s")

extern void sna_init_clear_flags_8004E344(Actor_SnaInit* param_1, unsigned int param_2);

void sub_8004FA74(Actor_SnaInit* param_1)
{
    sna_init_clear_flags_8004E344(param_1, 0x20);
    GM_ClearPlayerStatusFlag_8004E2D4(0x8408);
}

extern void sub_80051FD0(Actor_SnaInit *snake);
extern void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = *snake->field_9B0_pad_bits;
    sub_80051FD0(snake);
    if (action & 0x4000)
    {
        sna_init_sub_8004E330(snake, 1);
    }
}

#pragma INCLUDE_ASM("asm/sub_8004FAE8.s")
#pragma INCLUDE_ASM("asm/sub_8004FB38.s")
#pragma INCLUDE_ASM("asm/sub_8004FB4C.s")
#pragma INCLUDE_ASM("asm/sub_8004FB90.s")
#pragma INCLUDE_ASM("asm/sub_8004FBA0.s")
#pragma INCLUDE_ASM("asm/Game/GM_ClearBulName_8004FBE4.s")
#pragma INCLUDE_ASM("asm/Game/GM_CheckShukanReverse_8004FBF8.s")
#pragma INCLUDE_ASM("asm/Game/GM_CheckShukanReverseAnalog_8004FC70.s")
#pragma INCLUDE_ASM("asm/sub_8004FCB8.s")
#pragma INCLUDE_ASM("asm/sub_8004FDE8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper5_8004FF88.s")
#pragma INCLUDE_ASM("asm/sub_8005009C.s")
#pragma INCLUDE_ASM("asm/sub_800501F8.s")
#pragma INCLUDE_ASM("asm/sub_8005027C.s")
#pragma INCLUDE_ASM("asm/sub_80050398.s")
#pragma INCLUDE_ASM("asm/sna_init_80050440.s")
#pragma INCLUDE_ASM("asm/sub_80050568.s")
#pragma INCLUDE_ASM("asm/sub_80050668.s")
#pragma INCLUDE_ASM("asm/sub_800507D8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_80050878.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_80050A64.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk2_80051170.s")
#pragma INCLUDE_ASM("asm/sna_init_weapon_switching_800511BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_800515BC.s")
#pragma INCLUDE_ASM("asm/sub_80051A10.s")
#pragma INCLUDE_ASM("asm/sub_80051BA4.s")
#pragma INCLUDE_ASM("asm/sub_80051DA0.s")
#pragma INCLUDE_ASM("asm/sub_80051FD0.s")

void sna_init_fn_80052120(Actor_SnaInit *pActor, int a2);
#pragma INCLUDE_ASM("asm/sna_init_fn_80052120.s")


#pragma INCLUDE_ASM("asm/sub_8005230C.s")
#pragma INCLUDE_ASM("asm/sub_80052468.s")
#pragma INCLUDE_ASM("asm/sub_80052540.s")
#pragma INCLUDE_ASM("asm/sub_800525F8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_helper_800526BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_idle_8005275C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_crouch_800527DC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_idle_800528BC.s")

void sna_init_anim_run_8005292C(Actor_SnaInit *pActor, int a2)
{
    int action_flag; // $a1

    if ( !a2 )
    {
        pActor->field_9C8 = sna_init_80053360;
        pActor->field_9CC = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(16);
        if ( GM_AlertMode_800ABA00 >= 3 )
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

void sna_init_anim_prone_move_800529C0(Actor_SnaInit *pActor, int a2)
{
    int action_flag; // $a1

    if ( !a2 )
    {
        pActor->field_A28 = 450;
        GM_SetPlayerStatusFlag_8004E2B4(0x10);
        pActor->field_9C8 = sna_init_fn_800535B8;
        pActor->field_9CC = sna_init_fn_80052120;
        if ( pActor->field_A54 )
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
#pragma INCLUDE_ASM("asm/sub_80052E58.s")
#pragma INCLUDE_ASM("asm/sub_80053014.s")
#pragma INCLUDE_ASM("asm/sub_800531F4.s")
#pragma INCLUDE_ASM("asm/sna_init_80053360.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_800535B8.s")
#pragma INCLUDE_ASM("asm/sub_800537D4.s")
#pragma INCLUDE_ASM("asm/sub_800538CC.s")
#pragma INCLUDE_ASM("asm/sub_80053A54.s")

void nullsub_18_80053B80(void)
{

}



#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_run_begin_80053B88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_begin_80053BE8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_standup_80053D74.s")
#pragma INCLUDE_ASM("asm/sub_80053E9C.s")
#pragma INCLUDE_ASM("asm/sub_80053FAC.s")
#pragma INCLUDE_ASM("asm/sub_800540D0.s")
#pragma INCLUDE_ASM("asm/sub_800541A8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_chokethrow_begin1_80054210.s")
#pragma INCLUDE_ASM("asm/sub_8005425C.s")
#pragma INCLUDE_ASM("asm/sub_80054318.s")
#pragma INCLUDE_ASM("asm/sub_800543A8.s")
#pragma INCLUDE_ASM("asm/sub_80054424.s")

extern void sub_80056928(void);
extern void sub_80052468(void);

void sub_80054488(int param_1, int param_2)
{
    if (param_2 == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(0x10);
        *(void **)(param_1 + 0x9c8) = (void*)&sub_80056928;
        *(void **)(param_1 + 0x9cc) = (void*)&sub_80052468;
    }
    *(short *)(param_1 + 0xa62) = *(short *)(param_1 + 0x98) + 0xfa;
    sna_init_80050440(param_1);
    return;
}



#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shot_flinch_800544E0.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper7_80054648.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper8_80054710.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_idle_80054930.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_getup_80054A10.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_shot_80054B50.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper10_80054C08.s")
#pragma INCLUDE_ASM("asm/sub_80054D68.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_80054EFC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_scope_80055334.s")


extern void sna_init_anim_scope_80055334(int param_1, int param_2);

void sna_init_anim_jpegcam_800553CC(int param_1, int param_2)
{
    sna_init_anim_scope_80055334(param_1, param_2);
    return;
}




#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_idle_800553EC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_run_8005544C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_stop_800554B4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_dying_80055524.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_800559D8.s")

