#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern Anim_Data stru_8009F774;

void sub_8007E0AC(int y, SVECTOR *pVec)
{
    int i; // $s2
    SVECTOR vec[2]; // [sp+10h] [-B0h] BYREF
    anime_data_0x14 data[8]; // [sp+20h] [-A0h] BYREF

    vec[0].vx = 0;
    vec[0].vy = y;
    vec[0].vz = 0;
    vec[1] = DG_ZeroVector_800AB39C;
    
    for (i = 0; i < 8; i++)
    {
        data[i].field_0_vec = *pVec;

        vec[1].vx = GV_RandU_80017090(64);
        vec[1].vz = GV_RandU_80017090(64);
        vec[0].vz += 512;

        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &vec[0]);
        DG_PutVector_8001BE48(&vec[1], &data[i].field_8_vec, 1);
        data[i].field_10_anim_idx = 0;
    }
    
    stru_8009F774.field_14 = data;
    anime_init_8005FBC8(0, 0, &stru_8009F774);
}
