// vrsave: VR save menu, runs the GCL proc of the chosen menu item.
#include <sys/types.h>

#include "mgstype.h"
#include "libgcl/libgcl.h"
#include "overlays/vrsave/vrsave.h"

void vrsave_800C4E44(VR_SAVEMNGR_ITEM *item)
{
    if (item->proc != 0)
    {
        GCL_ExecProc(item->proc, NULL);
    }
}
