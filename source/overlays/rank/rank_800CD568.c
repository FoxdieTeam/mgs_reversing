#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800CD568(int idx, int param_2, int param_3, int divisor, int idx2)
{
    RadioFileModeUnk2     *pUnk;
    RadioFileModeStruElem *pElem;

    pUnk = &rank_dword_800E189C->field_c0_array[idx];
    pElem = &rank_dword_800E189C->field_0_array[idx];

    pUnk->field_4 = (const char *)((int *)&rank_dword_800C330C)[idx2];

    pElem->field_8_pFn = rank_800CD1A8;
    pElem->field_C_unk1 = (RadioFileModeUnk1 *)pUnk;

    if (idx2 < 0)
    {
        pElem->field_0 = 0;
        return;
    }

    if (divisor <= 0)
    {
        pUnk->field_8 = param_2 * 65536;
        pUnk->field_10 = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_C = (param_2 * 65536 - pUnk->field_8) / divisor;
        pUnk->field_14 = (param_3 * 65536 - pUnk->field_10) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_18 = 0x748956;
    pElem->field_4 = divisor;
}
