#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"
#include "gcl.h"

void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);

void sub_80037EE0(int, int);
int sub_80037CD8(void);

extern const char aVoxcodeX[];

void sub_80047330(menu_chara_struct *unknown, unsigned char *pScript)
{
    unsigned int voxCode = 
    ((unsigned int)pScript[0] << 0x18) |
    ((unsigned int)pScript[1] << 0x10) |
    ((unsigned int)pScript[2] << 8) |
    ((unsigned int)pScript[3]);
    pScript += sizeof(unsigned int);

    mts_printf_8008BBA0(aVoxcodeX, voxCode);

    if ((unknown->field_18 & 0x100) == 0)
    {
        SwEnterCriticalSection_8009954C();
        sub_80037EE0(voxCode, 0);
        SwExitCriticalSection_8009956C();
        unknown->field_14_bInExecBlock = 1;
        menu_gcl_exec_block_800478B4(unknown, pScript);
        unknown->field_14_bInExecBlock = 0;
        while (sub_80037CD8() != -1) // wait vox finish ?
        {
            mts_wait_vbl_800895F4(2);
        }
    }
    else
    {
        menu_gcl_exec_block_800478B4(unknown, pScript);
    }
}
