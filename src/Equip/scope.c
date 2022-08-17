#include "scope.h"
#include "menu/menuman.h"

extern const char aZoomLevelD[];
extern const char aD_44[];  // = "%d"

extern int GM_PlayerStatus_800ABA50;
extern GM_Camera GM_Camera_800B77E8;

#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_helper_80062320.s") // 92 bytes
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
    if ( (GM_PlayerStatus_800ABA50 & 0x4000000) == 0 )
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
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_80063238.s")     // 60 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_80063274.s")     // 96 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_800632D4.s")     // 148 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_80063368.s")     // 108 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_800633D4.s")            // 308 bytes
#pragma INCLUDE_ASM("asm/Equip/NewScope_80063508.s")                // 180 bytes
