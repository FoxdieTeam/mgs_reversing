#include "game/game.h"
#include "bullet/blast.h"
#include "okajima/splash2.h"

extern void sub_8007DC24(SVECTOR *pPosition);
extern void sub_8007DD80(short param_1, SVECTOR *pPos);
extern void sub_8007DF10(SVECTOR *pRotation, SVECTOR *pTranslation);
extern void sub_8007E0AC(int y, SVECTOR *pPosition);

typedef struct _Work
{
    GV_ACT  actor;     /* 0x00 */
    int     field_20;  /* 0x20 */
    int     field_24;  /* 0x24 */
    SVECTOR field_28;  /* 0x28 */
    SVECTOR field_30;  /* 0x30 */
    int     field_38;  /* 0x38 */
    int     field_3C;  /* 0x3C */
} Work;

extern const char s05a_dword_800E34E8[]; /* = "m1e1smke.c" */

void s05a_800DC058(Work *work);
void s05a_800DC224(void *work);

void *s05a_800DBF58(int arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    work->field_24 = arg0;
    work->field_20 = GM_CurrentMap;
    work->field_28 = *arg1;
    work->field_30 = *arg2;
    work->field_3C = 0;
    switch (work->field_24)
    {
    case 0:
        work->field_38 = 0x3C;
        break;
    case 1:
        work->field_38 = 0xA;
        break;
    }
    GV_SetNamedActor(work, s05a_800DC058, s05a_800DC224, s05a_dword_800E34E8);

    return work;
}

void s05a_800DC058(Work *work)
{
    SVECTOR vec;

    GM_CurrentMap = work->field_20;
    switch (work->field_24)
    {
    case 0:
        if (work->field_38 == 0x39)
            sub_8007DF10(&work->field_30, &work->field_28);
        if ((work->field_3C / 4) * 4 == work->field_3C - 1)
        {
            if (work->field_38 >= 0x24)
                sub_8007E0AC(work->field_30.vy, &work->field_28);
        }
        if ((work->field_3C & 3) == 0)
        {
            if (work->field_38 >= 0x29)
                sub_8007DD80(work->field_30.vy, &work->field_28);
        }
        break;
    case 1:
        if (work->field_38 == 5)
        {
            DG_SetPos2(&DG_ZeroVector, &work->field_30);
            memset(&vec, 0, 8);
            vec.vx = -227;
            DG_RotatePos(&vec);
            memset(&vec, 0, 8);
            vec.vz = 0x258;
            DG_PutVector(&vec, &vec, 1);
            AN_Blast_high2(&work->field_28, &vec);
        }
        if (work->field_38 >= 7)
            NewSplash2_800DB5E4(&work->field_30, &work->field_28);
        if ((work->field_3C & 3) == 0)
            sub_8007DC24(&work->field_28);
        break;
    }
    if (--work->field_38 < 0)
        GV_DestroyActor(work);
    if ((work->field_38 & 1) == 0)
        work->field_3C++;
}

void s05a_800DC224(void *work)
{
    /* do nothing */
}
