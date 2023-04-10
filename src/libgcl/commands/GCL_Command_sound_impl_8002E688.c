#include "libgcl/libgcl.h"
#include "linker.h"
#include "Game/game.h"

extern int GM_GameOverVox_800AB45C;
extern int dword_800ABA58;

extern int dword_800ABA78[2];
extern int dword_800ABA70;
// Force last 3 variables to use $gp register
int SECTION(".sbss") dword_800ABA78[2];
int SECTION(".sbss") dword_800ABA70;

void GCL_Command_sound_impl_8002E688()
{
    int sdCode, xCode, voxCode, proc;

    if (GCL_GetParam_80020968('b'))
    {
        dword_800ABA78[0] = GCL_GetNextParamValue_80020AD4();
        dword_800ABA78[1] = GCL_GetNextParamValue_80020AD4();
        dword_800ABA70 &= ~1;
    }
    if (GCL_GetParam_80020968('s'))
    {
        sub_8002E508(GCL_GetNextParamValue_80020AD4());
        dword_800ABA70 |= 1;
    }
    if (GCL_GetParam_80020968('c'))
    {
        sdCode = GCL_GetNextParamValue_80020AD4();
        GM_Sound_80032C48(sdCode | 0x1FFFF00, 0);
        if (sdCode == 0x1FFFF01 || sdCode + 0xFE0000FD < 3)
        {
            dword_800ABA70 &= ~2;
        }
        else
        {
            dword_800ABA70 |= 2;
        }
    }
    if (GCL_GetParam_80020968('x'))
    {
        xCode = GCL_GetNextParamValue_80020AD4();
        if (xCode + 0xFE0000F6 < 4)
        {
            dword_800ABA70 |= 1;
        }
        GM_Sound_80032C48(xCode, 0);
    }
    if (GCL_GetParam_80020968('e'))
    {
        GM_SeSet2_80032968(GCL_GetNextParamValue_80020AD4(), GCL_GetNextParamValue_80020AD4(),
                          GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetParam_80020968('v')) // vox
    {
        voxCode = GCL_GetNextParamValue_80020AD4();
        proc = 0;
        if (GCL_GetParam_80020968('f')) // func
        {
            proc = GCL_GetNextParamValue_80020AD4() | 0x80000000;
        }
        GM_VoxStream_80037E40(voxCode, proc);
    }
    if (GCL_GetParam_80020968('g'))
    {
        GM_GameOverVox_800AB45C = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('k'))
    {
        GM_set_noise_sound_8002E588(0);
    }
    if (GCL_GetParam_80020968('r'))
    {
        GM_set_noise_sound_8002E588(1);
    }
    if (GCL_GetParam_80020968('l'))
    {
        GM_set_noise_sound_8002E588(2);
    }
    if (GCL_GetParam_80020968('n'))
    {
        GM_SoundStart_8002E640();
    }
}
