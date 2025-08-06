#include "equip.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"
#include "anime/animconv/anime.h"

/*---------------------------------------------------------------------------*/
// Cigarettes

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    DG_PRIM       *prim;
    SVECTOR        vertex;
    RECT           prim_rect;
} Work;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

int tabako_dword_8009F2C0 = 0;

static void Act(Work *work)
{
    OBJECT_NO_ROTS *object = &work->object;
    SVECTOR         vec;
    MATRIX          rotMtx;

    GM_SetCurrentMap(work->control->map->index);

    GM_ActObject2((OBJECT *)object);

    if ((work->parent->objs->flag & DG_FLAG_INVISIBLE) != 0)
    {
        DG_InvisibleObjs(object->objs);
        DG_InvisiblePrim(work->prim);
    }
    else
    {
        DG_VisibleObjs(object->objs);
        DG_VisiblePrim(work->prim);

        DG_SetPos(&work->prim->world);
        DG_MovePos(&work->vertex);

        ReadRotMatrix(&rotMtx);
        vec.vx = rotMtx.t[0];
        vec.vy = rotMtx.t[1];
        vec.vz = rotMtx.t[2];

        if (GV_Time % 150 >= 121 && tabako_dword_8009F2C0 == 1 &&
            (GM_PlayerStatus & PLAYER_MOVE) == 0)
        {
            NewAnime_8005E6A4(&vec);
        }
    }

    // Snake, smoking is bad for your health!
    if (!(GV_Time & 63) && GM_SnakeCurrentHealth >= 2)
    {
        GM_SnakeCurrentHealth--;
        GM_GameStatus |= STATE_DAMAGED;
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object = &work->object;
    RECT *pRect;
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int i;
    POLY_FT4 *pPoly;
    int u0, v0, u1, v1;

    GM_InitObjectNoRots(object, GV_StrCode("cigar"), 109, 0);

    if (!object->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot((OBJECT *)object, parent, num_parent);

    pRect = &work->prim_rect;
    pRect->x = pRect->y = 6;
    pRect->w = pRect->h = 12;

    work->prim = pPrim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &work->vertex, pRect);

    if (!pPrim)
    {
        return -1;
    }

    work->vertex.vx = 37;
    work->vertex.vy = -55;
    work->vertex.vz = 140;

    pPrim->field_2E_k500 = 250;
    pTex = DG_GetTexture(GV_StrCode("rcm_l"));

    for (i = 0; i < 2; i++)
    {
        pPoly = &pPrim->packs[i]->poly_ft4;

        LSTORE(COLOR_GRAY, &pPoly->r0);

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        u0 = pTex->off_x;
        u1 = u0 + pTex->w;

        v0 = pTex->off_y;
        v1 = v0 + pTex->h;

        pPoly->u0 = u0;
        pPoly->v0 = v0;

        pPoly->u1 = u1;
        pPoly->v1 = v0;

        pPoly->u2 = u0;
        pPoly->v2 = v1;

        pPoly->u3 = u1;
        pPoly->v3 = v1;

        pPoly->tpage = pTex->tpage;
        pPoly->clut = pTex->clut;
    }

    work->prim->root = work->object.objs->root;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewTabako(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "tabako.c");

        if (GetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
    }

    return (void *)work;
}
