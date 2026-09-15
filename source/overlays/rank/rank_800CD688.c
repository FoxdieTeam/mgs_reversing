#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800CD688(int idx, int param_2, int param_3, int divisor, SELECT_INFO *field_14)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &rank_dword_800E189C->field_0_array[idx];
    pUnk = &rank_dword_800E189C->field_220_unk1;

    pElem->field_8_pFn = rank_800CD474;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_14 = (int)field_14;
    pElem->field_4 = divisor;
}
