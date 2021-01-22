#include "linker.h"
#include "gcl.h"

extern const char aVarsaveNotVar[];

extern void     mts_printf_8008BBA0(const char*, ...);
unsigned char*  sub_800217F0(unsigned char *);
void            sub_80021314(void);

int Script_tbl_varsave_8002C72C(void)
{
    unsigned char *param;

    param = GCL_Get_Param_Result_80020AA4();
    if (GCL_GetParam_80020968('a'))
    {
        sub_80021314();
        return 0;
    }
    while (*param)
    {
        if ((*param & 0xf0) != 0x10)
        {
            mts_printf_8008BBA0(aVarsaveNotVar);
        }
        param = sub_800217F0(param);
    }
    return 0;
}
