#include "socom.h"

extern int dword_800AB824;
int SECTION(".sdata") dword_800AB824;

void socom_act_helper_800653B8(Actor_Socom *socom)
{
	int local_var = socom->field_100;
	
	if (local_var == 0) {
		socom->field_10C_pPrim->n_prims = 1;
		(socom->field_110).vy = (short)dword_800AB824;
	}
	else
	{
		socom->field_10C_pPrim->n_prims = 2;
		(socom->field_118).vy = -0xd7 - (short)local_var;
		(socom->field_110).vy = (short)dword_800AB824;
	}
}