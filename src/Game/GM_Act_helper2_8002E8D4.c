#include "linker.h"

extern char GM_NoiseSound_800B76E0[ 4 ][ 3 ];
char        SECTION( ".sbss" ) GM_NoiseSound_800B76E0[ 4 ][ 3 ];

extern int  dword_800ABA70;
int         SECTION( ".sbss" ) dword_800ABA70;

extern int  dword_800ABA78[ 2 ];
int         SECTION( ".sbss" ) dword_800ABA78[ 2 ];

void        GM_Act_helper2_8002E8D4()
{
	int  i;
	char val;

	GM_NoiseSound_800B76E0[ 0 ][ 0 ] = 55;
	dword_800ABA70 = 0;
	dword_800ABA78[ 0 ] = 0;
	dword_800ABA78[ 1 ] = 0;
	GM_NoiseSound_800B76E0[ 0 ][ 1 ] = 39;

	val = 40;
	for ( i = 3; i >= 0; i-- )
	{
		GM_NoiseSound_800B76E0[ i ][ 2 ] = val;
	}
}
