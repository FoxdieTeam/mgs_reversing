#include "equip.h"

#include "common.h"
#include "Game/linkvarbuf.h"

extern short GM_Magazine_800AB9EC;
extern short snake_weapon_idx_800BDCBA;
extern short snake_weapon_max_ammo_800BDCBC;
extern short snake_mag_size_800BDCB8;

/*---------------------------------------------------------------------------*/

typedef struct BandanaWork
{
    GV_ACT  actor;
    OBJECT *parent;
    int     unused1;
    int     unused2;
} BandanaWork;

#define EXEC_LEVEL GV_ACTOR_AFTER2

/*---------------------------------------------------------------------------*/

STATIC const char *bandana_orig_tex[3] = {
    "sna_face",
    "sna_face2",
    "sna_face3"
};
STATIC const char *bandana_new_tex[3] = {
    "sna_mf1",
    "sna_mf2",
    "sna_mf3"
};

STATIC void BandanaSwapTextures(OBJECT *parent)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        DG_FreeObjPacket(&parent->objs->objs[6], i);
    }

    for (i = 0; i < 3; i++)
    {
        EQ_ChangeTexture(bandana_orig_tex[i], bandana_new_tex[i]);
    }
}

STATIC void BandanaAct(BandanaWork *work)
{
    int ammo;

    if (snake_weapon_idx_800BDCBA >= 0)
    {
        ammo = GM_CurrentWeapon;
        if (ammo < snake_weapon_max_ammo_800BDCBC)
        {
            GM_Weapons[snake_weapon_idx_800BDCBA] = snake_weapon_max_ammo_800BDCBC;
        }

        ammo = GM_Magazine_800AB9EC;
        if (ammo < snake_mag_size_800BDCB8)
        {
            GM_Magazine_800AB9EC = snake_mag_size_800BDCB8;
        }
    }
}

STATIC void BandanaDie(BandanaWork *work)
{
    BandanaSwapTextures(work->parent);
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewBandana(CONTROL *control, OBJECT *parent, int num_parent)
{
    BandanaWork *work = (BandanaWork *)GV_NewActor(EXEC_LEVEL, sizeof(BandanaWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)BandanaAct,
                         (GV_ACTFUNC)BandanaDie, "bandana.c");
        work->parent = parent;
        BandanaSwapTextures(parent);
    }
    return &work->actor;
}
