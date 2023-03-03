#include "linker.h"
#include "game.h"

extern char  dword_800AB400[ 9 ];
extern int   GV_PauseLevel_800AB928;
extern void  menu_AreaNameWrite_80049534( char *areaName );
extern char *GM_StageName_800AB918;
char         SECTION( ".sbss" ) * GM_StageName_800AB918;

void         GM_Act_helper3_helper_8002AB40( void )
{
	char *areaName;

	areaName = dword_800AB400;
	GV_PauseLevel_800AB928 |= 2;
	GM_Sound_80032C48( 0x1ffff01, 0 );
	if ( GM_StageName_800AB918 )
	{
		areaName = GM_StageName_800AB918;
	}
	menu_AreaNameWrite_80049534( areaName );
}