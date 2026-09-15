#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800CD474(MenuPrim *prim, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        rank_800CD178(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16;
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16;
    rank_800CDFC8(prim, (SELECT_INFO *)pUnk->field_14);
}
