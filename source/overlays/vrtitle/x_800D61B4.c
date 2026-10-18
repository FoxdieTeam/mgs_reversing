// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (CameraGetResources_800CE6EC), adapted from the asm.
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "overlays/camera/unknown/camera.h"

void vrtitle_800D044C( void );
void vrtitle_800D0160( void );
void vrtitle_800D613C( Work *work );

int vrtitle_800D61B4( Work *work, int where )
{
    GM_CurrentMap = where;

    work->pad = &GV_PadData[ 2 ];

    work->field_700.prim = (MenuPrim *)&work->field_920;
    work->field_92C[ 0 ] = work->padding5;
    work->f28 = 0;
    work->field_4938 = 0;
    work->field_92C[ 1 ] = work->padding5 + 0x2000;

    vrtitle_800D044C();
    vrtitle_800D0160();

    work->f49E0 = 0;
    vrtitle_800D613C( work );
    return 0;
}
