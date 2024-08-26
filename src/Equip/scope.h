#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Game/map.h"

typedef struct ScopeWork
{
  GV_ACT         field_0_scope;
  CONTROL       *control;
  OBJECT        *field_24_pParent;
  OBJECT_NO_ROTS field_28_obj;
  short          field_4C_saved_packs;
  short          field_4E_saved_raise;
  MAP           *field_50_pMap;
  GV_PAD        *field_54_pOldPad;
  int            field_58;
  short          field_5C_hudDelay; // Adds some delay before showing the HUD of the scope.
  short          field_5E; // Initialized with 2 but apparently never read.
  short          field_60; // Value set to 0 and 1 but apparently never read.
  short          field_62; // Some helper for side lines.
  SVECTOR        field_64_vec;
  SVECTOR        field_6C_turn_vec;
  LINE_F2       *field_74_sideLine_F2s[2]; // Vertical lines on left and right side of the HUD that move when zooming in/out.
  LINE_F4       *field_7C_rect[2]; // Top, right and bottom border of the moving rectangle in the center of the HUD.
  short          field_84_rectOffset[2]; // (x, y) offset of the top left corner of the moving rectangle.
  LINE_F3       *field_88_movingLine_F3s[2]; // Vertical lines that "randomly" change their height.
  LINE_F3       *field_90_zoomLevelLine_F3s[2]; // The horizontal zoom level line on top of the HUD.
  int            field_98_zoomSoundCounter; // Used to play the sound when zooming in/out at a fixed rate.
  int            field_9C_flags;
} ScopeWork;

GV_ACT * NewScope_80063508(CONTROL *pCtrl, OBJECT *pParent, int unused);

#endif // _SCOPE_H_
