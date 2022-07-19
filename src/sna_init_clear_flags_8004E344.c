#include "sna_init.h"

void sna_init_clear_flags_8004E344(Actor_SnaInit* pActor, unsigned int flags)
{
    // TODO: Using pActor->field_898_flags doesn't match for some reason
    *(unsigned int *)((char*)pActor + 0x898) = *(unsigned int *)((char*)pActor + 0x898) & ~flags;
}
