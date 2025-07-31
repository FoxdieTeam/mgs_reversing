#include "goggleir.h"
#include "goggle.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/map.h"
#include "linkvar.h"
#include "game/object.h"
#include "equip/equip.h"
#include "scn_mask.h"

extern int DG_CurrentGroupID;
extern int dword_800BDFA8;
extern u_long DG_PaletteBuffer_800B3818[256];

/*---------------------------------------------------------------------------*/
// thermal goggles (screen effect)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define GOGGLES_MODEL   GV_StrCode("goggles")
#define MODEL_FLAGS     ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent_obj;
    int            head_hidden;
    int            counter;
    GV_ACT        *screen_mask;     // NewNightVisionScreen
    GV_ACT        *manager;         // NewGoggleManager
    int            field_5C;
    int            field_60;
    GV_ACT        *manager2;        // NewGoggleManager
    short          saved_n_packs;
    short          saved_raise;
} Work;

/*---------------------------------------------------------------------------*/

STATIC RECT rect_8009F718 = {768, 226, 256, 2};
STATIC RECT rect_8009F720 = {768, 196, 256, 2};

// Uses RGBA5551 format
static u_short PaletteConvert(u_short base)
{
    int r,g,b,a;
    int r2;

    if ((base & 0x7fff) == 0)
    {
        return base;
    }

    r = base & 0x001f;
    r2 = r;

    g = ((base & 0x03E0) >> 5) & 31;
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

static void PaletteCallback(void)
{
    int i, j;
    u_short *ptr;
    u_short color;

    rect_8009F718.y = 226;
    rect_8009F720.y = 196;

    for (i = 15; i > 0; i--)
    {
        DrawSync(0);
        StoreImage2(&rect_8009F720, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        ptr = (u_short *)DG_PaletteBuffer_800B3818;

        for (j = 512; j > 0; j--)
        {
            *ptr++ = PaletteConvert(*ptr);
        }

        if (i == 1)
        {
            color = PaletteConvert(0xffff);
            ptr = (u_short *)&DG_PaletteBuffer_800B3818[248];

            for (j = 16; j > 0; j--)
            {
                *ptr++ = color;
            }
        }

        LoadImage2(&rect_8009F718, DG_PaletteBuffer_800B3818);

        rect_8009F720.y += 2;
        rect_8009F718.y += 2;
    }
}

static void Act(Work *work)
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

    if (work->counter == 3)
    {
        DG_SetExtPaletteMakeFunc(PaletteCallback, PaletteConvert);
        GM_GameStatus |= STATE_THERMG;
        dword_800BDFA8 = 1;
        work->screen_mask = NewNightVisionScreen(SCREEN_MASK_IR_MODE);
    }

    if (work->counter < 11)
    {
        work->counter++;
    }
}

static void Die(Work *work)
{
    GM_GameStatus &= ~STATE_THERMG;
    DG_ResetExtPaletteMakeFunc();

    if (work->screen_mask)
    {
        GV_DestroyOtherActor(work->screen_mask);
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

static int GetResources(Work *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    if (parent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots(obj, GOGGLES_MODEL, MODEL_FLAGS, 0);
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

    work->manager2 = NewGoggleManager(IT_ThermG);
    if (!work->manager2)
    {
        return -1;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewGoggleIr(CONTROL *control, OBJECT *parent_obj, int num_parent)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "goggleir.c");

        if (GetResources(work, parent_obj) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    work->control = control;
    work->counter = 0;

    return (void *)work;
}
