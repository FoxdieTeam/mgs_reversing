#include "game.h"
#include "tabako.h"
#include "Script_tbl_map_8002BB44.h"
#include "GM_Control.h"
#include "map.h"
#include <libgpu.h>

extern void DG_DequeuePrim_800182E0(DG_OBJS *param_1);
extern void DG_FreePrim_8001BC04(int *param_1);
extern void GM_FreeObject_80034BF8(OBJECT *obj);

void GM_ActObject2_80034B88(OBJECT *obj);
void DG_SetPos_8001BC44(MATRIX *);
void DG_MovePos_8001BD20(SVECTOR *svector);
void ReadRotMatrix_80092DD8(MATRIX *m);

extern int game_state_flags_800AB3CC;
extern GameState_800B4D98 gGameState_800B4D98;
extern int gRenderedFramesCount_800AB330;

extern int dword_8009F2C0;

int SECTION(".gSna_init_flags_800ABA50") gSna_init_flags_800ABA50;

int anime_create_8005E6A4(SVECTOR *); // todo: type is prob bigger

extern int GM_CurrentMap_800AB9B0;
int SECTION(".sbss") GM_CurrentMap_800AB9B0;

static inline void GM_SetCurrentMap(map) int map;
{
    GM_CurrentMap_800AB9B0 = map;
}

void tabako_act_80061EAC(Actor_tabako *pActor)
{
    SVECTOR vec;

    MATRIX rotMtx;
    OBJECT *obj;

    obj = &pActor->field_20_pObj;

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

        if (gRenderedFramesCount_800AB330 % 150 >= 121 && dword_8009F2C0 == 1 && (gSna_init_flags_800ABA50 & 0x10) == 0)
        {
            anime_create_8005E6A4(&vec);
        }
    }

    // Snake, smoking is bad for your health!
    if ((gRenderedFramesCount_800AB330 & 63) == 0 && gGameState_800B4D98.field_16_snake_current_health >= 2)
    {
        gGameState_800B4D98.field_16_snake_current_health--;
        game_state_flags_800AB3CC |= 0x2000000u;
    }
}

void tabako_kill_8006206C(Actor_tabako *pActor)
{
    void *iVar1;
    GM_FreeObject_80034BF8(&pActor->field_20_pObj);
    iVar1 = pActor->field_50_prims;
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
}

extern const char aCigar[]; // = "cigar";
extern const char aRcmL[];  // = "rcm_l";


extern DG_TEX *DG_FindTexture_8001D830(int);
void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

extern int GV_StrCode_80016CCC(const char *string);


DG_PRIM *DG_Prim_Alloc_8001BABC(int type, int prim_count, int chanl, SVECTOR *pRect, RECT *a5);

int DG_QueuePrim_80018274(DG_OBJS *pPrim);

static inline void DG_GroupPrim(prim, group_id)
    DG_PRIM *prim;
int group_id;
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

static inline DG_PRIM *test(int type, int prim_count, int chanl, SVECTOR *pRect, RECT *a5)
{
    DG_PRIM *pPrims = DG_Prim_Alloc_8001BABC(type, prim_count, chanl, pRect, a5);
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
