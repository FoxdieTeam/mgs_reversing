#include "game.h"
#include "tabako.h"
#include "Script_tbl_map_8002BB44.h"
#include "GM_Control.h"
#include "map.h"

extern void DG_DequeuePrim_800182E0(int *param_1);
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
//int SECTION(".data") dword_8009F2C0 = 0;

int SECTION(".gSna_init_flags_800ABA50") gSna_init_flags_800ABA50;

int anime_create_8005E6A4(SVECTOR *); // todo: type is prob bigger

/*
void tabako_act_80061EAC(Actor_tabako *pActor)
{
     SVECTOR vec;
 
    MATRIX rotMtx;

   
    struct map_record* pMap = pActor->field_44_pCtrl->field_2C_map;

    GM_CurrentMap_800AB9B0 = pMap->field_0_map_index_bit;
    GM_ActObject2_80034B88(&pActor->field_20_pObj);

    if ((pActor->field_48_pObj->objs->flag & 0x80) != 0)
    {
        pActor->field_20_pObj.objs->flag |= 0x80u;
        pActor->field_50_prims->type |= 0x100u;
    }
    else
    {
        pActor->field_20_pObj.objs->flag &= ~0x80u;
        pActor->field_50_prims->type &= ~0x100u;

        DG_SetPos_8001BC44(&pActor->field_50_prims->world);
        DG_MovePos_8001BD20(&pActor->field_54_vec);

        ReadRotMatrix_80092DD8(&rotMtx);
        vec.vy = rotMtx.t[1];
        vec.vx = rotMtx.t[0];
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
*/

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
