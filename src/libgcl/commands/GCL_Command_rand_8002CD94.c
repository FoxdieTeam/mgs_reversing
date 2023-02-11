#include "linker.h"
#include "libgcl/gcl.h"
#include "psyq.h"
#include "Game/linkvarbuf.h"

int GCL_Command_rand_8002CD94(int argc, char **argv)
{
    int param;
    int rand;

    param = GCL_GetNextParamValue_80020AD4();
    rand = rand_8008E6B8();
    GM_LastResultFlag = rand % param;
    return 0;
}
