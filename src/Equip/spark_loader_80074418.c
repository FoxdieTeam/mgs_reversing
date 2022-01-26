#include "linker.h"
#include "libdg.h"
#include "map.h"
#include "actor.h"
#include <libgpu.h>

void spark_loader4_80074234(POLY_FT4 *pPoly, int count, DG_TEX *pTex);
void spark_800742F0(POLY_FT4 *pPoly, int count, int a3);
void spark_loader2_80073DB0();
void spark_loader3_80073E48(int *a1, SVECTOR *a2, int a3, int a4);

extern int GV_StrCode_80016CCC(const char *string);

DG_PRIM *DG_Prim_Alloc_8001BABC(int type, int prim_count, int chanl, SVECTOR *pRect, RECT *a5);
void DG_SetPos_8001BC44(MATRIX *);
void DG_MovePos_8001BD20(SVECTOR *svector);
void ReadRotMatrix_80092DD8(MATRIX *m);
int DG_QueuePrim_80018274(DG_OBJS *pPrim);
void DG_PutPrim_8001BE00(MATRIX *matrix);
extern DG_TEX *DG_FindTexture_8001D830(int);

struct Actor_Spark
{
    Actor field_0_actor;
    int field_20;
    DG_PRIM *field_24_pPrim;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    SVECTOR field_68;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
    int field_90;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int field_108;
    int field_10C;
    int field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    int field_128;
    int field_12C;
    int field_130;
    int field_134;
    int field_138;
    int field_13C;
    int field_140;
    int field_144;
    int field_148;
    int field_14C;
    int field_150;
    int field_154;
    int field_158;
    int field_15C;
    int field_160;
    int field_164;
    short field_168;
    short field_16A;
    short field_16C;
    short field_16E;
    int field_170_counter;
};

static inline void DG_GroupPrim(prim, group_id)
    DG_PRIM *prim;
int group_id;
{
    prim->group_id = group_id;
}
static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap_800AB9B0;
};

extern const char aSparkFl[];
int spark_loader_80074418(struct Actor_Spark *pActor, MATRIX *a2, int a3)
{
    DG_TEX *pTexture;
    DG_PRIM *pNewPrim;

    pActor->field_20 = GM_CurrentMap_800AB9B0;
    spark_loader2_80073DB0();
    spark_loader3_80073E48(&pActor->field_28, &pActor->field_68, 8, a3);
    pNewPrim = DG_Prim_Alloc_8001BABC(18, 8, 0, &pActor->field_68, 0);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS *)pNewPrim);
        DG_GroupPrim(pNewPrim, GM_CurrentMap_800AB9B0);
    }

    pActor->field_24_pPrim = pNewPrim;
    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos_8001BC44(a2);
    DG_PutPrim_8001BE00(pNewPrim);
    pActor->field_168 = a2->t[0];
    pActor->field_16A = a2->t[1];
    pActor->field_16C = a2->t[2];
    pTexture = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aSparkFl));

    if (!pTexture)
    {
        return -1;
    }

    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, pTexture);
    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, pTexture);
    spark_800742F0(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, 0);
    spark_800742F0(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, 0);

    pActor->field_170_counter = 12;
    return 0;
}
