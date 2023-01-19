#include "over.h"

extern const char aInit_0[];
extern const char aTitle[];
extern short      gGameState_800B4D98[ 0x60 ];

extern int        GM_GameOverTimer_800AB3D4;
extern int        GM_LoadRequest_800AB3D0;
extern int        GV_PauseLevel_800AB928;

//------------------------------------------------------------------------------

int *over_act_helper_80036A10( int *param_1, short param_2, short param_3, int texture_id, int param_5, int *param_6 )
{
	DG_TEX *texture;
	int    *tmp;
	int     new_var;

	texture = DG_GetTexture_8001D830( texture_id );
	*(short *)( param_1 + 2 ) = param_2;
	*(short *)( (int)param_1 + 10 ) = param_3;
	*(char *)( param_1 + 3 ) = texture->field_8_offx;
	*(char *)( (int)param_1 + 0xd ) = texture->field_9_offy;
	*(ushort *)( param_1 + 4 ) = texture->field_A_width + 1;
	*(ushort *)( (int)param_1 + 0x12 ) = texture->field_B_height + 1;
	param_2 = *(short *)( (int)param_1 + 0xe ) = texture->field_6_clut;
	*(char *)( ( (int)param_1 ) + 3 ) = 4;
	param_1[ 1 ] = param_5;
	*(char *)( ( (int)param_1 ) + 7 ) = 100;
	*param_1 = ( *param_1 & 0xff000000 ) | ( *param_6 & 0xffffff );
	*param_6 = ( *param_6 & 0xff000000 ) | ( (int)param_1 & 0xffffff );
	tmp = param_1 + 0x5;
	*(char *)( (int)tmp + 3 ) = 1;
	*(int *)( (int)tmp + 4 ) = ( (short)texture->field_4_tPage & 0x9ff ) | 0xe1000400;
	do
	{
	} while ( 0 );
	new_var = (int)( param_1 + 5 ) & 0xffffff;
	param_1[ 5 ] = ( param_1[ 5 ] & 0xff000000 ) | ( *param_6 & 0xffffff );
	*param_6 = ( *param_6 & 0xff000000 ) | new_var;
	return param_1 + 7;
}

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
	GM_SetArea_8002A7D8( GV_StrCode_80016CCC( stage_name ), stage_name );
	GM_LoadRequest_800AB3D0 = 0x81;
}

#pragma INCLUDE_ASM( "asm/Game/over_loader_80037600.s" ) // 248 bytes
#pragma INCLUDE_ASM( "asm/Game/over_init_800376F8.s" )   // 244 bytes
