#include "bandana.h"
#include "unknown.h"
#include "Game/linkvarbuf.h"

extern short GM_Magazine_800AB9EC;

extern short snake_weapon_idx_800BDCBA;
extern short snake_weapon_max_ammo_800BDCBC;
extern short GM_Magazine_800AB9EC;
extern short snake_mag_size_800BDCB8;

//------------------------------------------------------------------------------

const char *off_8009F2A8[3] = {"sna_face", "sna_face2", "sna_face3"};
const char *off_8009F2B4[3] = {"sna_mf1", "sna_mf2", "sna_mf3"};

//------------------------------------------------------------------------------

void bandana_80061D14(OBJECT *pObj)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], i);
    }

    for (i = 0; i < 3; i++)
    {
        EQ_ChangeTexture_80060CE4(off_8009F2A8[i], off_8009F2B4[i]);
    }
}

void bandana_act_80061DA0(BandanaWork *work)
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

void bandana_kill_80061E1C(BandanaWork *work)
{
    bandana_80061D14(work->field_20_pParent);
}

GV_ACT * NewBandana_80061E40(CONTROL *pCtrl, OBJECT *pParent, int unused)
{
    BandanaWork *work = (BandanaWork *)GV_NewActor_800150E4(7, sizeof(BandanaWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)bandana_act_80061DA0,
                                  (TActorFunction)bandana_kill_80061E1C, "bandana.c");
        work->field_20_pParent = pParent;
        bandana_80061D14(pParent);
    }
    return &work->field_0_actor;
}
