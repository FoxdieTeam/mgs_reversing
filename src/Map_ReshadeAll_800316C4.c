#include "linker.h"
#include "libdg.h"
#include "dgd.h"

DG_OBJS* SECTION(".StageObjs_800B7890") StageObjs_800B7890[32];

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int SECTION(".sbss") N_StageObjs_800ABAA4;

void Map_Reshade_80031660(DG_OBJS *);

// TODO: OG name is GM_ReshadeMapAll
void Map_ReshadeAll_800316C4() // from memleak
{
	DG_OBJS **obj;
	int		i ;

	obj = StageObjs_800B7890;
	for ( i = N_StageObjs_800ABAA4 ; i > 0 ; -- i ) {
		Map_Reshade_80031660( *obj ); // GM_ReshadeObjs
		obj ++ ;
	}
}
