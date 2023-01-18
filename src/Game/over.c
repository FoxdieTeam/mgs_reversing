#include "gamestate.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "linker.h"
#include "strctrl.h"

#pragma INCLUDE_ASM( "asm/Game/over_act_helper_80036A10.s" ) // 304 bytes

unsigned int over_act_helper_80036B40( int param_1, int param_2 )
{
	int          iVar1;
	unsigned int uVar2;
	int          iVar3;

	iVar1 = 0xff;
	if ( param_2 < 8 )
	{
		uVar2 = 0x80;
	}
	else
	{
		param_2 -= 8;
		iVar1 = param_2 - 8;
		if ( param_2 > 8 )
		{
			param_2 = 8;
		}
		iVar3 = ( 0xff - param_1 ) * param_2;
		uVar2 = 0x80 - ( param_2 * 0x10 );
		if ( iVar3 < 0 )
		{
			iVar3 = iVar3 + 7;
		}
		iVar1 = 0xff - ( iVar3 >> 3 );
	}
	return uVar2 | iVar1 << 8 | iVar1 << 0x10;
}

#pragma INCLUDE_ASM( "asm/Game/over_act_helper_80036BA4.s" ) // 1412 bytes
#pragma INCLUDE_ASM( "asm/Game/over_act_helper_80037128.s" ) // 244 bytes
#pragma INCLUDE_ASM( "asm/Game/over_act_8003721C.s" )        // 760 bytes

extern const char aInit_0[];
extern const char aTitle[];
extern short      gGameState_800B4D98[ 0x60 ];

extern int        GM_GameOverTimer_800AB3D4;
extern int        GM_LoadRequest_800AB3D0;
extern int        GV_PauseLevel_800AB928;

extern void       DG_8001844C( void );
extern void       GM_ContinueStart_8002B62C( void );

int               GM_SetArea_8002A7D8( char *, int );

typedef struct   Over
{
	struct Actor f00_base;
	short        f20;
	short        f22;
	short        f24;
	short        f26;
	short        f28;
} Over;

void over_kill_80037514( Over *actor )
{
	char *stage_name;

	GV_PauseLevel_800AB928 &= ~1;
	DG_8001844C();
	GM_StreamPlayStop_80037D64();
	GM_GameOverTimer_800AB3D4 = 0;
	if ( actor->f24 == 0 )
	{
		GM_ContinueStart_8002B62C();
		return;
	}
	if ( ( gGameState_800B4D98[ GM_Flags ] & 0x20 ) || ( gGameState_800B4D98[ GM_Difficulty ] == -1 ) )
	{
		GV_ResidentHeapReset_800163B0();
		GV_InitCacheSystem_80015458();
		DG_ClearResidentTexture_8001DB10();
		stage_name = (char *)aInit_0;
		gGameState_800B4D98[ GM_Flags ] &= 0xFFDF;
	}
	else
	{
		stage_name = (char *)aTitle;
	}
	GM_SetArea_8002A7D8( (char*)GV_StrCode_80016CCC( stage_name ), (int)stage_name );
	GM_LoadRequest_800AB3D0 = 0x81;
}

#pragma INCLUDE_ASM( "asm/Game/over_loader_80037600.s" ) // 248 bytes
#pragma INCLUDE_ASM( "asm/Game/over_init_800376F8.s" ) // 244 bytes
