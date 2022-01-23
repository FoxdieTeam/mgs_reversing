#include "linker.h"
#include "dgd.h"

extern struct_dg gOts_800B1800[3];

// Force gp usage
extern unsigned short gCurrentRootCnt_800AB984;
unsigned short SECTION(".sbss") gCurrentRootCnt_800AB984;

void DrawOTag_8008FE58(unsigned int *pOt);
unsigned int GetRCnt_800996E8(unsigned int rcnt);

unsigned short SECTION(".gOldRootCnt_800B1DC8") gOldRootCnt_800B1DC8[32];

void DG_DrawOTag_80017E4C(int activeBuffer)
{
    gOldRootCnt_800B1DC8[0] = gCurrentRootCnt_800AB984;
    gCurrentRootCnt_800AB984 = GetRCnt_800996E8(0xF2000001);
    DrawOTag_8008FE58(&gOts_800B1800[0].dword_6BC3D8_dst[activeBuffer][0]);
}
