#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern Anim_Data stru_8009F774;

int DM_ThreadStream_80079460(int flag, int unused)
{
    Actor_demothrd *pDemoThrd = (Actor_demothrd *)GV_NewActor_800150E4(1, sizeof(Actor_demothrd));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->field_20_flag = flag;
    pDemoThrd->field_2C_timer_ticks = -1;
    GV_SetNamedActor_8001514C(&pDemoThrd->field_0_actor, (TActorFunction)demothrd_1_80079664,
                              (TActorFunction)demothrd_1_FrameRunDemo_helper_800797CC, aDemothrdC);
    pDemoThrd->field_28_map = GM_CurrentMap_800AB9B0;
    FS_StreamOpen_80024060();
    return 1;
}

#pragma INCLUDE_ASM("asm/Kojo/DM_ThreadFile_800794E4.s")                           // 384 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_80079664.s")                              // 360 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper_800797CC.s")          // 48 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_update_800797FC.s")                         // 356 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_kill_80079960.s")                           // 72 bytes
#pragma INCLUDE_ASM("asm/Kojo/FS_EnableMemfile_800799A8.s")                        // 116 bytes
#pragma INCLUDE_ASM("asm/sub_80079A1C.s")                                          // 16 bytes
#pragma INCLUDE_ASM("asm/sub_80079A2C.s")                                          // 184 bytes
#pragma INCLUDE_ASM("asm/sub_80079AE4.s")                                          // 108 bytes
#pragma INCLUDE_ASM("asm/Kojo/CreateDemo_80079B50.s")                              // 2844 bytes
#pragma INCLUDE_ASM("asm/Kojo/DestroyDemo_8007A66C.s")                             // 732 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_8007A948.s")                 // 1224 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper2_8007AE10.s")         // 8016 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper2_helper_8007CD60.s")  // 152 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper3_8007CDF8.s")         // 284 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper4_8007CF14.s")         // 212 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_8007CFE8.s")         // 1052 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_helper_8007D404.s")  // 1476 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_helper2_8007D9C8.s") // 96 bytes
#pragma INCLUDE_ASM("asm/Kojo/AN_CaterpillerSmoke_8007DA28.s")                     // 108 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_2_8007DA94.s")                              // 400 bytes
#pragma INCLUDE_ASM("asm/Kojo/sub_8007DC24.s")                                     // 348 bytes
#pragma INCLUDE_ASM("asm/sub_8007DD80.s")                                          // 400 bytes
#pragma INCLUDE_ASM("asm/sub_8007DF10.s")                                          // 412 bytes
