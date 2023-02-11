#include "scope.h"
#include "Menu/menuman.h"
#include "Game/camera.h"

extern const char aZoomLevelD[];
extern const char aD_44[];  // = "%d"

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GM_Camera GM_Camera_800B77E8;

void scope_act_helper_helper_80062320(int *a1, int *a2)
{
    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) == 0)
    {
        addPrim(a1, a2);
    }
}

#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_helper_8006237C.s") // 320 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_800624BC.s")        // 56 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_helper_800624F4.s") // 152 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_8006258C.s")        // 324 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_800626D0.s")        // 712 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062998.s")        // 580 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062BDC.s")        // 160 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062C7C.s")        // 300 bytes


void scope_draw_text_80062DA8(Actor_scope *pActor)
{
    if ( (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) == 0 )
    {
        menu_Text_XY_Flags_80038B34(20, 34, 0);
        menu_Color_80038B4C(127, 166, 97);
        menu_Text_80038C38(aZoomLevelD, 100 * (GM_Camera_800B77E8.field_20 / 320));
        menu_Color_80038B4C(101, 133, 77);
        menu_Text_XY_Flags_80038B34(32, 101, 1);
        menu_Text_80038C38(aD_44, -pActor->field_6C);
        menu_Text_Init_80038B98();
    }
}

#pragma INCLUDE_ASM("asm/Equip/scope_act_80062E8C.s")               // 752 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_kill_8006317C.s")              // 188 bytes

void scope_loader_helper_80063238(LINE_F2 *lines)
{
	int i;

	for (i = 0; i < 16; i++)
	{
		*(int *)&lines->r0 = 0x41412e;
		setLineF2(lines);
		setSemiTrans(lines, 1);
		lines++;
	}
}

void scope_loader_helper_80063274(LINE_F4 *lines)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		*(int *)&lines->r0 = 0x68b187;
		setLineF4(lines);
		lines++;

		*(int *)&lines->r0 = 0x68b187;
		setLineF2(lines);
		lines++;
	}
}

#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_800632D4.s")     // 148 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_80063368.s")     // 108 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_800633D4.s")            // 308 bytes

extern const char aScopeC[];

extern short scope_created_8009F2C4;

void scope_act_80062E8C(Actor_scope *pActor);
void scope_kill_8006317C(Actor_scope *pActor);
int scope_loader_800633D4(Actor_scope *pActor, GM_Control *pCtrl, OBJECT *pObj);

Actor_scope* NewScope_80063508(GM_Control *a1, OBJECT *a2)
{
    Actor_scope *pActor; // $s0

    if ( scope_created_8009F2C4 )
    {
        return 0;
    }

    pActor = (Actor_scope *)GV_NewActor_800150E4(7, sizeof(Actor_scope));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_scope, (TActorFunction)scope_act_80062E8C, (TActorFunction)scope_kill_8006317C, aScopeC);
        if ( scope_loader_800633D4(pActor, a1, a2) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0_scope);
            return 0;
        }
        scope_created_8009F2C4 = 1;
    }
    return pActor;
}
