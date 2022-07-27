#include "menuMan.h"
#include "linker.h"
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "data.h"
#include "dgd.h"

MenuMan SECTION(".gMenuMan_800BD360") gMenuMan_800BD360;
unsigned char SECTION(".gPrimBackingBuffers_800B9360") gPrimBackingBuffers_800B9360[2][8192];

extern const char aItem[]; // sdata
extern const char aMenumanC[];

extern MenuGlue gMenuPrimBuffer_8009E2D0;
extern TInitKillFn gMenuInitFns_8009E290[];
extern int GV_Clock_800AB920;
extern DG_CHNL DG_Chanls_800B1800[3];
extern int MENU_PrimUse_800AB68C;

void menu_rpk_init_8003DD1C(const char *);
void SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);
void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void menuman_act_800386A4(MenuMan *);
void menuman_kill_800387E8(MenuMan *);
void menu_viewer_init_80044A70(MenuMan *);
void MENU_InitRadioTable_80049644(void);
extern void menu_right_unknown_8003DEB0(void);
void MENU_Text_Init_80038B98(void);
void nullsub_8_8008BB98(void);

#pragma INCLUDE_ASM("asm/Menu/menuman_act_800386A4.s")
#pragma INCLUDE_ASM("asm/menuman_kill_800387E8.s")

void menu_init_subsystems_8003884C(MenuMan *pMenuMan)
{
    TInitKillFn *pIter;
    DRAWENV drawEnv;


    pMenuMan->field_2A_state = 0;
    pMenuMan->field_29 = 0;
    pMenuMan->field_28_flags = 0;

    pMenuMan->field_20_otBuf = (struct Menu_Prim_Buffer*)&gMenuPrimBuffer_8009E2D0.mPrimBuf;

    gMenuPrimBuffer_8009E2D0.mPrimPtrs[0] = &gPrimBackingBuffers_800B9360[0][0];
    gMenuPrimBuffer_8009E2D0.mPrimPtrs[1] = &gPrimBackingBuffers_800B9360[1][0];

    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv_800906B0(&pMenuMan->field_4C_drawEnv[0], &drawEnv);

    DG_Init_DrawEnv_80018384(&drawEnv, 320, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv_800906B0(&pMenuMan->field_4C_drawEnv[1], &drawEnv);

    menu_rpk_init_8003DD1C(aItem);

    pIter = &gMenuInitFns_8009E290[0];
    while (*pIter)
    {
        (*pIter)(pMenuMan);
        pIter++;
    }

    menu_viewer_init_80044A70(pMenuMan);
}

void menuman_init_80038954(void)
{
    GV_SetNamedActor_8001514C(&gMenuMan_800BD360.field_0_actor, (TActorFunction)menuman_act_800386A4, (TActorFunction)menuman_kill_800387E8, aMenumanC);
    menu_init_subsystems_8003884C(&gMenuMan_800BD360);
    MENU_InitRadioTable_80049644();
}

#pragma INCLUDE_ASM("asm/sub_800389A8.s")

void MENU_ResetTexture_80038A00(void)
{
    menu_right_unknown_8003DEB0();
}

void MENU_StartDeamon_80038A20(void)
{
    GV_InitActor_800150A8(1, &gMenuMan_800BD360.field_0_actor, 0);
    GV_SetNamedActor_8001514C(&gMenuMan_800BD360.field_0_actor, 0, 0, aMenumanC);
}

void menu_radio_update_helper_80038A6C(void)
{
    gMenuMan_800BD360.field_1D8 = 1;
}

void menu_radio_update_helper2_80038A7C(void)
{
  gMenuMan_800BD360.field_1D8 = 0;
}

#pragma INCLUDE_ASM("asm/MENU_ResetSystem_80038A88.s")

/*
void MENU_ResetSystem_80038A88(void)
{
    MenuGlue* pGlue = &gMenuPrimBuffer_8009E2D0;
    MenuPrimBuffer* pPrimBuf = &pGlue->mPrimBuf;
    if (pPrimBuf->mOtEnd < pPrimBuf->mFreeLocation)
    {
        nullsub_8_8008BB98();
    }

    pPrimBuf->mOtEnd =  pGlue->mPrimPtrs[GV_Clock_800AB920] + 0x2000;
    pPrimBuf->mOt = DG_Chanls_800B1800[2].mOrderingTables[GV_Clock_800AB920];
    MENU_PrimUse_800AB68C = pPrimBuf->mFreeLocation - pGlue->mPrimPtrs[1 - GV_Clock_800AB920];
    pPrimBuf->mFreeLocation = pGlue->mPrimPtrs[GV_Clock_800AB920];
    MENU_Text_Init_80038B98();
}
*/

void MENU_Text_XY_Flags_80038B34(int xpos, int ypos, int flags)
{
	TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;

	pTextConfig->xpos = xpos;
	pTextConfig->ypos = ypos;
	pTextConfig->flags = flags;
}

void MENU_Color_80038B4C(int r, int g, int b)
{
	unsigned int newColour;
	unsigned int unknown;
	TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;

	if ((pTextConfig->flags & TextConfig_Flags_eSemiTransparent_20) != 0)
	{
		newColour = r | g << 8 | b << 0x10;
		unknown = 0x66000000;
	}
	else
	{
		newColour = r | g << 8 | b << 0x10;
		unknown = 0x64000000;
	}

	pTextConfig->colour = newColour | unknown;
}

void MENU_Text_Init_80038B98(void)
{
	TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;
	pTextConfig->colour = 0x64808080;
	pTextConfig->flags = 0;
}

#pragma INCLUDE_ASM("asm/sub_80038BB4.s")
#pragma INCLUDE_ASM("asm/MENU_Text_80038C38.s")
#pragma INCLUDE_ASM("asm/sub_80038D10.s")

MenuGlue* MENU_GetPrimInfo_80038D68(void)
{
  return &gMenuPrimBuffer_8009E2D0;
}

#pragma INCLUDE_ASM("asm/MENU_DrawBar_80038D74.s")
#pragma INCLUDE_ASM("asm/MENU_DrawBar2_80038DE0.s")
