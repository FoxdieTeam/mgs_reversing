#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800CD8F0(int param_1, int param_2, int param_3, int param_4, int divisor)
{
    RadioFileModeStruElem *pElem;
    RadioFileModeUnk1     *pUnk;

    pElem = &rank_dword_800E189C->field_0_array[11];
    pUnk = (RadioFileModeUnk1 *)&rank_dword_800E189C->field_220_unk1.field_18;

    pElem->field_8_pFn = rank_800CD32C;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_1 * 65536;
        pUnk->field_C = param_2 * 65536;
        pUnk->field_14 = param_3 * 65536;
        pUnk->field_1C = param_4 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_1 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_2 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_3 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_4 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pElem->field_4 = divisor;
}
