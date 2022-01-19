#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"

int Map_Script_tbl_hzd_impl_800310D0(void);

int GCL_Command_hzd_8002BD04(int argc, char **argv)
{
    if (!Map_Script_tbl_hzd_impl_800310D0())
    {
        return -1;
    }
    return 0;
}
