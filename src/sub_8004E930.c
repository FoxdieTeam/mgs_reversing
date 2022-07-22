#include "linker.h"
#include "sna_init.h"
#include "libdg.h"

extern int HZD_SlopeFloorLevel_800298F8(short *param_1,int arg1);
extern long SquareRoot0_80092708(long a);
extern int GV_VecDir2_80016EF8(SVECTOR *vec);

extern int dword_800ABBB8;
int SECTION(".sbss") dword_800ABBB8;

int sub_8004E930(Actor_SnaInit *snake, int arg1)
{
	int int0;
	int int1;
	SVECTOR vec0;
	SVECTOR vec1;

	vec0.vy = 0;
	vec0.vx = 0;
	vec0.vz = (short)arg1;
	DG_PutVector_8001BE48(&vec0,&vec0,1);
	int0 = HZD_SlopeFloorLevel_800298F8(&vec0.vx,dword_800ABBB8);
	int1 = int0 - (snake->field_20_ctrl).field_78;
	vec1.vx = int1;
	vec1.vz = SquareRoot0_80092708(arg1 * arg1 - int1 * int1);
	int0 = -GV_VecDir2_80016EF8(&vec1);

	if (int0 < -0x800)
	{
		int0 += 0x1000;
	}

	return int0;
}

