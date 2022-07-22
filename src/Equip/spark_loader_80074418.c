#include "linker.h"
#include "libdg.h"
#include "map.h"
#include "actor.h"
#include <libgpu.h>

void            spark_loader4_80074234(POLY_FT4 *pPoly, int count, DG_TEX *pTex);
void            spark_800742F0(POLY_FT4 *pPoly, int count, int a3);
void            InitRandamTable_80073DB0();
void            spark_loader3_80073E48(int *a1, SVECTOR *a2, int a3, int a4);

extern int      GV_StrCode_80016CCC(const char *string);

DG_PRIM         *DG_MakePrim_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, RECT *pRect);
void            DG_MovePos_8001BD20(SVECTOR *svector);
void            ReadRotMatrix_80092DD8(MATRIX *m);
int             DG_QueuePrim_80018274(DG_OBJS *pPrim);
void            DG_PutPrim_8001BE00(MATRIX *matrix);
extern DG_TEX   *DG_FindTexture_8001D830(int);

struct          Actor_Spark
{
    Actor       f000_actor;
    int         f020;
    DG_PRIM     *f024_pPrim;
    int         f028;
    int         f02C;
    int         f030;
    int         f034;
    int         f038;
    int         f03C;
    int         f040;
    int         f044;
    int         f048;
    int         f04C;
    int         f050;
    int         f054;
    int         f058;
    int         f05C;
    int         f060;
    int         f064;
    SVECTOR     f068;
    int         f070;
    int         f074;
    int         f078;
    int         f07C;
    int         f080;
    int         f084;
    int         f088;
    int         f08C;
    int         f090;
    int         f094;
    int         f098;
    int         f09C;
    int         f0A0;
    int         f0A4;
    int         f0A8;
    int         f0AC;
    int         f0B0;
    int         f0B4;
    int         f0B8;
    int         f0BC;
    int         f0C0;
    int         f0C4;
    int         f0C8;
    int         f0CC;
    int         f0D0;
    int         f0D4;
    int         f0D8;
    int         f0DC;
    int         f0E0;
    int         f0E4;
    int         f0E8;
    int         f0EC;
    int         f0F0;
    int         f0F4;
    int         f0F8;
    int         f0FC;
    int         f100;
    int         f104;
    int         f108;
    int         f10C;
    int         f110;
    int         f114;
    int         f118;
    int         f11C;
    int         f120;
    int         f124;
    int         f128;
    int         f12C;
    int         f130;
    int         f134;
    int         f138;
    int         f13C;
    int         f140;
    int         f144;
    int         f148;
    int         f14C;
    int         f150;
    int         f154;
    int         f158;
    int         f15C;
    int         f160;
    int         f164;
    short       f168;
    short       f16A;
    short       f16C;
    short       f16E;
    int         f170_counter;
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
    DG_TEX  *pTexture;
    DG_PRIM *pNewPrim;

    pActor->f020 = GM_CurrentMap_800AB9B0;
    InitRandamTable_80073DB0();
    spark_loader3_80073E48(&pActor->f028, &pActor->f068, 8, a3);
    pNewPrim = DG_MakePrim_8001BABC(18, 8, 0, &pActor->f068, 0);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS *)pNewPrim);
        DG_GroupPrim(pNewPrim, GM_CurrentMap_800AB9B0);
    }

    pActor->f024_pPrim = pNewPrim;
    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos_8001BC44(a2);
    DG_PutPrim_8001BE00((MATRIX*)pNewPrim);
    pActor->f168 = a2->t[0];
    pActor->f16A = a2->t[1];
    pActor->f16C = a2->t[2];
    pTexture = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aSparkFl));

    if (!pTexture)
    {
        return -1;
    }

    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, pTexture);
    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, pTexture);
    spark_800742F0(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, 0);
    spark_800742F0(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, 0);

    pActor->f170_counter = 12;
    return 0;
}
