#include "rifle.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98   gGameState_800B4D98;
extern short                dword_800B7800[];

extern void                 GM_FreeObject_80034BF8(OBJECT *object);
extern int                  sd_set_cli_800887EC(int sdCode, int unused);
extern void                 GV_DestroyOtherActor_800151D8(struct Actor *pActorToKill);

void rifle_kill_80068118(Actor_Rifle *rifle)
{
	GM_FreeObject_80034BF8(&rifle->f20_obj);
	if (gGameState_800B4D98.field_1C_equipped_weapon != 9)
	{
		dword_800B7800[4] = 0x140;
	}
	sd_set_cli_800887EC(0x1ffff21, 0);
	if ((Actor*)rifle->f5c)
	{
		GV_DestroyOtherActor_800151D8((Actor*)rifle->f5c);
	}
}

