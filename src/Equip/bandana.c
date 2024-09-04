#include "bandana.h"
#include "Equip/effect.h"
#include "Game/linkvarbuf.h"

typedef struct BandanaWork
{
    GV_ACT  actor;
    OBJECT *parent;
    int     unused1;
    int     unused2;
} BandanaWork;

extern short GM_Magazine_800AB9EC;

extern short snake_weapon_idx_800BDCBA;
extern short snake_weapon_max_ammo_800BDCBC;
extern short GM_Magazine_800AB9EC;
extern short snake_mag_size_800BDCB8;

//------------------------------------------------------------------------------

const char *bandana_orig_tex_8009F2A8[3] = {"sna_face", "sna_face2", "sna_face3"};
const char *bandana_new_tex_8009F2B4[3] = {"sna_mf1", "sna_mf2", "sna_mf3"};

//------------------------------------------------------------------------------

void BandanaSwapTextures_80061D14(OBJECT *parent)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        DG_FreeObjPacket(&parent->objs->objs[6], i);
    }

    for (i = 0; i < 3; i++)
    {
        EQ_ChangeTexture_80060CE4(bandana_orig_tex_8009F2A8[i], bandana_new_tex_8009F2B4[i]);
    }
}

void BandanaAct_80061DA0(BandanaWork *work)
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

void BandanaDie_80061E1C(BandanaWork *work)
{
    BandanaSwapTextures_80061D14(work->parent);
}

GV_ACT * NewBandana_80061E40(CONTROL *control, OBJECT *parent, int num_parent)
{
    BandanaWork *work = (BandanaWork *)GV_NewActor(7, sizeof(BandanaWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BandanaAct_80061DA0,
                         (TActorFunction)BandanaDie_80061E1C, "bandana.c");
        work->parent = parent;
        BandanaSwapTextures_80061D14(parent);
    }
    return &work->actor;
}
