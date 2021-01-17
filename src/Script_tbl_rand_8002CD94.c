#include "linker.h"
#include "gcl.h"
#include "idaTypes.h"

typedef struct
{
    short unknown_1;
    short unknown_2;
    short unknown_3;
    short unknown_4;
    short unknown_5;
    short unknown_6;
} unknown_800B4D98;

unknown_800B4D98 SECTION(".gUnknown_800B4D98") gUnknown_struct_800B4D98;

unsigned int rand_8008E6B8(void);

int Script_tbl_rand_8002CD94(unsigned char *pScript)
{
    int param;
    int rand;

    param = GCL_Get_Param_80020AD4();
    rand = rand_8008E6B8();
    gUnknown_struct_800B4D98.unknown_6 = (short)(rand % param);
    return 0;
}
