#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "libgcl/gcl.h"

struct map_record *GCL_Command_hzd_impl_800310D0(void);

int GCL_Command_hzd_8002BD04(int argc, char **argv)
{
    if (!GCL_Command_hzd_impl_800310D0())
    {
        return -1;
    }
    return 0;
}
