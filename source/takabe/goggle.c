#include "goggle.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/map.h"
#include "equip/equip.h"
#include "scn_mask.h"

extern int DG_CurrentGroupID;
extern u_long DG_PaletteBuffer_800B3818[256];

/*---------------------------------------------------------------------------*/
// night vision goggles (screen effect)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define GOGGLES_MODEL   GV_StrCode("goggles")
#define MODEL_FLAGS     ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

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
    short          saved_n_packs;
    short          saved_raise;
} Work;

/*---------------------------------------------------------------------------*/

STATIC RECT rect_8009F704 = {768, 226, 256, 2};
STATIC RECT rect_8009F70C = {768, 196, 256, 2};

// Uses RGBA5551 format
static u_short PaletteConvert(u_short value)
{
    int r,g,b,a;
    int r2;

    if ((value & 0x7fff) == 0)
    {
        return value;
    }

    r = value & 0x001f;
    r2 = r;

    g = (value & 0x03e0) >> 5;
    if (r2 < g) r2 = g;

    b = (value & 0x7c00) >> 10;
    if (r2 < b) r2 = b;

    a = value & 0x8000;

    r2 <<= 1;
    if (r2 > 31) r2 = 31;

    r = r2;
    g = r;
    b = r;

    return r | g << 5 | b << 10 | a;
}

static void PaletteCallback(void)
{
    int i, j;
    u_short *ptr;

    rect_8009F704.y = 226;
    rect_8009F70C.y = 196;

    for (i = 15; i > 0; i--) {
        DrawSync(0);
        StoreImage2(&rect_8009F70C, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        ptr = (u_short *)DG_PaletteBuffer_800B3818;

        for (j = 512; j > 0; j--) {
            *ptr++ = PaletteConvert(*ptr);
        }

        LoadImage2(&rect_8009F704, DG_PaletteBuffer_800B3818);

        rect_8009F70C.y += 2;
        rect_8009F704.y += 2;
    }
}

static void Act(Work *work)
{
    DG_OBJS *objs;
    int      new_map;

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

    if (work->counter == 2)
    {
        GM_GameStatus |= STATE_NVG;
        DG_SetExtPaletteMakeFunc(PaletteCallback, PaletteConvert);
        // night vision screen effect
        work->screen_mask = NewNightVisionScreen(SCREEN_MASK_NV_MODE);
    }

    if (work->counter < 11)
    {
        work->counter++;
    }
}

static void Die(Work *work)
{
    GM_GameStatus &= ~STATE_NVG;
    DG_ResetExtPaletteMakeFunc();

    if (work->screen_mask)
    {
        GV_DestroyOtherActor(work->screen_mask);
    }

    if (work->manager)
    {
        GV_DestroyOtherActor(work->manager);
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

    work->manager = NewGoggleManager(IT_NVG);
    if (!work->manager)
    {
        return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewGoggle(CONTROL *control, OBJECT *parent_obj, int num_parent)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "goggle.c");

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
