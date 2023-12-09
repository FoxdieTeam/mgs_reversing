#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "../select1/Game/select.h"

GV_ACT *NewVibEdit_800C47B4(int flags, int perms);

GCL_ActorTableEntry selectOverlayCharas[] =
{
    { CHARA_SELECT, NewSelect_800c3434 },
    { CHARA_VIB_EDIT, (TGCL_ActorCreateFn)NewVibEdit_800C47B4 },
    { 0, NULL }
};
