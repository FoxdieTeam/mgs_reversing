#include "tabako.h"
#include "Game/control.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "Game/map.h"
#include "psyq.h"
#include <libgpu.h>
#include "Anime/animeconv/anime.h"

// cigarettes

extern int GM_GameStatus_800AB3CC;
extern int GV_Time_800AB330;
extern int GM_CurrentMap_800AB9B0;

int SECTION(".sbss")    GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

int tabako_dword_8009F2C0 = 0;

void tabako_act_80061EAC(TabakoWork *work)
{
    OBJECT_NO_ROTS *pObject = &work->field_20_obj;
    SVECTOR         vec;
    MATRIX          rotMtx;

    GM_SetCurrentMap(work->control->map->index);

    GM_ActObject2_80034B88((OBJECT *)pObject);

    if ((work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0)
    {
        DG_InvisibleObjs(pObject->objs);
        DG_InvisiblePrim(work->field_50_pPrims);
    }
    else
    {
        DG_VisibleObjs(pObject->objs);
        DG_VisiblePrim(work->field_50_pPrims);

        DG_SetPos_8001BC44(&work->field_50_pPrims->world);
        DG_MovePos_8001BD20(&work->field_54_vec);

        ReadRotMatrix(&rotMtx);
        vec.vx = rotMtx.t[0];
        vec.vy = rotMtx.t[1];
        vec.vz = rotMtx.t[2];

        if (GV_Time_800AB330 % 150 >= 121 && tabako_dword_8009F2C0 == 1 &&
            (GM_PlayerStatus_800ABA50 & PLAYER_MOVING) == 0)
        {
            anime_create_8005E6A4(&vec);
        }
    }

    // Snake, smoking is bad for your health!
    if (!(GV_Time_800AB330 & 63) && GM_SnakeCurrentHealth >= 2)
    {
        GM_SnakeCurrentHealth--;
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_26;
    }
}

void tabako_kill_8006206C(TabakoWork *work)
{
    DG_PRIM *pPrims;

    GM_FreeObject_80034BF8((OBJECT *)&work->field_20_obj);

    pPrims = work->field_50_pPrims;

    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }
}

int tabako_loader_800620B4(TabakoWork *work, OBJECT *pParent, int numParent)
{
    OBJECT_NO_ROTS *pObject = &work->field_20_obj;
    RECT *pRect;
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int i;
    POLY_FT4 *pPoly;
    int u0, v0, u1, v1;

    GM_InitObjectNoRots_800349B0(pObject, GV_StrCode("cigar"), 109, 0);

    if (!pObject->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C((OBJECT *)pObject, pParent, numParent);

    pRect = &work->field_5C_rect;
    pRect->x = pRect->y = 6;
    pRect->w = pRect->h = 12;

    work->field_50_pPrims = pPrim = DG_GetPrim(1042, 1, 0, &work->field_54_vec, pRect);

    if (!pPrim)
    {
        return -1;
    }

    work->field_54_vec.vx = 37;
    work->field_54_vec.vy = -55;
    work->field_54_vec.vz = 140;

    pPrim->field_2E_k500 = 250;
    pTex = DG_GetTexture_8001D830(GV_StrCode("rcm_l"));

    for (i = 0; i < 2; i++)
    {
        pPoly = &pPrim->packs[i]->poly_ft4;

        LSTORE(0x808080, &pPoly->r0);

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

    work->field_50_pPrims->root = work->field_20_obj.objs->root;
    return 0;
}

GV_ACT * NewTabako_80062274(CONTROL *pCtrl, OBJECT *pParent, int numParent)
{
    TabakoWork *work = (TabakoWork *)GV_NewActor(6, sizeof(TabakoWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)tabako_act_80061EAC,
                         (TActorFunction)tabako_kill_8006206C, "tabako.c");

        if (tabako_loader_800620B4(work, pParent, numParent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }

        work->control = pCtrl;
        work->field_48_pParent = pParent;
        work->field_4C_numParent = numParent;
    }

    return &work->actor;
}
