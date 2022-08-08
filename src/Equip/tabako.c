#include "tabako.h"
#include "Game/GM_Control.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "map/map.h"
#include "psyq.h"
#include <LIBGPU.H>
#include "Anime/animeconv/anime.h"

// cigarettes

/* struct Actor        *GV_NewActor_800150E4(int level, int memSize); */

extern const char aTabakoC[]; // = "tabako.c"
extern const char aCigar[];   // = "cigar";
extern const char aRcmL[];    // = "rcm_l";

extern int                GM_GameStatus_800AB3CC;
extern GameState_800B4D98 gGameState_800B4D98;
extern int                GV_Time_800AB330;
extern int                dword_8009F2C0;
extern int                GM_CurrentMap_800AB9B0;

int                     SECTION(".sbss") GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

static inline void GM_SetCurrentMap(map) int map;
{
    GM_CurrentMap_800AB9B0 = map;
}

void tabako_act_80061EAC(Actor_tabako *pActor)
{
    SVECTOR vec;
    MATRIX  rotMtx;
    OBJECT *obj;

    obj = (OBJECT *)&pActor->field_20_pObj;

    GM_SetCurrentMap(pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit);

    GM_ActObject2_80034B88(obj);

    if ((pActor->field_48_pObj->objs->flag & 0x80) != 0)
    {
        obj->objs->flag |= 0x80u;
        pActor->field_50_prims->type |= 0x100u;
    }
    else
    {
        obj->objs->flag &= ~0x80u;
        pActor->field_50_prims->type &= ~0x100u;

        DG_SetPos_8001BC44(&pActor->field_50_prims->world);
        DG_MovePos_8001BD20(&pActor->field_54_vec);

        ReadRotMatrix_80092DD8(&rotMtx);
        vec.vx = rotMtx.t[0];
        vec.vy = rotMtx.t[1];
        vec.vz = rotMtx.t[2];

        if (GV_Time_800AB330 % 150 >= 121 && dword_8009F2C0 == 1 &&
            (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_MOVING) == 0)
        {
            anime_create_8005E6A4(&vec);
        }
    }

    // Snake, smoking is bad for your health!
    if ((GV_Time_800AB330 & 63) == 0 && gGameState_800B4D98.field_16_snake_current_health >= 2)
    {
        gGameState_800B4D98.field_16_snake_current_health--;
        GM_GameStatus_800AB3CC |= 0x2000000u;
    }
}

void tabako_kill_8006206C(Actor_tabako *pActor)
{
    void *prims;

    GM_FreeObject_80034BF8((OBJECT *)&pActor->field_20_pObj);
    prims = pActor->field_50_prims;
    if (prims)
    {
        DG_DequeuePrim_800182E0(prims);
        DG_FreePrim_8001BC04(prims);
    }
}

static inline void DG_GroupPrim(prim, group_id) DG_PRIM *prim;
int                group_id;
{
    prim->group_id = group_id;
}

/*
static inline void DG_SetPacketTexture4(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1

    t_u0 = tex->field_8_offx;
    t_u1 = t_u0 + tex->field_A_width;

    t_v0 = tex->field_9_offy;
    t_v2 = t_v0 + tex->field_B_height;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->field_4_tPage;
    prims->clut = tex->field_6_clut;
}

static inline DG_PRIM *test(int type, int prim_count, int chanl, SVECTOR *pVec, RECT *pRect)
{
    DG_PRIM *pPrims = DG_MakePrim_8001BABC(type, prim_count, chanl, pVec, pRect);
    if (pPrims) // beqz		$s0, 0xc0
    {
        DG_QueuePrim_80018274((DG_OBJS *)pPrims);
        // sh		$v0, 0x28($s0)
        DG_GroupPrim(pPrims, GM_CurrentMap_800AB9B0);
        // missing: move    $v0, $s0
    }
    return pPrims;
}

int tabako_loader_800620B4(Actor_tabako *pActor, OBJECT *pObj, int a3)
{
    DG_PRIM *pPrims;  // $v0
    DG_PRIM *_pPrims; // $v0

    DG_TEX *Texture_8001D830; // $a3
    int pack_idx;             // $t1
    DG_PRIM *pPrimIter;       // $t0
    int ret;

    GM_InitObjectNoRots_800349B0(&pActor->field_20_pObj, GV_StrCode_80016CCC(aCigar), 0x6D, 0);
    if (!pActor->field_20_pObj.objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C(&pActor->field_20_pObj, pObj, a3);

    {
        RECT *pRect;
        pRect = &pActor->field_5C_unknown;
        pRect->y = 6;
        pRect->x = 6;
        pRect->h = 12;
        pRect->w = 12;
    }

    ret = 0;

    pActor->field_50_prims = test(1042, 1, 0, &pActor->field_54_vec, &pActor->field_5C_unknown);
    _pPrims = pActor->field_50_prims;
    if (!pActor->field_50_prims) // bnez		$v0, 0xd0
    {
        ret = -1;
        return ret;
    }
    pPrims = pActor->field_50_prims;

    pActor->field_54_vec.vx = 37;
    pActor->field_54_vec.vy = -55;
    pActor->field_54_vec.vz = 140;

    pPrims->field_2E_k500 = 250;

    Texture_8001D830 = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aRcmL));
    pack_idx = 0;
    pPrimIter = _pPrims;
    do
    {
        union Prim_Union *prims = pPrimIter->field_40_pBuffers[0];
        *(int *)&prims->poly_ft4.r0 = 0x808080; // 	sw		$t2, 4($v0)
        setPolyFT4(&prims->poly_ft4);           // 7
        setSemiTrans(&prims->poly_ft4, 1);      // 3 ?
        DG_SetPacketTexture4(&prims->poly_ft4, Texture_8001D830);
        pPrimIter = (DG_PRIM *)((char *)pPrimIter + 4);
        pack_idx++;
    } while (pack_idx < 2);

    pActor->field_50_prims->root = pActor->field_20_pObj.objs->root;
    return ret;
}
*/

#pragma INCLUDE_ASM("asm/Equip/tabako_loader_800620B4.s") // 448 bytes

Actor_tabako *NewTabako_80062274(GM_Control *pCtrl, OBJECT *pObj, int a3)
{
    Actor_tabako *pActor;

    pActor = (Actor_tabako *)GV_NewActor_800150E4(6, sizeof(Actor_tabako));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)tabako_act_80061EAC,
                                  (TActorFunction)tabako_kill_8006206C, aTabakoC);
        if (tabako_loader_800620B4(pActor, pObj, a3) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pObj = pObj;
        pActor->field_4C_unknown = a3;
    }
    return pActor;
}
