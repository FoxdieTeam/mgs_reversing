#ifndef __MGS_KOBA_VRMENU_H__
#define __MGS_KOBA_VRMENU_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg/libdg.h"

// One selectable entry of the VR menus (VR clear screen, VR pause menu).
// Tables of these are initialised data of the menu files.
typedef struct VR_MENU_ITEM
{
    RECT      rect;         // 0x00: highlight rectangle (when selected)
    short     link[4];      // 0x08: index of the neighbour item for up, left, down, right (-1: none)
    int       tex_id;       // 0x10: label texture
    int       proc;         // 0x14: GCL proc executed when chosen (0: none)
    RECT      label;        // 0x18: where the label is drawn
    short     step;         // 0x20: open/close animation step
    u_char    state;        // 0x22: VR_MENU_ITEM_STATE_*
    u_char    pad23;
    DG_TEX   *tex;          // 0x24
    POLY_FT4  polys[2];     // 0x28: highlight (double buffered)
} VR_MENU_ITEM;             // 0x78

#define VR_MENU_ITEM_STATE_OPEN     0   // fully open
#define VR_MENU_ITEM_STATE_GROW_W   1   // opening: horizontal line grows
#define VR_MENU_ITEM_STATE_GROW_H   2   // opening: line grows to the full height
#define VR_MENU_ITEM_STATE_SHRINK_H 3   // closing: shrinks to a line
#define VR_MENU_ITEM_STATE_SHRINK_W 4   // closing: line shrinks
#define VR_MENU_ITEM_STATE_CLOSED   5   // not drawn

#define VR_MENU_FRAME_POLYS         8   // corners and edges of a menu frame

void VrMenu_InitFrame(POLY_FT4 polys[2][VR_MENU_FRAME_POLYS], TILE tiles[2], int clut);
int  VrMenu_LoadFrameTexture(void);
void VrMenu_UpdateFrame(RECT *rect, RECT *target, POLY_FT4 *polys, TILE *tile);
void VrMenu_ExecItem(VR_MENU_ITEM *item);
void VrMenu_DrawItem(VR_MENU_ITEM *item);
int  VrMenu_InitItem(VR_MENU_ITEM *item, int proc, int state);

#endif // __MGS_KOBA_VRMENU_H__
