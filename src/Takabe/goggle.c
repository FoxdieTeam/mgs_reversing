#include "goggle.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Game/map.h"
#include "unknown.h"
#include "scn_mask.h"
#include "Equip/gglmng.h"

// night vision goggles (screen effect)

extern int GM_GameStatus_800AB3CC;
extern int DG_CurrentGroupID_800AB968;

RECT rect_8009F704 = {768, 226, 256, 2};
RECT rect_8009F70C = {768, 196, 256, 2};

ushort goggle_pal_convert_8007743C(ushort value)
{
    int r, r2;
    int g;
    int b;
    int a;

    if ((value & 0x7fff) == 0)
    {
        return value;
    }

    r = value & 0x1f;
    r2 = r;

    g = (value & 0x3e0) >> 5;
    if (r2 < g)
    {
        r2 = g;
    }

    b = (value & 0x7c00) >> 10;
    if (r2 < b)
    {
        r2 = b;
    }

    a = value & 0x8000;

    r2 <<= 1;
    if (r2 > 31)
    {
        r2 = 31;
    }

    r = r2;
    g = r;
    b = r;

    return r | g << 5 | b << 10 | a;
}

extern u_long image_data_800B3818[256];

void goggle_pal_cb_800774C0(void)
{
    int iVar1;
    int iVar2;
    ushort *ptr;

    rect_8009F704.y = 0xe2;
    rect_8009F70C.y = 0xc4;

    for (iVar1 = 15; iVar1 > 0; iVar1--) {
        DrawSync(0);
        StoreImage2(&rect_8009F70C, image_data_800B3818);
        DrawSync(0);

        ptr = (ushort *)image_data_800B3818;

        for (iVar2 = 512; iVar2 > 0; iVar2--) {
            *ptr++ = goggle_pal_convert_8007743C(*ptr);
        }

        LoadImage2(&rect_8009F704, image_data_800B3818);

        rect_8009F70C.y += 2;
        rect_8009F704.y += 2;
    }
}

void goggle_act_800775B4(GoggleWork *work)
{
    DG_OBJS *objs;    // $a1
    int      new_map; // $a0

    if (work->field_4C_head_hidden)
    {
        objs = work->field_20_obj.objs;
        new_map = work->field_44_pCtrl->field_2C_map->field_0_map_index_bit;
        DG_GroupObjs(work->field_20_obj.objs, DG_CurrentGroupID_800AB968);

        GM_CurrentMap_800AB9B0 = new_map;
        if (work->field_48_pObj->objs->flag & DG_FLAG_INVISIBLE)
        {
            DG_InvisibleObjs(work->field_20_obj.objs);
        }
        else
        {
            DG_VisibleObjs(work->field_20_obj.objs);
        }
    }

    if (work->field_50 == 2)
    {
        GM_GameStatus_800AB3CC |= 4u;
        set_pal_effect_fns_80079194(goggle_pal_cb_800774C0, goggle_pal_convert_8007743C);
        work->field_54_pScn_mask = (GV_ACT *)new_scn_mask_8007895C(0);
    }

    if (work->field_50 < 11)
    {
        work->field_50++;
    }
}

void goggle_kill_800776AC(GoggleWork *work)
{
    GM_GameStatus_800AB3CC &= ~4u;
    DG_ResetExtPaletteMakeFunc_800791E4();

    if (work->field_54_pScn_mask)
    {
        GV_DestroyOtherActor_800151D8(work->field_54_pScn_mask);
    }

    if (work->field_58_pGglmng)
    {
        GV_DestroyOtherActor_800151D8(work->field_58_pGglmng);
    }

    if (work->field_4C_head_hidden)
    {
        GM_FreeObject_80034BF8((OBJECT *)&work->field_20_obj);
        EQ_VisibleHead_80060DF0(work->field_48_pObj, &work->field_5C_saved_n_packs, &work->field_5E_saved_rise);
    }
}

int goggle_loader_8007773C(GoggleWork *work, OBJECT *pParent)
{
    OBJECT_NO_ROTS *pObj = &work->field_20_obj;
    if (pParent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots_800349B0(pObj, GV_StrCode_80016CCC("goggles"), WEAPON_FLAG, 0);
        if (!pObj->objs)
        {
            return -1;
        }
        GM_ConfigObjectRoot_80034C5C((OBJECT *)pObj, pParent, 6);
        if (pParent->light)
        {
            GM_ConfigObjectLight_80034C44((OBJECT *)pObj, pParent->light);
        }
        work->field_48_pObj = pParent;
        EQ_InvisibleHead_80060D5C(pParent, &work->field_5C_saved_n_packs, &work->field_5E_saved_rise);
        work->field_4C_head_hidden = 1;
    }

    work->field_58_pGglmng = gglmng_init_800779B8(5);
    if (!work->field_58_pGglmng)
    {
        return -1;
    }

    return 0;
}

GV_ACT * NewGoggle_8007781C(CONTROL *a1, OBJECT *parent_obj, int unused)
{
    GoggleWork *goggle_actor = (GoggleWork *)GV_NewActor_800150E4(6, sizeof(GoggleWork));

    if (goggle_actor)
    {
        GV_SetNamedActor_8001514C(&goggle_actor->field_0_actor, (TActorFunction)&goggle_act_800775B4,
                                  (TActorFunction)&goggle_kill_800776AC, "goggle.c");

        if (goggle_loader_8007773C(goggle_actor, parent_obj) < 0)
        {
            GV_DestroyActor_800151C8(&goggle_actor->field_0_actor);
            return 0;
        }
    }

    goggle_actor->field_44_pCtrl = a1;
    goggle_actor->field_50 = 0;

    return &goggle_actor->field_0_actor;
}
