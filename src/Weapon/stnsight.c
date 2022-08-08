#include "linker.h"
#include "stnsight.h"
#include "Game/game.h"

// stinger first person HUD

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_8006837C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068420.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068798.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068A24.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068BF4.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_80068D0C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_kill_80068ED8.s")

int stnsight_init_helper_helper_80068F74(Actor_stnsight *actor)
{
    LINE_F4 *lines;
    TILE_1 *tiles;
    int count;

    // NOTE: despite allocating 56 LINE_F4s, this function only inits 42
    actor->field_28_lines = lines = GV_Malloc_8001620C(sizeof(LINE_F4) * 56);
    
    if (!lines) {
        return -1;
    }

    actor->field_2C_lines = lines + 14;
    actor->field_30_lines = lines + 28;
    actor->field_34_lines = lines + 42;

    actor->field_48_tiles = tiles = GV_Malloc_8001620C(sizeof(TILE_1) * 14);

    if (!tiles) {
        return -1;
    }

    actor->field_4C_tiles = tiles + 7;
    
    for (count = 0; count < 14; count++) {
        *(int *)&lines->r0 = 0x41412e;
        lines->x3 = 18;
        lines->x0 = 18;
        lines->x2 = 41;
        lines->x1 = 41;
        setLineF4(lines);
        lines++;

        *(int *)&lines->r0 = 0x41412e;
        lines->x1 = 18;
        lines->x0 = 18;
        setLineF2(lines);
        lines++;
    }

    for (count = 0; count < 28; count++) {
        *(int *)&lines->r0 = 0x41412e;
        lines->x2 = 42;
        lines->x1 = 42;
        lines->x0 = 42;
        lines->x3 = 45;
        setLineF4(lines);
        lines++;
    }

    tiles = actor->field_48_tiles;
    
    for (count = 0; count < 14; count++) {
        *(int *)&tiles->r0 = 0x68b187;
        tiles->x0 = 47;
        setTile1(tiles);
        tiles++;
    }
        
    return 0;
}

#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069100.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069184.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069234.s")

extern GV_PAD GV_PadData_800B05C0[4];

int stnsight_init_helper_800692D0(Actor_stnsight *actor, int type)
{  
    if (stnsight_init_helper_helper_80068F74(actor) < 0) {
        return -1;
    }

    if (stnsight_init_helper_helper_80069100(actor) < 0) {
        return -1;
    }
    
    if (stnsight_init_helper_helper_80069184(actor) < 0) {
        return -1;
    }
    
    if (stnsight_init_helper_helper_80069234(actor) < 0) {
        return -1;
    }

    actor->field_60_18Array[0] = 0x93;
    actor->field_60_18Array[1] = 0x75;
    actor->field_60_18Array[2] = 0x93;
    actor->field_60_18Array[3] = 0x68;
    actor->field_60_18Array[4] = 0x9f;
    actor->field_60_18Array[5] = 0x74;
    actor->field_60_18Array[6] = 0xab;
    actor->field_60_18Array[7] = 0x68;
    actor->field_60_18Array[8] = 0xab;
    actor->field_60_18Array[9] = 0x75;
    actor->field_60_18Array[10] = 0x90;
    actor->field_60_18Array[11] = 0x78;
    actor->field_60_18Array[12] = 0x90;
    actor->field_60_18Array[13] = 0x7b;
    actor->field_60_18Array[14] = 0xae;
    actor->field_60_18Array[15] = 0x7b;
    actor->field_60_18Array[16] = 0xae;
    actor->field_60_18Array[17] = 0x78;
    actor->field_24_pad_data = GV_PadData_800B05C0;
    actor->field_5C = 0;
    actor->field_58 = 0;
    actor->field_20_type = type;
    actor->field_84_4Array[0] = 0;
    actor->field_84_4Array[1] = 0;
    actor->field_84_4Array[2] = 0;
    actor->field_84_4Array[3] = 0;
    actor->field_94 = 8;

    return 0;
}

extern const char aStnsightC[]; // = "stnsight.c"

// re-declare to force GP usage
extern int dword_800AB8EC;
int        SECTION(".dword_800AB8EC") dword_800AB8EC;

Actor_stnsight * NewStnSight_800693E0(int type)
{
    Actor_stnsight *actor;

    if ((short)dword_800AB8EC != 0) {
        return 0;
    }

    actor = (Actor_stnsight *)GV_NewActor_800150E4(7, sizeof(Actor_stnsight));

    if (actor) {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)stnsight_act_80068D0C, (TActorFunction)stnsight_kill_80068ED8, aStnsightC);

        if (stnsight_init_helper_800692D0(actor, type) < 0) {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        *(short *)&dword_800AB8EC = 1;
    }

    return actor;
}
