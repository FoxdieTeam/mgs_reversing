#include "hzd.h"
#include "idaTypes.h"
extern void     *GV_Malloc_8001620C(int size);
extern void     sub_80021D6C(HZD_HEADER *hzd, int *param_2); // navmeshes

typedef struct      HzdMap
{
    HZD_HEADER      *f00_header;
    HZD_AREA        *f04_area;
    short           f08_areaIndex;
    short           f0A;
    short           f0C;
    short           f0E_n_cameras;
    short           f10_24size;
    short           f12_48size;
    void            *f14_navmeshes;
    HZD_TRP         *f18_traps;
    int             *f1C_pEndOfHzdMap;
    int             *f20_pAfterStructure_24;
    int             *f20_pAfterStructure_48;
} HzdMap; // 28

HzdMap* HZD_Load_Helper_80021AE0(HZD_HEADER *hzd, int areaIndex, int default_48, int default_24)
{
    short           n_navmeshes;
    void            *navmeshes;
    HzdMap          *hzdMap;
    int             i;
    HZD_CAM_TRP     *trig;

    if (*(int*)hzd == 0)
    {
        n_navmeshes = hzd->n_navmeshes;
        if (n_navmeshes > 1)
        {
            navmeshes = GV_Malloc_8001620C((n_navmeshes - 1) * (n_navmeshes - 2) / 2 + (n_navmeshes - 1));
            sub_80021D6C(hzd, navmeshes);
            *(int*)hzd = (int)navmeshes;
        }
    }

    hzdMap = (HzdMap*)GV_Malloc_8001620C((4 * default_24) + sizeof(HzdMap) + (4 * default_48) + (2 * default_48));
    if (hzdMap)
    {
        hzdMap->f1C_pEndOfHzdMap = (void*)&hzdMap[1];
        hzdMap->f20_pAfterStructure_24 = &hzdMap->f1C_pEndOfHzdMap[default_24];
        hzdMap->f20_pAfterStructure_48 = &hzdMap->f20_pAfterStructure_24[default_48];

        hzdMap->f12_48size = default_48;
        hzdMap->f10_24size = default_24;
        hzdMap->f00_header = hzd;
        hzdMap->f04_area = &hzd->areas[areaIndex];
        hzdMap->f0A = 0;
        hzdMap->f0C = 0;
        (int)hzdMap->f14_navmeshes = *(int*)hzd;

        trig = hzdMap->f04_area->trapsAndCameras;
        for (i = hzdMap->f04_area->n_trapsAndCameras; i > 0; i--)
        {
            // stop when we find a camera (traps are stored after cameras)
            if (trig->trap.id2 == (char)-1)
            {
                break;
            }
            trig++;
        }
        hzdMap->f0E_n_cameras = i;
        hzdMap->f18_traps = (HZD_TRP*)trig;
    }

    return hzdMap;
}
