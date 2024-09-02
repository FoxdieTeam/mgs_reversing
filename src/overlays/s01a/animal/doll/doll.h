#ifndef _DOLL_H_
#define _DOLL_H_

#include "libgv/libgv.h"
#include "Game/object.h"

struct _DollWork;
typedef void (*DollFunc)(struct _DollWork *, int);

typedef struct _DollMotion
{
    int     index;
    SVECTOR entries[4];
} DollMotion;

typedef struct _DollWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT oars[42];
    SVECTOR        rots[20];
    SVECTOR        adjust[20];
    MATRIX         light[2];
    char           pad[0x4];
    OBJECT         weapon;
    GV_ACT        *glight;
    char           pad13[0x54];
    int            fA78;
    char           pad25[0xA];
    short          fA86;
    char           pad16[0x4];
    char           fA8C[4];
    int            fA90;
    SVECTOR        fA94[32];
    int            fB94;
    SVECTOR        fB98;
    SVECTOR        fBA0;
    int            fBA8;
    int            fBAC;
    int            fBB0;
    int            fBB4;
    int            fBB8;
    char           pad9[0x8];
    int            fBC4;
    SVECTOR        fBC8;
    DollFunc       fBD0;
    char           pad20[0x4];
    int            fBD8;
    char           pad7[0x4];
    int            fBE0;
    int            fBE4;
    int            fBE8[5];
    int            fBFC;
    char           pad14[0x4];
    int            fC04;
    short          fC08;
    short          fC0A;
    short          fC0C;
    short          fC0E;
    int            fC10;
    int            fC14;
    int            fC18;
    int            fC1C;
    int            fC20;
    char           pad8[0xC];
    short          fC30[8];
    short          fC40[4];
    DollMotion     fC48[12];
    int            fDF8;
    short          fDFC;
    short          fDFE;
    short          fE00[2];
    GV_ACT        *fE04;
    int            fE08;
    int            fE0C;
    char           pad21[0x4];
    GV_ACT        *shadow;
    int            fE18[8];
    int            fE38;
    short          fE3C;
    short          fE3E;
    int            fE40;
    int            fE44;
    char           fE48[16];
    int            fE58;
    int            fE5C;
    int            fE60[8];
    short          fE80;
    short          fE82;
} DollWork;

GV_ACT * NewDoll_800DCD78(int name, int where, int argc, char **argv);

#endif // _DOLL_H_
