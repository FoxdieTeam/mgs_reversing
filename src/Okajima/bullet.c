#include "linker.h"
#include "libdg.h"
#include "target.h"

#pragma INCLUDE_ASM("asm/Okajima/bullet_80075314.s") // 68 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075358.s") // 188 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_80075414.s") // 208 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_800754E4.s") // 300 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075610.s") // 332 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader3_8007575C.s") // 1656 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_80075DD4.s") // 912 bytes

void bullet_kill_80076164(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x8c);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

extern int SECTION(".data") aDdd_8009F6EC[]; // TODO: define as SVECTOR*
int bullet_loader_800761A0(int pActor, int param_2)
{
  SVECTOR local_18;
  
  GM_SetTarget_8002DC74((GM_Target *)(pActor + 0x44), 4, param_2, (SVECTOR *)aDdd_8009F6EC);
    
  local_18.vx = *(short *)(pActor + 0x120) >> 3; // divide 8 won't match
  local_18.vy = *(short *)(pActor + 0x122) >> 3;
  local_18.vz = *(short *)(pActor + 0x124) >> 3;
    
  if ((*(int *)(pActor + 0x14c) & 0x800) != 0)
  {
      GM_Target_8002DCCC((GM_Target *)(pActor + 0x44), 0, 2,
          *(int *)(pActor + 0x154), 0, &local_18);
  }
  else
  {
      GM_Target_8002DCCC((GM_Target *)(pActor + 0x44), 0, 1,
          *(int *)(pActor + 0x154), 0, &local_18);
  }
    
  return 0;
}

#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_80076274.s") // 428 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBulletEnemy_80076420.s") // 356 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_init_80076584.s") // 388 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBulletEx_80076708.s") // 548 bytes
#pragma INCLUDE_ASM("asm/Okajima/sub_8007692C.s") // 192 bytes
