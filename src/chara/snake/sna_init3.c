#include "linker.h"
#include "sna_init.h"
#include "libdg.h"

#pragma INCLUDE_ASM("asm/sub_8004E458.s")

extern Sna_E1 e1_800AB7C4;
Sna_E1 SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int SECTION(".sbss") dword_800ABBA8;

extern int dword_800ABBB4;
int SECTION(".sbss") dword_800ABBB4;

int sub_8004E4C0(int unused, int param_2)
{
  int iVar1;
  
  if (-1 < dword_800ABBA8) {
    if ((*(char *)dword_800ABBB4 & 0x40) != 0) {
      return param_2;
    }
    iVar1 = (param_2 - dword_800ABBA8) & 0xfff;
    if (iVar1 < 0x400) {
      param_2 = dword_800ABBA8 + 0x400;
    }
    if (iVar1 > 0xc00) {
      param_2 = dword_800ABBA8 - 0x400;
    }
  }
  return param_2;
}

#pragma INCLUDE_ASM("asm/sub_8004E51C.s")

extern int    sub_800296C4(int param_1, short *param_2, unsigned int param_3);
extern void   sub_800298DC(int *param_1);

void sub_8004E588(int param_1, short *param_2, int *param_3)
{
    unsigned int uVar1;

    uVar1 = sub_800296C4(param_1, param_2, 3);
    sub_800298DC(param_3);
    if ((uVar1 & 1) == 0)
    {
        *param_3 = 0xffff8001;
    }
    if ((uVar1 & 2) == 0)
    {
        param_3[1] = 0x7fff;
    }
    return;
}
#pragma INCLUDE_ASM("asm/sub_8004E5E8.s")
#pragma INCLUDE_ASM("asm/sub_8004E71C.s")
#pragma INCLUDE_ASM("asm/sub_8004E808.s")

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

	int1 = HZD_SlopeFloorLevel_800298F8(&vec0.vx,dword_800ABBB8);
	int1 -= snake->field_20_ctrl.field_78;

	vec1.vx = int1;
	vec1.vz = SquareRoot0_80092708(arg1 * arg1 - int1 * int1);
	int0 = -GV_VecDir2_80016EF8(&vec1);

	if (int0 < -0x800)
	{
		int0 += 0x1000;
	}

	return int0;
}

#pragma INCLUDE_ASM("asm/sub_8004E9D0.s")

extern unsigned int GV_DiffDirS_8001704C(int param_1, int param_2);

void sub_8004EA50(int param_1, int param_2)
{
    unsigned int uVar1;

    uVar1 = GV_DiffDirS_8001704C(param_2, (int) *(short *)(param_1 + 0x2a));
    if ((int)uVar1 >= 0x81)
    {
        uVar1 = 0x80;
    }
    else if ((int)uVar1 < -0x80)
    {
        uVar1 = 0xffffff80;
    }
    *(short *)(param_1 + 0x70) = (short)uVar1;
    return;
}
#pragma INCLUDE_ASM("asm/sub_8004EAA8.s")
#pragma INCLUDE_ASM("asm/sub_8004EB14.s")
#pragma INCLUDE_ASM("asm/sub_8004EB74.s")
#pragma INCLUDE_ASM("asm/sub_8004EC00.s")

extern short dword_800B7800[];

extern void  sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flag);
extern void  sd_set_cli_800887EC(int code, int unused);
extern void  sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);
extern void  GM_ClearPlayerStatusFlag_8004E2D4(unsigned int flag);

void sub_8004EC8C(Actor_SnaInit *snake)
{
    ushort sVar0;
    
    sna_init_set_flags_8004E2F4(snake, 0x800);
    snake->field_A28 = 0x1cc;
    dword_800B7800[5] = 1;
    sVar0 = *(ushort*)&e1_800AB7C4.field_4;
    snake->field_A20 = -6;
    snake->field_9D4 = 0x140;
    snake->field_9D8 = sVar0;
    snake->field_9DC = sVar0;
    sd_set_cli_800887EC(0x1ffff20, 0);
    sna_init_sub_8004E330(snake,0x10);
    GM_ClearPlayerStatusFlag_8004E2D4(1);
}
#pragma INCLUDE_ASM("asm/sub_8004ED08.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper3_8004ED6C.s")
#pragma INCLUDE_ASM("asm/sub_8004EE28.s")
#pragma INCLUDE_ASM("asm/sub_8004EEB0.s")
#pragma INCLUDE_ASM("asm/sub_8004EF14.s")
#pragma INCLUDE_ASM("asm/sub_8004EFE4.s")

extern int  sub_8004EFE4(int param_1, int param_2);

void sub_8004F034(int param_1, unsigned int param_2)
{
    int iVar1;

    if (param_2 != *(unsigned int *)(param_1 + 0x18c))
    {
        *(unsigned int *)(param_1 + 0x1a4) = ~param_2;
        *(unsigned int *)(param_1 + 0x18c) = param_2;
        if ((param_2 == 0xffff) && (iVar1 = sub_8004EFE4(param_1, 2),  -1 < iVar1))
        {
            *(int *)(param_1 + 0x1c0) = 4;
            *(short *)(param_1 + 0x1b0) = 2;
        }
    }
    return;
}
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper4_8004F090.s")
#pragma INCLUDE_ASM("asm/sub_8004F14C.s")
#pragma INCLUDE_ASM("asm/sub_8004F204.s")
#pragma INCLUDE_ASM("asm/sub_8004F2A0.s")

extern void GM_ClearPlayerStatusFlag_8004E2D4(unsigned int param_1);
extern void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags);


void sub_8004F2EC(Actor_SnaInit *snake)
{
  GM_ClearPlayerStatusFlag_8004E2D4(0x800000);
  sna_init_clear_flags_8004E308(snake, 1);
  snake->field_89C_pTarget->field_0_flags |= 0x9e;
  return;
}

#pragma INCLUDE_ASM("asm/sub_8004F338.s")
#pragma INCLUDE_ASM("asm/sub_8004F454.s")
#pragma INCLUDE_ASM("asm/sub_8004F544.s")
#pragma INCLUDE_ASM("asm/sub_8004F628.s")
