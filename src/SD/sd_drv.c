#include "SD/sd.h"

extern int sng_status_800BF158;
extern int sng_fout_term_800C0518;
extern int sng_fade_time_800C0430[14];
extern int sd_KaihiMode_800BF05C;

#pragma INCLUDE_ASM("asm/SD/IntSdMain_80084494.s")
#pragma INCLUDE_ASM("asm/SD/SD_SongFadeIn_80084CCC.s")

int SngFadeOutP_80084D60(unsigned int a1)
{
    int temp; // $a1
    int i; // $v1

    if ( sng_status_800BF158 && sng_fout_term_800C0518 != 0x1FFF )
    {
        switch (a1)
        {
            case 0x1FFFF06: temp = 1310; break;
            case 0x1FFFF07: temp = 655; break;
            case 0x1FFFF08: temp = 218; break;
            case 0x1FFFF09: temp = 131; break;
            //default: temp = 0; break; // we like UB
        }

        if ( !temp )
        {
            temp = 1;
        }

        for (i = 0; i < 13; i++)
        {
            if ( ((sng_fout_term_800C0518 >> i) & 1) == 0 )
            {
                sng_fade_time_800C0430[i] = temp;
            }
        }
        
        sd_KaihiMode_800BF05C = 0;
        return 0;
    }
    else
    {
        return -1;
    }
}

#pragma INCLUDE_ASM("asm/SD/SD_SongFadeoutAndStop_80084E48.s")
#pragma INCLUDE_ASM("asm/SD/SD_SongKaihiMode_80084F88.s")
#pragma INCLUDE_ASM("asm/SD/SD_80085020.s")
#pragma INCLUDE_ASM("asm/SD/SD_80085164.s")
#pragma INCLUDE_ASM("asm/SD/SD_80085480.s")
#pragma INCLUDE_ASM("asm/SD/SD_800854F0.s")
#pragma INCLUDE_ASM("asm/SD/SD_8008559C.s")
#pragma INCLUDE_ASM("asm/SD/sng_adrs_set_80085658.s")
#pragma INCLUDE_ASM("asm/SD/SD_8008576C.s")
#pragma INCLUDE_ASM("asm/SD/SD_800859B8.s")
