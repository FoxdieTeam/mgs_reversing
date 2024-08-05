#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"
#include "common.h"

extern const char s04c_dword_800DBAD8[];



typedef struct _UnknownRevolverWork
{
    GV_ACT   actor;
    TARGET  *target;
    CONTROL  control;
    OBJECT   body;
    char padding[0x6b5];
    TARGET  *pTarget;
    char padding_840[0x98];
    GV_ACT* field_8D8;
    char padding_8DC[0x9a];
} UnknownRevolverWork;



void s04c_revolver_800CF3DC(int arg0) {
    if (GM_StreamStatus_80037CD8() != 2) {
        GM_SeSet2_80032968(0, 63, arg0);
    }
}


void s04c_revolver_800CF418(void)
{
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF420.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF4A0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF518.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF584.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF650.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF69C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF71C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF748.s")


typedef struct _Data800CF7AC {
    char padding[0xA0];  // Add padding to ensure obj is at offset 0xA0
    OBJECT obj;
    char padding2[0xC];
    int unk190;
    char padding3[0x12];
    int unk1A8;
    char padding4[0x6D2];
    int unk880;
    int padding_884;
    int unk888;
} Data800CF7AC;

void GM_ConfigObjectAction_80034CD4(OBJECT *obj, int action_flag, int motion, int interp);


void s04c_revolver_800CF7AC(Data800CF7AC *work) {
    work->unk880 = 0;
    GM_ConfigObjectAction_80034CD4(&work->obj, 0, 0, 4);
    if (work->unk888 != 0) {
        work->unk190 = -1;
        work->unk1A8 = 0;
    }
}



#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF7FC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF868.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF8D8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFAF0.s")

int s04c_revolver_800CFBE0(int pos_vx, int pos_vz)
{
    int v0, v1;

    pos_vx += 2500;
    pos_vz -= 6000;

    do {} while (0);
    v1 = ABS(pos_vx);
    v0 = ABS(pos_vz);
    v0 = v0 < v1;
    v1 = v0 ^ 1;

    if (pos_vx > 0) {
        if (pos_vz > 0) {
            return 1 - (v0 ^ 1);
        } else {
            return v1 | 2;
        }
    } else {
        int result;
        if (pos_vz <= 0) {
            result = 5 - v1;
        } else {
            result = v1 | 6;
        }
        return result;
    }
}

extern SVECTOR GM_PlayerPosition_800ABA10;

int s04c_revolver_800CFC3C(void) {
    SVECTOR* pos = &GM_PlayerPosition_800ABA10;
    return s04c_revolver_800CFBE0(pos->vx, pos->vz);
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC6C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFD08.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFD84.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFE44.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFED4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D00B4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D02C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03C0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03EC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0418.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0444.s")

void s04c_revolver_800D04B8(int *arg0, int arg1)
{
    arg0[0] = arg1;
    arg0[1] = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D04C4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D07F4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0A94.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1120.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D11C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1318.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1364.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D149C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D158C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D15D4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D168C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1760.s")

void s04c_revolver_800D184C(void* arg0);
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D184C.s")


void s04c_revolver_800D1BE4(UnknownRevolverWork *work)
{
    GM_GameStatus_800AB3CC &= 0xFFFF7FFF;

    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->body);
    GM_FreeTarget_8002D4B0(work->pTarget);
    GV_DestroyActor_800151C8(work->field_8D8);

    GM_GameStatus_800AB3CC &= 0xFFFF7FFF;
}


#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1C60.s")

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1CE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D2028.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revbullt_800D20BC.s")
