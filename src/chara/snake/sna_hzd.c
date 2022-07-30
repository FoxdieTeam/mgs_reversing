#include "linker.h"
#include "hzd.h"

int sub_8005C05C(HZD_ZON *a1, HZD_ZON *a2, SVECTOR *a3);
extern void sub_8005C498(void);

int sub_8005BF84(int a1, int a2, int a3, int a4)
{
	int iVar1;
	int iVar2;

	if (a3 < a2)
	{
		iVar1 = a3;
		a3 = a2;
		a2 = iVar1;
		iVar2 = 2 * a4;
	}
	else
	{
		iVar2 = 2 * a4;
		if (a2 == a3)
		{
			return 0;
		}
	}

	return *((unsigned char *) (((((a2 * ((iVar2 - a2) - 3)) / 2) + a3) + a1) - 1));
}

#pragma INCLUDE_ASM("asm/sub_8005BFDC.s")
#pragma INCLUDE_ASM("asm/sub_8005C05C.s")
#pragma INCLUDE_ASM("asm/sub_8005C140.s")


int sub_8005C1E4(HZD_MAP *pHzd, HZD_ZON *pZon, SVECTOR *pVec)
{
    unsigned char *nears; // $s2
    int i; // $s1
    int cur_near; // $s0

    nears = pZon->nears;
    for ( i = 6; i > 0; --i )
    {
        cur_near = *nears++;
        if ( cur_near == 255 )
        {
            break;
        }
        if ( sub_8005C05C(pZon, &pHzd->f00_header->navmeshes[cur_near], pVec) )
        {
            return cur_near;
        }
    }
    return -1;
}

#pragma INCLUDE_ASM("asm/sub_8005C298.s")
#pragma INCLUDE_ASM("asm/sub_8005C354.s")
#pragma INCLUDE_ASM("asm/HZD_ReachTo_helper_8005C404.s")
#pragma INCLUDE_ASM("asm/sub_8005C458.s")
#pragma INCLUDE_ASM("asm/sub_8005C498.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_helper_helper_helper_8005C4E4.s")
#pragma INCLUDE_ASM("asm/sub_8005C5D4.s")
#pragma INCLUDE_ASM("asm/sub_8005C6C4.s")
#pragma INCLUDE_ASM("asm/HZD_ReachTo_8005C89C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_helper_helper_8005C974.s")
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CB48.s")
#pragma INCLUDE_ASM("asm/sub_8005CD1C.s")
#pragma INCLUDE_ASM("asm/sub_8005CE5C.s")
#pragma INCLUDE_ASM("asm/sub_8005CFAC.s")
#pragma INCLUDE_ASM("asm/sub_8005D134.s")

void sub_8005D168(void)
{
    sub_8005C498();
}

#pragma INCLUDE_ASM("asm/sub_8005D188.s")
#pragma INCLUDE_ASM("asm/sub_8005D288.s")
