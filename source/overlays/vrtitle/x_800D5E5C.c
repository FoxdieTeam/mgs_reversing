// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (CameraAct_800CE404), adapted from the asm.
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "overlays/camera/unknown/camera.h"

void vrtitle_800D5D94( Work *work );

void vrtitle_800D5E5C( Work *work )
{
    work->field_920 = work->field_92C[GV_Clock];
    work->field_924_mOrderingTable = DG_Chanl(1)->ot[GV_Clock];
    vrtitle_800D5D94(work);
    work->field_4938++;
}
