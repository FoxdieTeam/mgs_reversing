#include "goggleir.h"
#include "goggle.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/map.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Equip/equip.h"
#include "scn_mask.h"

extern int DG_CurrentGroupID;
extern int dword_800BDFA8;
extern u_long DG_PaletteBuffer_800B3818[256];

/*---------------------------------------------------------------------------*/
// thermal goggles (screen effect)

typedef struct GoggleIrWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent_obj;
    int            head_hidden;
    int            field_50;
    GV_ACT        *scn_mask; // thermal goggles screen effect
    GV_ACT        *manager;
    int            field_5C;
    int            field_60;
    GV_ACT        *manager2;
    short          saved_n_packs;
    short          saved_raise;
} GoggleIrWork;

// STATIC_ASSERT(sizeof(GoggleIrWork) == 0x6C, "sizeof(GoggleIrWork) is wrong!");

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC RECT rect_8009F718 = {768, 226, 256, 2};
STATIC RECT rect_8009F720 = {768, 196, 256, 2};

STATIC u_short goggleir_PaletteConvert(u_short base)
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

STATIC void goggleir_PaletteCallback(void)
{
    int     iVar1;
    u_short *puVar2;
    int     iVar3;
    u_short uVar4;

    iVar1 = 15;

    rect_8009F718.y = 0xe2;
    rect_8009F720.y = 0xc4;

    for (; iVar1 > 0; iVar1--)
    {
        DrawSync(0);
        StoreImage2(&rect_8009F720, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        puVar2 = (u_short *)DG_PaletteBuffer_800B3818;
        iVar3 = 0x200;

        for (; iVar3 > 0; iVar3--)
        {
            *puVar2++ = goggleir_PaletteConvert(*puVar2);
        }

        if (iVar1 == 1)
        {
            uVar4 = goggleir_PaletteConvert(0xffff);
            puVar2 = (u_short *)&DG_PaletteBuffer_800B3818[248];
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

STATIC void goggleir_Act(GoggleIrWork *work)
{
    int new_map;
    if (work->head_hidden)
    {
        new_map = work->control->map->index;
        DG_GroupObjs(work->object.objs, DG_CurrentGroupID);
        GM_CurrentMap = new_map;
        if (work->parent_obj->objs->flag & DG_FLAG_INVISIBLE)
        {
            DG_InvisibleObjs(work->object.objs);
        }
        else
        {
            DG_VisibleObjs(work->object.objs);
        }
    }

    if (work->field_50 == 3)
    {
        DG_SetExtPaletteMakeFunc(goggleir_PaletteCallback, goggleir_PaletteConvert);
        GM_GameStatus |= STATE_THERMG;
        dword_800BDFA8 = 1;
        work->scn_mask = (GV_ACT *)NewNightVisionScreen(1);
    }

    if (work->field_50 < 11)
    {
        work->field_50++;
    }
}

STATIC void goggleir_Die(GoggleIrWork *work)
{
    GM_GameStatus &= ~STATE_THERMG;
    DG_ResetExtPaletteMakeFunc();

    if (work->scn_mask)
    {
        GV_DestroyOtherActor(work->scn_mask);
    }

    if (work->manager)
    {
        GV_DestroyOtherActor(work->manager);
    }

    if (work->manager2)
    {
        GV_DestroyOtherActor(work->manager2);
    }

    if (work->head_hidden)
    {
        GM_FreeObject((OBJECT *)&work->object);
        EQ_VisibleHead(work->parent_obj, &work->saved_n_packs, &work->saved_raise);
    }
}

STATIC int goggleir_GetResources(GoggleIrWork *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    if (parent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots(obj, GV_StrCode("goggles"), 877, 0);
        if (!obj->objs)
        {
            return -1;
        }
        GM_ConfigObjectRoot((OBJECT *)obj, parent, 6);
        if (parent->light)
        {
            GM_ConfigObjectLight((OBJECT *)obj, parent->light);
        }
        work->parent_obj = parent;
        EQ_InvisibleHead(parent, &work->saved_n_packs, &work->saved_raise);
        work->head_hidden = TRUE;
    }

    work->manager2 = NewGoggleManager(ITEM_THERM_G);
    if (!work->manager2)
    {
        return -1;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewGoggleIr(CONTROL *control, OBJECT *parent_obj, int num_parent)
{
    GoggleIrWork *work = (GoggleIrWork *)GV_NewActor(EXEC_LEVEL, sizeof(GoggleIrWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&goggleir_Act,
                         (GV_ACTFUNC)&goggleir_Die, "goggleir.c");

        if (goggleir_GetResources(work, parent_obj) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    work->control = control;
    work->field_50 = 0;

    return &work->actor;
}
