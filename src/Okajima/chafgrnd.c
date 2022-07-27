#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern unsigned int GV_RandU_80017090(unsigned int input);

void chafgrnd_init_tiles_800769EC(TILE* a1)
{
    TILE* pIter = a1;
    int i;
    unsigned int rand_width, rand_height;
	
    for ( i = 64; i > 0; i-- )
    {
        setTile(pIter);
        rand_width = GV_RandU_80017090(2) + 1;
        rand_height = GV_RandU_80017090(2) + 1;
        setWH(pIter, rand_width, rand_height);
        pIter++;
    }
}

#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A6C.s")
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A98.s")
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_80076B28.s")
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_loader_80077014.s")
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_kill_8007721C.s")
#pragma INCLUDE_ASM("asm/Okajima/NewChaffGrd_80077264.s")
