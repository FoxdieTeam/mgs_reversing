#ifndef __MGS_OKAJIMA_WOLF2_H__
#define __MGS_OKAJIMA_WOLF2_H__

#include "libdg/libdg.h"
#include "game/game.h"
#include "menu/menuman.h"

typedef struct Wolf2Alloc
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} Wolf2Alloc;

typedef struct Wolf2Work
{
    GV_ACT         actor;
    Wolf2Alloc    *alloc;
    CONTROL        control;
    OBJECT         body;
    OBJECT         weapon;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs[17];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    TARGET        *f65C;
    TARGET        *f660;
    char           pad12[0x24];
    int            f688;
    char           pad4[0x4];
    int            f690;
    char           pad5[0x8];
    int            f69C;
    int            f6A0;
    int            f6A4;
    int            f6A8;
    int            f6AC;
    int            f6B0;
    char           pad6[0x8];
    int            f6BC;
    char           pad33[0x20];
    int            f6E0;
    char           pad21[0x8]; // 6E4
    int            voices[1];  // 6EC
    char           pad7[0xC];
    int            f6FC;
    int            f700;
    char           pad22[0x20];
    int            f724;
    char           pad23[0x24];
    DG_PRIM       *lsight_prim;
    DG_TEX        *lsight_tex;
    SVECTOR        lsight_verts[3]; // wrong size
    char           pad38[0x4];
    int            f770;
    int            f774;
    int            f778;
    char           pad34[0x8];
    int            f784;
    int            f788;
    int            f78C;
    char           pad35[0x14];
    int            f7A4;
    char           pad36[0x2C];
    int            f7D4;
    int            f7D8;
    int            f7DC;
    DG_PRIM       *f7E0;
    SVECTOR        f7E4[2];
    char           pad8[0x8];
    int            f7FC;
    int            f800[1]; // num?
    char           pad19[0x84];
    SVECTOR        f888[1]; // num?
    char           pad20[0x10C];
    int            f99C;
    char           pad25[0xC];
    short          f9AC;
    short          f9AE;
    short          f9B0;
    char           pad16[0xA];
    int            f9BC;
    int            f9C0;
    int            f9C4;
    int            f9C8;
    char           pad17[0x4];
    int            f9D0;
    int            f9D4;
    int            f9D8;
    int            f9DC;
    int            f9E0;
    int            f9E4;
    int            f9E8;
    char           pad18[0x4];
    int            f9F0;
    char           pad10[0x18];
    int            fA0C;
    SVECTOR        fA10;
    char           pad30[0x10];
    int            fA28;
    char           pad31[0x4];
    GV_ACT        *cinema_screen;
    MENU_BAR_CONF  lifebar;
    int            fA40;
    int            fA44;
    int            fA48;
    int            fA4C;
    int            fA50;
    char           pad27[0x4];
    int            fA58;
    char           pad11[0xC];
    int            fA68;
    int            fA6C;
    char           pad24[0x4];
} Wolf2Work;

#endif // __MGS_OKAJIMA_WOLF2_H__
