#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"
#include "gcl.h"

void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);

void sub_80037EE0(int, int);
int sub_80037CD8(void);

extern const char aVoxcodeX[];

#define MakeVoxCode(x) ((unsigned int)x[0] << 0x18) |     \
                           ((unsigned int)x[1] << 0x10) | \
                           ((unsigned int)x[2] << 8) |    \
                           ((unsigned int)x[3])

void sub_80047330(menu_chara_struct *unknown, unsigned char *pScript)
{
    unsigned int voxCode = MakeVoxCode(pScript);
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

void mts_8008C408(int, int);
void mts_8008C454(int, int);
void sub_80032C48(int, int code);

void sub_80047414(menu_chara_struct *unknown, unsigned char *pScript)
{
    unsigned char *pScriptIter;
    int scriptVal;
    int i;

    switch (*pScript)
    {
    case 0x00:
        pScriptIter = pScript;
        pScriptIter++;
        sub_80032C48(MakeVoxCode(pScriptIter), 0);
        break;

    case 0x01:
        scriptVal = pScript[1];
        i = (signed short int)(pScript[3] | (pScript[2] << 8));
        while (i > 0)
        {
            if (scriptVal > 0)
            {
                mts_8008C408(1, 2);
                mts_8008C454(1, scriptVal);
            }
            mts_wait_vbl_800895F4(1);
            i--;
        }
        break;
    }
}
