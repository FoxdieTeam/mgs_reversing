#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"

void rank_800CDB1C(SPRT *sprt)
{
    LSTORE(0x80808080, &sprt->r0);
    setSprt(sprt);
    setClut(sprt, 960, 510);
}
