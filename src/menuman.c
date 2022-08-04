#include "menuMan.h"
#include "linker.h"
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "data.h"
#include "dgd.h"

Actor_MenuMan SECTION(".gMenuMan_800BD360") gMenuMan_800BD360;
unsigned char SECTION(".gPrimBackingBuffers_800B9360") gPrimBackingBuffers_800B9360[2][8192];

extern const char aItem[]; // sdata
extern const char aMenumanC[];
extern const char aMenuPrimOver[];

extern MenuGlue gMenuPrimBuffer_8009E2D0;
extern TInitKillFn gMenuInitFns_8009E290[];
extern int GV_Clock_800AB920;
extern DG_CHNL DG_Chanls_800B1800[3];
extern int MENU_PrimUse_800AB68C;
extern TInitKillFn gMenuKillFns_8009E2B4[];

void menu_rpk_init_8003DD1C(const char *);
void SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);
void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void menuman_act_800386A4(Actor_MenuMan *);
void menuman_kill_800387E8(Actor_MenuMan *);
void menu_viewer_init_80044A70(Actor_MenuMan *);
void MENU_InitRadioTable_80049644(void);
void menu_right_unknown_8003DEB0(void);
void MENU_Text_Init_80038B98(void);
void menu_viewer_kill_80044A90(Actor_MenuMan *pActor);
int mts_nullsub_8_8008BB98(int, const char *, ...);

extern int GV_PauseLevel_800AB928;
extern int GM_LoadComplete_800ABA38;
extern int GM_GameStatus_800AB3CC;
extern int GM_LoadRequest_800AB3D0;

extern short* GM_CurrentPadData_800AB91C; // sbss

void menu_jimaku_act_80048FD4(Actor_MenuMan *pActor, unsigned int *pOt);

#pragma INCLUDE_ASM("asm/Menu/menuman_act_800386A4.s") // 324 bytes


void menuman_kill_800387E8(Actor_MenuMan *pActor)
{
    TInitKillFn* pIter = gMenuKillFns_8009E2B4;
    while ( *pIter )
    {
        (*pIter)(pActor);
        pIter++;
    }
    
    menu_viewer_kill_80044A90(pActor);
}

void menu_init_subsystems_8003884C(Actor_MenuMan *pMenuMan)
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

#pragma INCLUDE_ASM("asm/sub_800389A8.s") // 88 bytes

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


void MENU_ResetSystem_80038A88()
{
    DG_CHNL* p;
    unsigned char *pFreeLoc = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;    
    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd  < pFreeLoc)
    {
        mts_nullsub_8_8008BB98(-1, aMenuPrimOver);
    }
  
    MENU_PrimUse_800AB68C = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation - gMenuPrimBuffer_8009E2D0.mPrimPtrs[1 - GV_Clock_800AB920];

    gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation = gMenuPrimBuffer_8009E2D0.mPrimPtrs[GV_Clock_800AB920];
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation + 0x2000;
 
    p = &DG_Chanls_800B1800[1];
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOt = (p + 1)->mOrderingTables[GV_Clock_800AB920];
    MENU_Text_Init_80038B98();
}

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

#pragma INCLUDE_ASM("asm/sub_80038BB4.s") // 132 bytes

int sprintf_8008E878(char *buffer, const char *fmt, ...);
int strlen_8008E7B8(char *s);
void _menu_number_draw_string_80042BF4(MenuGlue *param_1, int *param_2, char *param_3);
void _menu_number_draw_string2_80043220(MenuGlue *param_1, int *param_2, char *param_3);
void sub_80038BB4();

int MENU_Text_80038C38(char *fmt, const char *str, int param_3, int param_4, int param_5)
{
    int string_length;
    unsigned int free_space;
    char string_buffer[64];

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {
        sprintf_8008E878(string_buffer, fmt, str, param_3, param_4, param_5);
        free_space = gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd - gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
        string_length = strlen_8008E7B8(string_buffer);
        if (string_length * 0x14 + 0x28U <= free_space)
        {
            if (gMenuTextConfig_8009E2E4.flags & 0x10U)
            {
                _menu_number_draw_string2_80043220(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4.xpos, string_buffer);
            }
            else
            {
                _menu_number_draw_string_80042BF4(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4.xpos,
                                                   string_buffer);
            }
            sub_80038BB4();
        }
    }
    return gMenuTextConfig_8009E2E4.xpos;
}

#pragma INCLUDE_ASM("asm/sub_80038D10.s") // 88 bytes

MenuGlue* MENU_GetPrimInfo_80038D68(void)
{
  return &gMenuPrimBuffer_8009E2D0;
}

#pragma INCLUDE_ASM("asm/MENU_DrawBar_80038D74.s") // 108 bytes
#pragma INCLUDE_ASM("asm/MENU_DrawBar2_80038DE0.s") // 72 bytes
