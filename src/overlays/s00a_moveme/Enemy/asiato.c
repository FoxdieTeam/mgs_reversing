// ====================================
// asiato.c - あしあと 足跡 - Footprints
// ====================================

/* Func names from leaks
 *
 * NewAsiatoChar
 * AsiatoPos
 * NextAsiato
 * CleanAsiato
 * NearAsiato
 * SearchNearAsiato
 * AsiatoCheck
 * NewAsiato
 * NewAsiatoKun
 */

#include "libgv/libgv.h"
#include "Game/game.h"

#define EXEC_LEVEL 4

typedef struct _Work
{
    GV_ACT actor;
    char    pad[0x8];
} Work;

extern int GM_PlayerStatus_800ABA50;

void asiato_800D199C(Work* work);
void asiato_act_800D18C8(); // has arg, not sure what type



void asiato_800D0DD4(int param_1, char param_2, char param_3, char param_4, char param_5)
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

void asiato_800D0E00(SVECTOR* arg0, short arg1, short arg2, short arg3)
{
    // Not confirmed that it's SVECTOR, but it worked without creating a new struct [-ChrizNuh]
    arg0->vx = arg1;
    arg0->vy = arg2;
    arg0->vz = arg3;
}

int asiato_800D13A0(void) { return *(int* )0x800E0F90; }

int asiato_800d179c(void) // If player is moving and not on wall or prone
{
  return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_MOVING | PLAYER_PRONE)) == PLAYER_MOVING;
}

void asiato_kill_800D1994(void) {}



GV_ACT* NewAsiato_800D1A14(void)
{
    Work* work = NULL;
    

    work = (Work*)GV_NewActor_800150E4(EXEC_LEVEL , sizeof(Work));
    if (work != NULL) 
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)asiato_act_800D18C8, (TActorFunction)asiato_kill_800D1994, "asiato.c");
        asiato_800D199C(work);
    }
    
    return (GV_ACT*) work;
}