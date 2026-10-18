// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C82B0, camera_800C82EC), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>
#include <string.h>

#include "mgstype.h"
#include "menu/menuman.h"
#include "menu/radio.h"

extern MenuWork Work;
extern char    *MGS_MemoryCardName; /* in main.c */

extern DATA_INFO *vrsave_dword_800D1BEC;
extern int        vrsave_dword_800D1C28;
extern int        vrsave_dword_800D1BF4;
extern short      vrsave_dword_800D1BF0;
extern int        vrsave_dword_800C1AC8; /* index of the selected memory card */
extern char       vrsave_dword_800C1A40[];

void vrsave_800C69E8(void);
void vrsave_800C661C(int mode);
void vrsave_800C8938(MenuWork *work, GV_PAD *pad);
void vrsave_800CA144(MenuWork *work);
void vrsave_800CA2CC(MenuWork *work);

void vrsave_800CA2FC(DATA_INFO *info, int mode)
{
    vrsave_dword_800D1C28 = 0;
    vrsave_dword_800D1BEC = info;
    vrsave_800C69E8();
    vrsave_dword_800C1AC8 = -1;
    strcpy(vrsave_dword_800C1A40, MGS_MemoryCardName);
    vrsave_dword_800C1A40[12] = info->field_0[0];
    vrsave_800C661C(mode);
}

void vrsave_800CA378(DATA_INFO *info, int mission, short score, int mode)
{
    vrsave_dword_800D1BF4 = mission;
    vrsave_dword_800D1BF0 = score;
    vrsave_800CA2FC(info, mode);
}

void vrsave_800CA3A8(DATA_INFO *info, int mission, short score)
{
    vrsave_800CA144(&Work);
    vrsave_800CA378(info, mission, score, 2);
}

void vrsave_800CA404(GV_PAD *pad)
{
    vrsave_800C8938(&Work, pad);
}

void vrsave_800CA42C(void)
{
    vrsave_800CA2CC(&Work);
}
