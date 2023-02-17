#ifndef _BULLET_H
#define _BULLET_H

#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/target.h"

typedef struct Actor_Bullet
{
    GV_ACT     f000_actor;
    char       f020_[0x24];
    GM_Target  f044_target;
    char       f08C_[0x94];
    SVECTOR    f120_target_pos;
    int        f128_unk;
    int        f12C_unk;
    int        f130_unk;
    int        f134_unk;
    int        f138_unk;
    int        f13C_unk;
    int        f140_unk;
    int        f144_unk;
    int        f148_unk;
    int        f14C_flags;
    int        f150_unk;
    int        f154_unk;
    int        f158_unk;
    int        f15C_unk;
    int        f160_vec_len;
    int        f164_unk;
    int        f168_unk;
    int        f16C_unk;
} Actor_Bullet;

#endif // _BULLET_H
