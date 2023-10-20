#include "libgv/libgv.h"
#include "Game/game.h"

extern unsigned int GM_PlayerStatus_800ABA50;
extern int s00a_dword_800E0F90;

extern const char aAsiatoc_800E0998[]; //asiato.c

typedef struct _Work
{
    GV_ACT actor;
    char    pad[0x8];
} Work;

void s00a_asiato_800D0DD4(int param_1, char param_2, char param_3, char param_4, char param_5)
{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x40);
  *(char *)(iVar1 + 4) = param_3;
  *(char *)(iVar1 + 5) = param_4;
  *(char *)(iVar1 + 6) = param_5;
  iVar1 = *(int *)(param_1 + 0x44);
  *(char *)(iVar1 + 4) = param_3;
  *(char *)(iVar1 + 5) = param_4;
  *(char *)(iVar1 + 6) = param_5;
  return;
}

void s00a_asiato_800D0E00(SVECTOR* arg0, short arg1, short arg2, short arg3)
{
    // Not confirmed that it's SVECTOR, but it worked without creating a new struct [-ChrizNuh]
    arg0->vx = arg1;
    arg0->vy = arg2;
    arg0->vz = arg3;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0E10.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0E9C.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0F90.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D116C.s")

//NewAsiatoChar
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D11DC.s")

//AsiatoPos
#pragma INCLUDE_ASM("asm/overlays/s00a/AsiatoPos_800D129C.s")

//NextAsiato
#pragma INCLUDE_ASM("asm/overlays/s00a/NextAsiato_800D12D0.s")

//CleanAsiato
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1378.s")

//NearAsiato
int NearAsiato_800D13A0(void) { return s00a_dword_800E0F90; };

//SearchNearAsiato
#pragma INCLUDE_ASM("asm/overlays/s00a/SearchNearAsiato_800D13B0.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1500.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D15D8.s")

//AsiatoCheck
#pragma INCLUDE_ASM("asm/overlays/s00a/AsiatoCheck_800D16C0.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D16F8.s")

//#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D179C.s")
int s00a_asiato_800D179C(void) // If player is moving and not on wall or prone
{
  return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_MOVING | PLAYER_PRONE)) == PLAYER_MOVING;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D17BC.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1844.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D18C8.s")


void AsiatoDie_800D1994(void) {}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D199C.s")

extern void s00a_asiato_800D18C8(Work *work);
extern void s00a_asiato_800D199C(Work *work);


GV_ACT* NewAsiato_800D1A14(void)
{
    Work* work = NULL;
    
    work = (Work*)GV_NewActor_800150E4(4 , sizeof(Work));
    if (work != NULL) 
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)s00a_asiato_800D18C8, (TActorFunction)AsiatoDie_800D1994, aAsiatoc_800E0998);
        s00a_asiato_800D199C(work);
    }
    
    return (GV_ACT*) work;
}

//NewAsiatoKun
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1A70.s")