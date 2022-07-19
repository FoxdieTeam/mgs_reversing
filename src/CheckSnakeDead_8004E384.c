#include "Script_tbl_map_8002BB44.h"
#include "sna_init.h"

extern GameState_800B4D98   gGameState_800B4D98;
extern int                  GM_GameOverTimer_800AB3D4;
extern int                  GM_GameStatus_800AB3CC;

extern void                 GM_SetPlayerStatusFlag_8004E2B4(unsigned int flag);
extern void                 SetSnakeFlag_8004E2F4(Actor_SnaInit *snake, unsigned int flag);

void CheckSnakeDead_8004E384(Actor_SnaInit *snake)
{
	if ((gGameState_800B4D98.field_16_snake_current_health == 0) || (GM_GameOverTimer_800AB3D4 != 0))
	{
		(snake->field_20_ctrl).field_55_flags = (snake->field_20_ctrl).field_55_flags | 2;
		GM_SetPlayerStatusFlag_8004E2B4(0x20008000);
		SetSnakeFlag_8004E2F4(snake,0x400000);
		GM_GameStatus_800AB3CC |= 0x10080000;

        if (GM_GameOverTimer_800AB3D4 != -2)
    	{
    		SetSnakeFlag_8004E2F4(snake,0x30);
    	}
	}
}