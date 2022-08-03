#include "actor.h"
#include "kogaku2.h"

extern int GV_Clock_800AB920;
extern int GM_GameStatus_800AB3CC;

void EQ_InvisibleUnit_80060E68(DG_OBJS* param_1, int param_2, int param_3);
void DG_WriteObjPacketUV_8001A774(DG_OBJ *pObj, int idx);
void DG_FreeObjsPacket_8001ABA8(DG_OBJS *pObjs, int idx);

#pragma INCLUDE_ASM("asm/Equip/kogaku2_tpage_uv_update_80060F98.s") // 268 bytes
POLY_GT4* kogaku2_tpage_uv_update_80060F98(POLY_GT4 *pPrims, int pack_count);

#pragma INCLUDE_ASM("asm/Equip/kogaku2_tpage_uv_rgb_update_800610A4.s") // 352 bytes
POLY_GT4* kogaku2_tpage_uv_rgb_update_800610A4(POLY_GT4 *pPack, int pack_count, int ypos);

void kogaku2_update_prims1_80061204(Actor_kogaku2 *pActor)
{
    DG_OBJS *objs; // $v0
    int n_models; // $s2
    DG_OBJ *i; // $s1
    POLY_GT4 *pPack; // $v0
    DG_OBJ *j; // $s0

    objs = pActor->field_20_pObj->objs;
    n_models = objs->n_models;
    for ( i = objs->objs; n_models > 0; ++i )
    {
        pPack = i->packs[1 - GV_Clock_800AB920];
        if ( pPack )
        {
            for ( j = i; j; j = j->extend )
            {
                pPack = kogaku2_tpage_uv_update_80060F98(pPack, j->n_packs);
            }
        }
        --n_models;
    }
}

void kogaku2_update_prims2_800612BC(Actor_kogaku2 *pActor)
{
    DG_OBJS *objs; // $v0
    int n_models; // $s2
    DG_OBJ *i; // $s1
    POLY_GT4 *pPack; // $v0
    DG_OBJ *j; // $s0

    objs = pActor->field_20_pObj->objs;
    n_models = objs->n_models;
    for ( i = objs->objs; n_models > 0; ++i )
    {
        pPack = i->packs[1 - GV_Clock_800AB920];
        if ( pPack )
        {
            for ( j = i; j; j = j->extend )
            {
                pPack = kogaku2_tpage_uv_rgb_update_800610A4(pPack, j->n_packs, pActor->field_2C_ypos2);
            }
        }
        --n_models;
    }
}

void kogaku2_kill_helper_80061384(Actor_kogaku2 *pActor)
{
    DG_OBJS *objs; // $a2
    DG_OBJ *pIter; // $s0
    int n_models; // $s1

    objs = pActor->field_20_pObj->objs;
    pIter = objs->objs;
    n_models = objs->n_models;
    objs->flag = (objs->flag & 0x80) | (pActor->field_28_obj_old_flag & ~0x80u);
    while ( n_models > 0 )
    {
        DG_WriteObjPacketUV_8001A774(pIter, 0);
        DG_WriteObjPacketUV_8001A774(pIter, 1);
        ++pIter;
        --n_models;
    }
}

void kogaku2_act_nullsub_800615F4(Actor_kogaku2 *pActor);
void kogaku2_act_helper_80061528(Actor_kogaku2 *pActor);

void kogaku2_act_800613FC(Actor_kogaku2 *pActor)
{
    int field_2C_ypos2 = pActor->field_2C_ypos2;
    if ( pActor->field_30_ypos1 < field_2C_ypos2 )
    {
        pActor->field_2C_ypos2 = field_2C_ypos2 - pActor->field_38_ninja_var;
        kogaku2_update_prims2_800612BC(pActor);
        
        field_2C_ypos2 = pActor->field_2C_ypos2;
        if ( pActor->field_30_ypos1 >=field_2C_ypos2 )
        {
            EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 0);
        }
    }
    else
    {
        EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 1);
        kogaku2_update_prims1_80061204(pActor);
       
    }
    if ( (GM_GameStatus_800AB3CC & 8) != 0 )
    {
        pActor->field_20_pObj->objs->flag = pActor->field_28_obj_old_flag;
        DG_FreeObjsPacket_8001ABA8(pActor->field_20_pObj->objs, 0);
        DG_FreeObjsPacket_8001ABA8(pActor->field_20_pObj->objs, 1);
        pActor->field_0_actor.mFnUpdate = (TActorFunction)kogaku2_act_helper_80061528;
        pActor->field_0_actor.mFnShutdown = (TActorFunction)kogaku2_act_nullsub_800615F4;
    }
}

void kogaku2_kill_80061508(Actor_kogaku2 *pActor)
{
    kogaku2_kill_helper_80061384(pActor);
}

void kogaku2_act_helper_80061528(Actor_kogaku2 *pActor)
{
    if ( !(GM_GameStatus_800AB3CC & 8) )
    {
        pActor->field_20_pObj->objs->flag &= ~8u;
        pActor->field_20_pObj->objs->flag &= ~0x10u;
        pActor->field_20_pObj->objs->flag |= 0x20u;
        EQ_InvisibleUnit_80060E68(pActor->field_20_pObj->objs, pActor->field_40_rgb, 0);
        pActor->field_0_actor.mFnUpdate = (TActorFunction)kogaku2_act_800613FC;
        pActor->field_0_actor.mFnShutdown = (TActorFunction)kogaku2_kill_80061508;
    }
    else
    {
        pActor->field_2C_ypos2 = pActor->field_30_ypos1;
    }
}

void kogaku2_act_nullsub_800615F4(Actor_kogaku2 *pActor)
{
}

#pragma INCLUDE_ASM("asm/Equip/NewKogaku2_800615FC.s") // 268 bytes
#pragma INCLUDE_ASM("asm/Equip/NewKogaku3_80061708.s") // 596 bytes
