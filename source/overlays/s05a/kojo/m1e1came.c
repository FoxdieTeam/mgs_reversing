#include "game/game.h"

extern GM_CameraSystemWork GM_Camera;
extern int s05a_dword_800C38CC;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1134.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1448.s")

void s05a_800E1A68(void)
{
    GM_Camera.flag &= ~2;
    GM_SetCameraCallbackFunc(1, NULL);
    s05a_dword_800C38CC = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1AA8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1C14.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1D7C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E209C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E2328.s")
