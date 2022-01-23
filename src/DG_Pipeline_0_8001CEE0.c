#include "linker.h"
#include "libdg.h"
#include "dgd.h"

void DG_800174DC(MATRIX* m);
void sub_8001CDB8(DG_OBJS* pObj);

void DG_Pipeline_0_8001CEE0(struct_dg *pOt, int idx)
{
    DG_OBJS **mQueue; // $s1
    int i;            // $s0
    DG_OBJS *v10;     // $a0

    mQueue = pOt->mQueue;

    *((MATRIX*)0x1F800000) = pOt->field_10_matrix;
    DG_800174DC((MATRIX *)0x1F800000);

    for (i = pOt->mTotalObjectCount; i > 0; --i)
    {
        v10 = *mQueue++;
        sub_8001CDB8(v10);
    }
}

void sub_8001CF80()
{

}