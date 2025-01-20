#include "goggle.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Equip/equip.h"
#include "scn_mask.h"

extern int DG_CurrentGroupID;
extern u_long DG_PaletteBuffer_800B3818[256];

/*---------------------------------------------------------------------------*/
// night vision goggles (screen effect)

typedef struct GoggleWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent_obj;
    int            head_hidden;
    int            field_50;
    GV_ACT        *scn_mask;
    GV_ACT        *manager;
    short          saved_n_packs;
    short          saved_rise;
} GoggleWork;

#define EXEC_LEVEL 6
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

/*---------------------------------------------------------------------------*/

STATIC RECT rect_8009F704 = {768, 226, 256, 2};
STATIC RECT rect_8009F70C = {768, 196, 256, 2};

STATIC u_short goggle_PaletteConvert(u_short value)
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

STATIC void goggle_PaletteCallback(void)
{
    int i, j;
    u_short *ptr;

    rect_8009F704.y = 0xe2;
    rect_8009F70C.y = 0xc4;

    for (i = 15; i > 0; i--) {
        DrawSync(0);
        StoreImage2(&rect_8009F70C, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        ptr = (u_short *)DG_PaletteBuffer_800B3818;

        for (j = 512; j > 0; j--) {
            *ptr++ = goggle_PaletteConvert(*ptr);
        }

        LoadImage2(&rect_8009F704, DG_PaletteBuffer_800B3818);

        rect_8009F70C.y += 2;
        rect_8009F704.y += 2;
    }
}

STATIC void goggle_Act(GoggleWork *work)
{
    DG_OBJS *objs;    // $a1
    int      new_map; // $a0

    if (work->head_hidden)
    {
        objs = work->object.objs;
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

    if (work->field_50 == 2)
    {
        GM_GameStatus |= STATE_NVG;
        DG_SetExtPaletteMakeFunc(goggle_PaletteCallback, goggle_PaletteConvert);
        // night vision screen effect
        work->scn_mask = (GV_ACT *)NewNightVisionScreen(0);
    }

    if (work->field_50 < 11)
    {
        work->field_50++;
    }
}

STATIC void goggle_Die(GoggleWork *work)
{
    GM_GameStatus &= ~STATE_NVG;
    DG_ResetExtPaletteMakeFunc();

    if (work->scn_mask)
    {
        GV_DestroyOtherActor(work->scn_mask);
    }

    if (work->manager)
    {
        GV_DestroyOtherActor(work->manager);
    }

    if (work->head_hidden)
    {
        GM_FreeObject((OBJECT *)&work->object);
        EQ_VisibleHead(work->parent_obj, &work->saved_n_packs, &work->saved_rise);
    }
}

STATIC int goggle_GetResources(GoggleWork *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *obj = &work->object;
    if (parent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots(obj, GV_StrCode("goggles"), BODY_FLAG, 0);
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
        EQ_InvisibleHead(parent, &work->saved_n_packs, &work->saved_rise);
        work->head_hidden = TRUE;
    }

    work->manager = NewGoggleManager(ITEM_N_V_G);
    if (!work->manager)
    {
        return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewGoggle(CONTROL *control, OBJECT *parent_obj, int num_parent)
{
    GoggleWork *work = (GoggleWork *)GV_NewActor(EXEC_LEVEL, sizeof(GoggleWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&goggle_Act,
                         (GV_ACTFUNC)&goggle_Die, "goggle.c");

        if (goggle_GetResources(work, parent_obj) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    work->control = control;
    work->field_50 = 0;

    return &work->actor;
}
