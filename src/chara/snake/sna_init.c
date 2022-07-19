#include "sna_init.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98   gGameState_800B4D98;
extern int                  GM_GameOverTimer_800AB3D4;
extern int                  GM_GameStatus_800AB3CC;

extern void                 GM_SetPlayerStatusFlag_8004E2B4(unsigned int flag);

void sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flags)
{
	snake->field_898_flags |= flags;
}

void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags)
{
  snake->field_898_flags &= ~flags;
}

int sna_init_check_flags_8004E31C(Actor_SnaInit *snake, unsigned int flags)
{
  return (snake->field_898_flags & flags) != 0;
}

void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag)
{
	snake->field_89C_pTarget = (GM_Target *)((unsigned int)snake->field_89C_pTarget | flag);
}

void sna_init_clear_flags_8004E344(Actor_SnaInit *snake, unsigned int flags)
{
  snake->field_89C_pTarget = (GM_Target *)((unsigned int)snake->field_89C_pTarget & ~flags);
}

unsigned int sna_init_sub_8004E358(Actor_SnaInit *snake, unsigned int param_2)
{
	unsigned int result = 0;

	if (gGameState_800B4D98.field_BE != 0)
	{
		result = (((unsigned int)snake->field_89C_pTarget & param_2) != result);
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

void sub_8004E41C(int param_1, unsigned short param_2)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x8e8);
    if (iVar1 != 0)
    {
        *(unsigned short *)(iVar1 + 6) = *(unsigned short *)(iVar1 + 6) & ~param_2;
        *(int *)(param_1 + 0x8e8) = 0;
        *(short *)(param_1 + 0xa54) = 0;
        *(short *)(*(int *)(param_1 + 0x89c) + 0x10) = 300;
    }
    return;
}

/*
void sna_init_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags)
{
	int iVar1;

	iVar1 = *(int *)&snake->field_8E8;
	
	if (iVar1 != 0) {
		*(unsigned short *)(iVar1 + 6) = *(unsigned short *)(iVar1 + 6) & ~flags;
		snake->field_8E8_pTarget = 0;
		snake->field_A54 = 0;
		snake->field_89C_pTarget->field_10 = 300;
	}
}
*/