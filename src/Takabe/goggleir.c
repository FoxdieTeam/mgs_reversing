#include "goggleir.h"
#include "goggle.h"

#include "psyq.h"
#include "scn_mask.h"
#include "Equip/effect.h"
#include "Game/map.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"

// thermal goggles (screen effect)

extern int GM_GameStatus;
extern int DG_CurrentGroupID_800AB968;
extern int dword_800BDFA8;
extern u_long DG_PaletteBuffer_800B3818[256];

RECT rect_8009F718 = {768, 226, 256, 2};
RECT rect_8009F720 = {768, 196, 256, 2};

ushort goggleir_pal_convert_800789E0(ushort base)
{
    int r, r2;
    int g;
    int b;
    int a;

    if ((base & 0x7fff) == 0)
    {
        return base;
    }

    r = base & 31;
    r2 = r;

    g = ((base & 0x3E0) >> 5) & 31;
    if (g > r2) r2 = g;

    b = ((base & 0x7C00) >> 10) & 31;
    if (b > r2) r2 = b;

    a = base & 0x8000;

    r2 = 4 * r2 / 3;

    r = r2 / 2 + 2;
    if (r > 31) r = 31;

    g = r2 / 4;
    if ((r2 / 4) > 31) g = 31; // why

    b = r2 / 4;
    if (b > 31) b = 31;

    return r | g << 5 | b << 10 | a;
}

void goggleir_pal_cb_80078AB8(void)
{
    int     iVar1;
    ushort *puVar2;
    int     iVar3;
    ushort  uVar4;

    iVar1 = 0xf;

    rect_8009F718.y = 0xe2;
    rect_8009F720.y = 0xc4;

    for (; iVar1 > 0; iVar1--)
    {
        DrawSync(0);
        StoreImage2(&rect_8009F720, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        puVar2 = (ushort *)DG_PaletteBuffer_800B3818;
        iVar3 = 0x200;

        for (; iVar3 > 0; iVar3--)
        {
            *puVar2++ = goggleir_pal_convert_800789E0(*puVar2);
        }

        if (iVar1 == 1)
        {
            uVar4 = goggleir_pal_convert_800789E0(0xffff);
            puVar2 = (ushort *)&DG_PaletteBuffer_800B3818[248];
            iVar3 = 0x10;

            for (; iVar3 > 0; iVar3--)
            {
                *puVar2++ = uVar4;
            }
        }

        LoadImage2(&rect_8009F718, DG_PaletteBuffer_800B3818);

        rect_8009F720.y += 2;
        rect_8009F718.y += 2;
    }
}

void goggleir_act_80078BE0(GoggleIrWork *work)
{
    int new_map; // $a0
    if (work->field_4C_head_hidden)
    {
        new_map = work->control->map->index;
        DG_GroupObjs(work->field_20_obj.objs, DG_CurrentGroupID_800AB968);
        GM_CurrentMap_800AB9B0 = new_map;
        if (work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE)
        {
            DG_InvisibleObjs(work->field_20_obj.objs);
        }
        else
        {
            DG_VisibleObjs(work->field_20_obj.objs);
        }
    }

    if (work->field_50 == 3)
    {
        DG_SetExtPaletteMakeFunc_80079194(goggleir_pal_cb_80078AB8, goggleir_pal_convert_800789E0);
        GM_GameStatus |= STATE_THERMG;
        dword_800BDFA8 = 1;
        work->field_54_pScn_mask = (GV_ACT *)new_scn_mask_8007895C(1);
    }

    if (work->field_50 < 11)
    {
        work->field_50++;
    }
}

void goggleir_kill_80078CE4(GoggleIrWork *work)
{
    GM_GameStatus &= ~STATE_THERMG;
    DG_ResetExtPaletteMakeFunc_800791E4();

    if (work->field_54_pScn_mask)
    {
        GV_DestroyOtherActor(work->field_54_pScn_mask);
    }

    if (work->field_58_pGglmng)
    {
        GV_DestroyOtherActor(work->field_58_pGglmng);
    }

    if (work->field_64_pGglmng)
    {
        GV_DestroyOtherActor(work->field_64_pGglmng);
    }

    if (work->field_4C_head_hidden)
    {
        GM_FreeObject((OBJECT *)&work->field_20_obj);
        EQ_VisibleHead(work->field_48_pParent, &work->field_68_savedNPacks, &work->field_6A_saved_raise);
    }
}

int goggleir_loader_80078D8C(GoggleIrWork *work, OBJECT *pParent)
{
    OBJECT_NO_ROTS *pObj = &work->field_20_obj;

    if (pParent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots(pObj, GV_StrCode("goggles"), 877, 0);
        if (!pObj->objs)
        {
            return -1;
        }
        GM_ConfigObjectRoot((OBJECT *)pObj, pParent, 6);
        if (pParent->light)
        {
            GM_ConfigObjectLight((OBJECT *)pObj, pParent->light);
        }
        work->field_48_pParent = pParent;
        EQ_InvisibleHead(pParent, &work->field_68_savedNPacks, &work->field_6A_saved_raise);
        work->field_4C_head_hidden = 1;
    }

    work->field_64_pGglmng = NewGglmng_800779B8(ITEM_THERM_G);
    if (!work->field_64_pGglmng)
    {
        return -1;
    }
    return 0;
}

GV_ACT *NewGoggleIr_80078E6C(CONTROL *pCtrl, OBJECT *parent_obj, int unused)
{
    GoggleIrWork *work = (GoggleIrWork *)GV_NewActor(6, sizeof(GoggleIrWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&goggleir_act_80078BE0,
                         (GV_ACTFUNC)&goggleir_kill_80078CE4, "goggleir.c");

        if (goggleir_loader_80078D8C(work, parent_obj) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
    }

    work->control = pCtrl;
    work->field_50 = 0;

    return &work->actor;
}
