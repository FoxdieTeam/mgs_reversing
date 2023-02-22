#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

void sub_8004A648(MenuGlue *, int *);

void sub_8004ABF0(int param_1, int param_2, int param_3, int param_4, int divisor)

{
    RadioFileModeStruElem *pElem = &stru_800ABB7C->field_0_array[11];

    // TODO: WTF??? Why is it reinterpreting a middle of RadioFileModeUnk1 as another RadioFileModeUnk1,
    // going past the memory of original RadioFileModeUnk1?
    RadioFileModeUnk1 *pUnk = (RadioFileModeUnk1 *)&(stru_800ABB7C->field_220_unk1).field_18;

    pElem->field_8_pFn = sub_8004A648;
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
