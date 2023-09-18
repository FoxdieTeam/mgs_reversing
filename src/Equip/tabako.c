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
#include <LIBGPU.H>
#include "Anime/animeconv/anime.h"

// cigarettes

extern const char aCigar[];   // = "cigar"
extern const char aRcmL[];    // = "rcm_l";
extern const char aTabakoC[]; // = "tabako.c"

extern int   GM_GameStatus_800AB3CC;
extern int   GV_Time_800AB330;
extern int   GM_CurrentMap_800AB9B0;

int SECTION(".sbss")    GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

int tabako_dword_8009F2C0 = 0;

void tabako_act_80061EAC(Actor_tabako *pActor)
{
    OBJECT *pObject = &pActor->field_20_obj;
    SVECTOR vec;
    MATRIX  rotMtx;

    GM_SetCurrentMap(pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit);

    GM_ActObject2_80034B88(pObject);

    if ((pActor->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0)
    {
        DG_InvisibleObjs(pObject->objs);
        DG_InvisiblePrim(pActor->field_50_pPrims);
    }
    else
    {
        DG_VisibleObjs(pObject->objs);
        DG_VisiblePrim(pActor->field_50_pPrims);

        DG_SetPos_8001BC44(&pActor->field_50_pPrims->world);
        DG_MovePos_8001BD20(&pActor->field_54_vec);

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
        GM_GameStatus_800AB3CC |= 0x2000000u;
    }
}

void tabako_kill_8006206C(Actor_tabako *pActor)
{
    DG_PRIM *pPrims;

    GM_FreeObject_80034BF8(&pActor->field_20_obj);

    pPrims = pActor->field_50_pPrims;

    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }
}

int tabako_loader_800620B4(Actor_tabako *pActor, OBJECT *pParent, int numParent)
{
    OBJECT *pObject = &pActor->field_20_obj;
    RECT *pRect;
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int i;
    POLY_FT4 *pPoly;
    int u0, v0, u1, v1;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)pObject, GV_StrCode_80016CCC(aCigar), 109, 0);

    if (!pObject->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C(pObject, pParent, numParent);

    pRect = &pActor->field_5C_rect;
    pRect->x = pRect->y = 6;
    pRect->w = pRect->h = 12;

    pActor->field_50_pPrims = pPrim = DG_GetPrim(1042, 1, 0, &pActor->field_54_vec, pRect);

    if (!pPrim)
    {
        return -1;
    }

    pActor->field_54_vec.vx = 37;
    pActor->field_54_vec.vy = -55;
    pActor->field_54_vec.vz = 140;

    pPrim->field_2E_k500 = 250;
    pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aRcmL));

    for (i = 0; i < 2; i++)
    {
        pPoly = &pPrim->field_40_pBuffers[i]->poly_ft4;

        LSTORE(0x808080, &pPoly->r0);

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        u0 = pTex->field_8_offx;
        u1 = u0 + pTex->field_A_width;

        v0 = pTex->field_9_offy;
        v1 = v0 + pTex->field_B_height;

        pPoly->u0 = u0;
        pPoly->v0 = v0;

        pPoly->u1 = u1;
        pPoly->v1 = v0;

        pPoly->u2 = u0;
        pPoly->v2 = v1;

        pPoly->u3 = u1;
        pPoly->v3 = v1;

        pPoly->tpage = pTex->field_4_tPage;
        pPoly->clut = pTex->field_6_clut;
    }

    pActor->field_50_pPrims->root = pActor->field_20_obj.objs->root;
    return 0;
}

GV_ACT * NewTabako_80062274(CONTROL *pCtrl, OBJECT *pParent, int numParent)
{
    Actor_tabako *pActor = (Actor_tabako *)GV_NewActor_800150E4(6, sizeof(Actor_tabako));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)tabako_act_80061EAC,
                                  (TActorFunction)tabako_kill_8006206C, aTabakoC);

        if (tabako_loader_800620B4(pActor, pParent, numParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pParent = pParent;
        pActor->field_4C_numParent = numParent;
    }

    return &pActor->field_0_actor;
}
